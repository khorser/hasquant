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

import qualified QuantLib.Date as Date(minDate, maxDate, isLeap, isValid)
import qualified QuantLib.Error as Error(Error(message))
import qualified QuantLib.Leg as Leg(leg, startDate)
import qualified QuantLib.Settings as Settings(evaluationDate,
  setEvaluationDate, enforceTodaysHistoricFixings,
  setEnforceTodaysHistoricFixings)
import qualified QuantLib.Utilities as Utilities(version, boostVersion)

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
      ~: do Settings.setEvaluationDate (fromGregorian 2012 12 29)
            t1 <- Settings.evaluationDate
            assertEqual "new valuation date" t1 (fromGregorian 2012 12 29)
  , "invalid evaluation date"
      ~: catch
          (do Settings.setEvaluationDate (fromGregorian 1861 1 1)
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

dates :: Test
dates = test
  [
    "min date" ~: "min date" ~:
      Date.minDate ~?= fromGregorian 1901 01 01
  , "max date" ~: "max date" ~:
      Date.maxDate ~?= fromGregorian 2199 12 31
  , "leap years" ~: "leap year" ~:
      [False, True, False] ~=? Date.isLeap
            [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5]
  ]

legs :: Test
legs = TestList
  [
    "single leg today"
      ~: do t <- today
            l <- Leg.leg [(100, t)] False
            assertEqual "today's leg start date" t (Leg.startDate l)
  , "two legs unsorted"
      ~: do t <- today
            l <- Leg.leg [(100, t), (-1000, addDays (-10) t)] False
            assertEqual "today's leg start date" (addDays (-10) t) (Leg.startDate l)
  , "three legs sorted"
      ~: do t <- today
            l <- Leg.leg [(100, t), (1000, addDays (-10) t), (-2000, addDays 10 t)] True
            assertEqual "today's leg start date" (addDays (-10) t) (Leg.startDate l)
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
  do Settings.setEvaluationDate d
     Settings.evaluationDate

setAndGetEvaluationDateWithExceptions :: Day -> IO Day
setAndGetEvaluationDateWithExceptions d =
  do catch (Settings.setEvaluationDate d)
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
               _ <- run $ Settings.setEvaluationDate t
               d2 <- run $ setAndGetEvaluationDateWithExceptions d
               assert $ t == d2

prop_singleLegStartDate :: (Double, Day) -> Bool -> Property
prop_singleLegStartDate flow@(_, d) s =
  Date.isValid d
    ==> monadicIO
          $ do l <- run $ Leg.leg [flow] s
               assert $ d == Leg.startDate l

prop_legStartDate :: [(Double, Day)] -> Bool -> Property
prop_legStartDate flows s =
  (not (null flows) && all Date.isValid (map snd flows))
    ==> monadicIO
          $ do l <- run $ Leg.leg flows s
               assert $ minimum (map snd flows) == Leg.startDate l

-- Main --
main :: IO ()
main = do putStrLn $ "QuantLib version " ++ Utilities.version
            ++ ", Boost " ++ Utilities.boostVersion
          _ <- runTestTT $ test [settings, dates, legs]
          quickCheckWith stdArgs{maxSuccess = 500} prop_validEvaluationDate
          quickCheck prop_invalidEvaluationDate
          quickCheck prop_singleLegStartDate
          --quickCheckWith stdArgs{maxDiscardRatio = 20} prop_legStartDate
          quickCheck prop_legStartDate
          return ()
