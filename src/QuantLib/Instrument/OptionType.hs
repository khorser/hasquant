module QuantLib.Instrument.OptionType
  (
    OptionType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum OptionType

data OptionType = Put | Call
  deriving (Show, Eq, Enum)
