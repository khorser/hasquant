{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Instrument.Bond
  (
    Bond
  , FixedRateBond
  , ConvertibleBond
  , CallableBond
  , CPIBond

  , asBond

  , BondPriceType(..)
  , CPIInterpolationType(..)

  , bond
  , bond'
  , fixedRateBond
  , zeroCouponBond
  , floatingRateBond
  , cmsRateBond
  , cpiBond
  , amortizingFixedRateBond
  , amortizingCmsRateBond
  , AmortizingFloatingRateBondOpts(..)
  , defaultAmortizingFloatingRateBondOpts
  , amortizingFloatingRateBond
  , sinkingSchedule
  , sinkingNotionals

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
{#import QuantLib.Time.Calendar#}(BusinessDayConvention(..))
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(Frequency)
{#import QuantLib.CashFlow#}(DurationType)
{#import QuantLib.InterestRate#}(Compounding)
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import Data.Maybe(fromMaybe)

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
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlFixedRateBond as FixedRateBond foreign -> CFixedRateBond' nocode#}
{#pointer *QlCPIBond as CPIBond foreign -> CCPIBond' nocode#}
{#pointer *QlCallableBond as CallableBond foreign -> CCallableBond' nocode#}
{#pointer *QlConvertibleBond as ConvertibleBond foreign -> CConvertibleBond' nocode#}
{#pointer *QlExercise nocode#}

-- AmortizingFloatingRateBondOpts bundles every trailing param
-- amortizingFloatingRateBond hardcodes, pre-populated with upstream's own
-- defaults via defaultAmortizingFloatingRateBondOpts, overridden through
-- record-update syntax at the call site -- see the add-quantlib-options-record
-- skill. This splice must stay textually before every {#fun#}-generated
-- binding in this file: c2hs always appends its raw foreign-import stubs at
-- the physical end of the generated module regardless of where in the .chs a
-- {#fun#} hook appears, and a top-level TH splice anywhere in between would
-- otherwise split the file into declaration groups that can't see each
-- other, breaking every earlier {#fun#} wrapper's reference to its own
-- (always-last) foreign-import stub.
$(deriveOptionsRecord "AmortizingFloatingRateBondOpts" []
  [ ("afrbPaymentConvention", [t|BusinessDayConvention|], [|Following|])
  , ("afrbFixingDays", [t|Maybe Word|], [|Nothing|])
  , ("afrbGearings", [t|[Double]|], [|[1.0]|])
  , ("afrbSpreads", [t|[Double]|], [|[0.0]|])
  , ("afrbCaps", [t|[Double]|], [|[]|])
  , ("afrbFloors", [t|[Double]|], [|[]|])
  , ("afrbInArrears", [t|Bool|], [|False|])
  , ("afrbIssueDate", [t|Maybe Day|], [|Nothing|])
  , ("afrbExCouponPeriod", [t|(Int, TimeUnit)|], [|(0, Days)|])
  , ("afrbExCouponCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("afrbExCouponConvention", [t|BusinessDayConvention|], [|Unadjusted|])
  , ("afrbExCouponEndOfMonth", [t|Bool|], [|False|])
  , ("afrbRedemptions", [t|[Double]|], [|[100.0]|])
  , ("afrbPaymentLag", [t|Int|], [|0|])
  ])

{#fun qlBondFunctionsAtmRate as atmRate{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',fromEnumDouble`Double,BondPriceType'&,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
{#fun qlBond as bond{fromIntegral`Word',withCalendar*`Calendar',withMaybeDay*`Maybe Day' -- ^issueDate
  ,withLeg*`GenLeg l' -- ^coupons
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
{#fun qlBond1 as bond'{fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar'
  ,`Double' -- ^faceAmount
  ,withMaybeDay*`Maybe Day' -- ^maturityDate
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withLeg*`GenLeg l' -- ^cashFlows
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}

-- |Returns the maturity date of the bond
{#fun pure qlBondMaturityDate as maturityDate{withBond*`GenBond b'}->`Maybe Day' toMaybeDay#}
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
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,withDayCounter*`DayCounter' -- ^firstPeriodDayCounter
  ,preErrorCheck-`String'errorCheck*-}->`FixedRateBond'peekFixedRateBond*#}
-- |amortizing fixed-rate bond: like 'fixedRateBond' but with a per-period notional schedule
-- instead of a single face amount (see 'sinkingSchedule'\/'sinkingNotionals' for building one).
{#fun qlAmortizingFixedRateBond as amortizingFixedRateBond{fromIntegral`Word' -- ^settlementDays
  ,withDoubleArray*`[Double]'& -- ^notionals
  ,withSchedule*`Schedule' -- ^schedule
  ,withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,withDoubleArray*`[Double]'& -- ^redemptions
  ,fromIntegral`Int' -- ^paymentLag
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |returns a schedule for French amortization
{#fun qlSinkingSchedule as sinkingSchedule{withDay*`Day' -- ^startDate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^bondLength
  ,`Frequency'
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}
-- |returns a sequence of notionals for French amortization
{#fun qlSinkingNotionals as sinkingNotionals{fromEnumQuantity`(Int,TimeUnit)'& -- ^bondLength
  ,`Frequency'
  ,`Double' -- ^couponRate
  ,`Double' -- ^initialNotional
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |An inflation-linked bond whose redemption and coupons scale with a 'ZeroInflationIndex'
-- fixing relative to /baseCPI/.
{#fun qlCPIBond as cpiBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,`Double' -- ^baseCPI
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withSchedule*`Schedule'
  ,withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,preErrorCheck-`String'errorCheck*-}->`CPIBond'peekCPIBond*#}
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
  ,withIborIndex*`GenIborIndex ibor'
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
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,`BusinessDayConvention' -- ^fixingConvention
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |CMS-rate bond
{#fun qlCmsRateBond as cmsRateBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withSchedule*`Schedule' -- ^schedule
  ,withSwapIndex*`GenSwapIndex sidx'
  ,withDayCounter*`DayCounter' -- ^paymentDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |amortizing CMS-rate bond (possibly capped and\/or floored) with a per-period
-- notional schedule instead of a single face amount, and a per-period redemption
-- schedule instead of a single redemption value.
{#fun qlAmortizingCmsRateBond as amortizingCmsRateBond{fromIntegral`Word' -- ^settlementDays
  ,withDoubleArray*`[Double]'& -- ^notionals
  ,withSchedule*`Schedule' -- ^schedule
  ,withSwapIndex*`GenSwapIndex sidx'
  ,withDayCounter*`DayCounter' -- ^paymentDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withDoubleArray*`[Double]'& -- ^redemptions
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |amortizing floating-rate bond (possibly capped and\/or floored) with a per-period
-- notional schedule instead of a single face amount; see 'AmortizingFloatingRateBondOpts'
-- for the trailing optional parameters (default via 'defaultAmortizingFloatingRateBondOpts',
-- override with record-update syntax).
amortizingFloatingRateBond :: Word -> [Double] -> Schedule -> GenIborIndex ibor -> DayCounter
  -> AmortizingFloatingRateBondOpts -> IO Bond
amortizingFloatingRateBond settlementDays notionalsArg schedule idx accrualDayCounter opts = do
  cal <- calendar Null
  amortizingFloatingRateBond_ settlementDays notionalsArg schedule idx accrualDayCounter
    (afrbPaymentConvention opts) (fromMaybeInt (afrbFixingDays opts))
    (afrbGearings opts) (afrbSpreads opts) (afrbCaps opts) (afrbFloors opts)
    (afrbInArrears opts) (afrbIssueDate opts) (afrbExCouponPeriod opts)
    (fromMaybe cal (afrbExCouponCalendar opts)) (afrbExCouponConvention opts)
    (afrbExCouponEndOfMonth opts) (afrbRedemptions opts) (afrbPaymentLag opts)

{#fun qlAmortizingFloatingRateBond as amortizingFloatingRateBond_{fromIntegral`Word' -- ^settlementDays
  ,withDoubleArray*`[Double]'& -- ^notionals
  ,withSchedule*`Schedule' -- ^schedule
  ,withIborIndex*`GenIborIndex ibor'
  ,withDayCounter*`DayCounter' -- ^accrualDayCounter
  ,`BusinessDayConvention' -- ^paymentConvention
  ,fromIntegral`Word' -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,withDoubleArray*`[Double]'& -- ^redemptions
  ,fromIntegral`Int' -- ^paymentLag
  ,preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
-- |theoretical bond yield
{#fun qlBondYield as yield{withBond*`GenBond b',withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,fromEnumDouble`Double,BondPriceType'& -- ^guess, priceType
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |accrued amount at a given date
{#fun qlBondAccruedAmount as accruedAmount{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |clean price given a yield and settlement date
{#fun qlBondCleanPrice1 as cleanPriceFromYield{withBond*`GenBond b',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |dirty price given a yield and settlement date
{#fun qlBondDirtyPrice1 as dirtyPriceFromYield{withBond*`GenBond b',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondNextCashFlowDate as nextCashFlowDate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
{#fun qlBondNextCouponRate as nextCouponRate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondNotional as notional{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondPreviousCashFlowDate as previousCashFlowDate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
{#fun qlBondPreviousCouponRate as previousCouponRate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue1 as settlementValueFromCleanPrice{withBond*`GenBond b',`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
{#fun qlBondSettlementValue as settlementValue{withBond*`GenBond b',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |yield given a (clean) price and settlement date
{#fun qlBondYield1 as yieldFromPrice{withBond*`GenBond b',fromEnumDouble`Double,BondPriceType'&
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- settlementDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondIsTradable as isTradable{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlBondNotionals as notionals{withBond*`GenBond b',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |returns all the cashflows, including the redemptions.
{#fun qlBondCashflows as cashFlows{withBond*`GenBond b',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |returns just the redemption flows (not interest payments)
{#fun qlBondRedemptions as redemptions{withBond*`GenBond b',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlBondSettlementDate as settlementDate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlBondStartDate as startDate{withBond*`GenBond b',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlBondFunctionsAccrualDays as accrualDays{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlBondFunctionsAccrualEndDate as accrualEndDate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsAccrualPeriod as accrualPeriod{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsAccrualStartDate as accrualStartDate{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsAccruedDays as accruedDays{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlBondFunctionsAccruedPeriod as accruedPeriod{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBasisPointValue1 as basisPointValue{withBond*`GenBond b',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBasisPointValue as basisPointValue'{withBond*`GenBond b',withInterestRate*`InterestRate',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBps1 as bpsFromYield'{withBond*`GenBond b',withInterestRate*`InterestRate',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBps2 as bpsFromYield{withBond*`GenBond b',`Double',withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsBps as bps{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsCleanPrice2 as cleanPrice{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure y',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsCleanPrice3 as cleanPrice'{withBond*`GenBond b',withYieldTermStructure*`GenYieldTermStructure y' -- ^discount
  ,`Double' -- ^zSpread
  ,`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsCleanPrice4 as cleanPriceFromYield'{withBond*`GenBond b',withInterestRate*`InterestRate',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsConvexity1 as convexity{withBond*`GenBond b',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsConvexity as convexity'{withBond*`GenBond b',withInterestRate*`InterestRate' -- ^yield
  ,withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsDuration1 as duration{withBond*`GenBond b',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`DurationType',withDay*`Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsDuration as duration'{withBond*`GenBond b',withInterestRate*`InterestRate' -- ^yield
  ,`DurationType',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsNextCashFlowAmount as nextCashFlowAmount{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsPreviousCashFlowAmount as previousCashFlowAmount{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsReferencePeriodEnd as referencePeriodEnd{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsReferencePeriodStart as referencePeriodStart{withBond*`GenBond b',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlBondFunctionsYield2 as yieldFromPrice'{withBond*`GenBond b',fromEnumDouble`Double,BondPriceType'&
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,`Double' --  ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsYieldValueBasisPoint1 as yieldValueBasisPoint{withBond*`GenBond b',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsYieldValueBasisPoint as yieldValueBasisPoint'{withBond*`GenBond b',withInterestRate*`InterestRate' -- ^yield
  ,withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBondFunctionsZSpread as zSpread{withBond*`GenBond b',fromEnumDouble`Double,BondPriceType'&
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,`Compounding',`Frequency',withDay*`Day' -- ^settlementDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |theoretical clean price for the current evaluation date and term structure
{#fun qlBondCleanPrice as currentCleanPrice{withBond*`GenBond b',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
{#fun qlBondDirtyPrice as currentDirtyPrice{withBond*`GenBond b',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCallableFixedRateBond as callableFixedRateBond{fromIntegral`Word' -- ^settlementDays
  ,`Double' -- ^faceAmount
  ,withSchedule*`Schedule',withDoubleArray*`[Double]'& -- ^coupons
  ,withDayCounter*`DayCounter',`BusinessDayConvention'
  ,`Double' -- ^redemption
  ,withMaybeDay*`Maybe Day' -- ^issueDate
  ,withCallabilityArray*`[Callability]'&
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,preErrorCheck-`String'errorCheck*-}->`CallableBond'peekCallableBond*#}
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
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}
{#fun qlConvertibleFloatingRateBond as convertibleFloatingRateBond{withExercise*`Exercise',`Double' -- ^conversionRatio
  ,withCallabilityArray*`[Callability]'&
  ,withDay*`Day' -- ^issueDate
  ,fromIntegral`Word' -- ^settlementDays
  ,withIborIndex*`GenIborIndex ibor',fromIntegral`Word' -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDayCounter*`DayCounter',withSchedule*`Schedule',`Double' -- ^redemption
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}
{#fun qlConvertibleZeroCouponBond as convertibleZeroCouponBond{withExercise*`Exercise',`Double' -- ^conversionRatio
  ,withCallabilityArray*`[Callability]'&
  ,withDay*`Day' -- ^issueDate
  ,fromIntegral`Word' -- ^settlementDays
  ,withDayCounter*`DayCounter',withSchedule*`Schedule',`Double' -- redemption
  ,preErrorCheck-`String'errorCheck*-}->`ConvertibleBond'peekConvertibleBond*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
