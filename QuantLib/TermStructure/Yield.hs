{-# LANGUAGE ForeignFunctionInterface #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
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

import Control.Monad(liftM)

import QuantLib.Internal
import QuantLib.Types
import QuantLib.Math.Interpolation(Interpolation)
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Frequency(Frequency)

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

foreign import ccall safe "ql.h &qlFreeYieldTermStructure"
  p_freeYieldTermStructure :: FunPtr (Ptr CYieldTermStructure -> IO ())
foreign import ccall safe "ql.h qlYieldTSDiscount"
  c_yieldTSDiscount :: Ptr CYieldTermStructure -> CDate -> CInt
    -> Ptr CString -> IO CDouble

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

-- |Returns a discount factor from the given YieldTermStructure object (qlYieldTSDiscount)
discount :: YieldTermStructure -> Day -> Bool -> IO Double
discount ts d ex = liftM realToFrac (withObject
                    ts
                    (\t -> handleExceptions
                      $ c_yieldTSDiscount t
                          (toQlDate d)
                          (fromBool ex)))

foreign import ccall safe "ql.h qlSwapRateHelper1"
  c_swapRateHelper' :: Ptr CQuote -> Ptr CPeriod -> Ptr CCalendar -> CInt
    -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CQuote -> Ptr CPeriod
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CRateHelper)

-- |(qlSwapRateHelper2)
swapRateHelper' :: Quote -> Period -> Calendar -> Frequency
  -> BusinessDayConvention -> DayCounter -> IborIndex -> Quote
  -> Period -> Maybe YieldTermStructure -> IO RateHelper
swapRateHelper' rate tenor cal fixedFreq fixedConv fixedDayCount
  index spread fwdStart disc =
    withObject7 rate tenor cal fixedDayCount index spread fwdStart
    (\r t c dc i s f ->
      maybeWithObject disc
      (construct . c_swapRateHelper' r
                                             t
                                             c
                                             (toQlEnum fixedFreq)
                                             (toQlEnum fixedConv)
                                             dc
                                             i
                                             s
                                             f))

