module QuantLib.SettlementType
  (
    SettlementType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum SettlementType

data SettlementType = Physical | Cash
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
