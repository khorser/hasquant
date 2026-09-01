-- | Coverage for 'QuantLib.Instrument' entry points ported from
-- @test/smoke/CheckAdditionalResults.hs@ (see CLAUDE.md: coverage is only measured over
-- @test\/hspec\/**@ + @test\/example\/**@, so this proven-correct smoke script was invisible
-- to the coverage number).
--
-- Checks 'additionalResults' end-to-end against two real QuantLib 1.43 engines that exercise
-- three of its four discriminants: the Bjerksund-Stensland American option engine writes
-- @exerciseType@ (std::string -> 'StringVal') and @strikeGamma@ (Real -> 'RealVal'); the Black
-- cap/floor engine writes @optionletsPrice@ as a @vector\<Real\>@ -> 'RealVectorVal',
-- exercising the vector marshalling branch the first check never touches. No shipped 1.43
-- engine stores a type this binding can't name, so the fourth discriminant ('UnsupportedVal',
-- the RTTI-name fallback) isn't exercised here -- its C++ side is a trivial, visibly-correct
-- @else@, and its Haskell side is a compiler-checked exhaustive @case@.
{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Spec.Instrument (spec) where

import Data.Time.Calendar(fromGregorian)
import Control.Monad(forM_)
import qualified Data.List.NonEmpty as NE

import Test.Hspec

import QuantLib.Instrument
import QuantLib.Instrument.CapFloor
import QuantLib.Instrument.Option
import QuantLib.CashFlow hiding(npv, leg)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor6M))
import QuantLib.PricingEngine
import QuantLib.Process
import qualified QuantLib.Settings as Settings
import QuantLib.Syntax
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Quote
import QuantLib.InterestRate

spec :: Spec
spec = do
  describe "additionalResults" $ do
    it "Bjerksund-Stensland American option engine: exerciseType (StringVal) and strikeGamma (RealVal, > 0)" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate $ Just (fromGregorian 1998 5 15)
        dc <- dayCounter Actual365FixedStandard
        let evalDate = 17 `may` 1998
            maturity = 17 `may` 1999
            under = 36; strike = 40; dividend = 0.0; riskFreeRate = 0.06; vol = 0.20
            optType = Put
        underQ <- simpleQuote under
        riskFreeQ <- simpleQuote riskFreeRate
        ts <- flatForward evalDate riskFreeQ dc Continuous Annual
        divQ <- simpleQuote dividend
        divTS <- flatForward evalDate divQ dc Continuous Annual
        volQ <- simpleQuote vol
        volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) evalDate volQ dc
        let payoff = PlainVanilla $ PlainVanillaPayoff optType strike
        bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False
        americanOpt <- vanillaOption payoff (American Nothing maturity False)

        bjs <- bjerksundStenslandApproximationEngine bsmProc
        setPricingEngine americanOpt bjs
        _ <- npv americanOpt

        addl <- additionalResults americanOpt
        lookup "exerciseType" addl `shouldBe` Just (StringVal "American")
        case lookup "strikeGamma" addl of
          Just (RealVal g) -> g `shouldSatisfy` (> 0)
          other -> expectationFailure ("expected strikeGamma present as RealVal, got " ++ show other)
        length addl `shouldSatisfy` (> 0)

    it "Black cap/floor engine: optionletsPrice (RealVectorVal, non-empty and non-negative)" $
      Settings.keepingSettings' $ do
        let today' = 11 `december` 2012
        Settings.setEvaluationDate (Just today')
        cal <- calendar TARGET
        settle <- advance cal today' (2, Days) Following False
        discQ <- simpleQuote 0.02
        dc <- dayCounter Actual365FixedStandard
        discountTS <- flatForward today' discQ dc Continuous Annual
        idx <- iborIndex Euribor6M (Just discountTS)
        floatDC <- dayCounter (Actual360 False)
        floatSch <- schedule (Just settle) (11 `december` 2017) (6, Months) cal
          ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
        leg <- iborLeg floatSch idx (1000000 NE.:| []) floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
        capfl <- cap leg (0.03 NE.:| [])
        volQ <- simpleQuote 0.20
        vol0 <- constantOptionletVolatility today' cal ModifiedFollowing volQ dc ShiftedLognormal 0
        eng <- blackCapFloorEngine' discountTS vol0
        setPricingEngine capfl eng
        _ <- npv capfl

        addl <- additionalResults capfl
        case lookup "optionletsPrice" addl of
          Just (RealVectorVal xs) -> do
            xs `shouldSatisfy` (not . null)
            xs `shouldSatisfy` all (>= 0)
          other -> expectationFailure ("expected optionletsPrice present as RealVectorVal, got " ++ show other)

  describe "PerpetualFutures" $
    it "reproduces perpetualfutures.cpp's constant-parameter analytic values" $
      Settings.keepingSettings' $ do
        let evalDate = fromGregorian 2024 1 2
            spot = 10000.0
            domesticRate = 0.04
            foreignRate = 0.02
            fundingRate = 0.01
            interestRateDiff = 0.005
            cases =
              [ (PerpetualFuturesLinear, PerpetualFuturesFundingWithPreviousSpot, (3, Months))
              , (PerpetualFuturesLinear, PerpetualFuturesFundingWithCurrentSpot, (3, Months))
              , (PerpetualFuturesInverse, PerpetualFuturesFundingWithPreviousSpot, (3, Months))
              , (PerpetualFuturesInverse, PerpetualFuturesFundingWithCurrentSpot, (3, Months))
              , (PerpetualFuturesLinear, PerpetualFuturesFundingWithPreviousSpot, (0, Months))
              , (PerpetualFuturesInverse, PerpetualFuturesFundingWithPreviousSpot, (0, Months))
              ]
            expected payoff fundingType (frequency, _) =
              let dt = fromIntegral frequency / 12.0
               in if frequency == 0
                    then case payoff of
                      PerpetualFuturesLinear -> spot * (fundingRate - interestRateDiff) /
                        (foreignRate - domesticRate + fundingRate)
                      PerpetualFuturesInverse -> spot * (domesticRate - foreignRate + fundingRate) /
                        (fundingRate - interestRateDiff)
                      PerpetualFuturesQuanto -> error "Quanto is unsupported by the engine"
                    else case (payoff, fundingType) of
                      (PerpetualFuturesLinear, PerpetualFuturesFundingWithPreviousSpot) ->
                        spot * (fundingRate - interestRateDiff) * exp (foreignRate * dt) /
                        (exp (foreignRate * dt) - exp (domesticRate * dt) + fundingRate * exp (foreignRate * dt))
                      (PerpetualFuturesLinear, PerpetualFuturesFundingWithCurrentSpot) ->
                        spot * (fundingRate - interestRateDiff) * exp (domesticRate * dt) /
                        (exp (foreignRate * dt) - exp (domesticRate * dt) + fundingRate * exp (domesticRate * dt))
                      (PerpetualFuturesInverse, PerpetualFuturesFundingWithPreviousSpot) ->
                        spot * (exp (domesticRate * dt) - exp (foreignRate * dt) + fundingRate * exp (domesticRate * dt)) /
                        (fundingRate - interestRateDiff) / exp (domesticRate * dt)
                      (PerpetualFuturesInverse, PerpetualFuturesFundingWithCurrentSpot) ->
                        spot * (exp (domesticRate * dt) - exp (foreignRate * dt) + fundingRate * exp (foreignRate * dt)) /
                        (fundingRate - interestRateDiff) / exp (foreignRate * dt)
                      (_, _) -> error "Quanto is unsupported by the engine"
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter ActualActualISDA
        cal <- calendar (Bespoke "PerpetualFutures" [])
        domesticQuote <- simpleQuote domesticRate
        foreignQuote <- simpleQuote foreignRate
        domesticCurve <- flatForward evalDate domesticQuote dc Continuous Annual
        foreignCurve <- flatForward evalDate foreignQuote dc Continuous Annual
        spotQuote <- simpleQuote spot
        forM_ cases $ \(payoff, fundingType, frequency) -> do
          future <- perpetualFutures payoff fundingType frequency cal dc
          engine <- discountingPerpetualFuturesEngine domesticCurve foreignCurve spotQuote
            ((0, fundingRate, interestRateDiff) NE.:| []) PerpetualFuturesPiecewiseConstant 60
          setPricingEngine future engine
          actual <- npv future
          abs (actual / expected payoff fundingType frequency - 1) `shouldSatisfy` (< 1.0e-6)
