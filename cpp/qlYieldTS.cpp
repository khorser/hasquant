#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>

#include "ql.h"
#include "qlYieldTSAux.h"

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
	    Handle<Quote> qq(*arg(quote));
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
    YieldTermStructure *ts = qlPiecewiseYieldCurveAux(Date(date),
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
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
