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
  , fFTVanillaEngine
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
  , mcVarianceSwapEngine
  , midPointCdsEngine
  , replicatingVarianceSwapEngine
  , stulzEngine
  , lfmSwaptionEngine

  , alpha
  , beta
  , blackCalculator'
  , blackCalculator
  , delta
  , deltaForward
  , dividendRho
  , elasticity
  , elasticityForward
  , gamma
  , gammaForward
  , itmAssetProbability
  , itmCashProbability
  , rho
  , strikeSensitivity
  , theta
  , thetaPerDay
  , value
  , vega
  , blackScholesCalculator'
  , blackScholesCalculator
  , delta'
  , elasticity'
  , gamma'
  , theta'
  , thetaPerDay'
  , blackFormula'
  , blackFormula
  , blackFormulaCashItmProbability'
  , blackFormulaCashItmProbability
  , blackFormulaImpliedStdDev'
  , blackFormulaImpliedStdDev
  , blackFormulaImpliedStdDevApproximation'
  , blackFormulaImpliedStdDevApproximation
  , blackFormulaStdDevDerivative'
  , blackFormulaStdDevDerivative
  , blackFormulaVolDerivative
  , blackScholesTheta
  , bachelierBlackFormula'
  , bachelierBlackFormula
  , defaultThetaPerDay
  )
where

import QuantLib.Instrument.OptionType
import QuantLib.Internal.Date
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Internal.Syntax
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

