{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Swap
  (
    swap'
  )

where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

-- |Multi leg constructor.
swap' :: [Leg] -- ^legs
  -> [Bool] -- ^payer
  -> IO Swap
swap' = $(ffiConstruct 'swap') c_swap'

foreign import ccall safe "ql.h qlSwap1"
  c_swap' :: CUInt -> Ptr (Ptr CLeg) -> CUInt -> Ptr CInt -> Ptr CString -> IO (Ptr CSwap)
