module QuantLib.Example.Bond
  (
    Result(..)
  , result
  )
where

import Data.List(zip4)
import Data.Time.Calendar(Day, fromGregorian)

import qualified QuantLib.CashFlow.CouponPricer as CouponPricer
import qualified QuantLib.Compounding as Compounding
import qualified QuantLib.Index as Index
import qualified QuantLib.Index.Ibor as Ibor
import qualified QuantLib.Instrument as Instrument
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.Math.Interpolation as Interpolation
import qualified QuantLib.PricingEngine as Pricing
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import qualified QuantLib.TermStructure.Trait as Trait
import qualified QuantLib.TermStructure.Yield as Yield
import qualified QuantLib.TermStructure.Volatility as Vol
import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import QuantLib.Time.Date
import qualified QuantLib.Time.DateGenerationRule as DateGenerationRule
import qualified QuantLib.Time.DayCounter as DayCounter
import qualified QuantLib.Time.Frequency as Frequency
import qualified QuantLib.Time.Period as Period
import qualified QuantLib.Time.Schedule as Schedule
import qualified QuantLib.Time.Unit as Unit
import qualified QuantLib.Types as Types

data Result = Result
  { npv :: (Double, Double, Double)
  , cleanPrice :: (Double, Double, Double)
  , dirtyPrice :: (Double, Double, Double)
  , accruedAmount :: (Double, Double, Double)
  , previousCoupon :: (Double, Double)
  , nextCoupon :: (Double, Double)
  , yield :: (Double, Double, Double)
  , cleanPriceFromYield :: Double
  , yieldFromCleanPrice :: Double
  , nextCouponDate :: (Day, Day, Day)
  , tradable :: (Bool, Bool, Bool)
  }
  
listToTuple :: [a] -> (a, a)
listToTuple [x, y] = (x, y)
listToTuple _ = error "Invalid list"

listToTriple :: [a] -> (a, a, a)
listToTriple [x, y, z] = (x, y, z)
listToTriple _ = error "Invalid list"