alpha :: BlackCalculator -> IO Double
alpha = $(ffiCallX 'alpha) c_alpha

foreign import ccall safe "ql.h qlBlackCalculatorAlpha"
  c_alpha :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

beta :: BlackCalculator -> IO Double
beta = $(ffiCallX 'beta) c_beta

foreign import ccall safe "ql.h qlBlackCalculatorBeta"
  c_beta :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

blackCalculator' :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> IO BlackCalculator
blackCalculator' = $(ffiCall 'blackCalculator') c_blackCalculator'

foreign import ccall safe "ql.h qlBlackCalculator1"
  c_blackCalculator' :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackCalculator)

blackCalculator :: StrikedTypePayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> IO BlackCalculator
blackCalculator = $(ffiCall 'blackCalculator) c_blackCalculator

foreign import ccall safe "ql.h qlBlackCalculator"
  c_blackCalculator :: Ptr CStrikedTypePayoff -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackCalculator)

-- |Sensitivity to change in the underlying spot price.
delta :: BlackCalculator
  -> Double -- ^spot
  -> IO Double
delta = $(ffiCallX 'delta) c_delta

foreign import ccall safe "ql.h qlBlackCalculatorDelta"
  c_delta :: Ptr CBlackCalculator -> CDouble -> Ptr CString -> IO CDouble

-- |Sensitivity to change in the underlying forward price.
deltaForward :: BlackCalculator -> IO Double
deltaForward = $(ffiCallX 'deltaForward) c_deltaForward

foreign import ccall safe "ql.h qlBlackCalculatorDeltaForward"
  c_deltaForward :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to dividend/growth rate.
dividendRho :: BlackCalculator
  -> YearFraction -- ^maturity
  -> IO Double
dividendRho = $(ffiCallX 'dividendRho) c_dividendRho

foreign import ccall safe "ql.h qlBlackCalculatorDividendRho"
  c_dividendRho :: Ptr CBlackCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity in percent to a percent change in the underlying spot price.
elasticity :: BlackCalculator
  -> Double -- ^spot
  -> IO Double
elasticity = $(ffiCallX 'elasticity) c_elasticity

foreign import ccall safe "ql.h qlBlackCalculatorElasticity"
  c_elasticity :: Ptr CBlackCalculator -> CDouble -> Ptr CString -> IO CDouble

-- |Sensitivity in percent to a percent change in the underlying forward price.
elasticityForward :: BlackCalculator -> IO Double
elasticityForward = $(ffiCallX 'elasticityForward) c_elasticityForward

foreign import ccall safe "ql.h qlBlackCalculatorElasticityForward"
  c_elasticityForward :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Second order derivative with respect to change in the underlying spot price.
gamma :: BlackCalculator
  -> Double -- ^spot
  -> IO Double
gamma = $(ffiCallX 'gamma) c_gamma

foreign import ccall safe "ql.h qlBlackCalculatorGamma"
  c_gamma :: Ptr CBlackCalculator -> CDouble -> Ptr CString -> IO CDouble

-- |Second order derivative with respect to change in the underlying forward price.
gammaForward :: BlackCalculator -> IO Double
gammaForward = $(ffiCallX 'gammaForward) c_gammaForward

foreign import ccall safe "ql.h qlBlackCalculatorGammaForward"
  c_gammaForward :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
itmAssetProbability :: BlackCalculator
  -> IO Double
itmAssetProbability = $(ffiCallX 'itmAssetProbability) c_itmAssetProbability

foreign import ccall safe "ql.h qlBlackCalculatorItmAssetProbability"
  c_itmAssetProbability :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Probability of being in the money in the bond martingale measure, i.e. N(d2). It is a risk-neutral probability, not the real world one.
itmCashProbability :: BlackCalculator -> IO Double
itmCashProbability = $(ffiCallX 'itmCashProbability) c_itmCashProbability

foreign import ccall safe "ql.h qlBlackCalculatorItmCashProbability"
  c_itmCashProbability :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to discounting rate.
rho :: BlackCalculator
  -> YearFraction -- ^maturity
  -> IO Double
rho = $(ffiCallX 'rho) c_rho

foreign import ccall safe "ql.h qlBlackCalculatorRho"
  c_rho :: Ptr CBlackCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity to strike.
strikeSensitivity :: BlackCalculator -> IO Double
strikeSensitivity = $(ffiCallX 'strikeSensitivity) c_strikeSensitivity

foreign import ccall safe "ql.h qlBlackCalculatorStrikeSensitivity"
  c_strikeSensitivity :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity.
theta :: BlackCalculator
  -> Double -- ^spot
  -> YearFraction -- ^maturity
  -> IO Double
theta = $(ffiCallX 'theta) c_theta

foreign import ccall safe "ql.h qlBlackCalculatorTheta"
  c_theta :: Ptr CBlackCalculator -> CDouble -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity per day, assuming 365 day per year.
thetaPerDay :: BlackCalculator
  -> Double -- ^spot
  -> YearFraction -- ^maturity
  -> IO Double
thetaPerDay = $(ffiCallX 'thetaPerDay) c_thetaPerDay

foreign import ccall safe "ql.h qlBlackCalculatorThetaPerDay"
  c_thetaPerDay :: Ptr CBlackCalculator -> CDouble -> CYearFraction -> Ptr CString -> IO CDouble

value :: BlackCalculator -> IO Double
value = $(ffiCallX 'value) c_value

foreign import ccall safe "ql.h qlBlackCalculatorValue"
  c_value :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to volatility.
vega :: BlackCalculator
  -> YearFraction -- ^maturity
  -> IO Double
vega = $(ffiCallX 'vega) c_vega

foreign import ccall safe "ql.h qlBlackCalculatorVega"
  c_vega :: Ptr CBlackCalculator -> CYearFraction -> Ptr CString -> IO CDouble

blackScholesCalculator' :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^spot
  -> Double -- ^growth
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> IO BlackScholesCalculator
blackScholesCalculator' = $(ffiCall 'blackScholesCalculator') c_blackScholesCalculator'

foreign import ccall safe "ql.h qlBlackScholesCalculator1"
  c_blackScholesCalculator' :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackScholesCalculator)

blackScholesCalculator :: StrikedTypePayoff -- ^payoff
  -> Double -- ^spot
  -> Double -- ^growth
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> IO BlackScholesCalculator
blackScholesCalculator = $(ffiCall 'blackScholesCalculator) c_blackScholesCalculator

foreign import ccall safe "ql.h qlBlackScholesCalculator"
  c_blackScholesCalculator :: Ptr CStrikedTypePayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackScholesCalculator)

-- |Sensitivity to change in the underlying spot price.
delta' :: BlackScholesCalculator -> IO Double
delta' = $(ffiCallX 'delta') c_delta'

foreign import ccall safe "ql.h qlBlackScholesCalculatorDelta"
  c_delta' :: Ptr CBlackScholesCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity in percent to a percent change in the underlying spot price.
elasticity' :: BlackScholesCalculator -> IO Double
elasticity' = $(ffiCallX 'elasticity') c_elasticity'

foreign import ccall safe "ql.h qlBlackScholesCalculatorElasticity"
  c_elasticity' :: Ptr CBlackScholesCalculator -> Ptr CString -> IO CDouble

-- |Second order derivative with respect to change in the underlying spot price.
gamma' :: BlackScholesCalculator -> IO Double
gamma' = $(ffiCallX 'gamma') c_gamma'

foreign import ccall safe "ql.h qlBlackScholesCalculatorGamma"
  c_gamma' :: Ptr CBlackScholesCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity.
theta' :: BlackScholesCalculator
  -> YearFraction -- ^maturity
  -> IO Double
theta' = $(ffiCallX 'theta') c_theta'

foreign import ccall safe "ql.h qlBlackScholesCalculatorTheta"
  c_theta' :: Ptr CBlackScholesCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity per day (assuming 365 day in a year).
thetaPerDay' :: BlackScholesCalculator
  -> YearFraction -- ^maturity
  -> IO Double
thetaPerDay' = $(ffiCallX 'thetaPerDay') c_thetaPerDay'

foreign import ccall safe "ql.h qlBlackScholesCalculatorThetaPerDay"
  c_thetaPerDay' :: Ptr CBlackScholesCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormula' :: PlainVanillaPayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormula' = $(ffiCallX 'blackFormula') c_blackFormula'

foreign import ccall safe "ql.h qlQuantLibBlackFormula1"
  c_blackFormula' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormula :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormula = $(ffiCallX 'blackFormula) c_blackFormula

foreign import ccall safe "ql.h qlQuantLibBlackFormula"
  c_blackFormula :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormulaCashItmProbability' :: PlainVanillaPayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^displacement
  -> IO Double
blackFormulaCashItmProbability' = $(ffiCallX 'blackFormulaCashItmProbability') c_blackFormulaCashItmProbability'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaCashItmProbability1"
  c_blackFormulaCashItmProbability' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormulaCashItmProbability :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^displacement
  -> IO Double
blackFormulaCashItmProbability = $(ffiCallX 'blackFormulaCashItmProbability) c_blackFormulaCashItmProbability

foreign import ccall safe "ql.h qlQuantLibBlackFormulaCashItmProbability"
  c_blackFormulaCashItmProbability :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormulaImpliedStdDev' :: PlainVanillaPayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> IO Double
blackFormulaImpliedStdDev' = $(ffiCallX 'blackFormulaImpliedStdDev') c_blackFormulaImpliedStdDev'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDev1"
  c_blackFormulaImpliedStdDev' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO CDouble

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormulaImpliedStdDev :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> IO Double
blackFormulaImpliedStdDev = $(ffiCallX 'blackFormulaImpliedStdDev) c_blackFormulaImpliedStdDev

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDev"
  c_blackFormulaImpliedStdDev :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO CDouble

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
blackFormulaImpliedStdDevApproximation' :: PlainVanillaPayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormulaImpliedStdDevApproximation' = $(ffiCallX 'blackFormulaImpliedStdDevApproximation') c_blackFormulaImpliedStdDevApproximation'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDevApproximation1"
  c_blackFormulaImpliedStdDevApproximation' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
blackFormulaImpliedStdDevApproximation :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormulaImpliedStdDevApproximation = $(ffiCallX 'blackFormulaImpliedStdDevApproximation) c_blackFormulaImpliedStdDevApproximation

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDevApproximation"
  c_blackFormulaImpliedStdDevApproximation :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
blackFormulaStdDevDerivative' :: PlainVanillaPayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormulaStdDevDerivative' = $(ffiCallX 'blackFormulaStdDevDerivative') c_blackFormulaStdDevDerivative'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaStdDevDerivative1"
  c_blackFormulaStdDevDerivative' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
blackFormulaStdDevDerivative :: Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormulaStdDevDerivative = $(ffiCallX 'blackFormulaStdDevDerivative) c_blackFormulaStdDevDerivative

foreign import ccall safe "ql.h qlQuantLibBlackFormulaStdDevDerivative"
  c_blackFormulaStdDevDerivative :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula for derivative with respect to implied vol, this is basically the vega, but if you want 1% change multiply by 1%
blackFormulaVolDerivative :: Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^expiry
  -> Double -- ^discount
  -> Double -- ^displacement
  -> IO Double
blackFormulaVolDerivative = $(ffiCallX 'blackFormulaVolDerivative) c_blackFormulaVolDerivative

foreign import ccall safe "ql.h qlQuantLibBlackFormulaVolDerivative"
  c_blackFormulaVolDerivative :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |default theta calculation for Black-Scholes options
blackScholesTheta :: GeneralizedBlackScholesProcess
  -> Double -- ^value
  -> Double -- ^delta
  -> Double -- ^gamma
  -> IO Double
blackScholesTheta = $(ffiCallX 'blackScholesTheta) c_blackScholesTheta

foreign import ccall safe "ql.h qlQuantLibBlackScholesTheta"
  c_blackScholesTheta :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
bachelierBlackFormula' :: PlainVanillaPayoff -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> IO Double
bachelierBlackFormula' = $(ffiCallX 'bachelierBlackFormula') c_bachelierBlackFormula'

foreign import ccall safe "ql.h qlQuantLibBachelierBlackFormula1"
  c_bachelierBlackFormula' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
bachelierBlackFormula :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> IO Double
bachelierBlackFormula = $(ffiCallX 'bachelierBlackFormula) c_bachelierBlackFormula

foreign import ccall safe "ql.h qlQuantLibBachelierBlackFormula"
  c_bachelierBlackFormula :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |default theta-per-day calculation
defaultThetaPerDay :: Double -- ^theta
  -> IO Double
defaultThetaPerDay = $(ffiCallX 'defaultThetaPerDay) c_defaultThetaPerDay

foreign import ccall safe "ql.h qlQuantLibDefaultThetaPerDay"
  c_defaultThetaPerDay :: CDouble -> Ptr CString -> IO CDouble

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

fFTVanillaEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^logStrikeSpacing
  -> IO PricingEngine
fFTVanillaEngine = $(ffiCall 'fFTVanillaEngine) c_fFTVanillaEngine

foreign import ccall safe "ql.h qlFFTVanillaEngine"
  c_fFTVanillaEngine :: Ptr CGeneralizedBlackScholesProcess -> CDouble -> Ptr CString -> IO (Ptr CPricingEngine)

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

-- |/NB/ Monte Carlo engines are additionally parameterised via template arguments
-- with RNG and Statistics classes in C++. For now we are using default values
mcHestonHullWhiteEngine :: HybridHestonHullWhiteProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcHestonHullWhiteEngine = $(ffiCall 'mcHestonHullWhiteEngine) c_mcHestonHullWhiteEngine

foreign import ccall safe "ql.h qlMCHestonHullWhiteEngine"
  c_mcHestonHullWhiteEngine :: Ptr CHybridHestonHullWhiteProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcAmericanEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> Word -- ^polynomOrder
  -> LsmBasisSystemPolynomType -- ^polynomType
  -> Word -- ^nCalibrationSamples
  -> IO PricingEngine
mcAmericanEngine = $(ffiCall 'mcAmericanEngine) c_mcAmericanEngine

foreign import ccall safe "ql.h qlMCAmericanEngine"
  c_mcAmericanEngine :: Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> CUInt -> CInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcBarrierEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Bool -- ^isBiased
  -> Word -- ^seed
  -> IO PricingEngine
mcBarrierEngine = $(ffiCall 'mcBarrierEngine) c_mcBarrierEngine

foreign import ccall safe "ql.h qlMCBarrierEngine"
  c_mcBarrierEngine :: Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDigitalEngine :: GeneralizedBlackScholesProcess
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDigitalEngine = $(ffiCall 'mcDigitalEngine) c_mcDigitalEngine

foreign import ccall safe "ql.h qlMCDigitalEngine"
  c_mcDigitalEngine :: Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteArithmeticAPEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Bool -- ^controlVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDiscreteArithmeticAPEngine = $(ffiCall 'mcDiscreteArithmeticAPEngine) c_mcDiscreteArithmeticAPEngine

foreign import ccall safe "ql.h qlMCDiscreteArithmeticAPEngine"
  c_mcDiscreteArithmeticAPEngine :: Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteArithmeticASEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDiscreteArithmeticASEngine = $(ffiCall 'mcDiscreteArithmeticASEngine) c_mcDiscreteArithmeticASEngine

foreign import ccall safe "ql.h qlMCDiscreteArithmeticASEngine"
  c_mcDiscreteArithmeticASEngine :: Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcDiscreteGeometricAPEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcDiscreteGeometricAPEngine = $(ffiCall 'mcDiscreteGeometricAPEngine) c_mcDiscreteGeometricAPEngine

foreign import ccall safe "ql.h qlMCDiscreteGeometricAPEngine"
  c_mcDiscreteGeometricAPEngine :: Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcEuropeanEngine = $(ffiCall 'mcEuropeanEngine) c_mcEuropeanEngine

foreign import ccall safe "ql.h qlMCEuropeanEngine"
  c_mcEuropeanEngine :: Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanGJRGARCHEngine :: GJRGARCHProcess
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcEuropeanGJRGARCHEngine = $(ffiCall 'mcEuropeanGJRGARCHEngine) c_mcEuropeanGJRGARCHEngine

foreign import ccall safe "ql.h qlMCEuropeanGJRGARCHEngine"
  c_mcEuropeanGJRGARCHEngine :: Ptr CGJRGARCHProcess -> CUInt -> CUInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcEuropeanHestonEngine :: HestonProcess
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcEuropeanHestonEngine = $(ffiCall 'mcEuropeanHestonEngine) c_mcEuropeanHestonEngine

foreign import ccall safe "ql.h qlMCEuropeanHestonEngine"
  c_mcEuropeanHestonEngine :: Ptr CHestonProcess -> CUInt -> CUInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcHullWhiteCapFloorEngine :: HullWhite -- ^model
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcHullWhiteCapFloorEngine = $(ffiCall 'mcHullWhiteCapFloorEngine) c_mcHullWhiteCapFloorEngine

foreign import ccall safe "ql.h qlMCHullWhiteCapFloorEngine"
  c_mcHullWhiteCapFloorEngine :: Ptr CHullWhite -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

mcPerformanceEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcPerformanceEngine = $(ffiCall 'mcPerformanceEngine) c_mcPerformanceEngine

foreign import ccall safe "ql.h qlMCPerformanceEngine"
  c_mcPerformanceEngine :: Ptr CGeneralizedBlackScholesProcess -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

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

mcVarianceSwapEngine :: GeneralizedBlackScholesProcess -- ^process
  -> Word -- ^timeSteps
  -> Word -- ^timeStepsPerYear
  -> Bool -- ^brownianBridge
  -> Bool -- ^antitheticVariate
  -> Word -- ^requiredSamples
  -> Double -- ^requiredTolerance
  -> Word -- ^maxSamples
  -> Word -- ^seed
  -> IO PricingEngine
mcVarianceSwapEngine = $(ffiCall 'mcVarianceSwapEngine) c_mcVarianceSwapEngine

foreign import ccall safe "ql.h qlMCVarianceSwapEngine"
  c_mcVarianceSwapEngine :: Ptr CGeneralizedBlackScholesProcess -> CUInt -> CUInt -> CInt -> CInt -> CUInt -> CDouble -> CUInt -> CUInt -> Ptr CString -> IO (Ptr CPricingEngine)

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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
