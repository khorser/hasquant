#include <ql/shared_ptr.hpp>
#include <type_traits>
using QuantLib::ext::shared_ptr;
#include "qlTermStructureAux.h"
namespace hasquant {
#include "qlEnumObjects.h"
}

using namespace QuantLib;

// Shared piecewise-curve dispatcher; the entry points differ only in leading arguments.

// Use the curve's bootstrap type to avoid invalid template instantiation.
template <class Curve>
typename Curve::bootstrap_type makeIterativeBootstrap(const QlIterativeBootstrapOpts& b) {
  return typename Curve::bootstrap_type(b.accuracy, b.minValue, b.maxValue, b.maxAttempts,
      b.maxFactor, b.minFactor, b.dontThrow != 0, b.dontThrowSteps, b.maxEvaluations);
}

// Cubic and LogCubic take the same constructor arguments, hence one helper over both.
template <class C>
C makeCubic(int approximator, int approximatorArg) {
  switch (approximator) {
  case hasquant::NaturalSpline:
    return C(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0);
  case hasquant::Kruger: return C(CubicInterpolation::Kruger);
  case hasquant::FritschButland: return C(CubicInterpolation::FritschButland);
  case hasquant::Parabolic: return C(CubicInterpolation::Parabolic, approximatorArg);
  default: QL_FAIL("Unsupported approximation " << approximator);
  }
}

// Type-only tag, for the dispatchers whose selected type is a trait (no runtime state to carry,
// unlike an interpolator instance). `make(Tag<QuantLib::Discount>())` reaches the type inside the
// callable as `typename decltype(t)::type`.
template <class T> struct Tag { using type = T; };

// The single interpolator x approximation dispatch for this whole file. `make` is a generic
// lambda; it is called once, with a *constructed* interpolator instance of the selected type, and
// spells its own `new SomeCurve<decltype(i)>(..., i)`. Before this there were ~18 hand-duplicated
// copies of this two-level switch, one per curve template, each repeating its constructor
// argument list six to ten times.
//
// The result type is an explicit leading template argument
// (`dispatchInterpolation<YieldTermStructure*>(...)`), not a trailing
// `-> decltype(make(Linear()))`. That is load-bearing: a trailing return type is an *unevaluated*
// operand, so the probe call it names becomes the first instantiation of the caller's lambda for
// that interpolator -- and clang then emits the curve's constructor but never marks its vtable
// used, leaving the destructor and its thunks undefined. It surfaces as a link/dlopen failure for
// one arm only (whichever type the probe named), which reads like a QuantLib packaging problem
// rather than a bug here. Keep the explicit `Ret`; the same rule applies to every dispatcher in
// cbits/qlPricingEngineAux.cpp.
template <class Ret, class F>
Ret dispatchInterpolation(int interpolator, int approximator, int approximatorArg, F&& make) {
  switch (interpolator) {
  case hasquant::BackwardFlat: return make(BackwardFlat());
  case hasquant::ForwardFlat: return make(ForwardFlat());
  case hasquant::Linear: return make(Linear());
  case hasquant::LogLinear: return make(LogLinear());
  case hasquant::Cubic: return make(makeCubic<Cubic>(approximator, approximatorArg));
  case hasquant::LogCubic: return make(makeCubic<LogCubic>(approximator, approximatorArg));
  // hasquant::Abcd (InterpolationType's 7th case) has no arm: QuantLib's Abcd interpolation
  // isn't usable as a PiecewiseYieldCurve interpolator. Pre-existing gap, preserved.
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

// Args is the entry-point-specific prefix (a Date, or settlementDays + Calendar) followed by
// instruments/dayCounter/jumps/jumpDates; every PiecewiseYieldCurve constructor ends with the
// interpolator and the bootstrapper, so those two go last in the lambda below.
template <class... Args>
YieldTermStructure *dispatchTrait(int trait, int interpolator, int approximator, int approximatorArg,
    const QlIterativeBootstrapOpts& b, Args&&... args) {
  auto makeForTrait = [&](auto t) -> YieldTermStructure* {
    using Trait = typename decltype(t)::type;
    return dispatchInterpolation<YieldTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
          using CurveType = PiecewiseYieldCurve<Trait, decltype(i)>;
          return new CurveType(std::forward<Args>(args)..., i, makeIterativeBootstrap<CurveType>(b));
        });
  };
  switch (trait) {
  case hasquant::Discount: return makeForTrait(Tag<QuantLib::Discount>());
  case hasquant::ForwardRate: return makeForTrait(Tag<QuantLib::ForwardRate>());
  case hasquant::ZeroYield: return makeForTrait(Tag<QuantLib::ZeroYield>());
  case hasquant::SimpleZeroYield: return makeForTrait(Tag<QuantLib::SimpleZeroYield>());
  default:
    QL_FAIL("Unsupported trait" << trait);
  }
}

