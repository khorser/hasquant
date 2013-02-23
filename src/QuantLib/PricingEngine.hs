{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.PricingEngine
  (
    discountingBondEngine
  , discountingSwapEngine

  , analyticBarrierEngine
  , analyticCliquetEngine
  , analyticContinuousFixedLookbackEngine
  , analyticContinuousFloatingLookbackEngine
  , analyticContinuousGeometricAveragePriceAsianEngine
  , analyticDigitalAmericanEngine
  , analyticDiscreteGeometricAveragePriceAsianEngine
  , analyticDiscreteGeometricAverageStrikeAsianEngine
  , analyticDividendEuropeanEngine
  , analyticEuropeanEngine
  , analyticPerformanceEngine
  , blackCapFloorEngine'
  , blackCapFloorEngine
  , blackSwaptionEngine
  , blackSwaptionEngine'
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

analyticBarrierEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticBarrierEngine = $(ffiCall 'analyticBarrierEngine) c_analyticBarrierEngine

foreign import ccall safe "ql.h qlAnalyticBarrierEngine"
  c_analyticBarrierEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticCliquetEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticCliquetEngine = $(ffiCall 'analyticCliquetEngine) c_analyticCliquetEngine

foreign import ccall safe "ql.h qlAnalyticCliquetEngine"
  c_analyticCliquetEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticContinuousFixedLookbackEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticContinuousFixedLookbackEngine = $(ffiCall 'analyticContinuousFixedLookbackEngine) c_analyticContinuousFixedLookbackEngine

foreign import ccall safe "ql.h qlAnalyticContinuousFixedLookbackEngine"
  c_analyticContinuousFixedLookbackEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticContinuousFloatingLookbackEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticContinuousFloatingLookbackEngine = $(ffiCall 'analyticContinuousFloatingLookbackEngine) c_analyticContinuousFloatingLookbackEngine

foreign import ccall safe "ql.h qlAnalyticContinuousFloatingLookbackEngine"
  c_analyticContinuousFloatingLookbackEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticContinuousGeometricAveragePriceAsianEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticContinuousGeometricAveragePriceAsianEngine = $(ffiCall 'analyticContinuousGeometricAveragePriceAsianEngine) c_analyticContinuousGeometricAveragePriceAsianEngine

foreign import ccall safe "ql.h qlAnalyticContinuousGeometricAveragePriceAsianEngine"
  c_analyticContinuousGeometricAveragePriceAsianEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDigitalAmericanEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
analyticDigitalAmericanEngine = $(ffiCall 'analyticDigitalAmericanEngine) c_analyticDigitalAmericanEngine

foreign import ccall safe "ql.h qlAnalyticDigitalAmericanEngine"
  c_analyticDigitalAmericanEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDiscreteGeometricAveragePriceAsianEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticDiscreteGeometricAveragePriceAsianEngine = $(ffiCall 'analyticDiscreteGeometricAveragePriceAsianEngine) c_analyticDiscreteGeometricAveragePriceAsianEngine

foreign import ccall safe "ql.h qlAnalyticDiscreteGeometricAveragePriceAsianEngine"
  c_analyticDiscreteGeometricAveragePriceAsianEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDiscreteGeometricAverageStrikeAsianEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticDiscreteGeometricAverageStrikeAsianEngine = $(ffiCall 'analyticDiscreteGeometricAverageStrikeAsianEngine) c_analyticDiscreteGeometricAverageStrikeAsianEngine

foreign import ccall safe "ql.h qlAnalyticDiscreteGeometricAverageStrikeAsianEngine"
  c_analyticDiscreteGeometricAverageStrikeAsianEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDividendEuropeanEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
analyticDividendEuropeanEngine = $(ffiCall 'analyticDividendEuropeanEngine) c_analyticDividendEuropeanEngine

foreign import ccall safe "ql.h qlAnalyticDividendEuropeanEngine"
  c_analyticDividendEuropeanEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticEuropeanEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
analyticEuropeanEngine = $(ffiCall 'analyticEuropeanEngine) c_analyticEuropeanEngine

foreign import ccall safe "ql.h qlAnalyticEuropeanEngine"
  c_analyticEuropeanEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticPerformanceEngine :: GeneralizedBlackScholesProcess -- ^process
  -> IO PricingEngine
analyticPerformanceEngine = $(ffiCall 'analyticPerformanceEngine) c_analyticPerformanceEngine

foreign import ccall safe "ql.h qlAnalyticPerformanceEngine"
  c_analyticPerformanceEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

blackCapFloorEngine' :: YieldTermStructure -- ^discountCurve
  -> OptionletVolatilityStructure -- ^vol
  -> IO PricingEngine
blackCapFloorEngine' = $(ffiCall 'blackCapFloorEngine') c_blackCapFloorEngine'

foreign import ccall safe "ql.h qlBlackCapFloorEngine1"
  c_blackCapFloorEngine' :: Ptr CYieldTermStructure -> Ptr COptionletVolatilityStructure -> Ptr CString -> IO (Ptr CPricingEngine)

blackCapFloorEngine :: YieldTermStructure -- ^discountCurve
  -> Quote -- ^vol
  -> DayCounter -- ^dc
  -> IO PricingEngine
blackCapFloorEngine = $(ffiCall 'blackCapFloorEngine) c_blackCapFloorEngine

foreign import ccall safe "ql.h qlBlackCapFloorEngine"
  c_blackCapFloorEngine :: Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CPricingEngine)

blackSwaptionEngine :: YieldTermStructure -- ^discountCurve
  -> Quote -- ^vol
  -> DayCounter -- ^dc
  -> IO PricingEngine
blackSwaptionEngine = $(ffiCall 'blackSwaptionEngine) c_blackSwaptionEngine

foreign import ccall safe "ql.h qlBlackSwaptionEngine"
  c_blackSwaptionEngine :: Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CPricingEngine)

blackSwaptionEngine' :: YieldTermStructure -- ^discountCurve
  -> SwaptionVolatilityStructure -- ^vol
  -> IO PricingEngine
blackSwaptionEngine' = $(ffiCall 'blackSwaptionEngine') c_blackSwaptionEngine'

foreign import ccall safe "ql.h qlBlackSwaptionEngine1"
  c_blackSwaptionEngine' :: Ptr CYieldTermStructure -> Ptr CSwaptionVolatilityStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
