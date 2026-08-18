// this file intentionally does not contain any references to wrappers, only vanilla QuantLib is used here
#include <ql/pricingengines/all.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/pricingengines/barrier/binomialbarrierengine.hpp>
#include <ql/experimental/barrieroption/binomialdoublebarrierengine.hpp>
#include <ql/experimental/barrieroption/mcdoublebarrierengine.hpp>
#include <ql/experimental/callablebonds/blackcallablebondengine.hpp>
#include <ql/experimental/callablebonds/treecallablebondengine.hpp>
#include <ql/pricingengines/bond/binomialconvertibleengine.hpp>
#include <ql/experimental/lattices/extendedbinomialtree.hpp>
#include <ql/experimental/math/zigguratrng.hpp>
#include <ql/methods/finitedifferences/expliciteuler.hpp>
#include <ql/methods/finitedifferences/impliciteuler.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/instruments/dividendschedule.hpp>
#include <ql/methods/montecarlo/pathgenerator.hpp>
#include <ql/methods/montecarlo/multipathgenerator.hpp>
#include <ql/experimental/exoticoptions/mchimalayaengine.hpp>
#include <ql/experimental/exoticoptions/mcpagodaengine.hpp>

namespace hasquant {
#include "qlEnumObjects.h"
}

using QuantLib::ext::shared_ptr;
#include "qlPricingEngineAux.h"
using namespace QuantLib;

PricingEngine* qlBinomialVanillaEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  switch (tree) {
  case hasquant::JarrowRudd:
    return new BinomialVanillaEngine<JarrowRudd>(process, timeSteps);
  case hasquant::CoxRossRubinstein:
    return new BinomialVanillaEngine<CoxRossRubinstein>(process, timeSteps);
  case hasquant::AdditiveEQPBinomialTree:
    return new BinomialVanillaEngine<AdditiveEQPBinomialTree>(process, timeSteps);
  case hasquant::Trigeorgis:
    return new BinomialVanillaEngine<Trigeorgis>(process, timeSteps);
  case hasquant::Tian:
    return new BinomialVanillaEngine<Tian>(process, timeSteps);
  case hasquant::LeisenReimer:
    return new BinomialVanillaEngine<LeisenReimer>(process, timeSteps);
  case hasquant::Joshi4:
    return new BinomialVanillaEngine<Joshi4>(process, timeSteps);
  case hasquant::ExtendedJarrowRudd:
    return new BinomialVanillaEngine<ExtendedJarrowRudd>(process, timeSteps);
  case hasquant::ExtendedCoxRossRubinstein:
    return new BinomialVanillaEngine<ExtendedCoxRossRubinstein>(process, timeSteps);
  case hasquant::ExtendedAdditiveEQPBinomialTree:
    return new BinomialVanillaEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps);
  case hasquant::ExtendedTrigeorgis:
    return new BinomialVanillaEngine<ExtendedTrigeorgis>(process, timeSteps);
  case hasquant::ExtendedTian:
    return new BinomialVanillaEngine<ExtendedTian>(process, timeSteps);
  case hasquant::ExtendedLeisenReimer:
    return new BinomialVanillaEngine<ExtendedLeisenReimer>(process, timeSteps);
  case hasquant::ExtendedJoshi4:
    return new BinomialVanillaEngine<ExtendedJoshi4>(process, timeSteps);
  };
  QL_FAIL("Unknown Binomial Tree "<< tree);
}

PricingEngine* qlBinomialConvertibleEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, const Handle<Quote>& cs, DividendSchedule d) {
  switch (tree) {
  case hasquant::JarrowRudd:
    return new BinomialConvertibleEngine<JarrowRudd>(process, timeSteps, cs, d);
  case hasquant::CoxRossRubinstein:
    return new BinomialConvertibleEngine<CoxRossRubinstein>(process, timeSteps, cs, d);
  case hasquant::AdditiveEQPBinomialTree:
    return new BinomialConvertibleEngine<AdditiveEQPBinomialTree>(process, timeSteps, cs, d);
  case hasquant::Trigeorgis:
    return new BinomialConvertibleEngine<Trigeorgis>(process, timeSteps, cs, d);
  case hasquant::Tian:
    return new BinomialConvertibleEngine<Tian>(process, timeSteps, cs, d);
  case hasquant::LeisenReimer:
    return new BinomialConvertibleEngine<LeisenReimer>(process, timeSteps, cs, d);
  case hasquant::Joshi4:
    return new BinomialConvertibleEngine<Joshi4>(process, timeSteps, cs, d);
  case hasquant::ExtendedJarrowRudd:
    return new BinomialConvertibleEngine<ExtendedJarrowRudd>(process, timeSteps, cs, d);
  case hasquant::ExtendedCoxRossRubinstein:
    return new BinomialConvertibleEngine<ExtendedCoxRossRubinstein>(process, timeSteps, cs, d);
  case hasquant::ExtendedAdditiveEQPBinomialTree:
    return new BinomialConvertibleEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps, cs, d);
  case hasquant::ExtendedTrigeorgis:
    return new BinomialConvertibleEngine<ExtendedTrigeorgis>(process, timeSteps, cs, d);
  case hasquant::ExtendedTian:
    return new BinomialConvertibleEngine<ExtendedTian>(process, timeSteps, cs, d);
  case hasquant::ExtendedLeisenReimer:
    return new BinomialConvertibleEngine<ExtendedLeisenReimer>(process, timeSteps, cs, d);
  case hasquant::ExtendedJoshi4:
    return new BinomialConvertibleEngine<ExtendedJoshi4>(process, timeSteps, cs, d);
  };
  QL_FAIL("Unknown Binomial Tree "<< tree);
}

