module QuantLib.TermStructure.Inflation
  (
    ZeroInflationTermStructure
  , YoYInflationTermStructure
  , ZeroCouponInflationSwapHelper
  , YearOnYearInflationSwapHelper

  , CPIInterpolationType(..) -- ^re-exported from "QuantLib.Internal.Enum"

  , zeroCouponInflationSwapHelper
  , yearOnYearInflationSwapHelper
  , zeroCouponInflationSwapHelperSwap
  , yearOnYearInflationSwapHelperSwap

  , piecewiseZeroInflationCurve
  , piecewiseYoYInflationCurve

  , zeroRate
  , yoyRate
  ) where
import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency)
import QuantLib.Internal.Enum
{#import QuantLib.TermStructure.Yield#}(PillarChoice)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlZeroInflationTermStructure as ZeroInflationTermStructure foreign -> CZeroInflationTermStructure' nocode#}
{#pointer *QlYoYInflationTermStructure as YoYInflationTermStructure foreign -> CYoYInflationTermStructure' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *QlZeroCouponInflationSwapHelper as ZeroCouponInflationSwapHelper foreign -> CZeroCouponInflationSwapHelper nocode#}
{#pointer *QlYearOnYearInflationSwapHelper as YearOnYearInflationSwapHelper foreign -> CYearOnYearInflationSwapHelper nocode#}
{#pointer *QlZeroCouponInflationSwap as ZeroCouponInflationSwap foreign -> CZeroCouponInflationSwap' nocode#}
{#pointer *QlYearOnYearInflationSwap as YearOnYearInflationSwap foreign -> CYearOnYearInflationSwap' nocode#}

-- |Bootstrap helper for a zero-coupon inflation swap, at the given (observation lag, maturity).
{#fun qlZeroCouponInflationSwapHelper as zeroCouponInflationSwapHelper{withQuote*`GenQuote a' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwapHelper'peekZeroCouponInflationSwapHelper*#}
-- |Bootstrap helper for a year-on-year inflation swap. Unlike 'zeroCouponInflationSwapHelper',
-- also needs the nominal discount curve (the YoY swap's fixed/floating legs discount off it).
{#fun qlYearOnYearInflationSwapHelper as yearOnYearInflationSwapHelper{withQuote*`GenQuote a' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withYoYInflationIndex*`YoYInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`YearOnYearInflationSwapHelper'peekYearOnYearInflationSwapHelper*#}

-- |The underlying swap the helper builds from its quote, observation lag and maturity.
{#fun qlZeroCouponInflationSwapHelperSwap as zeroCouponInflationSwapHelperSwap{withZeroCouponInflationSwapHelper*`ZeroCouponInflationSwapHelper',preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwap'peekZeroCouponInflationSwap*#}
-- |The underlying swap the helper builds from its quote, observation lag and maturity.
{#fun qlYearOnYearInflationSwapHelperSwap as yearOnYearInflationSwapHelperSwap{withYearOnYearInflationSwapHelper*`YearOnYearInflationSwapHelper',preErrorCheck-`String'errorCheck*-}->`YearOnYearInflationSwap'peekYearOnYearInflationSwap*#}

piecewiseZeroInflationCurve :: Day -- ^referenceDate
  -> Day -- ^baseDate
  -> Frequency -> DayCounter -> [ZeroCouponInflationSwapHelper] -> Interpolation
  -> IO ZeroInflationTermStructure
piecewiseZeroInflationCurve r b f dc h i = uncurryNested (qlPiecewiseZeroInflationCurve r b f dc h) (qlInterpolation i)
{#fun qlPiecewiseZeroInflationCurve{withDay*`Day',withDay*`Day',`Frequency',withDayCounter*`DayCounter'
  ,withZeroCouponInflationSwapHelperArray*`[ZeroCouponInflationSwapHelper]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`ZeroInflationTermStructure'peekZeroInflationTermStructure*#}

piecewiseYoYInflationCurve :: Day -- ^referenceDate
  -> Day -- ^baseDate
  -> Double -- ^baseYoYRate
  -> Frequency -> DayCounter -> [YearOnYearInflationSwapHelper] -> Interpolation
  -> IO YoYInflationTermStructure
piecewiseYoYInflationCurve r b y f dc h i = uncurryNested (qlPiecewiseYoYInflationCurve r b y f dc h) (qlInterpolation i)
{#fun qlPiecewiseYoYInflationCurve{withDay*`Day',withDay*`Day',`Double',`Frequency',withDayCounter*`DayCounter'
  ,withYearOnYearInflationSwapHelperArray*`[YearOnYearInflationSwapHelper]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YoYInflationTermStructure'peekYoYInflationTermStructure*#}

-- |Zero-coupon inflation rate implied by the curve.
{#fun qlZeroInflationTermStructureZeroRate as zeroRate{withGenTermStructure*`ZeroInflationTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Year-on-year inflation rate implied by the curve.
{#fun qlYoYInflationTermStructureYoYRate as yoyRate{withGenTermStructure*`YoYInflationTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
