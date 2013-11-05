module QuantLib.Instrument.CallabilityType
  (
    CallabilityType(..)
  , CallabilityPriceType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

data CallabilityType = Call | Put
  deriving (Show, Eq, Enum)
instance QLEnum CallabilityType

data CallabilityPriceType = Dirty | Clean
  deriving (Show, Eq, Enum)
instance QLEnum CallabilityPriceType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
