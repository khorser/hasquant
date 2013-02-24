#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>
#include <ql/version.hpp>

#include "qlaux.h"
#include "qlYieldTSAux.h"

using namespace QuantLib;

template <> class objClassName<FittedBondDiscountCurve::FittingMethod *> { public: static const char *name() { return "FittedBondDiscountCurve::FittingMethod"; } };

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

QlBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e) {
  try {
    std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlBondHelper(new FixedRateBondHelper(
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
    return handleException<QlBondHelper *>(e, er);
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

QlSwapRateHelper *qlSwapRateHelper1(QlQuote *q, Period *t, Calendar *cal, int freq,
  int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, Period *fwdStart,
  QlYieldTermStructure *ts, char **e) {
  try {
    return ret(new QlSwapRateHelper(new SwapRateHelper(Handle<Quote>(*arg(q)),
	    *arg(t), *arg(cal), (Frequency) freq, (BusinessDayConvention) conv,
	    *arg(dc), *arg(i), Handle<Quote>(*arg(s)), fwdStart ? *arg(fwdStart) : 0 * Days,
	    ts ? Handle<YieldTermStructure>(*arg(ts)) : Handle<YieldTermStructure>())));
  } catch (std::exception& er) {
    return handleException<QlSwapRateHelper *>(e, er);
  }
}

// generated methods
QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {
    return ret(new QlYieldTermStructure(alloc(new FlatForward(Date(referenceDate), Handle<Quote>(*arg(forward)), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {
    return ret(new QlYieldTermStructure(alloc(new FlatForward(settlementDays, *arg(calendar), Handle<Quote>(*arg(forward)), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

void qlFreeFittedBondDiscountCurveFittingMethod(FittedBondDiscountCurve::FittingMethod *o) { del(o); }

// generated functions
InterestRate* qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
try {
    return ret(new InterestRate((*arg(o))->zeroRate(Date(d), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, Period* p, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(Date(d), *arg(p), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(Date(d1), Date(d2), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
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
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), monthsToStart, monthsToEnd, fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}

void qlFreeBondHelper(QlBondHelper *o) { del(o); }
QlRateHelper* qlBondHelperAsRateHelper(QlBondHelper *o) { return ret(new QlRateHelper(*arg(o))); }

FittedBondDiscountCurve::FittingMethod* qlCubicBSplinesFitting(unsigned knotVectorLen, double *knotVector, int constrainAtZero, char **e) {
  try {
    return alloc(new CubicBSplinesFitting(std::vector<double>(knotVector, knotVector+knotVectorLen), constrainAtZero));
  } catch (std::exception& er) {
    return handleException<FittedBondDiscountCurve::FittingMethod*>(e, er);
  }
}

QuantLib::FittedBondDiscountCurve::FittingMethod* qlExponentialSplinesFitting(int constrainAtZero, char **e) {
  try {
    return alloc(new ExponentialSplinesFitting(constrainAtZero));
  } catch (std::exception& er) {
    return handleException<QuantLib::FittedBondDiscountCurve::FittingMethod*>(e, er);
  }
}

QuantLib::FittedBondDiscountCurve::FittingMethod* qlNelsonSiegelFitting(char **e) {
  try {
    return alloc(new NelsonSiegelFitting());
  } catch (std::exception& er) {
    return handleException<QuantLib::FittedBondDiscountCurve::FittingMethod*>(e, er);
  }
}

QuantLib::FittedBondDiscountCurve::FittingMethod* qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, char **e) {
  try {
    return alloc(new SimplePolynomialFitting(degree, constrainAtZero));
  } catch (std::exception& er) {
    return handleException<QuantLib::FittedBondDiscountCurve::FittingMethod*>(e, er);
  }
}

QuantLib::FittedBondDiscountCurve::FittingMethod* qlSvenssonFitting(char **e) {
  try {
    return alloc(new SvenssonFitting());
  } catch (std::exception& er) {
    return handleException<QuantLib::FittedBondDiscountCurve::FittingMethod*>(e, er);
  }
}

QlFittedBondDiscountCurve* qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e) {
  try {
    return ret(new QlFittedBondDiscountCurve(alloc(new FittedBondDiscountCurve(settlementDays, *arg(calendar), qlBuildVector(bonds, bondsLen), *arg(dayCounter), *arg(fittingMethod), accuracy, maxEvaluations, Array(guess, guess+guessLen), simplexLambda))));
  } catch (std::exception& er) {
    return handleException<QlFittedBondDiscountCurve*>(e, er);
  }
}

QlFittedBondDiscountCurve* qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e) {
  try {
    return ret(new QlFittedBondDiscountCurve(alloc(new FittedBondDiscountCurve(Date(referenceDate), qlBuildVector(bonds, bondsLen), *arg(dayCounter), *arg(fittingMethod), accuracy, maxEvaluations, Array(guess, guess+guessLen), simplexLambda))));
  } catch (std::exception& er) {
    return handleException<QlFittedBondDiscountCurve*>(e, er);
  }
}

void qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o) { del(o); }
QlYieldTermStructure* qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o) { return ret(new QlYieldTermStructure(*arg(o))); }

double qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve *o, char **e) {
  try {
    return (*arg(o))->fitResults().minimumCostValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

int qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve *o, char **e) {
  try {
    return (*arg(o))->fitResults().numberOfIterations();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeSwapRateHelper(QlSwapRateHelper *o) { del(o); }
QlRateHelper* qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o) { return ret(new QlRateHelper(*arg(o))); }

void qlFreeOISRateHelper(QlOISRateHelper *o) { del(o); }
QlRateHelper* qlOISRateHelperAsRateHelper(QlOISRateHelper *o) { return ret(new QlRateHelper(*arg(o))); }

QlBondHelper* qlBondHelper(QlQuote* cleanPrice, QlBond* bond, char **e) {
  try {
    return ret(new QlBondHelper(alloc(new BondHelper(Handle<Quote>(*arg(cleanPrice)), *arg(bond)))));
  } catch (std::exception& er) {
    return handleException<QlBondHelper*>(e, er);
  }
}
QlOISRateHelper* qlOISRateHelper(unsigned settlementDays, Period* tenor, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e) {
  try {
    return ret(new QlOISRateHelper(alloc(new OISRateHelper(settlementDays, *arg(tenor), Handle<Quote>(*arg(fixedRate)), *arg(overnightIndex)
#if QL_HEX_VERSION >= 0x010201f0
// version 1.2.1 or newer
              , qlNullableHandle(arg(discountingCurve))
#endif
              ))));
  } catch (std::exception& er) {
    return handleException<QlOISRateHelper*>(e, er);
  }
}
QlSwapRateHelper* qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, Period* fwdStart, QlYieldTermStructure* discountingCurve, char **e) {
  try {
    return ret(new QlSwapRateHelper(alloc(new SwapRateHelper(Handle<Quote>(*arg(rate)), *arg(swapIndex), qlNullableHandle(arg(spread)), *arg(fwdStart), qlNullableHandle(arg(discountingCurve))))));
  } catch (std::exception& er) {
    return handleException<QlSwapRateHelper*>(e, er);
  }
}

QlYieldTermStructure* qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new ForwardSpreadedTermStructure(Handle<YieldTermStructure>(*arg(x0)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlYieldTermStructure* qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, DayCounter* dc, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new ZeroSpreadedTermStructure(Handle<YieldTermStructure>(*arg(x0)), Handle<Quote>(*arg(spread)), (Compounding)comp, (Frequency)freq, *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlRateHelper* qlBMASwapRateHelper(QlQuote* liborFraction, Period* tenor, unsigned settlementDays, Calendar* calendar, Period* bmaPeriod, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new BMASwapRateHelper(Handle<Quote>(*arg(liborFraction)), *arg(tenor), settlementDays, *arg(calendar), *arg(bmaPeriod), (BusinessDayConvention)bmaConvention, *arg(bmaDayCount), *arg(bmaIndex), *arg(index)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlDatedOISRateHelper(int startDate, int endDate, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new DatedOISRateHelper(Date(startDate), Date(endDate), Handle<Quote>(*arg(fixedRate)), *arg(overnightIndex)
#if QL_HEX_VERSION >= 0x010201f0
// version 1.2.1 or newer
              , qlNullableHandle(arg(discountingCurve))
#endif
              ))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new DepositRateHelper(Handle<Quote>(*arg(rate)), *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), monthsToStart, *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFraRateHelper2(QlQuote* rate, Period* periodToStart, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), *arg(periodToStart), lengthInMonths, fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFraRateHelper3(QlQuote* rate, Period* periodToStart, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), *arg(periodToStart), *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FuturesRateHelper(Handle<Quote>(*arg(price)), Date(immStartDate), Date(endDate), *arg(dayCounter), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FuturesRateHelper(Handle<Quote>(*arg(price)), Date(immDate), *arg(iborIndex), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FuturesRateHelper(Handle<Quote>(*arg(price)), Date(immDate), lengthInMonths, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
double qlRateHelperImpliedQuote(QlRateHelper* o, char **e) {
  try {
    return (*arg(o))->impliedQuote();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlBond* qlBondHelperBond(QlBondHelper* o, char **e) {
  try {
    return ret(new QlBond((*arg(o))->bond()));
  } catch (std::exception& er) {
    return handleException<QlBond*>(e, er);
  }
}
QlOvernightIndexedSwap* qlOISRateHelperSwap(QlOISRateHelper* o, char **e) {
  try {
    return ret(new QlOvernightIndexedSwap((*arg(o))->swap()));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndexedSwap*>(e, er);
  }
}
QlVanillaSwap* qlSwapRateHelperSwap(QlSwapRateHelper* o, char **e) {
  try {
    return ret(new QlVanillaSwap((*arg(o))->swap()));
  } catch (std::exception& er) {
    return handleException<QlVanillaSwap*>(e, er);
  }
}
int qlTermStructureReferenceDate(QlTermStructure* o, char **e) {
  try {
    return (*arg(o))->referenceDate().serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeTermStructure(QlTermStructure *o) { del(o); }
QlTermStructure* qlYieldTermStructureAsTermStructure(QlYieldTermStructure *o) { return ret(new QlTermStructure(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