// Upstream QuantLib-SWIG's canned-functor GlobalBootstrap construction (SWIG/piecewiseyieldcurve.i
// :186-282's AdditionalErrors/AdditionalDates), confirmed to compile against both clang and
// g++-16 by an earlier standalone spike (see README's # TODO). AdditionalErrors is a fixed linear-
// interpolation formula between the first and last additional helper's implied quote -- not a
// user-supplied callback -- so it needs no Haskell-side marshalling; it and AdditionalDates are
// trait-independent (Traits::helper is BootstrapHelper<YieldTermStructure> == RateHelper for
// every trait this file dispatches, per ratehelpers.hpp/bootstraptraits.hpp), so they live here
// once rather than duplicated per trait x interpolator combination that ends up using them.

class AdditionalErrors {
  std::vector<shared_ptr<RateHelper> > additionalHelpers_;
public:
  AdditionalErrors(const std::vector<shared_ptr<RateHelper> >& additionalHelpers)
  : additionalHelpers_(additionalHelpers) {}
  Array operator()() const {
    Array errors(additionalHelpers_.size() - 2);
    Real a = additionalHelpers_.front()->impliedQuote();
    Real b = additionalHelpers_.back()->impliedQuote();
    for (Size k = 0; k < errors.size(); ++k) {
      errors[k] = (static_cast<Real>(errors.size()-k) * a + static_cast<Real>(1+k) * b) / static_cast<Real>(errors.size()+1)
          - additionalHelpers_.at(1+k)->impliedQuote();
    }
    return errors;
  }
};

class AdditionalDates {
  std::vector<Date> additionalDates_;
public:
  AdditionalDates(const std::vector<Date>& additionalDates) : additionalDates_(additionalDates) {}
  std::vector<Date> operator()() const { return additionalDates_; }
};

// Spelled CurveType::bootstrap_type(accuracy), not GlobalBootstrap<CurveType>(accuracy):
// GlobalBootstrap overrides pure-virtual methods from MultiCurveBootstrapContributor, and
// [temp.inst] instantiates a class's virtual member function bodies together with the class
// itself. Naming GlobalBootstrap<CurveType> directly starts instantiating *that* specialization
// first, which then needs CurveType complete -- but CurveType is simultaneously mid-instantiation
// because of this very argument (its bootstrap_ field has type GlobalBootstrap<CurveType>),
// producing a hard "incomplete type" error (reproduced independently with clang and g++-16).
// Naming CurveType (via ::bootstrap_type) first instead makes CurveType the outer instantiation,
// so GlobalBootstrap<CurveType>'s virtual bodies are only instantiated once CurveType is
// complete. Don't "simplify" this back to the direct spelling -- it silently reintroduces the
// compile failure. Templated over Trait/Interp (same shape makeCurveLocalBootstrap already uses
// for LocalBootstrap below) so each trait/interpolator combination is one dispatch arm instead of
// a hand-duplicated block.
template <class Trait, class Interp>
YieldTermStructure *makeGlobalBootstrapCurve(unsigned settl, const Calendar &cal,
    const std::vector<shared_ptr<RateHelper> >& instr, const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    const Interp& interp, double accuracy, const std::vector<double>& instrumentWeights) {
  using CurveType = PiecewiseYieldCurve<Trait, Interp, QuantLib::GlobalBootstrap>;
  return new CurveType(settl, cal, instr, dayCount, jumps, jumpDates, interp,
      typename CurveType::bootstrap_type(accuracy, nullptr, nullptr, instrumentWeights));
}

