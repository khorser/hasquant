#include <ql/termstructures/credit/flathazardrate.hpp>
#include <ql/experimental/credit/spreadedhazardratecurve.hpp>
#include <ql/experimental/credit/factorspreadedhazardratecurve.hpp>
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>

#include "qlaux.h"
#include "qlDefaultTS.h"
#include "qlTSAux.h"

using namespace QuantLib;

void qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o) { del(o); }
QlTermStructure* qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o) { return ret(new QlTermStructure(*arg(o))); }

//QlDefaultProbabilityTermStructure* qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(new FactorSpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), Handle<Quote>(*arg(spread))))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//QlDefaultProbabilityTermStructure* qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(settlementDays, *arg(calendar), Handle<Quote>(*arg(hazardRate)), (*arg(x3))))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//QlDefaultProbabilityTermStructure* qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(Date(referenceDate), Handle<Quote>(*arg(hazardRate)), (*arg(x2))))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//QlDefaultProbabilityTermStructure* qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(new SpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), Handle<Quote>(*arg(spread))))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//QlDefaultProbabilityTermStructure* qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedDefaultDensityCurveAux(qlDateVector(datesLen, dates), std::vector<double>(densities, densities+densitiesLen), *arg(dayCounter), *arg(calendar), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), interpolator))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//QlDefaultProbabilityTermStructure* qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedHazardRateCurveAux(qlDateVector(datesLen, dates), std::vector<double>(hazardRates, hazardRates+hazardRatesLen), *arg(dayCounter), *arg(cal), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), interpolator))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//QlDefaultProbabilityTermStructure* qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedSurvivalProbabilityCurveAux(qlDateVector(datesLen, dates), std::vector<double>(probabilities, probabilities+probabilitiesLen), *arg(dayCounter), *arg(calendar), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), interpolator))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}

void qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o) { del(o); }

//QlDefaultProbabilityHelper* qlSpreadCdsHelper(QlQuote* runningSpread, int n, int u, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityHelper(alloc(new SpreadCdsHelper(Handle<Quote>(*arg(runningSpread)), Period(n, (TimeUnit)u), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), settlesAccrual, paysAtDefaultTime))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityHelper*>(e, er);
//  }
//}
//QlDefaultProbabilityHelper* qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, int n, int u, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, char **e) {
//  try {
//    return ret(new QlDefaultProbabilityHelper(alloc(new UpfrontCdsHelper(Handle<Quote>(*arg(upfront)), runningSpread, Period(n, (TimeUnit)u), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), upfrontSettlementDays, settlesAccrual, paysAtDefaultTime))));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityHelper*>(e, er);
//  }
//}

//QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve(int referenceDate, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, double accuracy, char *trait, char* interpolator, char **e) {
//  try {
//    DefaultProbabilityTermStructure *ts = qlPiecewiseDefaultCurveAux(Date(referenceDate), qlBuildVector(instruments, instrumentsLen), *arg(dayCounter), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), accuracy, trait, interpolator);
//    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}
//
//QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve1(unsigned settlementDays, Calendar *calendar, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, double accuracy, char *trait, char* interpolator, char **e) {
//  try {
//    DefaultProbabilityTermStructure *ts = qlPiecewiseDefaultCurveAux1(settlementDays, *arg(calendar), qlBuildVector(instruments, instrumentsLen), *arg(dayCounter), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), accuracy, trait, interpolator);
//    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
//  } catch (std::exception& er) {
//    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
//  }
//}

double qlDefaultProbabilityTermStructureDefaultDensity1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultDensity(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultDensity(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultDensity(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultProbability(t, (bool)extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability2(QlDefaultProbabilityTermStructure* o, int x1, int x2, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultProbability(Date(x1), Date(x2), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability3(QlDefaultProbabilityTermStructure* o, double x1, double x2, int extrapo, char **e) {
  try {
    return (*arg(o))->defaultProbability(x1, x2, extrapo);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultProbability(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureHazardRate1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->hazardRate(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureHazardRate(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->hazardRate(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureSurvivalProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->survivalProbability(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureSurvivalProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->survivalProbability(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
