module QuantLib.PricingEngine
  (
    PricingEngine
  , BlackCalculator
  , BlackScholesCalculator

  , GenBlackCalculator
  , asBlackCalculator

  , discountingBondEngine
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
  --, analyticCapFloorEngine
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
  , fdBlackScholesVanillaEngine

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
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Math#}
{#import QuantLib.Instrument.Option#} hiding(itmCashProbability, deltaForward, strikeSensitivity, dividendRho, rho, vega)
import QuantLib.Internal.Enum

{#pointer *DayCounter foreign -> CDayCounter nocode#}

{#pointer *QlDividend as Dividend foreign -> CDividend nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign -> CCallableBondVolatilityStructure' nocode#}
{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign -> CGJRGARCHModel' nocode#}
{#pointer *QlHestonModel as HestonModel foreign -> CHestonModel' nocode#}
{#pointer *QlBatesModel as BatesModel foreign -> CBatesModel' nocode#}
{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign -> CPiecewiseTimeDependentHestonModel' nocode#}
{#pointer *QlShortRateModel as ShortRateModel foreign -> CShortRateModel' nocode#}
{#pointer *QlAffineModel as AffineModel foreign -> CAffineModel' nocode#}
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
{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}

{#fun qlDiscountingBondEngine as discountingBondEngine{withYieldTermStructure*`GenYieldTermStructure a',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlDiscountingSwapEngine as discountingSwapEngine{withYieldTermStructure*`GenYieldTermStructure a',fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,withMaybeDay*`Maybe Day' -- ^settlementDate
  ,withMaybeDay*`Maybe Day' -- ^npvDate
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#fun qlAnalyticBarrierEngine as analyticBarrierEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticCliquetEngine as analyticCliquetEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticContinuousFixedLookbackEngine as analyticContinuousFixedLookbackEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticContinuousFloatingLookbackEngine as analyticContinuousFloatingLookbackEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticContinuousGeometricAveragePriceAsianEngine as analyticContinuousGeometricAveragePriceAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticDigitalAmericanEngine as analyticDigitalAmericanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticDiscreteGeometricAveragePriceAsianEngine as analyticDiscreteGeometricAveragePriceAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticDiscreteGeometricAverageStrikeAsianEngine as analyticDiscreteGeometricAverageStrikeAsianEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticDividendEuropeanEngine as analyticDividendEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticEuropeanEngine as analyticEuropeanEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticPerformanceEngine as analyticPerformanceEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBlackCapFloorEngine1 as blackCapFloorEngine'{withYieldTermStructure*`GenYieldTermStructure a',withGenVolatilityTermStructure*`OptionletVolatilityStructure',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBlackCapFloorEngine as blackCapFloorEngine{withYieldTermStructure*`GenYieldTermStructure b',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBlackSwaptionEngine as blackSwaptionEngine{withYieldTermStructure*`GenYieldTermStructure y',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBlackSwaptionEngine1 as blackSwaptionEngine'{withYieldTermStructure*`GenYieldTermStructure y',withGenVolatilityTermStructure*`SwaptionVolatilityStructure',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticBSMHullWhiteEngine as analyticBSMHullWhiteEngine{`Double',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withHullWhite*`HullWhite',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
--{#fun qlAnalyticCapFloorEngine as analyticCapFloorEngine{withAffineModel*`AffineModel',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticGJRGARCHEngine as analyticGJRGARCHEngine{withGenCalibratedModel*`GJRGARCHModel',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticHestonEngine as analyticHestonEngine{withHestonModel*`HestonModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticHestonHullWhiteEngine as analyticHestonHullWhiteEngine{withHestonModel*`HestonModel',withHullWhite*`HullWhite'
  ,fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesEngine as batesEngine{withBatesModel*`BatesModel'
  ,fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlFFTVanillaEngine as fftVanillaEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^logStrikeSpacing
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlG2SwaptionEngine as g2SwaptionEngine{withG2*`G2',`Double' -- ^range
  ,fromIntegral`Word' -- ^intervals
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlJumpDiffusionEngine as jumpDiffusionEngine{withGenStochasticProcess1D*`Merton76Process'
  ,`Double' -- ^relativeAccuracy
  ,fromIntegral`Word' -- ^maxIterations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeCapFloorEngine as treeCapFloorEngine{withShortRateModel*`ShortRateModel',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeSwaptionEngine as treeSwaptionEngine{withShortRateModel*`ShortRateModel',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeVanillaSwapEngine as treeVanillaSwapEngine{withShortRateModel*`ShortRateModel',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlVarianceGammaEngine as varianceGammaEngine{withGenStochasticProcess1D*`VarianceGammaProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticHestonEngine1 as analyticHestonEngine'{withHestonModel*`HestonModel',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlAnalyticHestonHullWhiteEngine1 as analyticHestonHullWhiteEngine'{withHestonModel*`HestonModel',withHullWhite*`HullWhite',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesEngine1 as batesEngine'{withBatesModel*`BatesModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBaroneAdesiWhaleyApproximationEngine as baroneAdesiWhaleyApproximationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesDetJumpEngine1 as batesDetJumpEngine'{withBatesDetJumpModel*`BatesDetJumpModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesDetJumpEngine as batesDetJumpEngine{withBatesDetJumpModel*`BatesDetJumpModel',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesDoubleExpDetJumpEngine1 as batesDoubleExpDetJumpEngine'{withBatesDoubleExpDetJumpModel*`BatesDoubleExpDetJumpModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesDoubleExpDetJumpEngine as batesDoubleExpDetJumpEngine{withBatesDoubleExpDetJumpModel*`BatesDoubleExpDetJumpModel',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesDoubleExpEngine1 as batesDoubleExpEngine'{withBatesDoubleExpModel*`BatesDoubleExpModel',`Double' -- ^relTolerance
  ,fromIntegral`Word' -- ^maxEvaluations
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBatesDoubleExpEngine as batesDoubleExpEngine{withBatesDoubleExpModel*`BatesDoubleExpModel',fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBjerksundStenslandApproximationEngine as bjerksundStenslandApproximationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#fun qlIntegralCdsEngine as integralCdsEngine{fromEnumQuantity`(Word,TimeUnit)'& -- ^integrationStep
  ,withGenTermStructure*`DefaultProbabilityTermStructure',`Double' -- ^recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^discountCurve
  ,fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlIntegralEngine as integralEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
{#fun qlJamshidianSwaptionEngine as jamshidianSwaptionEngine{withOneFactorAffineModel*`OneFactorAffineModel',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlJuQuadraticApproximationEngine as juQuadraticApproximationEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlKirkEngine as kirkEngine{withBlackProcess*`BlackProcess',withBlackProcess*`BlackProcess',`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMidPointCdsEngine as midPointCdsEngine{withGenTermStructure*`DefaultProbabilityTermStructure',`Double' -- ^recoveryRate
  ,withYieldTermStructure*`GenYieldTermStructure y'
  ,fromMaybeBool`Maybe Bool' -- ^includeSettlementDateFlows
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlReplicatingVarianceSwapEngine as replicatingVarianceSwapEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^dk
  ,withDoubleArray*`[Double]'& -- ^callStrikes
  ,withDoubleArray*`[Double]'& -- ^putStrikes
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlStulzEngine as stulzEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^correlation
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlLfmSwaptionEngine as lfmSwaptionEngine{withGenCalibratedModel*`LiborForwardModel',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeCapFloorEngine1 as treeCapFloorEngine'{withShortRateModel*`ShortRateModel',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeSwaptionEngine1 as treeSwaptionEngine'{withShortRateModel*`ShortRateModel',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeVanillaSwapEngine1 as treeVanillaSwapEngine'{withShortRateModel*`ShortRateModel',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}
{#fun qlFdG2SwaptionEngine as fdG2SwaptionEngine{withG2*`G2',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^yGrid
  ,fromIntegral`Word' -- ^dampingSpecs
  ,`Double' -- ^invEps
  ,withFdmSchemeDesc*`FdmScheme',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlFdHullWhiteSwaptionEngine as fdHullWhiteSwaptionEngine{withHullWhite*`HullWhite',fromIntegral`Word' -- ^tGrid
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^dampingSpecs
  ,`Double' -- ^invEps
  ,withFdmSchemeDesc*`FdmScheme',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

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
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
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
{#fun qlMCDigitalEngine1 as mcDigitalEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word', -- ^timeStepsPerYear
  `Bool', -- ^brownianBridge
  `Bool', -- ^antitheticVariate
  fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCDiscreteArithmeticAPEngine1 as mcDiscreteArithmeticAPEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,`Bool' -- ^controlVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCDiscreteArithmeticASEngine1 as mcDiscreteArithmeticASEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCDiscreteGeometricAPEngine1 as mcDiscreteGeometricAPEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCEuropeanEngine1 as mcEuropeanEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCEuropeanGJRGARCHEngine1 as mcEuropeanGJRGARCHEngine{`RngTrait',withGenStochasticProcess*`GJRGARCHProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCEuropeanHestonEngine1 as mcEuropeanHestonEngine{`RngTrait',withHestonProcess*`GenHestonProcess a',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCHullWhiteCapFloorEngine1 as mcHullWhiteCapFloorEngine{`RngTrait',withHullWhite*`HullWhite',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCPerformanceEngine1 as mcPerformanceEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlMCVarianceSwapEngine1 as mcVarianceSwapEngine{`RngTrait',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromMaybeInt`Maybe Word' -- ^timeSteps
  ,fromMaybeInt`Maybe Word' -- ^timeStepsPerYear
  ,`Bool' -- ^brownianBridge
  ,`Bool' -- ^antitheticVariate
  ,fromMaybeInt`Maybe Word' -- ^requiredSamples
  ,fromMaybeDouble`Maybe Double' -- ^requiredTolerance
  ,fromMaybeInt`Maybe Word' -- ^maxSamples
  ,fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBinomialVanillaEngine as binomialVanillaEngine{`BinomialTree',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^timeSteps
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlFdBlackScholesVanillaEngine as fdBlackScholesVanillaEngine{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',fromIntegral`Word' -- ^timeSteps
  ,fromIntegral`Word' -- ^gridPoints
  ,fromIntegral`Word' -- ^timeDependent
  ,withFdmSchemeDesc*`FdmScheme',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#fun qlBinomialConvertibleEngine as binomialConvertibleEngine{`BinomialTree',withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,fromIntegral`Word' -- ^timeSteps
  ,withQuote*`GenQuote a' -- ^creditSpread
  ,withDividendArray*`[Dividend]'& -- ^dividends
  ,preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableFixedRateBondEngine1 as blackCallableFixedRateBondEngine'{withGenTermStructure*`CallableBondVolatilityStructure',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableFixedRateBondEngine as blackCallableFixedRateBondEngine{withQuote*`GenQuote a',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine1 as blackCallableZeroCouponBondEngine'{withGenTermStructure*`CallableBondVolatilityStructure',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine as blackCallableZeroCouponBondEngine{withQuote*`GenQuote a',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#fun qlTreeCallableFixedRateBondEngine1 as treeCallableFixedRateBondEngine'{withShortRateModel*`ShortRateModel',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}

{#fun qlTreeCallableFixedRateBondEngine as treeCallableFixedRateBondEngine{withShortRateModel*`ShortRateModel',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeCallableZeroCouponBondEngine1 as treeCallableZeroCouponBondEngine'{withShortRateModel*`ShortRateModel',withTimeGrid*`TimeGrid',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlTreeCallableZeroCouponBondEngine as treeCallableZeroCouponBondEngine{withShortRateModel*`ShortRateModel',fromIntegral`Word' -- ^timeSteps
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`PricingEngine'peekPricingEngine*#}
{#fun qlBlackCalculatorAlpha as alpha{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBlackCalculatorBeta as beta{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBlackCalculator1 as blackCalculator'{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalculator'peekBlackCalculator*#}

{#pointer *QlStrikedTypePayoff foreign newtype nocode#}
{#fun qlBlackCalculator as blackCalculator{withStrikedPayoff*`StrikedPayoff'
  ,`Double' -- ^forward
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalculator'peekBlackCalculator*#}

-- |Sensitivity to change in the underlying spot price.
{#fun qlBlackCalculatorDelta as blackDelta{withBlackCalculator*`GenBlackCalculator a', `Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to change in the underlying forward price.
{#fun qlBlackCalculatorDeltaForward as deltaForward{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to dividend/growth rate.
{#fun qlBlackCalculatorDividendRho as dividendRho{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity in percent to a percent change in the underlying spot price.
{#fun qlBlackCalculatorElasticity as blackElasticity{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity in percent to a percent change in the underlying forward price.
{#fun qlBlackCalculatorElasticityForward as elasticityForward{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Second order derivative with respect to change in the underlying spot price.
{#fun qlBlackCalculatorGamma as blackGamma{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^spot
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Second order derivative with respect to change in the underlying forward price.
{#fun qlBlackCalculatorGammaForward as gammaForward{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
{#fun qlBlackCalculatorItmAssetProbability as itmAssetProbability{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Probability of being in the money in the bond martingale measure, i.e. N(d2). It is a risk-neutral probability, not the real world one.
{#fun qlBlackCalculatorItmCashProbability as itmCashProbability{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to discounting rate.
{#fun qlBlackCalculatorRho as rho{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to strike.
{#fun qlBlackCalculatorStrikeSensitivity as strikeSensitivity{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to time to maturity.
{#fun qlBlackCalculatorTheta as blackTheta{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to time to maturity per day, assuming 365 day per year.
{#fun qlBlackCalculatorThetaPerDay as blackThetaPerDay{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^spot
  ,`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBlackCalculatorValue as value{withBlackCalculator*`GenBlackCalculator a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Sensitivity to volatility.
{#fun qlBlackCalculatorVega as vega{withBlackCalculator*`GenBlackCalculator a',`Double' -- ^maturity
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlBlackScholesCalculator1 as blackScholesCalculator'{fromEnumC`OptionType',`Double' -- ^strike
  ,`Double' -- ^spot
  ,`Double' -- ^growth
  ,`Double' -- ^stdDev
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`BlackScholesCalculator'peekBlackScholesCalculator*#}
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

{#pointer *QlPlainVanillaPayoff foreign newtype nocode#}

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

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
