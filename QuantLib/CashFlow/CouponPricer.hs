{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.CashFlow.CouponPricer
  (
  -- makers
    blackIborCouponPricer
  )
where

import QuantLib.Internal
import QuantLib.Types

foreign import ccall safe "ql.h qlBlackIborCouponPricer"
  c_blackIborCouponPricer :: Ptr COptionletVolStructure -> Ptr CString
    -> IO (Ptr CFloatingRateCouponPricer)

blackIborCouponPricer :: OptionletVolStructure -> IO FloatingRateCouponPricer
blackIborCouponPricer capletVol = withObject capletVol (construct . c_blackIborCouponPricer)
