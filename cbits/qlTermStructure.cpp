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
#include <ql/termstructures/credit/flathazardrate.hpp>
#include <ql/experimental/credit/spreadedhazardratecurve.hpp>
#include <ql/experimental/credit/factorspreadedhazardratecurve.hpp>
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>
#include <ql/termstructures/yield/all.hpp>
#include <ql/math/interpolations/all.hpp>

#include "qlaux.h"
#include "qlTermStructure.h"
#include "qlTermStructureAux.h"

namespace hasquant {
#include "qlEnumObjects.h"
}

using namespace QuantLib;

template <class T>
std::vector<Handle<T> > qlBuildHandleVector(shared_ptr<T> **vals, size_t len) {
  std::vector<Handle<T> > r; r.reserve(len);
  for (size_t i = 0; i < len; ++i)
    r.push_back(Handle<T>(*vals[i]));
  return r;
}

template <class T>
std::vector< std::vector<Handle<T> > > qlBuildHandleMatrix(shared_ptr<T> **vals, size_t rows, size_t cols) {
  std::vector< std::vector<Handle<T> > > r; r.reserve(rows);
  for (size_t i = 0; i < rows; ++i) {
    std::vector<Handle<T> > row; row.reserve(cols);
    for (size_t j = 0; j < cols; ++j)
      row.push_back(Handle<T>(*vals[i * cols + j]));
    r.push_back(row);
  }
  return r;
}

QlOptionletVolatilityStructure *qlConstantOptionletVol1(unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e) {
  try {
    return ret(new QlOptionletVolatilityStructure(new ConstantOptionletVolatility(days, *arg(cal), (BusinessDayConvention) conv, Handle<Quote>(*q), *arg(dc))));
  } catch (std::exception& er) {
    return handleException<QlOptionletVolatilityStructure *>(e, er);
  }
}

void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p) {del(p);}

QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}

void qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o) {del(o);}
QlVolatilityTermStructure* qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}

void qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o) {del(o);}
QlTermStructure* qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}

void qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o) {del(o);}
QlVolatilityTermStructure* qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}

void qlFreeSmileSection(QlSmileSection *o) {del(o);}

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
int qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, int *u, char **e) {
  try {
    const Period &p = (*arg(o))->maxSwapTenor();
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
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
QlVolatilityTermStructure* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {
    // the length of units array is unused
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc, periods, qlBuildHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlVolatilityTermStructure*>(e, er);
  }
}
QlVolatilityTermStructure* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {
    // the length of units array is unused
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

void qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o) {del(o);}
QlVolatilityTermStructure* qlCapFloorTermVolSurfaceAsVolatilityTermStructure(QlCapFloorTermVolSurface *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}
void qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o) {del(o);}
QlVolatilityTermStructure* qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}

