module QuantLib.Spec.TermStructure.Commodity (spec) where

import Control.Exception(evaluate)
import Data.Maybe(isNothing, isJust)
import Data.List.NonEmpty(fromList)

import Test.Hspec hiding(before)

import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..))
import QuantLib.Commodity
import qualified QuantLib.TermStructure.Commodity as Curve

spec :: Spec
spec = do
  describe "CommodityCurve" $ do
    it "round-trips name/commodityType/Curve.unitOfMeasure/currency/nodes" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let dates = [1 `january` 2024, 1 `february` 2024, 1 `march` 2024]
          prices = [70.0, 71.5, 72.0]
          nodes = fromList (zip dates prices)
      curve <- Curve.commodityCurve "HO curve" ho usd bbl cal nodes dc
      Curve.name curve `shouldReturn` "HO curve"
      ct <- Curve.commodityType curve
      ct `shouldBe` ho
      uom <- Curve.unitOfMeasure curve
      uom `shouldBe` bbl
      ccy <- Curve.currency curve
      ccy `shouldBe` usd
      Curve.nodes curve `shouldReturn` zip dates prices
      Curve.isEmpty curve `shouldBe` False

    it "has no basis curve until one is set, and finds it afterwards" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let dates = [1 `january` 2024, 1 `february` 2024]
      curve <- Curve.commodityCurve "HO curve" ho usd bbl cal (fromList (zip dates [70.0, 71.0])) dc
      basis <- Curve.commodityCurve "HO basis" ho usd bbl cal (fromList (zip dates [1.0, 1.0])) dc
      before <- Curve.basisOfCurve curve
      isNothing before `shouldBe` True
      Curve.setBasisOfCurve curve basis
      found <- Curve.basisOfCurve curve
      isJust found `shouldBe` True

    it "prices at a node date via forward-flat interpolation, plus any chained basis price" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let d0 = 1 `january` 2024
          d1 = 1 `february` 2024
      curve <- Curve.commodityCurve "HO curve" ho usd bbl cal (fromList [(d0, 70.0), (d1, 71.0)]) dc
      p0 <- Curve.price curve d0
      p0 `shouldBe` 70.0
      basis <- Curve.commodityCurve "HO basis" ho usd bbl cal (fromList [(d0, 1.0), (d1, 1.0)]) dc
      Curve.setBasisOfCurve curve basis
      p0' <- Curve.price curve d0
      p0' `shouldBe` 71.0
      basisPrice <- Curve.basisOfPrice curve d0
      basisPrice `shouldBe` 1.0

    it "Curve.priceNearby with no contracts and offset 0 reproduces the flat price exactly" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let d0 = 1 `january` 2024
          d1 = 1 `february` 2024
      curve <- Curve.commodityCurve "HO curve" ho usd bbl cal (fromList [(d0, 70.0), (d1, 71.0)]) dc
      flat <- Curve.price curve d0
      rolled <- Curve.priceNearby curve d0 [] 0
      rolled `shouldBe` flat

    it "Curve.underlyingPriceDate rolls onto the nearbyOffset'th exchange contract at or after the query date" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let d0 = 1 `january` 2024
          d1 = 1 `february` 2024
      curve <- Curve.commodityCurve "HO curve" ho usd bbl cal (fromList [(d0, 70.0), (d1, 71.0)]) dc
      let jan1 = 1 `january` 2024
          feb1 = 1 `february` 2024
          mar1 = 1 `march` 2024
          us1 = 5 `january` 2024
          us2 = 5 `february` 2024
          us3 = 5 `march` 2024
          ecs = [ (jan1, ("HOF24", jan1, us1, 31 `january` 2024))
                , (feb1, ("HOG24", feb1, us2, 28 `february` 2024))
                , (mar1, ("HOH24", mar1, us3, 31 `march` 2024))
                ]
      Curve.underlyingPriceDate curve jan1 ecs 1 `shouldReturn` us1
      Curve.underlyingPriceDate curve jan1 ecs 2 `shouldReturn` us2
      Curve.underlyingPriceDate curve jan1 ecs 3 `shouldReturn` us3
      Curve.underlyingPriceDate curve jan1 ecs 4 `shouldThrow` anyException
      Curve.underlyingPriceDate curve jan1 ecs 0 `shouldThrow` anyException

  describe "DateInterval" $ do
    it "isDateBetween respects the includeFirst/includeLast flags" $ do
      let d0 = 1 `january` 2024
          d1 = 31 `january` 2024
          mid = 15 `january` 2024
          iv = (d0, d1)
      isDateBetween iv mid True True `shouldBe` True
      isDateBetween iv d0 True True `shouldBe` True
      isDateBetween iv d0 False True `shouldBe` False
      isDateBetween iv d1 True True `shouldBe` True
      isDateBetween iv d1 True False `shouldBe` False

    it "intersection overlaps two ranges, or Nothing if disjoint" $ do
      let iv1 = (1 `january` 2024, 31 `january` 2024)
          iv2 = (15 `january` 2024, 15 `february` 2024)
          iv3 = (1 `march` 2024, 31 `march` 2024)
      intersection iv1 iv2 `shouldBe` Just (15 `january` 2024, 31 `january` 2024)
      intersection iv1 iv3 `shouldBe` Nothing

  describe "PricingPeriod" $ do
    it "carries its dates/payment date/quantity, rejecting an end before the start" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      let s = 1 `january` 2024
          e = 31 `january` 2024
          p = 5 `february` 2024
          q = (ho, bbl, 1000)
          pp = pricingPeriod s e p q
      pricingPeriodStartDate pp `shouldBe` s
      pricingPeriodEndDate pp `shouldBe` e
      pricingPeriodPaymentDate pp `shouldBe` p
      pricingPeriodQuantity pp `shouldBe` q
      evaluate (pricingPeriod e s p q) `shouldThrow` anyErrorCall

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
