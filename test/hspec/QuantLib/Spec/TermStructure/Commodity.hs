module QuantLib.Spec.TermStructure.Commodity (spec) where

import Control.Exception(evaluate)
import Data.Maybe(isNothing, isJust)

import Test.Hspec

import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..))
import QuantLib.Commodity
import QuantLib.TermStructure.Commodity

spec :: Spec
spec = do
  describe "CommodityCurve" $ do
    it "round-trips name/commodityType/unitOfMeasure/currency/dates/prices, non-empty" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let dates = [1 `january` 2024, 1 `february` 2024, 1 `march` 2024]
          prices = [70.0, 71.5, 72.0]
      curve <- commodityCurve "HO curve" ho usd bbl cal dates prices dc
      commodityCurveName curve `shouldReturn` "HO curve"
      ct <- commodityCurveCommodityType curve
      ct `shouldBe` ho
      uom <- commodityCurveUnitOfMeasure curve
      uom `shouldBe` bbl
      ccy <- commodityCurveCurrency curve
      ccy `shouldBe` usd
      commodityCurveDates curve `shouldReturn` dates
      commodityCurvePrices curve `shouldReturn` prices
      commodityCurveEmpty curve `shouldBe` False

    it "has no basis curve until one is set, and finds it afterwards" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let dates = [1 `january` 2024, 1 `february` 2024]
      curve <- commodityCurve "HO curve" ho usd bbl cal dates [70.0, 71.0] dc
      basis <- commodityCurve "HO basis" ho usd bbl cal dates [1.0, 1.0] dc
      before <- commodityCurveBasisOfCurve curve
      isNothing before `shouldBe` True
      setCommodityCurveBasisOfCurve curve basis
      found <- commodityCurveBasisOfCurve curve
      isJust found `shouldBe` True

    it "prices at a node date via forward-flat interpolation, plus any chained basis price" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let d0 = 1 `january` 2024
          d1 = 1 `february` 2024
      curve <- commodityCurve "HO curve" ho usd bbl cal [d0, d1] [70.0, 71.0] dc
      p0 <- commodityCurvePrice curve d0
      p0 `shouldBe` 70.0
      basis <- commodityCurve "HO basis" ho usd bbl cal [d0, d1] [1.0, 1.0] dc
      setCommodityCurveBasisOfCurve curve basis
      p0' <- commodityCurvePrice curve d0
      p0' `shouldBe` 71.0
      basisPrice <- commodityCurveBasisOfPrice curve d0
      basisPrice `shouldBe` 1.0

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
