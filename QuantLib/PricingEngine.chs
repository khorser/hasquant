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
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.TermStructure.Volatility#}(OptionletVolatilityStructure, SwaptionVolatilityStructure, CallableBondVolatilityStructure)
{#import QuantLib.TermStructure.Credit#}(DefaultProbabilityTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Process#}
{#import QuantLib.Model#}
{#import QuantLib.Quote#}(Quote)
import QuantLib.Internal.Quote
{#import QuantLib.Time.Schedule#}(DayCounter, TimeUnit)
import QuantLib.Internal.Schedule
{#import QuantLib.Math#}
import QuantLib.Internal.Enum

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
{#fun qlBlackScholesCalculatorAsBlackCalculator as asBlackCalculator {`BlackScholesCalculator'} -> `BlackCalculator'#}

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

{#fun qlBlackCapFloorEngine as blackCapFloorEngine {`YieldTermStructure', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlBlackSwaptionEngine as blackSwaptionEngine {`YieldTermStructure', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

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

{#fun qlTreeCapFloorEngine1 as treeCapFloorEngine' {withObject* `ShortRateModel', withObject* `TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeSwaptionEngine1 as treeSwaptionEngine' {withObject* `ShortRateModel', withObject* `TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeVanillaSwapEngine1 as treeVanillaSwapEngine' {withObject* `ShortRateModel', withObject* `TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

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
{#fun qlBlackCallableFixedRateBondEngine as blackCallableFixedRateBondEngine {`Quote', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine1 as blackCallableZeroCouponBondEngine' {withObject* `CallableBondVolatilityStructure', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- |volatility is the quoted fwd yield volatility, not price vol
{#fun qlBlackCallableZeroCouponBondEngine as blackCallableZeroCouponBondEngine {`Quote', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableFixedRateBondEngine1 as treeCallableFixedRateBondEngine' {withObject* `ShortRateModel', withObject* `TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableFixedRateBondEngine as treeCallableFixedRateBondEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableZeroCouponBondEngine1 as treeCallableZeroCouponBondEngine' {withObject* `ShortRateModel', withObject* `TimeGrid', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

{#fun qlTreeCallableZeroCouponBondEngine as treeCallableZeroCouponBondEngine {withObject* `ShortRateModel', fromIntegral `Word', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `PricingEngine'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
