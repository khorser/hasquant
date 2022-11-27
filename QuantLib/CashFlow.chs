module QuantLib.CashFlow
  (
    Leg
  , CouponLeg
  , asLeg
  , Dividend
  , DurationType(..)
  , RateAveragingType(..)
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
  , overnightLeg
  , rangeAccrualLeg
  , YieldCurveModel(..)

  , FloatingRateCouponPricer
  , blackIborCouponPricer
  , setCouponPricer
  , setCouponPricers
  , analyticHaganPricer
  , numericHaganPricer
  )
  where

import QuantLib.Internal
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.Time.Schedule#}(Frequency, TimeUnit)
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type

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
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}

{#enum DurationType{} deriving(Show, Eq)#}

{#enum RateAveragingType{} add prefix="Averaging" deriving(Show, Eq)#}

{#fun qlLeg{withDoubleArray*`[Double]'&,withDayPtr*`[Day]',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

leg :: [(Day, Double)] -- ^amounts and dates
  -> IO Leg
leg f = qlLeg fs ds where (ds, fs) = unzip f

-- |Returns the start (i.e. first accrual) date for the given Leg
{#fun qlLegStartDate as startDate{withLeg*`GenLeg a',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
-- |return cashflows that will occur after /settlementDate/
{#fun qlNextCashFlows as nextCashFlows{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |return cashflows that occurred before /settlementDate/
{#fun qlPreviousCashFlows as previousCashFlows{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlLegCashFlows{withLeg*`GenLeg a',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
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
{#fun qlCashFlowsDuration as duration{withLeg*`GenLeg a',withInterestRate*`InterestRate' -- ^yield
  ,`DurationType',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsAccrualDays as accrualDays{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlCashFlowsAccrualEndDate as accrualEndDate{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlCashFlowsAccrualPeriod as accrualPeriod{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsAccrualStartDate as accrualStartDate{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlCashFlowsAccruedAmount as accruedAmount{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsAccruedDays as accruedDays{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Int'#}
{#fun qlCashFlowsAccruedPeriod as accruedPeriod{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsBasisPointValue1 as basisPointValue{withLeg*`GenLeg a',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Basis-point value.
-- Obtained by setting dy = 0.0001 in the 2nd-order Taylor series expansion.
{#fun qlCashFlowsBasisPointValue as basisPointValue'{withLeg*`GenLeg a',withInterestRate*`InterestRate'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsBps1 as bpsFromYield'{withLeg*`GenLeg a',withInterestRate*`InterestRate'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsBps2 as bpsFromYield{withLeg*`GenLeg a',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsConvexity1 as convexity{withLeg*`GenLeg a',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
    ,withMaybeDay*`Maybe Day' -- ^settlementDate
    ,withMaybeDay*`Maybe Day' -- ^npvDate
    ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Cash-flow convexity.
-- The convexity of a string of cash flows is defined as \[ C = \frac{1}{P} \frac{\partial^2 P}{\partial y^2} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.
{#fun qlCashFlowsConvexity as convexity'{withLeg*`GenLeg a',withInterestRate*`InterestRate'
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsDuration1 as duration'{withLeg*`GenLeg a',`Double'
  ,withDayCounter*`DayCounter'
  ,`Compounding',`Frequency',`DurationType',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsIsExpired as isExpired{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Bool'#}
{#fun qlCashFlowsMaturityDate as maturityDate{withLeg*`GenLeg a',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
{#fun qlCashFlowsNextCashFlowAmount as nextCashFlowAmount{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsNextCashFlowDate as nextCashFlowDate{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`(Maybe Day)' toMaybeDay#}
{#fun qlCashFlowsNextCouponRate as nextCouponRate{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsNominal as nominal{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |NPV of the cash flows.
-- The IRR is the interest rate at which the NPV of the cash flows equals the dirty price.The NPV is the sum of the cash flows, each discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv1 as npvFromYield'{withLeg*`GenLeg a',withInterestRate*`InterestRate',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsNpv2 as npvFromYield{withLeg*`GenLeg a',`Double'
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |At-the-money rate of the cash flows.
-- The result is the fixed rate for which a fixed rate cash flow vector, equivalent to the input vector, has the required NPV according to the given term structure. If the required NPV is not given, the input cash flow vector's NPV is used instead.
{#fun qlCashFlowsAtmRate as atmRate{withLeg*`GenLeg a',withYieldTermStructure*`GenYieldTermStructure b',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,`Double' -- ^npv
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given term structure.
{#fun qlCashFlowsBps as bps{withLeg*`GenLeg a',withYieldTermStructure*`GenYieldTermStructure b',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |NPV of the cash flows.
-- For details on z-spread refer to: "Credit Spreads Explained", Lehman Brothers European Fixed Income Research - March 2004, D. O'KaneThe NPV is the sum of the cash flows, each discounted according to the z-spreaded term structure. The result is affected by the choice of the z-spread compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv3 as npv'{withLeg*`GenLeg a',withYieldTermStructure*`GenYieldTermStructure b',`Double' -- ^zSpread
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |NPV of the cash flows.
-- The NPV is the sum of the cash flows, each discounted according to the given term structure.
{#fun qlCashFlowsNpv as npv{withLeg*`GenLeg a',withYieldTermStructure*`GenYieldTermStructure b',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |NPV and BPS of the cash flows.
-- The NPV and BPS of the cash flows calculated together for performance reason
{#fun qlCashFlowsNpvbps as npvbps{withLeg*`GenLeg a',withYieldTermStructure*`GenYieldTermStructure b',`Bool' -- ^includeSettlementDateFlows
  ,withDay*`Day' -- ^settlementDate
  ,withDay*`Day' -- ^npvDate
  ,prePtr-`Double'peekDouble*,prePtr-`Double'peekDouble*,preErrorCheck-`String'errorCheck*-}->`()'#}
-- |implied Z-spread.
{#fun qlCashFlowsZSpread as zSpread{withLeg*`GenLeg a',`Double' -- ^npv
  ,withYieldTermStructure*`GenYieldTermStructure b',withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsPreviousCashFlowAmount as previousCashFlowAmount{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsPreviousCashFlowDate as previousCashFlowDate{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day'toMaybeDay#}
{#fun qlCashFlowsPreviousCouponRate as previousCouponRate{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsReferencePeriodEnd as referencePeriodEnd{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
{#fun qlCashFlowsReferencePeriodStart as referencePeriodStart{withLeg*`GenLeg a',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,preErrorCheck-`String'errorCheck*-}->`Maybe Day' toMaybeDay#}
-- |Implied internal rate of return.
-- The function verifies the theoretical existance of an IRR and numerically establishes the IRR to the desired precision.
{#fun qlCashFlowsYield as yield{withLeg*`GenLeg a',`Double' -- ^npv
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,`Double' -- ^guess
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlCashFlowsYieldValueBasisPoint1 as yieldValueBasisPoint{withLeg*`GenLeg a',`Double' -- ^yield
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Yield value of a basis point.
-- The yield value of a one basis point change in price is the derivative of the yield with respect to the price multiplied by 0.01
{#fun qlCashFlowsYieldValueBasisPoint as yieldValueBasisPoint'{withLeg*`GenLeg a',withInterestRate*`InterestRate' -- ^yield
  ,`Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |start of the accrual periods for a coupon leg
{#fun qlCouponAccrualStartDates as couponAccrualStartDates{withLegDescendant*`CouponLeg',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
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
{#fun qlIborLeg as iborLeg{withSchedule*`Schedule',withIborIndex*`GenIborIndex a',withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter',`BusinessDayConvention' -- ^paymentAdjustment
  ,withIntArray*`[Word]'&  -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^caps
  ,withDoubleArray*`[Double]'& -- ^floors
  ,`Bool' -- ^inArrears
  ,`Bool' -- ^zeroPayments
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlOvernightLeg as overnightLeg{withSchedule*`Schedule',withOvernightIborIndex*`OvernightIborIndex',withDoubleArray*`[Double]'& -- ^notionals'
  ,withDayCounter*`DayCounter',`BusinessDayConvention',withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
{#fun qlRangeAccrualLeg as rangeAccrualLeg{withSchedule*`Schedule',withIborIndex*`GenIborIndex a',withDoubleArray*`[Double]'& -- ^notionals
  ,withDayCounter*`DayCounter',`BusinessDayConvention',withIntArray*`[Word]'& -- ^fixingDays
  ,withDoubleArray*`[Double]'& -- ^gearings
  ,withDoubleArray*`[Double]'& -- ^spreads
  ,withDoubleArray*`[Double]'& -- ^lowerTriggers
  ,withDoubleArray*`[Double]'& -- ^upperTriggers
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^observationTenor
  ,`BusinessDayConvention',preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}
-- |try to downcast leg to a coupon leg
-- don't blame me, it's how QuantLib works
{#fun qlLegToCouponLeg as toCouponLeg{withLeg*`GenLeg a',preErrorCheck-`String'errorCheck*-}->`CouponLeg'peekCouponLeg*#}

{#enum YieldCurveModel{} deriving(Show, Eq)#}

{#pointer *QlFloatingRateCouponPricer as FloatingRateCouponPricer foreign -> CFloatingRateCouponPricer nocode#}

-- |Black-formula pricer for capped/floored Ibor coupons
{#fun qlBlackIborCouponPricer as blackIborCouponPricer{withVolatilityTermStructureDescendant*`OptionletVolatilityStructure',preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlQuantLibSetCouponPricer as setCouponPricer{withLeg*`GenLeg a',withFloatingRateCouponPricer*`FloatingRateCouponPricer',preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlQuantLibSetCouponPricers as setCouponPricers{withLeg*`GenLeg a',withFloatingRateCouponPricerArray*`[FloatingRateCouponPricer]'&,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlAnalyticHaganPricer as analyticHaganPricer{withVolatilityTermStructureDescendant*`SwaptionVolatilityStructure',`YieldCurveModel',withQuote*`GenQuote a' -- ^meanReversion
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}
{#fun qlNumericHaganPricer as numericHaganPricer{withVolatilityTermStructureDescendant*`SwaptionVolatilityStructure',`YieldCurveModel',withQuote*`GenQuote a' -- ^meanReversion
  ,`Double' -- ^lowerLimit
  ,`Double' -- ^upperLimit
  ,`Double' -- ^precision
  ,preErrorCheck-`String'errorCheck*-}->`FloatingRateCouponPricer'peekFloatingRateCouponPricer*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