// GlobalBootstrap is wired up only for the combinations concrete use cases have asked for --
// Discount/LogLinear (the multi-curve relinkable-handle test), SimpleZeroYield/Linear (upstream
// QuantLib-SWIG's GlobalLinearSimpleZeroCurve), and ForwardRate/Linear and ZeroYield/Linear (the
// other two IterativeBootstrap traits paired with the cheapest interpolator, see issue #15) --
// not the full trait x interpolator matrix; CLAUDE.md is explicit about not building dispatch for
// hypothetical future combinations.
YieldTermStructure *dispatchTraitGlobalBootstrap(int trait, int interpolator, unsigned settl,
    const Calendar &cal, const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount, const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates, double accuracy, const std::vector<double>& instrumentWeights) {
  switch (trait) {
  case hasquant::Discount:
    QL_REQUIRE(interpolator == hasquant::LogLinear,
        "GlobalBootstrap-based PiecewiseYieldCurve construction with trait=Discount only "
        "supports interpolator=LogLinear (got interpolator " << interpolator << ")");
    return makeGlobalBootstrapCurve<QuantLib::Discount>(settl, cal, instr, dayCount, jumps,
        jumpDates, QuantLib::LogLinear(), accuracy, instrumentWeights);
  case hasquant::SimpleZeroYield:
    QL_REQUIRE(interpolator == hasquant::Linear,
        "GlobalBootstrap-based PiecewiseYieldCurve construction with trait=SimpleZeroYield "
        "only supports interpolator=Linear (got interpolator " << interpolator << ")");
    return makeGlobalBootstrapCurve<QuantLib::SimpleZeroYield>(settl, cal, instr, dayCount, jumps,
        jumpDates, QuantLib::Linear(), accuracy, instrumentWeights);
  case hasquant::ForwardRate:
    QL_REQUIRE(interpolator == hasquant::Linear,
        "GlobalBootstrap-based PiecewiseYieldCurve construction with trait=ForwardRate only "
        "supports interpolator=Linear (got interpolator " << interpolator << ")");
    return makeGlobalBootstrapCurve<QuantLib::ForwardRate>(settl, cal, instr, dayCount, jumps,
        jumpDates, QuantLib::Linear(), accuracy, instrumentWeights);
  case hasquant::ZeroYield:
    QL_REQUIRE(interpolator == hasquant::Linear,
        "GlobalBootstrap-based PiecewiseYieldCurve construction with trait=ZeroYield only "
        "supports interpolator=Linear (got interpolator " << interpolator << ")");
    return makeGlobalBootstrapCurve<QuantLib::ZeroYield>(settl, cal, instr, dayCount, jumps,
        jumpDates, QuantLib::Linear(), accuracy, instrumentWeights);
  default:
    QL_FAIL("GlobalBootstrap-based PiecewiseYieldCurve construction is only supported for "
        "trait=Discount/interpolator=LogLinear, trait=ForwardRate/interpolator=Linear, "
        "trait=ZeroYield/interpolator=Linear, or trait=SimpleZeroYield/interpolator=Linear "
        "(got trait " << trait << ", interpolator " << interpolator << ")");
  }
}

// PiecewiseYieldCurve<SimpleZeroYield, Linear, GlobalBootstrap> built via GlobalBootstrap's
// functor-callback constructor, taking additionalHelpers/additionalDates and constructing
// AdditionalErrors/AdditionalDates internally -- the same GlobalLinearSimpleZeroCurve combination
// QuantLib-SWIG demonstrates. A separate entry point from qlPiecewiseYieldCurveAux1's
// bootstrap==1 branch (not a widened version of it): that branch's plain accuracy/
// instrumentWeights constructor and this functor constructor are different GlobalBootstrap
// overloads entirely, not more parameters on the same one.
YieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrapFullAux(unsigned settl, const Calendar &cal,
    const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    const std::vector<shared_ptr<RateHelper> >& additionalHelpers,
    const std::vector<Date>& additionalDates,
    double accuracy) {
  // AdditionalErrors returns additionalHelpers.size()-2 equations; GlobalBootstrap requires
  // #equations == #unknowns, so additionalDates must supply exactly that many extra unknowns
  // (confirmed empirically by an earlier standalone spike, which crashed at runtime with
  // QuantLib's own "less functions than available variables" until the two were matched).
  // Surfaced here with a message in terms of the Haskell-visible arguments, not left to that
  // internal QuantLib error.
  QL_REQUIRE(additionalHelpers.size() >= 2,
      "GlobalBootstrap's canned AdditionalErrors formula needs at least 2 additionalHelpers "
      "(got " << additionalHelpers.size() << ")");
  QL_REQUIRE(additionalDates.size() == additionalHelpers.size() - 2,
      "additionalDates must have exactly additionalHelpers.size() - 2 entries for "
      "GlobalBootstrap's canned AdditionalErrors formula (got " << additionalHelpers.size() <<
      " additionalHelpers and " << additionalDates.size() << " additionalDates, expected " <<
      (additionalHelpers.size() - 2) << " additionalDates)");
  using CurveType = PiecewiseYieldCurve<QuantLib::SimpleZeroYield, QuantLib::Linear, QuantLib::GlobalBootstrap>;
  // CurveType::bootstrap_type(...) naming order -- see the comment on the plain-constructor
  // GlobalBootstrap branch in qlPiecewiseYieldCurveAux1, same [temp.inst] reason.
  return new CurveType(settl, cal, instr, dayCount, jumps, jumpDates, QuantLib::Linear(),
      CurveType::bootstrap_type(additionalHelpers, AdditionalDates(additionalDates),
          AdditionalErrors(additionalHelpers), accuracy, nullptr, nullptr));
}

