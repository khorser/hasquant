module QuantLib.Math.RNGTrait
  (
    RNGTrait(..)
  )
where

import QuantLib.Internal.Enum

data RNGTrait = PseudoRandom | PoissonPseudoRandom | LowDiscrepancy | Ziggurat
  deriving (Show, Eq)
instance QLLitEnum RNGTrait

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
