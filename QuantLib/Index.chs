module QuantLib.Index
  (
    Index
  , GenIndex

  , addFixing
  , fixingCalendar
  , fixing
  , hasHistoricalFixing
  , isValidFixingDate
  , addFixings
  , clearFixings
  , fixingHistory
  , fixingHistoryNames
  , clearAllFixingHistories
  , asIndex

  , HistoricalIndexAnalysis
  , historicalIndexAnalysis
  , historicalIndexAnalysisSkippedDates
  , historicalIndexAnalysisSkippedDatesErrorMessage
  , historicalIndexAnalysisMean
  , historicalIndexAnalysisStandardDeviation
  , historicalIndexAnalysisSkewness
  , historicalIndexAnalysisKurtosis
  , historicalIndexAnalysisMin
  , historicalIndexAnalysisMax
  , historicalIndexAnalysisSemiVariance
  , historicalIndexAnalysisSemiDeviation
  , historicalIndexAnalysisDownsideVariance
  , historicalIndexAnalysisDownsideDeviation
  , historicalIndexAnalysisPercentile
  , historicalIndexAnalysisGaussianPercentile
  , historicalIndexAnalysisValueAtRisk
  , historicalIndexAnalysisGaussianValueAtRisk
  , historicalIndexAnalysisExpectedShortfall
  , historicalIndexAnalysisGaussianExpectedShortfall
  , historicalIndexAnalysisCovariance
  , historicalIndexAnalysisCorrelation
  ) where
import QuantLib.Internal
import QuantLib.Internal.Common
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *QlIndex as Index foreign -> CIndex' nocode#}

