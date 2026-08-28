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
#include <ql/pricingengines/forward/mcforwardeuropeanbsengine.hpp>
#include <ql/pricingengines/basket/mceuropeanbasketengine.hpp>
#include <ql/pricingengines/basket/mcamericanbasketengine.hpp>
#include <ql/math/statistics/incrementalstatistics.hpp>

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

template <class RNG>
PricingEngine* qlMCDoubleBarrierEngineAuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCDoubleBarrierEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCDoubleBarrierEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCDoubleBarrierEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCDoubleBarrierEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCDoubleBarrierEngineAux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCDoubleBarrierEngineAuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCDoubleBarrierEngineAuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCDoubleBarrierEngineAuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCDoubleBarrierEngineAuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}

template <class RNG>
PricingEngine* qlMCVarianceSwapEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess>& process, unsigned timeSteps, unsigned timeStepsPerYear, bool brownianBridge, bool antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCVarianceSwapEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCVarianceSwapEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCVarianceSwapEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCVarianceSwapEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCVarianceSwapEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCVarianceSwapEngine1AuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCVarianceSwapEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCVarianceSwapEngine1AuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCVarianceSwapEngine1AuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCHestonHullWhiteEngine1AuxStat(int stattrait, const shared_ptr<HybridHestonHullWhiteProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCHestonHullWhiteEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCHestonHullWhiteEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCHestonHullWhiteEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCHestonHullWhiteEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCHestonHullWhiteEngine1Aux(int rngtrait, int stattrait, const shared_ptr<HybridHestonHullWhiteProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCHestonHullWhiteEngine1AuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCHestonHullWhiteEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCHestonHullWhiteEngine1AuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCHestonHullWhiteEngine1AuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCAmericanEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, LsmBasisSystem::PolynomialType polynomType, unsigned nCalibrationSamples, ext::optional<bool> antitheticVariateCalibration, unsigned seedCalibration) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCAmericanEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::GaussianStatistics:
    return new MCAmericanEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::GeneralStatistics:
    return new MCAmericanEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::IncrementalStatistics:
    return new MCAmericanEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCAmericanEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, LsmBasisSystem::PolynomialType polynomType, unsigned nCalibrationSamples, ext::optional<bool> antitheticVariateCalibration, unsigned seedCalibration) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCAmericanEngine1AuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::PoissonPseudoRandom:
    return qlMCAmericanEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::LowDiscrepancy:
    return qlMCAmericanEngine1AuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  case hasquant::Ziggurat:
    return qlMCAmericanEngine1AuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCBarrierEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCBarrierEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::GaussianStatistics:
    return new MCBarrierEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::GeneralStatistics:
    return new MCBarrierEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::IncrementalStatistics:
    return new MCBarrierEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCBarrierEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCBarrierEngine1AuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCBarrierEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::LowDiscrepancy:
    return qlMCBarrierEngine1AuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  case hasquant::Ziggurat:
    return qlMCBarrierEngine1AuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCDigitalEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCDigitalEngine<RNG, QuantLib::Statistics>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCDigitalEngine<RNG, QuantLib::GaussianStatistics>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCDigitalEngine<RNG, QuantLib::GeneralStatistics>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCDigitalEngine<RNG, QuantLib::IncrementalStatistics>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCDigitalEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCDigitalEngine1AuxStat<PseudoRandom>(stattrait, x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCDigitalEngine1AuxStat<PoissonPseudoRandom>(stattrait, x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCDigitalEngine1AuxStat<LowDiscrepancy>(stattrait, x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCDigitalEngine1AuxStat<Ziggurat>(stattrait, x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCForwardEuropeanBSEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCForwardEuropeanBSEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCForwardEuropeanBSEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCForwardEuropeanBSEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCForwardEuropeanBSEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCForwardEuropeanBSEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCForwardEuropeanBSEngine1AuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCForwardEuropeanBSEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCForwardEuropeanBSEngine1AuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCForwardEuropeanBSEngine1AuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCDiscreteArithmeticAPEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCDiscreteArithmeticAPEngine<RNG, QuantLib::Statistics>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCDiscreteArithmeticAPEngine<RNG, QuantLib::GaussianStatistics>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCDiscreteArithmeticAPEngine<RNG, QuantLib::GeneralStatistics>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCDiscreteArithmeticAPEngine<RNG, QuantLib::IncrementalStatistics>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCDiscreteArithmeticAPEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCDiscreteArithmeticAPEngine1AuxStat<PseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCDiscreteArithmeticAPEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCDiscreteArithmeticAPEngine1AuxStat<LowDiscrepancy>(stattrait, process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCDiscreteArithmeticAPEngine1AuxStat<Ziggurat>(stattrait, process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCDiscreteArithmeticASEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCDiscreteArithmeticASEngine<RNG, QuantLib::Statistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCDiscreteArithmeticASEngine<RNG, QuantLib::GaussianStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCDiscreteArithmeticASEngine<RNG, QuantLib::GeneralStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCDiscreteArithmeticASEngine<RNG, QuantLib::IncrementalStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCDiscreteArithmeticASEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCDiscreteArithmeticASEngine1AuxStat<PseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCDiscreteArithmeticASEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCDiscreteArithmeticASEngine1AuxStat<LowDiscrepancy>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCDiscreteArithmeticASEngine1AuxStat<Ziggurat>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCDiscreteGeometricAPEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCDiscreteGeometricAPEngine<RNG, QuantLib::Statistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCDiscreteGeometricAPEngine<RNG, QuantLib::GaussianStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCDiscreteGeometricAPEngine<RNG, QuantLib::GeneralStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCDiscreteGeometricAPEngine<RNG, QuantLib::IncrementalStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCDiscreteGeometricAPEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCDiscreteGeometricAPEngine1AuxStat<PseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCDiscreteGeometricAPEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCDiscreteGeometricAPEngine1AuxStat<LowDiscrepancy>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCDiscreteGeometricAPEngine1AuxStat<Ziggurat>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCEuropeanEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCEuropeanEngine<RNG, QuantLib::Statistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCEuropeanEngine<RNG, QuantLib::GaussianStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCEuropeanEngine<RNG, QuantLib::GeneralStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCEuropeanEngine<RNG, QuantLib::IncrementalStatistics>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCEuropeanEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCEuropeanEngine1AuxStat<PseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCEuropeanEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCEuropeanEngine1AuxStat<LowDiscrepancy>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCEuropeanEngine1AuxStat<Ziggurat>(stattrait, process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCEuropeanGJRGARCHEngine1AuxStat(int stattrait, const shared_ptr<GJRGARCHProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCEuropeanGJRGARCHEngine<RNG, QuantLib::Statistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCEuropeanGJRGARCHEngine<RNG, QuantLib::GaussianStatistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCEuropeanGJRGARCHEngine<RNG, QuantLib::GeneralStatistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCEuropeanGJRGARCHEngine<RNG, QuantLib::IncrementalStatistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCEuropeanGJRGARCHEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GJRGARCHProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCEuropeanGJRGARCHEngine1AuxStat<PseudoRandom>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCEuropeanGJRGARCHEngine1AuxStat<PoissonPseudoRandom>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCEuropeanGJRGARCHEngine1AuxStat<LowDiscrepancy>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCEuropeanGJRGARCHEngine1AuxStat<Ziggurat>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCEuropeanHestonEngine1AuxStat(int stattrait, const shared_ptr<HestonProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCEuropeanHestonEngine<RNG, QuantLib::Statistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCEuropeanHestonEngine<RNG, QuantLib::GaussianStatistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCEuropeanHestonEngine<RNG, QuantLib::GeneralStatistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCEuropeanHestonEngine<RNG, QuantLib::IncrementalStatistics>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCEuropeanHestonEngine1Aux(int rngtrait, int stattrait, const shared_ptr<HestonProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCEuropeanHestonEngine1AuxStat<PseudoRandom>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCEuropeanHestonEngine1AuxStat<PoissonPseudoRandom>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCEuropeanHestonEngine1AuxStat<LowDiscrepancy>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCEuropeanHestonEngine1AuxStat<Ziggurat>(stattrait, x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCHullWhiteCapFloorEngine1AuxStat(int stattrait, shared_ptr<HullWhite> model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCHullWhiteCapFloorEngine<RNG, QuantLib::Statistics>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCHullWhiteCapFloorEngine<RNG, QuantLib::GaussianStatistics>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCHullWhiteCapFloorEngine<RNG, QuantLib::GeneralStatistics>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCHullWhiteCapFloorEngine<RNG, QuantLib::IncrementalStatistics>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCHullWhiteCapFloorEngine1Aux(int rngtrait, int stattrait, shared_ptr<HullWhite> model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCHullWhiteCapFloorEngine1AuxStat<PseudoRandom>(stattrait, model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCHullWhiteCapFloorEngine1AuxStat<PoissonPseudoRandom>(stattrait, model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCHullWhiteCapFloorEngine1AuxStat<LowDiscrepancy>(stattrait, model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCHullWhiteCapFloorEngine1AuxStat<Ziggurat>(stattrait, model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCHimalayaEngine1AuxStat(int stattrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCHimalayaEngine<RNG, QuantLib::Statistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCHimalayaEngine<RNG, QuantLib::GaussianStatistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCHimalayaEngine<RNG, QuantLib::GeneralStatistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCHimalayaEngine<RNG, QuantLib::IncrementalStatistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCHimalayaEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCHimalayaEngine1AuxStat<PseudoRandom>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCHimalayaEngine1AuxStat<PoissonPseudoRandom>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCHimalayaEngine1AuxStat<LowDiscrepancy>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCHimalayaEngine1AuxStat<Ziggurat>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCPagodaEngine1AuxStat(int stattrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCPagodaEngine<RNG, QuantLib::Statistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCPagodaEngine<RNG, QuantLib::GaussianStatistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCPagodaEngine<RNG, QuantLib::GeneralStatistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCPagodaEngine<RNG, QuantLib::IncrementalStatistics>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCPagodaEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCPagodaEngine1AuxStat<PseudoRandom>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCPagodaEngine1AuxStat<PoissonPseudoRandom>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCPagodaEngine1AuxStat<LowDiscrepancy>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCPagodaEngine1AuxStat<Ziggurat>(stattrait, processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCEuropeanBasketEngine1AuxStat(int stattrait, const shared_ptr<StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCEuropeanBasketEngine<RNG, QuantLib::Statistics>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCEuropeanBasketEngine<RNG, QuantLib::GaussianStatistics>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCEuropeanBasketEngine<RNG, QuantLib::GeneralStatistics>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCEuropeanBasketEngine<RNG, QuantLib::IncrementalStatistics>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCEuropeanBasketEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCEuropeanBasketEngine1AuxStat<PseudoRandom>(stattrait, processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCEuropeanBasketEngine1AuxStat<PoissonPseudoRandom>(stattrait, processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCEuropeanBasketEngine1AuxStat<LowDiscrepancy>(stattrait, processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCEuropeanBasketEngine1AuxStat<Ziggurat>(stattrait, processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
// MCAmericanBasketEngine is templated <RNG> only upstream (its base MCLongstaffSchwartzEngine<BasketOption::engine,
// MultiVariate,RNG> never forwards a second template argument), so unlike every other engine in this file it has no
// S axis to expose -- not a gap, a real upstream limitation. See CLAUDE.md/PricingEngine.chs for the note.
PricingEngine* qlMCAmericanBasketEngine1Aux(int rngtrait, const shared_ptr<StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, LsmBasisSystem::PolynomialType polynomialType) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return new MCAmericanBasketEngine<PseudoRandom>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, polynomialType);
  case hasquant::PoissonPseudoRandom:
    return new MCAmericanBasketEngine<PoissonPseudoRandom>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, polynomialType);
  case hasquant::LowDiscrepancy:
    return new MCAmericanBasketEngine<LowDiscrepancy>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, polynomialType);
  case hasquant::Ziggurat:
    return new MCAmericanBasketEngine<Ziggurat>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, polynomialType);
  };
  QL_FAIL("Unknown RNG "<< rngtrait);
}
template <class RNG>
PricingEngine* qlMCPerformanceEngine1AuxStat(int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (stattrait) {
  case hasquant::Statistics:
    return new MCPerformanceEngine<RNG, QuantLib::Statistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GaussianStatistics:
    return new MCPerformanceEngine<RNG, QuantLib::GaussianStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::GeneralStatistics:
    return new MCPerformanceEngine<RNG, QuantLib::GeneralStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::IncrementalStatistics:
    return new MCPerformanceEngine<RNG, QuantLib::IncrementalStatistics>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  };
  QL_FAIL("Unknown Statistics "<< stattrait);
}

PricingEngine* qlMCPerformanceEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  switch (rngtrait) {
  case hasquant::PseudoRandom:
    return qlMCPerformanceEngine1AuxStat<PseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::PoissonPseudoRandom:
    return qlMCPerformanceEngine1AuxStat<PoissonPseudoRandom>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::LowDiscrepancy:
    return qlMCPerformanceEngine1AuxStat<LowDiscrepancy>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  case hasquant::Ziggurat:
    return qlMCPerformanceEngine1AuxStat<Ziggurat>(stattrait, process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
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
