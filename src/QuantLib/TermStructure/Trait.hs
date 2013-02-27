module QuantLib.TermStructure.Trait
  (
    Trait(..)
  , YieldCurveModel(..)
  , BlackVarSurfaceExtrapolation(..)
  , ExtBlackVarSurfaceExtrapolation(..)
  , CmsMarketCalibrationType(..)
  )
where

import QuantLib.Internal.Enum

data Trait = Discount | ZeroYield | ForwardRate deriving (Show, Eq)
instance QLLitEnum Trait

data YieldCurveModel = Standard | ExactYield | ParallelShifts
  | NonParallelShifts
  deriving (Show, Eq, Enum)
instance QLEnum YieldCurveModel

data BlackVarSurfaceExtrapolation =
    BlackVarSurfaceConstant | BlackVaSurfaceInterpolatorDefault
  deriving (Show, Eq, Enum)
instance QLEnum BlackVarSurfaceExtrapolation

data ExtBlackVarSurfaceExtrapolation =
    ExtBlackVarSurfaceConstant | ExtBlackVarSurfaceInterpolatorDefault
  deriving (Show, Eq, Enum)
instance QLEnum ExtBlackVarSurfaceExtrapolation

data CmsMarketCalibrationType =
    CmsMarketOnSpread | CmsMarketOnPrice | CmsMarketOnForwardCmsPrice
  deriving (Show, Eq, Enum)
instance QLEnum CmsMarketCalibrationType

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
