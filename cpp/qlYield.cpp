#include <ql/termstructures/yield/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlDepositRateHelper(void *quote, void *period, unsigned fixDays,
  void *calendar, int conv, int eom, void *dayCount, char **e)
{
  *e = 0;
  try {
    return TP("Allocated deposit rate helper",
      new DepositRateHelper(
	    Handle<Quote>(log_and_cast<Quote>("Pquote", quote), false),
	    *log_and_cast<Period>("Pperiod", period),
	    fixDays,
	    *log_and_cast<Calendar>("Pcalendar", calendar),
	    (BusinessDayConvention) conv,
	    eom,
	    *log_and_cast<DayCounter>("Pdaycounter", dayCount)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlFixedRateBondHelper(void *quote, unsigned settlDays, double face,
  void *sched, unsigned cLen, double *coupons, void *dayCount, int conv,
  double redemption, int issue, char **e)
{
  *e = 0;
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);
    return TP("Allocated deposit rate helper",
      new FixedRateBondHelper(
	    Handle<Quote>(log_and_cast<Quote>("Pquote", quote), false),
	    settlDays,
	    face,
	    *log_and_cast<Schedule>("Pschedule", sched),
	    cpns,
	    *log_and_cast<DayCounter>("Pdaycounter", dayCount),
	    (BusinessDayConvention) conv,
	    redemption,
	    qlNullableDate(issue)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeRateHelper(void *helper) {
  delete log_and_cast<RateHelper>("Pfreeing rate helper", helper);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
