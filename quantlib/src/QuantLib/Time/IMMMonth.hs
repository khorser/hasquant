module QuantLib.Time.IMMMonth
  (
    IMMMonth(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum IMMMonth

-- |Finite differences calculation.
data IMMMonth = F | G | H | J | K | M | N | Q | U | V | X | Z
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
