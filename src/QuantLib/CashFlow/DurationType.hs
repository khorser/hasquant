module QuantLib.CashFlow.DurationType
  (
    DurationType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum DurationType

-- |duration type
data DurationType = Simple | Macaulay | Modified
  deriving (Show, Eq, Enum)
