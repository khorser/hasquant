module QuantLib.CashFlow.DurationType
  (
    DurationType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum DurationType

-- |duration type
data DurationType = Simple | Macaulay | Modified
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
