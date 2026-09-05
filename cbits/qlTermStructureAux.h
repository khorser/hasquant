#include <ql/termstructures/yield/all.hpp>
#include <ql/termstructures/globalbootstrap.hpp>
#include <ql/termstructures/localbootstrap.hpp>
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
#include <ql/termstructures/volatility/equityfx/blackvariancecurve.hpp>
#include <ql/termstructures/volatility/equityfx/blackvariancesurface.hpp>
#include <ql/termstructures/volatility/zabrsmilesection.hpp>
#include <ql/experimental/inflation/cpicapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/yoycapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/interpolatedyoyoptionletstripper.hpp>
#include <ql/experimental/inflation/kinterpolatedyoyoptionletvolatilitysurface.hpp>
#include <ql/pricingengines/inflation/inflationcapfloorengines.hpp>
#include <ql/experimental/credit/constantlosslatentmodel.hpp>
#include <ql/experimental/math/gaussiancopulapolicy.hpp>
#include <ql/experimental/math/tcopulapolicy.hpp>

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
//
// The Haskell-visible choice of bootstrapper (IterativeBootstrap/GlobalBootstrap/
// LocalBootstrap) is unified on the Haskell side instead, by QuantLib/TermStructure/Yield.chs's
// `Bootstrap` ADT and its `piecewiseYieldCurve2'` entry point: it pattern-matches on `Bootstrap`
// and calls straight through to whichever already-existing C shim wrapper matches (this
// function's qlPiecewiseYieldCurveFull1 wrapper for `Iterative`, qlPiecewiseYieldCurveGlobalBootstrap1/2/3
// for the `Global*` constructors, qlPiecewiseYieldCurveLocalBootstrap1 for `Local`), rather than
// threading a fourth case through this C-side `bootstrap` int. So this int still only ever takes
// 0 or 1, and still isn't the place a third (Local) or unified value would go.
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

// PiecewiseYieldCurve<Trait, ConvexMonotone, LocalBootstrap>, dispatched over
// ForwardRate/ZeroYield/SimpleZeroYield -- Discount is rejected (QL_FAIL) at trait=Discount:
// verified numerically incorrect with this bootstrapper/interpolator pair, see
// qlTermStructureAux.cpp. ConvexMonotone is the only upstream interpolator LocalBootstrap works
// with -- see qlTermStructureAux.cpp for why -- so it's implicit, not a Haskell-visible choice;
// quadraticity/monotonicity/convexForcePositive are its own constructor params, distinct from
// localisation/forcePositive/accuracy (LocalBootstrap's own).
QuantLib::YieldTermStructure *qlPiecewiseYieldCurveLocalBootstrapAux1(
  unsigned settl, const QuantLib::Calendar &cal,
  const std::vector<QuantLib::ext::shared_ptr<QuantLib::RateHelper> >& instr,
  const QuantLib::DayCounter& dayCount,
  const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
  const std::vector<QuantLib::Date>& jumpDates,
  int trait, QuantLib::Size localisation, bool forcePositive, double accuracy,
  double quadraticity, double monotonicity, bool convexForcePositive);

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
    int trait,int interpolator, int approximator, int approximatorArg,
    const QlIterativeBootstrapOpts& bootstrapOpts);

QuantLib::DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux1(unsigned settlementDays,
    const QuantLib::Calendar& calendar,
    const std::vector<QuantLib::ext::shared_ptr<QuantLib::DefaultProbabilityHelper> >& instruments,
    QuantLib::DayCounter& dayCounter,
    const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps, const std::vector<QuantLib::Date>& jumpDates,
    int trait,int interpolator, int approximator, int approximatorArg,
    const QlIterativeBootstrapOpts& bootstrapOpts);

// ConstantLossModel<CopulaPolicy>, only the Handle<Quote>/nVariables (one-factor) constructor.
// tOrders empty -> GaussianCopulaPolicy (initTraits is a bare int upstream, unused here);
// tOrders non-empty -> TCopulaPolicy, whose initTraits::tOrders takes exactly these degrees of
// freedom (one per latent factor, plus one for the idiosyncratic factor -- for this one-factor
// constructor that's always 2 elements; TCopulaPolicy's own constructor QL_REQUIREs the exact
// count). See qlTermStructureAux.cpp for the dispatcher itself.
QuantLib::DefaultLossModel* qlConstantLossModelAux(const QuantLib::Handle<QuantLib::Quote>& mktCorrel,
    const std::vector<QuantLib::Real>& recoveries,
    QuantLib::LatentModelIntegrationType::LatentModelIntegrationType integralType,
    QuantLib::Size nVariables, const std::vector<QuantLib::Integer>& tOrders);

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

