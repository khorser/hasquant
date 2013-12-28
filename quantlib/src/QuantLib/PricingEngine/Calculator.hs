{-# LANGUAGE TemplateHaskell #-}
module QuantLib.PricingEngine.Calculator
  (
    alpha
  , beta
  , blackCalculator'
  , blackCalculator
  , blackDelta
  , deltaForward
  , dividendRho
  , blackElasticity
  , elasticityForward
  , blackGamma
  , gammaForward
  , itmAssetProbability
  , itmCashProbability
  , rho
  , strikeSensitivity
  , blackTheta
  , blackThetaPerDay
  , value
  , vega
  , blackScholesCalculator'
  , blackScholesCalculator
  , blackScholesDelta
  , blackScholesElasticity
  , blackScholesGamma
  , blackScholesTheta
  , blackScholesThetaPerDay
  , blackFormula'
  , blackFormula
  , blackCashItmProbability'
  , blackCashItmProbability
  , blackImpliedStdDev'
  , blackImpliedStdDev
  , blackImpliedStdDevApproximation'
  , blackImpliedStdDevApproximation
  , blackStdDevDerivative'
  , blackStdDevDerivative
  , blackVolDerivative
  , bachelierBlackFormula'
  , bachelierBlackFormula
  , defaultThetaPerDay
  )
where

import QuantLib.Instrument.OptionType(OptionType)
import QuantLib.Internal.Date
import QuantLib.Internal.Types
import QuantLib.Internal.Syntax
import QuantLib.Types

alpha :: BlackCalculator s -> QLE s Double
alpha = $(ffiCallX 'alpha) c_alpha

foreign import ccall safe "ql.h qlBlackCalculatorAlpha"
  c_alpha :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

beta :: BlackCalculator s -> QLE s Double
beta = $(ffiCallX 'beta) c_beta

foreign import ccall safe "ql.h qlBlackCalculatorBeta"
  c_beta :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

blackCalculator' :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> QLE s (BlackCalculator s)
blackCalculator' = $(ffiCall 'blackCalculator') c_blackCalculator'

foreign import ccall safe "ql.h qlBlackCalculator1"
  c_blackCalculator' :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackCalculator)

blackCalculator :: StrikedTypePayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> QLE s (BlackCalculator s)
blackCalculator = $(ffiCall 'blackCalculator) c_blackCalculator

foreign import ccall safe "ql.h qlBlackCalculator"
  c_blackCalculator :: Ptr CStrikedTypePayoff -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackCalculator)

-- |Sensitivity to change in the underlying spot price.
blackDelta :: BlackCalculator s
  -> Double -- ^spot
  -> QLE s Double
blackDelta = $(ffiCallX 'blackDelta) c_blackDelta

foreign import ccall safe "ql.h qlBlackCalculatorDelta"
  c_blackDelta :: Ptr CBlackCalculator -> CDouble -> Ptr CString -> IO CDouble

-- |Sensitivity to change in the underlying forward price.
deltaForward :: BlackCalculator s -> QLE s Double
deltaForward = $(ffiCallX 'deltaForward) c_deltaForward

foreign import ccall safe "ql.h qlBlackCalculatorDeltaForward"
  c_deltaForward :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to dividend/growth rate.
dividendRho :: BlackCalculator s
  -> YearFraction -- ^maturity
  -> QLE s Double
dividendRho = $(ffiCallX 'dividendRho) c_dividendRho

foreign import ccall safe "ql.h qlBlackCalculatorDividendRho"
  c_dividendRho :: Ptr CBlackCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity in percent to a percent change in the underlying spot price.
blackElasticity :: BlackCalculator s
  -> Double -- ^spot
  -> QLE s Double
blackElasticity = $(ffiCallX 'blackElasticity) c_blackElasticity

foreign import ccall safe "ql.h qlBlackCalculatorElasticity"
  c_blackElasticity :: Ptr CBlackCalculator -> CDouble -> Ptr CString -> IO CDouble

-- |Sensitivity in percent to a percent change in the underlying forward price.
elasticityForward :: BlackCalculator s -> QLE s Double
elasticityForward = $(ffiCallX 'elasticityForward) c_elasticityForward

foreign import ccall safe "ql.h qlBlackCalculatorElasticityForward"
  c_elasticityForward :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Second order derivative with respect to change in the underlying spot price.
blackGamma :: BlackCalculator s
  -> Double -- ^spot
  -> QLE s Double
blackGamma = $(ffiCallX 'blackGamma) c_blackGamma

foreign import ccall safe "ql.h qlBlackCalculatorGamma"
  c_blackGamma :: Ptr CBlackCalculator -> CDouble -> Ptr CString -> IO CDouble

-- |Second order derivative with respect to change in the underlying forward price.
gammaForward :: BlackCalculator s -> QLE s Double
gammaForward = $(ffiCallX 'gammaForward) c_gammaForward

foreign import ccall safe "ql.h qlBlackCalculatorGammaForward"
  c_gammaForward :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
itmAssetProbability :: BlackCalculator s -> QLE s Double
itmAssetProbability = $(ffiCallX 'itmAssetProbability) c_itmAssetProbability

foreign import ccall safe "ql.h qlBlackCalculatorItmAssetProbability"
  c_itmAssetProbability :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Probability of being in the money in the bond martingale measure, i.e. N(d2). It is a risk-neutral probability, not the real world one.
itmCashProbability :: BlackCalculator s -> QLE s Double
itmCashProbability = $(ffiCallX 'itmCashProbability) c_itmCashProbability

foreign import ccall safe "ql.h qlBlackCalculatorItmCashProbability"
  c_itmCashProbability :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to discounting rate.
rho :: BlackCalculator s
  -> YearFraction -- ^maturity
  -> QLE s Double
rho = $(ffiCallX 'rho) c_rho

foreign import ccall safe "ql.h qlBlackCalculatorRho"
  c_rho :: Ptr CBlackCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity to strike.
strikeSensitivity :: BlackCalculator s -> QLE s Double
strikeSensitivity = $(ffiCallX 'strikeSensitivity) c_strikeSensitivity

foreign import ccall safe "ql.h qlBlackCalculatorStrikeSensitivity"
  c_strikeSensitivity :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity.
blackTheta :: BlackCalculator s
  -> Double -- ^spot
  -> YearFraction -- ^maturity
  -> QLE s Double
blackTheta = $(ffiCallX 'blackTheta) c_blackTheta

foreign import ccall safe "ql.h qlBlackCalculatorTheta"
  c_blackTheta :: Ptr CBlackCalculator -> CDouble -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity per day, assuming 365 day per year.
blackThetaPerDay :: BlackCalculator s
  -> Double -- ^spot
  -> YearFraction -- ^maturity
  -> QLE s Double
blackThetaPerDay = $(ffiCallX 'blackThetaPerDay) c_blackThetaPerDay

foreign import ccall safe "ql.h qlBlackCalculatorThetaPerDay"
  c_blackThetaPerDay :: Ptr CBlackCalculator -> CDouble -> CYearFraction -> Ptr CString -> IO CDouble

value :: BlackCalculator s -> QLE s Double
value = $(ffiCallX 'value) c_value

foreign import ccall safe "ql.h qlBlackCalculatorValue"
  c_value :: Ptr CBlackCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to volatility.
vega :: BlackCalculator s
  -> YearFraction -- ^maturity
  -> QLE s Double
vega = $(ffiCallX 'vega) c_vega

foreign import ccall safe "ql.h qlBlackCalculatorVega"
  c_vega :: Ptr CBlackCalculator -> CYearFraction -> Ptr CString -> IO CDouble

blackScholesCalculator' :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^spot
  -> Double -- ^growth
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> QLE s (BlackScholesCalculator s)
blackScholesCalculator' = $(ffiCall 'blackScholesCalculator') c_blackScholesCalculator'

foreign import ccall safe "ql.h qlBlackScholesCalculator1"
  c_blackScholesCalculator' :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackScholesCalculator)

blackScholesCalculator :: StrikedTypePayoff s -- ^payoff
  -> Double -- ^spot
  -> Double -- ^growth
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> QLE s (BlackScholesCalculator s)
blackScholesCalculator = $(ffiCall 'blackScholesCalculator) c_blackScholesCalculator

foreign import ccall safe "ql.h qlBlackScholesCalculator"
  c_blackScholesCalculator :: Ptr CStrikedTypePayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CBlackScholesCalculator)

-- |Sensitivity to change in the underlying spot price.
blackScholesDelta :: BlackScholesCalculator s -> QLE s Double
blackScholesDelta = $(ffiCallX 'blackScholesDelta) c_blackScholesDelta

foreign import ccall safe "ql.h qlBlackScholesCalculatorDelta"
  c_blackScholesDelta :: Ptr CBlackScholesCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity in percent to a percent change in the underlying spot price.
blackScholesElasticity :: BlackScholesCalculator s -> QLE s Double
blackScholesElasticity = $(ffiCallX 'blackScholesElasticity) c_blackScholesElasticity

foreign import ccall safe "ql.h qlBlackScholesCalculatorElasticity"
  c_blackScholesElasticity :: Ptr CBlackScholesCalculator -> Ptr CString -> IO CDouble

-- |Second order derivative with respect to change in the underlying spot price.
blackScholesGamma :: BlackScholesCalculator s -> QLE s Double
blackScholesGamma = $(ffiCallX 'blackScholesGamma) c_blackScholesGamma

foreign import ccall safe "ql.h qlBlackScholesCalculatorGamma"
  c_blackScholesGamma :: Ptr CBlackScholesCalculator -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity.
blackScholesTheta :: BlackScholesCalculator s
  -> YearFraction -- ^maturity
  -> QLE s Double
blackScholesTheta = $(ffiCallX 'blackScholesTheta) c_blackScholesTheta

foreign import ccall safe "ql.h qlBlackScholesCalculatorTheta"
  c_blackScholesTheta :: Ptr CBlackScholesCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Sensitivity to time to maturity per day (assuming 365 day in a year).
blackScholesThetaPerDay :: BlackScholesCalculator s
  -> YearFraction -- ^maturity
  -> QLE s Double
blackScholesThetaPerDay = $(ffiCallX 'blackScholesThetaPerDay) c_blackScholesThetaPerDay

foreign import ccall safe "ql.h qlBlackScholesCalculatorThetaPerDay"
  c_blackScholesThetaPerDay :: Ptr CBlackScholesCalculator -> CYearFraction -> Ptr CString -> IO CDouble

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackFormula' :: PlainVanillaPayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> QLE s Double
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
  -> QLE s Double
blackFormula = $(ffiCallX 'blackFormula) c_blackFormula

foreign import ccall safe "ql.h qlQuantLibBlackFormula"
  c_blackFormula :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackCashItmProbability' :: PlainVanillaPayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^displacement
  -> QLE s Double
blackCashItmProbability' = $(ffiCallX 'blackCashItmProbability') c_blackCashItmProbability'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaCashItmProbability1"
  c_blackCashItmProbability' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackCashItmProbability :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^displacement
  -> QLE s Double
blackCashItmProbability = $(ffiCallX 'blackCashItmProbability) c_blackCashItmProbability

foreign import ccall safe "ql.h qlQuantLibBlackFormulaCashItmProbability"
  c_blackCashItmProbability :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackImpliedStdDev' :: PlainVanillaPayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> QLE s Double
blackImpliedStdDev' = $(ffiCallX 'blackImpliedStdDev') c_blackImpliedStdDev'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDev1"
  c_blackImpliedStdDev' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO CDouble

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
blackImpliedStdDev :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxIterations
  -> QLE s Double
blackImpliedStdDev = $(ffiCallX 'blackImpliedStdDev) c_blackImpliedStdDev

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDev"
  c_blackImpliedStdDev :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO CDouble

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
blackImpliedStdDevApproximation' :: PlainVanillaPayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> QLE s Double
blackImpliedStdDevApproximation' = $(ffiCallX 'blackImpliedStdDevApproximation') c_blackImpliedStdDevApproximation'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDevApproximation1"
  c_blackImpliedStdDevApproximation' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
blackImpliedStdDevApproximation :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^blackPrice
  -> Double -- ^discount
  -> Double -- ^displacement
  -> QLE s Double
blackImpliedStdDevApproximation = $(ffiCallX 'blackImpliedStdDevApproximation) c_blackImpliedStdDevApproximation

foreign import ccall safe "ql.h qlQuantLibBlackFormulaImpliedStdDevApproximation"
  c_blackImpliedStdDevApproximation :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
blackStdDevDerivative' :: PlainVanillaPayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> QLE s Double
blackStdDevDerivative' = $(ffiCallX 'blackStdDevDerivative') c_blackStdDevDerivative'

foreign import ccall safe "ql.h qlQuantLibBlackFormulaStdDevDerivative1"
  c_blackStdDevDerivative' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
blackStdDevDerivative :: Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> Double -- ^displacement
  -> QLE s Double
blackStdDevDerivative = $(ffiCallX 'blackStdDevDerivative) c_blackStdDevDerivative

foreign import ccall safe "ql.h qlQuantLibBlackFormulaStdDevDerivative"
  c_blackStdDevDerivative :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black 1976 formula for derivative with respect to implied vol, this is basically the vega, but if you want 1% change multiply by 1%
blackVolDerivative :: Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^expiry
  -> Double -- ^discount
  -> Double -- ^displacement
  -> QLE s Double
blackVolDerivative = $(ffiCallX 'blackVolDerivative) c_blackVolDerivative

foreign import ccall safe "ql.h qlQuantLibBlackFormulaVolDerivative"
  c_blackVolDerivative :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
bachelierBlackFormula' :: PlainVanillaPayoff s -- ^payoff
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> QLE s Double
bachelierBlackFormula' = $(ffiCallX 'bachelierBlackFormula') c_bachelierBlackFormula'

foreign import ccall safe "ql.h qlQuantLibBachelierBlackFormula1"
  c_bachelierBlackFormula' :: Ptr CPlainVanillaPayoff -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
bachelierBlackFormula :: OptionType -- ^optionType
  -> Double -- ^strike
  -> Double -- ^forward
  -> Double -- ^stdDev
  -> Double -- ^discount
  -> QLE s Double
bachelierBlackFormula = $(ffiCallX 'bachelierBlackFormula) c_bachelierBlackFormula

foreign import ccall safe "ql.h qlQuantLibBachelierBlackFormula"
  c_bachelierBlackFormula :: CInt -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |default theta-per-day calculation
defaultThetaPerDay :: Double -- ^theta
  -> QLE s Double
defaultThetaPerDay = $(ffiCallX 'defaultThetaPerDay) c_defaultThetaPerDay

foreign import ccall safe "ql.h qlQuantLibDefaultThetaPerDay"
  c_defaultThetaPerDay :: CDouble -> Ptr CString -> IO CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
