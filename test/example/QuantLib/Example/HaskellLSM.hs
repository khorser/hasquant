{-# LANGUAGE TemplateHaskell #-}
-- |Benchmarks 'QuantLib.Method.lsmRegress' (the coarsened primitive CLAUDE.md's callback-shape
-- rule prescribes -- one batched regression call per exercise date, using QuantLib's own
-- Eigen-backed least-squares solve) against the naive alternative: the identical backward
-- induction, but with the per-date regression re-implemented from scratch in plain Haskell
-- (normal equations solved by hand-rolled Gauss-Jordan elimination over @[[Double]]@, no
-- optimized linear algebra). QuantLib is used only for path generation -- both loops walk the
-- exact same calibration\/pricing path sets from "QuantLib.Example.AmericanLSM"'s fixture, so
-- any timing difference is the regression implementation, not the paths.
--
-- This is deliberately an apples-to-oranges comparison, not a controlled microbenchmark: the
-- Haskell side uses lists and a textbook (unoptimized, non-pivoted-for-speed) solve, while
-- 'lsmRegress' calls into QuantLib's C++ least-squares machinery. That gap is the point -- it
-- illustrates why CLAUDE.md's "coarsen the language-boundary crossing" pattern reuses QuantLib's
-- own regression primitive instead of shipping the state across the FFI boundary once per path
-- and reimplementing the fit on the Haskell side.
--
-- Every list traversal below is total: no 'head'\/'tail'\/'last'\/'init'\/@(!!)@\/'maximum', and
-- no partial conversion of a plain list into a 'NonEmpty'. Genuinely non-empty-by-construction
-- values (a monomial basis of a given order always has at least one term, the constant) are
-- built directly as a 'NonEmpty' via @(':|')@; everywhere else, list recursion pattern-matches
-- both @[]@ and @(x:xs)@ explicitly (with a defined, if practically unreachable, result for the
-- empty case) instead of calling a function that would fail on it.
module QuantLib.Example.HaskellLSM
  (
    Result(..)
  , run
  ) where
import Control.Monad(replicateM)
import Data.List(transpose)
import qualified Data.Vector.Storable as V
import Data.List.NonEmpty(NonEmpty(..))
import qualified Data.List.NonEmpty as NE
import System.CPUTime(getCPUTime)

import QuantLib.InterestRate
import QuantLib.Math
import QuantLib.Method
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Syntax

data Result = Result
  { lsmPrice :: !Double        -- ^lsmRegress-driven backward induction (as QuantLib.Example.AmericanLSM)
  , haskellPrice :: !Double    -- ^identical backward induction, regression reimplemented in plain Haskell
  , lsmSeconds :: !Double      -- ^CPU time of the lsmRegress backward induction only (path generation excluded)
  , haskellSeconds :: !Double  -- ^CPU time of the Haskell-regression backward induction only
  }

payoff :: Double -> Double -> Double
payoff strike s = max (strike - s) 0

mean :: [Double] -> Double
mean xs = sum xs / fromIntegral (length xs)

cpuSeconds :: IO a -> IO (a, Double)
cpuSeconds act = do
  t0 <- getCPUTime
  r <- act
  t1 <- getCPUTime
  return (r, fromIntegral (t1 - t0) / 1.0e12)

-- |the monomial basis @[1, x, x^2, .., x^order]@ -- always has at least one term (the constant),
-- so it is built directly as a 'NonEmpty' rather than a plain list.
monomialBasis :: Word -> Double -> NonEmpty Double
monomialBasis order x = 1 :| take (fromIntegral order) (drop 1 (iterate (* x) 1))

-- |dot product of two equal-length lists (the shorter one wins if they differ, same as 'zipWith').
dot :: [Double] -> [Double] -> Double
dot xs ys = sum (zipWith (*) xs ys)

-- |naive ordinary-least-squares fit of 'monomialBasis', solved via the normal equations
-- (@(A^T A) c = A^T y@). The @A^T A@\/@A^T y@ entries are read off column-by-column via
-- 'transpose' (total, unlike indexing each row with @(!!)@) -- no optimized linear algebra,
-- unlike 'lsmRegress''s underlying C++ solve.
haskellRegress :: Word -> [Double] -> [Double] -> [Double] -> [Double]
haskellRegress order fitStates fitTargets evalStates =
  let basisRows = map (NE.toList . monomialBasis order) fitStates
      cols = transpose basisRows -- one column per basis term, [] if fitStates is []
      ata = [ [ dot c1 c2 | c2 <- cols ] | c1 <- cols ]
      aty = [ dot c fitTargets | c <- cols ]
      coeffs = gaussSolve ata aty
  in map (dot coeffs . NE.toList . monomialBasis order) evalStates

-- |value at column @k@ (0-based) of a row, via 'drop' rather than @(!!)@ -- total regardless of
-- @k@\/row length, though every call site here only ever asks for a column the row actually has.
columnAt :: Int -> [Double] -> Double
columnAt k row = case drop k row of
  (v : _) -> v
  []      -> 0 -- unreachable: k is always < length row at every call site below

-- |the last element of a row, via 'reverse' rather than 'last'.
lastColumn :: [Double] -> Double
lastColumn row = case reverse row of
  (v : _) -> v
  []      -> 0 -- unreachable: every row here is an augmented coefficient-plus-rhs row, never empty

-- |pick the element maximizing @key@ out of a list, returning it paired with the rest (order of
-- the rest preserved) -- a total, pattern-matching-only stand-in for 'Data.Foldable.maximumBy'
-- plus manual removal, since @maximumBy@ alone doesn't give the "rest" needed to move the pivot
-- to the front. 'Nothing' only for an empty input, which never happens at either call site (both
-- iterate the current elimination step's own nonempty remaining-rows suffix).
extractMaxBy :: (a -> Double) -> [a] -> Maybe (a, [a])
extractMaxBy key = go
  where
    go [] = Nothing
    go (x : xs) = case go xs of
      Nothing -> Just (x, [])
      Just (best, rest)
        | key x >= key best -> Just (x, best : rest)
        | otherwise         -> Just (best, x : rest)

-- |solve a small dense linear system @A c = y@ (rows of @A@, then @y@) by Gauss-Jordan
-- elimination with partial pivoting -- deliberately the naive textbook approach 'lsmRegress''s
-- C++ solve is not. Every row access goes through 'columnAt'\/'extractMaxBy'\/'splitAt', never
-- @(!!)@\/'head'\/'maximum'; @[]@ input (never seen in practice: 'haskellRegress' only calls this
-- with as many rows/columns as 'monomialBasis' terms, always >= 1) yields @[]@.
gaussSolve :: [[Double]] -> [Double] -> [Double]
gaussSolve rows y = case zipWith (\r yi -> r ++ [yi]) rows y of
  []        -> []
  augmented -> map lastColumn (foldl reduceColumn augmented [0 .. length augmented - 1])
  where
    reduceColumn current k =
      let (before, atOrAfterK) = splitAt k current
      in case extractMaxBy (abs . columnAt k) atOrAfterK of
           Nothing -> before ++ atOrAfterK -- unreachable: k < length current always
           Just (pivot, restAtK) ->
             let leadingCoeff = columnAt k pivot
                 normPivot = map (/ leadingCoeff) pivot
                 eliminate row = zipWith (\v p -> v - columnAt k row * p) row normPivot
             in map eliminate before ++ [normPivot] ++ map eliminate restAtK

-- |one backward-induction step, structurally identical to 'QuantLib.Example.AmericanLSM.step'
-- except the continuation-value estimate comes from 'haskellRegress' instead of 'lsmRegress'.
haskellStep :: Word -> Double -> Double -> [Double] -> [Double] -> [Double] -> [Double] -> [Bool]
            -> ([Double], [Double], [Bool])
haskellStep order strike df calibS priceS calibCF0 priceCF0 exFlags0 =
  let calibCF = map (* df) calibCF0
      priceCF = map (* df) priceCF0
      calibEx = map (payoff strike) calibS
      priceEx = map (payoff strike) priceS
      (fitStates, fitTargets, _) = unzip3 $ filter (\(_, _, e) -> e > 0) $ zip3 calibS calibCF calibEx
  in if length fitStates <= fromIntegral order
       then (calibCF, priceCF, exFlags0)
       else
         let contCalib = haskellRegress order fitStates fitTargets calibS
             contPrice = haskellRegress order fitStates fitTargets priceS
             calibCF' = zipWith3 (\cf ex cont -> if ex > 0 && ex > cont then ex else cf) calibCF calibEx contCalib
             decidePrice cf ex cont = if ex > 0 && ex > cont then (ex, True) else (cf, False)
             (priceCF', exercisedNow) = unzip $ zipWith3 decidePrice priceCF priceEx contPrice
             exFlags' = zipWith (||) exFlags0 exercisedNow
         in (calibCF', priceCF', exFlags')

-- |walk the exercise dates strictly backward, given as a list of @(discount factor, calibration
-- states, pricing states)@ triples already in backward (latest-exercise-date-first) order --
-- see 'exerciseSteps' for how that list is built without 'last'\/'init'.
haskellGoBack :: Word -> Double -> [(Double, [Double], [Double])] -> [Double] -> [Double] -> [Bool]
              -> ([Double], [Double], [Bool])
haskellGoBack order strike steps calibCF priceCF exFlags = case steps of
  [] -> (calibCF, priceCF, exFlags)
  ((df, calibS, priceS) : rest) ->
    let (calibCF', priceCF', exFlags') = haskellStep order strike df calibS priceS calibCF priceCF exFlags
    in haskellGoBack order strike rest calibCF' priceCF' exFlags'

-- |lsmRegress-driven step, copied from "QuantLib.Example.AmericanLSM" so this module can time it
-- head-to-head against 'haskellStep' over the exact same paths.
lsmStep :: PolynomialType -> Word -> Double -> Double -> [Double] -> [Double] -> [Double] -> [Double] -> [Bool]
        -> IO ([Double], [Double], [Bool])
lsmStep polyT order strike df calibS priceS calibCF0 priceCF0 exFlags0 = do
  let calibCF = map (* df) calibCF0
      priceCF = map (* df) priceCF0
      calibEx = map (payoff strike) calibS
      priceEx = map (payoff strike) priceS
      (fitStates, fitTargets, _) = unzip3 $ filter (\(_, _, e) -> e > 0) $ zip3 calibS calibCF calibEx
  if length fitStates <= fromIntegral order
    then return (calibCF, priceCF, exFlags0)
    else do
      contCalib <- V.toList <$> lsmRegress polyT order (V.fromList fitStates) (V.fromList fitTargets) (V.fromList calibS)
      contPrice <- V.toList <$> lsmRegress polyT order (V.fromList fitStates) (V.fromList fitTargets) (V.fromList priceS)
      let calibCF' = zipWith3 (\cf ex cont -> if ex > 0 && ex > cont then ex else cf) calibCF calibEx contCalib
          decidePrice cf ex cont = if ex > 0 && ex > cont then (ex, True) else (cf, False)
          (priceCF', exercisedNow) = unzip $ zipWith3 decidePrice priceCF priceEx contPrice
          exFlags' = zipWith (||) exFlags0 exercisedNow
      return (calibCF', priceCF', exFlags')

-- |'lsmStep' counterpart of 'haskellGoBack', walking the same backward-ordered triples.
lsmGoBack :: PolynomialType -> Word -> Double -> [(Double, [Double], [Double])] -> [Double] -> [Double] -> [Bool]
          -> IO ([Double], [Double], [Bool])
lsmGoBack polyT order strike steps calibCF priceCF exFlags = case steps of
  [] -> return (calibCF, priceCF, exFlags)
  ((df, calibS, priceS) : rest) -> do
    (calibCF', priceCF', exFlags') <- lsmStep polyT order strike df calibS priceS calibCF priceCF exFlags
    lsmGoBack polyT order strike rest calibCF' priceCF' exFlags'

-- |split a per-date state matrix (ascending, one row per date including both endpoints) into its
-- last row (maturity) and every earlier row, in backward (latest-first) order -- via 'reverse'
-- and pattern matching, rather than 'last'\/'init'. @[]@ only if the process is sampled at zero
-- dates, which never happens ('timeSteps' is fixed and positive below).
splitMaturity :: [[Double]] -> ([Double], [[Double]])
splitMaturity states = case reverse states of
  (m : rest) -> (m, rest)
  []         -> ([], [])

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter Actual365FixedStandard
  underQ <- simpleQuote under
  riskFreeQ <- simpleQuote riskFreeRate
  ts <- flatForward settl riskFreeQ dc Continuous Annual
  divQ <- simpleQuote dividend
  divTS <- flatForward settl divQ dc Continuous Annual
  volQ <- simpleQuote vol
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) settl volQ dc
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False

  t <- years dc settl maturity Nothing Nothing
  grid <- timeGrid t timeSteps
  times <- points grid
  discFactors <- mapM (\x -> discount ts x False) (V.toList times)
  let dfs = zipWith (flip (/)) discFactors (drop 1 discFactors)
      dfsRev = reverse (drop 1 dfs) -- one-step discount factors for exercise dates, latest first
      df0 = case discFactors of
              (d0 : d1 : _) -> d1 / d0
              _             -> 1 -- unreachable: timeSteps >= 1 below gives at least two entries

  genCalib <- pathGenerator PseudoRandom bsmProc grid seedCalib (size grid - 1) False
  calibPaths <- replicateM nCalib (V.toList <$> (next genCalib >>= \s -> asset s 0))
  genPrice <- pathGenerator PseudoRandom bsmProc grid seedPrice (size grid - 1) False
  pricePaths <- replicateM nPrice (V.toList <$> (next genPrice >>= \s -> asset s 0))
  let calibStates = transpose calibPaths
      priceStates = transpose pricePaths
      (calibMaturity, calibRestRev) = splitMaturity calibStates
      (priceMaturity, priceRestRev) = splitMaturity priceStates
      calibCF0 = map (payoff strike) calibMaturity
      priceCF0 = map (payoff strike) priceMaturity
      -- backward-ordered (discount factor, calibration state, pricing state) triples
      -- 'haskellGoBack'\/'lsmGoBack' walk. dfsRev already excludes the valuation-date step and is
      -- one shorter than calibRestRev\/priceRestRev (which still include the valuation date as
      -- their final entry); zip3 truncates to the shortest list, dropping that trailing entry for
      -- free -- the total-function replacement for the 'init' this would otherwise need.
      steps = zip3 dfsRev calibRestRev priceRestRev

  -- 'mean' (via 'sum') fully forces each backward-induction result inside the timed block --
  -- without it, the lazily-built cashflow lists would only be forced later, when 'Result' is
  -- printed, and the CPU time captured here would be meaningless.
  (lsmP, lsmT) <- cpuSeconds $ do
    (_, priceFinal, _) <- lsmGoBack polyT order strike steps calibCF0 priceCF0 (replicate nPrice False)
    let p = mean (map (* df0) priceFinal)
    p `seq` return p
  (haskellP, haskellT) <- cpuSeconds $ do
    let (_, priceFinal, _) = haskellGoBack order strike steps calibCF0 priceCF0 (replicate nPrice False)
        p = mean (map (* df0) priceFinal)
    p `seq` return p

  return $ Result lsmP haskellP lsmT haskellT
  where
    evalDate = 15 `may` 1998
    settl = 17 `may` 1998
    under = 36
    strike = 40
    dividend = 0.0
    riskFreeRate = 0.06
    vol = 0.20
    maturity = 17 `may` 1999
    timeSteps = 100 :: Word
    order = 2 :: Word
    polyT = Monomial
    nCalib = 4096 :: Int
    nPrice = 8192 :: Int
    seedCalib = 42 :: Word
    seedPrice = 43 :: Word

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
