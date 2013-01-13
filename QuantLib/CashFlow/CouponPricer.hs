{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.CashFlow.CouponPricer
  (
  -- types
    CFloatingRateCouponPricer
  , FloatingRateCouponPricer
  -- makers
  , blackIborCouponPricer
  )
where

import QuantLib.Internal
import QuantLib.TermStructure.Volatility(OptionletVolStructure, COptionletVolStructure)

data CFloatingRateCouponPricer
type FloatingRateCouponPricer = Object CFloatingRateCouponPricer

foreign import ccall safe "ql.h qlBlackIborCouponPricer"
  c_blackIborCouponPricer :: Ptr COptionletVolStructure -> Ptr CString
    -> IO (Ptr CFloatingRateCouponPricer)
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer

blackIborCouponPricer :: OptionletVolStructure -> IO FloatingRateCouponPricer
blackIborCouponPricer capletVol = withObject capletVol (construct . c_blackIborCouponPricer)
