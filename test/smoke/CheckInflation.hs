-- Smoke test: construct every named zero/YoY inflation index and CPI
-- interpolation-type enum case, then bootstrap a tiny zero-coupon and
-- year-on-year inflation curve end-to-end and print the implied rates, so a
-- stale c2hs-generated enum or wrong factory-table entry shows up
-- immediately, not just "the build succeeded" (see reconcile-*/
-- add-quantlib-index skills' "gotcha" notes).
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckInflation.hs -o /tmp/checkinfl -outputdir /tmp/checkinfl_build && /tmp/checkinfl
import Control.Monad
import qualified QuantLib.CashFlow as CF
import qualified QuantLib.InterestRate as IR
import QuantLib.Currency(currency, Ccy(GBP))
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import QuantLib.Math(Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Inflation
import QuantLib.TermStructure.Yield(flatForward, PillarChoice(..))
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, fromDates, DayCounterConstructor(..), Frequency(..), TimeUnit(..))

import SmokeCheck (checkWith)

-- c2hs only derives Show/Eq for the *Type enums (no Bounded), so those case
-- lists are spelled out explicitly here rather than via [minBound .. maxBound].
main :: IO ()
main = do
  forM_ [AUCPI, EUHICP, EUHICPXT, FRHICP, UKHICP, UKRPI, USCPI, ZACPI] $ \ty -> do
    idx <- zeroInflationIndex ty
    addFixing idx (1 `january` 2020) 100.0 False
    f <- fixing idx (1 `january` 2020)
    putStrLn (show ty ++ " -> fixing " ++ show f)
  forM_ [YYAUCPI, YYEUHICP, YYEUHICPXT, YYFRHICP, YYUKRPI, YYUSCPI, YYZACPI] $ \ty -> do
    idx <- yoyInflationIndex ty
    addFixing idx (1 `january` 2020) 0.03 False
    f <- yoyFixing idx (1 `january` 2020)
    putStrLn (show ty ++ " -> fixing " ++ show f)

  forM_ [minBound .. maxBound :: RegionType] $ \ty -> do
    r <- region ty
    putStrLn (show ty ++ " -> " ++ show r)

  gbp <- currency GBP
  customRegion <- region' "Wonderland" "WL"
  zii' <- zeroInflationIndex' "WL CPI" customRegion False Monthly (1, Months) gbp Nothing
  addFixing zii' (1 `january` 2019) 97.0 False
  addFixing zii' (1 `january` 2020) 100.0 False
  fz' <- fixing zii' (1 `january` 2020)
  putStrLn ("custom zeroInflationIndex' -> fixing " ++ show fz')

  yii' <- yoyInflationIndex' "WL YoY CPI" customRegion False Monthly (1, Months) gbp Nothing
  addFixing yii' (1 `january` 2020) 0.03 False
  fy' <- yoyFixing yii' (1 `january` 2020)
  putStrLn ("custom yoyInflationIndex' -> fixing " ++ show fy')

  -- ratio YoY index needs the underlying zero index's fixings a year apart
  yiiRatio <- yoyInflationIndexFromZero zii' Nothing
  fyr <- yoyFixing yiiRatio (1 `january` 2020)
  putStrLn ("yoyInflationIndexFromZero (ratio off custom zero index) -> fixing " ++ show fyr)

  setEvaluationDate $ Just today
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  -- UKRPI needs a fixing near every month up to referenceDate, not just at
  -- baseDate, or the bootstrap fails with "Missing UK RPI fixing for ..."
  fixingDates <- mapM (\n -> advance cal (1 `january` 2022) (n, Months) Unadjusted False) [0 .. 24 :: Int]

  zii <- zeroInflationIndex UKRPI
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing zii d (260.0 + i) False
  q1 <- simpleQuote 0.03
  q2 <- simpleQuote 0.03
  h1 <- zeroCouponInflationSwapHelper q1 obsLag maturity1 cal Unadjusted dc zii CPILinear LastRelevantDate Nothing
  h2 <- zeroCouponInflationSwapHelper q2 obsLag maturity2 cal Unadjusted dc zii CPILinear LastRelevantDate Nothing
  curve <- piecewiseZeroInflationCurve today baseDate Monthly dc [h1, h2] Linear
  r1 <- zeroRate curve maturity1 True
  r2 <- zeroRate curve maturity2 True
  putStrLn ("zeroRate @1Y = " ++ show r1 ++ ", @2Y = " ++ show r2 ++ " (both should be ~0.03)")

  yii <- yoyInflationIndex YYUKRPI
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing yii d (0.03 + i * 0.0001) False
  nominalQ <- simpleQuote 0.02
  nominalCurve <- flatForward today nominalQ dc IR.Continuous Annual
  qy1 <- simpleQuote 0.03
  qy2 <- simpleQuote 0.03
  hy1 <- yearOnYearInflationSwapHelper qy1 obsLag maturity1 cal Unadjusted dc yii CPILinear nominalCurve LastRelevantDate Nothing
  hy2 <- yearOnYearInflationSwapHelper qy2 obsLag maturity2 cal Unadjusted dc yii CPILinear nominalCurve LastRelevantDate Nothing
  yoyCurve <- piecewiseYoYInflationCurve today baseDate 0.03 Monthly dc [hy1, hy2] Linear
  ry1 <- yoyRate yoyCurve maturity1 True
  ry2 <- yoyRate yoyCurve maturity2 True
  putStrLn ("yoyRate @1Y = " ++ show ry1 ++ ", @2Y = " ++ show ry2 ++ " (both should be ~0.03)")

  -- CPIInterpolationType is a hand-written Enum in QuantLib.Internal.Type (not c2hs
  -- {#enum#}-derived, see its haddock) that must stay in sync with cbits/qlEnumObjects.h by
  -- hand -- exercise *both* cases and confirm they actually diverge numerically, not just that
  -- each constructs without crashing. fixingDates are on the 1st of each month with strictly
  -- increasing values, and this leg's schedule dates are mid-month (and after the evaluation
  -- date set above, or CashFlows::npv would exclude the cashflow as already-occurred
  -- regardless of interpolation), so CPIFlat's last-published-fixing lookup and CPILinear's
  -- interpolation between straddling fixings must disagree.
  --
  -- The second (coupon) date must also stay within zii's "available" window: even with a
  -- manually-added future fixing, ZeroInflationIndex::needsForecast forces forecasting (and
  -- since zii has no linked curve, throws "empty Handle") for any month past
  -- evaluationDate-availabilityLag, independent of whether historical data was actually
  -- supplied for it -- see ql/indexes/inflationindex.cpp. With today = 2 Jan 2024,
  -- availabilityLag = 1M and obsLag = 3M, CPILinear's forward-bracketing fixing must resolve
  -- to Dec 2023 or earlier, which bounds the coupon date to on/before ~end of Feb 2024.
  midMonthSchedule <- fromDates [3 `january` 2024, 20 `february` 2024] cal Unadjusted Nothing Nothing Nothing Nothing
  legFlat <- CF.cpiLeg midMonthSchedule zii 260.0 obsLag [100.0] [0.05] dc Unadjusted cal CPIFlat True
  legLinear <- CF.cpiLeg midMonthSchedule zii 260.0 obsLag [100.0] [0.05] dc Unadjusted cal CPILinear True
  npvFlat <- CF.npv legFlat nominalCurve True Nothing Nothing
  npvLinear <- CF.npv legLinear nominalCurve True Nothing Nothing
  putStrLn ("cpiLeg NPV: CPIFlat=" ++ show npvFlat ++ ", CPILinear=" ++ show npvLinear ++ " (must differ)")
  checkWith "cpiLeg CPIFlat vs CPILinear"
    "NPVs differ (equality means the CPIInterpolationType mapping may be stale)"
    (npvFlat /= npvLinear)
  where
    today = 2 `january` 2024
    baseDate = 1 `october` 2023
    obsLag = (3, Months)
    maturity1 = 2 `january` 2025
    maturity2 = 2 `january` 2026
