#include <ql/experimental/callablebonds/blackcallablebondengine.hpp>
#include <ql/experimental/callablebonds/treecallablebondengine.hpp>
#include <ql/experimental/math/zigguratrng.hpp>
#include <ql/experimental/variancegamma/all.hpp>
#include <ql/experimental/barrieroption/vannavolgabarrierengine.hpp>
#include <ql/experimental/varianceoption/integralhestonvarianceoptionengine.hpp>
#include <ql/legacy/libormarketmodels/lfmswaptionengine.hpp>
#include <ql/methods/montecarlo/lsmbasissystem.hpp>
#include <ql/math/generallinearleastsquares.hpp>
#include <ql/pricingengines/asian/analytic_cont_geom_av_price.hpp>
#include <ql/pricingengines/asian/analytic_discr_geom_av_strike.hpp>
#include <ql/pricingengines/asian/mc_discr_arith_av_price.hpp>
#include <ql/pricingengines/asian/turnbullwakemanasianengine.hpp>
#include <ql/pricingengines/asian/fdblackscholesasianengine.hpp>
#include <ql/pricingengines/forward/forwardengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/experimental/forward/analytichestonforwardeuropeanengine.hpp>
#include <ql/experimental/barrieroption/vannavolgadoublebarrierengine.hpp>
#include <ql/pricingengines/barrier/analyticbarrierengine.hpp>
#include <ql/pricingengines/barrier/analytictwoassetbarrierengine.hpp>
#include <ql/pricingengines/barrier/analyticsoftbarrierengine.hpp>
#include <ql/pricingengines/quanto/quantoengine.hpp>
#include <ql/instruments/quantovanillaoption.hpp>
#include <ql/instruments/forwardvanillaoption.hpp>
#include <ql/pricingengines/forward/forwardperformanceengine.hpp>
#include <ql/pricingengines/exotic/analyticsimplechooserengine.hpp>
#include <ql/pricingengines/exotic/analytictwoassetcorrelationengine.hpp>
#include <ql/pricingengines/exotic/analyticwriterextensibleoptionengine.hpp>
#include <ql/pricingengines/barrier/analyticpartialtimebarrieroptionengine.hpp>
#include <ql/pricingengines/barrier/analyticbinarybarrierengine.hpp>
#include <ql/pricingengines/barrier/analyticdoublebarrierengine.hpp>
#include <ql/pricingengines/barrier/fdblackscholesbarrierengine.hpp>
#include <ql/pricingengines/barrier/fdhestonbarrierengine.hpp>
#include <ql/pricingengines/barrier/fdhestondoublebarrierengine.hpp>
#include <ql/pricingengines/basket/kirkengine.hpp>
#include <ql/pricingengines/basket/stulzengine.hpp>
#include <ql/pricingengines/bacheliercalculator.hpp>
#include <ql/pricingengines/blackdeltacalculator.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/pricingengines/futures/discountingperpetualfuturesengine.hpp>
#include <ql/pricingengines/bond/riskybondengine.hpp>
#include <ql/pricingengines/capfloor/analyticcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/bacheliercapfloorengine.hpp>
#include <ql/pricingengines/capfloor/blackcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/treecapfloorengine.hpp>
#include <ql/pricingengines/cliquet/analyticcliquetengine.hpp>
#include <ql/pricingengines/cliquet/analyticperformanceengine.hpp>
#include <ql/pricingengines/credit/integralcdsengine.hpp>
#include <ql/pricingengines/credit/isdacdsengine.hpp>
#include <ql/pricingengines/exotic/analyticcompoundoptionengine.hpp>
#include <ql/pricingengines/credit/midpointcdsengine.hpp>
#include <ql/pricingengines/forward/discountingfxforwardengine.hpp>
#include <ql/pricingengines/forward/replicatingvarianceswapengine.hpp>
#include <ql/pricingengines/greeks.hpp>
#include <ql/pricingengines/lookback/analyticcontinuousfixedlookback.hpp>
#include <ql/pricingengines/lookback/analyticcontinuousfloatinglookback.hpp>
#include <ql/pricingengines/swap/cvaswapengine.hpp>
#include <ql/pricingengines/swap/treeswapengine.hpp>
#include <ql/pricingengines/swap/discountingconstnotionalcrosscurrencyswapengine.hpp>
#include <ql/pricingengines/swaption/blackswaptionengine.hpp>
#include <ql/termstructures/volatility/sabr.hpp>
#include <ql/pricingengines/swaption/fdg2swaptionengine.hpp>
#include <ql/pricingengines/swaption/fdg2swaptionengine.hpp>
#include <ql/pricingengines/swaption/fdhullwhiteswaptionengine.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>
#include <ql/pricingengines/capfloor/gaussian1dcapfloorengine.hpp>
#include <ql/pricingengines/swaption/gaussian1dswaptionengine.hpp>
#include <ql/pricingengines/swaption/gaussian1dnonstandardswaptionengine.hpp>
#include <ql/pricingengines/swaption/gaussian1dfloatfloatswaptionengine.hpp>
#include <ql/pricingengines/swaption/gaussian1djamshidianswaptionengine.hpp>
#include <ql/models/shortrate/calibrationhelpers/swaptionhelper.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/pricingengines/swaption/treeswaptionengine.hpp>
#include <ql/pricingengines/vanilla/analyticbsmhullwhiteengine.hpp>
#include <ql/pricingengines/vanilla/analyticdigitalamericanengine.hpp>
#include <ql/pricingengines/vanilla/analyticdividendeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analyticgjrgarchengine.hpp>
#include <ql/pricingengines/vanilla/analytichestonhullwhiteengine.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/batesengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/integralengine.hpp>
#include <ql/pricingengines/vanilla/jumpdiffusionengine.hpp>
#include <ql/pricingengines/vanilla/juquadraticengine.hpp>
#include <ql/instruments/dividendschedule.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearopcomposite.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>
#include <ql/methods/finitedifferences/utilities/fdmquantohelper.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <ql/methods/finitedifferences/utilities/fdmaffinemodelswapinnervalue.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/meshers/predefined1dmesher.hpp>
#include <ql/methods/finitedifferences/meshers/uniform1dmesher.hpp>
#include <ql/methods/finitedifferences/meshers/concentrating1dmesher.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include <ql/methods/finitedifferences/meshers/fdmcev1dmesher.hpp>
#include <ql/methods/finitedifferences/meshers/exponentialjump1dmesher.hpp>
#include <ql/methods/finitedifferences/meshers/fdmsimpleprocess1dmesher.hpp>
#include <ql/methods/finitedifferences/meshers/fdmhestonvariancemesher.hpp>
#include <ql/experimental/finitedifferences/glued1dmesher.hpp>
#include <ql/pricingengines/vanilla/fdhestonvanillaengine.hpp>
#include <ql/pricingengines/vanilla/fdhestonhullwhitevanillaengine.hpp>
#include <ql/models/all.hpp>
#include <ql/legacy/libormarketmodels/all.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>
#include <ql/experimental/variancegamma/variancegammamodel.hpp>
#include <ql/processes/all.hpp>
#include <ql/experimental/processes/all.hpp>
#include <ql/experimental/variancegamma/all.hpp>
#include <ql/legacy/libormarketmodels/lfmprocess.hpp>

#include "qlaux.h"
#include "qlPricingEngineAux.h"
#include "qlPricingEngine.h"

namespace hasquant {
#include "qlEnumObjects.h"
}

using namespace QuantLib;

#ifdef QLTRACK_ALLOCATIONS
QL_TRACE_NAME(SamplePath)
#endif

namespace {
  shared_ptr<StochasticProcess1D::discretization> createDiscretization1D(int n) {
    switch (n) {
    case hasquant::EulerDiscretization:
      return shared_ptr<StochasticProcess1D::discretization>(new EulerDiscretization());
    case hasquant::EndEulerDiscretization:
      return shared_ptr<StochasticProcess1D::discretization>(new EndEulerDiscretization());
    default:
      QL_FAIL("Invalid discretization: " << n);
    }
  }

  // Wraps 3 Haskell-defined callbacks (produced by QuantLib.Internal.Type's withFdmApply/
  // withFdmApplyDirection/withFdmSolveSplitting, mirroring qlOptimize's HsCostFunction above) as a
  // QuantLib FdmLinearOpComposite driving FdmBackwardSolver::rollback -- see the "coarsen the
  // language-boundary crossing" bullet in CLAUDE.md and qlFdmRollback below. Only the 3 virtuals
  // DouglasScheme::step actually calls (size/setTime are plain state, not callbacks -- see below)
  // are implemented; apply_mixed/preconditioner QL_FAIL, so only schemes that never need them
  // (Douglas, Crank-Nicolson in 1D) work through this hook.
  using FdmApplyFun = void (*)(const double* in, unsigned n, double t1, double t2, double* out);
  using FdmApplyDirectionFun = void (*)(const double* in, unsigned n, unsigned direction, double t1, double t2, double* out);
  using FdmSolveSplittingFun = void (*)(const double* in, unsigned n, unsigned direction, double s, double t1, double t2, double* out);
  using FdmStepConditionFun = void (*)(const double* in, unsigned n, double t, double* out);

  class HsFdmLinearOpComposite : public FdmLinearOpComposite {
  public:
    HsFdmLinearOpComposite(Size size, FdmApplyFun applyFn, FdmApplyDirectionFun applyDirFn, FdmSolveSplittingFun solveSplitFn)
    : size_(size), applyFn_(applyFn), applyDirFn_(applyDirFn), solveSplitFn_(solveSplitFn), t1_(0.0), t2_(0.0) {}

    Size size() const override {return size_;}
    // Not a callback: DouglasScheme (and every scheme) calls setTime once per outer step, then
    // makes several apply*/solve_splitting calls against the *same* (t1,t2) -- so the C++
    // wrapper just stores them as mutable state and passes them as extra scalar args to every
    // apply*/solve_splitting callback below, keeping the Haskell callbacks themselves pure.
    void setTime(Time t1, Time t2) override {t1_ = t1; t2_ = t2;}

    Array apply(const Array& r) const override {
      Array out(r.size());
      applyFn_(r.begin(), (unsigned)r.size(), t1_, t2_, out.begin());
      return out;
    }
    Array apply_direction(Size direction, const Array& r) const override {
      Array out(r.size());
      applyDirFn_(r.begin(), (unsigned)r.size(), (unsigned)direction, t1_, t2_, out.begin());
      return out;
    }
    Array solve_splitting(Size direction, const Array& r, Real s) const override {
      Array out(r.size());
      solveSplitFn_(r.begin(), (unsigned)r.size(), (unsigned)direction, s, t1_, t2_, out.begin());
      return out;
    }
    Array apply_mixed(const Array&) const override {
      QL_FAIL("HsFdmLinearOpComposite::apply_mixed not implemented -- fdmRollback only supports schemes that never need mixed derivatives (Douglas, Crank-Nicolson in 1D)");
    }
    Array preconditioner(const Array&, Real) const override {
      QL_FAIL("HsFdmLinearOpComposite::preconditioner not implemented -- fdmRollback only supports schemes that never need it (Douglas, Crank-Nicolson in 1D)");
    }
  private:
    Size size_;
    FdmApplyFun applyFn_;
    FdmApplyDirectionFun applyDirFn_;
    FdmSolveSplittingFun solveSplitFn_;
    mutable Time t1_, t2_;
  };

  // Wraps one optional Haskell-defined step condition (withMaybeFdmStepCondition) as a
  // StepCondition<Array>. applyTo's caller-supplied `a' buffer is both the read source and the
  // write destination -- safe because the Haskell-side callback fully reads its input (peekArray)
  // before writing any of its output (pokeArray), so an in-place update never reads
  // already-overwritten data.
  class HsFdmStepCondition : public StepCondition<Array> {
  public:
    explicit HsFdmStepCondition(FdmStepConditionFun fn) : fn_(fn) {}
    void applyTo(Array& a, Time t) const override {
      fn_(a.begin(), (unsigned)a.size(), t, a.begin());
    }
  private:
    FdmStepConditionFun fn_;
  };
  // Genuine per-grid-node Haskell callback -- see QuantLib.Method's haddock ("coarsen the
  // language-boundary crossing" exception case) and CLAUDE.md's own note on this hook. Unlike
  // HsFdmLinearOpComposite/HsFdmStepCondition above, this cannot be coarsened to cross once per
  // outer iteration: FdmInnerValueCalculator::innerValue/avgInnerValue is called once per mesher
  // node (see qlFdmSolve below, mirroring Fdm1DimSolver's/FdmNdimSolver's own constructor loop),
  // and QuantLib's own step conditions (e.g. FdmAmericanStepCondition, not bound here) call it
  // again per node at every exercise date -- matching QuantLib-SWIG's own
  // FdmInnerValueCalculatorDelegate (SWIG/fdm.i), which accepts the same real per-call cost.
  using FdmInnerValueFun = double (*)(const double* loc, unsigned n, double t);

  class HsFdmInnerValueCalculator : public FdmInnerValueCalculator {
  public:
    HsFdmInnerValueCalculator(shared_ptr<FdmMesher> mesher, FdmInnerValueFun innerValueFn, FdmInnerValueFun avgInnerValueFn)
    : mesher_(std::move(mesher)), innerValueFn_(innerValueFn), avgInnerValueFn_(avgInnerValueFn) {}

    Real innerValue(const FdmLinearOpIterator& iter, Time t) override {return call(innerValueFn_, iter, t);}
    Real avgInnerValue(const FdmLinearOpIterator& iter, Time t) override {return call(avgInnerValueFn_, iter, t);}
  private:
    // Converts the node's grid-index iterator into its real-valued location per dimension --
    // the reason this whole feature needs a mesher, unlike qlFdmRollback's raw-index callbacks.
    Real call(FdmInnerValueFun fn, const FdmLinearOpIterator& iter, Time t) const {
      const Size n = mesher_->layout()->dim().size();
      std::vector<Real> loc(n);
      for (Size d = 0; d < n; ++d) loc[d] = mesher_->location(iter, d);
      return fn(loc.data(), (unsigned)n, t);
    }
    shared_ptr<FdmMesher> mesher_;
    FdmInnerValueFun innerValueFn_, avgInnerValueFn_;
  };

