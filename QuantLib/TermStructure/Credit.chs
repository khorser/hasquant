{-# LANGUAGE MultiParamTypeClasses, TypeOperators #-}
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
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(DateGenerationRule, Frequency)
import QuantLib.Internal.Enum

{#enum ProbabilityTrait{} deriving(Show, Eq)#}

{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote nocode#}

{#pointer *QlDefaultProbabilityHelper as DefaultProbabilityHelper foreign -> CDefaultProbabilityHelper nocode#}

{#fun qlFactorSpreadedHazardRateCurve as factorSpreadedHazardRateCurve{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote a',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

{#fun qlFlatHazardRate1 as flatHazardRate'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

{#fun qlFlatHazardRate as flatHazardRate{withDay*`Day',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

{#fun qlSpreadedHazardRateCurve as spreadedHazardRateCurve{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withQuote*`GenQuote a',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

{#fun qlDefaultProbabilityTermStructureDefaultProbability as defaultProbability{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureHazardRate1 as hazardRate'{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureHazardRate as hazardRate{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureSurvivalProbability1 as survivalProbability'{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureSurvivalProbability as survivalProbability{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureDefaultDensity1 as defaultDensity'{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlDefaultProbabilityTermStructureDefaultDensity as defaultDensity{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureDefaultProbability1 as defaultProbability'{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |probability of default between two given dates
{#fun qlDefaultProbabilityTermStructureDefaultProbability2 as defaultProbabilityBetween{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',withDay*`Day',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |probability of default between two given times
{#fun qlDefaultProbabilityTermStructureDefaultProbability3 as defaultProbabilityBetween'{withDefaultProbabilityTermStructure*`DefaultProbabilityTermStructure',`Double',`Double',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlSpreadCdsHelper as spreadCdsHelper{withQuote*`GenQuote a' -- ^runningSpread
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,`Int' -- ^settlementDays
  ,withCalendar*`Calendar',`Frequency',`BusinessDayConvention',`DateGenerationRule',withDayCounter*`DayCounter'
  ,`Double' -- recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^discountCurve
  ,`Bool' -- ^settlesAccrual
  ,`Bool' -- ^paysAtDefaultTime
  ,preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityHelper'peekDefaultProbabilityHelper*#}

-- |the upfront must be quoted in fractional units.
{#fun qlUpfrontCdsHelper as upfrontCdsHelper{withQuote*`GenQuote a' -- ^upfront
  ,`Double' -- ^runningSpread
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,`Int' -- ^settlementDays
  ,withCalendar*`Calendar',`Frequency',`BusinessDayConvention',`DateGenerationRule',withDayCounter*`DayCounter'
  ,`Double' -- ^recoveryDate
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^discountCurve
  ,fromIntegral`Word' -- ^upfrontSettlementDays
  ,`Bool' -- &settlesAccrual
  ,`Bool' -- ^paysAtDefaultTime
  ,preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityHelper'peekDefaultProbabilityHelper*#}

interpolatedDefaultDensityCurve :: [(Day, Double)] -> DayCounter -> Calendar -> [(Day, GenQuote a)] -- ^jumps
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedDefaultDensityCurve d dc c q i = uncurry' (qlInterpolatedDefaultDensityCurve dd dq dc c qq qd) (qlInterpolation i) where {(qd, qq) = unzip q; (dd, dq) = unzip d}
{#fun qlInterpolatedDefaultDensityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

interpolatedHazardRateCurve :: [(Day, Double)] -> DayCounter -> Calendar -> [(Day, GenQuote a)] -- ^jumps
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedHazardRateCurve d dc c q i = uncurry' (qlInterpolatedHazardRateCurve dd dq dc c qq qd) (qlInterpolation i)  where {(qd, qq) = unzip q; (dd, dq) = unzip d}
{#fun qlInterpolatedHazardRateCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

interpolatedSurvivalProbabilityCurve :: [(Day, Double)] -> DayCounter -> Calendar -> [(Day, GenQuote a)] -- ^jumps
  -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedSurvivalProbabilityCurve d dc c q i = uncurry' (qlInterpolatedSurvivalProbabilityCurve dd dq dc c qq qd) (qlInterpolation i) where {(qd, qq) = unzip q; (dd, dq) = unzip d}
{#fun qlInterpolatedSurvivalProbabilityCurve{withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

piecewiseDefaultCurve :: Day -> [DefaultProbabilityHelper] -> DayCounter -> [(Day, GenQuote a)] -- ^jumps
  -> ProbabilityTrait -> Interpolation -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve d h dc q t i = uncurry' (qlPiecewiseDefaultCurve d h dc qq qd t) (qlInterpolation i) where (qd, qq) = unzip q
{#fun qlPiecewiseDefaultCurve{withDay*`Day',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

piecewiseDefaultCurve' :: Word -> Calendar -> [DefaultProbabilityHelper] -> DayCounter -> [(Day, GenQuote a)] -- ^jumps
  -> ProbabilityTrait -> Interpolation -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve' d c h dc q t i = uncurry' (qlPiecewiseDefaultCurve1 d c h dc qq qd t) (qlInterpolation i) where (qd, qq) = unzip q
{#fun qlPiecewiseDefaultCurve1{fromIntegral`Word',withCalendar*`Calendar',withDefaultProbabilityHelperArray*`[DefaultProbabilityHelper]'&,withDayCounter*`DayCounter',withQuoteArray*`[GenQuote a]'&,withDayArray*`[Day]'&,`ProbabilityTrait',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`DefaultProbabilityTermStructure'peekDefaultProbabilityTermStructure*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
