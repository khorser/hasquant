{-# LANGUAGE TemplateHaskell #-}
module QuantLib.CashFlow
  (
    Leg
  , CouponLeg
  , asLeg
  , Dividend
  , DurationType(..)
  , RateAveragingType(..)
  , TimingAdjustment(..)
  , PositionType(..)
  , CPIInterpolationType(..)
  , GenLeg
  , CashFlow

  , leg
  , simpleCashFlow
  , indexedCashFlow
  , fixedRateCoupon
  , floatingRateCoupon
  , iborCoupon
  , IborCoupon
  , iborCouponAsCashFlow
  , averageBMACoupon
  , cappedFlooredCoupon
  , cappedFlooredIborCoupon
  , digitalIborCoupon
  , multipleResetsCoupon
  , averagingMultipleResetsPricer
  , compoundingMultipleResetsPricer
  , OvernightIndexedCoupon
  , overnightIndexedCoupon
  , cappedFlooredOvernightIndexedCoupon
  , compoundingOvernightIndexedCouponPricer
  , arithmeticAveragedOvernightIndexedCouponPricer
  , blackCompoundingOvernightIndexedCouponPricer
  , blackAveragingOvernightIndexedCouponPricer
  , CPICoupon
  , cpiCoupon
  , cpiCouponFromBaseDate
  , cpiCouponWithBaseDate
  , CPICouponPricer
  , cpiCouponPricer
  , cpiCouponPricerWithVol
  , setCpiCouponPricer
  , redemption
  , amortizingPayment
  , cashFlowLeg
  , startDate
  , nextCashFlows
  , previousCashFlows
  , cashFlows

  , duration
  , accrualDays
  , accrualEndDate
  , accrualPeriod
  , accrualStartDate
  , accruedAmount
  , accruedDays
  , accruedPeriod
  , atmRate
  , basisPointValue'
  , basisPointValue
  , bpsFromYield
  , bpsFromYield'
  , bps
  , convexity'
  , convexity
  , duration'
  , isExpired
  , maturityDate
  , nextCashFlowAmount
  , nextCashFlowDate
  , nextCouponRate
  , nominal
  , npvFromYield
  , npvFromYield'
  , npv'
  , npv
  , npvbps
  , previousCashFlowAmount
  , previousCashFlowDate
  , previousCouponRate
  , referencePeriodEnd
  , referencePeriodStart
  , yield
  , yieldValueBasisPoint'
  , yieldValueBasisPoint
  , zSpread

  , toCouponLeg
  , couponAccrualStartDates

  , fixedDividend
  , fractionalDividend'
  , fractionalDividend

  , averageBMALeg
  , fixedRateLeg
  , iborLeg
  , iborLegFull
  , IborLegOpts(..)
  , defaultIborLegOpts
  , cmsLeg
  , cmsLegFull
  , CmsLegOpts(..)
  , defaultCmsLegOpts
  , FloatingRateCoupon
  , GenFloatingRateCoupon
  , asFloatingRateCoupon
  , floatingRateCouponRate
  , floatingRateCouponAmount
  , setFloatingRateCouponPricer
  , CmsCoupon
  , cmsCoupon
  , cappedFlooredCmsCoupon
  , cmsSpreadCoupon
  , cappedFlooredCmsSpreadCoupon
  , ReplicationType(..)
  , DigitalReplication
  , digitalReplication
  , digitalReplicationType
  , digitalReplicationGap
  , DigitalCmsCoupon
  , digitalCmsCoupon
  , digitalCmsCouponCallOptionRate
  , digitalCmsCouponPutOptionRate
  , digitalCmsLeg
  , DigitalCmsLegOpts(..)
  , defaultDigitalCmsLegOpts
  , overnightLeg
  , rangeAccrualLeg
  , cpiLeg
  , yoyInflationLeg
  , YoYInflationCouponPricer
  , blackYoYInflationCouponPricer
  , unitDisplacedBlackYoYInflationCouponPricer
  , bachelierYoYInflationCouponPricer
  , setYoYInflationCouponPricer
  , ZeroInflationCashFlow
  , zeroInflationCashFlow
  , zeroInflationCashFlowAsCashFlow
  , zeroInflationCashFlowAmount
  , zeroInflationCashFlowBaseFixing
  , zeroInflationCashFlowIndexFixing
  , CPICashFlow
  , cpiCashFlow
  , cpiCashFlowAsCashFlow
  , cpiCashFlowAmount
  , cpiCashFlowBaseFixing
  , cpiCashFlowIndexFixing
  , EquityCashFlow
  , equityCashFlow
  , equityCashFlowAsCashFlow
  , equityCashFlowAmount
  , equityCashFlowBaseFixing
  , equityCashFlowIndexFixing
  , setEquityCashFlowPricer
  , YieldCurveModel(..)

  , FloatingRateCouponPricer
  , GenFloatingRateCouponPricer
  , asFloatingRateCouponPricer
  , CmsCouponPricer
  , blackIborCouponPricer
  , blackIborQuantoCouponPricer
  , rangeAccrualPricerByBgm
  , setCouponPricer
  , setCouponPricers
  , analyticHaganPricer
  , numericHaganPricer
  , LinearTsrPricerStrategy(..)
  , LinearTsrPricerSettings(..)
  , linearTsrPricer
  , lognormalCmsSpreadPricer
  , EquityCashFlowPricer
  , equityQuantoCashFlowPricer
  , setEquityLegPricer
  ) where
import QuantLib.Internal
{#import QuantLib.InterestRate#}(Compounding, VolatilityType)
{#import QuantLib.Time.Schedule#}(Frequency)
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Internal.Type
import QuantLib.Internal.Common
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import Data.Maybe(fromMaybe)
import Data.List.NonEmpty(NonEmpty, toList)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *CouponLeg foreign -> CCouponLeg' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlCashFlow as CashFlow foreign -> CCashFlow nocode#}
{#pointer *InterestRate foreign -> CInterestRate nocode#}
{#pointer *QlIndex as Index foreign -> CIndex' nocode#}
{#pointer *QlInterestRateIndex as InterestRateIndex foreign -> CInterestRateIndex' nocode#}
{#pointer *QlDividend as Dividend foreign -> CDividend nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex' nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}
{#pointer *QlZeroInflationIndex as ZeroInflationIndex foreign -> CZeroInflationIndex' nocode#}
{#pointer *QlEquityIndex as EquityIndex foreign -> CEquityIndex' nocode#}
{#pointer *QlZeroInflationCashFlow as ZeroInflationCashFlow foreign -> CZeroInflationCashFlow nocode#}
{#pointer *QlCPICashFlow as CPICashFlow foreign -> CCPICashFlow nocode#}
{#pointer *QlEquityCashFlow as EquityCashFlow foreign -> CEquityCashFlow nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *QlFloatingRateCouponPricer as FloatingRateCouponPricer foreign -> CFloatingRateCouponPricer' nocode#}
{#pointer *QlFloatingRateCoupon as FloatingRateCoupon foreign -> CFloatingRateCoupon' nocode#}
{#pointer *QlDigitalReplication as DigitalReplication foreign -> CDigitalReplication nocode#}
{#pointer *QlIborCoupon as IborCoupon foreign -> CIborCoupon' nocode#}
{#pointer *QlOvernightIndexedCoupon as OvernightIndexedCoupon foreign -> COvernightIndexedCoupon' nocode#}
{#pointer *QlCPICoupon as CPICoupon foreign -> CCPICoupon nocode#}
{#pointer *QlCPICouponPricer as CPICouponPricer foreign -> CCPICouponPricer nocode#}
{#pointer *QlCPIVolatilitySurface as CPIVolatilitySurface foreign -> CCPIVolatilitySurface' nocode#}

{#enum DurationType{} deriving(Show, Eq, Read)#}
{#enum RateAveragingType{} add prefix="Averaging" deriving(Show, Eq, Read)#}
{#enum TimingAdjustment{} deriving(Show, Eq, Read)#}

-- IborLegOpts/CmsLegOpts bundle every IborLeg/CmsLeg builder-method param beyond
-- iborLeg/cmsLeg's original 12-arg shape, pre-populated with upstream's own defaults via
-- defaultIborLegOpts/defaultCmsLegOpts, overridden through record-update syntax at the
-- call site -- see OISRateHelperOpts (QuantLib.TermStructure.Yield) for the worked
-- example this follows. The Calendar fields are Maybe here (unlike the raw bindings'
-- plain Calendar) since a real Calendar is only obtainable in IO (`calendar Null`) and
-- can't live in a pure default record value -- iborLegFull/cmsLegFull substitute a fresh
-- Null calendar for Nothing. This splice must stay textually before every
-- {#fun#}-generated binding in this file: c2hs always appends its raw foreign-import
-- stubs at the physical end of the generated module regardless of where in the .chs a
-- {#fun#} hook appears, and a top-level TH splice anywhere in between would otherwise
-- split the file into declaration groups that can't see each other, breaking every
-- earlier {#fun#} wrapper's reference to its own (always-last) foreign-import stub.
$(deriveOptionsRecord "IborLegOpts" []
  [ ("ilgPaymentLag", [t|Int|], [|0|])
  , ("ilgPaymentCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("ilgExCouponPeriod", [t|(Int, TimeUnit)|], [|(0, Days)|])
  , ("ilgExCouponCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("ilgExCouponConvention", [t|BusinessDayConvention|], [|Unadjusted|])
  , ("ilgExCouponEndOfMonth", [t|Bool|], [|False|])
  , ("ilgFixingConvention", [t|BusinessDayConvention|], [|Preceding|])
  , ("ilgUseIndexedCoupons", [t|Maybe Bool|], [|Nothing|])
  ])

-- Same shape as IborLegOpts, minus the fields CmsLeg's builder doesn't have
-- (withPaymentLag/withPaymentCalendar/withIndexedCoupons -- confirmed absent from
-- ql/cashflows/cmscoupon.hpp's CmsLeg). Same splice-placement constraint as above.
$(deriveOptionsRecord "CmsLegOpts" []
  [ ("cmslExCouponPeriod", [t|(Int, TimeUnit)|], [|(0, Days)|])
  , ("cmslExCouponCalendar", [t|Maybe Calendar|], [|Nothing|])
  , ("cmslExCouponConvention", [t|BusinessDayConvention|], [|Unadjusted|])
  , ("cmslExCouponEndOfMonth", [t|Bool|], [|False|])
  , ("cmslFixingConvention", [t|BusinessDayConvention|], [|Preceding|])
  ])

$(deriveOptionsRecord "DigitalCmsLegOpts" []
  [ ("dcmlCallStrikes", [t|[Double]|], [|[]|])
  , ("dcmlCallPosition", [t|PositionType|], [|Long|])
  , ("dcmlCallATM", [t|Bool|], [|False|])
  , ("dcmlCallPayoffs", [t|[Double]|], [|[]|])
  , ("dcmlPutStrikes", [t|[Double]|], [|[]|])
  , ("dcmlPutPosition", [t|PositionType|], [|Long|])
  , ("dcmlPutATM", [t|Bool|], [|False|])
  , ("dcmlPutPayoffs", [t|[Double]|], [|[]|])
  , ("dcmlReplication", [t|Maybe DigitalReplication|], [|Nothing|])
  , ("dcmlNakedOption", [t|Bool|], [|False|])
  ])

-- |Build a 'Leg' of plain, predetermined cash flows from parallel amount\/date arrays.
{#fun qlLeg{withDoubleArray*`[Double]'&,withDayPtr*`[Day]',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

leg :: [(Day, Double)] -- ^amounts and dates
  -> IO Leg
leg f = qlLeg fs ds where (ds, fs) = unzip f

-- |A predetermined payment, suitable for mixing with other cash-flow kinds in
-- 'cashFlowLeg'.  For a leg made entirely of such payments, 'leg' is a more concise API.
{#fun qlSimpleCashFlow as simpleCashFlow{`Double' -- ^amount
  ,withDay*`Day' -- ^payment date
  ,preErrorCheck-`String'errorCheck*-}->`CashFlow'peekCashFlow*#}

-- |A payment of @notional * i(fixingDate) \/ i(baseDate)@, or the same ratio minus one when
-- /growthOnly/ is true.  QuantLib does no date adjustment here; callers supply the already
-- adjusted fixing and payment dates.  This is the generic building block behind the specialized
-- CPI and equity cash flows, and accepts any bound 'GenIndex'.
{#fun qlIndexedCashFlow as indexedCashFlow{`Double' -- ^notional
  ,withIndex*`GenIndex idx' -- ^index
  ,withDay*`Day' -- ^base date
  ,withDay*`Day' -- ^fixing date
  ,withDay*`Day' -- ^payment date
  ,`Bool' -- ^growthOnly
  ,preErrorCheck-`String'errorCheck*-}->`CashFlow'peekCashFlow*#}

-- |A fixed coupon with explicitly supplied payment, accrual, reference-period, and ex-coupon
-- dates.  'Nothing' for a reference or ex-coupon date passes QuantLib's empty @Date()@.
{#fun qlFixedRateCoupon as fixedRateCoupon{withDay*`Day' -- ^payment date
  ,`Double' -- ^nominal
  ,`Double' -- ^rate
  ,withDayCounter*`DayCounter'
  ,withDay*`Day' -- ^accrual start
  ,withDay*`Day' -- ^accrual end
  ,withMaybeDay*`Maybe Day' -- ^reference-period start
  ,withMaybeDay*`Maybe Day' -- ^reference-period end
  ,withMaybeDay*`Maybe Day' -- ^ex-coupon date
  ,preErrorCheck-`String'errorCheck*-}->`CashFlow'peekCashFlow*#}

-- |A generic floating-rate coupon.  Attach a 'FloatingRateCouponPricer' to the resulting leg
-- with 'setCouponPricer' before evaluating a coupon whose rate requires one.  'Nothing' dates
-- pass QuantLib's empty @Date()@; all other constructor parameters are explicit.
{#fun qlFloatingRateCoupon as floatingRateCoupon{withDay*`Day' -- ^payment date
  ,`Double' -- ^nominal
  ,withDay*`Day' -- ^accrual start
  ,withDay*`Day' -- ^accrual end
  ,fromIntegral`Word' -- ^fixing days
  ,withInterestRateIndex*`GenInterestRateIndex ridx'
  ,`Double' -- ^gearing
  ,`Double' -- ^spread
  ,withMaybeDay*`Maybe Day' -- ^reference-period start
  ,withMaybeDay*`Maybe Day' -- ^reference-period end
  ,withDayCounter*`DayCounter'
  ,`Bool' -- ^in arrears
  ,withMaybeDay*`Maybe Day' -- ^ex-coupon date
  ,fromEnumC`BusinessDayConvention' -- ^fixing convention
  ,preErrorCheck-`String'errorCheck*-}->`CashFlow'peekCashFlow*#}

-- |An Ibor-specific floating coupon.  Prefer this to 'floatingRateCoupon' when the index is
-- Ibor: QuantLib then uses IborCoupon's fixing value/maturity-date logic rather than the base
-- floating-coupon implementation.  Date and pricer handling are as in 'floatingRateCoupon'.
{#fun qlIborCouponExact as iborCoupon{withDay*`Day'
  ,`Double',withDay*`Day',withDay*`Day',fromIntegral`Word'
  ,withIborIndex*`GenIborIndex ibor',`Double',`Double'
  ,withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter'
  ,`Bool',withMaybeDay*`Maybe Day',fromEnumC`BusinessDayConvention'
  ,preErrorCheck-`String'errorCheck*-}->`IborCoupon'peekIborCoupon*#}

-- |Convert a concrete Ibor coupon to the generic cash-flow representation used by
-- heterogeneous 'cashFlowLeg' inputs.
{#fun qlIborCouponAsCashFlow as iborCouponAsCashFlow{withIborCoupon*`IborCoupon'}->`CashFlow'peekCashFlow*#}

{#fun qlAverageBMACoupon as averageBMACoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',withBMAIndex*`BMAIndex',`Double',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}
{#fun qlCappedFlooredCoupon as cappedFlooredCoupon{withFloatingRateCoupon*`GenFloatingRateCoupon frc',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}
{#fun qlCappedFlooredIborCoupon as cappedFlooredIborCoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',fromIntegral`Word',withIborIndex*`GenIborIndex ibor',`Double',`Double',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',`Bool',withMaybeDay*`Maybe Day',fromEnumC`BusinessDayConvention',preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}
{#fun qlDigitalIborCoupon as digitalIborCoupon{withIborCoupon*`IborCoupon',fromMaybeDouble`Maybe Double',fromEnumC`PositionType',`Bool',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',fromEnumC`PositionType',`Bool',fromMaybeDouble`Maybe Double',withMaybeDigitalReplication*`Maybe DigitalReplication',`Bool',preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}
{#fun qlMultipleResetsCoupon as multipleResetsCoupon{withDay*`Day',`Double',withSchedule*`Schedule',fromIntegral`Word',withIborIndex*`GenIborIndex ibor',`Double',`Double',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}
{#fun qlAveragingMultipleResetsPricer as averagingMultipleResetsPricer{preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlCompoundingMultipleResetsPricer as compoundingMultipleResetsPricer{preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlOvernightIndexedCoupon as overnightIndexedCoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',withOvernightIborIndex*`OvernightIborIndex',`Double',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',`Bool',fromEnumC`RateAveragingType',fromIntegral`Word',fromIntegral`Word',`Bool',`Bool',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',fromMaybeInt`Maybe Int',preErrorCheck-`String'errorCheck*-}->`OvernightIndexedCoupon'peekOvernightIndexedCoupon*#}
{#fun qlCappedFlooredOvernightIndexedCoupon as cappedFlooredOvernightIndexedCoupon{withOvernightIndexedCoupon*`OvernightIndexedCoupon',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',`Bool',`Bool',preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}
{#fun qlCompoundingOvernightIndexedCouponPricer as compoundingOvernightIndexedCouponPricer{withMaybeOptionletVolatilityStructure*`Maybe OptionletVolatilityStructure',`Bool',preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlArithmeticAveragedOvernightIndexedCouponPricer as arithmeticAveragedOvernightIndexedCouponPricer{`Double',`Double',`Bool',withMaybeOptionletVolatilityStructure*`Maybe OptionletVolatilityStructure',`Bool',preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlBlackCompoundingOvernightIndexedCouponPricer as blackCompoundingOvernightIndexedCouponPricer{withMaybeOptionletVolatilityStructure*`Maybe OptionletVolatilityStructure',`Bool',preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlBlackAveragingOvernightIndexedCouponPricer as blackAveragingOvernightIndexedCouponPricer{withMaybeOptionletVolatilityStructure*`Maybe OptionletVolatilityStructure',`Bool',preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlCPICoupon as cpiCoupon{`Double',withDay*`Day',`Double',withDay*`Day',withDay*`Day',withZeroInflationIndex*`GenZeroInflationIndex zidx',fromEnumQuantity`(Int,TimeUnit)'&,fromEnumC`CPIInterpolationType',withDayCounter*`DayCounter',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`CPICoupon'peekCPICoupon*#}
{#fun qlCPICouponFromBaseDate as cpiCouponFromBaseDate{withDay*`Day',withDay*`Day',`Double',withDay*`Day',withDay*`Day',withZeroInflationIndex*`GenZeroInflationIndex zidx',fromEnumQuantity`(Int,TimeUnit)'&,fromEnumC`CPIInterpolationType',withDayCounter*`DayCounter',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`CPICoupon'peekCPICoupon*#}
{#fun qlCPICouponWithBaseDate as cpiCouponWithBaseDate{`Double',withDay*`Day',withDay*`Day',`Double',withDay*`Day',withDay*`Day',withZeroInflationIndex*`GenZeroInflationIndex zidx',fromEnumQuantity`(Int,TimeUnit)'&,fromEnumC`CPIInterpolationType',withDayCounter*`DayCounter',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`CPICoupon'peekCPICoupon*#}
{#fun qlCPICouponPricer as cpiCouponPricer{withMaybeYieldTermStructure*`Maybe YieldTermStructure',preErrorCheck-`String'errorCheck*-}->`CPICouponPricer'peekCPICouponPricer*#}
{#fun qlCPICouponPricerWithVol as cpiCouponPricerWithVol{withGenVolatilityTermStructure*`CPIVolatilitySurface',withMaybeYieldTermStructure*`Maybe YieldTermStructure',preErrorCheck-`String'errorCheck*-}->`CPICouponPricer'peekCPICouponPricer*#}
{#fun qlCPICouponSetPricer as setCpiCouponPricer{withCPICoupon*`CPICoupon',withCPICouponPricer*`CPICouponPricer',preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlRedemption as redemption{`Double',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`CashFlow'peekCashFlow*#}
{#fun qlAmortizingPayment as amortizingPayment{`Double',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`CashFlow'peekCashFlow*#}

-- |Build a heterogeneous 'Leg' from cash-flow building blocks.  The leg takes shared ownership
-- of each flow, so it remains valid when the individual 'CashFlow' values are no longer retained.
{#fun qlCashFlowLeg as cashFlowLeg{withCashFlowArray*`[CashFlow]'&,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Returns the start (i.e. first accrual) date for the given Leg
{#fun qlLegStartDate as startDate{withLeg*`GenLeg l',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |return cashflows that will occur after /settlementDate/
{#fun qlNextCashFlows as nextCashFlows{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |return cashflows that occurred before /settlementDate/
{#fun qlPreviousCashFlows as previousCashFlows{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Raw binding for 'cashFlows': dates, amounts, and whether each has occurred as of /settlementDate/.
{#fun qlLegCashFlows{withLeg*`GenLeg l',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preArray-`[Double]'&peekDoubleArray*,preArray-`[Day]'&peekDayArray*,preArray-`[Bool]'&peekBoolArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |return cash flows together with an indicator whether they occurred as of /settlementDate/
cashFlows :: Leg
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> IO [(Day, Double, Bool)] -- ^date, amount, hasOccurred
cashFlows l i d = do{(as, ds, hs) <- qlLegCashFlows l i d; return $ zip3 ds as hs}

-- |Cash-flow duration.
-- The simple duration of a string of cash flows is defined as \[ D_{\mathrm{simple}} = \frac{\sum t_i c_i B(t_i)}{\sum c_i B(t_i)} \] where $ c_i $ is the amount of the $ i $-th cash flow, $ t_i $ is its payment time, and $ B(t_i) $ is the corresponding discount according to the passed yield.The modified duration is defined as \[ D_{\mathrm{modified}} = -\frac{1}{P} \frac{\partial P}{\partial y} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.The Macaulay duration is defined for a compounded IRR as \[ D_{\mathrm{Macaulay}} = \left( 1 + \frac{y}{N} \right) D_{\mathrm{modified}} \] where $ y $ is the IRR and $ N $ is the number of cash flows per year.
{#fun qlCashFlowsDuration as duration{withLeg*`GenLeg l',withInterestRate*`InterestRate' -- ^yield
  ,`DurationType',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Number of days in the accrual period of the coupon paying on /settlementDate/.
{#fun qlCashFlowsAccrualDays as accrualDays{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |End of the accrual period of the coupon paying on /settlementDate/.
{#fun qlCashFlowsAccrualEndDate as accrualEndDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

-- |Length, in years, of the accrual period of the coupon paying on /settlementDate/.
{#fun qlCashFlowsAccrualPeriod as accrualPeriod{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Start of the accrual period of the coupon paying on /settlementDate/.
{#fun qlCashFlowsAccrualStartDate as accrualStartDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

-- |Accrued amount of the coupon paying on /settlementDate/.
{#fun qlCashFlowsAccruedAmount as accruedAmount{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Number of days accrued so far on the coupon paying on /settlementDate/.
{#fun qlCashFlowsAccruedDays as accruedDays{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |Fraction of the accrual period elapsed, as of /settlementDate/, for the coupon paying then.
{#fun qlCashFlowsAccruedPeriod as accruedPeriod{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Basis-point value, as 'basisPointValue'' but taking a plain yield\/day counter\/compounding\/frequency
-- instead of an 'InterestRate'.
{#fun qlCashFlowsBasisPointValue1 as basisPointValue{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Basis-point value.
-- Obtained by setting dy = 0.0001 in the 2nd-order Taylor series expansion.
{#fun qlCashFlowsBasisPointValue as basisPointValue'{withLeg*`GenLeg l',withInterestRate*`InterestRate'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsBps1 as bpsFromYield'{withLeg*`GenLeg l',withInterestRate*`InterestRate'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Basis-point sensitivity, as 'bpsFromYield'' but taking a plain yield\/day counter\/compounding\/frequency
-- instead of an 'InterestRate'.
{#fun qlCashFlowsBps2 as bpsFromYield{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Cash-flow convexity, as 'convexity'' but taking a plain yield\/day counter\/compounding\/frequency
-- instead of an 'InterestRate'.
{#fun qlCashFlowsConvexity1 as convexity{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
    ,withMaybeDay*`Maybe Day' -- ^settlementDate
    ,withMaybeDay*`Maybe Day' -- ^npvDate
    ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Cash-flow convexity.
-- The convexity of a string of cash flows is defined as \[ C = \frac{1}{P} \frac{\partial^2 P}{\partial y^2} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.
{#fun qlCashFlowsConvexity as convexity'{withLeg*`GenLeg l',withInterestRate*`InterestRate'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Cash-flow duration, as 'duration' but taking a plain yield\/day counter\/compounding\/frequency
-- instead of an 'InterestRate'.
{#fun qlCashFlowsDuration1 as duration'{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter'
  ,`Compounding',`Frequency',`DurationType',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Whether every cash flow in the leg has occurred as of /settlementDate/.
{#fun qlCashFlowsIsExpired as isExpired{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |Date of the leg's last cash flow.
{#fun qlCashFlowsMaturityDate as maturityDate{withLeg*`GenLeg l',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Amount of the first cash flow paying after /settlementDate/.
{#fun qlCashFlowsNextCashFlowAmount as nextCashFlowAmount{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Date of the first cash flow paying after /settlementDate/.
{#fun qlCashFlowsNextCashFlowDate as nextCashFlowDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}

-- |Coupon rate of the next cash flow paying after /settlementDate/.
{#fun qlCashFlowsNextCouponRate as nextCouponRate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Nominal of the coupon paying on /settlementDate/.
{#fun qlCashFlowsNominal as nominal{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the cash flows.
-- The IRR is the interest rate at which the NPV of the cash flows equals the dirty price.The NPV is the sum of the cash flows, each discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv1 as npvFromYield'{withLeg*`GenLeg l',withInterestRate*`InterestRate',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the cash flows, as 'npvFromYield'' but taking a plain yield\/day counter\/compounding\/frequency
-- instead of an 'InterestRate'.
{#fun qlCashFlowsNpv2 as npvFromYield{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |At-the-money rate of the cash flows.
-- The result is the fixed rate for which a fixed rate cash flow vector, equivalent to the input vector, has the required NPV according to the given term structure. If the required NPV is not given, the input cash flow vector's NPV is used instead.
{#fun qlCashFlowsAtmRate as atmRate{withLeg*`GenLeg l',withYieldTermStructure*`GenYieldTermStructure y',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,`Double' -- ^npv
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given term structure.
{#fun qlCashFlowsBps as bps{withLeg*`GenLeg l',withYieldTermStructure*`GenYieldTermStructure y',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the cash flows.
-- For details on z-spread refer to: "Credit Spreads Explained", Lehman Brothers European Fixed Income Research - March 2004, D. O'KaneThe NPV is the sum of the cash flows, each discounted according to the z-spreaded term structure. The result is affected by the choice of the z-spread compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv3 as npv'{withLeg*`GenLeg l',withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^zSpread
  ,`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV of the cash flows.
-- The NPV is the sum of the cash flows, each discounted according to the given term structure.
{#fun qlCashFlowsNpv as npv{withLeg*`GenLeg l',withYieldTermStructure*`GenYieldTermStructure y',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV and BPS of the cash flows.
-- The NPV and BPS of the cash flows calculated together for performance reason
{#fun qlCashFlowsNpvbps as npvbps{withLeg*`GenLeg l',withYieldTermStructure*`GenYieldTermStructure y',`Bool' -- ^includeSettlementDateFlows
  ,withDay*`Day' -- ^settlementDate
  ,withDay*`Day' -- ^npvDate
  ,prePtr-`Double'peekDouble*,prePtr-`Double'peekDouble*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |implied Z-spread.
{#fun qlCashFlowsZSpread as zSpread{withLeg*`GenLeg l',`Double' -- ^npv
  ,withYieldTermStructure*`GenYieldTermStructure y',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Amount of the last cash flow that paid before or at /settlementDate/.
{#fun qlCashFlowsPreviousCashFlowAmount as previousCashFlowAmount{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Date of the last cash flow that paid before or at /settlementDate/.
{#fun qlCashFlowsPreviousCashFlowDate as previousCashFlowDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day'toMaybeDay#}

-- |Coupon rate of the last cash flow that paid before or at /settlementDate/.
{#fun qlCashFlowsPreviousCouponRate as previousCouponRate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |End of the reference period of the coupon paying on /settlementDate/.
{#fun qlCashFlowsReferencePeriodEnd as referencePeriodEnd{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

-- |Start of the reference period of the coupon paying on /settlementDate/.
{#fun qlCashFlowsReferencePeriodStart as referencePeriodStart{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}

-- |Implied internal rate of return.
-- The function verifies the theoretical existance of an IRR and numerically establishes the IRR to the desired precision.
{#fun qlCashFlowsYield as yield{withLeg*`GenLeg l',`Double' -- ^npv
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Yield value of a basis point, as 'yieldValueBasisPoint'' but taking a plain
-- yield\/day counter\/compounding\/frequency instead of an 'InterestRate'.
{#fun qlCashFlowsYieldValueBasisPoint1 as yieldValueBasisPoint{withLeg*`GenLeg l',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Yield value of a basis point.
-- The yield value of a one basis point change in price is the derivative of the yield with respect to the price multiplied by 0.01
{#fun qlCashFlowsYieldValueBasisPoint as yieldValueBasisPoint'{withLeg*`GenLeg l',withInterestRate*`InterestRate' -- ^yield
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |start of the accrual periods for a coupon leg
{#fun qlCouponAccrualStartDates as couponAccrualStartDates{withGenLeg*`CouponLeg',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Predetermined cash flow paying a fixed /amount/ at /date/.
{#fun qlFixedDividend as fixedDividend{`Double' -- ^amount
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Dividend'peekDividend*#}

-- |Predetermined cash flow paying /rate/ times /nominal/ at /date/.
{#fun qlFractionalDividend1 as fractionalDividend'{`Double' -- ^rate
  ,`Double' -- ^nominal
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Dividend'peekDividend*#}

-- |Predetermined cash flow paying a fractional /rate/ of the underlying's price at /date/.
{#fun qlFractionalDividend as fractionalDividend{`Double' -- ^rate
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Dividend'peekDividend*#}

-- |Build a leg of average-BMA coupons.
{#fun qlAverageBMALeg as averageBMALeg{withSchedule*`Schedule',withBMAIndex*`BMAIndex'
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention',withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Build a leg of fixed-rate coupons.
fixedRateLeg :: Schedule -> NonEmpty Double -> NonEmpty InterestRate -> BusinessDayConvention -> DayCounter -> Calendar -> IO Leg
fixedRateLeg schedule notionals rates = fixedRateLeg_ schedule notionals (toList rates)
{#fun qlFixedRateLeg as fixedRateLeg_{withSchedule*`Schedule',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withInterestRateArray*`[InterestRate]'& -- ^couponRates
  ,fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withDayCounter*`DayCounter' -- ^firstPeriodDayCounter
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |iborLeg keeps its original 12-arg signature -- existing callers are unaffected -- but
-- now delegates to iborLeg_, the raw binding widened to IborLeg's full builder surface,
-- hardcoding upstream's own defaults for the params iborLeg doesn't expose. Use
-- 'iborLegFull' to reach those (payment lag\/calendar, ex-coupon period, fixing
-- convention, indexed\/at-par coupons) via 'IborLegOpts'.
iborLeg :: Schedule -> GenIborIndex ibor -> NonEmpty Double -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> IO Leg
iborLeg schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp = do
  cal <- calendar Null
  iborLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (ilgPaymentLag defaultIborLegOpts) cal (ilgExCouponPeriod defaultIborLegOpts) cal
    (ilgExCouponConvention defaultIborLegOpts) (ilgExCouponEndOfMonth defaultIborLegOpts)
    (ilgFixingConvention defaultIborLegOpts) (ilgUseIndexedCoupons defaultIborLegOpts)

-- |'iborLeg' widened to every 'IborLeg' builder-method param via 'IborLegOpts'.
iborLegFull :: Schedule -> GenIborIndex ibor -> NonEmpty Double -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> IborLegOpts
  -> IO Leg
iborLegFull schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp opts = do
  cal <- calendar Null
  iborLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (ilgPaymentLag opts) (fromMaybe cal (ilgPaymentCalendar opts)) (ilgExCouponPeriod opts)
    (fromMaybe cal (ilgExCouponCalendar opts)) (ilgExCouponConvention opts)
    (ilgExCouponEndOfMonth opts) (ilgFixingConvention opts) (ilgUseIndexedCoupons opts)

-- |Raw binding for 'iborLeg'\/'iborLegFull': builds a leg of capped\/floored Ibor-rate coupons.
{#fun qlIborLeg as iborLeg_{withSchedule*`Schedule',withIborIndex*`GenIborIndex ibor',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withIntArray*`[Word]'&  -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,`Bool' -- ^zeroPayments
  ,fromIntegral`Int' -- ^paymentLag
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,fromEnumC`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,fromEnumC`BusinessDayConvention' -- ^fixingConvention
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |CMS leg builder (analog of 'iborLeg'), 12-arg core shape -- same defaults-hardcoding
-- pattern as 'iborLeg' for the params not in this signature. Use 'cmsLegFull' to reach
-- them ('CmsLegOpts').
cmsLeg :: Schedule -> GenSwapIndex sidx -> NonEmpty Double -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> IO Leg
cmsLeg schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp = do
  cal <- calendar Null
  cmsLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (cmslExCouponPeriod defaultCmsLegOpts) cal (cmslExCouponConvention defaultCmsLegOpts)
    (cmslExCouponEndOfMonth defaultCmsLegOpts) (cmslFixingConvention defaultCmsLegOpts)

-- |'cmsLeg' widened to every 'CmsLeg' builder-method param via 'CmsLegOpts'.
cmsLegFull :: Schedule -> GenSwapIndex sidx -> NonEmpty Double -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> CmsLegOpts
  -> IO Leg
cmsLegFull schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp opts = do
  cal <- calendar Null
  cmsLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (cmslExCouponPeriod opts) (fromMaybe cal (cmslExCouponCalendar opts))
    (cmslExCouponConvention opts) (cmslExCouponEndOfMonth opts) (cmslFixingConvention opts)

-- |Raw binding for 'cmsLeg'\/'cmsLegFull': builds a leg of capped\/floored CMS-rate coupons.
{#fun qlCmsLeg as cmsLeg_{withSchedule*`Schedule',withSwapIndex*`GenSwapIndex sidx',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withIntArray*`[Word]'&  -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,`Bool' -- ^zeroPayments
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,fromEnumC`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,fromEnumC`BusinessDayConvention' -- ^fixingConvention
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Build a leg of overnight-index coupons.
{#fun qlOvernightLeg as overnightLeg{withSchedule*`Schedule',withOvernightIborIndex*`OvernightIborIndex',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals'
  ,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention',withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Build a leg of range-accrual floating-rate coupons.
{#fun qlRangeAccrualLeg as rangeAccrualLeg{withSchedule*`Schedule',withIborIndex*`GenIborIndex ibor',withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention',withIntArray*`[Word]'& -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^lowerTriggers
  ,withDoubleArray*`[Double]'& -- ^upperTriggers
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^observationTenor
  ,fromEnumC`BusinessDayConvention',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Fixed-rate coupons scaled by the ratio of a 'ZeroInflationIndex' fixing to /baseCPI/
-- (a 'CPICoupon' leg -- no capped\/floored variant, unlike 'yoyInflationLeg': QL 1.43 has no
-- @CappedFlooredCPICoupon@ class to build one from, see README.md's TODO).
{#fun qlCPILeg as cpiLeg{withSchedule*`Schedule',withZeroInflationIndex*`ZeroInflationIndex'
  ,`Double' -- ^baseCPI
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^fixedRates
  ,withDayCounter*`DayCounter' -- ^paymentDayCounter
  ,fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`Bool' -- ^subtractInflationNominal
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |Year-on-year inflation-linked coupons (a 'YoYInflationCoupon' leg). Non-empty /caps/\//floors/
-- build 'CappedFlooredYoYInflationCoupon's instead of plain ones -- but /any/ resulting coupon
-- (capped or not) still needs a pricer set via 'setYoYInflationCouponPricer' before its
-- 'QuantLib.CashFlow.npv'\/'amount' can be computed: upstream's @InflationCoupon::rate()@
-- requires @pricer_@ unconditionally, not just for the capped\/floored case (confirmed by reading
-- @inflationcoupon.cpp@). CPI-leg ('cpiLeg') caps\/floors have no equivalent in QL 1.43 (no
-- @CappedFlooredCPICoupon@ class exists upstream, see README.md's TODO) -- this is a
-- QuantLib-version limitation, not an unbound feature.
{#fun qlYoYInflationLeg as yoyInflationLeg{withSchedule*`Schedule',withCalendar*`Calendar'
  ,withYoYInflationIndex*`YoYInflationIndex'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,fromEnumC`CPIInterpolationType' -- ^interpolation
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^notionals
  ,withDayCounter*`DayCounter' -- ^paymentDayCounter
  ,fromEnumC`BusinessDayConvention' -- ^paymentAdjustment
  ,withIntArray*`[Word]'& -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#pointer *QlZeroInflationCashFlow as ZeroInflationCashFlow foreign -> CZeroInflationCashFlow nocode#}
{#pointer *QlCPICashFlow as CPICashFlow foreign -> CCPICashFlow nocode#}
{#pointer *QlEquityCashFlow as EquityCashFlow foreign -> CEquityCashFlow nocode#}
{#pointer *QlEquityCashFlowPricer as EquityCashFlowPricer foreign -> CEquityCashFlowPricer nocode#}

-- |Cash flow dependent on a 'ZeroInflationIndex' ratio (not a coupon -- no accruals).
-- The ratio is taken between fixings observed at /startDate/ and /endDate/ minus /observationLag/.
{#fun qlZeroInflationCashFlow as zeroInflationCashFlow{`Double' -- ^notional
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,withDay*`Day' -- ^startDate
  ,withDay*`Day' -- ^endDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withDay*`Day' -- ^paymentDate
  ,`Bool' -- ^growthOnly
  ,preErrorCheck-`String'errorCheck*-}->`ZeroInflationCashFlow'peekZeroInflationCashFlow*#}

-- |Use this zero-inflation cash flow in a heterogeneous 'cashFlowLeg'. The returned generic
-- 'CashFlow' shares ownership with the original, so both values remain valid independently.
{#fun qlZeroInflationCashFlowAsCashFlow as zeroInflationCashFlowAsCashFlow{withZeroInflationCashFlow*`ZeroInflationCashFlow'}->`CashFlow'peekCashFlow*#}

-- |Amount of the cash flow: the index ratio (times notional), or the ratio minus one if growthOnly.
{#fun qlZeroInflationCashFlowAmount as zeroInflationCashFlowAmount{withZeroInflationCashFlow*`ZeroInflationCashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Fixing used as the base of the ratio (as of /startDate/, lagged).
{#fun qlZeroInflationCashFlowBaseFixing as zeroInflationCashFlowBaseFixing{withZeroInflationCashFlow*`ZeroInflationCashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Fixing used as the numerator of the ratio (as of /endDate/, lagged).
{#fun qlZeroInflationCashFlowIndexFixing as zeroInflationCashFlowIndexFixing{withZeroInflationCashFlow*`ZeroInflationCashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |CPI-linked cash flow (not a coupon -- no accruals), with an optional explicit /baseFixing/
-- (pass 'Nothing' to derive it from /baseDate/ instead).
{#fun qlCPICashFlow as cpiCashFlow{`Double' -- ^notional
  ,withZeroInflationIndex*`ZeroInflationIndex'
  ,withMaybeDay*`Maybe Day' -- ^baseDate
  ,fromMaybeDouble`Maybe Double' -- ^baseFixing
  ,withDay*`Day' -- ^observationDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,fromEnumC`CPIInterpolationType' -- ^interpolation
  ,withDay*`Day' -- ^paymentDate
  ,`Bool' -- ^growthOnly
  ,preErrorCheck-`String'errorCheck*-}->`CPICashFlow'peekCPICashFlow*#}

-- |Use this CPI cash flow in a heterogeneous 'cashFlowLeg'. The returned generic 'CashFlow'
-- shares ownership with the original, so both values remain valid independently.
{#fun qlCPICashFlowAsCashFlow as cpiCashFlowAsCashFlow{withCPICashFlow*`CPICashFlow'}->`CashFlow'peekCashFlow*#}

-- |Amount of the cash flow: the index ratio (times notional), or the ratio minus one if growthOnly.
{#fun qlCPICashFlowAmount as cpiCashFlowAmount{withCPICashFlow*`CPICashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Fixing used as the base of the ratio: the explicit /baseFixing/ if given at construction, else derived from /baseDate/.
{#fun qlCPICashFlowBaseFixing as cpiCashFlowBaseFixing{withCPICashFlow*`CPICashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Fixing used as the numerator of the ratio (as of /observationDate/, lagged).
{#fun qlCPICashFlowIndexFixing as cpiCashFlowIndexFixing{withCPICashFlow*`CPICashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Cash flow dependent on the total return of an 'QuantLib.Index.Equity.EquityIndex' (not a coupon
-- -- no accruals): @index(fixingDate)\/index(baseDate)@, or that ratio minus one if /growthOnly/.
-- If no 'EquityCashFlowPricer' is attached via 'setEquityCashFlowPricer', 'equityCashFlowAmount'
-- computes this ratio directly from the index; a pricer (e.g. 'equityQuantoCashFlowPricer') is only
-- needed to price a quanto-adjusted variant.
{#fun qlEquityCashFlow as equityCashFlow{`Double' -- ^notional
  ,withEquityIndex*`EquityIndex'
  ,withDay*`Day' -- ^baseDate
  ,withDay*`Day' -- ^fixingDate
  ,withDay*`Day' -- ^paymentDate
  ,`Bool' -- ^growthOnly
  ,preErrorCheck-`String'errorCheck*-}->`EquityCashFlow'peekEquityCashFlow*#}

-- |Use this equity cash flow in a heterogeneous 'cashFlowLeg'. The returned generic 'CashFlow'
-- shares ownership with the original, so both values remain valid independently.
{#fun qlEquityCashFlowAsCashFlow as equityCashFlowAsCashFlow{withEquityCashFlow*`EquityCashFlow'}->`CashFlow'peekCashFlow*#}

-- |Amount of the cash flow: the index ratio (times notional), or the ratio minus one if growthOnly --
-- or, if a pricer is attached, the notional times the pricer's 'price'.
{#fun qlEquityCashFlowAmount as equityCashFlowAmount{withEquityCashFlow*`EquityCashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Fixing used as the base of the ratio (as of /baseDate/).
{#fun qlEquityCashFlowBaseFixing as equityCashFlowBaseFixing{withEquityCashFlow*`EquityCashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Fixing used as the numerator of the ratio (as of /fixingDate/).
{#fun qlEquityCashFlowIndexFixing as equityCashFlowIndexFixing{withEquityCashFlow*`EquityCashFlow',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Attach a pricer (e.g. from 'equityQuantoCashFlowPricer') to a single 'EquityCashFlow'; see
-- 'setEquityLegPricer' to attach one to every 'EquityCashFlow' in a leg instead.
{#fun qlEquityCashFlowSetPricer as setEquityCashFlowPricer{withEquityCashFlow*`EquityCashFlow',withEquityCashFlowPricer*`EquityCashFlowPricer',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Quanto-adjusted pricer for an 'EquityCashFlow' whose equity leg is denominated in a currency
-- other than the swap's payment currency.
{#fun qlEquityQuantoCashFlowPricer as equityQuantoCashFlowPricer{withYieldTermStructure*`GenYieldTermStructure y' -- ^quantoCurrencyTermStructure
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv1' -- ^equityVolatility
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv2' -- ^fxVolatility
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`EquityCashFlowPricer'peekEquityCashFlowPricer*#}

-- |Attach a pricer to every 'EquityCashFlow' found in /leg/ (non-'EquityCashFlow' entries are left
-- untouched); see 'setEquityCashFlowPricer' to attach one to a single cash flow instead.
{#fun qlQuantLibSetEquityCashFlowPricer as setEquityLegPricer{withLeg*`GenLeg l',withEquityCashFlowPricer*`EquityCashFlowPricer',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |try to downcast leg to a coupon leg
-- don't blame me, it's how QuantLib works
{#fun qlLegToCouponLeg as toCouponLeg{withLeg*`GenLeg l',preErrorCheck-`String'errorCheck*-}->`CouponLeg'peekCouponLeg*#}

{#enum YieldCurveModel{} deriving(Show, Eq, Read)#}

{#pointer *QlCmsCouponPricer as CmsCouponPricer foreign -> CCmsCouponPricer' nocode#}
{#pointer *QlCmsCoupon as CmsCoupon foreign -> CCmsCoupon' nocode#}
{#pointer *QlSwapSpreadIndex as SwapSpreadIndex foreign -> CSwapSpreadIndex' nocode#}
{#pointer *QlDigitalCmsCoupon as DigitalCmsCoupon foreign -> CDigitalCmsCoupon' nocode#}
{#pointer *QlSmileSection as SmileSection foreign -> CSmileSection nocode#}
{#pointer *QlYoYOptionletVolatilitySurface as YoYOptionletVolatilitySurface foreign -> CYoYOptionletVolatilitySurface' nocode#}
{#pointer *QlYoYInflationCouponPricer as YoYInflationCouponPricer foreign -> CYoYInflationCouponPricer nocode#}
{#enum ReplicationType{} deriving(Show, Eq, Read)#}

-- |Black-formula pricer for capped/floored Ibor coupons
{#fun qlBlackIborCouponPricer as blackIborCouponPricer{withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov'
  ,`TimingAdjustment'
  ,withMaybeQuote*`Maybe (GenQuote q)' -- ^correlation
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

-- |Experimental quanto-adjusted Black-formula pricer for capped/floored Ibor coupons.
-- The FX Black volatility and underlying/FX correlation determine the quanto adjustment;
-- the caplet volatility supplies the ordinary Ibor optionlet pricing inputs.  The three
-- handles are retained by QuantLib, so relinking their underlying quotes or term structures
-- updates the pricer in the usual way.
{#fun qlBlackIborQuantoCouponPricer as blackIborQuantoCouponPricer{withBlackVolTermStructure*`GenBlackVolTermStructure bv'
  ,withQuote*`GenQuote q' -- ^underlyingFxCorrelation
  ,withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov' -- ^capletVolatility
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

-- |BGM-based pricer for 'RangeAccrualFloatersCoupon's (a 'rangeAccrualLeg')
{#fun qlRangeAccrualPricerByBgm as rangeAccrualPricerByBgm{`Double' -- ^correlation
  ,withSmileSection*`SmileSection' -- ^smilesOnExpiry
  ,withSmileSection*`SmileSection' -- ^smilesOnPayment
  ,`Bool' -- ^withSmile
  ,`Bool' -- ^byCallSpread
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

-- |Black-formula pricer for capped\/floored 'yoyInflationLeg' coupons.
{#fun qlBlackYoYInflationCouponPricer as blackYoYInflationCouponPricer{withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCouponPricer'peekYoYInflationCouponPricer*#}

-- |Unit-Displaced-Black-formula pricer for capped\/floored 'yoyInflationLeg' coupons.
{#fun qlUnitDisplacedBlackYoYInflationCouponPricer as unitDisplacedBlackYoYInflationCouponPricer{withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCouponPricer'peekYoYInflationCouponPricer*#}

-- |Bachelier-formula pricer for capped\/floored 'yoyInflationLeg' coupons.
{#fun qlBachelierYoYInflationCouponPricer as bachelierYoYInflationCouponPricer{withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,preErrorCheck-`String'errorCheck*-}->`YoYInflationCouponPricer'peekYoYInflationCouponPricer*#}

-- |Set the pricer of every 'QuantLib.Instrument.InflationCapFloor.YoYInflationCapFloor'-ready
-- 'YoYInflationCoupon'\/'CappedFlooredYoYInflationCoupon' in /leg/. Required before pricing (via
-- 'QuantLib.CashFlow.npv' or an 'QuantLib.Instrument.setPricingEngine'd instrument built on the
-- leg) any 'yoyInflationLeg' built with non-empty caps\/floors -- 'yoyInflationLeg' auto-attaches
-- a default (non-vol) pricer only when caps and floors are both empty.
{#fun qlSetYoYInflationCouponPricer as setYoYInflationCouponPricer{withLeg*`GenLeg l',withYoYInflationCouponPricer*`YoYInflationCouponPricer',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Set the pricer of every floating-rate coupon in /leg/.
{#fun qlQuantLibSetCouponPricer as setCouponPricer{withLeg*`GenLeg l',withFloatingRateCouponPricer*`GenFloatingRateCouponPricer frcp',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Set the pricer of every floating-rate coupon in /leg/, picking each coupon's pricer from
-- /pricers/ by matching coupon type.
{#fun qlQuantLibSetCouponPricers as setCouponPricers{withLeg*`GenLeg l',withFloatingRateCouponPricerArray*`[GenFloatingRateCouponPricer frcp]'&,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Constant-maturity-swap (CMS) coupon.
--
-- The start and end dates are used as supplied: QuantLib performs no business-day adjustment
-- when constructing this coupon, so callers must supply already adjusted dates.  Attach a CMS
-- pricer before asking for its rate or amount.
{#fun qlCmsCoupon as cmsCoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',fromIntegral`Word',withSwapIndex*`GenSwapIndex sidx'
  ,`Double',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',`Bool',withMaybeDay*`Maybe Day',fromEnumC`BusinessDayConvention'
  ,preErrorCheck-`String'errorCheck*-}->`CmsCoupon'peekCmsCoupon*#}

-- |Constant-maturity-swap-spread coupon.  Its index is the geared difference of two swap rates.
-- QuantLib does no date adjustment at construction, so callers must provide business dates.
{#fun qlCmsSpreadCoupon as cmsSpreadCoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',fromIntegral`Word',withSwapSpreadIndex*`SwapSpreadIndex'
  ,`Double',`Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',`Bool',withMaybeDay*`Maybe Day',fromEnumC`BusinessDayConvention'
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}

-- |The coupon rate.  It is calculated by the attached 'FloatingRateCouponPricer'.
{#fun qlFloatingRateCouponRate as floatingRateCouponRate{withFloatingRateCoupon*`GenFloatingRateCoupon frc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Cash-flow amount, equal to @rate * accrualPeriod * nominal@.
{#fun qlFloatingRateCouponAmount as floatingRateCouponAmount{withFloatingRateCoupon*`GenFloatingRateCoupon frc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Set the coupon pricer used to calculate a floating-rate coupon's rate.
{#fun qlFloatingRateCouponSetPricer as setFloatingRateCouponPricer{withFloatingRateCoupon*`GenFloatingRateCoupon frc',withFloatingRateCouponPricer*`GenFloatingRateCouponPricer frcp',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |CMS coupon with optional cap and floor.  This is QuantLib's
-- @CappedFlooredCmsCoupon@: it wraps a 'CmsCoupon' in a capped/floored coupon and returns it at
-- the useful 'FloatingRateCoupon' level.  'Nothing' means no cap or floor.
{#fun qlCappedFlooredCmsCoupon as cappedFlooredCmsCoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',fromIntegral`Word',withSwapIndex*`GenSwapIndex sidx'
  ,`Double',`Double',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',`Bool',withMaybeDay*`Maybe Day',fromEnumC`BusinessDayConvention'
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}

-- |Capped/floored CMS-spread coupon, returned at the useful 'FloatingRateCoupon' level.
-- 'Nothing' represents QuantLib's absent cap or floor.
{#fun qlCappedFlooredCmsSpreadCoupon as cappedFlooredCmsSpreadCoupon{withDay*`Day',`Double',withDay*`Day',withDay*`Day',fromIntegral`Word',withSwapSpreadIndex*`SwapSpreadIndex'
  ,`Double',`Double',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',withMaybeDay*`Maybe Day',withMaybeDay*`Maybe Day',withDayCounter*`DayCounter',`Bool',withMaybeDay*`Maybe Day',fromEnumC`BusinessDayConvention'
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCoupon'peekFloatingRateCoupon*#}

-- |Digital-option replication strategy.  It specifies the sub, central, or super replication
-- used to price the embedded digital option in a digital coupon; /gap/ is the call/put-spread
-- width used by that replication.
{#fun qlDigitalReplication as digitalReplication{`ReplicationType',`Double',preErrorCheck-`String'errorCheck*-}->`DigitalReplication'peekDigitalReplication*#}
{#fun pure qlDigitalReplicationType as digitalReplicationType{withDigitalReplication*`DigitalReplication'}->`ReplicationType'#}
{#fun pure qlDigitalReplicationGap as digitalReplicationGap{withDigitalReplication*`DigitalReplication'}->`Double'#}

-- |CMS-rate coupon with embedded digital call and put options.
--
-- QuantLib evaluates the digital options by call/put-spread replication.  A supplied digital
-- payoff produces a cash-or-nothing option; without one the option is asset-or-nothing.  When
-- /nakedOption/ is true, the underlying coupon rate is excluded from the payoff.  Optional
-- strikes and payoffs use 'Nothing' for QuantLib's null-rate sentinel.
{#fun qlDigitalCmsCoupon as digitalCmsCoupon{withCmsCoupon*`CmsCoupon',fromMaybeDouble`Maybe Double',fromEnumC`PositionType',`Bool',fromMaybeDouble`Maybe Double'
  ,fromMaybeDouble`Maybe Double',fromEnumC`PositionType',`Bool',fromMaybeDouble`Maybe Double',withMaybeDigitalReplication*`Maybe DigitalReplication',`Bool'
  ,preErrorCheck-`String'errorCheck*-}->`DigitalCmsCoupon'peekDigitalCmsCoupon*#}

-- |Call-option rate.  Multiply by @nominal * accrualPeriod * discount@ to obtain the option NPV.
{#fun qlDigitalCmsCouponCallOptionRate as digitalCmsCouponCallOptionRate{withDigitalCmsCoupon*`DigitalCmsCoupon',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Put-option rate.  Multiply by @nominal * accrualPeriod * discount@ to obtain the option NPV.
{#fun qlDigitalCmsCouponPutOptionRate as digitalCmsCouponPutOptionRate{withDigitalCmsCoupon*`DigitalCmsCoupon',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Build a sequence of digital CMS-rate coupons.  The options record covers all digital call/put
-- and replication choices.
digitalCmsLeg :: Schedule -> GenSwapIndex sidx -> NonEmpty Double -> DayCounter -> BusinessDayConvention -> [Word] -> [Double] -> [Double] -> Bool -> DigitalCmsLegOpts -> IO Leg
digitalCmsLeg schedule index notionals dc adjustment fixingDays gearings spreads inArrears opts =
  digitalCmsLeg_ schedule index notionals dc adjustment fixingDays gearings spreads inArrears
    (dcmlCallStrikes opts) (dcmlCallPosition opts) (dcmlCallATM opts) (dcmlCallPayoffs opts)
    (dcmlPutStrikes opts) (dcmlPutPosition opts) (dcmlPutATM opts) (dcmlPutPayoffs opts)
    (dcmlReplication opts) (dcmlNakedOption opts)

{#fun qlDigitalCmsLeg as digitalCmsLeg_{withSchedule*`Schedule',withSwapIndex*`GenSwapIndex sidx',withNonEmptyDoubleArray*`NonEmpty Double'&,withDayCounter*`DayCounter',fromEnumC`BusinessDayConvention'
  ,withIntArray*`[Word]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,`Bool'
  ,withDoubleArray*`[Double]'&,fromEnumC`PositionType',`Bool',withDoubleArray*`[Double]'&
  ,withDoubleArray*`[Double]'&,fromEnumC`PositionType',`Bool',withDoubleArray*`[Double]'&
  ,withMaybeDigitalReplication*`Maybe DigitalReplication',`Bool',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |CMS-coupon pricer via static replication (Hagan's "Conundrums..."), using an analytic
-- closed-form approximation of the replication integrals.
{#fun qlAnalyticHaganPricer as analyticHaganPricer{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',`YieldCurveModel',withQuote*`GenQuote q' -- ^meanReversion
  ,preErrorCheck-`String'errorCheck*-}->`CmsCouponPricer'peekCmsCouponPricer*#}

-- |CMS-coupon pricer via static replication (Hagan's "Conundrums..."), evaluating the
-- replication integrals by numerical integration over vanilla swaption prices.
{#fun qlNumericHaganPricer as numericHaganPricer{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',`YieldCurveModel',withQuote*`GenQuote q' -- ^meanReversion
  ,`Double' -- ^lowerLimit
  ,`Double' -- ^upperLimit
  ,`Double' -- ^precision
  ,`Double' -- ^hardUpperLimit
  ,preErrorCheck-`String'errorCheck*-}->`CmsCouponPricer'peekCmsCouponPricer*#}

-- |The strategy 'LinearTsrPricer' uses to pick the integration cut-off strike bounds; each
-- carries the strategy-specific parameter upstream's corresponding @Settings::withX@ takes
-- ('LinearTsrRateBound' has none). Pass explicit bounds via 'LinearTsrPricerSettings''
-- /ltsrBounds/ rather than baking upstream's own default bounds in here, since upstream's
-- no-explicit-bounds overloads aren't just sugar for those same numbers -- they also flip
-- @Settings::defaultBounds_@, which under a normal-vol swaption surface adjusts the lower
-- bound to @min(-upperBound, lowerBound)@ (see @ql/cashflows/lineartsrpricer.cpp@). Passing
-- 'Nothing' reaches that adjustment; passing explicit bounds via 'Just' does not.
data LinearTsrPricerStrategy
  = LinearTsrRateBound
  | LinearTsrVegaRatio Double        -- ^vegaRatio
  | LinearTsrPriceThreshold Double   -- ^priceThreshold
  | LinearTsrBSStdDevs Double        -- ^stdDevs
  deriving (Show, Eq)

-- |'ltsrBounds' of 'Nothing' uses upstream's own default lower\/upper rate bounds (and, for a
-- normal-vol surface, its default-bounds strike adjustment -- see 'LinearTsrPricerStrategy');
-- @'Just' (lower, upper)@ pins explicit bounds instead.
data LinearTsrPricerSettings = LinearTsrPricerSettings
  { ltsrStrategy :: LinearTsrPricerStrategy
  , ltsrBounds :: Maybe (Double, Double)
  } deriving (Show, Eq)

-- |CMS-coupon pricer using a linear terminal swap rate model (Andersen\/Piterbarg 16.3.2).
-- /couponDiscountCurve/ of 'Nothing' uses the coupon's own discount curve, matching upstream's
-- default empty 'Handle'. The upstream constructor's trailing /integrator/ parameter (an
-- advanced numerical-integration override) is not exposed; upstream's own default
-- (@ext::shared_ptr\<Integrator\>()@) is always used.
linearTsrPricer :: GenSwaptionVolatilityStructure sv -> GenQuote q -> Maybe (GenYieldTermStructure y)
  -> LinearTsrPricerSettings -> IO CmsCouponPricer
linearTsrPricer swaptionVol meanReversion couponDiscountCurve (LinearTsrPricerSettings strat bounds) =
  linearTsrPricer_ swaptionVol meanReversion couponDiscountCurve strategyTag param
    (maybe False (const True) bounds) lowerBound upperBound
  where
    (strategyTag, param) = case strat of
      LinearTsrRateBound        -> (fromEnum LinearTsrPricerRateBound, 0)
      LinearTsrVegaRatio p      -> (fromEnum LinearTsrPricerVegaRatio, p)
      LinearTsrPriceThreshold p -> (fromEnum LinearTsrPricerPriceThreshold, p)
      LinearTsrBSStdDevs p      -> (fromEnum LinearTsrPricerBSStdDevs, p)
    (lowerBound, upperBound) = fromMaybe (0, 0) bounds

{#enum LinearTsrPricerStrategyType as LinearTsrPricerStrategyTag {} deriving (Show, Eq, Read)#}

-- |Raw binding for 'linearTsrPricer', taking the 'LinearTsrPricerSettings' unpacked into a
-- strategy tag\/parameter and an explicit-bounds flag.
{#fun qlLinearTsrPricer as linearTsrPricer_{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',withQuote*`GenQuote q' -- ^meanReversion
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^couponDiscountCurve
  ,fromIntegral`Int' -- ^strategy tag, see 'LinearTsrPricerStrategyTag'
  ,`Double' -- ^strategy-specific parameter (unused for RateBound)
  ,`Bool' -- ^haveBounds
  ,`Double' -- ^lowerBound (ignored unless haveBounds)
  ,`Double' -- ^upperBound (ignored unless haveBounds)
  ,preErrorCheck-`String'errorCheck*-}->`CmsCouponPricer'peekCmsCouponPricer*#}

-- |CMS-spread pricer using the Brigo--Mercurio bivariate model, with extensions for shifted
-- lognormal and normal dynamics.  /volatilityType/ of 'Nothing' inherits the type and shifts
-- from the component swaption volatility structures; in that case both shifts must be 'Nothing'.
lognormalCmsSpreadPricer :: CmsCouponPricer -> GenQuote q -> Maybe (GenYieldTermStructure y) -> Word
  -> Maybe VolatilityType -> Maybe Double -> Maybe Double -> IO FloatingRateCouponPricer
lognormalCmsSpreadPricer cmsPricer correlation discountCurve integrationPoints volatilityType shift1 shift2 =
  lognormalCmsSpreadPricer_ cmsPricer correlation discountCurve integrationPoints
    (maybe False (const True) volatilityType) (maybe 0 fromEnum volatilityType) shift1 shift2

{#fun qlLognormalCmsSpreadPricer as lognormalCmsSpreadPricer_{withCmsCouponPricer*`CmsCouponPricer',withQuote*`GenQuote q',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)'
  ,fromIntegral`Word',`Bool',`Int',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double'
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
