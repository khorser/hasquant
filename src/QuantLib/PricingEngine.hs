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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
