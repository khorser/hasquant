module QuantLib.Time.Schedule
  (
    TimeUnit
  , DayCounter
  )

where

import Foreign.ForeignPtr(ForeignPtr)

data TimeUnit
instance Enum TimeUnit
instance Show TimeUnit

newtype DayCounter = DayCounter (ForeignPtr DayCounter)
instance Show DayCounter
instance Eq DayCounter
