{-# LANGUAGE OverloadedLists #-}
-- Golden-value tests for the exotic single-/multi-asset options bound
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

import Prelude hiding(iterate, tail, drop)
import Test.Hspec
import Data.Time.Calendar(addDays)
import Data.Bits(shiftR, xor)
import Data.Word(Word64)
import Data.List.NonEmpty(iterate, tail, fromList, drop, toList)
import qualified Data.Vector.Storable as V

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote, Quote)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Process hiding(drift)
import QuantLib.Math(Matrix, boxedRealMatrix, realMatrixFromVector, RealMatrix, PolynomialType(..), RngTrait(..), StatisticsTrait(..), Interpolation2D(..))
import QuantLib.Instrument(npv, setPricingEngine, errorEstimate, BarrierType(..), AverageType(..))
import QuantLib.Instrument.Option hiding(theta)
import QuantLib.Instrument.Swap(varianceOption, varianceSwap, variance)
import QuantLib.TermStructure.Volatility(blackConstantVol, blackVarianceSurface, BlackVarianceSurfaceExtrapolation(..))
import QuantLib.PricingEngine
import QuantLib.Spec.Helpers(closePrec)

matrix :: Word -> Word -> [Double] -> Matrix Double
matrix rows columns = either error id . boxedRealMatrix rows columns

