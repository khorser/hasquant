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
#include <ql/pricingengines/barrier/analyticsoftbarrierengine.hpp>
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
#include <ql/methods/finitedifferences/utilities/fdmquantohelper.hpp>
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
template <> class ObjClassName<SamplePath*> {public: static void output(std::ostream& os) {os << "SamplePath";}};
#endif

shared_ptr<StochasticProcess::discretization> createDiscretization(int n) {
  switch (n) {
  case hasquant::EulerDiscretization:
    return shared_ptr<StochasticProcess::discretization>(new EulerDiscretization());
  case hasquant::EndEulerDiscretization:
    return shared_ptr<StochasticProcess::discretization>(new EndEulerDiscretization());
  default:
      QL_FAIL("Invalid discretization: " << n);
  }
}

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

extern "C" {
QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new DiscountingBondEngine(*arg(ts), qlOptBool(f)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine *>(e, er);}}
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
QlPricingEngine* qlMCDoubleBarrierEngine(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDoubleBarrierEngineAux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
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
QlPricingEngine* qlMCVarianceSwapEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCVarianceSwapEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCHestonHullWhiteEngine1(int rngtrait, QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCHestonHullWhiteEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCAmericanEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, int antitheticVariateCalibration, unsigned seedCalibration, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCAmericanEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, (LsmBasisSystem::PolynomialType)polynomType, nCalibrationSamples, qlOptBool(antitheticVariateCalibration), seedCalibration))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCBarrierEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCBarrierEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDigitalEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDigitalEngine1Aux(rngtrait, *arg(x0), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCForwardEuropeanBSEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCForwardEuropeanBSEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDiscreteArithmeticAPEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDiscreteArithmeticAPEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDiscreteArithmeticASEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDiscreteArithmeticASEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCDiscreteGeometricAPEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCDiscreteGeometricAPEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanGJRGARCHEngine1(int rngtrait, QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanGJRGARCHEngine1Aux(rngtrait, *arg(x0), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanHestonEngine1(int rngtrait, QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanHestonEngine1Aux(rngtrait, *arg(x0), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlIntegralHestonVarianceOptionEngine(QlHestonProcess* process, char **e) {
  try {return ret(new QlPricingEngine(alloc(new IntegralHestonVarianceOptionEngine(*arg(process)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCHullWhiteCapFloorEngine1(int rngtrait, QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCHullWhiteCapFloorEngine1Aux(rngtrait, *arg(model), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCHimalayaEngine1(int rngtrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCHimalayaEngine1Aux(rngtrait, *arg(processes), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCPagodaEngine1(int rngtrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCPagodaEngine1Aux(rngtrait, *arg(processes), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCEuropeanBasketEngine1(int rngtrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCEuropeanBasketEngine1Aux(rngtrait, *arg(processes), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCAmericanBasketEngine1(int rngtrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, int polynomialType, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCAmericanBasketEngine1Aux(rngtrait, *arg(processes), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed, nCalibrationSamples, polynomialOrder, (LsmBasisSystem::PolynomialType)polynomialType))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlMCPerformanceEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlMCPerformanceEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlBinomialVanillaEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlBinomialVanillaEngineAux(tree, *arg(process), timeSteps))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}
QlPricingEngine* qlFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, char **e) {
  try {return ret(new QlPricingEngine(alloc(qlFdBlackScholesVanillaEngineAux(*arg(process), tGrid, xGrid, dampingSteps, *arg(fdScheme), localVol, illegalLocalVolOverwrite, cashDividendModel))));
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
void qlFreeFdmQuantoHelper(QlFdmQuantoHelper *o) {del(o);}
QlFdmQuantoHelper* qlFdmQuantoHelper(QlYieldTermStructure* rTS, QlYieldTermStructure* fTS, QlBlackVolTermStructure* fxVolTS, double equityFxCorrelation, double exchRateATMlevel, char **e) {
  try {shared_ptr<YieldTermStructure> r = (*arg(rTS)).currentLink(), f = (*arg(fTS)).currentLink();
    shared_ptr<BlackVolTermStructure> fxVol = (*arg(fxVolTS)).currentLink();
    return ret(new QlFdmQuantoHelper(alloc(new FdmQuantoHelper(r, f, fxVol, equityFxCorrelation, exchRateATMlevel))));
  } catch (std::exception& er) {return handleException<QlFdmQuantoHelper*>(e, er);}}
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
void qlGsrCalibrateVolatilitiesIterative(QlGsr* o, unsigned helpersLen, QlBlackCalibrationHelper** helpers, OptimizationMethod* method, EndCriteria* endCriteria, Constraint* constraint, unsigned weightsLen, double* weights, char **e) {
  try {(*arg(o))->calibrateVolatilitiesIterative(qlVector(helpers, helpersLen), *arg(method), *arg(endCriteria), Constraint(constraint ? *arg(constraint) : Constraint()), std::vector<double>(weights, weights+weightsLen));
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

void qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, unsigned wLen, double *weights, OptimizationMethod* method, EndCriteria* endCriteria, Constraint* constraint, unsigned fpLen, int* fixParameters, char **e) {
  try {(*arg(o))->calibrate(qlVector(x1, x1Len), *arg(method), *arg(endCriteria), Constraint(constraint ? *arg(constraint) : Constraint()), std::vector<double>(weights, weights+wLen), std::vector<bool>(fixParameters, fixParameters+fpLen));
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

QlBatesProcess* qlBatesProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, double lambda, double nu, double delta, int d, char **e) {
  try {return ret(new QlBatesProcess(alloc(new BatesProcess(*arg(riskFreeRate), *arg(dividendYield), *arg(s0), v0, kappa, theta, sigma, rho, lambda, nu, delta, (HestonProcess::Discretization)d))));
  } catch (std::exception& er) {return handleException<QlBatesProcess*>(e, er);}}
QlExtOUWithJumpsProcess* qlExtOUWithJumpsProcess(QlExtendedOrnsteinUhlenbeckProcess* process, double Y0, double beta, double jumpIntensity, double eta, char **e) {
  try {return ret(new QlExtOUWithJumpsProcess(alloc(new ExtOUWithJumpsProcess(*arg(process), Y0, beta, jumpIntensity, eta))));
  } catch (std::exception& er) {return handleException<QlExtOUWithJumpsProcess*>(e, er);}}
QlStochasticProcess* qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlStochasticProcess(alloc(new G2ForwardProcess(a, sigma, b, eta, rho, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlStochasticProcess*>(e, er);}}
QlStochasticProcess* qlG2Process(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, char **e) {
  try {return ret(new QlStochasticProcess(alloc(new G2Process(a, sigma, b, eta, rho, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {return handleException<QlStochasticProcess*>(e, er);}}
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

// qlFreePolymorphicPathGeneratorAux does the actual `delete` (PolymorphicPathGenerator
// is only forward-declared here, so del()'s own `delete` can't run in this translation
// unit) -- trace around it by hand so freed generators don't look permanently live.
void qlFreePathGenerator(PolymorphicPathGenerator *gen) {
  (void)TP("deleting", gen); qlFreePolymorphicPathGeneratorAux(gen); TP2("deleted", gen);
}
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
  } catch (std::exception& er) {*e = DUP(er.what());}}

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
  } catch (std::exception& er) {*e = DUP(er.what());}}

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
