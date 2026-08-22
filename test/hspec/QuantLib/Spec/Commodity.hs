module QuantLib.Spec.Commodity (spec) where

import Test.Hspec

import Data.Time.Calendar(addDays)
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, adjust, CalendarConstructor(..), BusinessDayConvention(..))
import QuantLib.Currency(code)
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

  describe "Quantity" $ do
    it "rounds the amount per the unit of measure's rounding convention, unit/type unchanged" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      let (ct, uom, amt) = roundedQuantity (ho, bbl, 1.006)
      amt `shouldBe` 1.0
      ct `shouldBe` ho
      uom `shouldBe` bbl

    it "considers equal-unit quantities with the same amount close" $ do
      nullCt <- nullCommodityType
      bbl <- barrelUnitOfMeasure
      close <- closeQuantity (nullCt, bbl, 1000) (nullCt, bbl, 1000) 42
      close `shouldBe` True

    it "throws comparing quantities in different units with no conversion setting configured" $ do
      nullCt <- nullCommodityType
      bbl <- barrelUnitOfMeasure
      gal <- gallonUnitOfMeasure
      closeQuantity (nullCt, bbl, 1) (nullCt, gal, 42) 42 `shouldThrow` anyException

  describe "UnitOfMeasureConversion" $ do
    it "round-trips source/target/commodityType/type/factor/code" $ do
      nullCt <- nullCommodityType
      mb <- mbUnitOfMeasure
      bbl <- barrelUnitOfMeasure
      conv <- unitOfMeasureConversion nullCt mb bbl 1000
      src <- unitOfMeasureConversionSource conv
      tgt <- unitOfMeasureConversionTarget conv
      ct <- unitOfMeasureConversionCommodityType conv
      src `shouldBe` mb
      tgt `shouldBe` bbl
      ct `shouldBe` nullCt
      unitOfMeasureConversionType conv `shouldBe` UomDirect
      unitOfMeasureConversionFactor conv `shouldBe` 1000

    it "converts a quantity from source to target" $ do
      nullCt <- nullCommodityType
      mb <- mbUnitOfMeasure
      bbl <- barrelUnitOfMeasure
      conv <- unitOfMeasureConversion nullCt mb bbl 1000
      (ct, uom, amt) <- convertQuantity conv (nullCt, mb, 1000)
      ct `shouldBe` nullCt
      uom `shouldBe` bbl
      amt `shouldBe` 1000000

    -- Ported from test-suite/commodityunitofmeasure.cpp's testDirect: a direct conversion built
    -- by hand must agree with the manager's pre-populated lookup for the same unit pair.
    it "agrees with the pre-populated manager lookup (ported testDirect, MB to BBL leg)" $ do
      nullCt <- nullCommodityType
      mb <- mbUnitOfMeasure
      bbl <- barrelUnitOfMeasure
      direct <- unitOfMeasureConversion nullCt mb bbl 1000
      actual <- convertQuantity direct (nullCt, mb, 1000)
      looked <- lookupUomConversion nullCt bbl mb UomDirect
      calc <- convertQuantity looked (nullCt, mb, 1000)
      isClose <- closeQuantity calc actual 42
      isClose `shouldBe` True

    it "agrees with the pre-populated manager lookup (ported testDirect, BBL to Gallon leg)" $ do
      nullCt <- nullCommodityType
      bbl <- barrelUnitOfMeasure
      gal <- gallonUnitOfMeasure
      direct <- unitOfMeasureConversion nullCt bbl gal 42
      actual <- convertQuantity direct (nullCt, gal, 1000)
      looked <- lookupUomConversion nullCt bbl gal UomDirect
      calc <- convertQuantity looked (nullCt, gal, 1000)
      isClose <- closeQuantity calc actual 42
      isClose `shouldBe` True

    it "chains two conversions sharing a common unit" $ do
      nullCt <- nullCommodityType
      mb <- mbUnitOfMeasure
      bbl <- barrelUnitOfMeasure
      gal <- gallonUnitOfMeasure
      mbToBbl <- unitOfMeasureConversion nullCt mb bbl 1000
      bblToGal <- unitOfMeasureConversion nullCt bbl gal 42
      chained <- chainUnitOfMeasureConversion mbToBbl bblToGal
      unitOfMeasureConversionType chained `shouldBe` UomDerived
      (_, uom, amt) <- convertQuantity chained (nullCt, mb, 1)
      uom `shouldBe` gal
      amt `shouldBe` 42000

  describe "UnitOfMeasureConversionManager" $ do
    it "resolves petroleum conversions via triangulation, pre-populated before any add" $ do
      nullCt <- nullCommodityType
      litre <- litreUnitOfMeasure
      gal <- gallonUnitOfMeasure
      conv <- lookupUomConversion nullCt litre gal UomDerived
      src <- unitOfMeasureConversionSource conv
      tgt <- unitOfMeasureConversionTarget conv
      [src, tgt] `shouldSatisfy` \l -> litre `elem` l && gal `elem` l

    it "add/clear round-trip: a direct conversion registered via addUomConversion is found by a\
       \ direct lookup, and clear discards it" $ do
      ho <- commodityType "HO" "Heating Oil"
      lot <- lotUnitOfMeasure
      bbl <- barrelUnitOfMeasure
      conv <- unitOfMeasureConversion ho lot bbl 500
      addUomConversion conv
      found <- lookupUomConversion ho lot bbl UomDirect
      unitOfMeasureConversionFactor found `shouldBe` 500
      clearUomConversions
      lookupUomConversion ho lot bbl UomDirect `shouldThrow` anyException

  describe "CommoditySettings" $ do
    it "defaults to USD and barrels, and round-trips a new setting" $ do
      origCcy <- commoditySettingsCurrency
      origUom <- commoditySettingsUnitOfMeasure
      code origCcy `shouldBe` "USD"
      unitOfMeasureCode origUom `shouldBe` "BBL"

      mt <- mtUnitOfMeasure
      setCommoditySettingsUnitOfMeasure mt
      commoditySettingsUnitOfMeasure `shouldReturn` mt
      setCommoditySettingsUnitOfMeasure origUom
      commoditySettingsUnitOfMeasure `shouldReturn` origUom
