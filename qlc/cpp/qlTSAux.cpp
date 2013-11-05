#include "qlTSAux.h"

using namespace QuantLib;

// TODO use third termplate argument (Bootstrap)

// extracted some template-heavy stuff into a separate file to speed up the compilation
YieldTermStructure *qlPiecewiseYieldCurveAux(const Date &date,
  const std::vector<boost::shared_ptr<RateHelper> >& instr,
  const DayCounter& dayCount,
  const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
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

YieldTermStructure *qlPiecewiseYieldCurveAux1(unsigned settl, const Calendar &cal,
  const std::vector<boost::shared_ptr<RateHelper> >& instr,
  const DayCounter& dayCount,
  const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
  double accuracy, const char *trait, const char *interpolator) {
    if (!strcmp(trait, "Discount")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	return new PiecewiseYieldCurve<Discount, BackwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	return new PiecewiseYieldCurve<Discount, ForwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	return new PiecewiseYieldCurve<Discount, Linear>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	return new PiecewiseYieldCurve<Discount, LogLinear>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	return new PiecewiseYieldCurve<Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	return new PiecewiseYieldCurve<Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	return new PiecewiseYieldCurve<Discount, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	return new PiecewiseYieldCurve<Discount, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    } else if (!strcmp(trait, "ForwardRate")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	return new PiecewiseYieldCurve<ForwardRate, BackwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	return new PiecewiseYieldCurve<ForwardRate, ForwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	return new PiecewiseYieldCurve<ForwardRate, Linear>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	return new PiecewiseYieldCurve<ForwardRate, LogLinear>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ForwardRate, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ForwardRate, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    } else if (!strcmp(trait, "ZeroYield")) {
      if (!strcmp(interpolator, "BackwardFlat"))
	return new PiecewiseYieldCurve<ZeroYield, BackwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "ForwardFlat"))
	return new PiecewiseYieldCurve<ZeroYield, ForwardFlat>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Linear"))
	return new PiecewiseYieldCurve<ZeroYield, Linear>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "LogLinear"))
	return new PiecewiseYieldCurve<ZeroYield, LogLinear>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy);
      else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      else if (!strcmp(interpolator, "Cubic Kruger"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "LogCubic Kruger"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Kruger));
      else if (!strcmp(interpolator, "Cubic FritschButland"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "LogCubic FritschButland"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::FritschButland));
      else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ZeroYield, Cubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  Cubic(CubicInterpolation::Parabolic, true));
      else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, false));
      else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
	return new PiecewiseYieldCurve<ZeroYield, LogCubic>(settl, cal, instr, dayCount, jumps, jumpDates, accuracy,
		  LogCubic(CubicInterpolation::Parabolic, true));
      else
	QL_FAIL("Unsupported interpolation " << interpolator);
    }
    else
	QL_FAIL("Unsupported trait" << trait);
}

