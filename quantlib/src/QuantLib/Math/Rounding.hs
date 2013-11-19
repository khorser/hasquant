{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Math.Rounding
  (
    rounding
  , rounding'
  , applyRounding
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Math.RoundingType(RoundingType)
import QuantLib.Types

-- |default instance
-- Instances built through this constructor don't perform any rounding.
rounding :: IO Rounding
rounding = $(ffiCall 'rounding) c_rounding

foreign import ccall safe "ql.h qlRounding"
  c_rounding :: Ptr CString -> IO (Ptr CRounding)

rounding' :: Int -- ^precision
  -> RoundingType -- ^type
  -> Int -- ^digit
  -> IO Rounding
rounding' = $(ffiCall 'rounding') c_rounding'

foreign import ccall safe "ql.h qlRounding1"
  c_rounding' :: CInt -> CInt -> CInt -> Ptr CString -> IO (Ptr CRounding)

applyRounding :: Rounding -> Double -> Double
applyRounding = $(ffiCallPure 'applyRounding) c_applyRounding

foreign import ccall safe "ql.h qlRound"
  c_applyRounding :: Ptr CRounding -> CDouble -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
