module QuantLib.Instrument.VanillaSwapType
  (
    VanillaSwapType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum VanillaSwapType

data VanillaSwapType = Receiver | Payer
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
