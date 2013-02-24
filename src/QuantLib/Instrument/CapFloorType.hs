module QuantLib.Instrument.CapFloorType
  (
    CapFloorType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum CapFloorType

data CapFloorType = Cap | Floor | Collar
  deriving (Show, Eq, Enum)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
