module QuantLib.Math.Interpolation
  (
    Interpolation(..)
  )

where

data Interpolation = BackwardFlat | ForwardFlat | Linear | LogLinear
  | CubicNaturalSpline | MonotonicCubicNaturalSpline | LogCubicNaturalSpline
  | MonotonicLogCubicNaturalSpline | KrugerCubic | KrugerLogCubic
  | FritschButlandCubic | FritschButlandLogCubic | Parabolic
  | MonotonicParabolic | LogParabolic | MonotonicLogParabolic | Abcd
 deriving (Show, Eq)
