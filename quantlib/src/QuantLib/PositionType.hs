module QuantLib.PositionType
  (
    PositionType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum PositionType

data PositionType = Long | Short deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
