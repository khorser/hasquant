{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Compounding
  (
    Compounding(..)
  )

where

import Data.Typeable(Typeable)

data Compounding = Simple | Compounded | Continuous | SimpleThenCompounded
  deriving (Show, Eq, Enum, Typeable)
