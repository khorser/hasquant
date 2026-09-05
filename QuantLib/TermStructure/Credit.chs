module QuantLib.TermStructure.Credit
  (
    ProbabilityTrait(..)
  , DefaultProbabilityTermStructure
  , DefaultProbabilityHelper
  , factorSpreadedHazardRateCurve
  , flatHazardRate'
  , flatHazardRate
  , spreadedHazardRateCurve
  , defaultProbability
  , hazardRate'
  , hazardRate
  , survivalProbability'
  , survivalProbability
  , defaultDensity'
  , defaultDensity
  , defaultProbability'
  , defaultProbabilityBetween
  , defaultProbabilityBetween'
  , spreadCdsHelper
  , upfrontCdsHelper
  , interpolatedDefaultDensityCurve
  , interpolatedHazardRateCurve
  , interpolatedSurvivalProbabilityCurve
  , IterativeBootstrapOpts(..)
  , defaultIterativeBootstrapOpts
  , piecewiseDefaultCurve
  , piecewiseDefaultCurve'
  , piecewiseDefaultCurveFull
  , piecewiseDefaultCurveFull'
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

-- |flat hazard-rate curve anchored at a settlement date
{#fun qlFlatHazardRate1 as flatHazardRate'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- |flat hazard-rate curve anchored at a reference date
{#fun qlFlatHazardRate as flatHazardRate{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- |a curve whose survival probability is another curve's, multiplied by a spread factor
{#fun qlSpreadedHazardRateCurve as spreadedHazardRateCurve{withGenTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- |default probability from the reference date until a given date
{#fun qlDefaultProbabilityTermStructureDefaultProbability as defaultProbability{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |hazard rate at a given time, with annual frequency and continuous compounding
{#fun qlDefaultProbabilityTermStructureHazardRate1 as hazardRate'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |hazard rate at a given date, with annual frequency and continuous compounding
{#fun qlDefaultProbabilityTermStructureHazardRate as hazardRate{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureSurvivalProbability1 as survivalProbability'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |survival probability from the reference date until a given date
{#fun qlDefaultProbabilityTermStructureSurvivalProbability as survivalProbability{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureDefaultDensity1 as defaultDensity'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |default density at a given date
{#fun qlDefaultProbabilityTermStructureDefaultDensity as defaultDensity{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureDefaultProbability1 as defaultProbability'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |probability of default between two given dates
{#fun qlDefaultProbabilityTermStructureDefaultProbability2 as defaultProbabilityBetween{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |probability of default between two given times
{#fun qlDefaultProbabilityTermStructureDefaultProbability3 as defaultProbabilityBetween'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

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

interpolatedDefaultDensityCurve :: NonEmpty (Day, Double) -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedDefaultDensityCurve d dc c q i = uncurryNested (qlInterpolatedDefaultDensityCurve dd dq dc c qq qd) (qlInterpolation i) where {(qd, qq) = unzip q; (dd, dq) = unzip (toList d)}

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
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedSurvivalProbabilityCurve d dc c q i = uncurryNested (qlInterpolatedSurvivalProbabilityCurve dd dq dc c qq qd) (qlInterpolation i) where {(qd, qq) = unzip q; (dd, dq) = unzip (toList d)}

-- |default-probability term structure built by interpolating survival probabilities at given dates
{#fun qlInterpolatedSurvivalProbabilityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- QuantLib uses Null<Real>() rather than a number for these defaults.
nullableDouble :: Maybe Double -> Double
nullableDouble = realToFrac . fromMaybeDouble

-- |Default-probability term structure bootstrapped from CDS/default helpers, anchored at an
-- explicit reference date and using QuantLib's default iterative-bootstrap settings.
piecewiseDefaultCurve :: Day -- ^referenceDate
  -> NonEmpty DefaultProbabilityHelper -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps paired with their dates
  -> ProbabilityTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve d h dc q t i =
  piecewiseDefaultCurveFull d h dc q t i defaultIterativeBootstrapOpts

-- |Like 'piecewiseDefaultCurve', but exposes every @IterativeBootstrap@ setting. Start from
-- 'defaultIterativeBootstrapOpts' and override selected fields. Setting 'ibDontThrow' to 'True'
-- returns the best fallback pillar value found after a bootstrap failure; this is a recovery
-- option and does not establish that the resulting curve reprices its instruments.
piecewiseDefaultCurveFull :: Day -- ^referenceDate
  -> NonEmpty DefaultProbabilityHelper -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps paired with their dates
  -> ProbabilityTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurveFull d h dc q t i b =
  uncurryNested (piecewiseDefaultCurve_ d (toList h) dc qq qd t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
  where (qd, qq) = unzip q
{#fun qlPiecewiseDefaultCurve as piecewiseDefaultCurve_{withDay*`Day',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- |Default-probability term structure bootstrapped from CDS/default helpers, anchored at a
-- settlement-days/calendar pair and using QuantLib's default iterative-bootstrap settings.
piecewiseDefaultCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty DefaultProbabilityHelper -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps paired with their dates
  -> ProbabilityTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve' d c h dc q t i =
  piecewiseDefaultCurveFull' d c h dc q t i defaultIterativeBootstrapOpts

-- |Like 'piecewiseDefaultCurve'', but exposes every @IterativeBootstrap@ setting. See
-- 'piecewiseDefaultCurveFull' for the fallback semantics of 'ibDontThrow'.
piecewiseDefaultCurveFull' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> NonEmpty DefaultProbabilityHelper -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Day, GenQuote q)] -- ^jumps paired with their dates
  -> ProbabilityTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IterativeBootstrapOpts -- ^bootstrap settings
  -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurveFull' d c h dc q t i b =
  uncurryNested (piecewiseDefaultCurve1_ d c (toList h) dc qq qd t) (qlInterpolation i)
    (nullableDouble (ibAccuracy b)) (nullableDouble (ibMinValue b)) (nullableDouble (ibMaxValue b))
    (ibMaxAttempts b) (ibMaxFactor b) (ibMinFactor b) (ibDontThrow b) (ibDontThrowSteps b) (ibMaxEvaluations b)
  where (qd, qq) = unzip q
{#fun qlPiecewiseDefaultCurve1 as piecewiseDefaultCurve1_{fromIntegral`Word',withCalendar*`Calendar',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',`Double',`Double',`Double',fromIntegral`Word',`Double',`Double',`Bool',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
