module QuantLib.SettlementType
  (
    SettlementType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum SettlementType

data SettlementType = Physical | Cash
  deriving (Show, Eq, Enum)
