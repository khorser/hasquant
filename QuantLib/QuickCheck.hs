{-# OPTIONS_GHC -F -pgmF htfpp #-}
{-# LANGUAGE ScopedTypeVariables #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.QuickCheck(htf_thisModulesTests)

where

import Test.Framework

import Control.Exception(catch)
import Data.Time.Calendar(Day, fromGregorian)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)
import Prelude hiding(catch)

import Test.QuickCheck.Monadic

import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Error as Error
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import QuantLib.Time.Date
import qualified QuantLib.Time.Frequency as Frequency
import qualified QuantLib.Time.Period as Period
import qualified QuantLib.Time.Schedule as Schedule

today :: IO Day
today =
  do now <- getCurrentTime
     tz <- getTimeZone now
     return $ localDay $ utcToLocalTime tz now

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
       pre (isValid d1)
       d2 <- run $ setAndGetEvaluationDate d1
       assert $ d1 == d2

prop_invalidEvaluationDate :: Day -> Property
prop_invalidEvaluationDate d =
  not (isValid d)
    ==> monadicIO
          $ do t <- run today
               _ <- run $ Settings.setEvaluationDate (Just t)
               d2 <- run $ setAndGetEvaluationDateWithExceptions d
               assert $ t == d2

prop_singleLegStartDate :: (Double, Day) -> Property
prop_singleLegStartDate flow@(_, d) =
  isValid d
    ==> monadicIO
          $ do l <- run $ Leg.leg [flow]
               assert $ d == Leg.startDate l

prop_legStartDate :: [(Double, Day)] -> Property
prop_legStartDate flows =
  not (null flows) && all isValid (map snd flows)
    ==> monadicIO
          $ do l <- run $ Leg.leg flows
               assert $ minimum (map snd flows) == Leg.startDate l

prop_quoteValue :: Double -> Property
prop_quoteValue val =
  val > 0
    ==> monadicIO
          $ do q <- run $ Quote.simpleQuote val
               assert $ Quote.value q == val

prop_scheduleDates :: [Day] -> Property
prop_scheduleDates dates =
  all isValid dates
    ==> monadicIO
      $ do c <- run Calendar.russia
           s <- run $ Schedule.schedule' dates c BusinessDayConvention.Unadjusted
           assert $ dates == Schedule.dates s

instance Arbitrary Frequency.Frequency where
  arbitrary = arbitraryBoundedEnum

prop_frequencyFromPeriodFromFrequency :: Frequency.Frequency -> Property
prop_frequencyFromPeriodFromFrequency freq =
  freq /= Frequency.OtherFrequency
    ==> monadicIO
      $ do p <- run $ Period.fromFrequency freq
           assert $ Period.toFrequency p == freq

-- Main --
--main :: IO ()
--main = do putStrLn $ "QuantLib version " ++ Utilities.version
--            ++ ", Boost " ++ Utilities.boostVersion
--          t <- today
--          putStrLn $ "Today is " ++ show (weekday t)
--          _ <- runTestTT $ test
--            [
--              settings
--              , date
--              , leg
--              , currency
--              , calendar
--              , dayCounter
--              , bond
--              , frequency
--              , schedule
--              , bondval
--            ]
--          -- if we don't do GC we have a chance of getting 
--          -- "could not notify one or more observers: year 2200 out of bounds"
--          -- from one of the outstanding rate helpers
--          -- when QuickCheck sets evaluation date to some border value like 27Nov2199
--          performGC
--          putStrLn "-- Done with HUnit --"
--          quickCheckWith stdArgs{maxSuccess = 500} prop_validEvaluationDate
--          quickCheck prop_invalidEvaluationDate
--          quickCheck prop_singleLegStartDate
--          quickCheckWith stdArgs{maxDiscardRatio = 20} prop_legStartDate
--          quickCheckWith stdArgs{maxDiscardRatio = 20} prop_scheduleDates
--          quickCheck prop_frequencyFromPeriodFromFrequency
--          quickCheckWith stdArgs{maxSuccess = 10} prop_quoteValue
--          return ()