realGrid :: Word -> Word -> [Double] -> RealMatrix
realGrid rows columns = either error id . realMatrixFromVector rows columns . V.fromList

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

  describe "ComplexChooserOption" $
    -- cached reference from QuantLib test-suite/chooseroption.cpp::testAnalyticComplexChooserEngine
    it "reproduces Haug's complex chooser option value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 50.0 0.05 0.10 0.35
        eng <- analyticComplexChooserEngine process
        opt <- complexChooserOption (addDays 90 evalDate) 55.0 48.0
                 (europeanIn 270 evalDate) (europeanIn 300 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 6.0508 1e-4

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
        procs <- stochasticProcessArray (fromList [process1, process2]) (matrix 2 2 [1.0, 0.5, 0.5, 1.0])
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

  describe "HolderExtensibleOption" $
    -- cached reference from QuantLib test-suite/extensibleoptions.cpp::testAnalyticHolderExtensibleOptionEngine
    it "reproduces the upstream holder-extensible option value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.0 0.08 0.25
        eng <- analyticHolderExtensibleOptionEngine process
        opt <- holderExtensibleOption Call 1.0 (addDays 270 evalDate) 105.0
                 (PlainVanilla (PlainVanillaPayoff Call 100.0)) (europeanIn 180 evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 9.4233 1e-4

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
      ([(26, 1.81430536630), (100, 1.83822402464)] :: [(Int, Double)])

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
      ([ (Call, 100.0, 120.0, 0.06, 0.10, 0.50, 0.30, 25.3533)
      , (Call, 100.0, 100.0, 0.00, 0.05, 1.00, 0.30, 23.7884)
      , (Put,  100.0, 100.0, 0.00, 0.10, 0.50, 0.30, 15.3526)
      ] :: [(OptionType, Double, Double, Double, Double, Double, Double, Double)])

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
      ([ (95.0, 100.0, 100.0, 0.0, 0.10, 0.50, 0.10, 13.2687)
      , (100.0, 100.0, 100.0, 0.0, 0.10, 0.50, 0.20, 14.1702)
      , (105.0, 100.0, 100.0, 0.0, 0.10, 0.50, 0.30, 15.8512)
      ] :: [(Double, Double, Double, Double, Double, Double, Double, Double)])

    -- cached reference from QuantLib test-suite/lookbackoptions.cpp::testAnalyticContinuousPartialFloatingLookback
    -- (Haug 2006 p.146).
    it "matches the partial-time floating-strike lookback value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 90.0 0.0 0.06 0.1
        eng <- analyticContinuousPartialFloatingLookbackEngine process
        opt <- continuousPartialFloatingLookbackOption 90.0 1.0 (dateOffset evalDate 0.25)
                 (Floating Call) (europeanIn (round (1.0 * 360 :: Double)) evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 8.6524 1.0e-4

    -- cached reference from QuantLib test-suite/lookbackoptions.cpp::testAnalyticContinuousPartialFixedLookback
    -- (Haug 2006 p.148).
    it "matches the partial-time fixed-strike lookback value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        process <- flatProcess evalDate 100.0 0.0 0.06 0.1
        eng <- analyticContinuousPartialFixedLookbackEngine process
        opt <- continuousPartialFixedLookbackOption (dateOffset evalDate 0.25)
                 (PlainVanilla (PlainVanillaPayoff Call 90.0)) (europeanIn (round (1.0 * 360 :: Double)) evalDate)
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 20.2845 1.0e-4

  describe "Continuous lookback options (MC engines)" $ do
    -- cross-checks from QuantLib test-suite/lookbackoptions.cpp::testMonteCarloLookback: each MC
    -- lookback engine variant is checked against its own already-bound analytic engine, not an
    -- independent literal (upstream does the same). tolerance 0.1 absolute is upstream's own.
    let mcTolerance = 0.1 :: Double

    mapM_ (\ty ->
      it ("partial-time fixed-strike MC engine matches its analytic engine for " ++ show ty) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate 100.0 0.0 0.06 0.1
          let lookbackStart = dateOffset evalDate 0.25
              exercise = europeanIn 360 evalDate
              payoff = PlainVanilla (PlainVanillaPayoff ty 90.0)
          opt <- continuousPartialFixedLookbackOption lookbackStart payoff exercise
          analyticEng <- analyticContinuousPartialFixedLookbackEngine process
          setPricingEngine opt analyticEng
          analytical <- npv opt
          mcEng <- mcLookbackPartialFixedEngine PseudoRandom Statistics process (Just 2000) Nothing False True Nothing (Just mcTolerance) Nothing 1
          setPricingEngine opt mcEng
          monteCarlo <- npv opt
          monteCarlo `shouldSatisfy` closePrec analytical mcTolerance)
      ([Call, Put] :: [OptionType])

    mapM_ (\ty ->
      it ("fixed-strike MC engine matches its analytic engine for " ++ show ty) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate 100.0 0.0 0.06 0.1
          let exercise = europeanIn 360 evalDate
              payoff = PlainVanilla (PlainVanillaPayoff ty 90.0)
          opt <- continuousFixedLookbackOption 100.0 payoff exercise
          analyticEng <- analyticContinuousFixedLookbackEngine process
          setPricingEngine opt analyticEng
          analytical <- npv opt
          mcEng <- mcLookbackFixedEngine PseudoRandom Statistics process (Just 2000) Nothing False True Nothing (Just mcTolerance) Nothing 1
          setPricingEngine opt mcEng
          monteCarlo <- npv opt
          monteCarlo `shouldSatisfy` closePrec analytical mcTolerance)
      ([Call, Put] :: [OptionType])

    mapM_ (\ty ->
      it ("partial-time floating-strike MC engine matches its analytic engine for " ++ show ty) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate 100.0 0.0 0.06 0.1
          let lookbackEnd = dateOffset evalDate 0.25
              exercise = europeanIn 360 evalDate
          opt <- continuousPartialFloatingLookbackOption 100.0 1.0 lookbackEnd (Floating ty) exercise
          analyticEng <- analyticContinuousPartialFloatingLookbackEngine process
          setPricingEngine opt analyticEng
          analytical <- npv opt
          mcEng <- mcLookbackPartialFloatingEngine PseudoRandom Statistics process (Just 2000) Nothing False True Nothing (Just mcTolerance) Nothing 1
          setPricingEngine opt mcEng
          monteCarlo <- npv opt
          monteCarlo `shouldSatisfy` closePrec analytical mcTolerance)
      ([Call, Put] :: [OptionType])

    mapM_ (\ty ->
      it ("floating-strike MC engine matches its analytic engine for " ++ show ty) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate 100.0 0.0 0.06 0.1
          let exercise = europeanIn 360 evalDate
          opt <- continuousFloatingLookbackOption 100.0 (Floating ty) exercise
          analyticEng <- analyticContinuousFloatingLookbackEngine process
          setPricingEngine opt analyticEng
          analytical <- npv opt
          mcEng <- mcLookbackFloatingEngine PseudoRandom Statistics process (Just 2000) Nothing False True Nothing (Just mcTolerance) Nothing 1
          setPricingEngine opt mcEng
          monteCarlo <- npv opt
          monteCarlo `shouldSatisfy` closePrec analytical mcTolerance)
      ([Call, Put] :: [OptionType])

  describe "Vecer engine (continuous arithmetic-average Asian options)" $
    -- cached references from QuantLib test-suite/asianoptions.cpp::testVecerEngine.
    mapM_ (\(spot, r, vol, strike, len, expected, tol) ->
      it ("matches the Vecer reference value at spot=" ++ show spot ++ " r=" ++ show r ++
          " vol=" ++ show vol ++ " length=" ++ show len ++ "y") $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process <- flatProcess evalDate spot 0.0 r vol
          let maturity = dateOffset evalDate len
          eng <- continuousArithmeticAsianVecerEngine process (Nothing :: Maybe Quote) evalDate 200 200 (-1.0) 1.0
          opt <- continuousAveragingAsianOption Arithmetic (PlainVanilla (PlainVanillaPayoff Call strike))
                                                 (European (EuropeanExercise maturity))
          setPricingEngine opt eng
          v <- npv opt
          v `shouldSatisfy` closePrec expected tol)
      ([ (1.9, 0.05,   0.5,  2.0, 1.0, 0.193174, 1.0e-5)
       , (2.0, 0.05,   0.5,  2.0, 1.0, 0.246416, 1.0e-5)
       , (2.1, 0.05,   0.5,  2.0, 1.0, 0.306220, 1.0e-4)
       , (2.0, 0.02,   0.1,  2.0, 1.0, 0.055986, 2.0e-4)
       , (2.0, 0.18,   0.3,  2.0, 1.0, 0.218388, 1.0e-4)
       , (2.0, 0.0125, 0.25, 2.0, 2.0, 0.172269, 1.0e-4)
       , (2.0, 0.05,   0.5,  2.0, 2.0, 0.350095, 2.0e-4)
       ] :: [(Double, Double, Double, Double, Double, Double, Double)])

  describe "EverestOption" $
    -- cached reference from QuantLib test-suite/everestoption.cpp::testCached.
    it "matches the cached MCEverestEngine value" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        p1 <- flatProcess evalDate 1.0 0.01 0.05 0.30 >>= asStochasticProcess1D
        p2 <- flatProcess evalDate 1.0 0.05 0.05 0.35 >>= asStochasticProcess1D
        p3 <- flatProcess evalDate 1.0 0.04 0.05 0.25 >>= asStochasticProcess1D
        p4 <- flatProcess evalDate 1.0 0.03 0.05 0.20 >>= asStochasticProcess1D
        let correlation = matrix 4 4
              [ 1.00, 0.50, 0.30, 0.10
              , 0.50, 1.00, 0.20, 0.40
              , 0.30, 0.20, 1.00, 0.60
              , 0.10, 0.40, 0.60, 1.00 ]
        procs <- stochasticProcessArray (fromList [p1, p2, p3, p4]) correlation
        opt <- everestOption 1.0 0.0 (europeanIn 360 evalDate)
        eng <- mcEverestEngine PseudoRandom Statistics procs Nothing (Just 1) False False (Just 1023) Nothing Nothing 86421
        setPricingEngine opt eng
        v <- npv opt
        v `shouldSatisfy` closePrec 0.75784944 1.0e-8
        -- yield = NPV/(notional*discount) - 1; sanity-checked here (no cached reference),
        -- consistent with an NPV well below the notional under a positive discount rate.
        y <- yield opt
        y `shouldSatisfy` (< 0)
        y `shouldSatisfy` (> -1)

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
      ([(2.0, 0.05, Call, 1.5, 0.9104619), (1.5, 0.7, Put, 1.0, 0.0466796)] :: [(Double, Double, OptionType, Double, Double)])

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
            putStrikes  = [50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
            putVols     = [0.30, 0.29, 0.28, 0.27, 0.26, 0.25, 0.24, 0.23, 0.22, 0.21, 0.20 :: Double]
            callStrikes = [100, 105, 110, 115, 120, 125, 130, 135]
            callVols    = [0.20, 0.19, 0.18, 0.17, 0.16, 0.15, 0.14, 0.13 :: Double]
            strikes = toList putStrikes ++ drop 1 callStrikes
            vols = putVols ++ drop 1 callVols
        cal <- calendar Null
        volTS <- blackVarianceSurface evalDate cal [exDate] strikes (realGrid (fromIntegral (length strikes)) 1 vols)
                                       dc BlackVarianceSurfaceConstantExtrapolation
                                       BlackVarianceSurfaceConstantExtrapolation Bilinear
        process <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
        eng <- replicatingVarianceSwapEngine process 5.0 callStrikes putStrikes
        swp <- varianceSwap Long 0.04 50000 evalDate exDate
        setPricingEngine swp eng
        v <- variance swp
        v `shouldSatisfy` closePrec 0.04189 1.0e-4

  describe "MargrabeOption" $ do
    -- cached references from QuantLib test-suite/margrabeoption.cpp::testEuroExchangeTwoAssets
    -- (Margrabe 1978 p.52, plus quantity variants from Excel calculations). theta/rho aren't
    -- checked here: MargrabeOption only has dedicated delta1/delta2/gamma1/gamma2 bound, not
    -- the generic MultiAssetOption theta/rho (those need an upcast this step doesn't add).
    mapM_ (\(s1, s2, q1n, q2n, div1, div2, r, t, v1, v2, correlation, expV, expD1, expD2, expG1, expG2) ->
      it ("matches the European exchange-option value/greeks at s1=" ++ show s1 ++ " s2=" ++ show s2 ++ " rho=" ++ show correlation) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process1 <- flatProcess evalDate s1 div1 r v1
          process2 <- flatProcess evalDate s2 div2 r v2
          eng <- analyticEuropeanMargrabeEngine process1 process2 correlation
          opt <- margrabeOption q1n q2n (europeanIn (round (t * 360 :: Double)) evalDate)
          setPricingEngine opt eng
          v <- npv opt
          d1 <- delta1 opt
          d2 <- delta2 opt
          g1 <- gamma1 opt
          g2 <- gamma2 opt
          v `shouldSatisfy` closePrec expV 1.0e-3
          d1 `shouldSatisfy` closePrec expD1 1.0e-3
          d2 `shouldSatisfy` closePrec expD2 1.0e-3
          g1 `shouldSatisfy` closePrec expG1 1.0e-3
          g2 `shouldSatisfy` closePrec expG2 1.0e-3)
      ([ (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.15, -0.50, 2.125, 0.841, -0.818, 0.112, 0.135)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.20, -0.50, 2.199, 0.813, -0.784, 0.109, 0.132)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.25, -0.50, 2.283, 0.788, -0.753, 0.105, 0.126)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.15,  0.00, 2.045, 0.883, -0.870, 0.108, 0.131)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.20,  0.00, 2.091, 0.857, -0.838, 0.112, 0.135)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.25,  0.00, 2.152, 0.830, -0.805, 0.111, 0.134)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.15,  0.50, 1.974, 0.946, -0.942, 0.079, 0.096)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.20,  0.50, 1.989, 0.929, -0.922, 0.092, 0.111)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.25,  0.50, 2.019, 0.902, -0.891, 0.104, 0.125)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15, -0.50, 2.762, 0.672, -0.602, 0.072, 0.087)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20, -0.50, 2.989, 0.661, -0.578, 0.064, 0.078)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25, -0.50, 3.228, 0.653, -0.557, 0.058, 0.070)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15,  0.00, 2.479, 0.695, -0.640, 0.085, 0.102)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20,  0.00, 2.650, 0.680, -0.616, 0.077, 0.093)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25,  0.00, 2.847, 0.668, -0.592, 0.069, 0.083)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15,  0.50, 2.138, 0.746, -0.713, 0.106, 0.128)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20,  0.50, 2.231, 0.728, -0.689, 0.099, 0.120)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25,  0.50, 2.374, 0.707, -0.659, 0.090, 0.109)
       , (22.0, 10.0, 1, 2, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15,  0.50, 2.138, 0.746, -1.426, 0.106, 0.255)
       , (11.0, 20.0, 2, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20,  0.50, 2.231, 1.455, -0.689, 0.198, 0.120)
       , (11.0, 10.0, 2, 2, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25,  0.50, 2.374, 1.413, -1.317, 0.181, 0.219)
       ] :: [(Double, Double, Int, Int, Double, Double, Double, Double, Double, Double, Double, Double, Double, Double, Double, Double)])

    -- cached references from QuantLib test-suite/margrabeoption.cpp::testAmericanExchangeTwoAssets (Haug).
    mapM_ (\(s1, s2, q1n, q2n, div1, div2, r, t, v1, v2, correlation, expV) ->
      it ("matches the American exchange-option value at s1=" ++ show s1 ++ " s2=" ++ show s2 ++ " t=" ++ show t ++ " rho=" ++ show correlation) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          process1 <- flatProcess evalDate s1 div1 r v1
          process2 <- flatProcess evalDate s2 div2 r v2
          eng <- analyticAmericanMargrabeEngine process1 process2 correlation
          let exDate = addDays (round (t * 360 :: Double)) evalDate
          opt <- margrabeOption q1n q2n (American (Just evalDate) exDate False)
          setPricingEngine opt eng
          v <- npv opt
          v `shouldSatisfy` closePrec expV 1.0e-3)
      ([ (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.15, -0.50, 2.1357)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.20, -0.50, 2.2074)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.25, -0.50, 2.2902)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.15,  0.00, 2.0592)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.20,  0.00, 2.1032)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.25,  0.00, 2.1618)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.15,  0.50, 2.0001)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.20,  0.50, 2.0110)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.10, 0.20, 0.25,  0.50, 2.0359)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15, -0.50, 2.8051)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20, -0.50, 3.0288)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25, -0.50, 3.2664)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15,  0.00, 2.5282)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20,  0.00, 2.6945)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25,  0.00, 2.8893)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.15,  0.50, 2.2053)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.20,  0.50, 2.2906)
       , (22.0, 20.0, 1, 1, 0.06, 0.04, 0.10, 0.50, 0.20, 0.25,  0.50, 2.4261)
       ] :: [(Double, Double, Int, Int, Double, Double, Double, Double, Double, Double, Double, Double)])
