module QuantLib.Instrument.BarrierType
  (
    BarrierType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum BarrierType

data BarrierType = DownIn | UpIn | DownOut | UpOut
  deriving (Show, Eq, Enum)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
