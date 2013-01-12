module QuantLib.Math.Interpolation
  (
    Interpolation(..)
  , Approximation(..)
  )

where

-- bool indicates if the approximation is monotonic
data Approximation = NaturalSpline Bool | Parabolic Bool | Kruger
  | FritschButland
  deriving (Show, Eq)

data Interpolation = BackwardFlat | ForwardFlat | Linear | LogLinear
  | Cubic Approximation | LogCubic Approximation | Abcd
 deriving (Show, Eq)
