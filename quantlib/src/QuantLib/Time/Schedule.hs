{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Schedule
  (
    schedule
  , scheduleFromDays
  , until

  , dates
  )
where

import Prelude hiding(until)

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Unit(Unit)

foreign import ccall safe "ql.h qlSchedule"
  c_schedule :: CDate -> CDate -> CInt -> CInt -> Ptr CCalendar -> CInt -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlSchedule1"
  c_scheduleFromDays :: CUInt -> Ptr CDate -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlScheduleUntil"
  c_until :: Ptr CSchedule -> CDate -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlScheduleDates"
  c_dates :: Ptr CSchedule -> Ptr CUInt -> IO (Ptr CDate)

schedule :: Maybe Day -- ^effectiveDate
  -> Day -- ^terminationDate
  -> (Int, Unit) -- ^tenor
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> BusinessDayConvention -- ^terminationDateConvention
  -> DateGenerationRule -- ^rule
  -> Bool -- ^endOfMonth
  -> Maybe Day -- ^firstDate
  -> Maybe Day -- ^nextToLastDate
  -> QLE s (Schedule s)
schedule = $(ffiCall 'schedule) c_schedule

scheduleFromDays :: [Day]
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> QLE s (Schedule s)
scheduleFromDays = $(ffiCall 'scheduleFromDays) c_scheduleFromDays

-- |truncated schedule
-- DO NOT call this on schedules created with 'scheduleFromDays'
-- because result.isRegular_.pop_back() in QuantLib's Schedule::until
-- is called on empty isRegular_ causing unspecified behaviour including
-- segfaults.
-- XXX Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
until :: Schedule
  -> Day -- ^truncationDate
  -> QLE s (Schedule s)
until = $(ffiCall 'until) c_until

-- |returns the dates for the given Schedule object
dates :: Schedule -> [Day]
dates = $(ffiCallPure 'dates) c_dates

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