// LocalBootstrap requires its Interpolator to provide localInterpolate(), which upstream only
// ConvexMonotoneInterpolation (ql/math/interpolations/convexmonotoneinterpolation.hpp) supplies
// -- Linear/LogLinear/Cubic/LogCubic/BackwardFlat/ForwardFlat do not. So unlike dispatchTrait
// (interpolator-generic), this dispatches trait only, with the interpolator fixed to
// ConvexMonotone.
//
// Discount is deliberately excluded, unlike dispatchTrait's IterativeBootstrap dispatch (which
// includes it): a standalone raw-C++ reproduction against this same installed libQuantLib (no
// hasquant involved) showed PiecewiseYieldCurve<Discount, ConvexMonotone, LocalBootstrap>
// returning wildly wrong discount factors (>1, growing with maturity) for ordinary deposit-rate
// inputs, reproducibly across both a flat 3% quote and varied per-tenor quotes, and independent
// of LocalBootstrap's accuracy parameter -- not a hasquant marshalling bug, a genuine numerical
// incompatibility between Discount's discount-factor-space guess/updateGuess and ConvexMonotone's
// localInterpolate. ForwardRate, ZeroYield and SimpleZeroYield all reproduce the expected
// 1/(1+rate*tau) values correctly under the same fixture. This matches upstream's own
// test-suite/piecewiseyieldcurve.cpp, whose only LocalBootstrap+ConvexMonotone coverage
// (testLocalBootstrapConsistency) uses ForwardRate, never Discount.
template <class Trait, class... Args>
YieldTermStructure *makeCurveLocalBootstrap(const ConvexMonotone& interp, Size localisation,
    bool forcePositive, double accuracy, Args&&... args) {
  using CurveType = PiecewiseYieldCurve<Trait, QuantLib::ConvexMonotone, QuantLib::LocalBootstrap>;
  // CurveType::bootstrap_type(...) naming order -- see the comment on the GlobalBootstrap branch
  // in qlPiecewiseYieldCurveAux1, same [temp.inst] reasoning applied defensively here too.
  return new CurveType(std::forward<Args>(args)..., interp,
      typename CurveType::bootstrap_type(localisation, forcePositive, accuracy));
}

template <class... Args>
YieldTermStructure *dispatchTraitLocalBootstrap(int trait, const ConvexMonotone& interp,
    Size localisation, bool forcePositive, double accuracy, Args&&... args) {
  switch (trait) {
  case hasquant::ForwardRate:
    return makeCurveLocalBootstrap<QuantLib::ForwardRate>(interp, localisation, forcePositive, accuracy, std::forward<Args>(args)...);
  case hasquant::ZeroYield:
    return makeCurveLocalBootstrap<QuantLib::ZeroYield>(interp, localisation, forcePositive, accuracy, std::forward<Args>(args)...);
  case hasquant::SimpleZeroYield:
    return makeCurveLocalBootstrap<QuantLib::SimpleZeroYield>(interp, localisation, forcePositive, accuracy, std::forward<Args>(args)...);
  case hasquant::Discount:
    QL_FAIL("LocalBootstrap-based PiecewiseYieldCurve construction with trait=Discount produces "
        "numerically incorrect results with ConvexMonotone (verified independently against "
        "upstream QuantLib) -- use ForwardRate, ZeroYield or SimpleZeroYield instead");
  default:
    QL_FAIL("Unsupported trait" << trait);
  }
}

YieldTermStructure *qlPiecewiseYieldCurveLocalBootstrapAux1(unsigned settl, const Calendar &cal,
    const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, Size localisation, bool forcePositive, double accuracy,
    double quadraticity, double monotonicity, bool convexForcePositive) {
  return dispatchTraitLocalBootstrap(trait, ConvexMonotone(quadraticity, monotonicity, convexForcePositive),
      localisation, forcePositive, accuracy, settl, cal, instr, dayCount, jumps, jumpDates);
}

// extracted some template-heavy stuff into a separate file to speed up the compilation
YieldTermStructure *qlPiecewiseYieldCurveAux(const Date &date,
    const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg,
    const QlIterativeBootstrapOpts& bootstrapOpts) {
  return dispatchTrait(trait, interpolator, approximator, approximatorArg, bootstrapOpts,
      date, instr, dayCount, jumps, jumpDates);
}

YieldTermStructure *qlPiecewiseYieldCurveAux1(unsigned settl, const Calendar &cal,
    const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg,
    int bootstrap, double accuracy, const std::vector<double>& instrumentWeights,
    const QlIterativeBootstrapOpts& bootstrapOpts) {
  if (bootstrap == 1) {
    return dispatchTraitGlobalBootstrap(trait, interpolator, settl, cal, instr, dayCount, jumps,
        jumpDates, accuracy, instrumentWeights);
  }
  return dispatchTrait(trait, interpolator, approximator, approximatorArg, bootstrapOpts,
      settl, cal, instr, dayCount, jumps, jumpDates);
}