void qlFreeBlackVarianceCurve(QlBlackVarianceCurve *o) {del(o);}
QlBlackVolTermStructure* qlBlackVarianceCurveAsBlackVolTermStructure(QlBlackVarianceCurve *o) {return ret(new QlBlackVolTermStructure(*arg(o)));}

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
void setInterpolation(T* o, int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat:
    o->setInterpolation(BackwardFlat());
    break;
  case hasquant::ForwardFlat:
    o->setInterpolation(ForwardFlat());
    break;
  case hasquant::Linear:
    o->setInterpolation(Linear());
    break;
  case hasquant::LogLinear:
    o->setInterpolation(LogLinear());
    break;
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      o->setInterpolation(Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      break;
    case hasquant::Kruger:
      o->setInterpolation(Cubic(CubicInterpolation::Kruger));
      break;
    case hasquant::FritschButland:
      o->setInterpolation(Cubic(CubicInterpolation::FritschButland));
      break;
    case hasquant::Parabolic:
      o->setInterpolation(Cubic(CubicInterpolation::Parabolic, approximatorArg));
      break;
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
    break;
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline:
      o->setInterpolation(LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      break;
    case hasquant::Kruger:
      o->setInterpolation(LogCubic(CubicInterpolation::Kruger));
      break;
    case hasquant::FritschButland:
      o->setInterpolation(LogCubic(CubicInterpolation::FritschButland));
      break;
    case hasquant::Parabolic:
      o->setInterpolation(LogCubic(CubicInterpolation::Parabolic, approximatorArg));
      break;
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
    break;
  default:
    QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

QlBlackVarianceCurve* qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, int interpolator, int approximator, int approximatorArg, char **e) {
  BlackVarianceCurve *c = 0;
  try {
    c = new BlackVarianceCurve(Date(referenceDate), qlDateVector(datesLen, dates), std::vector<double>(blackVolCurve, blackVolCurve+blackVolCurveLen), *arg(dayCounter), forceMonotoneVariance);
    if (interpolator != QL_NULL_INTEGER)
      setInterpolation(c, interpolator, approximator, approximatorArg);
    return ret(new QlBlackVarianceCurve(alloc(c)));
  } catch (std::exception& er) {
    delete c;
    return handleException<QlBlackVarianceCurve*>(e, er);
  }
}

QlBlackVolTermStructure* qlBlackVarianceSurface(int referenceDate, Calendar* cal, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation/*, int interpolator, int approximator, int approximatorArg*/, char **e) {
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

QlCapFloorTermVolSurface* qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {
    // unit len is unused
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(settlementDays, *arg(calendar), (BusinessDayConvention)bdc, periods, std::vector<double>(strikes, strikes+strikesLen), qlBuildHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloorTermVolSurface*>(e, er);
  }
}

QlCapFloorTermVolSurface* qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {
    // unit len is unused
    std::vector<Period> periods;
    for (unsigned i = 0; i < l; ++i)
      periods.push_back(Period(n[i], (TimeUnit)u[i]));
    return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc, periods, std::vector<double>(strikes, strikes+strikesLen), qlBuildHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloorTermVolSurface*>(e, er);
  }
}

void qlFreeCallableBondVolatilityStructure(QlCallableBondVolatilityStructure *o) {del(o);}
QlTermStructure* qlCallableBondVolatilityStructureAsTermStructure(QlCallableBondVolatilityStructure *o) {return ret(new QlTermStructure(*arg(o)));}

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

void qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o) {del(o);}
QlTermStructure* qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}

QlDefaultProbabilityTermStructure* qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new FactorSpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(settlementDays, *arg(calendar), Handle<Quote>(*arg(hazardRate)), (*arg(x3))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(Date(referenceDate), Handle<Quote>(*arg(hazardRate)), (*arg(x2))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(new SpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedDefaultDensityCurveAux(qlDateVector(datesLen, dates), std::vector<double>(densities, densities+densitiesLen), *arg(dayCounter), *arg(calendar), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jDatesLen, jumpDates), interpolator, approximator, approximatorArg))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedHazardRateCurveAux(qlDateVector(datesLen, dates), std::vector<double>(hazardRates, hazardRates+hazardRatesLen), *arg(dayCounter), *arg(cal), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jDatesLen, jumpDates), interpolator, approximator, approximatorArg))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}
QlDefaultProbabilityTermStructure* qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedSurvivalProbabilityCurveAux(qlDateVector(datesLen, dates), std::vector<double>(probabilities, probabilities+probabilitiesLen), *arg(dayCounter), *arg(calendar), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jDatesLen, jumpDates), interpolator, approximator, approximatorArg))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}

void qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o) {del(o);}

QlDefaultProbabilityHelper* qlSpreadCdsHelper(QlQuote* runningSpread, int n, int u, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, char **e) {
  try {
    return ret(new QlDefaultProbabilityHelper(alloc(new SpreadCdsHelper(Handle<Quote>(*arg(runningSpread)), Period(n, (TimeUnit)u), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), settlesAccrual, paysAtDefaultTime))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityHelper*>(e, er);
  }
}
QlDefaultProbabilityHelper* qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, int n, int u, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, char **e) {
  try {
    return ret(new QlDefaultProbabilityHelper(alloc(new UpfrontCdsHelper(Handle<Quote>(*arg(upfront)), runningSpread, Period(n, (TimeUnit)u), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), upfrontSettlementDays, settlesAccrual, paysAtDefaultTime))));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityHelper*>(e, er);
  }
}

QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve(int referenceDate, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    DefaultProbabilityTermStructure *ts = qlPiecewiseDefaultCurveAux(Date(referenceDate), qlBuildVector(instruments, instrumentsLen), *arg(dayCounter), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jDatesLen, jumpDates), trait, interpolator, approximator, approximatorArg);
    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}

QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve1(unsigned settlementDays, Calendar *calendar, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    DefaultProbabilityTermStructure *ts = qlPiecewiseDefaultCurveAux1(settlementDays, *arg(calendar), qlBuildVector(instruments, instrumentsLen), *arg(dayCounter), qlBuildHandleVector(jumps, jumpsLen), qlDateVector(jDatesLen, jumpDates), trait, interpolator, approximator, approximatorArg);
    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlDefaultProbabilityTermStructure*>(e, er);
  }
}

