-- Smoke test: construct every named zero/YoY inflation index and CPI
-- interpolation-type enum case, then bootstrap a tiny zero-coupon and
-- year-on-year inflation curve end-to-end and print the implied rates, so a
-- stale c2hs-generated enum or wrong factory-table entry shows up
-- immediately, not just "the build succeeded" (see reconcile-*/
-- add-quantlib-index skills' "gotcha" notes).
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckInflation.hs -o /tmp/checkinfl -outputdir /tmp/checkinfl_build && /tmp/checkinfl
import Control.Monad
import qualified QuantLib.InterestRate as IR
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import QuantLib.Math(Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.Inflation
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..), TimeUnit(..))

-- c2hs only derives Show/Eq for these enums (no Bounded), so the case lists
-- are spelled out explicitly here rather than via [minBound .. maxBound].
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
  h1 <- zeroCouponInflationSwapHelper q1 obsLag maturity1 cal Unadjusted dc zii CPILinear
  h2 <- zeroCouponInflationSwapHelper q2 obsLag maturity2 cal Unadjusted dc zii CPILinear
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
  hy1 <- yearOnYearInflationSwapHelper qy1 obsLag maturity1 cal Unadjusted dc yii CPILinear nominalCurve
  hy2 <- yearOnYearInflationSwapHelper qy2 obsLag maturity2 cal Unadjusted dc yii CPILinear nominalCurve
  yoyCurve <- piecewiseYoYInflationCurve today baseDate 0.03 Monthly dc [hy1, hy2] Linear
  ry1 <- yoyRate yoyCurve maturity1 True
  ry2 <- yoyRate yoyCurve maturity2 True
  putStrLn ("yoyRate @1Y = " ++ show ry1 ++ ", @2Y = " ++ show ry2 ++ " (both should be ~0.03)")
  where
    today = 2 `january` 2024
    baseDate = 1 `october` 2023
    obsLag = (3, Months)
    maturity1 = 2 `january` 2025
    maturity2 = 2 `january` 2026
