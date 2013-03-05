module QuantLib.Math.EndCriteriaType
  (
    EndCriteriaType(..)
  )
where

import QuantLib.Internal.Enum

data EndCriteriaType = None | MaxIterations | StationaryPoint
  | StationaryFunctionValue | StationaryFunctionAccuracy | ZeroGradientNorm
  | Unknown
  deriving (Show, Eq, Enum)
instance QLEnum EndCriteriaType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
