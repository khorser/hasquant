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
#include <ql/experimental/exoticoptions/mceverestengine.hpp>
#include <ql/pricingengines/forward/mcforwardeuropeanbsengine.hpp>
#include <ql/pricingengines/forward/mcforwardeuropeanhestonengine.hpp>
#include <ql/pricingengines/basket/mceuropeanbasketengine.hpp>
#include <ql/pricingengines/basket/mcamericanbasketengine.hpp>
#include <ql/math/statistics/incrementalstatistics.hpp>

namespace hasquant {
#include "qlEnumObjects.h"
}

using QuantLib::ext::shared_ptr;
#include "qlPricingEngineAux.h"
using namespace QuantLib;

// ---------------------------------------------------------------------------------------------
// Trait dispatchers.
//
// Each engine is selected by one or two runtime traits. Dispatchers call a generic lambda with
// an empty `Tag<T>` per axis, so each constructor is written once and recovers types through
// `typename decltype(r)::type`.
//
// Every dispatcher takes its return type as an explicit leading template argument
// (`dispatchRngStat<PricingEngine*>(...)`) rather than deducing it with a trailing
// `-> decltype(make(Tag<PseudoRandom>()))`. That is not a style choice. A trailing return type is
// an *unevaluated* operand, so the probe call it names is the first instantiation of the lambda
// for that tag -- and clang then emits the engine's constructor but never marks its vtable used,
// leaving `~Engine()` and its thunks undefined. It links as a missing
// `..MCPagodaEngine<..,Statistics>..D0Ev` at dlopen time, and *only* for the exact tag named in
// the probe (`Statistics` here), which is why it looks like a QuantLib packaging problem rather
// than a bug in this file. Keep the explicit `Ret`; do not "simplify" it back to decltype.
template <class T> struct Tag { using type = T; };

template <class Ret, class F>
Ret dispatchTree(int tree, F&& make) {
  switch (tree) {
  case hasquant::JarrowRudd: return make(Tag<JarrowRudd>());
  case hasquant::CoxRossRubinstein: return make(Tag<CoxRossRubinstein>());
  case hasquant::AdditiveEQPBinomialTree: return make(Tag<AdditiveEQPBinomialTree>());
  case hasquant::Trigeorgis: return make(Tag<Trigeorgis>());
  case hasquant::Tian: return make(Tag<Tian>());
  case hasquant::LeisenReimer: return make(Tag<LeisenReimer>());
  case hasquant::Joshi4: return make(Tag<Joshi4>());
  case hasquant::ExtendedJarrowRudd: return make(Tag<ExtendedJarrowRudd>());
  case hasquant::ExtendedCoxRossRubinstein: return make(Tag<ExtendedCoxRossRubinstein>());
  case hasquant::ExtendedAdditiveEQPBinomialTree: return make(Tag<ExtendedAdditiveEQPBinomialTree>());
  case hasquant::ExtendedTrigeorgis: return make(Tag<ExtendedTrigeorgis>());
  case hasquant::ExtendedTian: return make(Tag<ExtendedTian>());
  case hasquant::ExtendedLeisenReimer: return make(Tag<ExtendedLeisenReimer>());
  case hasquant::ExtendedJoshi4: return make(Tag<ExtendedJoshi4>());
  }
  QL_FAIL("Unknown Binomial Tree "<< tree);
}

template <class Ret, class F>
Ret dispatchRng(int rngtrait, F&& make) {
  switch (rngtrait) {
  case hasquant::PseudoRandom: return make(Tag<PseudoRandom>());
  case hasquant::PoissonPseudoRandom: return make(Tag<PoissonPseudoRandom>());
  case hasquant::LowDiscrepancy: return make(Tag<LowDiscrepancy>());
  case hasquant::Ziggurat: return make(Tag<Ziggurat>());
  }
  QL_FAIL("Unknown RNG "<< rngtrait);
}

