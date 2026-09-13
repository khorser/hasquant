module QuantLib.TermStructure.Inflation
  (
    -- * Types
    ZeroInflationTermStructure
  , YoYInflationTermStructure
  , ZeroCouponInflationSwapHelper
  , YearOnYearInflationSwapHelper
  , CPIInterpolationType(..) -- ^re-exported from "QuantLib.Internal.Common"
    -- ** Seasonality
  , Seasonality(..)

    -- * Constructors
    -- ** Helpers
  , zeroCouponInflationSwapHelper
  , yearOnYearInflationSwapHelper
  , cpiBondHelper
    -- ** Curves
  , piecewiseZeroInflationCurve
  , piecewiseYoyInflationCurve
  , interpolatedYoyInflationCurve
  , interpolatedZeroInflationCurve

    -- * Inspectors
  , HasHelperUnderlying(..)
  , zeroRate
  , yoyRate
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency(..))
import QuantLib.Internal.Common
import QuantLib.TermStructure(HasHelperUnderlying(..))
import Data.List.NonEmpty(NonEmpty, toList)
{#import QuantLib.TermStructure.Yield#}(PillarChoice)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *QlZeroInflationTermStructure as ZeroInflationTermStructure foreign -> CZeroInflationTermStructure' nocode#}
{#pointer *QlYoYInflationTermStructure as YoYInflationTermStructure foreign -> CYoYInflationTermStructure' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *QlZeroCouponInflationSwapHelper as ZeroCouponInflationSwapHelper foreign -> CZeroCouponInflationSwapHelper nocode#}
{#pointer *QlYearOnYearInflationSwapHelper as YearOnYearInflationSwapHelper foreign -> CYearOnYearInflationSwapHelper nocode#}
{#pointer *QlBondHelper as BondHelper foreign -> CBondHelper' nocode#}

-- |Bootstrap helper for a zero-coupon inflation swap, at the given (observation lag, maturity).
{#fun qlZeroCouponInflationSwapHelper as zeroCouponInflationSwapHelper{withQuote*`GenQuote q' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwapHelper'peekZeroCouponInflationSwapHelper*#}

-- |Bootstrap helper for a year-on-year inflation swap. Unlike 'zeroCouponInflationSwapHelper',
-- also needs the nominal discount curve (the YoY swap's fixed/floating legs discount off it).
{#fun qlYearOnYearInflationSwapHelper as yearOnYearInflationSwapHelper{withQuote*`GenQuote q' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withYoYInflationIndex*`YoYInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`YearOnYearInflationSwapHelper'peekYearOnYearInflationSwapHelper*#}

-- |Bootstrap helper for a 'QuantLib.Instrument.Bond.CPIBond' -- a 'CPIBondHelper', which is a
-- plain 'BondHelper' subclass with no extra methods, so it's returned as the generic
-- 'BondHelper' type (same shape as 'QuantLib.TermStructure.Yield.fixedRateBondHelper').
{#fun qlCPIBondHelper as cpiBondHelper{withQuote*`GenQuote q',fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,`Double' -- ^baseCPI
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withSchedule*`Schedule',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^coupons
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`BondHelper'peekBondHelper*#}

-- |Bootstraps a zero-inflation term structure piecewise from a set of helpers, interpolating
-- between the bootstrapped nodes with the given 'Interpolation'.
piecewiseZeroInflationCurve :: Day -- ^referenceDate
  -> Day -- ^baseDate
  -> Frequency -> DayCounter -> NonEmpty ZeroCouponInflationSwapHelper -> Maybe Seasonality -> Interpolation
  -> IO ZeroInflationTermStructure
piecewiseZeroInflationCurve r b f dc h s i = seasonalityArgs r s $ \sk sd sf sfs ->
  uncurryNested (qlPiecewiseZeroInflationCurve r b f dc (toList h) sk sd sf sfs) (qlInterpolation i)

{#fun qlPiecewiseZeroInflationCurve{withDay*`Day',withDay*`Day',`Frequency',withDayCounter*`DayCounter'
  ,withZeroCouponInflationSwapHelperArray*`[ZeroCouponInflationSwapHelper]'&
  ,`Int',withDay*`Day',`Frequency',withDoubleArray*`[Double]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`ZeroInflationTermStructure'peekZeroInflationTermStructure*#}

-- |Bootstraps a year-on-year inflation term structure piecewise from a set of helpers,
-- interpolating between the bootstrapped nodes with the given 'Interpolation'.
piecewiseYoyInflationCurve :: Day -- ^referenceDate
  -> Day -- ^baseDate
  -> Double -- ^baseYoYRate
  -> Frequency -> DayCounter -> NonEmpty YearOnYearInflationSwapHelper -> Maybe Seasonality -> Interpolation
  -> IO YoYInflationTermStructure
piecewiseYoyInflationCurve r b y f dc h s i = seasonalityArgs r s $ \sk sd sf sfs ->
  uncurryNested (qlPiecewiseYoYInflationCurve r b y f dc (toList h) sk sd sf sfs) (qlInterpolation i)

{#fun qlPiecewiseYoYInflationCurve{withDay*`Day',withDay*`Day',`Double',`Frequency',withDayCounter*`DayCounter'
  ,withYearOnYearInflationSwapHelperArray*`[YearOnYearInflationSwapHelper]'&
  ,`Int',withDay*`Day',`Frequency',withDoubleArray*`[Double]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YoYInflationTermStructure'peekYoYInflationTermStructure*#}

-- |A YoY-inflation curve interpolating directly between given (date, rate) nodes, unlike
-- 'piecewiseYoyInflationCurve' bootstrap from swap helpers -- useful when the rates are
-- already known market YoY levels rather than swap quotes to calibrate against. The first
-- node is the curve's own base date\/rate.
interpolatedYoyInflationCurve :: Day -- ^referenceDate
  -> NonEmpty (Day, Double) -- ^dates, rates
  -> Frequency -> DayCounter -> Maybe Seasonality -> Interpolation
  -> IO YoYInflationTermStructure
interpolatedYoyInflationCurve r dr f dc s i = seasonalityArgs r s $ \sk sd sf sfs ->
  uncurryNested (qlInterpolatedYoYInflationCurve r ds rs f dc sk sd sf sfs) (qlInterpolation i)
  where (ds, rs) = unzip (toList dr)
{#fun qlInterpolatedYoYInflationCurve{withDay*`Day',withDayArray*`[Day]'&,withDoubleArrayRaw*`[Double]'
  ,`Frequency',withDayCounter*`DayCounter'
  ,`Int',withDay*`Day',`Frequency',withDoubleArray*`[Double]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`YoYInflationTermStructure'peekYoYInflationTermStructure*#}

-- |A zero-coupon inflation curve interpolating directly between given (date, rate) nodes. The
-- first node is the curve's base date.
interpolatedZeroInflationCurve :: Day -- ^referenceDate
  -> NonEmpty (Day, Double) -- ^dates, rates
  -> Frequency -> DayCounter -> Maybe Seasonality -> Interpolation
  -> IO ZeroInflationTermStructure
interpolatedZeroInflationCurve r dr f dc s i = seasonalityArgs r s $ \sk sd sf sfs ->
  uncurryNested (qlInterpolatedZeroInflationCurve r ds rs f dc sk sd sf sfs) (qlInterpolation i)
  where (ds, rs) = unzip (toList dr)
{#fun qlInterpolatedZeroInflationCurve{withDay*`Day',withDayArray*`[Day]'&,withDoubleArrayRaw*`[Double]'
  ,`Frequency',withDayCounter*`DayCounter'
  ,`Int',withDay*`Day',`Frequency',withDoubleArray*`[Double]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`ZeroInflationTermStructure'peekZeroInflationTermStructure*#}

-- |Multiplicative price seasonality applied by an inflation curve's zero and year-on-year rates.
-- Factors repeat every whole multiple of a year and are normalized to the curve's base date;
-- multi-year factors inconsistent at whole years around that date make construction throw.
data Seasonality
  = MultiplicativePriceSeasonality !Day !Frequency ![Double] -- ^seasonalityBaseDate, frequency, factors
  | KerkhofSeasonality !Day ![Double] -- ^seasonalityBaseDate, monthly factors

-- Flattens an optional seasonality into the shims' kind, base date, frequency and factors.
seasonalityArgs :: Day -> Maybe Seasonality -> (Int -> Day -> Frequency -> [Double] -> r) -> r
seasonalityArgs d s k = case s of
  Nothing -> k (-1) d NoFrequency []
  Just (MultiplicativePriceSeasonality b f fs) -> k 0 b f fs
  Just (KerkhofSeasonality b fs) -> k 1 b Monthly fs

-- |Zero-coupon inflation rate implied by the curve.
{#fun qlZeroInflationTermStructureZeroRate as zeroRate{withGenTermStructure*`ZeroInflationTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Year-on-year inflation rate implied by the curve.
{#fun qlYoYInflationTermStructureYoYRate as yoyRate{withGenTermStructure*`YoYInflationTermStructure',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
