module QuantLib.Instrument.OvernightIndexedSwapType
  (
    OvernightIndexedSwapType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum OvernightIndexedSwapType

data OvernightIndexedSwapType = Receiver | Payer
  deriving (Show, Eq, Enum, Bounded)