template <class Ret, class F>
Ret dispatchStat(int stattrait, F&& make) {
  switch (stattrait) {
  case hasquant::Statistics: return make(Tag<QuantLib::Statistics>());
  case hasquant::GaussianStatistics: return make(Tag<QuantLib::GaussianStatistics>());
  case hasquant::GeneralStatistics: return make(Tag<QuantLib::GeneralStatistics>());
  case hasquant::IncrementalStatistics: return make(Tag<QuantLib::IncrementalStatistics>());
  }
  QL_FAIL("Unknown Statistics "<< stattrait);
}

// The RNG x Statistics product every MC engine here is templated over. This nesting is what the
// per-engine `template <class RNG> ...AuxStat` helpers used to do by hand, once each.
template <class Ret, class F>
Ret dispatchRngStat(int rngtrait, int stattrait, F&& make) {
  return dispatchRng<Ret>(rngtrait, [&](auto r) {
    return dispatchStat<Ret>(stattrait, [&](auto st) { return make(r, st); });
  });
}
// ---------------------------------------------------------------------------------------------

PricingEngine* qlBinomialVanillaEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  return dispatchTree<PricingEngine*>(tree, [&](auto t) {
    return new BinomialVanillaEngine<typename decltype(t)::type>(process, timeSteps);
  });
}

PricingEngine* qlBinomialConvertibleEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, const Handle<Quote>& cs, DividendSchedule d) {
  return dispatchTree<PricingEngine*>(tree, [&](auto t) {
    return new BinomialConvertibleEngine<typename decltype(t)::type>(process, timeSteps, cs, d);
  });
}

PricingEngine* qlBinomialBarrierEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned maxTimeSteps) {
  return dispatchTree<PricingEngine*>(tree, [&](auto t) {
    return new BinomialBarrierEngine<typename decltype(t)::type, DiscretizedBarrierOption>(process, timeSteps, maxTimeSteps);
  });
}

PricingEngine* qlBinomialDoubleBarrierEngineAux(int tree, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  return dispatchTree<PricingEngine*>(tree, [&](auto t) {
    return new BinomialDoubleBarrierEngine<typename decltype(t)::type>(process, timeSteps);
  });
}

PricingEngine* qlMCDoubleBarrierEngineAux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCDoubleBarrierEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCVarianceSwapEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCVarianceSwapEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCHestonHullWhiteEngine1Aux(int rngtrait, int stattrait, const shared_ptr<HybridHestonHullWhiteProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCHestonHullWhiteEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCAmericanEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, LsmBasisSystem::PolynomialType polynomType, unsigned nCalibrationSamples, ext::optional<bool> antitheticVariateCalibration, unsigned seedCalibration) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCAmericanEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, polynomType, nCalibrationSamples, antitheticVariateCalibration, seedCalibration);
  });
}

PricingEngine* qlMCBarrierEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCBarrierEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed);
  });
}

PricingEngine* qlMCDigitalEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCDigitalEngine<typename decltype(r)::type, typename decltype(st)::type>(x0, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCForwardEuropeanBSEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCForwardEuropeanBSEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCForwardEuropeanHestonEngine1Aux(int rngtrait, int stattrait, const shared_ptr<HestonProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, int controlVariate) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCForwardEuropeanHestonEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, controlVariate);
  });
}