// Every function below is one `dispatchInterpolation` call whose generic lambda spells the
// curve's own constructor once, with `decltype(i)` as the Interpolator template argument. The
// curve's base-class pointer is the dispatcher's explicit `Ret` argument, so each of the six arms
// deduces its own concrete pointer type and converts on the way out.
//
// The interpolator instance is now passed explicitly in every arm, including the four that used
// to rely on the constructor's `const Interpolator& i = Interpolator()` default argument -- a
// default-constructed BackwardFlat/ForwardFlat/Linear/LogLinear is exactly what that default
// produced. Where a constructor has parameters *between* the data and the interpolator
// (seasonality/accuracy on the inflation curves), those are likewise spelled out with the same
// values upstream defaults them to, checked against the headers.

YieldTermStructure *qlInterpolatedDiscountCurveAux(
    const std::vector<Date> &dfDates,
    const std::vector<double>& dfs,
    const DayCounter& dayCount,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  // NB: this function's LogCubic/NaturalSpline arm used to hardcode `false` for
  // CubicInterpolation's `monotonic` flag where every sibling passes approximatorArg -- i.e. it
  // silently ignored the Bool the Haskell-side `LogCubic (NaturalSpline monotonic)` carries.
  // Routing through makeCubic<LogCubic> honours it, matching every other curve here.
  return dispatchInterpolation<YieldTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedDiscountCurve<decltype(i)>(dfDates, dfs, dayCount, cal, jumps, jumpDates, i);
      });
}

YieldTermStructure *qlInterpolatedForwardCurveAux(
    const std::vector<Date> &fwdDates,
    const std::vector<double>& fwds,
    const DayCounter& dayCount,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<YieldTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedForwardCurve<decltype(i)>(fwdDates, fwds, dayCount, cal, jumps, jumpDates, i);
      });
}

YieldTermStructure *qlInterpolatedZeroCurveAux(
    const std::vector<Date> &yDates,
    const std::vector<double>& yields,
    const DayCounter& dayCount,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<YieldTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedZeroCurve<decltype(i)>(yDates, yields, dayCount, cal, jumps, jumpDates, i);
      });
}

YieldTermStructure *qlInterpolatedSpreadDiscountCurveAux(
    const Handle<YieldTermStructure>& baseCurve,
    const std::vector<Date>& dates,
    const std::vector<double>& dfs,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<YieldTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedSpreadDiscountCurve<decltype(i)>(baseCurve, dates, dfs, i);
      });
}

YieldTermStructure *qlPiecewiseZeroSpreadedTermStructureAux(
    const Handle<YieldTermStructure>& baseCurve,
    const std::vector<Handle<Quote> >& spreads,
    const std::vector<Date>& dates,
    Compounding comp, Frequency freq,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<YieldTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedPiecewiseZeroSpreadedTermStructure<decltype(i)>(baseCurve, spreads, dates, comp, freq, i);
      });
}

// some credit stuff
DefaultProbabilityTermStructure *qlInterpolatedDefaultDensityCurveAux(
    const std::vector<Date>& dates,
    const std::vector<double>& densities,
    const DayCounter& dayCounter,
    const Calendar& calendar,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<DefaultProbabilityTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedDefaultDensityCurve<decltype(i)>(dates, densities, dayCounter, calendar, jumps, jumpDates, i);
      });
}

DefaultProbabilityTermStructure *qlInterpolatedHazardRateCurveAux(
    const std::vector<Date>& dates,
    const std::vector<double>& hazardRates,
    const DayCounter& dayCounter,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<DefaultProbabilityTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedHazardRateCurve<decltype(i)>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, i);
      });
}

DefaultProbabilityTermStructure *qlInterpolatedSurvivalProbabilityCurveAux(
    const std::vector<Date>& dates,
    const std::vector<double>& probabilities,
    const DayCounter& dayCounter,
    const Calendar& calendar,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<DefaultProbabilityTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedSurvivalProbabilityCurve<decltype(i)>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, i);
      });
}

// PiecewiseDefaultCurve's own trait axis (HazardRate/DefaultDensity/SurvivalProbability) --
// entirely separate from the yield curve's Discount/ForwardRate/ZeroYield/SimpleZeroYield above,
// hence its own dispatcher. Both entry points below differ only in their leading constructor
// arguments (a Date, or settlementDays + Calendar), so the nested trait x interpolator dispatch
// is written once and the difference lives in the lambda each passes.
template <class Ret, class F>
Ret dispatchDefaultTrait(int trait, F&& make) {
  switch (trait) {
  case hasquant::HazardRate: return make(Tag<QuantLib::HazardRate>());
  case hasquant::DefaultDensity: return make(Tag<QuantLib::DefaultDensity>());
  case hasquant::SurvivalProbability: return make(Tag<QuantLib::SurvivalProbability>());
  default: QL_FAIL("Unsupported trait" << trait);
  }
}

