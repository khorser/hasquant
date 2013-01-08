{-# LANGUAGE ScopedTypeVariables #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module Main(main)
where

import Control.Exception(catch)
import Data.Time.Calendar(Day, fromGregorian, addDays)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)
import Prelude hiding(catch)

import Test.HUnit(runTestTT, test, assertEqual, (~:), (~?=), (~=?),
  Test(TestList), assertBool, assertFailure)
import Test.QuickCheck as QC(Arbitrary, elements, arbitrary, Property,
  quickCheck, quickCheckWith, (==>), stdArgs, Args(..))
import Test.QuickCheck.Monadic as QC(assert, monadicIO, pick, pre, run)

import QuantLib.Internal(name)
import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Currency as Currency
import qualified QuantLib.Error as Error
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import qualified QuantLib.Time.Date as Date
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

-- HUnit --
settings :: Test
settings = TestList
  [
    "evaluation date 1"
      ~: do t1 <- Settings.evaluationDate
            t2 <- today
            assertEqual "default valuation date" t1 t2
  , "evaluation date 2"
      ~: do Settings.setEvaluationDate $ Just (fromGregorian 2012 12 29)
            t1 <- Settings.evaluationDate
            assertEqual "new valuation date" t1 (fromGregorian 2012 12 29)
  , "null evaluation date"
      ~: do Settings.setEvaluationDate $ Just (fromGregorian 2012 12 29)
            t0 <- Settings.evaluationDate
            assertEqual "new valuation date" t0 (fromGregorian 2012 12 29)
            Settings.setEvaluationDate Nothing
            t1 <- Settings.evaluationDate
            t2 <- today
            assertEqual "new valuation date" t1 t2
  , "invalid evaluation date"
      ~: catch
          (do Settings.setEvaluationDate $ Just (fromGregorian 1861 1 1)
              assertFailure "invalid evaluation date passed through")
          (assertBool "exception message not empty" . not . null . Error.message)
  , "enforce today's historic fixings 1"
      ~: do e1 <- Settings.enforceTodaysHistoricFixings
            assertEqual "default enforce today's historic fixings" e1 False
  , "enforce today's historic fixings 2"
      ~: do Settings.setEnforceTodaysHistoricFixings True
            e1 <- Settings.enforceTodaysHistoricFixings
            assertEqual "new enforce today's historic fixings" e1 True
  ]

date :: Test
date = test
  [
    "min date" ~: "min date" ~:
      Date.minDate ~?= fromGregorian 1901 01 01
  , "max date" ~: "max date" ~:
      Date.maxDate ~?= fromGregorian 2199 12 31
  , "leap years" ~: "leap year" ~:
      [False, True, False] ~=? map Date.isLeap
            [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5]
  ]

leg :: Test
leg = TestList
  [
    "start date of an empty leg"
      ~: catch
          (do l <- Leg.leg []
              print $ Leg.startDate l
              assertFailure "start date of empty leg didn't return an error")
          (assertBool "exception message not empty" . not . null . Error.message)
  , "single leg today"
      ~: do t <- today
            l <- Leg.leg [(100, t)]
            assertEqual "today's leg start date" t (Leg.startDate l)
  , "two legs unsorted"
      ~: do t <- today
            l <- Leg.leg [(100, t), (-1000, addDays (-10) t)]
            assertEqual "today's leg start date" (addDays (-10) t) (Leg.startDate l)
  , "three legs sorted"
      ~: do t <- today
            l <- Leg.leg [(100, t), (1000, addDays (-10) t), (-2000, addDays 10 t)]
            assertEqual "today's leg start date" (addDays (-10) t) (Leg.startDate l)
  ]

calendar :: Test
calendar = TestList
  [
    "GBP" ~: do c1 <- Calendar.londonStockExchange
                c2 <- Calendar.gbp
                assertEqual "GBP calendar name" (name c1) (name c2)
  , "adjust" ~: do c <- Calendar.russia 
                   assertEqual "Russian Calendar adjust"
                              (fromGregorian 2012 12 21)
                              (Calendar.adjust c (fromGregorian 2012 12 22) BusinessDayConvention.Preceding)
  , "advance" ~: do c <- Calendar.russia 
                    assertEqual "Russian Calendar advance"
                              (fromGregorian 2013 01 18)
                              (Calendar.advance c (fromGregorian 2012 12 20) 1 Unit.Months BusinessDayConvention.Preceding False)
  ]

currency :: Test
currency = TestList
  [
    "GBP" ~: do c <- Currency.gbp
                assertEqual "GBP currency name " "British pound sterling" (name c)
  ]

dayCounter :: Test
dayCounter = TestList
  [
    "ACT/365" ~: do c1 <- DayCounter.a365F
                    c2 <- DayCounter.actual365Fixed
                    assertEqual "ACT/365 names" (name c1) (name c2)
  ]

