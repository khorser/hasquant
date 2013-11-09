module QuantLib.Instrument.OptionType
  (
    OptionType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum OptionType

data OptionType = Put | Call
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
