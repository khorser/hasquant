#include <ql/shared_ptr.hpp>
using QuantLib::ext::shared_ptr;
#include "qlTermStructureAux.h"
namespace hasquant {
#include "qlEnumObjects.h"
}

using namespace QuantLib;

// The trait x interpolator x approximation dispatch below is shared by both piecewise-curve
// entry points (fixed reference date, and settlementDays + calendar): the two differ only in
// the leading constructor arguments, forwarded here as a variadic pack. It used to be two
// copies of the same ~150-line nested switch, one per entry point, with each of the ~30 arms
// spelling out its own `new PiecewiseYieldCurve<Trait, Interp>(...)` argument list -- which is
// why adding a bootstrap argument prompted the factoring. Shape borrowed from QuantLib-SWIG's
// make_bootstrap<Curve>() (SWIG/piecewiseyieldcurve.i).

// Spelled CurveType::bootstrap_type, not IterativeBootstrap<CurveType>, for the same
// [temp.inst] reason spelled out on the GlobalBootstrap branch further down -- see that
// comment before changing either.
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

// Args is the entry-point-specific prefix (a Date, or settlementDays + Calendar) followed by
// instruments/dayCounter/jumps/jumpDates; every PiecewiseYieldCurve constructor ends with the
// interpolator and the bootstrapper, so those two go last here.
template <class Trait, class Interp, class... Args>
YieldTermStructure *makeCurve(const QlIterativeBootstrapOpts& b, const Interp& i, Args&&... args) {
  using CurveType = PiecewiseYieldCurve<Trait, Interp>;
  return new CurveType(std::forward<Args>(args)..., i, makeIterativeBootstrap<CurveType>(b));
}

template <class Trait, class... Args>
YieldTermStructure *dispatchInterpolator(int interpolator, int approximator, int approximatorArg,
    const QlIterativeBootstrapOpts& b, Args&&... args) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return makeCurve<Trait>(b, BackwardFlat(), std::forward<Args>(args)...);
  case hasquant::ForwardFlat:
    return makeCurve<Trait>(b, ForwardFlat(), std::forward<Args>(args)...);
  case hasquant::Linear:
    return makeCurve<Trait>(b, Linear(), std::forward<Args>(args)...);
  case hasquant::LogLinear:
    return makeCurve<Trait>(b, LogLinear(), std::forward<Args>(args)...);
  case hasquant::Cubic:
    return makeCurve<Trait>(b, makeCubic<Cubic>(approximator, approximatorArg), std::forward<Args>(args)...);
  case hasquant::LogCubic:
    return makeCurve<Trait>(b, makeCubic<LogCubic>(approximator, approximatorArg), std::forward<Args>(args)...);
  // hasquant::Abcd (InterpolationType's 7th case) has no arm: QuantLib's Abcd interpolation
  // isn't usable as a PiecewiseYieldCurve interpolator. Pre-existing gap, preserved.
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

