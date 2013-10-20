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

  , immCode
  , immDate
  , isIMMcode
  , isIMMdate
  , nextIMMCode
  , nextIMMCode'
  , nextIMMDate
  , nextIMMDate'
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

today :: IO Day
today = do
  now <- getCurrentTime
  tz <- getTimeZone now
  return $ localDay $ utcToLocalTime tz now

-- |One-based (Jan 1st = 1)
dayOfYear :: Day -> Int
dayOfYear = $(ffiCall 'dayOfYear) c_dayOfYear

foreign import ccall safe "ql.h qlDateDayOfYear"
  c_dayOfYear :: CDate -> CInt

-- |last day of the month to which the given date belongs
endOfMonth :: Day -> Day
endOfMonth = $(ffiCall 'endOfMonth) c_endOfMonth

foreign import ccall safe "ql.h qlDateEndOfMonth"
  c_endOfMonth :: CDate -> CDate

-- |whether a date is the last day of its month
isEndOfMonth :: Day -> Bool
isEndOfMonth = $(ffiCall 'isEndOfMonth) c_isEndOfMonth

foreign import ccall safe "ql.h qlDateIsEndOfMonth"
  c_isEndOfMonth :: CDate -> CInt

-- |next given weekday following or equal to the given date
-- E.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002.see http://www.cpearson.com/excel/DateTimeWS.htm
nextWeekday :: Day -- ^d
  -> Weekday -- ^w
  -> Day
nextWeekday = $(ffiCall 'nextWeekday) c_nextWeekday

foreign import ccall safe "ql.h qlDateNextWeekday"
  c_nextWeekday :: CDate -> CInt -> CDate

-- |n-th given weekday in the given month and year
-- E.g., the 4th Thursday of March, 1998 was March 26th, 1998.see http://www.cpearson.com/excel/DateTimeWS.htm
nthWeekday :: Word -- ^n
  -> Weekday -- ^w
  -> Month -- ^m
  -> Int -- ^y
  -> Day
nthWeekday = $(ffiCall 'nthWeekday) c_nthWeekday

foreign import ccall safe "ql.h qlDateNthWeekday"
  c_nthWeekday :: CUInt -> CInt -> CInt -> CInt -> CDate

-- |returns the IMM code for the given date (e.g. H3 for March 20th, 2013). /Warning/ It raises an exception if the input date is not an IMM date
immCode :: Day -- ^immDate
  -> IO String
immCode = $(ffiCallX 'immCode) c_immCode

foreign import ccall safe "ql.h qlIMMCode"
  c_immCode :: CDate -> Ptr CString -> IO CString

-- |returns the IMM date for the given IMM code (e.g. March 20th, 2013 for H3). /Warning/ It raises an exception if the input string is not an IMM code
immDate :: String -- ^immCode
  -> Day -- ^referenceDate
  -> Either String Day
immDate = $(ffiCallPureX 'immDate) c_immDate

foreign import ccall safe "ql.h qlIMMDate"
  c_immDate :: CString -> CDate -> Ptr CString -> IO CDate

-- |returns whether or not the given string is an IMM code
isIMMcode ::String -- ^in
  -> Bool -- ^mainCycle
  -> Bool
isIMMcode = $(ffiCallPure 'isIMMcode) c_isIMMcode

foreign import ccall safe "ql.h qlIMMIsIMMcode"
  c_isIMMcode :: CString -> CInt -> IO CInt

-- |returns whether or not the given date is an IMM date
isIMMdate :: Day -- ^d
  -> Bool -- ^mainCycle
  -> Bool
isIMMdate = $(ffiCall 'isIMMdate) c_isIMMdate

foreign import ccall safe "ql.h qlIMMIsIMMdate"
  c_isIMMdate :: CDate -> CInt -> CInt

-- |next IMM code following the given code
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
nextIMMCode' :: String -- ^immCode
  -> Bool -- ^mainCycle
  -> Day -- ^referenceDate
  -> Either String String
nextIMMCode' = $(ffiCallPureX 'nextIMMCode') c_nextIMMCode'

foreign import ccall safe "ql.h qlIMMNextCode1"
  c_nextIMMCode' :: CString -> CInt -> CDate -> Ptr CString -> IO CString

-- |next IMM code following the given date
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
nextIMMCode :: Day -- ^d
  -> Bool -- ^mainCycle
  -> String
nextIMMCode = $(ffiCallPure 'nextIMMCode) c_nextIMMCode

foreign import ccall safe "ql.h qlIMMNextCode"
  c_nextIMMCode :: CDate -> CInt -> IO CString

-- |next IMM date following the given IMM code
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
nextIMMDate' :: String -- ^immCode
  -> Bool -- ^mainCycle
  -> Day -- ^referenceDate
  -> Either String Day
nextIMMDate' = $(ffiCallPureX 'nextIMMDate') c_nextIMMDate'

foreign import ccall safe "ql.h qlIMMNextDate1"
  c_nextIMMDate' :: CString -> CInt -> CDate -> Ptr CString -> IO CDate

-- |next IMM date following the given date
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
nextIMMDate :: Day -- ^d
  -> Bool -- ^mainCycle
  -> Day
nextIMMDate = $(ffiCall 'nextIMMDate) c_nextIMMDate

foreign import ccall safe "ql.h qlIMMNextDate"
  c_nextIMMDate :: CDate -> CInt -> CDate

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
