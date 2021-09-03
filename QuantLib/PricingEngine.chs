{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.PricingEngine
  (
    PricingEngine
  , BlackCalculator
  , BlackScholesCalculator

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
  --, fdAmericanEngine
  --, fdBermudanEngine
  --, fdEuropeanEngine

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

  , setPricingEngine
  )
  where

import QuantLib.Type
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.TermStructure.Volatility#}(OptionletVolatilityStructure, SwaptionVolatilityStructure, CallableBondVolatilityStructure)
{#import QuantLib.TermStructure.Credit#}(DefaultProbabilityTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Process#}(GeneralizedBlackScholesProcess, HestonProcess, BlackProcess, HybridHestonHullWhiteProcess, VarianceGammaProcess, HestonProcess, Merton76Process, GJRGARCHProcess)
{#import QuantLib.Model#}
{#import QuantLib.Time.Schedule#}(TimeUnit)
import QuantLib.Internal.Type
{#import QuantLib.Math#}
{#import QuantLib.Instrument#}(Instrument)
{#import QuantLib.Instrument.Option#} hiding(itmCashProbability, deltaForward, strikeSensitivity, dividendRho, rho, vega)
import QuantLib.Internal.Enum

{#pointer *QlQuote as Quote foreign -> CQuote nocode#}

{#pointer *QlPricingEngine as PricingEngine foreign finalizer qlFreePricingEngine newtype#}
instance ForeignObject PricingEngine where
  withObject = withPricingEngine
  constructor = PricingEngine
  finalizer = qlFreePricingEngine

{#pointer *QlBlackCalculator as BlackCalculator foreign finalizer qlFreeBlackCalculator newtype#}
instance ForeignObject BlackCalculator where
  withObject = withBlackCalculator
  constructor = BlackCalculator
  finalizer = qlFreeBlackCalculator

{#pointer *QlBlackScholesCalculator as BlackScholesCalculator foreign finalizer qlFreeBlackScholesCalculator newtype#}
instance ForeignObject BlackScholesCalculator where
  withObject = withBlackScholesCalculator
  constructor = BlackScholesCalculator
  finalizer = qlFreeBlackScholesCalculator
asBlackCalculator :: (a `Derives` BlackCalculator) => a -> IO BlackCalculator
asBlackCalculator = cast
instance BlackScholesCalculator `Derives` BlackCalculator where cast = qlBlackScholesCalculatorAsBlackCalculator
{#fun qlBlackScholesCalculatorAsBlackCalculator {`BlackScholesCalculator'} -> `BlackCalculator'#}

{#fun qlDiscountingBondEngine as discountingBondEngine {`YieldTermStructure', fromMaybeBool `Maybe Bool', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlDiscountingSwapEngine as discountingSwapEngine {`YieldTermStructure', fromMaybeBool `Maybe Bool', withMaybeDay* `Maybe Day', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticBarrierEngine as analyticBarrierEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticCliquetEngine as analyticCliquetEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticContinuousFixedLookbackEngine as analyticContinuousFixedLookbackEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticContinuousFloatingLookbackEngine as analyticContinuousFloatingLookbackEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticContinuousGeometricAveragePriceAsianEngine as analyticContinuousGeometricAveragePriceAsianEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticDigitalAmericanEngine as analyticDigitalAmericanEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticDiscreteGeometricAveragePriceAsianEngine as analyticDiscreteGeometricAveragePriceAsianEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticDiscreteGeometricAverageStrikeAsianEngine as analyticDiscreteGeometricAverageStrikeAsianEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticDividendEuropeanEngine as analyticDividendEuropeanEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticEuropeanEngine as analyticEuropeanEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticPerformanceEngine as analyticPerformanceEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBlackCapFloorEngine1 as blackCapFloorEngine' {`YieldTermStructure', `OptionletVolatilityStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBlackCapFloorEngine as blackCapFloorEngine {`YieldTermStructure', withComplexType* `Quote', withDayCounter*`DayCounter', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBlackSwaptionEngine as blackSwaptionEngine {`YieldTermStructure', withComplexType* `Quote', withDayCounter*`DayCounter', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBlackSwaptionEngine1 as blackSwaptionEngine' {`YieldTermStructure', `SwaptionVolatilityStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticBSMHullWhiteEngine as analyticBSMHullWhiteEngine {`Double', withObject* `GeneralizedBlackScholesProcess', withObject* `HullWhite', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
{#fun qlAnalyticCapFloorEngine as analyticCapFloorEngine {withObject* `AffineModel', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticGJRGARCHEngine as analyticGJRGARCHEngine {withObject* `GJRGARCHModel', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticHestonEngine as analyticHestonEngine {withObject* `HestonModel', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticHestonHullWhiteEngine as analyticHestonHullWhiteEngine {withObject* `HestonModel', withObject* `HullWhite', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesEngine as batesEngine {withObject* `BatesModel', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlFFTVanillaEngine as fftVanillaEngine {withObject* `GeneralizedBlackScholesProcess', `Double', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlG2SwaptionEngine as g2SwaptionEngine {withObject* `G2', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlJumpDiffusionEngine as jumpDiffusionEngine {withObject* `Merton76Process', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCapFloorEngine as treeCapFloorEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeSwaptionEngine as treeSwaptionEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeVanillaSwapEngine as treeVanillaSwapEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlVarianceGammaEngine as varianceGammaEngine {withObject* `VarianceGammaProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticHestonEngine1 as analyticHestonEngine' {withObject* `HestonModel', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlAnalyticHestonHullWhiteEngine1 as analyticHestonHullWhiteEngine' {withObject* `HestonModel', withObject* `HullWhite', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesEngine1 as batesEngine' {withObject* `BatesModel', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBaroneAdesiWhaleyApproximationEngine as baroneAdesiWhaleyApproximationEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesDetJumpEngine1 as batesDetJumpEngine' {withObject* `BatesDetJumpModel', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesDetJumpEngine as batesDetJumpEngine {withObject* `BatesDetJumpModel', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesDoubleExpDetJumpEngine1 as batesDoubleExpDetJumpEngine' {withObject* `BatesDoubleExpDetJumpModel', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesDoubleExpDetJumpEngine as batesDoubleExpDetJumpEngine {withObject* `BatesDoubleExpDetJumpModel', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesDoubleExpEngine1 as batesDoubleExpEngine' {withObject* `BatesDoubleExpModel', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBatesDoubleExpEngine as batesDoubleExpEngine {withObject* `BatesDoubleExpModel', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBjerksundStenslandApproximationEngine as bjerksundStenslandApproximationEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlIntegralCdsEngine as integralCdsEngine {fromEnumQuantity `(Word, TimeUnit)'&, withObject* `DefaultProbabilityTermStructure', `Double', `YieldTermStructure', fromMaybeBool `Maybe Bool', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlIntegralEngine as integralEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |the term structure is only needed when the short-rate model cannot provide one itself.
{#fun qlJamshidianSwaptionEngine as jamshidianSwaptionEngine {withObject* `OneFactorAffineModel', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlJuQuadraticApproximationEngine as juQuadraticApproximationEngine {withObject* `GeneralizedBlackScholesProcess', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlKirkEngine as kirkEngine {withObject* `BlackProcess', withObject* `BlackProcess', `Double', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMidPointCdsEngine as midPointCdsEngine {withObject* `DefaultProbabilityTermStructure', `Double', `YieldTermStructure', fromMaybeBool `Maybe Bool', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlReplicatingVarianceSwapEngine as replicatingVarianceSwapEngine {withObject* `GeneralizedBlackScholesProcess', `Double', withDoubleArray* `[Double]'&, withDoubleArray* `[Double]'&, preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlStulzEngine as stulzEngine {withObject* `GeneralizedBlackScholesProcess', withObject* `GeneralizedBlackScholesProcess', `Double', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlLfmSwaptionEngine as lfmSwaptionEngine {withObject* `LiborForwardModel', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCapFloorEngine1 as treeCapFloorEngine' {withObject* `ShortRateModel', withTimeGrid*`TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeSwaptionEngine1 as treeSwaptionEngine' {withObject* `ShortRateModel', withTimeGrid*`TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeVanillaSwapEngine1 as treeVanillaSwapEngine' {withObject* `ShortRateModel', withTimeGrid*`TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#pointer *FdmSchemeDesc foreign newtype nocode#}
{#fun qlFdG2SwaptionEngine as fdG2SwaptionEngine {withObject* `G2', fromIntegral `Word', fromIntegral `Word', fromIntegral `Word', fromIntegral `Word', `Double', withEnumObject* `FdmScheme', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlFdHullWhiteSwaptionEngine as fdHullWhiteSwaptionEngine {withObject* `HullWhite', fromIntegral `Word', fromIntegral `Word', fromIntegral `Word', `Double', withEnumObject* `FdmScheme', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |/NB/ C++ classes Monte Carlo engines are additionally parameterised via statistic template argument
-- Functions below use default value of Statistics
{#fun qlMCHestonHullWhiteEngine1 as mcHestonHullWhiteEngine {`RngTrait', withObject* `HybridHestonHullWhiteProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCAmericanEngine1 as mcAmericanEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', fromIntegral `Word', `PolynomType', fromMaybeInt `Maybe Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCBarrierEngine1 as mcBarrierEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', `Bool', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCDigitalEngine1 as mcDigitalEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCDiscreteArithmeticAPEngine1 as mcDiscreteArithmeticAPEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', `Bool', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCDiscreteArithmeticASEngine1 as mcDiscreteArithmeticASEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCDiscreteGeometricAPEngine1 as mcDiscreteGeometricAPEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCEuropeanEngine1 as mcEuropeanEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCEuropeanGJRGARCHEngine1 as mcEuropeanGJRGARCHEngine {`RngTrait', withObject* `GJRGARCHProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCEuropeanHestonEngine1 as mcEuropeanHestonEngine {`RngTrait', withObject* `HestonProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCHullWhiteCapFloorEngine1 as mcHullWhiteCapFloorEngine {`RngTrait', withObject* `HullWhite', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCPerformanceEngine1 as mcPerformanceEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlMCVarianceSwapEngine1 as mcVarianceSwapEngine {`RngTrait', withObject* `GeneralizedBlackScholesProcess', fromMaybeInt `Maybe Word', fromMaybeInt `Maybe Word', `Bool', `Bool', fromMaybeInt `Maybe Word', fromMaybeDouble `Maybe Double', fromMaybeInt `Maybe Word', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBinomialVanillaEngine as binomialVanillaEngine {`BinomialTree', withObject* `GeneralizedBlackScholesProcess', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- removed from QuanLib. TODO: add binding to new functionality
-- {#fun qlFDAmericanEngine as fdAmericanEngine {`FdmScheme', withObject* `GeneralizedBlackScholesProcess', fromIntegral `Word', fromIntegral `Word', `Bool', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}
-- {#fun qlFDBermudanEngine as fdBermudanEngine {`FdmScheme', withObject* `GeneralizedBlackScholesProcess', fromIntegral `Word', fromIntegral `Word', `Bool', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}
-- {#fun qlFDEuropeanEngine as fdEuropeanEngine {`FdmScheme', withObject* `GeneralizedBlackScholesProcess', fromIntegral `Word', fromIntegral `Word', `Bool', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBinomialConvertibleEngine as binomialConvertibleEngine {`BinomialTree', withObject* `GeneralizedBlackScholesProcess', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableFixedRateBondEngine1 as blackCallableFixedRateBondEngine' {withObject* `CallableBondVolatilityStructure', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableFixedRateBondEngine as blackCallableFixedRateBondEngine {withComplexType* `Quote', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine1 as blackCallableZeroCouponBondEngine' {withObject* `CallableBondVolatilityStructure', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine as blackCallableZeroCouponBondEngine {withComplexType* `Quote', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableFixedRateBondEngine1 as treeCallableFixedRateBondEngine' {withObject* `ShortRateModel', withTimeGrid*`TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableFixedRateBondEngine as treeCallableFixedRateBondEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableZeroCouponBondEngine1 as treeCallableZeroCouponBondEngine' {withObject* `ShortRateModel', withTimeGrid*`TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableZeroCouponBondEngine as treeCallableZeroCouponBondEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBlackCalculatorAlpha as alpha {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBlackCalculatorBeta as beta {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBlackCalculator1 as blackCalculator' {fromEnumC `OptionType', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `BlackCalculator'#}

{#pointer *QlStrikedTypePayoff foreign newtype nocode#}
{#fun qlBlackCalculator as blackCalculator {withEnumObject* `StrikedPayoff', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `BlackCalculator'#}

-- |Sensitivity to change in the underlying spot price.
{#fun qlBlackCalculatorDelta as blackDelta {`BlackCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to change in the underlying forward price.
{#fun qlBlackCalculatorDeltaForward as deltaForward {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to dividend/growth rate.
{#fun qlBlackCalculatorDividendRho as dividendRho {`BlackCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity in percent to a percent change in the underlying spot price.
{#fun qlBlackCalculatorElasticity as blackElasticity {`BlackCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity in percent to a percent change in the underlying forward price.
{#fun qlBlackCalculatorElasticityForward as elasticityForward {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Second order derivative with respect to change in the underlying spot price.
{#fun qlBlackCalculatorGamma as blackGamma {`BlackCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Second order derivative with respect to change in the underlying forward price.
{#fun qlBlackCalculatorGammaForward as gammaForward {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Probability of being in the money in the asset martingale measure, i.e. N(d1). It is a risk-neutral probability, not the real world one.
{#fun qlBlackCalculatorItmAssetProbability as itmAssetProbability {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Probability of being in the money in the bond martingale measure, i.e. N(d2). It is a risk-neutral probability, not the real world one.
{#fun qlBlackCalculatorItmCashProbability as itmCashProbability {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to discounting rate.
{#fun qlBlackCalculatorRho as rho {`BlackCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to strike.
{#fun qlBlackCalculatorStrikeSensitivity as strikeSensitivity {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to time to maturity.
{#fun qlBlackCalculatorTheta as blackTheta {`BlackCalculator', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to time to maturity per day, assuming 365 day per year.
{#fun qlBlackCalculatorThetaPerDay as blackThetaPerDay {`BlackCalculator', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBlackCalculatorValue as value {`BlackCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to volatility.
{#fun qlBlackCalculatorVega as vega {`BlackCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlBlackScholesCalculator1 as blackScholesCalculator' {fromEnumC `OptionType', `Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `BlackScholesCalculator'#}

{#fun qlBlackScholesCalculator as blackScholesCalculator {withEnumObject* `StrikedPayoff', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `BlackScholesCalculator'#}

-- |Sensitivity to change in the underlying spot price.
{#fun qlBlackScholesCalculatorDelta as blackScholesDelta {`BlackScholesCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity in percent to a percent change in the underlying spot price.
{#fun qlBlackScholesCalculatorElasticity as blackScholesElasticity {`BlackScholesCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Second order derivative with respect to change in the underlying spot price.
{#fun qlBlackScholesCalculatorGamma as blackScholesGamma {`BlackScholesCalculator', preErrorCheck- `String' errorCheck*-} -> `Double'#}
-- |Sensitivity to time to maturity.
{#fun qlBlackScholesCalculatorTheta as blackScholesTheta {`BlackScholesCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Sensitivity to time to maturity per day (assuming 365 day in a year).
{#fun qlBlackScholesCalculatorThetaPerDay as blackScholesThetaPerDay {`BlackScholesCalculator', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormula1 as blackFormula' {withEnumObject* `PlainVanillaPayoff', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 formula /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormula as blackFormula {fromEnumC `OptionType', `Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#pointer *QlPlainVanillaPayoff foreign newtype nocode#}

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaCashItmProbability1 as blackCashItmProbability' {withEnumObject *`PlainVanillaPayoff', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaCashItmProbability as blackCashItmProbability {fromEnumC `OptionType', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaImpliedStdDev1 as blackImpliedStdDev' {withEnumObject *`PlainVanillaPayoff', `Double', `Double', `Double', `Double', `Double', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity)
{#fun qlQuantLibBlackFormulaImpliedStdDev as blackImpliedStdDev {fromEnumC `OptionType', `Double', `Double', `Double', `Double', `Double', `Double', `Double', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
{#fun qlQuantLibBlackFormulaImpliedStdDevApproximation1 as blackImpliedStdDevApproximation' {withEnumObject *`PlainVanillaPayoff', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Approximated Black 1976 implied standard deviation, i.e. volatility*sqrt(timeToMaturity).It is calculated using Brenner and Subrahmanyan (1988) and Feinstein (1988) approximation for at-the-money forward option, with the extended moneyness approximation by Corrado and Miller (1996)
{#fun qlQuantLibBlackFormulaImpliedStdDevApproximation as blackImpliedStdDevApproximation {fromEnumC `OptionType', `Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
{#fun qlQuantLibBlackFormulaStdDevDerivative1 as blackStdDevDerivative' {withEnumObject *`PlainVanillaPayoff', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 formula for standard deviation derivative /Warning/ instead of volatility it uses standard deviation, i.e. volatility*sqrt(timeToMaturity), and it returns the derivative with respect to the standard deviation. If T is the time to maturity Black vega would be blackStdDevDerivative(strike, forward, stdDev)*sqrt(T)
{#fun qlQuantLibBlackFormulaStdDevDerivative as blackStdDevDerivative {`Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black 1976 formula for derivative with respect to implied vol, this is basically the vega, but if you want 1% change multiply by 1%
{#fun qlQuantLibBlackFormulaVolDerivative as blackVolDerivative {`Double', `Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
{#fun qlQuantLibBachelierBlackFormula1 as bachelierBlackFormula' {withEnumObject *`PlainVanillaPayoff', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Black style formula when forward is normal rather than log-normal. This is essentially the model of Bachelier. /Warning/ Bachelier model needs absolute volatility, not percentage volatility. Standard deviation is absoluteVolatility*sqrt(timeToMaturity)
{#fun qlQuantLibBachelierBlackFormula as bachelierBlackFormula {fromEnumC `OptionType', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |default theta-per-day calculation
{#fun qlQuantLibDefaultThetaPerDay as defaultThetaPerDay {`Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

class Priceable a where setPricingEngine :: a -> PricingEngine -> IO ()

instance Priceable BlackCalibrationHelper where setPricingEngine = qlBlackCalibrationHelperSetPricingEngine
{#fun qlBlackCalibrationHelperSetPricingEngine {withObject* `BlackCalibrationHelper', `PricingEngine', preErrorCheck- `String' errorCheck*-} -> `()'#}

instance Priceable Instrument where setPricingEngine = qlInstrumentSetPricingEngine
{#fun qlInstrumentSetPricingEngine {withObject* `Instrument', `PricingEngine', preErrorCheck- `String' errorCheck*-} -> `()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
