module QuantLib.PricingEngine
  (
    PricingEngine
  , BlackCalculator
  , BlackScholesCalculator
  , BachelierCalculator
  , BlackDeltaCalculator
  , CashAnnuityModel(..)
  , Probabilities(..)
  , CashDividendModel(..)
  , NumericalFix(..)
  , AccrualBias(..)
  , ForwardsInCouponPeriod(..)
  , FdmQuantoHelper

  , GenBlackCalculator
  , asBlackCalculator

  , discountingBondEngine
  , riskyBondEngine
  , discountingSwapEngine
  , discountingFxForwardEngine
  , counterpartyAdjSwapEngine

  , analyticBarrierEngine
  , analyticPartialTimeBarrierOptionEngine
  , analyticBinaryBarrierEngine
  , fdBlackScholesBarrierEngine
  , fdHestonBarrierEngine
  , fdHestonBarrierEngine'
  , binomialBarrierEngine
  , vannaVolgaBarrierEngine
  , analyticDoubleBarrierEngine
  , fdHestonDoubleBarrierEngine
  , vannaVolgaDoubleBarrierEngine
  , binomialDoubleBarrierEngine
  , mcDoubleBarrierEngine
  , analyticCliquetEngine
  , analyticCompoundOptionEngine
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
  , bachelierCapFloorEngine'
  , bachelierCapFloorEngine
  , bachelierSwaptionEngine
  , bachelierSwaptionEngine'
  , analyticBSMHullWhiteEngine
  , analyticCapFloorEngine
  , gaussian1dCapFloorEngine
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
  , integralHestonVarianceOptionEngine
  , mcHullWhiteCapFloorEngine
  , mcHimalayaEngine
  , mcPagodaEngine
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
  , isdaCdsEngine
  , jamshidianSwaptionEngine
  , gaussian1dSwaptionEngine
  , gaussian1dNonstandardSwaptionEngine
  , gaussian1dFloatFloatSwaptionEngine
  , gaussian1dJamshidianSwaptionEngine
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
  , fdBlackScholesVanillaEngine
  , fdmQuantoHelper
  , fdHestonVanillaEngine
  , fdHestonVanillaEngine'
  , fdHestonVanillaEngineQuanto
  , fdHestonVanillaEngineQuanto'
  , fdHestonHullWhiteVanillaEngine
  , fdHestonHullWhiteVanillaEngine'

  , binomialConvertibleEngine
  , blackCallableFixedRateBondEngine'
  , blackCallableFixedRateBondEngine
  , blackCallableZeroCouponBondEngine'
  , blackCallableZeroCouponBondEngine
  , treeCallableFixedRateBondEngine'
  , treeCallableFixedRateBondEngine
  , treeCallableZeroCouponBondEngine'
  , treeCallableZeroCouponBondEngine

  , alpha
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
  , strikeGamma
  , blackTheta
  , blackThetaPerDay
  , value
  , vanna
  , vega
  , volga
  , blackScholesCalculator'
  , blackScholesCalculator
  , blackScholesDelta
  , blackScholesElasticity
  , blackScholesGamma
  , blackScholesTheta
  , blackScholesThetaPerDay

  , bachelierCalculator'
  , bachelierCalculator
  , bachelierAlpha
  , bachelierBeta
  , bachelierDelta
  , bachelierDeltaForward
  , bachelierDividendRho
  , bachelierElasticity
  , bachelierElasticityForward
  , bachelierGamma
  , bachelierGammaForward
  , bachelierItmAssetProbability
  , bachelierItmCashProbability
  , bachelierRho
  , bachelierStrikeSensitivity
  , bachelierStrikeGamma
  , bachelierTheta
  , bachelierThetaPerDay
  , bachelierValue
  , bachelierVanna
  , bachelierVega
  , bachelierVolga

  , blackDeltaCalculator
  , deltaFromStrike
  , strikeFromDelta
  , atmStrike
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
  , unsafeSabrLogNormalVolatility
  , unsafeShiftedSabrVolatility
  , unsafeSabrNormalVolatility
  , unsafeSabrVolatility
  , sabrVolatility
  , shiftedSabrVolatility
  , sabrFlochKennedyVolatility
  , validateSabrParameters
  , sabrGuess
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.Math#}
{#import QuantLib.Quote#}(DeltaType, AtmType)
{#import QuantLib.Instrument.Option#} hiding(itmCashProbability, deltaForward, strikeSensitivity, dividendRho, rho, vega)
import QuantLib.Internal.Enum

{#enum CashAnnuityModel{} deriving(Show, Eq)#}
{#enum Probabilities{} deriving(Show, Eq)#}
{#enum CashDividendModel{} add prefix="CashDividend" deriving(Show, Eq)#}
{#enum NumericalFix{} deriving(Show, Eq)#}
{#enum AccrualBias{} deriving(Show, Eq)#}
{#enum ForwardsInCouponPeriod{} deriving(Show, Eq)#}

{#pointer *DayCounter foreign -> CDayCounter nocode#}

{#pointer *QlDividend as Dividend foreign -> CDividend nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign -> CCallableBondVolatilityStructure' nocode#}
{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign -> CGJRGARCHModel' nocode#}
{#pointer *QlHestonModel as HestonModel foreign -> CHestonModel' nocode#}
{#pointer *QlBatesModel as BatesModel foreign -> CBatesModel' nocode#}
{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign -> CPiecewiseTimeDependentHestonModel' nocode#}
{#pointer *QlShortRateModel as ShortRateModel foreign -> CShortRateModel' nocode#}
{#pointer *QlAffineModel foreign -> CAffineModel' nocode#}
{#pointer *QlGaussian1dModel foreign -> CGaussian1dModel' nocode#}
{#pointer *QlOneFactorAffineModel as OneFactorAffineModel foreign -> COneFactorAffineModel' nocode#}
{#pointer *QlLiborForwardModel as LiborForwardModel foreign -> CLiborForwardModel' nocode#}
{#pointer *QlHullWhite as HullWhite foreign -> CHullWhite' nocode#}
{#pointer *QlCalibratedModel as CalibratedModel foreign -> CCalibratedModel' nocode#}
{#pointer *QlG2 as G2 foreign -> CG2' nocode#}
{#pointer *QlBatesDetJumpModel as BatesDetJumpModel foreign -> CBatesDetJumpModel' nocode#}
{#pointer *QlBatesDoubleExpDetJumpModel as BatesDoubleExpDetJumpModel foreign -> CBatesDoubleExpDetJumpModel' nocode#}
{#pointer *QlBatesDoubleExpModel as BatesDoubleExpModel foreign -> CBatesDoubleExpModel' nocode#}

{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign -> CStochasticProcess1D' nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess' nocode#}
{#pointer *QlBlackProcess as BlackProcess foreign -> CBlackProcess' nocode#}
{#pointer *QlExtOUWithJumpsProcess as ExtOUWithJumpsProcess foreign -> CExtOUWithJumpsProcess' nocode#}
{#pointer *QlExtendedOrnsteinUhlenbeckProcess as ExtendedOrnsteinUhlenbeckProcess foreign -> CExtendedOrnsteinUhlenbeckProcess' nocode#}
{#pointer *QlGJRGARCHProcess as GJRGARCHProcess foreign -> CGJRGARCHProcess' nocode#}
{#pointer *QlHestonProcess as HestonProcess foreign -> CHestonProcess' nocode#}
{#pointer *QlBatesProcess as BatesProcess foreign -> CBatesProcess' nocode#}
{#pointer *QlHybridHestonHullWhiteProcess as HybridHestonHullWhiteProcess foreign -> CHybridHestonHullWhiteProcess' nocode#}
{#pointer *QlKlugeExtOUProcess as KlugeExtOUProcess foreign -> CKlugeExtOUProcess' nocode#}
{#pointer *QlLiborForwardModelProcess as LiborForwardModelProcess foreign -> CLiborForwardModelProcess' nocode#}
{#pointer *QlStochasticProcessArray as StochasticProcessArray foreign -> CStochasticProcessArray' nocode#}
{#pointer *QlVarianceGammaProcess as VarianceGammaProcess foreign -> CVarianceGammaProcess' nocode#}
{#pointer *QlMerton76Process as Merton76Process foreign -> CMerton76Process' nocode#}
{#pointer *QlHullWhiteProcess as HullWhiteProcess foreign -> CHullWhiteProcess' nocode#}
{#pointer *QlHullWhiteForwardProcess as HullWhiteForwardProcess foreign -> CHullWhiteForwardProcess' nocode#}

{#pointer *QlBlackCalculator as BlackCalculator foreign -> CBlackCalculator' nocode#}
{#pointer *QlBlackScholesCalculator as BlackScholesCalculator foreign -> CBlackScholesCalculator' nocode#}
{#pointer *QlBachelierCalculator as BachelierCalculator foreign -> CBachelierCalculator nocode#}
{#pointer *BlackDeltaCalculator foreign -> CBlackDeltaCalculator nocode#}
{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}
{#pointer *QlStrikedTypePayoff nocode#}
{#pointer *QlPlainVanillaPayoff nocode#}

-- |discounts a bond's cash flows off a yield term structure
{#fun qlDiscountingBondEngine as discountingBondEngine{withYieldTermStructure*`GenYieldTermStructure y',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |discounts a bond's cash flows off a default-risky curve and a flat recovery rate
{#fun qlRiskyBondEngine as riskyBondEngine{withGenTermStructure*`DefaultProbabilityTermStructure',`Double' -- ^recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |discounts a swap's legs off a single discount curve
{#fun qlDiscountingSwapEngine as discountingSwapEngine{withYieldTermStructure*`GenYieldTermStructure y',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |discounts an FX forward's two legs off their respective currency discount curves
{#fun qlDiscountingFxForwardEngine as discountingFxForwardEngine{withYieldTermStructure*`GenYieldTermStructure y1' -- ^sourceCurrencyDiscountCurve
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^targetCurrencyDiscountCurve
  ,withQuote*`GenQuote q' -- ^spotFx
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- | CVA/DVA-adjusted swap pricing engine. @invstDTS@\/@invstRecoveryRate@ are the
-- own (investor-side) default probability curve and recovery rate for bilateral
-- CVA\/DVA; pass 'Nothing' for @invstDTS@ and @0.999@ for @invstRecoveryRate@ to
-- match upstream's unilateral-CVA-only defaults.
{#fun qlCounterpartyAdjSwapEngine as counterpartyAdjSwapEngine{withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,withQuote*`GenQuote q' -- ^blackVol
  ,withGenTermStructure*`DefaultProbabilityTermStructure' -- ^ctptyDTS
  ,`Double' -- ^ctptyRecoveryRate
  ,withMaybeDefaultProbabilityTermStructure*`Maybe DefaultProbabilityTermStructure' -- ^invstDTS
  ,`Double' -- ^invstRecoveryRate
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for barrier options
{#fun qlAnalyticBarrierEngine as analyticBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for partial-time barrier options
{#fun qlAnalyticPartialTimeBarrierOptionEngine as analyticPartialTimeBarrierOptionEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for American binary barrier options (cash-or-nothing/asset-or-nothing)
{#fun qlAnalyticBinaryBarrierEngine as analyticBinaryBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |/NB/ Timesteps for Cox-Ross-Rubinstein trees are adjusted using the Boyle-Lau algorithm;
-- pass @maxTimeSteps = timeSteps@ to disable it, or @0@ to use the library's default heuristic.
{#fun qlBinomialBarrierEngine as binomialBarrierEngine{`BinomialTree',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^timeSteps
  ,fromIntegral`Word' -- ^maxTimeSteps
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |FX barrier option engine using the vanna-volga method to account for the volatility smile
{#fun qlVannaVolgaBarrierEngine as vannaVolgaBarrierEngine{withGenQuote*`DeltaVolQuote' -- ^atmVol
  ,withGenQuote*`DeltaVolQuote' -- ^vol25Put
  ,withGenQuote*`DeltaVolQuote' -- ^vol25Call
  ,withQuote*`GenQuote q' -- ^spotFX
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^domesticTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^foreignTS
  ,`Bool' -- ^adaptVanDelta
  ,`Double' -- ^bsPriceWithSmile
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for double-barrier European options
{#fun qlAnalyticDoubleBarrierEngine as analyticDoubleBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Int' -- ^series
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |always uses 'AnalyticDoubleBarrierEngine' as the underlying smile-free double-barrier engine
{#fun qlVannaVolgaDoubleBarrierEngine as vannaVolgaDoubleBarrierEngine{withGenQuote*`DeltaVolQuote' -- ^atmVol
  ,withGenQuote*`DeltaVolQuote' -- ^vol25Put
  ,withGenQuote*`DeltaVolQuote' -- ^vol25Call
  ,withQuote*`GenQuote q' -- ^spotFX
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^domesticTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^foreignTS
  ,`Bool' -- ^adaptVanDelta
  ,`Double' -- ^bsPriceWithSmile
  ,fromIntegral`Int' -- ^series
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for double-barrier options using binomial trees
{#fun qlBinomialDoubleBarrierEngine as binomialDoubleBarrierEngine{`BinomialTree',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^timeSteps
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for double-barrier options
{#fun qlMCDoubleBarrierEngine as mcDoubleBarrierEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for Cliquet (ratchet) options
{#fun qlAnalyticCliquetEngine as analyticCliquetEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for compound options
{#fun qlAnalyticCompoundOptionEngine as analyticCompoundOptionEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European continuous fixed-strike lookback options
{#fun qlAnalyticContinuousFixedLookbackEngine as analyticContinuousFixedLookbackEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European continuous floating-strike lookback options
{#fun qlAnalyticContinuousFloatingLookbackEngine as analyticContinuousFloatingLookbackEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European continuous geometric average-price Asian options
{#fun qlAnalyticContinuousGeometricAveragePriceAsianEngine as analyticContinuousGeometricAveragePriceAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for American digital (cash-or-nothing/asset-or-nothing) options
{#fun qlAnalyticDigitalAmericanEngine as analyticDigitalAmericanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European discrete geometric average-price Asian options
{#fun qlAnalyticDiscreteGeometricAveragePriceAsianEngine as analyticDiscreteGeometricAveragePriceAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European discrete geometric average-strike Asian options
{#fun qlAnalyticDiscreteGeometricAverageStrikeAsianEngine as analyticDiscreteGeometricAverageStrikeAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European options with discrete dividends
{#fun qlAnalyticDividendEuropeanEngine as analyticDividendEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withDividendArray*`[Dividend]'&,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic Black-Scholes pricing engine for European options
{#fun qlAnalyticEuropeanEngine as analyticEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for performance (return) options
{#fun qlAnalyticPerformanceEngine as analyticPerformanceEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Black-formula cap\/floor engine, taking an optionlet volatility structure
{#fun qlBlackCapFloorEngine1 as blackCapFloorEngine'{withYieldTermStructure*`GenYieldTermStructure y',withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Black-formula cap\/floor engine, taking a flat volatility quote
{#fun qlBlackCapFloorEngine as blackCapFloorEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',withDayCounter*`DayCounter'
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |shifted-lognormal Black-formula swaption engine, taking a flat volatility quote
{#fun qlBlackSwaptionEngine as blackSwaptionEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',withDayCounter*`DayCounter'
  ,`Double' -- ^displacement
  ,`CashAnnuityModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |shifted-lognormal Black-formula swaption engine, taking a swaption volatility structure
{#fun qlBlackSwaptionEngine1 as blackSwaptionEngine'{withYieldTermStructure*`GenYieldTermStructure y',withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) cap\/floor engine, taking an optionlet volatility structure
{#fun qlBachelierCapFloorEngine1 as bachelierCapFloorEngine'{withYieldTermStructure*`GenYieldTermStructure y',withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) cap\/floor engine, taking a flat volatility quote
{#fun qlBachelierCapFloorEngine as bachelierCapFloorEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) swaption engine, taking a flat volatility quote
{#fun qlBachelierSwaptionEngine as bachelierSwaptionEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',withDayCounter*`DayCounter',`CashAnnuityModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) swaption engine, taking a swaption volatility structure
{#fun qlBachelierSwaptionEngine1 as bachelierSwaptionEngine'{withYieldTermStructure*`GenYieldTermStructure y',withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic European option pricer including stochastic interest rates (Black-Scholes-Merton + Hull-White)
{#fun qlAnalyticBSMHullWhiteEngine as analyticBSMHullWhiteEngine{`Double',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withHullWhite*`HullWhite',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
{#fun qlAnalyticCapFloorEngine as analyticCapFloorEngine{withAffineModel*`AffineModel',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |cap\/floor pricing engine for any one-factor Gaussian short-rate model, evaluated by
-- integration over the model's state variable. As 'gaussian1dSwaptionEngine', without
-- 'Probabilities'.
{#fun qlGaussian1dCapFloorEngine as gaussian1dCapFloorEngine{withGaussian1dModel*`Gaussian1dModel'
  ,fromIntegral`Int' -- ^integrationPoints
  ,`Double' -- ^stddevs
  ,`Bool' -- ^extrapolatePayoff
  ,`Bool' -- ^flatPayoffExtrapolation
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for vanilla options under a GJR-GARCH process
{#fun qlAnalyticGJRGARCHEngine as analyticGJRGARCHEngine{withGenCalibratedModel*`GJRGARCHModel',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic Heston-model pricing engine, integrating with a fixed relative tolerance and evaluation cap
{#fun qlAnalyticHestonEngine as analyticHestonEngine{withHestonModel*`GenHestonModel hm',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic pricing engine combining a Heston equity model with a Hull-White short-rate model
{#fun qlAnalyticHestonHullWhiteEngine as analyticHestonHullWhiteEngine{withHestonModel*`GenHestonModel hm',withHullWhite*`HullWhite'
  ,fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic pricing engine for the Bates (Heston plus jumps) model, integrating with a fixed order
{#fun qlBatesEngine as batesEngine{withBatesModel*`GenBatesModel bm'
  ,fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |FFT-based pricing engine for vanilla options under a Black-Scholes process
{#fun qlFFTVanillaEngine as fftVanillaEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^logStrikeSpacing
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |swaption pricing engine for the G2 two-factor short-rate model, priced via the Black formula
{#fun qlG2SwaptionEngine as g2SwaptionEngine{withG2*`G2',`Double' -- ^range
  ,fromIntegral`Word' -- ^intervals
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |jump-diffusion pricing engine for vanilla options, taking a Merton76 process
{#fun qlJumpDiffusionEngine as jumpDiffusionEngine{withGenStochasticProcess1D*`Merton76Process'
  ,`Double' -- ^relativeAccuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for caps\/floors under a short-rate model
{#fun qlTreeCapFloorEngine as treeCapFloorEngine{withShortRateModel*`GenShortRateModel sm',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for swaptions under a short-rate model
{#fun qlTreeSwaptionEngine as treeSwaptionEngine{withShortRateModel*`GenShortRateModel sm',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for plain vanilla swaps under a short-rate model
{#fun qlTreeVanillaSwapEngine as treeVanillaSwapEngine{withShortRateModel*`GenShortRateModel sm',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for European vanilla options using the Variance Gamma model, integrated numerically
{#fun qlVarianceGammaEngine as varianceGammaEngine{withGenStochasticProcess1D*`VarianceGammaProcess'
  ,`Double' -- ^absoluteError
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic Heston-model pricing engine, integrating with a fixed quadrature order
{#fun qlAnalyticHestonEngine1 as analyticHestonEngine'{withHestonModel*`GenHestonModel hm',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic Heston/Hull-White engine, integrating with a fixed relative tolerance and evaluation cap
{#fun qlAnalyticHestonHullWhiteEngine1 as analyticHestonHullWhiteEngine'{withHestonModel*`GenHestonModel hm',withHullWhite*`HullWhite',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic Bates-model pricing engine, integrating with a fixed relative tolerance and evaluation cap
{#fun qlBatesEngine1 as batesEngine'{withBatesModel*`GenBatesModel bm',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Barone-Adesi and Whaley (1987) quadratic-approximation engine for American options
{#fun qlBaroneAdesiWhaleyApproximationEngine as baroneAdesiWhaleyApproximationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic engine for the Bates model with deterministic jumps, integrating with a fixed relative tolerance and evaluation cap
{#fun qlBatesDetJumpEngine1 as batesDetJumpEngine'{withBatesDetJumpModel*`BatesDetJumpModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic engine for the Bates model with deterministic jumps, integrating with a fixed quadrature order
{#fun qlBatesDetJumpEngine as batesDetJumpEngine{withBatesDetJumpModel*`BatesDetJumpModel',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic engine for the double-exponential-jump Bates model with deterministic jumps, integrating with a fixed relative tolerance and evaluation cap
{#fun qlBatesDoubleExpDetJumpEngine1 as batesDoubleExpDetJumpEngine'{withBatesDoubleExpDetJumpModel*`BatesDoubleExpDetJumpModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic engine for the double-exponential-jump Bates model with deterministic jumps, integrating with a fixed quadrature order
{#fun qlBatesDoubleExpDetJumpEngine as batesDoubleExpDetJumpEngine{withBatesDoubleExpDetJumpModel*`BatesDoubleExpDetJumpModel',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic engine for the double-exponential-jump Bates model, integrating with a fixed relative tolerance and evaluation cap
{#fun qlBatesDoubleExpEngine1 as batesDoubleExpEngine'{withBatesDoubleExpModel*`GenBatesDoubleExpModel bdem',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |semi-analytic engine for the double-exponential-jump Bates model, integrating with a fixed quadrature order
{#fun qlBatesDoubleExpEngine as batesDoubleExpEngine{withBatesDoubleExpModel*`GenBatesDoubleExpModel bdem',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bjerksund and Stensland (1993) approximation engine for American options
{#fun qlBjerksundStenslandApproximationEngine as bjerksundStenslandApproximationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |CDS pricing engine that integrates the default-leg payoff over the CDS's step-wise schedule
{#fun qlIntegralCdsEngine as integralCdsEngine{fromEnumQuantity`(Word,TimeUnit)'& -- ^integrationStep
  ,withGenTermStructure*`DefaultProbabilityTermStructure',`Double' -- ^recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for European vanilla options using an integral approach
{#fun qlIntegralEngine as integralEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
{#fun qlJamshidianSwaptionEngine as jamshidianSwaptionEngine{withOneFactorAffineModel*`GenOneFactorAffineModel om',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |swaption pricing engine for any one-factor Gaussian short-rate model, evaluated by integration over the model's state variable
{#fun qlGaussian1dSwaptionEngine as gaussian1dSwaptionEngine{withGaussian1dModel*`Gaussian1dModel'
  ,fromIntegral`Int' -- ^integrationPoints
  ,`Double' -- ^stddevs
  ,`Bool' -- ^extrapolatePayoff
  ,`Bool' -- ^flatPayoffExtrapolation
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,`Probabilities' -- ^probabilities
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |As 'gaussian1dSwaptionEngine', for a 'QuantLib.Instrument.Swap.NonstandardSwaption'. Adds
-- an optional OAS ('oas', continuously compounded w.r.t. the discount curve's day counter) on
-- top of the shared parameters.
{#fun qlGaussian1dNonstandardSwaptionEngine as gaussian1dNonstandardSwaptionEngine{withGaussian1dModel*`Gaussian1dModel'
  ,fromIntegral`Int' -- ^integrationPoints
  ,`Double' -- ^stddevs
  ,`Bool' -- ^extrapolatePayoff
  ,`Bool' -- ^flatPayoffExtrapolation
  ,withMaybeQuote*`Maybe (GenQuote q)' -- ^oas
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,`Probabilities' -- ^probabilities
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |As 'gaussian1dNonstandardSwaptionEngine', for a
-- 'QuantLib.Instrument.Swap.FloatFloatSwaption'. Adds 'includeTodaysExercise' -- whether a
-- fixing due exactly \"today\" counts as part of the exercise-into leg.
{#fun qlGaussian1dFloatFloatSwaptionEngine as gaussian1dFloatFloatSwaptionEngine{withGaussian1dModel*`Gaussian1dModel'
  ,fromIntegral`Int' -- ^integrationPoints
  ,`Double' -- ^stddevs
  ,`Bool' -- ^extrapolatePayoff
  ,`Bool' -- ^flatPayoffExtrapolation
  ,withMaybeQuote*`Maybe (GenQuote q)' -- ^oas
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,`Bool' -- ^includeTodaysExercise
  ,`Probabilities' -- ^probabilities
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |swaption pricing engine using Jamshidian's decomposition, for any one-factor Gaussian
-- short-rate model.
{#fun qlGaussian1dJamshidianSwaptionEngine as gaussian1dJamshidianSwaptionEngine{withGaussian1dModel*`Gaussian1dModel',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Ju (1999) quadratic-approximation engine for American options
{#fun qlJuQuadraticApproximationEngine as juQuadraticApproximationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for a spread option on two futures/assets
{#fun qlKirkEngine as kirkEngine{withBlackProcess*`BlackProcess',withBlackProcess*`BlackProcess',`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |CDS pricing engine using the mid-point approximation, evaluating the default leg at the mid-point of each accrual period
{#fun qlMidPointCdsEngine as midPointCdsEngine{withGenTermStructure*`DefaultProbabilityTermStructure',`Double' -- ^recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |CDS pricing engine implementing the ISDA standard model
{#fun qlIsdaCdsEngine as isdaCdsEngine{withGenTermStructure*`DefaultProbabilityTermStructure',`Double' -- ^recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,`NumericalFix' -- ^numericalFix
  ,`AccrualBias' -- ^accrualBias
  ,`ForwardsInCouponPeriod' -- ^forwardsInCouponPeriod
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |variance-swap pricing engine using a replicating portfolio of vanilla options at the given strikes
{#fun qlReplicatingVarianceSwapEngine as replicatingVarianceSwapEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^dk
  ,withDoubleArray*`[Double]'& -- ^callStrikes
  ,withDoubleArray*`[Double]'& -- ^putStrikes
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for 2D European basket options (Stulz formula)
{#fun qlStulzEngine as stulzEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Libor forward model swaption engine, priced via the Black formula
{#fun qlLfmSwaptionEngine as lfmSwaptionEngine{withGenCalibratedModel*`LiborForwardModel',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for caps\/floors under a short-rate model, on an explicit time grid
{#fun qlTreeCapFloorEngine1 as treeCapFloorEngine'{withShortRateModel*`GenShortRateModel sm',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for swaptions under a short-rate model, on an explicit time grid
{#fun qlTreeSwaptionEngine1 as treeSwaptionEngine'{withShortRateModel*`GenShortRateModel sm',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for plain vanilla swaps under a short-rate model, on an explicit time grid
{#fun qlTreeVanillaSwapEngine1 as treeVanillaSwapEngine'{withShortRateModel*`GenShortRateModel sm',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign -> CLocalVolTermStructure' nocode#}
{#pointer *QlFdmQuantoHelper as FdmQuantoHelper foreign -> CFdmQuantoHelper nocode#}

-- |Snapshots @rTS@/@fTS@/@fxVolTS@ at construction time (their underlying @shared_ptr@s are copied
-- out of their handles): a later relink of a 'RelinkableYieldTermStructure' or
-- 'RelinkableBlackVolTermStructure' passed in here will /not/ be reflected in this 'FdmQuantoHelper'.
{#fun qlFdmQuantoHelper as fdmQuantoHelper{withYieldTermStructure*`GenYieldTermStructure y1' -- ^rTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^fTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^fxVolTS
  ,`Double' -- ^equityFxCorrelation
  ,`Double' -- ^exchRateATMlevel
  ,preErrorCheck-`String'errorCheck*-}->`FdmQuantoHelper'peekFdmQuantoHelper*#}

{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}

-- |finite-differences swaption pricing engine for the G2 two-factor short-rate model
{#fun qlFdG2SwaptionEngine as fdG2SwaptionEngine{withG2*`G2',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^yGrid
  ,fromIntegral`Word' -- ^dampingSpecs
  ,`Double' -- ^invEps
  ,withFdmSchemeDesc*`FdmScheme',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences swaption pricing engine for the Hull-White short-rate model
{#fun qlFdHullWhiteSwaptionEngine as fdHullWhiteSwaptionEngine{withHullWhite*`HullWhite',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^dampingSpecs
  ,`Double' -- ^invEps
  ,withFdmSchemeDesc*`FdmScheme',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Black-Scholes barrier-option pricing engine
{#fun qlFdBlackScholesBarrierEngine as fdBlackScholesBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,`Bool' -- ^localVol
  ,`Double' -- ^illegalLocalVolOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model barrier-option pricing engine
{#fun qlFdHestonBarrierEngine as fdHestonBarrierEngine{withHestonModel*`GenHestonModel hm',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model barrier-option pricing engine, with discrete dividends
{#fun qlFdHestonBarrierEngine1 as fdHestonBarrierEngine'{withHestonModel*`GenHestonModel hm',withDividendArray*`[Dividend]'&
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model double-barrier-option pricing engine
{#fun qlFdHestonDoubleBarrierEngine as fdHestonDoubleBarrierEngine{withHestonModel*`GenHestonModel hm',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |/NB/ C++ classes Monte Carlo engines are additionally parameterised via statistic template argument
-- Functions below use default value of Statistics
{#fun qlMCHestonHullWhiteEngine1 as mcHestonHullWhiteEngine{`RngTrait',withGenStochasticProcess*`HybridHestonHullWhiteProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,`Bool' -- ^controlVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word'-- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo (least-squares) pricing engine for American options
{#fun qlMCAmericanEngine1 as mcAmericanEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word', -- ^timeSteps
  fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,`Bool' -- ^controlVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,fromIntegral`Word' -- ^polynomOrder
  ,`PolynomialType',fromMaybeInt`Maybe Word' -- ^nCalibrationSamples
  ,fromMaybeBool`Maybe Bool' -- ^antitheticVariateCalibration
  ,fromMaybeInt`Maybe Word' -- ^seedCalibration
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for barrier options
{#fun qlMCBarrierEngine1 as mcBarrierEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,`Bool' -- ^isBiased
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for digital (cash-or-nothing/asset-or-nothing) options
{#fun qlMCDigitalEngine1 as mcDigitalEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word', -- ^timeStepsPerYear
  `Bool', -- ^brownianBridge
  `Bool', -- ^antitheticVariate
  fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for discrete arithmetic average-price Asian options
{#fun qlMCDiscreteArithmeticAPEngine1 as mcDiscreteArithmeticAPEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,`Bool' -- ^controlVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for discrete arithmetic average-strike Asian options
{#fun qlMCDiscreteArithmeticASEngine1 as mcDiscreteArithmeticASEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for discrete geometric average-price Asian options
{#fun qlMCDiscreteGeometricAPEngine1 as mcDiscreteGeometricAPEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for European options under a Black-Scholes process
{#fun qlMCEuropeanEngine1 as mcEuropeanEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for European options under a GJR-GARCH process
{#fun qlMCEuropeanGJRGARCHEngine1 as mcEuropeanGJRGARCHEngine{`RngTrait',withGenStochasticProcess*`GJRGARCHProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for European options under a Heston process
{#fun qlMCEuropeanHestonEngine1 as mcEuropeanHestonEngine{`RngTrait',withHestonProcess*`GenHestonProcess hp',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Prices a 'VarianceOption' by integrating its payoff against the Heston-model transition density.
{#fun qlIntegralHestonVarianceOptionEngine as integralHestonVarianceOptionEngine{withHestonProcess*`GenHestonProcess hp',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo Hull-White pricing engine for caps\/floors
{#fun qlMCHullWhiteCapFloorEngine1 as mcHullWhiteCapFloorEngine{`RngTrait',withHullWhite*`HullWhite',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for 'himalayaOption'
{#fun qlMCHimalayaEngine1 as mcHimalayaEngine{`RngTrait',withGenStochasticProcess*`StochasticProcessArray',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for 'pagodaOption'
{#fun qlMCPagodaEngine1 as mcPagodaEngine{`RngTrait',withGenStochasticProcess*`StochasticProcessArray',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for performance (return) options
{#fun qlMCPerformanceEngine1 as mcPerformanceEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |variance-swap pricing engine using Monte Carlo simulation
{#fun qlMCVarianceSwapEngine1 as mcVarianceSwapEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for vanilla options using binomial trees
{#fun qlBinomialVanillaEngine as binomialVanillaEngine{`BinomialTree',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^timeSteps
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Black-Scholes pricing engine for vanilla options
{#fun qlFdBlackScholesVanillaEngine as fdBlackScholesVanillaEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^timeSteps
  ,fromIntegral`Word' -- ^gridPoints
  ,fromIntegral`Word' -- ^timeDependent
  ,withFdmSchemeDesc*`FdmScheme'
  ,`Bool' -- ^localVol
  ,`Double' -- ^illegalLocalVolOverwrite
  ,`CashDividendModel' -- ^cashDividendModel
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options
{#fun qlFdHestonVanillaEngine as fdHestonVanillaEngine{withHestonModel*`GenHestonModel hm',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options, with discrete dividends
{#fun qlFdHestonVanillaEngine1 as fdHestonVanillaEngine'{withHestonModel*`GenHestonModel hm',withDividendArray*`[Dividend]'&
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options, with quanto adjustment
{#fun qlFdHestonVanillaEngine2 as fdHestonVanillaEngineQuanto{withHestonModel*`GenHestonModel hm',withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options, with discrete dividends and quanto adjustment
{#fun qlFdHestonVanillaEngine3 as fdHestonVanillaEngineQuanto'{withHestonModel*`GenHestonModel hm',withDividendArray*`[Dividend]'&,withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences pricing engine for vanilla options combining a Heston equity model with a Hull-White short-rate model
{#fun qlFdHestonHullWhiteVanillaEngine as fdHestonHullWhiteVanillaEngine{withHestonModel*`GenHestonModel hm',withGenStochasticProcess1D*`HullWhiteProcess'
  ,`Double' -- ^corrEquityShortRate
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^rGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,`Bool' -- ^controlVariate, upstream default: true
  ,withFdmSchemeDesc*`FdmScheme'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences pricing engine for vanilla options combining a Heston equity model with a Hull-White short-rate model, with discrete dividends
{#fun qlFdHestonHullWhiteVanillaEngine1 as fdHestonHullWhiteVanillaEngine'{withHestonModel*`GenHestonModel hm',withGenStochasticProcess1D*`HullWhiteProcess',withDividendArray*`[Dividend]'&
  ,`Double' -- ^corrEquityShortRate
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^rGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,`Bool' -- ^controlVariate, upstream default: true
  ,withFdmSchemeDesc*`FdmScheme'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |binomial Tsiveriotis-Fernandes pricing engine for convertible bonds
{#fun qlBinomialConvertibleEngine as binomialConvertibleEngine{`BinomialTree',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,fromIntegral`Word' -- ^timeSteps
  ,withQuote*`GenQuote q' -- ^creditSpread
  ,withDividendArray*`[Dividend]'& -- ^dividends
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableFixedRateBondEngine1 as blackCallableFixedRateBondEngine'{withGenTermStructure*`CallableBondVolatilityStructure',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableFixedRateBondEngine as blackCallableFixedRateBondEngine{withQuote*`GenQuote q',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine1 as blackCallableZeroCouponBondEngine'{withGenTermStructure*`CallableBondVolatilityStructure',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine as blackCallableZeroCouponBondEngine{withQuote*`GenQuote q',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for callable fixed-rate bonds, on an explicit time grid
{#fun qlTreeCallableFixedRateBondEngine1 as treeCallableFixedRateBondEngine'{withShortRateModel*`GenShortRateModel sm',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for callable fixed-rate bonds
{#fun qlTreeCallableFixedRateBondEngine as treeCallableFixedRateBondEngine{withShortRateModel*`GenShortRateModel sm',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for callable zero coupon bonds, on an explicit time grid
{#fun qlTreeCallableZeroCouponBondEngine1 as treeCallableZeroCouponBondEngine'{withShortRateModel*`GenShortRateModel sm',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |numerical-lattice pricing engine for callable zero coupon bonds
{#fun qlTreeCallableZeroCouponBondEngine as treeCallableZeroCouponBondEngine{withShortRateModel*`GenShortRateModel sm',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |intermediate value N'(d1) (or its sign-flipped equivalent) used internally to derive the calculator's Greeks
{#fun qlBlackCalculatorAlpha as alpha{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |intermediate value N'(d2) (or its sign-flipped equivalent) used internally to derive the calculator's Greeks
{#fun qlBlackCalculatorBeta as beta{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 option-price calculator, from the option type and strike directly
{#fun qlBlackCalculator1 as blackCalculator'{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalculator'peekBlackCalculator*#}

-- |Black 1976 option-price calculator, from a striked payoff
{#fun qlBlackCalculator as blackCalculator{withStrikedPayoff*`StrikedPayoff'
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalculator'peekBlackCalculator*#}

-- |Sensitivity to change in the underlying spot price.
{#fun qlBlackCalculatorDelta as blackDelta{withBlackCalculator*`GenBlackCalculator bc', `Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to change in the underlying forward price.
{#fun qlBlackCalculatorDeltaForward as deltaForward{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to dividend/growth rate.
{#fun qlBlackCalculatorDividendRho as dividendRho{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity in percent to a percent change in the underlying spot price.
{#fun qlBlackCalculatorElasticity as blackElasticity{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity in percent to a percent change in the underlying forward price.
{#fun qlBlackCalculatorElasticityForward as elasticityForward{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second order derivative with respect to change in the underlying spot price.
{#fun qlBlackCalculatorGamma as blackGamma{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second order derivative with respect to change in the underlying forward price.
{#fun qlBlackCalculatorGammaForward as gammaForward{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
{#fun qlBlackCalculatorItmAssetProbability as itmAssetProbability{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability of being in the money in the bond martingale measure, i.e. N(d2). It is a risk-neutral probability, not the real world one.
{#fun qlBlackCalculatorItmCashProbability as itmCashProbability{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to discounting rate.
{#fun qlBlackCalculatorRho as rho{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to strike.
{#fun qlBlackCalculatorStrikeSensitivity as strikeSensitivity{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |gamma w.r.t. strike.
{#fun qlBlackCalculatorStrikeGamma as strikeGamma{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to time to maturity.
{#fun qlBlackCalculatorTheta as blackTheta{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to time to maturity per day, assuming 365 day per year.
{#fun qlBlackCalculatorThetaPerDay as blackThetaPerDay{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the option's fair value
{#fun qlBlackCalculatorValue as value{withBlackCalculator*`GenBlackCalculator bc',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of vega to spot (Vanna).
{#fun qlBlackCalculatorVanna as vanna{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to volatility.
{#fun qlBlackCalculatorVega as vega{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of vega to volatility (Volga).
{#fun qlBlackCalculatorVolga as volga{withBlackCalculator*`GenBlackCalculator bc',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black-Scholes-Merton option-price calculator, from the option type and strike directly
{#fun qlBlackScholesCalculator1 as blackScholesCalculator'{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^spot
  ,`Double' -- ^growth
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackScholesCalculator'peekBlackScholesCalculator*#}

-- |Black-Scholes-Merton option-price calculator, from a striked payoff and spot price
{#fun qlBlackScholesCalculator as blackScholesCalculator{withStrikedPayoff*`StrikedPayoff',`Double' -- ^spot
  ,`Double' -- ^growth
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackScholesCalculator'peekBlackScholesCalculator*#}

-- |Sensitivity to change in the underlying spot price.
{#fun qlBlackScholesCalculatorDelta as blackScholesDelta{withGenBlackCalculator*`BlackScholesCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity in percent to a percent change in the underlying spot price.
{#fun qlBlackScholesCalculatorElasticity as blackScholesElasticity{withGenBlackCalculator*`BlackScholesCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second order derivative with respect to change in the underlying spot price.
{#fun qlBlackScholesCalculatorGamma as blackScholesGamma{withGenBlackCalculator*`BlackScholesCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to time to maturity.
{#fun qlBlackScholesCalculatorTheta as blackScholesTheta{withGenBlackCalculator*`BlackScholesCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to time to maturity per day (assuming 365 day in a year).
{#fun qlBlackScholesCalculatorThetaPerDay as blackScholesThetaPerDay{withGenBlackCalculator*`BlackScholesCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier (normal-model) analogue of 'BlackCalculator', for options on a rate rather than a
-- price. No subclass hierarchy upstream, unlike BlackCalculator\/BlackScholesCalculator, so this
-- is a single leaf type with its own methods rather than a 'GenBlackCalculator' instance.
{#fun qlBachelierCalculator1 as bachelierCalculator'{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BachelierCalculator'peekBachelierCalculator*#}

-- |Bachelier (normal-model) option-price calculator, from a striked payoff
{#fun qlBachelierCalculator as bachelierCalculator{withStrikedPayoff*`StrikedPayoff'
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BachelierCalculator'peekBachelierCalculator*#}

-- |intermediate value used internally to derive the calculator's Greeks
{#fun qlBachelierCalculatorAlpha as bachelierAlpha{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |intermediate value used internally to derive the calculator's Greeks
{#fun qlBachelierCalculatorBeta as bachelierBeta{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to change in the underlying spot price.
{#fun qlBachelierCalculatorDelta as bachelierDelta{withBachelierCalculator*`BachelierCalculator', `Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to change in the underlying forward price.
{#fun qlBachelierCalculatorDeltaForward as bachelierDeltaForward{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to dividend/growth rate.
{#fun qlBachelierCalculatorDividendRho as bachelierDividendRho{withBachelierCalculator*`BachelierCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity in percent to a percent change in the underlying spot price.
{#fun qlBachelierCalculatorElasticity as bachelierElasticity{withBachelierCalculator*`BachelierCalculator',`Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity in percent to a percent change in the underlying forward price.
{#fun qlBachelierCalculatorElasticityForward as bachelierElasticityForward{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second order derivative with respect to change in the underlying spot price.
{#fun qlBachelierCalculatorGamma as bachelierGamma{withBachelierCalculator*`BachelierCalculator',`Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Second order derivative with respect to change in the underlying forward price.
{#fun qlBachelierCalculatorGammaForward as bachelierGammaForward{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability of being in the money in the asset martingale measure, i.e. N(d). It is a risk-neutral probability, not the real world one.
{#fun qlBachelierCalculatorItmAssetProbability as bachelierItmAssetProbability{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability of being in the money in the bond martingale measure, i.e. N(d). It is a risk-neutral probability, not the real world one.
{#fun qlBachelierCalculatorItmCashProbability as bachelierItmCashProbability{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to discounting rate.
{#fun qlBachelierCalculatorRho as bachelierRho{withBachelierCalculator*`BachelierCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to strike.
{#fun qlBachelierCalculatorStrikeSensitivity as bachelierStrikeSensitivity{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |gamma w.r.t. strike.
{#fun qlBachelierCalculatorStrikeGamma as bachelierStrikeGamma{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to time to maturity.
{#fun qlBachelierCalculatorTheta as bachelierTheta{withBachelierCalculator*`BachelierCalculator',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to time to maturity per day, assuming 365 day per year.
{#fun qlBachelierCalculatorThetaPerDay as bachelierThetaPerDay{withBachelierCalculator*`BachelierCalculator',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the option's fair value
{#fun qlBachelierCalculatorValue as bachelierValue{withBachelierCalculator*`BachelierCalculator',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of vega to spot (Vanna).
{#fun qlBachelierCalculatorVanna as bachelierVanna{withBachelierCalculator*`BachelierCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity to volatility.
{#fun qlBachelierCalculatorVega as bachelierVega{withBachelierCalculator*`BachelierCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sensitivity of vega to volatility (Volga).
{#fun qlBachelierCalculatorVolga as bachelierVolga{withBachelierCalculator*`BachelierCalculator',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |computes the strike given the option's Black-Scholes delta (in an FX-style delta/vol quotation)
{#fun qlBlackDeltaCalculator as blackDeltaCalculator{fromEnumC`OptionType'
  ,fromEnumC`DeltaType'
  ,`Double' -- ^spot
  ,`Double' -- ^dDiscount (domestic discount factor)
  ,`Double' -- ^fDiscount (foreign discount factor)
  ,`Double' -- ^stdDev
  ,preErrorCheck-`String'errorCheck*-}->`BlackDeltaCalculator'peekBlackDeltaCalculator*#}

-- |the option delta under the calculator's chosen convention, for the given strike
{#fun qlBlackDeltaCalculatorDeltaFromStrike as deltaFromStrike{withBlackDeltaCalculator*`BlackDeltaCalculator',`Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the strike price corresponding to the given option delta (under the calculator's chosen convention)
{#fun qlBlackDeltaCalculatorStrikeFromDelta as strikeFromDelta{withBlackDeltaCalculator*`BlackDeltaCalculator',`Double' -- ^delta
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the at-the-money strike under the given ATM convention, independent of the strike passed at construction
{#fun qlBlackDeltaCalculatorAtmStrike as atmStrike{withBlackDeltaCalculator*`BlackDeltaCalculator',fromEnumC`AtmType'
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormula1 as blackFormula'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormula as blackFormula{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}


-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaCashItmProbability1 as blackCashItmProbability'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaCashItmProbability as blackCashItmProbability{fromEnumC`OptionType',`Double'
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaImpliedStdDev1 as blackImpliedStdDev'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaImpliedStdDev as blackImpliedStdDev{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
{#fun qlQuantLibBlackFormulaImpliedStdDevApproximation1 as blackImpliedStdDevApproximation'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
{#fun qlQuantLibBlackFormulaImpliedStdDevApproximation as blackImpliedStdDevApproximation{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
{#fun qlQuantLibBlackFormulaStdDevDerivative1 as blackStdDevDerivative'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
{#fun qlQuantLibBlackFormulaStdDevDerivative as blackStdDevDerivative{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for derivative with respect to implied vol, this is basically the vega, but if you want 1% change multiply by 1%
{#fun qlQuantLibBlackFormulaVolDerivative as blackVolDerivative{`Double',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
{#fun qlQuantLibBachelierBlackFormula1 as bachelierBlackFormula'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
{#fun qlQuantLibBachelierBlackFormula as bachelierBlackFormula{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |default theta-per-day calculation
{#fun qlQuantLibDefaultThetaPerDay as defaultThetaPerDay{`Double' -- ^theta
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |lognormal SABR volatility, no validity checks on the parameters
{#fun qlUnsafeSabrLogNormalVolatility as unsafeSabrLogNormalVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |shifted SABR volatility (lognormal or normal), no validity checks on the parameters
{#fun qlUnsafeShiftedSabrVolatility as unsafeShiftedSabrVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |normal SABR volatility, no validity checks on the parameters
{#fun qlUnsafeSabrNormalVolatility as unsafeSabrNormalVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |SABR volatility (lognormal or normal), no validity checks on the parameters
{#fun qlUnsafeSabrVolatility as unsafeSabrVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |SABR volatility (lognormal or normal), with validity checks on the parameters
{#fun qlSabrVolatility as sabrVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |shifted SABR volatility (lognormal or normal), with validity checks on the parameters
{#fun qlShiftedSabrVolatility as shiftedSabrVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |lognormal SABR volatility using the Floc'h-Kennedy formula, with validity checks on the parameters
{#fun qlSabrFlochKennedyVolatility as sabrFlochKennedyVolatility{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |validate SABR parameters, throwing if they are not acceptable
{#fun qlValidateSabrParameters as validateSabrParameters{`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |initial guess (alpha, beta, nu, rho) for SABR calibration, per Le Floc'h and Kennedy
{#fun qlSabrGuess as sabrGuess{`Double' -- ^k_m
  ,`Double' -- ^vol_m
  ,`Double' -- ^k_0
  ,`Double' -- ^vol_0
  ,`Double' -- ^k_p
  ,`Double' -- ^vol_p
  ,`Double' -- ^forward
  ,`Double' -- ^expiryTime
  ,`Double' -- ^beta
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
