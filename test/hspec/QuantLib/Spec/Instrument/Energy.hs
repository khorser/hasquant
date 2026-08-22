module QuantLib.Spec.Instrument.Energy (spec) where

import Test.Hspec
import Data.Time.Calendar(addDays)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Yield(YieldTermStructure, flatForward)
import QuantLib.Commodity
import QuantLib.TermStructure.Commodity(commodityCurve)
import QuantLib.Index.Commodity(CommodityIndex, commodityIndex)
import QuantLib.Index(addFixing)
import QuantLib.Instrument(npv)
import QuantLib.Instrument.Energy

-- |A flat, zero-rate discount curve -- with pay/receive/discount legs all pointing at the same
-- curve, a swap's paid and received legs discount identically, so a zero @uDelta@ (the legs'
-- undiscounted difference) implies a zero NPV regardless of the curve's own rate (see CLAUDE.md's
-- TARF-style martingale-check precedent). Rate 0 just keeps the by-hand arithmetic trivial.
flatZeroCurve :: Day -> IO YieldTermStructure
flatZeroCurve evalDate = do
  q <- simpleQuote 0.0
  dc <- dayCounter Actual365FixedStandard
  flatForward evalDate q dc Continuous Annual

-- |A flat @price@ 'CommodityIndex' over @ct@\/@bbl@: one historical fixing well before
-- @evalDate@ (so every date in the pricing window below falls after 'lastQuoteDate' and is priced
-- off the forward curve, per energyvanillaswap.cpp's own per-day branch) backed by a forward curve
-- quoting the same flat @price@ across the whole window -- so every quote used anywhere in a
-- test is exactly @price@, regardless of which date it's fetched for.
flatIndex :: CommodityType -> UnitOfMeasure -> Day -> Double -> IO CommodityIndex
flatIndex ct bbl evalDate price = do
  usd <- commoditySettingsCurrency
  cal <- calendar Null
  curve <- commodityCurve "flat curve" ct usd bbl cal [evalDate, addDays 400 evalDate] [price, price]
             =<< dayCounter Actual365FixedStandard
  idx <- commodityIndex "flat index" ct usd bbl cal 1 (Just curve)
  addFixing idx (addDays (-30) evalDate) price False
  pure idx

spec :: Spec
spec = do
  describe "EnergyFuture" $ do
    it "nets to zero when the trade price matches the index's flat quote" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        ct <- commodityType "CL" "Crude Oil"
        bbl <- barrelUnitOfMeasure
        usd <- commoditySettingsCurrency
        idx <- flatIndex ct bbl evalDate 100
        fut <- energyFuture 1 (ct, bbl, 1000) (100, usd, bbl) idx ct []
        npv fut `shouldReturn` 0

    it "control: a below-market trade price nets to a positive, formula-predicted NPV" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        ct <- commodityType "CL" "Crude Oil"
        bbl <- barrelUnitOfMeasure
        usd <- commoditySettingsCurrency
        idx <- flatIndex ct bbl evalDate 100
        -- buySell=1, quantity 1000, trade price 90 vs a 100 flat quote, lot quantity 1:
        -- delta = (quote - tradePrice) * quantity * lotQuantity^2 * buySell = (100-90)*1000*1*1
        fut <- energyFuture 1 (ct, bbl, 1000) (90, usd, bbl) idx ct []
        npv fut `shouldReturn` 10000

  describe "EnergyVanillaSwap" $ do
    it "nets to zero (before financing cost) when the fixed price matches the flat floating quote" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        ct <- commodityType "CL" "Crude Oil"
        bbl <- barrelUnitOfMeasure
        usd <- commoditySettingsCurrency
        cal <- calendar Null
        idx <- flatIndex ct bbl evalDate 100
        ts <- flatZeroCurve evalDate
        let pp = pricingPeriod (addDays 10 evalDate) (addDays 14 evalDate) (addDays 20 evalDate) (ct, bbl, 1000)
        swp <- energyVanillaSwap True cal (100, usd) bbl idx usd usd [pp] ct [] ts ts ts
        npv swp `shouldReturn` 0

    it "control: paying a below-market fixed price nets to a positive NPV" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        ct <- commodityType "CL" "Crude Oil"
        bbl <- barrelUnitOfMeasure
        usd <- commoditySettingsCurrency
        cal <- calendar Null
        idx <- flatIndex ct bbl evalDate 100
        ts <- flatZeroCurve evalDate
        let pp = pricingPeriod (addDays 10 evalDate) (addDays 14 evalDate) (addDays 20 evalDate) (ct, bbl, 1000)
        swp <- energyVanillaSwap True cal (90, usd) bbl idx usd usd [pp] ct [] ts ts ts
        n <- npv swp
        n `shouldSatisfy` (> 0)

  describe "EnergyBasisSwap" $ do
    it "nets to zero (before financing cost) with a zero basis and matching flat quotes" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        ct <- commodityType "CL" "Crude Oil"
        bbl <- barrelUnitOfMeasure
        usd <- commoditySettingsCurrency
        cal <- calendar Null
        idx <- flatIndex ct bbl evalDate 100
        ts <- flatZeroCurve evalDate
        let pp = pricingPeriod (addDays 10 evalDate) (addDays 14 evalDate) (addDays 20 evalDate) (ct, bbl, 1000)
        swp <- energyBasisSwap cal idx idx idx True usd usd [pp] (0, usd, bbl) ct [] ts ts ts
        npv swp `shouldReturn` 0

    it "control: a nonzero basis added to the pay leg nets to a negative NPV" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        ct <- commodityType "CL" "Crude Oil"
        bbl <- barrelUnitOfMeasure
        usd <- commoditySettingsCurrency
        cal <- calendar Null
        idx <- flatIndex ct bbl evalDate 100
        ts <- flatZeroCurve evalDate
        let pp = pricingPeriod (addDays 10 evalDate) (addDays 14 evalDate) (addDays 20 evalDate) (ct, bbl, 1000)
        swp <- energyBasisSwap cal idx idx idx True usd usd [pp] (5, usd, bbl) ct [] ts ts ts
        n <- npv swp
        n `shouldSatisfy` (< 0)

  describe "createPricingPeriods" $ do
    it "splits a date range into monthly PerMonth periods, per the paymentTerm's offset" $ do
      ct <- commodityType "CL" "Crude Oil"
      bbl <- barrelUnitOfMeasure
      cal <- calendar Null
      pt <- paymentTerm "5 days after pricing end" PricingDate 5 cal
      let startDate = 1 `january` 2024
          endDate = 1 `april` 2024
      pps@(st: _) <- createPricingPeriods startDate endDate (ct, bbl, 100) DeliveryMonthly PerMonth pt
      length pps `shouldBe` 3
      pricingPeriodStartDate st `shouldBe` startDate

    it "silently returns no periods for a DeliverySchedule createPricingPeriods doesn't implement" $ do
      ct <- commodityType "CL" "Crude Oil"
      bbl <- barrelUnitOfMeasure
      cal <- calendar Null
      pt <- paymentTerm "5 days after pricing end" PricingDate 5 cal
      pps <- createPricingPeriods (1 `january` 2024) (1 `april` 2024) (ct, bbl, 100) DeliveryQuarterly PerQuarter pt
      pps `shouldBe` []

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
