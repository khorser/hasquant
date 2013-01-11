#include <ql/termstructures/yield/all.hpp>

#include "ql.h"

using namespace QuantLib;

qlRateHelper *qlDepositRateHelper(qlQuote *quote, Period *period, unsigned fixDays,
  Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e)
{
  try {
    return ret(new qlRateHelper(alloc(new DepositRateHelper(
	    Handle<Quote>(*arg(quote)),
	    *arg(period),
	    fixDays,
	    *arg(calendar),
	    (BusinessDayConvention) conv,
	    eom,
	    *arg(dayCount)))));
  } catch (std::exception& er) {
    return handleException<qlRateHelper *>(e, er);
  }
}

qlRateHelper *qlFixedRateBondHelper(qlQuote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e)
{
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);
    return ret(new qlRateHelper(alloc(new FixedRateBondHelper(
	    Handle<Quote>(*arg(quote)),
	    settlDays,
	    face,
	    *arg(sched),
	    cpns,
	    *arg(dayCount),
	    (BusinessDayConvention) conv,
	    redemption,
	    qlNullableDate(issue)))));
  } catch (std::exception& er) {
    return handleException<qlRateHelper *>(e, er);
  }
}

void qlFreeRateHelper(qlRateHelper *helper) {
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

YieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen,
  qlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  qlQuote **quotes, int *dates, double accuracy, char *trait,
  char *interpolator, char **e) {
  try {
    piecewiseYieldCurve_t c = 0;
    if (!strcmp(trait, "Discount")) {
      if (!strcmp(interpolator, "LogLinear"))
        c = &YieldCurveCreator<Discount, LogLinear>::piecewiseYieldCurve;
    }
    std::vector<boost::shared_ptr<RateHelper> > instr;
    std::vector<Handle<Quote> > jumps;
    std::vector<Date> jumpDates;
    for (unsigned i = 0; i < rateLen; ++i)
      instr.push_back(*arg(ratehelpers[i]));
    for (unsigned i = 0; i < quoteLen; ++i) {
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
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
