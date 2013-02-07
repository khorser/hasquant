#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>

#include "qlaux.h"
#include "qlYieldTSAux.h"

using namespace QuantLib;

QlRateHelper *qlDepositRateHelper(QlQuote *quote, Period *period, unsigned fixDays,
  Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e) {
  try {
    return ret(new QlRateHelper(new DepositRateHelper(
	    Handle<Quote>(*arg(quote)),
	    *arg(period),
	    fixDays,
	    *arg(calendar),
	    (BusinessDayConvention) conv,
	    eom,
	    *arg(dayCount))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper *>(e, er);
  }
}

QlRateHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e) {
  try {
    std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlRateHelper(new FixedRateBondHelper(
	    Handle<Quote>(*arg(quote)),
	    settlDays,
	    face,
	    *arg(sched),
	    cpns,
	    *arg(dayCount),
	    (BusinessDayConvention) conv,
	    redemption,
	    qlNullableDate(issue))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper *>(e, er);
  }
}

void qlFreeRateHelper(QlRateHelper *helper) {
  del(helper);
}

QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen,
  QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, int *dates, double accuracy, char *trait,
  char *interpolator, char **e) {
  try {
    std::vector<boost::shared_ptr<RateHelper> > instr;
    std::vector<Handle<Quote> > jumps;
    std::vector<Date> jumpDates;
    for (unsigned i = 0; i < rateLen; ++i)
      instr.push_back(*arg(ratehelpers[i]));
    for (unsigned i = 0; i < quoteLen; ++i) {
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
      jumpDates.push_back(Date(dates[i]));
    }
    YieldTermStructure *ts = qlPiecewiseYieldCurveAux(Date(date),
      instr, *arg(dayCount), jumps, jumpDates, accuracy, trait, interpolator);
    return ret(new QlYieldTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure *>(e, er);
  }
}

QlYieldTermStructure *DLLEXPORT qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal,
  unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, int *dates, double accuracy, char *trait,
  char *interpolator, char **e) {
  try {
    std::vector<boost::shared_ptr<RateHelper> > instr;
    std::vector<Handle<Quote> > jumps;
    std::vector<Date> jumpDates;
    for (unsigned i = 0; i < rateLen; ++i)
      instr.push_back(*arg(ratehelpers[i]));
    for (unsigned i = 0; i < quoteLen; ++i) {
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
      jumpDates.push_back(Date(dates[i]));
    }
    YieldTermStructure *ts = qlPiecewiseYieldCurveAux1(settl, *arg(cal),
      instr, *arg(dayCount), jumps, jumpDates, accuracy, trait, interpolator);
    return ret(new QlYieldTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure *>(e, er);
  }
}
void qlFreeYieldTermStructure(QlYieldTermStructure *ts) {
  del(ts);
}

double qlYieldTSDiscount(QlYieldTermStructure *ts, int date, int extrapolate, char **e) {
  try {
    return (*ts)->discount(Date(date), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlRateHelper *qlSwapRateHelper1(QlQuote *q, Period *t, Calendar *cal, int freq,
  int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, Period *fwdStart,
  QlYieldTermStructure *ts, char **e) {
  try {
    return ret(new QlRateHelper(new SwapRateHelper(Handle<Quote>(*arg(q)),
	    *arg(t), *arg(cal), (Frequency) freq, (BusinessDayConvention) conv,
	    *arg(dc), *arg(i), Handle<Quote>(*arg(s)), *arg(fwdStart),
	    ts ? Handle<YieldTermStructure>(*arg(ts)) : Handle<YieldTermStructure>())));
  } catch (std::exception& er) {
    return handleException<QlRateHelper *>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
