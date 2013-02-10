#include <ql/instrument.hpp>
#include <ql/instruments/forward.hpp>

#include "qlaux.h"

using namespace QuantLib;

double qlInstrumentNPV(QlInstrument *instr, char **e) {
  try {
    return (*arg(instr))->NPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
  char **e) {
  try {
    (*arg(instr))->setPricingEngine(*arg(eng));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

void DLLEXPORT qlFreeInstrument(QlInstrument *instr) {
  del(instr);
}

void DLLEXPORT qlFreeForward(QlForward *fwd) {
  del(fwd);
}

QlInstrument* DLLEXPORT qlForwardAsInstrument(QlForward *fwd) {
  return ret(new QlInstrument(*arg(fwd)));
}

double qlForwardForwardValue(QlForward* o, char **e) {
  try {
    return (*arg(o))->forwardValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

InterestRate* qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->impliedYield(underlyingSpotValue, forwardValue, Date(settlementDate), (Compounding)compoundingConvention, (*arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}
int qlForwardSettlementDate(QlForward* o, char **e) {
  try {
    return ((*arg(o))->settlementDate()).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, char **e) {
  try {
    return (*arg(o))->spotIncome(Handle<YieldTermStructure>(*arg(incomeDiscountCurve)));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlForwardSpotValue(QlForward* o, char **e) {
  try {
    return (*arg(o))->spotValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