  // Builds the FdmLinearOpIterator for the node at `coords` (one index per dimension) from
  // mesher's own layout dim(), the reverse of what HsFdmInnerValueCalculator::call does above --
  // lets any bound FdmInnerValueCalculator (native or Haskell-callback-driven) be inspected
  // node-by-node without assembling a whole PDE solve.
  // extern "C++": this whole file sits inside qlPricingEngine.h's extern "C" block, but a free
  // function returning a non-POD C++ class by value (rather than only pointers, as every C-linkage
  // shim function here does) needs real C++ linkage or GHC's C++ frontend warns
  // (-Wreturn-type-c-linkage).
  FdmLinearOpIterator fdmIteratorAt(QlFdmMesher* mesher, unsigned ndims, unsigned* coords) {
    const shared_ptr<FdmLinearOpLayout>& layout = (*arg(mesher))->layout();
    std::vector<Size> dim = layout->dim();
    std::vector<Size> coordinates(coords, coords + ndims);
    Size index = 0, stride = 1;
    for (Size d = 0; d < dim.size(); ++d) {
      index += coordinates[d] * stride;
      stride *= dim[d];
    }
    return FdmLinearOpIterator(dim, coordinates, index);
  }
  // FdmAffineModelSwapInnerValue<ModelType> -- template isn't crossable into a C signature, so one
  // concrete shim per ModelType (G2/HullWhite), matching how those two models are already separate
  // plain pointer types (QlG2/QlHullWhite), not a shared family. exerciseDates (upstream's
  // std::map<Time, Date>) is marshalled as two parallel arrays, zipped back into the map here --
  // same array-pair convention as every other multi-field marshaller in this codebase.
  // extern "C++": templates can't have C linkage (this file sits inside qlPricingEngine.h's
  // extern "C" block) -- same reasoning as fdmIteratorAt above.
  template <class ModelType>
  QlFdmInnerValueCalculator* fdmAffineModelSwapInnerValue(
                                                          shared_ptr<ModelType>* disModel, shared_ptr<ModelType>* fwdModel, QlFixedVsFloatingSwap* swap,
                                                          unsigned exDatesLen, double* exerciseTimes, int* exerciseDates,
                                                          QlFdmMesher* mesher, unsigned direction, char **e) {
    try {
      std::map<Time, Date> t2d;
      for (unsigned i = 0; i < exDatesLen; ++i) t2d[exerciseTimes[i]] = Date(exerciseDates[i]);
      return ret(new QlFdmInnerValueCalculator(alloc(new FdmAffineModelSwapInnerValue<ModelType>(
                                                                                                 *arg(disModel), *arg(fwdModel), *arg(swap), t2d, *arg(mesher), direction))));
    } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}
  }
  // Flattens one drawn gaussian sequence (qlGaussianRsgNextSequence/LastSequence below) into the
  // caller-owned array + weight pair every other array-returning shim here uses.
  void copySequence(const Sample<std::vector<Real> >& s, unsigned *len, double **values, double *weight) {
    *len = (unsigned)s.value.size();
    *values = qlAllocateDoubles(*len);
    std::copy(s.value.begin(), s.value.end(), *values);
    *weight = s.weight;
  }
}

#ifdef QLTRACK_ALLOCATIONS
// These live in the anonymous namespace above, so -- unlike PolymorphicPathGenerator, which is
// forward-declared in qlaux.h precisely so its label can sit beside the rest -- they cannot be
// named there. Specialize here instead; without it ObjClassName's primary template falls back to
// typeid().name() and the trace carries a mangled name. All three are shared_ptr payloads: alloc()
// only, never freed, so alloc-summary.py --census lists them rather than flagging a leak.
QL_TRACE_NAME(HsFdmLinearOpComposite)
QL_TRACE_NAME(HsFdmStepCondition)
QL_TRACE_NAME(HsFdmInnerValueCalculator)
#endif

