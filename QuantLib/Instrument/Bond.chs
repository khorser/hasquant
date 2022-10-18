{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.Instrument.Bond
  (
    Bond
  , FixedRateBond
  , ConvertibleBond
  , CallableBond

  , asBond

  , BondPriceType(..)

  , bond
  , bond'
  , fixedRateBondFromSchedule
  , fixedRateBond
  , fixedRateBondFromSchedule'
  , zeroCouponBond
  , floatingRateBond
  , floatingRateBond'

  , maturityDate
  , yield
  , accruedAmount
  , cleanPriceFromYield
  , dirtyPriceFromYield
  , nextCashFlowDate
  , nextCouponRate
  , notional
  , previousCashFlowDate
  , previousCouponRate
  , settlementValueFromCleanPrice
  , settlementValue
  , yieldFromCleanPrice
  , isTradable
  , notionals
  , cashFlows
  , redemptions
  , settlementDate
  , startDate

  , accrualDays
  , accrualEndDate
  , accrualPeriod
  , accrualStartDate
  , accruedDays
  , accruedPeriod
  , atmRate
  , basisPointValue'
  , basisPointValue
  , bpsFromYield
  , bpsFromYield'
  , bps
  , cleanPrice
  , cleanPrice'
  , cleanPriceFromYield'
  , convexity'
  , convexity
  , duration'
  , duration
  , nextCashFlowAmount
  , previousCashFlowAmount
  , referencePeriodEnd
  , referencePeriodStart
  , yieldFromCleanPrice'
  , yieldValueBasisPoint'
  , yieldValueBasisPoint
  , zSpread

  , currentCleanPrice
  , currentDirtyPrice

  , callableFixedRateBond
  , callableZeroCouponBond
  , convertibleFixedCouponBond
  , convertibleFloatingRateBond
  , convertibleZeroCouponBond
  )
  where

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(DateGenerationRule, Frequency)
{#import QuantLib.CashFlow#}(DurationType)
{#import QuantLib.InterestRate#}(Compounding)
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote nocode#}
{#pointer *QlCallability foreign -> CQlCallability nocode#}
{#pointer *InterestRate foreign -> CInterestRate nocode#}

{#pointer *QlBond as Bond foreign -> CBond nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex nocode#}

{#fun qlBondAsInstrument{withBond*`Bond'}->`Instrument'peekInstrument*#}
instance Bond`Derives` Instrument where cast = qlBondAsInstrument

asBond :: (a`Derives` Bond) => a -> IO Bond
asBond = cast

{#pointer *QlFixedRateBond as FixedRateBond foreign -> CFixedRateBond nocode#}

{#fun qlFixedRateBondAsBond{withFixedRateBond*`FixedRateBond'}->`Bond'peekBond*#}
instance FixedRateBond`Derives` Bond where cast = qlFixedRateBondAsBond

{#pointer *QlCallableBond as CallableBond foreign -> CCallableBond nocode#}

{#fun qlCallableBondAsBond{withCallableBond*`CallableBond'}->`Bond'peekBond*#}
instance CallableBond`Derives` Bond where cast = qlCallableBondAsBond

{#pointer *QlConvertibleBond as ConvertibleBond foreign -> CConvertibleBond nocode#}

{#fun qlConvertibleBondAsBond{withConvertibleBond*`ConvertibleBond'}->`Bond'peekBond*#}
instance ConvertibleBond`Derives` Bond where cast = qlConvertibleBondAsBond

{#fun qlBondFunctionsAtmRate as atmRate{withBond*`Bond',withYieldTermStructure*`YieldTermStructure', withDay*`Day',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
{#fun qlBond as bond{fromIntegral`Word', withCalendar*`Calendar', withMaybeDay*`Maybe Day', withLeg*`GenLeg a', preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
{#fun qlBond1 as bond'{fromIntegral`Word', withCalendar*`Calendar',`Double', withMaybeDay*`Maybe Day', withMaybeDay*`Maybe Day', withLeg*`GenLeg a', preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |Returns the maturity date of the bond
{#fun pure qlBondMaturityDate as maturityDate{withBond*`Bond'}->`Maybe Day' toMaybeDay#}

-- |simple annual compounding coupon rates
{#fun qlFixedRateBond2 as fixedRateBondFromSchedule{fromIntegral`Word',`Double', withSchedule*`Schedule', withInterestRateArray*`[InterestRate]'&,`BusinessDayConvention',`Double', withMaybeDay*`Maybe Day', withCalendar*`Calendar', preErrorCheck-`String'errorCheck*-}->`FixedRateBond'peekFixedRateBond*#}

-- |simple annual compounding coupon rates with internal schedule calculation
{#fun qlFixedRateBond1 as fixedRateBond{fromIntegral`Word', withCalendar*`Calendar',`Double', withDay*`Day', withDay*`Day', fromEnumQuantity`(Word, TimeUnit)'&, withDoubleArray*`[Double]'&, withDayCounter*`DayCounter',`BusinessDayConvention',`BusinessDayConvention',`Double', withMaybeDay*`Maybe Day', withMaybeDay*`Maybe Day',`DateGenerationRule',`Bool', withCalendar*`Calendar', preErrorCheck-`String'errorCheck*-}->`FixedRateBond'peekFixedRateBond*#}

-- |generic compounding and frequency InterestRate coupons
{#fun qlFixedRateBond as fixedRateBondFromSchedule'{fromIntegral`Word',`Double', withSchedule*`Schedule', withDoubleArray*`[Double]'&, withDayCounter*`DayCounter',`BusinessDayConvention',`Double', withMaybeDay*`Maybe Day', withCalendar*`Calendar', preErrorCheck-`String'errorCheck*-}->`FixedRateBond'peekFixedRateBond*#}

-- |zero-coupon bond
{#fun qlZeroCouponBond as zeroCouponBond{fromIntegral`Word', withCalendar*`Calendar',`Double', withDay*`Day',`BusinessDayConvention',`Double', withMaybeDay*`Maybe Day', preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |floating-rate bond (possibly capped and/or floored)
{#fun qlFloatingRateBond as floatingRateBond{fromIntegral`Word',`Double', withSchedule*`Schedule',withIborIndex*`GenIborIndex a', withDayCounter*`DayCounter',`BusinessDayConvention', fromIntegral`Word', withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&,`Bool',`Double', withMaybeDay*`Maybe Day', preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |theoretical bond yield
{#fun qlBondYield as yield{withBond*`Bond', withDayCounter*`DayCounter',`Compounding',`Frequency',`Double', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |accrued amount at a given date
{#fun qlBondAccruedAmount as accruedAmount{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |clean price given a yield and settlement date
{#fun qlBondCleanPrice1 as cleanPriceFromYield{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |dirty price given a yield and settlement date
{#fun qlBondDirtyPrice1 as dirtyPriceFromYield{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondNextCashFlowDate as nextCashFlowDate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
{#fun qlBondNextCouponRate as nextCouponRate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondNotional as notional{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondPreviousCashFlowDate as previousCashFlowDate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
{#fun qlBondPreviousCouponRate as previousCouponRate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue1 as settlementValueFromCleanPrice{withBond*`Bond',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue as settlementValue{withBond*`Bond', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |yield given a (clean) price and settlement date
{#fun qlBondYield1 as yieldFromCleanPrice{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day',`Double', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondIsTradable as isTradable{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Bool'#}

{#fun qlBondNotionals as notionals{withBond*`Bond', preArray-`[Double]'&peekDoubleArray*, preErrorCheck-`String'errorCheck*-}->`()'#}

-- |returns all the cashflows, including the redemptions.
{#fun qlBondCashflows as cashFlows{withBond*`Bond', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |returns just the redemption flows (not interest payments)
{#fun qlBondRedemptions as redemptions{withBond*`Bond', preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

{#fun qlBondSettlementDate as settlementDate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

{#fun qlBondStartDate as startDate{withBond*`Bond', preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

{#fun qlBondFunctionsAccrualDays as accrualDays{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Int'#}

{#fun qlBondFunctionsAccrualEndDate as accrualEndDate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsAccrualPeriod as accrualPeriod{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsAccrualStartDate as accrualStartDate{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsAccruedDays as accruedDays{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Int'#}

{#fun qlBondFunctionsAccruedPeriod as accruedPeriod{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsBasisPointValue1 as basisPointValue{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsBasisPointValue as basisPointValue'{withBond*`Bond', withInterestRate*`InterestRate', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsBps1 as bpsFromYield'{withBond*`Bond', withInterestRate*`InterestRate', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsBps2 as bpsFromYield{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsBps as bps{withBond*`Bond',withYieldTermStructure*`YieldTermStructure', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsCleanPrice2 as cleanPrice{withBond*`Bond',withYieldTermStructure*`YieldTermStructure', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsCleanPrice3 as cleanPrice'{withBond*`Bond',withYieldTermStructure*`YieldTermStructure',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsCleanPrice4 as cleanPriceFromYield'{withBond*`Bond', withInterestRate*`InterestRate', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsConvexity1 as convexity{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsConvexity as convexity'{withBond*`Bond', withInterestRate*`InterestRate', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsDuration1 as duration{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency',`DurationType', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsDuration as duration'{withBond*`Bond', withInterestRate*`InterestRate',`DurationType', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsNextCashFlowAmount as nextCashFlowAmount{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsPreviousCashFlowAmount as previousCashFlowAmount{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsReferencePeriodEnd as referencePeriodEnd{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsReferencePeriodStart as referencePeriodStart{withBond*`Bond', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsYield2 as yieldFromCleanPrice'{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day',`Double', fromIntegral`Word',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsYieldValueBasisPoint1 as yieldValueBasisPoint{withBond*`Bond',`Double', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsYieldValueBasisPoint as yieldValueBasisPoint'{withBond*`Bond', withInterestRate*`InterestRate', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlBondFunctionsZSpread as zSpread{withBond*`Bond',`Double',withYieldTermStructure*`YieldTermStructure', withDayCounter*`DayCounter',`Compounding',`Frequency', withDay*`Day',`Double', fromIntegral`Word',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlFloatingRateBond1 as floatingRateBond'{fromIntegral`Word',`Double', withDay*`Day', withDay*`Day',`Frequency', withCalendar*`Calendar',withIborIndex*`GenIborIndex a', withDayCounter*`DayCounter',`BusinessDayConvention',`BusinessDayConvention', fromIntegral`Word', withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&, withDoubleArray*`[Double]'&,`Bool',`Double', withMaybeDay*`Maybe Day', withMaybeDay*`Maybe Day',`DateGenerationRule',`Bool', preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |theoretical clean price for the current evaluation date and term structure
{#fun qlBondCleanPrice as currentCleanPrice{withBond*`Bond', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
{#fun qlBondDirtyPrice as currentDirtyPrice{withBond*`Bond', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCallableFixedRateBond as callableFixedRateBond{fromIntegral`Word',`Double', withSchedule*`Schedule', withDoubleArray*`[Double]'&, withDayCounter*`DayCounter',`BusinessDayConvention',`Double', withMaybeDay*`Maybe Day', withCallabilityArray*`[Callability]'&, preErrorCheck-`String'errorCheck*-}->`CallableBond'peekCallableBond*#}

{#fun qlCallableZeroCouponBond as callableZeroCouponBond{fromIntegral`Word',`Double', withCalendar*`Calendar', withDay*`Day', withDayCounter*`DayCounter',`BusinessDayConvention',`Double', withMaybeDay*`Maybe Day', withCallabilityArray*`[Callability]'&, preErrorCheck-`String'errorCheck*-}->`CallableBond'peekCallableBond*#}

{#pointer *QlExercise foreign newtype nocode#}

{#fun qlConvertibleFixedCouponBond as convertibleFixedCouponBond{withExercise*`Exercise',`Double', withCallabilityArray*`[Callability]'&, withDay*`Day', fromIntegral`Word', withDoubleArray*`[Double]'&, withDayCounter*`DayCounter', withSchedule*`Schedule',`Double', preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}

{#fun qlConvertibleFloatingRateBond as convertibleFloatingRateBond{withExercise*`Exercise',`Double', withCallabilityArray*`[Callability]'&, withDay*`Day', fromIntegral`Word',withIborIndex*`GenIborIndex b', fromIntegral`Word', withDoubleArray*`[Double]'&, withDayCounter*`DayCounter', withSchedule*`Schedule',`Double', preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}

{#fun qlConvertibleZeroCouponBond as convertibleZeroCouponBond{withExercise*`Exercise',`Double', withCallabilityArray*`[Callability]'&, withDay*`Day', fromIntegral`Word', withDayCounter*`DayCounter', withSchedule*`Schedule',`Double', preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
