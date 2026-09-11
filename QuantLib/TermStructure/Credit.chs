module QuantLib.TermStructure.Credit
  (
    -- * Types
    DefaultProbabilityTermStructure
  , DefaultProbabilityHelper
  , ProbabilityTrait(..)
  , Reference(..)
  , TermPoint(..)
  , TermInterval(..)
  , IterativeBootstrapOpts(..)

    -- * Constructors
    -- ** Flat and spreaded curves
  , factorSpreadedHazardRateCurve
  , flatHazardRate
  , spreadedHazardRateCurve
    -- ** Helpers and bootstrapped curves
  , spreadCdsHelper
  , upfrontCdsHelper
  , interpolatedDefaultDensityCurve
  , interpolatedHazardRateCurve
  , interpolatedSurvivalProbabilityCurve
  , defaultIterativeBootstrapOpts
  , piecewiseDefaultCurve

    -- * Inspectors
  , defaultProbability
  , hazardRate
  , survivalProbability
  , defaultDensity
  , defaultProbabilityBetween
  , impliedQuote
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
{#import QuantLib.Instrument#}(PricingModel)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(DateGenerationRule, Frequency)
import QuantLib.Internal.Common
import QuantLib.TermStructure (Reference(..), TermPoint(..), TermInterval(..), setExtrapolation)
import Data.List.NonEmpty(NonEmpty, toList)

{#enum ProbabilityTrait{} deriving(Show, Eq, Read)#}

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlDefaultProbabilityHelper as DefaultProbabilityHelper foreign -> CDefaultProbabilityHelper nocode#}

-- |a curve whose hazard rate is another curve's, scaled by a spread factor
{#fun qlFactorSpreadedHazardRateCurve as factorSpreadedHazardRateCurve{withGenTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- |Flat hazard-rate curve with either a fixed or evaluation-date-relative reference point.
flatHazardRate :: Reference -> GenQuote q -> DayCounter -> IO DefaultProbabilityTermStructure
flatHazardRate (ReferenceDate d) = flatHazardRateFixed d
flatHazardRate (SettlementDays n cal) = flatHazardRateMovingRaw n cal
{#fun qlFlatHazardRate1 as flatHazardRateMovingRaw{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}
{#fun qlFlatHazardRate as flatHazardRateFixed{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- |a curve whose survival probability is another curve's, multiplied by a spread factor
{#fun qlSpreadedHazardRateCurve as spreadedHazardRateCurve{withGenTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

{#fun qlDefaultProbabilityTermStructureDefaultProbability as defaultProbabilityAtDateRaw{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureHazardRate1 as hazardRateAtTimeRaw{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureHazardRate as hazardRateAtDateRaw{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureSurvivalProbability1 as survivalProbabilityAtTimeRaw{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureSurvivalProbability as survivalProbabilityAtDateRaw{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultDensity1 as defaultDensityAtTimeRaw{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultDensity as defaultDensityAtDateRaw{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultProbability1 as defaultProbabilityAtTimeRaw{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultProbability2 as defaultProbabilityBetweenDatesRaw{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultProbability3 as defaultProbabilityBetweenTimesRaw{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Hazard rate at a date or year fraction, with annual frequency and continuous compounding.
hazardRate :: DefaultProbabilityTermStructure -> TermPoint -> Bool -> IO Double
hazardRate curve point = case point of
  DatePoint d -> hazardRateAtDateRaw curve d
  TimePoint t -> hazardRateAtTimeRaw curve t

-- |Survival probability from the reference point to a date or year fraction.
survivalProbability :: DefaultProbabilityTermStructure -> TermPoint -> Bool -> IO Double
survivalProbability curve point = case point of
  DatePoint d -> survivalProbabilityAtDateRaw curve d
  TimePoint t -> survivalProbabilityAtTimeRaw curve t

-- |Default density at a date or year fraction.
defaultDensity :: DefaultProbabilityTermStructure -> TermPoint -> Bool -> IO Double
defaultDensity curve point = case point of
  DatePoint d -> defaultDensityAtDateRaw curve d
  TimePoint t -> defaultDensityAtTimeRaw curve t

-- |Default probability from the reference point to a date or year fraction.
defaultProbability :: DefaultProbabilityTermStructure -> TermPoint -> Bool -> IO Double
defaultProbability curve point = case point of
  DatePoint d -> defaultProbabilityAtDateRaw curve d
  TimePoint t -> defaultProbabilityAtTimeRaw curve t

-- |Default probability over a same-representation date or year-fraction interval.
defaultProbabilityBetween :: DefaultProbabilityTermStructure -> TermInterval -> Bool -> IO Double
defaultProbabilityBetween curve interval = case interval of
  DateInterval d1 d2 -> defaultProbabilityBetweenDatesRaw curve d1 d2
  TimeInterval t1 t2 -> defaultProbabilityBetweenTimesRaw curve t1 t2

-- |bootstrap helper for a CDS quoted by running spread
{#fun qlSpreadCdsHelper as spreadCdsHelper{withQuote*`GenQuote q' -- ^runningSpread
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,`Int' -- ^settlementDays
  ,withCalendar*`Calendar',`Frequency',fromEnumC`BusinessDayConvention',`DateGenerationRule',withDayCounter*`DayCounter'
  ,`Double' -- recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,`Bool' -- ^settlesAccrual
  ,`Bool' -- ^paysAtDefaultTime
  ,withMaybeDay*`Maybe Day' -- ^startDate
  ,withDayCounter*`DayCounter' -- ^lastPeriodDayCounter
  ,`Bool' -- ^rebatesAccrual
  ,`PricingModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityHelper'peekDefaultProbabilityHelper*#}

-- |the upfront must be quoted in fractional units.
{#fun qlUpfrontCdsHelper as upfrontCdsHelper{withQuote*`GenQuote q' -- ^upfront
  ,`Double' -- ^runningSpread
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,`Int' -- ^settlementDays
  ,withCalendar*`Calendar',`Frequency',fromEnumC`BusinessDayConvention',`DateGenerationRule',withDayCounter*`DayCounter'
  ,`Double' -- ^recoveryDate
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,fromIntegral`Word' -- ^upfrontSettlementDays
  ,`Bool' -- &settlesAccrual
  ,`Bool' -- ^paysAtDefaultTime
  ,withMaybeDay*`Maybe Day' -- ^startDate
  ,withDayCounter*`DayCounter' -- ^lastPeriodDayCounter
  ,`Bool' -- ^rebatesAccrual
  ,`PricingModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityHelper'peekDefaultProbabilityHelper*#}

-- |The fair running-spread/upfront quote implied by the helper's current market data and pricing
-- engine -- the value that would make the quoted instrument re-price at par. Requires the helper
-- to have already been used to bootstrap a curve (throws otherwise, per upstream).
{#fun qlDefaultProbabilityHelperImpliedQuote as impliedQuote{withDefaultProbabilityHelper*`DefaultProbabilityHelper'
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

interpolatedDefaultDensityCurve :: NonEmpty (Day, Double) -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -> Bool -> IO DefaultProbabilityTermStructure
interpolatedDefaultDensityCurve d dc c q i ex = do
  curve <- uncurryNested (qlInterpolatedDefaultDensityCurve dd dq dc c qq qd) (qlInterpolation i)
  setExtrapolation curve ex
  pure curve
  where (qd, qq) = unzip q
        (dd, dq) = unzip (toList d)

-- |default-probability term structure built by interpolating default densities at given dates
{#fun qlInterpolatedDefaultDensityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

interpolatedHazardRateCurve :: NonEmpty (Day, Double) -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation
  -> Bool -- ^extrapolate past the curve's max date
  -> IO DefaultProbabilityTermStructure
interpolatedHazardRateCurve d dc c q i ex = uncurryNested (qlInterpolatedHazardRateCurve dd dq dc c qq qd) (qlInterpolation i) ex where {(qd, qq) = unzip q; (dd, dq) = unzip (toList d)}

-- |default-probability term structure built by interpolating hazard rates at given dates
{#fun qlInterpolatedHazardRateCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',`Bool',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

interpolatedSurvivalProbabilityCurve :: NonEmpty (Day, Double) -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -> Bool -> IO DefaultProbabilityTermStructure
interpolatedSurvivalProbabilityCurve d dc c q i ex = do
  curve <- uncurryNested (qlInterpolatedSurvivalProbabilityCurve dd dq dc c qq qd) (qlInterpolation i)
  setExtrapolation curve ex
  pure curve
  where (qd, qq) = unzip q
        (dd, dq) = unzip (toList d)

-- |default-probability term structure built by interpolating survival probabilities at given dates
{#fun qlInterpolatedSurvivalProbabilityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- QuantLib uses Null<Real>() rather than a number for these defaults.
nullableDouble :: Maybe Double -> Double
nullableDouble = realToFrac . fromMaybeDouble

-- |Default-probability term structure bootstrapped from CDS/default helpers with either a fixed
-- or evaluation-date-relative reference point and complete iterative-bootstrap settings.
piecewiseDefaultCurve :: Reference
  -> NonEmpty DefaultProbabilityHelper -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps paired with their dates
  -> ProbabilityTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> Bool -- ^extrapolate past the curve's max date
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve reference h dc q t i b ex = do
  curve <- case reference of
    ReferenceDate d -> uncurryNested (piecewiseDefaultCurve_ d hs dc qq qd t) (qlInterpolation i)
      (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
      (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
    SettlementDays d c -> uncurryNested (piecewiseDefaultCurve1_ d c hs dc qq qd t) (qlInterpolation i)
      (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
      (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
  setExtrapolation curve ex
  pure curve
  where (qd, qq) = unzip q
        hs = toList h
{#fun qlPiecewiseDefaultCurve as piecewiseDefaultCurve_{withDay*`Day',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}
{#fun qlPiecewiseDefaultCurve1 as piecewiseDefaultCurve1_{fromIntegral`Word',withCalendar*`Calendar',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
