{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.CashFlow
  (
    Leg
  , CouponLeg
  , asLeg
  , Dividend
  , DurationType(..)
  , RateAveragingType(..)

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

  , asCouponLeg
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

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.InterestRate#}(InterestRate, Compounding)
import QuantLib.Internal.InterestRate
{#import QuantLib.Time.Schedule#}(DayCounter, Schedule, Frequency, TimeUnit)
import QuantLib.Internal.Schedule
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
import QuantLib.Internal.Calendar

{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Index.InterestRate#}(BMAIndex, OvernightIborIndex, IborIndex)
import QuantLib.Internal.Index
{#import QuantLib.TermStructure.Volatility#}(OptionletVolatilityStructure, SwaptionVolatilityStructure)
{#import QuantLib.Quote#}(Quote)
import QuantLib.Internal.Quote

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Leg foreign finalizer qlFreeLeg newtype#}
instance ForeignObject Leg where
  withObject = withLeg
  constructor = Leg
  finalizer = qlFreeLeg
  
{#pointer *CouponLeg foreign finalizer qlFreeCouponLeg newtype#}
instance ForeignObject CouponLeg where
  withObject = withCouponLeg
  constructor = CouponLeg
  finalizer = qlFreeCouponLeg
  
{#pointer *QlDividend as Dividend foreign finalizer qlFreeDividend newtype#}
instance ForeignObject Dividend where
  withObject = withDividend
  constructor = Dividend
  finalizer = qlFreeDividend
  
{#enum DurationType {} deriving(Show, Eq)#}

{#enum RateAveragingType {} add prefix="Averaging" deriving(Show, Eq)#}

{#fun qlLeg {withDoubleArray* `[Double]'&, withDayPtr* `[Day]', preErrorCheck- `String' errorCheck*-} -> `Leg'#}

leg :: [(Double, Day)] -- ^amounts and dates
  -> IO Leg
leg = (uncurry qlLeg) . unzip

-- |Returns the start (i.e. first accrual) date for the given Leg
{#fun qlLegStartDate as startDate {`Leg', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

-- |return cashflows that will occur after /settlementDate/
{#fun qlNextCashFlows as nextCashFlows {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Leg'#}

-- |return cashflows that occurred before /settlementDate/
{#fun qlPreviousCashFlows as previousCashFlows {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Leg'#}

{#fun qlLegCashFlows {`Leg', fromMaybeBool `Maybe Bool', withMaybeDay* `Maybe Day', preArray- `[Double]'& peekDoubleArray*, preArray- `[Day]'& peekDayArray*, preArray- `[Bool]'& peekBoolArray*, preErrorCheck- `String' errorCheck*-} -> `()'#}

-- |return cash flows together with an indicator whether they occurred as of /settlementDate/
cashFlows :: Leg
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> IO [(Double, Day, Bool)] -- ^amount, date, hasOccurred
cashFlows l i d = do {(as, ds, hs) <- qlLegCashFlows l i d; return $ zip3 as ds hs}

-- |Cash-flow duration.
-- The simple duration of a string of cash flows is defined as \[ D_{\mathrm{simple}} = \frac{\sum t_i c_i B(t_i)}{\sum c_i B(t_i)} \] where $ c_i $ is the amount of the $ i $-th cash flow, $ t_i $ is its payment time, and $ B(t_i) $ is the corresponding discount according to the passed yield.The modified duration is defined as \[ D_{\mathrm{modified}} = -\frac{1}{P} \frac{\partial P}{\partial y} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.The Macaulay duration is defined for a compounded IRR as \[ D_{\mathrm{Macaulay}} = \left( 1 + \frac{y}{N} \right) D_{\mathrm{modified}} \] where $ y $ is the IRR and $ N $ is the number of cash flows per year.
{#fun qlCashFlowsDuration as duration {`Leg', `InterestRate', `DurationType', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsAccrualDays as accrualDays {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlCashFlowsAccrualEndDate as accrualEndDate {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlCashFlowsAccrualPeriod as accrualPeriod {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsAccrualStartDate as accrualStartDate {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlCashFlowsAccruedAmount as accruedAmount {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsAccruedDays as accruedDays {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlCashFlowsAccruedPeriod as accruedPeriod {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsBasisPointValue1 as basisPointValue {`Leg', `Double' , `DayCounter' , `Compounding' , `Frequency' , `Bool' , withMaybeDay* `Maybe Day' , withMaybeDay* `Maybe Day' , preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Basis-point value.
-- Obtained by setting dy = 0.0001 in the 2nd-order Taylor series expansion.
{#fun qlCashFlowsBasisPointValue as basisPointValue' {`Leg' , `InterestRate' , `Bool' , withMaybeDay* `Maybe Day' , withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsBps1 as bpsFromYield' {`Leg' , `InterestRate' , `Bool' , withMaybeDay* `Maybe Day' , withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsBps2 as bpsFromYield {`Leg' , `Double' , `DayCounter' , `Compounding' , `Frequency' , `Bool' , withMaybeDay* `Maybe Day' , withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsConvexity1 as convexity {`Leg', `Double', `DayCounter', `Compounding', `Frequency', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Cash-flow convexity.
-- The convexity of a string of cash flows is defined as \[ C = \frac{1}{P} \frac{\partial^2 P}{\partial y^2} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.
{#fun qlCashFlowsConvexity as convexity' {`Leg', `InterestRate', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsDuration1 as duration' {`Leg', `Double', `DayCounter', `Compounding', `Frequency', `DurationType', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsIsExpired as isExpired {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Bool'#}

{#fun qlCashFlowsMaturityDate as maturityDate {`Leg', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlCashFlowsNextCashFlowAmount as nextCashFlowAmount {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsNextCashFlowDate as nextCashFlowDate {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `(Maybe Day)' toMaybeDay#}

{#fun qlCashFlowsNextCouponRate as nextCouponRate {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsNominal as nominal {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |NPV of the cash flows.
-- The IRR is the interest rate at which the NPV of the cash flows equals the dirty price.The NPV is the sum of the cash flows, each discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv1 as npvFromYield' {`Leg', `InterestRate', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsNpv2 as npvFromYield {`Leg', `Double', `DayCounter', `Compounding', `Frequency', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |At-the-money rate of the cash flows.
-- The result is the fixed rate for which a fixed rate cash flow vector, equivalent to the input vector, has the required NPV according to the given term structure. If the required NPV is not given, the input cash flow vector's NPV is used instead.
{#fun qlCashFlowsAtmRate as atmRate {`Leg', `YieldTermStructure', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given term structure.
{#fun qlCashFlowsBps as bps {`Leg', `YieldTermStructure', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |NPV of the cash flows.
-- For details on z-spread refer to: "Credit Spreads Explained", Lehman Brothers European Fixed Income Research - March 2004, D. O'KaneThe NPV is the sum of the cash flows, each discounted according to the z-spreaded term structure. The result is affected by the choice of the z-spread compounding and the relative frequency and day counter.
{#fun qlCashFlowsNpv3 as npv' {`Leg', `YieldTermStructure', `Double', `DayCounter', `Compounding', `Frequency', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |NPV of the cash flows.
-- The NPV is the sum of the cash flows, each discounted according to the given term structure.
{#fun qlCashFlowsNpv as npv {`Leg', `YieldTermStructure', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |NPV and BPS of the cash flows.
-- The NPV and BPS of the cash flows calculated together for performance reason
{#fun qlCashFlowsNpvbps as npvbps {`Leg', `YieldTermStructure', `Bool', withDay* `Day', withDay* `Day', prePtr- `Double' peekDouble*, prePtr- `Double' peekDouble*, preErrorCheck- `String' errorCheck*-} -> `()'#}

-- |implied Z-spread.
{#fun qlCashFlowsZSpread as zSpread {`Leg', `Double', `YieldTermStructure', `DayCounter', `Compounding', `Frequency', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', `Double', fromIntegral `Word', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsPreviousCashFlowAmount as previousCashFlowAmount {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsPreviousCashFlowDate as previousCashFlowDate {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlCashFlowsPreviousCouponRate as previousCouponRate {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsReferencePeriodEnd as referencePeriodEnd {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

{#fun qlCashFlowsReferencePeriodStart as referencePeriodStart {`Leg', `Bool', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Maybe Day' toMaybeDay#}

-- |Implied internal rate of return.
-- The function verifies the theoretical existance of an IRR and numerically establishes the IRR to the desired precision.
{#fun qlCashFlowsYield as yield {`Leg', `Double', `DayCounter', `Compounding', `Frequency', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', `Double', fromIntegral `Word', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCashFlowsYieldValueBasisPoint1 as yieldValueBasisPoint {`Leg', `Double', `DayCounter', `Compounding', `Frequency', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Yield value of a basis point.
-- The yield value of a one basis point change in price is the derivative of the yield with respect to the price multiplied by 0.01
{#fun qlCashFlowsYieldValueBasisPoint as yieldValueBasisPoint' {`Leg', `InterestRate', `Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |start of the accrual periods for a coupon leg
{#fun qlCouponAccrualStartDates as couponAccrualStartDates {`CouponLeg', preArray- `[Day]'& peekDayArray*, preErrorCheck- `String' errorCheck*-} -> `()'#}

{#fun qlFixedDividend as fixedDividend {`Double', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Dividend'#}

{#fun qlFractionalDividend1 as fractionalDividend' {`Double', `Double', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Dividend'#}

{#fun qlFractionalDividend as fractionalDividend {`Double', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Dividend'#}

{#fun qlAverageBMALeg as averageBMALeg {`Schedule', `BMAIndex', withDoubleArray* `[Double]'&, `DayCounter', `BusinessDayConvention', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, preErrorCheck- `String' errorCheck*-} -> `Leg'#}

{#fun qlFixedRateLeg as fixedRateLeg {`Schedule', withDoubleArray* `[Double]'&, withObjectArray* `[InterestRate]'&, `BusinessDayConvention', `DayCounter', `Calendar', preErrorCheck- `String' errorCheck*-} -> `Leg'#}

{#fun qlIborLeg as iborLeg {`Schedule', `IborIndex', withDoubleArray* `[Double]'&, `DayCounter', `BusinessDayConvention', withIntArray* `[Word]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, `Bool', `Bool', preErrorCheck- `String' errorCheck*-} -> `Leg'#}

{#fun qlOvernightLeg as overnightLeg {`Schedule', `OvernightIborIndex', withDoubleArray* `[Double]'&, `DayCounter', `BusinessDayConvention', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, preErrorCheck- `String' errorCheck*-} -> `Leg'#}

{#fun qlRangeAccrualLeg as rangeAccrualLeg {`Schedule', `IborIndex', withDoubleArray* `[Double]'&, `DayCounter', `BusinessDayConvention', withIntArray* `[Word]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, fromEnumQuantity `(Int, TimeUnit)'&, `BusinessDayConvention', preErrorCheck- `String' errorCheck*-} -> `Leg'#}

-- |try to downcast leg to a coupon leg
-- don't blame me, it's how QuantLib works
{#fun qlLegToCouponLeg as asCouponLeg {`Leg', preErrorCheck- `String' errorCheck*-} -> `CouponLeg'#}

asLeg :: (a `Derives` Leg) => a -> IO Leg
asLeg = cast
instance CouponLeg `Derives` Leg where cast = qlCouponLegAsLeg
{#fun qlCouponLegAsLeg {`CouponLeg'} -> `Leg'#}

{#enum YieldCurveModel {} deriving(Show, Eq)#}

{#pointer *QlFloatingRateCouponPricer as FloatingRateCouponPricer foreign finalizer qlFreeFloatingCouponPricer newtype#}
instance ForeignObject FloatingRateCouponPricer where
  withObject = withFloatingRateCouponPricer
  constructor = FloatingRateCouponPricer
  finalizer = qlFreeFloatingCouponPricer
  
-- |Black-formula pricer for capped/floored Ibor coupons
{#fun qlBlackIborCouponPricer as blackIborCouponPricer {withObject* `OptionletVolatilityStructure', preErrorCheck- `String' errorCheck*-} -> `FloatingRateCouponPricer'#}

{#fun qlQuantLibSetCouponPricer as setCouponPricer {`Leg', `FloatingRateCouponPricer', preErrorCheck- `String' errorCheck*-} -> `()'#}

{#fun qlQuantLibSetCouponPricers as setCouponPricers {`Leg', withObjectArray* `[FloatingRateCouponPricer]'&, preErrorCheck- `String' errorCheck*-} -> `()'#}

{#fun qlAnalyticHaganPricer as analyticHaganPricer {withObject* `SwaptionVolatilityStructure', `YieldCurveModel', `Quote', preErrorCheck- `String' errorCheck*-} -> `FloatingRateCouponPricer'#}

{#fun qlNumericHaganPricer as numericHaganPricer {withObject* `SwaptionVolatilityStructure', `YieldCurveModel', `Quote', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `FloatingRateCouponPricer'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
