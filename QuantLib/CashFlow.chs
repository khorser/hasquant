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
  , CPIInterpolationType(..)
  , GenLeg

  , leg
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
  , overnightLeg
  , rangeAccrualLeg
  , cpiLeg
  , yoyInflationLeg
  , ZeroInflationCashFlow
  , zeroInflationCashFlow
  , zeroInflationCashFlowAmount
  , zeroInflationCashFlowBaseFixing
  , zeroInflationCashFlowIndexFixing
  , CPICashFlow
  , cpiCashFlow
  , cpiCashFlowAmount
  , cpiCashFlowBaseFixing
  , cpiCashFlowIndexFixing
  , EquityCashFlow
  , equityCashFlow
  , equityCashFlowAmount
  , equityCashFlowBaseFixing
  , equityCashFlowIndexFixing
  , setEquityCashFlowPricer
  , YieldCurveModel(..)

  , FloatingRateCouponPricer
  , blackIborCouponPricer
  , rangeAccrualPricerByBgm
  , setCouponPricer
  , setCouponPricers
  , analyticHaganPricer
  , numericHaganPricer
  , LinearTsrPricerStrategy(..)
  , LinearTsrPricerSettings(..)
  , linearTsrPricer
  , EquityCashFlowPricer
  , equityQuantoCashFlowPricer
  , setEquityLegPricer
  ) where
import QuantLib.Internal
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.Time.Schedule#}(Frequency)
{#import QuantLib.Time.Calendar#}(BusinessDayConvention(..))
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import Data.Maybe(fromMaybe)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *CouponLeg foreign -> CCouponLeg' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *InterestRate foreign -> CInterestRate nocode#}
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
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}

