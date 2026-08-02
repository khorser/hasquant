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
  , fixedRateBond
  , zeroCouponBond
  , floatingRateBond

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
  , yieldFromPrice
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
  , yieldFromPrice'
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
  ) where
import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency)
{#import QuantLib.CashFlow#}(DurationType)
{#import QuantLib.InterestRate#}(Compounding)
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote nocode#}
{#pointer *QlCallability foreign -> CQlCallability nocode#}
{#pointer *InterestRate foreign -> CInterestRate nocode#}

{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlFixedRateBond as FixedRateBond foreign -> CFixedRateBond' nocode#}
{#pointer *QlCallableBond as CallableBond foreign -> CCallableBond' nocode#}
{#pointer *QlConvertibleBond as ConvertibleBond foreign -> CConvertibleBond' nocode#}
{#pointer *QlExercise nocode#}

{#fun qlBondFunctionsAtmRate as atmRate{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',fromEnumDouble`Double,BondPriceType'&,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
{#fun qlBond as bond{fromIntegral`Word',withCalendar*`Calendar',withMaybeDay*`Maybe Day' -- ^issueDate
  ,withLeg*`GenLeg a' -- ^coupons
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
{#fun qlBond1 as bond'{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,`Double' -- ^faceAmount
  ,withMaybeDay*`Maybe Day' -- ^maturityDate
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withLeg*`GenLeg a' -- ^cashFlows
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |Returns the maturity date of the bond
{#fun pure qlBondMaturityDate as maturityDate{withBond*`GenBond a'}->`Maybe Day' toMaybeDay#}
-- |generic compounding and frequency InterestRate coupons
{#fun qlFixedRateBond as fixedRateBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withSchedule*`Schedule' -- ^schedule
  ,withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`FixedRateBond'peekFixedRateBond*#}
-- |zero-coupon bond
{#fun qlZeroCouponBond as zeroCouponBond{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,`Double' -- ^faceAmount
  ,withDay*`Day' -- ^maturityDate
  ,`BusinessDayConvention'
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |floating-rate bond (possibly capped and/or floored)
{#fun qlFloatingRateBond as floatingRateBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withSchedule*`Schedule' -- ^schedule
  ,withIborIndex*`GenIborIndex a'
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,`BusinessDayConvention'
  ,fromIntegral`Word' -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |theoretical bond yield
{#fun qlBondYield as yield{withBond*`GenBond a',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |accrued amount at a given date
{#fun qlBondAccruedAmount as accruedAmount{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |clean price given a yield and settlement date
{#fun qlBondCleanPrice1 as cleanPriceFromYield{withBond*`GenBond a',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |dirty price given a yield and settlement date
{#fun qlBondDirtyPrice1 as dirtyPriceFromYield{withBond*`GenBond a',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondNextCashFlowDate as nextCashFlowDate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
{#fun qlBondNextCouponRate as nextCouponRate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondNotional as notional{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondPreviousCashFlowDate as previousCashFlowDate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
{#fun qlBondPreviousCouponRate as previousCouponRate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue1 as settlementValueFromCleanPrice{withBond*`GenBond a',`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue as settlementValue{withBond*`GenBond a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |yield given a (clean) price and settlement date
{#fun qlBondYield1 as yieldFromPrice{withBond*`GenBond a',fromEnumDouble`Double,BondPriceType'&
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- settlementDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondIsTradable as isTradable{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlBondNotionals as notionals{withBond*`GenBond a',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |returns all the cashflows, including the redemptions.
{#fun qlBondCashflows as cashFlows{withBond*`GenBond a',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |returns just the redemption flows (not interest payments)
{#fun qlBondRedemptions as redemptions{withBond*`GenBond a',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlBondSettlementDate as settlementDate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlBondStartDate as startDate{withBond*`GenBond a',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlBondFunctionsAccrualDays as accrualDays{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlBondFunctionsAccrualEndDate as accrualEndDate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsAccrualPeriod as accrualPeriod{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsAccrualStartDate as accrualStartDate{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsAccruedDays as accruedDays{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlBondFunctionsAccruedPeriod as accruedPeriod{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBasisPointValue1 as basisPointValue{withBond*`GenBond a',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBasisPointValue as basisPointValue'{withBond*`GenBond a',withInterestRate*`InterestRate',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBps1 as bpsFromYield'{withBond*`GenBond a',withInterestRate*`InterestRate',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBps2 as bpsFromYield{withBond*`GenBond a',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBps as bps{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsCleanPrice2 as cleanPrice{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsCleanPrice3 as cleanPrice'{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure a' -- ^discount
  ,`Double' -- ^zSpread
  ,`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsCleanPrice4 as cleanPriceFromYield'{withBond*`GenBond a',withInterestRate*`InterestRate',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsConvexity1 as convexity{withBond*`GenBond a',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsConvexity as convexity'{withBond*`GenBond a',withInterestRate*`InterestRate' -- ^yield
  ,withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsDuration1 as duration{withBond*`GenBond a',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`DurationType',withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsDuration as duration'{withBond*`GenBond a',withInterestRate*`InterestRate' -- ^yield
  ,`DurationType',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsNextCashFlowAmount as nextCashFlowAmount{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsPreviousCashFlowAmount as previousCashFlowAmount{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsReferencePeriodEnd as referencePeriodEnd{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsReferencePeriodStart as referencePeriodStart{withBond*`GenBond a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsYield2 as yieldFromPrice'{withBond*`GenBond a',fromEnumDouble`Double,BondPriceType'&
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,`Double' --  ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsYieldValueBasisPoint1 as yieldValueBasisPoint{withBond*`GenBond a',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsYieldValueBasisPoint as yieldValueBasisPoint'{withBond*`GenBond a',withInterestRate*`InterestRate' -- ^yield
  ,withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsZSpread as zSpread{withBond*`GenBond b',fromEnumDouble`Double,BondPriceType'&
  ,withYieldTermStructure*`GenYieldTermStructure a'
  ,`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |theoretical clean price for the current evaluation date and term structure
{#fun qlBondCleanPrice as currentCleanPrice{withBond*`GenBond a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
{#fun qlBondDirtyPrice as currentDirtyPrice{withBond*`GenBond a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCallableFixedRateBond as callableFixedRateBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withSchedule*`Schedule',withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter',`BusinessDayConvention'
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCallabilityArray*`[Callability]'&,preErrorCheck-`String'errorCheck*-}->`CallableBond'peekCallableBond*#}
{#fun qlCallableZeroCouponBond as callableZeroCouponBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withCalendar*`Calendar',withDay*`Day' -- ^maturityDate
  ,withDayCounter*`DayCounter',`BusinessDayConvention'
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCallabilityArray*`[Callability]'&,preErrorCheck-`String'errorCheck*-}->`CallableBond'peekCallableBond*#}
{#fun qlConvertibleFixedCouponBond as convertibleFixedCouponBond{withExercise*`Exercise',`Double' -- ^conversionRatio
  ,withCallabilityArray*`[Callability]'&
  ,withDay*`Day' -- ^issueDate
  ,fromIntegral`Word' -- ^settlementDays
  ,withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter',withSchedule*`Schedule',`Double' -- ^redemption
  ,preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}
{#fun qlConvertibleFloatingRateBond as convertibleFloatingRateBond{withExercise*`Exercise',`Double' -- ^conversionRatio
  ,withCallabilityArray*`[Callability]'&
  ,withDay*`Day' -- ^issueDate
  ,fromIntegral`Word' -- ^settlementDays
  ,withIborIndex*`GenIborIndex b',fromIntegral`Word' -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDayCounter*`DayCounter',withSchedule*`Schedule',`Double' -- ^redemption
  ,preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}
{#fun qlConvertibleZeroCouponBond as convertibleZeroCouponBond{withExercise*`Exercise',`Double' -- ^conversionRatio
  ,withCallabilityArray*`[Callability]'&
  ,withDay*`Day' -- ^issueDate
  ,fromIntegral`Word' -- ^settlementDays
  ,withDayCounter*`DayCounter',withSchedule*`Schedule',`Double' -- redemption
  ,preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
