module QuantLib.PricingEngine
  (
  -- makers
    discountingBondEngine
  )
where

import QuantLib.Internal
import QuantLib.Types

foreign import ccall safe "ql.h qlDiscountingBondEngine"
  c_discountingBondEngine :: Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CPricingEngine)

-- |(qlBondEngine)
discountingBondEngine :: YieldTermStructure -> IO PricingEngine
discountingBondEngine ts = withObject ts (construct . c_discountingBondEngine)
