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
  , timeGrid
  , timeGridFromList
  , timeGridFromList'
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

{#enum CmsMarketCalibrationType {} deriving(Show, Eq)#}

{#pointer *TimeGrid foreign finalizer qlFreeTimeGrid newtype#}
instance ForeignObject TimeGrid where
  withObject = withTimeGrid
  constructor = TimeGrid
  finalizer = qlFreeTimeGrid

-- |Regularly spaced time-grid.
{#fun qlTimeGrid1 as timeGrid {`Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `TimeGrid'#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. No additional points are added.
{#fun qlTimeGrid2 as timeGridFromList {withDoubleArray* `[Double]'&, preErrorCheck- `String' errorCheck*-} -> `TimeGrid'#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. Additional points are then added with regular spacing between pairs of mandatory times in order to reach the desired number of steps.
{#fun qlTimeGrid3 as timeGridFromList' {withDoubleArray* `[Double]'&, fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `TimeGrid'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
