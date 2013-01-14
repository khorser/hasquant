{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
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
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer

blackIborCouponPricer :: OptionletVolStructure -> IO FloatingRateCouponPricer
blackIborCouponPricer capletVol = withObject capletVol (construct . c_blackIborCouponPricer)
