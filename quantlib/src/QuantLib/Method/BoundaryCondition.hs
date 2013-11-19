module QuantLib.Method.BoundaryCondition
  (
    BoundaryConditionSide(..)
  )
where

import QuantLib.Internal.Enum(QLEnum)

-- |Possible enhancements: Generalize for n-dimensional conditions
data BoundaryConditionSide = BoundaryConditionNone | BoundaryConditionUpper
  | BoundaryConditionLower
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum BoundaryConditionSide

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
