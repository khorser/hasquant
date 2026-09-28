{-# LANGUAGE OverloadedLists #-}

-- Exercise MultiCurve with GlobalBootstrap against the compiled library.
--

import Control.Exception (SomeException, try)
import Control.Monad (forM_, when)
import Data.IORef (IORef, atomicModifyIORef', newIORef, writeIORef)
import Data.List (isInfixOf)
import Data.Maybe (isJust)
import System.IO.Unsafe (unsafePerformIO)
import QuantLib.CashFlow(iborLeg)

import Data.List.NonEmpty(fromList)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor3M, Euribor6M))
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Swap(swap)
import qualified QuantLib.InterestRate as IR
import QuantLib.PricingEngine(discountingSwapEngine)
import qualified QuantLib.Quote as Quote
import QuantLib.Context(setEvaluationDate, keepingSettingsGc, collectGarbage)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkWith)

curveToday :: Day
curveToday = 23 `october` 2025

-- Each probe keeps one value alive and drops the rest; all but Reentrant collect before evaluating.
data Ownership = External | Original | Internal | SpreadOverOriginal | Reentrant deriving Show

main :: IO ()
main = do
  forM_ ([External, Original, Internal, SpreadOverOriginal] :: [Ownership]) $ \ownership -> keepingSettingsGc $ do
    value <- case ownership of
      SpreadOverOriginal -> buildSpreadOverOriginal
      _ -> buildCycle ownership
    collectGarbage
    result <- try value :: IO (Either SomeException Double)
    case (ownership, result) of
      (External, Right v) -> checkWith "external pricing index retains MultiCurve"
        "only the instrument remains after GC" (abs v < 1.0e-4)
      (External, Left e) -> error ("External: " ++ show e)
      (_, Left e) -> checkWith (show ownership ++ " fails safely after the group is freed") (show e)
        (expectedFailure ownership `isInfixOf` show e)
      (_, Right _) -> error (show ownership ++ " unexpectedly retained the curve group")
    putStrLn ("multicurve " ++ show ownership ++ ": OK")
  keepingSettingsGc checkReentrantRelease

-- A quote callback drops the group's last owners and collects while the joint bootstrap runs.
checkReentrantRelease :: IO ()
checkReentrantRelease = do
  value <- buildCycle Reentrant
  d <- value
  checkWith "group released during its bootstrap finishes the call" (show d) (d > 0 && d < 1)
  -- No further collection: the group released inside the first call is freed when it returns.
  result <- try value :: IO (Either SomeException Double)
  case result of
    Left e -> checkWith "Reentrant fails safely after the group is freed" (show e)
      (expectedFailure Reentrant `isInfixOf` show e)
    Right _ -> error "Reentrant: the callback's collection did not release the curve group"
  putStrLn "multicurve Reentrant: OK"

