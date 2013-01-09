{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.TermStructure.Yield
  (
  -- objects
    CRateHelper
  , RateHelper
  , Bootstrap
  )
where

import QuantLib.Internal

data CRateHelper
type RateHelper = Object CRateHelper

foreign import ccall safe "ql.h &qlFreeRateHelper"
  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper

data Bootstrap = Discount | ZeroYield | ForwardRate deriving (Show, Eq)
