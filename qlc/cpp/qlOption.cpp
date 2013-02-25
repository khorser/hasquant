#include <ql/instruments/barrieroption.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/instruments/vanillaswingoption.hpp>
#include <ql/instruments/forwardvanillaoption.hpp>
#include <ql/instruments/dividendvanillaoption.hpp>
#include <ql/instruments/quantoforwardvanillaoption.hpp>
#include <ql/instruments/quantobarrieroption.hpp>
#include <ql/instruments/europeanoption.hpp>
#include <ql/instruments/asianoption.hpp>
#include <ql/instruments/vanillastorageoption.hpp>
#include <ql/instruments/lookbackoption.hpp>
#include <ql/instruments/cliquetoption.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/dividendbarrieroption.hpp>
#include <ql/experimental/exoticoptions/margrabeoption.hpp>
#include <ql/experimental/exoticoptions/himalayaoption.hpp>
#include <ql/experimental/exoticoptions/pagodaoption.hpp>
#include <ql/experimental/exoticoptions/spreadoption.hpp>
#include <ql/experimental/credit/cdsoption.hpp>

#include "qlaux.h"
#include "qlOption.h"

using namespace QuantLib;

void qlFreeBarrierOption(QlBarrierOption *o) { del(o); }
QlOneAssetOption* qlBarrierOptionAsOneAssetOption(QlBarrierOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeDividendVanillaOption(QlDividendVanillaOption *o) { del(o); }
QlOneAssetOption* qlDividendVanillaOptionAsOneAssetOption(QlDividendVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeForwardVanillaOption(QlForwardVanillaOption *o) { del(o); }
QlOneAssetOption* qlForwardVanillaOptionAsOneAssetOption(QlForwardVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeMargrabeOption(QlMargrabeOption *o) { del(o); }
QlMultiAssetOption* qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o) { return ret(new QlMultiAssetOption(*arg(o))); }

void qlFreeMultiAssetOption(QlMultiAssetOption *o) { del(o); }
QlOption* qlMultiAssetOptionAsOption(QlMultiAssetOption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeOneAssetOption(QlOneAssetOption *o) { del(o); }
QlOption* qlOneAssetOptionAsOption(QlOneAssetOption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeOption(QlOption *o) { del(o); }
QlInstrument* qlOptionAsInstrument(QlOption *o) { return ret(new QlInstrument(*arg(o))); }

void qlFreeQuantoVanillaOption(QlQuantoVanillaOption *o) { del(o); }
QlOneAssetOption* qlQuantoVanillaOptionAsOneAssetOption(QlQuantoVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeSwaption(QlSwaption *o) { del(o); }
QlOption* qlSwaptionAsOption(QlSwaption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeVanillaOption(QlVanillaOption *o) { del(o); }
QlOneAssetOption* qlVanillaOptionAsOneAssetOption(QlVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeSwingExercise(QlSwingExercise *o) { del(o); }
QlBermudanExercise* qlSwingExerciseAsBermudanExercise(QlSwingExercise *o) { return ret(new QlBermudanExercise(*arg(o))); }

double qlCdsOptionAtmRate(QlCdsOption* o, char **e) {
  try {
    return (*arg(o))->atmRate();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlCdsOption* qlCdsOption(QlCreditDefaultSwap* swap, QlExercise* exercise, int knocksOut, char **e) {
  try {
    return ret(new QlCdsOption(alloc(new CdsOption((*arg(swap)), (*arg(exercise)), knocksOut))));
  } catch (std::exception& er) {
    return handleException<QlCdsOption*>(e, er);
  }
}
double qlCdsOptionImpliedVolatility(QlCdsOption* o, double price, QlYieldTermStructure* termStructure, QlDefaultProbabilityTermStructure* x3, double recoveryRate, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(price, Handle<YieldTermStructure>(*arg(termStructure)), Handle<DefaultProbabilityTermStructure>(*arg(x3)), recoveryRate, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCdsOptionRiskyAnnuity(QlCdsOption* o, char **e) {
  try {
    return (*arg(o))->riskyAnnuity();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionImpliedVolatility(QlSwaption* o, double price, QlYieldTermStructure* discountCurve, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(price, Handle<YieldTermStructure>(*arg(discountCurve)), guess, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlSwaption* qlSwaption(QlVanillaSwap* swap, QlExercise* exercise, int delivery, char **e) {
  try {
    return ret(new QlSwaption(alloc(new Swaption(*arg(swap), *arg(exercise), (Settlement::Type) delivery))));
  } catch (std::exception& er) {
    return handleException<QlSwaption*>(e, er);
  }
}

void qlFreeQuantoBarrierOption(QlQuantoBarrierOption *o) { del(o); }
QlBarrierOption* qlQuantoBarrierOptionAsBarrierOption(QlQuantoBarrierOption *o) { return ret(new QlBarrierOption(*arg(o))); }

void qlFreeQuantoForwardVanillaOption(QlQuantoForwardVanillaOption *o) { del(o); }
QlForwardVanillaOption* qlQuantoForwardVanillaOptionAsForwardVanillaOption(QlQuantoForwardVanillaOption *o) { return ret(new QlForwardVanillaOption(*arg(o))); }

QlBarrierOption* qlBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlBarrierOption(alloc(new BarrierOption((Barrier::Type)barrierType, barrier, rebate, (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlBarrierOption*>(e, er);
  }
}
double qlBarrierOptionImpliedVolatility(QlBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(price, (*arg(process)), accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlDividendVanillaOption* qlDividendVanillaOption(QlStrikedTypePayoff* payoff, QlExercise* exercise, unsigned dividendDatesLen, int* dividendDates, unsigned dividendsLen, double* dividends, char **e) {
  try {
    return ret(new QlDividendVanillaOption(alloc(new DividendVanillaOption((*arg(payoff)), (*arg(exercise)), qlDateVector(dividendDatesLen, dividendDates), std::vector<double>(dividends, dividends+dividendsLen)))));
  } catch (std::exception& er) {
    return handleException<QlDividendVanillaOption*>(e, er);
  }
}
double qlDividendVanillaOptionImpliedVolatility(QlDividendVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(price, (*arg(process)), accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlForwardVanillaOption* qlForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlForwardVanillaOption(alloc(new ForwardVanillaOption(moneyness, Date(resetDate), (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlForwardVanillaOption*>(e, er);
  }
}
double qlMargrabeOptionDelta1(QlMargrabeOption* o, char **e) {
  try {
    return (*arg(o))->delta1();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMargrabeOptionDelta2(QlMargrabeOption* o, char **e) {
  try {
    return (*arg(o))->delta2();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMargrabeOptionGamma1(QlMargrabeOption* o, char **e) {
  try {
    return (*arg(o))->gamma1();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMargrabeOptionGamma2(QlMargrabeOption* o, char **e) {
  try {
    return (*arg(o))->gamma2();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlMargrabeOption* qlMargrabeOption(int Q1, int Q2, QlExercise* x2, char **e) {
  try {
    return ret(new QlMargrabeOption(alloc(new MargrabeOption(Q1, Q2, (*arg(x2))))));
  } catch (std::exception& er) {
    return handleException<QlMargrabeOption*>(e, er);
  }
}
double qlMultiAssetOptionDelta(QlMultiAssetOption* o, char **e) {
  try {
    return (*arg(o))->delta();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMultiAssetOptionDividendRho(QlMultiAssetOption* o, char **e) {
  try {
    return (*arg(o))->dividendRho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMultiAssetOptionGamma(QlMultiAssetOption* o, char **e) {
  try {
    return (*arg(o))->gamma();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlMultiAssetOption* qlMultiAssetOption(QlPayoff* x0, QlExercise* x1, char **e) {
  try {
    return ret(new QlMultiAssetOption(alloc(new MultiAssetOption((*arg(x0)), (*arg(x1))))));
  } catch (std::exception& er) {
    return handleException<QlMultiAssetOption*>(e, er);
  }
}
double qlMultiAssetOptionRho(QlMultiAssetOption* o, char **e) {
  try {
    return (*arg(o))->rho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMultiAssetOptionTheta(QlMultiAssetOption* o, char **e) {
  try {
    return (*arg(o))->theta();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlMultiAssetOptionVega(QlMultiAssetOption* o, char **e) {
  try {
    return (*arg(o))->vega();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionDelta(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->delta();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionDeltaForward(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->deltaForward();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionDividendRho(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->dividendRho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionElasticity(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->elasticity();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionGamma(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->gamma();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionItmCashProbability(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->itmCashProbability();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlOneAssetOption* qlOneAssetOption(QlPayoff* x0, QlExercise* x1, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new OneAssetOption((*arg(x0)), (*arg(x1))))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
double qlOneAssetOptionRho(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->rho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionStrikeSensitivity(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->strikeSensitivity();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionTheta(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->theta();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionThetaPerDay(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->thetaPerDay();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOneAssetOptionVega(QlOneAssetOption* o, char **e) {
  try {
    return (*arg(o))->vega();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantoBarrierOptionQlambda(QlQuantoBarrierOption* o, char **e) {
  try {
    return (*arg(o))->qlambda();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantoBarrierOptionQrho(QlQuantoBarrierOption* o, char **e) {
  try {
    return (*arg(o))->qrho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlQuantoBarrierOption* qlQuantoBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlQuantoBarrierOption(alloc(new QuantoBarrierOption((Barrier::Type)barrierType, barrier, rebate, (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlQuantoBarrierOption*>(e, er);
  }
}
double qlQuantoBarrierOptionQvega(QlQuantoBarrierOption* o, char **e) {
  try {
    return (*arg(o))->qvega();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantoForwardVanillaOptionQlambda(QlQuantoForwardVanillaOption* o, char **e) {
  try {
    return (*arg(o))->qlambda();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantoForwardVanillaOptionQrho(QlQuantoForwardVanillaOption* o, char **e) {
  try {
    return (*arg(o))->qrho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlQuantoForwardVanillaOption* qlQuantoForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* x2, QlExercise* x3, char **e) {
  try {
    return ret(new QlQuantoForwardVanillaOption(alloc(new QuantoForwardVanillaOption(moneyness, Date(resetDate), (*arg(x2)), (*arg(x3))))));
  } catch (std::exception& er) {
    return handleException<QlQuantoForwardVanillaOption*>(e, er);
  }
}
double qlQuantoForwardVanillaOptionQvega(QlQuantoForwardVanillaOption* o, char **e) {
  try {
    return (*arg(o))->qvega();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantoVanillaOptionQlambda(QlQuantoVanillaOption* o, char **e) {
  try {
    return (*arg(o))->qlambda();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantoVanillaOptionQrho(QlQuantoVanillaOption* o, char **e) {
  try {
    return (*arg(o))->qrho();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlQuantoVanillaOption* qlQuantoVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e) {
  try {
    return ret(new QlQuantoVanillaOption(alloc(new QuantoVanillaOption((*arg(x0)), (*arg(x1))))));
  } catch (std::exception& er) {
    return handleException<QlQuantoVanillaOption*>(e, er);
  }
}
double qlQuantoVanillaOptionQvega(QlQuantoVanillaOption* o, char **e) {
  try {
    return (*arg(o))->qvega();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlVanillaOptionImpliedVolatility(QlVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(price, (*arg(process)), accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlVanillaOption* qlVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e) {
  try {
    return ret(new QlVanillaOption(alloc(new VanillaOption((*arg(x0)), (*arg(x1))))));
  } catch (std::exception& er) {
    return handleException<QlVanillaOption*>(e, er);
  }
}
QlBarrierOption* qlDividendBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, unsigned dividendDatesLen, int* dividendDates, unsigned dividendsLen, double* dividends, char **e) {
  try {
    return ret(new QlBarrierOption(alloc(new DividendBarrierOption((Barrier::Type)barrierType, barrier, rebate, (*arg(payoff)), (*arg(exercise)), qlDateVector(dividendDatesLen, dividendDates), std::vector<double>(dividends, dividends+dividendsLen)))));
  } catch (std::exception& er) {
    return handleException<QlBarrierOption*>(e, er);
  }
}
QlMultiAssetOption* qlBasketOption(QlBasketPayoff* x0, QlExercise* x1, char **e) {
  try {
    return ret(new QlMultiAssetOption(alloc(new BasketOption((*arg(x0)), (*arg(x1))))));
  } catch (std::exception& er) {
    return handleException<QlMultiAssetOption*>(e, er);
  }
}
QlMultiAssetOption* qlHimalayaOption(unsigned fixingDatesLen, int* fixingDates, double strike, char **e) {
  try {
    return ret(new QlMultiAssetOption(alloc(new HimalayaOption(qlDateVector(fixingDatesLen, fixingDates), strike))));
  } catch (std::exception& er) {
    return handleException<QlMultiAssetOption*>(e, er);
  }
}
QlMultiAssetOption* qlPagodaOption(unsigned fixingDatesLen, int* fixingDates, double roof, double fraction, char **e) {
  try {
    return ret(new QlMultiAssetOption(alloc(new PagodaOption(qlDateVector(fixingDatesLen, fixingDates), roof, fraction))));
  } catch (std::exception& er) {
    return handleException<QlMultiAssetOption*>(e, er);
  }
}
QlMultiAssetOption* qlSpreadOption(QlPlainVanillaPayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlMultiAssetOption(alloc(new SpreadOption((*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlMultiAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlCliquetOption(QlPercentageStrikePayoff* x0, QlEuropeanExercise* maturity, unsigned resetDatesLen, int* resetDates, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new CliquetOption((*arg(x0)), (*arg(maturity)), qlDateVector(resetDatesLen, resetDates)))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlContinuousAveragingAsianOption(int averageType, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new ContinuousAveragingAsianOption((Average::Type)averageType, (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlContinuousFixedLookbackOption(double currentMinmax, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new ContinuousFixedLookbackOption(currentMinmax, (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlContinuousFloatingLookbackOption(double currentMinmax, QlTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new ContinuousFloatingLookbackOption(currentMinmax, (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlDiscreteAveragingAsianOption(int averageType, double runningAccumulator, unsigned pastFixings, unsigned fixingDatesLen, int* fixingDates, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new DiscreteAveragingAsianOption((Average::Type)averageType, runningAccumulator, pastFixings, qlDateVector(fixingDatesLen, fixingDates), (*arg(payoff)), (*arg(exercise))))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlVanillaStorageOption(QlBermudanExercise* ex, double capacity, double load, double changeRate, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new VanillaStorageOption((*arg(ex)), capacity, load, changeRate))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlOneAssetOption* qlVanillaSwingOption(QlStrikedTypePayoff* payoff, QlSwingExercise* ex, unsigned minExerciseRights, unsigned maxExerciseRights, char **e) {
  try {
    return ret(new QlOneAssetOption(alloc(new VanillaSwingOption((*arg(payoff)), (*arg(ex)), minExerciseRights, maxExerciseRights))));
  } catch (std::exception& er) {
    return handleException<QlOneAssetOption*>(e, er);
  }
}
QlVanillaOption* qlEuropeanOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e) {
  try {
    return ret(new QlVanillaOption(alloc(new EuropeanOption((*arg(x0)), (*arg(x1))))));
  } catch (std::exception& er) {
    return handleException<QlVanillaOption*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
