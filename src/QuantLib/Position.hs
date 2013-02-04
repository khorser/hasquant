{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Position
  (
    Position(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum Position

data Position = Long | Short deriving (Show, Eq, Enum, Typeable)
