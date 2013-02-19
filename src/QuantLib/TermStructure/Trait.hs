module QuantLib.TermStructure.Trait
  (
    Trait(..)
  )
where

import QuantLib.Internal.Enum

data Trait = Discount | ZeroYield | ForwardRate deriving (Show, Eq)

instance QLLitEnum Trait

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
