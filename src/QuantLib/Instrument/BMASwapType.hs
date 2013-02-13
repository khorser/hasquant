module QuantLib.Instrument.BMASwapType
  (
    BMASwapType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum BMASwapType

data BMASwapType = Receiver | Payer
  deriving (Show, Eq, Enum)
