#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>

QuantLib::YieldTermStructure *qlPiecewiseYieldCurveAux(
  const QuantLib::Date &date,
  const std::vector<boost::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date> jumpDates,
  double accuracy, const char *trait, const char *interpolator);

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
