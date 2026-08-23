module QuantLib.Spec.Instrument.InflationCapFloor (spec) where

import Control.Monad(forM_, forM)
import Data.Time.Calendar(toGregorian, fromGregorian)
import System.Mem(performGC)
import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.CashFlow(Leg, yoyInflationLeg, blackYoYInflationCouponPricer, setYoYInflationCouponPricer)
import qualified QuantLib.CashFlow as CF
import QuantLib.Currency(currency, Ccy(GBP))
import QuantLib.Instrument.Option(OptionType(..))
import QuantLib.TermStructure.Inflation
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import qualified QuantLib.InterestRate as IR
import QuantLib.InterestRate(VolatilityType(..))
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.InflationCapFloor
import QuantLib.Math(Interpolation(..), Matrix(..))
import QuantLib.PricingEngine(PricingEngine, yoyInflationBlackCapFloorEngine, interpolatingCPICapFloorEngine)
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
  yoyInflationLeg sch cal yii (3, Months) CPIFlat [1000000] dc Unadjusted [0] [1.0] [0.0] [] []

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

-- |A custom-named zero index, linked to a tiny bootstrapped 'ZeroInflationTermStructure' --
-- same fixing-store-isolation reasoning as 'customYoYIndex'. A link is required even though the
-- price surface only ever queries its own price grid: 'InterpolatedCPICapFloorTermPriceSurface's
-- @performCalculations@ computes each grid column's ATM level via the index's own
-- 'QuantLib.TermStructure.Inflation.ZeroInflationTermStructure' (put\/call parity, see this
-- type's own C++ haddock), which throws "ZITS missing from index" if unset -- mirrors upstream's
-- own CommonVars building 'PiecewiseZeroInflationCurve' before the price surface.
customZeroIndex :: Day -> IO ZeroInflationIndex
customZeroIndex today = do
  gbp <- currency GBP
  r <- region' "InflationCapFloor CPI Test" "ICFCT"
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  zii0 <- zeroInflationIndex' "ICFCT Zero" r False Monthly (1, Months) gbp Nothing
  -- Same today-relative fixing window as 'linkedYoYIndex', for the same reason.
  fixingDates <- mapM (\n -> advance cal today (n, Months) Unadjusted False) [-96 .. 12 :: Int]
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing zii0 d (100.0 + i * 0.1) False
  maturity1 <- advance cal today (2, Years) Unadjusted False
  -- 10y, not 5y: this curve must reach past the price surface's own widest grid maturity (7y,
  -- see the CPI cap/floor test below) since 'InterpolatedCPICapFloorTermPriceSurface's
  -- performCalculations computes each grid column's ATM level off this index's linked curve.
  maturity2 <- advance cal today (10, Years) Unadjusted False
  q1 <- simpleQuote 0.03
  q2 <- simpleQuote 0.03
  h1 <- zeroCouponInflationSwapHelper q1 (2, Months) maturity1 cal Unadjusted dc zii0 CPIFlat LastRelevantDate Nothing
  h2 <- zeroCouponInflationSwapHelper q2 (2, Months) maturity2 cal Unadjusted dc zii0 CPIFlat LastRelevantDate Nothing
  baseDate <- advance cal today (-2, Months) Unadjusted False
  zeroCurve <- piecewiseZeroInflationCurve today baseDate Monthly dc [h1, h2] Linear
  zeroInflationIndex' "ICFCT Zero" r False Monthly (1, Months) gbp (Just zeroCurve)

