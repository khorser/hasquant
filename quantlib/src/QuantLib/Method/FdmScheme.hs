module QuantLib.Method.FdmScheme
  (
    FdmScheme(..)
  , FdmSchemeType(..)
  )
where

import QuantLib.Internal.Enum

data FdmScheme = FDCrankNicolson | FDExplicitEuler | FDImplicitEuler 
  deriving (Show, Eq)
instance QLLitEnum FdmScheme

data FdmSchemeType = Hundsdorfer | Douglas | CraigSneyd | ModifiedCraigSneyd
  | ImplicitEuler | ExplicitEuler
  deriving (Show, Eq, Enum)
instance QLEnum FdmSchemeType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
