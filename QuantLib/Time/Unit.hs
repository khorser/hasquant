{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.Unit
  (
    Unit(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Unit

data Unit = Months | Days | Weeks | Years
  deriving (Show, Eq, Enum, Typeable)