-- |stores the historical fixing at the given date; the date must be the actual calendar date of the fixing, not a settlement date
{#fun qlIndexAddFixing as addFixing{withIndex*`GenIndex idx',withDay*`Day',`Double' -- ^fixing
  ,`Bool' -- ^forceOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |returns the calendar defining valid fixing dates
{#fun qlIndexFixingCalendar as fixingCalendar{withIndex*`GenIndex idx',preErrorCheck-`String'errorCheck*-}->`Calendar'peekCalendar*#}

-- |returns the fixing at the given date, forecasting it if not available and /forecastTodaysFixing/ is true
{#fun qlIndexFixing as fixing{withIndex*`GenIndex idx',withDay*`Day',`Bool' -- ^forecastTodaysFixing
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |whether a historical fixing has been stored for the given date
{#fun qlIndexHasHistoricalFixing as hasHistoricalFixing{withIndex*`GenIndex idx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |whether the given date is a valid fixing date for this index
{#fun qlIndexIsValidFixingDate as isValidFixingDate{withIndex*`GenIndex idx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |stores historical fixings at the given dates; the date and value lists must have equal length
{#fun qlIndexAddFixings as addFixings{withIndex*`GenIndex idx',withDayArray*`[Day]'&,withDoubleArrayRaw*`[Double]',`Bool' -- ^forceOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |clears all stored historical fixings for this index
{#fun qlIndexClearFixings as clearFixings{withIndex*`GenIndex idx',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Returns every stored native fixing for this index, in ascending date order.  This is a
-- snapshot copied out of QuantLib's process-global fixing store; it has no forecasting behavior.
fixingHistory :: GenIndex idx -> IO [(Day, Double)]
fixingHistory i = do
  (ds, vs) <- qlIndexFixingHistory i
  return $ zip ds vs
{#fun qlIndexFixingHistory{withIndex*`GenIndex idx'
  ,preArray-`[Day]'&peekDayArray*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Returns the names with an entry in QuantLib's process-global fixing store.  Names are
-- case-insensitive in that store and can be shared by separate index instances.
{#fun qlIndexManagerHistories as fixingHistoryNames{preArray-`[String]'&peekCStringArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Clears every native fixing history in QuantLib's process-global store, for all index names.
-- This affects other index instances and is intended for explicit session or test cleanup.
{#fun qlIndexManagerClearHistories as clearAllFixingHistories{preErrorCheck-`String'errorCheck*-}->`()'#}

{#pointer *QlHistoricalIndexAnalysis as HistoricalIndexAnalysis foreign -> CHistoricalIndexAnalysis nocode#}

-- |Computes 'SequenceStatistics' (mean\/standard deviation\/skewness\/kurtosis\/min\/max\/semi-
-- and downside-variance and -deviation\/percentiles\/value-at-risk\/expected shortfall,
-- empirical and gaussian-assumption\/covariance\/correlation) over historical fixings of the
-- given indexes, sampled every @step@ between @startDate@ and @endDate@. A date/index pair whose
-- fixing is unavailable is recorded in 'historicalIndexAnalysisSkippedDates'\/
-- 'historicalIndexAnalysisSkippedDatesErrorMessage' rather than failing the whole analysis.
-- 'SequenceStatistics' itself isn't given a dedicated Haskell type: it's only ever the
-- accumulator this constructor fills internally, with no other use in hasquant, so its full
-- risk-statistics surface is exposed directly as accessors here (see CLAUDE.md's \"don't mirror
-- the C++ hierarchy 1:1\").
{#fun qlHistoricalIndexAnalysis as historicalIndexAnalysis{withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^step
  ,withIndexArray*`[Index]'&
  ,preErrorCheck-`String'errorCheck*-}->`HistoricalIndexAnalysis'peekHistoricalIndexAnalysis*#}

-- |Fixing dates skipped because no historical fixing was available for at least one index.
{#fun qlHistoricalIndexAnalysisSkippedDates as historicalIndexAnalysisSkippedDates{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Day]'&peekDayArray*}->`()'#}

-- |The error message recorded for each date in 'historicalIndexAnalysisSkippedDates', in the same order.
{#fun qlHistoricalIndexAnalysisSkippedDatesErrorMessage as historicalIndexAnalysisSkippedDatesErrorMessage{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[String]'&peekCStringArray*}->`()'#}

-- |Per-index mean of the historical relative returns actually sampled.
{#fun qlHistoricalIndexAnalysisMean as historicalIndexAnalysisMean{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index standard deviation of the historical relative returns actually sampled.
{#fun qlHistoricalIndexAnalysisStandardDeviation as historicalIndexAnalysisStandardDeviation{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index skewness of the historical relative returns actually sampled.
{#fun qlHistoricalIndexAnalysisSkewness as historicalIndexAnalysisSkewness{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index (excess) kurtosis of the historical relative returns actually sampled.
{#fun qlHistoricalIndexAnalysisKurtosis as historicalIndexAnalysisKurtosis{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index minimum of the historical relative returns actually sampled.
{#fun qlHistoricalIndexAnalysisMin as historicalIndexAnalysisMin{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index maximum of the historical relative returns actually sampled.
{#fun qlHistoricalIndexAnalysisMax as historicalIndexAnalysisMax{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index variance of the historical relative returns falling below the mean.
{#fun qlHistoricalIndexAnalysisSemiVariance as historicalIndexAnalysisSemiVariance{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index square root of 'historicalIndexAnalysisSemiVariance'.
{#fun qlHistoricalIndexAnalysisSemiDeviation as historicalIndexAnalysisSemiDeviation{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index variance of the historical relative returns falling below zero.
{#fun qlHistoricalIndexAnalysisDownsideVariance as historicalIndexAnalysisDownsideVariance{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index square root of 'historicalIndexAnalysisDownsideVariance'.
{#fun qlHistoricalIndexAnalysisDownsideDeviation as historicalIndexAnalysisDownsideDeviation{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index empirical @y@-th percentile of the historical relative returns actually sampled;
-- @y@ must lie in @[0.9, 1.0)@.
{#fun qlHistoricalIndexAnalysisPercentile as historicalIndexAnalysisPercentile{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,`Double' -- ^y
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index @y@-th percentile assuming the historical relative returns are gaussian; @y@ must lie in @[0.9, 1.0)@.
{#fun qlHistoricalIndexAnalysisGaussianPercentile as historicalIndexAnalysisGaussianPercentile{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,`Double' -- ^y
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index empirical value-at-risk at the given @centile@, which must lie in @[0.9, 1.0)@.
{#fun qlHistoricalIndexAnalysisValueAtRisk as historicalIndexAnalysisValueAtRisk{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,`Double' -- ^centile
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index value-at-risk at the given @centile@ assuming the historical relative returns are gaussian; @centile@ must lie in @[0.9, 1.0)@.
{#fun qlHistoricalIndexAnalysisGaussianValueAtRisk as historicalIndexAnalysisGaussianValueAtRisk{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,`Double' -- ^centile
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index empirical expected shortfall at the given @centile@, which must lie in @[0.9, 1.0)@.
-- Throws if no sampled return falls below the value-at-risk threshold.
{#fun qlHistoricalIndexAnalysisExpectedShortfall as historicalIndexAnalysisExpectedShortfall{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,`Double' -- ^centile
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-index expected shortfall at the given @centile@ assuming the historical relative returns
-- are gaussian; @centile@ must lie in @[0.9, 1.0)@.
{#fun qlHistoricalIndexAnalysisGaussianExpectedShortfall as historicalIndexAnalysisGaussianExpectedShortfall{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,`Double' -- ^centile
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

toMatrixDouble :: (Word, Word, [Double]) -> Matrix Double
toMatrixDouble (r, c, d) = Matrix r c d

-- |Covariance matrix of the historical relative returns across indexes.
historicalIndexAnalysisCovariance :: HistoricalIndexAnalysis -> IO (Matrix Double)
historicalIndexAnalysisCovariance hra = toMatrixDouble <$> qlHistoricalIndexAnalysisCovariance hra
{#fun qlHistoricalIndexAnalysisCovariance{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Correlation matrix of the historical relative returns across indexes.
historicalIndexAnalysisCorrelation :: HistoricalIndexAnalysis -> IO (Matrix Double)
historicalIndexAnalysisCorrelation hra = toMatrixDouble <$> qlHistoricalIndexAnalysisCorrelation hra
{#fun qlHistoricalIndexAnalysisCorrelation{withHistoricalIndexAnalysis*`HistoricalIndexAnalysis'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