template <class... Args>
YieldTermStructure *dispatchTrait(int trait, int interpolator, int approximator, int approximatorArg,
    const QlIterativeBootstrapOpts& b, Args&&... args) {
  switch (trait) {
  case hasquant::Discount:
    return dispatchInterpolator<QuantLib::Discount>(interpolator, approximator, approximatorArg, b, std::forward<Args>(args)...);
  case hasquant::ForwardRate:
    return dispatchInterpolator<QuantLib::ForwardRate>(interpolator, approximator, approximatorArg, b, std::forward<Args>(args)...);
  case hasquant::ZeroYield:
    return dispatchInterpolator<QuantLib::ZeroYield>(interpolator, approximator, approximatorArg, b, std::forward<Args>(args)...);
  case hasquant::SimpleZeroYield:
    return dispatchInterpolator<QuantLib::SimpleZeroYield>(interpolator, approximator, approximatorArg, b, std::forward<Args>(args)...);
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
    // GlobalBootstrap is wired up only for the two combinations concrete use cases have asked
    // for -- Discount/LogLinear (the multi-curve relinkable-handle test) and SimpleZeroYield/
    // Linear (upstream QuantLib-SWIG's GlobalLinearSimpleZeroCurve) -- not the full trait x
    // interpolator matrix; CLAUDE.md is explicit about not building dispatch for hypothetical
    // future combinations.
    //
    // Spelled CurveType::bootstrap_type(accuracy), not GlobalBootstrap<CurveType>(accuracy), in
    // both branches below: GlobalBootstrap overrides pure-virtual methods from
    // MultiCurveBootstrapContributor, and [temp.inst] instantiates a class's virtual member
    // function bodies together with the class itself. Naming GlobalBootstrap<CurveType> directly
    // starts instantiating *that* specialization first, which then needs CurveType complete --
    // but CurveType is simultaneously mid-instantiation because of this very argument (its
    // bootstrap_ field has type GlobalBootstrap<CurveType>), producing a hard "incomplete type"
    // error (reproduced independently with clang and g++-16). Naming CurveType (via
    // ::bootstrap_type) first instead makes CurveType the outer instantiation, so
    // GlobalBootstrap<CurveType>'s virtual bodies are only instantiated once CurveType is
    // complete. Don't "simplify" this back to the direct spelling -- it silently reintroduces
    // the compile failure.
    if (trait == hasquant::SimpleZeroYield) {
      QL_REQUIRE(interpolator == hasquant::Linear,
          "GlobalBootstrap-based PiecewiseYieldCurve construction with trait=SimpleZeroYield "
          "only supports interpolator=Linear (got interpolator " << interpolator << ")");
      using CurveType = PiecewiseYieldCurve<QuantLib::SimpleZeroYield, QuantLib::Linear, QuantLib::GlobalBootstrap>;
      return new CurveType(settl, cal, instr, dayCount, jumps, jumpDates, QuantLib::Linear(),
          CurveType::bootstrap_type(accuracy, nullptr, nullptr, instrumentWeights));
    }
    QL_REQUIRE(trait == hasquant::Discount && interpolator == hasquant::LogLinear,
        "GlobalBootstrap-based PiecewiseYieldCurve construction is only supported for "
        "trait=Discount, interpolator=LogLinear or trait=SimpleZeroYield, interpolator=Linear "
        "(got trait " << trait << ", interpolator " << interpolator << ")");
    using CurveType = PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear, QuantLib::GlobalBootstrap>;
    return new CurveType(settl, cal, instr, dayCount, jumps, jumpDates, QuantLib::LogLinear(),
        CurveType::bootstrap_type(accuracy, nullptr, nullptr, instrumentWeights));
  }
  return dispatchTrait(trait, interpolator, approximator, approximatorArg, bootstrapOpts,
      settl, cal, instr, dayCount, jumps, jumpDates);
}