-- The first callback after the owners are stored drops them and collects garbage.
releaseOnce :: IORef (Maybe a) -> Double -> Double
releaseOnce owners x = unsafePerformIO $ do
  held <- atomicModifyIORef' owners (\h -> (Nothing, isJust h))
  when held collectGarbage
  pure x
{-# NOINLINE releaseOnce #-}

expectedFailure :: Ownership -> String
expectedFailure SpreadOverOriginal = "empty Handle"
expectedFailure _ = "null term structure"

buildCycle :: Ownership -> IO (IO Double)
buildCycle ownership = do
  setEvaluationDate (Just curveToday)
  cal <- calendar TARGET
  euriborDC <- dayCounter (Actual360 False)
  settleFix <- advance cal curveToday (2, Days) Following False

  discQ <- Quote.simpleQuote 0.02
  discountCurve <- flatForward (SettlementDays 0 cal) discQ euriborDC IR.Continuous Annual

  -- 1. One curve through the new GlobalBootstrap dispatch path, standalone (no cycle): a
  -- plain FRA-only curve is enough to exercise qlPiecewiseYieldCurveGlobalBootstrap1 and the
  -- Discount/LogLinear branch added to qlPiecewiseYieldCurveAux1.
  q <- Quote.simpleQuote 0.03
  standaloneHelpers <- mapM (\i -> fraRateHelper q (FraMonths i (i + 3) 2 cal ModifiedFollowing True euriborDC) LastRelevantDate Nothing False) [1 .. 5]
  standaloneCurve <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList standaloneHelpers) euriborDC []
    (GlobalDiscountLogLinear 1.0e-10 []) False
  sixM <- advance cal settleFix (6, Months) ModifiedFollowing True
  standaloneDiscount <- discount standaloneCurve (DatePoint sixM) False
  checkWith "standalone GlobalBootstrap curve produces a sane discount factor"
            "confirms qlPiecewiseYieldCurveGlobalBootstrap1 actually dispatched, not just linked"
            (standaloneDiscount > 0 && standaloneDiscount < 1)

  -- 2. A genuine two-curve MultiCurve cycle: 3m/6m Euribor forecast curves whose rate helpers
  -- reference each other's not-yet-bootstrapped handle, the scenario RelinkableHandle exists
  -- for. Trimmed relative to the full test (fewer instruments), but still a real cycle.
  intcurve3m <- relinkableYieldTermStructure Nothing
  intcurve6m <- relinkableYieldTermStructure Nothing
  euribor3m <- iborIndex Euribor3M (Just intcurve3m)
  euribor6m <- iborIndex Euribor6M (Just intcurve6m)
  owners <- newIORef Nothing
  b0 <- Quote.simpleQuote 0.0020
  b <- Quote.withDerivedQuote (releaseOnce owners) b0 pure
  helpers3mFra <- mapM (\i -> fraRateHelper q (FraMonths i (i + 3) 2 cal ModifiedFollowing True euriborDC) LastRelevantDate Nothing False) [1 .. 3]
  helpers3mBasis <- mapM (\i -> iborIborBasisSwapRateHelper b (i, Years) 2 cal ModifiedFollowing True euribor3m euribor6m discountCurve True) [2 .. 4]
  helpers6mBasis <- mapM (\i -> iborIborBasisSwapRateHelper b (i * 6, Months) 2 cal ModifiedFollowing True euribor3m euribor6m discountCurve False) [1 .. 2]
  helpers6mSwap <- mapM (\i -> swapRateHelper q (SwapRateTenor (i, Years) cal Annual Following euriborDC euribor6m (0, Days) Nothing Nothing) Nothing (Just discountCurve)
                                  LastRelevantDate Nothing False Nothing Nothing) [2 .. 4]
    >>= mapM asRateHelper
  ptr3m <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList $ helpers3mFra ++ helpers3mBasis) euriborDC []
    (GlobalDiscountLogLinear 1.0e-10 []) False
  ptr6m <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList $ helpers6mBasis ++ helpers6mSwap) euriborDC []
    (GlobalDiscountLogLinear 1.0e-10 []) False
  mc <- multiCurve 1.0e-10
  curve3m <- addBootstrappedCurve mc intcurve3m ptr3m
  curve6m <- addBootstrappedCurve mc intcurve6m ptr6m
  duplicateInternal <- relinkableYieldTermStructure Nothing
  duplicate <- try (addBootstrappedCurve mc duplicateInternal ptr3m)
    :: IO (Either SomeException YieldTermStructure)
  case duplicate of
    Left e -> checkWith "duplicate member is rejected" (show e)
      ("already belongs" `isInfixOf` show e)
    Right _ -> error "duplicate member was accepted"

  (pricing3m, pricing6m) <- case ownership of
    External -> (,) <$> iborIndex Euribor3M (Just curve3m) <*> iborIndex Euribor6M (Just curve6m)
    _ -> pure (euribor3m, euribor6m)

  -- Reprice a 3m/6m basis swap built on the bootstrapped curves: should be ~0, the same
  -- self-consistency property the real test checks.
  bVal <- Quote.value b
  maturity <- advance cal settleFix (2, Years) ModifiedFollowing True
  baseSchedule <- schedule (Just settleFix) maturity (3, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing
  otherSchedule <- schedule (Just settleFix) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing
  baseLeg <- iborLeg baseSchedule pricing3m [1.0] euriborDC ModifiedFollowing [] [] [bVal] [] [] False False
  otherLeg <- iborLeg otherSchedule pricing6m [1.0] euriborDC ModifiedFollowing [] [] [] [] [] False False
  sw <- swap baseLeg otherLeg
  eng <- discountingSwapEngine discountCurve Nothing Nothing Nothing
  setPricingEngine sw eng
  -- curve3m/curve6m are the external handles addBootstrappedCurve hands back; confirm they're
  -- usable YieldTermStructures independent of the swap check above.
  d3m <- discount curve3m (DatePoint maturity) False
  d6m <- discount curve6m (DatePoint maturity) False
  checkWith "both external curve handles from the MultiCurve cycle give sane discount factors"
            "d3m/d6m come from addBootstrappedCurve's returned Handle<YieldTermStructure>"
            (d3m > 0 && d3m < 1 && d6m > 0 && d6m < 1)

  -- Original: only the 3m curve survives, so its recalculation must not reach the freed 6m curve.
  case ownership of
    Original -> pure (discount ptr3m (DatePoint maturity) False)
    Reentrant -> do
      -- The bump forces a joint bootstrap; its first quote callback, in a 3m helper, releases these
      -- owners, which leaves the running 3m curve owned only by the group.
      writeIORef owners (Just (mc, curve3m, curve6m))
      pure (Quote.setValue b0 0.0021 >> discount ptr6m (DatePoint maturity) False)
    _ -> pure (npv sw)

-- The reported cycle: the spreaded member is built over the other member's original handle.
buildSpreadOverOriginal :: IO (IO Double)
buildSpreadOverOriginal = do
  setEvaluationDate (Just curveToday)
  cal <- calendar TARGET
  euriborDC <- dayCounter (Actual360 False)
  thirty360 <- dayCounter Thirty360BondBasis
  intcurveois <- relinkableYieldTermStructure Nothing
  intcurve3m <- relinkableYieldTermStructure Nothing
  euribor3m <- iborIndex Euribor3M (Just intcurve3m)
  q <- Quote.simpleQuote 0.03
  b <- Quote.simpleQuote (-0.01)
  helpers3m <- mapM (\i -> swapRateHelper q (SwapRateTenor (i, Years) cal Annual Following thirty360 euribor3m (0, Days) Nothing Nothing) Nothing (Just intcurveois)
                              LastRelevantDate Nothing False Nothing Nothing
                            >>= asRateHelper) [1 .. 4 :: Int]
  ptr3m <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList helpers3m) euriborDC []
    (GlobalDiscountLogLinear 1.0e-10 []) False
  ptrois <- zeroSpreadedTermStructure ptr3m b IR.Continuous NoFrequency
  mc <- multiCurve 1.0e-10
  curve3m <- addBootstrappedCurve mc intcurve3m ptr3m
  curveois <- addNonBootstrappedCurve mc intcurveois ptrois
  bVal <- Quote.value b
  zOis <- IR.rate <$> zeroRate curveois (RateAtTime 1.0) IR.Continuous NoFrequency False
  z3m <- IR.rate <$> zeroRate curve3m (RateAtTime 1.0) IR.Continuous NoFrequency False
  checkWith "spread over an original member handle bootstraps"
            "the spreaded member tracks the bootstrapped member through the cycle"
            (abs (zOis - z3m - bVal) < 1.0e-10)
  -- A self-owning group would keep this non-owning internal link populated after GC.
  pure (discount intcurveois (TimePoint 1.0) False)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
