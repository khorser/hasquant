module QuantLib.TermStructure.Trait
  (
    Trait(..)
  )
where

import QuantLib.Internal.Enum

data Trait = Discount | ZeroYield | ForwardRate deriving (Show, Eq)

instance QLLitEnum Trait