extern "C" {
QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new DiscountingBondEngine(*arg(ts), qlOptBool(f)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine *>(e, er);}}
QlPricingEngine* qlDiscountingPerpetualFuturesEngine(
    QlYieldTermStructure* domesticDiscountCurve, QlYieldTermStructure* foreignDiscountCurve,
    QlQuote* assetSpot, unsigned fundingTimesLen, double* fundingTimes,
    unsigned fundingRatesLen, double* fundingRates, unsigned interestRateDiffsLen,
    double* interestRateDiffs, int fundingInterpType, double maxT, char **e) {
  try {return ret(new QlPricingEngine(alloc(new DiscountingPerpetualFuturesEngine(
      *arg(domesticDiscountCurve), *arg(foreignDiscountCurve), *arg(assetSpot),
      std::vector<Time>(fundingTimes, fundingTimes + fundingTimesLen),
      std::vector<Rate>(fundingRates, fundingRates + fundingRatesLen),
      std::vector<Spread>(interestRateDiffs, interestRateDiffs + interestRateDiffsLen),
      (DiscountingPerpetualFuturesEngine::InterpolationType)fundingInterpType, maxT))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlRiskyBondEngine(QlDefaultProbabilityTermStructure* defaultTS, double recoveryRate, QlYieldTermStructure* yieldTS, char **e) {
  try {return ret(new QlPricingEngine(alloc(new RiskyBondEngine(Handle<DefaultProbabilityTermStructure>(*arg(defaultTS)), recoveryRate, *arg(yieldTS)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return ret(new QlPricingEngine(alloc(new DiscountingSwapEngine(*arg(discountCurve), qlOptBool(includeSettlementDateFlows), qlNullableDate(settlementDate), qlNullableDate(npvDate)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlDiscountingFxForwardEngine(QlYieldTermStructure* sourceCurrencyDiscountCurve, QlYieldTermStructure* targetCurrencyDiscountCurve, QlQuote* spotFx, char **e) {
  try {return ret(new QlPricingEngine(alloc(new DiscountingFxForwardEngine(*arg(sourceCurrencyDiscountCurve), *arg(targetCurrencyDiscountCurve), *arg(spotFx)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlDiscountingConstNotionalCrossCurrencySwapEngine(Currency* domesticCcy, QlYieldTermStructure* domesticCcyDiscountCurve, Currency* foreignCcy, QlYieldTermStructure* foreignCcyDiscountCurve, QlQuote* spotFX, int includeSettlementDateFlows, int settlementDate, int npvDate, int spotFXSettleDate, char **e) {
  try {return ret(new QlPricingEngine(alloc(new DiscountingConstNotionalCrossCurrencySwapEngine(*arg(domesticCcy), *arg(domesticCcyDiscountCurve), *arg(foreignCcy), *arg(foreignCcyDiscountCurve), *arg(spotFX), qlOptBool(includeSettlementDateFlows), qlNullableDate(settlementDate), qlNullableDate(npvDate), qlNullableDate(spotFXSettleDate)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlCounterpartyAdjSwapEngine(QlYieldTermStructure* discountCurve, QlQuote* blackVol, QlDefaultProbabilityTermStructure* ctptyDTS, double ctptyRecoveryRate, QlDefaultProbabilityTermStructure* invstDTS, double invstRecoveryRate, char **e) {
  try {return ret(new QlPricingEngine(alloc(new CounterpartyAdjSwapEngine(*arg(discountCurve), *arg(blackVol), Handle<DefaultProbabilityTermStructure>(*arg(ctptyDTS)), ctptyRecoveryRate, qlNullableHandle(arg(invstDTS)), invstRecoveryRate))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticBarrierEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticTwoAssetBarrierEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, QlQuote* rho, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticTwoAssetBarrierEngine(*arg(process1), *arg(process2), *arg(rho)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticSoftBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticSoftBarrierEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticSimpleChooserEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticSimpleChooserEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticTwoAssetCorrelationEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, QlQuote* correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticTwoAssetCorrelationEngine(*arg(process1), *arg(process2), *arg(correlation)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticWriterExtensibleOptionEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticWriterExtensibleOptionEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticPartialTimeBarrierOptionEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticPartialTimeBarrierOptionEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticBinaryBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticBinaryBarrierEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesBarrierEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdBlackScholesBarrierEngine(*arg(process), tGrid, xGrid, dampingSteps, *arg(fdScheme), localVol, illegalLocalVolOverwrite))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonBarrierEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonBarrierEngine(*arg(model), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonBarrierEngine1(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonBarrierEngine(*arg(model), qlVector(dividends, dividendsLen), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonDoubleBarrierEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonDoubleBarrierEngine(*arg(model), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBinomialBarrierEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned maxTimeSteps, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlBinomialBarrierEngineAux(tree, *arg(process), timeSteps, maxTimeSteps))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlVannaVolgaBarrierEngine(QlDeltaVolQuote* atmVol, QlDeltaVolQuote* vol25Put, QlDeltaVolQuote* vol25Call, QlQuote* spotFX, QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS, int adaptVanDelta, double bsPriceWithSmile, char **e) {
  try {return ret(new QlPricingEngine(alloc(new VannaVolgaBarrierEngine(Handle<DeltaVolQuote>(*arg(atmVol)), Handle<DeltaVolQuote>(*arg(vol25Put)), Handle<DeltaVolQuote>(*arg(vol25Call)), *arg(spotFX), *arg(domesticTS), *arg(foreignTS), adaptVanDelta, bsPriceWithSmile))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticDoubleBarrierEngine(QlGeneralizedBlackScholesProcess* process, int series, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticDoubleBarrierEngine(*arg(process), series))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlVannaVolgaDoubleBarrierEngine(QlDeltaVolQuote* atmVol, QlDeltaVolQuote* vol25Put, QlDeltaVolQuote* vol25Call, QlQuote* spotFX, QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS, int adaptVanDelta, double bsPriceWithSmile, int series, char **e) {
  try {return ret(new QlPricingEngine(alloc(new VannaVolgaDoubleBarrierEngine<AnalyticDoubleBarrierEngine>(Handle<DeltaVolQuote>(*arg(atmVol)), Handle<DeltaVolQuote>(*arg(vol25Put)), Handle<DeltaVolQuote>(*arg(vol25Call)), *arg(spotFX), *arg(domesticTS), *arg(foreignTS), adaptVanDelta, bsPriceWithSmile, series))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBinomialDoubleBarrierEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlBinomialDoubleBarrierEngineAux(tree, *arg(process), timeSteps))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDoubleBarrierEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDoubleBarrierEngineAux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticCliquetEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticCompoundOptionEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticCompoundOptionEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticContinuousFixedLookbackEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticContinuousFloatingLookbackEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticContinuousGeometricAveragePriceAsianEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticDigitalAmericanEngine(*arg(x0)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticDigitalAmericanKOEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticDigitalAmericanKOEngine(*arg(x0)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAveragePriceAsianEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAverageStrikeAsianEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTurnbullWakemanAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TurnbullWakemanAsianEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesAsianEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned aGrid, FdmSchemeDesc *fdScheme, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdBlackScholesAsianEngine(*arg(process), tGrid, xGrid, aGrid, *arg(fdScheme)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlForwardEuropeanEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new ForwardVanillaEngine<AnalyticEuropeanEngine>(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlForwardBaroneAdesiWhaleyEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new ForwardVanillaEngine<BaroneAdesiWhaleyApproximationEngine>(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlForwardBjerksundStenslandEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new ForwardVanillaEngine<BjerksundStenslandApproximationEngine>(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlForwardFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new ForwardVanillaEngine<FdBlackScholesVanillaEngine>(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlQuantoEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new QuantoEngine<VanillaOption, AnalyticEuropeanEngine>(*arg(process), *arg(foreignRiskFreeRate), *arg(exchangeRateVolatility), *arg(correlation)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlQuantoForwardEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new QuantoEngine<ForwardVanillaOption, ForwardVanillaEngine<AnalyticEuropeanEngine> >(*arg(process), *arg(foreignRiskFreeRate), *arg(exchangeRateVolatility), *arg(correlation)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlQuantoForwardPerformanceEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new QuantoEngine<ForwardVanillaOption, ForwardPerformanceVanillaEngine<AnalyticEuropeanEngine> >(*arg(process), *arg(foreignRiskFreeRate), *arg(exchangeRateVolatility), *arg(correlation)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlQuantoBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new QuantoEngine<BarrierOption, AnalyticBarrierEngine>(*arg(process), *arg(foreignRiskFreeRate), *arg(exchangeRateVolatility), *arg(correlation)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlQuantoDoubleBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new QuantoEngine<DoubleBarrierOption, AnalyticDoubleBarrierEngine>(*arg(process), *arg(foreignRiskFreeRate), *arg(exchangeRateVolatility), *arg(correlation)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticHestonForwardEuropeanEngine(QlHestonProcess* process, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticHestonForwardEuropeanEngine(*arg(process), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, unsigned dividendsLen, QlDividend** dividends, char **e) {
  try {DividendSchedule d = qlVector(dividends, dividendsLen);
    return ret(new QlPricingEngine(alloc(new AnalyticDividendEuropeanEngine(*arg(x0), d))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticEuropeanEngine(*arg(x0), qlNullableHandle(arg(discountCurve))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticPerformanceEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackCapFloorEngine(*arg(discountCurve), *arg(vol)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, double displacement, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackCapFloorEngine(*arg(discountCurve), *arg(vol), (*arg(dc)), displacement))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, double displacement, int model, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackSwaptionEngine(*arg(discountCurve), *arg(vol), (*arg(dc)), displacement, (BlackSwaptionEngine::CashAnnuityModel)model))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackSwaptionEngine(*arg(discountCurve), *arg(vol)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBachelierCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BachelierCapFloorEngine(*arg(discountCurve), *arg(vol)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBachelierCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BachelierCapFloorEngine(*arg(discountCurve), *arg(vol), (*arg(dc))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBachelierSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, int model, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BachelierSwaptionEngine(*arg(discountCurve), *arg(vol), (*arg(dc)), (BachelierSwaptionEngine::CashAnnuityModel)model))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBachelierSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BachelierSwaptionEngine(*arg(discountCurve), *arg(vol)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

void qlFreePricingEngine(QlPricingEngine *engine) {del(engine);}
void qlFreeBlackCalculator(QlBlackCalculator *o) {del(o);}
void qlFreeBlackScholesCalculator(QlBlackScholesCalculator *o) {del(o);}
QlBlackCalculator* qlBlackScholesCalculatorAsBlackCalculator(QlBlackScholesCalculator *o) {return ret(new QlBlackCalculator(*arg(o)));}

double qlBlackCalculatorAlpha(QlBlackCalculator* o, char **e) {try {return (*arg(o))->alpha();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorBeta(QlBlackCalculator* o, char **e) {try {return (*arg(o))->beta();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlBlackCalculator* qlBlackCalculator1(int optionType, double strike, double forward, double stdDev, double discount, char **e) {
  try {return ret(new QlBlackCalculator(alloc(new BlackCalculator((Option::Type)optionType, strike, forward, stdDev, discount))));
  } catch (std::exception& er) {return handleException<QlBlackCalculator*>(e, er);}}
QlBlackCalculator* qlBlackCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, char **e) {
  try {return ret(new QlBlackCalculator(alloc(new BlackCalculator(*arg(payoff), forward, stdDev, discount))));
  } catch (std::exception& er) {return handleException<QlBlackCalculator*>(e, er);}}
double qlBlackCalculatorDelta(QlBlackCalculator* o, double spot, char **e) {try {return (*arg(o))->delta(spot);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorDeltaForward(QlBlackCalculator* o, char **e) {try {return (*arg(o))->deltaForward();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorDividendRho(QlBlackCalculator* o, double maturity, char **e) {try {return (*arg(o))->dividendRho(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorElasticity(QlBlackCalculator* o, double spot, char **e) {try {return (*arg(o))->elasticity(spot);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorElasticityForward(QlBlackCalculator* o, char **e) {try {return (*arg(o))->elasticityForward();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorGamma(QlBlackCalculator* o, double spot, char **e) {try {return (*arg(o))->gamma(spot);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorGammaForward(QlBlackCalculator* o, char **e) {try {return (*arg(o))->gammaForward();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorItmAssetProbability(QlBlackCalculator* o, char **e) {try {return (*arg(o))->itmAssetProbability();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorItmCashProbability(QlBlackCalculator* o, char **e) {try {return (*arg(o))->itmCashProbability();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorRho(QlBlackCalculator* o, double maturity, char **e) {try {return (*arg(o))->rho(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorStrikeSensitivity(QlBlackCalculator* o, char **e) {try {return (*arg(o))->strikeSensitivity();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorStrikeGamma(QlBlackCalculator* o, char **e) {try {return (*arg(o))->strikeGamma();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorTheta(QlBlackCalculator* o, double spot, double maturity, char **e) {try {return (*arg(o))->theta(spot, maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorThetaPerDay(QlBlackCalculator* o, double spot, double maturity, char **e) {try {return (*arg(o))->thetaPerDay(spot, maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorValue(QlBlackCalculator* o, char **e) {try {return (*arg(o))->value();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorVanna(QlBlackCalculator* o, double spot, double maturity, char **e) {try {return (*arg(o))->vanna(spot, maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorVega(QlBlackCalculator* o, double maturity, char **e) {try {return (*arg(o))->vega(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalculatorVolga(QlBlackCalculator* o, double maturity, char **e) {try {return (*arg(o))->volga(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}

void qlFreeBachelierCalculator(QlBachelierCalculator *o) {del(o);}
double qlBachelierCalculatorAlpha(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->alpha();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorBeta(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->beta();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlBachelierCalculator* qlBachelierCalculator1(int optionType, double strike, double forward, double stdDev, double discount, char **e) {
  try {return ret(new QlBachelierCalculator(alloc(new BachelierCalculator((Option::Type)optionType, strike, forward, stdDev, discount))));
  } catch (std::exception& er) {return handleException<QlBachelierCalculator*>(e, er);}}
QlBachelierCalculator* qlBachelierCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, char **e) {
  try {return ret(new QlBachelierCalculator(alloc(new BachelierCalculator(*arg(payoff), forward, stdDev, discount))));
  } catch (std::exception& er) {return handleException<QlBachelierCalculator*>(e, er);}}
double qlBachelierCalculatorDelta(QlBachelierCalculator* o, double spot, char **e) {try {return (*arg(o))->delta(spot);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorDeltaForward(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->deltaForward();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorDividendRho(QlBachelierCalculator* o, double maturity, char **e) {try {return (*arg(o))->dividendRho(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorElasticity(QlBachelierCalculator* o, double spot, char **e) {try {return (*arg(o))->elasticity(spot);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorElasticityForward(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->elasticityForward();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorGamma(QlBachelierCalculator* o, double spot, char **e) {try {return (*arg(o))->gamma(spot);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorGammaForward(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->gammaForward();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorItmAssetProbability(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->itmAssetProbability();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorItmCashProbability(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->itmCashProbability();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorRho(QlBachelierCalculator* o, double maturity, char **e) {try {return (*arg(o))->rho(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorStrikeSensitivity(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->strikeSensitivity();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorStrikeGamma(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->strikeGamma();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorTheta(QlBachelierCalculator* o, double spot, double maturity, char **e) {try {return (*arg(o))->theta(spot, maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorThetaPerDay(QlBachelierCalculator* o, double spot, double maturity, char **e) {try {return (*arg(o))->thetaPerDay(spot, maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorValue(QlBachelierCalculator* o, char **e) {try {return (*arg(o))->value();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorVanna(QlBachelierCalculator* o, double maturity, char **e) {try {return (*arg(o))->vanna(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorVega(QlBachelierCalculator* o, double maturity, char **e) {try {return (*arg(o))->vega(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBachelierCalculatorVolga(QlBachelierCalculator* o, double maturity, char **e) {try {return (*arg(o))->volga(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}

QlBlackScholesCalculator* qlBlackScholesCalculator1(int optionType, double strike, double spot, double growth, double stdDev, double discount, char **e) {
  try {return ret(new QlBlackScholesCalculator(alloc(new BlackScholesCalculator((Option::Type)optionType, strike, spot, growth, stdDev, discount))));
  } catch (std::exception& er) {return handleException<QlBlackScholesCalculator*>(e, er);}}
QlBlackScholesCalculator* qlBlackScholesCalculator(QlStrikedTypePayoff* payoff, double spot, double growth, double stdDev, double discount, char **e) {
  try {return ret(new QlBlackScholesCalculator(alloc(new BlackScholesCalculator(*arg(payoff), spot, growth, stdDev, discount))));
  } catch (std::exception& er) {return handleException<QlBlackScholesCalculator*>(e, er);}}
double qlBlackScholesCalculatorDelta(QlBlackScholesCalculator* o, char **e) {try {return (*arg(o))->delta();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackScholesCalculatorElasticity(QlBlackScholesCalculator* o, char **e) {try {return (*arg(o))->elasticity();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackScholesCalculatorGamma(QlBlackScholesCalculator* o, char **e) {try {return (*arg(o))->gamma();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackScholesCalculatorTheta(QlBlackScholesCalculator* o, double maturity, char **e) {try {return (*arg(o))->theta(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackScholesCalculatorThetaPerDay(QlBlackScholesCalculator* o, double maturity, char **e) {try {return (*arg(o))->thetaPerDay(maturity);} catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeBlackDeltaCalculator(BlackDeltaCalculator *o) {del(o);}
BlackDeltaCalculator* qlBlackDeltaCalculator(int optionType, int deltaType, double spot, double dDiscount, double fDiscount, double stdDev, char **e) {
  try {return alloc(new BlackDeltaCalculator((Option::Type)optionType, (DeltaVolQuote::DeltaType)deltaType, spot, dDiscount, fDiscount, stdDev));
  } catch (std::exception& er) {return handleException<BlackDeltaCalculator*>(e, er);}}
double qlBlackDeltaCalculatorDeltaFromStrike(BlackDeltaCalculator* o, double strike, char **e) {try {return arg(o)->deltaFromStrike(strike);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackDeltaCalculatorStrikeFromDelta(BlackDeltaCalculator* o, double delta, char **e) {try {return arg(o)->strikeFromDelta(delta);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackDeltaCalculatorAtmStrike(BlackDeltaCalculator* o, int atmType, char **e) {try {return arg(o)->atmStrike((DeltaVolQuote::AtmType)atmType);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormula(*arg(payoff), forward, stdDev, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormula((Option::Type)optionType, strike, forward, stdDev, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaCashItmProbability1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double displacement, char **e) {
  try {return QuantLib::blackFormulaCashItmProbability(*arg(payoff), forward, stdDev, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaCashItmProbability(int optionType, double strike, double forward, double stdDev, double displacement, char **e) {
  try {return QuantLib::blackFormulaCashItmProbability((Option::Type)optionType, strike, forward, stdDev, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaImpliedStdDev1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e) {
  try {return QuantLib::blackFormulaImpliedStdDev(*arg(payoff), forward, blackPrice, discount, displacement, guess, accuracy, maxIterations);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaImpliedStdDev(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e) {
  try {return QuantLib::blackFormulaImpliedStdDev((Option::Type)optionType, strike, forward, blackPrice, discount, displacement, guess, accuracy, maxIterations);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaImpliedStdDevApproximation1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormulaImpliedStdDevApproximation(*arg(payoff), forward, blackPrice, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaImpliedStdDevApproximation(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormulaImpliedStdDevApproximation((Option::Type)optionType, strike, forward, blackPrice, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaStdDevDerivative1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormulaStdDevDerivative(*arg(payoff), forward, stdDev, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaStdDevDerivative(double strike, double forward, double stdDev, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormulaStdDevDerivative(strike, forward, stdDev, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackFormulaVolDerivative(double strike, double forward, double stdDev, double expiry, double discount, double displacement, char **e) {
  try {return QuantLib::blackFormulaVolDerivative(strike, forward, stdDev, expiry, discount, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBlackScholesTheta(QlGeneralizedBlackScholesProcess* x0, double value, double delta, double gamma, char **e) {
  try {return QuantLib::blackScholesTheta(*arg(x0), value, delta, gamma);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBachelierBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, char **e) {
  try {return QuantLib::bachelierBlackFormula(*arg(payoff), forward, stdDev, discount);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibBachelierBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, char **e) {
  try {return QuantLib::bachelierBlackFormula((Option::Type)optionType, strike, forward, stdDev, discount);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantLibDefaultThetaPerDay(double theta, char **e) {try {return QuantLib::defaultThetaPerDay(theta);} catch (std::exception& er) {return handleException<double>(e, er);}}

QlPricingEngine* qlAnalyticBSMHullWhiteEngine(double equityShortRateCorrelation, QlGeneralizedBlackScholesProcess* x1, QlHullWhite* x2, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticBSMHullWhiteEngine(equityShortRateCorrelation, *arg(x1), *arg(x2)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticCapFloorEngine(QlAffineModel* model, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticCapFloorEngine(*arg(model), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticGJRGARCHEngine(QlGJRGARCHModel* model, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticGJRGARCHEngine(*arg(model)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticHestonEngine(QlHestonModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticHestonEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticHestonHullWhiteEngine(QlHestonModel* hestonModel, QlHullWhite* hullWhiteModel, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticHestonHullWhiteEngine(*arg(hestonModel), *arg(hullWhiteModel), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesEngine(QlBatesModel* model, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFFTVanillaEngine(QlGeneralizedBlackScholesProcess* process, double logStrikeSpacing, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FFTVanillaEngine(*arg(process), logStrikeSpacing))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlG2SwaptionEngine(QlG2* model, double range, unsigned intervals, char **e) {
  try {return ret(new QlPricingEngine(alloc(new G2SwaptionEngine(*arg(model), range, intervals))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlJumpDiffusionEngine(QlMerton76Process* x0, double relativeAccuracy_, unsigned maxIterations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new JumpDiffusionEngine(*arg(x0), relativeAccuracy_, maxIterations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeCapFloorEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeCapFloorEngine(*arg(model), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeSwaptionEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeSwaptionEngine(*arg(x0), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeVanillaSwapEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeVanillaSwapEngine(*arg(x0), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlVarianceGammaEngine(QlVarianceGammaProcess* x0, double absoluteError, char **e) {
  try {return ret(new QlPricingEngine(alloc(new VarianceGammaEngine(*arg(x0), absoluteError))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticHestonEngine1(QlHestonModel* model, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticHestonEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlAnalyticHestonHullWhiteEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double relTolerance, unsigned maxEvaluations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new AnalyticHestonHullWhiteEngine(*arg(model), *arg(hullWhiteModel), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesEngine1(QlBatesModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBaroneAdesiWhaleyApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BaroneAdesiWhaleyApproximationEngine(*arg(x0)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesDetJumpEngine1(QlBatesDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesDetJumpEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesDetJumpEngine(QlBatesDetJumpModel* model, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesDetJumpEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesDoubleExpDetJumpEngine1(QlBatesDoubleExpDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesDoubleExpDetJumpEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesDoubleExpDetJumpEngine(QlBatesDoubleExpDetJumpModel* model, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesDoubleExpDetJumpEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesDoubleExpEngine1(QlBatesDoubleExpModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesDoubleExpEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBatesDoubleExpEngine(QlBatesDoubleExpModel* model, unsigned integrationOrder, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BatesDoubleExpEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBjerksundStenslandApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BjerksundStenslandApproximationEngine(*arg(x0)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlIntegralCdsEngine(int l, int u, QlDefaultProbabilityTermStructure* x1, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e) {
  try {return ret(new QlPricingEngine(alloc(new IntegralCdsEngine(Period(l, (TimeUnit)u), Handle<DefaultProbabilityTermStructure>(*arg(x1)), recoveryRate, *arg(discountCurve), qlOptBool(includeSettlementDateFlows)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlIntegralEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {return ret(new QlPricingEngine(alloc(new IntegralEngine(*arg(x0)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlJamshidianSwaptionEngine(QlOneFactorAffineModel* model, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new JamshidianSwaptionEngine(*arg(model), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlJuQuadraticApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {return ret(new QlPricingEngine(alloc(new JuQuadraticApproximationEngine(*arg(x0)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlKirkEngine(QlBlackProcess* process1, QlBlackProcess* process2, double correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new KirkEngine(*arg(process1), *arg(process2), correlation))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlIsdaCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int numericalFix, int accrualBias, int forwardsInCouponPeriod, char **e) {
  try {return ret(new QlPricingEngine(alloc(new IsdaCdsEngine(Handle<DefaultProbabilityTermStructure>(*arg(x0)), recoveryRate, *arg(discountCurve), qlOptBool(includeSettlementDateFlows),
      (IsdaCdsEngine::NumericalFix)numericalFix, (IsdaCdsEngine::AccrualBias)accrualBias, (IsdaCdsEngine::ForwardsInCouponPeriod)forwardsInCouponPeriod))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMidPointCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e) {
  try {return ret(new QlPricingEngine(alloc(new MidPointCdsEngine(Handle<DefaultProbabilityTermStructure>(*arg(x0)), recoveryRate, *arg(discountCurve), qlOptBool(includeSettlementDateFlows)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlReplicatingVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, double dk, unsigned callStrikesLen, double* callStrikes, unsigned putStrikesLen, double* putStrikes, char **e) {
  try {return ret(new QlPricingEngine(alloc(new ReplicatingVarianceSwapEngine(*arg(process), dk, std::vector<double>(callStrikes, callStrikes+callStrikesLen), std::vector<double>(putStrikes, putStrikes+putStrikesLen)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlStulzEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, char **e) {
  try {return ret(new QlPricingEngine(alloc(new StulzEngine(*arg(process1), *arg(process2), correlation))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlLfmSwaptionEngine(QlLiborForwardModel* model, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new LfmSwaptionEngine(*arg(model), *arg(discountCurve)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeCapFloorEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeCapFloorEngine(*arg(model), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeSwaptionEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeSwaptionEngine(*arg(x0), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeVanillaSwapEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeVanillaSwapEngine(*arg(x0), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdG2SwaptionEngine(QlG2* model, unsigned tGrid, unsigned xGrid, unsigned yGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdG2SwaptionEngine(*arg(model), tGrid, xGrid, yGrid, dampingSteps, invEps, *arg(schemeDesc)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHullWhiteSwaptionEngine(QlHullWhite* model, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHullWhiteSwaptionEngine(*arg(model), tGrid, xGrid, dampingSteps, invEps, *arg(schemeDesc)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCVarianceSwapEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCVarianceSwapEngine1Aux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCHestonHullWhiteEngine1(int rngtrait, int stattrait, QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCHestonHullWhiteEngine1Aux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCAmericanEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, int antitheticVariateCalibration, unsigned seedCalibration, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCAmericanEngine1Aux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, (LsmBasisSystem::PolynomialType)polynomType, nCalibrationSamples, qlOptBool(antitheticVariateCalibration), seedCalibration))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCBarrierEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCBarrierEngine1Aux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDigitalEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDigitalEngine1Aux(rngtrait, stattrait, *arg(x0), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCForwardEuropeanBSEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCForwardEuropeanBSEngine1Aux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDiscreteArithmeticAPEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDiscreteArithmeticAPEngine1Aux(rngtrait, stattrait, *arg(process), brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDiscreteArithmeticASEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDiscreteArithmeticASEngine1Aux(rngtrait, stattrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDiscreteGeometricAPEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDiscreteGeometricAPEngine1Aux(rngtrait, stattrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanEngine1Aux(rngtrait, stattrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanGJRGARCHEngine1(int rngtrait, int stattrait, QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanGJRGARCHEngine1Aux(rngtrait, stattrait, *arg(x0), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanHestonEngine1(int rngtrait, int stattrait, QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanHestonEngine1Aux(rngtrait, stattrait, *arg(x0), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlIntegralHestonVarianceOptionEngine(QlHestonProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new IntegralHestonVarianceOptionEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCHullWhiteCapFloorEngine1(int rngtrait, int stattrait, QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCHullWhiteCapFloorEngine1Aux(rngtrait, stattrait, *arg(model), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCHimalayaEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCHimalayaEngine1Aux(rngtrait, stattrait, *arg(processes), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCPagodaEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCPagodaEngine1Aux(rngtrait, stattrait, *arg(processes), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanBasketEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanBasketEngine1Aux(rngtrait, stattrait, *arg(processes), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCAmericanBasketEngine1(int rngtrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, int polynomialType, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCAmericanBasketEngine1Aux(rngtrait, *arg(processes), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, (LsmBasisSystem::PolynomialType)polynomialType))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCPerformanceEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCPerformanceEngine1Aux(rngtrait, stattrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBinomialVanillaEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlBinomialVanillaEngineAux(tree, *arg(process), timeSteps))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlFdBlackScholesVanillaEngineAux(*arg(process), tGrid, xGrid, dampingSteps, *arg(fdScheme), localVol, illegalLocalVolOverwrite, cashDividendModel))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesVanillaEngine1(QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdBlackScholesVanillaEngine(*arg(process), qlVector(dividends, dividendsLen), tGrid, xGrid, dampingSteps, *arg(fdScheme), localVol, illegalLocalVolOverwrite, (FdBlackScholesVanillaEngine::CashDividendModel)cashDividendModel))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesVanillaEngine2(QlGeneralizedBlackScholesProcess* process, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdBlackScholesVanillaEngine(*arg(process), quantoHelper ? *arg(quantoHelper) : shared_ptr<FdmQuantoHelper>(), tGrid, xGrid, dampingSteps, *arg(fdScheme), localVol, illegalLocalVolOverwrite, (FdBlackScholesVanillaEngine::CashDividendModel)cashDividendModel))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesVanillaEngine3(QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdBlackScholesVanillaEngine(*arg(process), qlVector(dividends, dividendsLen), quantoHelper ? *arg(quantoHelper) : shared_ptr<FdmQuantoHelper>(), tGrid, xGrid, dampingSteps, *arg(fdScheme), localVol, illegalLocalVolOverwrite, (FdBlackScholesVanillaEngine::CashDividendModel)cashDividendModel))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonVanillaEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonVanillaEngine(*arg(model), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonVanillaEngine1(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonVanillaEngine(*arg(model), qlVector(dividends, dividendsLen), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonVanillaEngine2(QlHestonModel* model, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonVanillaEngine(*arg(model), quantoHelper ? *arg(quantoHelper) : shared_ptr<FdmQuantoHelper>(), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonVanillaEngine3(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonVanillaEngine(*arg(model), qlVector(dividends, dividendsLen), quantoHelper ? *arg(quantoHelper) : shared_ptr<FdmQuantoHelper>(), tGrid, xGrid, vGrid, dampingSteps, *arg(fdScheme), leverageFct ? *arg(leverageFct) : shared_ptr<LocalVolTermStructure>(), mixingFactor))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonHullWhiteVanillaEngine(QlHestonModel* model, QlHullWhiteProcess* hwProcess, double corrEquityShortRate, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned rGrid, unsigned dampingSteps, int controlVariate, FdmSchemeDesc *fdScheme, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonHullWhiteVanillaEngine(*arg(model), *arg(hwProcess), corrEquityShortRate, tGrid, xGrid, vGrid, rGrid, dampingSteps, controlVariate, *arg(fdScheme)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdHestonHullWhiteVanillaEngine1(QlHestonModel* model, QlHullWhiteProcess* hwProcess, unsigned dividendsLen, QlDividend** dividends, double corrEquityShortRate, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned rGrid, unsigned dampingSteps, int controlVariate, FdmSchemeDesc *fdScheme, char **e) {
  try {return ret(new QlPricingEngine(alloc(new FdHestonHullWhiteVanillaEngine(*arg(model), *arg(hwProcess), qlVector(dividends, dividendsLen), corrEquityShortRate, tGrid, xGrid, vGrid, rGrid, dampingSteps, controlVariate, *arg(fdScheme)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBinomialConvertibleEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, QlQuote* creditSpread, unsigned dividendsLen, QlDividend** dividends, char **e) {
  try {const Handle<Quote>& cs = *arg(creditSpread); DividendSchedule d = qlVector(dividends, dividendsLen);
    return ret(new QlPricingEngine(alloc(qlBinomialConvertibleEngineAux(tree, *arg(process), timeSteps, cs, d))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackCallableFixedRateBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackCallableFixedRateBondEngine(Handle<CallableBondVolatilityStructure>(*arg(yieldVolStructure)), *arg(discountCurve)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackCallableFixedRateBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackCallableFixedRateBondEngine(*arg(fwdYieldVol), *arg(discountCurve)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackCallableZeroCouponBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackCallableZeroCouponBondEngine(Handle<CallableBondVolatilityStructure>(*arg(yieldVolStructure)), *arg(discountCurve)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBlackCallableZeroCouponBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new BlackCallableZeroCouponBondEngine(*arg(fwdYieldVol), *arg(discountCurve)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeCallableFixedRateBondEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeCallableFixedRateBondEngine(*arg(x0), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeCallableFixedRateBondEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeCallableFixedRateBondEngine(*arg(x0), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeCallableZeroCouponBondEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeCallableZeroCouponBondEngine(*arg(model), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlTreeCallableZeroCouponBondEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlPricingEngine(alloc(new TreeCallableZeroCouponBondEngine(*arg(model), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

FdmSchemeDesc* qlFdmSchemeDesc(int type, double theta, double mu, char **e) {try {return alloc(new FdmSchemeDesc((FdmSchemeDesc::FdmSchemeType)type, theta, mu));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescCraigSneyd(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::CraigSneyd()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescDouglas(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::Douglas()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescExplicitEuler(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::ExplicitEuler()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescHundsdorfer(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::Hundsdorfer()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescImplicitEuler(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::ImplicitEuler()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescModifiedCraigSneyd(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::ModifiedCraigSneyd()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
FdmSchemeDesc* qlFdmSchemeDescModifiedHundsdorfer(char **e) {try {return alloc(new FdmSchemeDesc(FdmSchemeDesc::ModifiedHundsdorfer()));} catch (std::exception& er) {return handleException<FdmSchemeDesc*>(e, er);}}
void qlFreeFdmSchemeDesc(FdmSchemeDesc *o) {del(o);}

// Drives FdmBackwardSolver::rollback with a Haskell-defined operator/step condition instead of a
// bound mesher+FdmInnerValueCalculator -- see QuantLib.Method.fdmRollback's haddock and the
// HsFdmLinearOpComposite/HsFdmStepCondition comments above. bcSet is always the empty
// FdmBoundaryConditionSet(); boundary conditions are not bound. A null stepCondFn means no step
// condition at all (matches FdmBackwardSolver's own null-condition default, an empty
// FdmStepConditionComposite({}, {})).
void qlFdmRollback(unsigned opSize, FdmApplyFun applyFn, FdmApplyDirectionFun applyDirFn, FdmSolveSplittingFun solveSplitFn,
                    FdmStepConditionFun stepCondFn, unsigned stoppingTimesLen, double* stoppingTimes,
                    FdmSchemeDesc* schemeDesc,
                    unsigned gridLen, double* grid,
                    double from, double to, unsigned steps, unsigned dampingSteps,
                    unsigned* outLen, double** outValues, char **e) {
  try {
    ext::shared_ptr<FdmLinearOpComposite> map(alloc(new HsFdmLinearOpComposite(opSize, applyFn, applyDirFn, solveSplitFn)));
    FdmStepConditionComposite::Conditions conditions;
    std::list<std::vector<Time> > stoppingTimesList;
    if (stepCondFn) {
      conditions.push_back(ext::shared_ptr<StepCondition<Array> >(alloc(new HsFdmStepCondition(stepCondFn))));
      stoppingTimesList.push_back(std::vector<Time>(stoppingTimes, stoppingTimes + stoppingTimesLen));
    }
    ext::shared_ptr<FdmStepConditionComposite> condition(alloc(new FdmStepConditionComposite(stoppingTimesList, conditions)));
    FdmBackwardSolver solver(map, FdmBoundaryConditionSet(), condition, *arg(schemeDesc));
    Array a(grid, grid + gridLen);
    solver.rollback(a, from, to, steps, dampingSteps);
    *outLen = (unsigned)a.size();
    *outValues = qlAllocateDoubles(*outLen);
    std::copy(a.begin(), a.end(), *outValues);
  } catch (std::exception& er) {*e = tracedup(er.what());}}

void qlFreeFdm1dMesher(QlFdm1dMesher *o) {del(o);}
void qlFreeFdmMesher(QlFdmMesher *o) {del(o);}

QlFdm1dMesher* qlPredefined1dMesher(unsigned len, double* points, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new Predefined1dMesher(std::vector<Real>(points, points + len)))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlUniform1dMesher(double start, double end, unsigned size, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new Uniform1dMesher(start, end, size))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlConcentrating1dMesher(double start, double end, unsigned size, double cPointLoc, double cPointDensity, int requireCPoint, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new Concentrating1dMesher(start, end, size, std::pair<Real, Real>(cPointLoc, cPointDensity), requireCPoint))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlConcentrating1dMesherMulti(double start, double end, unsigned size, unsigned cPointsLen, double* cPointLoc, double* cPointDensity, int* cPointRequire, double tol, char **e) {
  try {std::vector<std::tuple<Real, Real, bool> > cPoints;
    cPoints.reserve(cPointsLen);
    for (unsigned i = 0; i < cPointsLen; ++i)
      cPoints.push_back(std::make_tuple(cPointLoc[i], cPointDensity[i], cPointRequire[i] != 0));
    return ret(new QlFdm1dMesher(alloc(new Concentrating1dMesher(start, end, size, cPoints, tol))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlGluedMesher(QlFdm1dMesher* left, QlFdm1dMesher* right, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new Glued1dMesher(**arg(left), **arg(right)))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlFdmBlackScholesMesher(unsigned size, QlGeneralizedBlackScholesProcess* process, double maturity, double strike,
    double xMinConstraint, double xMaxConstraint, double eps, double scaleFactor, double cPointLoc, double cPointDensity,
    unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* fdmQuantoHelper, double spotAdjustment, char **e) {
  try {DividendSchedule d = qlVector(dividends, dividendsLen);
    return ret(new QlFdm1dMesher(alloc(new FdmBlackScholesMesher(size, *arg(process), maturity, strike,
      xMinConstraint, xMaxConstraint, eps, scaleFactor, std::pair<Real, Real>(cPointLoc, cPointDensity), d,
      fdmQuantoHelper ? *arg(fdmQuantoHelper) : shared_ptr<FdmQuantoHelper>(), spotAdjustment))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlFdmCev1dMesher(unsigned size, double f0, double alpha, double beta, double maturity, double eps, double scaleFactor, double cPointLoc, double cPointDensity, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new FdmCEV1dMesher(size, f0, alpha, beta, maturity, eps, scaleFactor, std::pair<Real, Real>(cPointLoc, cPointDensity)))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlExponentialJump1dMesher(unsigned steps, double beta, double jumpIntensity, double eta, double eps, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new ExponentialJump1dMesher(steps, beta, jumpIntensity, eta, eps))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlFdmSimpleProcess1dMesher(unsigned size, QlStochasticProcess1D* process, double maturity, unsigned tAvgSteps, double epsilon, double mandatoryPoint, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new FdmSimpleProcess1dMesher(size, *arg(process), maturity, tAvgSteps, epsilon, mandatoryPoint))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlFdmHestonVarianceMesher(unsigned size, QlHestonProcess* process, double maturity, unsigned tAvgSteps, double epsilon, double mixingFactor, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new FdmHestonVarianceMesher(size, *arg(process), maturity, tAvgSteps, epsilon, mixingFactor))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdm1dMesher* qlFdmHestonLocalVolatilityVarianceMesher(unsigned size, QlHestonProcess* process, QlLocalVolTermStructure* leverageFct, double maturity, unsigned tAvgSteps, double epsilon, double mixingFactor, char **e) {
  try {return ret(new QlFdm1dMesher(alloc(new FdmHestonLocalVolatilityVarianceMesher(size, *arg(process), *arg(leverageFct), maturity, tAvgSteps, epsilon, mixingFactor))));
  } catch (std::exception& er) {return handleException<QlFdm1dMesher*>(e, er);}}
QlFdmMesher* qlFdmMesherComposite(unsigned meshersLen, QlFdm1dMesher** meshers, char **e) {
  try {return ret(new QlFdmMesher(alloc(new FdmMesherComposite(qlVector(meshers, meshersLen)))));
  } catch (std::exception& er) {return handleException<QlFdmMesher*>(e, er);}}
void qlFdmMesherLocations(QlFdmMesher* mesher, unsigned direction, unsigned* outLen, double** outValues, char **e) {
  try {Array locs = (*arg(mesher))->locations(direction);
    *outLen = (unsigned)locs.size();
    *outValues = qlAllocateDoubles(*outLen);
    std::copy(locs.begin(), locs.end(), *outValues);
  } catch (std::exception& er) {*e = tracedup(er.what());}}

void qlFreeFdmInnerValueCalculator(QlFdmInnerValueCalculator *o) {del(o);}

// Heap-allocates the same HsFdmInnerValueCalculator qlFdmSolve used to build stack-locally,
// so a Haskell-defined calculator can be surfaced as a real QlFdmInnerValueCalculator and reused
// wherever a native one (FdmZeroInnerValue etc., bound alongside this) can be used -- see
// QuantLib.Method.fdmInnerValueCalculator's haddock.
QlFdmInnerValueCalculator* qlFdmInnerValueCalculatorFromFunctions(QlFdmMesher* mesher, FdmInnerValueFun innerValueFn, FdmInnerValueFun avgInnerValueFn, char **e) {
  try {return ret(new QlFdmInnerValueCalculator(alloc(new HsFdmInnerValueCalculator(*arg(mesher), innerValueFn, avgInnerValueFn))));
  } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}}

double qlFdmInnerValueCalculatorEval(QlFdmInnerValueCalculator* calc, QlFdmMesher* mesher, unsigned ndims, unsigned* coords, double t, char **e) {
  try {return (*arg(calc))->innerValue(fdmIteratorAt(mesher, ndims, coords), t);
  } catch (std::exception& er) {*e = tracedup(er.what()); return 0.0;}}
double qlFdmInnerValueCalculatorAvgEval(QlFdmInnerValueCalculator* calc, QlFdmMesher* mesher, unsigned ndims, unsigned* coords, double t, char **e) {
  try {return (*arg(calc))->avgInnerValue(fdmIteratorAt(mesher, ndims, coords), t);
  } catch (std::exception& er) {*e = tracedup(er.what()); return 0.0;}}

// Sibling of qlFdmRollback that derives its own initial grid from a mesher + a (native or
// Haskell-callback-driven) FdmInnerValueCalculator (calc->avgInnerValue(iter, maturity) per node)
// instead of taking a precomputed array -- everything else (operator/step-condition/scheme/
// rollback) is identical, reusing HsFdmLinearOpComposite/HsFdmStepCondition verbatim.
// Fdm1DimSolver/FdmNdimSolver themselves (their own LazyObject caching and spline interpolation)
// are not bound; a caller wanting interpolation combines this function's result with
// qlFdmMesherLocations itself.
void qlFdmSolve(QlFdmMesher* mesher, QlFdmInnerValueCalculator* calculator,
                unsigned opSize, FdmApplyFun applyFn, FdmApplyDirectionFun applyDirFn, FdmSolveSplittingFun solveSplitFn,
                FdmStepConditionFun stepCondFn, unsigned stoppingTimesLen, double* stoppingTimes,
                FdmSchemeDesc* schemeDesc,
                double maturity, double to, unsigned steps, unsigned dampingSteps,
                unsigned* outLen, double** outValues, char **e) {
  try {
    shared_ptr<FdmMesher> m = *arg(mesher);
    shared_ptr<FdmInnerValueCalculator> calc = *arg(calculator);
    Array a(m->layout()->size());
    for (const auto& iter : *m->layout())
      a[iter.index()] = calc->avgInnerValue(iter, maturity);

    ext::shared_ptr<FdmLinearOpComposite> map(alloc(new HsFdmLinearOpComposite(opSize, applyFn, applyDirFn, solveSplitFn)));
    FdmStepConditionComposite::Conditions conditions;
    std::list<std::vector<Time> > stoppingTimesList;
    if (stepCondFn) {
      conditions.push_back(ext::shared_ptr<StepCondition<Array> >(alloc(new HsFdmStepCondition(stepCondFn))));
      stoppingTimesList.push_back(std::vector<Time>(stoppingTimes, stoppingTimes + stoppingTimesLen));
    }
    ext::shared_ptr<FdmStepConditionComposite> condition(alloc(new FdmStepConditionComposite(stoppingTimesList, conditions)));
    FdmBackwardSolver solver(map, FdmBoundaryConditionSet(), condition, *arg(schemeDesc));
    solver.rollback(a, maturity, to, steps, dampingSteps);
    *outLen = (unsigned)a.size();
    *outValues = qlAllocateDoubles(*outLen);
    std::copy(a.begin(), a.end(), *outValues);
  } catch (std::exception& er) {*e = tracedup(er.what());}}

// Native (non-Haskell-callback) FdmInnerValueCalculator subclasses -- QuantLib's own concrete
// implementations, bound as a peer to qlFdmInnerValueCalculatorFromFunctions above so common cases
// (a vanilla/basket payoff on the grid) don't pay any per-node FFI cost. All upcast directly to
// QlFdmInnerValueCalculator at construction, like every other pricing-engine-family constructor
// here -- none of these classes have their own public methods beyond the ctor, so no dedicated
// leaf type is needed (see CLAUDE.md's "don't mirror the hierarchy 1:1").
QlFdmInnerValueCalculator* qlFdmZeroInnerValue(char **e) {
  try {return ret(new QlFdmInnerValueCalculator(alloc(new FdmZeroInnerValue())));
  } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}}

QlFdmInnerValueCalculator* qlFdmCellAveragingInnerValue(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, char **e) {
  try {return ret(new QlFdmInnerValueCalculator(alloc(new FdmCellAveragingInnerValue(*arg(payoff), *arg(mesher), direction))));
  } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}}

// gridMapping is a genuine per-node Haskell callback (invoked from inside avgInnerValueCalc's
// Simpson integration and from every innerValue call), unlike the identity-mapping ctor above --
// see QuantLib.Method.withCustomCellAveragingInnerValue's haddock for why its Haskell wrapper must
// be continuation-style, same reasoning as qlFdmInnerValueCalculatorFromFunctions/
// withCustomFdmInnerValueCalculator.
using FdmGridMappingFun = double (*)(double x);
QlFdmInnerValueCalculator* qlFdmCellAveragingInnerValueMapped(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, FdmGridMappingFun mappingFn, char **e) {
  try {return ret(new QlFdmInnerValueCalculator(alloc(new FdmCellAveragingInnerValue(*arg(payoff), *arg(mesher), direction,
    [mappingFn](Real x) -> Real { return mappingFn(x); }))));
  } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}}

QlFdmInnerValueCalculator* qlFdmLogInnerValue(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, char **e) {
  try {return ret(new QlFdmInnerValueCalculator(alloc(new FdmLogInnerValue(*arg(payoff), *arg(mesher), direction))));
  } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}}

QlFdmInnerValueCalculator* qlFdmLogBasketInnerValue(QlBasketPayoff* payoff, QlFdmMesher* mesher, char **e) {
  try {return ret(new QlFdmInnerValueCalculator(alloc(new FdmLogBasketInnerValue(*arg(payoff), *arg(mesher)))));
  } catch (std::exception& er) {return handleException<QlFdmInnerValueCalculator*>(e, er);}}

QlFdmInnerValueCalculator* qlFdmAffineG2ModelSwapInnerValue(QlG2* disModel, QlG2* fwdModel, QlFixedVsFloatingSwap* swap,
    unsigned exDatesLen, double* exerciseTimes, int* exerciseDates, QlFdmMesher* mesher, unsigned direction, char **e) {
  return fdmAffineModelSwapInnerValue<G2>(disModel, fwdModel, swap, exDatesLen, exerciseTimes, exerciseDates, mesher, direction, e);
}
QlFdmInnerValueCalculator* qlFdmAffineHullWhiteModelSwapInnerValue(QlHullWhite* disModel, QlHullWhite* fwdModel, QlFixedVsFloatingSwap* swap,
    unsigned exDatesLen, double* exerciseTimes, int* exerciseDates, QlFdmMesher* mesher, unsigned direction, char **e) {
  return fdmAffineModelSwapInnerValue<HullWhite>(disModel, fwdModel, swap, exDatesLen, exerciseTimes, exerciseDates, mesher, direction, e);
}

void qlFreeFdmQuantoHelper(QlFdmQuantoHelper *o) {del(o);}
QlFdmQuantoHelper* qlFdmQuantoHelper(QlYieldTermStructure* rTS, QlYieldTermStructure* fTS, QlBlackVolTermStructure* fxVolTS, double equityFxCorrelation, double exchRateATMlevel, char **e) {
  try {shared_ptr<YieldTermStructure> r = (*arg(rTS)).currentLink(), f = (*arg(fTS)).currentLink();
    shared_ptr<BlackVolTermStructure> fxVol = (*arg(fxVolTS)).currentLink();
    return ret(new QlFdmQuantoHelper(alloc(new FdmQuantoHelper(r, f, fxVol, equityFxCorrelation, exchRateATMlevel))));
  } catch (std::exception& er) {return handleException<QlFdmQuantoHelper*>(e, er);}}
double qlFdmQuantoHelperQuantoAdjustment(QlFdmQuantoHelper* helper, double equityVol, double t1, double t2, char **e) {
  try {return (*arg(helper))->quantoAdjustment(equityVol, t1, t2);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeGJRGARCHModel(QlGJRGARCHModel *o) {del(o);}
void qlFreeHestonModel(QlHestonModel *o) {del(o);}
void qlFreeBatesModel(QlBatesModel *o) {del(o);}
void qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o) {del(o);}
void qlFreeShortRateModel(QlShortRateModel *o) {del(o);}
void qlFreeAffineModel(QlAffineModel *o) {del(o);}
void qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o) {del(o);}
double qlOneFactorAffineModelDiscountBond(QlOneFactorAffineModel* o, double now, double maturity, double rate, char **e) {
  try {return (*arg(o))->discountBond(now, maturity, rate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlHullWhiteConvexityBias(double futurePrice, double t, double T, double sigma, double a, char **e) {
  try {return HullWhite::convexityBias(futurePrice, t, T, sigma, a);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlAffineModel* qlHullWhiteAsAffineModel(QlHullWhite *o) {return ret(new QlAffineModel(*arg(o)));}
QlAffineModel* qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o) {return ret(new QlAffineModel(*arg(o)));}
void qlFreeLiborForwardModel(QlLiborForwardModel *o) {del(o);}
QlAffineModel* qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o) {return ret(new QlAffineModel(*arg(o)));}
void qlFreeHullWhite(QlHullWhite *o) {del(o);}
QlOneFactorAffineModel* qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o) {return ret(new QlOneFactorAffineModel(*arg(o)));}
void qlFreeCalibratedModel(QlCalibratedModel *o) {del(o);}

QlBatesModel* qlBatesModel(QlBatesProcess* process, char **e) {try {return ret(new QlBatesModel(alloc(new BatesModel(*arg(process)))));} catch (std::exception& er) {return handleException<QlBatesModel*>(e, er);}}
QlShortRateModel* qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, char **e) {
  try {return ret(new QlShortRateModel(alloc(new BlackKarasinski(*arg(termStructure), a, sigma))));
  } catch (std::exception& er) {return handleException<QlShortRateModel*>(e, er);}}
QlOneFactorAffineModel* qlCoxIngersollRoss(double r0, double theta, double k, double sigma, int withFellerConstraint, char **e) {
  try {return ret(new QlOneFactorAffineModel(alloc(new CoxIngersollRoss(r0, theta, k, sigma, withFellerConstraint))));
  } catch (std::exception& er) {return handleException<QlOneFactorAffineModel*>(e, er);}}
QlOneFactorAffineModel* qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, int withFellerConstraint, char **e) {
  try {return ret(new QlOneFactorAffineModel(alloc(new ExtendedCoxIngersollRoss(*arg(termStructure), theta, k, sigma, x0, withFellerConstraint))));
  } catch (std::exception& er) {return handleException<QlOneFactorAffineModel*>(e, er);}}
QlG2* qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, char **e) {
  try {return ret(new QlG2(alloc(new G2(*arg(termStructure), a, sigma, b, eta, rho))));
  } catch (std::exception& er) {return handleException<QlG2*>(e, er);}}
QlShortRateModel* qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, char **e) {
  try {return ret(new QlShortRateModel(alloc(new GeneralizedHullWhite(*arg(yieldtermStructure), qlDateVector(speedstructure, speedstructureLen), qlDateVector(volstructure, volstructureLen), std::vector<double>(speed, speed+speedLen), std::vector<double>(vol, vol+volLen)))));
  } catch (std::exception& er) {return handleException<QlShortRateModel*>(e, er);}}
QlGJRGARCHModel* qlGJRGARCHModel(QlGJRGARCHProcess* process, char **e) {try {return ret(new QlGJRGARCHModel(alloc(new GJRGARCHModel(*arg(process)))));} catch (std::exception& er) {return handleException<QlGJRGARCHModel*>(e, er);}}
QlHestonModel* qlHestonModel(QlHestonProcess* process, char **e) {try {return ret(new QlHestonModel(alloc(new HestonModel(*arg(process)))));} catch (std::exception& er) {return handleException<QlHestonModel*>(e, er);}}
QlHullWhite* qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, char **e) {
  try {return ret(new QlHullWhite(alloc(new HullWhite(*arg(termStructure), a, sigma))));
  } catch (std::exception& er) {return handleException<QlHullWhite*>(e, er);}}
QlCalibratedModel* qlVarianceGammaModel(QlVarianceGammaProcess* process, char **e) {
  try {return ret(new QlCalibratedModel(alloc(new VarianceGammaModel(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlCalibratedModel*>(e, er);}}
QlOneFactorAffineModel* qlVasicek(double r0, double a, double b, double sigma, double lambda, char **e) {
  try {return ret(new QlOneFactorAffineModel(alloc(new Vasicek(r0, a, b, sigma, lambda))));
  } catch (std::exception& er) {return handleException<QlOneFactorAffineModel*>(e, er);}}

void qlFreeG2(QlG2 *o) {del(o);}
QlAffineModel* qlG2AsAffineModel(QlG2 *o) {return ret(new QlAffineModel(*arg(o)));}
QlShortRateModel* qlG2AsShortRateModel(QlG2 *o) {return ret(new QlShortRateModel(*arg(o)));}
void qlFreeShortRateDynamics(QlShortRateDynamics *o) {del(o);}
QlShortRateDynamics* qlG2Dynamics(QlG2 *o, char **e) {
  try {return ret(new QlShortRateDynamics((*arg(o))->dynamics()));
  } catch (std::exception& er) {return handleException<QlShortRateDynamics*>(e, er);}}
double qlShortRateDynamicsShortRate(QlShortRateDynamics *o, double t, double x, double y, char **e) {
  try {return (*arg(o))->shortRate(t, x, y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeBatesDetJumpModel(QlBatesDetJumpModel *o) {del(o);}
QlBatesModel* qlBatesDetJumpModelAsBatesModel(QlBatesDetJumpModel *o) {return ret(new QlBatesModel(*arg(o)));}
void qlFreeBatesDoubleExpDetJumpModel(QlBatesDoubleExpDetJumpModel *o) {del(o);}
QlBatesDoubleExpModel* qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel(QlBatesDoubleExpDetJumpModel *o) {return ret(new QlBatesDoubleExpModel(*arg(o)));}
void qlFreeBatesDoubleExpModel(QlBatesDoubleExpModel *o) {del(o);}
QlHestonModel* qlBatesDoubleExpModelAsHestonModel(QlBatesDoubleExpModel *o) {return ret(new QlHestonModel(*arg(o)));}
void qlFreeLmCorrelationModel(QlLmCorrelationModel *o) {del(o);}
void qlFreeLmVolatilityModel(QlLmVolatilityModel *o) {del(o);}

QlLmCorrelationModel* qlLmConstWrapperCorrelationModel(QlLmCorrelationModel* corrModel, char **e) {
  try {return ret(new QlLmCorrelationModel(alloc(new LmConstWrapperCorrelationModel(*arg(corrModel)))));
  } catch (std::exception& er) {return handleException<QlLmCorrelationModel*>(e, er);}}
QlLmVolatilityModel* qlLmConstWrapperVolatilityModel(QlLmVolatilityModel* volaModel, char **e) {
  try {return ret(new QlLmVolatilityModel(alloc(new LmConstWrapperVolatilityModel(*arg(volaModel)))));
  } catch (std::exception& er) {return handleException<QlLmVolatilityModel*>(e, er);}}
QlLmCorrelationModel* qlLmExponentialCorrelationModel(unsigned size, double rho, char **e) {
  try {return ret(new QlLmCorrelationModel(alloc(new LmExponentialCorrelationModel(size, rho))));
  } catch (std::exception& er) {return handleException<QlLmCorrelationModel*>(e, er);}}
QlLmVolatilityModel* qlLmFixedVolatilityModel(unsigned volatilitiesLen, double* volatilities, unsigned startTimesLen, double * startTimes, char **e) {
  try {return ret(new QlLmVolatilityModel(alloc(new LmFixedVolatilityModel(Array(volatilities, volatilities+volatilitiesLen), std::vector<double>(startTimes, startTimes+startTimesLen)))));
  } catch (std::exception& er) {return handleException<QlLmVolatilityModel*>(e, er);}}
QlLmCorrelationModel* qlLmLinearExponentialCorrelationModel(unsigned size, double rho, double beta, unsigned factors, char **e) {
  try {return ret(new QlLmCorrelationModel(alloc(new LmLinearExponentialCorrelationModel(size, rho, beta, factors))));
  } catch (std::exception& er) {return handleException<QlLmCorrelationModel*>(e, er);}}
QlLmVolatilityModel* qlLmLinearExponentialVolatilityModel(unsigned fixingTimesLen, double * fixingTimes, double a, double b, double c, double d, char **e) {
  try {return ret(new QlLmVolatilityModel(alloc(new LmLinearExponentialVolatilityModel(std::vector<double>(fixingTimes, fixingTimes+fixingTimesLen), a, b, c, d))));
  } catch (std::exception& er) {return handleException<QlLmVolatilityModel*>(e, er);}}
QlLiborForwardModel* qlLiborForwardModel(QlLiborForwardModelProcess* process, QlLmVolatilityModel* volaModel, QlLmCorrelationModel* corrModel, char **e) {
  try {return ret(new QlLiborForwardModel(alloc(new LiborForwardModel(*arg(process), *arg(volaModel), *arg(corrModel)))));
  } catch (std::exception& er) {return handleException<QlLiborForwardModel*>(e, er);}}

void qlFreeGsr(QlGsr *o) {del(o);}
void qlFreeMarkovFunctional(QlMarkovFunctional *o) {del(o);}
void qlFreeGaussian1dModel(QlGaussian1dModel *o) {del(o);}
QlCalibratedModel* qlGsrAsCalibratedModel(QlGsr *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlMarkovFunctionalAsCalibratedModel(QlMarkovFunctional *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlGaussian1dModel* qlGsrAsGaussian1dModel(QlGsr *o) {return ret(new QlGaussian1dModel(*arg(o)));}
QlGaussian1dModel* qlMarkovFunctionalAsGaussian1dModel(QlMarkovFunctional *o) {return ret(new QlGaussian1dModel(*arg(o)));}
QlGsr* qlGsr(QlYieldTermStructure* termStructure, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, QlQuote** volatilities, QlQuote* reversion, double T, char **e) {
  try {return ret(new QlGsr(alloc(new Gsr(*arg(termStructure), qlDateVector(volstepdates, volstepdatesLen), qlHandleVector(volatilities, volatilitiesLen), *arg(reversion), T))));
  } catch (std::exception& er) {return handleException<QlGsr*>(e, er);}}
void qlGsrVolatility(QlGsr* o, unsigned *len, double **vs, char **e) {
  try {Array vol = (*arg(o))->volatility(); *len = vol.size(); *vs = qlAllocateDoubles(*len); std::copy(vol.begin(), vol.end(), *vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlGsrCalibrateVolatilitiesIterative(QlGsr* o, unsigned helpersLen, QlBlackCalibrationHelper** helpers, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned weightsLen, double* weights, char **e) {
  try {(*arg(o))->calibrateVolatilitiesIterative(qlVector(helpers, helpersLen), **arg(method), **arg(endCriteria), Constraint(constraint ? *arg(constraint) : Constraint()), std::vector<double>(weights, weights+weightsLen));
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}
QlMarkovFunctional* qlMarkovFunctional(QlYieldTermStructure* termStructure, double reversion, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, double* volatilities, QlSwaptionVolatilityStructure* swaptionVol, unsigned expiriesLen, int* swaptionExpiries, unsigned tenorsLen, int* tenorQuantity, unsigned, int* tenorUnit, QlSwapIndex* swapIndexBase, unsigned yGridPoints, char **e) {
  try {return ret(new QlMarkovFunctional(alloc(new MarkovFunctional(*arg(termStructure), reversion, qlDateVector(volstepdates, volstepdatesLen), std::vector<double>(volatilities, volatilities+volatilitiesLen), *arg(swaptionVol), qlDateVector(swaptionExpiries, expiriesLen), qlPeriodVector(tenorQuantity, tenorUnit, tenorsLen), *arg(swapIndexBase), MarkovFunctional::ModelSettings().withYGridPoints(yGridPoints)))));
  } catch (std::exception& er) {return handleException<QlMarkovFunctional*>(e, er);}}
QlMarkovFunctional* qlMarkovFunctionalCaplet(QlYieldTermStructure* termStructure, double reversion, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, double* volatilities, QlOptionletVolatilityStructure* capletVol, unsigned expiriesLen, int* capletExpiries, QlIborIndex* iborIndex, unsigned yGridPoints, char **e) {
  try {return ret(new QlMarkovFunctional(alloc(new MarkovFunctional(*arg(termStructure), reversion, qlDateVector(volstepdates, volstepdatesLen), std::vector<double>(volatilities, volatilities+volatilitiesLen), *arg(capletVol), qlDateVector(capletExpiries, expiriesLen), *arg(iborIndex), MarkovFunctional::ModelSettings().withYGridPoints(yGridPoints)))));
  } catch (std::exception& er) {return handleException<QlMarkovFunctional*>(e, er);}}
void qlMarkovFunctionalVolatility(QlMarkovFunctional* o, unsigned *len, double **vs, char **e) {
  try {Array vol = (*arg(o))->volatility(); *len = vol.size(); *vs = qlAllocateDoubles(*len); std::copy(vol.begin(), vol.end(), *vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
QlPricingEngine* qlGaussian1dSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlYieldTermStructure* discountCurve, int probabilities, char **e) {
  try {return ret(new QlPricingEngine(alloc(new Gaussian1dSwaptionEngine(*arg(model), integrationPoints, stddevs, extrapolatePayoff, flatPayoffExtrapolation, qlNullableHandle(discountCurve), (Gaussian1dSwaptionEngine::Probabilities)probabilities))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlGaussian1dNonstandardSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlQuote* oas, QlYieldTermStructure* discountCurve, int probabilities, char **e) {
  try {return ret(new QlPricingEngine(alloc(new Gaussian1dNonstandardSwaptionEngine(*arg(model), integrationPoints, stddevs, extrapolatePayoff, flatPayoffExtrapolation, qlNullableHandle(oas), qlNullableHandle(discountCurve), (Gaussian1dNonstandardSwaptionEngine::Probabilities)probabilities))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
// As qlGaussian1dNonstandardSwaptionEngine, plus a trailing includeTodaysExercise bool before
// probabilities (gaussian1dfloatfloatswaptionengine.hpp).
QlPricingEngine* qlGaussian1dFloatFloatSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlQuote* oas, QlYieldTermStructure* discountCurve, int includeTodaysExercise, int probabilities, char **e) {
  try {return ret(new QlPricingEngine(alloc(new Gaussian1dFloatFloatSwaptionEngine(*arg(model), integrationPoints, stddevs, extrapolatePayoff, flatPayoffExtrapolation, qlNullableHandle(oas), qlNullableHandle(discountCurve), includeTodaysExercise, (Gaussian1dFloatFloatSwaptionEngine::Probabilities)probabilities))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlGaussian1dJamshidianSwaptionEngine(QlGaussian1dModel* model, char **e) {
  try {return ret(new QlPricingEngine(alloc(new Gaussian1dJamshidianSwaptionEngine(*arg(model)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlGaussian1dCapFloorEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlPricingEngine(alloc(new Gaussian1dCapFloorEngine(*arg(model), integrationPoints, stddevs, extrapolatePayoff, flatPayoffExtrapolation, qlNullableHandle(discountCurve)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

QlCalibratedModel* qlGJRGARCHModelAsCalibratedModel(QlGJRGARCHModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlHestonModelAsCalibratedModel(QlHestonModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlHestonModel* qlBatesModelAsHestonModel(QlBatesModel *o) {return ret(new QlHestonModel(*arg(o)));}
QlCalibratedModel* qlLiborForwardModelAsCalibratedModel(QlLiborForwardModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlPiecewiseTimeDependentHestonModelAsCalibratedModel(QlPiecewiseTimeDependentHestonModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlShortRateModelAsCalibratedModel(QlShortRateModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlShortRateModel* qlOneFactorAffineModelAsShortRateModel(QlOneFactorAffineModel *o) {return ret(new QlShortRateModel(*arg(o)));}
void qlFreeCalibrationHelper(QlCalibrationHelper *o) {del(o);}
void qlFreeBlackCalibrationHelper(QlBlackCalibrationHelper *o) {del(o);}
QlCalibrationHelper* qlBlackCalibrationHelperAsCalibrationHelper(QlBlackCalibrationHelper *o) {return ret(new QlCalibrationHelper(*arg(o)));}

void qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, unsigned wLen, double *weights, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned fpLen, int* fixParameters, char **e) {
  try {(*arg(o))->calibrate(qlVector(x1, x1Len), **arg(method), **arg(endCriteria), Constraint(constraint ? *arg(constraint) : Constraint()), std::vector<double>(weights, weights+wLen), std::vector<bool>(fixParameters, fixParameters+fpLen));
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}
double qlCalibratedModelValue(QlCalibratedModel* o, unsigned pLen, double* p, unsigned hLen, QlCalibrationHelper** h, char **e) {
  try {return (*arg(o))->value(Array(p, p+pLen), qlVector(h, hLen));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlBlackCalibrationHelperSetPricingEngine(QlBlackCalibrationHelper* o, QlPricingEngine* engine, char **e) {
  try {(*arg(o))->setPricingEngine(*arg(engine));
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}
QlBlackCalibrationHelper* qlCapHelper(int l, int u, QlQuote* volatility, QlIborIndex* index, int fixedLegFrequency, DayCounter* fixedLegDayCounter, int includeFirstSwaplet, QlYieldTermStructure* termStructure, int errorType, int type, double shift, char **e) {
  try {return ret(new QlBlackCalibrationHelper(alloc(new CapHelper(Period(l, (TimeUnit)u), *arg(volatility), *arg(index), (Frequency)fixedLegFrequency, *arg(fixedLegDayCounter), includeFirstSwaplet, *arg(termStructure), (BlackCalibrationHelper::CalibrationErrorType)errorType, (VolatilityType)type, shift))));
  } catch (std::exception& er) {return handleException<QlBlackCalibrationHelper*>(e, er);}}
QlBlackCalibrationHelper* qlHestonModelHelper(int l, int u, Calendar* calendar, QlQuote* s0, double strikePrice, QlQuote* volatility, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int errorType, char **e) {
  try {return ret(new QlBlackCalibrationHelper(alloc(new HestonModelHelper(Period(l, (TimeUnit)u), *arg(calendar), *arg(s0), strikePrice, *arg(volatility), *arg(riskFreeRate), *arg(dividendYield), (BlackCalibrationHelper::CalibrationErrorType)errorType))));
  } catch (std::exception& er) {return handleException<QlBlackCalibrationHelper*>(e, er);}}
void qlFreeSwaptionHelper(QlSwaptionHelper *o) {del(o);}
QlBlackCalibrationHelper* qlSwaptionHelperAsBlackCalibrationHelper(QlSwaptionHelper *o) {return ret(new QlBlackCalibrationHelper(*arg(o)));}
QlSwaptionHelper* qlSwaptionHelper(int l, int u, int ll, int lu, QlQuote* volatility, QlIborIndex* index, int fl, int fu, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, char **e) {
  try {return ret(new QlSwaptionHelper(alloc(new SwaptionHelper(Period(l, (TimeUnit)u), Period(ll, (TimeUnit)lu), *arg(volatility), *arg(index), Period(fl, (TimeUnit)fu), *arg(fixedLegDayCounter), *arg(floatingLegDayCounter), *arg(termStructure), (BlackCalibrationHelper::CalibrationErrorType)errorType, strike, nominal, (VolatilityType)volatilityType, shift, settlementDays, (RateAveraging::Type)averagingMethod))));
  } catch (std::exception& er) {return handleException<QlSwaptionHelper*>(e, er);}}
QlSwaptionHelper* qlSwaptionHelperFromDate(int exerciseDate, int ll, int lu, QlQuote* volatility, QlIborIndex* index, int fl, int fu, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, char **e) {
  try {return ret(new QlSwaptionHelper(alloc(new SwaptionHelper(Date(exerciseDate), Period(ll, (TimeUnit)lu), *arg(volatility), *arg(index), Period(fl, (TimeUnit)fu), *arg(fixedLegDayCounter), *arg(floatingLegDayCounter), *arg(termStructure), (BlackCalibrationHelper::CalibrationErrorType)errorType, strike, nominal, (VolatilityType)volatilityType, shift, settlementDays, (RateAveraging::Type)averagingMethod))));
  } catch (std::exception& er) {return handleException<QlSwaptionHelper*>(e, er);}}
QlSwaptionHelper* qlSwaptionHelperFromDates(int exerciseDate, int endDate, QlQuote* volatility, QlIborIndex* index, int fl, int fu, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, char **e) {
  try {return ret(new QlSwaptionHelper(alloc(new SwaptionHelper(Date(exerciseDate), Date(endDate), *arg(volatility), *arg(index), Period(fl, (TimeUnit)fu), *arg(fixedLegDayCounter), *arg(floatingLegDayCounter), *arg(termStructure), (BlackCalibrationHelper::CalibrationErrorType)errorType, strike, nominal, (VolatilityType)volatilityType, shift, settlementDays, (RateAveraging::Type)averagingMethod))));
  } catch (std::exception& er) {return handleException<QlSwaptionHelper*>(e, er);}}
// Both accessors are cast-free: o is already a genuine SwaptionHelper (constructed as one above),
// so underlying()/swaption() are plain method calls, not a downcast from a type-erased base.
QlFixedVsFloatingSwap* qlSwaptionHelperUnderlying(QlSwaptionHelper* o, char **e) {
  try {return ret(new QlFixedVsFloatingSwap((*arg(o))->underlying()));
  } catch (std::exception& er) {return handleException<QlFixedVsFloatingSwap*>(e, er);}}
QlSwaption* qlSwaptionHelperSwaption(QlSwaptionHelper* o, char **e) {
  try {return ret(new QlSwaption((*arg(o))->swaption()));
  } catch (std::exception& er) {return handleException<QlSwaption*>(e, er);}}
void qlBlackCalibrationHelperTimes(QlBlackCalibrationHelper* o, unsigned *len, double **ts, char **e) {
  try {std::list<double> times;(*arg(o))->addTimesTo(times);*len = times.size();*ts = qlAllocateDoubles(*len);std::copy(times.begin(), times.end(), *ts);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlCalibratedModelParams(QlCalibratedModel* o, unsigned *len, double** ps, char **e) {
  try {Array params = (*arg(o))->params(); *len = params.size(); *ps = qlAllocateDoubles(*len); std::copy(params.begin(), params.end(), *ps);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
double qlBlackCalibrationHelperBlackPrice(QlBlackCalibrationHelper* o, double volatility, char **e) {try {return (*arg(o))->blackPrice(volatility);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalibrationHelperCalibrationError(QlBlackCalibrationHelper* o, char **e) {try {return (*arg(o))->calibrationError();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalibrationHelperImpliedVolatility(QlBlackCalibrationHelper* o, double targetValue, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {return (*arg(o))->impliedVolatility(targetValue, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalibrationHelperMarketValue(QlBlackCalibrationHelper* o, char **e) {try {return (*arg(o))->marketValue();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackCalibrationHelperModelValue(QlBlackCalibrationHelper* o, char **e) {try {return (*arg(o))->modelValue();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlQuote* qlBlackCalibrationHelperVolatility(QlBlackCalibrationHelper* o, char **e) {
  try {return ret(new QlQuote((*arg(o))->volatility().currentLink()));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}

void qlFreeStochasticProcess1D(QlStochasticProcess1D *o) {del(o);}
QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeBlackProcess(QlBlackProcess *o) {del(o);}
QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o) {return ret(new QlGeneralizedBlackScholesProcess(*arg(o)));}
void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o) {del(o);}
QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeStochasticProcess(QlStochasticProcess *o) {del(o);}
unsigned qlStochasticProcessFactors(QlStochasticProcess* o, char **e) {
  try {return (*arg(o))->factors();
  } catch (std::exception& er) {return handleException<unsigned>(e, er);}}
void qlStochasticProcessInitialValues(QlStochasticProcess* o, unsigned *len, double **vs, char **e) {
  try {Array iv = (*arg(o))->initialValues(); *len = iv.size(); *vs = qlAllocateDoubles(*len); std::copy(iv.begin(), iv.end(), *vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlStochasticProcessDrift(QlStochasticProcess* o, double t, unsigned xLen, double *x, unsigned *len, double **vs, char **e) {
  try {Array d = (*arg(o))->drift(t, Array(x, x+xLen)); *len = d.size(); *vs = qlAllocateDoubles(*len); std::copy(d.begin(), d.end(), *vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlStochasticProcessDiffusion(QlStochasticProcess* o, double t, unsigned xLen, double *x, unsigned *rows, unsigned *cols, unsigned *len, double **vs, char **e) {
  try {Matrix m = (*arg(o))->diffusion(t, Array(x, x+xLen)); *rows = m.rows(); *cols = m.columns(); *len = m.rows()*m.columns();
    *vs = qlAllocateDoubles(*len); std::copy(m.begin(), m.end(), *vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlStochasticProcessExpectation(QlStochasticProcess* o, double t0, unsigned x0Len, double *x0, double dt, unsigned *len, double **vs, char **e) {
  try {Array ex = (*arg(o))->expectation(t0, Array(x0, x0+x0Len), dt); *len = ex.size(); *vs = qlAllocateDoubles(*len); std::copy(ex.begin(), ex.end(), *vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

QlBlackProcess* qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e) {
  try {return ret(new QlBlackProcess(alloc(new BlackProcess(*arg(x0), *arg(riskFreeTS), *arg(blackVolTS), createDiscretization1D(d), forceDiscretization))));
  } catch (std::exception& er) {return handleException<QlBlackProcess*>(e, er);}}
QlGeneralizedBlackScholesProcess* qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e) {
  try {return ret(new QlGeneralizedBlackScholesProcess(alloc(new BlackScholesMertonProcess(*arg(x0), *arg(dividendTS), *arg(riskFreeTS), *arg(blackVolTS), createDiscretization1D(d), forceDiscretization))));
  } catch (std::exception& er) {return handleException<QlGeneralizedBlackScholesProcess*>(e, er);}}
QlGeneralizedBlackScholesProcess* qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e) {
  try {return ret(new QlGeneralizedBlackScholesProcess(alloc(new BlackScholesProcess(*arg(x0), *arg(riskFreeTS), *arg(blackVolTS), createDiscretization1D(d), forceDiscretization))));
  } catch (std::exception& er) {return handleException<QlGeneralizedBlackScholesProcess*>(e, er);}}
QlGeneralizedBlackScholesProcess* qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int evolDisc, char **e) {
  try {return ret(new QlGeneralizedBlackScholesProcess(alloc(new ExtendedBlackScholesMertonProcess(*arg(x0), *arg(dividendTS), *arg(riskFreeTS), *arg(blackVolTS), createDiscretization1D(d), (ExtendedBlackScholesMertonProcess::Discretization)evolDisc))));
  } catch (std::exception& er) {return handleException<QlGeneralizedBlackScholesProcess*>(e, er);}}
QlGeneralizedBlackScholesProcess* qlGarmanKohlagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e) {
  try {return ret(new QlGeneralizedBlackScholesProcess(alloc(new GarmanKohlagenProcess(*arg(x0), *arg(foreignRiskFreeTS), *arg(domesticRiskFreeTS), *arg(blackVolTS), createDiscretization1D(d), forceDiscretization))));
  } catch (std::exception& er) {return handleException<QlGeneralizedBlackScholesProcess*>(e, er);}}
QlGeneralizedBlackScholesProcess* qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e) {
  try {return ret(new QlGeneralizedBlackScholesProcess(alloc(new GeneralizedBlackScholesProcess(*arg(x0), *arg(dividendTS), *arg(riskFreeTS), *arg(blackVolTS), createDiscretization1D(d), forceDiscretization))));
  } catch (std::exception& er) {return handleException<QlGeneralizedBlackScholesProcess*>(e, er);}}
QlStochasticProcess1D* qlSquareRootProcess(double b, double a, double sigma, double x0, int d, char **e) {
  try {return ret(new QlStochasticProcess1D(alloc(new SquareRootProcess(b, a, sigma, x0, createDiscretization1D(d)))));
  } catch (std::exception& er) {return handleException<QlStochasticProcess1D*>(e, er);}}
QlGeneralizedBlackScholesProcess* qlVegaStressedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, double lowerTimeBorderForStressTest, double upperTimeBorderForStressTest, double lowerAssetBorderForStressTest, double upperAssetBorderForStressTest, double stressLevel, int d, char **e) {
  try {return ret(new QlGeneralizedBlackScholesProcess(alloc(new VegaStressedBlackScholesProcess(*arg(x0), *arg(dividendTS), *arg(riskFreeTS), *arg(blackVolTS), lowerTimeBorderForStressTest, upperTimeBorderForStressTest, lowerAssetBorderForStressTest, upperAssetBorderForStressTest, stressLevel, createDiscretization1D(d)))));
  } catch (std::exception& er) {return handleException<QlGeneralizedBlackScholesProcess*>(e, er);}}

void qlFreeExtOUWithJumpsProcess(QlExtOUWithJumpsProcess *o) {del(o);}
QlStochasticProcess* qlExtOUWithJumpsProcessAsStochasticProcess(QlExtOUWithJumpsProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeExtendedOrnsteinUhlenbeckProcess(QlExtendedOrnsteinUhlenbeckProcess *o) {del(o);}
QlStochasticProcess1D* qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D(QlExtendedOrnsteinUhlenbeckProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeGJRGARCHProcess(QlGJRGARCHProcess *o) {del(o);}
QlStochasticProcess* qlGJRGARCHProcessAsStochasticProcess(QlGJRGARCHProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeHestonProcess(QlHestonProcess *o) {del(o);}
QlStochasticProcess* qlHestonProcessAsStochasticProcess(QlHestonProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeBatesProcess(QlBatesProcess *o) {del(o);}
QlHestonProcess* qlBatesProcessAsHestonProcess(QlBatesProcess *o) {return ret(new QlHestonProcess(*arg(o)));}
void qlFreeHybridHestonHullWhiteProcess(QlHybridHestonHullWhiteProcess *o) {del(o);}
QlStochasticProcess* qlHybridHestonHullWhiteProcessAsStochasticProcess(QlHybridHestonHullWhiteProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeKlugeExtOUProcess(QlKlugeExtOUProcess *o) {del(o);}
QlStochasticProcess* qlKlugeExtOUProcessAsStochasticProcess(QlKlugeExtOUProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeLiborForwardModelProcess(QlLiborForwardModelProcess *o) {del(o);}
QlStochasticProcess* qlLiborForwardModelProcessAsStochasticProcess(QlLiborForwardModelProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeStochasticProcessArray(QlStochasticProcessArray *o) {del(o);}
QlStochasticProcess* qlStochasticProcessArrayAsStochasticProcess(QlStochasticProcessArray *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeVarianceGammaProcess(QlVarianceGammaProcess *o) {del(o);}
QlStochasticProcess1D* qlVarianceGammaProcessAsStochasticProcess1D(QlVarianceGammaProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeMerton76Process(QlMerton76Process *o) {del(o);}
QlStochasticProcess1D* qlMerton76ProcessAsStochasticProcess1D(QlMerton76Process *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeHullWhiteProcess(QlHullWhiteProcess *o) {del(o);}
QlStochasticProcess1D* qlHullWhiteProcessAsStochasticProcess1D(QlHullWhiteProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeHullWhiteForwardProcess(QlHullWhiteForwardProcess *o) {del(o);}
QlStochasticProcess1D* qlHullWhiteForwardProcessAsStochasticProcess1D(QlHullWhiteForwardProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlHullWhiteForwardProcessSetForwardMeasureTime(QlHullWhiteForwardProcess* o, double t, char **e) {
  try {(*arg(o))->setForwardMeasureTime(t);
  } catch (std::exception& er) {(void)handleException<double>(e, er);}}

void qlFreeG2Process(QlG2Process *o) {del(o);}
QlStochasticProcess* qlG2ProcessAsStochasticProcess(QlG2Process *o) {return ret(new QlStochasticProcess(*arg(o)));}
double qlG2ProcessPhi(QlG2Process* o, double t, char **e) {
  try {return (*arg(o))->phi(t);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlG2ProcessShortRate(QlG2Process* o, double t, double x, double y) {return (*arg(o))->shortRate(t, x, y);}

void qlFreeG2ForwardProcess(QlG2ForwardProcess *o) {del(o);}
QlStochasticProcess* qlG2ForwardProcessAsStochasticProcess(QlG2ForwardProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
double qlG2ForwardProcessPhi(QlG2ForwardProcess* o, double t, char **e) {
  try {return (*arg(o))->phi(t);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlG2ForwardProcessShortRate(QlG2ForwardProcess* o, double t, double x, double y) {return (*arg(o))->shortRate(t, x, y);}

QlBatesProcess* qlBatesProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, double lambda, double nu, double delta, int d, char **e) {
  try {return ret(new QlBatesProcess(alloc(new BatesProcess(*arg(riskFreeRate), *arg(dividendYield), *arg(s0), v0, kappa, theta, sigma, rho, lambda, nu, delta, (HestonProcess::Discretization)d))));
  } catch (std::exception& er) {return handleException<QlBatesProcess*>(e, er);}}
QlExtOUWithJumpsProcess* qlExtOUWithJumpsProcess(QlExtendedOrnsteinUhlenbeckProcess* process, double Y0, double beta, double jumpIntensity, double eta, char **e) {
  try {return ret(new QlExtOUWithJumpsProcess(alloc(new ExtOUWithJumpsProcess(*arg(process), Y0, beta, jumpIntensity, eta))));
  } catch (std::exception& er) {return handleException<QlExtOUWithJumpsProcess*>(e, er);}}
QlG2ForwardProcess* qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlG2ForwardProcess(alloc(new G2ForwardProcess(a, sigma, b, eta, rho, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlG2ForwardProcess*>(e, er);}}
QlG2Process* qlG2Process(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlG2Process(alloc(new G2Process(a, sigma, b, eta, rho, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlG2Process*>(e, er);}}
QlStochasticProcess1D* qlGemanRoncoroniProcess(double x0, double alpha, double beta, double gamma, double delta, double eps, double zeta, double d, double k, double tau, double sig2, double a, double b, double theta1, double theta2, double theta3, double psi, char **e) {
  try {return ret(new QlStochasticProcess1D(alloc(new GemanRoncoroniProcess(x0, alpha, beta, gamma, delta, eps, zeta, d, k, tau, sig2, a, b, theta1, theta2, theta3, psi))));
  } catch (std::exception& er) {return handleException<QlStochasticProcess1D*>(e, er);}}
QlStochasticProcess1D* qlGeometricBrownianMotionProcess(double initialValue, double mue, double sigma, char **e) {
  try {return ret(new QlStochasticProcess1D(alloc(new GeometricBrownianMotionProcess(initialValue, mue, sigma))));
  } catch (std::exception& er) {return handleException<QlStochasticProcess1D*>(e, er);}}
QlGJRGARCHProcess* qlGJRGARCHProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double omega, double alpha, double beta, double gamma, double lambda, double daysPerYear, int d, char **e) {
  try {return ret(new QlGJRGARCHProcess(alloc(new GJRGARCHProcess(*arg(riskFreeRate), *arg(dividendYield), *arg(s0), v0, omega, alpha, beta, gamma, lambda, daysPerYear, (GJRGARCHProcess::Discretization)d))));
  } catch (std::exception& er) {return handleException<QlGJRGARCHProcess*>(e, er);}}
QlHestonProcess* qlHestonProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, int d, char **e) {
  try {return ret(new QlHestonProcess(alloc(new HestonProcess(*arg(riskFreeRate), qlNullableHandle(arg(dividendYield)), *arg(s0), v0, kappa, theta, sigma, rho, (HestonProcess::Discretization)d))));
  } catch (std::exception& er) {return handleException<QlHestonProcess*>(e, er);}}
QlHullWhiteForwardProcess* qlHullWhiteForwardProcess(QlYieldTermStructure* h, double a, double sigma, char **e) {
  try {return ret(new QlHullWhiteForwardProcess(alloc(new HullWhiteForwardProcess(*arg(h), a, sigma))));
  } catch (std::exception& er) {return handleException<QlHullWhiteForwardProcess*>(e, er);}}
QlHullWhiteProcess* qlHullWhiteProcess(QlYieldTermStructure* h, double a, double sigma, char **e) {
  try {return ret(new QlHullWhiteProcess(alloc(new HullWhiteProcess(*arg(h), a, sigma))));
  } catch (std::exception& er) {return handleException<QlHullWhiteProcess*>(e, er);}}
QlHybridHestonHullWhiteProcess* qlHybridHestonHullWhiteProcess(QlHestonProcess* hestonProcess, QlHullWhiteForwardProcess* hullWhiteProcess, double corrEquityShortRate, int discretization, char **e) {
  try {return ret(new QlHybridHestonHullWhiteProcess(alloc(new HybridHestonHullWhiteProcess(*arg(hestonProcess), *arg(hullWhiteProcess), corrEquityShortRate, (HybridHestonHullWhiteProcess::Discretization)discretization))));
  } catch (std::exception& er) {return handleException<QlHybridHestonHullWhiteProcess*>(e, er);}}
QlKlugeExtOUProcess* qlKlugeExtOUProcess(double rho, QlExtOUWithJumpsProcess* kluge, QlExtendedOrnsteinUhlenbeckProcess* extOU, char **e) {
  try {return ret(new QlKlugeExtOUProcess(alloc(new KlugeExtOUProcess(rho, *arg(kluge), (*arg(extOU))))));
  } catch (std::exception& er) {return handleException<QlKlugeExtOUProcess*>(e, er);}}
QlLiborForwardModelProcess* qlLiborForwardModelProcess(unsigned size, QlIborIndex* index, char **e) {
  try {return ret(new QlLiborForwardModelProcess(alloc(new LiborForwardModelProcess(size, *arg(index)))));
  } catch (std::exception& er) {return handleException<QlLiborForwardModelProcess*>(e, er);}}
void qlLiborForwardModelProcessFixingDates(QlLiborForwardModelProcess* o, unsigned *len, int **dates, char **e) {
  *len = 0; *dates = 0;
  try {const std::vector<Date>& fixingDates = (*arg(o))->fixingDates();
    *dates = qlAllocateInts(fixingDates.size()); *len = fixingDates.size();
    for (unsigned i = 0; i < fixingDates.size(); ++i) (*dates)[i] = fixingDates[i].serialNumber();
  } catch (std::exception& er) {(void)handleException<int*>(e, er);}}
void qlLiborForwardModelProcessFixingTimes(QlLiborForwardModelProcess* o, unsigned *len, double **times, char **e) {
  *len = 0; *times = 0;
  try {const std::vector<Time>& fixingTimes = (*arg(o))->fixingTimes();
    *times = qlAllocateDoubles(fixingTimes.size()); *len = fixingTimes.size();
    std::copy(fixingTimes.begin(), fixingTimes.end(), *times);
  } catch (std::exception& er) {(void)handleException<double*>(e, er);}}
Leg* qlLiborForwardModelProcessCashFlows(QlLiborForwardModelProcess* o, double amount, char **e) {
  try {return ret(new Leg((*arg(o))->cashFlows(amount)));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
QlIborIndex* qlLiborForwardModelProcessIndex(QlLiborForwardModelProcess* o, char **e) {
  try {return ret(new QlIborIndex((*arg(o))->index()));
  } catch (std::exception& er) {return handleException<QlIborIndex*>(e, er);}}
QlMerton76Process* qlMerton76Process(QlQuote* stateVariable, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, QlQuote* jumpInt, QlQuote* logJMean, QlQuote* logJVol, int d, char **e) {
  try {return ret(new QlMerton76Process(alloc(new Merton76Process(*arg(stateVariable), *arg(dividendTS), *arg(riskFreeTS), *arg(blackVolTS), *arg(jumpInt), *arg(logJMean), *arg(logJVol), createDiscretization1D(d)))));
  } catch (std::exception& er) {return handleException<QlMerton76Process*>(e, er);}}
QlStochasticProcess1D* qlOrnsteinUhlenbeckProcess(double speed, double vol, double x0, double level, char **e) {
  try {return ret(new QlStochasticProcess1D(alloc(new OrnsteinUhlenbeckProcess(speed, vol, x0, level))));
  } catch (std::exception& er) {return handleException<QlStochasticProcess1D*>(e, er);}}
QlVarianceGammaProcess* qlVarianceGammaProcess(QlQuote* s0, QlYieldTermStructure* dividendYield, QlYieldTermStructure* riskFreeRate, double sigma, double nu, double theta, char **e) {
  try {return ret(new QlVarianceGammaProcess(alloc(new VarianceGammaProcess(*arg(s0), *arg(dividendYield), *arg(riskFreeRate), sigma, nu, theta))));
  } catch (std::exception& er) {return handleException<QlVarianceGammaProcess*>(e, er);}}
QlStochasticProcessArray* qlStochasticProcessArray(unsigned x0Len, QlStochasticProcess1D** x0, unsigned correlationRows, unsigned correlationCols, double* correlation, char **e) {
  try {return ret(new QlStochasticProcessArray(alloc(new StochasticProcessArray(qlVector(x0, x0Len), qlMatrix(correlation, correlationRows, correlationCols)))));
  } catch (std::exception& er) {return handleException<QlStochasticProcessArray*>(e, er);}}

// delWith rather than del(): qlFreePolymorphicPathGeneratorAux does the actual `delete`, since
// PolymorphicPathGenerator is only forward-declared in this translation unit.
void qlFreePathGenerator(PolymorphicPathGenerator *gen) {delWith(gen, qlFreePolymorphicPathGeneratorAux);}
PolymorphicPathGenerator *qlPathGenerator(int rngtrait, QlStochasticProcess *p, TimeGrid *t, unsigned seed, unsigned dim, int brownianBridge, char **e) {
  try {return ret(qlPathGeneratorAux(rngtrait, *arg(p), *arg(t), seed, dim, brownianBridge));
  } catch (std::exception& er) {return handleException<PolymorphicPathGenerator*>(e, er);}}
PolymorphicPathGenerator *qlSobolPathGenerator(int dir, QlStochasticProcess *p, TimeGrid *t, unsigned seed, unsigned dim, int brownianBridge, char **e) {
  try {return ret(qlSobolPathGeneratorAux((SobolRsg::DirectionIntegers)dir, *arg(p), *arg(t), seed, dim, brownianBridge));
  } catch (std::exception& er) {return handleException<PolymorphicPathGenerator*>(e, er);}}
SamplePath *qlPathGeneratorNext(PolymorphicPathGenerator *pgen, char **e) {
  try {return alloc(new SamplePath(qlPathGeneratorNextAux(pgen)));
  } catch (std::exception& er) {return handleException<SamplePath*>(e, er);}}
SamplePath *qlPathGeneratorAntithetic(PolymorphicPathGenerator *pgen, char **e) {
  try {return alloc(new SamplePath(qlPathGeneratorAntitheticAux(pgen)));
  } catch (std::exception& er) {return handleException<SamplePath*>(e, er);}}

double qlSamplePathWeight(SamplePath *p) {return arg(p)->weight;}
unsigned qlSamplePathAssetNumber(SamplePath *p) {return arg(p)->value.assetNumber();}
unsigned qlSamplePathSize(SamplePath *p) {return arg(p)->value.pathSize();}
void qlFreeSamplePath(SamplePath *p) {del(p);}
double qlSamplePathAt(SamplePath *p, unsigned asset, unsigned point, char **e) {try {return arg(p)->value.at(asset).at(point);} catch (std::exception& er) {return handleException<double>(e, er);}}

// delWith, for the same reason as qlFreePathGenerator above.
void qlFreeGaussianRsg(PolymorphicGaussianRsg *g) {delWith(g, qlFreePolymorphicGaussianRsgAux);}
// ret() only, no alloc(): the generator is a standalone heap object handed straight to Haskell and
// freed by qlFreeGaussianRsg -- not a shared_ptr payload. Wrapping it in both verbs would trace one
// pointer as two acquisitions against a single release, which alloc-summary.py reports as a leak.
// Same shape as qlPathGenerator below.
PolymorphicGaussianRsg *qlGaussianRsg(int rngtrait, unsigned dimension, unsigned seed, char **e) {
  try {return ret(qlGaussianRsgAux(rngtrait, dimension, seed));
  } catch (std::exception& er) {return handleException<PolymorphicGaussianRsg*>(e, er);}}
PolymorphicGaussianRsg *qlSobolGaussianRsg(int dir, unsigned dimension, unsigned seed, char **e) {
  try {return ret(qlSobolGaussianRsgAux((SobolRsg::DirectionIntegers)dir, dimension, seed));
  } catch (std::exception& er) {return handleException<PolymorphicGaussianRsg*>(e, er);}}
unsigned qlGaussianRsgDimension(PolymorphicGaussianRsg *g) {return qlGaussianRsgDimensionAux(arg(g));}

void qlGaussianRsgNextSequence(PolymorphicGaussianRsg *g, unsigned *len, double **values, double *weight, char **e) {
  try {copySequence(qlGaussianRsgNextSequenceAux(arg(g)), len, values, weight);
  } catch (std::exception& er) {*e = tracedup(er.what());}}
void qlGaussianRsgLastSequence(PolymorphicGaussianRsg *g, unsigned *len, double **values, double *weight, char **e) {
  try {copySequence(qlGaussianRsgLastSequenceAux(arg(g)), len, values, weight);
  } catch (std::exception& er) {*e = tracedup(er.what());}}

void qlSamplePathAssetPath(SamplePath *s, unsigned asset, unsigned *len, double **p, char **e) {
  try {*len = arg(s)->value.pathSize(); *p = qlAllocateDoubles(*len);std::copy(s->value.at(asset).begin(), s->value.at(asset).end(), *p);
  } catch (std::exception& er) {(void)handleException<double*>(e, er);}}

// Runs one Longstaff-Schwartz basis-function regression (fitStates -> fitTargets) and evaluates the
// fitted continuation value at each evalState -- the cross-path regression step LongstaffSchwartzPathPricer
// performs once per exercise date, with the payoff/exercise values supplied from Haskell instead of a
// bound Payoff.
void qlLsmRegress(int polynomType, unsigned order, unsigned fitStatesLen, double *fitStates, unsigned fitTargetsLen, double *fitTargets, unsigned evalLen, double *evalStates, unsigned *outLen, double **outValues, char **e) {
  try {
    QL_REQUIRE(fitStatesLen == fitTargetsLen, "fit states and fit targets must have the same length");
    std::vector<std::function<Real(Real)> > v = LsmBasisSystem::pathBasisSystem(order, (LsmBasisSystem::PolynomialType)polynomType);
    std::vector<Real> x(fitStates, fitStates + fitStatesLen), y(fitTargets, fitTargets + fitTargetsLen);
    Array coeff = GeneralLinearLeastSquares(x, y, v).coefficients();
    *outLen = evalLen; *outValues = qlAllocateDoubles(evalLen);
    for (unsigned i = 0; i < evalLen; ++i) {
      Real cont = 0.0;
      for (Size l = 0; l < v.size(); ++l) cont += coeff[l] * v[l](evalStates[i]);
      (*outValues)[i] = cont;
    }
  } catch (std::exception& er) {*e = tracedup(er.what());}}

// Multi-asset counterpart of qlLsmRegress, via LsmBasisSystem::multiPathBasisSystem: fitStates/evalStates
// are row-major (one row per path, fitCols/evalCols columns = underlyings, which must agree).
void qlLsmRegressMulti(int polynomType, unsigned order, unsigned fitRows, unsigned fitCols, double *fitStates, unsigned fitTargetsLen, double *fitTargets, unsigned evalRows, unsigned evalCols, double *evalStates, unsigned *outLen, double **outValues, char **e) {
  try {
    QL_REQUIRE(fitCols == evalCols, "fit states and eval states must have the same number of columns (underlyings)");
    QL_REQUIRE(fitRows == fitTargetsLen, "fit states and fit targets must have the same number of rows");
    std::vector<std::function<Real(Array)> > v = LsmBasisSystem::multiPathBasisSystem(fitCols, order, (LsmBasisSystem::PolynomialType)polynomType);
    std::vector<Array> x; x.reserve(fitRows);
    for (unsigned i = 0; i < fitRows; ++i) x.emplace_back(fitStates + i*fitCols, fitStates + (i+1)*fitCols);
    std::vector<Real> y(fitTargets, fitTargets + fitTargetsLen);
    Array coeff = GeneralLinearLeastSquares(x, y, v).coefficients();
    unsigned len = evalRows;
    double *values = qlAllocateDoubles(len);
    for (unsigned i = 0; i < evalRows; ++i) {
      Array row(evalStates + i*evalCols, evalStates + (i+1)*evalCols);
      Real cont = 0.0;
      for (Size l = 0; l < v.size(); ++l) cont += coeff[l] * v[l](row);
      values[i] = cont;
    }
    *outLen = len; *outValues = values;
  } catch (std::exception& er) {*e = tracedup(er.what());}}

double qlUnsafeSabrLogNormalVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, char **e) {
  try {return unsafeSabrLogNormalVolatility(strike, forward, expiryTime, alpha, beta, nu, rho);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlUnsafeShiftedSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e) {
  try {return unsafeShiftedSabrVolatility(strike, forward, expiryTime, alpha, beta, nu, rho, shift, (VolatilityType)volatilityType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlUnsafeSabrNormalVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, char **e) {
  try {return unsafeSabrNormalVolatility(strike, forward, expiryTime, alpha, beta, nu, rho);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlUnsafeSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, int volatilityType, char **e) {
  try {return unsafeSabrVolatility(strike, forward, expiryTime, alpha, beta, nu, rho, (VolatilityType)volatilityType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, int volatilityType, char **e) {
  try {return sabrVolatility(strike, forward, expiryTime, alpha, beta, nu, rho, (VolatilityType)volatilityType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlShiftedSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e) {
  try {return shiftedSabrVolatility(strike, forward, expiryTime, alpha, beta, nu, rho, shift, (VolatilityType)volatilityType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrFlochKennedyVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, char **e) {
  try {return sabrFlochKennedyVolatility(strike, forward, expiryTime, alpha, beta, nu, rho);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlValidateSabrParameters(double alpha, double beta, double nu, double rho, char **e) {
  try {validateSabrParameters(alpha, beta, nu, rho);
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}
void qlSabrGuess(double k_m, double vol_m, double k_0, double vol_0, double k_p, double vol_p, double forward, double expiryTime, double beta, double shift, int volatilityType, unsigned *len, double **out, char **e) {
  try {std::array<Real, 4> guess = sabrGuess(k_m, vol_m, k_0, vol_0, k_p, vol_p, forward, expiryTime, beta, shift, (VolatilityType)volatilityType);
    *len = guess.size(); *out = qlAllocateDoubles(*len); std::copy(guess.begin(), guess.end(), *out);
  } catch (std::exception& er) {(void)handleException<double*>(e, er);}}
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
