{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Bond
  (
    bond
  , bond'
  , fixedRateBond
  , fixedRateBond'
  , fixedRateBond''
  , zeroCouponBond
  , floatingRateBond
  , fixedRateBondForward

  , maturityDate
  , yield
  , accruedAmount
  , cleanPrice'
  , cleanPrice
  , dirtyPrice'
  , dirtyPrice
  , nextCashFlowDate
  , nextCouponRate
  , notional
  , previousCashFlowDate
  , previousCouponRate
  , settlementValue'
  , settlementValue
  , yield'
  , isTradable

  , setCouponPricer
  )

where

import QuantLib.Compounding
import QuantLib.Time.Frequency
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.PositionType
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.DateGenerationRule(DateGenerationRule)

foreign import ccall safe "ql.h qlBond"
  c_bond :: CUInt -> Ptr CCalendar -> CDate -> Ptr CLeg -> Ptr CString
  -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBond1"
  c_bond' :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate -> Ptr CLeg
  -> Ptr CString -> IO (Ptr CBond)

-- |constructor for amortizing or non-amortizing bonds.
-- Redemptions and maturity are calculated from the coupon data, if available. Therefore, redemptions must not be included in the passed cash flows.
-- QuantLibXL: qlBond
bond :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Maybe Day -- ^issueDate
  -> Leg -- ^coupons
  -> IO Bond
bond = $(ffiConstruct 'bond) c_bond

-- |old constructor for non amortizing bonds.
-- /Warning/ The last passed cash flow must be the bond redemption. No other cash flow can have a date later than the redemption date.
bond' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Double -- ^faceAmount
  -> Maybe Day -- ^maturityDate
  -> Maybe Day -- ^issueDate
  -> Leg -- ^cashflows
  -> IO Bond
bond' = $(ffiConstruct 'bond') c_bond'

foreign import ccall safe "ql.h qlBondMaturityDate"
  c_maturityDate :: Ptr CBond -> IO CDate

-- |Returns the maturity date of the bond. QuantLib: qlBondMaturityDate
maturityDate :: Bond -> Maybe Day
maturityDate = $(ffiCallIO 'maturityDate) c_maturityDate
--- XXX assuming bonds are immutable, any exceptions possible?

foreign import ccall safe "ql.h qlFixedRateBond"
  c_fixedRateBond :: CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr CDouble -> Ptr CDayCounter
    -> CInt -> CDouble -> CDate -> Ptr CCalendar -> Ptr CString
    -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedRateBond1"
  c_fixedRateBond' :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate
    -> Ptr CPeriod -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CInt
    -> CDouble -> CDate -> CDate -> CInt -> CInt -> Ptr CCalendar
    -> Ptr CString -> IO (Ptr CFixedRateBond)
foreign import ccall safe "ql.h qlFixedRateBond2"
  c_fixedRateBond'' :: CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr (Ptr CInterestRate) -> CInt -> CDouble -> CDate -> Ptr CCalendar
    -> Ptr CString -> IO (Ptr CFixedRateBond)

-- |simple annual compounding coupon rates. QuantLibXL: qlFixedRateBond
fixedRateBond :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [Double] -- ^coupons
  -> DayCounter -- ^accrualDayCounter
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> Calendar -- ^paymentCalendar
  -> IO FixedRateBond
fixedRateBond = $(ffiConstruct 'fixedRateBond) c_fixedRateBond

-- |simple annual compounding coupon rates with internal schedule calculation
fixedRateBond' :: Word -- ^settlementDays
  -> Calendar -- ^couponCalendar
  -> Double -- ^faceAmount
  -> Day -- ^startDate
  -> Day -- ^maturityDate
  -> Period -- ^tenor
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
  -> IO FixedRateBond
fixedRateBond' = $(ffiConstruct 'fixedRateBond') c_fixedRateBond'
                                         
-- |generic compounding and frequency InterestRate coupons. QuantLibXL: qlFixedRateBond2
fixedRateBond'' :: Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [InterestRate] -- ^coupons
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> Calendar -- ^paymentCalendar
  -> IO FixedRateBond
fixedRateBond'' = $(ffiConstruct 'fixedRateBond'') c_fixedRateBond''

foreign import ccall safe "ql.h qlZeroCouponBond"
  c_zeroCouponBond :: CUInt -> Ptr CCalendar -> CDouble -> CDate
    -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |zero-coupon bond. QuantLibXL: qlZeroCouponBond
zeroCouponBond :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Double -- ^faceAmount
  -> Day -- ^maturityDate
  -> BusinessDayConvention -- ^paymentConvention
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> IO Bond
zeroCouponBond = $(ffiConstruct 'zeroCouponBond) c_zeroCouponBond

foreign import ccall safe "ql.h qlBondSetCouponPricer"
  c_bondSetCouponPricer :: Ptr CBond -> Ptr CFloatingRateCouponPricer
    -> Ptr CString -> IO ()

-- |Set the coupon pricer at the given Bond object
-- following QuantLibXL qlBondSetCouponPricer here.
-- In C++ it is a function working on
-- cashflows (see the implementation in qlBondSetCouponPricer)
setCouponPricer :: Bond -> FloatingRateCouponPricer -> IO ()
setCouponPricer = $(ffiCallX 'setCouponPricer) c_bondSetCouponPricer

foreign import ccall safe "ql.h qlFloatingRateBond"
  c_floatingRateBond :: CUInt -> CDouble -> Ptr CSchedule -> Ptr CIborIndex
    -> Ptr CDayCounter -> CInt -> CUInt -> CUInt -> Ptr CDouble
    -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble
    -> CInt -> CDouble -> CDate -> Ptr CString -> IO (Ptr CBond)

-- |floating-rate bond (possibly capped and/or floored). QuantLibXL: qlFloatingRateBond
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
 -> IO Bond
floatingRateBond = $(ffiConstruct 'floatingRateBond) c_floatingRateBond

-- |theoretical bond yield
-- The default bond settlement and theoretical price are used for calculation.
yield :: Bond
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> IO Double
yield = $(ffiCallX 'yield) c_bondYield

foreign import ccall safe "ql.h qlBondYield"
  c_bondYield :: Ptr CBond -> Ptr CDayCounter -> CInt -> CInt -> CDouble -> CUInt -> Ptr CString -> IO CDouble

-- |accrued amount at a given date
-- The default bond settlement is used if no date is given.
accruedAmount :: Bond
  -> Maybe Day -- ^d
  -> IO Double
accruedAmount = $(ffiCallX 'accruedAmount) c_accruedAmount

foreign import ccall safe "ql.h qlBondAccruedAmount"
  c_accruedAmount :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

-- |clean price given a yield and settlement date
-- The default bond settlement is used if no date is given.
cleanPrice' :: Bond
  -> Double -- ^yield
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Maybe Day -- ^settlementDate
  -> IO Double
cleanPrice' = $(ffiCallX 'cleanPrice') c_cleanPrice'

foreign import ccall safe "ql.h qlBondCleanPrice1"
  c_cleanPrice' :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

-- |theoretical clean price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
cleanPrice :: Bond
  -> IO Double
cleanPrice = $(ffiCallX 'cleanPrice) c_cleanPrice

foreign import ccall safe "ql.h qlBondCleanPrice"
  c_cleanPrice :: Ptr CBond -> Ptr CString -> IO CDouble

-- |dirty price given a yield and settlement date
-- The default bond settlement is used if no date is given.
dirtyPrice' :: Bond
  -> Double -- ^yield
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Maybe Day -- ^settlementDate
  -> IO Double
dirtyPrice' = $(ffiCallX 'dirtyPrice') c_dirtyPrice'

foreign import ccall safe "ql.h qlBondDirtyPrice1"
  c_dirtyPrice' :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> Ptr CString -> IO CDouble

-- |theoretical dirty price
-- The default bond settlement is used for calculation. /Warning/ the theoretical price calculated from a flat term structure might differ slightly from the price calculated from the corresponding yield by means of the other overload of this function. If the price from a constant yield is desired, it is advisable to use such other overload.
dirtyPrice :: Bond
  -> IO Double
dirtyPrice = $(ffiCallX 'dirtyPrice) c_dirtyPrice

foreign import ccall safe "ql.h qlBondDirtyPrice"
  c_dirtyPrice :: Ptr CBond -> Ptr CString -> IO CDouble

nextCashFlowDate :: Bond
  -> Maybe Day -- ^d
  -> IO Day
nextCashFlowDate = $(ffiCallX 'nextCashFlowDate) c_nextCashFlowDate

foreign import ccall safe "ql.h qlBondNextCashFlowDate"
  c_nextCashFlowDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

-- |Expected next coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the already-fixed not-yet-paid one.The current bond settlement is used if no date is given.
nextCouponRate :: Bond
  -> Maybe Day -- ^d
  -> IO Double
nextCouponRate = $(ffiCallX 'nextCouponRate) c_nextCouponRate

foreign import ccall safe "ql.h qlBondNextCouponRate"
  c_nextCouponRate :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

notional :: Bond
  -> Maybe Day -- ^d
  -> IO Double
notional = $(ffiCallX 'notional) c_notional

foreign import ccall safe "ql.h qlBondNotional"
  c_notional :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

previousCashFlowDate :: Bond
  -> Maybe Day -- ^d
  -> IO Day
previousCashFlowDate = $(ffiCallX 'previousCashFlowDate) c_previousCashFlowDate

foreign import ccall safe "ql.h qlBondPreviousCashFlowDate"
  c_previousCashFlowDate :: Ptr CBond -> CDate -> Ptr CString -> IO CDate

-- |Previous coupon already paid at a given date.
-- Expected previous coupon: depending on (the bond and) the given date the coupon can be historic, deterministic or expected in a stochastic sense. When the bond settlement date is used the coupon is the last paid one.The current bond settlement is used if no date is given.
previousCouponRate :: Bond
  -> Maybe Day -- ^d
  -> IO Double
previousCouponRate = $(ffiCallX 'previousCouponRate) c_previousCouponRate

foreign import ccall safe "ql.h qlBondPreviousCouponRate"
  c_previousCouponRate :: Ptr CBond -> CDate -> Ptr CString -> IO CDouble

-- |settlement value as a function of the clean price
-- The default bond settlement date is used for calculation.
settlementValue' :: Bond
  -> Double -- ^cleanPrice
  -> IO Double
settlementValue' = $(ffiCallX 'settlementValue') c_settlementValue'

foreign import ccall safe "ql.h qlBondSettlementValue1"
  c_settlementValue' :: Ptr CBond -> CDouble -> Ptr CString -> IO CDouble

-- |theoretical settlement value
-- The default bond settlement date is used for calculation.
settlementValue :: Bond
  -> IO Double
settlementValue = $(ffiCallX 'settlementValue) c_settlementValue

foreign import ccall safe "ql.h qlBondSettlementValue"
  c_settlementValue :: Ptr CBond -> Ptr CString -> IO CDouble

-- |yield given a (clean) price and settlement date
-- The default bond settlement is used if no date is given.
yield' :: Bond
  -> Double -- ^cleanPrice
  -> DayCounter -- ^dc
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Maybe Day -- ^settlementDate
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> IO Double
yield' = $(ffiCallX 'yield') c_yield'

foreign import ccall safe "ql.h qlBondYield1"
  c_yield' :: Ptr CBond -> CDouble -> Ptr CDayCounter -> CInt -> CInt -> CDate -> CDouble -> CUInt -> Ptr CString -> IO CDouble

isTradable :: Bond
  -> Maybe Day -- ^d
  -> IO Bool
isTradable = $(ffiCallX 'isTradable) c_isTradable

foreign import ccall safe "ql.h qlBondIsTradable"
  c_isTradable :: Ptr CBond -> CDate -> Ptr CString -> IO CInt

-- |If strike is given in the constructor, can calculate the NPV of the contract via NPV().If strike/forward price is desired, it can be obtained via forwardPrice(). In this case, the strike variable in the constructor is irrelevant and will be ignored.
fixedRateBondForward :: Day -- ^valueDate
  -> Day -- ^maturityDate
  -> PositionType -- ^type
  -> Double -- ^strike
  -> Word -- ^settlementDays
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^businessDayConvention
  -> FixedRateBond -- ^fixedCouponBond
  -> Maybe YieldTermStructure -- ^discountCurve
  -> Maybe YieldTermStructure -- ^incomeDiscountCurve
  -> IO FixedRateBondForward
fixedRateBondForward = $(ffiConstruct 'fixedRateBondForward) c_fixedRateBondForward

foreign import ccall safe "ql.h qlFixedRateBondForward"
  c_fixedRateBondForward :: CDate -> CDate -> CInt -> CDouble -> CUInt -> Ptr CDayCounter -> Ptr CCalendar -> CInt -> Ptr CFixedRateBond -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CFixedRateBondForward)
