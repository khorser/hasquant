-- | Golden-value tests for 'QuantLib.Instrument.CapFloor' ('cap'\/'floor'\/'atmRate'\/
-- 'impliedVolatility'\/'optionlet'), ported from QuantLib's own test-suite/capfloor.cpp.
--
-- The cached NPVs in testCachedValue depend on QuantLib's global @IborCoupon::Settings@
-- \"at-par coupons\" toggle, which hasquant doesn't bind (there is no way to set it from
-- Haskell) -- both installed-QuantLib variants (par-coupon vs. index-fixing pricing) are
-- accepted rather than assuming one.
{-# LANGUAGE OverloadedLists #-}

module QuantLib.Spec.Instrument.CapFloor (spec) where

import Prelude hiding(floor)
import Control.Monad(forM_)

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..), VolatilityType(..))
import QuantLib.Quote hiding(value)
import QuantLib.TermStructure.Yield
import QuantLib.CashFlow(iborLeg, Leg)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor6M))
import QuantLib.Instrument(npv, setPricingEngine, additionalResults, AdditionalResultVal(..))
import QuantLib.Instrument.Swap(vanillaSwap, SwapType(..))
import QuantLib.Instrument.CapFloor
import QuantLib.PricingEngine(blackCapFloorEngine, discountingSwapEngine)

import QuantLib.Spec.Helpers(closePrec)

-- |accepts either of the two cached values QuantLib's own test carries (index-fixing vs.
-- at-par coupon pricing), since hasquant has no binding to select between them
closeToEither :: Double -> Double -> Double -> Bool
closeToEither a b v = closePrec a 1.0e-8 v || closePrec b 1.0e-8 v

-- |Euribor6M-based 20Y cap/floor leg on a flat 5% Actual360 curve referenced at 18 March 2002,
-- the exact fixture test-suite/capfloor.cpp's CommonVars\/testCachedValue build (evaluation
-- date pinned to 14 March 2002).
cachedFixture :: IO Leg
cachedFixture = do
  Settings.setEvaluationDate (Just (14 `march` 2002))
  cal <- calendar TARGET
  let startDate = 18 `march` 2002
  dc <- dayCounter (Actual360 False)
  q <- simpleQuote 0.05
  ts <- flatForward startDate q dc Continuous Annual
  idx <- iborIndex Euribor6M (Just ts)
  endDate <- advance cal startDate (20, Years) ModifiedFollowing False
  sch <- schedule (Just startDate) endDate (6, Months) cal ModifiedFollowing ModifiedFollowing
    Forward False Nothing Nothing
  iborDC <- dayCounter (Actual360 False)
  iborLeg sch idx [100] iborDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False

spec :: Spec
spec = do
  describe "testCachedValue" $
    it "Black cap/floor NPV reproduces capfloor.cpp's cached values" $
      Settings.keepingSettings' $ do
        leg <- cachedFixture
        dc <- dayCounter (Actual360 False)
        volQ <- simpleQuote 0.20
        q <- simpleQuote 0.05
        ts <- flatForward (18 `march` 2002) q dc Continuous Annual
        volDC <- dayCounter Actual365FixedStandard
        eng <- blackCapFloorEngine ts volQ volDC 0.0
        capfl <- cap leg [0.07]
        setPricingEngine capfl eng
        capNPV <- npv capfl
        capNPV `shouldSatisfy` closeToEither 6.87630307745 6.87570026732
        flr <- floor leg [0.03]
        setPricingEngine flr eng
        flrNPV <- npv flr
        flrNPV `shouldSatisfy` closeToEither 2.65796764715 2.65812927959

  describe "testCachedValueFromOptionLets" $
    it "sums additionalResults[optionletsPrice] to the same cached cap/floor NPVs" $
      Settings.keepingSettings' $ do
        leg <- cachedFixture
        dc <- dayCounter (Actual360 False)
        volQ <- simpleQuote 0.20
        q <- simpleQuote 0.05
        ts <- flatForward (18 `march` 2002) q dc Continuous Annual
        volDC <- dayCounter Actual365FixedStandard
        eng <- blackCapFloorEngine ts volQ volDC 0.0

        capfl <- cap leg [0.07]
        setPricingEngine capfl eng
        _ <- npv capfl
        capAddl <- additionalResults capfl
        case lookup "optionletsPrice" capAddl of
          Just (RealVectorVal xs) -> do
            length xs `shouldBe` 40
            sum xs `shouldSatisfy` closeToEither 6.87630307745 6.87570026732
          other -> expectationFailure ("expected optionletsPrice as RealVectorVal, got " ++ show other)

        flr <- floor leg [0.03]
        setPricingEngine flr eng
        _ <- npv flr
        flrAddl <- additionalResults flr
        case lookup "optionletsPrice" flrAddl of
          Just (RealVectorVal xs) -> sum xs `shouldSatisfy` closeToEither 2.65796764715 2.65812927959
          other -> expectationFailure ("expected optionletsPrice as RealVectorVal, got " ++ show other)

  describe "testATMRate" $
    it "cap atmRate == floor atmRate, and a VanillaSwap struck there reprices to ~0" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just (11 `december` 2012))
        cal <- calendar TARGET
        settle <- advance cal (11 `december` 2012) (2, Days) ModifiedFollowing False
        dc <- dayCounter Actual365FixedStandard
        q <- simpleQuote 0.05
        ts <- flatForward settle q dc Continuous Annual
        idx <- iborIndex Euribor6M (Just ts)
        maturity <- advance cal settle (10, Years) ModifiedFollowing False
        sch <- schedule (Just settle) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing
          Forward False Nothing Nothing
        iborDC <- dayCounter (Actual360 False)
        leg <- iborLeg sch idx [100] iborDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False

        capfl <- cap leg [0.05]
        flr <- floor leg [0.05]
        capATM <- atmRate capfl ts
        floorATM <- atmRate flr ts
        floorATM `shouldSatisfy` closePrec capATM 1.0e-10

        swap <- vanillaSwap Payer 100 sch floorATM iborDC sch idx 0.0 iborDC Nothing Nothing
        swapEng <- discountingSwapEngine ts Nothing Nothing Nothing
        setPricingEngine swap swapEng
        swapNPV <- npv swap
        swapNPV `shouldSatisfy` closePrec 0 1.0e-8

  describe "testImpliedVolatility" $
    it "round-trips impliedVolatility against the vol used to build the cap's price" $
      Settings.keepingSettings' $ do
        Settings.setEvaluationDate (Just (11 `december` 2012))
        cal <- calendar TARGET
        settle <- advance cal (11 `december` 2012) (2, Days) ModifiedFollowing False
        dc <- dayCounter (Actual360 False)
        q <- simpleQuote 0.05
        ts <- flatForward settle q dc Continuous Annual
        idx <- iborIndex Euribor6M (Just ts)
        maturity <- advance cal settle (10, Years) ModifiedFollowing False
        sch <- schedule (Just settle) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing
          Forward False Nothing Nothing
        leg <- iborLeg sch idx [100] dc ModifiedFollowing [2] [1.0] [0.0] [] [] False False
        capfl <- cap leg [0.03]
        volDC <- dayCounter Actual365FixedStandard

        forM_ ([0.10, 0.20, 0.30] :: [Double]) $ \v -> do
          volQ <- simpleQuote v
          eng <- blackCapFloorEngine ts volQ volDC 0.0
          setPricingEngine capfl eng
          value <- npv capfl
          implVol <- impliedVolatility capfl value ts 0.10 1.0e-8 100 1.0e-7 4.0 ShiftedLognormal 0.0
          implVol `shouldSatisfy` closePrec v 1.0e-6
