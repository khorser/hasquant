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

  , marshalDay
  , unmarshalDay

  , marshalDay'
  , unmarshalDay'

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
--  , knownECBDates
  , nextECBCode'
  , nextECBCode
  , nextECBDate'
  , nextECBDate
--  , nextECBDates'
--  , nextECBDates
  , removeECBDate
  )
where

import Control.Exception(throwIO)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, toGregorian, isLeapYear, fromGregorian)
import QuantLib.Types(Error(DateConversion))
import Foreign.C.Types(CInt)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)

import QuantLib.Utility
import QuantLib.Period(marshalPeriod, TimeUnit)

#include "ql.h"

#include "qlEnum.h"

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

marshalDay :: Day -> (CInt -> IO a) -> IO a
marshalDay x f = toSerial x >>= f . fromIntegral

unmarshalDay :: CInt -> Day
unmarshalDay = fromSerial . fromIntegral

marshalDay' :: Maybe Day -> (CInt -> IO a) -> IO a
marshalDay' Nothing f = f 0
marshalDay' (Just x) f = marshalDay x f

unmarshalDay' :: Int -> Maybe Day
unmarshalDay' 0 = Nothing
unmarshalDay' x = Just $ fromSerial x

--withDays :: [Day] -> (CUInt -> Ptr CDate -> IO b) -> IO b
--withDays = withArrayULenTIO toSerial

{#fun qlWeekday as weekday {marshalDay* `Day'} -> `Weekday' #}

today :: IO Day
today = do
  now <- getCurrentTime
  tz <- getTimeZone now
  return $ localDay $ utcToLocalTime tz now

-- |One-based (Jan 1st = 1)
{#fun qlDateDayOfYear as dayOfYear {marshalDay* `Day'} -> `Int' #}

-- |last day of the month to which the given date belongs
{#fun qlDateEndOfMonth as endOfMonth {marshalDay* `Day'} -> `Day' unmarshalDay #}

-- |whether a date is the last day of its month
{#fun qlDateIsEndOfMonth as isEndOfMonth {marshalDay* `Day'} -> `Bool' #}

-- |next given weekday following or equal to the given date
-- E.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002.see http://www.cpearson.com/excel/DateTimeWS.htm
{#fun qlDateNextWeekday as nextWeekday {marshalDay* `Day', `Weekday'} -> `Day' unmarshalDay #}

-- |n-th given weekday in the given month and year
-- E.g., the 4th Thursday of March, 1998 was March 26th, 1998.see http://www.cpearson.com/excel/DateTimeWS.htm
{#fun qlDateNthWeekday as nthWeekday {fromIntegral `Word', `Weekday', `Month', `Int'} -> `Day' unmarshalDay #}

-- |returns the IMM code for the given date (e.g. H3 for March 20th, 2013). /Warning/ It raises an exception if the input date is not an IMM date
{#fun qlIMMCode as immCode {marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `String' unmarshalDynamicString* #}

-- |returns the IMM date for the given IMM code (e.g. March 20th, 2013 for H3). /Warning/ It raises an exception if the input string is not an IMM code
{#fun qlIMMDate as immDate {`String', marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

-- |returns whether or not the given string is an IMM code, immCode -> mainCycle -> bool
{#fun pure qlIMMIsIMMcode as isIMMCode {`String', `Bool'} -> `Bool' #}

-- |returns whether or not the given date is an IMM date -> mainCycle -> bool
{#fun qlIMMIsIMMdate as isIMMDate {marshalDay* `Day', `Bool'} -> `Bool' #}

-- |next IMM code following the given code
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextCode1 as nextIMMCode' {`String', `Bool', marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `String' unmarshalDynamicString* #}

-- |next IMM code following the given date
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextCode as nextIMMCode {marshalDay* `Day', `Bool'} -> `String' unmarshalDynamicString* #}

-- |next IMM date following the given IMM code
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextDate1 as nextIMMDate' {`String', `Bool', marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

-- |next IMM date following the given date
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
{#fun qlIMMNextDate as nextIMMDate {marshalDay* `Day', `Bool'} -> `Day' unmarshalDay #}

{#fun qlAddPeriod as addPeriod {marshalDay* `Day', marshalPeriod `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

{#fun qlECBAddDate as addECBDate {marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

-- |returns the ECB code for the given date (e.g. MAR10 for March xxth, 2010).Warning It raises an exception if the input date is not an ECB date
{#fun qlECBCode as ecbCode {marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `String' unmarshalDynamicString* #}

-- |returns the ECB date for the given ECB code (e.g. March xxth, 2013 for MAR10).WarningIt raises an exception if the input string is not an ECB code
{#fun qlECBDate1 as ecbDate' {`String', marshalDay'* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

-- |maintenance period start date in the given month/year
{#fun qlECBDate as ecbDate {`Month', `Int', preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

-- |returns whether or not the given string is an ECB code
{#fun qlECBIsECBcode as isECBCode {`String', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

-- |returns whether or not the given date is a maintenance period start date
{#fun qlECBIsECBdate as isECBDate {marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

{-
knownECBDates :: IO [Day]
knownECBDates = map fromQlDate <$> getArrayX c_knownECBDates

foreign import ccall safe "ql.h qlECBKnownDates"
  c_knownECBDates :: Ptr CUInt -> Ptr CString -> IO (Ptr CDate)
-}

-- |next ECB code following the given code
{#fun qlECBNextCode1 as nextECBCode' {`String', preErrorCheck- `String' errorCheck*-} -> `String' #}

-- |next ECB code following the given date
{#fun qlECBNextCode as nextECBCode {marshalDay'* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `String' #}

-- |next maintenance period start date following the given ECB code
{#fun qlECBNextDate1 as nextECBDate'{`String', marshalDay'* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

-- |next maintenance period start date following the given date
{#fun qlECBNextDate as nextECBDate {marshalDay'* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Day' unmarshalDay #}

{-
-- |next maintenance period start dates following the given code
nextECBDates' :: String -- ^ecbCode
  -> Maybe Day -- ^referenceDate
  -> IO [Day]
nextECBDates' c d = map fromQlDate <$>
  withCString c (\s -> withDay d (getArrayX . c_nextECBDates' s))

foreign import ccall safe "ql.h qlECBNextDates1"
  c_nextECBDates' :: CString -> CDate -> Ptr CUInt -> Ptr CString -> IO (Ptr CDate)

-- |next maintenance period start dates following the given date
nextECBDates :: Maybe Day -- ^d
  -> IO [Day]
nextECBDates d = map fromQlDate <$> do
  dd <- toQlDate d
  getArrayX $ c_nextECBDates dd

foreign import ccall safe "ql.h qlECBNextDates"
  c_nextECBDates :: CDate -> Ptr CUInt -> Ptr CString -> IO(Ptr CDate)
-}

{#fun qlECBRemoveDate as removeECBDate {marshalDay* `Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
