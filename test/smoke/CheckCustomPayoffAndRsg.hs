-- Smoke test for issue #18's two hooks:
--
-- A. withCustomPayoff / withCustomBasketPayoff -- a Haskell-defined QuantLib Payoff. Checked by
--    reproducing a PlainVanilla call as a Haskell lambda and requiring the *native* and *custom*
--    payoff to give bit-for-bit identical results through two independent payoff-generic
--    consumers: fdmLogInnerValue driving fdmSolve, and fdmLogBasketInnerValue evaluated at a node.
--    Also drives a custom payoff through mcAmericanEngine (controlVariate = False), the one bound
--    pricing engine that never downcasts the payoff.
--
-- B. gaussianRsg -- the standalone gaussian sequence generator. Checked by evolving a
--    Black-Scholes SDE in Haskell from its draws and requiring the resulting path to match
--    pathGenerator's own path on the equivalent bound process, same trait/dimension/seed. This
--    pins the draw order MultiPathGenerator consumes (offset (i-1)*factors per timestep) as much
--    as it pins the binding.
--
-- Run with:
--   cabal exec -- ghc -package hasquant test/smoke/CheckCustomPayoffAndRsg.hs \
--     -o /tmp/checkcustom -outputdir /tmp/checkcustom_build && /tmp/checkcustom
{-# LANGUAGE TemplateHaskell #-}
import Control.Monad(unless)
import Data.Time.Calendar(addDays, fromGregorian)
import qualified Data.Vector.Storable as V
import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.Math(FdmScheme(..), PolynomialType(..), RngTrait(..), StatisticsTrait(..), timeGrid)
import QuantLib.Method
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Syntax
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield

main :: IO ()
main = do
  setEvaluationDate (Just evalDate)
  dc <- dayCounter Actual365FixedStandard
  underQ <- simpleQuote spot
  riskFreeQ <- simpleQuote r
  divQ <- simpleQuote q
  volQ <- simpleQuote vol
  ts <- flatForward evalDate riskFreeQ dc Continuous Annual
  divTS <- flatForward evalDate divQ dc Continuous Annual
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) evalDate volQ dc
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False

  let nativePayoff = Type (Striked (PlainVanilla (PlainVanillaPayoff Call strike)))
      bands = operatorBands nPts h mu sigma2 r
      applyFn _ = V.fromList . applyOp bands . V.toList
      applyDirFn _dir _t = V.fromList . applyOp bands . V.toList
      solveFn _dir s _t =
        let (lo, di, up) = bands
        in V.fromList . thomasSolve (map (s *) lo) (map (\d -> 1 + s * d) di) (map (s *) up) . V.toList

  mesh1d <- predefined1dMesher (V.fromList xs)
  mesher <- fdmMesherComposite [mesh1d]
  basketMesher <- fdmMesherComposite [mesh1d, mesh1d]

  nativeCalc <- fdmLogInnerValue nativePayoff mesher 0
  nativeEuro <- fdmSolve mesher nativeCalc 1 applyFn applyDirFn solveFn Nothing V.empty Douglas tMat 0 nSteps 0
  nativeBasketCalc <- fdmLogBasketInnerValue (Max nativePayoff) basketMesher
  nativeBasket <- fdmAvgInnerValue nativeBasketCalc basketMesher [centerIdx + 5, centerIdx - 5] tMat

  -- The same call payoff, written in Haskell. fdmLogInnerValue applies gridMapping = exp itself,
  -- so the Haskell function sees spot, not log-spot -- hence (s - strike), not intrinsicAt.
  (customEuro, customBasket) <-
    withCustomPayoff "HaskellCall" "max(S - K, 0), defined in Haskell" (\s -> max (s - strike) 0) $ \custom -> do
      customCalc <- fdmLogInnerValue custom mesher 0
      euro <- fdmSolve mesher customCalc 1 applyFn applyDirFn solveFn Nothing V.empty Douglas tMat 0 nSteps 0
      basket <- withCustomBasketPayoff custom maximum $ \customBasketPayoff -> do
        calc <- fdmLogBasketInnerValue customBasketPayoff basketMesher
        fdmAvgInnerValue calc basketMesher [centerIdx + 5, centerIdx - 5] tMat
      pure (euro, basket)

  check "custom payoff vs native, through fdmLogInnerValue + fdmSolve"
    (nativeEuro V.! centerIdx) (customEuro V.! centerIdx) 0
  check "custom basket accumulate vs native Max, through fdmLogBasketInnerValue"
    nativeBasket customBasket 0

  -- mcAmericanEngine with controlVariate = False is the one bound engine that hands the payoff
  -- through untouched (mcamericanengine.hpp's lsmPathPricer does no cast). Same engine settings,
  -- same seed, native vs custom payoff: identical price.
  let americanEx = American Nothing maturity False
      mcEngine = mcAmericanEngine PseudoRandom Statistics bsmProc (Just 25) Nothing True False
        (Just 4096) Nothing Nothing 42 2 Monomial (Just 1024) Nothing Nothing
  nativeOpt <- oneAssetOption nativePayoff americanEx
  mcEngine >>= setPricingEngine nativeOpt
  nativeMC <- npv nativeOpt
  customMC <- withCustomPayoff "HaskellCall" "max(S - K, 0), defined in Haskell" (\s -> max (s - strike) 0) $ \custom -> do
    opt <- oneAssetOption custom americanEx
    mcEngine >>= setPricingEngine opt
    npv opt
  check "custom payoff vs native, through mcAmericanEngine" nativeMC customMC 0

  -- withCustomStrikedPayoff: fdBlackScholesVanillaEngine dynamic_pointer_casts the payoff to
  -- StrikedTypePayoff with NO null check and calls ->strike() for its mesher geometry
  -- (fdblackscholesvanillaengine.cpp:154-166). A withCustomPayoff payoff crashes there; a
  -- withCustomStrikedPayoff one carries a real strike, so the cast succeeds and the engine prices
  -- the Haskell function correctly. Checked against the native PlainVanilla payoff through the
  -- same engine: identical, since the payoff values are identical and the strike given matches.
  let fdEngine = fdBlackScholesVanillaEngine bsmProc 100 200 0 Douglas False 0.0 CashDividendSpot
  nativeFdOpt <- vanillaOption (PlainVanilla (PlainVanillaPayoff Call strike)) americanEx
  nativeFdInst <- asOneAssetOption nativeFdOpt
  fdEngine >>= setPricingEngine nativeFdInst
  nativeFd <- npv nativeFdInst
  customFd <- withCustomStrikedPayoff Call strike "HaskellCall" (\s -> max (s - strike) 0) $ \custom -> do
    opt <- vanillaOption custom americanEx
    inst <- asOneAssetOption opt
    fdEngine >>= setPricingEngine inst
    npv inst
  check "custom striked payoff vs native, through fdBlackScholesVanillaEngine" nativeFd customFd 0

  -- B. gaussianRsg: evolve the same Black-Scholes process by hand and compare against
  -- pathGenerator. MultiPathGenerator consumes the sequence at offset (i-1)*factors per step,
  -- and QuantLib's own exact BSM evolution is expectation = x * exp(drift*dt) with drift the
  -- log-drift, stdDev = vol*sqrt(dt) -- reproduced here in log space.
  grid <- timeGrid tMat (fromIntegral nSteps)
  gen <- pathGenerator PseudoRandom bsmProc grid rngSeed (fromIntegral nSteps) False
  qlPath <- next gen >>= \s -> asset s 0

  rsg <- gaussianRsg PseudoRandom (fromIntegral nSteps) rngSeed
  (draws, _w) <- nextSequence rsg
  let dt = tMat / fromIntegral nSteps
      logDrift = r - q - 0.5 * vol * vol
      hsPath = V.scanl (\x dw -> x * exp (logDrift * dt + vol * sqrt dt * dw)) spot draws
  unless (V.length qlPath == V.length hsPath) $
    fail ("path length mismatch: " ++ show (V.length qlPath, V.length hsPath))
  mapM_ (\(i, a, b) -> check ("gaussianRsg-evolved path, step " ++ show i) a b 1e-10)
    (zip3 [(0 :: Int) ..] (V.toList qlPath) (V.toList hsPath))

  -- rsgDimension/lastSequence round-trip: lastSequence must re-read what nextSequence just drew.
  (again, _) <- lastSequence rsg
  unless (again == draws) $ fail "lastSequence did not reproduce the last nextSequence draw"
  unless (rsgDimension rsg == fromIntegral nSteps) $ fail "rsgDimension mismatch"

  putStrLn "OK"
  where
    check label a b tol =
      let d = abs (a - b)
          scale = max 1 (max (abs a) (abs b))
      in unless (d <= tol * scale) $
           fail (label ++ ": " ++ show a ++ " vs " ++ show b ++ " (diff " ++ show d ++ ")")

    evalDate = fromGregorian 2024 5 15
    maturity = addDays 365 evalDate
    spot = 100.0
    strike = 100.0
    r = 0.03
    q = 0.01
    vol = 0.20
    tMat = 1.0
    mu = r - q - 0.5 * vol * vol
    sigma2 = vol * vol
    nPts = 201
    nSteps = 25
    rngSeed = 42
    centerIdx = nPts `div` 2
    xWidth = 5 * vol * sqrt tMat
    h = 2 * xWidth / fromIntegral (nPts - 1)
    xs = [log spot + (fromIntegral i - fromIntegral centerIdx) * h | i <- [0 .. nPts - 1]]

-- Copies of QuantLib.Example.Fdm's operator/solver helpers -- test/smoke programs are standalone
-- against the installed library, so they cannot import the example modules.
thomasSolve :: [Double] -> [Double] -> [Double] -> [Double] -> [Double]
thomasSolve lo di up rhs = foldr back [] (forward lo di up rhs)
  where
    back (_, d) [] = [d]
    back (c, d) acc@(xNext : _) = (d - c * xNext) : acc
    forward (_ : los) (d0 : dis) (u0 : ups) (r0 : rs) = (c0, x0) : go x0 c0 los dis ups rs
      where
        c0 = u0 / d0
        x0 = r0 / d0
        go dPrev cPrev (a : as) (d : ds) (u : us) (r : rs') =
          let denom = d - a * cPrev
              c' = u / denom
              x' = (r - a * dPrev) / denom
          in (c', x') : go x' c' as ds us rs'
        go _ _ _ _ _ _ = []
    forward _ _ _ _ = []

operatorBands :: Int -> Double -> Double -> Double -> Double -> ([Double], [Double], [Double])
operatorBands m h mu sigma2 r = unzip3 (map row [0 .. m - 1])
  where
    row i
      | i == 0 = (0, -mu / h - r, mu / h)
      | i == m - 1 = (-mu / h, mu / h - r, 0)
      | otherwise =
          let a = mu / (2 * h)
              b = 0.5 * sigma2 / (h * h)
          in (b - a, -sigma2 / (h * h) - r, b + a)

applyOp :: ([Double], [Double], [Double]) -> [Double] -> [Double]
applyOp (lo, di, up) u = go lo di up (0 : u) u (drop 1 u ++ [0])
  where
    go (l : ls) (d : ds) (uu : us) (p : ps) (c : cs) (nx : nxs) =
      (l * p + d * c + uu * nx) : go ls ds us ps cs nxs
    go _ _ _ _ _ _ = []
