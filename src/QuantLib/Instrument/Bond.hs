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

  , setCouponPricer
  )

where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
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
