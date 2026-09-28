{-# LANGUAGE OverloadedLists #-}

-- Exercise MultiCurve with GlobalBootstrap against the compiled library.
--

import Control.Exception (SomeException, try)
import Control.Monad (forM_)
import Data.List (isInfixOf)
import QuantLib.CashFlow(iborLeg)

import Data.List.NonEmpty(fromList)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor3M, Euribor6M))
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Swap(Swap, swap)
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

data Ownership = External | Original | Internal deriving Show

main :: IO ()
main = forM_ ([External, Original, Internal] :: [Ownership]) $ \ownership -> keepingSettingsGc $ do
  sw <- buildSwap ownership
  collectGarbage
  result <- try (npv sw) :: IO (Either SomeException Double)
  case (ownership, result) of
    (Internal, Left e) -> checkWith "expired internal handle fails safely" (show e)
      ("null term structure" `isInfixOf` show e)
    (Internal, Right _) -> error "internal handle unexpectedly retained the curve group"
    (_, Right v) -> checkWith (show ownership ++ " pricing index retains MultiCurve")
      "only the instrument remains after GC" (abs v < 1.0e-4)
    (_, Left e) -> error (show ownership ++ ": " ++ show e)
  putStrLn ("multicurve " ++ show ownership ++ ": OK")

buildSwap :: Ownership -> IO Swap
buildSwap ownership = do
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
  b <- Quote.simpleQuote 0.0020
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
  original3m <- iborIndex Euribor3M (Just ptr3m)
  original6m <- iborIndex Euribor6M (Just ptr6m)
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
    Original -> pure (original3m, original6m)
    Internal -> pure (euribor3m, euribor6m)

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

  pure sw

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
