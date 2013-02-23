#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/pricingengines/barrier/analyticbarrierengine.hpp>
#include <ql/pricingengines/cliquet/all.hpp>
#include <ql/pricingengines/lookback/all.hpp>
#include <ql/pricingengines/vanilla/analyticdigitalamericanengine.hpp>
#include <ql/pricingengines/vanilla/analyticdividendeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/asian/all.hpp>
#include <ql/pricingengines/capfloor/blackcapfloorengine.hpp>
#include <ql/pricingengines/swaption/blackswaptionengine.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(
                    new DiscountingBondEngine(
                        Handle<YieldTermStructure>(*(arg(ts))),
                        qlOptBool((f))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine *>(e, er);
  }
}

void qlFreePricingEngine(QlPricingEngine *engine) {
  del(engine);
}

QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new DiscountingSwapEngine(qlNullableHandle(arg(discountCurve)), qlOptBool(includeSettlementDateFlows), qlNullableDate(settlementDate), qlNullableDate(npvDate)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticBarrierEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticCliquetEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousFixedLookbackEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousFloatingLookbackEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousGeometricAveragePriceAsianEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDigitalAmericanEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAveragePriceAsianEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAverageStrikeAsianEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDividendEuropeanEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticEuropeanEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticPerformanceEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCapFloorEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<OptionletVolatilityStructure>(*arg(vol))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCapFloorEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<Quote>(*arg(vol)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackSwaptionEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<Quote>(*arg(vol)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackSwaptionEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<SwaptionVolatilityStructure>(*arg(vol))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
