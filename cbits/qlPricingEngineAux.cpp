#include <ql/pricingengines/all.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/experimental/callablebonds/blackcallablebondengine.hpp>
#include <ql/experimental/callablebonds/treecallablebondengine.hpp>
#include <ql/experimental/convertiblebonds/binomialconvertibleengine.hpp>
#include <ql/experimental/lattices/extendedbinomialtree.hpp>
#include <ql/experimental/math/zigguratrng.hpp>
#include <ql/methods/finitedifferences/expliciteuler.hpp>
#include <ql/methods/finitedifferences/impliciteuler.hpp>

#include "qlPricingEngineAux.h"

using namespace QuantLib;

PricingEngine* qlBinomialVanillaEngineAux(const char *tree, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  if (!strcmp(tree, "JarrowRudd"))
    return new BinomialVanillaEngine<JarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "CoxRossRubinstein"))
    return new BinomialVanillaEngine<CoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "AdditiveEQPBinomialTree"))
    return new BinomialVanillaEngine<AdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "Trigeorgis"))
    return new BinomialVanillaEngine<Trigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "Tian"))
    return new BinomialVanillaEngine<Tian>(process, timeSteps);
  else if (!strcmp(tree, "LeisenReimer"))
    return new BinomialVanillaEngine<LeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "Joshi4"))
    return new BinomialVanillaEngine<Joshi4>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJarrowRudd"))
    return new BinomialVanillaEngine<ExtendedJarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedCoxRossRubinstein"))
    return new BinomialVanillaEngine<ExtendedCoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedAdditiveEQPBinomialTree"))
    return new BinomialVanillaEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTrigeorgis"))
    return new BinomialVanillaEngine<ExtendedTrigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTian"))
    return new BinomialVanillaEngine<ExtendedTian>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedLeisenReimer"))
    return new BinomialVanillaEngine<ExtendedLeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJoshi4"))
    return new BinomialVanillaEngine<ExtendedJoshi4>(process, timeSteps);
  else
    QL_FAIL("Unknown Binomial Tree "<< tree);
}

PricingEngine* qlBinomialConvertibleEngineAux(const char *tree, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  if (!strcmp(tree, "JarrowRudd"))
    return new BinomialConvertibleEngine<JarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "CoxRossRubinstein"))
    return new BinomialConvertibleEngine<CoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "AdditiveEQPBinomialTree"))
    return new BinomialConvertibleEngine<AdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "Trigeorgis"))
    return new BinomialConvertibleEngine<Trigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "Tian"))
    return new BinomialConvertibleEngine<Tian>(process, timeSteps);
  else if (!strcmp(tree, "LeisenReimer"))
    return new BinomialConvertibleEngine<LeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "Joshi4"))
    return new BinomialConvertibleEngine<Joshi4>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJarrowRudd"))
    return new BinomialConvertibleEngine<ExtendedJarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedCoxRossRubinstein"))
    return new BinomialConvertibleEngine<ExtendedCoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedAdditiveEQPBinomialTree"))
    return new BinomialConvertibleEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTrigeorgis"))
    return new BinomialConvertibleEngine<ExtendedTrigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTian"))
    return new BinomialConvertibleEngine<ExtendedTian>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedLeisenReimer"))
    return new BinomialConvertibleEngine<ExtendedLeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJoshi4"))
    return new BinomialConvertibleEngine<ExtendedJoshi4>(process, timeSteps);
  else
    QL_FAIL("Unknown Binomial Tree "<< tree);
}

