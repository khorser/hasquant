{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.CashFlow.Leg
  (
    leg

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
  , bps'
  , bps''
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
  , npv'
  , npv''
  , npv'''
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
  )
where

import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Utils(fromBool, toBool)
import Foreign.Storable(peek)


import QuantLib.CashFlow.DurationType
import QuantLib.Compounding
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Time.Frequency
import QuantLib.Types

foreign import ccall safe "ql.h qlLeg"
  c_leg :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
  c_legStartDate :: Ptr CLeg -> Ptr CString -> IO CDate

-- | QuantLibXL: qlLeg
leg :: [(Double, Day)] -- ^amounts and dates
  -> IO Leg
leg = $(ffiCall 'leg) c_leg

-- |Returns the start (i.e. first accrual) date for the given Leg. QuantLibXL: qlLegStartDate
startDate :: Leg -> Either String Day
startDate = $(ffiCallPureX 'startDate) c_legStartDate

foreign import ccall safe "ql.h qlNextCashFlows"
  c_nextCashFlows :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO (Ptr CLeg)

-- |return cashflows that will occur after /settlementDate/
nextCashFlows :: Leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> IO Leg
nextCashFlows = $(ffiCall 'nextCashFlows) c_nextCashFlows

foreign import ccall safe "ql.h qlPreviousCashFlows"
  c_previousCashFlows :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO (Ptr CLeg)

-- |return cashflows that occurred before /settlementDate/
previousCashFlows :: Leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> IO Leg
previousCashFlows = $(ffiCall 'previousCashFlows) c_previousCashFlows

foreign import ccall safe "ql.h qlLegCashFlows"
  c_legCashFlows :: Ptr CLeg -> CInt -> CDate -> Ptr (Ptr CDouble)
    -> Ptr (Ptr CDate) -> Ptr (Ptr CInt) -> Ptr CString -> IO CUInt

-- |return cash flows together with an indicator whether they occurred as of /settlementDate/
cashFlows :: Leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String [(Double, Day, Bool)] -- ^amount, date, hasOccurred
cashFlows l inc d = purifyExceptions $
  withObject l $
  \ll -> alloca $
    \pam -> alloca $
      \pdt -> alloca $
        \pocc -> do
          num <- unmarshalExceptions $ c_legCashFlows ll (fromBool inc) (toQlDate d) pam pdt pocc
          am <- peek pam >>= buildArray num
          dt <- peek pdt >>= buildArray num
          occ <- peek pocc >>= buildArray num
          return $ zip3 (map realToFrac am) (map fromQlDate dt) (map toBool occ)

-- |Cash-flow duration.
-- The simple duration of a string of cash flows is defined as \[ D_{\mathrm{simple}} = \frac{\sum t_i c_i B(t_i)}{\sum c_i B(t_i)} \] where $ c_i $ is the amount of the $ i $-th cash flow, $ t_i $ is its payment time, and $ B(t_i) $ is the corresponding discount according to the passed yield.The modified duration is defined as \[ D_{\mathrm{modified}} = -\frac{1}{P} \frac{\partial P}{\partial y} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.The Macaulay duration is defined for a compounded IRR as \[ D_{\mathrm{Macaulay}} = \left( 1 + \frac{y}{N} \right) D_{\mathrm{modified}} \] where $ y $ is the IRR and $ N $ is the number of cash flows per year.
duration :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> DurationType -- ^type
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String YearFraction
duration = $(ffiCallPureX 'duration) c_duration

foreign import ccall safe "ql.h qlCashFlowsDuration"
  c_duration :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CYearFraction

accrualDays :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Int
accrualDays = $(ffiCallPureX 'accrualDays) c_accrualDays

foreign import ccall safe "ql.h qlCashFlowsAccrualDays"
  c_accrualDays :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CInt

accrualEndDate :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String (Maybe Day)
accrualEndDate = $(ffiCallPureX 'accrualEndDate) c_accrualEndDate

foreign import ccall safe "ql.h qlCashFlowsAccrualEndDate"
  c_accrualEndDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

accrualPeriod :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String YearFraction
accrualPeriod = $(ffiCallPureX 'accrualPeriod) c_accrualPeriod

foreign import ccall safe "ql.h qlCashFlowsAccrualPeriod"
  c_accrualPeriod :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CYearFraction

accrualStartDate :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlDate
  -> Either String (Maybe Day)
accrualStartDate = $(ffiCallPureX 'accrualStartDate) c_accrualStartDate

foreign import ccall safe "ql.h qlCashFlowsAccrualStartDate"
  c_accrualStartDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

accruedAmount :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Double
accruedAmount = $(ffiCallPureX 'accruedAmount) c_accruedAmount

foreign import ccall safe "ql.h qlCashFlowsAccruedAmount"
  c_accruedAmount :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

accruedDays :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Int
accruedDays = $(ffiCallPureX 'accruedDays) c_accruedDays

foreign import ccall safe "ql.h qlCashFlowsAccruedDays"
  c_accruedDays :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CInt

accruedPeriod :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String YearFraction
accruedPeriod = $(ffiCallPureX 'accruedPeriod) c_accruedPeriod

foreign import ccall safe "ql.h qlCashFlowsAccruedPeriod"
  c_accruedPeriod :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CYearFraction

-- |At-the-money rate of the cash flows.
-- The result is the fixed rate for which a fixed rate cash flow vector, equivalent to the input vector, has the required NPV according to the given term structure. If the required NPV is not given, the input cash flow vector's NPV is used instead.
atmRate :: Leg -- ^leg
  -> YieldTermStructure -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Double -- ^npv
  -> Either String Double
atmRate = $(ffiCallPureX 'atmRate) c_atmRate

foreign import ccall safe "ql.h qlCashFlowsAtmRate"
  c_atmRate :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> CDouble -> Ptr CString -> IO CDouble

basisPointValue' :: Leg -- ^leg
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
basisPointValue' = $(ffiCallPureX 'basisPointValue') c_basisPointValue'

foreign import ccall safe "ql.h qlCashFlowsBasisPointValue1"
  c_basisPointValue' :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Basis-point value.
-- Obtained by setting dy = 0.0001 in the 2nd-order Taylor series expansion.
basisPointValue :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
basisPointValue = $(ffiCallPureX 'basisPointValue) c_basisPointValue

foreign import ccall safe "ql.h qlCashFlowsBasisPointValue"
  c_basisPointValue :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
bps' :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
bps' = $(ffiCallPureX 'bps') c_bps'

foreign import ccall safe "ql.h qlCashFlowsBps1"
  c_bps' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

bps'' :: Leg -- ^leg
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
bps'' = $(ffiCallPureX 'bps'') c_bps''

foreign import ccall safe "ql.h qlCashFlowsBps2"
  c_bps'' :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given term structure.
bps :: Leg -- ^leg
  -> YieldTermStructure -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> IO Double
bps = $(ffiCallX 'bps) c_bps

foreign import ccall safe "ql.h qlCashFlowsBps"
  c_bps :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

convexity' :: Leg -- ^leg
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
convexity' = $(ffiCallPureX 'convexity') c_convexity'

foreign import ccall safe "ql.h qlCashFlowsConvexity1"
  c_convexity' :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Cash-flow convexity.
-- The convexity of a string of cash flows is defined as \[ C = \frac{1}{P} \frac{\partial^2 P}{\partial y^2} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.
convexity :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
convexity = $(ffiCallPureX 'convexity) c_convexity

foreign import ccall safe "ql.h qlCashFlowsConvexity"
  c_convexity :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

duration' :: Leg -- ^leg
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> DurationType -- ^type
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String YearFraction
duration' = $(ffiCallPureX 'duration') c_duration'

foreign import ccall safe "ql.h qlCashFlowsDuration1"
  c_duration' :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CYearFraction

isExpired :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Bool
isExpired = $(ffiCallPureX 'isExpired) c_isExpired

foreign import ccall safe "ql.h qlCashFlowsIsExpired"
  c_isExpired :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CInt

maturityDate :: Leg -- ^leg
  -> Either String Day
maturityDate = $(ffiCallPureX 'maturityDate) c_maturityDate

foreign import ccall safe "ql.h qlCashFlowsMaturityDate"
  c_maturityDate :: Ptr CLeg -> Ptr CString -> IO CDate

nextCashFlowAmount :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Double
nextCashFlowAmount = $(ffiCallPureX 'nextCashFlowAmount) c_nextCashFlowAmount

foreign import ccall safe "ql.h qlCashFlowsNextCashFlowAmount"
  c_nextCashFlowAmount :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

nextCashFlowDate :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String (Maybe Day)
nextCashFlowDate = $(ffiCallPureX 'nextCashFlowDate) c_nextCashFlowDate

foreign import ccall safe "ql.h qlCashFlowsNextCashFlowDate"
  c_nextCashFlowDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

nextCouponRate :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Double
nextCouponRate = $(ffiCallPureX 'nextCouponRate) c_nextCouponRate

foreign import ccall safe "ql.h qlCashFlowsNextCouponRate"
  c_nextCouponRate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

nominal :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlDate
  -> Either String Double
nominal = $(ffiCallPureX 'nominal) c_nominal

foreign import ccall safe "ql.h qlCashFlowsNominal"
  c_nominal :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

-- |NPV of the cash flows.
-- The IRR is the interest rate at which the NPV of the cash flows equals the dirty price.The NPV is the sum of the cash flows, each discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
npv' :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
npv' = $(ffiCallPureX 'npv') c_npv'

foreign import ccall safe "ql.h qlCashFlowsNpv1"
  c_npv' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

npv'' :: Leg -- ^leg
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
npv'' = $(ffiCallPureX 'npv'') c_npv''

foreign import ccall safe "ql.h qlCashFlowsNpv2"
  c_npv'' :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |NPV of the cash flows.
-- For details on z-spread refer to: "Credit Spreads Explained", Lehman Brothers European Fixed Income Research - March 2004, D. O'KaneThe NPV is the sum of the cash flows, each discounted according to the z-spreaded term structure. The result is affected by the choice of the z-spread compounding and the relative frequency and day counter.
npv''' :: Leg -- ^leg
  -> YieldTermStructure -- ^discount
  -> Double -- ^zSpread
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> IO Double
npv''' = $(ffiCallX 'npv''') c_npv'''

foreign import ccall safe "ql.h qlCashFlowsNpv3"
  c_npv''' :: Ptr CLeg -> Ptr CYieldTermStructure -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |NPV of the cash flows.
-- The NPV is the sum of the cash flows, each discounted according to the given term structure.
npv :: Leg -- ^leg
  -> YieldTermStructure -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> IO Double
npv = $(ffiCallX 'npv) c_npv

foreign import ccall safe "ql.h qlCashFlowsNpv"
  c_npv :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |NPV and BPS of the cash flows.
-- The NPV and BPS of the cash flows calculated together for performance reason
npvbps :: Leg -- ^leg
  -> YieldTermStructure -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> IO (Double, Double) -- ^(npv, bps)
npvbps l y i s n =
  withObject l $
  \ll -> withObject y $
    \yy -> alloca $
      \pnpv -> alloca $
        \pbps -> do
          unmarshalExceptions $ c_npvbps ll yy (fromBool i) (toQlDate s) (toQlDate n) pnpv pbps
          npv <- peek pnpv
          bps <- peek pbps
          return (realToFrac npv, realToFrac bps)

foreign import ccall safe "ql.h qlCashFlowsNpvbps"
  c_npvbps :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CDouble -> Ptr CDouble -> Ptr CString -> IO ()

previousCashFlowAmount :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Double
previousCashFlowAmount = $(ffiCallPureX 'previousCashFlowAmount) c_previousCashFlowAmount

foreign import ccall safe "ql.h qlCashFlowsPreviousCashFlowAmount"
  c_previousCashFlowAmount :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

previousCashFlowDate :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String (Maybe Day)
previousCashFlowDate = $(ffiCallPureX 'previousCashFlowDate) c_previousCashFlowDate

foreign import ccall safe "ql.h qlCashFlowsPreviousCashFlowDate"
  c_previousCashFlowDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

previousCouponRate :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Either String Double
previousCouponRate = $(ffiCallPureX 'previousCouponRate) c_previousCouponRate

foreign import ccall safe "ql.h qlCashFlowsPreviousCouponRate"
  c_previousCouponRate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

referencePeriodEnd :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlDate
  -> Either String (Maybe Day)
referencePeriodEnd = $(ffiCallPureX 'referencePeriodEnd) c_referencePeriodEnd

foreign import ccall safe "ql.h qlCashFlowsReferencePeriodEnd"
  c_referencePeriodEnd :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

referencePeriodStart :: Leg -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlDate
  -> Either String (Maybe Day)
referencePeriodStart = $(ffiCallPureX 'referencePeriodStart) c_referencePeriodStart

foreign import ccall safe "ql.h qlCashFlowsReferencePeriodStart"
  c_referencePeriodStart :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

-- |Implied internal rate of return.
-- The function verifies the theoretical existance of an IRR and numerically establishes the IRR to the desired precision.
yield :: Leg -- ^leg
  -> Double -- ^npv
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> Double -- ^guess
  -> Either String Double
yield = $(ffiCallPureX 'yield) c_yield

foreign import ccall safe "ql.h qlCashFlowsYield"
  c_yield :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> CDouble -> CUInt -> CDouble -> Ptr CString -> IO CDouble

yieldValueBasisPoint' :: Leg -- ^leg
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
yieldValueBasisPoint' = $(ffiCallPureX 'yieldValueBasisPoint') c_yieldValueBasisPoint'

foreign import ccall safe "ql.h qlCashFlowsYieldValueBasisPoint1"
  c_yieldValueBasisPoint' :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Yield value of a basis point.
-- The yield value of a one basis point change in price is the derivative of the yield with respect to the price multiplied by 0.01
yieldValueBasisPoint :: Leg -- ^leg
  -> InterestRate -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Either String Double
yieldValueBasisPoint = $(ffiCallPureX 'yieldValueBasisPoint) c_yieldValueBasisPoint

foreign import ccall safe "ql.h qlCashFlowsYieldValueBasisPoint"
  c_yieldValueBasisPoint :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |implied Z-spread.
zSpread :: Leg -- ^leg
  -> Double -- ^npv
  -> YieldTermStructure
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> Double -- ^guess
  -> IO Double
zSpread = $(ffiCallX 'zSpread) c_zSpread

foreign import ccall safe "ql.h qlCashFlowsZSpread"
  c_zSpread :: Ptr CLeg -> CDouble -> Ptr CYieldTermStructure -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> CDouble -> CUInt -> CDouble -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
