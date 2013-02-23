#include <ql/instruments/barrieroption.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/instruments/vanillaswingoption.hpp>
#include <ql/instruments/forwardvanillaoption.hpp>
#include <ql/instruments/dividendvanillaoption.hpp>
#include <ql/instruments/quantoforwardvanillaoption.hpp>
#include <ql/experimental/exoticoptions/margrabeoption.hpp>
#include <ql/experimental/exoticoptions/himalayaoption.hpp>
#include <ql/experimental/exoticoptions/pagodaoption.hpp>
#include <ql/experimental/credit/cdsoption.hpp>

#include "qlaux.h"

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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
