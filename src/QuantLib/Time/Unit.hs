module QuantLib.Time.Unit
  (
    Unit(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Unit

-- |Units used to describe time periods
data Unit = Months | Days | Weeks | Years
  deriving (Show, Eq, Enum)
