{-# LANGUAGE TemplateHaskell #-}
module QuantLib.CashFlow.CouponPricer
  (
  -- makers
    blackIborCouponPricer
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlBlackIborCouponPricer"
  c_blackIborCouponPricer :: Ptr COptionletVolStructure -> Ptr CString
    -> IO (Ptr CFloatingRateCouponPricer)

blackIborCouponPricer :: OptionletVolStructure -> IO FloatingRateCouponPricer
blackIborCouponPricer = $(ffiConstruct 'blackIborCouponPricer 'c_blackIborCouponPricer)
