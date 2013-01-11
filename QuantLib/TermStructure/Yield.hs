{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.TermStructure.Yield
  (
  -- types
    CRateHelper
  , RateHelper
  , Trait(..)
  , CYieldTermStructure
  , YieldTermStructure
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
    -> CString -> CString -> Ptr CString -> IO (Ptr CYieldTermStructure)

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper

data Trait = Discount | ZeroYield | ForwardRate deriving (Show, Eq)

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

data CYieldTermStructure
type YieldTermStructure = Object CYieldTermStructure

foreign import ccall safe "ql.h &qlFreeYieldTermStructure"
  p_freeYieldTermStructure :: FunPtr (Ptr CYieldTermStructure -> IO ())

instance Finalizable CYieldTermStructure
  where finalize = p_freeYieldTermStructure

piecewiseYieldCurve :: Day -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Trait -> Interpolation
  -> IO YieldTermStructure
piecewiseYieldCurve refDate instr dayCounter jumps accuracy trait interp =
  withObjects instr
  (\ni i ->
    withObjects quotes
    (\nq q ->
      withDays dates
      (\_ ds ->
        withObject dayCounter
          (\dc ->
            withString2 (show trait) (show interp)
            (\t int ->
              construct $ c_piecewiseYieldCurve
                            (toQlDate refDate)
                            ni
                            i
                            dc
                            nq
                            q
                            ds
                            (realToFrac accuracy)
                            t
                            int)))))
  where (quotes, dates) = unzip jumps

-- |(qlPiecewiseYieldCurve)
piecewiseYieldCurve' :: Word -> Calendar -> [RateHelper] -> DayCounter
  -> [(Quote, Day)] -> Double -> Trait -> Interpolation
  -> IO YieldTermStructure
piecewiseYieldCurve' = undefined
