module QuantLib.Instrument.AverageType
  (
    AverageType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum AverageType

data AverageType = Arithmetic | Geometric
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
