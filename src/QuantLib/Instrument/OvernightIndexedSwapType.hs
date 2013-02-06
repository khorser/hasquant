{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Instrument.OvernightIndexedSwapType
  (
    OvernightIndexedSwapType(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum OvernightIndexedSwapType

data OvernightIndexedSwapType = Receiver | Payer
  deriving (Show, Eq, Enum, Typeable, Bounded)
