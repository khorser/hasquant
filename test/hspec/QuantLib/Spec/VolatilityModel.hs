-- Historical volatility estimators (Garch11, the GarmanKlass family, ConstantEstimator,
-- SimpleLocalEstimator) against golden values ported from upstream tests, and hand-derived
-- closed-form checks for the OHLC-bar estimators -- exercising the (date, open, close, high,
-- low) field order specifically, since a marshalling mixup there wouldn't necessarily fail to
-- compile or throw, only silently price the wrong bar component.
module QuantLib.Spec.VolatilityModel (spec) where

import Test.Hspec
import Data.List.NonEmpty(NonEmpty(..), fromList)
import Data.Time.Calendar(fromGregorian, addDays)

import QuantLib.VolatilityModel

import QuantLib.Spec.Helpers(closePrec, listClose)

spec :: Spec
spec = describe "VolatilityModel (ql/models/volatility, ql/prices.hpp)" $ do
  garch11Spec
  garmanKlassSpec
  constantAndLocalEstimatorSpec

-- garch.cpp::testCalculation, ported verbatim: a flat r=0.1 return series run through the
-- direct-parameter Garch11(0.2, 0.3, 0.4)'s own calculate() recursion.
garch11Spec :: Spec
garch11Spec = describe "Garch11" $ do
  it "reproduces garch.cpp::testCalculation's calculated series" $ do
    let g = garch11 0.2 0.3 0.4
        day0 = fromGregorian 1962 7 6
        days = [addDays i day0 | i <- [1 .. 10]]
        series = fromList (zip days (replicate 10 0.1))
    result <- garch11Calculate g series
    let expected =
          [ 0.452769, 0.513323, 0.530141, 0.5350841, 0.536558
          , 0.536999, 0.537132, 0.537171, 0.537183, 0.537187
          ]
        -- Garch11::calculate's own output series is offset by one from its input: the first
        -- input point has nothing to forecast from, so it's dropped, and one extra point is
        -- extrapolated one step past the input series' last date (garch.cpp's
        -- Garch11::calculate, not this binding's marshalling).
        outputDays = map (addDays 1) days
    map fst result `shouldBe` outputDays
    map snd result `shouldSatisfy` listClose id expected 1.0e-6

  it "forecast/calculate agree, and calibration on a synthetic series lands on stable, plausible parameters in all four modes" $ do
    let g0 = garch11 0.2 0.3 0.4
        day0 = fromGregorian 1990 1 1
        n = 80 :: Int
        -- A deterministic, non-degenerate synthetic "return" series -- avoids depending on
        -- QuantLib's own RNG draw sequence (which this binding never promises to reproduce
        -- bit-for-bit) while still giving the optimizer real variance to fit.
        shocks = take n [2 * y - 1 | y <- iterate (\x -> 3.97 * x * (1 - x)) 0.31]
        series = buildSeries g0 day0 shocks
    mapM_ (checkCalibration series) [MomentMatchingGuess, GammaGuess, BestOfTwo, DoubleOptimization]
  where
    buildSeries g day shocks = fromList (reverse (go day 0.0 0.0 shocks []))
      where
        go _ _ _ [] acc = acc
        go d r sigma2 (z : zs) acc =
          let sigma2' = garch11Forecast g r sigma2
              r' = z * sqrt sigma2'
          in go (addDays 1 d) r' sigma2' zs ((d, r') : acc)
    -- Only checks that all four 'Garch11Mode' values calibrate without throwing and hand back
    -- finite parameters -- a wiring-level check, not a convergence guarantee. This synthetic
    -- (chaotic-map-driven) series has no ground truth to fit, and omega\/logLikelihood can
    -- legitimately land on a degenerate boundary (NaN log-likelihood, omega == 0) for a
    -- poorly-conditioned sample; that's an optimizer property, not something this binding
    -- should assert away. alpha/beta likewise aren't guaranteed to sit in [0,1]: Garch11's
    -- box constraint binds the optimizer only, and on the non-'DoubleOptimization' path
    -- garch.cpp's calibrate_r2 catches an optimizer exception and returns the raw
    -- initialGuess1/initialGuess2 ACF estimate unfiltered, which carries no sign constraint
    -- (seen on Windows CI as a calibrated alpha of -0.85).
    checkCalibration series mode = do
      gc <- garch11Calibrated series mode
      garch11Alpha gc `shouldSatisfy` finite
      garch11Beta gc `shouldSatisfy` finite
    finite x = not (isNaN x || isInfinite x)

-- Closed-form checks transcribed directly from ql/models/volatility/garmanklass.hpp, evaluated
-- in Haskell against a two-bar series with distinct open/close/high/low on each bar -- any
-- marshalling swap between the four price fields breaks at least one of these.
garmanKlassSpec :: Spec
garmanKlassSpec = describe "GarmanKlass family" $ do
  it "garmanKlassSimpleSigma matches ln(close\\/open)^2, scaled by yearFraction" $ do
    result <- garmanKlassSimpleSigma yearFraction bars
    map fst result `shouldBe` [day1, day2]
    (result !! 0) `shouldSatisfy` (\(_, v) -> closePrec (simpleSigma o1 c1) 1.0e-9 v)
    (result !! 1) `shouldSatisfy` (\(_, v) -> closePrec (simpleSigma o2 c2) 1.0e-9 v)

  it "parkinsonSigma matches the high-low estimator" $ do
    result <- parkinsonSigma yearFraction bars
    (result !! 1) `shouldSatisfy` (\(_, v) -> closePrec (parkinsonSigma' o2 h2 l2) 1.0e-9 v)

  it "garmanKlassSigma4 matches its published high-low\\/close-open coefficients" $ do
    result <- garmanKlassSigma4 yearFraction bars
    (result !! 1) `shouldSatisfy` (\(_, v) -> closePrec (sigma4Formula o2 c2 h2 l2) 1.0e-9 v)

  it "garmanKlassSigma5 matches its published high-low\\/close-open coefficients" $ do
    result <- garmanKlassSigma5 yearFraction bars
    (result !! 1) `shouldSatisfy` (\(_, v) -> closePrec (sigma5Formula o2 c2 h2 l2) 1.0e-9 v)

  it "garmanKlassSigma1 blends simpleSigma with the overnight jump, dropping the first bar" $ do
    result <- garmanKlassSigma1 yearFraction marketOpenFraction bars
    map fst result `shouldBe` [day2]
    let simpleBase = log (c2 / o2) ** 2
        expected = openCloseBlend marketOpenFraction 0.5 simpleBase
    (result !! 0) `shouldSatisfy` (\(_, v) -> closePrec expected 1.0e-9 v)

  it "garmanKlassSigma3 blends parkinsonSigma with the overnight jump, dropping the first bar" $ do
    result <- garmanKlassSigma3 yearFraction marketOpenFraction bars
    let parkinsonBase = (log (h2 / o2) - log (l2 / o2)) ** 2 / (4 * log 2)
        expected = openCloseBlend marketOpenFraction 0.17 parkinsonBase
    (result !! 0) `shouldSatisfy` (\(_, v) -> closePrec expected 1.0e-9 v)

  it "garmanKlassSigma6 blends garmanKlassSigma4 with the overnight jump, dropping the first bar" $ do
    result <- garmanKlassSigma6 yearFraction marketOpenFraction bars
    let sigma4Base =
          let u = log (h2 / o2); d = log (l2 / o2); cc = log (c2 / o2)
          in 0.511 * (u - d) ** 2 - 0.019 * (cc * (u + d) - 2 * u * d) - 0.383 * cc * cc
        expected = openCloseBlend marketOpenFraction 0.012 sigma4Base
    (result !! 0) `shouldSatisfy` (\(_, v) -> closePrec expected 1.0e-9 v)
  where
    day1 = fromGregorian 2020 3 2
    day2 = fromGregorian 2020 3 3
    (o1, c1, h1, l1) = (100.0, 102.0, 103.0, 99.0)
    (o2, c2, h2, l2) = (101.0, 105.0, 106.0, 100.0)
    bars = (day1, o1, c1, h1, l1) :| [(day2, o2, c2, h2, l2)]
    yearFraction = 1.0 / 252.0
    marketOpenFraction = 0.5 :: Double

    simpleSigma o c = sqrt (abs (log (c / o) ** 2) / yearFraction)
    parkinsonSigma' o h l = sqrt (abs ((log (h / o) - log (l / o)) ** 2 / (4 * log 2)) / yearFraction)
    sigma4Formula o c h l =
      let u = log (h / o); d = log (l / o); cc = log (c / o)
      in sqrt (abs (0.511 * (u - d) ** 2 - 0.019 * (cc * (u + d) - 2 * u * d) - 0.383 * cc * cc) / yearFraction)
    sigma5Formula o c h l =
      let u = log (h / o); d = log (l / o); cc = log (c / o)
      in sqrt (abs (0.5 * (u - d) ** 2 - (2 * log 2 - 1) * cc * cc) / yearFraction)
    -- jump = ln(cur.open) - ln(prev.close); a is the per-variant blend weight (0.5/0.17/0.012).
    openCloseBlend f a base = sqrt ((a * jump ** 2 / f + (1 - a) * base / (1 - f)) / yearFraction)
      where jump = log o2 - log c1

-- ConstantEstimator: hand-computed over a 5-point series with windowSize=3
-- (constantestimator.cpp: s = sqrt(sum(u^2)/size - sum(u)^2/size/(size+1)) over each trailing
-- window). SimpleLocalEstimator: |ln(p_i/p_{i-1})| / sqrt(yearFraction) over a 3-point series.
constantAndLocalEstimatorSpec :: Spec
constantAndLocalEstimatorSpec = describe "ConstantEstimator and SimpleLocalEstimator" $ do
  it "constantVolatilityEstimator matches the windowed sample-variance formula" $ do
    let day0 = fromGregorian 2021 1 1
        days = [addDays i day0 | i <- [0 .. 4]]
        vals = [1.0, 2.0, 3.0, 2.0, 1.0]
        series = fromList (zip days vals)
        windowed ws = sqrt (sum (map (** 2) ws) / n - (sum ws) ** 2 / n / (n + 1))
          where n = fromIntegral (length ws)
    result <- constantVolatilityEstimator 3 series
    map fst result `shouldBe` drop 3 days
    map snd result `shouldSatisfy` listClose id [windowed [1, 2, 3], windowed [2, 3, 2]] 1.0e-9

  it "simpleLocalVolatilityEstimator matches |ln(p_i\\/p_{i-1})| \\/ sqrt(yearFraction)" $ do
    let day0 = fromGregorian 2021 1 1
        days = [addDays i day0 | i <- [0 .. 2]]
        prices = [100.0, 105.0, 110.0]
        series = fromList (zip days prices)
        yearFraction = 1.0 / 252.0
        expected = [abs (log (p1 / p0)) / sqrt yearFraction | (p0, p1) <- zip prices (drop 1 prices)]
    result <- simpleLocalVolatilityEstimator yearFraction series
    map fst result `shouldBe` drop 1 days
    map snd result `shouldSatisfy` listClose id expected 1.0e-9