bond :: Test
bond = TestList
  [
    "bond statics"
      ~: do c <- Calendar.gbp
            l <- Leg.leg [(1000, fromGregorian 2013 1 1)] 
            b <- Bond.bond' 2 c 1000 m i l
            assertEqual "matirity date" m (Bond.maturityDate b)
            assertEqual "issue date" i (Bond.issueDate b)
  , "special bond statics"
      ~: do c <- Calendar.gbp
            l <- Leg.leg [] 
            b <- Bond.bond 3 c Nothing l
            assertEqual "issue date" Nothing (Bond.issueDate b)
  , "fixed rate bond"
      ~: do c <- Calendar.russia
            tenor <- Period.period 1 Unit.Months
            s <- Schedule.schedule
              (Just (fromGregorian 2012 12 20))
              (fromGregorian 2013 12 21)
              tenor
              c
              BusinessDayConvention.Following
              BusinessDayConvention.Unadjusted
              DateGenerationRule.Forward
              False
              (Just (fromGregorian 2012 12 21))
              (Just (fromGregorian 2013 12 21))
            cnt <- DayCounter.actual365Fixed
            b <- Bond.fixedRateBond
                  1
                  100
                  s
                  [3]
                  cnt
                  BusinessDayConvention.Following
                  100
                  (Just $ fromGregorian 2012 10 01)
                  c
            assertEqual "issue date" (Just $ fromGregorian 2012 10 01) (Bond.issueDate b)
            assertEqual "maturity date" (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
            assertEqual "fixed rate bond frequency" Frequency.Monthly (Bond.frequency b)

  ]
  where i = Just (fromGregorian 2012 1 1)
        m = Just (fromGregorian 2013 1 1)

frequency :: Test
frequency = TestList
  [
    "period to frequency"
      ~: do p <- Period.period 1 Unit.Months
            f <- Period.toFrequency p
            assertEqual "Monthly frequency" f Frequency.Monthly
  , "period from frequency"
      ~: do p <- Period.fromFrequency Frequency.Annual
            f <- Period.toFrequency p
            assertEqual "Annual frequency" f Frequency.Annual
  ]

schedule :: Test
schedule = TestList
  [
    "schedule'"
      ~: do cal <- Calendar.russia
            s <- Schedule.schedule'
              [fromGregorian 2012 12 20, fromGregorian 2012 5 20]
              cal
              BusinessDayConvention.Following
            assertEqual "Schedule dates" [fromGregorian 2012 12 20, fromGregorian 2012 5 20] (Schedule.dates s)
  , "schedule truncation"
      ~: do tenor <- Period.period 1 Unit.Months
            cal <- Calendar.russia
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
            truncated <- Schedule.until s (fromGregorian 2013 4 15)
            assertEqual "Schedule dates" [fromGregorian 2012 12 20,
                                          fromGregorian 2012 12 21,
                                          fromGregorian 2013 01 21,
                                          fromGregorian 2013 02 21,
                                          fromGregorian 2013 03 21,
                                          fromGregorian 2013 04 15]
                                         (Schedule.dates truncated)
  ]


-- QuickCheck --
instance Arbitrary Day where
  arbitrary = do
    y <- elements [1900 .. 2300]
    m <- elements [1 .. 12]
    d <- elements [1 .. 31]
    return (fromGregorian y m d)

setAndGetEvaluationDate :: Day -> IO Day
setAndGetEvaluationDate d =
  do Settings.setEvaluationDate (Just d)
     Settings.evaluationDate

setAndGetEvaluationDateWithExceptions :: Day -> IO Day
setAndGetEvaluationDateWithExceptions d =
  do catch (Settings.setEvaluationDate (Just d))
           (\(_ :: Error.Error) -> return ())
     Settings.evaluationDate

prop_validEvaluationDate :: Property
prop_validEvaluationDate = monadicIO
  $ do d1 <- pick arbitrary
       pre (Date.isValid d1)
       d2 <- run $ setAndGetEvaluationDate d1
       assert $ d1 == d2

prop_invalidEvaluationDate :: Day -> Property
prop_invalidEvaluationDate d =
  not (Date.isValid d)
    ==> monadicIO
          $ do t <- run today
               _ <- run $ Settings.setEvaluationDate (Just t)
               d2 <- run $ setAndGetEvaluationDateWithExceptions d
               assert $ t == d2

prop_singleLegStartDate :: (Double, Day) -> Property
prop_singleLegStartDate flow@(_, d) =
  Date.isValid d
    ==> monadicIO
          $ do l <- run $ Leg.leg [flow]
               assert $ d == Leg.startDate l

prop_legStartDate :: [(Double, Day)] -> Property
prop_legStartDate flows =
  not (null flows) && all Date.isValid (map snd flows)
    ==> monadicIO
          $ do l <- run $ Leg.leg flows
               assert $ minimum (map snd flows) == Leg.startDate l

prop_quoteValue :: Double -> Property
prop_quoteValue val =
  val > 0
    ==> monadicIO
          $ do q <- run $ Quote.simpleQuote val
               assert $ Quote.value q == val


-- Main --
main :: IO ()
main = do putStrLn $ "QuantLib version " ++ Utilities.version
            ++ ", Boost " ++ Utilities.boostVersion
          _ <- runTestTT $ test
            [
              settings
              , date
              , leg
              , currency
              , calendar
              , dayCounter
              , bond
              , frequency
              , schedule
            ]
          quickCheckWith stdArgs{maxSuccess = 500} prop_validEvaluationDate
          quickCheck prop_invalidEvaluationDate
          quickCheck prop_singleLegStartDate
          --quickCheckWith stdArgs{maxDiscardRatio = 20} prop_legStartDate
          quickCheck prop_legStartDate
          quickCheckWith stdArgs{maxSuccess = 10} prop_quoteValue
          return ()
