module QuantLib.ExerciseType
  (
    ExerciseType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum ExerciseType

data ExerciseType = American | Bermudan | European
  deriving (Show, Eq, Enum)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
