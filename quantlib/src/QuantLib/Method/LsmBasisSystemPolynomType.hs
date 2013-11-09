module QuantLib.Method.LsmBasisSystemPolynomType
  (
    LsmBasisSystemPolynomType(..)
  )

where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum LsmBasisSystemPolynomType

data LsmBasisSystemPolynomType = Monomial | Laguerre | Hermite | Hyperbolic
  | Legendre | Chebyshev | Chebyshev2nd
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
