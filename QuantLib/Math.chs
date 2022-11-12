module QuantLib.Math
  (
    RoundingType(..)
  , Rounding(..)
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
  , PolynomialType(..)
  , ComplexLogFormula(..)
  , CmsMarketCalibrationType(..)
  , EndCriteria(..)
  , OptimizationMethod(..)
  , Constraint(..)
  , SobolDirectionIntegers(..)

  , Matrix
  , realMatrix
  , objectMatrix

  , TimeGrid
  , timeGrid
  , timeGridFromList
  , timeGridFromList'
  , timeAt
  , size
  )
where

import QuantLib.Internal
import QuantLib.Internal.Enum
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

{#pointer *Rounding as QlRounding foreign -> CRounding nocode#}

{#fun pure qlRound as applyRounding{withRounding*`Rounding',`Double'}->`Double'#}

{#enum EndCriteriaType{} deriving(Show, Eq)#}

{#enum HistogramAlgorithm{} deriving(Show, Eq)#}

{#enum RngTrait{} deriving(Show, Eq)#}

{#enum BinomialTree{} deriving(Show, Eq)#}

{#enum BoundaryConditionSide{} deriving(Show, Eq)#}

{#enum PolynomialType{} deriving(Show, Eq)#}

{#enum ComplexLogFormula{} deriving(Show, Eq)#}

{#enum CmsMarketCalibrationType{} deriving(Show, Eq)#}

{#enum SobolDirectionIntegers{} deriving(Show, Eq)#}

{#pointer *TimeGrid foreign -> CTimeGrid nocode#}

-- |Regularly spaced time-grid.
{#fun qlTimeGrid1 as timeGrid{`Double', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. No additional points are added.
{#fun qlTimeGrid2 as timeGridFromList{withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. Additional points are then added with regular spacing between pairs of mandatory times in order to reach the desired number of steps.
{#fun qlTimeGrid3 as timeGridFromList'{withDoubleArray*`[Double]'&, fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

{#fun qlTimeGridSize as size{withTimeGrid*`TimeGrid'}->`Word'fromIntegral#}
{#fun qlTimeGridAt as timeAt{withTimeGrid*`TimeGrid',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
