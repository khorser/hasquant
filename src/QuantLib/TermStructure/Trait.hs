module QuantLib.TermStructure.Trait
  (
    Trait(..)
  , YieldCurveModel(..)
  )
where

import QuantLib.Internal.Enum

data Trait = Discount | ZeroYield | ForwardRate deriving (Show, Eq)
instance QLLitEnum Trait

data YieldCurveModel = Standard | ExactYield | ParallelShifts
  | NonParallelShifts
  deriving (Show, Eq, Enum)
instance QLEnum YieldCurveModel

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
