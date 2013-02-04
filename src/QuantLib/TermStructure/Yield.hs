{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.TermStructure.Yield
  (
  -- makers
    depositRateHelper
  , fixedRateBondHelper
  , swapRateHelper'
  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  -- accessors
  , discount
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Frequency(Frequency)
import QuantLib.TermStructure.Trait(Trait)

foreign import ccall safe "ql.h qlDepositRateHelper"
  c_depositRateHelper :: Ptr CQuote -> Ptr CPeriod -> CUInt -> Ptr CCalendar
    -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlFixedRateBondHelper"
  c_fixedRateBondHelper :: Ptr CQuote -> CUInt -> CDouble -> Ptr CSchedule
    -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CDouble -> CInt
    -> Ptr CString -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlPiecewiseYieldCurve"
  c_piecewiseYieldCurve :: CDate -> CUInt -> Ptr (Ptr CRateHelper)
    -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble
    -> CString -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

-- |QuantLibXL: qlDepositRateHelper2
depositRateHelper :: Quote -- ^rate
  -> Period -- ^tenor
  -> Word -- ^fixingDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> IO RateHelper
depositRateHelper = $(ffiConstruct 'depositRateHelper) c_depositRateHelper

-- |QuantLibXL: qlFixedRateBondHelper
fixedRateBondHelper :: Quote -- ^cleanPrice
  -> Word -- ^settlementDays
  -> Double -- ^faceAmount
  -> Schedule -- ^schedule
  -> [Double] -- ^coupons
  -> DayCounter -- ^dayCounter
  -> BusinessDayConvention -- ^paymentConv
  -> Double -- ^redemption
  -> Maybe Day -- ^issueDate
  -> IO RateHelper
fixedRateBondHelper = $(ffiConstruct 'fixedRateBondHelper) c_fixedRateBondHelper

foreign import ccall safe "ql.h qlYieldTSDiscount"
  c_yieldTSDiscount :: Ptr CYieldTermStructure -> CDate -> CInt
    -> Ptr CString -> IO CDouble

piecewiseYieldCurve :: Day -- ^referenceDate
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> Double -- ^accuracy
  -> Trait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve =
  $(ffiConstruct 'piecewiseYieldCurve) c_piecewiseYieldCurve

foreign import ccall safe "ql.h qlPiecewiseYieldCurve1"
  c_piecewiseYieldCurve' :: CUInt -> Ptr CCalendar -> CUInt
    -> Ptr (Ptr CRateHelper) -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote)
    -> Ptr CDate -> CDouble -> CString -> CString -> Ptr CString
    -> IO (Ptr CYieldTermStructure)

-- |QuantLibXL: qlPiecewiseYieldCurve
piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> Double -- ^accuracy
  -> Trait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve' = $(ffiConstruct 'piecewiseYieldCurve') c_piecewiseYieldCurve'

-- |Returns a discount factor from the given YieldTermStructure object. QuantLibXL: qlYieldTSDiscount
discount :: YieldTermStructure
  -> Day -- ^d
  -> Bool -- ^extrapolate
  -> IO Double
discount = $(ffiCallX 'discount) c_yieldTSDiscount

foreign import ccall safe "ql.h qlSwapRateHelper1"
  c_swapRateHelper' :: Ptr CQuote -> Ptr CPeriod -> Ptr CCalendar -> CInt
    -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CQuote -> Ptr CPeriod
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CRateHelper)

-- |QuantLibXL: qlSwapRateHelper2
swapRateHelper' :: Quote -- ^rate
  -> Period -- ^tenor
  -> Calendar -- ^calendar
  -> Frequency -- ^fixedFrequency
  -> BusinessDayConvention -- ^fixedConvention
  -> DayCounter -- ^fixedDayCount
  -> IborIndex -- ^iborIndex
  -> Quote -- ^spread
  -> Period -- ^fwdStart
  -> Maybe YieldTermStructure -- ^discountingCurve
  -> IO RateHelper
swapRateHelper' = $(ffiConstruct 'swapRateHelper') c_swapRateHelper'
