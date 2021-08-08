module QuantLib.Date
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
  , BusinessDayConvention(..)
  , DateGenerationRule(..)
  , ImmMonth(..)

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

  , endOfMonth
  , isEndOfMonth
  , nextWeekday
  , nthWeekday

  , immCode
  , immDate
  , isIMMCode
  , isIMMDate
  , nextIMMCode
  , nextIMMCode'
  , nextIMMDate
  , nextIMMDate'

  , addPeriod

  , addECBDate
  , ecbCode
  , ecbDate'
  , ecbDate
  , isECBCode
  , isECBDate
  , knownECBDates
  , nextECBCode'
  , nextECBCode
  , nextECBDate'
  , nextECBDate
  , nextECBDates'
  , nextECBDates
  , removeECBDate
  -- marshaling
  , fromDay
  , toDay
  , fromMaybeDay
  , toMaybeDay
  , peekDayArray
  , withDayArray
  )
where

import Foreign.C.Types(CInt, CUInt)
import Foreign.Ptr(Ptr)
import Foreign.Marshal.Array(withArray)

import Control.Exception(throwIO)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, toGregorian, isLeapYear, fromGregorian)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)

import QuantLib.Type(Error(DateConversion))
import QuantLib.Utility
import QuantLib.Period(TimeUnit)

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"

{#enum Month {} deriving(Show, Eq, Bounded) #}

{#enum Weekday {} deriving(Show, Eq, Bounded) #}

{#enum BusinessDayConvention {} deriving(Show, Eq, Bounded) #}

{#enum Rule as DateGenerationRule {} deriving(Show, Eq, Bounded) #}

{#enum ImmMonth {} deriving(Show, Eq, Bounded) #}

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

fromDay :: Day -> (CInt -> IO a) -> IO a
fromDay x f = toSerial x >>= f . fromIntegral

toDay :: CInt -> Day
toDay = fromSerial . fromIntegral

fromMaybeDay :: Maybe Day -> (CInt -> IO a) -> IO a
fromMaybeDay Nothing f = f 0
fromMaybeDay (Just x) f = fromDay x f

toMaybeDay :: Int -> Maybe Day
toMaybeDay 0 = Nothing
toMaybeDay x = Just $ fromSerial x

{#fun qlWeekday as weekday {fromDay* `Day'} -> `Weekday' #}

today :: IO Day
today = do
  now <- getCurrentTime
  tz <- getTimeZone now
  return $ localDay $ utcToLocalTime tz now

-- |One-based (Jan 1st = 1)
{#fun qlDateDayOfYear as dayOfYear {fromDay* `Day'} -> `Int' #}

-- |last day of the month to which the given date belongs
{#fun qlDateEndOfMonth as endOfMonth {fromDay* `Day'} -> `Day' toDay #}

-- |whether a date is the last day of its month
{#fun qlDateIsEndOfMonth as isEndOfMonth {fromDay* `Day'} -> `Bool' #}

-- |next given weekday following or equal to the given date
-- E.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002.see http://www.cpearson.com/excel/DateTimeWS.htm
{#fun qlDateNextWeekday as nextWeekday {fromDay* `Day', `Weekday'} -> `Day' toDay #}

-- |n-th given weekday in the given month and year
-- E.g., the 4th Thursday of March, 1998 was March 26th, 1998.see http://www.cpearson.com/excel/DateTimeWS.htm
{#fun qlDateNthWeekday as nthWeekday {fromIntegral `Word', `Weekday', `Month', `Int'} -> `Day' toDay #}

-- |returns the IMM code for the given date (e.g. H3 for March 20th, 2013). /Warning/ It raises an exception if the input date is not an IMM date
{#fun qlIMMCode as immCode {fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `String' peekDynString* #}

-- |returns the IMM date for the given IMM code (e.g. March 20th, 2013 for H3). /Warning/ It raises an exception if the input string is not an IMM code
{#fun qlIMMDate as immDate {`String', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |returns whether or not the given string is an IMM code, immCode -> mainCycle -> bool
{#fun pure qlIMMIsIMMcode as isIMMCode {`String', `Bool'} -> `Bool' #}

-- |returns whether or not the given date is an IMM date -> mainCycle -> bool
{#fun qlIMMIsIMMdate as isIMMDate {fromDay* `Day', `Bool'} -> `Bool' #}

-- |next IMM code following the given code
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextCode1 as nextIMMCode' {`String', `Bool', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `String' peekDynString* #}

-- |next IMM code following the given date
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextCode as nextIMMCode {fromDay* `Day', `Bool'} -> `String' peekDynString* #}

-- |next IMM date following the given IMM code
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextDate1 as nextIMMDate' {`String', `Bool', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |next IMM date following the given date
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextDate as nextIMMDate {fromDay* `Day', `Bool'} -> `Day' toDay #}

{#fun qlAddPeriod as addPeriod {fromDay* `Day', fromEnumQuantity `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

{#fun qlECBAddDate as addECBDate {fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

-- |returns the ECB code for the given date (e.g. MAR10 for March xxth, 2010).Warning It raises an exception if the input date is not an ECB date
{#fun qlECBCode as ecbCode {fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `String' peekDynString* #}

-- |returns the ECB date for the given ECB code (e.g. March xxth, 2013 for MAR10).WarningIt raises an exception if the input string is not an ECB code
{#fun qlECBDate1 as ecbDate' {`String', fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |maintenance period start date in the given month/year
{#fun qlECBDate as ecbDate {`Month', `Int', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |returns whether or not the given string is an ECB code
{#fun qlECBIsECBcode as isECBCode {`String', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

-- |returns whether or not the given date is a maintenance period start date
{#fun qlECBIsECBdate as isECBDate {fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

peekDayArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Day]
peekDayArray = peekIntArray (fromSerial . fromIntegral)

{#fun qlECBKnownDates as knownECBDates {preArray- `[Day]'& peekDayArray*, preErrorCheck- `String' errorCheck*-} -> `()' #}

-- |next ECB code following the given code
{#fun qlECBNextCode1 as nextECBCode' {`String', preErrorCheck- `String' errorCheck*-} -> `String' #}

-- |next ECB code following the given date
{#fun qlECBNextCode as nextECBCode {fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `String' #}

-- |next maintenance period start date following the given ECB code
{#fun qlECBNextDate1 as nextECBDate'{`String', fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |next maintenance period start date following the given date
{#fun qlECBNextDate as nextECBDate {fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |next maintenance period start dates following the given code
{#fun qlECBNextDates1 as nextECBDates' {`String', fromMaybeDay* `Maybe Day', preArray- `[Day]'& peekDayArray*, preErrorCheck- `String' errorCheck*-} -> `()' #}

{#fun qlECBNextDates as nextECBDates {fromMaybeDay* `Maybe Day', preArray- `[Day]'& peekDayArray*, preErrorCheck- `String' errorCheck*-} -> `()' #}

{#fun qlECBRemoveDate as removeECBDate {fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

withDayArray :: [Day] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withDayArray x f = do
  xs <- mapM toSerial x
  withArray (map fromIntegral xs) (\xs -> f (fromIntegral $ length x, xs))

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
