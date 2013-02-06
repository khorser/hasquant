{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Instrument.VanillaSwapType
  (
    VanillaSwapType(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum VanillaSwapType

data VanillaSwapType = Receiver | Payer
  deriving (Show, Eq, Enum, Typeable, Bounded)
