-- Smoke test for NonstandardSwap/NonstandardSwaption/calibrationBasket/
-- Gaussian1dNonstandardSwaptionEngine (Gaussian1dModels.cpp port, increment 1). Checks:
-- 1. All three NonstandardSwap constructors materialize (from-VanillaSwap, scalar
--    gearing/spread with per-period nominal/rate, vector gearing/spread).
-- 2. Both NonstandardSwaption constructors materialize (from-Swaption, swap+exercise).
-- 3. calibrationBasket in both Naive and MaturityStrikeByDeltaGamma modes returns a
--    non-empty basket -- this is what actually proves the peekPtrArray/retPtrArray/
--    qlFreePointerArray array marshalling built for this increment works end-to-end,
--    not just that it compiles (run under trackAllocations separately).
-- 4. Gaussian1dNonstandardSwaptionEngine prices the NonstandardSwaption without crashing.
--
-- Run with: .claude/skills/run-hasquant/driver.sh test/smoke/NonstandardSwaption.hs
import Control.Monad (forM, forM_)
import System.Exit (exitFailure)
import qualified Data.List.NonEmpty as NE

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
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

  start <- advance cal settl (1, Years) ModifiedFollowing False
  maturity <- advance cal start (10, Years) ModifiedFollowing False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  let strike = 0.04

  -- 1a. From-VanillaSwap ctor.
  vswp <- vanillaSwap Payer 1.0 fixedSchedule strike thirty360bb floatSchedule euribor6m 0.0 act360 (Just ModifiedFollowing) Nothing
  underlying1 <- nonstandardSwapFromVanilla vswp
  bermudanDates <- fixedLeg vswp >>= CF.toCouponLeg >>= CF.couponAccrualStartDates
  let ex = Bermudan (BermudanExercise (NE.fromList bermudanDates) False)
  swpn1 <- nonstandardSwaption underlying1 ex Physical PhysicalOTC

  -- 1b. Scalar gearing/spread, per-period nominal/rate (linear amortizing).
  let n = length bermudanDates
      nominalFixed = [1.0 - fromIntegral i / fromIntegral (max 1 (n - 1)) | i <- [0 .. n - 1]]
      strikes = replicate n strike
  underlying2 <- nonstandardSwap Payer nominalFixed (concatMap (\x -> [x, x]) nominalFixed) fixedSchedule strikes thirty360bb floatSchedule euribor6m 1.0 0.0 act360 False False Nothing
  swpn2 <- nonstandardSwaption underlying2 ex Physical PhysicalOTC

  -- 1c. Vector gearing/spread ctor (full coverage; not used by the upstream example).
  underlying3 <- nonstandardSwap' Payer nominalFixed (concatMap (\x -> [x, x]) nominalFixed) fixedSchedule strikes thirty360bb floatSchedule euribor6m (replicate (2 * n) 1.0) (replicate (2 * n) 0.0) act360 False False Nothing
  _swpn3 <- nonstandardSwaption underlying3 ex Physical PhysicalOTC

  -- 2. From-Swaption ctor.
  plainSwpn <- swaption vswp ex Physical PhysicalOTC
  _swpnFromSwaption <- nonstandardSwaptionFromSwaption plainSwpn

  -- 3. calibrationBasket in both modes -- needs a BasketGeneratingEngine (i.e. this engine)
  -- already attached to the swaption before it's called.
  gsrInitialVolQuote <- simpleQuote 0.01
  gsrStepVolQuotes <- forM [1 :: Int ..2] $ \_ -> simpleQuote 0.01
  gsrReversionQuote <- simpleQuote 0.01
  stepDates <- forM [1, 2 :: Int] $ \yr -> advance cal today (yr, Years) Following False
  gsrModel <- gsr ts gsrInitialVolQuote (zip stepDates gsrStepVolQuotes) gsrReversionQuote 60.0
  gsrGm <- gsrAsGaussian1dModel gsrModel
  engine <- gaussian1dNonstandardSwaptionEngine gsrGm 32 5.0 True False Nothing (Just ts) None
  forM_ [swpn1, swpn2] (`setPricingEngine` engine)

  swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
  swaptionVolQ <- simpleQuote 0.20
  swaptionVolTS <- constantSwaptionVolatility 0 cal ModifiedFollowing swaptionVolQ dc365 ShiftedLognormal 0.0
  basketNaive <- calibrationBasket swpn1 swapBase swaptionVolTS CalibrationBasketNaive
  basketMSDG <- calibrationBasket swpn1 swapBase swaptionVolTS MaturityStrikeByDeltaGamma
  putStrLn ("Naive basket size: " ++ show (length basketNaive))
  putStrLn ("MaturityStrikeByDeltaGamma basket size: " ++ show (length basketMSDG))
  if null basketNaive || null basketMSDG
    then putStrLn "MISMATCH: calibrationBasket should return a non-empty basket in both modes" >> exitFailure
    else putStrLn "OK: calibrationBasket returns non-empty baskets in both modes"

  -- 4. Gaussian1dNonstandardSwaptionEngine prices without crashing.
  forM_ [swpn1, swpn2] $ \s -> do
    v <- npv s
    putStrLn ("NonstandardSwaption NPV: " ++ show v)

  putStrLn "NonstandardSwaption smoke test passed"
