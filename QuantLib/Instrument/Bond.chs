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
{#import QuantLib.Instrument#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(TimeUnit, DateGenerationRule, Frequency)
{#import QuantLib.CashFlow#}(Leg, Dividend, DurationType)
import QuantLib.Internal.CashFlow
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.Index.InterestRate#}(IborIndex)
import QuantLib.Internal.Index
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlQuote as Quote foreign -> CQuote nocode#}
{#pointer *QlCallability foreign -> CQlCallability nocode#}
{#pointer *InterestRate foreign -> CInterestRate nocode#}

{#pointer *QlBond as Bond foreign finalizer qlFreeBond newtype#}
instance ForeignObject Bond where
  withObject = withBond
  constructor = Bond
  finalizer=qlFreeBond

{#fun qlBondAsInstrument {`Bond'} -> `Instrument' peekObject*#}
instance Bond `Derives` Instrument where cast = qlBondAsInstrument

asBond :: (a `Derives` Bond) => a -> IO Bond
asBond = cast

{#pointer *QlFixedRateBond as FixedRateBond foreign finalizer qlFreeFixedRateBond newtype#}
instance ForeignObject FixedRateBond where
  withObject = withFixedRateBond
  constructor = FixedRateBond
  finalizer=qlFreeFixedRateBond
{#fun qlFixedRateBondAsBond {`FixedRateBond'} -> `Bond'#}
instance FixedRateBond `Derives` Bond where cast = qlFixedRateBondAsBond

{#pointer *QlCallableBond as CallableBond foreign finalizer qlFreeCallableBond newtype#}
instance ForeignObject CallableBond where
  withObject = withCallableBond
  constructor = CallableBond
  finalizer=qlFreeCallableBond
{#fun qlCallableBondAsBond {`CallableBond'} -> `Bond'#}
instance CallableBond `Derives` Bond where cast = qlCallableBondAsBond

{#pointer *QlConvertibleBond as ConvertibleBond foreign finalizer qlFreeConvertibleBond newtype#}
instance ForeignObject ConvertibleBond where
  withObject = withConvertibleBond
  constructor = ConvertibleBond
  finalizer=qlFreeConvertibleBond
{#fun qlConvertibleBondAsBond {`ConvertibleBond'} -> `Bond'#}
instance ConvertibleBond `Derives` Bond where cast = qlConvertibleBondAsBond

{#fun qlBondFunctionsAtmRate as atmRate {`Bond', `YieldTermStructure', withDay* `Day', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
{#fun qlBond as bond {fromIntegral `Word', withCalendar*`Calendar', withMaybeDay* `Maybe Day', `Leg', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
{#fun qlBond1 as bond' {fromIntegral `Word', withCalendar*`Calendar', `Double', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', `Leg', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |Returns the maturity date of the bond
{#fun pure qlBondMaturityDate as maturityDate {`Bond'} -> `Maybe Day' toMaybeDay#}

-- |simple annual compounding coupon rates
{#fun qlFixedRateBond2 as fixedRateBondFromSchedule {fromIntegral `Word', `Double', withSchedule*`Schedule', withInterestRateArray*`[InterestRate]'&, `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', withCalendar*`Calendar', preErrorCheck- `String' errorCheck*-} -> `FixedRateBond'#}

-- |simple annual compounding coupon rates with internal schedule calculation
{#fun qlFixedRateBond1 as fixedRateBond {fromIntegral `Word', withCalendar*`Calendar', `Double', withDay* `Day', withDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, withDoubleArray* `[Double]'&, withDayCounter*`DayCounter', `BusinessDayConvention', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', `DateGenerationRule', `Bool', withCalendar*`Calendar', preErrorCheck- `String' errorCheck*-} -> `FixedRateBond'#}

-- |generic compounding and frequency InterestRate coupons
{#fun qlFixedRateBond as fixedRateBondFromSchedule' {fromIntegral `Word', `Double', withSchedule*`Schedule', withDoubleArray* `[Double]'&, withDayCounter*`DayCounter', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', withCalendar*`Calendar', preErrorCheck- `String' errorCheck*-} -> `FixedRateBond'#}

-- |zero-coupon bond
{#fun qlZeroCouponBond as zeroCouponBond {fromIntegral `Word', withCalendar*`Calendar', `Double', withDay* `Day', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |floating-rate bond (possibly capped and/or floored)
{#fun qlFloatingRateBond as floatingRateBond {fromIntegral `Word', `Double', withSchedule*`Schedule', `IborIndex', withDayCounter*`DayCounter', `BusinessDayConvention', fromIntegral `Word', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, `Bool', `Double', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |theoretical bond yield
{#fun qlBondYield as yield {`Bond', withDayCounter*`DayCounter', `Compounding', `Frequency', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |accrued amount at a given date
{#fun qlBondAccruedAmount as accruedAmount {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |clean price given a yield and settlement date
{#fun qlBondCleanPrice1 as cleanPriceFromYield {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |dirty price given a yield and settlement date
{#fun qlBondDirtyPrice1 as dirtyPriceFromYield {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondNextCashFlowDate as 
nextCashFlowDate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
{#fun qlBondNextCouponRate as nextCouponRate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondNotional as notional {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondPreviousCashFlowDate as previousCashFlowDate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
{#fun qlBondPreviousCouponRate as previousCouponRate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue1 as settlementValueFromCleanPrice {`Bond', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue as settlementValue {`Bond', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |yield given a (clean) price and settlement date
{#fun qlBondYield1 as yieldFromCleanPrice {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondIsTradable as isTradable {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool'#}

{#fun qlBondNotionals as notionals {`Bond', preArray- `[Double]'& peekDoubleArray*, preErrorCheck- `String' errorCheck*-} -> `()'#}

-- |returns all the cashflows, including the redemptions.
{#fun qlBondCashflows as cashFlows {`Bond', preErrorCheck- `String' errorCheck*-} -> `Leg' peekObject*#}

-- |returns just the redemption flows (not interest payments)
{#fun qlBondRedemptions as redemptions {`Bond', preErrorCheck- `String' errorCheck*-} -> `Leg' peekObject*#}

{#fun qlBondSettlementDate as settlementDate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlBondStartDate as startDate {`Bond', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlBondFunctionsAccrualDays as accrualDays {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlBondFunctionsAccrualEndDate as accrualEndDate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsAccrualPeriod as accrualPeriod {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsAccrualStartDate as accrualStartDate {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsAccruedDays as accruedDays {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlBondFunctionsAccruedPeriod as accruedPeriod {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBasisPointValue1 as basisPointValue {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBasisPointValue as basisPointValue' {`Bond', withInterestRate*`InterestRate', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBps1 as bpsFromYield' {`Bond', withInterestRate*`InterestRate', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBps2 as bpsFromYield {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBps as bps {`Bond', `YieldTermStructure', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsCleanPrice2 as cleanPrice {`Bond', `YieldTermStructure', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsCleanPrice3 as cleanPrice' {`Bond', `YieldTermStructure', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsCleanPrice4 as cleanPriceFromYield' {`Bond', withInterestRate*`InterestRate', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsConvexity1 as convexity {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsConvexity as convexity' {`Bond', withInterestRate*`InterestRate', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsDuration1 as duration {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', `DurationType', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsDuration as duration' {`Bond', withInterestRate*`InterestRate', `DurationType', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsNextCashFlowAmount as nextCashFlowAmount {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsPreviousCashFlowAmount as previousCashFlowAmount {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsReferencePeriodEnd as referencePeriodEnd {`Bond', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsReferencePeriodStart as referencePeriodStart {`Bond' , withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsYield2 as yieldFromCleanPrice' {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', `Double', fromIntegral `Word', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsYieldValueBasisPoint1 as yieldValueBasisPoint {`Bond', `Double', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsYieldValueBasisPoint as yieldValueBasisPoint' {`Bond', withInterestRate*`InterestRate', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsZSpread as zSpread {`Bond', `Double', `YieldTermStructure', withDayCounter*`DayCounter', `Compounding', `Frequency', withDay* `Day', `Double', fromIntegral `Word', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlFloatingRateBond1 as floatingRateBond' {fromIntegral `Word', `Double', withDay* `Day', withDay* `Day', `Frequency', withCalendar*`Calendar', `IborIndex', withDayCounter*`DayCounter', `BusinessDayConvention', `BusinessDayConvention', fromIntegral `Word', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, `Bool', `Double', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', `DateGenerationRule', `Bool', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |theoretical clean price for the current evaluation date and term structure
{#fun qlBondCleanPrice as currentCleanPrice {`Bond', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
{#fun qlBondDirtyPrice as currentDirtyPrice {`Bond', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCallableFixedRateBond as callableFixedRateBond {fromIntegral `Word', `Double', withSchedule*`Schedule', withDoubleArray* `[Double]'&, withDayCounter*`DayCounter', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', withCallabilityArray* `[Callability]'&, preErrorCheck- `String' errorCheck*-} -> `CallableBond'#}

{#fun qlCallableZeroCouponBond as callableZeroCouponBond {fromIntegral `Word', `Double', withCalendar*`Calendar', withDay* `Day', withDayCounter*`DayCounter', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', withCallabilityArray* `[Callability]'&, preErrorCheck- `String' errorCheck*-} -> `CallableBond'#}

{#pointer *QlExercise foreign newtype nocode#}

{#fun qlConvertibleFixedCouponBond as convertibleFixedCouponBond {withEnumObject* `Exercise', `Double', withObjectArray* `[Dividend]'&, withCallabilityArray* `[Callability]'&, withComplexType* `Quote', withDay* `Day', fromIntegral `Word', withDoubleArray* `[Double]'&, withDayCounter*`DayCounter', withSchedule*`Schedule', `Double', preErrorCheck- `String' errorCheck*-} -> `ConvertibleBond'#}

{#fun qlConvertibleFloatingRateBond as convertibleFloatingRateBond {withEnumObject* `Exercise', `Double', withObjectArray* `[Dividend]'&, withCallabilityArray* `[Callability]'&, withComplexType* `Quote', withDay* `Day', fromIntegral `Word', `IborIndex', fromIntegral `Word', withDoubleArray* `[Double]'&, withDayCounter*`DayCounter', withSchedule*`Schedule', `Double', preErrorCheck- `String' errorCheck*-} -> `ConvertibleBond'#}

{#fun qlConvertibleZeroCouponBond as convertibleZeroCouponBond {withEnumObject* `Exercise', `Double', withObjectArray* `[Dividend]'&, withCallabilityArray* `[Callability]'&, withComplexType* `Quote', withDay* `Day', fromIntegral `Word', withDayCounter*`DayCounter', withSchedule*`Schedule', `Double', preErrorCheck- `String' errorCheck*-} -> `ConvertibleBond'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
