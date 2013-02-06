{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.ExerciseType
  (
    ExerciseType(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum ExerciseType

data ExerciseType = American | Bermudan | European
  deriving (Show, Eq, Enum, Typeable, Bounded)