// The trait x interpolator product, with the entry-point-specific constructor prefix forwarded
// as a variadic pack -- same shape as dispatchTrait's for PiecewiseYieldCurve above.
template <class... Args>
DefaultProbabilityTermStructure *makePiecewiseDefaultCurve(int trait, int interpolator,
    int approximator, int approximatorArg, Args&&... args) {
  return dispatchDefaultTrait<DefaultProbabilityTermStructure*>(trait, [&](auto t) {
    using Trait = typename decltype(t)::type;
    return dispatchInterpolation<DefaultProbabilityTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
          return new PiecewiseDefaultCurve<Trait, decltype(i)>(std::forward<Args>(args)..., i);
        });
  });
}

DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux(const Date &referenceDate,
    const std::vector<shared_ptr<DefaultProbabilityHelper> >& instruments,
    DayCounter& dayCounter,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg) {
  return makePiecewiseDefaultCurve(trait, interpolator, approximator, approximatorArg,
      referenceDate, instruments, dayCounter, jumps, jumpDates);
}

DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux1(unsigned settlementDays,
    const Calendar& calendar,
    const std::vector<shared_ptr<DefaultProbabilityHelper> >& instruments,
    DayCounter& dayCounter,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg) {
  return makePiecewiseDefaultCurve(trait, interpolator, approximator, approximatorArg,
      settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
}

// Selects ConstantLossModel's Gaussian or Student-T copula policy.
template <class Ret, class F>
Ret dispatchCopulaPolicy(bool useStudent, F&& make) {
  if (useStudent) return make(Tag<TCopulaPolicy>());
  return make(Tag<GaussianCopulaPolicy>());
}

// The policies use different init-trait types; initialize Student-T orders only on its branch.
DefaultLossModel* qlConstantLossModelAux(const Handle<Quote>& mktCorrel,
    const std::vector<Real>& recoveries,
    LatentModelIntegrationType::LatentModelIntegrationType integralType,
    Size nVariables, const std::vector<Integer>& tOrders) {
  return dispatchCopulaPolicy<DefaultLossModel*>(!tOrders.empty(), [&](auto tag) {
    using Policy = typename decltype(tag)::type;
    typename Policy::initTraits ini{};
    if constexpr (std::is_same_v<Policy, TCopulaPolicy>) ini.tOrders = tOrders;
    return new ConstantLossModel<Policy>(mktCorrel, recoveries, integralType, nVariables, ini);
  });
}

// The `{}` seasonality and the 1.0e-14 / 1.0e-12 accuracy below are upstream's own default
// arguments, spelled explicitly only because the interpolator sits after them
// (piecewisezeroinflationcurve.hpp / piecewiseyoyinflationcurve.hpp).
ZeroInflationTermStructure *qlPiecewiseZeroInflationCurveAux(
    const Date &referenceDate,
    const Date &baseDate,
    Frequency frequency,
    const DayCounter& dayCounter,
    const std::vector<shared_ptr<BootstrapHelper<ZeroInflationTermStructure> > >& instruments,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<ZeroInflationTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new PiecewiseZeroInflationCurve<decltype(i)>(referenceDate, baseDate, frequency,
            dayCounter, instruments, {}, 1.0e-14, i);
      });
}

YoYInflationTermStructure *qlPiecewiseYoYInflationCurveAux(
    const Date &referenceDate,
    const Date &baseDate,
    Rate baseYoYRate,
    Frequency frequency,
    const DayCounter& dayCounter,
    const std::vector<shared_ptr<BootstrapHelper<YoYInflationTermStructure> > >& instruments,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<YoYInflationTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new PiecewiseYoYInflationCurve<decltype(i)>(referenceDate, baseDate, baseYoYRate,
            frequency, dayCounter, instruments, {}, 1.0e-12, i);
      });
}

YoYInflationTermStructure *qlInterpolatedYoYInflationCurveAux(
    const Date &referenceDate,
    const std::vector<Date> &dates,
    const std::vector<Rate> &rates,
    Frequency frequency,
    const DayCounter& dayCounter,
    int interpolator, int approximator, int approximatorArg) {
  return dispatchInterpolation<YoYInflationTermStructure*>(interpolator, approximator, approximatorArg,
[&](auto i) {
        return new InterpolatedYoYInflationCurve<decltype(i)>(referenceDate, dates, rates,
            frequency, dayCounter, {}, i);
      });
}

// ---------------------------------------------------------------------------------------------
// Moved here from qlTermStructure.cpp (see qlTermStructureAux.h): these instantiate a QuantLib
// class template per Interpolation, which is exactly the kind of work this TU exists to hold.
// Each takes the raw interpolator/approximator enum ints, so the caller over there no longer
// names an interpolator type at all.
// ---------------------------------------------------------------------------------------------

