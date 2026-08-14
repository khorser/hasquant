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
  , piecewiseDefaultCurve
  , piecewiseDefaultCurve'
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
{#import QuantLib.Instrument#}(PricingModel)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(DateGenerationRule, Frequency)
import QuantLib.Internal.Enum

{#enum ProbabilityTrait{} deriving(Show, Eq)#}

{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}

{#pointer *QlDefaultProbabilityHelper as DefaultProbabilityHelper foreign -> CDefaultProbabilityHelper nocode#}

{#fun qlFactorSpreadedHazardRateCurve as factorSpreadedHazardRateCurve{withGenTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}
{#fun qlFlatHazardRate1 as flatHazardRate'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}
{#fun qlFlatHazardRate as flatHazardRate{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}
{#fun qlSpreadedHazardRateCurve as spreadedHazardRateCurve{withGenTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}
{#fun qlDefaultProbabilityTermStructureDefaultProbability as defaultProbability{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureHazardRate1 as hazardRate'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureHazardRate as hazardRate{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureSurvivalProbability1 as survivalProbability'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureSurvivalProbability as survivalProbability{withGenTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureDefaultDensity1 as defaultDensity'{withGenTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
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

{#fun qlSpreadCdsHelper as spreadCdsHelper{withQuote*`GenQuote q' -- ^runningSpread
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,`Int' -- ^settlementDays
  ,withCalendar*`Calendar',`Frequency',`BusinessDayConvention',`DateGenerationRule',withDayCounter*`DayCounter'
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
  ,withCalendar*`Calendar',`Frequency',`BusinessDayConvention',`DateGenerationRule',withDayCounter*`DayCounter'
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

interpolatedDefaultDensityCurve :: [(Day, Double)] -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedDefaultDensityCurve d dc c q i = uncurryNested (qlInterpolatedDefaultDensityCurve dd dq dc c qq qd) (qlInterpolation i) where {(qd, qq) = unzip q; (dd, dq) = unzip d}
{#fun qlInterpolatedDefaultDensityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

interpolatedHazardRateCurve :: [(Day, Double)] -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation
  -> Bool -- ^extrapolate past the curve's max date
  -> IO DefaultProbabilityTermStructure
interpolatedHazardRateCurve d dc c q i ex = uncurryNested (qlInterpolatedHazardRateCurve dd dq dc c qq qd) (qlInterpolation i) ex where {(qd, qq) = unzip q; (dd, dq) = unzip d}
{#fun qlInterpolatedHazardRateCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',`Bool',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

interpolatedSurvivalProbabilityCurve :: [(Day, Double)] -> DayCounter -> Calendar -> [(Day, GenQuote q)] -- ^jumps
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedSurvivalProbabilityCurve d dc c q i = uncurryNested (qlInterpolatedSurvivalProbabilityCurve dd dq dc c qq qd) (qlInterpolation i) where {(qd, qq) = unzip q; (dd, dq) = unzip d}
{#fun qlInterpolatedSurvivalProbabilityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

piecewiseDefaultCurve :: Day -> [DefaultProbabilityHelper] -> DayCounter -> [(Day, GenQuote q)] -- ^jumps
  -> ProbabilityTrait -> Interpolation -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve d h dc q t i = uncurryNested (qlPiecewiseDefaultCurve d h dc qq qd t) (qlInterpolation i) where (qd, qq) = unzip q
{#fun qlPiecewiseDefaultCurve{withDay*`Day',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

piecewiseDefaultCurve' :: Word -> Calendar -> [DefaultProbabilityHelper] -> DayCounter -> [(Day, GenQuote q)] -- ^jumps
  -> ProbabilityTrait -> Interpolation -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve' d c h dc q t i = uncurryNested (qlPiecewiseDefaultCurve1 d c h dc qq qd t) (qlInterpolation i) where (qd, qq) = unzip q
{#fun qlPiecewiseDefaultCurve1{fromIntegral`Word',withCalendar*`Calendar',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote q]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
