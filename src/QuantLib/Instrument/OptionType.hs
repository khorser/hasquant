{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Instrument.OptionType
  (
    OptionType(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum OptionType

data OptionType = Put | Call
  deriving (Show, Eq, Enum, Typeable, Bounded)
