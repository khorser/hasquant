-- Stale-build guard for the GlobalBootstrap dispatch branch and MultiCurve binding.
--
-- The behavioural checks live in the "multi-curve bootstrap (GlobalBootstrap + MultiCurve
-- cycle)" block nested inside main/test/QuantLib/Spec/TermStructure.hs's "relinkable handles"
-- describe group, and run on every `stack test`. This file exists for the one thing test/
-- structurally cannot catch: editing a C header without touching any .chs leaves cabal/stack
-- silently stale -- neither tracks that a .chs file's #include'd header changed, so the build
-- reports success without re-running c2hs and the tests then pass against the *old* generated
-- code. qlPiecewiseYieldCurveAux1 gained a new (bootstrap, accuracy) dispatch parameter and
-- QlMultiCurve is a brand-new typedef in cbits/qlaux.h -- both are exactly the kind of change
-- that wouldn't be caught by a stale build. Compiled standalone against the installed library,
-- this script sees whatever was actually built.
--
-- Run with:
--   cabal exec -- ghc -ismoke -package hasquant smoke/CheckMultiCurve.hs -o /tmp/mc_smoke -outputdir /tmp/mc_smoke_build && /tmp/mc_smoke

import QuantLib.CashFlow(iborLeg)
import qualified Data.List.NonEmpty as NE
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor3M, Euribor6M))
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Swap(swap)
import qualified QuantLib.InterestRate as IR
import QuantLib.PricingEngine(discountingSwapEngine)
import qualified QuantLib.Quote as Quote
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkWith)

curveToday :: Day
curveToday = 23 `october` 2025

main :: IO ()
main = do
  setEvaluationDate (Just curveToday)
  cal <- calendar TARGET
  euriborDC <- dayCounter (Actual360 False)
  settleFix <- advance cal curveToday (2, Days) Following False

  discQ <- Quote.simpleQuote 0.02
  discountCurve <- flatForward' 0 cal discQ euriborDC IR.Continuous Annual

  -- 1. One curve through the new GlobalBootstrap dispatch path, standalone (no cycle): a
  -- plain FRA-only curve is enough to exercise qlPiecewiseYieldCurveGlobalBootstrap1 and the
  -- Discount/LogLinear branch added to qlPiecewiseYieldCurveAux1.
  q <- Quote.simpleQuote 0.03
  standaloneHelpers <- mapM (\i -> fraRateHelper q i (i + 3) 2 cal ModifiedFollowing True euriborDC LastRelevantDate Nothing False) [1 .. 5]
  standaloneCurve <- piecewiseYieldCurveGlobalBootstrap' 0 cal (NE.fromList standaloneHelpers) euriborDC [] 1.0e-10 [] False
  sixM <- advance cal settleFix (6, Months) ModifiedFollowing True
  standaloneDiscount <- discount' standaloneCurve sixM False
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
  helpers3mFra <- mapM (\i -> fraRateHelper q i (i + 3) 2 cal ModifiedFollowing True euriborDC LastRelevantDate Nothing False) [1 .. 3]
  helpers3mBasis <- mapM (\i -> iborIborBasisSwapRateHelper b (i, Years) 2 cal ModifiedFollowing True euribor3m euribor6m discountCurve True) [2 .. 4]
  helpers6mBasis <- mapM (\i -> iborIborBasisSwapRateHelper b (i * 6, Months) 2 cal ModifiedFollowing True euribor3m euribor6m discountCurve False) [1 .. 2]
  helpers6mSwap <- mapM (\i -> swapRateHelper' q (i, Years) cal Annual Following euriborDC euribor6m Nothing (0, Days) (Just discountCurve)
                                  Nothing LastRelevantDate Nothing False Nothing Nothing Nothing) [2 .. 4]
    >>= mapM asRateHelper
  ptr3m <- piecewiseYieldCurveGlobalBootstrap' 0 cal (NE.fromList $ helpers3mFra ++ helpers3mBasis) euriborDC [] 1.0e-10 [] False
  ptr6m <- piecewiseYieldCurveGlobalBootstrap' 0 cal (NE.fromList $ helpers6mBasis ++ helpers6mSwap) euriborDC [] 1.0e-10 [] False
  mc <- multiCurve 1.0e-10
  curve3m <- addBootstrappedCurve mc intcurve3m ptr3m
  curve6m <- addBootstrappedCurve mc intcurve6m ptr6m

  -- Reprice a 3m/6m basis swap built on the bootstrapped curves: should be ~0, the same
  -- self-consistency property the real test checks.
  bVal <- Quote.value b
  maturity <- advance cal settleFix (2, Years) ModifiedFollowing True
  baseSchedule <- schedule (Just settleFix) maturity (3, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing
  otherSchedule <- schedule (Just settleFix) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward True Nothing Nothing
  baseLeg <- iborLeg baseSchedule euribor3m (1.0 NE.:| []) euriborDC ModifiedFollowing [] [] [bVal] [] [] False False
  otherLeg <- iborLeg otherSchedule euribor6m (1.0 NE.:| []) euriborDC ModifiedFollowing [] [] [] [] [] False False
  sw <- swap baseLeg otherLeg
  eng <- discountingSwapEngine discountCurve Nothing Nothing Nothing
  setPricingEngine sw eng
  v <- npv sw
  checkWith "MultiCurve-cycle basis swap reprices to ~0"
            "confirms curve3m/curve6m came out of a genuine bidirectional bootstrap, not stale finalizer wiring"
            (abs v < 1.0e-4)

  -- curve3m/curve6m are the external handles addBootstrappedCurve hands back; confirm they're
  -- usable YieldTermStructures independent of the swap check above.
  d3m <- discount' curve3m maturity False
  d6m <- discount' curve6m maturity False
  checkWith "both external curve handles from the MultiCurve cycle give sane discount factors"
            "d3m/d6m come from addBootstrappedCurve's returned Handle<YieldTermStructure>"
            (d3m > 0 && d3m < 1 && d6m > 0 && d6m < 1)

  putStrLn "multicurve: all checks passed"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
