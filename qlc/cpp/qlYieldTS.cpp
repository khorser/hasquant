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

QlFixedRateBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e) {
  try {
    std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlFixedRateBondHelper(new FixedRateBondHelper(
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
    return handleException<QlFixedRateBondHelper *>(e, er);
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

typedef QuantLib::YieldTermStructure *(*curveBuilder)(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& dfs,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  const char *interpolator);

QlYieldTermStructure *qlInterpolatedCurve(curveBuilder builder,
  unsigned rateLen, double *rates, int *rateDates,
  DayCounter *dayCount, Calendar *cal,
  unsigned quoteLen, QlQuote **quotes, int *dates, char *interpolator, char **e) {
  try {
    std::vector<Date> rds;
    std::vector<double> rs(rates, rates+rateLen);
    std::vector<Handle<Quote> > jumps;
    std::vector<Date> jumpDates;
    for (unsigned i = 0; i < rateLen; ++i)
      rds.push_back(Date(rateDates[i]));
    for (unsigned i = 0; i < quoteLen; ++i) {
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
      jumpDates.push_back(Date(dates[i]));
    }
    YieldTermStructure *ts = builder(rds,
      rs, *arg(dayCount), *arg(cal), jumps, jumpDates, interpolator);
    return ret(new QlYieldTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure *>(e, er);
  }
}

QlYieldTermStructure *qlInterpolatedDiscountCurve(unsigned dfsLen,
  double *dfs, int *dfsDates, DayCounter *dayCount, Calendar *cal,
  unsigned quoteLen, QlQuote **quotes, int *dates, char *interpolator, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedDiscountCurveAux, dfsLen, dfs, dfsDates,
    dayCount, cal, quoteLen, quotes, dates, interpolator, e);
}

QlYieldTermStructure *qlInterpolatedForwardCurve(unsigned fwdLen,
  double *fwds, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, int *dates, char *interpolator, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedForwardCurveAux, fwdLen, fwds, fwdDates,
    dayCount, cal, quoteLen, quotes, dates, interpolator, e);
}

QlYieldTermStructure *qlInterpolatedZeroCurve(unsigned yieldLen,
  double *yields, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, int *dates, char *interpolator, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedZeroCurveAux, yieldLen, yields, yieldDates,
    dayCount, cal, quoteLen, quotes, dates, interpolator, e);
}

QlYieldTermStructure *qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal,
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

// generated methods
QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {
    return ret(new QlYieldTermStructure(alloc(new FlatForward(Date(referenceDate), Handle<Quote>(*arg(forward)), (*arg(dayCounter)), (Compounding)compounding, (Frequency)frequency))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {
    return ret(new QlYieldTermStructure(alloc(new FlatForward(settlementDays, (*arg(calendar)), Handle<Quote>(*arg(forward)), (*arg(dayCounter)), (Compounding)compounding, (Frequency)frequency))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

// generated functions
InterestRate* qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
try {
    return ret(new InterestRate((*arg(o))->zeroRate(Date(d), (*arg(resultDayCounter)), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, Period* p, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(Date(d), (*arg(p)), (*arg(resultDayCounter)), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(Date(d1), Date(d2), (*arg(resultDayCounter)), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(t1, t2, (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->zeroRate(t, (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

double qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->discount(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlRateHelper* qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), monthsToStart, monthsToEnd, fixingDays, (*arg(calendar)), (BusinessDayConvention)convention, endOfMonth, (*arg(dayCounter))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}

void qlFreeFixedRateBondHelper(QlFixedRateBondHelper *o) { del(o); }
QlBondHelper* qlFixedRateBondHelperAsBondHelper(QlFixedRateBondHelper *o) { return ret(new QlBondHelper(*arg(o))); }

void qlFreeBondHelper(QlBondHelper *o) { del(o); }
QlRateHelper* qlBondHelperAsRateHelper(QlBondHelper *o) { return ret(new QlRateHelper(*arg(o))); }
	
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */