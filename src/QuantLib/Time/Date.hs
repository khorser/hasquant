{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.Date
  (
    minDate
  , maxDate

  , isLeap
  , isValid
  , Weekday(..)
  , Month(..)
  , today

  , year
  , month
  , weekday

  , january
  , february
  , march
  , april
  , may
  , june
  , july
  , august
  , september
  , october
  , november
  , december
  )
where

import Data.Time.Calendar(fromGregorian, toGregorian, isLeapYear)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)

import Data.Typeable(Typeable)

import QuantLib.Internal.Enum
import QuantLib.Internal.Date
import QuantLib.Internal.Utils

instance QLEnum Weekday

year :: Day -> Integer
year x = y where (y, _, _) = toGregorian x

-- |returns TRUE if a year is leap (qlDateIsLeap), reimplemented in Haskell
isLeap :: Day -> Bool
isLeap = isLeapYear . year

data Weekday = Sunday | Monday | Tuesday | Wednesday | Thursday | Friday
  | Saturday
  deriving (Show, Eq, Enum, Typeable)

data Month = January | February | March | April | May | June | July | August
  | September | October | November | December
  deriving (Show, Eq, Enum, Typeable)

-- |returns the earliest date allowed in QuantLib (qlDateMinDate)
minDate :: Day
minDate = fromQlDate c_minDateSerialNumber

-- |returns the latest date allowed in QuantLib (qlDateMaxDate)
maxDate :: Day
maxDate = fromQlDate c_maxDateSerialNumber

weekday :: Day -> Weekday
weekday x = fromQlEnum $ c_weekday (toQlDate x)

month :: Day -> Month
month x = let (_, m, _) = toGregorian x in
              case m of
                1 -> January
                2 -> February
                3 -> March
                4 -> April
                5 -> May
                6 -> June
                7 -> July
                8 -> August
                9 -> September
                10 -> October
                11 -> November
                12 -> December
                _  -> signalError "Invalid month number in the date"

january :: Int -> Int -> Day
january d y = fromGregorian (fromIntegral y) 1 d

february :: Int -> Int -> Day
february d y = fromGregorian (fromIntegral y) 2 d

march :: Int -> Int -> Day
march d y = fromGregorian (fromIntegral y) 3 d

april :: Int -> Int -> Day
april d y = fromGregorian (fromIntegral y) 4 d

may :: Int -> Int -> Day
may d y = fromGregorian (fromIntegral y) 5 d

june :: Int -> Int -> Day
june d y = fromGregorian (fromIntegral y) 6 d

july :: Int -> Int -> Day
july d y = fromGregorian (fromIntegral y) 7 d

august :: Int -> Int -> Day
august d y = fromGregorian (fromIntegral y) 8 d

september :: Int -> Int -> Day
september d y = fromGregorian (fromIntegral y) 9 d

october :: Int -> Int -> Day
october d y = fromGregorian (fromIntegral y) 10 d

november :: Int -> Int -> Day
november d y = fromGregorian (fromIntegral y) 11 d

december :: Int -> Int -> Day
december d y = fromGregorian (fromIntegral y) 12 d

today :: IO Day
today =
  do now <- getCurrentTime
     tz <- getTimeZone now
     return $ localDay $ utcToLocalTime tz now
