{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.CashFlow.CouponPricer
  (
    blackIborCouponPricer
  , setCouponPricer
  , setCouponPricers
  , analyticHaganPricer
  , numericHaganPricer
  )
where

import QuantLib.TermStructure.Trait
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlBlackIborCouponPricer"
  c_blackIborCouponPricer :: Ptr COptionletVolatilityStructure -> Ptr CString
    -> IO (Ptr CFloatingRateCouponPricer)

-- |Black-formula pricer for capped/floored Ibor coupons
blackIborCouponPricer :: OptionletVolatilityStructure -> IO FloatingRateCouponPricer
blackIborCouponPricer = $(ffiCall 'blackIborCouponPricer) c_blackIborCouponPricer

setCouponPricer :: Leg -- ^leg
  -> FloatingRateCouponPricer
  -> IO ()
setCouponPricer = $(ffiCallX 'setCouponPricer) c_setCouponPricer

foreign import ccall safe "ql.h qlQuantLibSetCouponPricer"
  c_setCouponPricer :: Ptr CLeg -> Ptr CFloatingRateCouponPricer -> Ptr CString -> IO ()

setCouponPricers :: Leg -- ^leg
  -> [FloatingRateCouponPricer]
  -> IO ()
setCouponPricers = $(ffiCallX 'setCouponPricers) c_setCouponPricers

foreign import ccall safe "ql.h qlQuantLibSetCouponPricers"
  c_setCouponPricers :: Ptr CLeg -> CUInt -> Ptr (Ptr CFloatingRateCouponPricer) -> Ptr CString -> IO ()

analyticHaganPricer :: SwaptionVolatilityStructure -- ^swaptionVol
  -> YieldCurveModel -- ^modelOfYieldCurve
  -> Quote -- ^meanReversion
  -> IO FloatingRateCouponPricer
analyticHaganPricer = $(ffiCall 'analyticHaganPricer) c_analyticHaganPricer

foreign import ccall safe "ql.h qlAnalyticHaganPricer"
  c_analyticHaganPricer :: Ptr CSwaptionVolatilityStructure -> CInt -> Ptr CQuote -> Ptr CString -> IO (Ptr CFloatingRateCouponPricer)

numericHaganPricer :: SwaptionVolatilityStructure -- ^swaptionVol
  -> YieldCurveModel -- ^modelOfYieldCurve
  -> Quote -- ^meanReversion
  -> Double -- ^lowerLimit
  -> Double -- ^upperLimit
  -> Double -- ^precision
  -> IO FloatingRateCouponPricer
numericHaganPricer = $(ffiCall 'numericHaganPricer) c_numericHaganPricer

foreign import ccall safe "ql.h qlNumericHaganPricer"
  c_numericHaganPricer :: Ptr CSwaptionVolatilityStructure -> CInt -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CFloatingRateCouponPricer)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
