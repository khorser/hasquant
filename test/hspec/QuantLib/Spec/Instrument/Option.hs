-- | Golden-value tests for the exotic single-/multi-asset options bound
-- alongside their analytic engines: 'simpleChooserOption', 'softBarrierOption',
-- 'twoAssetCorrelationOption' reproduce cached NPVs from QuantLib's own
-- test-suite (chooseroption.cpp, softbarrieroption.cpp,
-- twoassetcorrelationoption.cpp). 'writerExtensibleOption' has no upstream
-- test-suite fixture, so it's checked instead against an independent
-- Monte Carlo simulation of its own payoff definition (see CLAUDE.md's
-- TARF-style self-consistency precedent) -- exact lognormal (GBM) path
-- simulation under the same flat-rate/flat-vol process, entirely
-- self-contained (no 'random' package dependency: a fixed-seed splitmix-style
-- LCG plus Box-Muller, both defined below).
module QuantLib.Spec.Instrument.Option (spec) where

import Prelude hiding(iterate, tail)
import Test.Hspec
import Data.Time.Calendar(addDays)
import Data.Bits(shiftR, xor)
import Data.Word(Word64)
import Data.List.NonEmpty(iterate, tail)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.TermStructure.Volatility(blackConstantVol)
import QuantLib.Process hiding(drift)
import QuantLib.Math(Matrix(..), PolynomialType(..), RngTrait(..), StatisticsTrait(..), Interpolation2D(..))
import QuantLib.Instrument(npv, setPricingEngine, errorEstimate, BarrierType(..), AverageType(..))
import QuantLib.Instrument.Option hiding(theta)
import QuantLib.Instrument.Swap(varianceOption, varianceSwap, variance)
import QuantLib.TermStructure.Volatility(blackVarianceSurface, BlackVarianceSurfaceExtrapolation(..))
import QuantLib.PricingEngine
import QuantLib.Spec.Helpers(closePrec)

dateOffset :: Day -> Double -> Day
dateOffset d t = addDays (round (t * 360 :: Double)) d

-- |10 future fixings, evenly spaced every round(360\/10)=36 days out to a 360-day maturity --
-- matches asianoptions.cpp's own @dt = lround(360.0 \/ futureFixings)@ construction, shared by
-- the discrete-geometric-average-price\/strike Asian cases below.
discreteAsianFixingDates :: Day -> [Day]
discreteAsianFixingDates evalDate = [addDays (36 * i) evalDate | i <- [1 .. 10]]

-- |A flat Black-Scholes-Merton process: spot/dividend-yield/risk-free-rate/vol all constant.
flatProcess :: Day -> Double -> Double -> Double -> Double -> IO GeneralizedBlackScholesProcess
flatProcess evalDate spot q r vol = do
  dc <- dayCounter (Actual360 False)
  spotQ <- simpleQuote spot
  qTS <- simpleQuote q >>= \qQ -> flatForward evalDate qQ dc Continuous Annual
  rTS <- simpleQuote r >>= \rQ -> flatForward evalDate rQ dc Continuous Annual
  volQ <- simpleQuote vol
  cal <- calendar Null
  volTS <- blackConstantVol evalDate cal volQ dc
  blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False

europeanIn :: Word -> Day -> Exercise
europeanIn days evalDate = European (EuropeanExercise (addDays (fromIntegral days) evalDate))

-- |Fixed-seed splitmix-style LCG producing i.i.d. standard normal draws via
-- Box-Muller, entirely self-contained so the writer-extensible cross-check
-- below doesn't need the @random@ package as a new dependency.
lcgStream :: Word64 -> [Word64]
lcgStream = tail . iterate step
  where step x = let x1 = (x `xor` (x `shiftR` 12)) * 2545536902123478967
                     x2 = (x1 `xor` (x1 `shiftR` 25)) * 2545536902123478967
                 in x2 `xor` (x2 `shiftR` 33)

