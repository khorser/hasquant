#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>

#include "ql.h"

using namespace QuantLib;

#ifdef QLTRACK_ALLOCATIONS
// very minimal implementation to check that all objects are actually freed
class RateHelperWrapper: public RateHelper {
  public:
    RateHelperWrapper(RateHelper *helper)
	: RateHelper(helper->quote()), helper_(helper) {
      TP2("wrapped", helper); TP2("in", this);
    }
    ~RateHelperWrapper() { TP2("destroying underlying", helper_); delete helper_; }
    const Handle<Quote>& quote() const { return helper_->quote(); }
    Real impliedQuote() const { return helper_->impliedQuote(); }
    Real quoteError() const { return helper_->quoteError(); }
    void setTermStructure(YieldTermStructure* ts) { helper_->setTermStructure(ts); }
    Date earliestDate() const { return helper_->earliestDate(); }
    Date latestDate() const {return helper_->latestDate(); }
    void update() {helper_->update();}
    void accept(AcyclicVisitor& v) {helper_->accept(v);}
    void notifyObservers() {helper_->notifyObservers();}
  private:
    RateHelper *helper_;
};
template <class T>
RateHelper *wrap(T *h) {
  return new RateHelperWrapper(alloc(h));
}
#else
template <class T>
RateHelper *wrap(T *h) { return alloc(h); }
#endif

