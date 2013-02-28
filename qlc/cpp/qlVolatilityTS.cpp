#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/equityfx/all.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/spreadedswaptionvol.hpp>
#include <ql/instruments/capfloor.hpp>
#include <ql/termstructures/volatility/capfloor/all.hpp>
#include <ql/math/interpolations/all.hpp>

#include "qlaux.h"
#include "qlVolatilityTS.h"

using namespace QuantLib;

QlOptionletVolatilityStructure *qlConstantOptionletVol1(
    unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e) {
  try {
    return ret(new QlOptionletVolatilityStructure(new ConstantOptionletVolatility(
		    days, *arg(cal), (BusinessDayConvention) conv, Handle<Quote>(*q),
		    *arg(dc))));
  } catch (std::exception& er) {
    return handleException<QlOptionletVolatilityStructure *>(e, er);
  }
}

void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p) {
  del(p);
}

QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

void qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o) { del(o); }
QlVolatilityTermStructure* qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

void qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o) { del(o); }
QlTermStructure* qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o) { return ret(new QlTermStructure(*arg(o))); }

void qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o) { del(o); }
QlVolatilityTermStructure* qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

void qlFreeSmileSection(QlSmileSection *o) { del(o); }

QlBlackVolTermStructure* qlBlackConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(alloc(new BlackConstantVol(settlementDays, (*arg(x1)), Handle<Quote>(*arg(volatility)), (*arg(dayCounter))))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}
QlBlackVolTermStructure* qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(alloc(new BlackConstantVol(Date(referenceDate), (*arg(x1)), Handle<Quote>(*arg(volatility)), (*arg(dayCounter))))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}
QlOptionletVolatilityStructure* qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlOptionletVolatilityStructure(alloc(new ConstantOptionletVolatility(Date(referenceDate), (*arg(cal)), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlOptionletVolatilityStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new ConstantSwaptionVolatility(Date(referenceDate), (*arg(cal)), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new ConstantSwaptionVolatility(settlementDays, (*arg(cal)), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Date(optionDate), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(optionTime, (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance((*arg(optionTenor)), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Date(optionDate), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(optionTime, swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance((*arg(optionTenor)), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureMaxSwapLength(QlSwaptionVolatilityStructure* o, char **e) {
  try {
    return (*arg(o))->maxSwapLength();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Period* qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, char **e) {
  try {
    return ret(new Period((*arg(o))->maxSwapTenor()));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), (*arg(swapTenor)), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
/* The following methods are not implemented in Swaption TS
QlSmileSection* qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, (*arg(swapTenor)), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection((*arg(optionTenor)), swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
*/
QlSmileSection* qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection((*arg(optionTenor)), (*arg(swapTenor)), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
double qlSwaptionVolatilityStructureSwapLength1(QlSwaptionVolatilityStructure* o, int start, int end, char **e) {
  try {
    return (*arg(o))->swapLength(Date(start), Date(end));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, Period* swapTenor, char **e) {
  try {
    return (*arg(o))->swapLength((*arg(swapTenor)));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Date(optionDate), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(optionTime, (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility((*arg(optionTenor)), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Date(optionDate), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(optionTime, swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility((*arg(optionTenor)), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlVolatilityTermStructure* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned optionTenorsLen, Period** optionTenors, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {
    return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc, qlBuildVector(optionTenors, optionTenorsLen), qlBuildHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlVolatilityTermStructure*>(e, er);
  }
}
QlVolatilityTermStructure* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned optionTenorsLen, Period** optionTenors, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {
    return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(settlementDays, *arg(calendar), (BusinessDayConvention)bdc, qlBuildVector(optionTenors, optionTenorsLen), qlBuildHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlVolatilityTermStructure*>(e, er);
  }
}
QlVolatilityTermStructure* qlConstantCapFloorTermVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlVolatilityTermStructure(alloc(new ConstantCapFloorTermVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlVolatilityTermStructure*>(e, er);
  }
}
QlVolatilityTermStructure* qlConstantCapFloorTermVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlVolatilityTermStructure(alloc(new ConstantCapFloorTermVolatility(settlementDays, *arg(cal), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlVolatilityTermStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlSpreadedSwaptionVolatility(QlSwaptionVolatilityStructure* x0, QlQuote* spread, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new SpreadedSwaptionVolatility(Handle<SwaptionVolatilityStructure>(*arg(x0)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}

void qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o) { del(o); }
QlVolatilityTermStructure* qlCapFloorTermVolSurfaceAsVolatilityTermStructure(QlCapFloorTermVolSurface *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }
void qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o) { del(o); }
QlVolatilityTermStructure* qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

void qlFreeBlackVarianceCurve(QlBlackVarianceCurve *o) { del(o); }
QlBlackVolTermStructure* qlBlackVarianceCurveAsBlackVolTermStructure(QlBlackVarianceCurve *o) { return ret(new QlBlackVolTermStructure(*arg(o))); }

QlLocalVolTermStructure* qlLocalConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlLocalVolTermStructure(alloc(new LocalConstantVol(settlementDays, *arg(x1), Handle<Quote>(*arg(volatility)), *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlLocalVolTermStructure*>(e, er);
  }
}
QlLocalVolTermStructure* qlLocalConstantVol(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlLocalVolTermStructure(alloc(new LocalConstantVol(Date(referenceDate), Handle<Quote>(*arg(volatility)), *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlLocalVolTermStructure*>(e, er);
  }
}
QlLocalVolTermStructure* qlLocalVolCurve(QlBlackVarianceCurve* curve, char **e) {
  try {
    return ret(new QlLocalVolTermStructure(alloc(new LocalVolCurve(Handle<BlackVarianceCurve>(*arg(curve))))));
  } catch (std::exception& er) {
    return handleException<QlLocalVolTermStructure*>(e, er);
  }
}
QlLocalVolTermStructure* qlLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, char **e) {
  try {
    return ret(new QlLocalVolTermStructure(alloc(new LocalVolSurface(Handle<BlackVolTermStructure>(*arg(blackTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<Quote>(*arg(underlying))))));
    return 0;
  } catch (std::exception& er) {
    return handleException<QlLocalVolTermStructure*>(e, er);
  }
}
QlBlackVolTermStructure* qlImpliedVolTermStructure(QlBlackVolTermStructure* origTS, int referenceDate, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(alloc(new ImpliedVolTermStructure(Handle<BlackVolTermStructure>(*arg(origTS)), Date(referenceDate)))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}

// move into qlTSAux?
template <class T>
void setInterpolation(T* o, const char *interpolator) {
  if (!strcmp(interpolator, "BackwardFlat"))
    o->setInterpolation(BackwardFlat());
  else if (!strcmp(interpolator, "ForwardFlat"))
    o->setInterpolation(ForwardFlat());
  else if (!strcmp(interpolator, "Linear"))
    o->setInterpolation(Linear());
  else if (!strcmp(interpolator, "LogLinear"))
    o->setInterpolation(LogLinear());
  else if (!strcmp(interpolator, "Cubic (NaturalSpline False)"))
    o->setInterpolation(Cubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic (NaturalSpline True)"))
    o->setInterpolation(Cubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline False)"))
    o->setInterpolation(LogCubic(CubicInterpolation::Spline, false, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "LogCubic (NaturalSpline True)"))
    o->setInterpolation(LogCubic(CubicInterpolation::Spline, true, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
  else if (!strcmp(interpolator, "Cubic Kruger"))
    o->setInterpolation(Cubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "LogCubic Kruger"))
    o->setInterpolation(LogCubic(CubicInterpolation::Kruger));
  else if (!strcmp(interpolator, "Cubic FritschButland"))
    o->setInterpolation(Cubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "LogCubic FritschButland"))
    o->setInterpolation(LogCubic(CubicInterpolation::FritschButland));
  else if (!strcmp(interpolator, "Cubic (Parabolic False)"))
    o->setInterpolation(Cubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "Cubic (Parabolic True)"))
    o->setInterpolation(Cubic(CubicInterpolation::Parabolic, true));
  else if (!strcmp(interpolator, "LogCubic (Parabolic False)"))
    o->setInterpolation(LogCubic(CubicInterpolation::Parabolic, false));
  else if (!strcmp(interpolator, "LogCubic (Parabolic True)"))
    o->setInterpolation(LogCubic(CubicInterpolation::Parabolic, true));
  else
    QL_FAIL("Unsupported interpolation " << interpolator);
}

QlBlackVarianceCurve* qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, char *interpolation, char **e) {
  BlackVarianceCurve *c = 0;
  try {
    c = new BlackVarianceCurve(Date(referenceDate), qlDateVector(datesLen, dates), std::vector<double>(blackVolCurve, blackVolCurve+blackVolCurveLen), *arg(dayCounter), forceMonotoneVariance);
    setInterpolation(c, interpolation);
    return ret(new QlBlackVarianceCurve(alloc(c)));
  } catch (std::exception& er) {
    delete c;
    return handleException<QlBlackVarianceCurve*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
