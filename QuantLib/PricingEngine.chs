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
  , SolverType(..)
  , FixedPointEquation(..)
  , QdFpScheme(..)
  , FdmQuantoHelper

  , GenBlackCalculator
  , asBlackCalculator

  , discountingBondEngine
  , riskyBondEngine
  , discountingSwapEngine
  , discountingFxForwardEngine
  , discountingConstNotionalCrossCurrencySwapEngine
  , counterpartyAdjSwapEngine
  , PerpetualFuturesInterpolationType(..)
  , discountingPerpetualFuturesEngine

  , analyticBarrierEngine
  , analyticTwoAssetBarrierEngine
  , analyticSoftBarrierEngine
  , analyticPartialTimeBarrierOptionEngine
  , analyticBinaryBarrierEngine
  , analyticSimpleChooserEngine
  , analyticComplexChooserEngine
  , analyticTwoAssetCorrelationEngine
  , analyticEuropeanMargrabeEngine
  , analyticAmericanMargrabeEngine
  , analyticWriterExtensibleOptionEngine
  , analyticHolderExtensibleOptionEngine
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
  , analyticContinuousPartialFloatingLookbackEngine
  , analyticContinuousPartialFixedLookbackEngine
  , analyticContinuousGeometricAveragePriceAsianEngine
  , mcLookbackFixedEngine
  , mcLookbackFloatingEngine
  , mcLookbackPartialFixedEngine
  , mcLookbackPartialFloatingEngine
  , analyticDigitalAmericanEngine
  , analyticDigitalAmericanKOEngine
  , analyticDiscreteGeometricAveragePriceAsianEngine
  , analyticDiscreteGeometricAverageStrikeAsianEngine
  , turnbullWakemanAsianEngine
  , fdBlackScholesAsianEngine
  , analyticDividendEuropeanEngine
  , analyticEuropeanEngine
  , analyticPerformanceEngine
  , forwardEuropeanEngine
  , forwardBaroneAdesiWhaleyEngine
  , forwardBjerksundStenslandEngine
  , forwardFdBlackScholesVanillaEngine
  , mcForwardEuropeanBSEngine
  , mcForwardEuropeanHestonEngine
  , analyticHestonForwardEuropeanEngine
  , quantoEuropeanEngine
  , quantoForwardEuropeanEngine
  , quantoForwardPerformanceEuropeanEngine
  , quantoBarrierEngine
  , quantoDoubleBarrierEngine
  , blackCapFloorEngine'
  , blackCapFloorEngine
  , blackSwaptionEngine
  , haganIrregularSwaptionEngine
  , blackSwaptionEngine'
  , bachelierCapFloorEngine'
  , bachelierCapFloorEngine
  , yoyInflationBlackCapFloorEngine
  , yoyInflationUnitDisplacedBlackCapFloorEngine
  , yoyInflationBachelierCapFloorEngine
  , interpolatingCPICapFloorEngine
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
  , mcEuropeanBasketEngine
  , mcEverestEngine
  , mcAmericanBasketEngine
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
  , qdPlusAmericanEngine
  , qdFpAmericanEngine
  , continuousArithmeticAsianVecerEngine
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
  , midPointCDOEngine
  , integralCDOEngine
  , integralNtdEngine
  , replicatingVarianceSwapEngine
  , stulzEngine
  , bjerksundStenslandSpreadEngine
  , OperatorSplittingOrder(..)
  , operatorSplittingSpreadEngine
  , pearsonSpreadEngine
  , gaussianCopulaSpreadEngine
  , fd2dBlackScholesVanillaEngine
  , choiBasketEngine
  , dengLiZhouBasketEngine
  , fdndimBlackScholesVanillaEngine
  , fdndimBlackScholesVanillaEngine'
  , singleFactorBsmBasketEngine
  , lfmSwaptionEngine
  , treeCapFloorEngine'
  , treeSwaptionEngine'
  , treeVanillaSwapEngine'

  , fdG2SwaptionEngine
  , fdHullWhiteSwaptionEngine
  , binomialVanillaEngine
  , fdBlackScholesVanillaEngine
  , fdBlackScholesVanillaEngine'
  , fdBlackScholesVanillaEngineQuanto
  , fdBlackScholesVanillaEngineQuanto'
  , fdmQuantoHelper
  , fdmQuantoHelperQuantoAdjustment
  , fdHestonVanillaEngine
  , fdHestonVanillaEngine'
  , cosHestonEngine
  , analyticPdfHestonEngine
  , fdBatesVanillaEngine
  , fdBatesVanillaEngine'
  , fdBlackScholesShoutEngine
  , fdBlackScholesShoutEngine'
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
  , blackForwardDerivative'
  , blackForwardDerivative
  , blackImpliedStdDevChambers'
  , blackImpliedStdDevChambers
  , blackImpliedStdDevApproximationRS'
  , blackImpliedStdDevApproximationRS
  , blackImpliedStdDevLiRS'
  , blackImpliedStdDevLiRS
  , blackAssetItmProbability'
  , blackAssetItmProbability
  , blackStdDevSecondDerivative'
  , blackStdDevSecondDerivative
  , bachelierForwardDerivative'
  , bachelierForwardDerivative
  , bachelierImpliedVol
  , bachelierImpliedVolChoi
  , bachelierStdDevDerivative'
  , bachelierStdDevDerivative
  , bachelierAssetItmProbability'
  , bachelierAssetItmProbability
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
#include "qlEnumObjects.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.Math#}
{#import QuantLib.Quote#}(DeltaType, AtmType)
{#import QuantLib.Instrument.Option#} hiding(itmCashProbability, deltaForward, strikeSensitivity, dividendRho, rho, vega)
import QuantLib.Internal.Common
import Data.List.NonEmpty(NonEmpty, toList)

{#enum CashAnnuityModel{} deriving(Show, Eq, Read)#}
{#enum Probabilities{} deriving(Show, Eq, Read)#}
{#enum CashDividendModel{} add prefix="CashDividend" deriving(Show, Eq, Read)#}
{#enum NumericalFix{} deriving(Show, Eq, Read)#}
{#enum AccrualBias{} deriving(Show, Eq, Read)#}
{#enum ForwardsInCouponPeriod{} deriving(Show, Eq, Read)#}
{#enum SolverType{} deriving(Show, Eq, Read)#}
{#enum FixedPointEquation{} deriving(Show, Eq, Read)#}
{#enum QdFpScheme{} deriving(Show, Eq, Read)#}
{#enum OperatorSplittingOrder{} deriving(Show, Eq, Read)#}
{#enum PerpetualFuturesInterpolationType{} deriving(Show, Eq, Read)#}

{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}

{#pointer *QlDividend as Dividend foreign -> CDividend nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign -> CCallableBondVolatilityStructure' nocode#}
{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}
{#pointer *QlYoYOptionletVolatilitySurface as YoYOptionletVolatilitySurface foreign -> CYoYOptionletVolatilitySurface' nocode#}
{#pointer *QlYoYInflationIndex as YoYInflationIndex foreign -> CYoYInflationIndex' nocode#}
{#pointer *QlCPICapFloorTermPriceSurface as CPICapFloorTermPriceSurface foreign -> CCPICapFloorTermPriceSurface' nocode#}

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

-- |Discounts perpetual-futures cashflows to the curves' reference date. The
-- three funding vectors must be non-empty and have identical lengths. The
-- engine supports only 'PerpetualFuturesLinear' and 'PerpetualFuturesInverse'
-- payoffs; QuantLib rejects a Quanto payoff at pricing time.
discountingPerpetualFuturesEngine
  :: GenYieldTermStructure y1 -> GenYieldTermStructure y2 -> GenQuote q
  -> NonEmpty (Double, Double, Double) -- ^@(fundingTime, fundingRate, interestRateDiff)@
  -> PerpetualFuturesInterpolationType -> Double -> IO PricingEngine
discountingPerpetualFuturesEngine domestic foreignCurve spot funding interpolation maxT =
  qlDiscountingPerpetualFuturesEngine domestic foreignCurve spot times rates diffs interpolation maxT
  where (times, rates, diffs) = unzip3 (toList funding)

{#fun qlDiscountingPerpetualFuturesEngine{
   withYieldTermStructure*`GenYieldTermStructure y1' -- ^domesticDiscountCurve
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^foreignDiscountCurve
  ,withQuote*`GenQuote q' -- ^assetSpot
  ,withDoubleArray*`[Double]'& -- ^fundingTimes
  ,withDoubleArray*`[Double]'& -- ^fundingRates
  ,withDoubleArray*`[Double]'& -- ^interestRateDiffs
  ,fromEnumC`PerpetualFuturesInterpolationType' -- ^fundingInterpType
  ,`Double' -- ^maxT
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

-- |Discounts each leg of a 'QuantLib.Instrument.Swap.ConstNotionalCrossCurrencySwap' (or either
-- of its two leaves) off its own currency's discount curve, converting to @domesticCcy@ via
-- @spotFX@ (quoted as units of @domesticCcy@ per unit of @foreignCcy@, w.r.t. a settlement equal
-- to the npv date unless @spotFXSettleDate@ says otherwise). Each leg's stored currency must equal
-- @domesticCcy@ or @foreignCcy@; the two discount curves must share the same reference date.
{#fun qlDiscountingConstNotionalCrossCurrencySwapEngine as discountingConstNotionalCrossCurrencySwapEngine{withCurrency*`Currency' -- ^domesticCcy
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^domesticCcyDiscountCurve
  ,withCurrency*`Currency' -- ^foreignCcy
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^foreignCcyDiscountCurve
  ,withQuote*`GenQuote q' -- ^spotFX
  ,fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,withMaybeDay*`Maybe Day' -- ^spotFXSettleDate
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

-- |analytic (Heynen and Kat) pricing engine for a barrier option on two assets, where the first asset's value is compared to the strike and the second's is monitored against the barrier
{#fun qlAnalyticTwoAssetBarrierEngine as analyticTwoAssetBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process1
  ,withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process2
  ,withQuote*`GenQuote q' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for soft barrier options, knocked in/out proportionally over a barrier range
{#fun qlAnalyticSoftBarrierEngine as analyticSoftBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for simple chooser options
{#fun qlAnalyticSimpleChooserEngine as analyticSimpleChooserEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Analytic Black-Scholes engine for a 'complexChooserOption'. Both alternatives must have European exercise.
{#fun qlAnalyticComplexChooserEngine as analyticComplexChooserEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for two-asset correlation options
{#fun qlAnalyticTwoAssetCorrelationEngine as analyticTwoAssetCorrelationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process1
  ,withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process2
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Analytic (Margrabe) engine for a European 'margrabeOption': the closed-form price of an
-- option to exchange one asset for another, from W. Margrabe, \"The Value of an Option to
-- Exchange One Asset for Another\", Journal of Finance 33 (March 1978), 177-186.
{#fun qlAnalyticEuropeanMargrabeEngine as analyticEuropeanMargrabeEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process1
  ,withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process2
  ,`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Analytic (Margrabe) engine for an American 'margrabeOption': the closed-form price of an
-- option to exchange one asset for another with early exercise, from W. Margrabe, \"The Value
-- of an American Option to Exchange One Asset for Another\", Journal of Finance 33, 177-86.
{#fun qlAnalyticAmericanMargrabeEngine as analyticAmericanMargrabeEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process1
  ,withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process2
  ,`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for writer-extensible options
{#fun qlAnalyticWriterExtensibleOptionEngine as analyticWriterExtensibleOptionEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Analytic Black-Scholes engine for a 'holderExtensibleOption'. The original option must have European exercise.
{#fun qlAnalyticHolderExtensibleOptionEngine as analyticHolderExtensibleOptionEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

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
{#fun qlMCDoubleBarrierEngine as mcDoubleBarrierEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
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

-- |analytic pricing engine for European continuous partial-time floating-strike lookback options
{#fun qlAnalyticContinuousPartialFloatingLookbackEngine as analyticContinuousPartialFloatingLookbackEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European continuous partial-time fixed-strike lookback options
{#fun qlAnalyticContinuousPartialFixedLookbackEngine as analyticContinuousPartialFixedLookbackEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European continuous geometric average-price Asian options
{#fun qlAnalyticContinuousGeometricAveragePriceAsianEngine as analyticContinuousGeometricAveragePriceAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for continuous fixed-strike lookback options. Exactly one of
-- @timeSteps@\/@timeStepsPerYear@ must be given; the other must be 'Nothing'.
{#fun qlMCLookbackFixedEngine as mcLookbackFixedEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for continuous floating-strike lookback options. Exactly one of
-- @timeSteps@\/@timeStepsPerYear@ must be given; the other must be 'Nothing'.
{#fun qlMCLookbackFloatingEngine as mcLookbackFloatingEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for continuous partial-time fixed-strike lookback options. Exactly
-- one of @timeSteps@\/@timeStepsPerYear@ must be given; the other must be 'Nothing'.
{#fun qlMCLookbackPartialFixedEngine as mcLookbackPartialFixedEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for continuous partial-time floating-strike lookback options.
-- Exactly one of @timeSteps@\/@timeStepsPerYear@ must be given; the other must be 'Nothing'.
{#fun qlMCLookbackPartialFloatingEngine as mcLookbackPartialFloatingEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for American digital (cash-or-nothing/asset-or-nothing) options
{#fun qlAnalyticDigitalAmericanEngine as analyticDigitalAmericanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for American knock-out digital (cash-or-nothing/asset-or-nothing) options
{#fun qlAnalyticDigitalAmericanKOEngine as analyticDigitalAmericanKOEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European discrete geometric average-price Asian options
{#fun qlAnalyticDiscreteGeometricAveragePriceAsianEngine as analyticDiscreteGeometricAveragePriceAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European discrete geometric average-strike Asian options
{#fun qlAnalyticDiscreteGeometricAverageStrikeAsianEngine as analyticDiscreteGeometricAverageStrikeAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Turnbull-Wakeman moment-matching pricing engine for discrete arithmetic average-price\/-strike Asian options
{#fun qlTurnbullWakemanAsianEngine as turnbullWakemanAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for European options with discrete dividends
{#fun qlAnalyticDividendEuropeanEngine as analyticDividendEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withDividendArray*`[Dividend]'&,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic Black-Scholes pricing engine for European options
{#fun qlAnalyticEuropeanEngine as analyticEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for performance (return) options
{#fun qlAnalyticPerformanceEngine as analyticPerformanceEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for forward-starting European options; binds the @AnalyticEuropeanEngine@ instantiation of upstream's @ForwardVanillaEngine\<Engine\>@ template
{#fun qlForwardEuropeanEngine as forwardEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Barone-Adesi\/Whaley approximation pricing engine for forward-starting American options; binds the @BaroneAdesiWhaleyApproximationEngine@ instantiation of @ForwardVanillaEngine\<Engine\>@
{#fun qlForwardBaroneAdesiWhaleyEngine as forwardBaroneAdesiWhaleyEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bjerksund\/Stensland approximation pricing engine for forward-starting American options; binds the @BjerksundStenslandApproximationEngine@ instantiation of @ForwardVanillaEngine\<Engine\>@
{#fun qlForwardBjerksundStenslandEngine as forwardBjerksundStenslandEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Black-Scholes pricing engine for forward-starting vanilla options, with the wrapped engine's grid\/scheme params fixed at their QuantLib defaults; binds the @FdBlackScholesVanillaEngine@ instantiation of @ForwardVanillaEngine\<Engine\>@
{#fun qlForwardFdBlackScholesVanillaEngine as forwardFdBlackScholesVanillaEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for forward-starting European options under a Black-Scholes process
{#fun qlMCForwardEuropeanBSEngine1 as mcForwardEuropeanBSEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo engine for European 'forwardVanillaOption's under a Heston process. Supply either @requiredSamples@ or @requiredTolerance@, and use a fixed nonzero @seed@ for reproducible results.
{#fun qlMCForwardEuropeanHestonEngine1 as mcForwardEuropeanHestonEngine{`RngTrait' -- ^rng
  ,`StatisticsTrait' -- ^statistics
  ,withHestonProcess*`GenHestonProcess hp' -- ^process
  ,fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,`Bool' -- ^controlVariate
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic pricing engine for forward-starting European options under a Heston process
{#fun qlAnalyticHestonForwardEuropeanEngine as analyticHestonForwardEuropeanEngine{withHestonProcess*`GenHestonProcess hp',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |quanto-adjusts a European vanilla option's price and greeks for a payoff paid in a currency other than the underlying's; binds the @VanillaOption@\/@AnalyticEuropeanEngine@ instantiation of upstream's @QuantoEngine\<Instr,Engine\>@ template
{#fun qlQuantoEuropeanEngine as quantoEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^foreignRiskFreeRate
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^exchangeRateVolatility
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |quanto-adjusts a forward-starting vanilla option; binds the @ForwardVanillaOption@\/@ForwardVanillaEngine\<AnalyticEuropeanEngine\>@ instantiation of @QuantoEngine\<Instr,Engine\>@
{#fun qlQuantoForwardEuropeanEngine as quantoForwardEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^foreignRiskFreeRate
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^exchangeRateVolatility
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |quanto-adjusts a forward-starting performance (strike-resetting, percentage-payoff) vanilla option; binds the @ForwardVanillaOption@\/@ForwardPerformanceVanillaEngine\<AnalyticEuropeanEngine\>@ instantiation of @QuantoEngine\<Instr,Engine\>@
{#fun qlQuantoForwardPerformanceEuropeanEngine as quantoForwardPerformanceEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^foreignRiskFreeRate
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^exchangeRateVolatility
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |quanto-adjusts a single-barrier option; binds the @BarrierOption@\/@AnalyticBarrierEngine@ instantiation of @QuantoEngine\<Instr,Engine\>@
{#fun qlQuantoBarrierEngine as quantoBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^foreignRiskFreeRate
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^exchangeRateVolatility
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |quanto-adjusts a double-barrier option; binds the @DoubleBarrierOption@\/@AnalyticDoubleBarrierEngine@ instantiation of @QuantoEngine\<Instr,Engine\>@
{#fun qlQuantoDoubleBarrierEngine as quantoDoubleBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^foreignRiskFreeRate
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^exchangeRateVolatility
  ,withQuote*`GenQuote q' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

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
{#fun qlHaganIrregularSwaptionEngine as haganIrregularSwaptionEngine{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |shifted-lognormal Black-formula swaption engine, taking a swaption volatility structure
{#fun qlBlackSwaptionEngine1 as blackSwaptionEngine'{withYieldTermStructure*`GenYieldTermStructure y',withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) cap\/floor engine, taking an optionlet volatility structure
{#fun qlBachelierCapFloorEngine1 as bachelierCapFloorEngine'{withYieldTermStructure*`GenYieldTermStructure y',withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) cap\/floor engine, taking a flat volatility quote
{#fun qlBachelierCapFloorEngine as bachelierCapFloorEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Black-formula YoY inflation cap\/floor engine. The nominal discount curve and the index's
-- own linked 'QuantLib.TermStructure.Inflation.YoYInflationTermStructure' are separate --
-- @nominalTermStructure@ discounts cashflows, while the index forecasts them.
{#fun qlYoYInflationBlackCapFloorEngine as yoyInflationBlackCapFloorEngine{withYoYInflationIndex*`GenYoYInflationIndex yidx'
  ,withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface' -- ^vol
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |as 'yoyInflationBlackCapFloorEngine', but unit-displaced Black
{#fun qlYoYInflationUnitDisplacedBlackCapFloorEngine as yoyInflationUnitDisplacedBlackCapFloorEngine{withYoYInflationIndex*`GenYoYInflationIndex yidx'
  ,withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface' -- ^vol
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |as 'yoyInflationBlackCapFloorEngine', but Bachelier (normal model)
{#fun qlYoYInflationBachelierCapFloorEngine as yoyInflationBachelierCapFloorEngine{withYoYInflationIndex*`GenYoYInflationIndex yidx'
  ,withGenVolatilityTermStructure*`YoYOptionletVolatilitySurface' -- ^vol
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^nominalTermStructure
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |The only 'QuantLib.Instrument.InflationCapFloor.CPICapFloor' pricing engine in QL 1.43 --
-- prices purely by interpolating a market price surface, no stochastic-vol model (see that
-- type's own haddock for the CPI\/YoY asymmetry).
{#fun qlInterpolatingCPICapFloorEngine as interpolatingCPICapFloorEngine{withGenTermStructure*`CPICapFloorTermPriceSurface'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) swaption engine, taking a flat volatility quote
{#fun qlBachelierSwaptionEngine as bachelierSwaptionEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote q',withDayCounter*`DayCounter',`CashAnnuityModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bachelier (normal) swaption engine, taking a swaption volatility structure
{#fun qlBachelierSwaptionEngine1 as bachelierSwaptionEngine'{withYieldTermStructure*`GenYieldTermStructure y',withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |analytic European option pricer including stochastic interest rates (Black-Scholes-Merton + Hull-White)
{#fun qlAnalyticBSMHullWhiteEngine as analyticBSMHullWhiteEngine{`Double',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withHullWhite*`HullWhite',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
{#fun qlAnalyticCapFloorEngine as analyticCapFloorEngine{withStandalone*`AffineModel',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |cap\/floor pricing engine for any one-factor Gaussian short-rate model, evaluated by
-- integration over the model's state variable. As 'gaussian1dSwaptionEngine', without
-- 'Probabilities'.
{#fun qlGaussian1dCapFloorEngine as gaussian1dCapFloorEngine{withStandalone*`Gaussian1dModel'
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

-- |American engine based on the QD+ approximation to the exercise boundary. Mainly a good
-- initial guess for the exercise boundary of 'qdFpAmericanEngine'; usable as a standalone
-- (lower-accuracy) American pricer on its own.
{#fun qlQdPlusAmericanEngine as qdPlusAmericanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,fromIntegral`Word' -- ^interpolationPoints, number of Chebyshev nodes used to interpolate the exercise boundary
  ,`SolverType' -- ^solverType, root-finding method used to locate the exercise boundary
  ,`Double' -- ^eps, solver accuracy
  ,fromMaybeInt`Maybe Word' -- ^maxIter, solver iteration cap; Nothing uses upstream's default
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |High performance\/precision American engine based on fixed point iteration for the exercise
-- boundary (Andersen, Lake and Offengenden 2015; Andersen and Lake 2021). 'QdFpScheme' selects
-- one of upstream's three built-in 'iterationScheme's ('FastScheme', 'AccurateScheme',
-- 'HighPrecisionScheme'), trading speed for accuracy.
{#fun qlQdFpAmericanEngine as qdFpAmericanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,`QdFpScheme' -- ^iterationScheme
  ,`FixedPointEquation' -- ^fpEquation, which fixed-point formulation of the exercise boundary equation to solve
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Vecer (2001) engine for continuous-averaging arithmetic Asian options, replicating the average
-- by a self-financing strategy in the underlying and solving the resulting PDE on a finite
-- @[zMin,zMax]@ grid; requires @zMin <= 0 <= zMax@ and @startDate@ no earlier than the evaluation
-- date (seasoned Asians are not supported). @currentAverage@ is accepted for parity with upstream's
-- constructor but is not read by the current implementation (only the not-yet-seasoned case is
-- handled), so 'Nothing' is fine.
{#fun qlContinuousArithmeticAsianVecerEngine as continuousArithmeticAsianVecerEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,withMaybeQuote*`Maybe (GenQuote q)' -- ^currentAverage
  ,withDay*`Day' -- ^startDate
  ,fromIntegral`Word' -- ^timeSteps
  ,fromIntegral`Word' -- ^assetSteps
  ,`Double' -- ^zMin
  ,`Double' -- ^zMax
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

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
{#fun qlGaussian1dSwaptionEngine as gaussian1dSwaptionEngine{withStandalone*`Gaussian1dModel'
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
{#fun qlGaussian1dNonstandardSwaptionEngine as gaussian1dNonstandardSwaptionEngine{withStandalone*`Gaussian1dModel'
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
{#fun qlGaussian1dFloatFloatSwaptionEngine as gaussian1dFloatFloatSwaptionEngine{withStandalone*`Gaussian1dModel'
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
{#fun qlGaussian1dJamshidianSwaptionEngine as gaussian1dJamshidianSwaptionEngine{withStandalone*`Gaussian1dModel',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

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

-- |Synthetic CDO tranche pricing engine using the mid-point approximation, evaluating the
-- expected tranche loss at the mid-point of each accrual/protection period. The basket must
-- already have a 'QuantLib.Credit.DefaultLossModel' attached.
{#fun qlMidPointCDOEngine as midPointCDOEngine{withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Synthetic CDO tranche pricing engine that integrates the expected tranche loss over
-- @stepSize@-sized steps of the tranche's schedule.
{#fun qlIntegralCDOEngine as integralCDOEngine{withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^stepSize
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Nth-to-default pricing engine that integrates the probability of at least @n@ defaults over
-- @integrationStep@-sized steps of the underlying basket's copula.
{#fun qlIntegralNtdEngine as integralNtdEngine{fromEnumQuantity`(Word,TimeUnit)'& -- ^integrationStep
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
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
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^callStrikes
  ,withNonEmptyDoubleArray*`NonEmpty Double'& -- ^putStrikes
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for 2D European basket options (Stulz formula)
{#fun qlStulzEngine as stulzEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Bjerksund-Stensland (2014) closed-form pricing engine for a spread option on two futures
{#fun qlBjerksundStenslandSpreadEngine as bjerksundStenslandSpreadEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Chi-Fai Lo (2015) operator-splitting-approximation pricing engine for a spread option
{#fun qlOperatorSplittingSpreadEngine as operatorSplittingSpreadEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,`OperatorSplittingOrder' -- ^order, upstream default: 'Second'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Pearson (1995) 1-D-numerical-integration pricing engine for a spread option
{#fun qlPearsonSpreadEngine as pearsonSpreadEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,`Double' -- ^integrationTolerance, upstream default: 1e-10
  ,fromIntegral`Word' -- ^maxIntegrationIterations, upstream default: 10000
  ,`Double' -- ^nStd, upstream default: 8.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Gaussian-copula nested-Gauss-Hermite-quadrature pricing engine for a spread option with smile-implied marginals
{#fun qlGaussianCopulaSpreadEngine as gaussianCopulaSpreadEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,fromIntegral`Word' -- ^nPoints, upstream default: 64
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Choi (2018) \"sum of Black-Scholes-Merton models\" pricing engine for a basket option on
-- multiple underlyings, correlated via @rho@
choiBasketEngine :: NonEmpty GeneralizedBlackScholesProcess -> Matrix Double -- ^correlation matrix rho
  -> Double -- ^lambda, upstream default: 10.0
  -> Word -- ^maxNrIntegrationSteps, upstream default: unbounded; the C shim takes a 32-bit count
  -> Bool -- ^calcfwdDelta
  -> Bool -- ^controlVariate
  -> IO PricingEngine
choiBasketEngine ps (Matrix mr mc md) = qlChoiBasketEngine (toList ps) mr mc md
{#fun qlChoiBasketEngine{withGeneralizedBlackScholesProcessArray*`[GeneralizedBlackScholesProcess]'&
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,`Double' -- ^lambda
  ,fromIntegral`Word' -- ^maxNrIntegrationSteps
  ,`Bool' -- ^calcfwdDelta
  ,`Bool' -- ^controlVariate
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Deng-Li-Zhou (2008) closed-form-approximation pricing engine for a spread option on multiple
-- underlyings, correlated via @rho@
dengLiZhouBasketEngine :: NonEmpty GeneralizedBlackScholesProcess -> Matrix Double -- ^correlation matrix rho
  -> IO PricingEngine
dengLiZhouBasketEngine ps (Matrix mr mc md) = qlDengLiZhouBasketEngine (toList ps) mr mc md
{#fun qlDengLiZhouBasketEngine{withGeneralizedBlackScholesProcessArray*`[GeneralizedBlackScholesProcess]'&
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |pricing engine for a basket where all underlyings are driven by one stochastic factor
singleFactorBsmBasketEngine :: NonEmpty GeneralizedBlackScholesProcess
  -> Double -- ^xTol, upstream default: @1e4*QL_EPSILON@
  -> IO PricingEngine
singleFactorBsmBasketEngine ps = qlSingleFactorBsmBasketEngine (toList ps)
{#fun qlSingleFactorBsmBasketEngine{withGeneralizedBlackScholesProcessArray*`[GeneralizedBlackScholesProcess]'&
  ,`Double' -- ^xTol
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

-- |quanto drift adjustment @domesticRate - foreignRate + equityFxCorrelation*equityVol*fxVol@ over @[t1,t2]@
{#fun qlFdmQuantoHelperQuantoAdjustment as fdmQuantoHelperQuantoAdjustment{withFdmQuantoHelper*`FdmQuantoHelper'
  ,`Double' -- ^equityVol
  ,`Double' -- ^t1
  ,`Double' -- ^t2
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}

-- |two-dimensional finite-differences Black-Scholes basket-option pricing engine
{#fun qlFd2dBlackScholesVanillaEngine as fd2dBlackScholesVanillaEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,fromIntegral`Word' -- ^xGrid, upstream default: 100
  ,fromIntegral`Word' -- ^yGrid, upstream default: 100
  ,fromIntegral`Word' -- ^tGrid, upstream default: 50
  ,fromIntegral`Word' -- ^dampingSteps, upstream default: 0
  ,withFdmSchemeDesc*`FdmScheme' -- ^schemeDesc, upstream default: 'Hundsdorfer'
  ,`Bool' -- ^localVol
  ,`Double' -- ^illegalLocalVolOverwrite, upstream default: @-Null\<Real\>()@
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |n-dimensional finite-differences Black-Scholes basket-option pricing engine, with an explicit
-- per-axis grid size
fdndimBlackScholesVanillaEngine :: NonEmpty GeneralizedBlackScholesProcess -> Matrix Double -- ^correlation matrix rho
  -> NonEmpty Word -- ^xGrids, one per underlying
  -> Word -- ^tGrid, upstream default: 50
  -> Word -- ^dampingSteps, upstream default: 0
  -> FdmScheme -- ^schemeDesc, upstream default: 'Douglas'
  -> IO PricingEngine
fdndimBlackScholesVanillaEngine ps (Matrix mr mc md) xGrids = qlFdndimBlackScholesVanillaEngine (toList ps) mr mc md (toList xGrids)
{#fun qlFdndimBlackScholesVanillaEngine{withGeneralizedBlackScholesProcessArray*`[GeneralizedBlackScholesProcess]'&
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,withIntArray*`[Word]'&
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |n-dimensional finite-differences Black-Scholes basket-option pricing engine, auto-scaling every
-- axis' grid from a single size (largest eigenvalue gets @xGrid@)
fdndimBlackScholesVanillaEngine' :: NonEmpty GeneralizedBlackScholesProcess -> Matrix Double -- ^correlation matrix rho
  -> Word -- ^xGrid
  -> Word -- ^tGrid, upstream default: 50
  -> Word -- ^dampingSteps, upstream default: 0
  -> FdmScheme -- ^schemeDesc, upstream default: 'Douglas'
  -> IO PricingEngine
fdndimBlackScholesVanillaEngine' ps (Matrix mr mc md) = qlFdndimBlackScholesVanillaEngine1 (toList ps) mr mc md
{#fun qlFdndimBlackScholesVanillaEngine1{withGeneralizedBlackScholesProcessArray*`[GeneralizedBlackScholesProcess]'&
  ,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]'
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

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
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model barrier-option pricing engine, with discrete dividends
{#fun qlFdHestonBarrierEngine1 as fdHestonBarrierEngine'{withHestonModel*`GenHestonModel hm',withDividendArray*`[Dividend]'&
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model double-barrier-option pricing engine
{#fun qlFdHestonDoubleBarrierEngine as fdHestonDoubleBarrierEngine{withHestonModel*`GenHestonModel hm',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |/NB/ every Monte Carlo engine in this module is C++-templated on both an RNG policy and a
-- statistics accumulator; all of them (bar 'mcAmericanBasketEngine', see its own doc comment)
-- take an explicit 'StatisticsTrait' argument for the latter, letting the caller pick
-- 'Statistics'\/'GaussianStatistics'\/'GeneralStatistics'\/'IncrementalStatistics' instead of being
-- pinned to upstream's default @Statistics@.
{#fun qlMCHestonHullWhiteEngine1 as mcHestonHullWhiteEngine{`RngTrait',`StatisticsTrait',withGenStochasticProcess*`HybridHestonHullWhiteProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,`Bool' -- ^controlVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word'-- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo (least-squares) pricing engine for American options
{#fun qlMCAmericanEngine1 as mcAmericanEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word', -- ^timeSteps
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
{#fun qlMCBarrierEngine1 as mcBarrierEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
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
{#fun qlMCDigitalEngine1 as mcDigitalEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word', -- ^timeStepsPerYear
  `Bool', -- ^brownianBridge
  `Bool', -- ^antitheticVariate
  fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for discrete arithmetic average-price Asian options
{#fun qlMCDiscreteArithmeticAPEngine1 as mcDiscreteArithmeticAPEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,`Bool' -- ^controlVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for discrete arithmetic average-strike Asian options
{#fun qlMCDiscreteArithmeticASEngine1 as mcDiscreteArithmeticASEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for discrete geometric average-price Asian options
{#fun qlMCDiscreteGeometricAPEngine1 as mcDiscreteGeometricAPEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for European options under a Black-Scholes process
{#fun qlMCEuropeanEngine1 as mcEuropeanEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for European options under a GJR-GARCH process
{#fun qlMCEuropeanGJRGARCHEngine1 as mcEuropeanGJRGARCHEngine{`RngTrait',`StatisticsTrait',withGenStochasticProcess*`GJRGARCHProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for European options under a Heston process
{#fun qlMCEuropeanHestonEngine1 as mcEuropeanHestonEngine{`RngTrait',`StatisticsTrait',withHestonProcess*`GenHestonProcess hp',fromMaybeInt`Maybe Word' -- ^timeSteps
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
{#fun qlMCHullWhiteCapFloorEngine1 as mcHullWhiteCapFloorEngine{`RngTrait',`StatisticsTrait',withHullWhite*`HullWhite',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for 'himalayaOption'
{#fun qlMCHimalayaEngine1 as mcHimalayaEngine{`RngTrait',`StatisticsTrait',withGenStochasticProcess*`StochasticProcessArray',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for 'pagodaOption'
{#fun qlMCPagodaEngine1 as mcPagodaEngine{`RngTrait',`StatisticsTrait',withGenStochasticProcess*`StochasticProcessArray',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for a European 'basketOption'.
{#fun qlMCEuropeanBasketEngine1 as mcEuropeanBasketEngine{`RngTrait',`StatisticsTrait',withGenStochasticProcess*`StochasticProcessArray',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for 'everestOption'. Exactly one of @timeSteps@\/@timeStepsPerYear@ must be given.
{#fun qlMCEverestEngine1 as mcEverestEngine{`RngTrait',`StatisticsTrait',withGenStochasticProcess*`StochasticProcessArray',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo (least-squares) pricing engine for an American 'basketOption'. /NB/ unlike every
-- other MC engine in this module, this one has no 'StatisticsTrait' parameter: upstream's
-- @MCAmericanBasketEngine\<RNG\>@ is templated on @RNG@ only -- its base
-- @MCLongstaffSchwartzEngine\<BasketOption::engine,MultiVariate,RNG\>@ never forwards a second
-- template argument, so there is no @S@ to expose here (a real upstream limitation, not an
-- oversight).
{#fun qlMCAmericanBasketEngine1 as mcAmericanBasketEngine{`RngTrait',withGenStochasticProcess*`StochasticProcessArray',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,fromMaybeInt`Maybe Word' -- ^nCalibrationSamples
  ,fromIntegral`Word' -- ^polynomialOrder
  ,`PolynomialType' -- ^polynomialType
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Monte Carlo pricing engine for performance (return) options
{#fun qlMCPerformanceEngine1 as mcPerformanceEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |variance-swap pricing engine using Monte Carlo simulation (see the note above
-- 'mcHestonHullWhiteEngine' for the 'StatisticsTrait' parameter shared by every MC engine here).
{#fun qlMCVarianceSwapEngine1 as mcVarianceSwapEngine{`RngTrait',`StatisticsTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
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

-- |finite-differences Black-Scholes pricing engine for discrete-averaging Asian options
{#fun qlFdBlackScholesAsianEngine as fdBlackScholesAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^aGrid
  ,withFdmSchemeDesc*`FdmScheme'
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

-- |finite-differences Black-Scholes pricing engine for vanilla options, with discrete dividends
{#fun qlFdBlackScholesVanillaEngine1 as fdBlackScholesVanillaEngine'{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withDividendArray*`[Dividend]'&
  ,fromIntegral`Word' -- ^timeSteps
  ,fromIntegral`Word' -- ^gridPoints
  ,fromIntegral`Word' -- ^timeDependent
  ,withFdmSchemeDesc*`FdmScheme'
  ,`Bool' -- ^localVol
  ,`Double' -- ^illegalLocalVolOverwrite
  ,`CashDividendModel' -- ^cashDividendModel
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Black-Scholes pricing engine for vanilla options, with quanto adjustment
{#fun qlFdBlackScholesVanillaEngine2 as fdBlackScholesVanillaEngineQuanto{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,fromIntegral`Word' -- ^timeSteps
  ,fromIntegral`Word' -- ^gridPoints
  ,fromIntegral`Word' -- ^timeDependent
  ,withFdmSchemeDesc*`FdmScheme'
  ,`Bool' -- ^localVol
  ,`Double' -- ^illegalLocalVolOverwrite
  ,`CashDividendModel' -- ^cashDividendModel
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Black-Scholes pricing engine for vanilla options, with discrete dividends and quanto adjustment
{#fun qlFdBlackScholesVanillaEngine3 as fdBlackScholesVanillaEngineQuanto'{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withDividendArray*`[Dividend]'&,withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,fromIntegral`Word' -- ^timeSteps
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
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options, with discrete dividends
{#fun qlFdHestonVanillaEngine1 as fdHestonVanillaEngine'{withHestonModel*`GenHestonModel hm',withDividendArray*`[Dividend]'&
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Fourier-cosine-series Heston engine for European vanilla options. @L@ controls the truncation range and @n@ the number of cosine terms.
{#fun qlCOSHestonEngine as cosHestonEngine{withHestonModel*`GenHestonModel hm' -- ^model
  ,`Double' -- ^L
  ,fromIntegral`Word' -- ^n
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Heston transition-density integration engine for European vanilla options. @eps@ and @integrationOrder@ control Gauss-Lobatto integration accuracy and its iteration limit.
{#fun qlAnalyticPDFHestonEngine as analyticPdfHestonEngine{withHestonModel*`GenHestonModel hm' -- ^model
  ,`Double' -- ^eps
  ,fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Partial-integro finite-difference Bates-model engine for vanilla options.
{#fun qlFdBatesVanillaEngine as fdBatesVanillaEngine{withBatesModel*`GenBatesModel bm' -- ^model
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme' -- ^schemeDesc
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Partial-integro finite-difference Bates-model engine for vanilla options with discrete dividends.
{#fun qlFdBatesVanillaEngine1 as fdBatesVanillaEngine'{withBatesModel*`GenBatesModel bm' -- ^model
  ,withDividendArray*`[Dividend]'& -- ^dividends
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme' -- ^schemeDesc
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Finite-difference Black-Scholes engine for American shout options.
{#fun qlFdBlackScholesShoutEngine as fdBlackScholesShoutEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme' -- ^schemeDesc
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |Finite-difference Black-Scholes engine for American shout options with discrete dividends.
{#fun qlFdBlackScholesShoutEngine1 as fdBlackScholesShoutEngine'{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess' -- ^process
  ,withDividendArray*`[Dividend]'& -- ^dividends
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme' -- ^schemeDesc
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options, with quanto adjustment
{#fun qlFdHestonVanillaEngine2 as fdHestonVanillaEngineQuanto{withHestonModel*`GenHestonModel hm',withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
  ,`Double' -- ^mixingFactor, upstream default: 1.0
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |finite-differences Heston-model pricing engine for vanilla options, with discrete dividends and quanto adjustment
{#fun qlFdHestonVanillaEngine3 as fdHestonVanillaEngineQuanto'{withHestonModel*`GenHestonModel hm',withDividendArray*`[Dividend]'&,withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^dampingSteps
  ,withFdmSchemeDesc*`FdmScheme'
  ,withMaybeLocalVolTermStructure*`Maybe (GenLocalVolTermStructure lv)' -- ^leverageFct
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
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
{#fun qlQuantLibBlackFormulaStdDevDerivative as blackStdDevDerivative{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for derivative with respect to implied vol, this is basically the vega, but if you want 1% change multiply by 1%
{#fun qlQuantLibBlackFormulaVolDerivative as blackVolDerivative{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^expiry
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

-- |Black 1976 formula for the derivative with respect to the forward
{#fun qlQuantLibBlackFormulaForwardDerivative1 as blackForwardDerivative'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for the derivative with respect to the forward. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaForwardDerivative as blackForwardDerivative{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Approximated Black 1976 implied standard deviation following Chambers and Nawalkha, /The Financial Review/ 2001, 89-100. The at-the-money option price must be known to use this method.
{#fun qlQuantLibBlackFormulaImpliedStdDevChambers1 as blackImpliedStdDevChambers'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^blackAtmPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Approximated Black 1976 implied standard deviation following Chambers and Nawalkha, /The Financial Review/ 2001, 89-100. The at-the-money option price must be known to use this method.
{#fun qlQuantLibBlackFormulaImpliedStdDevChambers as blackImpliedStdDevChambers{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^blackAtmPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Approximated Black 1976 implied standard deviation following Radoicic and Stefanica, /An Explicit Implicit Volatility Formula/
{#fun qlQuantLibBlackFormulaImpliedStdDevApproximationRS1 as blackImpliedStdDevApproximationRS'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Approximated Black 1976 implied standard deviation following Radoicic and Stefanica, /An Explicit Implicit Volatility Formula/
{#fun qlQuantLibBlackFormulaImpliedStdDevApproximationRS as blackImpliedStdDevApproximationRS{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 implied standard deviation by the Li-Rational-Substitution solver, started from the Radoicic-Stefanica approximation. Pass 'Nothing' for the guess to let QuantLib pick the starting point.
{#fun qlQuantLibBlackFormulaImpliedStdDevLiRS1 as blackImpliedStdDevLiRS'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,fromMaybeDouble`Maybe Double' -- ^guess
  ,`Double' -- ^omega
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 implied standard deviation by the Li-Rational-Substitution solver, started from the Radoicic-Stefanica approximation. Pass 'Nothing' for the guess to let QuantLib pick the starting point.
{#fun qlQuantLibBlackFormulaImpliedStdDevLiRS as blackImpliedStdDevLiRS{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^blackPrice
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,fromMaybeDouble`Maybe Double' -- ^guess
  ,`Double' -- ^omega
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
{#fun qlQuantLibBlackFormulaAssetItmProbability1 as blackAssetItmProbability'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
{#fun qlQuantLibBlackFormulaAssetItmProbability as blackAssetItmProbability{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for the second derivative with respect to the standard deviation. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaStdDevSecondDerivative1 as blackStdDevSecondDerivative'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black 1976 formula for the second derivative with respect to the standard deviation. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaStdDevSecondDerivative as blackStdDevSecondDerivative{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier formula for the derivative with respect to the forward. /Warning/ the Bachelier model needs absolute volatility, not percentage volatility; standard deviation is absoluteVolatility*sqrt(timeToMaturity)
{#fun qlQuantLibBachelierBlackFormulaForwardDerivative1 as bachelierForwardDerivative'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier formula for the derivative with respect to the forward. /Warning/ the Bachelier model needs absolute volatility, not percentage volatility; standard deviation is absoluteVolatility*sqrt(timeToMaturity)
{#fun qlQuantLibBachelierBlackFormulaForwardDerivative as bachelierForwardDerivative{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier implied (absolute) volatility by the analytic formula of Jaeckel (2017), /Implied Normal Volatility/. Unlike the Black implied-standard-deviation functions this takes the time to expiry and returns a volatility, not a standard deviation.
{#fun qlQuantLibBachelierBlackFormulaImpliedVol as bachelierImpliedVol{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^tte
  ,`Double' -- ^bachelierPrice
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier implied (absolute) volatility by the analytic approximation of Choi, Kim and Kwak (2009). Unlike the Black implied-standard-deviation functions this takes the time to expiry and returns a volatility, not a standard deviation.
{#fun qlQuantLibBachelierBlackFormulaImpliedVolChoi as bachelierImpliedVolChoi{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^tte
  ,`Double' -- ^bachelierPrice
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier formula for the standard deviation derivative. /Warning/ it returns the derivative with respect to the standard deviation; Bachelier vega is this times sqrt(T).
{#fun qlQuantLibBachelierBlackFormulaStdDevDerivative1 as bachelierStdDevDerivative'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier formula for the standard deviation derivative. /Warning/ it returns the derivative with respect to the standard deviation; Bachelier vega is this times sqrt(T).
{#fun qlQuantLibBachelierBlackFormulaStdDevDerivative as bachelierStdDevDerivative{`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier probability of being in the money in the asset martingale measure, i.e. N(d). It is a risk-neutral probability, not the real world one.
{#fun qlQuantLibBachelierBlackFormulaAssetItmProbability1 as bachelierAssetItmProbability'{withPlainVanillaPayoff*`PlainVanillaPayoff',`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Bachelier probability of being in the money in the asset martingale measure, i.e. N(d). It is a risk-neutral probability, not the real world one.
{#fun qlQuantLibBachelierBlackFormulaAssetItmProbability as bachelierAssetItmProbability{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
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
