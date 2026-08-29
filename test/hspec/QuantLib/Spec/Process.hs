-- | Coverage for model-level self-consistency/golden-value checks that don't fit naturally
-- under 'QuantLib.Instrument' or 'QuantLib.PricingEngine' -- 'HestonModel'/'HestonProcess'
-- against a closed-form Black price, and 'GJRGARCHModel'/'GJRGARCHProcess' analytic vs. Monte
-- Carlo. Ported from QuantLib's own test-suite/hestonmodel.cpp::testAnalyticVsBlack and
-- test-suite/gjrgarchmodel.cpp::testEngines (a small representative subset of the latter's
-- 3x2x6 case table, to keep the MC engine's runtime reasonable).
--
-- G2Process/G2ForwardProcess and HybridHestonHullWhiteProcess were investigated for this
-- module and dropped: neither exposes the accessors upstream's own tests need
-- (@phi@/@shortRate@/@factors@ for G2, @HullWhiteForwardProcess::setForwardMeasureTime@ for
-- the hybrid process -- a required post-construction call with no hasquant binding), so no
-- meaningful self-consistency check is reachable through the current binding surface without
-- adding a new binding, which is out of scope for a test-porting task.
module QuantLib.Spec.Process (spec) where

import Test.Hspec
import Data.Time.Calendar(addDays)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Option(europeanOption, StrikedPayoff(PlainVanilla), PlainVanillaPayoff(..), OptionType(..), Exercise(European), EuropeanExercise(..))
import QuantLib.Process(hestonProcess, gjrGARCHProcess, HestonProcessDiscretization(..), GJRGARCHProcessDiscretization(..))
import QuantLib.Model(hestonModel, gJRGARCHModel)
import QuantLib.Math(RngTrait(..), StatisticsTrait(..))
import QuantLib.PricingEngine(analyticHestonEngine', analyticGJRGARCHEngine, mcEuropeanGJRGARCHEngine, blackFormula)

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = do
  describe "HestonModel (AnalyticHestonEngine vs. Black formula)" $
    -- cached reference from test-suite/hestonmodel.cpp::testAnalyticVsBlack: a near-zero
    -- vol-of-vol Heston process (sigma=1e-4) should reproduce the flat-vol Black price almost
    -- exactly.
    it "reproduces the Black price at near-zero vol-of-vol" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter Actual365FixedStandard
        let exerciseDays = round (0.5 * 365 :: Double) :: Integer
            -- the *exact* Actual365Fixed year fraction the process's own date-based
            -- discounting will use for a 'round(0.5*365)'-day exercise -- not exactly 0.5, so
            -- computing 'expected' at a hardcoded 0.5 would miss the 2e-7 tolerance below by a
            -- day-rounding amount many orders of magnitude larger.
            t = fromIntegral exerciseDays / 365 :: Double
            strike = 30.0
            spot = 32.0
            r = 0.1
            q = 0.04
            v0 = 0.05
        rQ <- simpleQuote r
        qQ <- simpleQuote q
        rTS <- flatForward evalDate rQ dc Continuous Annual
        qTS <- flatForward evalDate qQ dc Continuous Annual
        s0 <- simpleQuote spot
        process <- hestonProcess rTS (Just qTS) s0 v0 5.0 0.05 1.0e-4 0.0 QuadraticExponentialMartingale
        model <- hestonModel process
        eng <- analyticHestonEngine' model 144
        let exerciseDate = addDays exerciseDays evalDate
        opt <- europeanOption (PlainVanilla (PlainVanillaPayoff Put strike)) (European (EuropeanExercise exerciseDate))
        setPricingEngine opt eng
        calculated <- npv opt

        let forwardPrice = spot * exp ((r - q) * t)
        expected <- blackFormula Put strike forwardPrice (sqrt (v0 * t)) (exp (-r * t)) 0.0
        calculated `shouldSatisfy` closePrec expected 2.0e-7

  describe "GJRGARCHModel (AnalyticGJRGARCHEngine vs. MCEuropeanGJRGARCHEngine)" $
    -- cached references from test-suite/gjrgarchmodel.cpp::testEngines: a 2-of-36-case subset
    -- (lambda=0, maturity=90 days, strikes 35/50) of the full 3x2x6 table, checked against both
    -- upstream's own cached analytic and Monte Carlo values, at upstream's own tolerance.
    mapM_ (\(strike, analyticExpected, mcExpected) ->
      it ("matches upstream's cached analytic/MC values at strike=" ++ show strike) $
        Settings.keepingSettings' $ do
          evalDate <- today
          Settings.setEvaluationDate (Just evalDate)
          dc <- dayCounter ActualActualISDA
          rTS <- simpleQuote 0.05 >>= \rQ -> flatForward evalDate rQ dc Continuous Annual
          qTS <- simpleQuote 0.0 >>= \qQ -> flatForward evalDate qQ dc Continuous Annual
          s0 <- simpleQuote 50.0
          let omega = 2.0e-6; alpha = 0.024; beta = 0.93; gamma = 0.059; lambda = 0.0
              daysPerYear = 365.0
              -- m1/v0 per upstream's own GJR-GARCH stationary-variance formula
              cumNorm x = 0.5 * (1 + erf (x / sqrt 2))
              m1 = beta + (alpha + gamma * cumNorm lambda) * (1 + lambda * lambda)
                     + gamma * lambda * exp (-lambda * lambda / 2) / sqrt (2 * pi)
              v0 = omega / (1 - m1)
          process <- gjrGARCHProcess rTS qTS s0 v0 omega alpha beta gamma lambda daysPerYear GJRGARCHFullTruncation
          model <- gJRGARCHModel process
          analyticEng <- analyticGJRGARCHEngine model
          mcEng <- mcEuropeanGJRGARCHEngine PseudoRandom Statistics process Nothing (Just 20) False Nothing (Just 0.02) Nothing 1234
          let exerciseDate = addDays 90 evalDate
          optA <- europeanOption (PlainVanilla (PlainVanillaPayoff Call strike)) (European (EuropeanExercise exerciseDate))
          setPricingEngine optA analyticEng
          analyticNpv <- npv optA
          analyticNpv `shouldSatisfy` closePrec analyticExpected 0.15

          optM <- europeanOption (PlainVanilla (PlainVanillaPayoff Call strike)) (European (EuropeanExercise exerciseDate))
          setPricingEngine optM mcEng
          mcNpv <- npv optM
          mcNpv `shouldSatisfy` closePrec mcExpected 0.15)
      [ (35.0 :: Double, 15.4315 :: Double, 15.4332 :: Double)
      , (50.0, 2.3282, 2.3521)
      ]
  where
    -- Abramowitz & Stegun 7.1.26 approximation, accurate to ~1.5e-7 -- ample for this
    -- table's 0.15 tolerance; avoids a new dependency for a single-call use.
    erf :: Double -> Double
    erf x =
      let a1 = 0.254829592; a2 = -0.284496736; a3 = 1.421413741
          a4 = -1.453152027; a5 = 1.061405429; p = 0.3275911
          sign = if x < 0 then -1 else 1
          ax = abs x
          t' = 1 / (1 + p * ax)
          y = 1 - (((((a5 * t' + a4) * t') + a3) * t' + a2) * t' + a1) * t' * exp (-ax * ax)
      in sign * y

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
