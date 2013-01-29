{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Schedule
  (
  -- makers
    schedule
  , schedule'
  , until
  -- accessors
  , dates
  )
where

import Prelude hiding(until)

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
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
  c_scheduleDates :: Ptr CSchedule -> Ptr CInt -> IO (Ptr CDate)

-- | (qlSchedule)
schedule :: Maybe Day -> Day -> Period -> Calendar -> BusinessDayConvention
  -> BusinessDayConvention -> DateGenerationRule -> Bool
  -> Maybe Day -> Maybe Day -> IO Schedule
schedule = $(ffiConstruct 'schedule 'c_schedule)

-- | (qlScheduleFromDateVector)
schedule' :: [Day] -> Calendar -> BusinessDayConvention -> IO Schedule
schedule' = $(ffiConstruct 'schedule' 'c_schedule')

-- | (qlScheduleTruncated)
-- DO NOT call this on schedules created with 'schedule'
-- because result.isRegular_.pop_back() in QuantLib's Schedule::until
-- is called on empty isRegular_ causing unspecified behaviour including
-- segfaults.
-- TODO Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
until :: Schedule -> Day -> IO Schedule
until = $(ffiConstruct 'until 'c_until)

-- |returns the dates for the given Schedule object (qlScheduleDates)
dates :: Schedule -> [Day]
dates sched = map fromQlDate (unsafePerformIO
                $ withObject sched (getDynIntArray . c_scheduleDates))