// Interpolation set after construction rather than through a template parameter -- these two
// classes take a member template instead. Same one-body-per-Interpolation cost, so the same
// dispatchInterpolation shape applies, with Ret = void.
void qlSetBlackVarianceCurveInterpolationAux(BlackVarianceCurve *o,
    int interpolator, int approximator, int approximatorArg) {
  dispatchInterpolation<void>(interpolator, approximator, approximatorArg,
      [&](auto i) { o->setInterpolation<decltype(i)>(i); });
}

// 2-D counterpart, for BlackVarianceSurface. setInterpolation is a member *template* taking a
// default-constructed Interpolator, so there is no approximator or approximatorArg to thread and
// no Interpolation2D object to marshal -- just a two-case switch. Same set QuantLib-SWIG exposes
// (SWIG/volatilities.i).
void qlSetBlackVarianceSurfaceInterpolationAux(BlackVarianceSurface *o, int interpolator) {
  switch (interpolator) {
  case hasquant::Bilinear: o->setInterpolation<QuantLib::Bilinear>(); break;
  case hasquant::Bicubic: o->setInterpolation<QuantLib::Bicubic>(); break;
  default: QL_FAIL("Unsupported 2-D interpolation " << interpolator);
  }
}

// The 2-D (cap/floor price grid) interpolator axis, shared by both price surfaces below.
// Bilinear/Bicubic are the only two QuantLib offers here, and neither carries constructor
// arguments, so this is a plain Tag dispatch with no approximator to thread.
template <class Ret, class F>
Ret dispatchInterpolation2D(int interpolator2D, F&& make) {
  switch (interpolator2D) {
  case hasquant::Bilinear: return make(Tag<QuantLib::Bilinear>());
  case hasquant::Bicubic: return make(Tag<QuantLib::Bicubic>());
  default: QL_FAIL("Unsupported 2-D interpolation " << interpolator2D);
  }
}

CPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurfaceAux(
    double nominal, double baseRate, const Period &observationLag, const Calendar &cal,
    BusinessDayConvention bdc, const DayCounter &dc, const shared_ptr<ZeroInflationIndex> &zii,
    CPI::InterpolationType interpolationType, const Handle<YieldTermStructure> &yts,
    const std::vector<Rate> &cStrikes, const std::vector<Rate> &fStrikes,
    const std::vector<Period> &cfMaturities, const Matrix &cPrice, const Matrix &fPrice,
    int interpolator2D) {
  return dispatchInterpolation2D<CPICapFloorTermPriceSurface*>(interpolator2D, [&](auto i2d) {
    return new InterpolatedCPICapFloorTermPriceSurface<typename decltype(i2d)::type>(nominal, baseRate,
        observationLag, cal, bdc, dc, zii, interpolationType, yts, cStrikes, fStrikes, cfMaturities,
        cPrice, fPrice);
  });
}

// Both interpolator axes at once: the 2-D price grid and the inner 1-D per-maturity curve. The
// four non-cubic 1-D arms used to omit the trailing `I2D(), interp` pair and rely on the
// constructor's defaults; passing them explicitly is the same default-constructed value.
YoYCapFloorTermPriceSurface *qlYoYCapFloorTermPriceSurfaceAux(
    Natural fixingDays, const Period &yyLag, const shared_ptr<YoYInflationIndex> &yii,
    CPI::InterpolationType interpolation, const Handle<YieldTermStructure> &nominal,
    const DayCounter &dc, const Calendar &cal, BusinessDayConvention bdc,
    const std::vector<Rate> &cStrikes, const std::vector<Rate> &fStrikes,
    const std::vector<Period> &cfMaturities, const Matrix &cPrice, const Matrix &fPrice,
    int interpolator2D, int interpolator1D, int approximator, int approximatorArg) {
  return dispatchInterpolation2D<YoYCapFloorTermPriceSurface*>(interpolator2D, [&](auto i2d) {
    using I2D = typename decltype(i2d)::type;
    return dispatchInterpolation<YoYCapFloorTermPriceSurface*>(interpolator1D, approximator, approximatorArg,
[&](auto i) {
          return new InterpolatedYoYCapFloorTermPriceSurface<I2D, decltype(i)>(fixingDays, yyLag, yii,
              interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
              I2D(), i);
        });
  });
}

// The stripper's own internal PiecewiseYoYOptionletVolatilityCurve<Interpolator1D> always
// default-constructs its interpolator (interpolatedyoyoptionletstripper.hpp's initialize()
// never passes one) -- only the surface's own K-direction interpolator (factory1D_) takes an
// explicit instance, so only that one needs the Cubic/LogCubic approximator-specific
// construction.
template <class Interpolator1D>
YoYOptionletVolatilitySurface *makeKInterpolatedYoYOptionletVolatilitySurface(
    unsigned settlementDays, const Calendar &cal, BusinessDayConvention bdc, const DayCounter &dc,
    const shared_ptr<YoYCapFloorTermPriceSurface> &capFloorPrices,
    const shared_ptr<YoYInflationCapFloorEngine> &engine, double slope,
    const Interpolator1D &interpolator) {
  return new KInterpolatedYoYOptionletVolatilitySurface<Interpolator1D>(
      settlementDays, cal, bdc, dc, capFloorPrices->observationLag(), capFloorPrices, engine,
      shared_ptr<YoYOptionletStripper>(new InterpolatedYoYOptionletStripper<Interpolator1D>()),
      slope, interpolator);
}

