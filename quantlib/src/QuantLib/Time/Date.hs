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
  )
where

import Control.Applicative ((<$>))

import Data.Time.Calendar(fromGregorian, toGregorian, isLeapYear)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)
import Foreign.Marshal.Utils(fromBool, toBool)

import QuantLib.Error(QLError)
import QuantLib.Internal.Date
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Time.Month(Month(..))
import QuantLib.Time.Unit(Unit)
import QuantLib.Time.Weekday(Weekday)

year :: Day -> Integer
year x = y where (y, _, _) = toGregorian x

-- |returns TRUE if the given date's year is leap
isLeap :: Day -> Bool
isLeap = isLeapYear . year

-- |earliest allowed date in QuantLib
minDate :: Day
minDate = fromQlDate c_minDateSerialNumber

-- |latest date allowed in QuantLib
maxDate :: Day
maxDate = fromQlDate c_maxDateSerialNumber

weekday :: Day -> Either QLError Weekday
weekday x = purifyExceptions $ do
  d <- toQlDate x
  fromQlEnum (show ''Weekday) $ c_weekday d

foreign import ccall safe "ql.h qlWeekday"
  c_weekday :: CInt -> CInt

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
                _  -> error "Invalid month number in the date" -- unreachable

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
dayOfYear :: Day -> Either QLError Int
dayOfYear x = purifyExceptions $ fromIntegral <$> c_dayOfYear <$> toQlDate x

foreign import ccall safe "ql.h qlDateDayOfYear"
  c_dayOfYear :: CDate -> CInt

-- |last day of the month to which the given date belongs
endOfMonth :: Day -> Either QLError Day
endOfMonth x = purifyExceptions $ fromQlDate <$> c_endOfMonth <$> toQlDate x

foreign import ccall safe "ql.h qlDateEndOfMonth"
  c_endOfMonth :: CDate -> CDate

-- |whether a date is the last day of its month
isEndOfMonth :: Day -> Either QLError Bool
isEndOfMonth x = purifyExceptions $ toBool <$> do
  dd <- toQlDate x
  return $ c_isEndOfMonth dd

foreign import ccall safe "ql.h qlDateIsEndOfMonth"
  c_isEndOfMonth :: CDate -> CInt

-- |next given weekday following or equal to the given date
-- E.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002.see http://www.cpearson.com/excel/DateTimeWS.htm
nextWeekday :: Day -- ^d
  -> Weekday -- ^w
  -> Either QLError Day
nextWeekday d w = purifyExceptions $ do
  dd <- toQlDate d
  ww <- toQlEnum (show $ ''Weekday) w
  return $ fromQlDate $ c_nextWeekday dd ww

foreign import ccall safe "ql.h qlDateNextWeekday"
  c_nextWeekday :: CDate -> CInt -> CDate

-- |n-th given weekday in the given month and year
-- E.g., the 4th Thursday of March, 1998 was March 26th, 1998.see http://www.cpearson.com/excel/DateTimeWS.htm
nthWeekday :: Word -- ^n
  -> Weekday -- ^w
  -> Month -- ^m
  -> Int -- ^y
  -> Day
