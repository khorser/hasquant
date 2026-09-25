-- Interpolated zero inflation curves and construction-time price seasonality. Expected
-- seasonal rates follow MultiplicativePriceSeasonality::seasonalityCorrection on a flat curve.
module QuantLib.Spec.TermStructure.Inflation (spec) where

import Control.Monad(forM_)
import Data.List.NonEmpty(fromList)
import Data.Time.Calendar(Day, fromGregorian, addGregorianMonthsClip, diffDays)
import Test.Hspec

import qualified QuantLib.Context as Context
import QuantLib.Currency(currency, Ccy(GBP))
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation(customRegion, customZeroInflationIndex, customYoyInflationIndex)
import qualified QuantLib.InterestRate as IR
import QuantLib.Math(Interpolation(..), Approximation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Inflation
import QuantLib.TermStructure.Yield(PillarChoice(..), Reference(..), flatForward)
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule

import QuantLib.Spec.Helpers(closePrec)

baseDate :: Day
baseDate = fromGregorian 2020 1 1

monthly :: Integer -> Day
monthly k = addGregorianMonthsClip k baseDate

-- A zero inflation curve bootstrapped from 2Y and 10Y zero-coupon swaps on a custom monthly
-- index with a linear fixing history, the swaps' dates given by 'period' from the evaluation date
-- and each maturity. Returns the curve's zero rate a year out.
zeroCouponCurveRate :: Day -> (Day -> Day -> InflationSwapPeriod) -> CPIInterpolationType -> IO Double
zeroCouponCurveRate evalDate period interp = do
  gbp <- currency GBP
  r <- customRegion "InflationSwapHelper Test" "ISHT"
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  zii0 <- customZeroInflationIndex "ISHT Zero" r False Monthly (1, Months) gbp Nothing
  fixingDates <- mapM (\n -> advance cal evalDate (n, Months) Unadjusted False) [-96 .. 12 :: Int]
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing zii0 d (100.0 + i * 0.1) False
  helpers <- mapM (\(n, rate) -> do
      m <- advance cal evalDate (n, Years) Unadjusted False
      q <- simpleQuote rate
      zeroCouponInflationSwapHelper q (2, Months) (period evalDate m) cal Unadjusted dc zii0 interp LastRelevantDate Nothing)
    [(2, 0.03), (10, 0.025) :: (Int, Double)]
  baseDate' <- advance cal evalDate (-2, Months) Unadjusted False
  curve <- piecewiseZeroInflationCurve evalDate baseDate' Monthly dc (fromList helpers) Nothing Linear
  zeroRate curve (addGregorianMonthsClip 12 evalDate) False

-- The same for a year-on-year curve from 2Y and 5Y swaps discounted on a flat nominal curve,
-- returning its year-on-year rate a year out.
yearOnYearCurveRate :: Day -> (Day -> Day -> InflationSwapPeriod) -> IO Double
yearOnYearCurveRate evalDate period = do
  gbp <- currency GBP
  r <- customRegion "InflationSwapHelper Test" "ISHT"
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  yii0 <- customYoyInflationIndex "ISHT YoY" r False Monthly (1, Months) gbp Nothing
  fixingDates <- mapM (\n -> advance cal evalDate (n, Months) Unadjusted False) [-96 .. 12 :: Int]
  forM_ (zip [1 :: Double ..] fixingDates) $ \(i, d) -> addFixing yii0 d (0.03 + i * 0.0001) False
  nominalQ <- simpleQuote 0.02
  nominalCurve <- flatForward (ReferenceDate evalDate) nominalQ dc IR.Continuous Annual
  helpers <- mapM (\(n, rate) -> do
      m <- advance cal evalDate (n, Years) Unadjusted False
      q <- simpleQuote rate
      yearOnYearInflationSwapHelper q (3, Months) (period evalDate m) cal Unadjusted dc yii0 CPIFlat nominalCurve LastRelevantDate Nothing)
    [(2, 0.03), (5, 0.028) :: (Int, Double)]
  baseDate' <- advance cal evalDate (-2, Months) Unadjusted False
  curve <- piecewiseYoyInflationCurve evalDate baseDate' 0.03 Monthly dc (fromList helpers) Nothing Linear
  yoyRate curve (addGregorianMonthsClip 12 evalDate) False

spec :: Spec
spec = do
 describe "zero-coupon inflation swap helpers" $ do
  -- Mid-month, so a linearly interpolated CPI differs from the month's flat fixing.
  let evalDate = fromGregorian 2024 1 15

  it "InflationSwapBetweenDates from the evaluation date matches InflationSwapToMaturity" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just evalDate)
    -- Flat observation: the dated form takes its pillar's interpolation weight from the start date
    -- rather than the maturity, which only matters when the observation is interpolated.
    toMaturity <- zeroCouponCurveRate evalDate (const InflationSwapToMaturity) CPIFlat
    betweenDates <- zeroCouponCurveRate evalDate InflationSwapBetweenDates CPIFlat
    betweenDates `shouldSatisfy` closePrec toMaturity 1.0e-12

  it "a year-on-year InflationSwapBetweenDates from the evaluation date matches InflationSwapToMaturity" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just evalDate)
    toMaturity <- yearOnYearCurveRate evalDate (const InflationSwapToMaturity)
    betweenDates <- yearOnYearCurveRate evalDate InflationSwapBetweenDates
    betweenDates `shouldSatisfy` closePrec toMaturity 1.0e-12

  -- The shim once mapped the interpolation with `== 0 ? Flat : Linear`, but CPIFlat is 1, so every
  -- helper interpolated linearly and these two curves were the same.
  it "honours flat against linear observation interpolation" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just evalDate)
    flat <- zeroCouponCurveRate evalDate (const InflationSwapToMaturity) CPIFlat
    linear <- zeroCouponCurveRate evalDate (const InflationSwapToMaturity) CPILinear
    abs (flat - linear) `shouldSatisfy` (> 1.0e-6)

 describe "zero inflation term structures" $ do
  it "interpolatedZeroInflationCurve reproduces its node rates" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just baseDate)
    dc <- dayCounter Actual365FixedStandard
    let nodes = [(baseDate, 0.010), (monthly 12, 0.015), (monthly 36, 0.020), (monthly 120, 0.025)]
    forM_ [Linear, Cubic Kruger] $ \i -> do
      curve <- interpolatedZeroInflationCurve baseDate (fromList nodes) Monthly dc Nothing i
      forM_ (drop 1 nodes) $ \(d, r) -> zeroRate curve d False >>= (`shouldSatisfy` closePrec r 1.0e-10)

  it "applies multiplicative price seasonality normalized to the curve's base date" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just baseDate)
    dc <- dayCounter Actual365FixedStandard
    let flatRate = 0.02
        nodes = [(baseDate, flatRate), (monthly 120, flatRate)]
        factors = [1.0, 1.01, 1.02, 1.015, 1.005, 0.995, 0.99, 0.985, 0.99, 1.0, 1.005, 1.01] :: [Double]
        curveWith s = interpolatedZeroInflationCurve baseDate (fromList nodes) Monthly dc s Linear
    plain <- curveWith Nothing
    unit <- curveWith (Just (MultiplicativePriceSeasonality baseDate Monthly (replicate 12 1.0)))
    seasonal <- curveWith (Just (MultiplicativePriceSeasonality baseDate Monthly factors))
    forM_ [1 .. 11 :: Int] $ \k -> do
      let d = monthly (fromIntegral k)
          t = fromIntegral (diffDays d baseDate) / 365
          -- factors !! 0 is 1, so the base-date normalization is the factor itself
          expected = (1 + flatRate) * (factors !! k) ** (1 / t) - 1
      r <- zeroRate plain d False
      r `shouldSatisfy` closePrec flatRate 1.0e-12
      zeroRate unit d False >>= (`shouldSatisfy` closePrec r 1.0e-12)
      zeroRate seasonal d False >>= (`shouldSatisfy` closePrec expected 1.0e-10)

    kerkhof <- curveWith (Just (KerkhofSeasonality baseDate factors))
    rk <- zeroRate kerkhof (monthly 5) False
    abs (rk - flatRate) `shouldSatisfy` (> 1.0e-6)

  it "rejects multi-year seasonality inconsistent at whole years from the base date" $ Context.keepingSettingsGc $ do
    Context.setEvaluationDate (Just baseDate)
    dc <- dayCounter Actual365FixedStandard
    let nodes = [(baseDate, 0.02), (monthly 120, 0.02)]
        factors = replicate 12 1.0 ++ replicate 12 1.1
    interpolatedZeroInflationCurve baseDate (fromList nodes) Monthly dc
      (Just (MultiplicativePriceSeasonality baseDate Monthly factors)) Linear `shouldThrow` anyException