// Everything below is here for the same reason as the curves above -- it instantiates a QuantLib
// class template once per Interpolation (and, for the two price surfaces, per 2-D interpolator
// too), which is the expensive kind of code to have sitting in the 2000-line qlTermStructure.cpp
// TU. The `int interpolator*`/`approximator`/`approximatorArg` dispatch that used to live at each
// call site there is absorbed into these entry points, so the caller passes the raw enum values
// straight through and never names an interpolator type.

// BlackVarianceCurve/BlackVarianceSurface configure their interpolation after construction rather
// than through a template parameter, so these are setters rather than factories; the
// instantiation cost is the same, one member-template body per Interpolation.
void qlSetBlackVarianceCurveInterpolationAux(QuantLib::BlackVarianceCurve *o,
    int interpolator, int approximator, int approximatorArg);
void qlSetBlackVarianceSurfaceInterpolationAux(QuantLib::BlackVarianceSurface *o, int interpolator);

QuantLib::CPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurfaceAux(
    double nominal, double baseRate, const QuantLib::Period &observationLag, const QuantLib::Calendar &cal,
    QuantLib::BusinessDayConvention bdc, const QuantLib::DayCounter &dc,
    const QuantLib::ext::shared_ptr<QuantLib::ZeroInflationIndex> &zii,
    QuantLib::CPI::InterpolationType interpolationType,
    const QuantLib::Handle<QuantLib::YieldTermStructure> &yts,
    const std::vector<QuantLib::Rate> &cStrikes, const std::vector<QuantLib::Rate> &fStrikes,
    const std::vector<QuantLib::Period> &cfMaturities,
    const QuantLib::Matrix &cPrice, const QuantLib::Matrix &fPrice,
    int interpolator2D);

// Two interpolator axes: the 2-D cap/floor price grid, and the 1-D per-maturity curve.
QuantLib::YoYCapFloorTermPriceSurface *qlYoYCapFloorTermPriceSurfaceAux(
    QuantLib::Natural fixingDays, const QuantLib::Period &yyLag,
    const QuantLib::ext::shared_ptr<QuantLib::YoYInflationIndex> &yii,
    QuantLib::CPI::InterpolationType interpolation,
    const QuantLib::Handle<QuantLib::YieldTermStructure> &nominal,
    const QuantLib::DayCounter &dc, const QuantLib::Calendar &cal, QuantLib::BusinessDayConvention bdc,
    const std::vector<QuantLib::Rate> &cStrikes, const std::vector<QuantLib::Rate> &fStrikes,
    const std::vector<QuantLib::Period> &cfMaturities,
    const QuantLib::Matrix &cPrice, const QuantLib::Matrix &fPrice,
    int interpolator2D, int interpolator1D, int approximator, int approximatorArg);

// Builds the InterpolatedYoYOptionletStripper and the KInterpolatedYoYOptionletVolatilitySurface
// over it, both on the same Interpolator1D. LogCubic is rejected -- see qlTermStructureAux.cpp.
QuantLib::YoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceAux(
    unsigned settlementDays, const QuantLib::Calendar &cal, QuantLib::BusinessDayConvention bdc,
    const QuantLib::DayCounter &dc,
    const QuantLib::ext::shared_ptr<QuantLib::YoYCapFloorTermPriceSurface> &capFloorPrices,
    const QuantLib::ext::shared_ptr<QuantLib::YoYInflationCapFloorEngine> &engine, double slope,
    int interpolator1D, int approximator, int approximatorArg);

// ZabrSmileSection<Evaluation> is templated over the evaluation-tag axis (4 type-only tags, no
// runtime state) -- dispatched here rather than in qlTermStructure.cpp, same rule as every other
// "runtime enum selects a template argument" case. Returns the generic SmileSection base, same
// shape as qlSviSmileSection/qlNoArbSabrSmileSection (no dedicated leaf: ZabrSmileSection's only
// extra getter, model(), isn't exposed -- see qlTermStructure.cpp).
QuantLib::SmileSection *qlZabrSmileSectionAux(
    int evaluation, double timeToExpiry, double forward,
    const std::vector<QuantLib::Real> &params, const std::vector<QuantLib::Real> &moneyness,
    QuantLib::Size fdRefinement);
QuantLib::SmileSection *qlZabrSmileSectionAux1(
    int evaluation, const QuantLib::Date &d, double forward,
    const std::vector<QuantLib::Real> &params, const QuantLib::DayCounter &dc,
    const std::vector<QuantLib::Real> &moneyness, QuantLib::Size fdRefinement);

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