YieldTermStructure *qlInterpolatedDiscountCurveAux(
    const std::vector<Date> &dfDates,
    const std::vector<double>& dfs,
    const DayCounter& dayCount,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedDiscountCurve<BackwardFlat>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  case hasquant::ForwardFlat:
    return new InterpolatedDiscountCurve<ForwardFlat>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  case hasquant::Linear:
    return new InterpolatedDiscountCurve<Linear>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  case hasquant::LogLinear:
    return new InterpolatedDiscountCurve<LogLinear>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

YieldTermStructure *qlInterpolatedForwardCurveAux(
    const std::vector<Date> &fwdDates,
    const std::vector<double>& fwds,
    const DayCounter& dayCount,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedForwardCurve<BackwardFlat>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  case hasquant::ForwardFlat:
    return new InterpolatedForwardCurve<ForwardFlat>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  case hasquant::Linear:
    return new InterpolatedForwardCurve<Linear>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  case hasquant::LogLinear:
    return new InterpolatedForwardCurve<LogLinear>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

YieldTermStructure *qlInterpolatedZeroCurveAux(
    const std::vector<Date> &yDates,
    const std::vector<double>& yields,
    const DayCounter& dayCount,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedZeroCurve<BackwardFlat>(yDates, yields, dayCount, cal, jumps, jumpDates);
  case hasquant::ForwardFlat:
    return new InterpolatedZeroCurve<ForwardFlat>(yDates, yields, dayCount, cal, jumps, jumpDates);
  case hasquant::Linear:
    return new InterpolatedZeroCurve<Linear>(yDates, yields, dayCount, cal, jumps, jumpDates);
  case hasquant::LogLinear:
    return new InterpolatedZeroCurve<LogLinear>(yDates, yields, dayCount, cal, jumps, jumpDates);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

YieldTermStructure *qlInterpolatedSpreadDiscountCurveAux(
    const Handle<YieldTermStructure>& baseCurve,
    const std::vector<Date>& dates,
    const std::vector<double>& dfs,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedSpreadDiscountCurve<BackwardFlat>(baseCurve, dates, dfs);
  case hasquant::ForwardFlat:
    return new InterpolatedSpreadDiscountCurve<ForwardFlat>(baseCurve, dates, dfs);
  case hasquant::Linear:
    return new InterpolatedSpreadDiscountCurve<Linear>(baseCurve, dates, dfs);
  case hasquant::LogLinear:
    return new InterpolatedSpreadDiscountCurve<LogLinear>(baseCurve, dates, dfs);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedSpreadDiscountCurve<Cubic>(baseCurve, dates, dfs,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedSpreadDiscountCurve<Cubic>(baseCurve, dates, dfs,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedSpreadDiscountCurve<Cubic>(baseCurve, dates, dfs,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedSpreadDiscountCurve<Cubic>(baseCurve, dates, dfs,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedSpreadDiscountCurve<LogCubic>(baseCurve, dates, dfs,
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedSpreadDiscountCurve<LogCubic>(baseCurve, dates, dfs,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedSpreadDiscountCurve<LogCubic>(baseCurve, dates, dfs,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedSpreadDiscountCurve<LogCubic>(baseCurve, dates, dfs,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

YieldTermStructure *qlPiecewiseZeroSpreadedTermStructureAux(
    const Handle<YieldTermStructure>& baseCurve,
    const std::vector<Handle<Quote> >& spreads,
    const std::vector<Date>& dates,
    Compounding comp, Frequency freq,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedPiecewiseZeroSpreadedTermStructure<BackwardFlat>(baseCurve, spreads, dates, comp, freq);
  case hasquant::ForwardFlat:
    return new InterpolatedPiecewiseZeroSpreadedTermStructure<ForwardFlat>(baseCurve, spreads, dates, comp, freq);
  case hasquant::Linear:
    return new InterpolatedPiecewiseZeroSpreadedTermStructure<Linear>(baseCurve, spreads, dates, comp, freq);
  case hasquant::LogLinear:
    return new InterpolatedPiecewiseZeroSpreadedTermStructure<LogLinear>(baseCurve, spreads, dates, comp, freq);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<Cubic>(baseCurve, spreads, dates, comp, freq,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<Cubic>(baseCurve, spreads, dates, comp, freq,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<Cubic>(baseCurve, spreads, dates, comp, freq,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<Cubic>(baseCurve, spreads, dates, comp, freq,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<LogCubic>(baseCurve, spreads, dates, comp, freq,
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<LogCubic>(baseCurve, spreads, dates, comp, freq,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<LogCubic>(baseCurve, spreads, dates, comp, freq,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedPiecewiseZeroSpreadedTermStructure<LogCubic>(baseCurve, spreads, dates, comp, freq,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

DefaultProbabilityTermStructure *qlInterpolatedDefaultDensityCurveAux(
    const std::vector<Date>& dates,
    const std::vector<double>& densities,
    const DayCounter& dayCounter,
    const Calendar& calendar,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedDefaultDensityCurve<BackwardFlat>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::ForwardFlat:
    return new InterpolatedDefaultDensityCurve<ForwardFlat>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::Linear:
    return new InterpolatedDefaultDensityCurve<Linear>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::LogLinear:
    return new InterpolatedDefaultDensityCurve<LogLinear>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}


DefaultProbabilityTermStructure *qlInterpolatedHazardRateCurveAux(
    const std::vector<Date>& dates,
    const std::vector<double>& hazardRates,
    const DayCounter& dayCounter,
    const Calendar& cal,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedHazardRateCurve<BackwardFlat>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  case hasquant::ForwardFlat:
    return new InterpolatedHazardRateCurve<ForwardFlat>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  case hasquant::Linear:
    return new InterpolatedHazardRateCurve<Linear>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  case hasquant::LogLinear:
    return new InterpolatedHazardRateCurve<LogLinear>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

DefaultProbabilityTermStructure *qlInterpolatedSurvivalProbabilityCurveAux(
    const std::vector<Date>& dates,
    const std::vector<double>& probabilities,
    const DayCounter& dayCounter,
    const Calendar& calendar,
    const std::vector<Handle<Quote> >& jumps,
    const std::vector<Date>& jumpDates,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedSurvivalProbabilityCurve<BackwardFlat>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::ForwardFlat:
    return new InterpolatedSurvivalProbabilityCurve<ForwardFlat>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::Linear:
    return new InterpolatedSurvivalProbabilityCurve<Linear>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::LogLinear:
    return new InterpolatedSurvivalProbabilityCurve<LogLinear>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux(const Date &referenceDate,
    const std::vector<shared_ptr<DefaultProbabilityHelper> >& instruments,
    DayCounter& dayCounter,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg) {
  switch (trait) {
  case hasquant::HazardRate:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, BackwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, ForwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, Linear>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogLinear>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::SurvivalProbability:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, BackwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, ForwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Linear>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogLinear>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::DefaultDensity:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, BackwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, ForwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Linear>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogLinear>(referenceDate, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  default:
    QL_FAIL("Unsupported trait" << trait);
  }
}

QuantLib::DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux1(unsigned settlementDays,
    const QuantLib::Calendar& calendar,
    const std::vector<shared_ptr<DefaultProbabilityHelper> >& instruments,
    DayCounter& dayCounter,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg) {
  switch (trait) {
  case hasquant::HazardRate:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, BackwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, ForwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, Linear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogLinear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::SurvivalProbability:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, BackwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, ForwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Linear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogLinear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::DefaultDensity:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, BackwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, ForwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Linear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogLinear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseDefaultCurve<QuantLib::DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  default:
    QL_FAIL("Unsupported trait" << trait);
  }
}

ZeroInflationTermStructure *qlPiecewiseZeroInflationCurveAux(
    const Date &referenceDate,
    const Date &baseDate,
    Frequency frequency,
    const DayCounter& dayCounter,
    const std::vector<shared_ptr<BootstrapHelper<ZeroInflationTermStructure> > >& instruments,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new PiecewiseZeroInflationCurve<BackwardFlat>(referenceDate, baseDate, frequency, dayCounter, instruments);
  case hasquant::ForwardFlat:
    return new PiecewiseZeroInflationCurve<ForwardFlat>(referenceDate, baseDate, frequency, dayCounter, instruments);
  case hasquant::Linear:
    return new PiecewiseZeroInflationCurve<Linear>(referenceDate, baseDate, frequency, dayCounter, instruments);
  case hasquant::LogLinear:
    return new PiecewiseZeroInflationCurve<LogLinear>(referenceDate, baseDate, frequency, dayCounter, instruments);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new PiecewiseZeroInflationCurve<Cubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new PiecewiseZeroInflationCurve<Cubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new PiecewiseZeroInflationCurve<Cubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new PiecewiseZeroInflationCurve<Cubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new PiecewiseZeroInflationCurve<LogCubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new PiecewiseZeroInflationCurve<LogCubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new PiecewiseZeroInflationCurve<LogCubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new PiecewiseZeroInflationCurve<LogCubic>(referenceDate, baseDate, frequency, dayCounter, instruments, {}, 1.0e-14,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

YoYInflationTermStructure *qlPiecewiseYoYInflationCurveAux(
    const Date &referenceDate,
    const Date &baseDate,
    Rate baseYoYRate,
    Frequency frequency,
    const DayCounter& dayCounter,
    const std::vector<shared_ptr<BootstrapHelper<YoYInflationTermStructure> > >& instruments,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new PiecewiseYoYInflationCurve<BackwardFlat>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments);
  case hasquant::ForwardFlat:
    return new PiecewiseYoYInflationCurve<ForwardFlat>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments);
  case hasquant::Linear:
    return new PiecewiseYoYInflationCurve<Linear>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments);
  case hasquant::LogLinear:
    return new PiecewiseYoYInflationCurve<LogLinear>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new PiecewiseYoYInflationCurve<Cubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new PiecewiseYoYInflationCurve<Cubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new PiecewiseYoYInflationCurve<Cubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new PiecewiseYoYInflationCurve<Cubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new PiecewiseYoYInflationCurve<LogCubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new PiecewiseYoYInflationCurve<LogCubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new PiecewiseYoYInflationCurve<LogCubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new PiecewiseYoYInflationCurve<LogCubic>(referenceDate, baseDate, baseYoYRate, frequency, dayCounter, instruments, {}, 1.0e-12,
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

YoYInflationTermStructure *qlInterpolatedYoYInflationCurveAux(
    const Date &referenceDate,
    const std::vector<Date> &dates,
    const std::vector<Rate> &rates,
    Frequency frequency,
    const DayCounter& dayCounter,
    int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    return new InterpolatedYoYInflationCurve<BackwardFlat>(referenceDate, dates, rates, frequency, dayCounter);
  case hasquant::ForwardFlat:
    return new InterpolatedYoYInflationCurve<ForwardFlat>(referenceDate, dates, rates, frequency, dayCounter);
  case hasquant::Linear:
    return new InterpolatedYoYInflationCurve<Linear>(referenceDate, dates, rates, frequency, dayCounter);
  case hasquant::LogLinear:
    return new InterpolatedYoYInflationCurve<LogLinear>(referenceDate, dates, rates, frequency, dayCounter);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedYoYInflationCurve<Cubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedYoYInflationCurve<Cubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedYoYInflationCurve<Cubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedYoYInflationCurve<Cubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedYoYInflationCurve<LogCubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedYoYInflationCurve<LogCubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedYoYInflationCurve<LogCubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedYoYInflationCurve<LogCubic>(referenceDate, dates, rates, frequency, dayCounter, {},
          LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
