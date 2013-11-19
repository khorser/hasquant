#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/equityfx/all.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/spreadedswaptionvol.hpp>
#include <ql/instruments/capfloor.hpp>
#include <ql/termstructures/volatility/capfloor/all.hpp>
#include <ql/math/interpolations/all.hpp>
#include <ql/experimental/callablebonds/callablebondvolstructure.hpp>
#include <ql/experimental/callablebonds/callablebondconstantvol.hpp>

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
    return ret(new QlBlackVolTermStructure(alloc(new BlackConstantVol(settlementDays, *arg(x1), Handle<Quote>(*arg(volatility)), *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}
QlBlackVolTermStructure* qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(alloc(new BlackConstantVol(Date(referenceDate), *arg(x1), Handle<Quote>(*arg(volatility)), *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}
QlOptionletVolatilityStructure* qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlOptionletVolatilityStructure(alloc(new ConstantOptionletVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlOptionletVolatilityStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new ConstantSwaptionVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new ConstantSwaptionVolatility(settlementDays, *arg(cal), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, int n, int u, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Date(optionDate), Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, int n, int u, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(optionTime, Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, int n, int u, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Period(n, (TimeUnit)u), swapLength, strike, extrapolate);
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
double qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, int n, int u, int n1, int u1, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Period(n, (TimeUnit)u), Period(n1, (TimeUnit)u1), strike, extrapolate);
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
QlSmileSection* qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, int n, int u, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), Period(n, (TimeUnit)u), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, int n, int u, int extr, char **e) {
  try {
    // declared but not implemented in Swaption TS for some reason:
    //return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, *arg(swapTenor), extr))));
    SwaptionVolatilityStructure *ts = arg(o)->get();
    Time length = ts->swapLength(Period(n, (TimeUnit)u));
    return ret(new QlSmileSection(alloc(ts->smileSection(optionTime, length, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, int n, int u, double swapLength, int extr, char **e) {
  try {
    // declared but not implemented in Swaption TS for some reason:
    //return ret(new QlSmileSection(alloc((*arg(o))->smileSection(*arg(optionTenor), swapLength, extr))));
    SwaptionVolatilityStructure *ts = arg(o)->get();
    Date optionDate = ts->optionDateFromTenor(Period(n, (TimeUnit)u));
    Time optionTime = ts->timeFromReference(optionDate);
    return ret(new QlSmileSection(alloc(ts->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e) {
  try {
    // declared but not implemented in Swaption TS for some reason:
    //return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), swapLength, extr))));
    SwaptionVolatilityStructure *ts = arg(o)->get();
    Time optionTime = ts->timeFromReference(Date(optionDate));
    return ret(new QlSmileSection(alloc(ts->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}

QlSmileSection* qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, int n, int u, int n1, int u1, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Period(n, (TimeUnit)u), Period(n1, (TimeUnit)u1), extr))));
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
double qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, int n, int u, char **e) {
  try {
    return (*arg(o))->swapLength(Period(n, (TimeUnit)u));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, int n, int u, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Date(optionDate), Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, int n, int u, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(optionTime, Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, int n, int u, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Period(n, (TimeUnit)u), swapLength, strike, extrapolate);
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
double qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, int n, int u, int n1, int u1, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Period(n, (TimeUnit)u), Period(n1, (TimeUnit)u1), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlVolatilityTermStructure* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc, periods, qlBuildHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlVolatilityTermStructure*>(e, er);
  }
}
QlVolatilityTermStructure* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(settlementDays, *arg(calendar), (BusinessDayConvention)bdc, periods, qlBuildHandleVector(vols, volsLen), *arg(dc)))));
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
    if (interpolation)
      setInterpolation(c, interpolation);
    return ret(new QlBlackVarianceCurve(alloc(c)));
  } catch (std::exception& er) {
    delete c;
    return handleException<QlBlackVarianceCurve*>(e, er);
  }
}

QlBlackVolTermStructure* qlBlackVarianceSurface(int referenceDate, Calendar* cal, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation/*, char *interpolation*/, char **e) {
  BlackVarianceSurface *s = 0;
  try {
    s = new BlackVarianceSurface(Date(referenceDate), *arg(cal), qlDateVector(datesLen, dates), std::vector<double>(strikes, strikes+strikesLen), qlBuildMatrix(blackVolMatrix, blackVolMatrixRows, blackVolMatrixCols), *arg(dayCounter), (BlackVarianceSurface::Extrapolation)lowerExtrapolation, (BlackVarianceSurface::Extrapolation)upperExtrapolation);
    /* TODO uncomment when 2-D Interpolation is added
    if (interpolation)
      setInterpolation(s, interpolation);
    */
    return ret(new QlBlackVolTermStructure(alloc(s)));
  } catch (std::exception& er) {
    delete s;
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}

QlCapFloorTermVolSurface* qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(settlementDays, *arg(calendar), (BusinessDayConvention)bdc, periods, std::vector<double>(strikes, strikes+strikesLen), qlBuildHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloorTermVolSurface*>(e, er);
  }
}

QlCapFloorTermVolSurface* qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc, periods, std::vector<double>(strikes, strikes+strikesLen), qlBuildHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloorTermVolSurface*>(e, er);
  }
}

void qlFreeCallableBondVolatilityStructure(QlCallableBondVolatilityStructure *o) { del(o); }
QlTermStructure* qlCallableBondVolatilityStructureAsTermStructure(QlCallableBondVolatilityStructure *o) { return ret(new QlTermStructure(*arg(o))); }

QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlCallableBondVolatilityStructure(alloc(new CallableBondConstantVolatility(settlementDays, *arg(x1), Handle<Quote>(*arg(volatility)), *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlCallableBondVolatilityStructure*>(e, er);
  }
}
QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlCallableBondVolatilityStructure(alloc(new CallableBondConstantVolatility(Date(referenceDate), Handle<Quote>(*arg(volatility)), *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlCallableBondVolatilityStructure*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
