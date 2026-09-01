module QuantLib.Spec.Index.Commodity (spec) where

import Test.Hspec
import Data.List.NonEmpty(fromList)

import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..))
import QuantLib.Index
import QuantLib.Index.Commodity
import QuantLib.Commodity
import QuantLib.TermStructure.Commodity

spec :: Spec
spec = do
  describe "CommodityIndex" $ do
    it "has no historical fixings and no forward price before any are added" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      idx <- commodityIndex "HO index" ho usd bbl cal 1000 Nothing
      commodityIndexEmpty idx `shouldBe` True

    it "forecasts a forward price from a forward curve" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      dc <- dayCounter Actual365FixedStandard
      let d0 = 1 `january` 2024
          d1 = 1 `february` 2024
      curve <- commodityCurve "HO curve" ho usd bbl cal (fromList [(d0, 70.0), (d1, 71.0)]) dc
      idx <- commodityIndex "HO index" ho usd bbl cal 1000 (Just curve)
      commodityIndexForwardPrice idx d0 `shouldReturn` 70.0

    it "stores and returns historical fixings via QuantLib.Index's generic addFixing/fixing" $ do
      ho <- commodityType "HO" "Heating Oil"
      bbl <- barrelUnitOfMeasure
      usd <- commoditySettingsCurrency
      cal <- calendar TARGET
      idx <- commodityIndex "HO index" ho usd bbl cal 1000 Nothing
      let d0 = 2 `january` 2024 -- a TARGET business day (Jan 1st is a holiday)
      addFixing idx d0 72.5 False
      commodityIndexEmpty idx `shouldBe` False
      commodityIndexLastQuoteDate idx `shouldReturn` d0
      fixing idx d0 False `shouldReturn` 72.5

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
