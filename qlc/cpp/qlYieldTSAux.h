#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>
#include <ql/time/calendar.hpp>
#include <ql/termstructures/credit/interpolateddefaultdensitycurve.hpp>
#include <ql/termstructures/credit/interpolatedhazardratecurve.hpp>
#include <ql/termstructures/credit/interpolatedsurvivalprobabilitycurve.hpp>

QuantLib::YieldTermStructure *qlPiecewiseYieldCurveAux(
  const QuantLib::Date &date,
  const std::vector<boost::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  double accuracy, const char *trait, const char *interpolator);

QuantLib::YieldTermStructure *qlPiecewiseYieldCurveAux1(
  unsigned settl, const QuantLib::Calendar &cal,
  const std::vector<boost::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  double accuracy, const char *trait, const char *interpolator);

QuantLib::YieldTermStructure *qlInterpolatedDiscountCurveAux(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& dfs,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  const char *interpolator);

QuantLib::YieldTermStructure *qlInterpolatedForwardCurveAux(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& fwds,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  const char *interpolator);

QuantLib::YieldTermStructure *qlInterpolatedZeroCurveAux(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& yields,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  const char *interpolator);

// some credit stuff
QuantLib::DefaultProbabilityTermStructure *qlInterpolatedDefaultDensityCurveAux(
            const std::vector<QuantLib::Date>& dates,
            const std::vector<double>& densities,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& calendar,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            const char *interpolator);

QuantLib::DefaultProbabilityTermStructure *qlInterpolatedHazardRateCurveAux(
            const std::vector<QuantLib::Date>& dates,
            const std::vector<double>& hazardRates,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& cal,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            const char *interpolator);

QuantLib::DefaultProbabilityTermStructure *qlInterpolatedSurvivalProbabilityCurveAux(
            const std::vector<QuantLib::Date>& dates,
            const std::vector<double>& probabilities,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& calendar,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            const char *interpolator);

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
