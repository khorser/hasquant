{-# LANGUAGE TemplateHaskell #-}
-- |Prices a 3-asset American basket put (payoff on the maximum of three correlated underlyings)
-- with a Haskell-defined payoff, generalizing "QuantLib.Example.AmericanLSM"'s backward-induction
-- pattern from the scalar 'QuantLib.Method.lsmRegress' to the multi-asset
-- 'QuantLib.Method.lsmRegressMulti'. Fixture and golden values are QuantLib's own
-- @test-suite\/basketoption.cpp@ @testBarraquandThreeValues@ case (Barraquand & Martineau 1995):
-- three assets at spot 40, strike 40, r=5%, q=0, vol 20%\/30%\/50%, zero correlation, maturity 1
-- month -- cached European reference 0.13, American reference 0.23.
module QuantLib.Example.BasketLSM
  (
    Result(..)
  , run
  ) where
import Control.Monad(replicateM, zipWithM)
import Data.Time.Calendar(addDays)
import qualified Data.Vector.Storable as V
import qualified Data.List.NonEmpty as NE

import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.Math
import QuantLib.Method
import QuantLib.Process
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Syntax

data Result = Result
  { lsmPrice :: !Double        -- ^custom multi-asset LSM loop, out-of-sample pricing paths priced against a fit from a separate calibration path set (unbiased)
  , calibPrice :: !Double      -- ^same loop, but pricing the calibration paths against their own (in-sample) fit -- the naive, biased single-pass estimate
  , mcPrice :: !Double         -- ^'mcAmericanBasketEngine' pricing the equivalent bound MaxBasketPayoff option
  , referencePrice :: !Double  -- ^upstream's own cached golden value for this exact fixture (Barraquand & Martineau 1995)
  , exerciseProb :: !Double    -- ^fraction of pricing paths exercised before maturity
  , simulatedForwards :: ![Double]  -- ^per-asset mean simulated terminal spot, pricing path set
  , impliedForwards :: ![Double]    -- ^per-asset curve-implied forward: spot \/ discount(T) (q=0)
  }

payoff :: Double -> [Double] -> Double
payoff strike ss = max (strike - maximum ss) 0

mean :: [Double] -> Double
mean xs = sum xs / fromIntegral (length xs)

-- |every asset's full simulated time series for one drawn path.
pathAssets :: Int -> PathGenerator -> IO [[Double]]
pathAssets dim gen = next gen >>= \s -> mapM (fmap V.toList . asset s) [0 .. fromIntegral dim - 1]

-- |all paths' state at exercise-date index @t@, one row (of @dim@ underlyings) per path.
statesAt :: Int -> Int -> [[[Double]]] -> [[Double]]
statesAt dim t paths = [ [ p !! a !! t | a <- [0 .. dim-1] ] | p <- paths ]

toMatrix :: Int -> [[Double]] -> RealMatrix
toMatrix dim rows = either error id $
  realMatrixFromVector (fromIntegral (length rows)) (fromIntegral dim) (V.fromList (concat rows))

-- |one backward-induction step, generalizing "QuantLib.Example.AmericanLSM"'s 'step' from a
-- scalar state to an @dim@-underlying state vector per path (via 'lsmRegressMulti' instead of
-- 'lsmRegress').
step :: PolynomialType -> Word -> Double -> Int -> Double -> Int -> [[[Double]]] -> [[[Double]]]
     -> [Double] -> [Double] -> [Bool] -> IO ([Double], [Double], [Bool])
step polyT order strike dim df t calibPaths pricePaths calibCF0 priceCF0 exFlags0 = do
  let calibCF = map (* df) calibCF0
      priceCF = map (* df) priceCF0
      calibS = statesAt dim t calibPaths
      priceS = statesAt dim t pricePaths
      calibEx = map (payoff strike) calibS
      priceEx = map (payoff strike) priceS
      (fitStates, fitTargets, _) = unzip3 $ filter (\(_, _, e) -> e > 0) $ zip3 calibS calibCF calibEx
      basisNeeded = fromIntegral (lsmBasisSize (fromIntegral dim) order)
  if length fitStates <= basisNeeded
    then return (calibCF, priceCF, exFlags0)
    else do
      let fitMat = toMatrix dim fitStates
      contCalib <- V.toList <$> lsmRegressMulti polyT order fitMat (V.fromList fitTargets) (toMatrix dim calibS)
      contPrice <- V.toList <$> lsmRegressMulti polyT order fitMat (V.fromList fitTargets) (toMatrix dim priceS)
      let calibCF' = zipWith3 (\cf ex cont -> if ex > 0 && ex > cont then ex else cf) calibCF calibEx contCalib
          decidePrice cf ex cont = if ex > 0 && ex > cont then (ex, True) else (cf, False)
          (priceCF', exercisedNow) = unzip $ zipWith3 decidePrice priceCF priceEx contPrice
          exFlags' = zipWith (||) exFlags0 exercisedNow
      return (calibCF', priceCF', exFlags')

-- |walk exercise dates strictly backward, from index @timeSteps-1@ down to 1 -- same range as
-- "QuantLib.Example.AmericanLSM"'s 'goBack', but indexing directly into the fully-stored
-- per-asset path lists (already available in full) rather than peeling a transposed state list.
goBack :: PolynomialType -> Word -> Double -> Int -> Int -> [Double] -> [[[Double]]] -> [[[Double]]]
       -> [Double] -> [Double] -> [Bool] -> IO ([Double], [Double], [Bool])
goBack polyT order strike dim i dfs calibPaths pricePaths calibCF priceCF exFlags
  | i < 1 = return (calibCF, priceCF, exFlags)
  | otherwise = do
      (calibCF', priceCF', exFlags') <- step polyT order strike dim (dfs !! i) i calibPaths pricePaths calibCF priceCF exFlags
      goBack polyT order strike dim (i - 1) dfs calibPaths pricePaths calibCF' priceCF' exFlags'

run :: IO Result
run = do
  setEvaluationDate $ Just evalDate
  dc <- dayCounter (Actual360 False)
  cal <- calendar TARGET
  underQs <- mapM simpleQuote spots
  riskFreeQ <- simpleQuote riskFreeRate
  ts <- flatForward evalDate riskFreeQ dc Continuous Annual
  divQ <- simpleQuote 0.0
  divTS <- flatForward evalDate divQ dc Continuous Annual
  volQs <- mapM simpleQuote vols
  volTSs <- mapM (\vq -> $(free2nd 'blackConstantVol) evalDate vq dc cal) volQs
  procs1D <- zipWithM (\uq vts -> blackScholesMertonProcess uq divTS ts vts EulerDiscretization False) underQs volTSs
  let corrFlat = concat [ [ if i == j then 1 else assetCorrelation | j <- [0 .. dim-1] ] | i <- [0 .. dim-1] ]
      corrMat = Matrix (fromIntegral dim) (fromIntegral dim) corrFlat
  procs <- stochasticProcessArray (NE.fromList procs1D) corrMat

  t <- years dc evalDate maturity Nothing Nothing
  grid <- timeGrid t timeSteps
  times <- V.toList <$> points grid
  discFactors@(df0h:_) <- mapM (\x -> discount ts x False) times
  let dfs = zipWith (flip (/)) discFactors (drop 1 discFactors)

  genCalib <- pathGenerator PseudoRandom procs grid seedCalib (fromIntegral dim * (size grid - 1)) False
  calibPaths <- replicateM nCalib (pathAssets dim genCalib)
  genPrice <- pathGenerator PseudoRandom procs grid seedPrice (fromIntegral dim * (size grid - 1)) False
  pricePaths <- replicateM nPrice (pathAssets dim genPrice)

  let nSteps = fromIntegral timeSteps
      calibCF0 = map (payoff strike . map (!! nSteps)) calibPaths
      priceCF0 = map (payoff strike . map (!! nSteps)) pricePaths

  (calibFinal, priceFinal, exFlags) <- goBack polyT order strike dim (nSteps - 1) dfs
    calibPaths pricePaths calibCF0 priceCF0 (replicate nPrice False)

  let df0 = discFactors !! 1 / df0h
      lsmP = mean (map (* df0) priceFinal)
      calibP = mean (map (* df0) calibFinal)
      exProb = fromIntegral (length (filter id exFlags)) / fromIntegral nPrice

  let payoffQL = Max (Type (Striked (PlainVanilla (PlainVanillaPayoff Put strike))))
      americanEx = American Nothing maturity False
  amOpt <- basketOption payoffQL americanEx
  amEng <- mcAmericanBasketEngine PseudoRandom procs (Just timeSteps) Nothing False False Nothing (Just 0.02) Nothing seedCalib (Just (fromIntegral nCalib)) order polyT
  QuantLib.Instrument.setPricingEngine amOpt amEng
  mcA <- npv amOpt

  -- martingale self-consistency check: under the risk-neutral measure, each simulated asset's
  -- mean terminal spot should match the curve-implied forward spot\/discount(T) (q=0 here) --
  -- guards against a process/curve wiring mistake (e.g. a swapped foreign\/domestic curve) the
  -- way the TARF example's own check does.
  let terminalDF = discFactors !! nSteps
      impliedFwds = map (/ terminalDF) spots
      simFwds = [ mean (map (\p -> p !! a !! nSteps) pricePaths) | a <- [0 .. dim-1] ]

  return $ Result lsmP calibP mcA referenceAmerican exProb simFwds impliedFwds
  where
    evalDate = 1 `may` 2024
    dim = 3 :: Int
    spots = [40, 40, 40] :: [Double]
    vols = [0.20, 0.30, 0.50] :: [Double]
    assetCorrelation = 0.0 :: Double
    strike = 40 :: Double
    riskFreeRate = 0.05
    maturity = addDays 30 evalDate  -- upstream: today + 1 (month) * 30 days
    timeSteps = 50 :: Word
    order = 2 :: Word
    polyT = Monomial
    nCalib = 4096 :: Int
    nPrice = 8192 :: Int
    seedCalib = 42 :: Word
    seedPrice = 43 :: Word
    referenceAmerican = 0.23

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
