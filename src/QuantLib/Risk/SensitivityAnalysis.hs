{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Risk.SensitivityAnalysis
  (
    SensitivityAnalysis(..)
  )

where

import Data.Typeable(Typeable)
import QuantLib.Internal.Enum(QLEnum)

instance QLEnum SensitivityAnalysis

-- |Finite differences calculation.
data SensitivityAnalysis = OneSide | Centered
  deriving (Show, Eq, Enum, Typeable, Bounded)
