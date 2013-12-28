{-# LANGUAGE TemplateHaskell #-}
module QuantLib.CashFlow.CouponPricer
  (
    blackIborCouponPricer
  , setCouponPricer
  , setCouponPricers
  , analyticHaganPricer
  , numericHaganPricer
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.TermStructure.Trait(YieldCurveModel)
import QuantLib.Types

foreign import ccall safe "ql.h qlBlackIborCouponPricer"
  c_blackIborCouponPricer :: Ptr COptionletVolatilityStructure -> Ptr CString
    -> IO (Ptr CFloatingRateCouponPricer)

-- |Black-formula pricer for capped/floored Ibor coupons
blackIborCouponPricer :: OptionletVolatilityStructure s -> QLE s (FloatingRateCouponPricer s)
blackIborCouponPricer = $(ffiCall 'blackIborCouponPricer) c_blackIborCouponPricer

setCouponPricer :: Leg s -- ^leg
  -> FloatingRateCouponPricer s
  -> QLE s ()
setCouponPricer = $(ffiCallX 'setCouponPricer) c_setCouponPricer

foreign import ccall safe "ql.h qlQuantLibSetCouponPricer"
  c_setCouponPricer :: Ptr CLeg -> Ptr CFloatingRateCouponPricer -> Ptr CString -> IO ()

setCouponPricers :: Leg s -- ^leg
  -> [FloatingRateCouponPricer s]
  -> QLE s ()
setCouponPricers = $(ffiCallX 'setCouponPricers) c_setCouponPricers

foreign import ccall safe "ql.h qlQuantLibSetCouponPricers"
  c_setCouponPricers :: Ptr CLeg -> CUInt -> Ptr (Ptr CFloatingRateCouponPricer) -> Ptr CString -> IO ()

analyticHaganPricer :: SwaptionVolatilityStructure s -- ^swaptionVol
  -> YieldCurveModel -- ^modelOfYieldCurve
  -> Quote s -- ^meanReversion
  -> QLE s (FloatingRateCouponPricer s)
analyticHaganPricer = $(ffiCall 'analyticHaganPricer) c_analyticHaganPricer

foreign import ccall safe "ql.h qlAnalyticHaganPricer"
  c_analyticHaganPricer :: Ptr CSwaptionVolatilityStructure -> CInt -> Ptr CQuote -> Ptr CString -> IO (Ptr CFloatingRateCouponPricer)

numericHaganPricer :: SwaptionVolatilityStructure s -- ^swaptionVol
  -> YieldCurveModel -- ^modelOfYieldCurve
  -> Quote s -- ^meanReversion
  -> Double -- ^lowerLimit
  -> Double -- ^upperLimit
  -> Double -- ^precision
  -> QLE s (FloatingRateCouponPricer s)
numericHaganPricer = $(ffiCall 'numericHaganPricer) c_numericHaganPricer

foreign import ccall safe "ql.h qlNumericHaganPricer"
  c_numericHaganPricer :: Ptr CSwaptionVolatilityStructure -> CInt -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CFloatingRateCouponPricer)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
