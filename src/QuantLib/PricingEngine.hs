{-# LANGUAGE TemplateHaskell #-}
module QuantLib.PricingEngine
  (
  -- makers
    discountingBondEngine
  )
where

import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Syntax
import QuantLib.Types

foreign import ccall safe "ql.h qlDiscountingBondEngine"
  c_discountingBondEngine :: Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CPricingEngine)

-- |(qlBondEngine)
discountingBondEngine :: YieldTermStructure -> IO PricingEngine
discountingBondEngine = $(ffiConstruct 'discountingBondEngine) c_discountingBondEngine
