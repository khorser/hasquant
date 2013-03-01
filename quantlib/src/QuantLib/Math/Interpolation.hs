module QuantLib.Math.Interpolation
  (
    Interpolation(..)
  , Approximation(..)
  )

where

import QuantLib.Internal.Enum

-- bool indicates if the approximation is monotonic
data Approximation = NaturalSpline Bool | Parabolic Bool | Kruger
  | FritschButland
  deriving (Show, Eq)

data Interpolation = BackwardFlat | ForwardFlat | Linear | LogLinear
  | Cubic Approximation | LogCubic Approximation | Abcd
 deriving (Show, Eq)

instance QLLitEnum Interpolation

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
