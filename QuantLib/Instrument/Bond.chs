module QuantLib.Instrument.Bond
  (
    Bond
  , FixedRateBond
  , ConvertibleBond
  , CallableBond

  , asInstrument
  , asBond

  , PriceType(..)

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
  , softCallability
  )
  where
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
{#import QuantLib.Time.Schedule#}(Schedule, DayCounter, TimeUnit, DateGenerationRule, Frequency)
{#import QuantLib.CashFlow#}(Leg, Dividend, DurationType)
{#import QuantLib.InterestRate#}(InterestRate, Compounding)
{#import QuantLib.Index.InterestRate#}(IborIndex)
{#import QuantLib.Quote#}(Quote)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum PriceType {} deriving(Eq, Show)#}

{#pointer *QlBond as Bond foreign finalizer qlFreeBond newtype#}
instance ForeignObject Bond where
  withObject = withBond
  peekObject = newForeignPtr qlFreeBond >=> return . Bond

{#fun qlBondAsInstrument {`Bond'} -> `Instrument' peekObject*#}
instance IsInstrument Bond where asInstrument = qlBondAsInstrument

class IsBond a where asBond :: a -> IO Bond

{#pointer *QlFixedRateBond as FixedRateBond foreign finalizer qlFreeFixedRateBond newtype#}
instance ForeignObject FixedRateBond where
  withObject = withFixedRateBond
  peekObject = newForeignPtr qlFreeFixedRateBond >=> return . FixedRateBond
{#fun qlFixedRateBondAsBond {`FixedRateBond'} -> `Bond'#}
instance IsBond FixedRateBond where asBond = qlFixedRateBondAsBond

{#pointer *QlCallableBond as CallableBond foreign finalizer qlFreeCallableBond newtype#}
instance ForeignObject CallableBond where
  withObject = withCallableBond
  peekObject = newForeignPtr qlFreeCallableBond >=> return . CallableBond
{#fun qlCallableBondAsBond {`CallableBond'} -> `Bond'#}
instance IsBond CallableBond where asBond = qlCallableBondAsBond

{#pointer *QlConvertibleBond as ConvertibleBond foreign finalizer qlFreeConvertibleBond newtype#}
instance ForeignObject ConvertibleBond where
  withObject = withConvertibleBond
  peekObject = newForeignPtr qlFreeConvertibleBond >=> return . ConvertibleBond
{#fun qlConvertibleBondAsBond {`ConvertibleBond'} -> `Bond'#}
instance IsBond ConvertibleBond where asBond = qlConvertibleBondAsBond

{#fun qlBondFunctionsAtmRate as atmRate {`Bond', withObject* `YieldTermStructure', fromDay* `Day', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
{#fun qlBond as bond {fromIntegral `Word', withObject* `Calendar', fromMaybeDay* `Maybe Day', withObject* `Leg', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
{#fun qlBond1 as bond' {fromIntegral `Word', withObject* `Calendar', `Double', fromMaybeDay* `Maybe Day', fromMaybeDay* `Maybe Day', withObject* `Leg', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |Returns the maturity date of the bond
{#fun pure qlBondMaturityDate as maturityDate {`Bond'} -> `Maybe Day' toMaybeDay#}

-- |simple annual compounding coupon rates
{#fun qlFixedRateBond2 as fixedRateBondFromSchedule {fromIntegral `Word', `Double', withObject* `Schedule', withObjectArray* `[InterestRate]'&, `BusinessDayConvention', `Double', fromMaybeDay* `Maybe Day', withObject* `Calendar', preErrorCheck- `String' errorCheck*-} -> `FixedRateBond'#}

-- |simple annual compounding coupon rates with internal schedule calculation
{#fun qlFixedRateBond1 as fixedRateBond {fromIntegral `Word', withObject* `Calendar', `Double', fromDay* `Day', fromDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, withDoubleArray* `[Double]'&, withObject* `DayCounter', `BusinessDayConvention', `BusinessDayConvention', `Double', fromMaybeDay* `Maybe Day', fromMaybeDay* `Maybe Day', `DateGenerationRule', `Bool', withObject* `Calendar', preErrorCheck- `String' errorCheck*-} -> `FixedRateBond'#}

-- |generic compounding and frequency InterestRate coupons
{#fun qlFixedRateBond as fixedRateBondFromSchedule' {fromIntegral `Word', `Double', withObject* `Schedule', withDoubleArray* `[Double]'&, withObject* `DayCounter', `BusinessDayConvention', `Double', fromMaybeDay* `Maybe Day', withObject* `Calendar', preErrorCheck- `String' errorCheck*-} -> `FixedRateBond'#}

-- |zero-coupon bond
{#fun qlZeroCouponBond as zeroCouponBond {fromIntegral `Word', withObject* `Calendar', `Double', fromDay* `Day', `BusinessDayConvention', `Double', fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |floating-rate bond (possibly capped and/or floored)
{#fun qlFloatingRateBond as floatingRateBond {fromIntegral `Word', `Double', withObject* `Schedule', withObject* `IborIndex', withObject* `DayCounter', `BusinessDayConvention', fromIntegral `Word', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, `Bool', `Double', fromMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |theoretical bond yield
{#fun qlBondYield as yield {`Bond', withObject* `DayCounter', `Compounding', `Frequency', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |accrued amount at a given date
{#fun qlBondAccruedAmount as accruedAmount {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |clean price given a yield and settlement date
{#fun qlBondCleanPrice1 as cleanPriceFromYield {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |dirty price given a yield and settlement date
{#fun qlBondDirtyPrice1 as dirtyPriceFromYield {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondNextCashFlowDate as 
nextCashFlowDate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
{#fun qlBondNextCouponRate as nextCouponRate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondNotional as notional {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondPreviousCashFlowDate as previousCashFlowDate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
{#fun qlBondPreviousCouponRate as previousCouponRate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue1 as settlementValueFromCleanPrice {`Bond', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue as settlementValue {`Bond', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |yield given a (clean) price and settlement date
{#fun qlBondYield1 as yieldFromCleanPrice {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondIsTradable as isTradable {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool'#}

{#fun qlBondNotionals as notionals {`Bond', preArray- `[Double]'& peekDoubleArray*, preErrorCheck- `String' errorCheck*-} -> `()'#}

-- |returns all the cashflows, including the redemptions.
{#fun qlBondCashflows as cashFlows {`Bond', preErrorCheck- `String' errorCheck*-} -> `Leg' peekObject*#}

-- |returns just the redemption flows (not interest payments)
{#fun qlBondRedemptions as redemptions {`Bond', preErrorCheck- `String' errorCheck*-} -> `Leg' peekObject*#}

{#fun qlBondSettlementDate as settlementDate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlBondStartDate as startDate {`Bond', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlBondFunctionsAccrualDays as accrualDays {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlBondFunctionsAccrualEndDate as accrualEndDate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsAccrualPeriod as accrualPeriod {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsAccrualStartDate as accrualStartDate {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsAccruedDays as accruedDays {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlBondFunctionsAccruedPeriod as accruedPeriod {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBasisPointValue1 as basisPointValue {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBasisPointValue as basisPointValue' {`Bond', withObject* `InterestRate', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBps1 as bpsFromYield' {`Bond', withObject* `InterestRate', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBps2 as bpsFromYield {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsBps as bps {`Bond', withObject* `YieldTermStructure', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsCleanPrice2 as cleanPrice {`Bond', withObject* `YieldTermStructure', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsCleanPrice3 as cleanPrice' {`Bond', withObject* `YieldTermStructure', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsCleanPrice4 as cleanPriceFromYield' {`Bond', withObject* `InterestRate', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsConvexity1 as convexity {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsConvexity as convexity' {`Bond', withObject* `InterestRate', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsDuration1 as duration {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', `DurationType', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsDuration as duration' {`Bond', withObject* `InterestRate', `DurationType', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsNextCashFlowAmount as nextCashFlowAmount {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsPreviousCashFlowAmount as previousCashFlowAmount {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsReferencePeriodEnd as referencePeriodEnd {`Bond', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsReferencePeriodStart as referencePeriodStart {`Bond' , fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlBondFunctionsYield2 as yieldFromCleanPrice' {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', `Double', fromIntegral `Word', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsYieldValueBasisPoint1 as yieldValueBasisPoint {`Bond', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsYieldValueBasisPoint as yieldValueBasisPoint' {`Bond', withObject* `InterestRate', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBondFunctionsZSpread as zSpread {`Bond', `Double', withObject* `YieldTermStructure', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', `Double', fromIntegral `Word', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlFloatingRateBond1 as floatingRateBond' {fromIntegral `Word', `Double', fromDay* `Day', fromDay* `Day', `Frequency', withObject* `Calendar', withObject* `IborIndex', withObject* `DayCounter', `BusinessDayConvention', `BusinessDayConvention', fromIntegral `Word', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, `Bool', `Double', fromMaybeDay* `Maybe Day', fromMaybeDay* `Maybe Day', `DateGenerationRule', `Bool', preErrorCheck- `String' errorCheck*-} -> `Bond'#}

-- |theoretical clean price for the current evaluation date and term structure
{#fun qlBondCleanPrice as currentCleanPrice {`Bond', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
{#fun qlBondDirtyPrice as currentDirtyPrice {`Bond', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCallableFixedRateBond as callableFixedRateBond {fromIntegral `Word', `Double', withObject* `Schedule', withDoubleArray* `[Double]'&, withObject* `DayCounter', `BusinessDayConvention', `Double', fromMaybeDay* `Maybe Day', withObjectArray* `[Callability]'&, preErrorCheck- `String' errorCheck*-} -> `CallableBond'#}

{#fun qlCallableZeroCouponBond as callableZeroCouponBond {fromIntegral `Word', `Double', withObject* `Calendar', fromDay* `Day', withObject* `DayCounter', `BusinessDayConvention', `Double', fromMaybeDay* `Maybe Day', withObjectArray* `[Callability]'&, preErrorCheck- `String' errorCheck*-} -> `CallableBond'#}

{#fun qlConvertibleFixedCouponBond as convertibleFixedCouponBond {withObject* `Exercise', `Double', withObjectArray* `[Dividend]'&, withObjectArray* `[Callability]'&, withObject* `Quote', fromDay* `Day', fromIntegral `Word', withDoubleArray* `[Double]'&, withObject* `DayCounter', withObject* `Schedule', `Double', preErrorCheck- `String' errorCheck*-} -> `ConvertibleBond'#}

{#fun qlConvertibleFloatingRateBond as convertibleFloatingRateBond {withObject* `Exercise', `Double', withObjectArray* `[Dividend]'&, withObjectArray* `[Callability]'&, withObject* `Quote', fromDay* `Day', fromIntegral `Word', withObject* `IborIndex', fromIntegral `Word', withDoubleArray* `[Double]'&, withObject* `DayCounter', withObject* `Schedule', `Double', preErrorCheck- `String' errorCheck*-} -> `ConvertibleBond'#}

{#fun qlConvertibleZeroCouponBond as convertibleZeroCouponBond {withObject* `Exercise', `Double', withObjectArray* `[Dividend]'&, withObjectArray* `[Callability]'&, withObject* `Quote', fromDay* `Day', fromIntegral `Word', withObject* `DayCounter', withObject* `Schedule', `Double', preErrorCheck- `String' errorCheck*-} -> `ConvertibleBond'#}

-- |callability leaving to the holder the possibility to convert
{#fun qlSoftCallability as softCallability {`Double', `PriceType', fromDay* `Day', `Double', preErrorCheck- `String' errorCheck*-} -> `Callability' peekObject*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
