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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