PricingEngine* qlBinomialBarrierEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned maxTimeSteps) {
  switch (tree) {
  case hasquant::JarrowRudd:
    return new BinomialBarrierEngine<JarrowRudd, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::CoxRossRubinstein:
    return new BinomialBarrierEngine<CoxRossRubinstein, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::AdditiveEQPBinomialTree:
    return new BinomialBarrierEngine<AdditiveEQPBinomialTree, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::Trigeorgis:
    return new BinomialBarrierEngine<Trigeorgis, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::Tian:
    return new BinomialBarrierEngine<Tian, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::LeisenReimer:
    return new BinomialBarrierEngine<LeisenReimer, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::Joshi4:
    return new BinomialBarrierEngine<Joshi4, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedJarrowRudd:
    return new BinomialBarrierEngine<ExtendedJarrowRudd, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedCoxRossRubinstein:
    return new BinomialBarrierEngine<ExtendedCoxRossRubinstein, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedAdditiveEQPBinomialTree:
    return new BinomialBarrierEngine<ExtendedAdditiveEQPBinomialTree, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedTrigeorgis:
    return new BinomialBarrierEngine<ExtendedTrigeorgis, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedTian:
    return new BinomialBarrierEngine<ExtendedTian, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedLeisenReimer:
    return new BinomialBarrierEngine<ExtendedLeisenReimer, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  case hasquant::ExtendedJoshi4:
    return new BinomialBarrierEngine<ExtendedJoshi4, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  };
  QL_FAIL("Unknown Binomial Tree "<< tree);
}

PricingEngine* qlBinomialDoubleBarrierEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  switch (tree) {
  case hasquant::JarrowRudd:
    return new BinomialDoubleBarrierEngine<JarrowRudd>(process, timeSteps);
  case hasquant::CoxRossRubinstein:
    return new BinomialDoubleBarrierEngine<CoxRossRubinstein>(process, timeSteps);
  case hasquant::AdditiveEQPBinomialTree:
    return new BinomialDoubleBarrierEngine<AdditiveEQPBinomialTree>(process, timeSteps);
  case hasquant::Trigeorgis:
    return new BinomialDoubleBarrierEngine<Trigeorgis>(process, timeSteps);
  case hasquant::Tian:
    return new BinomialDoubleBarrierEngine<Tian>(process, timeSteps);
  case hasquant::LeisenReimer:
    return new BinomialDoubleBarrierEngine<LeisenReimer>(process, timeSteps);
  case hasquant::Joshi4:
    return new BinomialDoubleBarrierEngine<Joshi4>(process, timeSteps);
  case hasquant::ExtendedJarrowRudd:
    return new BinomialDoubleBarrierEngine<ExtendedJarrowRudd>(process, timeSteps);
  case hasquant::ExtendedCoxRossRubinstein:
    return new BinomialDoubleBarrierEngine<ExtendedCoxRossRubinstein>(process, timeSteps);
  case hasquant::ExtendedAdditiveEQPBinomialTree:
    return new BinomialDoubleBarrierEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps);
  case hasquant::ExtendedTrigeorgis:
    return new BinomialDoubleBarrierEngine<ExtendedTrigeorgis>(process, timeSteps);
  case hasquant::ExtendedTian:
    return new BinomialDoubleBarrierEngine<ExtendedTian>(process, timeSteps);
  case hasquant::ExtendedLeisenReimer:
    return new BinomialDoubleBarrierEngine<ExtendedLeisenReimer>(process, timeSteps);
  case hasquant::ExtendedJoshi4:
    return new BinomialDoubleBarrierEngine<ExtendedJoshi4>(process, timeSteps);
  };
  QL_FAIL("Unknown Binomial Tree "<< tree);
}

PricingEngine* qlMCDoubleBarrierEngineAux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCDoubleBarrierEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCDoubleBarrierEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCDoubleBarrierEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCDoubleBarrierEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}

