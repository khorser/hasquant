{-# OPTIONS_GHC -F -pgmF htfpp #-}
{-# LANGUAGE ScopedTypeVariables #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.Test.QuickCheck(htf_thisModulesTests)

where

import Test.Framework

import Control.Exception(catch)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay)
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

newtype ValidDay = ValidDay{validDay::Day} deriving (Show, Eq)
newtype InvalidDay = InvalidDay Day deriving (Show, Eq)

instance Arbitrary ValidDay where
  arbitrary = do
    d <- elements [(toModifiedJulianDay minDate) .. (toModifiedJulianDay maxDate)]
    return $ ValidDay (ModifiedJulianDay d)

instance Arbitrary InvalidDay where
  arbitrary = do
    d <- elements $ [minD-500 .. minD-1] ++ [maxD+1 .. maxD+500]
    return $ InvalidDay (ModifiedJulianDay d)
    where minD = toModifiedJulianDay minDate
          maxD = toModifiedJulianDay maxDate

setAndGetEvaluationDate :: Day -> IO Day
setAndGetEvaluationDate d =
  do Settings.setEvaluationDate (Just d)
     Settings.evaluationDate

setAndGetEvaluationDateWithExceptions :: Day -> IO Day
setAndGetEvaluationDateWithExceptions d =
  do catch (Settings.setEvaluationDate (Just d))
           (\(_ :: Error.Error) -> return ())
     Settings.evaluationDate

prop_validDate :: ValidDay -> Bool
prop_validDate (ValidDay d) = isValid d

prop_invalidDate :: InvalidDay -> Bool
prop_invalidDate (InvalidDay d) = not $ isValid d

prop_validEvaluationDate :: Property
prop_validEvaluationDate = monadicIO
  $ do d1 <- pick arbitrary
       d2 <- run $ setAndGetEvaluationDate (validDay d1)
       assert $ validDay d1 == d2

prop_invalidEvaluationDate :: InvalidDay -> Property
prop_invalidEvaluationDate (InvalidDay d) =
  monadicIO
    $ do t <- run today
         _ <- run $ Settings.setEvaluationDate (Just t)
         -- TODO use assertThrowsIO
         d2 <- run $ setAndGetEvaluationDateWithExceptions d
         assert $ t == d2

prop_singleLegStartDate :: (Double, ValidDay) -> Property
prop_singleLegStartDate (a, ValidDay d) =
  monadicIO
    $ do  l <- run $ Leg.leg [(a, d)]
          assert $ d == Leg.startDate l

prop_legStartDate :: [(Double, ValidDay)] -> Property
prop_legStartDate flows =
  not (null flows)
    ==> monadicIO
          $ do l <- run $ Leg.leg f
               assert $ minimum ds == Leg.startDate l
        where (a, d) = unzip flows
              ds = map validDay d
              f = zip a ds

prop_quoteValue :: Double -> Property
prop_quoteValue val =
  val > 0
    ==> monadicIO
          $ do q <- run $ Quote.simpleQuote val
               assert $ Quote.value q == val

prop_scheduleDates :: [ValidDay] -> Property
prop_scheduleDates dates =
  monadicIO
      $ do c <- run Calendar.russia
           s <- run $ Schedule.schedule' (map validDay dates) c BusinessDayConvention.Unadjusted
           assert $ map validDay dates == Schedule.dates s

instance Arbitrary Frequency.Frequency where
  arbitrary = arbitraryBoundedEnum

prop_frequencyFromPeriodFromFrequency :: Frequency.Frequency -> Property
prop_frequencyFromPeriodFromFrequency freq =
  freq /= Frequency.OtherFrequency
    ==> monadicIO
      $ do p <- run $ Period.fromFrequency freq
           assert $ Period.toFrequency p == freq
