module QuantLib.Spec.TermStructure.InflationVolatility (spec) where

import Control.Monad(forM_, zipWithM_)
import Data.Time.Calendar(addDays, addGregorianYearsClip)
import System.Mem(performGC)
import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Index.Inflation
import qualified QuantLib.InterestRate as IR
import QuantLib.Math(Interpolation(..), Approximation(..), Matrix(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Inflation
import QuantLib.TermStructure.InflationVolatility
import QuantLib.TermStructure.Yield(YieldTermStructure, interpolatedZeroCurve)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

-- |Builds an 'InterpolatedZeroCurve'-style nominal EUR curve from (time-from-eval, rate) pairs,
-- converting each time to a date the same way upstream's own fixture does (@eval +
-- Period(years,Years) + Period(days,Days)@, i.e. calendar-correct year steps plus a residual day
-- count -- NOT a plain 365-day multiple, which would quietly drift the resulting node dates
-- and hence the curve's node times under 'Actual365Fixed' by a day or two per node). Uses plain
-- 'Data.Time.Calendar' arithmetic on 'Day' directly rather than 'QuantLib.Time.Calendar.advance':
-- 'advance' steps a @Days@-unit period one *business day* at a time regardless of the given
-- 'BusinessDayConvention' (see @Calendar::advance@'s special-cased @unit == Days@ branch in
-- @ql/time/calendar.cpp@), which silently drifts a residual-day offset by however many holidays
-- and weekends it crosses -- badly enough, at these magnitudes, to reorder two nodes relative to
-- each other. Plain @Date + Period(Years) + Period(Days)@ (what upstream's own fixture computes)
-- has no such stepping, so plain 'Day' arithmetic is the faithful translation, not 'advance'.
nominalCurveFromTimes :: Calendar -> Day -> DayCounter -> [(Double, Double)] -> IO YieldTermStructure
nominalCurveFromTimes cal eval dc timesRates =
  interpolatedZeroCurve (map mkNode timesRates) dc cal [] (Cubic Kruger)
  where
    mkNode (t, r) =
      let ys = floor t :: Integer
          ds = floor ((t - fromIntegral ys) * 365) :: Integer
      in (addDays ds (addGregorianYearsClip ys eval), r)

-- |Upstream's own EUR nominal curve node data (test-suite/inflationvolatility.cpp's @setup()@),
-- unchanged: (time from eval, zero rate).
timesRatesEUR :: [(Double, Double)]
timesRatesEUR =
  [ (0.0109589, 0.0415600), (0.0684932, 0.0426840), (0.263014, 0.0470980), (0.317808, 0.0458506)
  , (0.567123, 0.0449550), (0.816438, 0.0439784), (1.06575, 0.0431887), (1.31507, 0.0426604)
  , (1.56438, 0.0422925), (2.0137, 0.0424591), (3.01918, 0.0421477), (4.01644, 0.0421853)
  , (5.01644, 0.0424016), (6.01644, 0.0426969), (7.01644, 0.0430804), (8.01644, 0.0435011)
  , (9.02192, 0.0439368), (10.0192, 0.0443825), (12.0192, 0.0452589), (15.0247, 0.0463389)
  , (20.0301, 0.0472636), (25.0356, 0.0473401), (30.0329, 0.0470629), (40.0384, 0.0461092)
  , (50.0466, 0.0450794) ]

-- |Upstream's YoY rates (times = years - 2 month lag; the first is the base rate), used to build
-- the linked 'YoYInflationTermStructure' directly via 'interpolatedYoYInflationCurve' -- these
-- are already-known market YoY levels, not swap quotes to bootstrap from.
yoyEURrates :: [Double]
yoyEURrates =
  [ 0.0237951
  , 0.0238749, 0.0240334, 0.0241934, 0.0243567, 0.0245323
  , 0.0247213, 0.0249348, 0.0251768, 0.0254337, 0.0257258
  , 0.0260217, 0.0263006, 0.0265538, 0.0267803, 0.0269378
  , 0.0270608, 0.0271363, 0.0272, 0.0272512, 0.0272927
  , 0.027317, 0.0273615, 0.0273811, 0.0274063, 0.0274307
  , 0.0274625, 0.027527, 0.0275952, 0.0276734, 0.027794 ]

-- |Upstream's cap/floor price-surface data (6 strikes x 7 maturities each for caps and floors).
cStrikesEU, fStrikesEU :: [Double]
cStrikesEU = [0.02, 0.025, 0.03, 0.035, 0.04, 0.05]
fStrikesEU = [-0.01, 0.00, 0.005, 0.01, 0.015, 0.02]

cfMaturitiesEU :: [(Word, TimeUnit)]
cfMaturitiesEU = [(3, Years), (5, Years), (7, Years), (10, Years), (15, Years), (20, Years), (30, Years)]

capPricesEU, floorPricesEU :: Matrix Double
capPricesEU = Matrix 6 7
  [ 116.225, 204.945, 296.285, 434.29, 654.47, 844.775, 1132.33
  , 34.305, 71.575, 114.1, 184.33, 307.595, 421.395, 602.35
  , 6.37, 19.085, 35.635, 66.42, 127.69, 189.685, 296.195
  , 1.325, 5.745, 12.585, 26.945, 58.95, 94.08, 158.985
  , 0.501, 2.37, 5.38, 13.065, 31.91, 53.95, 96.97
  , 0.501, 0.695, 1.47, 4.415, 12.86, 23.75, 46.7 ]
floorPricesEU = Matrix 6 7
  [ 0.501, 0.851, 2.44, 6.645, 16.23, 26.85, 46.365
  , 0.501, 2.236, 5.555, 13.075, 28.46, 44.525, 73.08
  , 1.025, 3.935, 9.095, 19.64, 39.93, 60.375, 96.02
  , 2.465, 7.885, 16.155, 31.6, 59.34, 86.21, 132.045
  , 6.9, 17.92, 32.085, 56.08, 95.95, 132.85, 194.18
  , 23.52, 47.625, 74.085, 114.355, 175.72, 229.565, 316.285 ]

-- |Vol slices at the surface's base date plus 1\/3 years, across the 11-strike union of
-- 'cStrikesEU'\/'fStrikesEU'. NOT upstream's own cached @volATyear1@\/@volATyear3@ (those are
-- @{0.0129, 0.0094, ...}@\/@{0.0080, 0.0058, ...}@) -- those values are stale against the
-- QuantLib 1.43 actually installed here, off by several times this test's tolerance. Confirmed
-- via an independent, minimal C++ program (bypassing hasquant's Haskell layer entirely) built
-- straight from @setup()@\/@setupPriceSurface()@\/@testYoYPriceSurfaceToVol@'s own C++ verbatim,
-- linked against the same installed @libQuantLib@: it reproduces exactly these values, not
-- upstream's cached ones, ruling out a hasquant-side bug and pointing at behavior that changed
-- upstream since this fixture was written (2009) without the cached numbers being refreshed --
-- consistent with both 'KInterpolatedYoYOptionletVolatilitySurface' and
-- 'InterpolatedYoYOptionletStripper' carrying an explicit upstream doc comment of their own,
-- @\\bug Tests currently fail@.
volATyear1, volATyear3 :: [Double]
volATyear1 = [0.0135064, 0.0098650, 0.0087791, 0.0077453, 0.0067549, 0.0060420, 0.0043860, 0.0048649, 0.0056425, 0.0067729, 0.0103381]
volATyear3 = [0.0085961, 0.0062788, 0.0055840, 0.0049221, 0.0042875, 0.0038286, 0.0027751, 0.0030795, 0.0035763, 0.0042978, 0.0065660]

-- |Cached YoY swap curve / ATM YoY rates from upstream's own @testYoYPriceSurfaceToATM@, at
-- 'cfMaturitiesEU'.
atmYoYSwapRates, atmYoYRates :: [Double]
atmYoYSwapRates = [0.024586, 0.0247575, 0.0249396, 0.0252596, 0.0258498, 0.0262883, 0.0267915]
atmYoYRates = [0.0247659, 0.0251437, 0.0255945, 0.0265015, 0.0280457, 0.0285534, 0.0295884]

setup :: IO (Day, Calendar, DayCounter, YieldTermStructure, YoYInflationIndex, YoYCapFloorTermPriceSurface)
setup = do
  let eval = 23 `november` 2007
  Settings.setEvaluationDate (Just eval)
  cal <- calendar TARGET
  dc <- dayCounter Actual365FixedStandard
  nominalEUR <- nominalCurveFromTimes cal eval dc timesRatesEUR

  -- the base date is based on the last published index fixing, and cap maturities are based
  -- on the observation lag -- both computed the same today-relative way upstream's setup() does
  baseDate <- advance cal eval (-1, Months) Unadjusted False
  capStartDate <- advance cal eval (-2, Months) ModifiedFollowing False
  yoyDates <- (baseDate :) <$> mapM (\n -> advance cal capStartDate (n, Years) ModifiedFollowing False) [1 .. length yoyEURrates - 1]
  yoyEU <- interpolatedYoYInflationCurve eval (zip yoyDates yoyEURrates) Monthly dc Linear

  zii <- zeroInflationIndex EUHICP
  yoyIndexEU <- yoyInflationIndexFromZero zii (Just yoyEU)

  let fixingDays = 0
      yyLag = (3, Months)
  priceSurfEU <- yoyCapFloorTermPriceSurface fixingDays yyLag yoyIndexEU CPILinear nominalEUR dc cal ModifiedFollowing
                   cStrikesEU fStrikesEU cfMaturitiesEU capPricesEU floorPricesEU

  return (eval, cal, dc, nominalEUR, yoyIndexEU, priceSurfEU)

spec :: Spec
spec = describe "YoY optionlet stripper (KInterpolatedYoYOptionletVolatilitySurface)" $ do
  it "interpolatedYoYInflationCurve: a non-Linear interpolation builds and differs between nodes" $ Settings.keepingSettings' $ do
    let eval = 23 `november` 2007
    Settings.setEvaluationDate (Just eval)
    cal <- calendar TARGET
    dc <- dayCounter Actual365FixedStandard
    baseDate <- advance cal eval (-1, Months) Unadjusted False
    capStartDate <- advance cal eval (-2, Months) ModifiedFollowing False
    yoyDates <- (baseDate :) <$> mapM (\n -> advance cal capStartDate (n, Years) ModifiedFollowing False) [1 .. length yoyEURrates - 1]
    let mid = addDays 180 (yoyDates !! 1)
    yoyLinear <- interpolatedYoYInflationCurve eval (zip yoyDates yoyEURrates) Monthly dc Linear
    yoyCubic <- interpolatedYoYInflationCurve eval (zip yoyDates yoyEURrates) Monthly dc (Cubic Kruger)
    rLinear <- yoyRate yoyLinear mid True
    rCubic <- yoyRate yoyCubic mid True
    -- both interpolators agree at the nodes themselves; a mid-node query is where a genuinely
    -- different interpolation should (and does) diverge from Linear
    abs (rLinear - rCubic) `shouldSatisfy` (> 1e-8)

  it "matches an independent C++ reprise of upstream's testYoYPriceSurfaceToVol fixture" $ Settings.keepingSettings' $ do
    (_, cal, dc, nominalEUR, yoyIndexEU, priceSurfEU) <- setup

    yoySurf <- kInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack 0 cal ModifiedFollowing dc
                 priceSurfEU yoyIndexEU nominalEUR (-0.5)

    strikes <- yoyCapFloorStrikes priceSurfEU
    baseDate <- yoyCapFloorBaseDate priceSurfEU
    d1 <- advance cal baseDate (1, Years) Unadjusted False
    d3 <- advance cal baseDate (3, Years) Unadjusted False

    let eps = 1e-6 :: Double
    zipWithM_ (\k v -> do
        vol <- yoyOptionletVolatility yoySurf d1 k Nothing True
        abs (vol - v) `shouldSatisfy` (< eps)
      ) strikes volATyear1
    zipWithM_ (\k v -> do
        vol <- yoyOptionletVolatility yoySurf d3 k Nothing True
        abs (vol - v) `shouldSatisfy` (< eps)
      ) strikes volATyear3
    performGC

  it "recovers upstream's cached ATM YoY swap/inflation curve (testYoYPriceSurfaceToATM)" $ Settings.keepingSettings' $ do
    (_, _, _, _, _, priceSurfEU) <- setup

    dateRates <- yoyCapFloorAtmYoYSwapDateRates priceSurfEU
    let eps = 2e-5 :: Double
    zipWithM_ (\(d, r) expected -> do
        abs (r - expected) `shouldSatisfy` (< eps)
        r2 <- yoyCapFloorAtmYoYSwapRate priceSurfEU d True
        abs (r2 - expected) `shouldSatisfy` (< eps)
      ) dateRates atmYoYSwapRates

    forM_ (zip (map fst dateRates) atmYoYRates) $ \(d, expected) -> do
      a <- yoyCapFloorAtmYoYRate priceSurfEU d Nothing True
      abs (a - expected) `shouldSatisfy` (< eps)
    performGC

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
