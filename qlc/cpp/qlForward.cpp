#include <ql/instruments/fixedratebondforward.hpp>
#include <ql/instruments/forwardrateagreement.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeForward(QlForward *fwd) {
  del(fwd);
}

void qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd) {
  del(fwd);
}

QlForward* qlForwardRateAgreementAsForward(QlForwardRateAgreement *fwd) {
  return ret(new QlForward(*arg(fwd)));
}

// generated code

QlInstrument* qlForwardAsInstrument(QlForward *fwd) {
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

QlForwardRateAgreement* qlForwardRateAgreement(int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlIborIndex* index, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return ret(new QlForwardRateAgreement(alloc(new ForwardRateAgreement(Date(valueDate), Date(maturityDate), (Position::Type)type, strikeForwardRate, notionalAmount, (*arg(index)), qlNullableHandle(arg(discountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlForwardRateAgreement*>(e, er);
  }
}

void qlFreeFixedRateBondForward(QlFixedRateBondForward *fwd) {
  del(fwd);
}

QlForward* qlFixedRateBondForwardAsForward(QlFixedRateBondForward *fwd) {
  return ret(new QlForward(*arg(fwd)));
}

QlFixedRateBondForward* qlFixedRateBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlFixedRateBond* fixedCouponBond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, char **e) {
  try {
    return ret(new QlFixedRateBondForward(alloc(new FixedRateBondForward(Date(valueDate), Date(maturityDate), (Position::Type)type, strike, settlementDays, (*arg(dayCounter)), (*arg(calendar)), (BusinessDayConvention)businessDayConvention, (*arg(fixedCouponBond)), qlNullableHandle(arg(discountCurve)), qlNullableHandle(arg(incomeDiscountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlFixedRateBondForward*>(e, er);
  }
}

double qlFixedRateBondForwardCleanForwardPrice(QlFixedRateBondForward* o, char **e) {
  try {
    return (*arg(o))->cleanForwardPrice();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlFixedRateBondForwardForwardPrice(QlFixedRateBondForward* o, char **e) {
  try {
    return (*arg(o))->forwardPrice();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