spec :: Spec
spec = do
 describe "YoY inflation cap/floor" $ do
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

  it "a capped yoyInflationLeg's NPV decomposes as uncapped leg NPV minus the equivalent cap's NPV" $ Settings.keepingSettings' $ do
    -- Confirmed by reading inflationcoupon.cpp: InflationCoupon::rate() unconditionally requires
    -- a pricer (QL_REQUIRE(pricer_, "pricer not set")), capped or not -- yoyInflationLeg's own
    -- operator Leg() (yoyinflationcoupon.cpp) auto-attaches a default (non-vol) pricer only when
    -- caps and floors are BOTH empty; a non-empty cap here means 'setYoYInflationCouponPricer'
    -- must be called explicitly, and this test's NPV assertion below only succeeds if it actually
    -- ran (leaving it out reproduces "pricer not set", not a silently-wrong number) -- so this
    -- doubles as the setter's own regression check.
    todayD <- today
    Settings.setEvaluationDate (Just todayD)
    yii <- linkedYoYIndex todayD
    cal <- calendar Null
    dc <- dayCounter Actual365FixedStandard
    endDate <- advance cal todayD (3, Years) Unadjusted False
    sch <- schedule (Just todayD) endDate (1, Years) cal Unadjusted Unadjusted Forward False Nothing Nothing

    let capRate = 0.035
    cappedLeg <- yoyInflationLeg sch cal yii (3, Months) CPIFlat [1000000] dc Unadjusted [0] [1.0] [0.0] [capRate] []
    uncappedLeg <- yoyInflationLeg sch cal yii (3, Months) CPIFlat [1000000] dc Unadjusted [0] [1.0] [0.0] [] []

    nominalQ <- simpleQuote 0.02
    nominalCurve <- flatForward todayD nominalQ dc IR.Continuous Annual
    volQ <- simpleQuote 0.02
    vol <- constantYoYOptionletVolatility volQ 0 cal Unadjusted dc (3, Months) Annual False (-1.0) 100.0 ShiftedLognormal 0.0
    pricer <- blackYoYInflationCouponPricer vol nominalCurve
    setYoYInflationCouponPricer cappedLeg pricer

    cappedNPV <- CF.npv cappedLeg nominalCurve True Nothing Nothing
    uncappedNPV <- CF.npv uncappedLeg nominalCurve True Nothing Nothing

    capEngine <- yoyInflationBlackCapFloorEngine yii vol nominalCurve
    capInst <- yoyInflationCap uncappedLeg [capRate]
    setPricingEngine capInst capEngine
    capNPV <- npv capInst

    abs ((uncappedNPV - capNPV) - cappedNPV) `shouldSatisfy` (< 1e-6)
    performGC

 describe "CPI cap/floor" $
  -- CPI cap/floor has no vol-driven engine in QL 1.43 -- InterpolatingCPICapFloorEngine prices
  -- purely by interpolating a market price surface (see cbits/qlInflationVol.cpp's
  -- qlInterpolatingCPICapFloorEngine and CPICapFloorTermPriceSurface's own haddock). At an
  -- exact grid node the interpolation is an identity, so this reproduces the input price
  -- exactly rather than just approximately -- mirrors upstream's own
  -- test-suite/inflationcpicapfloor.cpp::cpicapfloorpricer, whose fixture is built the same
  -- way: pick an evaluation date on the 1st of a month (so "the start of the inflation period
  -- containing the maturity", what CPI::Flat actually samples, coincides exactly with the
  -- maturity itself) and a maturity/strike that exactly match one price-surface grid node.
  -- baseCPI is a required constructor argument but never touched by this engine's calculate()
  -- (confirmed by reading cpicapfloorengines.cpp) so an arbitrary placeholder is fine.
  it "reproduces the exact grid price at a matching strike/maturity node" $ Settings.keepingSettings' $ do
    -- First-of-month, derived from the real wall-clock date rather than hardcoded, so
    -- CPI::Flat's period-start sampling (see the comment above) lands exactly on the raw date
    -- without pinning the test to a date that will eventually become stale/past.
    (y, m, _) <- toGregorian <$> today
    let today' = fromGregorian y m 1
    Settings.setEvaluationDate (Just today')
    cal <- calendar Null
    dc <- dayCounter Actual365FixedStandard
    nominalQ <- simpleQuote 0.02
    nominalCurve <- flatForward today' nominalQ dc IR.Continuous Annual
    zii <- customZeroIndex today'
    maturity5Y <- advance cal today' (5, Years) Unadjusted False

    let obsLag = (2, Months)
        cStrike = 0.04
        fStrike = 0.01
        cPriceGrid = 0.01279
        fPriceGrid = 0.006666
    -- A non-square (2 strikes x 3 maturities) slice of upstream's own cached cap/floor price
    -- grid (test-suite/inflationcpicapfloor.cpp's cPrice/fPrice tables, strikes 0.03/0.04 and
    -- 0.01/-0.01, maturities 3Y/5Y/7Y), row-major by strike then maturity -- deliberately
    -- non-square so a Matrix construction that silently transposed strikes/maturities (rather
    -- than throwing a dimension mismatch) would produce a detectably wrong value here; a square
    -- grid can't distinguish the two orientations. The assertions below check the (strike
    -- 0.04, maturity 5Y) and (strike 0.01, maturity 5Y) cells -- both off the [0][0] corner --
    -- rather than only the corner a transposed 2x2 grid would still get right by accident.
    surface <- cpiCapFloorTermPriceSurface 1.0 cStrike obsLag cal Unadjusted dc zii CPIFlat nominalCurve
      [0.03, cStrike] [-0.01, fStrike] [(3, Years), (5, Years), (7, Years)]
      (Matrix 2 3 [0.02276, 0.034532, 0.047795, 0.010027, cPriceGrid, 0.017019])
      (Matrix 2 3 [0.001562, 0.002145, 0.002445, 0.005361, fPriceGrid, 0.007704])
    engine <- interpolatingCPICapFloorEngine surface

    capInst <- cpiCapFloor Call 1.0 today' 100.0 maturity5Y cal Unadjusted cal Unadjusted cStrike zii obsLag CPIFlat
    setPricingEngine capInst engine
    capNPV <- npv capInst
    abs (capNPV - cPriceGrid) `shouldSatisfy` (< 1e-9)

    floorInst <- cpiCapFloor Put 1.0 today' 100.0 maturity5Y cal Unadjusted cal Unadjusted fStrike zii obsLag CPIFlat
    setPricingEngine floorInst engine
    floorNPV <- npv floorInst
    abs (floorNPV - fPriceGrid) `shouldSatisfy` (< 1e-9)
    performGC
