{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Compounding
  (
    Compounding(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Compounding

data Compounding = Simple | Compounded | Continuous | SimpleThenCompounded
  deriving (Show, Eq, Enum, Typeable)
