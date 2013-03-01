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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
