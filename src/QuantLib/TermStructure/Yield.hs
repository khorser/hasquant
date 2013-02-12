{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.TermStructure.Yield
  (
    depositRateHelper
  , fixedRateBondHelper
  , swapRateHelper'
  , fraRateHelper
  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  , flatForward
  , flatForward'

  , discount
  , discount'
  , zeroRate
  , zeroRate'
  , forwardRate
  , forwardRate'
  , forwardRate''
  )
where

import QuantLib.Compounding
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

flatForward :: Day -- ^referenceDate
  -> Quote -- ^forward
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> IO YieldTermStructure
flatForward = $(ffiConstruct 'flatForward) c_flatForward

foreign import ccall safe "ql.h qlFlatForward"
  c_flatForward :: CDate -> Ptr CQuote -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CYieldTermStructure)

flatForward' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> Quote -- ^forward
  -> DayCounter -- ^dayCounter
  -> Compounding -- ^compounding
  -> Frequency -- ^frequency
  -> IO YieldTermStructure
flatForward' = $(ffiConstruct 'flatForward') c_flatForward'

foreign import ccall safe "ql.h qlFlatForward1"
  c_flatForward' :: CUInt -> Ptr CCalendar -> Ptr CQuote -> Ptr CDayCounter -> CInt -> CInt -> Ptr CString -> IO (Ptr CYieldTermStructure)

-- |The resulting interest rate has the required daycounting rule.
zeroRate :: YieldTermStructure
  -> Day -- ^d
  -> DayCounter -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
zeroRate = $(ffiConstruct 'zeroRate) c_zeroRate

foreign import ccall safe "ql.h qlYieldTermStructureZeroRate"
  c_zeroRate :: Ptr CYieldTermStructure -> CDate -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
forwardRate' :: YieldTermStructure
  -> Day -- ^d
  -> Period -- ^p
  -> DayCounter -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
forwardRate' = $(ffiConstruct 'forwardRate') c_forwardRate'

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate1"
  c_forwardRate' :: Ptr CYieldTermStructure -> CDate -> Ptr CPeriod -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the required day-counting rule.
forwardRate :: YieldTermStructure
  -> Day -- ^d1
  -> Day -- ^d2
  -> DayCounter -- ^resultDayCounter
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
forwardRate = $(ffiConstruct 'forwardRate) c_forwardRate

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate"
  c_forwardRate :: Ptr CYieldTermStructure -> CDate -> CDate -> Ptr CDayCounter -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
forwardRate'' :: YieldTermStructure
  -> YearFraction -- ^t1
  -> YearFraction -- ^t2
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
forwardRate'' = $(ffiConstruct 'forwardRate'') c_forwardRate''

foreign import ccall safe "ql.h qlYieldTermStructureForwardRate2"
  c_forwardRate'' :: Ptr CYieldTermStructure -> CYearFraction -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
zeroRate' :: YieldTermStructure
  -> YearFraction -- ^t
  -> Compounding -- ^comp
  -> Frequency -- ^freq
  -> Bool -- ^extrapolate
  -> IO InterestRate
zeroRate' = $(ffiConstruct 'zeroRate') c_zeroRate'

foreign import ccall safe "ql.h qlYieldTermStructureZeroRate1"
  c_zeroRate' :: Ptr CYieldTermStructure -> CYearFraction -> CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CInterestRate)

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
discount' :: YieldTermStructure
  -> YearFraction -- ^t
  -> Bool -- ^extrapolate
  -> IO Double
discount' = $(ffiCallX 'discount') c_discount'

foreign import ccall safe "ql.h qlYieldTermStructureDiscount1"
  c_discount' :: Ptr CYieldTermStructure -> CYearFraction -> CInt -> Ptr CString -> IO CDouble

fraRateHelper :: Quote -- ^rate
  -> Word -- ^monthsToStart
  -> Word -- ^monthsToEnd
  -> Word -- ^fixingDays
  -> Calendar -- ^calendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> IO RateHelper
fraRateHelper = $(ffiConstruct 'fraRateHelper) c_fraRateHelper

foreign import ccall safe "ql.h qlFraRateHelper"
  c_fraRateHelper :: Ptr CQuote -> CUInt -> CUInt -> CUInt -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)
