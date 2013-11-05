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

QlDefaultProbabilityTermStructure* qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new FactorSpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(settlementDays, *arg(calendar), Handle<Quote>(*arg(hazardRate)), (*arg(x3))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(Date(referenceDate), Handle<Quote>(*arg(hazardRate)), (*arg(x2))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new SpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedDefaultDensityCurveAux(qlDateVector(datesLen, dates), std::vector<double>(densities, densities+densitiesLen), *arg(dayCounter), *arg(calendar), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), interpolator))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedHazardRateCurveAux(qlDateVector(datesLen, dates), std::vector<double>(hazardRates, hazardRates+hazardRatesLen), *arg(dayCounter), *arg(cal), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), interpolator))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedSurvivalProbabilityCurveAux(qlDateVector(datesLen, dates), std::vector<double>(probabilities, probabilities+probabilitiesLen), *arg(dayCounter), *arg(calendar), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jumpsLen, jumpDates), interpolator))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}

void qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o) { del(o); }

QlDefaultProbabilityHelper* qlSpreadCdsHelper(QlQuote* runningSpread, Period* tenor, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, char **e) {
  try {
    return ret(new QlDefaultProbabilityHelper(alloc(new SpreadCdsHelper(Handle<Quote>(*arg(runningSpread)), *arg(tenor), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), settlesAccrual, paysAtDefaultTime))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityHelper*>(e, er);
  }
}
QlDefaultProbabilityHelper* qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, Period* tenor, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, char **e) {
  try {
    return ret(new QlDefaultProbabilityHelper(alloc(new UpfrontCdsHelper(Handle<Quote>(*arg(upfront)), runningSpread, *arg(tenor), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), upfrontSettlementDays, settlesAccrual, paysAtDefaultTime))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityHelper*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
