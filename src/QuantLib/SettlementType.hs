{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.SettlementType
  (
    SettlementType(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum SettlementType

data SettlementType = Physical | Cash
  deriving (Show, Eq, Enum, Typeable, Bounded)
