{-# LANGUAGE TemplateHaskell #-}
module QuantLib.PricingEngine
  (
    discountingBondEngine
  , discountingSwapEngine
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Syntax
import QuantLib.Types

foreign import ccall safe "ql.h qlDiscountingBondEngine"
  c_discountingBondEngine :: Ptr CYieldTermStructure -> CInt -> Ptr CString
    -> IO (Ptr CPricingEngine)

-- |QuantLibXL: qlBondEngine
discountingBondEngine :: YieldTermStructure -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> IO PricingEngine
discountingBondEngine = $(ffiCall 'discountingBondEngine) c_discountingBondEngine

discountingSwapEngine :: Maybe YieldTermStructure -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> IO PricingEngine
discountingSwapEngine = $(ffiCall 'discountingSwapEngine) c_discountingSwapEngine

foreign import ccall safe "ql.h qlDiscountingSwapEngine"
  c_discountingSwapEngine :: Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CString -> IO (Ptr CPricingEngine)
