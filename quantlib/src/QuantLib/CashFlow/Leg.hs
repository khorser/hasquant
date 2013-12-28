{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-cse -fno-full-laziness #-} -- for unsafePerformIO
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
  , npv'
  , npvFromYield
  , npvFromYield'
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
  )
where

import Control.Applicative((<$>))
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Utils(fromBool, toBool)
import Foreign.Storable(peek)


import QuantLib.CashFlow.DurationType(DurationType)
import QuantLib.Compounding(Compounding)
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Unit(Unit)
import QuantLib.Types

foreign import ccall safe "ql.h qlLeg"
  c_leg :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
  c_startDate :: Ptr CLeg -> Ptr CString -> IO CDate

leg :: [(Double, Day)] -- ^amounts and dates
  -> QLE s (Leg s)
leg = $(ffiCall 'leg) c_leg

-- |Returns the start (i.e. first accrual) date for the given Leg
startDate :: Leg s -> Either QLError Day
{-# NOINLINE startDate #-}
startDate = $(ffiCallPureX 'startDate) c_startDate

foreign import ccall safe "ql.h qlNextCashFlows"
  c_nextCashFlows :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO (Ptr CLeg)

-- |return cashflows that will occur after /settlementDate/
nextCashFlows :: Leg s
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s (Leg s)
nextCashFlows = $(ffiCall 'nextCashFlows) c_nextCashFlows

foreign import ccall safe "ql.h qlPreviousCashFlows"
  c_previousCashFlows :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO (Ptr CLeg)

-- |return cashflows that occurred before /settlementDate/
previousCashFlows :: Leg s
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s (Leg s)
previousCashFlows = $(ffiCall 'previousCashFlows) c_previousCashFlows

foreign import ccall safe "ql.h qlLegCashFlows"
  c_legCashFlows :: Ptr CLeg -> CInt -> CDate -> Ptr (Ptr CDouble) -> Ptr (Ptr CDate) -> Ptr (Ptr CInt) -> Ptr CString -> IO CUInt

-- |return cash flows together with an indicator whether they occurred as of /settlementDate/
cashFlows :: Leg s
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s [(Double, Day, Bool)] -- ^amount, date, hasOccurred
cashFlows l inc d = mkQLE $
  withObject l $
  \ll -> alloca $
    \pam -> alloca $
      \pdt -> alloca $
        \pocc -> do
          dd <- toQlDate d
          num <- unmarshalExceptions $ c_legCashFlows ll (maybe (-1) fromBool inc) dd pam pdt pocc
          am <- peek pam >>= buildArray num
          dt <- peek pdt >>= buildArray num
          occ <- peek pocc >>= buildArray num
          return $ zip3 (map realToFrac am) (map fromQlDate dt) (map toBool occ)

-- |Cash-flow duration.
-- The simple duration of a string of cash flows is defined as \[ D_{\mathrm{simple}} = \frac{\sum t_i c_i B(t_i)}{\sum c_i B(t_i)} \] where $ c_i $ is the amount of the $ i $-th cash flow, $ t_i $ is its payment time, and $ B(t_i) $ is the corresponding discount according to the passed yield.The modified duration is defined as \[ D_{\mathrm{modified}} = -\frac{1}{P} \frac{\partial P}{\partial y} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.The Macaulay duration is defined for a compounded IRR as \[ D_{\mathrm{Macaulay}} = \left( 1 + \frac{y}{N} \right) D_{\mathrm{modified}} \] where $ y $ is the IRR and $ N $ is the number of cash flows per year.
duration' :: Leg s -- ^leg
  -> InterestRate s -- ^yield
  -> DurationType -- ^type
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s YearFraction
duration' = $(ffiCallX 'duration') c_duration'

foreign import ccall safe "ql.h qlCashFlowsDuration"
  c_duration' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CYearFraction

accrualDays :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Int
accrualDays = $(ffiCallX 'accrualDays) c_accrualDays

foreign import ccall safe "ql.h qlCashFlowsAccrualDays"
  c_accrualDays :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CInt

accrualEndDate :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s (Maybe Day)
accrualEndDate = $(ffiCallX 'accrualEndDate) c_accrualEndDate

foreign import ccall safe "ql.h qlCashFlowsAccrualEndDate"
  c_accrualEndDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

accrualPeriod :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s YearFraction
accrualPeriod = $(ffiCallX 'accrualPeriod) c_accrualPeriod

foreign import ccall safe "ql.h qlCashFlowsAccrualPeriod"
  c_accrualPeriod :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CYearFraction

accrualStartDate :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlDate
  -> QLE s (Maybe Day)
accrualStartDate = $(ffiCallX 'accrualStartDate) c_accrualStartDate

foreign import ccall safe "ql.h qlCashFlowsAccrualStartDate"
  c_accrualStartDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

accruedAmount :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Double
accruedAmount = $(ffiCallX 'accruedAmount) c_accruedAmount

foreign import ccall safe "ql.h qlCashFlowsAccruedAmount"
  c_accruedAmount :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

accruedDays :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Int
accruedDays = $(ffiCallX 'accruedDays) c_accruedDays

foreign import ccall safe "ql.h qlCashFlowsAccruedDays"
  c_accruedDays :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CInt

accruedPeriod :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s YearFraction
accruedPeriod = $(ffiCallX 'accruedPeriod) c_accruedPeriod

foreign import ccall safe "ql.h qlCashFlowsAccruedPeriod"
  c_accruedPeriod :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CYearFraction

-- |At-the-money rate of the cash flows.
-- The result is the fixed rate for which a fixed rate cash flow vector, equivalent to the input vector, has the required NPV according to the given term structure. If the required NPV is not given, the input cash flow vector's NPV is used instead.
atmRate :: Leg s -- ^leg
  -> YieldTermStructure s -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> Double -- ^npv
  -> QLE s Double
atmRate = $(ffiCallX 'atmRate) c_atmRate

foreign import ccall safe "ql.h qlCashFlowsAtmRate"
  c_atmRate :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> CDouble -> Ptr CString -> IO CDouble

basisPointValue :: Leg s -- ^leg
  -> Double -- ^yield
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
basisPointValue = $(ffiCallX 'basisPointValue) c_basisPointValue

foreign import ccall safe "ql.h qlCashFlowsBasisPointValue1"
  c_basisPointValue :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Basis-point value.
-- Obtained by setting dy = 0.0001 in the 2nd-order Taylor series expansion.
basisPointValue' :: Leg s -- ^leg
  -> InterestRate s -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
basisPointValue' = $(ffiCallX 'basisPointValue') c_basisPointValue'

foreign import ccall safe "ql.h qlCashFlowsBasisPointValue"
  c_basisPointValue' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
bpsFromYield' :: Leg s -- ^leg
  -> InterestRate s -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
bpsFromYield' = $(ffiCallX 'bpsFromYield') c_bpsFromYield'

foreign import ccall safe "ql.h qlCashFlowsBps1"
  c_bpsFromYield' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

bpsFromYield :: Leg s -- ^leg
  -> Double -- ^yield
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
bpsFromYield = $(ffiCallX 'bpsFromYield) c_bpsFromYield

foreign import ccall safe "ql.h qlCashFlowsBps2"
  c_bpsFromYield :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Basis-point sensitivity of the cash flows.
-- The result is the change in NPV due to a uniform 1-basis-point change in the rate paid by the cash flows. The change for each coupon is discounted according to the given term structure.
bps :: Leg s -- ^leg
  -> YieldTermStructure s -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
bps = $(ffiCallX 'bps) c_bps

foreign import ccall safe "ql.h qlCashFlowsBps"
  c_bps :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

convexity :: Leg s -- ^leg
  -> Double -- ^yield
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
convexity = $(ffiCallX 'convexity) c_convexity

foreign import ccall safe "ql.h qlCashFlowsConvexity1"
  c_convexity :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Cash-flow convexity.
-- The convexity of a string of cash flows is defined as \[ C = \frac{1}{P} \frac{\partial^2 P}{\partial y^2} \] where $ P $ is the present value of the cash flows according to the given IRR $ y $.
convexity' :: Leg s -- ^leg
  -> InterestRate s -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
convexity' = $(ffiCallX 'convexity') c_convexity'

foreign import ccall safe "ql.h qlCashFlowsConvexity"
  c_convexity' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

duration :: Leg s -- ^leg
  -> Double -- ^yield
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> DurationType -- ^type
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s YearFraction
duration = $(ffiCallX 'duration) c_duration

foreign import ccall safe "ql.h qlCashFlowsDuration1"
  c_duration :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CYearFraction

isExpired :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Bool
isExpired = $(ffiCallX 'isExpired) c_isExpired

foreign import ccall safe "ql.h qlCashFlowsIsExpired"
  c_isExpired :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CInt

maturityDate :: Leg s -- ^leg
  -> Either QLError Day
{-# NOINLINE maturityDate #-}
maturityDate = $(ffiCallPureX 'maturityDate) c_maturityDate

foreign import ccall safe "ql.h qlCashFlowsMaturityDate"
  c_maturityDate :: Ptr CLeg -> Ptr CString -> IO CDate

nextCashFlowAmount :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Double
nextCashFlowAmount = $(ffiCallX 'nextCashFlowAmount) c_nextCashFlowAmount

foreign import ccall safe "ql.h qlCashFlowsNextCashFlowAmount"
  c_nextCashFlowAmount :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

nextCashFlowDate :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s (Maybe Day)
nextCashFlowDate = $(ffiCallX 'nextCashFlowDate) c_nextCashFlowDate

foreign import ccall safe "ql.h qlCashFlowsNextCashFlowDate"
  c_nextCashFlowDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

nextCouponRate :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Double
nextCouponRate = $(ffiCallX 'nextCouponRate) c_nextCouponRate

foreign import ccall safe "ql.h qlCashFlowsNextCouponRate"
  c_nextCouponRate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

nominal :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlDate
  -> QLE s Double
nominal = $(ffiCallX 'nominal) c_nominal

foreign import ccall safe "ql.h qlCashFlowsNominal"
  c_nominal :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

-- |NPV of the cash flows.
-- The IRR is the interest rate at which the NPV of the cash flows equals the dirty price.The NPV is the sum of the cash flows, each discounted according to the given constant interest rate. The result is affected by the choice of the interest-rate compounding and the relative frequency and day counter.
npvFromYield' :: Leg s -- ^leg
  -> InterestRate s -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
npvFromYield' = $(ffiCallX 'npvFromYield') c_npvFromYield'

foreign import ccall safe "ql.h qlCashFlowsNpv1"
  c_npvFromYield' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

npvFromYield :: Leg s -- ^leg
  -> Double -- ^yield
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
npvFromYield = $(ffiCallX 'npvFromYield) c_npvFromYield

foreign import ccall safe "ql.h qlCashFlowsNpv2"
  c_npvFromYield :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |NPV of the cash flows.
-- For details on z-spread refer to: "Credit Spreads Explained", Lehman Brothers European Fixed Income Research - March 2004, D. O'KaneThe NPV is the sum of the cash flows, each discounted according to the z-spreaded term structure. The result is affected by the choice of the z-spread compounding and the relative frequency and day counter.
npv' :: Leg s -- ^leg
  -> YieldTermStructure s -- ^discount
  -> Double -- ^zSpread
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
npv' = $(ffiCallX 'npv') c_npv'

foreign import ccall safe "ql.h qlCashFlowsNpv3"
  c_npv' :: Ptr CLeg -> Ptr CYieldTermStructure -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |NPV of the cash flows.
-- The NPV is the sum of the cash flows, each discounted according to the given term structure.
npv :: Leg s -- ^leg
  -> YieldTermStructure s -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
npv = $(ffiCallX 'npv) c_npv

foreign import ccall safe "ql.h qlCashFlowsNpv"
  c_npv :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |NPV and BPS of the cash flows.
-- The NPV and BPS of the cash flows calculated together for performance reason
npvbps :: Leg s -- ^leg
  -> YieldTermStructure s -- ^discountCurve
  -> Bool -- ^includeSettlementDateFlows
  -> Day -- ^settlementDate
  -> Day -- ^npvDate
  -> QLE s (Double, Double) -- ^(npv, bps)
npvbps l y i s n = mkQLE $
  withObject l $
  \ll -> withObject y $
    \yy -> alloca $
      \pnpv -> alloca $
        \pbps -> do
          ss <- toQlDate s
          nn <- toQlDate n
          unmarshalExceptions $ c_npvbps ll yy (fromBool i) ss nn pnpv pbps
          npvRes <- peek pnpv
          bpsRes <- peek pbps
          return (realToFrac npvRes, realToFrac bpsRes)

foreign import ccall safe "ql.h qlCashFlowsNpvbps"
  c_npvbps :: Ptr CLeg -> Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CDouble -> Ptr CDouble -> Ptr CString -> IO ()

previousCashFlowAmount :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Double
previousCashFlowAmount = $(ffiCallX 'previousCashFlowAmount) c_previousCashFlowAmount

foreign import ccall safe "ql.h qlCashFlowsPreviousCashFlowAmount"
  c_previousCashFlowAmount :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

previousCashFlowDate :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s (Maybe Day)
previousCashFlowDate = $(ffiCallX 'previousCashFlowDate) c_previousCashFlowDate

foreign import ccall safe "ql.h qlCashFlowsPreviousCashFlowDate"
  c_previousCashFlowDate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

previousCouponRate :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> QLE s Double
previousCouponRate = $(ffiCallX 'previousCouponRate) c_previousCouponRate

foreign import ccall safe "ql.h qlCashFlowsPreviousCouponRate"
  c_previousCouponRate :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDouble

referencePeriodEnd :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlDate
  -> QLE s (Maybe Day)
referencePeriodEnd = $(ffiCallX 'referencePeriodEnd) c_referencePeriodEnd

foreign import ccall safe "ql.h qlCashFlowsReferencePeriodEnd"
  c_referencePeriodEnd :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

referencePeriodStart :: Leg s -- ^leg
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlDate
  -> QLE s (Maybe Day)
referencePeriodStart = $(ffiCallX 'referencePeriodStart) c_referencePeriodStart

foreign import ccall safe "ql.h qlCashFlowsReferencePeriodStart"
  c_referencePeriodStart :: Ptr CLeg -> CInt -> CDate -> Ptr CString -> IO CDate

-- |Implied internal rate of return.
-- The function verifies the theoretical existance of an IRR and numerically establishes the IRR to the desired precision.
yield :: Leg s -- ^leg
  -> Double -- ^npv
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> Double -- ^guess
  -> QLE s Double
yield = $(ffiCallX 'yield) c_yield

foreign import ccall safe "ql.h qlCashFlowsYield"
  c_yield :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> CDouble -> CUInt -> CDouble -> Ptr CString -> IO CDouble

yieldValueBasisPoint :: Leg s -- ^leg
  -> Double -- ^yield
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
yieldValueBasisPoint = $(ffiCallX 'yieldValueBasisPoint) c_yieldValueBasisPoint

foreign import ccall safe "ql.h qlCashFlowsYieldValueBasisPoint1"
  c_yieldValueBasisPoint :: Ptr CLeg -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |Yield value of a basis point.
-- The yield value of a one basis point change in price is the derivative of the yield with respect to the price multiplied by 0.01
yieldValueBasisPoint' :: Leg s -- ^leg
  -> InterestRate s -- ^yield
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s Double
yieldValueBasisPoint' = $(ffiCallX 'yieldValueBasisPoint') c_yieldValueBasisPoint'

foreign import ccall safe "ql.h qlCashFlowsYieldValueBasisPoint"
  c_yieldValueBasisPoint' :: Ptr CLeg -> Ptr CInterestRate -> CInt -> CDate -> CDate -> Ptr CString -> IO CDouble

-- |implied Z-spread.
zSpread :: Leg s -- ^leg
  -> Double -- ^npv
  -> YieldTermStructure s
  -> DayCounter s -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> Double -- ^guess
  -> QLE s Double
zSpread = $(ffiCallX 'zSpread) c_zSpread

foreign import ccall safe "ql.h qlCashFlowsZSpread"
  c_zSpread :: Ptr CLeg -> CDouble -> Ptr CYieldTermStructure -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> CDate -> CDouble -> CUInt -> CDouble -> Ptr CString -> IO CDouble

-- |start of the accrual periods for a coupon leg
couponAccrualStartDates :: CouponLeg s -> QLE s [Day]
couponAccrualStartDates l = mkQLE $ map fromQlDate <$>
  withObject l (getArrayX . c_couponAccrualStartDates)

foreign import ccall safe "ql.h qlCouponAccrualStartDates"
  c_couponAccrualStartDates :: Ptr CCouponLeg -> Ptr CUInt -> Ptr CString -> IO (Ptr CDate)

fixedDividend :: Double -- ^amount
  -> Day -- ^date
  -> QLE s (Dividend s)
fixedDividend = $(ffiCall 'fixedDividend) c_fixedDividend

foreign import ccall safe "ql.h qlFixedDividend"
  c_fixedDividend :: CDouble -> CDate -> Ptr CString -> IO (Ptr CDividend)

fractionalDividend' :: Double -- ^rate
  -> Double -- ^nominal
  -> Day -- ^date
  -> QLE s (Dividend s)
fractionalDividend' = $(ffiCall 'fractionalDividend') c_fractionalDividend'

foreign import ccall safe "ql.h qlFractionalDividend1"
  c_fractionalDividend' :: CDouble -> CDouble -> CDate -> Ptr CString -> IO (Ptr CDividend)

fractionalDividend :: Double -- ^rate
  -> Day -- ^date
  -> QLE s (Dividend s)
fractionalDividend = $(ffiCall 'fractionalDividend) c_fractionalDividend

foreign import ccall safe "ql.h qlFractionalDividend"
  c_fractionalDividend :: CDouble -> CDate -> Ptr CString -> IO (Ptr CDividend)

averageBMALeg :: Schedule s -- ^schedule
  -> BMAIndex s -- ^index
  -> [Double] -- ^notionals
  -> DayCounter s -- ^paymentDayCounter
  -> BusinessDayConvention -- ^paymentAdjustment
  -> [Double] -- ^gearings
  -> [Double] -- ^spreads
  -> QLE s (Leg s)
averageBMALeg = $(ffiCall 'averageBMALeg) c_averageBMALeg

foreign import ccall safe "ql.h qlAverageBMALeg"
  c_averageBMALeg :: Ptr CSchedule -> Ptr CBMAIndex -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CLeg)

fixedRateLeg :: Schedule s -- ^schedule
  -> [Double] -- ^Notionals
  -> [InterestRate s] -- ^couponRates
  -> BusinessDayConvention -- ^paymentAdjustment
  -> DayCounter s -- ^firstPeriodDayCounter
  -> Calendar s -- ^paymentCalendar
  -> QLE s (Leg s)
fixedRateLeg = $(ffiCall 'fixedRateLeg) c_fixedRateLeg

foreign import ccall safe "ql.h qlFixedRateLeg"
  c_fixedRateLeg :: Ptr CSchedule -> CUInt -> Ptr CDouble -> CUInt -> Ptr (Ptr CInterestRate) -> CInt -> Ptr CDayCounter -> Ptr CCalendar -> Ptr CString -> IO (Ptr CLeg)

iborLeg :: Schedule s -- ^schedule
  -> IborIndex s -- ^index
  -> [Double] -- ^notionals
  -> DayCounter s -- ^paymentDayCounter
  -> BusinessDayConvention -- ^paymentAdjustment
  -> [Word] -- ^fixingDays
  -> [Double] -- ^gearings
  -> [Double] -- ^spreads
  -> [Double] -- ^caps
  -> [Double] -- ^floors
  -> Bool -- ^inArrears
  -> Bool -- ^zeroPayments
  -> QLE s (Leg s)
iborLeg = $(ffiCall 'iborLeg) c_iborLeg

foreign import ccall safe "ql.h qlIborLeg"
  c_iborLeg :: Ptr CSchedule -> Ptr CIborIndex -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CUInt -> Ptr CUInt -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CInt -> CInt -> Ptr CString -> IO (Ptr CLeg)

overnightLeg :: Schedule s -- ^schedule
  -> OvernightIndex s -- ^overnightIndex
  -> [Double] -- ^notionals
  -> DayCounter s -- ^paymentDayCounter
  -> BusinessDayConvention -- ^paymentAdjustment
  -> [Double] -- ^gearings
  -> [Double] -- ^spreads
  -> QLE s (Leg s)
overnightLeg = $(ffiCall 'overnightLeg) c_overnightLeg

foreign import ccall safe "ql.h qlOvernightLeg"
  c_overnightLeg :: Ptr CSchedule -> Ptr COvernightIndex -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CLeg)

rangeAccrualLeg :: Schedule s -- ^schedule
  -> IborIndex s -- ^index
  -> [Double] -- ^notionals
  -> DayCounter s -- ^paymentDayCounter
  -> BusinessDayConvention -- ^paymentAdjustment
  -> [Word] -- ^fixingDays
  -> [Double] -- ^gearings
  -> [Double] -- ^spreads
  -> [Double] -- ^lowerTriggers
  -> [Double] -- ^upperTriggers
  -> (Int, Unit) -- ^observationTenor
  -> BusinessDayConvention -- ^observationConvention
  -> QLE s (Leg s)
rangeAccrualLeg = $(ffiCall 'rangeAccrualLeg) c_rangeAccrualLeg

foreign import ccall safe "ql.h qlRangeAccrualLeg"
  c_rangeAccrualLeg :: Ptr CSchedule -> Ptr CIborIndex -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CUInt -> Ptr CUInt -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CLeg)

-- |try to downcast leg to a coupon leg
-- don't blame me, it's how QuantLib works
toCouponLeg :: Leg s -> QLE s (CouponLeg s)
toCouponLeg = $(ffiCall 'toCouponLeg) c_toCouponLeg

foreign import ccall safe "ql.h qlLegToCouponLeg"
  c_toCouponLeg :: Ptr CLeg -> Ptr CString -> IO (Ptr CCouponLeg)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
