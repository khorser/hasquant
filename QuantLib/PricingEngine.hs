{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.PricingEngine
  (
  -- types
    CPricingEngine
  , PricingEngine
  -- makers
  , discountingBondEngine
  )
where

import QuantLib.Internal
import QuantLib.TermStructure.Yield(YieldTermStructure, CYieldTermStructure)

data CPricingEngine
type PricingEngine = Object CPricingEngine

foreign import ccall safe "ql.h &qlFreePricingEngine"
  p_freePricingEngine :: FunPtr (Ptr CPricingEngine -> IO ())

instance Finalizable CPricingEngine where
  finalize = p_freePricingEngine

foreign import ccall safe "ql.h qlDiscountingBondEngine"
  c_discountingBondEngine :: Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CPricingEngine)

-- |(qlBondEngine)
discountingBondEngine :: YieldTermStructure -> IO PricingEngine
discountingBondEngine ts = withObject ts (construct . c_discountingBondEngine)
