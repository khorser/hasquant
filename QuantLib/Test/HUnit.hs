{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.HUnit (htf_thisModulesTests)
where

import Test.Framework

import Control.Exception(catch)
import Data.List(zip4)
import Data.Time.Calendar(Day, fromGregorian, addDays)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)
import Prelude hiding(catch)
import System.Mem(performGC)

import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.CashFlow.CouponPricer as CouponPricer
import qualified QuantLib.Compounding as Compounding
import qualified QuantLib.Currency as Currency
import qualified QuantLib.Error as Error
import qualified QuantLib.Index as Index
import qualified QuantLib.Index.Ibor as Ibor
import qualified QuantLib.Instrument as Instrument
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.InterestRate as InterestRate
import qualified QuantLib.Math.Interpolation as Interpolation
import qualified QuantLib.PricingEngine as Pricing
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
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
import qualified QuantLib.Utilities as Utilities

today :: IO Day
today =
  do now <- getCurrentTime
     tz <- getTimeZone now
     return $ localDay $ utcToLocalTime tz now

test_evalDate :: IO ()
test_evalDate = do  t1 <- Settings.evaluationDate
                    t2 <- today
                    assertEqual t1 t2

test_nullEvalDate :: IO ()
test_nullEvalDate = do  Settings.setEvaluationDate $ Just (december 29 2012)
                        t0 <- Settings.evaluationDate
                        assertEqual t0 (fromGregorian 2012 12 29)
                        Settings.setEvaluationDate Nothing
                        t1 <- Settings.evaluationDate
                        t2 <- today
                        assertEqual t1 t2

test_defaultTodaysHistFixings :: IO ()
test_defaultTodaysHistFixings = do  e1 <- Settings.enforceTodaysHistoricFixings
                                    assertEqual e1 False

test_setTodaysHistFixings :: IO ()
test_setTodaysHistFixings = do  Settings.setEnforceTodaysHistoricFixings True
                                e1 <- Settings.enforceTodaysHistoricFixings
                                assertEqual e1 True

test_minDate :: IO ()
test_minDate = assertEqual minDate (fromGregorian 1901 01 01)

test_maxDate :: IO ()
test_maxDate = assertEqual maxDate (fromGregorian 2199 12 31)

test_leapYears :: IO ()
test_leapYears = assertEqual
                  [False, True, False]
                  (map isLeap [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5])

test_emptyLegStart :: IO ()
test_emptyLegStart = catch
                      (do l <- Leg.leg []
                          print $ Leg.startDate l
                          assertFailure "start date of empty leg didn't return an error")
                      (\e -> assertBool (not (null (Error.message e))))

test_singleLegToday :: IO ()
test_singleLegToday = do  t <- today
                          l <- Leg.leg [(100, t)]
                          assertEqual t (Leg.startDate l)

test_twoLegsUnsorted :: IO ()
test_twoLegsUnsorted = do t <- today
                          l <- Leg.leg [(100, t), (-1000, addDays (-10) t)]
                          assertEqual (addDays (-10) t) (Leg.startDate l)

test_threeLegsSorted :: IO ()
test_threeLegsSorted = do t <- today
                          l <- Leg.leg [(100, t), (1000, addDays (-10) t), (-2000, addDays 10 t)]
                          assertEqual (addDays (-10) t) (Leg.startDate l)

test_GBPCalendar :: IO ()
test_GBPCalendar = do c1 <- Calendar.londonStockExchange
                      c2 <- Calendar.gbp
                      assertEqual (Utilities.name c1) (Utilities.name c2)

test_calAdjust :: IO ()
test_calAdjust = do c <- Calendar.russia 
                    a <- Calendar.adjust
                            c
                            (fromGregorian 2012 12 22)
                            BusinessDayConvention.Preceding
                    assertEqual (fromGregorian 2012 12 21) a

test_calAdvance :: IO ()
test_calAdvance = do  c <- Calendar.russia 
                      a <- Calendar.advance
                            c
                            (fromGregorian 2012 12 20)
                            1
                            Unit.Months
                            BusinessDayConvention.Preceding
                            False
                      assertEqual (fromGregorian 2013 01 18) a
                              
test_currency :: IO ()
test_currency = do  c <- Currency.gbp
                    assertEqual "British pound sterling" (Utilities.name c)

test_a365fCounter :: IO ()
test_a365fCounter = do  c1 <- DayCounter.a365F
                        c2 <- DayCounter.actual365Fixed
                        assertEqual (Utilities.name c1) (Utilities.name c2)

test_bondStatics :: IO ()
test_bondStatics = do c <- Calendar.gbp
                      l <- Leg.leg [(1000, fromGregorian 2013 1 1)] 
                      b <- Bond.bond' 2 c 1000 m i l
                      assertEqual m (Bond.maturityDate b)
                      assertEqual i (Bond.issueDate b)
                   where i = Just (fromGregorian 2012 1 1)
                         m = Just (fromGregorian 2013 1 1)

