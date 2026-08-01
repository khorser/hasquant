#include <ql/shared_ptr.hpp>
using QuantLib::ext::shared_ptr;
#include "qlTermStructureAux.h"
namespace hasquant {
#include "qlEnumObjects.h"
}

using namespace QuantLib;

// TODO use third termplate argument (Bootstrap)

// extracted some template-heavy stuff into a separate file to speed up the compilation
YieldTermStructure *qlPiecewiseYieldCurveAux(const Date &date,
    const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg) {
  switch (trait) {
  case hasquant::Discount:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseYieldCurve<QuantLib::Discount, QuantLib::BackwardFlat>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseYieldCurve<QuantLib::Discount, QuantLib::ForwardFlat>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseYieldCurve<QuantLib::Discount, QuantLib::Linear>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseYieldCurve<QuantLib::Discount, QuantLib::LogLinear>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::Discount, QuantLib::Cubic>(date, instr, dayCount, jumps, jumpDates,
            QuantLib::Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::ForwardRate:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, BackwardFlat>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, ForwardFlat>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, Linear>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogLinear>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::ZeroYield:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, BackwardFlat>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, ForwardFlat>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, Linear>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogLinear>(date, instr, dayCount, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Parabolic, approximatorArg));
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

YieldTermStructure *qlPiecewiseYieldCurveAux1(unsigned settl, const Calendar &cal,
    const std::vector<shared_ptr<RateHelper> >& instr,
    const DayCounter& dayCount,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    int trait, int interpolator, int approximator, int approximatorArg) {
  switch (trait) {
  case hasquant::Discount:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseYieldCurve<QuantLib::Discount, BackwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseYieldCurve<QuantLib::Discount, ForwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseYieldCurve<QuantLib::Discount, Linear>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseYieldCurve<QuantLib::Discount, LogLinear>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::ForwardRate:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, BackwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, ForwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, Linear>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogLinear>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    default:
      QL_FAIL("Unsupported interpolation " << interpolator);
    }
  case hasquant::ZeroYield:
    switch (interpolator) {
    case hasquant::BackwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, BackwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::ForwardFlat:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, ForwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::Linear:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, Linear>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::LogLinear:
      return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogLinear>(settl, cal, instr, dayCount, jumps, jumpDates);
    case hasquant::Cubic:
      switch (approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    case hasquant::LogCubic:
      switch(approximator) {
      case hasquant::NaturalSpline:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return new PiecewiseYieldCurve<QuantLib::ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates,
            LogCubic(CubicInterpolation::Parabolic, approximatorArg));
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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
