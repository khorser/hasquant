module QuantLib.Math
  (
    RoundingType(..)
  , Rounding(..)
  , applyRounding
  , optimize

  , EndCriteriaType(..)
  , HistogramAlgorithm(..)

  , Approximation(..)
  , Interpolation(..)
  , Interpolation2D(..)

  , RngTrait(..)
  , StatisticsTrait(..)
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

  , Matrix(..)
  , realMatrix
  , objectMatrix

  , TimeGrid
  , timeGrid
  , timeGridFromList
  , timeGridFromList'
  , timeAt
  , size
  , points
  , points'
  ) where
import QuantLib.Internal
import QuantLib.Internal.Common
import QuantLib.Internal.Type
import Foreign.C.Types(CDouble)
import Foreign.Marshal.Alloc(alloca)
import Data.Vector.Storable(Vector)
import Data.List.NonEmpty(NonEmpty)

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

{#enum EndCriteriaType{} deriving(Show, Eq, Read)#}
{#enum HistogramAlgorithm{} deriving(Show, Eq, Read)#}
{#enum RngTrait{} deriving(Show, Eq, Read)#}
{#enum StatisticsTrait{} deriving(Show, Eq, Read)#}
{#enum BinomialTree{} deriving(Show, Eq, Read)#}
{#enum BoundaryConditionSide{} deriving(Show, Eq, Read)#}
{#enum PolynomialType{} deriving(Show, Eq, Read)#}
-- |Characteristic-function contour/control-variate choice used by Heston integrations.
{#enum ComplexLogFormula{} deriving(Show, Eq, Read)#}
{#enum CmsMarketCalibrationType{} deriving(Show, Eq, Read)#}
{#enum SobolDirectionIntegers{} deriving(Show, Eq, Read)#}

{#pointer *TimeGrid foreign -> CTimeGrid nocode#}
{#pointer *Rounding as QlRounding foreign -> CRounding nocode#}
{#pointer *QlOptimizationMethod as QlOptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *QlEndCriteria as QlEndCriteria foreign -> CEndCriteria nocode#}
{#pointer *Constraint as QlConstraint foreign -> CConstraint nocode#}

-- |rounds a value to the precision and rule carried by the given 'Rounding'
{#fun pure qlRound as applyRounding{withRounding*`Rounding' -- ^rounding
  ,`Double' -- ^value
  }->`Double'#}

-- |Minimizes an arbitrary Haskell-defined cost function via QuantLib's general-purpose
-- 'Problem'\/'OptimizationMethod' machinery -- unlike 'QuantLib.Model.calibrate', which drives a
-- 'QuantLib.Model.CalibratedModel''s own built-in calibration error against bound
-- 'QuantLib.Model.CalibrationHelper's, this takes any @[Double] -> Double@ objective. The cost
-- function crosses back into Haskell once per outer optimizer iteration, over the whole parameter
-- vector, not once per component -- see CLAUDE.md's "coarsen the language-boundary crossing"
-- bullet and 'QuantLib.Internal.Type.withCostFunction'.
{#fun qlOptimize as optimize{withCostFunction*`[Double] -> Double' -- ^cost function
  ,withDoubleArray*`[Double]'& -- ^initial guess
  ,withMaybeConstraint*`Maybe Constraint'
  ,withOptimizationMethod*`OptimizationMethod'
  ,withEndCriteria*`EndCriteria'
  ,preArray-`[Double]'&peekDoubleArray* -- ^solution
  ,alloca-`Double'peekDouble* -- ^achieved cost
  ,alloca-`EndCriteriaType'peekEnum* -- ^end criteria reached
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Regularly spaced time-grid.
{#fun qlTimeGrid1 as timeGrid{`Double' -- ^end
  ,fromIntegral`Word' -- ^steps
  ,preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. No additional points are added.
{#fun qlTimeGrid2 as timeGridFromList{withNonEmptyDoubleArray*`NonEmpty Double'&,preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. Additional points are then added with regular spacing between pairs of mandatory times in order to reach the desired number of steps.
{#fun qlTimeGrid3 as timeGridFromList'{withNonEmptyDoubleArray*`NonEmpty Double'&,fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |returns the number of times on the grid
{#fun pure qlTimeGridSize as size{withTimeGrid*`TimeGrid'}->`Word'fromIntegral#}

-- |returns the time at the given index of the grid
{#fun qlTimeGridAt as timeAt{withTimeGrid*`TimeGrid' -- ^grid
  ,fromIntegral`Word' -- ^index
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns all the times on the grid, as a list
{#fun qlTimeGridPoints as points{withTimeGrid*`TimeGrid',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |returns all the times on the grid, as a vector
{#fun qlTimeGridPoints as points'{withTimeGrid*`TimeGrid',preArray-`Vector CDouble'&peekDoubleVector*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
