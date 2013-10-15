{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Time.Schedule
  (
    schedule
  , schedule'
  , until

  , dates
  )
where

import Prelude hiding(until)

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)

foreign import ccall safe "ql.h qlSchedule"
  c_schedule :: CDate -> CDate -> Ptr CPeriod -> Ptr CCalendar
    -> CInt -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString
    -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlSchedule1"
  c_schedule' :: CUInt -> Ptr CDate -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlScheduleUntil"
  c_until :: Ptr CSchedule -> CDate -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlScheduleDates"
  c_scheduleDates :: Ptr CSchedule -> Ptr CUInt -> IO (Ptr CDate)

-- | QuantLibXL: qlSchedule
schedule :: Maybe Day -- ^effectiveDate
  -> Day -- ^terminationDate
  -> Period -- ^tenor
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> BusinessDayConvention -- ^terminationDateConvention
  -> DateGenerationRule -- ^rule
  -> Bool -- ^endOfMonth
  -> Maybe Day -- ^firstDate
  -> Maybe Day -- ^nextToLastDate
  -> IO Schedule
schedule = $(ffiCall 'schedule) c_schedule

-- | QuantLibXL: qlScheduleFromDateVector
schedule' :: [Day]
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> IO Schedule
schedule' = $(ffiCall 'schedule') c_schedule'

-- |truncated schedule. QuantLibXL: qlScheduleTruncated
-- DO NOT call this on schedules created with 'schedule''
-- because result.isRegular_.pop_back() in QuantLib's Schedule::until
-- is called on empty isRegular_ causing unspecified behaviour including
-- segfaults.
-- XXX Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
until :: Schedule
  -> Day -- ^truncationDate
  -> IO Schedule
until = $(ffiCall 'until) c_until

-- |returns the dates for the given Schedule object. QuantLibXL: qlScheduleDates
dates :: Schedule -> [Day]
dates = $(ffiCallPure 'dates) c_scheduleDates

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
