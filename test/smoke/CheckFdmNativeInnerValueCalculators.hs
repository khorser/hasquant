-- Smoke test for issue #20's finalization: QuantLib's native FdmInnerValueCalculator subclasses
-- (FdmZeroInnerValue, FdmCellAveragingInnerValue, FdmLogInnerValue, FdmLogBasketInnerValue), bound
-- alongside the pre-existing Haskell-callback path (withCustomFdmInnerValueCalculator). Checks:
-- 1. fdmZeroInnerValue is always 0 at any node.
-- 2. fdmLogInnerValue (native, cell-averaging with gridMapping = exp) driving fdmSolve reprices a
--    European call close to analyticEuropeanEngine's closed-form value.
-- 3. fdmLogBasketInnerValue evaluates a max-of-two-assets basket payoff exactly at a node.
-- 4. gluedMesher splices two Fdm1dMeshers back into the original grid (dedup'd shared node), and
--    rejects an overlapping/reversed pair.
--
-- Run with:
--   cabal exec -- ghc -package hasquant test/smoke/CheckFdmNativeInnerValueCalculators.hs \
--     -o /tmp/checkfdm -outputdir /tmp/checkfdm_build && /tmp/checkfdm
{-# LANGUAGE TemplateHaskell #-}
import Control.Exception(SomeException, try)
import Data.Time.Calendar(addDays)
import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.Math(FdmScheme(..))
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

  let vanillaPayoff = PlainVanilla (PlainVanillaPayoff Call strike)
      payoff = Type (Striked vanillaPayoff)
      europeanEx = European (EuropeanExercise maturity)
      intrinsicAt x = max (exp x - strike) 0
      bands = operatorBands nPts h mu sigma2 r
      applyFn _ u = applyOp bands u
      applyDirFn _dir _t u = applyOp bands u
      solveFn _dir s _t u =
        let (lo, di, up) = bands
        in thomasSolve (map (s *) lo) (map (\d -> 1 + s * d) di) (map (s *) up) u

  europeanOpt <- vanillaOption vanillaPayoff europeanEx
  analyticEuropeanEngine bsmProc Nothing >>= QuantLib.Instrument.setPricingEngine europeanOpt
  analytic <- npv europeanOpt

  mesh1d <- predefined1dMesher xs
  mesher <- fdmMesherComposite [mesh1d]

  zeroCalc <- fdmZeroInnerValue
  zeroAtCenter <- fdmAvgInnerValue zeroCalc mesher [centerIdx] tMat
  check "FdmZeroInnerValue is always 0" (zeroAtCenter == 0)

  logCalc <- fdmLogInnerValue payoff mesher 0
  fdmLogEuro <- fdmSolve mesher logCalc 1 applyFn applyDirFn solveFn Nothing [] Douglas tMat 0 nSteps 0
  let fdmLogPrice = fdmLogEuro !! centerIdx
  putStrLn ("fdmLogInnerValue European price: " ++ show fdmLogPrice ++ ", analytic: " ++ show analytic)
  check "fdmLogInnerValue reprices close to analyticEuropeanEngine"
    (abs (fdmLogPrice - analytic) < 2.0e-3 * analytic)

  basketMesher <- fdmMesherComposite [mesh1d, mesh1d]
  basketCalc <- fdmLogBasketInnerValue (Max payoff) basketMesher
  basketAt <- fdmAvgInnerValue basketCalc basketMesher [centerIdx + 5, centerIdx - 5] tMat
  let expected = max (max (exp (xs !! (centerIdx + 5))) (exp (xs !! (centerIdx - 5))) - strike) 0
  putStrLn ("fdmLogBasketInnerValue at node: " ++ show basketAt ++ ", expected: " ++ show expected)
  check "fdmLogBasketInnerValue exact max-basket intrinsic" (basketAt == expected)

  leftHalf <- predefined1dMesher (take (centerIdx + 1) xs)
  rightHalf <- predefined1dMesher (drop centerIdx xs)
  glued <- gluedMesher leftHalf rightHalf
  gluedComposite <- fdmMesherComposite [glued]
  gluedLocations <- fdmMesherLocations gluedComposite 0
  meshLocations <- fdmMesherLocations mesher 0
  check "gluedMesher reproduces the un-split grid, deduplicating the shared node" (gluedLocations == meshLocations)
  overlapResult <- try (gluedMesher rightHalf leftHalf) :: IO (Either SomeException Fdm1dMesher)
  check "gluedMesher rejects an overlapping/reversed range" (either (const True) (const False) overlapResult)

  putStrLn "OK: native FdmInnerValueCalculator subclasses and gluedMesher (issue #20) all work end to end"
  where
    check label cond = if cond then putStrLn ("OK  " ++ label) else error ("FAILED: " ++ label)
    evalDate = 1 `january` 2020
    maturity = addDays 365 evalDate
    tMat = 1.0
    spot = 100 :: Double
    strike = 100 :: Double
    r = 0.05 :: Double
    q = 0.02 :: Double
    vol = 0.25 :: Double
    sigma2 = vol * vol
    mu = r - q - 0.5 * sigma2
    nPts = 201 :: Int
    centerIdx = nPts `div` 2
    halfWidth = 8 * vol * sqrt tMat
    h = 2 * halfWidth / fromIntegral (nPts - 1)
    xs = [log spot - halfWidth + fromIntegral i * h | i <- [0 .. nPts - 1]]
    nSteps = 200 :: Int

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
