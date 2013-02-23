{-# LANGUAGE TemplateHaskell #-}
module QuantLib.CashFlow.CouponPricer
  (
    blackIborCouponPricer
  )
where

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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
