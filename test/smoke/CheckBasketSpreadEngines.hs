module Main(main) where

import Control.Monad(unless)
import Data.List.NonEmpty(NonEmpty((:|)))
import Text.Printf(printf)

import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Option(basketOption, plainVanillaPayoff, BasketPayoff(Average, Spread), OptionType(Call, Put), PlainVanillaPayoff(PlainVanillaPayoff), Exercise(European), EuropeanExercise(EuropeanExercise))
import QuantLib.Math(boxedRealMatrix, RngTrait(PseudoRandom), StatisticsTrait(Statistics), FdmScheme(Hundsdorfer, Douglas))
import QuantLib.PricingEngine
  ( bjerksundStenslandSpreadEngine, operatorSplittingSpreadEngine, OperatorSplittingOrder(First, Second)
  , pearsonSpreadEngine, gaussianCopulaSpreadEngine, fd2dBlackScholesVanillaEngine
  , choiBasketEngine, dengLiZhouBasketEngine, fdndimBlackScholesVanillaEngine, fdndimBlackScholesVanillaEngine'
  , singleFactorBsmBasketEngine, kirkEngine, mcEuropeanBasketEngine
  )
import QuantLib.Process(blackProcess, blackScholesMertonProcess, stochasticProcessArray, asGeneralizedBlackScholesProcess, ProcessDiscretization(EulerDiscretization))
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(keepingSettings')
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar(calendar, CalendarConstructor(TARGET))
import QuantLib.Time.Date(addPeriod, march)
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(Actual365FixedStandard), TimeUnit(Months), Frequency(Annual))
import QuantLib.TermStructure.Yield(flatForward, discount')
import QuantLib.TermStructure.Volatility(blackConstantVol)
import QuantLib.InterestRate(Compounding(Continuous))

check :: String -> Bool -> IO ()
check name ok = unless ok (error (name ++ ": FAILED"))

approx :: Double -> Double -> Double -> Bool
approx tol expected actual = abs (expected - actual) <= tol

main :: IO ()
main = keepingSettings' $ do
  let today = 1 `march` 2024
  Settings.setEvaluationDate (Just today)
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar TARGET
  maturity <- addPeriod today (12, Months)

  -- test-suite/basketoption.cpp::testBjerksundStenslandSpreadEngine
  let f1 = 100 :: Double
      f2 = 110 :: Double
      rho = 0.75 :: Double
      spreadStrike = 5 :: Double
  rQ <- simpleQuote 0.05
  rTS <- flatForward today rQ dc Continuous Annual
  v1Q <- simpleQuote 0.25
  v2Q <- simpleQuote 0.35
  vol1TS <- blackConstantVol today cal v1Q dc
  vol2TS <- blackConstantVol today cal v2Q dc
  s1 <- simpleQuote f1
  s2 <- simpleQuote f2
  p1 <- blackScholesMertonProcess s1 rTS rTS vol1TS EulerDiscretization False
  p2 <- blackScholesMertonProcess s2 rTS rTS vol2TS EulerDiscretization False

  bjEngine <- bjerksundStenslandSpreadEngine p1 p2 rho
  putOpt <- basketOption (Spread (plainVanillaPayoff (PlainVanillaPayoff Put spreadStrike))) (European (EuropeanExercise maturity))
  setPricingEngine putOpt bjEngine
  putNPV <- npv putOpt
  let expectedPutNPV = 17.850835947276213 :: Double
  printf "BjerksundStenslandSpreadEngine put NPV: %.6f (expected %.6f)\n" putNPV expectedPutNPV
  check "BjerksundStenslandSpreadEngine put value" (approx 1e-6 expectedPutNPV putNPV)

  callOpt <- basketOption (Spread (plainVanillaPayoff (PlainVanillaPayoff Call spreadStrike))) (European (EuropeanExercise maturity))
  setPricingEngine callOpt bjEngine
  callNPV <- npv callOpt
  df <- discount' rTS maturity False
  let fwd = (callNPV - putNPV) / df
  printf "BjerksundStenslandSpreadEngine call-put parity fwd diff: %.6f\n" (fwd - (f1 - f2 - spreadStrike))
  check "BjerksundStenslandSpreadEngine call-put parity" (approx 1e-3 (f1 - f2 - spreadStrike) fwd)

  -- test-suite/basketoption.cpp::testOperatorSplittingSpreadEngine: forward-adjusted BlackProcess
  -- inputs (f1=110*dq1/df, f2=90*dq2/df), Kirk-vs-Strang(First/Second) golden table (a few rows)
  dq1Q <- simpleQuote 0.03
  dq2Q <- simpleQuote 0.02
  dq1TS <- flatForward today dq1Q dc Continuous Annual
  dq2TS <- flatForward today dq2Q dc Continuous Annual
  dfR <- discount' rTS maturity False
  dq1 <- discount' dq1TS maturity False
  dq2 <- discount' dq2TS maturity False
  let f1' = 110 * dq1 / dfR
      f2' = 90 * dq2 / dfR
  v1Q' <- simpleQuote 0.3
  v2Q' <- simpleQuote 0.2
  vol1TS' <- blackConstantVol today cal v1Q' dc
  vol2TS' <- blackConstantVol today cal v2Q' dc
  f1Q <- simpleQuote f1'
  f2Q <- simpleQuote f2'
  bp1' <- blackProcess f1Q rTS vol1TS' EulerDiscretization False
  bp2' <- blackProcess f2Q rTS vol2TS' EulerDiscretization False
  p1' <- asGeneralizedBlackScholesProcess bp1'
  p2' <- asGeneralizedBlackScholesProcess bp2'
  let opsRows = [(-0.9 :: Double, 18.9323 :: Double, 18.9361 :: Double), (0.5, 10.8323, 10.8323)]
  opsOpt <- basketOption (Spread (plainVanillaPayoff (PlainVanillaPayoff Call 20.0))) (European (EuropeanExercise maturity))
  mapM_ (\(r, exp1, exp2) -> do
      e1 <- operatorSplittingSpreadEngine p1' p2' r First
      setPricingEngine opsOpt e1
      v1 <- npv opsOpt
      check ("OperatorSplittingSpreadEngine First rho=" ++ show r) (approx 1e-3 exp1 v1)
      e2 <- operatorSplittingSpreadEngine p1' p2' r Second
      setPricingEngine opsOpt e2
      v2 <- npv opsOpt
      check ("OperatorSplittingSpreadEngine Second rho=" ++ show r) (approx 5e-3 exp2 v2)
      printf "OperatorSplittingSpreadEngine rho=%.2f: First=%.4f (exp %.4f), Second=%.4f (exp %.4f)\n" r v1 exp1 v2 exp2
    ) opsRows

  -- cross-check PearsonSpreadEngine / GaussianCopulaSpreadEngine / Fd2dBlackScholesVanillaEngine
  -- against KirkEngine on the same spread option (test-suite/basketoption.cpp::testPDEvsApproximations idea)
  kirk <- kirkEngine bp1' bp2' rho
  pearson <- pearsonSpreadEngine p1' p2' rho 1e-10 10000 8.0
  gauss <- gaussianCopulaSpreadEngine p1' p2' rho 64
  fd2d <- fd2dBlackScholesVanillaEngine p1' p2' rho 100 100 50 0 Hundsdorfer False (-1e10)
  crossOpt <- basketOption (Spread (plainVanillaPayoff (PlainVanillaPayoff Call 20.0))) (European (EuropeanExercise maturity))
  setPricingEngine crossOpt kirk
  kirkV <- npv crossOpt
  setPricingEngine crossOpt pearson
  pearsonV <- npv crossOpt
  setPricingEngine crossOpt gauss
  gaussV <- npv crossOpt
  setPricingEngine crossOpt fd2d
  fd2dV <- npv crossOpt
  printf "cross-check @ rho=%.2f: Kirk=%.4f Pearson=%.4f GaussianCopula=%.4f Fd2d=%.4f\n" rho kirkV pearsonV gaussV fd2dV
  check "PearsonSpreadEngine vs Kirk" (approx 0.05 kirkV pearsonV)
  check "GaussianCopulaSpreadEngine vs Kirk" (approx 0.5 kirkV gaussV)
  check "Fd2dBlackScholesVanillaEngine vs Kirk" (approx 0.1 kirkV fd2dV)

  -- ChoiBasketEngine / DengLiZhouBasketEngine / SingleFactorBsmBasketEngine self-consistency vs
  -- the already-bound MCEuropeanBasketEngine, on a 2-asset spread call. DengLiZhouBasketEngine and
  -- SingleFactorBsmBasketEngine both require an additively-separable (Average/Spread) basket
  -- payoff -- Min/Max throws "average or spread basket payoff expected" -- so this uses Spread,
  -- unlike the MinBasket/MaxBasket cases above that only exercise Stulz/Kirk/MC/Fd2d.
  let bs1 = 100 :: Double
      bs2 = 100 :: Double
      brho = 0.3 :: Double
  bq1 <- simpleQuote 0.0
  bq2 <- simpleQuote 0.0
  bqTS1 <- flatForward today bq1 dc Continuous Annual
  bqTS2 <- flatForward today bq2 dc Continuous Annual
  brQ <- simpleQuote 0.05
  brTS <- flatForward today brQ dc Continuous Annual
  bv1 <- simpleQuote 0.3
  bv2 <- simpleQuote 0.3
  bvolTS1 <- blackConstantVol today cal bv1 dc
  bvolTS2 <- blackConstantVol today cal bv2 dc
  bs1Q <- simpleQuote bs1
  bs2Q <- simpleQuote bs2
  bp1 <- blackScholesMertonProcess bs1Q bqTS1 brTS bvolTS1 EulerDiscretization False
  bp2 <- blackScholesMertonProcess bs2Q bqTS2 brTS bvolTS2 EulerDiscretization False
  rhoMatrix <- either error pure (boxedRealMatrix 2 2 [1, brho, brho, 1])
  procArr <- stochasticProcessArray (bp1 :| [bp2]) rhoMatrix
  mc <- mcEuropeanBasketEngine PseudoRandom Statistics procArr (Just 1) Nothing False False (Just 20000) Nothing Nothing 42
  choi <- choiBasketEngine (bp1 :| [bp2]) rhoMatrix 10.0 100000 False False
  dlz <- dengLiZhouBasketEngine (bp1 :| [bp2]) rhoMatrix
  sfb <- singleFactorBsmBasketEngine (bp1 :| [bp2]) 1e-8

  -- Choi/DengLiZhou accept Average or Spread; SingleFactorBsm requires Average only
  spreadOpt <- basketOption (Spread (plainVanillaPayoff (PlainVanillaPayoff Call 0.0))) (European (EuropeanExercise maturity))
  setPricingEngine spreadOpt mc
  mcV <- npv spreadOpt
  setPricingEngine spreadOpt choi
  choiV <- npv spreadOpt
  setPricingEngine spreadOpt dlz
  dlzV <- npv spreadOpt

  avgOpt <- basketOption (Average (plainVanillaPayoff (PlainVanillaPayoff Call 100.0)) 2) (European (EuropeanExercise maturity))
  setPricingEngine avgOpt mc
  mcAvgV <- npv avgOpt
  setPricingEngine avgOpt sfb
  sfbV <- npv avgOpt
  printf "2-asset spread call: MC=%.4f Choi=%.4f DengLiZhou=%.4f\n" mcV choiV dlzV
  printf "2-asset average call (rho=%.2f, not single-factor): MC=%.4f SingleFactorBsm=%.4f (approximation, sanity-checked only)\n" brho mcAvgV sfbV
  check "ChoiBasketEngine vs MC" (approx (0.02 * mcV) mcV choiV)
  check "DengLiZhouBasketEngine vs MC" (approx (0.05 * mcV) mcV dlzV)
  -- SingleFactorBsmBasketEngine assumes every underlying is driven by one common factor (rho=1
  -- in effect); at rho=0.3 it is only a rough approximation, so just sanity-check it's finite
  -- and of the right order of magnitude here...
  check "SingleFactorBsmBasketEngine sanity (rho=0.3, approximation)" (sfbV > 0 && sfbV < 2 * mcAvgV)

  -- ...and verify it closely against MC at rho=1.0, where the single-factor assumption actually
  -- holds and the approximation becomes exact.
  rhoMatrix1 <- either error pure (boxedRealMatrix 2 2 [1, 1, 1, 1])
  procArr1 <- stochasticProcessArray (bp1 :| [bp2]) rhoMatrix1
  mc1 <- mcEuropeanBasketEngine PseudoRandom Statistics procArr1 (Just 1) Nothing False False (Just 20000) Nothing Nothing 42
  sfb1 <- singleFactorBsmBasketEngine (bp1 :| [bp2]) 1e-8
  setPricingEngine avgOpt mc1
  mcAvgV1 <- npv avgOpt
  setPricingEngine avgOpt sfb1
  sfbV1 <- npv avgOpt
  printf "2-asset average call (rho=1.0, single-factor): MC=%.4f SingleFactorBsm=%.4f\n" mcAvgV1 sfbV1
  check "SingleFactorBsmBasketEngine vs MC (rho=1.0)" (approx (0.02 * mcAvgV1) mcAvgV1 sfbV1)

  -- FdndimBlackScholesVanillaEngine (both overloads) vs Fd2dBlackScholesVanillaEngine, same
  -- 2-asset spread option as the cross-check above
  fdndim1 <- fdndimBlackScholesVanillaEngine (p1' :| [p2']) (either error id (boxedRealMatrix 2 2 [1, rho, rho, 1])) (50 :| [50]) 50 0 Douglas
  fdndim2 <- fdndimBlackScholesVanillaEngine' (p1' :| [p2']) (either error id (boxedRealMatrix 2 2 [1, rho, rho, 1])) 100 50 0 Douglas
  setPricingEngine crossOpt fdndim1
  fdndim1V <- npv crossOpt
  setPricingEngine crossOpt fdndim2
  fdndim2V <- npv crossOpt
  printf "Fdndim vs Fd2d: fdndim(explicit)=%.4f fdndim(auto)=%.4f fd2d=%.4f\n" fdndim1V fdndim2V fd2dV
  check "FdndimBlackScholesVanillaEngine (explicit grids) vs Fd2d" (approx 0.1 fd2dV fdndim1V)
  check "FdndimBlackScholesVanillaEngine (auto grid) vs Fd2d" (approx 0.1 fd2dV fdndim2V)

  putStrLn "OK basket/spread engines"
