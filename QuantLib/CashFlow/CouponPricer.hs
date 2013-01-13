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
import QuantLib.TermStructure.Volatility(OptionletVolStructure)

data CFloatingRateCouponPricer
type FloatingRateCouponPricer = Object CFloatingRateCouponPricer

--foreign import ccall safe "ql.h qlLeg"
--  c_leg :: CUInt -> Ptr CDouble -> Ptr CDate -> Ptr CString -> IO (Ptr CLeg)
--foreign import ccall safe "ql.h &qlFreeLeg"
--  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

--instance Finalizable CLeg where
--  finalize = p_freeLeg

blackIborCouponPricer :: OptionletVolStructure -> IO FloatingRateCouponPricer
blackIborCouponPricer _capletVol = undefined
