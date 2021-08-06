#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/conundrumpricer.hpp>

#include "qlaux.h"
#include "qlCouponPricer.h"

using namespace QuantLib;

//QlFloatingRateCouponPricer *qlBlackIborCouponPricer(
//    QlOptionletVolatilityStructure *vol, char **e) {
//  try {
//    return ret(new QlFloatingRateCouponPricer(new BlackIborCouponPricer(
//	    Handle<OptionletVolatilityStructure>(*arg(vol)))));
//  } catch (std::exception& er) {
//    return handleException<QlFloatingRateCouponPricer *>(e, er);
//  }
//}

void qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p) {
  del(p);
}

//QlFloatingRateCouponPricer* qlAnalyticHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, char **e) {
//  try {
//    return ret(new QlFloatingRateCouponPricer(alloc(new AnalyticHaganPricer(Handle<SwaptionVolatilityStructure>(*arg(swaptionVol)), (GFunctionFactory::YieldCurveModel)modelOfYieldCurve, Handle<Quote>(*arg(meanReversion))))));
//  } catch (std::exception& er) {
//    return handleException<QlFloatingRateCouponPricer*>(e, er);
//  }
//}
//QlFloatingRateCouponPricer* qlNumericHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, double lowerLimit, double upperLimit, double precision, char **e) {
//  try {
//    return ret(new QlFloatingRateCouponPricer(alloc(new NumericHaganPricer(Handle<SwaptionVolatilityStructure>(*arg(swaptionVol)), (GFunctionFactory::YieldCurveModel)modelOfYieldCurve, Handle<Quote>(*arg(meanReversion)), lowerLimit, upperLimit, precision))));
//  } catch (std::exception& er) {
//    return handleException<QlFloatingRateCouponPricer*>(e, er);
//  }
//}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
