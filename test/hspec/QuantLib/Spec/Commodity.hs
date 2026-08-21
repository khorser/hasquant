module QuantLib.Spec.Commodity (spec) where

import Test.Hspec

import Data.Time.Calendar(addDays)
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, adjust, CalendarConstructor(..), BusinessDayConvention(..))
import QuantLib.Commodity

spec :: Spec
spec = do
  describe "CommodityType" $ do
    it "round-trips code/name" $ do
      ho <- commodityType "HO" "Heating Oil"
      commodityTypeCode ho `shouldBe` "HO"
      commodityTypeName ho `shouldBe` "Heating Oil"
      commodityTypeEmpty ho `shouldBe` False

    it "equality is by code" $ do
      ho1 <- commodityType "HO" "Heating Oil"
      ho2 <- commodityType "HO" "Heating Oil (again)"
      wti <- commodityType "CL" "WTI Crude"
      ho1 `shouldBe` ho2
      ho1 `shouldNotBe` wti

    it "has a fixed null placeholder" $ do
      n1 <- nullCommodityType
      n2 <- nullCommodityType
      n1 `shouldBe` n2
      commodityTypeCode n1 `shouldBe` "<NULL>"

  describe "UnitOfMeasure" $ do
    it "round-trips name/code/type" $ do
      u <- unitOfMeasure "Barrels" "BBL" Volume
      unitOfMeasureName u `shouldBe` "Barrels"
      unitOfMeasureCode u `shouldBe` "BBL"
      unitOfMeasureType u `shouldBe` Volume
      unitOfMeasureEmpty u `shouldBe` False

    it "equality is by code" $ do
      u1 <- unitOfMeasure "Barrels" "BBL" Volume
      u2 <- unitOfMeasure "Barrels (again)" "BBL" Volume
      u1 `shouldBe` u2

    it "renames the Quantity tag to QuantityUnit to avoid clashing with the Quantity class" $ do
      u <- unitOfMeasure "Lots" "LOT" QuantityUnit
      unitOfMeasureType u `shouldBe` QuantityUnit

    it "has the petroleum and lot predefined units, each with the expected code" $ do
      lot <- lotUnitOfMeasure
      bbl <- barrelUnitOfMeasure
      mt <- mtUnitOfMeasure
      mb <- mbUnitOfMeasure
      gal <- gallonUnitOfMeasure
      litre <- litreUnitOfMeasure
      kl <- kilolitreUnitOfMeasure
      tkl <- tokyoKilolitreUnitOfMeasure
      map unitOfMeasureCode [lot, bbl, mt, mb, gal, litre, kl, tkl]
        `shouldBe` ["Lot", "BBL", "MT", "MB", "GAL", "l", "kl", "KL_tk"]

  describe "PaymentTerm" $ do
    it "round-trips name/eventType/offsetDays/calendar" $ do
      cal <- calendar BrazilSettlement
      pt <- paymentTerm "Pricing end + 5 days" PricingDate 5 cal
      paymentTermName pt `shouldBe` "Pricing end + 5 days"
      paymentTermEventType pt `shouldBe` PricingDate
      paymentTermOffsetDays pt `shouldBe` 5
      paymentTermEmpty pt `shouldBe` False
      cal' <- paymentTermCalendar pt
      show cal' `shouldBe` show cal

    it "computes the payment date as the calendar-adjusted offset" $ do
      cal <- calendar BrazilSettlement
      pt <- paymentTerm "Trade + 2 days" TradeDate 2 cal
      let d = 3 `january` 2024
      expected <- adjust cal (addDays 2 d) Following
      paymentTermGetPaymentDate pt d `shouldReturn` expected
