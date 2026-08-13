#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/equityfx/all.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/spreadedswaptionvol.hpp>
#include <ql/termstructures/volatility/sabrsmilesection.hpp>
#include <ql/termstructures/volatility/sabrinterpolatedsmilesection.hpp>
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
#include <ql/index.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/indexes/bmaindex.hpp>
#include <ql/indexes/swap/all.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>
#include <ql/indexes/inflation/all.hpp>
#include <ql/termstructures/inflation/inflationhelpers.hpp>
#include <ql/indexes/equityindex.hpp>

#include "qlaux.h"
using namespace QuantLib;
// these are typedefs so we cannot use their forward declarations in qlaux.h without including all relevant header files
typedef shared_ptr<DefaultProbabilityHelper> QlDefaultProbabilityHelper;
typedef shared_ptr<RateHelper> QlRateHelper;
typedef FittedBondDiscountCurve::FittingMethod FittedBondDiscountCurveFittingMethod;
#include "qlTermStructure.h"
#include "qlTermStructureAux.h"

namespace hasquant {
#include "qlEnumObjects.h"
}

#ifdef QLTRACK_ALLOCATIONS
template <> class ObjClassName<DefaultProbabilityHelper*> {public: static void output(std::ostream& os) {os << "DefaultProbabilityHelper";}};
template <> class ObjClassName<QlDefaultProbabilityHelper*> {public: static void output(std::ostream& os) {os << "QlDefaultProbabilityHelper";}};
template <> class ObjClassName<RateHelper*> {public: static void output(std::ostream& os) {os << "RateHelper";}};
template <> class ObjClassName<QlRateHelper*> {public: static void output(std::ostream& os) {os << "QlRateHelper";}};
template <> class ObjClassName<FittedBondDiscountCurveFittingMethod*> {public: static void output(std::ostream& os) {os << "FittedBondDiscountCurveFittingMethod";}};
template <> class ObjClassName<PiecewiseZeroSpreadedTermStructure*> {public: static void output(std::ostream& os) {os << "PiecewiseZeroSpreadedTermStructure";}};
#endif

// vals elements are already Handle<T>*, since a Quote/vol-structure array is an array of the
// same Handle-backed pointer type used everywhere else -- copying *arg(vals[i]) into the
// vector shares its Link like any other Handle copy, so a relinkable element stays tracked.
template <class T>
inline std::vector<Handle<T> > qlHandleVector(Handle<T> **vals, size_t len) {
  std::vector<Handle<T> > r; r.reserve(len);
  for (size_t i = 0; i < len; ++i)
    r.push_back(*arg(vals[i]));
  return r;
}

template <class T>
inline std::vector< std::vector<Handle<T> > > qlHandleMatrix(Handle<T> **vals, size_t rows, size_t cols) {
  std::vector< std::vector<Handle<T> > > r; r.reserve(rows);
  for (size_t i = 0; i < rows; ++i) {
    std::vector<Handle<T> > row; row.reserve(cols);
    for (size_t j = 0; j < cols; ++j)
      row.push_back(*arg(vals[i * cols + j]));
    r.push_back(row);
  }
  return r;
}

// move into qlTSAux?
template <class T>
void setInterpolation(T* o, int interpolator, int approximator, int approximatorArg) {
  switch (interpolator) {
  case hasquant::BackwardFlat: o->setInterpolation(BackwardFlat()); break;
  case hasquant::ForwardFlat: o->setInterpolation(ForwardFlat()); break;
  case hasquant::Linear: o->setInterpolation(Linear()); break;
  case hasquant::LogLinear: o->setInterpolation(LogLinear()); break;
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline: o->setInterpolation(Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0)); break;
    case hasquant::Kruger: o->setInterpolation(Cubic(CubicInterpolation::Kruger)); break;
    case hasquant::FritschButland: o->setInterpolation(Cubic(CubicInterpolation::FritschButland)); break;
    case hasquant::Parabolic: o->setInterpolation(Cubic(CubicInterpolation::Parabolic, approximatorArg)); break;
    default: QL_FAIL("Unsupported approximation " << approximator);
    }
    break;
  case hasquant::LogCubic:
    switch(approximator) {
    case hasquant::NaturalSpline: o->setInterpolation(LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0)); break;
    case hasquant::Kruger: o->setInterpolation(LogCubic(CubicInterpolation::Kruger)); break;
    case hasquant::FritschButland: o->setInterpolation(LogCubic(CubicInterpolation::FritschButland)); break;
    case hasquant::Parabolic: o->setInterpolation(LogCubic(CubicInterpolation::Parabolic, approximatorArg)); break;
    default: QL_FAIL("Unsupported approximation " << approximator);
    }
    break;
  // hasquant::Abcd (InterpolationType's 7th case) has no case here -- QuantLib's Abcd
  // interpolation isn't wired up to setInterpolation on this codepath; falls through to the
  // default QL_FAIL below. Pre-existing gap, not something the Interpolation/Approximation TH
  // refactor (see deriveCrossEnum in QuantLib/Internal/Enum.chs) introduced or touches.
  default: QL_FAIL("Unsupported interpolation " << interpolator);
  }
}

namespace {
ext::shared_ptr<SabrInterpolatedSmileSection> asSabrInterpolatedSmileSection(const QlSmileSection& o) {
  auto s = ext::dynamic_pointer_cast<SabrInterpolatedSmileSection>(o);
  QL_REQUIRE(s, "not a SabrInterpolatedSmileSection");
  return s;
}
}

extern "C" {
QlOptionletVolatilityStructure *qlConstantOptionletVol1(unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, int type, double displacement, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(new ConstantOptionletVolatility(days, *arg(cal), (BusinessDayConvention) conv, *arg(q), *arg(dc), (VolatilityType)type, displacement)));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure *>(e, er);}}

void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p) {del(p);}
QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}
void qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o) {del(o);}
// VolatilityTermStructure is never a Handle upstream (confirmed by grep), so this is a
// deliberate snapshot detach -- same reasoning as qlYieldTermStructureAsTermStructure.
QlVolatilityTermStructure* qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o) {return ret(new QlVolatilityTermStructure(handlePtr(arg(o))));}

// A relinkable handle, empty when `initial` is null -- mirrors qlRelinkableYieldTermStructure.
QlRelinkableBlackVolTermStructure* qlRelinkableBlackVolTermStructure(QlBlackVolTermStructure *initial, char **e) {
  try {return ret(initial ? new QlRelinkableBlackVolTermStructure(handlePtr(arg(initial)))
                          : new QlRelinkableBlackVolTermStructure());
  } catch (std::exception& er) {return handleException<QlRelinkableBlackVolTermStructure*>(e, er);}}
void qlFreeRelinkableBlackVolTermStructure(QlRelinkableBlackVolTermStructure *o) {del(o);}
void qlRelinkableBlackVolTermStructureLinkTo(QlRelinkableBlackVolTermStructure *o, QlBlackVolTermStructure *c, char **e) {
  try {arg(o)->linkTo(handlePtr(arg(c)));} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
QlBlackVolTermStructure* qlRelinkableBlackVolTermStructureAsBlackVolTermStructure(QlRelinkableBlackVolTermStructure *o) {return ret(new QlBlackVolTermStructure(*arg(o)));}
void qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o) {del(o);}
QlTermStructure* qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}
void qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o) {del(o);}
// Deliberate snapshot detach, same reasoning as qlBlackVolTermStructureAsVolatilityTermStructure.
QlVolatilityTermStructure* qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o) {return ret(new QlVolatilityTermStructure(handlePtr(arg(o))));}

// A relinkable handle, empty when `initial` is null -- mirrors qlRelinkableYieldTermStructure.
QlRelinkableSwaptionVolatilityStructure* qlRelinkableSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *initial, char **e) {
  try {return ret(initial ? new QlRelinkableSwaptionVolatilityStructure(handlePtr(arg(initial)))
                          : new QlRelinkableSwaptionVolatilityStructure());
  } catch (std::exception& er) {return handleException<QlRelinkableSwaptionVolatilityStructure*>(e, er);}}
void qlFreeRelinkableSwaptionVolatilityStructure(QlRelinkableSwaptionVolatilityStructure *o) {del(o);}
void qlRelinkableSwaptionVolatilityStructureLinkTo(QlRelinkableSwaptionVolatilityStructure *o, QlSwaptionVolatilityStructure *c, char **e) {
  try {arg(o)->linkTo(handlePtr(arg(c)));} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
QlSwaptionVolatilityStructure* qlRelinkableSwaptionVolatilityStructureAsSwaptionVolatilityStructure(QlRelinkableSwaptionVolatilityStructure *o) {return ret(new QlSwaptionVolatilityStructure(*arg(o)));}
void qlFreeSmileSection(QlSmileSection *o) {del(o);}

QlBlackVolTermStructure* qlBlackConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(new BlackConstantVol(settlementDays, *arg(x1), *arg(volatility), *arg(dayCounter))))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}
QlBlackVolTermStructure* qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(new BlackConstantVol(Date(referenceDate), *arg(x1), *arg(volatility), *arg(dayCounter))))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}
QlOptionletVolatilityStructure* qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, int type, double displacement, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(alloc(new ConstantOptionletVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), (*arg(dc)), (VolatilityType)type, displacement))));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure*>(e, er);}}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, int type, double shift, char **e) {
  try {return ret(new QlSwaptionVolatilityStructure(shared_ptr<SwaptionVolatilityStructure>(alloc(new ConstantSwaptionVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), (*arg(dc)), (VolatilityType)type, shift)))));
  } catch (std::exception& er) {return handleException<QlSwaptionVolatilityStructure*>(e, er);}}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, int type, double shift, char **e) {
  try {return ret(new QlSwaptionVolatilityStructure(shared_ptr<SwaptionVolatilityStructure>(alloc(new ConstantSwaptionVolatility(settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), (*arg(dc)), (VolatilityType)type, shift)))));
  } catch (std::exception& er) {return handleException<QlSwaptionVolatilityStructure*>(e, er);}}
double qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, int n, int u, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->blackVariance(Date(optionDate), Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, int n, int u, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->blackVariance(optionTime, Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, int n, int u, double swapLength, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->blackVariance(Period(n, (TimeUnit)u), swapLength, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureBlackVariance4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->blackVariance(Date(optionDate), swapLength, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureBlackVariance5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->blackVariance(optionTime, swapLength, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, int n, int u, int n1, int u1, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->blackVariance(Period(n, (TimeUnit)u), Period(n1, (TimeUnit)u1), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureMaxSwapLength(QlSwaptionVolatilityStructure* o, char **e) {try {return (*arg(o))->maxSwapLength();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, int *u, char **e) {
  try {const Period &p = (*arg(o))->maxSwapTenor();*u = p.units(); return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, int n, int u, int extr, char **e) {
  try {return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), Period(n, (TimeUnit)u), extr))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, int n, int u, int extr, char **e) {
  try {
    // declared but not implemented in Swaption TS for some reason:
    //return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, *arg(swapTenor), extr))));
    SwaptionVolatilityStructure *ts = handlePtr(arg(o)).get(); Time length = ts->swapLength(Period(n, (TimeUnit)u));
    return ret(new QlSmileSection(alloc(ts->smileSection(optionTime, length, extr))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, int n, int u, double swapLength, int extr, char **e) {
  try {
    // declared but not implemented in Swaption TS for some reason:
    //return ret(new QlSmileSection(alloc((*arg(o))->smileSection(*arg(optionTenor), swapLength, extr))));
    SwaptionVolatilityStructure *ts = handlePtr(arg(o)).get(); Date optionDate = ts->optionDateFromTenor(Period(n, (TimeUnit)u));
    Time optionTime = ts->timeFromReference(optionDate);
    return ret(new QlSmileSection(alloc(ts->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e) {
  try {
    // declared but not implemented in Swaption TS for some reason:
    //return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), swapLength, extr))));
    SwaptionVolatilityStructure *ts = handlePtr(arg(o)).get(); Time optionTime = ts->timeFromReference(Date(optionDate));
    return ret(new QlSmileSection(alloc(ts->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}

QlSmileSection* qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e) {
  try {return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, int n, int u, int n1, int u1, int extr, char **e) {
  try {return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Period(n, (TimeUnit)u), Period(n1, (TimeUnit)u1), extr))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlSabrSmileSection(double timeToExpiry, double forward, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new SabrSmileSection(
      timeToExpiry, forward, std::vector<Real>{alpha, beta, nu, rho}, shift, (VolatilityType)volatilityType)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
double qlSmileSectionVolatility(QlSmileSection* o, double strike, char **e) {
  try {return (*arg(o))->volatility(strike);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSmileSectionVariance(QlSmileSection* o, double strike, char **e) {
  try {return (*arg(o))->variance(strike);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSmileSection* qlSabrInterpolatedSmileSection(int optionDate, double forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, double atmVolatility, unsigned volsLen, double* vols, double alpha, double beta, double nu, double rho, int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed, int vegaWeighted, DayCounter* dc, double shift, char **e) {
  try {
    // endCriteria/optMethod are left at their empty-shared_ptr defaults (SABRInterpolation's
    // own internal EndCriteria/LevenbergMarquardt defaults apply) rather than accepting
    // Haskell-owned EndCriteria/OptimizationMethod handles here: those are raw,
    // Haskell-finalized pointers (see the qlXxxFitting comment above), and this ctor stores
    // them as shared_ptr members for the object's full lifetime, not just for the duration of
    // this call -- the same ownership hazard already avoided for FittedBondDiscountCurve's
    // fitting methods.
    ext::shared_ptr<SmileSection> section(new SabrInterpolatedSmileSection(
        Date(optionDate), forward, std::vector<Real>(strikes, strikes + strikesLen), hasFloatingStrikes,
        atmVolatility, std::vector<Real>(vols, vols + volsLen), alpha, beta, nu, rho,
        isAlphaFixed, isBetaFixed, isNuFixed, isRhoFixed, vegaWeighted,
        ext::shared_ptr<EndCriteria>(), ext::shared_ptr<OptimizationMethod>(), *arg(dc), shift));
    section->volatility(forward); // force calibration now, surfacing failures at construction
    return ret(new QlSmileSection(alloc(section)));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
double qlSabrInterpolatedSmileSectionAlpha(QlSmileSection* o, char **e) {
  try {return asSabrInterpolatedSmileSection(*arg(o))->alpha();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionBeta(QlSmileSection* o, char **e) {
  try {return asSabrInterpolatedSmileSection(*arg(o))->beta();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionNu(QlSmileSection* o, char **e) {
  try {return asSabrInterpolatedSmileSection(*arg(o))->nu();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionRho(QlSmileSection* o, char **e) {
  try {return asSabrInterpolatedSmileSection(*arg(o))->rho();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionRmsError(QlSmileSection* o, char **e) {
  try {return asSabrInterpolatedSmileSection(*arg(o))->rmsError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionMaxError(QlSmileSection* o, char **e) {
  try {return asSabrInterpolatedSmileSection(*arg(o))->maxError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlSabrInterpolatedSmileSectionEndCriteria(QlSmileSection* o, char **e) {
  try {return (int)asSabrInterpolatedSmileSection(*arg(o))->endCriteria();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlSwaptionVolatilityStructureSwapLength1(QlSwaptionVolatilityStructure* o, int start, int end, char **e) {
  try {return (*arg(o))->swapLength(Date(start), Date(end));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, int n, int u, char **e) {
  try {return (*arg(o))->swapLength(Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, int n, int u, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(Date(optionDate), Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, int n, int u, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(optionTime, Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, int n, int u, double swapLength, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(Period(n, (TimeUnit)u), swapLength, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureVolatility4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(Date(optionDate), swapLength, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureVolatility5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(optionTime, swapLength, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, int n, int u, int n1, int u1, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(Period(n, (TimeUnit)u), Period(n1, (TimeUnit)u1), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlVolatilityTermStructure* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc,
              qlPeriodVector(n, u, l), qlHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlVolatilityTermStructure*>(e, er);}}
QlVolatilityTermStructure* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {return ret(new QlVolatilityTermStructure(alloc(new CapFloorTermVolCurve(settlementDays, *arg(calendar), (BusinessDayConvention)bdc,
              qlPeriodVector(n, u, l), qlHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlVolatilityTermStructure*>(e, er);}}
QlVolatilityTermStructure* qlConstantCapFloorTermVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {return ret(new QlVolatilityTermStructure(alloc(new ConstantCapFloorTermVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlVolatilityTermStructure*>(e, er);}}
QlVolatilityTermStructure* qlConstantCapFloorTermVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {return ret(new QlVolatilityTermStructure(alloc(new ConstantCapFloorTermVolatility(settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlVolatilityTermStructure*>(e, er);}}
QlSwaptionVolatilityStructure* qlSpreadedSwaptionVolatility(QlSwaptionVolatilityStructure* x0, QlQuote* spread, char **e) {
  try {return ret(new QlSwaptionVolatilityStructure(shared_ptr<SwaptionVolatilityStructure>(alloc(new SpreadedSwaptionVolatility(*arg(x0), *arg(spread))))));
  } catch (std::exception& er) {return handleException<QlSwaptionVolatilityStructure*>(e, er);}}

void qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o) {del(o);}
QlVolatilityTermStructure* qlCapFloorTermVolSurfaceAsVolatilityTermStructure(QlCapFloorTermVolSurface *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}
void qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o) {del(o);}
QlVolatilityTermStructure* qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}
void qlFreeBlackVarianceCurve(QlBlackVarianceCurve *o) {del(o);}
QlBlackVolTermStructure* qlBlackVarianceCurveAsBlackVolTermStructure(QlBlackVarianceCurve *o) {return ret(new QlBlackVolTermStructure(*arg(o)));}
QlLocalVolTermStructure* qlLocalConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new LocalConstantVol(settlementDays, *arg(x1), *arg(volatility), *arg(dayCounter)))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
QlLocalVolTermStructure* qlLocalConstantVol(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new LocalConstantVol(Date(referenceDate), *arg(volatility), *arg(dayCounter)))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
QlLocalVolTermStructure* qlLocalVolCurve(QlBlackVarianceCurve* curve, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new LocalVolCurve(Handle<BlackVarianceCurve>(*arg(curve))))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
QlLocalVolTermStructure* qlLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new LocalVolSurface(*arg(blackTS), *arg(riskFreeTS), *arg(dividendTS), *arg(underlying)))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
QlBlackVolTermStructure* qlImpliedVolTermStructure(QlBlackVolTermStructure* origTS, int referenceDate, char **e) {
  try {return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(new ImpliedVolTermStructure(*arg(origTS), Date(referenceDate))))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}

QlBlackVarianceCurve* qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, int interpolator, int approximator, int approximatorArg, char **e) {
  BlackVarianceCurve *c = 0;
  try {
    c = new BlackVarianceCurve(Date(referenceDate), qlDateVector(dates, datesLen), std::vector<double>(blackVolCurve, blackVolCurve+blackVolCurveLen), *arg(dayCounter), forceMonotoneVariance);
    if (interpolator != Null<Integer>())
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
    s = new BlackVarianceSurface(Date(referenceDate), *arg(cal), qlDateVector(dates, datesLen), std::vector<double>(strikes, strikes+strikesLen), qlMatrix(blackVolMatrix, blackVolMatrixRows, blackVolMatrixCols), *arg(dayCounter), (BlackVarianceSurface::Extrapolation)lowerExtrapolation, (BlackVarianceSurface::Extrapolation)upperExtrapolation);
    /* TODO uncomment when 2-D Interpolation is added
    if (interpolation)
      setInterpolation(s, interpolation);
    */
    return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(s))));
  } catch (std::exception& er) {delete s; return handleException<QlBlackVolTermStructure*>(e, er);}}
QlCapFloorTermVolSurface* qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(settlementDays, *arg(calendar), (BusinessDayConvention)bdc,
            qlPeriodVector(n, u, l), std::vector<double>(strikes, strikes+strikesLen), qlHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolSurface*>(e, er);}}
QlCapFloorTermVolSurface* qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc,
            qlPeriodVector(n, u, l), std::vector<double>(strikes, strikes+strikesLen), qlHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolSurface*>(e, er);}}

void qlFreeCallableBondVolatilityStructure(QlCallableBondVolatilityStructure *o) {del(o);}
QlTermStructure* qlCallableBondVolatilityStructureAsTermStructure(QlCallableBondVolatilityStructure *o) {return ret(new QlTermStructure(*arg(o)));}
void qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o) {del(o);}
QlTermStructure* qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}

QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {return ret(new QlCallableBondVolatilityStructure(alloc(new CallableBondConstantVolatility(settlementDays, *arg(x1), *arg(volatility), *arg(dayCounter)))));
  } catch (std::exception& er) {return handleException<QlCallableBondVolatilityStructure*>(e, er);}}
QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {return ret(new QlCallableBondVolatilityStructure(alloc(new CallableBondConstantVolatility(Date(referenceDate), *arg(volatility), *arg(dayCounter)))));
  } catch (std::exception& er) {return handleException<QlCallableBondVolatilityStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
  try {return ret(new QlDefaultProbabilityTermStructure(alloc(new FactorSpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), *arg(spread)))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e) {
  try {return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(settlementDays, *arg(calendar), *arg(hazardRate), (*arg(x3))))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e) {
  try {return ret(new QlDefaultProbabilityTermStructure(alloc(new FlatHazardRate(Date(referenceDate), *arg(hazardRate), (*arg(x2))))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e) {
  try {return ret(new QlDefaultProbabilityTermStructure(alloc(new SpreadedHazardRateCurve(Handle<DefaultProbabilityTermStructure>(*arg(originalCurve)), *arg(spread)))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedDefaultDensityCurveAux(qlDateVector(dates, datesLen), std::vector<double>(densities, densities+densitiesLen), *arg(dayCounter), *arg(calendar), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), interpolator, approximator, approximatorArg))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e) {
  try {
    DefaultProbabilityTermStructure *ts = qlInterpolatedHazardRateCurveAux(qlDateVector(dates, datesLen), std::vector<double>(hazardRates, hazardRates+hazardRatesLen), *arg(dayCounter), *arg(cal), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), interpolator, approximator, approximatorArg);
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {return ret(new QlDefaultProbabilityTermStructure(alloc(qlInterpolatedSurvivalProbabilityCurveAux(qlDateVector(dates, datesLen), std::vector<double>(probabilities, probabilities+probabilitiesLen), *arg(dayCounter), *arg(calendar), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), interpolator, approximator, approximatorArg))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}

void qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o) {del(o);}

QlDefaultProbabilityHelper* qlSpreadCdsHelper(QlQuote* runningSpread, int n, int u, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, int startDate, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int model, char **e) {
  try {return ret(new QlDefaultProbabilityHelper(alloc(new SpreadCdsHelper(*arg(runningSpread), Period(n, (TimeUnit)u), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, *arg(discountCurve), settlesAccrual, paysAtDefaultTime,
            qlNullableDate(startDate), *arg(lastPeriodDayCounter), rebatesAccrual, (CreditDefaultSwap::PricingModel)model))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityHelper*>(e, er);}}
QlDefaultProbabilityHelper* qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, int n, int u, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, int startDate, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int model, char **e) {
  try {return ret(new QlDefaultProbabilityHelper(alloc(new UpfrontCdsHelper(*arg(upfront), runningSpread, Period(n, (TimeUnit)u), settlementDays, *arg(calendar), (Frequency)frequency, (BusinessDayConvention)paymentConvention, (DateGeneration::Rule)rule, *arg(dayCounter), recoveryRate, *arg(discountCurve), upfrontSettlementDays, settlesAccrual, paysAtDefaultTime,
            qlNullableDate(startDate), *arg(lastPeriodDayCounter), rebatesAccrual, (CreditDefaultSwap::PricingModel)model))));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityHelper*>(e, er);}}
QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve(int referenceDate, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    DefaultProbabilityTermStructure *ts = qlPiecewiseDefaultCurveAux(Date(referenceDate), qlVector(instruments, instrumentsLen), *arg(dayCounter), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), trait, interpolator, approximator, approximatorArg);
    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve1(unsigned settlementDays, Calendar *calendar, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    DefaultProbabilityTermStructure *ts = qlPiecewiseDefaultCurveAux1(settlementDays, *arg(calendar), qlVector(instruments, instrumentsLen), *arg(dayCounter), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), trait, interpolator, approximator, approximatorArg);
    return ret(new QlDefaultProbabilityTermStructure(alloc(ts)));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
double qlDefaultProbabilityTermStructureDefaultDensity1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->defaultDensity(t, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureDefaultDensity(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {return (*arg(o))->defaultDensity(Date(d), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureDefaultProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->defaultProbability(t, (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureDefaultProbability2(QlDefaultProbabilityTermStructure* o, int x1, int x2, int extrapolate, char **e) {
  try {return (*arg(o))->defaultProbability(Date(x1), Date(x2), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureDefaultProbability3(QlDefaultProbabilityTermStructure* o, double x1, double x2, int extrapo, char **e) {
  try {return (*arg(o))->defaultProbability(x1, x2, extrapo);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureDefaultProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {return (*arg(o))->defaultProbability(Date(d), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureHazardRate1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->hazardRate(t, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureHazardRate(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {return (*arg(o))->hazardRate(Date(d), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureSurvivalProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->survivalProbability(t, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlDefaultProbabilityTermStructureSurvivalProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e) {
  try {return (*arg(o))->survivalProbability(Date(d), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

void qlFreeZeroInflationTermStructure(QlZeroInflationTermStructure *o) {del(o);}
QlTermStructure* qlZeroInflationTermStructureAsTermStructure(QlZeroInflationTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}
double qlZeroInflationTermStructureZeroRate(QlZeroInflationTermStructure* o, int d, int extrapolate, char **e) {
  try {return (*arg(o))->zeroRate(Date(d), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeYoYInflationTermStructure(QlYoYInflationTermStructure *o) {del(o);}
QlTermStructure* qlYoYInflationTermStructureAsTermStructure(QlYoYInflationTermStructure *o) {return ret(new QlTermStructure(*arg(o)));}
double qlYoYInflationTermStructureYoYRate(QlYoYInflationTermStructure* o, int d, int extrapolate, char **e) {
  try {return (*arg(o))->yoyRate(Date(d), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

void qlFreeZeroCouponInflationSwapHelper(QlZeroCouponInflationSwapHelper *o) {del(o);}
QlZeroCouponInflationSwapHelper* qlZeroCouponInflationSwapHelper(QlQuote* quote, int n, int u, int maturity, Calendar* calendar, int paymentConvention, DayCounter* dayCounter, QlZeroInflationIndex* zii, int observationInterpolation, int pillar, int customPillarDate, char **e) {
  try {return ret(new QlZeroCouponInflationSwapHelper(alloc(new ZeroCouponInflationSwapHelper(*arg(quote), Period(n, (TimeUnit)u), Date(maturity),
          *arg(calendar), (BusinessDayConvention)paymentConvention, *arg(dayCounter), *arg(zii),
          observationInterpolation == 0 ? CPI::Flat : CPI::Linear, (Pillar::Choice)pillar, qlNullableDate(customPillarDate)))));
  } catch (std::exception& er) {return handleException<QlZeroCouponInflationSwapHelper*>(e, er);}}

void qlFreeYearOnYearInflationSwapHelper(QlYearOnYearInflationSwapHelper *o) {del(o);}
QlYearOnYearInflationSwapHelper* qlYearOnYearInflationSwapHelper(QlQuote* quote, int n, int u, int maturity, Calendar* calendar, int paymentConvention, DayCounter* dayCounter, QlYoYInflationIndex* yii, int observationInterpolation, QlYieldTermStructure* nominalTermStructure, int pillar, int customPillarDate, char **e) {
  try {return ret(new QlYearOnYearInflationSwapHelper(alloc(new YearOnYearInflationSwapHelper(*arg(quote), Period(n, (TimeUnit)u), Date(maturity),
          *arg(calendar), (BusinessDayConvention)paymentConvention, *arg(dayCounter), *arg(yii),
          observationInterpolation == 0 ? CPI::Flat : CPI::Linear, *arg(nominalTermStructure), (Pillar::Choice)pillar, qlNullableDate(customPillarDate)))));
  } catch (std::exception& er) {return handleException<QlYearOnYearInflationSwapHelper*>(e, er);}}

QlZeroInflationTermStructure* qlPiecewiseZeroInflationCurve(int referenceDate, int baseDate, int frequency, DayCounter* dayCounter, unsigned instrumentsLen, QlZeroCouponInflationSwapHelper** instruments, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    // instruments[i] is shared_ptr<ZeroCouponInflationSwapHelper>*; push_back upcasts each
    // element to shared_ptr<BootstrapHelper<ZeroInflationTermStructure>> (PiecewiseZeroInflationCurve's
    // helper type) -- qlVector can't do this since it deduces the vector's element type from the
    // array's pointee type, not the target parameter type.
    std::vector<shared_ptr<BootstrapHelper<ZeroInflationTermStructure> > > instr;
    instr.reserve(instrumentsLen);
    for (unsigned i = 0; i < instrumentsLen; ++i) instr.push_back(*instruments[i]);
    ZeroInflationTermStructure *ts = qlPiecewiseZeroInflationCurveAux(Date(referenceDate), Date(baseDate), (Frequency)frequency, *arg(dayCounter),
        instr, interpolator, approximator, approximatorArg);
    return ret(new QlZeroInflationTermStructure(alloc(ts)));
  } catch (std::exception& er) {return handleException<QlZeroInflationTermStructure*>(e, er);}}
QlYoYInflationTermStructure* qlPiecewiseYoYInflationCurve(int referenceDate, int baseDate, double baseYoYRate, int frequency, DayCounter* dayCounter, unsigned instrumentsLen, QlYearOnYearInflationSwapHelper** instruments, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    std::vector<shared_ptr<BootstrapHelper<YoYInflationTermStructure> > > instr;
    instr.reserve(instrumentsLen);
    for (unsigned i = 0; i < instrumentsLen; ++i) instr.push_back(*instruments[i]);
    YoYInflationTermStructure *ts = qlPiecewiseYoYInflationCurveAux(Date(referenceDate), Date(baseDate), baseYoYRate, (Frequency)frequency, *arg(dayCounter),
        instr, interpolator, approximator, approximatorArg);
    return ret(new QlYoYInflationTermStructure(alloc(ts)));
  } catch (std::exception& er) {return handleException<QlYoYInflationTermStructure*>(e, er);}}

QlRateHelper *qlDepositRateHelper(QlQuote *quote, int l, int u, unsigned fixDays, Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e) {
  try {return ret(new QlRateHelper(new DepositRateHelper( *arg(quote), Period(l, (TimeUnit)u), fixDays,
          *arg(calendar), (BusinessDayConvention) conv, eom, *arg(dayCount))));
  } catch (std::exception& er) {return handleException<QlRateHelper *>(e, er);}}
QlBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
    Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv, double redemption, int issue, char **e) {
  try {return ret(new QlBondHelper(new FixedRateBondHelper(*arg(quote), settlDays, face, *arg(sched),
          std::vector<Rate>(coupons, coupons+cLen), *arg(dayCount), (BusinessDayConvention) conv, redemption, qlNullableDate(issue))));
  } catch (std::exception& er) {return handleException<QlBondHelper *>(e, er);}}
QlBondHelper *qlCPIBondHelper(QlQuote *quote, unsigned settlementDays, double faceAmount, double baseCPI, int obsLagLen, int obsLagUnit,
    QlZeroInflationIndex* index, int observationInterpolation, Schedule *schedule, unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter,
    int paymentConvention, int issueDate, Calendar *paymentCalendar, char **e) {
  try {return ret(new QlBondHelper(new CPIBondHelper(*arg(quote), settlementDays, faceAmount, baseCPI, Period(obsLagLen, (TimeUnit)obsLagUnit),
          *arg(index), (CPI::InterpolationType)observationInterpolation, *arg(schedule), std::vector<Rate>(coupons, coupons+couponsLen),
          *arg(accrualDayCounter), (BusinessDayConvention)paymentConvention, qlNullableDate(issueDate), *arg(paymentCalendar))));
  } catch (std::exception& er) {return handleException<QlBondHelper *>(e, er);}}
void qlFreeRateHelper(QlRateHelper *helper) {del(helper);}

QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  YieldTermStructure *ts = 0;
  try {
    ts = qlPiecewiseYieldCurveAux(Date(date), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), trait, interpolator, approximator, approximatorArg);
    return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(ts))));
  } catch (std::exception& er) {delete ts; return handleException<QlYieldTermStructure *>(e, er);}}

typedef YieldTermStructure *(*curveBuilder)( const std::vector<Date>& dates, const std::vector<double>& dfs, const DayCounter& dayCount, const Calendar& cal,
  const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates, int interpolator, int approximator, int approximatorArg);

QlYieldTermStructure *qlInterpolatedCurve(curveBuilder builder, unsigned rateLen, double *rates, unsigned rateDatesLen, int *rateDates,
  DayCounter *dayCount, Calendar *cal, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    YieldTermStructure *ts = builder(qlDateVector(rateDates, rateDatesLen), std::vector<double>(rates, rates+rateLen), *arg(dayCount), *arg(cal),
        qlHandleVector(quotes, quoteLen), qlDateVector(dates, datesLen), interpolator, approximator, approximatorArg);
    return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(ts))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}
QlYieldTermStructure *qlInterpolatedDiscountCurve(unsigned dfsLen, double *dfs, unsigned dfdatesLen, int *dfsDates, DayCounter *dayCount, Calendar *cal,
  unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedDiscountCurveAux, dfsLen, dfs, dfdatesLen, dfsDates,
    dayCount, cal, quoteLen, quotes, datesLen, dates, interpolator, approximator, approximatorArg, e);
}
QlYieldTermStructure *qlInterpolatedForwardCurve(unsigned fwdLen, double *fwds, unsigned fwddatesLen, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedForwardCurveAux, fwdLen, fwds, fwddatesLen, fwdDates,
    dayCount, cal, quoteLen, quotes, datesLen, dates, interpolator, approximator, approximatorArg, e);
}
QlYieldTermStructure *qlInterpolatedZeroCurve(unsigned yieldLen, double *yields, unsigned ydatesLen, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedZeroCurveAux, yieldLen, yields, ydatesLen, yieldDates,
    dayCount, cal, quoteLen, quotes,  datesLen, dates, interpolator, approximator, approximatorArg, e);
}
QlYieldTermStructure *qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e) {
  try {
    YieldTermStructure *ts = qlPiecewiseYieldCurveAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), trait, interpolator, approximator, approximatorArg);
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(ts))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}
double qlYieldTSDiscount(QlYieldTermStructure *ts, int date, int extrapolate, char **e) {
  try {return (*ts)->discount(Date(date), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSwapRateHelper *qlSwapRateHelper1(QlQuote *q, int l, int u, Calendar *cal, int freq,
  int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, int fl, int fu, QlYieldTermStructure *ts,
  unsigned settlementDays, int pillar, int customPillarDate, int endOfMonth, int useIndexedCoupons,
  int floatConvention, QlFloatingRateCouponPricer *couponPricer, char **e) {
  try {
    return ret(new QlSwapRateHelper(new SwapRateHelper(*arg(q),
	    Period(l, (TimeUnit)u), *arg(cal), (Frequency) freq, (BusinessDayConvention) conv, *arg(dc), *arg(i),
            qlNullableHandle(arg(s)),
            Period(fl, (TimeUnit)fu), qlNullableHandle(arg(ts)),
            settlementDays, (Pillar::Choice)pillar, qlNullableDate(customPillarDate), endOfMonth,
            qlOptBool(useIndexedCoupons),
            qlOptBusinessDayConvention(floatConvention),
            couponPricer ? *arg(couponPricer) : ext::shared_ptr<FloatingRateCouponPricer>())));
  } catch (std::exception& er) {return handleException<QlSwapRateHelper *>(e, er);}}
QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new FlatForward(Date(referenceDate), *arg(forward), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new FlatForward(settlementDays, *arg(calendar), *arg(forward), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

void qlFreeFittedBondDiscountCurveFittingMethod(FittedBondDiscountCurveFittingMethod *o) {del(o);}

// generated functions
InterestRate* qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
try {return ret(new InterestRate((*arg(o))->zeroRate(Date(d), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}
InterestRate* qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, int l, int u, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {return ret(new InterestRate((*arg(o))->forwardRate(Date(d), Period(l, (TimeUnit)u), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}
InterestRate* qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e) {
  try {return ret(new InterestRate((*arg(o))->forwardRate(Date(d1), Date(d2), *arg(resultDayCounter), (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}
InterestRate* qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e) {
  try {return ret(new InterestRate((*arg(o))->forwardRate(t1, t2, (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}
InterestRate* qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e) {
  try {return ret(new InterestRate((*arg(o))->zeroRate(t, (Compounding)comp, (Frequency)freq, extrapolate)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}
double qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->discount(t, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlRateHelper* qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, int pillar, int customPillarDate, int useIndexedCoupon, char **e) {
  try {return ret(new QlRateHelper(alloc(new FraRateHelper(*arg(rate), monthsToStart, monthsToEnd, fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter), (Pillar::Choice)pillar, qlNullableDate(customPillarDate), useIndexedCoupon))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
// Each shim below binds the sibling overload that omits the leading
// `optimizationMethod` param, not the primary ctor -- OptimizationMethod's
// hasquant-side handle is a raw, Haskell-finalized pointer (see
// qlLevenbergMarquardt/qlSimplex), not a QlXxx shared_ptr box, and
// FittedBondDiscountCurve additionally clones its fitting method, so there
// is no safe way to hand it into a `const ext::shared_ptr<OptimizationMethod>&`
// slot without a real ownership-representation change (would also touch
// qlGsrCalibrateVolatilitiesIterative/qlCalibratedModelCalibrate) -- see the
// README TODO.
FittedBondDiscountCurveFittingMethod* qlCubicBSplinesFitting(unsigned knotVectorLen, double *knotVector, int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, Constraint* constraint, char **e) {
  try {return alloc(new CubicBSplinesFitting(std::vector<double>(knotVector, knotVector+knotVectorLen), constrainAtZero, Array(weights, weights+weightsLen), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlExponentialSplinesFitting(int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, unsigned numCoeffs, double fixedKappa, Constraint* constraint, char **e) {
  try {return alloc(new ExponentialSplinesFitting(constrainAtZero, Array(weights, weights+weightsLen), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, numCoeffs, fixedKappa, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlNelsonSiegelFitting(unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, Constraint* constraint, char **e) {
  try {return alloc(new NelsonSiegelFitting(Array(weights, weights+weightsLen), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, Constraint* constraint, char **e) {
  try {return alloc(new SimplePolynomialFitting(degree, constrainAtZero, Array(weights, weights+weightsLen), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlSvenssonFitting(unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, Constraint* constraint, char **e) {
  try {return alloc(new SvenssonFitting(Array(weights, weights+weightsLen), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
QlFittedBondDiscountCurve* qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e) {
  try {return ret(new QlFittedBondDiscountCurve(alloc(new FittedBondDiscountCurve(settlementDays, *arg(calendar), qlVector(bonds, bondsLen), *arg(dayCounter), *arg(fittingMethod), accuracy, maxEvaluations, Array(guess, guess+guessLen), simplexLambda))));
  } catch (std::exception& er) {return handleException<QlFittedBondDiscountCurve*>(e, er);}}
QlFittedBondDiscountCurve* qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurveFittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e) {
  try {return ret(new QlFittedBondDiscountCurve(alloc(new FittedBondDiscountCurve(Date(referenceDate), qlVector(bonds, bondsLen), *arg(dayCounter), *arg(fittingMethod), accuracy, maxEvaluations, Array(guess, guess+guessLen), simplexLambda))));
  } catch (std::exception& er) {return handleException<QlFittedBondDiscountCurve*>(e, er);}}

double qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve *o, char **e) {try {return (*arg(o))->fitResults().minimumCostValue();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve *o, char **e) {try {return (*arg(o))->fitResults().numberOfIterations();} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlFreeYieldTermStructure(QlYieldTermStructure *ts) {del(ts);}

// A relinkable handle, empty when `initial` is null. An empty handle is meaningful, not an
// error: it is what makes a rate helper discount off the curve being bootstrapped.
QlRelinkableYieldTermStructure* qlRelinkableYieldTermStructure(QlYieldTermStructure *initial, char **e) {
  try {return ret(initial ? new QlRelinkableYieldTermStructure(handlePtr(arg(initial)))
                          : new QlRelinkableYieldTermStructure());
  } catch (std::exception& er) {return handleException<QlRelinkableYieldTermStructure*>(e, er);}}
void qlFreeRelinkableYieldTermStructure(QlRelinkableYieldTermStructure *o) {del(o);}
void qlRelinkableYieldTermStructureLinkTo(QlRelinkableYieldTermStructure *o, QlYieldTermStructure *c, char **e) {
  try {arg(o)->linkTo(handlePtr(arg(c)));} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
// The hierarchy upcast. Copy-constructing Handle<YieldTermStructure> from
// RelinkableHandle<YieldTermStructure> is the same T, so link_ is shared and relinking
// through the original still reaches everything built on the upcast copy. This is the
// whole reason the design works.
QlYieldTermStructure* qlRelinkableYieldTermStructureAsYieldTermStructure(QlRelinkableYieldTermStructure *o) {
  return ret(new QlYieldTermStructure(*arg(o)));}
void qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o) {del(o);}
QlYieldTermStructure* qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o) {return ret(new QlYieldTermStructure(*arg(o)));}
void qlFreeBondHelper(QlBondHelper *o) {del(o);}
QlRateHelper* qlBondHelperAsRateHelper(QlBondHelper *o) {return ret(new QlRateHelper(*arg(o)));}
void qlFreeSwapRateHelper(QlSwapRateHelper *o) {del(o);}
QlRateHelper* qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o) {return ret(new QlRateHelper(*arg(o)));}
void qlFreeOISRateHelper(QlOISRateHelper *o) {del(o);}
QlRateHelper* qlOISRateHelperAsRateHelper(QlOISRateHelper *o) {return ret(new QlRateHelper(*arg(o)));}
void qlFreeTermStructure(QlTermStructure *o) {del(o);}
QlTermStructure* qlYieldTermStructureAsTermStructure(QlYieldTermStructure *o) {return ret(new QlTermStructure(handlePtr(arg(o))));}

QlBondHelper* qlBondHelper(QlQuote* cleanPrice, QlBond* bond, int priceType, char **e) {
  try {return ret(new QlBondHelper(alloc(new BondHelper(*arg(cleanPrice), *arg(bond), (Bond::Price::Type)priceType))));
  } catch (std::exception& er) {return handleException<QlBondHelper*>(e, er);}}
QlOISRateHelper* qlOISRateHelper(unsigned settlementDays, int l, int u, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve,
  int telescopicValueDates, int paymentLag, int paymentConvention, int paymentFrequency, Calendar* paymentCalendar,
  int fl, int fu, QlQuote* overnightSpread, int pillar, int customPillarDate, int averagingMethod, int endOfMonth, int fixedPaymentFrequency,
  Calendar* fixedCalendar, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift,
  QlFloatingRateCouponPricer* pricer, int rule, Calendar* overnightCalendar, int convention, char **e) {
  try {return ret(new QlOISRateHelper(alloc(new OISRateHelper(settlementDays, Period(l, (TimeUnit)u), *arg(fixedRate), *arg(overnightIndex), qlNullableHandle(arg(discountingCurve)),
    telescopicValueDates, paymentLag, (BusinessDayConvention)paymentConvention, (Frequency)paymentFrequency, *arg(paymentCalendar),
    Period(fl, (TimeUnit)fu),
    overnightSpread ? std::variant<Spread, Handle<Quote>>(*arg(overnightSpread)) : std::variant<Spread, Handle<Quote>>(Spread(0.0)),
    (Pillar::Choice)pillar, qlNullableDate(customPillarDate), (RateAveraging::Type)averagingMethod, qlOptBool(endOfMonth),
    fixedPaymentFrequency < 0 ? ext::optional<Frequency>() : ext::optional<Frequency>((Frequency)fixedPaymentFrequency),
    *arg(fixedCalendar), lookbackDays, lockoutDays, applyObservationShift,
    pricer ? *arg(pricer) : ext::shared_ptr<FloatingRateCouponPricer>(), (DateGeneration::Rule)rule, *arg(overnightCalendar), (BusinessDayConvention)convention))));
  } catch (std::exception& er) {return handleException<QlOISRateHelper*>(e, er);}}
QlOISRateHelper* qlOISRateHelper2(int start, int end, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve,
  int telescopicValueDates, int paymentLag, int paymentConvention, int paymentFrequency, Calendar* paymentCalendar,
  QlQuote* overnightSpread, int pillar, int customPillarDate, int averagingMethod, int endOfMonth, int fixedPaymentFrequency,
  Calendar* fixedCalendar, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift,
  QlFloatingRateCouponPricer* pricer, int rule, Calendar* overnightCalendar, int convention, char **e) {
    try {return ret(new QlOISRateHelper(alloc(new OISRateHelper(Date(start), Date(end), *arg(fixedRate), *arg(overnightIndex), qlNullableHandle(arg(discountingCurve)),
    telescopicValueDates, paymentLag, (BusinessDayConvention)paymentConvention, (Frequency)paymentFrequency, *arg(paymentCalendar),
    overnightSpread ? std::variant<Spread, Handle<Quote>>(*arg(overnightSpread)) : std::variant<Spread, Handle<Quote>>(Spread(0.0)),
    (Pillar::Choice)pillar, qlNullableDate(customPillarDate), (RateAveraging::Type)averagingMethod, qlOptBool(endOfMonth),
    fixedPaymentFrequency < 0 ? ext::optional<Frequency>() : ext::optional<Frequency>((Frequency)fixedPaymentFrequency),
    *arg(fixedCalendar), lookbackDays, lockoutDays, applyObservationShift,
    pricer ? *arg(pricer) : ext::shared_ptr<FloatingRateCouponPricer>(), (DateGeneration::Rule)rule, *arg(overnightCalendar), (BusinessDayConvention)convention))));
  } catch (std::exception& er) {return handleException<QlOISRateHelper*>(e, er);}}
QlSwapRateHelper* qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, int fl, int fu, QlYieldTermStructure* discountingCurve,
  int pillar, int customPillarDate, int endOfMonth, int useIndexedCoupons, QlFloatingRateCouponPricer *couponPricer, char **e) {
  try {return ret(new QlSwapRateHelper(alloc(new SwapRateHelper(*arg(rate), *arg(swapIndex), qlNullableHandle(arg(spread)), Period(fl, (TimeUnit)fu), qlNullableHandle(arg(discountingCurve)),
          (Pillar::Choice)pillar, qlNullableDate(customPillarDate), endOfMonth,
          qlOptBool(useIndexedCoupons),
          couponPricer ? *arg(couponPricer) : ext::shared_ptr<FloatingRateCouponPricer>()))));
  } catch (std::exception& er) {return handleException<QlSwapRateHelper*>(e, er);}}

QlYieldTermStructure* qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new ForwardSpreadedTermStructure(*arg(x0), *arg(spread))))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

QlYieldTermStructure* qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new ZeroSpreadedTermStructure(*arg(x0), *arg(spread), (Compounding)comp, (Frequency)freq)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

QlRateHelper* qlBMASwapRateHelper(QlQuote* liborFraction, int tl, int tu, unsigned settlementDays, Calendar* calendar, int bl, int bu, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e) {
  try {return ret(new QlRateHelper(alloc(new BMASwapRateHelper(*arg(liborFraction), Period(tl, (TimeUnit)tu), settlementDays, *arg(calendar), Period(bl, (TimeUnit)bu), (BusinessDayConvention)bmaConvention, *arg(bmaDayCount), *arg(bmaIndex), *arg(index)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e) {
  try {return ret(new QlRateHelper(alloc(new DepositRateHelper(*arg(rate), *arg(iborIndex)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, int pillar, int customPillarDate, int useIndexedCoupon, char **e) {
  try {return ret(new QlRateHelper(alloc(new FraRateHelper(*arg(rate), monthsToStart, *arg(iborIndex), (Pillar::Choice)pillar, qlNullableDate(customPillarDate), useIndexedCoupon))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlFraRateHelper2(QlQuote* rate, int l, int u, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, int pillar, int customPillarDate, int useIndexedCoupon, char **e) {
  try {return ret(new QlRateHelper(alloc(new FraRateHelper(*arg(rate), Period(l, (TimeUnit)u), lengthInMonths, fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter), (Pillar::Choice)pillar, qlNullableDate(customPillarDate), useIndexedCoupon))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlFraRateHelper3(QlQuote* rate, int l, int u, QlIborIndex* iborIndex, int pillar, int customPillarDate, int useIndexedCoupon, char **e) {
  try {return ret(new QlRateHelper(alloc(new FraRateHelper(*arg(rate), Period(l, (TimeUnit)u), *arg(iborIndex), (Pillar::Choice)pillar, qlNullableDate(customPillarDate), useIndexedCoupon))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, int type, char **e) {
  try {return ret(new QlRateHelper(alloc(new FuturesRateHelper(*arg(price), Date(immStartDate), Date(endDate), *arg(dayCounter), qlNullableHandle(arg(convexityAdjustment)), (Futures::Type)type))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e) {
  try {return ret(new QlRateHelper(alloc(new FuturesRateHelper(*arg(price), Date(immDate), *arg(iborIndex), qlNullableHandle(arg(convexityAdjustment))))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, int type, char **e) {
  try {return ret(new QlRateHelper(alloc(new FuturesRateHelper(*arg(price), Date(immDate), lengthInMonths, *arg(calendar), (BusinessDayConvention)convention, endOfMonth, *arg(dayCounter), qlNullableHandle(arg(convexityAdjustment)), (Futures::Type)type))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
double qlRateHelperImpliedQuote(QlRateHelper* o, char **e) {try {return (*arg(o))->impliedQuote();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlBond* qlBondHelperBond(QlBondHelper* o, char **e) {try {return ret(new QlBond((*arg(o))->bond()));} catch (std::exception& er) {return handleException<QlBond*>(e, er);}}
QlOvernightIndexedSwap* qlOISRateHelperSwap(QlOISRateHelper* o, char **e) {
  try {return ret(new QlOvernightIndexedSwap((*arg(o))->swap()));
  } catch (std::exception& er) {return handleException<QlOvernightIndexedSwap*>(e, er);}}
QlVanillaSwap* qlSwapRateHelperSwap(QlSwapRateHelper* o, char **e) {try {return ret(new QlVanillaSwap((*arg(o))->swap()));} catch (std::exception& er) {return handleException<QlVanillaSwap*>(e, er);} }
int qlTermStructureReferenceDate(QlTermStructure* o, char **e) {try {return (*arg(o))->referenceDate().serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlTermStructureMaxDate(QlTermStructure* o, char **e) {try {return (*arg(o))->maxDate().serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
QlYieldTermStructure* qlImpliedTermStructure(QlYieldTermStructure* x0, int referenceDate, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new ImpliedTermStructure(*arg(x0), Date(referenceDate))))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

QlYieldTermStructure* qlPiecewiseZeroSpreadedTermStructure(QlYieldTermStructure* x0, unsigned spreadsLen, QlQuote** spreads, unsigned datesLen, int* dates, int comp, int freq, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new PiecewiseZeroSpreadedTermStructure(*arg(x0), qlHandleVector(spreads, spreadsLen), qlDateVector(dates, datesLen), (Compounding)comp, (Frequency)freq)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure* qlQuantoTermStructure(QlYieldTermStructure* underlyingDividendTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* foreignRiskFreeTS, QlBlackVolTermStructure* underlyingBlackVolTS, double strike, QlBlackVolTermStructure* exchRateBlackVolTS, double exchRateATMlevel, double underlyingExchRateCorrelation, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new QuantoTermStructure(*arg(underlyingDividendTS), *arg(riskFreeTS), *arg(foreignRiskFreeTS), *arg(underlyingBlackVolTS), strike, *arg(exchRateBlackVolTS), exchRateATMlevel, underlyingExchRateCorrelation)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

void qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e) {try {(*arg(i))->addFixing(Date(date), fix, overwrite);} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
typedef SwapIndex *(*makeSwapIndex)(const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2);
// must match with the order of qlEnumObjects.h:LiborSwapIndexType
static const makeSwapIndex swapIndices[] = {
    [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new ChfLiborSwapIsdaFix(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new EurLiborSwapIfrFix(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new EurLiborSwapIsdaFixA(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new EurLiborSwapIsdaFixB(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new EuriborSwapIfrFix(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new EuriborSwapIsdaFixA(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new EuriborSwapIsdaFixB(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new GbpLiborSwapIsdaFix(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new JpyLiborSwapIsdaFixAm(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new JpyLiborSwapIsdaFixPm(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new UsdLiborSwapIsdaFixAm(p, h1, h2));}
  , [](const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2){return static_cast<SwapIndex *>(new UsdLiborSwapIsdaFixPm(p, h1, h2));}
};

QlSwapIndex* qlCreateLiborSwapIndex(int index, int l, int u, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(swapIndices))
      QL_FAIL("Invalid swap index index" << index);
    QlYieldTermStructure ts1 = qlNullableHandle(h1);
    QlYieldTermStructure ts2 = qlNullableHandle(h2);
    SwapIndex *i = swapIndices[index](Period(l, (TimeUnit)u), ts1, ts2);
    return ret(new QlSwapIndex(alloc(i)));
  } catch (std::exception& er) {return handleException<QlSwapIndex*>(e, er);}}

void qlFreeIndex(QlIndex *i) {del(i);}
void qlFreeInterestRateIndex(QlInterestRateIndex *o) {del(o);}
QlIndex* qlInterestRateIndexAsIndex(QlInterestRateIndex *o) {return ret(new QlIndex(*arg(o)));}
void qlFreeSwapIndex(QlSwapIndex *o) {del(o);}
QlInterestRateIndex* qlSwapIndexAsInterestRateIndex(QlSwapIndex *o) {return ret(new QlInterestRateIndex(*arg(o)));}
void qlFreeBMAIndex(QlBMAIndex *o) {del(o);}
QlInterestRateIndex* qlBMAIndexAsInterestRateIndex(QlBMAIndex *o) {return ret(new QlInterestRateIndex(*arg(o)));}
void qlFreeOvernightIndexedSwapIndex(QlOvernightIndexedSwapIndex *o) {del(o);}
QlSwapIndex* qlOvernightIndexedSwapIndexAsSwapIndex(QlOvernightIndexedSwapIndex *o) {return ret(new QlSwapIndex(*arg(o)));}

QlBMAIndex* qlBMAIndex(QlYieldTermStructure* h, char **e) {
  try {return ret(new QlBMAIndex(alloc(new BMAIndex(qlNullableHandle(arg(h))))));
  } catch (std::exception& er) {return handleException<QlBMAIndex*>(e, er);}}
QlOvernightIndexedSwapIndex* qlOvernightIndexedSwapIndex(char* familyName, int l, int u, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, int telescopicValueDates, int averagingMethod, char **e) {
  try {return ret(new QlOvernightIndexedSwapIndex(alloc(new OvernightIndexedSwapIndex(std::string(arg(familyName)), Period(l, (TimeUnit)u), settlementDays, *arg(currency), *arg(overnightIndex), telescopicValueDates, (RateAveraging::Type)averagingMethod))));
  } catch (std::exception& er) {return handleException<QlOvernightIndexedSwapIndex*>(e, er);}}
QlSwapIndex* qlSwapIndex1(char* familyName, int l, int u, unsigned settlementDays, Currency* currency, Calendar* calendar, int fl, int fu, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, QlYieldTermStructure* discountingTermStructure, char **e) {
  try {return ret(new QlSwapIndex(alloc(new SwapIndex(std::string(arg(familyName)), Period(l, (TimeUnit)u), settlementDays, *arg(currency), *arg(calendar), Period(fl, (TimeUnit)fu), (BusinessDayConvention)fixedLegConvention, *arg(fixedLegDayCounter), *arg(iborIndex), *arg(discountingTermStructure)))));
  } catch (std::exception& er) {return handleException<QlSwapIndex*>(e, er);}}
QlSwapIndex* qlSwapIndex(char* familyName, int l, int u, unsigned settlementDays, Currency* currency, Calendar* calendar, int fl, int fu, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, char **e) {
  try {return ret(new QlSwapIndex(alloc(new SwapIndex(std::string(arg(familyName)), Period(l, (TimeUnit)u), settlementDays, *arg(currency), *arg(calendar), Period(fl, (TimeUnit)fu), (BusinessDayConvention)fixedLegConvention, *arg(fixedLegDayCounter), *arg(iborIndex)))));
  } catch (std::exception& er) {return handleException<QlSwapIndex*>(e, er);}}
Schedule* qlBMAIndexFixingSchedule(QlBMAIndex* o, int start, int end, char **e) {
  try {return ret(new Schedule((*arg(o))->fixingSchedule(Date(start), Date(end))));
  } catch (std::exception& er) {return handleException<Schedule*>(e, er);}}
QlOvernightIndexedSwap* qlOvernightIndexedSwapIndexUnderlyingSwap(QlOvernightIndexedSwapIndex* o, int fixingDate, char **e) {
  try {return ret(new QlOvernightIndexedSwap((*arg(o))->underlyingSwap(Date(fixingDate))));
  } catch (std::exception& er) {return handleException<QlOvernightIndexedSwap*>(e, er);}}
QlVanillaSwap* qlSwapIndexUnderlyingSwap(QlSwapIndex* o, int fixingDate, char **e) {
  try {return ret(new QlVanillaSwap((*arg(o))->underlyingSwap(Date(fixingDate))));
  } catch (std::exception& er) {return handleException<QlVanillaSwap*>(e, er);}}
double qlInterestRateIndexForecastFixing(QlInterestRateIndex* o, int fixingDate, char **e) {
  try {return (*arg(o))->forecastFixing(Date(fixingDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
Calendar* qlIndexFixingCalendar(QlIndex* o, char **e) {
  try {return alloc(new Calendar((*arg(o))->fixingCalendar()));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}
Currency* qlInterestRateIndexCurrency(QlInterestRateIndex* o, char **e) {
  try {return alloc(new Currency((*arg(o))->currency()));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}}
DayCounter* qlInterestRateIndexDayCounter(QlInterestRateIndex* o, char **e) {
  try {return alloc(new DayCounter((*arg(o))->dayCounter()));
  } catch (std::exception& er) {return handleException<DayCounter*>(e, er);}}
unsigned qlInterestRateIndexFixingDays(QlInterestRateIndex* o) {return (*arg(o))->fixingDays();}

int qlInterestRateIndexTenor(QlInterestRateIndex* o, int *u, char **e) {
  try {const Period& p = (*arg(o))->tenor();*u = p.units();return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
QlIborIndex *qlIborIndex(char *name, int l, int u, unsigned settlDays, Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
  QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlIborIndex(alloc(new IborIndex(name, Period(l, (TimeUnit)u),
	  settlDays, *arg(ccy), *arg(cal), (BusinessDayConvention) conv,
	  eom, *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {return handleException<QlIborIndex *>(e, er);}}

const char* qlIndexName(QlIndex *index) {std::string name = (*arg(index))->name(); return DUP(name.c_str());}
void qlFreeIborIndex(QlIborIndex *i) {del(i);}

QlIborIndex *qlLibor(char *name, int l, int u, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd, char **e) {
  try {return ret(new QlIborIndex(alloc(new Libor(name, Period(l, (TimeUnit)u), settlDays,
            *arg(ccy), *arg(cal), *arg(dc), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {return handleException<QlIborIndex *>(e, er);}}
QlIborIndex *qlDailyTenorLibor(char *name, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc,
    QlYieldTermStructure *fwd, char **e) {
  try {return ret(new QlIborIndex(alloc(new DailyTenorLibor(name, settlDays,
            *arg(ccy), *arg(cal), *arg(dc), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {return handleException<QlIborIndex *>(e, er);}}
QlOvernightIndex *qlOvernightIndex(char *name, unsigned settlDays, Currency *ccy,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e) {
  try {return ret(new QlOvernightIndex(alloc(new OvernightIndex(name, settlDays,
            *arg(ccy), *arg(cal), *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {return handleException<QlOvernightIndex *>(e, er);}}

typedef IborIndex *(*makeIborIndex)(int l, int u, const QlYieldTermStructure& ts);
// must match the order of qlEnumObjects.h:IborIndexType (Standard block), then
// IborDailyTenorIndexType (DailyTenor block), then IborONIndexType (Overnight block) --
// see deriveIborConstructor in QuantLib/Internal/Syntax.hs for how the three Haskell-side
// enums are stitched back into a single flat offset into this array.
static const makeIborIndex iborIndices[] = {
    // -- Standard block (IborIndexType) --
    [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Bbsw(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Bibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Bkbm(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Cdor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new EURLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new AUDLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new CADLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new CHFLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new DKKLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new GBPLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new JPYLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new NZDLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new SEKLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new USDLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Euribor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Euribor365(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Jibar(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Mosprime(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Pribor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Robor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Shibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new THBFIX(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new TRLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Tibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Wibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Zibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new Nibor(Period(l, (TimeUnit)u), ts));}
    // -- DailyTenor block (IborDailyTenorIndexType) --
  , [](int l, int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new DailyTenorEURLibor(l, ts));}
  , [](int l, int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new DailyTenorCHFLibor(l, ts));}
  , [](int l, int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new DailyTenorGBPLibor(l, ts));}
  , [](int l, int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new DailyTenorJPYLibor(l, ts));}
  , [](int l, int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new DailyTenorUSDLibor(l, ts));}
    // -- Overnight block (IborONIndexType) --
  , [](int  , int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new CADLiborON(ts));}
  , [](int  , int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new EURLiborON(ts));}
  , [](int  , int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new GBPLiborON(ts));}
  , [](int  , int  , const QlYieldTermStructure& ts) {return static_cast<IborIndex *>(new USDLiborON(ts));}
};

QlIborIndex *qlCreateIbor(int index, int l, int u, QlYieldTermStructure *fwd, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(iborIndices))
      QL_FAIL("Invalid IBOR index index: " << index);
    QlYieldTermStructure ts = qlNullableHandle(fwd);
    IborIndex *i = iborIndices[index](l, u, ts);
    return ret(new QlIborIndex(alloc(i)));
  } catch (std::exception& er) {return handleException<QlIborIndex *>(e, er);}}

typedef OvernightIndex *(*makeONIndex)(const QlYieldTermStructure &ts);
// should match the order of qlEnumObjects.h:OvernightIborIndexType
static const makeONIndex onIndices[] = {
    [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Aonia(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Eonia(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Estr(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new FedFunds(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Nzocr(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Sofr(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Sonia(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Cdi(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Corra(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Kofr(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Destr(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Swestr(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Shir(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Tonar(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Saron(ts));}
  , [](const QlYieldTermStructure &ts){return static_cast<OvernightIndex *>(new Zaronia(ts));}
};

QlOvernightIndex *qlCreateONIndex(int index, QlYieldTermStructure *fwd, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(onIndices))
      QL_FAIL("Invalid O/N index index" << index);
    QlYieldTermStructure ts = qlNullableHandle(fwd);
    OvernightIndex *i = onIndices[index](ts);
    return ret(new QlOvernightIndex(alloc(i)));
  } catch (std::exception& er) {return handleException<QlOvernightIndex *>(e, er);}}

QlInterestRateIndex* qlIborIndexAsInterestRateIndex(QlIborIndex *o) {return ret(new QlInterestRateIndex(*arg(o)));}
void qlFreeOvernightIndex(QlOvernightIndex *o) {del(o);}
QlIborIndex* qlOvernightIndexAsIborIndex(QlOvernightIndex *o) {return ret(new QlIborIndex(*arg(o)));}
int qlIborIndexBusinessDayConvention(QlIborIndex* o) {return (*arg(o))->businessDayConvention();}
int qlIborIndexEndOfMonth(QlIborIndex* o) {return (*arg(o))->endOfMonth();}

QlEquityIndex *qlEquityIndex(char *name, Calendar *fixingCalendar, Currency *ccy, QlYieldTermStructure *interest, QlYieldTermStructure *dividend, QlQuote *spot, char **e) {
  try {
    return ret(new QlEquityIndex(alloc(new EquityIndex(name, *arg(fixingCalendar), *arg(ccy),
      qlNullableHandle(interest), qlNullableHandle(dividend), qlNullableHandle(spot)))));
  } catch (std::exception& er) {return handleException<QlEquityIndex *>(e, er);}}
void qlFreeEquityIndex(QlEquityIndex *o) {del(o);}
QlIndex* qlEquityIndexAsIndex(QlEquityIndex *o) {return ret(new QlIndex(*arg(o)));}
Currency* qlEquityIndexCurrency(QlEquityIndex* o, char **e) {
  try {return alloc(new Currency((*arg(o))->currency()));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}}
QlYieldTermStructure* qlEquityIndexInterestRateCurve(QlEquityIndex* o, char **e) {
  try {return ret(new QlYieldTermStructure((*arg(o))->equityInterestRateCurve().currentLink()));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure* qlEquityIndexDividendCurve(QlEquityIndex* o, char **e) {
  try {return ret(new QlYieldTermStructure((*arg(o))->equityDividendCurve().currentLink()));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlQuote* qlEquityIndexSpot(QlEquityIndex* o, char **e) {
  try {return ret(new QlQuote((*arg(o))->spot().currentLink()));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}

typedef ZeroInflationIndex *(*makeZeroInflationIndex)();
// must match the order of qlEnumObjects.h:ZeroInflationIndexType
static const makeZeroInflationIndex zeroInflationIndices[] = {
    []{return static_cast<ZeroInflationIndex *>(new AUCPI(Quarterly, false));} // AU CPI is published quarterly, unlike the other (monthly) named indices
  , []{return static_cast<ZeroInflationIndex *>(new EUHICP());}
  , []{return static_cast<ZeroInflationIndex *>(new EUHICPXT());}
  , []{return static_cast<ZeroInflationIndex *>(new FRHICP());}
  , []{return static_cast<ZeroInflationIndex *>(new UKHICP());}
  , []{return static_cast<ZeroInflationIndex *>(new UKRPI());}
  , []{return static_cast<ZeroInflationIndex *>(new USCPI());}
  , []{return static_cast<ZeroInflationIndex *>(new ZACPI());}
};

QlZeroInflationIndex *qlCreateZeroInflationIndex(int index, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(zeroInflationIndices))
      QL_FAIL("Invalid zero inflation index index" << index);
    return ret(new QlZeroInflationIndex(alloc(zeroInflationIndices[index]())));
  } catch (std::exception& er) {return handleException<QlZeroInflationIndex *>(e, er);}}

typedef YoYInflationIndex *(*makeYoYInflationIndex)();
// must match the order of qlEnumObjects.h:YoYInflationIndexType
static const makeYoYInflationIndex yoyInflationIndices[] = {
    []{return static_cast<YoYInflationIndex *>(new YYAUCPI(Quarterly, false));}
  , []{return static_cast<YoYInflationIndex *>(new YYEUHICP());}
  , []{return static_cast<YoYInflationIndex *>(new YYEUHICPXT());}
  , []{return static_cast<YoYInflationIndex *>(new YYFRHICP());}
  , []{return static_cast<YoYInflationIndex *>(new YYUKRPI());}
  , []{return static_cast<YoYInflationIndex *>(new YYUSCPI());}
  , []{return static_cast<YoYInflationIndex *>(new YYZACPI());}
};

QlYoYInflationIndex *qlCreateYoYInflationIndex(int index, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(yoyInflationIndices))
      QL_FAIL("Invalid year-on-year inflation index index" << index);
    return ret(new QlYoYInflationIndex(alloc(yoyInflationIndices[index]())));
  } catch (std::exception& er) {return handleException<QlYoYInflationIndex *>(e, er);}}

typedef Region *(*makeRegion)();
// must match the order of qlEnumObjects.h:RegionType
static const makeRegion regions[] = {
    []{return static_cast<Region *>(new AustraliaRegion());}
  , []{return static_cast<Region *>(new EURegion());}
  , []{return static_cast<Region *>(new FranceRegion());}
  , []{return static_cast<Region *>(new UKRegion());}
  , []{return static_cast<Region *>(new USRegion());}
  , []{return static_cast<Region *>(new ZARegion());}
};
Region *qlRegion(int r, char **e) {
  try {
    if (r < 0 || r >= (int)LENGTH(regions)) QL_FAIL("Invalid region index " << r);
    return alloc(regions[r]());
  } catch (std::exception& er) {return handleException<Region*>(e, er);}}
Region *qlCreateRegion(char* name, char* code, char **e) {
  try {return alloc(static_cast<Region*>(new CustomRegion(arg(name), arg(code))));
  } catch (std::exception& er) {return handleException<Region*>(e, er);}}
void qlFreeRegion(Region *o) {del(o);}
const char *qlRegionName(Region *o) {return DUP(arg(o)->name().c_str());}

QlZeroInflationIndex *qlZeroInflationIndex(char *familyName, Region *region, int revised, int frequency,
    int availLagN, int availLagU, Currency *currency, QlZeroInflationTermStructure *ts, char **e) {
  try {return ret(new QlZeroInflationIndex(alloc(new ZeroInflationIndex(arg(familyName), *arg(region), revised,
          (Frequency)frequency, Period(availLagN, (TimeUnit)availLagU), *arg(currency), qlNullableHandle(ts)))));
  } catch (std::exception& er) {return handleException<QlZeroInflationIndex *>(e, er);}}
QlYoYInflationIndex *qlYoYInflationIndex(char *familyName, Region *region, int revised, int frequency,
    int availLagN, int availLagU, Currency *currency, QlYoYInflationTermStructure *ts, char **e) {
  try {return ret(new QlYoYInflationIndex(alloc(new YoYInflationIndex(arg(familyName), *arg(region), revised,
          (Frequency)frequency, Period(availLagN, (TimeUnit)availLagU), *arg(currency), qlNullableHandle(ts)))));
  } catch (std::exception& er) {return handleException<QlYoYInflationIndex *>(e, er);}}
QlYoYInflationIndex *qlYoYInflationIndexFromZero(QlZeroInflationIndex *underlying, QlYoYInflationTermStructure *ts, char **e) {
  try {return ret(new QlYoYInflationIndex(alloc(new YoYInflationIndex(*arg(underlying), qlNullableHandle(ts)))));
  } catch (std::exception& er) {return handleException<QlYoYInflationIndex *>(e, er);}}

void qlFreeInflationIndex(QlInflationIndex *o) {del(o);}
QlIndex* qlInflationIndexAsIndex(QlInflationIndex *o) {return ret(new QlIndex(*arg(o)));}
void qlFreeZeroInflationIndex(QlZeroInflationIndex *o) {del(o);}
QlInflationIndex* qlZeroInflationIndexAsInflationIndex(QlZeroInflationIndex *o) {return ret(new QlInflationIndex(*arg(o)));}
void qlFreeYoYInflationIndex(QlYoYInflationIndex *o) {del(o);}
QlInflationIndex* qlYoYInflationIndexAsInflationIndex(QlYoYInflationIndex *o) {return ret(new QlInflationIndex(*arg(o)));}

double qlZeroInflationIndexFixing(QlZeroInflationIndex* o, int fixingDate, char **e) {
  try {return (*arg(o))->fixing(Date(fixingDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlYoYInflationIndexFixing(QlYoYInflationIndex* o, int fixingDate, char **e) {
  try {return (*arg(o))->fixing(Date(fixingDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
