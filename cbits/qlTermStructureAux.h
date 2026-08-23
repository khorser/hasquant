#include <ql/termstructures/yield/all.hpp>
#include <ql/termstructures/globalbootstrap.hpp>
#include <ql/math/interpolations/all.hpp>
#include <ql/time/calendar.hpp>
#include <ql/termstructures/credit/interpolateddefaultdensitycurve.hpp>
#include <ql/termstructures/credit/interpolatedhazardratecurve.hpp>
#include <ql/termstructures/credit/interpolatedsurvivalprobabilitycurve.hpp>
#include <ql/termstructures/credit/piecewisedefaultcurve.hpp>
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>
#include <ql/termstructures/inflation/piecewisezeroinflationcurve.hpp>
#include <ql/termstructures/inflation/piecewiseyoyinflationcurve.hpp>
#include <ql/termstructures/inflation/interpolatedyoyinflationcurve.hpp>

// Every IterativeBootstrap constructor parameter (ql/termstructures/iterativebootstrap.hpp),
// as one flat POD so the piecewise-curve entry points don't grow nine more positional
// scalars each. Mirrors QuantLib-SWIG's _IterativeBootstrap struct + make_bootstrap<Curve>()
// shape (SWIG/piecewiseyieldcurve.i). accuracy/minValue/maxValue take qlNullReal() to mean
// "upstream's default", matching their Null<Real>() defaults; dontThrow is an int because
// this header is consumed from C.
struct QlIterativeBootstrapOpts {
  double accuracy, minValue, maxValue;
  unsigned maxAttempts;
  double maxFactor, minFactor;
  int dontThrow;
  unsigned dontThrowSteps, maxEvaluations;
};

QuantLib::YieldTermStructure *qlPiecewiseYieldCurveAux(
  const QuantLib::Date &date,
  const std::vector<QuantLib::ext::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  int trait, int interpolator, int approximator, int approximatorArg,
  const QlIterativeBootstrapOpts& bootstrapOpts);

// bootstrap: 0 = IterativeBootstrap (existing behaviour, default), 1 = GlobalBootstrap,
// wired up only for trait=Discount/interpolator=LogLinear and trait=SimpleZeroYield/
// interpolator=Linear (see qlTermStructureAux.cpp).
// This is a cbits-internal dispatch value, never exposed as a Haskell enum: the Haskell entry
// points (piecewiseYieldCurve'/piecewiseYieldCurveGlobalBootstrap'/
// piecewiseYieldCurveGlobalBootstrapSimpleZeroLinear') each hardcode their own literal from
// their own C shim, per CLAUDE.md's "dedicated constructor hardcodes the enum value" convention.
// accuracy and instrumentWeights are only used by the GlobalBootstrap branch (instrumentWeights
// empty means upstream's default, equal weighting); conversely bootstrapOpts is only used by the
// IterativeBootstrap branch.
QuantLib::YieldTermStructure *qlPiecewiseYieldCurveAux1(
  unsigned settl, const QuantLib::Calendar &cal,
  const std::vector<QuantLib::ext::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  int trait, int interpolator, int approximator, int approximatorArg,
  int bootstrap, double accuracy, const std::vector<double>& instrumentWeights,
  const QlIterativeBootstrapOpts& bootstrapOpts);

// PiecewiseYieldCurve<SimpleZeroYield, Linear, GlobalBootstrap> built via
// GlobalBootstrap's functor-callback constructor (additionalHelpers/additionalDates, with
// AdditionalErrors/AdditionalDates constructed internally -- see qlTermStructureAux.cpp).
// additionalDates.size() must equal additionalHelpers.size() - 2 (QL_REQUIRE'd inside).
QuantLib::YieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrapFullAux(
  unsigned settl, const QuantLib::Calendar &cal,
  const std::vector<QuantLib::ext::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  const std::vector<QuantLib::ext::shared_ptr<QuantLib::RateHelper> >& additionalHelpers,
  const std::vector<QuantLib::Date>& additionalDates,
  double accuracy);

QuantLib::YieldTermStructure *qlInterpolatedDiscountCurveAux(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& dfs,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  int interpolator, int approximator, int approximatorArg);