// Not written in terms of dispatchInterpolation, unlike everything else in this file: that
// dispatcher has a LogCubic arm and this one must not.
YoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceAux(
    unsigned settlementDays, const Calendar &cal, BusinessDayConvention bdc, const DayCounter &dc,
    const shared_ptr<YoYCapFloorTermPriceSurface> &capFloorPrices,
    const shared_ptr<YoYInflationCapFloorEngine> &engine, double slope,
    int interpolator1D, int approximator, int approximatorArg) {
  auto make = [&](auto i) -> YoYOptionletVolatilitySurface* {
    return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc,
        capFloorPrices, engine, slope, i);
  };
  switch (interpolator1D) {
  case hasquant::BackwardFlat: return make(BackwardFlat());
  case hasquant::ForwardFlat: return make(ForwardFlat());
  case hasquant::Linear: return make(Linear());
  case hasquant::LogLinear: return make(LogLinear());
  case hasquant::Cubic: return make(makeCubic<Cubic>(approximator, approximatorArg));
  // LogCubic is deliberately not instantiated here: unlike Cubic, QuantLib's LogCubic
  // (ql/math/interpolations/loginterpolation.hpp) has no default constructor -- its
  // DerivativeApprox parameter is required, no default value. InterpolatedYoYOptionletStripper's
  // own initialize() (interpolatedyoyoptionletstripper.hpp) builds a
  // PiecewiseYoYOptionletVolatilityCurve<Interpolator1D> via that curve's own default-arg'd
  // Interpolator1D ctor parameter -- and since that's a virtual member, instantiating
  // InterpolatedYoYOptionletStripper<LogCubic> at all (even just to hold it in a shared_ptr,
  // never calling initialize) forces the compiler to instantiate initialize() to build the
  // vtable, which fails to compile: "no matching constructor for initialization of
  // QuantLib::LogCubic". This is a real upstream restriction, not a hasquant gap -- confirmed
  // by reading loginterpolation.hpp's LogCubic ctor (no default 'da' argument, unlike Cubic's).
  case hasquant::LogCubic:
    QL_FAIL("LogCubic cannot back InterpolatedYoYOptionletStripper/KInterpolatedYoYOptionletVolatilitySurface -- "
            "see the comment above this case");
  default:
    QL_FAIL("Unsupported interpolation " << interpolator1D);
  }
}

// ZabrSmileSection<Evaluation> is templated over the evaluation-tag axis: four type-only C++ tags
// (no runtime state to carry), same Tag<T> idiom as dispatchTrait above. The explicit leading Ret
// template argument is load-bearing here too -- see the comment above dispatchInterpolation.
template <class Ret, class F>
Ret dispatchZabrEvaluation(int evaluation, F&& make) {
  switch (evaluation) {
  case hasquant::ZabrShortMaturityLognormal: return make(Tag<ZabrShortMaturityLognormal>());
  case hasquant::ZabrShortMaturityNormal: return make(Tag<ZabrShortMaturityNormal>());
  case hasquant::ZabrLocalVolatility: return make(Tag<ZabrLocalVolatility>());
  case hasquant::ZabrFullFd: return make(Tag<ZabrFullFd>());
  default:
    QL_FAIL("Unsupported ZABR evaluation " << evaluation);
  }
}

SmileSection *qlZabrSmileSectionAux(int evaluation, double timeToExpiry, double forward,
    const std::vector<Real> &params, const std::vector<Real> &moneyness, Size fdRefinement) {
  return dispatchZabrEvaluation<SmileSection*>(evaluation, [&](auto tag) {
    using Evaluation = typename decltype(tag)::type;
    return new ZabrSmileSection<Evaluation>(timeToExpiry, forward, params, moneyness, fdRefinement);
  });
}

SmileSection *qlZabrSmileSectionAux1(int evaluation, const Date &d, double forward,
    const std::vector<Real> &params, const DayCounter &dc, const std::vector<Real> &moneyness,
    Size fdRefinement) {
  return dispatchZabrEvaluation<SmileSection*>(evaluation, [&](auto tag) {
    using Evaluation = typename decltype(tag)::type;
    return new ZabrSmileSection<Evaluation>(d, forward, params, dc, moneyness, fdRefinement);
  });
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
