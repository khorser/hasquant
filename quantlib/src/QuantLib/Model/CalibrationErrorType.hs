module QuantLib.Model.CalibrationErrorType
  (
    CalibrationErrorType(..)
  )
where

import QuantLib.Internal.Enum(QLEnum)

data CalibrationErrorType =
    RelativePriceError | PriceError | ImpliedVolError
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum CalibrationErrorType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