QuantLib::YieldTermStructure *qlInterpolatedForwardCurveAux(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& fwds,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  int interpolator, int approximator, int approximatorArg);

QuantLib::YieldTermStructure *qlInterpolatedZeroCurveAux(
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& yields,
  const QuantLib::DayCounter& dayCount,
  const QuantLib::Calendar& cal,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  int interpolator, int approximator, int approximatorArg);

QuantLib::YieldTermStructure *qlInterpolatedSpreadDiscountCurveAux(
  const QuantLib::Handle<QuantLib::YieldTermStructure>& baseCurve,
  const std::vector<QuantLib::Date>& dates,
  const std::vector<double>& dfs,
  int interpolator, int approximator, int approximatorArg);

QuantLib::YieldTermStructure *qlPiecewiseZeroSpreadedTermStructureAux(
  const QuantLib::Handle<QuantLib::YieldTermStructure>& baseCurve,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& spreads,
  const std::vector<QuantLib::Date>& dates,
  QuantLib::Compounding comp, QuantLib::Frequency freq,
  int interpolator, int approximator, int approximatorArg);

// some credit stuff
QuantLib::DefaultProbabilityTermStructure *qlInterpolatedDefaultDensityCurveAux(
            const std::vector<QuantLib::Date>& dates,
            const std::vector<double>& densities,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& calendar,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            int interpolator, int approximator, int approximatorArg);

QuantLib::DefaultProbabilityTermStructure *qlInterpolatedHazardRateCurveAux(
            const std::vector<QuantLib::Date>& dates,
            const std::vector<double>& hazardRates,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& cal,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            int interpolator, int approximator, int approximatorArg);

QuantLib::DefaultProbabilityTermStructure *qlInterpolatedSurvivalProbabilityCurveAux(
            const std::vector<QuantLib::Date>& dates,
            const std::vector<double>& probabilities,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& calendar,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            int interpolator, int approximator, int approximatorArg);

QuantLib::DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux(const QuantLib::Date &referenceDate,
    const std::vector<QuantLib::ext::shared_ptr<QuantLib::DefaultProbabilityHelper> >& instruments,
    QuantLib::DayCounter& dayCounter,
    const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps, const std::vector<QuantLib::Date>& jumpDates,
    int trait,int interpolator, int approximator, int approximatorArg);

QuantLib::DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux1(unsigned settlementDays,
    const QuantLib::Calendar& calendar,
    const std::vector<QuantLib::ext::shared_ptr<QuantLib::DefaultProbabilityHelper> >& instruments,
    QuantLib::DayCounter& dayCounter,
    const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps, const std::vector<QuantLib::Date>& jumpDates,
    int trait,int interpolator, int approximator, int approximatorArg);

QuantLib::ZeroInflationTermStructure *qlPiecewiseZeroInflationCurveAux(
    const QuantLib::Date &referenceDate,
    const QuantLib::Date &baseDate,
    QuantLib::Frequency frequency,
    const QuantLib::DayCounter& dayCounter,
    const std::vector<QuantLib::ext::shared_ptr<QuantLib::BootstrapHelper<QuantLib::ZeroInflationTermStructure> > >& instruments,
    int interpolator, int approximator, int approximatorArg);

QuantLib::YoYInflationTermStructure *qlPiecewiseYoYInflationCurveAux(
    const QuantLib::Date &referenceDate,
    const QuantLib::Date &baseDate,
    QuantLib::Rate baseYoYRate,
    QuantLib::Frequency frequency,
    const QuantLib::DayCounter& dayCounter,
    const std::vector<QuantLib::ext::shared_ptr<QuantLib::BootstrapHelper<QuantLib::YoYInflationTermStructure> > >& instruments,
    int interpolator, int approximator, int approximatorArg);

QuantLib::YoYInflationTermStructure *qlInterpolatedYoYInflationCurveAux(
    const QuantLib::Date &referenceDate,
    const std::vector<QuantLib::Date> &dates,
    const std::vector<QuantLib::Rate> &rates,
    QuantLib::Frequency frequency,
    const QuantLib::DayCounter& dayCounter,
    int interpolator, int approximator, int approximatorArg);

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