// TODO use second template argument (Statistics)
PricingEngine* qlMCVarianceSwapEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCVarianceSwapEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCVarianceSwapEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCVarianceSwapEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCVarianceSwapEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCHestonHullWhiteEngine1Aux(const char *rngtrait, const ext::shared_ptr<HybridHestonHullWhiteProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCHestonHullWhiteEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCHestonHullWhiteEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCHestonHullWhiteEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCHestonHullWhiteEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCAmericanEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, LsmBasisSystem::PolynomType polynomType, unsigned nCalibrationSamples) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCAmericanEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCAmericanEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCAmericanEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCAmericanEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCBarrierEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCBarrierEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCBarrierEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCBarrierEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCBarrierEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDigitalEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCDigitalEngine<PseudoRandom>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCDigitalEngine<PoissonPseudoRandom>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCDigitalEngine<LowDiscrepancy>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCDigitalEngine<Ziggurat>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDiscreteArithmeticAPEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCDiscreteArithmeticAPEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCDiscreteArithmeticAPEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCDiscreteArithmeticAPEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCDiscreteArithmeticAPEngine<Ziggurat>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDiscreteArithmeticASEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCDiscreteArithmeticASEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCDiscreteArithmeticASEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCDiscreteArithmeticASEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCDiscreteArithmeticASEngine<Ziggurat>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDiscreteGeometricAPEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCDiscreteGeometricAPEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCDiscreteGeometricAPEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCDiscreteGeometricAPEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCDiscreteGeometricAPEngine<Ziggurat>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCEuropeanEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCEuropeanEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCEuropeanEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCEuropeanEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCEuropeanEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCEuropeanGJRGARCHEngine1Aux(const char *rngtrait, const ext::shared_ptr<GJRGARCHProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCEuropeanGJRGARCHEngine<PseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCEuropeanGJRGARCHEngine<PoissonPseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCEuropeanGJRGARCHEngine<LowDiscrepancy>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCEuropeanGJRGARCHEngine<Ziggurat>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCEuropeanHestonEngine1Aux(const char *rngtrait, const ext::shared_ptr<HestonProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCEuropeanHestonEngine<PseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCEuropeanHestonEngine<PoissonPseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCEuropeanHestonEngine<LowDiscrepancy>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCEuropeanHestonEngine<Ziggurat>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCHullWhiteCapFloorEngine1Aux(const char *rngtrait, ext::shared_ptr<HullWhite> model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCHullWhiteCapFloorEngine<PseudoRandom>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCHullWhiteCapFloorEngine<PoissonPseudoRandom>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCHullWhiteCapFloorEngine<LowDiscrepancy>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCHullWhiteCapFloorEngine<Ziggurat>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCPerformanceEngine1Aux(const char *rngtrait, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  if (!strcmp(rngtrait, "PseudoRandom"))
    return new MCPerformanceEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "PoissonPseudoRandom"))
    return new MCPerformanceEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "LowDiscrepancy"))
    return new MCPerformanceEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else if (!strcmp(rngtrait, "Ziggurat"))
    return new MCPerformanceEngine<Ziggurat>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  else
    QL_FAIL("Unknown RNG "<< rngtrait);
}

//PricingEngine* qlFDAmericanEngineAux(const char *fdscheme, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned gridPoints, int timeDependent) {
//    if (!strcmp(fdscheme, "FDCrankNicolson"))
//      return new FDAmericanEngine<CrankNicolson>(process, timeSteps, gridPoints, timeDependent);
//    else if (!strcmp(fdscheme, "FDExplicitEuler"))
//      return new FDAmericanEngine<ExplicitEuler>(process, timeSteps, gridPoints, timeDependent);
//    else if (!strcmp(fdscheme, "FDImplicitEuler"))
//      return new FDAmericanEngine<ImplicitEuler>(process, timeSteps, gridPoints, timeDependent);
//    else
//      QL_FAIL("Unknown FD Scheme "<< fdscheme);
//}
//PricingEngine* qlFDBermudanEngineAux(const char *fdscheme, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned gridPoints, int timeDependent) {
//    if (!strcmp(fdscheme, "FDCrankNicolson"))
//      return new FDBermudanEngine<CrankNicolson>(process, timeSteps, gridPoints, timeDependent);
//    else if (!strcmp(fdscheme, "FDExplicitEuler"))
//      return new FDBermudanEngine<ExplicitEuler>(process, timeSteps, gridPoints, timeDependent);
//    else if (!strcmp(fdscheme, "FDImplicitEuler"))
//      return new FDBermudanEngine<ImplicitEuler>(process, timeSteps, gridPoints, timeDependent);
//    else
//      QL_FAIL("Unknown FD Scheme "<< fdscheme);
//}
//PricingEngine* qlFDEuropeanEngineAux(const char *fdscheme, const ext::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned gridPoints, int timeDependent) {
//    if (!strcmp(fdscheme, "FDCrankNicolson"))
//      return new FDEuropeanEngine<CrankNicolson>(process, timeSteps, gridPoints, timeDependent);
//    else if (!strcmp(fdscheme, "FDExplicitEuler"))
//      return new FDEuropeanEngine<ExplicitEuler>(process, timeSteps, gridPoints, timeDependent);
//    else if (!strcmp(fdscheme, "FDImplicitEuler"))
//      return new FDEuropeanEngine<ImplicitEuler>(process, timeSteps, gridPoints, timeDependent);
//    else
//      QL_FAIL("Unknown FD Scheme "<< fdscheme);
//}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