// TODO use second template argument (Statistics)
PricingEngine* qlMCVarianceSwapEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCVarianceSwapEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCVarianceSwapEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCVarianceSwapEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCVarianceSwapEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCHestonHullWhiteEngine1Aux(int rngtrait, const shared_ptr<HybridHestonHullWhiteProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCHestonHullWhiteEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCHestonHullWhiteEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCHestonHullWhiteEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCHestonHullWhiteEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCAmericanEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, LsmBasisSystem::PolynomialType polynomType, unsigned nCalibrationSamples, ext::optional<bool> antitheticVariateCalibration, unsigned seedCalibration) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCAmericanEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::PoissonPseudoRandom:
    return new MCAmericanEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::LowDiscrepancy:
    return new MCAmericanEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::Ziggurat:
    return new MCAmericanEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCBarrierEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCBarrierEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCBarrierEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::LowDiscrepancy:
    return new MCBarrierEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::Ziggurat:
    return new MCBarrierEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDigitalEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCDigitalEngine<PseudoRandom>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCDigitalEngine<PoissonPseudoRandom>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCDigitalEngine<LowDiscrepancy>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCDigitalEngine<Ziggurat>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDiscreteArithmeticAPEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCDiscreteArithmeticAPEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCDiscreteArithmeticAPEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCDiscreteArithmeticAPEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCDiscreteArithmeticAPEngine<Ziggurat>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDiscreteArithmeticASEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCDiscreteArithmeticASEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCDiscreteArithmeticASEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCDiscreteArithmeticASEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCDiscreteArithmeticASEngine<Ziggurat>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCDiscreteGeometricAPEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCDiscreteGeometricAPEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCDiscreteGeometricAPEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCDiscreteGeometricAPEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCDiscreteGeometricAPEngine<Ziggurat>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCEuropeanEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCEuropeanEngine<PseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCEuropeanEngine<PoissonPseudoRandom>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCEuropeanEngine<LowDiscrepancy>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCEuropeanEngine<Ziggurat>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCEuropeanGJRGARCHEngine1Aux(int rngtrait, const shared_ptr<GJRGARCHProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCEuropeanGJRGARCHEngine<PseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCEuropeanGJRGARCHEngine<PoissonPseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCEuropeanGJRGARCHEngine<LowDiscrepancy>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCEuropeanGJRGARCHEngine<Ziggurat>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCEuropeanHestonEngine1Aux(int rngtrait, const shared_ptr<HestonProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCEuropeanHestonEngine<PseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCEuropeanHestonEngine<PoissonPseudoRandom>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCEuropeanHestonEngine<LowDiscrepancy>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCEuropeanHestonEngine<Ziggurat>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCHullWhiteCapFloorEngine1Aux(int rngtrait, shared_ptr<HullWhite> model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCHullWhiteCapFloorEngine<PseudoRandom>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCHullWhiteCapFloorEngine<PoissonPseudoRandom>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCHullWhiteCapFloorEngine<LowDiscrepancy>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCHullWhiteCapFloorEngine<Ziggurat>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCHimalayaEngine1Aux(int rngtrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCHimalayaEngine<PseudoRandom>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCHimalayaEngine<PoissonPseudoRandom>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCHimalayaEngine<LowDiscrepancy>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCHimalayaEngine<Ziggurat>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCPagodaEngine1Aux(int rngtrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCPagodaEngine<PseudoRandom>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCPagodaEngine<PoissonPseudoRandom>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCPagodaEngine<LowDiscrepancy>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCPagodaEngine<Ziggurat>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
PricingEngine* qlMCPerformanceEngine1Aux(int rngtrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCPerformanceEngine<PseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return new MCPerformanceEngine<PoissonPseudoRandom>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return new MCPerformanceEngine<LowDiscrepancy>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return new MCPerformanceEngine<Ziggurat>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}

PricingEngine* qlFdBlackScholesVanillaEngineAux(const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, const FdmSchemeDesc &fdScheme, bool localVol, double illegalLocalVolOverwrite, int cashDividendModel) {return new FdBlackScholesVanillaEngine(process, tGrid, xGrid, dampingSteps, fdScheme, localVol, illegalLocalVolOverwrite, (FdBlackScholesVanillaEngine::CashDividendModel)cashDividendModel);}

class PolymorphicPathGenerator {
private:
  typedef MultiPathGenerator<PseudoRandom::rsg_type> PseudoRandomPathGenerator;
  typedef MultiPathGenerator<LowDiscrepancy::rsg_type> SobolPathGenerator;
  typedef MultiPathGenerator<PoissonPseudoRandom::rsg_type> PoissonPathGenerator;
  typedef MultiPathGenerator<Ziggurat::rsg_type> ZigguratPathGenerator;
public:
  PolymorphicPathGenerator(int rngtrait, const shared_ptr<StochasticProcess> p, const TimeGrid &t, unsigned seed, unsigned dim, bool brownianBridge) {
    init(rngtrait, p, t, seed, dim, brownianBridge, SobolRsg::Jaeckel);
  }
  PolymorphicPathGenerator(SobolRsg::DirectionIntegers dir, const shared_ptr<StochasticProcess> p, const TimeGrid &t, unsigned seed, unsigned dim, bool brownianBridge) {
    init(hasquant::LowDiscrepancy, p, t, seed, dim, brownianBridge, dir);
  }
  const Sample<MultiPath>& next() const {return _next();}
  const Sample<MultiPath>& antithetic() const {return _antithetic();}
private:
  void init(int rngtrait, const shared_ptr<StochasticProcess> p, const TimeGrid &t, unsigned seed, unsigned dim, bool brownianBridge, SobolRsg::DirectionIntegers dir) {
    switch (rngtrait) {
    case hasquant::PseudoRandom:
      _pseudoRandom = std::unique_ptr<PseudoRandomPathGenerator>(new PseudoRandomPathGenerator(p, t, PseudoRandom::rsg_type(PseudoRandom::ursg_type(dim, PseudoRandom::urng_type(seed))), brownianBridge));
      _next = std::bind(static_cast<const Sample<MultiPath>& (PseudoRandomPathGenerator::*)() const>(&PseudoRandomPathGenerator::next), _pseudoRandom.get());
      _antithetic = std::bind(&PseudoRandomPathGenerator::antithetic, _pseudoRandom.get());
      break;
    case hasquant::PoissonPseudoRandom:
      _poisson = std::unique_ptr<PoissonPathGenerator>(new PoissonPathGenerator(p, t, PoissonPseudoRandom::rsg_type(PoissonPseudoRandom::ursg_type(dim, PoissonPseudoRandom::urng_type(seed))), brownianBridge));
      _next = std::bind(static_cast<const Sample<MultiPath>& (PoissonPathGenerator::*)() const>(&PoissonPathGenerator::next), _poisson.get());
      _antithetic = std::bind(&PoissonPathGenerator::antithetic, _poisson.get());
      break;
    case hasquant::LowDiscrepancy:
      _sobol = std::unique_ptr<SobolPathGenerator>(new SobolPathGenerator(p, t, LowDiscrepancy::rsg_type(SobolRsg(dim, seed, dir)), brownianBridge));
      _next = std::bind(static_cast<const Sample<MultiPath>& (SobolPathGenerator::*)() const>(&SobolPathGenerator::next), _sobol.get());
      _antithetic = std::bind(&SobolPathGenerator::antithetic, _sobol.get());
      break;
    case hasquant::Ziggurat:
      _ziggurat = std::unique_ptr<ZigguratPathGenerator>(new ZigguratPathGenerator(p, t, Ziggurat::rsg_type(dim, ZigguratRng(seed)), brownianBridge));
      _next = std::bind(static_cast<const Sample<MultiPath>& (ZigguratPathGenerator::*)() const>(&ZigguratPathGenerator::next), _ziggurat.get());
      _antithetic = std::bind(&ZigguratPathGenerator::antithetic, _ziggurat.get());
      break;
    default:
      QL_FAIL("Unknown RNG "<< rngtrait);
    }
  }
  std::unique_ptr<PseudoRandomPathGenerator> _pseudoRandom;
  std::unique_ptr<SobolPathGenerator> _sobol;
  std::unique_ptr<PoissonPathGenerator> _poisson;
  std::unique_ptr<ZigguratPathGenerator> _ziggurat;
  std::function<const Sample<MultiPath>& ()> _next;
  std::function<const Sample<MultiPath>& ()> _antithetic;
};

PolymorphicPathGenerator* qlPathGeneratorAux(int rngtrait, const shared_ptr<StochasticProcess> p, const TimeGrid &grid, unsigned seed, unsigned dim, bool brownianBridge) {
  return new PolymorphicPathGenerator(rngtrait, p, grid, seed, dim, brownianBridge);
}

PolymorphicPathGenerator* qlSobolPathGeneratorAux(SobolRsg::DirectionIntegers dir, const shared_ptr<StochasticProcess> p, const TimeGrid &grid, unsigned seed, unsigned dim, bool brownianBridge) {
  return new PolymorphicPathGenerator(dir, p, grid, seed, dim, brownianBridge);
}

void qlFreePolymorphicPathGeneratorAux(PolymorphicPathGenerator *p) {delete p;}
const Sample<MultiPath>& qlPathGeneratorNextAux(PolymorphicPathGenerator *p) {return p->next();}
const Sample<MultiPath>& qlPathGeneratorAntitheticAux(PolymorphicPathGenerator *p) {return p->antithetic();}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
