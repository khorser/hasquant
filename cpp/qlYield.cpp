#include <ql/termstructures/yield/all.hpp>

#include "ql.h"

using namespace QuantLib;

// Extract value for a quotes and put it into a new SimpleQuote
// to avoid problems with ownership when the Handle class destroys
// its Quote so Haskell finalizer is called on an invalid pointer.
// Anyway we are not going to use features of Observable/RelinkableHandle
class QuoteWrapper: public Quote {
public:
  QuoteWrapper(Quote *q) : quote_(q->value()){
    TPP("Created quote wrapper", this);
  }
  ~QuoteWrapper() {
    TPP("Destroying quote wrapper", this);
  }
  Handle<Quote> createHandle() {
    return Handle<Quote>(this, false);
  }
  Real value() const { return quote_.value(); }
  bool isValid() const { return quote_.isValid(); }
private:
  const SimpleQuote quote_;
};

void *qlDepositRateHelper(void *quote, void *period, unsigned fixDays,
  void *calendar, int conv, int eom, void *dayCount, char **e)
{
  *e = 0;
  try {
    return TP("Allocated deposit rate helper",
      new DepositRateHelper(
	    (new QuoteWrapper(log_and_cast<Quote>("Pquote", quote)))->createHandle(),
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
	    (new QuoteWrapper(log_and_cast<Quote>("Pquote", quote)))->createHandle(),
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
