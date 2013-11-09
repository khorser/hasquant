module QuantLib.Instrument.BMASwapType
  (
    BMASwapType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum BMASwapType

data BMASwapType = Receiver | Payer
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
