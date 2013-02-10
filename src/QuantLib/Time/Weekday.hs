module QuantLib.Time.Weekday
  (
    Weekday(..)
  )
where

import QuantLib.Internal.Enum

instance QLEnum Weekday

data Weekday = Sunday | Monday | Tuesday | Wednesday | Thursday | Friday
  | Saturday
  deriving (Show, Eq, Enum)
