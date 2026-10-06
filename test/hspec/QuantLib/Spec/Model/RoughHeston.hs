{-# LANGUAGE TupleSections #-}
module QuantLib.Spec.Model.RoughHeston (spec) where

import Control.Monad(forM, forM_)
import Data.Complex(Complex((:+)), magnitude)
import Data.List.NonEmpty(NonEmpty(..))
import Data.Time.Calendar(Day, fromGregorian, addDays)
import Test.Hspec
import qualified QuantLib.Context as Context
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote
import QuantLib.TermStructure(Reference(..), TermPoint(..), timeFromReference)
import QuantLib.TermStructure.Yield(flatForward, discount)
import QuantLib.Process(hestonProcess, HestonProcessDiscretization(..))
import qualified QuantLib.Model as Model
import QuantLib.Model(RoughHestonModel, roughHestonModel)
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Option
import QuantLib.PricingEngine
import QuantLib.Math(OptimizationMethod(..), EndCriteria(..))
import QuantLib.Spec.Helpers(quantLibAtMost143, unsupportedQuantLib144)

fixtureDate :: Day
fixtureDate = fromGregorian 2026 7 2

fixture :: Double -> IO (RoughHestonModel, SimpleQuote)
fixture hurst = do
  Context.setEvaluationDate (Just fixtureDate)
  dc <- dayCounter Actual365FixedStandard
  r <- simpleQuote 0.03 >>= \q -> flatForward (ReferenceDate fixtureDate) q dc Continuous Annual
  q <- simpleQuote 0 >>= \v -> flatForward (ReferenceDate fixtureDate) v dc Continuous Annual
  spot <- simpleQuote 100
  process <- hestonProcess r (Just q) spot 0.04 0.3 0.04 0.4 (-0.7) QuadraticExponentialMartingale
  model <- roughHestonModel process hurst
  pure (model, spot)

near :: Double -> Double -> Double -> Expectation
near tolerance expected actual = abs (actual - expected) `shouldSatisfy` (< tolerance)

spec :: Spec
spec = describe "Rough Heston 1.44" $
  if quantLibAtMost143 then
    it "reports the required version before constructing the model" $ Context.keepingSettingsGc $
      fixture 0.1 `shouldThrow` unsupportedQuantLib144 "roughHestonModel"
  else do
    it "matches upstream independent reference prices" $ Context.keepingSettingsGc $ do
      (model, _) <- fixture 0.1
      engine <- analyticRoughHestonEngine model 128 512 AdamsPredictorCorrector
      forM_ [(0.25, 75, 25.762400), (0.25, 100, 3.793313), (1, 100, 8.336634), (2, 130, 1.285820)] $ \(t,k,expected) ->
        roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call k) (TimePoint t) >>= near 5e-4 expected

    it "prices through the engine family and preserves date/time semantics" $ Context.keepingSettingsGc $ do
      (model, _) <- fixture 0.1
      engine <- analyticRoughHestonEngine model 128 256 AdamsPredictorCorrector
      let maturity = addDays 365 fixtureDate
          payoff = PlainVanillaPayoff Call 100
      option <- vanillaOption (PlainVanilla payoff) (European (EuropeanExercise maturity))
      setPricingEngine option engine
      expected <- npv option
      roughHestonPriceVanillaPayoff engine payoff (DatePoint maturity) >>= near 1e-8 expected
      roughHestonPriceVanillaPayoff engine payoff (TimePoint 1) >>= near 1e-8 expected
      process <- Model.roughHestonProcess model
      -- The process's risk-free curve uses the same day counter as direct date pricing.
      Model.roughHestonHurst model `shouldReturn` 0.1
      Model.params model >>= \ps -> length ps `shouldBe` 6
      engineAsBase <- asPricingEngine engine
      setPricingEngine option engineAsBase
      npv option >>= near 1e-8 expected
      hm <- Model.hestonModel process
      analyticHestonEngine hm (IntegrationOrder 128) >>= setPricingEngine option
      hestonPrice <- npv option
      (classical, _) <- fixture 0.5
      classicalEngine <- analyticRoughHestonEngine classical 128 512 AdamsPredictorCorrector
      roughHestonPriceVanillaPayoff classicalEngine payoff (DatePoint maturity) >>= near 5e-4 hestonPrice

    it "supports all approximations, complex analytics and observer updates" $ Context.keepingSettingsGc $ do
      (model, spot) <- fixture 0.1
      engines <- mapM (analyticRoughHestonEngine model 128 512) [AdamsPredictorCorrector, Pade, Lifted 40]
      forM_ engines $ \engine -> do
        roughHestonCharacteristicFunction engine (0 :+ 0) 1 >>= \z -> magnitude (z - 1) `shouldSatisfy` (< 1e-10)
        phi <- roughHestonCharacteristicFunction engine (1.2 :+ (-0.5)) 1
        logPhi <- roughHestonLogCharacteristicFunction engine (1.2 :+ (-0.5)) 1
        magnitude (phi - exp logPhi) `shouldSatisfy` (< 1e-10)
        roughHestonRiccatiSolution engine (0 :+ 0) 1 >>= \z -> magnitude z `shouldSatisfy` (< 1e-10)
        p <- roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call 100) (TimePoint 1)
        near 0.4 8.336634 p
        roughHestonNumberOfEvaluations engine >>= (`shouldSatisfy` (> 0))
      case engines of
        engine:_ -> do
          priceBefore <- roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call 100) (TimePoint 1)
          _ <- setValue spot 110
          priceAfter <- roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call 100) (TimePoint 1)
          priceAfter `shouldSatisfy` (> priceBefore)
          Model.setParams model [0.05, 0.4, 0.3, -0.6, 0.03, 0.2]
          Model.roughHestonTheta model `shouldReturn` 0.05
          Model.roughHestonHurst model `shouldReturn` 0.2
          changed <- roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call 100) (TimePoint 1)
          changed `shouldSatisfy` (\p -> abs (p - priceAfter) > 1e-4)
        [] -> expectationFailure "missing approximation engines"

    it "honours Fourier integration controls and rejects invalid configurations" $ Context.keepingSettingsGc $ do
      (model, _) <- fixture 0.1
      engine <- analyticRoughHestonEngineWithIntegration model (FourierGaussLobatto 1e-8 1e-8 10000 False) 256 1e-25 (-0.5) AdamsPredictorCorrector
      roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call 100) (TimePoint 1) >>= near 5e-4 8.336634
      analyticRoughHestonEngine model 128 0 AdamsPredictorCorrector `shouldThrow` anyException
      analyticRoughHestonEngine model 128 256 (Lifted 0) `shouldThrow` anyException
      analyticRoughHestonEngineWithIntegration model (FourierGaussLaguerre 128) 256 1e-25 0 Pade `shouldThrow` anyException

    it "calibrates Hurst and regenerates model state" $ Context.keepingSettingsGc $ do
      (model, _) <- fixture 0.12
      dc <- dayCounter Actual365FixedStandard
      r <- simpleQuote 0.03 >>= \q -> flatForward (ReferenceDate fixtureDate) q dc Continuous Annual
      q <- simpleQuote 0 >>= \v -> flatForward (ReferenceDate fixtureDate) v dc Continuous Annual
      spot <- simpleQuote 100
      cal <- calendar Null
      truth <- analyticRoughHestonEngine model 64 256 Pade
      helpers <- forM [3, 6, 12] $ \months -> do
        maturity <- advance cal fixtureDate (months, Months) Unadjusted False
        t <- timeFromReference r maturity
        df <- discount r (DatePoint maturity) False
        let fwd = 100 / df
        price <- roughHestonPriceVanillaPayoff truth (PlainVanillaPayoff Call 100) (DatePoint maturity)
        stddev <- blackImpliedStdDev Call 100 fwd price df 0 0.2 1e-10 100
        vol <- simpleQuote (stddev / sqrt t)
        Model.hestonModelHelper (fromIntegral months, Months) cal spot 100 vol r q Model.ImpliedVolError
      Model.setParams model [0.04, 0.3, 0.4, -0.7, 0.04, 0.2]
      engine <- analyticRoughHestonEngine model 64 256 Pade
      forM_ helpers $ \helper -> Model.setPricingEngine helper engine
      case helpers of
        h:hs -> Model.calibrate model ((h,1) :| map (,1) hs)
          (LevenbergMarquardt 1e-8 1e-8 1e-8 False) (EndCriteria 100 20 1e-8 1e-8 1e-8) Nothing [True,True,True,True,True,False]
        [] -> expectationFailure "missing calibration helpers"
      Model.roughHestonHurst model >>= near 1e-4 0.12