test_specialBondStatics :: IO ()
test_specialBondStatics = do  c <- Calendar.gbp
                              l <- Leg.leg [] 
                              b <- Bond.bond 3 c Nothing l
                              assertEqual Nothing (Bond.issueDate b)

test_fixedBondWithWchedule :: IO ()
test_fixedBondWithWchedule = do c <- Calendar.russia
                                tenor <- Period.period 1 Unit.Months
                                s <- Schedule.schedule
                                  (Just $ fromGregorian 2012 12 20)
                                  (fromGregorian 2013 12 21)
                                  tenor
                                  c
                                  BusinessDayConvention.Following
                                  BusinessDayConvention.Unadjusted
                                  DateGenerationRule.Forward
                                  False
                                  (Just $ fromGregorian 2012 12 21)
                                  (Just $ fromGregorian 2013 12 21)
                                cnt <- DayCounter.actual365Fixed
                                b <- Bond.fixedRateBond
                                      1
                                      100
                                      s
                                      [3]
                                      cnt
                                      BusinessDayConvention.Following
                                      100
                                      (Just $ fromGregorian 2012 10 11)
                                      c
                                assertEqual (Just $ fromGregorian 2012 10 11) (Bond.issueDate b)
                                assertEqual (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
                                assertEqual Frequency.Monthly (Bond.frequency b)

test_fixedBondWithCalendars :: IO ()
test_fixedBondWithCalendars = do  c <- Calendar.russia
                                  tenor <- Period.period 1 Unit.Months
                                  cnt <- DayCounter.actual365Fixed
                                  b <- Bond.fixedRateBond'
                                    1
                                    c
                                    100
                                    (fromGregorian 2012 12 20)
                                    (fromGregorian 2013 12 21)
                                    tenor
                                    [0.12]
                                    cnt
                                    BusinessDayConvention.Following
                                    BusinessDayConvention.Unadjusted
                                    100
                                    (Just $ fromGregorian 2012 10 01)
                                    Nothing
                                    DateGenerationRule.Forward
                                    False
                                    c
                                  assertEqual (Just $ fromGregorian 2012 10 01) (Bond.issueDate b)
                                  assertEqual (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
                                  assertEqual Frequency.Monthly (Bond.frequency b)
test_fixedBond :: IO ()
test_fixedBond = do dc <- DayCounter.actual365Fixed
                    r1 <- InterestRate.interestRate 0.12 dc Compounding.Simple Frequency.Annual
                    r2 <- InterestRate.interestRate 0.125 dc Compounding.Simple Frequency.Monthly
                    cal <- Calendar.russia
                    tenor <- Period.period 6 Unit.Months
                    s <- Schedule.schedule
                      (Just (fromGregorian 2012 12 20))
                      (fromGregorian 2013 12 21)
                      tenor
                      cal
                      BusinessDayConvention.Following
                      BusinessDayConvention.Unadjusted
                      DateGenerationRule.Forward
                      False
                      (Just (fromGregorian 2012 12 21))
                      (Just (fromGregorian 2013 12 21))
                    b <- Bond.fixedRateBond''
                            3
                            100
                            s
                            [r1, r2]
                            BusinessDayConvention.Preceding
                            100
                            (Just (fromGregorian 2012 12 21))
                            cal
                    assertEqual (Just $ fromGregorian 2012 12 21) (Bond.issueDate b)
                    assertEqual (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
                    assertEqual Frequency.Semiannual (Bond.frequency b)

test_frequency :: IO ()
test_frequency = do p <- Period.period 1 Unit.Months
                    assertEqual Frequency.Monthly (Period.toFrequency p)

test_truncateSchedule :: IO ()
test_truncateSchedule = do  tenor <- Period.period 1 Unit.Months
                            cal <- Calendar.russia
                            s <- Schedule.schedule
                              (Just $ 20 `december` 2012)
                              (21 `december` 2013)
                              tenor
                              cal
                              BusinessDayConvention.Following
                              BusinessDayConvention.Unadjusted
                              DateGenerationRule.Forward
                              False
                              (Just $ 21 `december` 2012)
                              (Just $ 21 `december` 2013)
                            truncated <- Schedule.until s (15 `april` 2013)
                            assertEqual [fromGregorian 2012 12 20,
                                         fromGregorian 2012 12 21,
                                         fromGregorian 2013 01 21,
                                         fromGregorian 2013 02 21,
                                         fromGregorian 2013 03 21,
                                         fromGregorian 2013 04 15]
                                        (Schedule.dates truncated)

test_bondEval :: IO ()
test_bondEval = do  actual365Fixed <- DayCounter.actual365Fixed
                    actActBond <- DayCounter.actualActualBond
                    actActISDA <- DayCounter.actualActualISDA
                    actual360 <- DayCounter.actual360
                    thirty360European <- DayCounter.thirty360European
        
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
                      (\(q, p) -> do tenor <- Period.period p Unit.Months
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
                    p6m <- Period.fromFrequency Frequency.Semiannual
                    discBondHelpers <- mapM
                      (\(q, c, i, m) -> do s <- Schedule.schedule
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
                            Yield.Discount
                            Interpolation.LogLinear
                            --(Interpolation.Cubic $ Interpolation.NaturalSpline True)
                            --(Interpolation.LogCubic $ Interpolation.Parabolic False)
                            --(Interpolation.LogCubic Interpolation.Kruger)
                            --(Interpolation.Cubic Interpolation.FritschButland)
                            --Interpolation.Abcd
                    --df <- Yield.discount ts (fromGregorian 2011 08 03) True
                    pricing <- Pricing.discountingBondEngine ts
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
                    Instrument.setPricingEngine fixedBond pricing
                    npv <- Instrument.npv fixedBond
                    assertBool $ abs(npv-107.67) < 0.01
                    zcBond <- Bond.zeroCouponBond settlementDays
                                                 usGovBondCal
                                                 faceAmount
                                                 (15 `august` 2013)
                                                 BusinessDayConvention.Following
                                                 116.92
                                                 (Just $ 15 `august` 2003)
                    Instrument.setPricingEngine zcBond pricing
                    znpv <- Instrument.npv zcBond
                    assertBool $ abs(znpv-100.92) < 0.01
        
                    depoLiborHelpers <-
                      mapM (\(q, (n, u)) ->
                        do quote <- Quote.simpleQuote q
                           p <- Period.period n u
                           Yield.depositRateHelper quote p fixingDays targetCal
                                                          BusinessDayConvention.ModifiedFollowing
                                                          True actual360)
                           $ zip liborDepoQuotes liborDepoTerms
        
                    eur6M <- Ibor.euribor p6m Nothing
                    spread <- Quote.simpleQuote 0
        
                    swapLiborHelpers <-
                      mapM (\(q, n) ->
                        do quote <- Quote.simpleQuote q
                           p <- Period.period n Unit.Years
                           p1d <- Period.period 1 Unit.Days
                           Yield.swapRateHelper' quote p targetCal Frequency.Annual BusinessDayConvention.Unadjusted
                                                 thirty360European eur6M spread p1d Nothing)
                            $ zip liborSwapQuotes liborSwapTerms
        
                    fwdCurve <- Yield.piecewiseYieldCurve
                                  settlementDate
                                  (depoLiborHelpers ++ swapLiborHelpers)
                                  actActISDA
                                  []
                                  tolerance
                                  Yield.Discount
                                  Interpolation.LogLinear
        
                    p3m <- Period.period 3 Unit.Months
                    usd3m <- Ibor.usdLibor p3m (Just fwdCurve)
                    Index.addFixing usd3m (fromGregorian 2008 07 17) 0.0278625 False
        
                    pq <- Period.fromFrequency Frequency.Quarterly
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
                    Instrument.setPricingEngine floater pricing
                    volval <- Quote.simpleQuote 0
                    vol <- Vol.constantOptionletVol settlementDays
                                                    targetCal
                                                    BusinessDayConvention.ModifiedFollowing
                                                    volval
                                                    actual365Fixed
                    couponPricer <- CouponPricer.blackIborCouponPricer vol
                    Bond.setCouponPricer floater couponPricer
        
                    fnpv <- Instrument.npv floater
                    assertBool $ abs(fnpv-102.36) < 0.01
         
                    -- putStrLn "\nData from QL Bond Example (QuantLib-1.2 on Windows x86):    100.92217820704442  107.66828913260436 102.35931459949133"
                    -- putStrLn "\nData from QL Bond Example (QuantLib-1.2.1 on Windows x86):  100.9221782070444  107.66828913260427  102.35931459949143"
                    -- putStrLn "\nData from QL Bond Example (QuantLib-1.2 on Linux x86-64):   100.92217820704460962 107.66828913260425793 102.35931459949132716
                    -- putStrLn "\nData from QL Bond Example (QuantLib-1.2.1 on Linux x86-64): 100.92217820704460962 107.66828913260425793 102.35931459949128453 
                    -- putStrLn $ "Ours: " ++ show [znpv, npv, fnpv]
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

test_final :: IO ()
test_final = do performGC
          -- if we don't do GC we have a chance of getting 
          -- "could not notify one or more observers: year 2200 out of bounds"
          -- from one of the outstanding rate helpers
          -- when QuickCheck sets evaluation date to some border value like 27Nov2199