YieldTermStructure *qlInterpolatedDiscountCurveAux(
  const std::vector<Date> &dfDates,
  const std::vector<double>& dfs,
  const DayCounter& dayCount,
  const Calendar& cal,
  const std::vector<Handle<Quote> >& jumps,
  const std::vector<Date>& jumpDates,
  const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    return new InterpolatedDiscountCurve<BackwardFlat>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "ForwardFlat"))
    return new InterpolatedDiscountCurve<ForwardFlat>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Linear"))
    return new InterpolatedDiscountCurve<Linear>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "LogLinear"))
    return new InterpolatedDiscountCurve<LogLinear>(dfDates, dfs, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    return new InterpolatedDiscountCurve<Cubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    return new InterpolatedDiscountCurve<LogCubic>(dfDates, dfs, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

YieldTermStructure *qlInterpolatedForwardCurveAux(
  const std::vector<Date> &fwdDates,
  const std::vector<double>& fwds,
  const DayCounter& dayCount,
  const Calendar& cal,
  const std::vector<Handle<Quote> >& jumps,
  const std::vector<Date>& jumpDates,
  const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    return new InterpolatedForwardCurve<BackwardFlat>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "ForwardFlat"))
    return new InterpolatedForwardCurve<ForwardFlat>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Linear"))
    return new InterpolatedForwardCurve<Linear>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "LogLinear"))
    return new InterpolatedForwardCurve<LogLinear>(fwdDates, fwds, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    return new InterpolatedForwardCurve<Cubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    return new InterpolatedForwardCurve<LogCubic>(fwdDates, fwds, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

YieldTermStructure *qlInterpolatedZeroCurveAux(
  const std::vector<Date> &yDates,
  const std::vector<double>& yields,
  const DayCounter& dayCount,
  const Calendar& cal,
  const std::vector<Handle<Quote> >& jumps,
  const std::vector<Date>& jumpDates,
  const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    return new InterpolatedZeroCurve<BackwardFlat>(yDates, yields, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "ForwardFlat"))
    return new InterpolatedZeroCurve<ForwardFlat>(yDates, yields, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Linear"))
    return new InterpolatedZeroCurve<Linear>(yDates, yields, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "LogLinear"))
    return new InterpolatedZeroCurve<LogLinear>(yDates, yields, dayCount, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    return new InterpolatedZeroCurve<Cubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    return new InterpolatedZeroCurve<LogCubic>(yDates, yields, dayCount, cal, jumps, jumpDates,
        LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

DefaultProbabilityTermStructure *qlInterpolatedDefaultDensityCurveAux(
            const std::vector<Date>& dates,
            const std::vector<double>& densities,
            const DayCounter& dayCounter,
            const Calendar& calendar,
            const std::vector<Handle<Quote> >& jumps,
            const std::vector<Date>& jumpDates,
            const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    return new InterpolatedDefaultDensityCurve<BackwardFlat>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "ForwardFlat"))
    return new InterpolatedDefaultDensityCurve<ForwardFlat>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "Linear"))
    return new InterpolatedDefaultDensityCurve<Linear>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "LogLinear"))
    return new InterpolatedDefaultDensityCurve<LogLinear>(dates, densities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    return new InterpolatedDefaultDensityCurve<Cubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    return new InterpolatedDefaultDensityCurve<LogCubic>(dates, densities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

DefaultProbabilityTermStructure *qlInterpolatedHazardRateCurveAux(
            const std::vector<Date>& dates,
            const std::vector<double>& hazardRates,
            const DayCounter& dayCounter,
            const Calendar& cal,
            const std::vector<Handle<Quote> >& jumps,
            const std::vector<Date>& jumpDates,
            const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    return new InterpolatedHazardRateCurve<BackwardFlat>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "ForwardFlat"))
    return new InterpolatedHazardRateCurve<ForwardFlat>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Linear"))
    return new InterpolatedHazardRateCurve<Linear>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "LogLinear"))
    return new InterpolatedHazardRateCurve<LogLinear>(dates, hazardRates, dayCounter, cal, jumps, jumpDates);
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    return new InterpolatedHazardRateCurve<Cubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    return new InterpolatedHazardRateCurve<LogCubic>(dates, hazardRates, dayCounter, cal, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

DefaultProbabilityTermStructure *qlInterpolatedSurvivalProbabilityCurveAux(
            const std::vector<Date>& dates,
            const std::vector<double>& probabilities,
            const DayCounter& dayCounter,
            const Calendar& calendar,
            const std::vector<Handle<Quote> >& jumps,
            const std::vector<Date>& jumpDates,
            const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    return new InterpolatedSurvivalProbabilityCurve<BackwardFlat>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "ForwardFlat"))
    return new InterpolatedSurvivalProbabilityCurve<ForwardFlat>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "Linear"))
    return new InterpolatedSurvivalProbabilityCurve<Linear>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "LogLinear"))
    return new InterpolatedSurvivalProbabilityCurve<LogLinear>(dates, probabilities, dayCounter, calendar, jumps, jumpDates);
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    return new InterpolatedSurvivalProbabilityCurve<Cubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    return new InterpolatedSurvivalProbabilityCurve<LogCubic>(dates, probabilities, dayCounter, calendar, jumps, jumpDates, LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux(const Date &referenceDate,
    const std::vector<boost::shared_ptr<DefaultProbabilityHelper> >& instruments,
    DayCounter& dayCounter,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    double accuracy, const char* trait, const char *interpolator) {
  if (!strcmp(trait, "HazardRate"))
  {
    if (!strcmp(interpolator, "BackwardFlat"))
      return new PiecewiseDefaultCurve<HazardRate, BackwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "ForwardFlat"))
      return new PiecewiseDefaultCurve<HazardRate, ForwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Linear"))
      return new PiecewiseDefaultCurve<HazardRate, Linear>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "LogLinear"))
      return new PiecewiseDefaultCurve<HazardRate, LogLinear>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic Kruger"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "LogCubic Kruger"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "Cubic FritschButland"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "LogCubic FritschButland"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, true));
    else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, true));
    else
      QL_FAIL("Unsupported interpolation " << interpolator);
  }
  else if (!strcmp(trait, "SurvivalProbability"))
  {
    if (!strcmp(interpolator, "BackwardFlat"))
      return new PiecewiseDefaultCurve<SurvivalProbability, BackwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "ForwardFlat"))
      return new PiecewiseDefaultCurve<SurvivalProbability, ForwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Linear"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Linear>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "LogLinear"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogLinear>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic Kruger"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "LogCubic Kruger"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "Cubic FritschButland"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "LogCubic FritschButland"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, true));
    else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, true));
    else
      QL_FAIL("Unsupported interpolation " << interpolator);
  }
  else if (!strcmp(trait, "DefaultDensity"))
  {
    if (!strcmp(interpolator, "BackwardFlat"))
      return new PiecewiseDefaultCurve<DefaultDensity, BackwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "ForwardFlat"))
      return new PiecewiseDefaultCurve<DefaultDensity, ForwardFlat>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Linear"))
      return new PiecewiseDefaultCurve<DefaultDensity, Linear>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "LogLinear"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogLinear>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic Kruger"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "LogCubic Kruger"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "Cubic FritschButland"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "LogCubic FritschButland"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, true));
    else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(referenceDate, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, true));
    else
      QL_FAIL("Unsupported interpolation " << interpolator);
  }
  else
    QL_FAIL("Unsupported trait " << trait);
}

