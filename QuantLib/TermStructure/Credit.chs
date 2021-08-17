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
{#import QuantLib.Quote#}(Quote)
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
{#import QuantLib.Time.Schedule#}(DayCounter, DateGenerationRule, Frequency, TimeUnit)
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.TermStructure#}
import QuantLib.Math(Interpolation)
import QuantLib.Enum

{#enum ProbabilityTrait {} deriving(Show, Eq)#}

{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign finalizer qlFreeDefaultProbabilityTermStructure newtype#}
instance ForeignObject DefaultProbabilityTermStructure where
  withObject = withDefaultProbabilityTermStructure
  peekObject = newForeignPtr qlFreeDefaultProbabilityTermStructure >=> return . DefaultProbabilityTermStructure
instance IsTermStructure DefaultProbabilityTermStructure where asTermStructure = qlDefaultProbabilityTermStructureAsTermStructure

{#pointer *QlDefaultProbabilityHelper as DefaultProbabilityHelper foreign finalizer qlFreeDefaultProbabilityHelper newtype#}
instance ForeignObject DefaultProbabilityHelper where
  withObject = withDefaultProbabilityHelper
  peekObject = newForeignPtr qlFreeDefaultProbabilityHelper >=> return . DefaultProbabilityHelper

{#fun qlDefaultProbabilityTermStructureAsTermStructure {`DefaultProbabilityTermStructure'} -> `TermStructure' peekObject*#}

{#fun qlFactorSpreadedHazardRateCurve as factorSpreadedHazardRateCurve {`DefaultProbabilityTermStructure', withObject* `Quote', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

{#fun qlFlatHazardRate1 as flatHazardRate' {fromIntegral `Word', withObject* `Calendar', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

{#fun qlFlatHazardRate as flatHazardRate {withDay* `Day', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

{#fun qlSpreadedHazardRateCurve as spreadedHazardRateCurve {`DefaultProbabilityTermStructure', withObject* `Quote', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

{#fun qlDefaultProbabilityTermStructureDefaultProbability as defaultProbability {`DefaultProbabilityTermStructure' , withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlDefaultProbabilityTermStructureHazardRate1 as hazardRate' {`DefaultProbabilityTermStructure', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlDefaultProbabilityTermStructureHazardRate as hazardRate {`DefaultProbabilityTermStructure', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureSurvivalProbability1 as survivalProbability' {`DefaultProbabilityTermStructure', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlDefaultProbabilityTermStructureSurvivalProbability as survivalProbability {`DefaultProbabilityTermStructure', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultDensity1 as defaultDensity' {`DefaultProbabilityTermStructure', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlDefaultProbabilityTermStructureDefaultDensity as defaultDensity {`DefaultProbabilityTermStructure', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlDefaultProbabilityTermStructureDefaultProbability1 as defaultProbability' {`DefaultProbabilityTermStructure', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |probability of default between two given dates
{#fun qlDefaultProbabilityTermStructureDefaultProbability2 as defaultProbabilityBetween {`DefaultProbabilityTermStructure', withDay* `Day', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |probability of default between two given times
{#fun qlDefaultProbabilityTermStructureDefaultProbability3 as defaultProbabilityBetween' {`DefaultProbabilityTermStructure', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlSpreadCdsHelper as spreadCdsHelper {withObject* `Quote', fromEnumQuantity `(Word, TimeUnit)'&, `Int', withObject* `Calendar', `Frequency', `BusinessDayConvention', `DateGenerationRule', withObject* `DayCounter', `Double', withObject* `YieldTermStructure', `Bool', `Bool', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityHelper'#}

-- |the upfront must be quoted in fractional units.
{#fun qlUpfrontCdsHelper as upfrontCdsHelper {withObject* `Quote', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Int', withObject* `Calendar', `Frequency', `BusinessDayConvention', `DateGenerationRule', withObject* `DayCounter', `Double', withObject* `YieldTermStructure', fromIntegral `Word', `Bool', `Bool', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityHelper'#}

interpolatedDefaultDensityCurve :: [Day] -> [Double] -> DayCounter -> Calendar -> [(Quote, Day)] -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedDefaultDensityCurve d dens dc c q i = qlInterpolatedDefaultDensityCurve d dens dc c qq qd i1 i2 i3 where
  (qq, qd) = unzip q
  (i1, (i2, i3)) = qlInterpolation i
{#fun qlInterpolatedDefaultDensityCurve {withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, withObject* `DayCounter', withObject* `Calendar', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

interpolatedHazardRateCurve :: [Day] -> [Double] -> DayCounter -> Calendar -> [(Quote, Day)] -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedHazardRateCurve d dens dc c q i = qlInterpolatedHazardRateCurve d dens dc c qq qd i1 i2 i3 where
  (qq, qd) = unzip q
  (i1, (i2, i3)) = qlInterpolation i
{#fun qlInterpolatedHazardRateCurve {withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, withObject* `DayCounter', withObject* `Calendar', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

interpolatedSurvivalProbabilityCurve :: [Day] -> [Double] -> DayCounter -> Calendar -> [(Quote, Day)] -> Interpolation -> IO DefaultProbabilityTermStructure
interpolatedSurvivalProbabilityCurve d dens dc c q i = qlInterpolatedSurvivalProbabilityCurve d dens dc c qq qd i1 i2 i3 where
  (qq, qd) = unzip q
  (i1, (i2, i3)) = qlInterpolation i
{#fun qlInterpolatedSurvivalProbabilityCurve {withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, withObject* `DayCounter', withObject* `Calendar', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

piecewiseDefaultCurve :: Day -> [DefaultProbabilityHelper] -> DayCounter -> [(Quote, Day)] -> ProbabilityTrait -> Interpolation -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve d h dc q t i = qlPiecewiseDefaultCurve d h dc qq qd t i1 i2 i3 where
  (qq, qd) = unzip q
  (i1, (i2, i3)) = qlInterpolation i
{#fun qlPiecewiseDefaultCurve {withDay* `Day', withObjectArray* `[DefaultProbabilityHelper]'&, withObject* `DayCounter', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `ProbabilityTrait', `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

piecewiseDefaultCurve' :: Word -> Calendar -> [DefaultProbabilityHelper] -> DayCounter -> [(Quote, Day)] -> ProbabilityTrait -> Interpolation -> IO DefaultProbabilityTermStructure
piecewiseDefaultCurve' d c h dc q t i = qlPiecewiseDefaultCurve1 d c h dc qq qd t i1 i2 i3 where
  (qq, qd) = unzip q
  (i1, (i2, i3)) = qlInterpolation i
{#fun qlPiecewiseDefaultCurve1 {fromIntegral `Word', withObject* `Calendar', withObjectArray* `[DefaultProbabilityHelper]'&, withObject* `DayCounter', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `ProbabilityTrait', `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `DefaultProbabilityTermStructure'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
