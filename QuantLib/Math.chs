-- |Numeric helpers and matrix/vector value types.
-- 'RealMatrix' stores dense numeric grids; boxed 'Matrix' supports small or object-valued data.
module QuantLib.Math
  (
    -- * Types
    RoundingType(..)
  , Rounding(..)
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
  , RealMatrix
  , SalvagingAlgorithm(..)
  , RealVector
  , NonEmptyVector
  , TimeGrid

    -- * Constructors
    -- ** Matrices and vectors
  , boxedRealMatrix
  , realMatrixFromVector
  , objectMatrix
  , singletonNonEmptyVector
  , consNonEmptyVector
  , nonEmptyVector
    -- ** Time grids
  , timeGrid
  , timeGridFromVector
  , timeGridFromVectorWithSteps

    -- * Inspectors
    -- ** Rounding and optimization
  , applyRounding
  , optimize
    -- ** Matrix decompositions
  , symmetricSchurDecomposition
  , pseudoSqrt
  , rankReducedSqrt
  , choleskyDecomposition
  , choleskySolveFor
    -- ** Risk statistics
  , riskStatisticsMean
  , riskStatisticsStandardDeviation
  , riskStatisticsVariance
  , riskStatisticsSkewness
  , riskStatisticsKurtosis
  , riskStatisticsMin
  , riskStatisticsMax
  , riskStatisticsSemiVariance
  , riskStatisticsSemiDeviation
  , riskStatisticsDownsideVariance
  , riskStatisticsDownsideDeviation
  , riskStatisticsPercentile
  , riskStatisticsGaussianPercentile
  , riskStatisticsValueAtRisk
  , riskStatisticsGaussianValueAtRisk
  , riskStatisticsExpectedShortfall
  , riskStatisticsGaussianExpectedShortfall
  , riskStatisticsPotentialUpside
  , riskStatisticsGaussianPotentialUpside
  , riskStatisticsRegret
  , riskStatisticsShortfall
  , riskStatisticsAverageShortfall
    -- ** Matrices and vectors
  , matrixRows
  , matrixColumns
  , matrixData
  , realMatrixRows
  , realMatrixColumns
  , realMatrixData
  , nonEmptyVectorToVector
    -- ** Time grids
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

-- |Algorithm used to salvage a matrix that is not positive semi-definite before taking its
-- pseudo square root. @Higham@ only works for correlation matrices.
{#enum SalvagingAlgorithm{} deriving(Show, Eq, Read)#}

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
-- function crosses back into Haskell once per outer optimizer iteration over the whole parameter
-- vector; see 'QuantLib.Internal.Type.withCostFunction'.
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
{#fun qlTimeGrid3 as timeGridFromVectorWithSteps{withNonEmptyRealVector*`NonEmptyVector Double'& -- ^mandatoryTimes
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

-- |Mean of a caller-supplied sample. Each @riskStatistics*@ call evaluates a fresh sample.
{#fun qlRiskStatisticsMean as riskStatisticsMean{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Standard deviation of the sample (square root of 'riskStatisticsVariance').
{#fun qlRiskStatisticsStandardDeviation as riskStatisticsStandardDeviation{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Variance of the sample, @N\/(N-1)@-corrected.
{#fun qlRiskStatisticsVariance as riskStatisticsVariance{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Skewness of the sample; 0 for a gaussian distribution.
{#fun qlRiskStatisticsSkewness as riskStatisticsSkewness{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Excess kurtosis of the sample; 0 for a gaussian distribution.
{#fun qlRiskStatisticsKurtosis as riskStatisticsKurtosis{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Minimum sample value. Throws if the sample is empty.
{#fun qlRiskStatisticsMin as riskStatisticsMin{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Maximum sample value. Throws if the sample is empty.
{#fun qlRiskStatisticsMax as riskStatisticsMax{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Variance of the sample values falling below the sample mean (Markowitz semi-variance).
-- Throws if fewer than two sample values fall below the mean.
{#fun qlRiskStatisticsSemiVariance as riskStatisticsSemiVariance{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Square root of 'riskStatisticsSemiVariance'.
{#fun qlRiskStatisticsSemiDeviation as riskStatisticsSemiDeviation{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Variance of the sample values falling below zero. Throws if fewer than two sample values
-- fall below zero.
{#fun qlRiskStatisticsDownsideVariance as riskStatisticsDownsideVariance{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Square root of 'riskStatisticsDownsideVariance'.
{#fun qlRiskStatisticsDownsideDeviation as riskStatisticsDownsideDeviation{withRealVector*`RealVector'& -- ^sample
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Empirical @y@-th percentile of the sample; @y@ must lie in @(0.0, 1.0]@.
{#fun qlRiskStatisticsPercentile as riskStatisticsPercentile{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^y
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |@y@-th percentile assuming the sample is gaussian (mean\/standard deviation matched); @y@
-- must lie in @(0.0, 1.0)@.
{#fun qlRiskStatisticsGaussianPercentile as riskStatisticsGaussianPercentile{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^y
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Empirical value-at-risk at the given @centile@, which must lie in @[0.9, 1.0)@ — a loss
-- (non-negative), the negative of the empirical @(1-centile)@-th percentile floored at zero.
{#fun qlRiskStatisticsValueAtRisk as riskStatisticsValueAtRisk{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^centile
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Value-at-risk at the given @centile@ assuming the sample is gaussian; @centile@ must lie in
-- @[0.9, 1.0)@.
{#fun qlRiskStatisticsGaussianValueAtRisk as riskStatisticsGaussianValueAtRisk{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^centile
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Empirical expected shortfall (conditional value-at-risk) at the given @centile@, which must
-- lie in @[0.9, 1.0)@: the average of the sample values below the value-at-risk threshold.
-- Throws if the sample is empty, or if no sample value falls below the threshold.
{#fun qlRiskStatisticsExpectedShortfall as riskStatisticsExpectedShortfall{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^centile
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Expected shortfall at the given @centile@ assuming the sample is gaussian; @centile@ must
-- lie in @[0.9, 1.0)@.
{#fun qlRiskStatisticsGaussianExpectedShortfall as riskStatisticsGaussianExpectedShortfall{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^centile
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Empirical potential upside (the reciprocal notion of value-at-risk, floored at zero) at the
-- given @centile@, which must lie in @[0.9, 1.0)@.
{#fun qlRiskStatisticsPotentialUpside as riskStatisticsPotentialUpside{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^centile
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Potential upside at the given @centile@ assuming the sample is gaussian; @centile@ must lie
-- in @[0.9, 1.0)@.
{#fun qlRiskStatisticsGaussianPotentialUpside as riskStatisticsGaussianPotentialUpside{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^centile
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Variance of the sample values falling below @target@ (Dembo\/Freeman regret). Throws if
-- fewer than two sample values fall below @target@.
{#fun qlRiskStatisticsRegret as riskStatisticsRegret{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^target
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability (fraction of the sample, by count) of falling below @target@. Throws if the
-- sample is empty.
{#fun qlRiskStatisticsShortfall as riskStatisticsShortfall{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^target
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Average shortfall below @target@, i.e. the mean of @target - x@ over sample values @x@
-- below @target@. Throws if no sample value falls below @target@.
{#fun qlRiskStatisticsAverageShortfall as riskStatisticsAverageShortfall{withRealVector*`RealVector'& -- ^sample
  ,`Double' -- ^target
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

toMatrixDouble :: (Word, Word, [Double]) -> Matrix Double
toMatrixDouble (r, c, d) = Matrix r c d

-- |Eigenvalues and eigenvectors of a real symmetric matrix, computed by the symmetric threshold
-- Jacobi algorithm. The eigenvalues come back in decreasing order, and the eigenvectors are the
-- /columns/ of the returned matrix: column @i@ belongs to the @i@-th eigenvalue.
symmetricSchurDecomposition :: Matrix Double -- ^symmetric matrix
  -> IO ([Double], Matrix Double) -- ^eigenvalues, eigenvectors as columns
symmetricSchurDecomposition (Matrix mr mc md) = do
  (values, r, c, vectors) <- qlSymmetricSchurDecomposition mr mc md
  pure (values, Matrix r c vectors)
{#fun qlSymmetricSchurDecomposition{fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,preArray-`[Double]'&peekDoubleArray*
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Pseudo square root @S@ of a real symmetric matrix @M@, i.e. the matrix with @S*transpose S == M@.
-- When @M@ is not positive semi-definite the given 'SalvagingAlgorithm' approximates it; with
-- 'SalvagingNone' a non-positive-semi-definite input throws instead.
pseudoSqrt :: Matrix Double -- ^symmetric matrix
  -> SalvagingAlgorithm
  -> IO (Matrix Double)
pseudoSqrt (Matrix mr mc md) salvaging = toMatrixDouble <$> qlPseudoSqrt mr mc md salvaging
{#fun qlPseudoSqrt{fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,fromEnumC`SalvagingAlgorithm'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Rank-reduced pseudo square root of a real symmetric matrix: the result has rank at most
-- @maxRank@. If @maxRank@ reaches the matrix size, the given percentage of the eigenvalues' sum
-- is retained instead.
rankReducedSqrt :: Matrix Double -- ^symmetric matrix
  -> Word -- ^maxRank
  -> Double -- ^componentRetainedPercentage
  -> SalvagingAlgorithm
  -> IO (Matrix Double)
rankReducedSqrt (Matrix mr mc md) maxRank retained salvaging =
  toMatrixDouble <$> qlRankReducedSqrt mr mc md maxRank retained salvaging
{#fun qlRankReducedSqrt{fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,fromIntegral`Word',`Double',fromEnumC`SalvagingAlgorithm'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Cholesky factor @L@ of a symmetric positive-definite matrix @M@, i.e. the lower-triangular
-- matrix with @L*transpose L == M@. Pass @True@ for @flexible@ to accept a merely positive
-- /semi/-definite (rank-deficient) input, whose factor is completed with zeroes rather than
-- producing @nan@.
choleskyDecomposition :: Matrix Double -- ^symmetric matrix
  -> Bool -- ^flexible
  -> IO (Matrix Double)
choleskyDecomposition (Matrix mr mc md) flexible = toMatrixDouble <$> qlCholeskyDecomposition mr mc md flexible
{#fun qlCholeskyDecomposition{fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,`Bool'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Solves @M*x == b@ given the Cholesky factor @L@ of @M@ -- the first argument is the factor
-- returned by 'choleskyDecomposition', not @M@ itself.
choleskySolveFor :: Matrix Double -- ^Cholesky factor L
  -> [Double] -- ^b
  -> IO [Double]
choleskySolveFor (Matrix mr mc md) b = qlCholeskySolveFor mr mc md b
{#fun qlCholeskySolveFor{fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,withDoubleArray*`[Double]'&
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