QlRateHelper *qlDepositRateHelper(QlQuote *quote, Period *period, unsigned fixDays,
  Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e)
{
  try {
    return ret(new QlRateHelper(wrap(new DepositRateHelper(
	    Handle<Quote>(*arg(quote)),
	    *arg(period),
	    fixDays,
	    *arg(calendar),
	    (BusinessDayConvention) conv,
	    eom,
	    *arg(dayCount)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper *>(e, er);
  }
}

QlRateHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e)
{
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);
    return ret(new QlRateHelper(wrap(new FixedRateBondHelper(
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
    return handleException<QlRateHelper *>(e, er);
  }
}

void qlFreeRateHelper(QlRateHelper *helper) {
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

QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen,
  QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, int *dates, double accuracy, char *trait,
  char *interpolator, char **e) {
  try {
    piecewiseYieldCurve_t c = 0;
    if (!strcmp(trait, "Discount")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	c = &YieldCurveCreator<Discount, BackwardFlat>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "ForwardFlat"))
	c = &YieldCurveCreator<Discount, ForwardFlat>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "Linear"))
        c = &YieldCurveCreator<Discount, Linear>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "LogLinear"))
        c = &YieldCurveCreator<Discount, LogLinear>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "CubicNaturalSpline"))
      //  c = &YieldCurveCreator<Discount, Cubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicCubicNaturalSpline"))
      //  c = &YieldCurveCreator<Discount, MonotonicCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "LogCubicNaturalSpline"))
      //  c = &YieldCurveCreator<Discount, LogCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicLogCubicNaturalSpline"))
      //  c = &YieldCurveCreator<Discount, MonotonicLogCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "KrugerCubic"))
      //  c = &YieldCurveCreator<Discount, KrugerCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "KrugerLogCubic"))
      //  c = &YieldCurveCreator<Discount, KrugerLogCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "FritschButlandCubic"))
      //  c = &YieldCurveCreator<Discount, FritschButlandCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "FritschButlandLogCubic"))
      //  c = &YieldCurveCreator<Discount, FritschButlandLogCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "Parabolic"))
      //  c = &YieldCurveCreator<Discount, Parabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicParabolic"))
      //  c = &YieldCurveCreator<Discount, MonotonicParabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "LogParabolic"))
      //  c = &YieldCurveCreator<Discount, LogParabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicLogParabolic"))
      //  c = &YieldCurveCreator<Discount, MonotonicLogParabolic>::piecewiseYieldCurve;
      else
	QL_FAIL("Unsupported interpolation");
    } else if (!strcmp(trait, "ForwardRate")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	c = &YieldCurveCreator<ForwardRate, BackwardFlat>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "ForwardFlat"))
	c = &YieldCurveCreator<ForwardRate, ForwardFlat>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "Linear"))
	c = &YieldCurveCreator<ForwardRate, Linear>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "LogLinear"))
	c = &YieldCurveCreator<ForwardRate, LogLinear>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "CubicNaturalSpline"))
      //  c = &YieldCurveCreator<ForwardRate, CubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicCubicNaturalSpline"))
      //  c = &YieldCurveCreator<ForwardRate, MonotonicCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "LogCubicNaturalSpline"))
      //  c = &YieldCurveCreator<ForwardRate, LogCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicLogCubicNaturalSpline"))
      //  c = &YieldCurveCreator<ForwardRate, MonotonicLogCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "KrugerCubic"))
      //  c = &YieldCurveCreator<ForwardRate, KrugerCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "KrugerLogCubic"))
      //  c = &YieldCurveCreator<ForwardRate, KrugerLogCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "FritschButlandCubic"))
      //  c = &YieldCurveCreator<ForwardRate, FritschButlandCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "FritschButlandLogCubic"))
      //  c = &YieldCurveCreator<ForwardRate, FritschButlandLogCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "Parabolic"))
      //  c = &YieldCurveCreator<ForwardRate, Parabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicParabolic"))
      //  c = &YieldCurveCreator<ForwardRate, MonotonicParabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "LogParabolic"))
      //  c = &YieldCurveCreator<ForwardRate, LogParabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicLogParabolic"))
      //  c = &YieldCurveCreator<ForwardRate, MonotonicLogParabolic>::piecewiseYieldCurve;
      else
	QL_FAIL("Unsupported interpolation");
    } else if (!strcmp(trait, "ZeroYield")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	c = &YieldCurveCreator<ZeroYield, BackwardFlat>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "ForwardFlat"))
	c = &YieldCurveCreator<ZeroYield, ForwardFlat>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "Linear"))
	c = &YieldCurveCreator<ZeroYield, Linear>::piecewiseYieldCurve;
      else if (!strcmp(interpolator, "LogLinear"))
	c = &YieldCurveCreator<ZeroYield, LogLinear>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "CubicNaturalSpline"))
      //  c = &YieldCurveCreator<ZeroYield, CubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicCubicNaturalSpline"))
      //  c = &YieldCurveCreator<ZeroYield, MonotonicCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "LogCubicNaturalSpline"))
      //  c = &YieldCurveCreator<ZeroYield, LogCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicLogCubicNaturalSpline"))
      //  c = &YieldCurveCreator<ZeroYield, MonotonicLogCubicNaturalSpline>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "KrugerCubic"))
      //  c = &YieldCurveCreator<ZeroYield, KrugerCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "KrugerLogCubic"))
      //  c = &YieldCurveCreator<ZeroYield, KrugerLogCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "FritschButlandCubic"))
      //  c = &YieldCurveCreator<ZeroYield, FritschButlandCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "FritschButlandLogCubic"))
      //  c = &YieldCurveCreator<ZeroYield, FritschButlandLogCubic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "Parabolic"))
      //  c = &YieldCurveCreator<ZeroYield, Parabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicParabolic"))
      //  c = &YieldCurveCreator<ZeroYield, MonotonicParabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "LogParabolic"))
      //  c = &YieldCurveCreator<ZeroYield, LogParabolic>::piecewiseYieldCurve;
      //else if (!strcmp(interpolator, "MonotonicLogParabolic"))
      //  c = &YieldCurveCreator<ZeroYield, MonotonicLogParabolic>::piecewiseYieldCurve;
      else
	QL_FAIL("Unsupported interpolation");
    } else
	QL_FAIL("Unsupported trait");

    std::vector<boost::shared_ptr<RateHelper> > instr;
    std::vector<Handle<Quote> > jumps;
    std::vector<Date> jumpDates;
    for (unsigned i = 0; i < rateLen; ++i)
      instr.push_back(*arg(ratehelpers[i]));
    for (unsigned i = 0; i < quoteLen; ++i) {
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
      jumpDates.push_back(Date(dates[i]));
    }
    return ret(new QlYieldTermStructure(
	  alloc(c(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy))));
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
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
