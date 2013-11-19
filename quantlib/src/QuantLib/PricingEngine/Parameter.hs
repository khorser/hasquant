module QuantLib.PricingEngine.Parameter
  (
    ComplexLogFormula(..)
  )
where

import QuantLib.Internal.Enum(QLEnum)

data ComplexLogFormula = Gatheral | BranchCorrection
  deriving (Show, Eq, Enum, Bounded)
instance QLEnum ComplexLogFormula

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