QuantLib::DefaultProbabilityTermStructure* qlPiecewiseDefaultCurveAux1(unsigned settlementDays,
    const QuantLib::Calendar& calendar,
    const std::vector<boost::shared_ptr<DefaultProbabilityHelper> >& instruments,
    DayCounter& dayCounter,
    const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates,
    double accuracy, const char* trait, const char *interpolator) {
  if (!strcmp(trait, "HazardRate"))
  {
    if (!strcmp(interpolator, "BackwardFlat"))
      return new PiecewiseDefaultCurve<HazardRate, BackwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "ForwardFlat"))
      return new PiecewiseDefaultCurve<HazardRate, ForwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Linear"))
      return new PiecewiseDefaultCurve<HazardRate, Linear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "LogLinear"))
      return new PiecewiseDefaultCurve<HazardRate, LogLinear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic Kruger"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "LogCubic Kruger"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "Cubic FritschButland"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "LogCubic FritschButland"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<HazardRate, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, true));
    else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<HazardRate, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, true));
    else
      QL_FAIL("Unsupported interpolation " << interpolator);
  }
  else if (!strcmp(trait, "SurvivalProbability"))
  {
    if (!strcmp(interpolator, "BackwardFlat"))
      return new PiecewiseDefaultCurve<SurvivalProbability, BackwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "ForwardFlat"))
      return new PiecewiseDefaultCurve<SurvivalProbability, ForwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Linear"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Linear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "LogLinear"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogLinear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic Kruger"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "LogCubic Kruger"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "Cubic FritschButland"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "LogCubic FritschButland"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, true));
    else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<SurvivalProbability, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, true));
    else
      QL_FAIL("Unsupported interpolation " << interpolator);
  }
  else if (!strcmp(trait, "DefaultDensity"))
  {
    if (!strcmp(interpolator, "BackwardFlat"))
      return new PiecewiseDefaultCurve<DefaultDensity, BackwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "ForwardFlat"))
      return new PiecewiseDefaultCurve<DefaultDensity, ForwardFlat>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Linear"))
      return new PiecewiseDefaultCurve<DefaultDensity, Linear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "LogLinear"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogLinear>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy);
    else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    else if (!strcmp(interpolator, "Cubic Kruger"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "LogCubic Kruger"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Kruger));
    else if (!strcmp(interpolator, "Cubic FritschButland"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "LogCubic FritschButland"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::FritschButland));
    else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, Cubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, Cubic(CubicInterpolation::Parabolic, true));
    else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, false));
    else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
      return new PiecewiseDefaultCurve<DefaultDensity, LogCubic>(settlementDays, calendar, instruments, dayCounter, jumps, jumpDates, accuracy, LogCubic(CubicInterpolation::Parabolic, true));
    else
      QL_FAIL("Unsupported interpolation " << interpolator);
  }
  else
    QL_FAIL("Unsupported trait " << trait);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
