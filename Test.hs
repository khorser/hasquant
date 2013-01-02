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

import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Error as Error
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Time.Calendar as Calendar
import qualified QuantLib.Time.Date as Date
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
      [False, True, False] ~=? Date.isLeap
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
    "GBP" ~: "GBP calendar name" ~:
      Calendar.name Calendar.londonStockExchange ~?= Calendar.name Calendar.gbp
  ]

bond :: Test
bond = TestList
  [
    "bond statics"
      ~: do l <- Leg.leg [(1000, fromGregorian 2013 1 1)] 
            b <- Bond.bond 2 Calendar.gbp 1000 m i l
            assertEqual "matirity date" m (Bond.maturityDate b)
            assertEqual "issue date" i (Bond.issueDate b)
  ]
  where i = fromGregorian 2012 1 1
        m = fromGregorian 2013 1 1

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

-- Main --
main :: IO ()
main = do putStrLn $ "QuantLib version " ++ Utilities.version
            ++ ", Boost " ++ Utilities.boostVersion
          _ <- runTestTT $ test [settings, date, leg, calendar, bond]
          quickCheckWith stdArgs{maxSuccess = 500} prop_validEvaluationDate
          quickCheck prop_invalidEvaluationDate
          quickCheck prop_singleLegStartDate
          --quickCheckWith stdArgs{maxDiscardRatio = 20} prop_legStartDate
          quickCheck prop_legStartDate
          return ()
