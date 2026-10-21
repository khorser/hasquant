module QuantLib.TermStructure.Inflation
  (
    -- * Types
    GenZeroInflationTermStructure
  , ZeroInflationTermStructure
  , PiecewiseZeroInflationCurve
  , GenYoYInflationTermStructure
  , YoYInflationTermStructure
  , PiecewiseYoYInflationCurve
  , ZeroCouponInflationSwapHelper
  , YearOnYearInflationSwapHelper
  , CPIInterpolationType(..) -- ^re-exported from "QuantLib.Internal.Common"
  , InflationSwapPeriod(..)
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
    -- ** Conversions
  , asZeroInflationTermStructure
  , asYoYInflationTermStructure

    -- * Inspectors
  , HasHelperUnderlying(..)
  , zeroRate
  , yoyRate
  , zeroCouponInflationSwapImpliedQuoteOn
  , yearOnYearInflationSwapImpliedQuoteOn
    -- ** Bootstrapped nodes
  , zeroInflationNodes
  , yoyInflationNodes
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
{#pointer *QlPiecewiseZeroInflationCurve as PiecewiseZeroInflationCurve foreign -> CPiecewiseZeroInflationCurve' nocode#}
{#pointer *QlPiecewiseYoYInflationCurve as PiecewiseYoYInflationCurve foreign -> CPiecewiseYoYInflationCurve' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *QlZeroCouponInflationSwapHelper as ZeroCouponInflationSwapHelper foreign -> CZeroCouponInflationSwapHelper nocode#}
{#pointer *QlYearOnYearInflationSwapHelper as YearOnYearInflationSwapHelper foreign -> CYearOnYearInflationSwapHelper nocode#}
{#pointer *QlBondHelper as BondHelper foreign -> CBondHelper' nocode#}

-- |Which dates an inflation swap helper's swap runs between. 'InflationSwapToMaturity' starts on
-- the evaluation date and moves with it; 'InflationSwapBetweenDates' is fixed. The fixed form also
-- takes its observation-interpolation weight from the start date rather than the maturity.
data InflationSwapPeriod
  = InflationSwapToMaturity
      !Day -- ^maturity
  | InflationSwapBetweenDates
      !Day -- ^startDate
      !Day -- ^endDate

-- |Bootstrap helper for a zero-coupon inflation swap, at the given observation lag and period.
zeroCouponInflationSwapHelper :: GenQuote q -- ^quote
  -> (Word, TimeUnit) -- ^swapObsLag
  -> InflationSwapPeriod
  -> Calendar
  -> BusinessDayConvention -- ^paymentConvention
  -> DayCounter
  -> GenZeroInflationIndex zidx
  -> CPIInterpolationType -- ^observationInterpolation
  -> PillarChoice -- ^pillar
  -> Maybe Day -- ^customPillarDate
  -> IO ZeroCouponInflationSwapHelper
zeroCouponInflationSwapHelper quote lag period cal conv dc zii interp pillar customPillarDate = case period of
  InflationSwapToMaturity m -> zeroCouponInflationSwapHelperRaw quote lag m cal conv dc zii interp pillar customPillarDate
  InflationSwapBetweenDates s e ->
    zeroCouponInflationSwapHelperBetweenDatesRaw quote lag s e cal conv dc zii interp pillar customPillarDate

-- |Bootstrap helper for a year-on-year inflation swap. Unlike 'zeroCouponInflationSwapHelper',
-- also needs the nominal discount curve (the YoY swap's fixed/floating legs discount off it).
yearOnYearInflationSwapHelper :: GenQuote q -- ^quote
  -> (Word, TimeUnit) -- ^swapObsLag
  -> InflationSwapPeriod
  -> Calendar
  -> BusinessDayConvention -- ^paymentConvention
  -> DayCounter
  -> GenYoYInflationIndex yidx
  -> CPIInterpolationType -- ^observationInterpolation
  -> GenYieldTermStructure y -- ^nominalTermStructure
  -> PillarChoice -- ^pillar
  -> Maybe Day -- ^customPillarDate
  -> IO YearOnYearInflationSwapHelper
yearOnYearInflationSwapHelper quote lag period cal conv dc yii interp nominal pillar customPillarDate = case period of
  InflationSwapToMaturity m -> yearOnYearInflationSwapHelperRaw quote lag m cal conv dc yii interp nominal pillar customPillarDate
  InflationSwapBetweenDates s e ->
    yearOnYearInflationSwapHelperBetweenDatesRaw quote lag s e cal conv dc yii interp nominal pillar customPillarDate

-- Raw inflation swap helper bindings; one per 'InflationSwapPeriod' constructor for each helper.
{#fun qlZeroCouponInflationSwapHelper as zeroCouponInflationSwapHelperRaw{withQuote*`GenQuote q' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withZeroInflationIndex*`GenZeroInflationIndex zidx'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwapHelper'peekZeroCouponInflationSwapHelper*#}

{#fun qlZeroCouponInflationSwapHelper2 as zeroCouponInflationSwapHelperBetweenDatesRaw{withQuote*`GenQuote q' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withZeroInflationIndex*`GenZeroInflationIndex zidx'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwapHelper'peekZeroCouponInflationSwapHelper*#}

{#fun qlYearOnYearInflationSwapHelper2 as yearOnYearInflationSwapHelperBetweenDatesRaw{withQuote*`GenQuote q' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withYoYInflationIndex*`GenYoYInflationIndex yidx'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,`PillarChoice' -- ^pillar
  ,withMaybeDay*`Maybe Day' -- ^customPillarDate
  ,preErrorCheck-`String'errorCheck*-}->`YearOnYearInflationSwapHelper'peekYearOnYearInflationSwapHelper*#}

{#fun qlYearOnYearInflationSwapHelper as yearOnYearInflationSwapHelperRaw{withQuote*`GenQuote q' -- ^quote
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapObsLag
  ,withDay*`Day' -- ^maturity
  ,withCalendar*`Calendar'
  ,fromEnumC`BusinessDayConvention' -- ^paymentConvention
  ,withDayCounter*`DayCounter'
  ,withYoYInflationIndex*`GenYoYInflationIndex yidx'
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
  ,withZeroInflationIndex*`GenZeroInflationIndex zidx'
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
  -> IO PiecewiseZeroInflationCurve
piecewiseZeroInflationCurve r b f dc h s i = seasonalityArgs r s $ \sk sd sf sfs ->
  uncurryNested (qlPiecewiseZeroInflationCurve r b f dc (toList h) sk sd sf sfs) (qlInterpolation i)

{#fun qlPiecewiseZeroInflationCurve{withDay*`Day',withDay*`Day',`Frequency',withDayCounter*`DayCounter'
  ,withZeroCouponInflationSwapHelperArray*`[ZeroCouponInflationSwapHelper]'&
  ,`Int',withDay*`Day',`Frequency',withDoubleArray*`[Double]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`PiecewiseZeroInflationCurve'peekPiecewiseZeroInflationCurve*#}

-- |Bootstraps a year-on-year inflation term structure piecewise from a set of helpers,
-- interpolating between the bootstrapped nodes with the given 'Interpolation'.
piecewiseYoyInflationCurve :: Day -- ^referenceDate
  -> Day -- ^baseDate
  -> Double -- ^baseYoYRate
  -> Frequency -> DayCounter -> NonEmpty YearOnYearInflationSwapHelper -> Maybe Seasonality -> Interpolation
  -> IO PiecewiseYoYInflationCurve
piecewiseYoyInflationCurve r b y f dc h s i = seasonalityArgs r s $ \sk sd sf sfs ->
  uncurryNested (qlPiecewiseYoYInflationCurve r b y f dc (toList h) sk sd sf sfs) (qlInterpolation i)

{#fun qlPiecewiseYoYInflationCurve{withDay*`Day',withDay*`Day',`Double',`Frequency',withDayCounter*`DayCounter'
  ,withYearOnYearInflationSwapHelperArray*`[YearOnYearInflationSwapHelper]'&
  ,`Int',withDay*`Day',`Frequency',withDoubleArray*`[Double]'&
  ,`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`PiecewiseYoYInflationCurve'peekPiecewiseYoYInflationCurve*#}

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
{#fun qlZeroInflationTermStructureZeroRate as zeroRate{withZeroInflationTermStructure*`GenZeroInflationTermStructure z',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The swap rate that would make a zero-coupon inflation swap helper reprice exactly on the given
-- zero-inflation curve, bootstrapped from it or not.
{#fun qlZeroCouponInflationSwapHelperImpliedQuoteOn as zeroCouponInflationSwapImpliedQuoteOn{withZeroCouponInflationSwapHelper*`ZeroCouponInflationSwapHelper'
  ,withZeroInflationTermStructure*`GenZeroInflationTermStructure z',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The swap rate that would make a year-on-year inflation swap helper reprice exactly on the given
-- year-on-year curve.
{#fun qlYearOnYearInflationSwapHelperImpliedQuoteOn as yearOnYearInflationSwapImpliedQuoteOn{withYearOnYearInflationSwapHelper*`YearOnYearInflationSwapHelper'
  ,withYoYInflationTermStructure*`GenYoYInflationTermStructure y',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Year-on-year inflation rate implied by the curve.
{#fun qlYoYInflationTermStructureYoYRate as yoyRate{withYoYInflationTermStructure*`GenYoYInflationTermStructure y',withDay*`Day',`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A bootstrapped zero-inflation curve's nodes, bootstrapping it if it has not been: its base date
-- first, then each helper's pillar, each with the zero inflation rate the curve interpolates, before
-- seasonality. 'interpolatedZeroInflationCurve' on these nodes, with the bootstrap's interpolation,
-- frequency, day counter and seasonality, is the same curve.
zeroInflationNodes :: PiecewiseZeroInflationCurve -> IO [(Day, Double)]
zeroInflationNodes c = zip <$> qlPiecewiseZeroInflationCurveDates c <*> qlPiecewiseZeroInflationCurveRates c
{#fun qlPiecewiseZeroInflationCurveDates{withPiecewiseZeroInflationCurve*`PiecewiseZeroInflationCurve',preIntArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlPiecewiseZeroInflationCurveRates{withPiecewiseZeroInflationCurve*`PiecewiseZeroInflationCurve',preDoubleArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |A bootstrapped year-on-year curve's nodes, bootstrapping it if it has not been: its base date
-- first, then each helper's pillar, each with the year-on-year rate the curve interpolates, before
-- seasonality. 'interpolatedYoyInflationCurve' on these nodes, with the bootstrap's interpolation,
-- frequency, day counter and seasonality, is the same curve.
yoyInflationNodes :: PiecewiseYoYInflationCurve -> IO [(Day, Double)]
yoyInflationNodes c = zip <$> qlPiecewiseYoYInflationCurveDates c <*> qlPiecewiseYoYInflationCurveRates c
{#fun qlPiecewiseYoYInflationCurveDates{withPiecewiseYoYInflationCurve*`PiecewiseYoYInflationCurve',preIntArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlPiecewiseYoYInflationCurveRates{withPiecewiseYoYInflationCurve*`PiecewiseYoYInflationCurve',preDoubleArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
