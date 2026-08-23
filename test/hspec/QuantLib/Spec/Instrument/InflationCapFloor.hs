module QuantLib.Spec.Instrument.InflationCapFloor (spec) where

import Control.Monad(forM_, forM)
import System.Mem(performGC)
import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.CashFlow(Leg, yoyInflationLeg)
import QuantLib.Currency(currency, Ccy(GBP))
import QuantLib.Instrument.Option(OptionType(..))
import QuantLib.TermStructure.Inflation
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import qualified QuantLib.InterestRate as IR
import QuantLib.InterestRate(VolatilityType(..))
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.InflationCapFloor
import QuantLib.PricingEngine(PricingEngine, yoyInflationBlackCapFloorEngine)
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.InflationVolatility
import QuantLib.TermStructure.Yield(flatForward, PillarChoice(..))
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

-- |A custom-named YoY index (rather than a shared named singleton like 'YYUKRPI') so this
-- module's made-up fixings and curve link can't collide with another test's fixings on the
-- same globally shared index-name fixing store -- QuantLib's fixing store is keyed by index
-- name, and hspec runs specs in random order, so any shared name is a latent cross-test
-- conflict.
customYoYIndex :: Maybe YoYInflationTermStructure -> IO YoYInflationIndex
customYoYIndex mts = do
  gbp <- currency GBP
  r <- region' "InflationCapFloor Test" "ICFT"
  yoyInflationIndex' "ICFT YoY" r False Monthly (1, Months) gbp mts

-- |Bootstraps a tiny YoY curve and returns an index linked to it. A YoY index's
-- 'needsForecast' (ql/indexes/inflationindex.cpp) is date-driven, not data-driven: any fixing
-- date beyond @evaluationDate - availabilityLag@ always forecasts through the index's own
-- linked 'YoYInflationTermStructure', regardless of whether a fixing has been manually added
-- for it -- so a future-dated cap/floor leg needs a real linked curve, not just extra
-- 'addFixing' calls (contrast 'QuantLib.Spec.Examples' CPI fixtures, which stay within the
-- historical window on purpose). Mirrors upstream's own CommonVars fixture
-- (test-suite/inflationcapfloor.cpp), minus the relinkable-handle indirection hasquant doesn't
-- expose for inflation curves: build the swap helpers off an unlinked index, bootstrap, then
-- construct a second, curve-linked index sharing the same family name (fixing history is keyed
-- by name, not object identity, so it's shared automatically).
linkedYoYIndex :: Day -> IO YoYInflationIndex
linkedYoYIndex today = do
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  yii0 <- customYoYIndex Nothing
  -- Fixings span [today-8y, today+1y] (not a hardcoded absolute range) so this test keeps
  -- working as the real wall-clock 'today' advances across future runs -- an absolute
  -- 2018-01..2026-01 window (this test's original form) silently falls out of range once
  -- 'today' itself passes 2026, since 'baseDate' below is derived from 'today'.
  fixingDates <- mapM (\n -> advance cal today (n, Months) Unadjusted False) [-96 .. 12 :: Int]
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing yii0 d (0.03 + i * 0.0001) False
  nominalQ <- simpleQuote 0.02
  nominalCurve <- flatForward today nominalQ dc IR.Continuous Annual
  maturity1 <- advance cal today (2, Years) Unadjusted False
  maturity2 <- advance cal today (5, Years) Unadjusted False
  q1 <- simpleQuote 0.03
  q2 <- simpleQuote 0.03
  h1 <- yearOnYearInflationSwapHelper q1 (3, Months) maturity1 cal Unadjusted dc yii0 CPIFlat nominalCurve LastRelevantDate Nothing
  h2 <- yearOnYearInflationSwapHelper q2 (3, Months) maturity2 cal Unadjusted dc yii0 CPIFlat nominalCurve LastRelevantDate Nothing
  baseDate <- advance cal today (-2, Months) Unadjusted False
  yoyCurve <- piecewiseYoYInflationCurve today baseDate 0.03 Monthly dc [h1, h2] Linear
  customYoYIndex (Just yoyCurve)

-- |A short YoY-inflation leg (3 annual coupons) on the given (curve-linked) index -- mirrors
-- the fixture in upstream's inflationcapfloor.cpp's CommonVars, trimmed to what a fast
-- structural-consistency check needs.
setupLeg :: YoYInflationIndex -> Day -> IO Leg
setupLeg yii today = do
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  endDate <- advance cal today (3, Years) Unadjusted False
  sch <- schedule (Just today) endDate (1, Years) cal Unadjusted Unadjusted Forward False Nothing Nothing
  yoyInflationLeg sch cal yii (3, Months) CPIFlat [1000000] dc Unadjusted [0] [1.0] [0.0]

-- |Builds the Black engine (constant vol) all cap\/floor\/collar instruments in this module
-- share -- mirrors 'QuantLib.Spec.TermStructure`'s "Black cap/floor engine" setup, YoY-inflation
-- flavoured.
setupEngine :: YoYInflationIndex -> Day -> IO PricingEngine
setupEngine yii today = do
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  nominalQ <- simpleQuote 0.02
  nominalCurve <- flatForward today nominalQ dc IR.Continuous Annual
  volQ <- simpleQuote 0.02
  vol <- constantYoYOptionletVolatility volQ 0 cal Unadjusted dc (3, Months) Annual False (-1.0) 100.0 ShiftedLognormal 0.0
  yoyInflationBlackCapFloorEngine yii vol nominalCurve

spec :: Spec
spec = do
 describe "YoY inflation cap/floor" $
  it "cap - floor = collar, and the sum of optionlets equals the parent NPV" $ Settings.keepingSettings' $ do
    -- Anchored to the real wall-clock date (like 'QuantLib.Spec.Examples`'s SimpleChooserOption),
    -- not a hardcoded past date: every maturity derived below is then always in the future, so a
    -- later test in the suite changing the global evaluation date can never see this test's
    -- still-alive curve/swap objects as stale. (An earlier version of this test hardcoded
    -- "2 january 2024" and relied on 'performGC' alone to finalize those objects before the next
    -- test moved the clock forward -- but 'performGC' only schedules finalizers, it doesn't run
    -- them synchronously, so that was a race rather than a fix.)
    todayD <- today
    Settings.setEvaluationDate (Just todayD)
    yii <- linkedYoYIndex todayD
    leg <- setupLeg yii todayD
    engine <- setupEngine yii todayD

    let capRate = 0.035
        floorRate = 0.025
    capInst <- yoyInflationCap leg [capRate]
    floorInst <- yoyInflationFloor leg [floorRate]
    collarInst <- yoyInflationCollar leg [capRate] [floorRate]
    mapM_ (`setPricingEngine` engine) [capInst, floorInst, collarInst]

    capNPV <- npv capInst
    floorNPV <- npv floorInst
    collarNPV <- npv collarInst
    abs ((capNPV - floorNPV) - collarNPV) `shouldSatisfy` (< 1e-6)

    caplets <- forM [0 .. 2 :: Word] $ \n -> do
      o <- yoyInflationCapFloorOptionlet capInst n
      setPricingEngine o engine
      npv o
    abs (capNPV - sum caplets) `shouldSatisfy` (< 1e-6)
    performGC
