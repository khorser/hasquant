{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Yield
  (
  -- types
    Trait(..)
  -- makers
  , depositRateHelper
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
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Frequency(Frequency)

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

data Trait = Discount | ZeroYield | ForwardRate deriving (Show, Eq)

-- |(qlDepositRateHelper2)
depositRateHelper :: Quote -> Period -> Word -> Calendar
  -> BusinessDayConvention -> Bool -> DayCounter -> IO RateHelper
depositRateHelper = $(ffiConstruct 'depositRateHelper 'c_depositRateHelper)

-- |(qlFixedRateBondHelper)
fixedRateBondHelper :: Quote -> Word -> Double -> Schedule -> [Double]
  -> DayCounter -> BusinessDayConvention -> Double -> Maybe Day
  -> IO RateHelper
fixedRateBondHelper = $(ffiConstruct 'fixedRateBondHelper 'c_fixedRateBondHelper)

foreign import ccall safe "ql.h qlYieldTSDiscount"
  c_yieldTSDiscount :: Ptr CYieldTermStructure -> CDate -> CInt
    -> Ptr CString -> IO CDouble

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

-- |Returns a discount factor from the given YieldTermStructure object (qlYieldTSDiscount)
discount :: YieldTermStructure -> Day -> Bool -> IO Double
discount = $(ffiCallHandleX 'discount 'c_yieldTSDiscount)

foreign import ccall safe "ql.h qlSwapRateHelper1"
  c_swapRateHelper' :: Ptr CQuote -> Ptr CPeriod -> Ptr CCalendar -> CInt
    -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CQuote -> Ptr CPeriod
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CRateHelper)

-- |(qlSwapRateHelper2)
swapRateHelper' :: Quote -> Period -> Calendar -> Frequency
  -> BusinessDayConvention -> DayCounter -> IborIndex -> Quote
  -> Period -> Maybe YieldTermStructure -> IO RateHelper
swapRateHelper' = $(ffiConstruct 'swapRateHelper' 'c_swapRateHelper')
