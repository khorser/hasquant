{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Schedule
  (
    Schedule
  , schedule
  , CSchedule
  , schedule'
  , until
  , dates
  )
where

import Data.Time.Calendar(Day)

import Foreign.C.Types(CInt(CInt))
import Foreign.C.String(CString)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(withArray, peekArray)
import Foreign.Marshal.Utils(fromBool)
import Foreign.Ptr(Ptr, FunPtr)
import Foreign.Storable(peek)

import Prelude hiding(until)

import QuantLib.Internal
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Period(Period, CPeriod)

import System.IO.Unsafe(unsafePerformIO)

data CSchedule
type Schedule = Object CSchedule

foreign import ccall safe "ql.h qlSchedule"
  c_schedule :: CDate -> CDate -> Ptr CPeriod -> Ptr CCalendar
    -> CInt -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString
    -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlSchedule1"
  c_schedule' :: CInt -> Ptr CDate -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h qlScheduleUntil"
  c_until :: Ptr CSchedule -> CDate -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h &qlFreeSchedule"
  p_freeSchedule :: FunPtr (Ptr CSchedule -> IO ())
foreign import ccall safe "ql.h qlScheduleDates"
  c_scheduleDates :: Ptr CSchedule -> Ptr CInt -> IO (Ptr CDate)

instance Finalizable CSchedule where
  finalize = p_freeSchedule

-- | (qlSchedule)
schedule :: Maybe Day -> Day -> Period -> Calendar -> BusinessDayConvention
  -> BusinessDayConvention -> DateGenerationRule -> Bool
  -> Maybe Day -> Maybe Day -> IO Schedule
schedule effective term tenor cal conv termConv rule eom first nextToLast =
  withObject
    tenor
    (\t ->
      withObject
        cal
        (\c -> construct
                $ c_schedule
                (toQlDateSerialNumber effective)
                (toQlDateSerialNumber term)
                t
                c
                (toQlEnum conv)
                (toQlEnum termConv)
                (toQlEnum rule)
                (fromBool eom)
                (toQlDateSerialNumber first)
                (toQlDateSerialNumber nextToLast)))


-- | (qlScheduleFromDateVector)
schedule' :: [Day] -> Calendar -> BusinessDayConvention -> IO Schedule
schedule' days cal conv =
  withArray
  (map toQlDateSerialNumber days)
  (\d ->
    withObject
      cal
      (\c -> construct
              $ c_schedule' (fromIntegral $ length days) d c (toQlEnum conv)))

-- | (qlScheduleTruncated)
-- DO NOT call this on schedules created with 'schedule'
-- because result.isRegular_.pop_back() in QuantLib's Schedule::until
-- is called on empty isRegular_ causing unspecified behaviour including
-- segfaults.
-- TODO Introduce another Schedule type with restricted interface?
-- moreover, a fixed rate bond can be constructed from a full schedule only!
until :: Schedule -> Day -> IO Schedule
until sched d =
  withObject
  sched
  (\s -> construct $ c_until s (toQlDateSerialNumber d))


-- |returns the dates for the given Schedule object (qlScheduleDates)
dates :: Schedule -> [Day]
dates sched = map fromQlDateSerialNumber (unsafePerformIO
                $ withObject
                    sched
                    (\s ->
                      alloca
                      (\pcnt -> do ds <- c_scheduleDates s pcnt
                                   count <- peek pcnt
                                   days <- peekArray (fromIntegral count) ds
                                   c_freeInts ds
                                   return days)))