normals :: Word64 -> [Double]
normals seed = go (map toUnit (lcgStream seed))
  where
    m = (2 :: Double) ^ (53 :: Int)
    toUnit w = fromIntegral (w `mod` round m :: Word64) / m
    go (u1:u2:rest) =
      let r = sqrt (-2 * log (max u1 1e-12))
          theta = 2 * pi * u2
      in r * cos theta : r * sin theta : go rest
    go _ = []

-- |Monte Carlo NPV (antithetic variates) for a writer-extensible option:
-- simulate GBM to @t1@; if @payoff1@ is in the money there, the holder is
-- paid @payoff1 S1@ at @t1@, otherwise the same path continues to @t2@ and
-- the holder is paid @payoff2 S2@ at @t2@ -- exactly
-- writerextensibleoption.hpp's own definition, simulated independently of
-- the analytic engine under test.
writerExtensibleMcNpv :: Int -> Double -> Double -> Double -> Double
                       -> Double -> Double -> (Double -> Double) -> (Double -> Double)
                       -> Double
writerExtensibleMcNpv halfN s0 q r vol t1 t2 payoff1 payoff2 =
  (sum (map pathValue zs) + sum (map (pathValue . negatePair) zs)) / fromIntegral (2 * halfN)
  where
    zs = take halfN (pairs (normals 0xC0FFEE))
    pairs (a:b:rest) = (a, b) : pairs rest
    pairs _ = []
    negatePair (a, b) = (-a, -b)
    drift dt = (r - q - 0.5 * vol * vol) * dt
    diffuse s dt z = s * exp (drift dt + vol * sqrt dt * z)
    pathValue (z1, z2) =
      let s1 = diffuse s0 t1 z1
          s2 = diffuse s1 (t2 - t1) z2
          v1 = payoff1 s1
      in if v1 > 0 then exp (-r * t1) * v1 else exp (-r * t2) * payoff2 s2

