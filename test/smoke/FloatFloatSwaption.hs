-- Smoke test for FloatFloatSwap/FloatFloatSwaption/Gaussian1dFloatFloatSwaptionEngine
-- (Gaussian1dModels.cpp port, increment 2). Mirrors the CMS-10Y-vs-Euribor-6M float-float
-- swaption built at ex/Gaussian1dModels.cpp:468-473 (gearing2/spread2 nonzero, everything else
-- upstream's default). Checks:
-- 1. Both FloatFloatSwap constructors materialize (flat-nominal via floatFloatSwap/
--    FloatFloatSwapOpts, per-period-nominal via floatFloatSwap'/FloatFloatSwapVaryingOpts).
-- 2. fairSpread1/fairSpread2 run without crashing once a pricing engine is attached.
-- 3. FloatFloatSwaption materializes from both underlyings and calibrationBasket returns a
--    non-empty basket in both CalibrationBasketNaive/MaturityStrikeByDeltaGamma modes -- reusing
--    the same peekPtrArray/retPtrArray plumbing increment 1 built and tested.
-- 4. Gaussian1dFloatFloatSwaptionEngine prices the swaption without crashing.
-- 5. additionalResults reports "underlyingValue" (Gaussian1dFloatFloatSwaptionEngine-specific).
--
-- Run with: .claude/skills/run-hasquant/driver.sh test/smoke/FloatFloatSwaption.hs
import Control.Monad (forM, forM_)
import Data.Maybe (mapMaybe)
import Data.List.NonEmpty(fromList)
import System.Exit (exitFailure)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import qualified QuantLib.Instrument as I
import QuantLib.Instrument
import QuantLib.Instrument.Option (BermudanExercise(..))
import QuantLib.Instrument.Swap
import QuantLib.Model hiding(setPricingEngine)
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.TermStructure.Volatility
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

main :: IO ()
main = do
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  settl <- advance cal today (2, Days) Following False
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)
  flatQ <- simpleQuote 0.03
  ts <- TS.flatForward settl flatQ dc365 Continuous Annual
  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
  swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)

  start <- advance cal settl (1, Years) ModifiedFollowing False
  maturity <- advance cal start (10, Years) ModifiedFollowing False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing

  -- 1a. Flat-nominal ctor -- CMS leg (gearing1=1, spread1=0) vs Euribor6M+10bp (spread2=0.0010),
  -- matching ex/Gaussian1dModels.cpp's underlying4.
  underlying1 <- floatFloatSwap Payer 1.0 1.0 fixedSchedule swapBase thirty360bb floatSchedule
    euribor6m act360 defaultFloatFloatSwapOpts{ffsSpread2 = 0.0010}

  -- 1b. Per-period-nominal ctor (full coverage; not used by the upstream example).
  -- leg 0 = CMS leg (schedule1/index1), not a FixedVsFloatingSwap's fixed leg -- FloatFloatSwap
  -- exchanges two floating legs, so use the generic Swap 'leg' accessor instead of 'fixedLeg'.
  bermudanDates <- leg underlying1 0 >>= CF.toCouponLeg >>= CF.couponAccrualStartDates
  let n = length bermudanDates
  underlying2 <- floatFloatSwap' Payer (replicate n 1.0) (replicate (2 * n) 1.0) fixedSchedule
    swapBase thirty360bb floatSchedule euribor6m act360
    defaultFloatFloatSwapVaryingOpts{ffsvSpread2 = replicate (2 * n) 0.0010}

  let ex = Bermudan (BermudanExercise (fromList bermudanDates) False)
  swpn1 <- floatFloatSwaption underlying1 ex Physical PhysicalOTC
  swpn2 <- floatFloatSwaption underlying2 ex Physical PhysicalOTC

  -- Leg 0 is a CMS leg (index1 = swapBase) -- CMS coupons always need a pricer, unlike the
  -- plain Euribor leg 1, which computes its forecast fixing directly.
  swaptionVolQ <- simpleQuote 0.20
  swaptionVolTS <- constantSwaptionVolatility 0 cal ModifiedFollowing swaptionVolQ dc365 ShiftedLognormal 0.0
  reversionQ <- simpleQuote 0.01
  cmsPricer <- CF.linearTsrPricer swaptionVolTS reversionQ Nothing
    (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
  forM_ [underlying1, underlying2] $ \u -> leg u 0 >>= (`CF.setCouponPricer` cmsPricer)

  gsrInitialVolQuote <- simpleQuote 0.01
  gsrStepVolQuotes <- forM [1 :: Int ..2] $ \_ -> simpleQuote 0.01
  gsrReversionQuote <- simpleQuote 0.01
  stepDates <- forM [1, 2 :: Int] $ \yr -> advance cal today (yr, Years) Following False
  gsrModel <- gsr ts gsrInitialVolQuote (zip stepDates gsrStepVolQuotes) gsrReversionQuote 60.0
  gsrGm <- gsrAsGaussian1dModel gsrModel
  engine <- gaussian1dFloatFloatSwaptionEngine gsrGm 64 7.0 True False Nothing (Just ts) True None
  forM_ [swpn1, swpn2] (`setPricingEngine` engine)

  -- 2. fairSpread1/fairSpread2 run without crashing once priced (via a plain swap pricing engine).
  swapEngine <- discountingSwapEngine ts Nothing Nothing Nothing
  I.setPricingEngine underlying1 swapEngine
  s1 <- fairSpread1 underlying1
  s2 <- fairSpread2 underlying1
  putStrLn ("fairSpread1: " ++ show s1 ++ ", fairSpread2: " ++ show s2)

  -- 3. calibrationBasket in both modes.
  basketNaive <- floatFloatSwaptionCalibrationBasket swpn1 swapBase swaptionVolTS CalibrationBasketNaive
  basketMSDG <- floatFloatSwaptionCalibrationBasket swpn1 swapBase swaptionVolTS MaturityStrikeByDeltaGamma
  putStrLn ("Naive basket size: " ++ show (length basketNaive))
  putStrLn ("MaturityStrikeByDeltaGamma basket size: " ++ show (length basketMSDG))
  if null basketNaive || null basketMSDG
    then putStrLn "MISMATCH: floatFloatSwaptionCalibrationBasket should return a non-empty basket in both modes" >> exitFailure
    else putStrLn "OK: floatFloatSwaptionCalibrationBasket returns non-empty baskets in both modes"

  -- 4. Gaussian1dFloatFloatSwaptionEngine prices without crashing.
  forM_ [swpn1, swpn2] $ \s -> do
    v <- npv s
    putStrLn ("FloatFloatSwaption NPV: " ++ show v)

  -- 5. additionalResults reports underlyingValue.
  results <- additionalResults swpn1
  let underlyingValues = mapMaybe (\(k, v) -> if k == "underlyingValue" then Just v else Nothing) results
  case underlyingValues of
    [RealVal uv] -> putStrLn ("OK: underlyingValue additional result = " ++ show uv)
    _ -> putStrLn ("MISMATCH: expected a single RealVal underlyingValue, got " ++ show underlyingValues) >> exitFailure

  putStrLn "FloatFloatSwaption smoke test passed"
