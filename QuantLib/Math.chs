module QuantLib.Math
  (
    RoundingType(..)
  , Rounding
  , rounding
  , rounding'
  , applyRounding

  , EndCriteriaType(..)
  , HistogramAlgorithm(..)

  , Approximation(..)
  , Interpolation(..)

  , RngTrait(..)
  , BinomialTree(..)
  , BoundaryConditionSide(..)
  , FdmSchemeType(..)
  , FdmScheme(..)
  , PolynomType(..)
  , ComplexLogFormula(..)
  , CmsMarketCalibrationType(..)
  , EndCriteria(..)
  , OptimizationMethod(..)
  , Constraint(..)

  , Matrix
  , realMatrix
  , objectMatrix

  , TimeGrid
  )
where

import QuantLib.Internal
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

{#enum RoundingType {} deriving (Show, Eq)#}

{#pointer *Rounding foreign finalizer qlFreeRounding newtype#}
instance ForeignObject Rounding where
  withObject = withRounding
  constructor = Rounding
  finalizer = qlFreeRounding

{#fun qlRounding as rounding {preErrorCheck- `String' errorCheck*-} -> `Rounding'#}

{#fun qlRounding1 as rounding' {`Int', `RoundingType', `Int', preErrorCheck- `String' errorCheck*-} -> `Rounding'#}

{#fun pure qlRound as applyRounding {`Rounding', `Double'} -> `Double'#}

{#enum EndCriteriaType {} deriving(Show, Eq)#}

{#enum HistogramAlgorithm {} deriving(Show, Eq)#}

{#enum RngTrait {} deriving(Show, Eq)#}

{#enum BinomialTree {} deriving(Show, Eq)#}

{#enum BoundaryConditionSide {} deriving(Show, Eq)#}

{#enum PolynomType {} deriving(Show, Eq)#}

{#enum ComplexLogFormula {} deriving(Show, Eq)#}

{#enum ExtendedBlackScholesMertonProcessDiscretization {} deriving(Show, Eq)#}

{#enum HestonProcessDiscretization {} deriving(Show, Eq)#}

{#enum GJRGARCHProcessDiscretization {} deriving(Show, Eq)#}

{#enum HybridHestonHullWhiteProcessDiscretization {} deriving(Show, Eq)#}

{#enum CmsMarketCalibrationType {} deriving(Show, Eq)#}

{#pointer *TimeGrid foreign finalizer qlFreeTimeGrid newtype#}
instance ForeignObject TimeGrid where
  withObject = withTimeGrid
  constructor = TimeGrid
  finalizer = qlFreeTimeGrid

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
