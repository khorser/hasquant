#include <ql/termstructures/yield/all.hpp>

#include "ql.h"

using namespace QuantLib;

// Extract value for a quotes and put it into a new SimpleQuote
// to avoid problems with ownership when the Handle class destroys
// its Quote so Haskell finalizer is called on an invalid pointer.
// Anyway we are not going to use features of Observable/RelinkableHandle
class QuoteWrapper: public Quote {
public:
  static Handle<Quote> clone(Quote *q) {
    return Handle<Quote>(new QuoteWrapper(q), false);
  }

  ~QuoteWrapper() {
    TP2("Destroying quote wrapper", (void *)this);
  }

  Real value() const { return quote_.value(); }
  bool isValid() const { return quote_.isValid(); }
private:
  QuoteWrapper(Quote *q) : quote_(q->value()){
    TP2("Created quote wrapper", (void *)this);
  }

  const SimpleQuote quote_;
};

RateHelper *qlDepositRateHelper(Quote *quote, Period *period, unsigned fixDays,
  Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e)
{
  try {
    return alloc(new DepositRateHelper(
	    QuoteWrapper::clone(arg(quote)),
	    *arg(period),
	    fixDays,
	    *arg(calendar),
	    (BusinessDayConvention) conv,
	    eom,
	    *arg(dayCount)));
  } catch (std::exception& er) {
    return handleException<RateHelper *>(e, er);
  }
}

RateHelper *qlFixedRateBondHelper(Quote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e)
{
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);
    return alloc(new FixedRateBondHelper(
	    QuoteWrapper::clone(arg(quote)),
	    settlDays,
	    face,
	    *arg(sched),
	    cpns,
	    *arg(dayCount),
	    (BusinessDayConvention) conv,
	    redemption,
	    qlNullableDate(issue)));
  } catch (std::exception& er) {
    return handleException<RateHelper *>(e, er);
  }
}

void qlFreeRateHelper(RateHelper *helper) {
  del(helper);
}

typedef YieldTermStructure *(*piecewiseYieldCurve_t)(const Date& referenceDate,
  const std::vector<boost::shared_ptr<RateHelper> >& instruments,
  const DayCounter& dayCounter,
  const std::vector<Handle<Quote> >& jumps,
  const std::vector<Date>& jumpDates,
  Real accuracy);

template <class T, class I>
class YieldCurveCreator {
public:
  static YieldTermStructure *piecewiseYieldCurve(const Date& referenceDate,
    const std::vector<boost::shared_ptr<typename T::helper> >& instruments,
  const DayCounter& dayCounter,
  const std::vector<Handle<Quote> >& jumps,
  const std::vector<Date>& jumpDates,
  Real accuracy) {
    return new PiecewiseYieldCurve<T, I>(referenceDate, instruments,
	dayCounter, jumps, jumpDates, accuracy);
  }
};

YieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen, RateHelper **ratehelpers,
  DayCounter *dayCount, unsigned quoteLen, Quote **quotes, int *dates,
  double accuracy, char *trait, char *interpolator, char **e) {
  try {
    piecewiseYieldCurve_t c;
    if (!strcmp(trait, "Discount")) {
      if (!strcmp(interpolator, "Linear"))
	c = &YieldCurveCreator<Discount, Linear>::piecewiseYieldCurve;
    }
    std::vector<boost::shared_ptr<RateHelper> > instr;
    std::vector<Handle<Quote> > jumps;
    std::vector<Date> jumpDates;
    //for (unsigned i = 0; i < rateLen; ++i)
    //  instr.push_back(*ratehelpers[i]);
    for (unsigned i = 0; i < quoteLen; ++i) {
      jumps.push_back(QuoteWrapper::clone(arg(quotes[i])));
      jumpDates.push_back(Date(dates[i]));
    }
    return alloc(c(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy));
  } catch (std::exception& er) {
    return handleException<YieldTermStructure *>(e, er);
  }
}

void qlFreeYieldTermStructure(YieldTermStructure *ts) {
  del(ts);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