result :: IO Result
result = do
  actual365Fixed <- DayCounter.actual365Fixed
  actActBond <- DayCounter.actualActualBond
  actActISDA <- DayCounter.actualActualISDA
  actual360 <- DayCounter.actual360
  thirty360European <- DayCounter.thirty360European
  
  p1d <- Period.period 1 Unit.Days
  p3m <- Period.period 3 Unit.Months
  pq <- Period.fromFrequency Frequency.Quarterly
  p6m <- Period.fromFrequency Frequency.Semiannual

  targetCal <- Calendar.target
  nyseCal <- Calendar.unitedStatesNYSE
  usGovBondCal <- Calendar.unitedStatesGovernmentBond
  nocal <- Calendar.noCalendar
  
  settlementDate <- Calendar.adjust targetCal
                                    (18 `september` 2008)
                                    BusinessDayConvention.Following
  todaysDate <- Calendar.advance  targetCal
                                  settlementDate
                                  (-(fromIntegral fixingDays))
                                  Unit.Days
                                  BusinessDayConvention.Following
                                  False
  Settings.setEvaluationDate (Just todaysDate)
  discDepoHelpers <- mapM
    (\(q, p) -> do
      tenor <- Period.period p Unit.Months
      rate <- Quote.simpleQuote q
      Yield.depositRateHelper
        rate
        tenor
        fixingDays
        targetCal
        BusinessDayConvention.ModifiedFollowing
        True
        actual365Fixed)
    $ zip zcQuotes zcTenors
  quotes <- mapM Quote.simpleQuote marketQuotes
  discBondHelpers <- mapM
    (\(q, c, i, m) -> do
      s <- Schedule.schedule
             i
             m
             p6m
             usGovBondCal
             BusinessDayConvention.Unadjusted
             BusinessDayConvention.Unadjusted
             DateGenerationRule.Backward
             False
             Nothing
             Nothing
      Yield.fixedRateBondHelper
        q
        settlementDays
        100.0
        s
        [c]
        actActBond
        BusinessDayConvention.Unadjusted
        redemption
        i)
    $ zip4 quotes couponRates issueDates maturities
  ts <- Yield.piecewiseYieldCurve
          settlementDate
          (discDepoHelpers ++ discBondHelpers)
          actActISDA
          []
          tolerance
          Trait.Discount
          Interpolation.LogLinear
          --(Interpolation.Cubic $ Interpolation.NaturalSpline True)
          --(Interpolation.LogCubic $ Interpolation.Parabolic False)
          --(Interpolation.LogCubic Interpolation.Kruger)
          --(Interpolation.Cubic Interpolation.FritschButland)
          --Interpolation.Abcd

  {-
  ts1 <- Yield.piecewiseYieldCurve'
          3
          targetCal
          (discDepoHelpers ++ discBondHelpers)
          actActISDA
          []
          tolerance
          Trait.Discount
          Interpolation.LogLinear
  -}

  --df <- Yield.discount ts (fromGregorian 2011 08 03) True
  pricing <- Pricing.discountingBondEngine ts Nothing
  -- Fixed 4.5% US Treasury Note
  fixedSchedule <- Schedule.schedule (Just (15 `may` 2007))
                                     (15 `may` 2017)
                                     p6m
                                     usGovBondCal
                                     BusinessDayConvention.Unadjusted
                                     BusinessDayConvention.Unadjusted
                                     DateGenerationRule.Backward
                                     False
                                     Nothing
                                     Nothing
  fixedBond <- Bond.fixedRateBond settlementDays
                                  faceAmount
                                  fixedSchedule
                                  [0.045]
                                  actActBond
                                  BusinessDayConvention.ModifiedFollowing
                                  100.0
                                  (Just (15 `may` 2007))
                                  nocal
  fbi <- Types.asBond fixedBond >>= Types.asInstrument
  Instrument.setPricingEngine fbi pricing
  fixnpv <- Instrument.npv fbi
  zcBond <- Bond.zeroCouponBond settlementDays
                               usGovBondCal
                               faceAmount
                               (15 `august` 2013)
                               BusinessDayConvention.Following
                               116.92
                               (Just $ 15 `august` 2003)
  Types.withInstrument zcBond $ flip Instrument.setPricingEngine pricing
  znpv <- Types.withInstrument zcBond Instrument.npv
  
  depoLiborHelpers <-
    mapM (\(q, (n, u)) ->
      do
        quote <- Quote.simpleQuote q
        p <- Period.period n u
        Yield.depositRateHelper quote p fixingDays targetCal
                                       BusinessDayConvention.ModifiedFollowing
                                       True actual360) $
          zip liborDepoQuotes liborDepoTerms
  
  eur6M <- Ibor.euribor6M Nothing
  spread <- Quote.simpleQuote 0
  
  swapLiborHelpers <-
    mapM (\(q, n) ->
      do
        quote <- Quote.simpleQuote q
        p <- Period.period n Unit.Years
        Yield.swapRateHelper' quote p targetCal Frequency.Annual BusinessDayConvention.Unadjusted
                              thirty360European eur6M spread p1d Nothing) $
          zip liborSwapQuotes liborSwapTerms
  
  fwdCurve <- Yield.piecewiseYieldCurve
                settlementDate
                (depoLiborHelpers ++ swapLiborHelpers)
                actActISDA
                []
                tolerance
                Trait.Discount
                Interpolation.LogLinear
  
  usd3m <- Ibor.usdLibor p3m (Just fwdCurve)
  Types.asIndex usd3m >>= (\i -> Index.addFixing i (fromGregorian 2008 07 17) 0.0278625 False)
  
  floatSchedule <- Schedule.schedule (Just $ fromGregorian 2005 10 21)
                                     (fromGregorian 2010 10 21)
                                     pq
                                     nyseCal
                                     BusinessDayConvention.Unadjusted
                                     BusinessDayConvention.Unadjusted
                                     DateGenerationRule.Backward
                                     True
                                     Nothing
                                     Nothing
  floater <- Bond.floatingRateBond settlementDays
                                   faceAmount
                                   floatSchedule
                                   usd3m
                                   actual360
                                   BusinessDayConvention.ModifiedFollowing
                                   2
                                   [1.0]
                                   [0.001]
                                   []
                                   []
                                   True
                                   100.0
                                   (Just $ fromGregorian 2005 10 21)
  Types.withInstrument floater $ flip Instrument.setPricingEngine pricing
  volval <- Quote.simpleQuote 0
  vol <- Vol.constantOptionletVol settlementDays
                                  targetCal
                                  BusinessDayConvention.ModifiedFollowing
                                  volval
                                  actual365Fixed
  couponPricer <- CouponPricer.blackIborCouponPricer vol
  Bond.setCouponPricer floater couponPricer
  
  fnpv <- Types.withInstrument floater Instrument.npv

  fb <- Types.asBond fixedBond
  let allBonds = [fb, zcBond, floater]
      twoBonds = [fb, floater]

  bCleanPrice <- mapM Bond.cleanPrice allBonds
  bDirtyPrice <- mapM Bond.dirtyPrice allBonds
  bAccruedAmount <- mapM (`Bond.accruedAmount` Nothing) allBonds
  bPreviousCoupon <- mapM (`Bond.previousCouponRate` Nothing) twoBonds
  bNextCoupon <- mapM (`Bond.nextCouponRate` Nothing) twoBonds

  bYield <- mapM
    (\b -> Bond.yield b actual360 Compounding.Compounded Frequency.Annual 1e-8 100)
    allBonds

  fCleanFromYield <- Bond.cleanPrice' floater (bYield!!2) actual360 Compounding.Compounded Frequency.Annual (Just settlementDate)
  fYieldFromClean <- Bond.yield' floater (bCleanPrice!!2) actual360 Compounding.Compounded Frequency.Annual (Just settlementDate) 1e-8 100

  bNextCouponDate <- mapM (`Bond.nextCashFlowDate` Nothing) allBonds
  
  bTradable <- mapM (`Bond.isTradable` (Just $ 10 `february` 2013)) allBonds

  return Result {
      npv = (fixnpv, znpv, fnpv)
    , cleanPrice = listToTriple bCleanPrice
    , dirtyPrice = listToTriple bDirtyPrice
    , accruedAmount = listToTriple bAccruedAmount
    , previousCoupon = listToTuple bPreviousCoupon
    , nextCoupon = listToTuple bNextCoupon
    , yield = listToTriple bYield
    , nextCouponDate = listToTriple bNextCouponDate
    , cleanPriceFromYield = fCleanFromYield
    , yieldFromCleanPrice = fYieldFromClean
    , tradable = listToTriple bTradable
    }

 where zcQuotes = [0.0096, 0.0145, 0.0194]
       zcTenors = [3, 6, 12]
       fixingDays = 3
       settlementDays = 3
       redemption = 100.0
       faceAmount = 100.0
       issueDates = map Just [
         fromGregorian 2005 03 15,
         fromGregorian 2005 06 15,
         fromGregorian 2006 06 30,
         fromGregorian 2002 11 15,
         fromGregorian 1987 05 15]
       maturities = [
         fromGregorian 2010 08 31,
         fromGregorian 2011 08 31,
         fromGregorian 2013 08 31,
         fromGregorian 2018 08 15,
         fromGregorian 2038 05 15]
       couponRates = [0.02375, 0.04625, 0.03125, 0.04000, 0.04500]
       marketQuotes = [100.390625, 106.21875, 100.59375, 101.6875, 102.140625]
       tolerance = 1.0e-15
       liborDepoQuotes = [0.043375, 0.031875, 0.0320375,
                             0.03385, 0.0338125, 0.0335125]
       liborDepoTerms = [(1, Unit.Weeks), (1, Unit.Months), (3, Unit.Months),
                         (6, Unit.Months), (9, Unit.Months), (1, Unit.Years)]
       liborSwapQuotes = [0.0295, 0.0323, 0.0359, 0.0412, 0.0433]
       liborSwapTerms = [2, 3, 5, 10, 15]
