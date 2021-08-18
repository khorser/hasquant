module QuantLib.Internal.Schedule(withSchedule, withDayCounter) where

import Foreign.Ptr(Ptr)
import QuantLib.Time.Schedule(Schedule, DayCounter)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withSchedule :: Schedule -> (Ptr Schedule -> IO b) -> IO b
withSchedule = withObject

withDayCounter :: DayCounter -> (Ptr DayCounter -> IO b) -> IO b
withDayCounter = withObject

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
