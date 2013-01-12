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
  Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e) {
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
  double redemption, int issue, char **e) {
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
    YieldTermStructure *ts = 0;
    if (!strcmp(trait, "Discount")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	ts = new PiecewiseYieldCurve<Discount, BackwardFlat>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	ts = new PiecewiseYieldCurve<Discount, ForwardFlat>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	ts = new PiecewiseYieldCurve<Discount, Linear>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	ts = new PiecewiseYieldCurve<Discount, LogLinear>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	ts = new PiecewiseYieldCurve<Discount, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	ts = new PiecewiseYieldCurve<Discount, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	ts = new PiecewiseYieldCurve<Discount, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	ts = new PiecewiseYieldCurve<Discount, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	ts = new PiecewiseYieldCurve<Discount, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	ts = new PiecewiseYieldCurve<Discount, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	ts = new PiecewiseYieldCurve<Discount, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	ts = new PiecewiseYieldCurve<Discount, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	ts = new PiecewiseYieldCurve<Discount, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	ts = new PiecewiseYieldCurve<Discount, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	ts = new PiecewiseYieldCurve<Discount, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	ts = new PiecewiseYieldCurve<Discount, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    } else if (!strcmp(trait, "ForwardRate")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	ts = new PiecewiseYieldCurve<ForwardRate, BackwardFlat>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	ts = new PiecewiseYieldCurve<ForwardRate, ForwardFlat>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	ts = new PiecewiseYieldCurve<ForwardRate, Linear>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogLinear>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	ts = new PiecewiseYieldCurve<ForwardRate, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	ts = new PiecewiseYieldCurve<ForwardRate, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	ts = new PiecewiseYieldCurve<ForwardRate, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	ts = new PiecewiseYieldCurve<ForwardRate, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	ts = new PiecewiseYieldCurve<ForwardRate, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	ts = new PiecewiseYieldCurve<ForwardRate, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	ts = new PiecewiseYieldCurve<ForwardRate, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    } else if (!strcmp(trait, "ZeroYield")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	ts = new PiecewiseYieldCurve<ZeroYield, BackwardFlat>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	ts = new PiecewiseYieldCurve<ZeroYield, ForwardFlat>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	ts = new PiecewiseYieldCurve<ZeroYield, Linear>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogLinear>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	ts = new PiecewiseYieldCurve<ZeroYield, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	ts = new PiecewiseYieldCurve<ZeroYield, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	ts = new PiecewiseYieldCurve<ZeroYield, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	ts = new PiecewiseYieldCurve<ZeroYield, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	ts = new PiecewiseYieldCurve<ZeroYield, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	ts = new PiecewiseYieldCurve<ZeroYield, Cubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	ts = new PiecewiseYieldCurve<ZeroYield, LogCubic>(Date(date), instr, *arg(dayCount), jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    }
    else
	QL_FAIL("Unsupported trait" << trait);

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
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
