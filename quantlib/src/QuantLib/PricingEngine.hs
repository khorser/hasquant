{-# LANGUAGE TemplateHaskell #-}
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
  , analyticBSMHullWhiteEngine
  , analyticCapFloorEngine
  , analyticGJRGARCHEngine
  , analyticHestonEngine
  , analyticHestonHullWhiteEngine
  , batesEngine
  , fftVanillaEngine
  , g2SwaptionEngine
  , jumpDiffusionEngine
  , treeCapFloorEngine
  , treeSwaptionEngine
  , treeVanillaSwapEngine
  , varianceGammaEngine
  , analyticHestonEngine'
  , analyticHestonHullWhiteEngine'
  , batesEngine'
  , mcHestonHullWhiteEngine
  , mcAmericanEngine
  , mcBarrierEngine
  , mcDigitalEngine
  , mcDiscreteArithmeticAPEngine
  , mcDiscreteArithmeticASEngine
  , mcDiscreteGeometricAPEngine
  , mcEuropeanEngine
  , mcEuropeanGJRGARCHEngine
  , mcEuropeanHestonEngine
  , mcHullWhiteCapFloorEngine
  , mcPerformanceEngine
  , mcVarianceSwapEngine
  , baroneAdesiWhaleyApproximationEngine
  , batesDetJumpEngine'
  , batesDetJumpEngine
  , batesDoubleExpDetJumpEngine'
  , batesDoubleExpDetJumpEngine
  , batesDoubleExpEngine'
  , batesDoubleExpEngine
  , bjerksundStenslandApproximationEngine
  , integralCdsEngine
  , integralEngine
  , jamshidianSwaptionEngine
  , juQuadraticApproximationEngine
  , kirkEngine
  , midPointCdsEngine
  , replicatingVarianceSwapEngine
  , stulzEngine
  , lfmSwaptionEngine
  , treeCapFloorEngine'
  , treeSwaptionEngine'
  , treeVanillaSwapEngine'

  , fdG2SwaptionEngine
  , fdHullWhiteSwaptionEngine
  , binomialVanillaEngine
  , fdAmericanEngine
  , fdBermudanEngine
  , fdEuropeanEngine

  , binomialConvertibleEngine
  , blackCallableFixedRateBondEngine'
  , blackCallableFixedRateBondEngine
  , blackCallableZeroCouponBondEngine'
  , blackCallableZeroCouponBondEngine
  , treeCallableFixedRateBondEngine'
  , treeCallableFixedRateBondEngine
  , treeCallableZeroCouponBondEngine'
  , treeCallableZeroCouponBondEngine
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Types
import QuantLib.Internal.Syntax
import QuantLib.Math.RNGTrait(RNGTrait)
import QuantLib.Method.BinomialTree(BinomialTree)
import QuantLib.Method.FdmScheme(FdmScheme)
import QuantLib.Method.LsmBasisSystemPolynomType(LsmBasisSystemPolynomType)
import QuantLib.Time.Unit(Unit)
import QuantLib.Types

foreign import ccall safe "ql.h qlDiscountingBondEngine"
  c_discountingBondEngine :: Ptr CYieldTermStructure -> CInt -> Ptr CString
    -> IO (Ptr CPricingEngine)

discountingBondEngine :: YieldTermStructure s -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> QLE s (PricingEngine s)
discountingBondEngine = $(ffiCall 'discountingBondEngine) c_discountingBondEngine

discountingSwapEngine :: YieldTermStructure s -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> Maybe Day -- ^settlementDate
  -> Maybe Day -- ^npvDate
  -> QLE s (PricingEngine s)
discountingSwapEngine = $(ffiCall 'discountingSwapEngine) c_discountingSwapEngine

foreign import ccall safe "ql.h qlDiscountingSwapEngine"
  c_discountingSwapEngine :: Ptr CYieldTermStructure -> CInt -> CDate -> CDate -> Ptr CString -> IO (Ptr CPricingEngine)

analyticBarrierEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticBarrierEngine = $(ffiCall 'analyticBarrierEngine) c_analyticBarrierEngine

foreign import ccall safe "ql.h qlAnalyticBarrierEngine"
  c_analyticBarrierEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticCliquetEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticCliquetEngine = $(ffiCall 'analyticCliquetEngine) c_analyticCliquetEngine

foreign import ccall safe "ql.h qlAnalyticCliquetEngine"
  c_analyticCliquetEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticContinuousFixedLookbackEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticContinuousFixedLookbackEngine = $(ffiCall 'analyticContinuousFixedLookbackEngine) c_analyticContinuousFixedLookbackEngine

foreign import ccall safe "ql.h qlAnalyticContinuousFixedLookbackEngine"
  c_analyticContinuousFixedLookbackEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticContinuousFloatingLookbackEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticContinuousFloatingLookbackEngine = $(ffiCall 'analyticContinuousFloatingLookbackEngine) c_analyticContinuousFloatingLookbackEngine

foreign import ccall safe "ql.h qlAnalyticContinuousFloatingLookbackEngine"
  c_analyticContinuousFloatingLookbackEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticContinuousGeometricAveragePriceAsianEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticContinuousGeometricAveragePriceAsianEngine = $(ffiCall 'analyticContinuousGeometricAveragePriceAsianEngine) c_analyticContinuousGeometricAveragePriceAsianEngine

foreign import ccall safe "ql.h qlAnalyticContinuousGeometricAveragePriceAsianEngine"
  c_analyticContinuousGeometricAveragePriceAsianEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDigitalAmericanEngine :: GeneralizedBlackScholesProcess s
  -> QLE s (PricingEngine s)
analyticDigitalAmericanEngine = $(ffiCall 'analyticDigitalAmericanEngine) c_analyticDigitalAmericanEngine

foreign import ccall safe "ql.h qlAnalyticDigitalAmericanEngine"
  c_analyticDigitalAmericanEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDiscreteGeometricAveragePriceAsianEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticDiscreteGeometricAveragePriceAsianEngine = $(ffiCall 'analyticDiscreteGeometricAveragePriceAsianEngine) c_analyticDiscreteGeometricAveragePriceAsianEngine

foreign import ccall safe "ql.h qlAnalyticDiscreteGeometricAveragePriceAsianEngine"
  c_analyticDiscreteGeometricAveragePriceAsianEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDiscreteGeometricAverageStrikeAsianEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticDiscreteGeometricAverageStrikeAsianEngine = $(ffiCall 'analyticDiscreteGeometricAverageStrikeAsianEngine) c_analyticDiscreteGeometricAverageStrikeAsianEngine

foreign import ccall safe "ql.h qlAnalyticDiscreteGeometricAverageStrikeAsianEngine"
  c_analyticDiscreteGeometricAverageStrikeAsianEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticDividendEuropeanEngine :: GeneralizedBlackScholesProcess s
  -> QLE s (PricingEngine s)
analyticDividendEuropeanEngine = $(ffiCall 'analyticDividendEuropeanEngine) c_analyticDividendEuropeanEngine

foreign import ccall safe "ql.h qlAnalyticDividendEuropeanEngine"
  c_analyticDividendEuropeanEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticEuropeanEngine :: GeneralizedBlackScholesProcess s
  -> QLE s (PricingEngine s)
analyticEuropeanEngine = $(ffiCall 'analyticEuropeanEngine) c_analyticEuropeanEngine

foreign import ccall safe "ql.h qlAnalyticEuropeanEngine"
  c_analyticEuropeanEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticPerformanceEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> QLE s (PricingEngine s)
analyticPerformanceEngine = $(ffiCall 'analyticPerformanceEngine) c_analyticPerformanceEngine

foreign import ccall safe "ql.h qlAnalyticPerformanceEngine"
  c_analyticPerformanceEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

blackCapFloorEngine' :: YieldTermStructure s -- ^discountCurve
  -> OptionletVolatilityStructure s -- ^vol
  -> QLE s (PricingEngine s)
blackCapFloorEngine' = $(ffiCall 'blackCapFloorEngine') c_blackCapFloorEngine'

foreign import ccall safe "ql.h qlBlackCapFloorEngine1"
  c_blackCapFloorEngine' :: Ptr CYieldTermStructure -> Ptr COptionletVolatilityStructure -> Ptr CString -> IO (Ptr CPricingEngine)

blackCapFloorEngine :: YieldTermStructure s -- ^discountCurve
  -> Quote s -- ^vol
  -> DayCounter s -- ^dc
  -> QLE s (PricingEngine s)
blackCapFloorEngine = $(ffiCall 'blackCapFloorEngine) c_blackCapFloorEngine

foreign import ccall safe "ql.h qlBlackCapFloorEngine"
  c_blackCapFloorEngine :: Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CPricingEngine)

blackSwaptionEngine :: YieldTermStructure s -- ^discountCurve
  -> Quote s -- ^vol
  -> DayCounter s -- ^dc
  -> QLE s (PricingEngine s)
blackSwaptionEngine = $(ffiCall 'blackSwaptionEngine) c_blackSwaptionEngine

foreign import ccall safe "ql.h qlBlackSwaptionEngine"
  c_blackSwaptionEngine :: Ptr CYieldTermStructure -> Ptr CQuote -> Ptr CDayCounter -> Ptr CString -> IO (Ptr CPricingEngine)

blackSwaptionEngine' :: YieldTermStructure s -- ^discountCurve
  -> SwaptionVolatilityStructure s -- ^vol
  -> QLE s (PricingEngine s)
blackSwaptionEngine' = $(ffiCall 'blackSwaptionEngine') c_blackSwaptionEngine'

foreign import ccall safe "ql.h qlBlackSwaptionEngine1"
  c_blackSwaptionEngine' :: Ptr CYieldTermStructure -> Ptr CSwaptionVolatilityStructure -> Ptr CString -> IO (Ptr CPricingEngine)

analyticBSMHullWhiteEngine :: Double -- ^equityShortRateCorrelation
  -> GeneralizedBlackScholesProcess s
  -> HullWhite s
  -> QLE s (PricingEngine s)
analyticBSMHullWhiteEngine = $(ffiCall 'analyticBSMHullWhiteEngine) c_analyticBSMHullWhiteEngine

foreign import ccall safe "ql.h qlAnalyticBSMHullWhiteEngine"
  c_analyticBSMHullWhiteEngine :: CDouble -> Ptr CGeneralizedBlackScholesProcess -> Ptr CHullWhite -> Ptr CString -> IO (Ptr CPricingEngine)

-- |the term structure is only needed when the short-rate model cannot provide one itself.
analyticCapFloorEngine :: AffineModel s -- ^model
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
analyticCapFloorEngine = $(ffiCall 'analyticCapFloorEngine) c_analyticCapFloorEngine

foreign import ccall safe "ql.h qlAnalyticCapFloorEngine"
  c_analyticCapFloorEngine :: Ptr CAffineModel -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

analyticGJRGARCHEngine :: GJRGARCHModel s -- ^model
  -> QLE s (PricingEngine s)
analyticGJRGARCHEngine = $(ffiCall 'analyticGJRGARCHEngine) c_analyticGJRGARCHEngine

foreign import ccall safe "ql.h qlAnalyticGJRGARCHEngine"
  c_analyticGJRGARCHEngine :: Ptr CGJRGARCHModel -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonEngine :: HestonModel s -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> QLE s (PricingEngine s)
analyticHestonEngine = $(ffiCall 'analyticHestonEngine) c_analyticHestonEngine

foreign import ccall safe "ql.h qlAnalyticHestonEngine"
  c_analyticHestonEngine :: Ptr CHestonModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonHullWhiteEngine :: HestonModel s -- ^hestonModel
  -> HullWhite s -- ^hullWhiteModel
  -> Word -- ^integrationOrder
  -> QLE s (PricingEngine s)
analyticHestonHullWhiteEngine = $(ffiCall 'analyticHestonHullWhiteEngine) c_analyticHestonHullWhiteEngine

foreign import ccall safe "ql.h qlAnalyticHestonHullWhiteEngine"
  c_analyticHestonHullWhiteEngine :: Ptr CHestonModel -> Ptr CHullWhite -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesEngine :: BatesModel s -- ^model
  -> Word -- ^integrationOrder
  -> QLE s (PricingEngine s)
batesEngine = $(ffiCall 'batesEngine) c_batesEngine

foreign import ccall safe "ql.h qlBatesEngine"
  c_batesEngine :: Ptr CBatesModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

fftVanillaEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> Double -- ^logStrikeSpacing
  -> QLE s (PricingEngine s)
fftVanillaEngine = $(ffiCall 'fftVanillaEngine) c_fftVanillaEngine

foreign import ccall safe "ql.h qlFFTVanillaEngine"
  c_fftVanillaEngine :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

g2SwaptionEngine :: G2 s -- ^model
  -> Double -- ^range
  -> Word -- ^intervals
  -> QLE s (PricingEngine s)
g2SwaptionEngine = $(ffiCall 'g2SwaptionEngine) c_g2SwaptionEngine

foreign import ccall safe "ql.h qlG2SwaptionEngine"
  c_g2SwaptionEngine :: Ptr CG2 -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

jumpDiffusionEngine :: Merton76Process s
  -> Double -- ^relativeAccuracy_
  -> Word -- ^maxIterations
  -> QLE s (PricingEngine s)
jumpDiffusionEngine = $(ffiCall 'jumpDiffusionEngine) c_jumpDiffusionEngine

foreign import ccall safe "ql.h qlJumpDiffusionEngine"
  c_jumpDiffusionEngine :: Ptr CMerton76Process -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

treeCapFloorEngine :: ShortRateModel s -- ^model
  -> Word -- ^timeSteps
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeCapFloorEngine = $(ffiCall 'treeCapFloorEngine) c_treeCapFloorEngine

foreign import ccall safe "ql.h qlTreeCapFloorEngine"
  c_treeCapFloorEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeSwaptionEngine :: ShortRateModel s
  -> Word -- ^timeSteps
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeSwaptionEngine = $(ffiCall 'treeSwaptionEngine) c_treeSwaptionEngine

foreign import ccall safe "ql.h qlTreeSwaptionEngine"
  c_treeSwaptionEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeVanillaSwapEngine :: ShortRateModel s
  -> Word -- ^timeSteps
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeVanillaSwapEngine = $(ffiCall 'treeVanillaSwapEngine) c_treeVanillaSwapEngine

foreign import ccall safe "ql.h qlTreeVanillaSwapEngine"
  c_treeVanillaSwapEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

varianceGammaEngine :: VarianceGammaProcess s -> QLE s (PricingEngine s)
varianceGammaEngine = $(ffiCall 'varianceGammaEngine) c_varianceGammaEngine

foreign import ccall safe "ql.h qlVarianceGammaEngine"
  c_varianceGammaEngine :: Ptr CVarianceGammaProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonEngine' :: HestonModel s -- ^model
  -> Word -- ^integrationOrder
  -> QLE s (PricingEngine s)
analyticHestonEngine' = $(ffiCall 'analyticHestonEngine') c_analyticHestonEngine'

foreign import ccall safe "ql.h qlAnalyticHestonEngine1"
  c_analyticHestonEngine' :: Ptr CHestonModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonHullWhiteEngine' :: HestonModel s -- ^model
  -> HullWhite s -- ^hullWhiteModel
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> QLE s (PricingEngine s)
analyticHestonHullWhiteEngine' = $(ffiCall 'analyticHestonHullWhiteEngine') c_analyticHestonHullWhiteEngine'

foreign import ccall safe "ql.h qlAnalyticHestonHullWhiteEngine1"
  c_analyticHestonHullWhiteEngine' :: Ptr CHestonModel -> Ptr CHullWhite -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesEngine' :: BatesModel s -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> QLE s (PricingEngine s)
batesEngine' = $(ffiCall 'batesEngine') c_batesEngine'

foreign import ccall safe "ql.h qlBatesEngine1"
  c_batesEngine' :: Ptr CBatesModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

baroneAdesiWhaleyApproximationEngine :: GeneralizedBlackScholesProcess s
  -> QLE s (PricingEngine s)
baroneAdesiWhaleyApproximationEngine = $(ffiCall 'baroneAdesiWhaleyApproximationEngine) c_baroneAdesiWhaleyApproximationEngine

foreign import ccall safe "ql.h qlBaroneAdesiWhaleyApproximationEngine"
  c_baroneAdesiWhaleyApproximationEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

batesDetJumpEngine' :: BatesDetJumpModel s -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> QLE s (PricingEngine s)
batesDetJumpEngine' = $(ffiCall 'batesDetJumpEngine') c_batesDetJumpEngine'

foreign import ccall safe "ql.h qlBatesDetJumpEngine1"
  c_batesDetJumpEngine' :: Ptr CBatesDetJumpModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDetJumpEngine :: BatesDetJumpModel s -- ^model
  -> Word -- ^integrationOrder
  -> QLE s (PricingEngine s)
batesDetJumpEngine = $(ffiCall 'batesDetJumpEngine) c_batesDetJumpEngine

foreign import ccall safe "ql.h qlBatesDetJumpEngine"
  c_batesDetJumpEngine :: Ptr CBatesDetJumpModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpDetJumpEngine' :: BatesDoubleExpDetJumpModel s -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> QLE s (PricingEngine s)
batesDoubleExpDetJumpEngine' = $(ffiCall 'batesDoubleExpDetJumpEngine') c_batesDoubleExpDetJumpEngine'

foreign import ccall safe "ql.h qlBatesDoubleExpDetJumpEngine1"
  c_batesDoubleExpDetJumpEngine' :: Ptr CBatesDoubleExpDetJumpModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpDetJumpEngine :: BatesDoubleExpDetJumpModel s -- ^model
  -> Word -- ^integrationOrder
  -> QLE s (PricingEngine s)
batesDoubleExpDetJumpEngine = $(ffiCall 'batesDoubleExpDetJumpEngine) c_batesDoubleExpDetJumpEngine

foreign import ccall safe "ql.h qlBatesDoubleExpDetJumpEngine"
  c_batesDoubleExpDetJumpEngine :: Ptr CBatesDoubleExpDetJumpModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpEngine' :: BatesDoubleExpModel s -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> QLE s (PricingEngine s)
batesDoubleExpEngine' = $(ffiCall 'batesDoubleExpEngine') c_batesDoubleExpEngine'

foreign import ccall safe "ql.h qlBatesDoubleExpEngine1"
  c_batesDoubleExpEngine' :: Ptr CBatesDoubleExpModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpEngine :: BatesDoubleExpModel s -- ^model
  -> Word -- ^integrationOrder
  -> QLE s (PricingEngine s)
batesDoubleExpEngine = $(ffiCall 'batesDoubleExpEngine) c_batesDoubleExpEngine

foreign import ccall safe "ql.h qlBatesDoubleExpEngine"
  c_batesDoubleExpEngine :: Ptr CBatesDoubleExpModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

bjerksundStenslandApproximationEngine :: GeneralizedBlackScholesProcess s
  -> QLE s (PricingEngine s)
bjerksundStenslandApproximationEngine = $(ffiCall 'bjerksundStenslandApproximationEngine) c_bjerksundStenslandApproximationEngine

foreign import ccall safe "ql.h qlBjerksundStenslandApproximationEngine"
  c_bjerksundStenslandApproximationEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

integralCdsEngine :: (Int, Unit) -- ^integrationStep
  -> DefaultProbabilityTermStructure s
  -> Double -- ^recoveryRate
  -> YieldTermStructure s -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> QLE s (PricingEngine s)
integralCdsEngine = $(ffiCall 'integralCdsEngine) c_integralCdsEngine

foreign import ccall safe "ql.h qlIntegralCdsEngine"
  c_integralCdsEngine :: CInt -> CInt -> Ptr CDefaultProbabilityTermStructure -> CDouble -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

integralEngine :: GeneralizedBlackScholesProcess s -> QLE s (PricingEngine s)
integralEngine = $(ffiCall 'integralEngine) c_integralEngine

foreign import ccall safe "ql.h qlIntegralEngine"
  c_integralEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

-- |the term structure is only needed when the short-rate model cannot provide one itself.
jamshidianSwaptionEngine :: OneFactorAffineModel s -- ^model
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
jamshidianSwaptionEngine = $(ffiCall 'jamshidianSwaptionEngine) c_jamshidianSwaptionEngine

foreign import ccall safe "ql.h qlJamshidianSwaptionEngine"
  c_jamshidianSwaptionEngine :: Ptr COneFactorAffineModel -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

juQuadraticApproximationEngine :: GeneralizedBlackScholesProcess s -> QLE s (PricingEngine s)
juQuadraticApproximationEngine = $(ffiCall 'juQuadraticApproximationEngine) c_juQuadraticApproximationEngine

foreign import ccall safe "ql.h qlJuQuadraticApproximationEngine"
  c_juQuadraticApproximationEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

kirkEngine :: BlackProcess s -- ^process1
  -> BlackProcess s -- ^process2
  -> Double -- ^correlation
  -> QLE s (PricingEngine s)
kirkEngine = $(ffiCall 'kirkEngine) c_kirkEngine

foreign import ccall safe "ql.h qlKirkEngine"
  c_kirkEngine :: Ptr CBlackProcess -> Ptr CBlackProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

midPointCdsEngine :: DefaultProbabilityTermStructure s
  -> Double -- ^recoveryRate
  -> YieldTermStructure s -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> QLE s (PricingEngine s)
midPointCdsEngine = $(ffiCall 'midPointCdsEngine) c_midPointCdsEngine

foreign import ccall safe "ql.h qlMidPointCdsEngine"
  c_midPointCdsEngine :: Ptr CDefaultProbabilityTermStructure -> CDouble -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

replicatingVarianceSwapEngine :: GeneralizedBlackScholesProcess s -- ^process
  -> Double -- ^dk
  -> [Double] -- ^callStrikes
  -> [Double] -- ^putStrikes
  -> QLE s (PricingEngine s)
replicatingVarianceSwapEngine = $(ffiCall 'replicatingVarianceSwapEngine) c_replicatingVarianceSwapEngine

foreign import ccall safe "ql.h qlReplicatingVarianceSwapEngine"
  c_replicatingVarianceSwapEngine :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

stulzEngine :: GeneralizedBlackScholesProcess s -- ^process1
  -> GeneralizedBlackScholesProcess s -- ^process2
  -> Double -- ^correlation
  -> QLE s (PricingEngine s)
stulzEngine = $(ffiCall 'stulzEngine) c_stulzEngine

foreign import ccall safe "ql.h qlStulzEngine"
  c_stulzEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

lfmSwaptionEngine :: LiborForwardModel s -- ^model
  -> YieldTermStructure s -- ^discountCurve
  -> QLE s (PricingEngine s)
lfmSwaptionEngine = $(ffiCall 'lfmSwaptionEngine) c_lfmSwaptionEngine

foreign import ccall safe "ql.h qlLfmSwaptionEngine"
  c_lfmSwaptionEngine :: Ptr CLiborForwardModel -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCapFloorEngine' :: ShortRateModel s -- ^model
  -> TimeGrid s -- ^timeGrid
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeCapFloorEngine' = $(ffiCall 'treeCapFloorEngine') c_treeCapFloorEngine'

foreign import ccall safe "ql.h qlTreeCapFloorEngine1"
  c_treeCapFloorEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeSwaptionEngine' :: ShortRateModel s
  -> TimeGrid s -- ^timeGrid
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeSwaptionEngine' = $(ffiCall 'treeSwaptionEngine') c_treeSwaptionEngine'

foreign import ccall safe "ql.h qlTreeSwaptionEngine1"
  c_treeSwaptionEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeVanillaSwapEngine' :: ShortRateModel s
  -> TimeGrid s -- ^timeGrid
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeVanillaSwapEngine' = $(ffiCall 'treeVanillaSwapEngine') c_treeVanillaSwapEngine'

foreign import ccall safe "ql.h qlTreeVanillaSwapEngine1"
  c_treeVanillaSwapEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

fdG2SwaptionEngine :: G2 s
  -> Word -- tGrid
  -> Word -- xGrid
  -> Word -- yGrid
  -> Word -- dampingSpecs
  -> Double -- invEps
  -> FdmSchemeDesc s
  -> QLE s (PricingEngine s)
fdG2SwaptionEngine = $(ffiCall 'fdG2SwaptionEngine) c_fdG2SwaptionEngine

foreign import ccall safe "ql.h qlFdG2SwaptionEngine"
  c_fdG2SwaptionEngine :: Ptr CG2 -> CUInt -> CUInt -> CUInt -> CUInt -> CDouble -> Ptr CFdmSchemeDesc -> Ptr CString -> IO (Ptr CPricingEngine)

fdHullWhiteSwaptionEngine :: HullWhite s
  -> Word -- tGrid
  -> Word -- xGrid
  -> Word -- dampingSpecs
  -> Double -- invEps
  -> FdmSchemeDesc s
  -> QLE s (PricingEngine s)
fdHullWhiteSwaptionEngine = $(ffiCall 'fdHullWhiteSwaptionEngine) c_fdHullWhiteSwaptionEngine

foreign import ccall safe "ql.h qlFdHullWhiteSwaptionEngine"
  c_fdHullWhiteSwaptionEngine :: Ptr CHullWhite -> CUInt -> CUInt -> CUInt -> CDouble -> Ptr CFdmSchemeDesc -> Ptr CString -> IO (Ptr CPricingEngine)

-- |/NB/ C++ classes Monte Carlo engines are additionally parameterised via statistic template argument
-- Functions below use default value of Statistics
mcHestonHullWhiteEngine :: RNGTrait
  -> HybridHestonHullWhiteProcess s -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcHestonHullWhiteEngine = $(ffiCall 'mcHestonHullWhiteEngine) c_mcHestonHullWhiteEngine

foreign import ccall safe "ql.h qlMCHestonHullWhiteEngine1"
  c_mcHestonHullWhiteEngine :: CString -> Ptr CHybridHestonHullWhiteProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcAmericanEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> Word -- ^polynomOrder
  -> LsmBasisSystemPolynomType -- ^polynomType
  -> Maybe Word -- ^nCalibrationSamples
  -> QLE s (PricingEngine s)
mcAmericanEngine = $(ffiCall 'mcAmericanEngine) c_mcAmericanEngine

foreign import ccall safe "ql.h qlMCAmericanEngine1"
  c_mcAmericanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> CUInt -> CInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcBarrierEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Bool -- ^isBiased
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcBarrierEngine = $(ffiCall 'mcBarrierEngine) c_mcBarrierEngine

foreign import ccall safe "ql.h qlMCBarrierEngine1"
  c_mcBarrierEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDigitalEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcDigitalEngine = $(ffiCall 'mcDigitalEngine) c_mcDigitalEngine

foreign import ccall safe "ql.h qlMCDigitalEngine1"
  c_mcDigitalEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteArithmeticAPEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcDiscreteArithmeticAPEngine = $(ffiCall 'mcDiscreteArithmeticAPEngine) c_mcDiscreteArithmeticAPEngine

foreign import ccall safe "ql.h qlMCDiscreteArithmeticAPEngine1"
  c_mcDiscreteArithmeticAPEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteArithmeticASEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcDiscreteArithmeticASEngine = $(ffiCall 'mcDiscreteArithmeticASEngine) c_mcDiscreteArithmeticASEngine

foreign import ccall safe "ql.h qlMCDiscreteArithmeticASEngine1"
  c_mcDiscreteArithmeticASEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteGeometricAPEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcDiscreteGeometricAPEngine = $(ffiCall 'mcDiscreteGeometricAPEngine) c_mcDiscreteGeometricAPEngine

foreign import ccall safe "ql.h qlMCDiscreteGeometricAPEngine1"
  c_mcDiscreteGeometricAPEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcEuropeanEngine = $(ffiCall 'mcEuropeanEngine) c_mcEuropeanEngine

foreign import ccall safe "ql.h qlMCEuropeanEngine1"
  c_mcEuropeanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanGJRGARCHEngine :: RNGTrait
  -> GJRGARCHProcess s
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcEuropeanGJRGARCHEngine = $(ffiCall 'mcEuropeanGJRGARCHEngine) c_mcEuropeanGJRGARCHEngine

foreign import ccall safe "ql.h qlMCEuropeanGJRGARCHEngine1"
  c_mcEuropeanGJRGARCHEngine :: CString -> Ptr CGJRGARCHProcess -> CUInt -> CUInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanHestonEngine :: RNGTrait
  -> HestonProcess s
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcEuropeanHestonEngine = $(ffiCall 'mcEuropeanHestonEngine) c_mcEuropeanHestonEngine

foreign import ccall safe "ql.h qlMCEuropeanHestonEngine1"
  c_mcEuropeanHestonEngine :: CString -> Ptr CHestonProcess -> CUInt -> CUInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcHullWhiteCapFloorEngine :: RNGTrait
  -> HullWhite s -- ^model
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcHullWhiteCapFloorEngine = $(ffiCall 'mcHullWhiteCapFloorEngine) c_mcHullWhiteCapFloorEngine

foreign import ccall safe "ql.h qlMCHullWhiteCapFloorEngine1"
  c_mcHullWhiteCapFloorEngine :: CString -> Ptr CHullWhite -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcPerformanceEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcPerformanceEngine = $(ffiCall 'mcPerformanceEngine) c_mcPerformanceEngine

foreign import ccall safe "ql.h qlMCPerformanceEngine1"
  c_mcPerformanceEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcVarianceSwapEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> QLE s (PricingEngine s)
mcVarianceSwapEngine = $(ffiCall 'mcVarianceSwapEngine) c_mcVarianceSwapEngine

foreign import ccall safe "ql.h qlMCVarianceSwapEngine1"
  c_mcVarianceSwapEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

binomialVanillaEngine :: BinomialTree
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Word -- ^timeSteps
  -> QLE s (PricingEngine s)
binomialVanillaEngine = $(ffiCall 'binomialVanillaEngine) c_binomialVanillaEngine

foreign import ccall safe "ql.h qlBinomialVanillaEngine"
  c_binomialVanillaEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

fdAmericanEngine :: FdmScheme
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^gridPoints
  -> Bool -- ^timeDependent
  -> QLE s (PricingEngine s)
fdAmericanEngine = $(ffiCall 'fdAmericanEngine) c_fdAmericanEngine

foreign import ccall safe "ql.h qlFDAmericanEngine"
  c_fdAmericanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

fdBermudanEngine :: FdmScheme
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^gridPoints
  -> Bool -- ^timeDependent
  -> QLE s (PricingEngine s)
fdBermudanEngine = $(ffiCall 'fdBermudanEngine) c_fdBermudanEngine

foreign import ccall safe "ql.h qlFDBermudanEngine"
  c_fdBermudanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

fdEuropeanEngine :: FdmScheme
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^gridPoints
  -> Bool -- ^timeDependent
  -> QLE s (PricingEngine s)
fdEuropeanEngine = $(ffiCall 'fdEuropeanEngine) c_fdEuropeanEngine

foreign import ccall safe "ql.h qlFDEuropeanEngine"
  c_fdEuropeanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

binomialConvertibleEngine :: BinomialTree
  -> GeneralizedBlackScholesProcess s -- ^process
  -> Word -- ^timeSteps
  -> QLE s (PricingEngine s)
binomialConvertibleEngine = $(ffiCall 'binomialConvertibleEngine) c_binomialConvertibleEngine

foreign import ccall safe "ql.h qlBinomialConvertibleEngine"
  c_binomialConvertibleEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableFixedRateBondEngine' :: CallableBondVolatilityStructure s -- ^yieldVolStructure
  -> YieldTermStructure s -- ^discountCurve
  -> QLE s (PricingEngine s)
blackCallableFixedRateBondEngine' = $(ffiCall 'blackCallableFixedRateBondEngine') c_blackCallableFixedRateBondEngine'

foreign import ccall safe "ql.h qlBlackCallableFixedRateBondEngine1"
  c_blackCallableFixedRateBondEngine' :: Ptr CCallableBondVolatilityStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableFixedRateBondEngine :: Quote s -- ^fwdYieldVol
  -> YieldTermStructure s -- ^discountCurve
  -> QLE s (PricingEngine s)
blackCallableFixedRateBondEngine = $(ffiCall 'blackCallableFixedRateBondEngine) c_blackCallableFixedRateBondEngine

foreign import ccall safe "ql.h qlBlackCallableFixedRateBondEngine"
  c_blackCallableFixedRateBondEngine :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableZeroCouponBondEngine' :: CallableBondVolatilityStructure s -- ^yieldVolStructure
  -> YieldTermStructure s -- ^discountCurve
  -> QLE s (PricingEngine s)
blackCallableZeroCouponBondEngine' = $(ffiCall 'blackCallableZeroCouponBondEngine') c_blackCallableZeroCouponBondEngine'

foreign import ccall safe "ql.h qlBlackCallableZeroCouponBondEngine1"
  c_blackCallableZeroCouponBondEngine' :: Ptr CCallableBondVolatilityStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableZeroCouponBondEngine :: Quote s -- ^fwdYieldVol
  -> YieldTermStructure s -- ^discountCurve
  -> QLE s (PricingEngine s)
blackCallableZeroCouponBondEngine = $(ffiCall 'blackCallableZeroCouponBondEngine) c_blackCallableZeroCouponBondEngine

foreign import ccall safe "ql.h qlBlackCallableZeroCouponBondEngine"
  c_blackCallableZeroCouponBondEngine :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableFixedRateBondEngine' :: ShortRateModel s
  -> TimeGrid s -- ^timeGrid
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeCallableFixedRateBondEngine' = $(ffiCall 'treeCallableFixedRateBondEngine') c_treeCallableFixedRateBondEngine'

foreign import ccall safe "ql.h qlTreeCallableFixedRateBondEngine1"
  c_treeCallableFixedRateBondEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableFixedRateBondEngine :: ShortRateModel s
  -> Word -- ^timeSteps
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeCallableFixedRateBondEngine = $(ffiCall 'treeCallableFixedRateBondEngine) c_treeCallableFixedRateBondEngine

foreign import ccall safe "ql.h qlTreeCallableFixedRateBondEngine"
  c_treeCallableFixedRateBondEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableZeroCouponBondEngine' :: ShortRateModel s -- ^model
  -> TimeGrid s -- ^timeGrid
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeCallableZeroCouponBondEngine' = $(ffiCall 'treeCallableZeroCouponBondEngine') c_treeCallableZeroCouponBondEngine'

foreign import ccall safe "ql.h qlTreeCallableZeroCouponBondEngine1"
  c_treeCallableZeroCouponBondEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableZeroCouponBondEngine :: ShortRateModel s -- ^model
  -> Word -- ^timeSteps
  -> Maybe (YieldTermStructure s) -- ^termStructure
  -> QLE s (PricingEngine s)
treeCallableZeroCouponBondEngine = $(ffiCall 'treeCallableZeroCouponBondEngine) c_treeCallableZeroCouponBondEngine

foreign import ccall safe "ql.h qlTreeCallableZeroCouponBondEngine"
  c_treeCallableZeroCouponBondEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
