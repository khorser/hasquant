#include <ql/instruments/creditdefaultswap.hpp>
#include <ql/experimental/credit/cdsoption.hpp>
#include <ql/instruments/claim.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

#include "qlaux.h"
#include "qlCredit.h"

using namespace QuantLib;

void qlFreeCdsOption(QlCdsOption *o) { del(o); }
QlOption* qlCdsOptionAsOption(QlCdsOption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o) { del(o); }
QlInstrument* qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o) { return ret(new QlInstrument(*arg(o))); }

void qlFreeClaim(QlClaim *o) { del(o); }

QlClaim* qlFaceValueAccrualClaim(QlBond* referenceSecurity, char **e) {
  try {
    return ret(new QlClaim(alloc(new FaceValueAccrualClaim(*arg(referenceSecurity)))));
  } catch (std::exception& er) {
    return handleException<QlClaim*>(e, er);
  }
}

QlClaim* qlFaceValueClaim(char **e) {
  try {
    return ret(new QlClaim(alloc(new FaceValueClaim())));
  } catch (std::exception& er) {
    return handleException<QlClaim*>(e, er);
  }
}

QlCreditDefaultSwap* qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, char **e) {
  try {
    return ret(new QlCreditDefaultSwap(alloc(new CreditDefaultSwap((Protection::Side)side, notional, upfront, spread, *arg(schedule), (BusinessDayConvention)paymentConvention, *arg(dayCounter), settlesAccrual, paysAtDefaultTime, qlNullableDate(protectionStart), qlNullableDate(upfrontDate), (*arg(x11))))));
  } catch (std::exception& er) {
    return handleException<QlCreditDefaultSwap*>(e, er);
  }
}

QlCreditDefaultSwap* qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, char **e) {
  try {
    return ret(new QlCreditDefaultSwap(alloc(new CreditDefaultSwap((Protection::Side)side, notional, spread, *arg(schedule), (BusinessDayConvention)paymentConvention, *arg(dayCounter), settlesAccrual, paysAtDefaultTime, qlNullableDate(protectionStart), (*arg(x9))))));
  } catch (std::exception& er) {
    return handleException<QlCreditDefaultSwap*>(e, er);
  }
}

double qlCreditDefaultSwapFairSpread(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->fairSpread();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlCreditDefaultSwapConventionalSpread(QlCreditDefaultSwap* o, double conventionalRecovery, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, char **e) {
  try {
    return (*arg(o))->conventionalSpread(conventionalRecovery, Handle<YieldTermStructure>(*arg(discountCurve)), *arg(dayCounter));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCreditDefaultSwapCouponLegBPS(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->couponLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCreditDefaultSwapCouponLegNPV(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->couponLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlCreditDefaultSwapCoupons(QlCreditDefaultSwap* o, char **e) {
  try {
    return alloc(new Leg((*arg(o))->coupons()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlCreditDefaultSwapDefaultLegNPV(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->defaultLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCreditDefaultSwapFairUpfront(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->fairUpfront();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCreditDefaultSwapImpliedHazardRate(QlCreditDefaultSwap* o, double targetNPV, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, double recoveryRate, double accuracy, char **e) {
  try {
    return (*arg(o))->impliedHazardRate(targetNPV, Handle<YieldTermStructure>(*arg(discountCurve)), *arg(dayCounter), recoveryRate, accuracy);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCreditDefaultSwapUpfrontBPS(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->upfrontBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCreditDefaultSwapUpfrontNPV(QlCreditDefaultSwap* o, char **e) {
  try {
    return (*arg(o))->upfrontNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
