{-# OPTIONS_GHC -F -pgmF htfpp #-}
{-# LANGUAGE ScopedTypeVariables,CPP #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.Test.QuickCheck(htf_thisModulesTests, today)

where

import Test.Framework

import Control.Exception(catch)
#if __GLASGOW_HASKELL__ < 706
import Prelude hiding(catch)
#endif
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay)

import Test.QuickCheck.Monadic

import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Error as Error
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import QuantLib.Time.Date
import QuantLib.Time.Frequency
import qualified QuantLib.Time.Period as Period
import qualified QuantLib.Time.Schedule as Schedule
import qualified QuantLib.Types as Types

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
setAndGetEvaluationDate d = do
  Settings.setEvaluationDate (Just d)
  Settings.evaluationDate

setAndGetEvaluationDateWithExceptions :: Day -> IO Day
setAndGetEvaluationDateWithExceptions d = do
  catch (Settings.setEvaluationDate (Just d))
    (\(_ :: Error.Error) -> return ())
  Settings.evaluationDate

prop_ValidDate :: ValidDay -> Bool
prop_ValidDate (ValidDay d) = isValid d

prop_InvalidDate :: InvalidDay -> Bool
prop_InvalidDate (InvalidDay d) = not $ isValid d

prop_ValidEvaluationDate :: Property
prop_ValidEvaluationDate = monadicIO $ do
  d1 <- pick arbitrary
  d2 <- run $ setAndGetEvaluationDate (validDay d1)
  assert $ validDay d1 == d2

prop_InvalidEvaluationDate :: InvalidDay -> Property
prop_InvalidEvaluationDate (InvalidDay d) = monadicIO $ do
  t <- run today
  _ <- run $ Settings.setEvaluationDate (Just t)
  -- TODO use assertThrowsIO
  d2 <- run $ setAndGetEvaluationDateWithExceptions d
  assert $ t == d2

prop_SingleLegStartDate :: (Double, ValidDay) -> Property
prop_SingleLegStartDate (a, ValidDay d) = monadicIO $ do
  l <- run $ Leg.leg [(a, d)]
  let (Right sd) = Leg.startDate l
  assert $ d == sd

prop_LegStartDate :: [(Double, ValidDay)] -> Property
prop_LegStartDate flows =
  not (null flows)
  ==> monadicIO $ do
    l <- run $ Leg.leg f
    let (Right sd) = Leg.startDate l
    assert $ minimum ds == sd
    where (a, d) = unzip flows
          ds = map validDay d
          f = zip a ds

prop_QuoteValue :: Double -> Property
prop_QuoteValue val =
  val > 0
  ==> monadicIO $ do
    q <- run $ Quote.simpleQuote val >>= Types.asQuote
    v <- run $ Quote.value q
    assert $ v == val

prop_ScheduleDates :: [ValidDay] -> Property
prop_ScheduleDates dates = monadicIO $ do
  c <- run Calendar.russia
  s <- run $ Schedule.scheduleFromDays (map validDay dates) c BusinessDayConvention.Unadjusted
  assert $ map validDay dates == Schedule.dates s

instance Arbitrary Frequency where
  arbitrary = arbitraryBoundedEnum

prop_FrequencyFromPeriodFromFrequency :: Frequency -> Property
prop_FrequencyFromPeriodFromFrequency freq =
  freq /= OtherFrequency
  ==> monadicIO $ do
    p <- run $ Period.fromFrequency freq
    assert $ Period.toFrequency p == Right freq

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
