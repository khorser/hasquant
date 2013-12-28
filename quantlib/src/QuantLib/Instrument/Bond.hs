{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-cse -fno-full-laziness #-} -- for unsafePerformIO
module QuantLib.Instrument.Bond
  (
    bond
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

import Data.Functor((<$>))

import QuantLib.Compounding(Compounding)
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.Time.Unit(Unit)
import QuantLib.CashFlow.DurationType(DurationType)

foreign import ccall safe "ql.h qlBond"
  c_bond :: CUInt -> Ptr CCalendar -> CDate -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBond1"
  c_bond' :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)

-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
bond :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Maybe Day -- ^issueDate
  -> Leg -- ^coupons
  -> QLE s (Bond s)
bond = $(ffiCall 'bond) c_bond

-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
bond' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Double -- ^faceAmount
  -> Maybe Day -- ^maturityDate
  -> Maybe Day -- ^issueDate
  -> Leg -- ^cashflows
  -> QLE s (Bond s)
bond' = $(ffiCall 'bond') c_bond'

foreign import ccall safe "ql.h qlBondMaturityDate"
  c_maturityDate :: Ptr CBond -> IO CDate

-- |Returns the maturity date of the bond
maturityDate :: Bond -> Maybe Day
maturityDate = $(ffiCallPure 'maturityDate) c_maturityDate

foreign import ccall safe "ql.h qlFixedRateBond"
  c_fixedRateBondFromSchedule :: CUInt -> CDouble -> Ptr CSchedule -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CDouble -> CDate -> Ptr CCalendar -> Ptr CString -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedRateBond1"
  c_fixedRateBond :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate
    -> CInt -> CInt -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> CDouble -> CDate -> CDate -> CInt -> CInt -> Ptr CCalendar
    -> Ptr CString -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedRateBond2"
  c_fixedRateBondFromSchedule' :: CUInt -> CDouble -> Ptr CSchedule -> CUInt -> Ptr (Ptr CInterestRate) -> CInt -> CDouble -> CDate -> Ptr CCalendar -> Ptr CString -> IO (Ptr CFixedRateBond)

-- |simple annual compounding coupon rates
fixedRateBondFromSchedule :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [Double] -- ^coupons
  -> DayCounter -- ^accrualDayCounter
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> Calendar -- ^paymentCalendar
  -> QLE s (FixedRateBond s)
fixedRateBondFromSchedule = $(ffiCall 'fixedRateBondFromSchedule) c_fixedRateBondFromSchedule

-- |simple annual compounding coupon rates with internal schedule calculation
fixedRateBond :: Word -- ^settlementDays
  -> Calendar -- ^couponCalendar
  -> Double -- ^faceAmount
  -> Day -- ^startDate
  -> Day -- ^maturityDate
  -> (Int, Unit) -- ^tenor
  -> [Double] -- ^coupons
  -> DayCounter -- ^accrualDayCounter
  -> BusinessDayConvention -- ^accrualConvention
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> Maybe Day -- ^stubDate
  -> DateGenerationRule -- ^rule
  -> Bool -- ^endOfMonth
  -> Calendar -- ^paymentCalendar
  -> QLE s (FixedRateBond s)
fixedRateBond = $(ffiCall 'fixedRateBond) c_fixedRateBond

-- |generic compounding and frequency InterestRate coupons
fixedRateBondFromSchedule' :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [InterestRate] -- ^coupons
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> Calendar -- ^paymentCalendar
  -> QLE s (FixedRateBond s)
fixedRateBondFromSchedule' = $(ffiCall 'fixedRateBondFromSchedule') c_fixedRateBondFromSchedule'

foreign import ccall safe "ql.h qlZeroCouponBond"
  c_zeroCouponBond :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |zero-coupon bond
zeroCouponBond :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Double -- ^faceAmount
  -> Day -- ^maturityDate
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> QLE s (Bond s)
zeroCouponBond = $(ffiCall 'zeroCouponBond) c_zeroCouponBond

foreign import ccall safe "ql.h qlFloatingRateBond"
  c_floatingRateBond :: CUInt -> CDouble -> Ptr CSchedule -> Ptr CIborIndex -> Ptr CDayCounter -> CInt -> CUInt -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |floating-rate bond (possibly capped and/or floored)
floatingRateBond :: Word -- ^settlementDays
 -> Double -- ^faceAmount
 -> Schedule -- ^schedule
 -> IborIndex -- ^iborIndex
 -> DayCounter -- ^accrualDayCounter
 -> BusinessDayConvention -- ^paymentConvention
 -> Word -- ^fixingDays
 -> [Double] -- ^gearings
 -> [Double] -- ^spreads
 -> [Double] -- ^caps
 -> [Double] -- ^floors
 -> Bool -- ^inArrears
 -> Double -- ^redemption
 -> Maybe Day -- ^issueDate
 -> QLE s (Bond s)
floatingRateBond = $(ffiCall 'floatingRateBond) c_floatingRateBond

-- |theoretical bond yield
yield :: Bond
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> QLE s Double
yield = $(ffiCallX 'yield) c_yield

foreign import ccall safe "ql.h qlBondYield"
  c_yield :: Ptr CBond -> Ptr CDayCounter -> CInt -> CInt -> CDouble -> CUInt -> Ptr CString -> IO CDouble

-- |accrued amount at a given date
accruedAmount :: Bond
  -> Day -- ^d
  -> QLE s Double
accruedAmount = $(ffiCallX 'accruedAmount) c_accruedAmount

foreign import ccall safe "ql.h qlBondAccruedAmount"
  c_accruedAmount :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

-- |clean price given a yield and settlement date
cleanPriceFromYield :: Bond
  -> Double -- ^yield
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Day -- ^settlementDate
  -> QLE s Double
cleanPriceFromYield = $(ffiCallX 'cleanPriceFromYield) c_cleanPriceFromYield

foreign import ccall safe "ql.h qlBondCleanPrice1"
  c_cleanPriceFromYield :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

-- |dirty price given a yield and settlement date
dirtyPriceFromYield :: Bond
  -> Double -- ^yield
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Day -- ^settlementDate
  -> QLE s Double
dirtyPriceFromYield = $(ffiCallX 'dirtyPriceFromYield) c_dirtyPriceFromYield

foreign import ccall safe "ql.h qlBondDirtyPrice1"
  c_dirtyPriceFromYield :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

nextCashFlowDate :: Bond
  -> Day -- ^d
  -> Either QLError (Maybe Day)
{-# NOINLINE nextCashFlowDate #-}
nextCashFlowDate = $(ffiCallPureX 'nextCashFlowDate) c_nextCashFlowDate

foreign import ccall safe "ql.h qlBondNextCashFlowDate"
  c_nextCashFlowDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
nextCouponRate :: Bond
  -> Day -- ^d
  -> QLE s Double
nextCouponRate = $(ffiCallX 'nextCouponRate) c_nextCouponRate

foreign import ccall safe "ql.h qlBondNextCouponRate"
  c_nextCouponRate :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

notional :: Bond
  -> Day -- ^d
  -> Either QLError Double
{-# NOINLINE notional #-}
notional = $(ffiCallPureX 'notional) c_notional

foreign import ccall safe "ql.h qlBondNotional"
  c_notional :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

previousCashFlowDate :: Bond
  -> Day -- ^d
  -> Either QLError (Maybe Day)
{-# NOINLINE previousCashFlowDate #-}
previousCashFlowDate = $(ffiCallPureX 'previousCashFlowDate) c_previousCashFlowDate

foreign import ccall safe "ql.h qlBondPreviousCashFlowDate"
  c_previousCashFlowDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
previousCouponRate :: Bond
  -> Day -- ^d
  -> QLE s Double
previousCouponRate = $(ffiCallX 'previousCouponRate) c_previousCouponRate

foreign import ccall safe "ql.h qlBondPreviousCouponRate"
  c_previousCouponRate :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
settlementValueFromCleanPrice :: Bond
  -> Double -- ^cleanPrice
  -> QLE s Double
settlementValueFromCleanPrice = $(ffiCallX 'settlementValueFromCleanPrice) c_settlementValueFromCleanPrice

foreign import ccall safe "ql.h qlBondSettlementValue1"
  c_settlementValueFromCleanPrice :: Ptr CBond -> CDouble -> Ptr CString -> IO CDouble

-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
settlementValue :: Bond
  -> QLE s Double
settlementValue = $(ffiCallX 'settlementValue) c_settlementValue

foreign import ccall safe "ql.h qlBondSettlementValue"
  c_settlementValue :: Ptr CBond -> Ptr CString -> IO CDouble

-- |yield given a (clean) price and settlement date
yieldFromCleanPrice :: Bond
  -> Double -- ^cleanPrice
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Day -- ^settlementDate
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> QLE s Double
yieldFromCleanPrice = $(ffiCallX 'yieldFromCleanPrice) c_yieldFromCleanPrice

foreign import ccall safe "ql.h qlBondYield1"
  c_yieldFromCleanPrice :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDouble -> CUInt -> Ptr CString -> IO CDouble

isTradable :: Bond
  -> Day -- ^d
  -> Either QLError Bool
{-# NOINLINE isTradable #-}
isTradable = $(ffiCallPureX 'isTradable) c_isTradable

foreign import ccall safe "ql.h qlBondIsTradable"
  c_isTradable :: Ptr CBond -> CDate -> Ptr CString -> IO CInt

notionals :: Bond -> IO [Double]
notionals b =
  map realToFrac <$> withObject b (getArrayX . c_notionals)

foreign import ccall safe "ql.h qlBondNotionals"
  c_notionals :: Ptr CBond -> Ptr CUInt -> Ptr CString -> IO (Ptr CDouble)

-- |returns all the cashflows, including the redemptions.
cashFlows :: Bond -> QLE s (Leg s)
cashFlows = $(ffiCall 'cashFlows) c_cashFlows

foreign import ccall safe "ql.h qlBondCashflows"
  c_cashFlows :: Ptr CBond -> Ptr CString -> IO (Ptr CLeg)

-- |returns just the redemption flows (not interest payments)
redemptions :: Bond -> QLE s (Leg s)
redemptions = $(ffiCall 'redemptions) c_redemptions

foreign import ccall safe "ql.h qlBondRedemptions"
  c_redemptions :: Ptr CBond -> Ptr CString -> IO (Ptr CLeg)

settlementDate :: Bond
  -> Day -- ^d
  -> Either QLError Day
{-# NOINLINE settlementDate #-}
settlementDate = $(ffiCallPureX 'settlementDate) c_settlementDate

foreign import ccall safe "ql.h qlBondSettlementDate"
  c_settlementDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

startDate :: Bond -> QLE s Day
startDate = $(ffiCallX 'startDate) c_startDate

foreign import ccall safe "ql.h qlBondStartDate"
  c_startDate :: Ptr CBond -> Ptr CString -> IO CDate

accrualDays :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError Int
{-# NOINLINE accrualDays #-}
accrualDays = $(ffiCallPureX 'accrualDays) c_accrualDays

foreign import ccall safe "ql.h qlBondFunctionsAccrualDays"
  c_accrualDays :: Ptr CBond -> CDate -> Ptr CString -> IO CInt

accrualEndDate :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError (Maybe Day)
{-# NOINLINE accrualEndDate #-}
accrualEndDate = $(ffiCallPureX 'accrualEndDate) c_accrualEndDate

foreign import ccall safe "ql.h qlBondFunctionsAccrualEndDate"
  c_accrualEndDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

accrualPeriod :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError YearFraction
{-# NOINLINE accrualPeriod #-}
accrualPeriod = $(ffiCallPureX 'accrualPeriod) c_accrualPeriod

foreign import ccall safe "ql.h qlBondFunctionsAccrualPeriod"
  c_accrualPeriod :: Ptr CBond -> CDate -> Ptr CString -> IO CYearFraction

accrualStartDate :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError (Maybe Day)
{-# NOINLINE accrualStartDate #-}
accrualStartDate = $(ffiCallPureX 'accrualStartDate) c_accrualStartDate

foreign import ccall safe "ql.h qlBondFunctionsAccrualStartDate"
  c_accrualStartDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

accruedDays :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError Int
{-# NOINLINE accruedDays #-}
accruedDays = $(ffiCallPureX 'accruedDays) c_accruedDays

foreign import ccall safe "ql.h qlBondFunctionsAccruedDays"
  c_accruedDays :: Ptr CBond -> CDate -> Ptr CString -> IO CInt

accruedPeriod :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError YearFraction
{-# NOINLINE accruedPeriod #-}
accruedPeriod = $(ffiCallPureX 'accruedPeriod) c_accruedPeriod

foreign import ccall safe "ql.h qlBondFunctionsAccruedPeriod"
  c_accruedPeriod :: Ptr CBond -> CDate -> Ptr CString -> IO CYearFraction

atmRate :: Bond -- ^bond
  -> YieldTermStructure -- ^discountCurve
  -> Day -- ^settlementDate
  -> Double -- ^cleanPrice
  -> QLE s Double
atmRate = $(ffiCallX 'atmRate) c_atmRate

foreign import ccall safe "ql.h qlBondFunctionsAtmRate"
  c_atmRate :: Ptr CBond -> Ptr CYieldTermStructure -> CDate -> CDouble -> Ptr CString -> IO CDouble

basisPointValue :: Bond -- ^bond
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> QLE s Double
basisPointValue = $(ffiCallX 'basisPointValue) c_basisPointValue

foreign import ccall safe "ql.h qlBondFunctionsBasisPointValue1"
  c_basisPointValue :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

basisPointValue' :: Bond -- ^bond
  -> InterestRate -- ^yield
  -> Day -- ^settlementDate
  -> QLE s Double
basisPointValue' = $(ffiCallX 'basisPointValue') c_basisPointValue'

foreign import ccall safe "ql.h qlBondFunctionsBasisPointValue"
  c_basisPointValue' :: Ptr CBond -> Ptr CInterestRate -> CDate -> Ptr CString -> IO CDouble

bpsFromYield' :: Bond -- ^bond
  -> InterestRate -- ^yield
  -> Day -- ^settlementDate
  -> QLE s Double
bpsFromYield' = $(ffiCallX 'bpsFromYield') c_bpsFromYield'

foreign import ccall safe "ql.h qlBondFunctionsBps1"
  c_bpsFromYield' :: Ptr CBond -> Ptr CInterestRate -> CDate -> Ptr CString -> IO CDouble

bpsFromYield :: Bond -- ^bond
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> QLE s Double
bpsFromYield = $(ffiCallX 'bpsFromYield) c_bpsFromYield

foreign import ccall safe "ql.h qlBondFunctionsBps2"
  c_bpsFromYield :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

bps :: Bond -- ^bond
  -> YieldTermStructure -- ^discountCurve
  -> Day -- ^settlementDate
  -> QLE s Double
bps = $(ffiCallX 'bps) c_bps

foreign import ccall safe "ql.h qlBondFunctionsBps"
  c_bps :: Ptr CBond -> Ptr CYieldTermStructure -> CDate -> Ptr CString -> IO CDouble

cleanPrice :: Bond -- ^bond
  -> YieldTermStructure -- ^discountCurve
  -> Day -- ^settlementDate
  -> QLE s Double
cleanPrice = $(ffiCallX 'cleanPrice) c_cleanPrice

foreign import ccall safe "ql.h qlBondFunctionsCleanPrice2"
  c_cleanPrice :: Ptr CBond -> Ptr CYieldTermStructure -> CDate -> Ptr CString -> IO CDouble

cleanPrice' :: Bond -- ^bond
  -> YieldTermStructure -- ^discount
  -> Double -- ^zSpread
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> QLE s Double
cleanPrice' = $(ffiCallX 'cleanPrice') c_cleanPrice'

foreign import ccall safe "ql.h qlBondFunctionsCleanPrice3"
  c_cleanPrice' :: Ptr CBond -> Ptr CYieldTermStructure -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

cleanPriceFromYield' :: Bond -- ^bond
  -> InterestRate -- ^yield
  -> Day -- ^settlementDate
  -> QLE s Double
cleanPriceFromYield' = $(ffiCallX 'cleanPriceFromYield') c_cleanPriceFromYield'

foreign import ccall safe "ql.h qlBondFunctionsCleanPrice4"
  c_cleanPriceFromYield' :: Ptr CBond -> Ptr CInterestRate -> CDate -> Ptr CString -> IO CDouble

convexity :: Bond -- ^bond
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> QLE s Double
convexity = $(ffiCallX 'convexity) c_convexity

foreign import ccall safe "ql.h qlBondFunctionsConvexity1"
  c_convexity :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

convexity' :: Bond -- ^bond
  -> InterestRate -- ^yield
  -> Day -- ^settlementDate
  -> QLE s Double
convexity' = $(ffiCallX 'convexity') c_convexity'

foreign import ccall safe "ql.h qlBondFunctionsConvexity"
  c_convexity' :: Ptr CBond -> Ptr CInterestRate -> CDate -> Ptr CString -> IO CDouble

duration :: Bond -- ^bond
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> DurationType -- ^type
  -> Day -- ^settlementDate
  -> QLE s YearFraction
duration = $(ffiCallX 'duration) c_duration

foreign import ccall safe "ql.h qlBondFunctionsDuration1"
  c_duration :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CInt -> CDate -> Ptr CString -> IO CYearFraction

duration' :: Bond -- ^bond
  -> InterestRate -- ^yield
  -> DurationType -- ^type
  -> Day -- ^settlementDate
  -> QLE s YearFraction
duration' = $(ffiCallX 'duration') c_duration'

foreign import ccall safe "ql.h qlBondFunctionsDuration"
  c_duration' :: Ptr CBond -> Ptr CInterestRate -> CInt -> CDate -> Ptr CString -> IO CYearFraction

nextCashFlowAmount :: Bond -- ^bond
  -> Day -- ^refDate
  -> QLE s Double
nextCashFlowAmount = $(ffiCallX 'nextCashFlowAmount) c_nextCashFlowAmount

foreign import ccall safe "ql.h qlBondFunctionsNextCashFlowAmount"
  c_nextCashFlowAmount :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

previousCashFlowAmount :: Bond -- ^bond
  -> Day -- ^refDate
  -> QLE s Double
previousCashFlowAmount = $(ffiCallX 'previousCashFlowAmount) c_previousCashFlowAmount

foreign import ccall safe "ql.h qlBondFunctionsPreviousCashFlowAmount"
  c_previousCashFlowAmount :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

referencePeriodEnd :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError (Maybe Day)
{-# NOINLINE referencePeriodEnd #-}
referencePeriodEnd = $(ffiCallPureX 'referencePeriodEnd) c_referencePeriodEnd

foreign import ccall safe "ql.h qlBondFunctionsReferencePeriodEnd"
  c_referencePeriodEnd :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

referencePeriodStart :: Bond -- ^bond
  -> Day -- ^settlementDate
  -> Either QLError (Maybe Day)
{-# NOINLINE referencePeriodStart #-}
referencePeriodStart = $(ffiCallPureX 'referencePeriodStart) c_referencePeriodStart

foreign import ccall safe "ql.h qlBondFunctionsReferencePeriodStart"
  c_referencePeriodStart :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

yieldFromCleanPrice' :: Bond -- ^bond
  -> Double -- ^cleanPrice
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> Double -- ^guess
  -> QLE s Double
yieldFromCleanPrice' = $(ffiCallX 'yieldFromCleanPrice') c_yieldFromCleanPrice'

foreign import ccall safe "ql.h qlBondFunctionsYield2"
  c_yieldFromCleanPrice' :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDouble -> CUInt -> CDouble -> Ptr CString -> IO CDouble

yieldValueBasisPoint :: Bond -- ^bond
  -> Double -- ^yield
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> QLE s Double
yieldValueBasisPoint = $(ffiCallX 'yieldValueBasisPoint) c_yieldValueBasisPoint

foreign import ccall safe "ql.h qlBondFunctionsYieldValueBasisPoint1"
  c_yieldValueBasisPoint :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

yieldValueBasisPoint' :: Bond -- ^bond
  -> InterestRate -- ^yield
  -> Day -- ^settlementDate
  -> QLE s Double
yieldValueBasisPoint' = $(ffiCallX 'yieldValueBasisPoint') c_yieldValueBasisPoint'

foreign import ccall safe "ql.h qlBondFunctionsYieldValueBasisPoint"
  c_yieldValueBasisPoint' :: Ptr CBond -> Ptr CInterestRate -> CDate -> Ptr CString -> IO CDouble

zSpread :: Bond -- ^bond
  -> Double -- ^cleanPrice
  -> YieldTermStructure
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> Day -- ^settlementDate
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> Double -- ^guess
  -> QLE s Double
zSpread = $(ffiCallX 'zSpread) c_zSpread

foreign import ccall safe "ql.h qlBondFunctionsZSpread"
  c_zSpread :: Ptr CBond -> CDouble -> Ptr CYieldTermStructure -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDouble -> CUInt -> CDouble -> Ptr CString -> IO CDouble

floatingRateBond' :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Day -- ^startDate
  -> Day -- ^maturityDate
  -> Frequency -- ^couponFrequency
  -> Calendar -- ^calendar
  -> IborIndex -- ^iborIndex
  -> DayCounter -- ^accrualDayCounter
  -> BusinessDayConvention -- ^accrualConvention
  -> BusinessDayConvention -- ^paymentConvention
  -> Word -- ^fixingDays
  -> [Double] -- ^gearings
  -> [Double] -- ^spreads
  -> [Double] -- ^caps
  -> [Double] -- ^floors
  -> Bool -- ^inArrears
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> Maybe Day -- ^stubDate
  -> DateGenerationRule -- ^rule
  -> Bool -- ^endOfMonth
  -> QLE s (Bond s)
floatingRateBond' = $(ffiCall 'floatingRateBond') c_floatingRateBond'

foreign import ccall safe "ql.h qlFloatingRateBond1"
  c_floatingRateBond' :: CUInt -> CDouble -> CDate -> CDate -> CInt -> Ptr CCalendar -> Ptr CIborIndex -> Ptr CDayCounter -> CInt -> CInt -> CUInt -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CInt -> CDouble -> CDate -> CDate -> CInt -> CInt -> Ptr CString -> IO (Ptr CBond)

-- |theoretical clean price for the current evaluation date and term structure
currentCleanPrice :: Bond -> QLE s Double
currentCleanPrice = $(ffiCallX 'currentCleanPrice) c_currentCleanPrice

foreign import ccall safe "ql.h qlBondCleanPrice"
  c_currentCleanPrice:: Ptr CBond -> Ptr CString -> IO CDouble

-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
currentDirtyPrice :: Bond -> QLE s Double
currentDirtyPrice= $(ffiCallX 'currentDirtyPrice) c_currentDirtyPrice

foreign import ccall safe "ql.h qlBondDirtyPrice"
  c_currentDirtyPrice :: Ptr CBond -> Ptr CString -> IO CDouble

callableFixedRateBond :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [Double] -- ^coupons
  -> DayCounter -- ^accrualDayCounter
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> [Callability] -- ^putCallSchedule
  -> IO CallableBond
callableFixedRateBond = $(ffiCall 'callableFixedRateBond) c_callableFixedRateBond

foreign import ccall safe "ql.h qlCallableFixedRateBond"
  c_callableFixedRateBond :: CUInt -> CDouble -> Ptr CSchedule -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CDouble -> CDate -> CUInt -> Ptr (Ptr CCallability) -> Ptr CString -> IO (Ptr CCallableBond)

callableZeroCouponBond :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Calendar -- ^calendar
  -> Day -- ^maturityDate
  -> DayCounter -- ^dayCounter
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> [Callability] -- ^putCallSchedule
  -> IO CallableBond
callableZeroCouponBond = $(ffiCall 'callableZeroCouponBond) c_callableZeroCouponBond

foreign import ccall safe "ql.h qlCallableZeroCouponBond"
  c_callableZeroCouponBond :: CUInt -> CDouble -> Ptr CCalendar -> CDate -> Ptr CDayCounter -> CInt -> CDouble -> CDate -> CUInt -> Ptr (Ptr CCallability) -> Ptr CString -> IO (Ptr CCallableBond)

convertibleFixedCouponBond :: Exercise -- ^exercise
  -> Double -- ^conversionRatio
  -> [Dividend] -- ^dividends
  -> [Callability] -- ^callability
  -> Quote -- ^creditSpread
  -> Day -- ^issueDate
  -> Word -- ^settlementDays
  -> [Double] -- ^coupons
  -> DayCounter -- ^dayCounter
  -> Schedule -- ^schedule
  -> Double -- ^redemption
  -> IO ConvertibleBond
convertibleFixedCouponBond = $(ffiCall 'convertibleFixedCouponBond) c_convertibleFixedCouponBond

foreign import ccall safe "ql.h qlConvertibleFixedCouponBond"
  c_convertibleFixedCouponBond :: Ptr CExercise -> CDouble -> CUInt -> Ptr (Ptr CDividend) -> CUInt -> Ptr (Ptr CCallability) -> Ptr CQuote -> CDate -> CUInt -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> Ptr CSchedule -> CDouble -> Ptr CString -> IO (Ptr CConvertibleBond)

convertibleFloatingRateBond :: Exercise -- ^exercise
  -> Double -- ^conversionRatio
  -> [Dividend] -- ^dividends
  -> [Callability] -- ^callability
  -> Quote -- ^creditSpread
  -> Day -- ^issueDate
  -> Word -- ^settlementDays
  -> IborIndex -- ^index
  -> Word -- ^fixingDays
  -> [Double] -- ^spreads
  -> DayCounter -- ^dayCounter
  -> Schedule -- ^schedule
  -> Double -- ^redemption
  -> IO ConvertibleBond
convertibleFloatingRateBond = $(ffiCall 'convertibleFloatingRateBond) c_convertibleFloatingRateBond

foreign import ccall safe "ql.h qlConvertibleFloatingRateBond"
  c_convertibleFloatingRateBond :: Ptr CExercise -> CDouble -> CUInt -> Ptr (Ptr CDividend) -> CUInt -> Ptr (Ptr CCallability) -> Ptr CQuote -> CDate -> CUInt -> Ptr CIborIndex -> CUInt -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> Ptr CSchedule -> CDouble -> Ptr CString -> IO (Ptr CConvertibleBond)

convertibleZeroCouponBond :: Exercise -- ^exercise
  -> Double -- ^conversionRatio
  -> [Dividend] -- ^dividends
  -> [Callability] -- ^callability
  -> Quote -- ^creditSpread
  -> Day -- ^issueDate
  -> Word -- ^settlementDays
  -> DayCounter -- ^dayCounter
  -> Schedule -- ^schedule
  -> Double -- ^redemption
  -> IO ConvertibleBond
convertibleZeroCouponBond = $(ffiCall 'convertibleZeroCouponBond) c_convertibleZeroCouponBond

foreign import ccall safe "ql.h qlConvertibleZeroCouponBond"
  c_convertibleZeroCouponBond :: Ptr CExercise -> CDouble -> CUInt -> Ptr (Ptr CDividend) -> CUInt -> Ptr (Ptr CCallability) -> Ptr CQuote -> CDate -> CUInt -> Ptr CDayCounter -> Ptr CSchedule -> CDouble -> Ptr CString -> IO (Ptr CConvertibleBond)

-- |callability leaving to the holder the possibility to convert
softCallability :: CallabilityPrice
  -> Day
  -> Double -- ^trigger
  -> IO Callability
softCallability = $(ffiCall 'softCallability) c_softCallability

foreign import ccall safe "ql.h qlSoftCallability"
  c_softCallability :: Ptr CCallabilityPrice -> CInt -> CDouble -> Ptr CString -> IO (Ptr CCallability)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
