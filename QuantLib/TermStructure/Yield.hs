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
foreign import ccall safe "ql.h qlPiecewiseYieldCurve"
  c_piecewiseYieldCurve :: CDate -> CUInt -> Ptr (Ptr CRateHelper)
    -> Ptr CDayCounter -> CUInt -> Ptr (Ptr CQuote) -> Ptr CDate -> CDouble
    -> CString -> CString -> Ptr CString -> IO (Ptr CTermStructure)

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

foreign import ccall safe "ql.h &qlFreeTermStructure"
  p_freeTermStructure :: FunPtr (Ptr CTermStructure -> IO ())

instance Finalizable CTermStructure
  where finalize = p_freeTermStructure

piecewiseYieldCurve :: Day -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Interpolation -> Bootstrap
  -> IO TermStructure
piecewiseYieldCurve refDate instr dayCounter jumps accuracy interp boot =
  withObjects instr
  (\ni i ->
    withObjects quotes
    (\nq q ->
      withDays dates
      (\_ ds ->
        withObject dayCounter
          (\dc ->
            withString2 (show interp) (show boot)
            (\int boo ->
              construct $ c_piecewiseYieldCurve
                            (toQlDate refDate)
                            ni
                            i
                            dc
                            nq
                            q
                            ds
                            (realToFrac accuracy)
                            int
                            boo)))))
  where (quotes, dates) = unzip jumps

-- |(qlPiecewiseYieldCurve)
piecewiseYieldCurve' :: Word -> Calendar -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Bootstrap -> Interpolation
  -> IO TermStructure
piecewiseYieldCurve' = undefined
