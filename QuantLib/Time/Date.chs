module QuantLib.Time.Date
  (
    Day
  , isValid
  , fromSerial
  , toSerial
  , minDate
  , maxDate
  , today
  , isLeap
  , year
  , month
  , weekday

  , Month(..)
  , Weekday(..)
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

  , dayOfYear
  )
where

import Control.Exception(throwIO)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, toGregorian, isLeapYear, fromGregorian)
import QuantLib.Types(Error(DateConversion))
import Foreign.C.Types(CInt)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)

#include "ql.h"

#include "qlEnum.h"

{#enum Month {} deriving(Show, Eq) #}

{#enum Weekday {} deriving(Show, Eq) #}

{#fun pure qlMinYear as minYear {} -> `Int' #}

{#fun pure qlMinMonth as minMonth {} -> `Int' #}

{#fun pure qlMinDay as minDay {} -> `Int' #}

{#fun pure qlMinDateSerialNumber as minDateSerialNumber {} -> `Int' #}

{#fun pure qlMaxDateSerialNumber as maxDateSerialNumber {} -> `Int' #}

-- |Julian day of the QuantLib zero date
qlStart :: Int
qlStart = minDateJulianDays - minDateSerialNumber
  where minDateJulianDays = toModifiedJulianDay' $ fromGregorian (fromIntegral minYear) (fromIntegral minMonth) (fromIntegral minDay)

toModifiedJulianDay' :: Day -> Int
toModifiedJulianDay' = fromIntegral . toModifiedJulianDay

fromSerial :: Int -> Day
fromSerial x = ModifiedJulianDay $ fromIntegral (x + qlStart)

isValid :: Day -> Bool
isValid x = s >= minDateSerialNumber && s <= maxDateSerialNumber
  where s = toModifiedJulianDay' x - qlStart

toSerial :: Day -> IO Int
toSerial x | isValid x = return $ toModifiedJulianDay' x - qlStart
           | otherwise = throwIO $ DateConversion x

year :: Day -> Int
year x = fromIntegral y where (y, _, _) = toGregorian x

-- |returns TRUE if the given date's year is leap
isLeap :: Day -> Bool
isLeap = isLeapYear . fromIntegral . year

month :: Day -> Month
month x = let (_, m, _) = toGregorian x in toEnum m

-- |helper function that is convenient for use as an infix operator
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

-- |earliest allowed date in QuantLib
minDate :: Day
minDate = fromSerial minDateSerialNumber

-- |latest date allowed in QuantLib
maxDate :: Day
maxDate = fromSerial maxDateSerialNumber

marshalDate :: Day -> (CInt -> IO a) -> IO a
marshalDate x f = toSerial x >>= f . fromIntegral

{#fun qlWeekday as weekday {marshalDate* `Day'} -> `Weekday' #}

today :: IO Day
today = do
  now <- getCurrentTime
  tz <- getTimeZone now
  return $ localDay $ utcToLocalTime tz now

{#fun qlDateDayOfYear as dayOfYear {marshalDate* `Day'} -> `Int' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
