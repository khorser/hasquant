{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Schedule
  (
    Schedule
  , schedule
  , CSchedule
  , schedule'
  , until
  )
where

import Data.Time.Calendar(Day)

import Foreign.C.Types(CDouble(CDouble))
import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr)

import Prelude hiding(until)
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal(CDate, handleExceptions, construct, withObject, Object, Finalizable, finalize, fromQlDateSerialNumber, toQlDateSerialNumber)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Period(Period, CPeriod)

data CSchedule

type Schedule = Object CSchedule

foreign import ccall safe "ql.h qlSchedule"
  c_schedule :: CDate -> CDate -> Ptr CPeriod -> Ptr CCalendar -> Int -> Int -> Int -> Int -> CDate -> CDate -> Ptr CString -> IO (Ptr CSchedule)
foreign import ccall safe "ql.h &qlFreeSchedule"
  p_freeSchedule :: FunPtr (Ptr CSchedule -> IO ())

instance Finalizable CSchedule where
  finalize = p_freeSchedule

-- | (qlSchedule)
schedule' :: Day -> Day -> Period -> Calendar -> BusinessDayConvention -> BusinessDayConvention -> DateGenerationRule -> Bool -> Maybe Day -> Maybe Day -> IO Schedule
schedule' effective term tenor cal conv termConv rule eom first nextToLast = undefined -- construct $ c_schedule (realToFrac v)

-- | (qlScheduleFromDateVector)
schedule :: [Day] -> Calendar -> BusinessDayConvention -> IO Schedule
schedule = undefined

-- | (qlScheduleTruncated)
until :: Schedule -> Day -> IO Schedule
until = undefined