PricingEngine* qlMCDiscreteArithmeticAPEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCDiscreteArithmeticAPEngine<typename decltype(r)::type, typename decltype(st)::type>(process, brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCDiscreteArithmeticASEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCDiscreteArithmeticASEngine<typename decltype(r)::type, typename decltype(st)::type>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCDiscreteGeometricAPEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCDiscreteGeometricAPEngine<typename decltype(r)::type, typename decltype(st)::type>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCEuropeanEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCEuropeanEngine<typename decltype(r)::type, typename decltype(st)::type>(process, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCEuropeanGJRGARCHEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GJRGARCHProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCEuropeanGJRGARCHEngine<typename decltype(r)::type, typename decltype(st)::type>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCEuropeanHestonEngine1Aux(int rngtrait, int stattrait, const shared_ptr<HestonProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCEuropeanHestonEngine<typename decltype(r)::type, typename decltype(st)::type>(x0, timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCHullWhiteCapFloorEngine1Aux(int rngtrait, int stattrait, shared_ptr<HullWhite> model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCHullWhiteCapFloorEngine<typename decltype(r)::type, typename decltype(st)::type>(model, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCHimalayaEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCHimalayaEngine<typename decltype(r)::type, typename decltype(st)::type>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCPagodaEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCPagodaEngine<typename decltype(r)::type, typename decltype(st)::type>(processes, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCEverestEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCEverestEngine<typename decltype(r)::type, typename decltype(st)::type>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCEuropeanBasketEngine1Aux(int rngtrait, int stattrait, const shared_ptr<StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCEuropeanBasketEngine<typename decltype(r)::type, typename decltype(st)::type>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

PricingEngine* qlMCPerformanceEngine1Aux(int rngtrait, int stattrait, const shared_ptr<GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed) {
  return dispatchRngStat<PricingEngine*>(rngtrait, stattrait, [&](auto r, auto st) {
    return new MCPerformanceEngine<typename decltype(r)::type, typename decltype(st)::type>(process, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed);
  });
}

// MCAmericanBasketEngine is templated <RNG> only upstream (its base MCLongstaffSchwartzEngine<BasketOption::engine,
// MultiVariate,RNG> never forwards a second template argument), so unlike every other engine in this file it has no
// S axis to expose -- not a gap, a real upstream limitation. See CLAUDE.md/PricingEngine.chs for the note.
PricingEngine* qlMCAmericanBasketEngine1Aux(int rngtrait, const shared_ptr<StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, LsmBasisSystem::PolynomialType polynomialType) {
  return dispatchRng<PricingEngine*>(rngtrait, [&](auto r) {
    return new MCAmericanBasketEngine<typename decltype(r)::type>(processes, timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, polynomialType);
  });
}

PricingEngine* qlFdBlackScholesVanillaEngineAux(const shared_ptr<GeneralizedBlackScholesProcess> process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, const FdmSchemeDesc &fdScheme, bool localVol, double illegalLocalVolOverwrite, int cashDividendModel) {return new FdBlackScholesVanillaEngine(process, tGrid, xGrid, dampingSteps, fdScheme, localVol, illegalLocalVolOverwrite, (FdBlackScholesVanillaEngine::CashDividendModel)cashDividendModel);}

class PolymorphicPathGenerator {
private:
  using PseudoRandomPathGenerator = MultiPathGenerator<PseudoRandom::rsg_type>;
  using SobolPathGenerator = MultiPathGenerator<LowDiscrepancy::rsg_type>;
  using PoissonPathGenerator = MultiPathGenerator<PoissonPseudoRandom::rsg_type>;
  using ZigguratPathGenerator = MultiPathGenerator<Ziggurat::rsg_type>;
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

// The gaussian sequence generator that PolymorphicPathGenerator's MultiPathGenerator merely
// consumes, lifted out so Haskell can drive its own SDE evolution with no callback in the hot
// loop -- shape 1 of CLAUDE.md's "coarsen the language-boundary crossing" bullet, the same trick
// lsmRegress plays on LongstaffSchwartzPathPricer. Same four-way RngTrait switch and the same
// SobolRsg::DirectionIntegers overload as PolymorphicPathGenerator above, deliberately: the two
// construct their rsg identically, so a Haskell-evolved path can be compared draw-for-draw
// against pathGenerator's own.
class PolymorphicGaussianRsg {
private:
  using PseudoRandomRsg = PseudoRandom::rsg_type;
  using SobolRsgType = LowDiscrepancy::rsg_type;
  using PoissonRsg = PoissonPseudoRandom::rsg_type;
  using ZigguratRsg = Ziggurat::rsg_type;
public:
  PolymorphicGaussianRsg(int rngtrait, unsigned dim, unsigned seed) {
    init(rngtrait, dim, seed, SobolRsg::Jaeckel);
  }
  PolymorphicGaussianRsg(SobolRsg::DirectionIntegers dir, unsigned dim, unsigned seed) {
    init(hasquant::LowDiscrepancy, dim, seed, dir);
  }
  const Sample<std::vector<Real> >& nextSequence() const {return _next();}
  const Sample<std::vector<Real> >& lastSequence() const {return _last();}
  unsigned dimension() const {return _dimension();}
private:
  void init(int rngtrait, unsigned dim, unsigned seed, SobolRsg::DirectionIntegers dir) {
    switch (rngtrait) {
    case hasquant::PseudoRandom:
      _pseudoRandom.reset(new PseudoRandomRsg(PseudoRandom::ursg_type(dim, PseudoRandom::urng_type(seed))));
      bind(_pseudoRandom.get());
      break;
    case hasquant::PoissonPseudoRandom:
      _poisson.reset(new PoissonRsg(PoissonPseudoRandom::ursg_type(dim, PoissonPseudoRandom::urng_type(seed))));
      bind(_poisson.get());
      break;
    case hasquant::LowDiscrepancy:
      _sobol.reset(new SobolRsgType(SobolRsg(dim, seed, dir)));
      bind(_sobol.get());
      break;
    case hasquant::Ziggurat:
      _ziggurat.reset(new ZigguratRsg(dim, ZigguratRng(seed)));
      bind(_ziggurat.get());
      break;
    default:
      QL_FAIL("Unknown RNG "<< rngtrait);
    }
  }
  template <class Rsg> void bind(Rsg* r) {
    _next = [r]() -> const Sample<std::vector<Real> >& {return r->nextSequence();};
    _last = [r]() -> const Sample<std::vector<Real> >& {return r->lastSequence();};
    _dimension = [r]() {return (unsigned)r->dimension();};
  }
  std::unique_ptr<PseudoRandomRsg> _pseudoRandom;
  std::unique_ptr<SobolRsgType> _sobol;
  std::unique_ptr<PoissonRsg> _poisson;
  std::unique_ptr<ZigguratRsg> _ziggurat;
  std::function<const Sample<std::vector<Real> >& ()> _next;
  std::function<const Sample<std::vector<Real> >& ()> _last;
  std::function<unsigned ()> _dimension;
};

PolymorphicGaussianRsg* qlGaussianRsgAux(int rngtrait, unsigned dimension, unsigned seed) {
  return new PolymorphicGaussianRsg(rngtrait, dimension, seed);
}
PolymorphicGaussianRsg* qlSobolGaussianRsgAux(SobolRsg::DirectionIntegers dir, unsigned dimension, unsigned seed) {
  return new PolymorphicGaussianRsg(dir, dimension, seed);
}
void qlFreePolymorphicGaussianRsgAux(PolymorphicGaussianRsg* g) {delete g;}
const Sample<std::vector<Real> >& qlGaussianRsgNextSequenceAux(PolymorphicGaussianRsg* g) {return g->nextSequence();}
const Sample<std::vector<Real> >& qlGaussianRsgLastSequenceAux(PolymorphicGaussianRsg* g) {return g->lastSequence();}
unsigned qlGaussianRsgDimensionAux(PolymorphicGaussianRsg* g) {return g->dimension();}

void qlFreePolymorphicPathGeneratorAux(PolymorphicPathGenerator *p) {delete p;}
const Sample<MultiPath>& qlPathGeneratorNextAux(PolymorphicPathGenerator *p) {return p->next();}
const Sample<MultiPath>& qlPathGeneratorAntitheticAux(PolymorphicPathGenerator *p) {return p->antithetic();}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
