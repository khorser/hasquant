{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.HUnit (htf_thisModulesTests)
where

import Test.Framework

import Data.Time.Calendar(fromGregorian, addDays)
import System.Mem(performGC)

import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Compounding as Compounding
import qualified QuantLib.Currency as Currency
import qualified QuantLib.Error as Error
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.InterestRate as InterestRate
import qualified QuantLib.Settings as Settings
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

import qualified QuantLib.Example.Bond as BondExample

{-# ANN module "HLint: ignore Use camelCase" #-}

test_evalDate :: IO ()
test_evalDate = do  t1 <- Settings.evaluationDate
                    t2 <- today
                    assertEqual t1 t2

test_nullEvalDate :: IO ()
test_nullEvalDate = do  Settings.setEvaluationDate $ Just (december 29 2012)
                        t0 <- Settings.evaluationDate
                        assertEqual t0 (fromGregorian 2012 12 29)
                        t2 <- today
                        Settings.setEvaluationDate Nothing
                        t1 <- Settings.evaluationDate
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
test_emptyLegStart = do l <- Leg.leg []
                        assertThrows (Leg.startDate l) (not . null . Error.message)

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
                      assertEqual (show c1) (show c2)

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
                    assertEqual "British pound sterling" (show c)

test_a365fCounter :: IO ()
test_a365fCounter = do  c1 <- DayCounter.a365F
                        c2 <- DayCounter.actual365Fixed
                        assertEqual (show c1) (show c2)

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
                                assertEqual (Just $ fromGregorian 2012 10 11) (Bond.issueDate $ Types.asBond b)
                                assertEqual (Just $ fromGregorian 2013 12 21) (Bond.maturityDate $ Types.asBond b)
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
                                  assertEqual (Just $ fromGregorian 2012 10 01) (Bond.issueDate $ Types.asBond b)
                                  assertEqual (Just $ fromGregorian 2013 12 21) (Bond.maturityDate $ Types.asBond b)
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
                    assertEqual (Just $ fromGregorian 2012 12 21) (Bond.issueDate $ Types.asBond b)
                    assertEqual (Just $ fromGregorian 2013 12 21) (Bond.maturityDate $ Types.asBond b)
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
test_bondEval = do  (fixnpv, znpv, fnpv) <- BondExample.npv
                    assertBool $ abs(fixnpv-107.6682891) < 1e-7
                    assertBool $ abs(znpv-100.9221782) < 1e-7
                    assertBool $ abs(fnpv-102.3593146) < 1e-7

test_final :: IO ()
test_final = performGC
          -- if we don't do GC we have a chance of getting 
          -- "could not notify one or more observers: year 2200 out of bounds"
          -- from one of the outstanding rate helpers
          -- when QuickCheck sets evaluation date to some border value like 27Nov2199