double qlDefaultProbabilityTermStructureDefaultDensity1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultDensity(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultDensity(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultDensity(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultProbability(t, (bool)extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability2(QlDefaultProbabilityTermStructure* o, int x1, int x2, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultProbability(Date(x1), Date(x2), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability3(QlDefaultProbabilityTermStructure* o, double x1, double x2, int extrapo, char **e) {
  try {
    return (*arg(o))->defaultProbability(x1, x2, extrapo);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureDefaultProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->defaultProbability(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureHazardRate1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->hazardRate(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureHazardRate(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->hazardRate(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureSurvivalProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->survivalProbability(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlDefaultProbabilityTermStructureSurvivalProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {
    return (*arg(o))->survivalProbability(Date(d), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlRateHelper *qlDepositRateHelper(QlQuote *quote, int l, int u, unsigned fixDays,
  Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e) {
  try {
    return ret(new QlRateHelper(new DepositRateHelper(
	    Handle<Quote>(*arg(quote)),
	    Period(l, (TimeUnit)u),
	    fixDays,
	    *arg(calendar),
	    (BusinessDayConvention) conv,
	    eom,
	    *arg(dayCount))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper *>(e, er);
  }
}

QlBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
  Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv,
  double redemption, int issue, char **e) {
  try {
    std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlBondHelper(new FixedRateBondHelper(Handle<Quote>(*arg(quote)), settlDays, face, *arg(sched), cpns, *arg(dayCount), (BusinessDayConvention) conv, redemption, qlNullableDate(issue))));
  } catch (std::exception& er) {
    return handleException<QlBondHelper *>(e, er);
  }
}

void qlFreeRateHelper(QlRateHelper *helper) {del(helper);}

QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    std::vector<shared_ptr<RateHelper> > instr; instr.reserve(rateLen);
    std::vector<Handle<Quote> > jumps; jumps.reserve(quoteLen);
    std::vector<Date> jumpDates; jumpDates.reserve(datesLen);
    for (unsigned i = 0; i < rateLen; ++i)
      instr.push_back(*arg(ratehelpers[i]));
    for (unsigned i = 0; i < quoteLen; ++i)
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
    for (unsigned i = 0; i < datesLen; ++i)
      jumpDates.push_back(Date(dates[i]));
    YieldTermStructure *ts = qlPiecewiseYieldCurveAux(Date(date), instr, *arg(dayCount), jumps, jumpDates, trait, interpolator, approximator, approximatorArg);
    // TODO free ts if allocation below fails
    return ret(new QlYieldTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure *>(e, er);
  }
}

typedef YieldTermStructure *(*curveBuilder)(
  const std::vector<Date>& dates,
  const std::vector<double>& dfs,
  const DayCounter& dayCount,
  const Calendar& cal,
  const std::vector<Handle<Quote> >& jumps,
  const std::vector<Date>& jumpDates,
  int interpolator, int approximator, int approximatorArg);

QlYieldTermStructure *qlInterpolatedCurve(curveBuilder builder,
  unsigned rateLen, double *rates, unsigned rateDatesLen, int *rateDates,
  DayCounter *dayCount, Calendar *cal,
  unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    std::vector<Date> rds; rds.reserve(rateDatesLen);
    std::vector<double> rs(rates, rates+rateLen);
    std::vector<Handle<Quote> > jumps; jumps.reserve(quoteLen);
    std::vector<Date> jumpDates; jumpDates.reserve(datesLen);
    for (unsigned i = 0; i < rateDatesLen; ++i)
      rds.push_back(Date(rateDates[i]));
    for (unsigned i = 0; i < quoteLen; ++i)
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
    for (unsigned i = 0; i < datesLen; ++i)
      jumpDates.push_back(Date(dates[i]));
    YieldTermStructure *ts = builder(rds, rs, *arg(dayCount), *arg(cal), jumps, jumpDates, interpolator, approximator, approximatorArg);
    return ret(new QlYieldTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure *>(e, er);
  }
}

QlYieldTermStructure *qlInterpolatedDiscountCurve(unsigned dfsLen,
  double *dfs, unsigned dfdatesLen, int *dfsDates, DayCounter *dayCount, Calendar *cal,
  unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedDiscountCurveAux, dfsLen, dfs, dfdatesLen, dfsDates,
    dayCount, cal, quoteLen, quotes, datesLen, dates, interpolator, approximator, approximatorArg, e);
}

QlYieldTermStructure *qlInterpolatedForwardCurve(unsigned fwdLen,
  double *fwds, unsigned fwddatesLen, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedForwardCurveAux, fwdLen, fwds, fwddatesLen, fwdDates,
    dayCount, cal, quoteLen, quotes, datesLen, dates, interpolator, approximator, approximatorArg, e);
}

QlYieldTermStructure *qlInterpolatedZeroCurve(unsigned yieldLen,
  double *yields, unsigned ydatesLen, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedZeroCurveAux, yieldLen, yields, ydatesLen, yieldDates,
    dayCount, cal, quoteLen, quotes,  datesLen, dates, interpolator, approximator, approximatorArg, e);
}

QlYieldTermStructure *qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal,
  unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int trait,
  int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    std::vector<shared_ptr<RateHelper> > instr; instr.reserve(rateLen);
    std::vector<Handle<Quote> > jumps; jumps.reserve(quoteLen);
    std::vector<Date> jumpDates; jumpDates.reserve(quoteLen);
    for (unsigned i = 0; i < rateLen; ++i)
      instr.push_back(*arg(ratehelpers[i]));
    for (unsigned i = 0; i < quoteLen; ++i)
      jumps.push_back(Handle<Quote>(*arg(quotes[i])));
    for (unsigned i = 0; i < datesLen; ++i)
      jumpDates.push_back(Date(dates[i]));
    YieldTermStructure *ts = qlPiecewiseYieldCurveAux1(settl, *arg(cal), instr, *arg(dayCount), jumps, jumpDates, trait, interpolator, approximator, approximatorArg);
    return ret(new QlYieldTermStructure(alloc(ts)));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure *>(e, er);
  }
}
void qlFreeYieldTermStructure(QlYieldTermStructure *ts) {del(ts);}

double qlYieldTSDiscount(QlYieldTermStructure *ts, int date, int extrapolate, char **e) {
  try {
    return (*ts)->discount(Date(date), extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlSwapRateHelper *qlSwapRateHelper1(QlQuote *q, int l, int u, Calendar *cal, int freq,
  int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, int fl, int fu,
  QlYieldTermStructure *ts, char **e) {
  try {
    return ret(new QlSwapRateHelper(new SwapRateHelper(Handle<Quote>(*arg(q)),
	    Period(l, (TimeUnit)u), *arg(cal), (Frequency) freq, (BusinessDayConvention) conv, *arg(dc), *arg(i),
            s ? Handle<Quote>(*arg(s)) : Handle<Quote>(),
            Period(fl, (TimeUnit)fu), ts ? Handle<YieldTermStructure>(*arg(ts)) : Handle<YieldTermStructure>())));
  } catch (std::exception& er) {
    return handleException<QlSwapRateHelper *>(e, er);
  }
}

// generated methods
QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {
    return ret(new QlYieldTermStructure(alloc(new FlatForward(Date(referenceDate), Handle<Quote>(*arg(forward)), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {
    return ret(new QlYieldTermStructure(alloc(new FlatForward(settlementDays, *arg(calendar), Handle<Quote>(*arg(forward)), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

void qlFreeFittedBondDiscountCurveFittingMethod(FittedBondDiscountCurveFittingMethod *o) {del(o);}

// generated functions
InterestRate* qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
try {
    return ret(new InterestRate((*arg(o))->zeroRate(Date(d), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, int l, int u, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(Date(d), Period(l, (TimeUnit)u), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(Date(d1), Date(d2), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->forwardRate(t1, t2, (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e) {
  try {
    return ret(new InterestRate((*arg(o))->zeroRate(t, (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

double qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e) {
  try {
    return (*arg(o))->discount(t, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlRateHelper* qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), monthsToStart, monthsToEnd, fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}

void qlFreeBondHelper(QlBondHelper *o) {del(o);}
QlRateHelper* qlBondHelperAsRateHelper(QlBondHelper *o) {return ret(new QlRateHelper(*arg(o)));}

FittedBondDiscountCurveFittingMethod* qlCubicBSplinesFitting(unsigned knotVectorLen, double *knotVector, int constrainAtZero, char **e) {
  try {
    return alloc(new CubicBSplinesFitting(std::vector<double>(knotVector, knotVector+knotVectorLen), constrainAtZero));
  } catch (std::exception& er) {
    return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);
  }
}

FittedBondDiscountCurveFittingMethod* qlExponentialSplinesFitting(int constrainAtZero, char **e) {
  try {
    return alloc(new ExponentialSplinesFitting(constrainAtZero));
  } catch (std::exception& er) {
    return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);
  }
}

FittedBondDiscountCurveFittingMethod* qlNelsonSiegelFitting(char **e) {
  try {
    return alloc(new NelsonSiegelFitting());
  } catch (std::exception& er) {
    return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);
  }
}

FittedBondDiscountCurveFittingMethod* qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, char **e) {
  try {
    return alloc(new SimplePolynomialFitting(degree, constrainAtZero));
  } catch (std::exception& er) {
    return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);
  }
}

FittedBondDiscountCurveFittingMethod* qlSvenssonFitting(char **e) {
  try {
    return alloc(new SvenssonFitting());
  } catch (std::exception& er) {
    return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);
  }
}

QlFittedBondDiscountCurve* qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e) {
  try {
    return ret(new QlFittedBondDiscountCurve(alloc(new FittedBondDiscountCurve(settlementDays, *arg(calendar), qlBuildVector(bonds, bondsLen), *arg(dayCounter), *arg(fittingMethod), accuracy, maxEvaluations, Array(guess, guess+guessLen), simplexLambda))));
  } catch (std::exception& er) {
    return handleException<QlFittedBondDiscountCurve*>(e, er);
  }
}

QlFittedBondDiscountCurve* qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurveFittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e) {
  try {
    return ret(new QlFittedBondDiscountCurve(alloc(new FittedBondDiscountCurve(Date(referenceDate), qlBuildVector(bonds, bondsLen), *arg(dayCounter), *arg(fittingMethod), accuracy, maxEvaluations, Array(guess, guess+guessLen), simplexLambda))));
  } catch (std::exception& er) {
    return handleException<QlFittedBondDiscountCurve*>(e, er);
  }
}

void qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o) {del(o);}
QlYieldTermStructure* qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o) {return ret(new QlYieldTermStructure(*arg(o)));}

double qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve *o, char **e) {
  try {
    return (*arg(o))->fitResults().minimumCostValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

int qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve *o, char **e) {
  try {
    return (*arg(o))->fitResults().numberOfIterations();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeSwapRateHelper(QlSwapRateHelper *o) {del(o);}
QlRateHelper* qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o) {return ret(new QlRateHelper(*arg(o)));}

void qlFreeOISRateHelper(QlOISRateHelper *o) {del(o);}
QlRateHelper* qlOISRateHelperAsRateHelper(QlOISRateHelper *o) {return ret(new QlRateHelper(*arg(o)));}

QlBondHelper* qlBondHelper(QlQuote* cleanPrice, QlBond* bond, char **e) {
  try {
    return ret(new QlBondHelper(alloc(new BondHelper(Handle<Quote>(*arg(cleanPrice)), *arg(bond)))));
  } catch (std::exception& er) {
    return handleException<QlBondHelper*>(e, er);
  }
}
QlOISRateHelper* qlOISRateHelper(unsigned settlementDays, int l, int u, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e) {
  try {
    return ret(new QlOISRateHelper(alloc(new OISRateHelper(settlementDays, Period(l, (TimeUnit)u), Handle<Quote>(*arg(fixedRate)), *arg(overnightIndex), qlNullableHandle(arg(discountingCurve))))));
  } catch (std::exception& er) {
    return handleException<QlOISRateHelper*>(e, er);
  }
}
QlSwapRateHelper* qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, int fl, int fu, QlYieldTermStructure* discountingCurve, char **e) {
  try {
    return ret(new QlSwapRateHelper(alloc(new SwapRateHelper(Handle<Quote>(*arg(rate)), *arg(swapIndex), qlNullableHandle(arg(spread)), Period(fl, (TimeUnit)fu), qlNullableHandle(arg(discountingCurve))))));
  } catch (std::exception& er) {
    return handleException<QlSwapRateHelper*>(e, er);
  }
}

QlYieldTermStructure* qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new ForwardSpreadedTermStructure(Handle<YieldTermStructure>(*arg(x0)), Handle<Quote>(*arg(spread))))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlYieldTermStructure* qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, DayCounter* dc, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new ZeroSpreadedTermStructure(Handle<YieldTermStructure>(*arg(x0)), Handle<Quote>(*arg(spread)), (Compounding)comp, (Frequency)freq, *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlRateHelper* qlBMASwapRateHelper(QlQuote* liborFraction, int tl, int tu, unsigned settlementDays, Calendar* calendar, int bl, int bu, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new BMASwapRateHelper(Handle<Quote>(*arg(liborFraction)), Period(tl, (TimeUnit)tu), settlementDays, *arg(calendar), Period(bl, (TimeUnit)bu), (BusinessDayConvention)bmaConvention, *arg(bmaDayCount), *arg(bmaIndex), *arg(index)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlDatedOISRateHelper(int startDate, int endDate, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new DatedOISRateHelper(Date(startDate), Date(endDate), Handle<Quote>(*arg(fixedRate)), *arg(overnightIndex), qlNullableHandle(arg(discountingCurve))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new DepositRateHelper(Handle<Quote>(*arg(rate)), *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), monthsToStart, *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFraRateHelper2(QlQuote* rate, int l, int u, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), Period(l, (TimeUnit)u), lengthInMonths, fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFraRateHelper3(QlQuote* rate, int l, int u, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FraRateHelper(Handle<Quote>(*arg(rate)), Period(l, (TimeUnit)u), *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FuturesRateHelper(Handle<Quote>(*arg(price)), Date(immStartDate), Date(endDate), *arg(dayCounter), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FuturesRateHelper(Handle<Quote>(*arg(price)), Date(immDate), *arg(iborIndex), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
QlRateHelper* qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FuturesRateHelper(Handle<Quote>(*arg(price)), Date(immDate), lengthInMonths, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {
    return handleException<QlRateHelper*>(e, er);
  }
}
double qlRateHelperImpliedQuote(QlRateHelper* o, char **e) {
  try {
    return (*arg(o))->impliedQuote();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlBond* qlBondHelperBond(QlBondHelper* o, char **e) {
  try {
    return ret(new QlBond((*arg(o))->bond()));
  } catch (std::exception& er) {
    return handleException<QlBond*>(e, er);
  }
}
QlOvernightIndexedSwap* qlOISRateHelperSwap(QlOISRateHelper* o, char **e) {
  try {
    return ret(new QlOvernightIndexedSwap((*arg(o))->swap()));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndexedSwap*>(e, er);
  }
}
QlVanillaSwap* qlSwapRateHelperSwap(QlSwapRateHelper* o, char **e) {
  try {
    return ret(new QlVanillaSwap((*arg(o))->swap()));
  } catch (std::exception& er) {
    return handleException<QlVanillaSwap*>(e, er);
  }
}
int qlTermStructureReferenceDate(QlTermStructure* o, char **e) {
  try {
    return (*arg(o))->referenceDate().serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlTermStructureMaxDate(QlTermStructure* o, char **e) {
  try {
    return (*arg(o))->maxDate().serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}


void qlFreeTermStructure(QlTermStructure *o) {del(o);}
QlTermStructure* qlYieldTermStructureAsTermStructure(QlYieldTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}

QlYieldTermStructure* qlImpliedTermStructure(QlYieldTermStructure* x0, int referenceDate, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new ImpliedTermStructure(Handle<YieldTermStructure>(*arg(x0)), Date(referenceDate)))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

QlYieldTermStructure* qlPiecewiseZeroSpreadedTermStructure(QlYieldTermStructure* x0, unsigned spreadsLen, QlQuote** spreads, unsigned datesLen, int* dates, int comp, int freq, DayCounter* dc, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new PiecewiseZeroSpreadedTermStructure(Handle<YieldTermStructure>(*arg(x0)), qlBuildHandleVector(spreads, spreadsLen), qlDateVector(datesLen, dates), (Compounding)comp, (Frequency)freq, *arg(dc)))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}
QlYieldTermStructure* qlQuantoTermStructure(QlYieldTermStructure* underlyingDividendTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* foreignRiskFreeTS, QlBlackVolTermStructure* underlyingBlackVolTS, double strike, QlBlackVolTermStructure* exchRateBlackVolTS, double exchRateATMlevel, double underlyingExchRateCorrelation, char **e) {
  try {
    return ret(new QlYieldTermStructure(alloc(new QuantoTermStructure(Handle<YieldTermStructure>(*arg(underlyingDividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<YieldTermStructure>(*arg(foreignRiskFreeTS)), Handle<BlackVolTermStructure>(*arg(underlyingBlackVolTS)), strike, Handle<BlackVolTermStructure>(*arg(exchRateBlackVolTS)), exchRateATMlevel, underlyingExchRateCorrelation))));
  } catch (std::exception& er) {
    return handleException<QlYieldTermStructure*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