{#enum DurationType{} deriving(Show, Eq)#}
{#enum RateAveragingType{} add prefix="Averaging" deriving(Show, Eq)#}
{#enum TimingAdjustment{} deriving(Show, Eq)#}

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

{#fun qlLeg{withDoubleArray*`[Double]'&,withDayPtr*`[Day]',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

leg :: [(Day, Double)] -- ^amounts and dates
  -> IO Leg
leg f = qlLeg fs ds where (ds, fs) = unzip f

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
{#fun qlCashFlowsAccrualDays as accrualDays{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlCashFlowsAccrualEndDate as accrualEndDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlCashFlowsAccrualPeriod as accrualPeriod{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsAccrualStartDate as accrualStartDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlCashFlowsAccruedAmount as accruedAmount{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsAccruedDays as accruedDays{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlCashFlowsAccruedPeriod as accruedPeriod{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
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
{#fun qlCashFlowsBps2 as bpsFromYield{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
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
{#fun qlCashFlowsDuration1 as duration'{withLeg*`GenLeg l',`Double'
  ,withDayCounter*`DayCounter'
  ,`Compounding',`Frequency',`DurationType',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsIsExpired as isExpired{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlCashFlowsMaturityDate as maturityDate{withLeg*`GenLeg l',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlCashFlowsNextCashFlowAmount as nextCashFlowAmount{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsNextCashFlowDate as nextCashFlowDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}
{#fun qlCashFlowsNextCouponRate as nextCouponRate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsNominal as nominal{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |NPV of the cash flows.
-- The IRR is the interest rate at which the NPV of the cash flows equals the dirty price.The NPV is the sum of the cash flows, each discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv1 as npvFromYield'{withLeg*`GenLeg l',withInterestRate*`InterestRate',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
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
{#fun qlCashFlowsPreviousCashFlowAmount as previousCashFlowAmount{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsPreviousCashFlowDate as previousCashFlowDate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day'toMaybeDay#}
{#fun qlCashFlowsPreviousCouponRate as previousCouponRate{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsReferencePeriodEnd as referencePeriodEnd{withLeg*`GenLeg l',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
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
{#fun qlFixedDividend as fixedDividend{`Double' -- ^amount
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Dividend'peekDividend*#}
{#fun qlFractionalDividend1 as fractionalDividend'{`Double' -- ^rate
  ,`Double' -- ^nominal
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Dividend'peekDividend*#}
{#fun qlFractionalDividend as fractionalDividend{`Double' -- ^rate
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Dividend'peekDividend*#}
{#fun qlAverageBMALeg as averageBMALeg{withSchedule*`Schedule',withBMAIndex*`BMAIndex'
  ,withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter',`BusinessDayConvention',withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlFixedRateLeg as fixedRateLeg{withSchedule*`Schedule',withDoubleArray*`[Double]'& -- ^notionals
  ,withInterestRateArray*`[InterestRate]'& -- ^couponRates
  ,`BusinessDayConvention' -- ^paymentAdjustment
  ,withDayCounter*`DayCounter' -- ^firstPeriodDayCounter
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |iborLeg keeps its original 12-arg signature -- existing callers are unaffected -- but
-- now delegates to iborLeg_, the raw binding widened to IborLeg's full builder surface,
-- hardcoding upstream's own defaults for the params iborLeg doesn't expose. Use
-- 'iborLegFull' to reach those (payment lag\/calendar, ex-coupon period, fixing
-- convention, indexed\/at-par coupons) via 'IborLegOpts'.
iborLeg :: Schedule -> GenIborIndex ibor -> [Double] -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> IO Leg
iborLeg schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp = do
  cal <- calendar Null
  iborLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (ilgPaymentLag defaultIborLegOpts) cal (ilgExCouponPeriod defaultIborLegOpts) cal
    (ilgExCouponConvention defaultIborLegOpts) (ilgExCouponEndOfMonth defaultIborLegOpts)
    (ilgFixingConvention defaultIborLegOpts) (ilgUseIndexedCoupons defaultIborLegOpts)

-- |'iborLeg' widened to every 'IborLeg' builder-method param via 'IborLegOpts'.
iborLegFull :: Schedule -> GenIborIndex ibor -> [Double] -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> IborLegOpts
  -> IO Leg
iborLegFull schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp opts = do
  cal <- calendar Null
  iborLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (ilgPaymentLag opts) (fromMaybe cal (ilgPaymentCalendar opts)) (ilgExCouponPeriod opts)
    (fromMaybe cal (ilgExCouponCalendar opts)) (ilgExCouponConvention opts)
    (ilgExCouponEndOfMonth opts) (ilgFixingConvention opts) (ilgUseIndexedCoupons opts)

{#fun qlIborLeg as iborLeg_{withSchedule*`Schedule',withIborIndex*`GenIborIndex ibor',withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter',`BusinessDayConvention' -- ^paymentAdjustment
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
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,`BusinessDayConvention' -- ^fixingConvention
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupons
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |CMS leg builder (analog of 'iborLeg'), 12-arg core shape -- same defaults-hardcoding
-- pattern as 'iborLeg' for the params not in this signature. Use 'cmsLegFull' to reach
-- them ('CmsLegOpts').
cmsLeg :: Schedule -> GenSwapIndex sidx -> [Double] -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> IO Leg
cmsLeg schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp = do
  cal <- calendar Null
  cmsLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (cmslExCouponPeriod defaultCmsLegOpts) cal (cmslExCouponConvention defaultCmsLegOpts)
    (cmslExCouponEndOfMonth defaultCmsLegOpts) (cmslFixingConvention defaultCmsLegOpts)

-- |'cmsLeg' widened to every 'CmsLeg' builder-method param via 'CmsLegOpts'.
cmsLegFull :: Schedule -> GenSwapIndex sidx -> [Double] -> DayCounter -> BusinessDayConvention
  -> [Word] -> [Double] -> [Double] -> [Double] -> [Double] -> Bool -> Bool -> CmsLegOpts
  -> IO Leg
cmsLegFull schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp opts = do
  cal <- calendar Null
  cmsLeg_ schedule idx notionals dc adj fixingDays gearings spreads caps floors inArrears zp
    (cmslExCouponPeriod opts) (fromMaybe cal (cmslExCouponCalendar opts))
    (cmslExCouponConvention opts) (cmslExCouponEndOfMonth opts) (cmslFixingConvention opts)

{#fun qlCmsLeg as cmsLeg_{withSchedule*`Schedule',withSwapIndex*`GenSwapIndex sidx',withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter',`BusinessDayConvention' -- ^paymentAdjustment
  ,withIntArray*`[Word]'&  -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,`Bool' -- ^zeroPayments
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^exCouponPeriod
  ,withCalendar*`Calendar' -- ^exCouponCalendar
  ,`BusinessDayConvention' -- ^exCouponConvention
  ,`Bool' -- ^exCouponEndOfMonth
  ,`BusinessDayConvention' -- ^fixingConvention
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlOvernightLeg as overnightLeg{withSchedule*`Schedule',withOvernightIborIndex*`OvernightIborIndex',withDoubleArray*`[Double]'& -- ^notionals'
  ,withDayCounter*`DayCounter',`BusinessDayConvention',withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlRangeAccrualLeg as rangeAccrualLeg{withSchedule*`Schedule',withIborIndex*`GenIborIndex ibor',withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter',`BusinessDayConvention',withIntArray*`[Word]'& -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^lowerTriggers
  ,withDoubleArray*`[Double]'& -- ^upperTriggers
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^observationTenor
  ,`BusinessDayConvention',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |Fixed-rate coupons scaled by the ratio of a 'ZeroInflationIndex' fixing to /baseCPI/
-- (a 'CPICoupon' leg -- caps/floors are not exposed, see README.md's TODO).
{#fun qlCPILeg as cpiLeg{withSchedule*`Schedule',withZeroInflationIndex*`ZeroInflationIndex'
  ,`Double' -- ^baseCPI
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,withDoubleArray*`[Double]'& -- ^notionals
  ,withDoubleArray*`[Double]'& -- ^fixedRates
  ,withDayCounter*`DayCounter' -- ^paymentDayCounter
  ,`BusinessDayConvention' -- ^paymentAdjustment
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,fromEnumC`CPIInterpolationType' -- ^observationInterpolation
  ,`Bool' -- ^subtractInflationNominal
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |Year-on-year inflation-linked coupons (a 'YoYInflationCoupon' leg -- caps/floors are not
-- exposed, see README.md's TODO).
{#fun qlYoYInflationLeg as yoyInflationLeg{withSchedule*`Schedule',withCalendar*`Calendar'
  ,withYoYInflationIndex*`YoYInflationIndex'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^observationLag
  ,fromEnumC`CPIInterpolationType' -- ^interpolation
  ,withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter' -- ^paymentDayCounter
  ,`BusinessDayConvention' -- ^paymentAdjustment
  ,withIntArray*`[Word]'& -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
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

{#enum YieldCurveModel{} deriving(Show, Eq)#}

{#pointer *QlFloatingRateCouponPricer as FloatingRateCouponPricer foreign -> CFloatingRateCouponPricer nocode#}
{#pointer *QlSmileSection as SmileSection foreign -> CSmileSection nocode#}

-- |Black-formula pricer for capped/floored Ibor coupons
{#fun qlBlackIborCouponPricer as blackIborCouponPricer{withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov'
  ,`TimingAdjustment'
  ,withMaybeQuote*`Maybe (GenQuote q)' -- ^correlation
  ,fromMaybeBool`Maybe Bool' -- ^useIndexedCoupon
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
-- |BGM-based pricer for 'RangeAccrualFloatersCoupon's (a 'rangeAccrualLeg')
{#fun qlRangeAccrualPricerByBgm as rangeAccrualPricerByBgm{`Double' -- ^correlation
  ,withSmileSection*`SmileSection' -- ^smilesOnExpiry
  ,withSmileSection*`SmileSection' -- ^smilesOnPayment
  ,`Bool' -- ^withSmile
  ,`Bool' -- ^byCallSpread
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlQuantLibSetCouponPricer as setCouponPricer{withLeg*`GenLeg l',withFloatingRateCouponPricer*`FloatingRateCouponPricer',preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlQuantLibSetCouponPricers as setCouponPricers{withLeg*`GenLeg l',withFloatingRateCouponPricerArray*`[FloatingRateCouponPricer]'&,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlAnalyticHaganPricer as analyticHaganPricer{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',`YieldCurveModel',withQuote*`GenQuote q' -- ^meanReversion
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlNumericHaganPricer as numericHaganPricer{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',`YieldCurveModel',withQuote*`GenQuote q' -- ^meanReversion
  ,`Double' -- ^lowerLimit
  ,`Double' -- ^upperLimit
  ,`Double' -- ^precision
  ,`Double' -- ^hardUpperLimit
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

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
  -> LinearTsrPricerSettings -> IO FloatingRateCouponPricer
linearTsrPricer swaptionVol meanReversion couponDiscountCurve (LinearTsrPricerSettings strat bounds) =
  linearTsrPricer_ swaptionVol meanReversion couponDiscountCurve strategyTag param
    (maybe False (const True) bounds) lowerBound upperBound
  where
    (strategyTag, param) = case strat of
      LinearTsrRateBound        -> (0 :: Int, 0)
      LinearTsrVegaRatio p      -> (1, p)
      LinearTsrPriceThreshold p -> (2, p)
      LinearTsrBSStdDevs p      -> (3, p)
    (lowerBound, upperBound) = fromMaybe (0, 0) bounds

{#fun qlLinearTsrPricer as linearTsrPricer_{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',withQuote*`GenQuote q' -- ^meanReversion
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^couponDiscountCurve
  ,fromIntegral`Int' -- ^strategy tag: 0=RateBound, 1=VegaRatio, 2=PriceThreshold, 3=BSStdDevs
  ,`Double' -- ^strategy-specific parameter (unused for RateBound)
  ,`Bool' -- ^haveBounds
  ,`Double' -- ^lowerBound (ignored unless haveBounds)
  ,`Double' -- ^upperBound (ignored unless haveBounds)
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
