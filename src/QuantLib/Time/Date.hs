{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Date
  (
    minDate
  , maxDate

  , isLeap
  , isValid
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

  , dayOfYear
  , endOfMonth
  , isEndOfMonth
  , nextWeekday
  , nthWeekday
  )
where

import Data.Time.Calendar(fromGregorian, toGregorian, isLeapYear)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)

import QuantLib.Internal.Date
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Time.Weekday
import QuantLib.Time.Month

year :: Day -> Integer
year x = y where (y, _, _) = toGregorian x

-- |returns TRUE if the given date's year is leap. QuantLibXL: qlDateIsLeap
isLeap :: Day -> Bool
isLeap = isLeapYear . year

-- |earliest allowed date in QuantLib. QuantLibXL: qlDateMinDate
minDate :: Day
minDate = fromQlDate c_minDateSerialNumber

-- |latest date allowed in QuantLib. QuantLibXL: qlDateMaxDate
maxDate :: Day
maxDate = fromQlDate c_maxDateSerialNumber

weekday :: Day -> Weekday
weekday x = fromQlEnum (show ''Weekday) $ c_weekday (toQlDate x)

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

-- |One-based (Jan 1st = 1)
dayOfYear :: Day -> IO Int
dayOfYear = $(ffiCallX 'dayOfYear) c_dayOfYear

foreign import ccall safe "ql.h qlDateDayOfYear"
  c_dayOfYear :: CDate -> Ptr CString -> IO CInt

-- |last day of the month to which the given date belongs
endOfMonth :: Day
  -> Day -- ^d
  -> IO Day
endOfMonth = $(ffiCallX 'endOfMonth) c_endOfMonth

foreign import ccall safe "ql.h qlDateEndOfMonth"
  c_endOfMonth :: CDate -> CDate -> Ptr CString -> IO CDate

-- |whether a date is the last day of its month
isEndOfMonth :: Day
  -> Day -- ^d
  -> IO Bool
isEndOfMonth = $(ffiCallX 'isEndOfMonth) c_isEndOfMonth

foreign import ccall safe "ql.h qlDateIsEndOfMonth"
  c_isEndOfMonth :: CDate -> CDate -> Ptr CString -> IO CInt

-- |next given weekday following or equal to the given date
-- E.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002.see http://www.cpearson.com/excel/DateTimeWS.htm
nextWeekday :: Day
  -> Day -- ^d
  -> Weekday -- ^w
  -> IO Day
nextWeekday = $(ffiCallX 'nextWeekday) c_nextWeekday

foreign import ccall safe "ql.h qlDateNextWeekday"
  c_nextWeekday :: CDate -> CDate -> CInt -> Ptr CString -> IO CDate

-- |n-th given weekday in the given month and year
-- E.g., the 4th Thursday of March, 1998 was March 26th, 1998.see http://www.cpearson.com/excel/DateTimeWS.htm
nthWeekday :: Day
  -> Word -- ^n
  -> Weekday -- ^w
  -> Month -- ^m
  -> Int -- ^y
  -> IO Day
nthWeekday = $(ffiCallX 'nthWeekday) c_nthWeekday

foreign import ccall safe "ql.h qlDateNthWeekday"
  c_nthWeekday :: CDate -> CUInt -> CInt -> CInt -> CInt -> Ptr CString -> IO CDate
