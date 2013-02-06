module QuantLib.Instrument.VanillaSwapType
  (
    VanillaSwapType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum VanillaSwapType

data VanillaSwapType = Receiver | Payer
  deriving (Show, Eq, Enum, Bounded)
