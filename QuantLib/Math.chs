-- |Numeric helpers, enum catalogues, and the matrix\/vector value types the rest of
-- @hasquant@ marshals through.
--
-- __Matrices.__ There are two, and the split is deliberate. 'RealMatrix' is a row-major
-- numeric matrix over a contiguous 'RealVector', for large dense grids (volatility
-- surfaces, LSM regression states); 'Matrix' is list-backed and boxed, for small
-- fixed-dimensional numeric data (correlation and diffusion matrices) and for element
-- types that cannot live in a storable vector at all, notably @'Matrix' ('QuantLib.Quote.GenQuote' q)@,
-- whose foreign pointers need continuation-based marshalling. Construct them with
-- 'realMatrixFromVector' and 'boxedRealMatrix' (or 'objectMatrix') respectively.
--
-- 'RealMatrix' interoperates with @hmatrix@ without @hasquant@ depending on it:
-- @Numeric.LinearAlgebra.reshape cols realMatrixData@ is a row-major view with no
-- element copy. The reverse, through @flatten@, is zero-copy only for a contiguous
-- row-major hmatrix matrix; BLAS-produced or sliced matrices can require a reorder.
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

  , Matrix
  , matrixRows
  , matrixColumns
  , matrixData
  , RealMatrix
  , realMatrixRows
  , realMatrixColumns
  , realMatrixData
  , boxedRealMatrix
  , realMatrixFromVector
  , objectMatrix

  , RealVector
  , NonEmptyVector
  , singletonNonEmptyVector
  , consNonEmptyVector
  , nonEmptyVector
  , nonEmptyVectorToVector

  , TimeGrid
  , timeGrid
  , timeGridFromVector
  , timeGridFromVector'
  , timeAt
  , size
  , points
  ) where
import QuantLib.Internal
import QuantLib.Internal.Common
import QuantLib.Internal.Type
import Foreign.Marshal.Alloc(alloca)

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
-- 'QuantLib.Model.CalibrationHelper's, this takes any 'RealVector -> Double' objective. The cost
-- function crosses back into Haskell once per outer optimizer iteration, over the whole parameter
-- vector, not once per component -- see CLAUDE.md's "coarsen the language-boundary crossing"
-- bullet and 'QuantLib.Internal.Type.withCostFunction'.
{#fun qlOptimize as optimize{withCostFunction*`RealVector -> Double' -- ^cost function
  ,withRealVector*`RealVector'& -- ^initial guess
  ,withMaybeConstraint*`Maybe Constraint'
  ,withOptimizationMethod*`OptimizationMethod'
  ,withEndCriteria*`EndCriteria'
  ,preArray-`RealVector'&peekRealVector* -- ^solution
  ,alloca-`Double'peekDouble* -- ^achieved cost
  ,alloca-`EndCriteriaType'peekEnum* -- ^end criteria reached
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Regularly spaced time-grid.
{#fun qlTimeGrid1 as timeGrid{`Double' -- ^end
  ,fromIntegral`Word' -- ^steps
  ,preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. No additional points are added.
{#fun qlTimeGrid2 as timeGridFromVector{withNonEmptyRealVector*`NonEmptyVector Double'& -- ^mandatoryTimes
  ,preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |Time grid with mandatory time points.
-- Mandatory points are guaranteed to belong to the grid. Additional points are then added with regular spacing between pairs of mandatory times in order to reach the desired number of steps.
{#fun qlTimeGrid3 as timeGridFromVector'{withNonEmptyRealVector*`NonEmptyVector Double'& -- ^mandatoryTimes
  ,fromIntegral`Word' -- ^steps
  ,preErrorCheck-`String'errorCheck*-}->`TimeGrid'peekTimeGrid*#}

-- |returns the number of times on the grid
{#fun pure qlTimeGridSize as size{withTimeGrid*`TimeGrid'}->`Word'fromIntegral#}

-- |returns the time at the given index of the grid
{#fun qlTimeGridAt as timeAt{withTimeGrid*`TimeGrid' -- ^grid
  ,fromIntegral`Word' -- ^index
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns all times on the grid in contiguous storage.
{#fun qlTimeGridPoints as points{withTimeGrid*`TimeGrid',preArray-`RealVector'&peekRealVector*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
