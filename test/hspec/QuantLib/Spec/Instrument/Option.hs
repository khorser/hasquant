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
import QuantLib.Process
import QuantLib.Math(Matrix(..), PolynomialType(..), RngTrait(..))
import QuantLib.Instrument(npv, setPricingEngine, BarrierType(..))
import QuantLib.Instrument.Option hiding(theta)
import QuantLib.PricingEngine
import QuantLib.Spec.Helpers(closePrec)

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
        euEngine <- mcEuropeanBasketEngine PseudoRandom procs Nothing (Just 1) False False (Just 10000) Nothing Nothing 42
        euOpt <- basketOption payoff (europeanIn 360 evalDate)
        setPricingEngine euOpt euEngine
        euNpv <- npv euOpt
        euNpv `shouldSatisfy` closePrec expected 1.0

        amEngine <- mcAmericanBasketEngine PseudoRandom procs (Just 50) Nothing False True (Just 10000) Nothing Nothing 43 (Just 2500) 2 Monomial
        amOpt <- basketOption payoff (American Nothing (addDays 360 evalDate) False)
        setPricingEngine amOpt amEngine
        amNpv <- npv amOpt
        amNpv `shouldSatisfy` closePrec expected 1.5

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
