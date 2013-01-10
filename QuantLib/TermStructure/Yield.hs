{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.TermStructure.Yield
  (
  -- types
    CRateHelper
  , RateHelper
  , Bootstrap
  , CTermStructure
  , TermStructure
  -- makers
  , depositRateHelper
  , fixedRateBondHelper
  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  )
where

import QuantLib.Internal
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Quote(Quote, CQuote)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Calendar(Calendar, CCalendar)
import QuantLib.Time.DayCounter(DayCounter, CDayCounter)
import QuantLib.Time.Period(Period, CPeriod)
import QuantLib.Time.Schedule(Schedule, CSchedule)

data CRateHelper
type RateHelper = Object CRateHelper

foreign import ccall safe "ql.h &qlFreeRateHelper"
  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())

foreign import ccall safe "ql.h qlDepositRateHelper"
  c_depositRateHelper :: Ptr CQuote -> Ptr CPeriod -> CUInt -> Ptr CCalendar
    -> CInt -> CInt -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlFixedRateBondHelper"
  c_fixedRateBondHelper :: Ptr CQuote -> CUInt -> CDouble -> Ptr CSchedule
  -> CUInt -> Ptr CDouble -> Ptr CDayCounter -> CInt -> CDouble -> CInt
  -> Ptr CString -> IO (Ptr CRateHelper)

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper

data Bootstrap = Discount | ZeroYield | ForwardRate deriving (Show, Eq)

-- |(qlDepositRateHelper2)
depositRateHelper :: Quote -> Period -> Word -> Calendar
  -> BusinessDayConvention -> Bool -> DayCounter -> IO RateHelper
depositRateHelper quote tenor fixDays cal conv eom dayCount =
  withObject4 quote tenor cal dayCount
  (\q t c dc -> construct $ c_depositRateHelper
                            q
                            t
                            (fromIntegral fixDays)
                            c
                            (toQlEnum conv)
                            (fromBool eom)
                            dc)

-- |(qlFixedRateBondHelper)
fixedRateBondHelper :: Quote -> Word -> Double -> Schedule -> [Double]
  -> DayCounter -> BusinessDayConvention -> Double -> Maybe Day
  -> IO RateHelper
fixedRateBondHelper quote settlDays face sched coupons dayCount conv
  redemption issue =
    withObject3 quote sched dayCount
    (\q s dc ->
      withAmounts
      coupons
      (\n cpns -> construct $ c_fixedRateBondHelper
                              q
                              (fromIntegral settlDays)
                              (realToFrac face)
                              s
                              n
                              cpns
                              dc
                              (toQlEnum conv)
                              (realToFrac redemption)
                              (toQlDate issue)))

data CTermStructure
type TermStructure = Object CTermStructure

piecewiseYieldCurve :: Day -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Bootstrap -> Interpolation
  -> IO TermStructure
piecewiseYieldCurve = undefined

-- |(qlPiecewiseYieldCurve)
piecewiseYieldCurve' :: Word -> Calendar -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Bootstrap -> Interpolation
  -> IO TermStructure
piecewiseYieldCurve' = undefined
