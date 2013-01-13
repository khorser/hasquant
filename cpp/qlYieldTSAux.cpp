#include "qlYieldTSAux.h"

using namespace QuantLib;

// extracted some template-heavy stuff into a separate file to speed up the compilation
YieldTermStructure *qlPiecewiseYieldCurveAux(const Date &date,
  const std::vector<boost::shared_ptr<RateHelper> >& instr,
  const DayCounter& dayCount,
  const std::vector<Handle<Quote> >& jumps, const std::vector<Date> jumpDates,
  double accuracy, const char *trait, const char *interpolator) {
    if (!strcmp(trait, "Discount")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	return new PiecewiseYieldCurve<Discount, BackwardFlat>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	return new PiecewiseYieldCurve<Discount, ForwardFlat>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	return new PiecewiseYieldCurve<Discount, Linear>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	return new PiecewiseYieldCurve<Discount, LogLinear>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	return new PiecewiseYieldCurve<Discount, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	return new PiecewiseYieldCurve<Discount, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    } else if (!strcmp(trait, "ForwardRate")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	return new PiecewiseYieldCurve<ForwardRate, BackwardFlat>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	return new PiecewiseYieldCurve<ForwardRate, ForwardFlat>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	return new PiecewiseYieldCurve<ForwardRate, Linear>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	return new PiecewiseYieldCurve<ForwardRate, LogLinear>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    } else if (!strcmp(trait, "ZeroYield")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	return new PiecewiseYieldCurve<ZeroYield, BackwardFlat>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	return new PiecewiseYieldCurve<ZeroYield, ForwardFlat>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	return new PiecewiseYieldCurve<ZeroYield, Linear>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	return new PiecewiseYieldCurve<ZeroYield, LogLinear>(date, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(date, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    }
    else
	QL_FAIL("Unsupported trait" << trait);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