nthWeekday = $(ffiCallPure 'nthWeekday) c_nthWeekday

foreign import ccall safe "ql.h qlDateNthWeekday"
  c_nthWeekday :: CUInt -> CInt -> CInt -> CInt -> IO CDate

-- |returns the IMM code for the given date (e.g. H3 for March 20th, 2013). /Warning/ It raises an exception if the input date is not an IMM date
immCode :: Day -- ^immDate
  -> Either QLError String
immCode = $(ffiCallPureX 'immCode) c_immCode

foreign import ccall safe "ql.h qlIMMCode"
  c_immCode :: CDate -> Ptr CString -> IO CString

-- |returns the IMM date for the given IMM code (e.g. March 20th, 2013 for H3). /Warning/ It raises an exception if the input string is not an IMM code
immDate :: String -- ^immCode
  -> Day -- ^referenceDate
  -> Either QLError Day
immDate = $(ffiCallPureX 'immDate) c_immDate

foreign import ccall safe "ql.h qlIMMDate"
  c_immDate :: CString -> CDate -> Ptr CString -> IO CDate

-- |returns whether or not the given string is an IMM code
isIMMCode ::String -- ^in
  -> Bool -- ^mainCycle
  -> Bool
isIMMCode = $(ffiCallPure 'isIMMCode) c_isIMMCode

foreign import ccall safe "ql.h qlIMMIsIMMcode"
  c_isIMMCode :: CString -> CInt -> IO CInt

-- |returns whether or not the given date is an IMM date
isIMMDate :: Day -- ^d
  -> Bool -- ^mainCycle
  -> Either QLError Bool
isIMMDate d b = purifyExceptions $ do
  dd <- toQlDate d
  return $ toBool $ c_isIMMDate dd (fromBool b)

foreign import ccall safe "ql.h qlIMMIsIMMdate"
  c_isIMMDate :: CDate -> CInt -> CInt

-- |next IMM code following the given code
-- returns the IMM code for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
nextIMMCode' :: String -- ^immCode
  -> Bool -- ^mainCycle
  -> Day -- ^referenceDate
  -> Either QLError String
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
  -> Either QLError Day
nextIMMDate' = $(ffiCallPureX 'nextIMMDate') c_nextIMMDate'

foreign import ccall safe "ql.h qlIMMNextDate1"
  c_nextIMMDate' :: CString -> CInt -> CDate -> Ptr CString -> IO CDate

-- |next IMM date following the given date
-- returns the 1st delivery date for next contract listed in the International Money Market section of the Chicago Mercantile Exchange.
nextIMMDate :: Day -- ^d
  -> Bool -- ^mainCycle
  -> Either QLError Day
nextIMMDate d b = purifyExceptions $ do
  dd <- toQlDate d
  return $ fromQlDate $ c_nextIMMDate dd (fromBool b)

foreign import ccall safe "ql.h qlIMMNextDate"
  c_nextIMMDate :: CDate -> CInt -> CDate

addPeriod :: Day -> (Int, Unit) -> Either QLError Day
addPeriod = $(ffiCallPureX 'addPeriod) c_addPeriod

foreign import ccall safe "ql.h qlAddPeriod"
  c_addPeriod :: CDate -> CInt -> CInt -> Ptr CString -> IO CDate

addECBDate :: Day -- ^d
  -> IO ()
addECBDate = $(ffiCallX 'addECBDate) c_addECBDate

foreign import ccall safe "ql.h qlECBAddDate"
  c_addECBDate :: CDate -> Ptr CString -> IO ()

-- |returns the ECB code for the given date (e.g. MAR10 for March xxth, 2010).WarningIt raises an exception if the input date is not an ECB date
ecbCode :: Day -- ^ecbDate
  -> IO String
ecbCode = $(ffiCallX 'ecbCode) c_ecbCode

foreign import ccall safe "ql.h qlECBCode"
  c_ecbCode :: CDate -> Ptr CString -> IO CString

-- |returns the ECB date for the given ECB code (e.g. March xxth, 2013 for MAR10).WarningIt raises an exception if the input string is not an ECB code
ecbDate' :: String -- ^ecbCode
  -> Maybe Day -- ^referenceDate
  -> IO Day
ecbDate' = $(ffiCallX 'ecbDate') c_ecbDate'

foreign import ccall safe "ql.h qlECBDate1"
  c_ecbDate' :: CString -> CDate -> Ptr CString -> IO CDate

-- |maintenance period start date in the given month/year
ecbDate :: Month -- ^m
  -> Int -- ^y
  -> IO Day
ecbDate = $(ffiCallX 'ecbDate) c_ecbDate

foreign import ccall safe "ql.h qlECBDate"
  c_ecbDate :: CInt -> CInt -> Ptr CString -> IO CDate

-- |returns whether or not the given string is an ECB code
isECBCode :: String -- ^in
  -> IO Bool
isECBCode = $(ffiCallX 'isECBCode) c_isECBCode

foreign import ccall safe "ql.h qlECBIsECBcode"
  c_isECBCode :: CString -> Ptr CString -> IO CInt

-- |returns whether or not the given date is a maintenance period start date
isECBDate :: Day -- ^d
  -> IO Bool
isECBDate = $(ffiCallX 'isECBDate) c_isECBDate

foreign import ccall safe "ql.h qlECBIsECBdate"
  c_isECBDate :: CDate -> Ptr CString -> IO CInt

knownECBDates :: IO [Day]
knownECBDates = map fromQlDate <$> getArrayX c_knownECBDates

foreign import ccall safe "ql.h qlECBKnownDates"
  c_knownECBDates :: Ptr CUInt -> Ptr CString -> IO (Ptr CDate)

-- |next ECB code following the given code
nextECBCode' :: String -- ^ecbCode
  -> IO String
nextECBCode' = $(ffiCallX 'nextECBCode') c_nextECBCode'

foreign import ccall safe "ql.h qlECBNextCode1"
  c_nextECBCode' :: CString -> Ptr CString -> IO CString

-- |next ECB code following the given date
nextECBCode :: Maybe Day -- ^d
  -> IO String
nextECBCode = $(ffiCallX 'nextECBCode) c_nextECBCode

foreign import ccall safe "ql.h qlECBNextCode"
  c_nextECBCode :: CDate -> Ptr CString -> IO CString

-- |next maintenance period start date following the given ECB code
nextECBDate' :: String -- ^ecbCode
  -> Maybe Day -- ^referenceDate
  -> IO Day
nextECBDate' = $(ffiCallX 'nextECBDate') c_nextECBDate'

foreign import ccall safe "ql.h qlECBNextDate1"
  c_nextECBDate' :: CString -> CDate -> Ptr CString -> IO CDate

-- |next maintenance period start date following the given date
nextECBDate :: Maybe Day -- ^d
  -> IO Day
nextECBDate = $(ffiCallX 'nextECBDate) c_nextECBDate

foreign import ccall safe "ql.h qlECBNextDate"
  c_nextECBDate :: CDate -> Ptr CString -> IO CDate

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

removeECBDate :: Day -- ^d
  -> IO ()
removeECBDate = $(ffiCallX 'removeECBDate) c_removeECBDate

foreign import ccall safe "ql.h qlECBRemoveDate"
  c_removeECBDate :: CDate -> Ptr CString -> IO ()

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
