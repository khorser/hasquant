#include <ql/cashflows/couponpricer.hpp>

#include "ql.h"

using namespace QuantLib;

QlFloatingRateCouponPricer *qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e) {
  try {
    return ret(new QlFloatingRateCouponPricer(new BlackIborCouponPricer(
	    Handle<OptionletVolatilityStructure>(*arg(vol)))));
  } catch (std::exception& er) {
    return handleException<QlFloatingRateCouponPricer *>(e, er);
  }
}

void qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p) {
  del(p);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
