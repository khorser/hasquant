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
import QuantLib.Internal.Utils
import QuantLib.Internal.Syntax
import QuantLib.Math.RNGTrait
import QuantLib.Method.BinomialTree
import QuantLib.Method.FdmScheme
import QuantLib.Method.LsmBasisSystemPolynomType
import QuantLib.Types

foreign import ccall safe "ql.h qlDiscountingBondEngine"
  c_discountingBondEngine :: Ptr CYieldTermStructure -> CInt -> Ptr CString
    -> IO (Ptr CPricingEngine)

-- |QuantLibXL: qlBondEngine
discountingBondEngine :: YieldTermStructure -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> IO PricingEngine
discountingBondEngine = $(ffiCall 'discountingBondEngine) c_discountingBondEngine

discountingSwapEngine :: YieldTermStructure -- ^discountCurve
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

analyticBSMHullWhiteEngine :: Double -- ^equityShortRateCorrelation
  -> GeneralizedBlackScholesProcess
  -> HullWhite
  -> IO PricingEngine
analyticBSMHullWhiteEngine = $(ffiCall 'analyticBSMHullWhiteEngine) c_analyticBSMHullWhiteEngine

foreign import ccall safe "ql.h qlAnalyticBSMHullWhiteEngine"
  c_analyticBSMHullWhiteEngine :: CDouble -> Ptr CGeneralizedBlackScholesProcess -> Ptr CHullWhite -> Ptr CString -> IO (Ptr CPricingEngine)

-- |the term structure is only needed when the short-rate model cannot provide one itself.
analyticCapFloorEngine :: AffineModel -- ^model
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
analyticCapFloorEngine = $(ffiCall 'analyticCapFloorEngine) c_analyticCapFloorEngine

foreign import ccall safe "ql.h qlAnalyticCapFloorEngine"
  c_analyticCapFloorEngine :: Ptr CAffineModel -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

analyticGJRGARCHEngine :: GJRGARCHModel -- ^model
  -> IO PricingEngine
analyticGJRGARCHEngine = $(ffiCall 'analyticGJRGARCHEngine) c_analyticGJRGARCHEngine

foreign import ccall safe "ql.h qlAnalyticGJRGARCHEngine"
  c_analyticGJRGARCHEngine :: Ptr CGJRGARCHModel -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonEngine :: HestonModel -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> IO PricingEngine
analyticHestonEngine = $(ffiCall 'analyticHestonEngine) c_analyticHestonEngine

foreign import ccall safe "ql.h qlAnalyticHestonEngine"
  c_analyticHestonEngine :: Ptr CHestonModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonHullWhiteEngine :: HestonModel -- ^hestonModel
  -> HullWhite -- ^hullWhiteModel
  -> Word -- ^integrationOrder
  -> IO PricingEngine
analyticHestonHullWhiteEngine = $(ffiCall 'analyticHestonHullWhiteEngine) c_analyticHestonHullWhiteEngine

foreign import ccall safe "ql.h qlAnalyticHestonHullWhiteEngine"
  c_analyticHestonHullWhiteEngine :: Ptr CHestonModel -> Ptr CHullWhite -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesEngine :: BatesModel -- ^model
  -> Word -- ^integrationOrder
  -> IO PricingEngine
batesEngine = $(ffiCall 'batesEngine) c_batesEngine

foreign import ccall safe "ql.h qlBatesEngine"
  c_batesEngine :: Ptr CBatesModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

fftVanillaEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^logStrikeSpacing
  -> IO PricingEngine
fftVanillaEngine = $(ffiCall 'fftVanillaEngine) c_fftVanillaEngine

foreign import ccall safe "ql.h qlFFTVanillaEngine"
  c_fftVanillaEngine :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

g2SwaptionEngine :: G2 -- ^model
  -> Double -- ^range
  -> Word -- ^intervals
  -> IO PricingEngine
g2SwaptionEngine = $(ffiCall 'g2SwaptionEngine) c_g2SwaptionEngine

foreign import ccall safe "ql.h qlG2SwaptionEngine"
  c_g2SwaptionEngine :: Ptr CG2 -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

jumpDiffusionEngine :: Merton76Process
  -> Double -- ^relativeAccuracy_
  -> Word -- ^maxIterations
  -> IO PricingEngine
jumpDiffusionEngine = $(ffiCall 'jumpDiffusionEngine) c_jumpDiffusionEngine

foreign import ccall safe "ql.h qlJumpDiffusionEngine"
  c_jumpDiffusionEngine :: Ptr CMerton76Process -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

treeCapFloorEngine :: ShortRateModel -- ^model
  -> Word -- ^timeSteps
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeCapFloorEngine = $(ffiCall 'treeCapFloorEngine) c_treeCapFloorEngine

foreign import ccall safe "ql.h qlTreeCapFloorEngine"
  c_treeCapFloorEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeSwaptionEngine :: ShortRateModel
  -> Word -- ^timeSteps
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeSwaptionEngine = $(ffiCall 'treeSwaptionEngine) c_treeSwaptionEngine

foreign import ccall safe "ql.h qlTreeSwaptionEngine"
  c_treeSwaptionEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeVanillaSwapEngine :: ShortRateModel
  -> Word -- ^timeSteps
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeVanillaSwapEngine = $(ffiCall 'treeVanillaSwapEngine) c_treeVanillaSwapEngine

foreign import ccall safe "ql.h qlTreeVanillaSwapEngine"
  c_treeVanillaSwapEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

varianceGammaEngine :: VarianceGammaProcess -> IO PricingEngine
varianceGammaEngine = $(ffiCall 'varianceGammaEngine) c_varianceGammaEngine

foreign import ccall safe "ql.h qlVarianceGammaEngine"
  c_varianceGammaEngine :: Ptr CVarianceGammaProcess -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonEngine' :: HestonModel -- ^model
  -> Word -- ^integrationOrder
  -> IO PricingEngine
analyticHestonEngine' = $(ffiCall 'analyticHestonEngine') c_analyticHestonEngine'

foreign import ccall safe "ql.h qlAnalyticHestonEngine1"
  c_analyticHestonEngine' :: Ptr CHestonModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

analyticHestonHullWhiteEngine' :: HestonModel -- ^model
  -> HullWhite -- ^hullWhiteModel
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> IO PricingEngine
analyticHestonHullWhiteEngine' = $(ffiCall 'analyticHestonHullWhiteEngine') c_analyticHestonHullWhiteEngine'

foreign import ccall safe "ql.h qlAnalyticHestonHullWhiteEngine1"
  c_analyticHestonHullWhiteEngine' :: Ptr CHestonModel -> Ptr CHullWhite -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesEngine' :: BatesModel -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> IO PricingEngine
batesEngine' = $(ffiCall 'batesEngine') c_batesEngine'

foreign import ccall safe "ql.h qlBatesEngine1"
  c_batesEngine' :: Ptr CBatesModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

baroneAdesiWhaleyApproximationEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
baroneAdesiWhaleyApproximationEngine = $(ffiCall 'baroneAdesiWhaleyApproximationEngine) c_baroneAdesiWhaleyApproximationEngine

foreign import ccall safe "ql.h qlBaroneAdesiWhaleyApproximationEngine"
  c_baroneAdesiWhaleyApproximationEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

batesDetJumpEngine' :: BatesDetJumpModel -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> IO PricingEngine
batesDetJumpEngine' = $(ffiCall 'batesDetJumpEngine') c_batesDetJumpEngine'

foreign import ccall safe "ql.h qlBatesDetJumpEngine1"
  c_batesDetJumpEngine' :: Ptr CBatesDetJumpModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDetJumpEngine :: BatesDetJumpModel -- ^model
  -> Word -- ^integrationOrder
  -> IO PricingEngine
batesDetJumpEngine = $(ffiCall 'batesDetJumpEngine) c_batesDetJumpEngine

foreign import ccall safe "ql.h qlBatesDetJumpEngine"
  c_batesDetJumpEngine :: Ptr CBatesDetJumpModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpDetJumpEngine' :: BatesDoubleExpDetJumpModel -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> IO PricingEngine
batesDoubleExpDetJumpEngine' = $(ffiCall 'batesDoubleExpDetJumpEngine') c_batesDoubleExpDetJumpEngine'

foreign import ccall safe "ql.h qlBatesDoubleExpDetJumpEngine1"
  c_batesDoubleExpDetJumpEngine' :: Ptr CBatesDoubleExpDetJumpModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpDetJumpEngine :: BatesDoubleExpDetJumpModel -- ^model
  -> Word -- ^integrationOrder
  -> IO PricingEngine
batesDoubleExpDetJumpEngine = $(ffiCall 'batesDoubleExpDetJumpEngine) c_batesDoubleExpDetJumpEngine

foreign import ccall safe "ql.h qlBatesDoubleExpDetJumpEngine"
  c_batesDoubleExpDetJumpEngine :: Ptr CBatesDoubleExpDetJumpModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpEngine' :: BatesDoubleExpModel -- ^model
  -> Double -- ^relTolerance
  -> Word -- ^maxEvaluations
  -> IO PricingEngine
batesDoubleExpEngine' = $(ffiCall 'batesDoubleExpEngine') c_batesDoubleExpEngine'

foreign import ccall safe "ql.h qlBatesDoubleExpEngine1"
  c_batesDoubleExpEngine' :: Ptr CBatesDoubleExpModel -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

batesDoubleExpEngine :: BatesDoubleExpModel -- ^model
  -> Word -- ^integrationOrder
  -> IO PricingEngine
batesDoubleExpEngine = $(ffiCall 'batesDoubleExpEngine) c_batesDoubleExpEngine

foreign import ccall safe "ql.h qlBatesDoubleExpEngine"
  c_batesDoubleExpEngine :: Ptr CBatesDoubleExpModel -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

bjerksundStenslandApproximationEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
bjerksundStenslandApproximationEngine = $(ffiCall 'bjerksundStenslandApproximationEngine) c_bjerksundStenslandApproximationEngine

foreign import ccall safe "ql.h qlBjerksundStenslandApproximationEngine"
  c_bjerksundStenslandApproximationEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

integralCdsEngine :: Period -- ^integrationStep
  -> DefaultProbabilityTermStructure
  -> Double -- ^recoveryRate
  -> YieldTermStructure -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> IO PricingEngine
integralCdsEngine = $(ffiCall 'integralCdsEngine) c_integralCdsEngine

foreign import ccall safe "ql.h qlIntegralCdsEngine"
  c_integralCdsEngine :: Ptr CPeriod -> Ptr CDefaultProbabilityTermStructure -> CDouble -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

integralEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
integralEngine = $(ffiCall 'integralEngine) c_integralEngine

foreign import ccall safe "ql.h qlIntegralEngine"
  c_integralEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

-- |the term structure is only needed when the short-rate model cannot provide one itself.
jamshidianSwaptionEngine :: OneFactorAffineModel -- ^model
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
jamshidianSwaptionEngine = $(ffiCall 'jamshidianSwaptionEngine) c_jamshidianSwaptionEngine

foreign import ccall safe "ql.h qlJamshidianSwaptionEngine"
  c_jamshidianSwaptionEngine :: Ptr COneFactorAffineModel -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

juQuadraticApproximationEngine :: GeneralizedBlackScholesProcess
  -> IO PricingEngine
juQuadraticApproximationEngine = $(ffiCall 'juQuadraticApproximationEngine) c_juQuadraticApproximationEngine

foreign import ccall safe "ql.h qlJuQuadraticApproximationEngine"
  c_juQuadraticApproximationEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CString -> IO (Ptr CPricingEngine)

kirkEngine :: BlackProcess -- ^process1
  -> BlackProcess -- ^process2
  -> Double -- ^correlation
  -> IO PricingEngine
kirkEngine = $(ffiCall 'kirkEngine) c_kirkEngine

foreign import ccall safe "ql.h qlKirkEngine"
  c_kirkEngine :: Ptr CBlackProcess -> Ptr CBlackProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

midPointCdsEngine :: DefaultProbabilityTermStructure
  -> Double -- ^recoveryRate
  -> YieldTermStructure -- ^discountCurve
  -> Maybe Bool -- ^includeSettlementDateFlows
  -> IO PricingEngine
midPointCdsEngine = $(ffiCall 'midPointCdsEngine) c_midPointCdsEngine

foreign import ccall safe "ql.h qlMidPointCdsEngine"
  c_midPointCdsEngine :: Ptr CDefaultProbabilityTermStructure -> CDouble -> Ptr CYieldTermStructure -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

replicatingVarianceSwapEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^dk
  -> [Double] -- ^callStrikes
  -> [Double] -- ^putStrikes
  -> IO PricingEngine
replicatingVarianceSwapEngine = $(ffiCall 'replicatingVarianceSwapEngine) c_replicatingVarianceSwapEngine

foreign import ccall safe "ql.h qlReplicatingVarianceSwapEngine"
  c_replicatingVarianceSwapEngine :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

stulzEngine :: GeneralizedBlackScholesProcess -- ^process1
  -> GeneralizedBlackScholesProcess -- ^process2
  -> Double -- ^correlation
  -> IO PricingEngine
stulzEngine = $(ffiCall 'stulzEngine) c_stulzEngine

foreign import ccall safe "ql.h qlStulzEngine"
  c_stulzEngine :: Ptr CGeneralizedBlackScholesProcess -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

lfmSwaptionEngine :: LiborForwardModel -- ^model
  -> YieldTermStructure -- ^discountCurve
  -> IO PricingEngine
lfmSwaptionEngine = $(ffiCall 'lfmSwaptionEngine) c_lfmSwaptionEngine

foreign import ccall safe "ql.h qlLfmSwaptionEngine"
  c_lfmSwaptionEngine :: Ptr CLiborForwardModel -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCapFloorEngine' :: ShortRateModel -- ^model
  -> TimeGrid -- ^timeGrid
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeCapFloorEngine' = $(ffiCall 'treeCapFloorEngine') c_treeCapFloorEngine'

foreign import ccall safe "ql.h qlTreeCapFloorEngine1"
  c_treeCapFloorEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeSwaptionEngine' :: ShortRateModel
  -> TimeGrid -- ^timeGrid
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeSwaptionEngine' = $(ffiCall 'treeSwaptionEngine') c_treeSwaptionEngine'

foreign import ccall safe "ql.h qlTreeSwaptionEngine1"
  c_treeSwaptionEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeVanillaSwapEngine' :: ShortRateModel
  -> TimeGrid -- ^timeGrid
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeVanillaSwapEngine' = $(ffiCall 'treeVanillaSwapEngine') c_treeVanillaSwapEngine'

foreign import ccall safe "ql.h qlTreeVanillaSwapEngine1"
  c_treeVanillaSwapEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

fdG2SwaptionEngine :: G2
  -> Word -- tGrid
  -> Word -- xGrid
  -> Word -- yGrid
  -> Word -- dampingSpecs
  -> Double -- invEps
  -> FdmSchemeDesc
  -> IO PricingEngine
fdG2SwaptionEngine = $(ffiCall 'fdG2SwaptionEngine) c_fdG2SwaptionEngine

foreign import ccall safe "ql.h qlFdG2SwaptionEngine"
  c_fdG2SwaptionEngine :: Ptr CG2 -> CUInt -> CUInt -> CUInt -> CUInt -> CDouble -> Ptr CFdmSchemeDesc -> Ptr CString -> IO (Ptr CPricingEngine)

fdHullWhiteSwaptionEngine :: HullWhite
  -> Word -- tGrid
  -> Word -- xGrid
  -> Word -- dampingSpecs
  -> Double -- invEps
  -> FdmSchemeDesc
  -> IO PricingEngine
fdHullWhiteSwaptionEngine = $(ffiCall 'fdHullWhiteSwaptionEngine) c_fdHullWhiteSwaptionEngine

foreign import ccall safe "ql.h qlFdHullWhiteSwaptionEngine"
  c_fdHullWhiteSwaptionEngine :: Ptr CHullWhite -> CUInt -> CUInt -> CUInt -> CDouble -> Ptr CFdmSchemeDesc -> Ptr CString -> IO (Ptr CPricingEngine)

-- |/NB/ C++ classes Monte Carlo engines are additionally parameterised via statistic template argument
-- Functions below use default value of Statistics
mcHestonHullWhiteEngine :: RNGTrait
  -> HybridHestonHullWhiteProcess -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcHestonHullWhiteEngine = $(ffiCall 'mcHestonHullWhiteEngine) c_mcHestonHullWhiteEngine

foreign import ccall safe "ql.h qlMCHestonHullWhiteEngine1"
  c_mcHestonHullWhiteEngine :: CString -> Ptr CHybridHestonHullWhiteProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcAmericanEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
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
  -> IO PricingEngine
mcAmericanEngine = $(ffiCall 'mcAmericanEngine) c_mcAmericanEngine

foreign import ccall safe "ql.h qlMCAmericanEngine1"
  c_mcAmericanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> CUInt -> CInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcBarrierEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Bool -- ^isBiased
  -> Word -- ^seed
  -> IO PricingEngine
mcBarrierEngine = $(ffiCall 'mcBarrierEngine) c_mcBarrierEngine

foreign import ccall safe "ql.h qlMCBarrierEngine1"
  c_mcBarrierEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDigitalEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDigitalEngine = $(ffiCall 'mcDigitalEngine) c_mcDigitalEngine

foreign import ccall safe "ql.h qlMCDigitalEngine1"
  c_mcDigitalEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteArithmeticAPEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDiscreteArithmeticAPEngine = $(ffiCall 'mcDiscreteArithmeticAPEngine) c_mcDiscreteArithmeticAPEngine

foreign import ccall safe "ql.h qlMCDiscreteArithmeticAPEngine1"
  c_mcDiscreteArithmeticAPEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteArithmeticASEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDiscreteArithmeticASEngine = $(ffiCall 'mcDiscreteArithmeticASEngine) c_mcDiscreteArithmeticASEngine

foreign import ccall safe "ql.h qlMCDiscreteArithmeticASEngine1"
  c_mcDiscreteArithmeticASEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteGeometricAPEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDiscreteGeometricAPEngine = $(ffiCall 'mcDiscreteGeometricAPEngine) c_mcDiscreteGeometricAPEngine

foreign import ccall safe "ql.h qlMCDiscreteGeometricAPEngine1"
  c_mcDiscreteGeometricAPEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcEuropeanEngine = $(ffiCall 'mcEuropeanEngine) c_mcEuropeanEngine

foreign import ccall safe "ql.h qlMCEuropeanEngine1"
  c_mcEuropeanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanGJRGARCHEngine :: RNGTrait
  -> GJRGARCHProcess
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcEuropeanGJRGARCHEngine = $(ffiCall 'mcEuropeanGJRGARCHEngine) c_mcEuropeanGJRGARCHEngine

foreign import ccall safe "ql.h qlMCEuropeanGJRGARCHEngine1"
  c_mcEuropeanGJRGARCHEngine :: CString -> Ptr CGJRGARCHProcess -> CUInt -> CUInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanHestonEngine :: RNGTrait
  -> HestonProcess
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcEuropeanHestonEngine = $(ffiCall 'mcEuropeanHestonEngine) c_mcEuropeanHestonEngine

foreign import ccall safe "ql.h qlMCEuropeanHestonEngine1"
  c_mcEuropeanHestonEngine :: CString -> Ptr CHestonProcess -> CUInt -> CUInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcHullWhiteCapFloorEngine :: RNGTrait
  -> HullWhite -- ^model
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcHullWhiteCapFloorEngine = $(ffiCall 'mcHullWhiteCapFloorEngine) c_mcHullWhiteCapFloorEngine

foreign import ccall safe "ql.h qlMCHullWhiteCapFloorEngine1"
  c_mcHullWhiteCapFloorEngine :: CString -> Ptr CHullWhite -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcPerformanceEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcPerformanceEngine = $(ffiCall 'mcPerformanceEngine) c_mcPerformanceEngine

foreign import ccall safe "ql.h qlMCPerformanceEngine1"
  c_mcPerformanceEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcVarianceSwapEngine :: RNGTrait
  -> GeneralizedBlackScholesProcess -- ^process
  -> Maybe Word -- ^timeSteps
  -> Maybe Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Maybe Word -- ^requiredSamples
  -> Maybe Double -- ^requiredTolerance
  -> Maybe Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcVarianceSwapEngine = $(ffiCall 'mcVarianceSwapEngine) c_mcVarianceSwapEngine

foreign import ccall safe "ql.h qlMCVarianceSwapEngine1"
  c_mcVarianceSwapEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

binomialVanillaEngine :: BinomialTree
  -> GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> IO PricingEngine
binomialVanillaEngine = $(ffiCall 'binomialVanillaEngine) c_binomialVanillaEngine

foreign import ccall safe "ql.h qlBinomialVanillaEngine"
  c_binomialVanillaEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

fdAmericanEngine :: FdmScheme
  -> GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^gridPoints
  -> Bool -- ^timeDependent
  -> IO PricingEngine
fdAmericanEngine = $(ffiCall 'fdAmericanEngine) c_fdAmericanEngine

foreign import ccall safe "ql.h qlFDAmericanEngine"
  c_fdAmericanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

fdBermudanEngine :: FdmScheme
  -> GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^gridPoints
  -> Bool -- ^timeDependent
  -> IO PricingEngine
fdBermudanEngine = $(ffiCall 'fdBermudanEngine) c_fdBermudanEngine

foreign import ccall safe "ql.h qlFDBermudanEngine"
  c_fdBermudanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

fdEuropeanEngine :: FdmScheme
  -> GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^gridPoints
  -> Bool -- ^timeDependent
  -> IO PricingEngine
fdEuropeanEngine = $(ffiCall 'fdEuropeanEngine) c_fdEuropeanEngine

foreign import ccall safe "ql.h qlFDEuropeanEngine"
  c_fdEuropeanEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> Ptr CString -> IO (Ptr CPricingEngine)

binomialConvertibleEngine :: BinomialTree
  -> GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> IO PricingEngine
binomialConvertibleEngine = $(ffiCall 'binomialConvertibleEngine) c_binomialConvertibleEngine

foreign import ccall safe "ql.h qlBinomialConvertibleEngine"
  c_binomialConvertibleEngine :: CString -> Ptr CGeneralizedBlackScholesProcess -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableFixedRateBondEngine' :: CallableBondVolatilityStructure -- ^yieldVolStructure
  -> YieldTermStructure -- ^discountCurve
  -> IO PricingEngine
blackCallableFixedRateBondEngine' = $(ffiCall 'blackCallableFixedRateBondEngine') c_blackCallableFixedRateBondEngine'

foreign import ccall safe "ql.h qlBlackCallableFixedRateBondEngine1"
  c_blackCallableFixedRateBondEngine' :: Ptr CCallableBondVolatilityStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableFixedRateBondEngine :: Quote -- ^fwdYieldVol
  -> YieldTermStructure -- ^discountCurve
  -> IO PricingEngine
blackCallableFixedRateBondEngine = $(ffiCall 'blackCallableFixedRateBondEngine) c_blackCallableFixedRateBondEngine

foreign import ccall safe "ql.h qlBlackCallableFixedRateBondEngine"
  c_blackCallableFixedRateBondEngine :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableZeroCouponBondEngine' :: CallableBondVolatilityStructure -- ^yieldVolStructure
  -> YieldTermStructure -- ^discountCurve
  -> IO PricingEngine
blackCallableZeroCouponBondEngine' = $(ffiCall 'blackCallableZeroCouponBondEngine') c_blackCallableZeroCouponBondEngine'

foreign import ccall safe "ql.h qlBlackCallableZeroCouponBondEngine1"
  c_blackCallableZeroCouponBondEngine' :: Ptr CCallableBondVolatilityStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- |volatility is the quoted fwd yield volatility, not price vol
blackCallableZeroCouponBondEngine :: Quote -- ^fwdYieldVol
  -> YieldTermStructure -- ^discountCurve
  -> IO PricingEngine
blackCallableZeroCouponBondEngine = $(ffiCall 'blackCallableZeroCouponBondEngine) c_blackCallableZeroCouponBondEngine

foreign import ccall safe "ql.h qlBlackCallableZeroCouponBondEngine"
  c_blackCallableZeroCouponBondEngine :: Ptr CQuote -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableFixedRateBondEngine' :: ShortRateModel
  -> TimeGrid -- ^timeGrid
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeCallableFixedRateBondEngine' = $(ffiCall 'treeCallableFixedRateBondEngine') c_treeCallableFixedRateBondEngine'

foreign import ccall safe "ql.h qlTreeCallableFixedRateBondEngine1"
  c_treeCallableFixedRateBondEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableFixedRateBondEngine :: ShortRateModel
  -> Word -- ^timeSteps
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeCallableFixedRateBondEngine = $(ffiCall 'treeCallableFixedRateBondEngine) c_treeCallableFixedRateBondEngine

foreign import ccall safe "ql.h qlTreeCallableFixedRateBondEngine"
  c_treeCallableFixedRateBondEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableZeroCouponBondEngine' :: ShortRateModel -- ^model
  -> TimeGrid -- ^timeGrid
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeCallableZeroCouponBondEngine' = $(ffiCall 'treeCallableZeroCouponBondEngine') c_treeCallableZeroCouponBondEngine'

foreign import ccall safe "ql.h qlTreeCallableZeroCouponBondEngine1"
  c_treeCallableZeroCouponBondEngine' :: Ptr CShortRateModel -> Ptr CTimeGrid -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

treeCallableZeroCouponBondEngine :: ShortRateModel -- ^model
  -> Word -- ^timeSteps
  -> Maybe YieldTermStructure -- ^termStructure
  -> IO PricingEngine
treeCallableZeroCouponBondEngine = $(ffiCall 'treeCallableZeroCouponBondEngine) c_treeCallableZeroCouponBondEngine

foreign import ccall safe "ql.h qlTreeCallableZeroCouponBondEngine"
  c_treeCallableZeroCouponBondEngine :: Ptr CShortRateModel -> CUInt -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CPricingEngine)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
