{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Time.Unit
  (
    Unit(..)
  )

where

import Data.Typeable(Typeable)

data Unit = Months | Days | Weeks | Years
  deriving (Show, Eq, Enum, Typeable)