spec :: Spec
spec = do
  describe "SimpleChooserOption" $
    -- cached reference from QuantLib test-suite/chooseroption.cpp::testAnalyticSimpleChooserEngine
    -- (Haug, "Complete Guide to Option Pricing Formulas", pp.39-40).
    it "reproduces Haug's simple chooser option value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 50.0 0.0 0.08 0.25
        eng <- analyticSimpleChooserEngine process
        opt <- simpleChooserOption (addDays 90 evalDate) 50.0 (europeanIn 180 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 6.1071 3e-5

  describe "SoftBarrierOption" $ do
    -- cached reference from QuantLib test-suite/softbarrieroption.cpp::testSoftBarrierHaug
    -- (Haug 2nd ed., p.166; first DownOut/Call row). Pinned to the upstream test's own
    -- literal evaluation date (8 August 2025), not a dynamic 'today': AnalyticSoftBarrierEngine
    -- (a 2025 upstream addition) turns out to price differently for different evaluation dates
    -- even at identical time-to-maturity T -- confirmed independently against a standalone C++
    -- program linked against the same installed QuantLib 1.43 (evalDate 2020-01-01/2025-08-08/
    -- 2026-08-22 with T pinned to exactly 0.5y each gave 3.79624/3.80752/3.78492 respectively).
    -- This looks like a genuine date-arithmetic quirk in the new upstream engine, not a
    -- hasquant marshalling bug; matching the test-suite's own fixture date is the correct fix.
    it "reproduces Haug's soft barrier option value" $
      Settings.keepingSettings' $ do
        let evalDate = 8 `august` 2025
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.05 0.1 0.1
        eng <- analyticSoftBarrierEngine process
        opt <- softBarrierOption DownOut 95.0 95.0 (PlainVanilla (PlainVanillaPayoff Call 100.0)) (europeanIn 180 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 3.8075 1e-4

    it "round-trips its own implied volatility" $
      Settings.keepingSettings' $ do
        let evalDate = 8 `august` 2025
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.05 0.1 0.1
        eng <- analyticSoftBarrierEngine process
        opt <- softBarrierOption DownOut 95.0 95.0 (PlainVanilla (PlainVanillaPayoff Call 100.0)) (europeanIn 180 evalDate)
        setPricingEngine opt eng
        price <- npv opt
        iv <- softBarrierOptionImpliedVolatility opt price process 1.0e-6 1000 1e-6 4.0
        iv `shouldSatisfy` closePrec 0.1 1e-4

  describe "TwoAssetCorrelationOption" $
    -- cached reference from QuantLib test-suite/twoassetcorrelationoption.cpp::testAnalyticEngine
    it "reproduces the upstream two-asset correlation option value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process1 <- flatProcess evalDate 52.0 0.0 0.1 0.2
        process2 <- flatProcess evalDate 65.0 0.0 0.1 0.3
        corr <- simpleQuote 0.75
        eng <- analyticTwoAssetCorrelationEngine process1 process2 corr
        opt <- twoAssetCorrelationOption Call 50.0 70.0 (europeanIn 180 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 4.7073 1e-4

  describe "Basket options (MC engines)" $
    -- cached reference from QuantLib test-suite/basketoption.cpp::testEuroTwoValues, the
    -- {MaxBasket, Call, strike=100, s1=s2=100, q=0, r=0.05, t=1, v1=v2=0.30, rho=0.5} row
    -- (expected 21.619, checked there against StulzEngine's closed-form value). Reused here
    -- for both engines: with no dividend yield, an American call is never optimal to exercise
    -- early (true for a max-of-two-assets call by the same convexity argument as the
    -- single-asset case), so the American engine is expected to land on the same value as the
    -- European one, not a materially higher one.
    it "European and American two-asset max-basket MC engines both reproduce Haug's analytic value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process1 <- flatProcess evalDate 100.0 0.0 0.05 0.30 >>= asStochasticProcess1D
        process2 <- flatProcess evalDate 100.0 0.0 0.05 0.30 >>= asStochasticProcess1D
        procs <- stochasticProcessArray [process1, process2] (Matrix 2 2 [1.0, 0.5, 0.5, 1.0])
        let payoff = Max (plainVanillaPayoff (PlainVanillaPayoff Call 100.0))
            expected = 21.619

        -- tolerance matches upstream's own check here: relativeError(calculated, expected,
        -- value.s1) there compares against the *spot* (100), i.e. an absolute tolerance of
        -- spot*1% = 1.0, not a tolerance relative to the option value itself.
        euEngine <- mcEuropeanBasketEngine PseudoRandom Statistics procs Nothing (Just 1) False False (Just 10000) Nothing Nothing 42
        euOpt <- basketOption payoff (europeanIn 360 evalDate)
        setPricingEngine euOpt euEngine
        euNpv <- npv euOpt
        euNpv `shouldSatisfy` closePrec expected 1.0
        -- errorEstimate is Instrument's generic MC std-error accessor (populated by any
        -- McSimulation-based engine's results_.errorEstimate, not just this basket engine);
        -- checking it here is cheap coverage that it round-trips through the FFI at all.
        euErr <- errorEstimate euOpt
        euErr `shouldSatisfy` (> 0)
        euErr `shouldSatisfy` (< 1.0)

        amEngine <- mcAmericanBasketEngine PseudoRandom procs (Just 50) Nothing False True (Just 10000) Nothing Nothing 43 (Just 2500) 2 Monomial
        amOpt <- basketOption payoff (American Nothing (addDays 360 evalDate) False)
        setPricingEngine amOpt amEngine
        amNpv <- npv amOpt
        amNpv `shouldSatisfy` closePrec expected 1.5
        amErr <- errorEstimate amOpt
        amErr `shouldSatisfy` (> 0)
        amErr `shouldSatisfy` (< 1.5)

  describe "WriterExtensibleOption" $
    it "matches an independent Monte Carlo simulation of its own payoff definition" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        let s0 = 100.0; q = 0.0; r = 0.05; vol = 0.2
            t1 = 0.5; t2 = 1.0; x1 = 100.0; x2 = 110.0
        process <- flatProcess evalDate s0 q r vol
        eng <- analyticWriterExtensibleOptionEngine process
        opt <- writerExtensibleOption (PlainVanillaPayoff Call x1) (europeanIn 180 evalDate)
                                       (PlainVanillaPayoff Call x2) (europeanIn 360 evalDate)
        setPricingEngine opt eng
        analytic <- npv opt
        let mcNpv = writerExtensibleMcNpv 100000 s0 q r vol t1 t2
                      (\s -> max 0 (s - x1)) (\s -> max 0 (s - x2))
        mcNpv `shouldSatisfy` closePrec analytic (0.03 * analytic)

  describe "Geometric-average Asian options" $ do
    -- cached reference from QuantLib test-suite/asianoptions.cpp::testAnalyticContinuousGeometricAveragePrice
    -- (Haug, "Option Pricing Formulas", pp.96-97).
    it "reproduces Haug's continuous geometric average-price value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 80.0 (-0.03) 0.05 0.20
        eng <- analyticContinuousGeometricAveragePriceAsianEngine process
        opt <- continuousAveragingAsianOption Geometric (PlainVanilla (PlainVanillaPayoff Put 85.0))
                                               (europeanIn 90 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 4.6922 1e-4

    -- cached reference from QuantLib test-suite/asianoptions.cpp::testAnalyticDiscreteGeometricAveragePrice
    -- (Clewlow & Strickland, "Implementing Derivatives Model", pp.118-123): 10 future fixings,
    -- evenly spaced every round(360/10)=36 days out to a 360-day maturity.
    it "reproduces Clewlow & Strickland's discrete geometric average-price value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.03 0.06 0.20
        eng <- analyticDiscreteGeometricAveragePriceAsianEngine process
        opt <- discreteAveragingAsianOption Geometric 1.0 0 (discreteAsianFixingDates evalDate)
                                             (PlainVanilla (PlainVanillaPayoff Call 100.0))
                                             (europeanIn 360 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 5.3425606635 1e-6

    it "reproduces the discrete geometric average-strike value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.03 0.06 0.20
        eng <- analyticDiscreteGeometricAverageStrikeAsianEngine process
        opt <- discreteAveragingAsianOption Geometric 1.0 0 (discreteAsianFixingDates evalDate)
                                             (PlainVanilla (PlainVanillaPayoff Call 100.0))
                                             (europeanIn 360 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 4.97109 1e-5

    -- cached reference from QuantLib test-suite/asianoptions.cpp::testMCDiscreteGeometricAveragePrice:
    -- the MC engine is checked against the analytic one above, not an independent literal (upstream
    -- does the same -- both engines price the identical option/process pair).
    it "MC discrete geometric average-price engine matches its own analytic engine" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.03 0.06 0.20
        opt <- discreteAveragingAsianOption Geometric 1.0 0 (discreteAsianFixingDates evalDate)
                                             (PlainVanilla (PlainVanillaPayoff Call 100.0))
                                             (europeanIn 360 evalDate)
        mcEng <- mcDiscreteGeometricAPEngine LowDiscrepancy Statistics process True False (Just 8191) Nothing Nothing 42
        setPricingEngine opt mcEng
        mc <- npv opt
        mc `shouldSatisfy` closePrec 5.3425606635 4.0e-3

  describe "Arithmetic-average Asian option (MC average-strike engine)" $
    -- cached references from QuantLib test-suite/asianoptions.cpp::testMCDiscreteArithmeticAverageStrike
    -- (Levy 1997, as reproduced in Clewlow & Strickland's "Exotic Options"): a two-row subset of
    -- upstream's 27-case table (spot 90, strike 87, q 6%, r 2.5%, vol 13%, first fixing at t=0,
    -- 11/12y to maturity), at 26 and 100 equally spaced fixings.
    mapM_ (\(fixings, expected) ->
      it ("matches Levy's value at " ++ show fixings ++ " fixings") $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate 90.0 0.06 0.025 0.13
          let len = 11 / 12 :: Double
              dt = len / fromIntegral (fixings - 1 :: Int)
              fixingDates = [dateOffset evalDate (fromIntegral i * dt) | i <- [0 .. fixings - 1 :: Int]]
          eng <- mcDiscreteArithmeticASEngine LowDiscrepancy Statistics process True False (Just 1023) Nothing Nothing 3456789
          opt <- discreteAveragingAsianOption Arithmetic 0.0 0 fixingDates
                                               (PlainVanilla (PlainVanillaPayoff Call 87.0))
                                               (europeanIn (round (len * 360)) evalDate)
          setPricingEngine opt eng
          v <- npv opt
          v `shouldSatisfy` closePrec expected 2.0e-2)
      [(26 :: Int, 1.81430536630 :: Double), (100, 1.83822402464)]

  describe "Continuous lookback options" $ do
    -- cached references from QuantLib test-suite/lookbackoptions.cpp::testAnalyticContinuousFloatingLookback
    -- (Haug 1998 pp.61-62; Broadie/Glasserman/Kou 1999 pp.70-74). q=0, r constant per row.
    mapM_ (\(typ, minmax, s, q, r, t, vol, expected) ->
      it ("matches the floating-strike lookback value at s=" ++ show s ++ " t=" ++ show t) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate s q r vol
          eng <- analyticContinuousFloatingLookbackEngine process
          opt <- continuousFloatingLookbackOption minmax (Floating (typ :: OptionType))
                                                   (europeanIn (round (t * 360 :: Double)) evalDate)
          setPricingEngine opt eng
          v <- npv opt
          v `shouldSatisfy` closePrec expected 1.0e-4)
      [ (Call, 100.0, 120.0, 0.06, 0.10, 0.50, 0.30, 25.3533 :: Double)
      , (Call, 100.0, 100.0, 0.00, 0.05, 1.00, 0.30, 23.7884)
      , (Put,  100.0, 100.0, 0.00, 0.10, 0.50, 0.30, 15.3526)
      ]

    -- cached references from QuantLib test-suite/lookbackoptions.cpp::testAnalyticContinuousFixedLookback
    -- (Haug 1998 pp.63-64).
    mapM_ (\(strike, minmax, s, q, r, t, vol, expected) ->
      it ("matches the fixed-strike lookback value at strike=" ++ show strike ++ " vol=" ++ show vol) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate s q r vol
          eng <- analyticContinuousFixedLookbackEngine process
          opt <- continuousFixedLookbackOption minmax (PlainVanilla (PlainVanillaPayoff Call strike))
                                                (europeanIn (round (t * 360 :: Double)) evalDate)
          setPricingEngine opt eng
          v <- npv opt
          v `shouldSatisfy` closePrec expected 1.0e-4)
      [ (95.0 :: Double, 100.0 :: Double, 100.0 :: Double, 0.0 :: Double, 0.10 :: Double, 0.50 :: Double, 0.10 :: Double, 13.2687 :: Double)
      , (100.0, 100.0, 100.0, 0.0, 0.10, 0.50, 0.20, 14.1702)
      , (105.0, 100.0, 100.0, 0.0, 0.10, 0.50, 0.30, 15.8512)
      ]

  describe "CliquetOption" $
    -- cached reference from QuantLib test-suite/cliquetoption.cpp::testValues (Haug, p.37).
    it "reproduces Haug's cliquet option value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 60.0 0.04 0.08 0.30
        eng <- analyticCliquetEngine process
        opt <- cliquetOption (PercentageStrikePayoff Call 1.1) (EuropeanExercise (addDays 360 evalDate))
                              [addDays 90 evalDate]
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 4.4064 1e-4

  describe "VarianceOption (IntegralHestonVarianceOptionEngine)" $
    -- cached references from QuantLib test-suite/varianceoption.cpp::testIntegralHeston. The
    -- Heston process's dividendYield is 'Nothing' (an empty term-structure handle), exactly
    -- matching upstream's default-constructed Handle<YieldTermStructure> -- this engine rejects
    -- a process with a non-empty dividend handle, per hestonProcess's own haddock.
    mapM_ (\(v0, strike, ty, t, expected) ->
      it ("reproduces the cached NPV at v0=" ++ show v0 ++ " strike=" ++ show strike) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          dc <- dayCounter (Actual360 False)
          s0 <- simpleQuote 1.0
          rTS <- simpleQuote 0.0 >>= \rQ -> flatForward evalDate rQ dc Continuous Annual
          process <- hestonProcess rTS Nothing s0 v0 2.0 0.01 0.1 (-0.5) QuadraticExponentialMartingale
          eng <- integralHestonVarianceOptionEngine process
          opt <- varianceOption (Type (Striked (PlainVanilla (PlainVanillaPayoff ty strike))))
                                 1.0 evalDate (dateOffset evalDate t)
          setPricingEngine opt eng
          nv <- npv opt
          nv `shouldSatisfy` closePrec expected 1.0e-6)
      [ (2.0 :: Double, 0.05 :: Double, Call, 1.5 :: Double, 0.9104619 :: Double)
      , (1.5, 0.7, Put, 1.0, 0.0466796)
      ]

  describe "VarianceSwap (ReplicatingVarianceSwapEngine)" $
    -- cached reference from QuantLib test-suite/varianceswaps.cpp::testReplicatingVarianceSwap
    -- (Derman, Kamal & Zou 1999). The replicating strip's 11 put strikes (50..100) and 8 call
    -- strikes (100..135) come straight from upstream's own two data tables.
    it "reproduces the Derman/Kamal/Zou replicating-cost variance" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        spotQ <- simpleQuote 100.0
        qTS <- simpleQuote 0.0 >>= \qQ -> flatForward evalDate qQ dc Continuous Annual
        rTS <- simpleQuote 0.05 >>= \rQ -> flatForward evalDate rQ dc Continuous Annual
        -- upstream: "maturity t corrected from 0.25 to 0.246575, corresponding to Jan 1, 1999
        -- to Apr 1, 1999" -- i.e. exactly 90 calendar days, not a t=0.246575 day-fraction to round.
        let exDate = addDays 90 evalDate
            putStrikes  = [50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100 :: Double]
            putVols     = [0.30, 0.29, 0.28, 0.27, 0.26, 0.25, 0.24, 0.23, 0.22, 0.21, 0.20 :: Double]
            callStrikes = [100, 105, 110, 115, 120, 125, 130, 135 :: Double]
            callVols    = [0.20, 0.19, 0.18, 0.17, 0.16, 0.15, 0.14, 0.13 :: Double]
            strikes = putStrikes ++ drop 1 callStrikes
            vols = putVols ++ drop 1 callVols
        cal <- calendar Null
        volTS <- blackVarianceSurface evalDate cal [exDate] strikes (Matrix (fromIntegral (length strikes)) 1 vols)
                                       dc BlackVarianceSurfaceConstantExtrapolation
                                       BlackVarianceSurfaceConstantExtrapolation Bilinear
        process <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
        eng <- replicatingVarianceSwapEngine process 5.0 callStrikes putStrikes
        swp <- varianceSwap Long 0.04 50000 evalDate exDate
        setPricingEngine swp eng
        v <- variance swp
        v `shouldSatisfy` closePrec 0.04189 1.0e-4
