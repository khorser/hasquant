#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/optionlet/capletvariancecurve.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper1.hpp>
#include <ql/termstructures/volatility/optionlet/strippedoptionletadapter.hpp>
#include <ql/termstructures/volatility/optionlet/spreadedoptionletvol.hpp>
#include <ql/termstructures/volatility/flatsmilesection.hpp>
#include <ql/termstructures/volatility/spreadedsmilesection.hpp>
#include <ql/termstructures/volatility/atmsmilesection.hpp>
#include <ql/experimental/volatility/svismilesection.hpp>
#include <ql/experimental/volatility/sviinterpolatedsmilesection.hpp>
#include <ql/termstructures/volatility/equityfx/all.hpp>
#include <ql/termstructures/volatility/equityfx/andreasenhugelocalvoladapter.hpp>
#include <ql/termstructures/volatility/equityfx/andreasenhugevolatilityadapter.hpp>
#include <ql/termstructures/volatility/equityfx/andreasenhugevolatilityinterpl.hpp>
#include <ql/termstructures/volatility/equityfx/gridmodellocalvolsurface.hpp>
#include <ql/termstructures/volatility/equityfx/hestonblackvolsurface.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/spreadedswaptionvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolmatrix.hpp>
#include <ql/termstructures/volatility/swaption/sabrswaptionvolatilitycube.hpp>
#include <ql/termstructures/volatility/swaption/interpolatedswaptionvolatilitycube.hpp>
#include <ql/termstructures/volatility/sabrsmilesection.hpp>
#include <ql/termstructures/volatility/sabrinterpolatedsmilesection.hpp>
#include <ql/experimental/volatility/noarbsabrsmilesection.hpp>
#include <ql/experimental/volatility/noarbsabrinterpolatedsmilesection.hpp>
#include <ql/experimental/volatility/blackatmvolcurve.hpp>
#include <ql/experimental/volatility/blackvolsurface.hpp>
#include <ql/experimental/volatility/abcdatmvolcurve.hpp>
#include <ql/experimental/volatility/sabrvolsurface.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper2.hpp>
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
#include <ql/termstructures/multicurve.hpp>
#include <ql/experimental/termstructures/basisswapratehelpers.hpp>
#include <ql/experimental/termstructures/crosscurrencyratehelpers.hpp>
#include <ql/math/interpolations/all.hpp>
#include <ql/index.hpp>
#include <ql/indexes/indexmanager.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/indexes/bmaindex.hpp>
#include <ql/indexes/swap/all.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>
#include <ql/indexes/inflation/all.hpp>
#include <ql/termstructures/inflation/inflationhelpers.hpp>
#include <ql/termstructures/inflation/interpolatedyoyinflationcurve.hpp>
#include <ql/indexes/equityindex.hpp>
#include <ql/experimental/commodities/commoditycurve.hpp>
#include <ql/experimental/commodities/commodityindex.hpp>
#include <ql/termstructures/volatility/inflation/yoyinflationoptionletvolatilitystructure.hpp>
#include <ql/pricingengines/inflation/inflationcapfloorengines.hpp>
#include <ql/experimental/inflation/cpicapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/cpicapfloorengines.hpp>
#include <ql/termstructures/volatility/inflation/constantcpivolatility.hpp>
#include <ql/experimental/inflation/yoycapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/interpolatedyoyoptionletstripper.hpp>
#include <ql/experimental/inflation/kinterpolatedyoyoptionletvolatilitysurface.hpp>

#include "qlaux.h"
#include "qlMisc.h"
using namespace QuantLib;
// these are type aliases so we cannot use their forward declarations in qlaux.h without including all relevant header files
using QlDefaultProbabilityHelper = shared_ptr<DefaultProbabilityHelper>;
using QlRateHelper = shared_ptr<RateHelper>;
using FittedBondDiscountCurveFittingMethod = FittedBondDiscountCurve::FittingMethod;
#include "qlTermStructure.h"
#include "qlTermStructureAux.h"

namespace hasquant {
#include "qlEnumObjects.h"
}

#ifdef QLTRACK_ALLOCATIONS
QL_TRACE_NAME(DefaultProbabilityHelper)
QL_TRACE_NAME(QlDefaultProbabilityHelper)
QL_TRACE_NAME(RateHelper)
QL_TRACE_NAME(QlRateHelper)
QL_TRACE_NAME(FittedBondDiscountCurveFittingMethod)
QL_TRACE_NAME(PiecewiseZeroSpreadedTermStructure)
#endif

namespace {
  bool sameIndexName(const std::string& s1, const std::string& s2) {
    return s1.size() == s2.size() && std::equal(s1.begin(), s1.end(), s2.begin(),
      [](const auto& c1, const auto& c2) {
        return std::toupper(static_cast<unsigned char>(c1)) == std::toupper(static_cast<unsigned char>(c2));
      });
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

  void fillMatrixOut(const Matrix& m, unsigned* rows, unsigned* cols, unsigned* len, double** vs) {
    *rows = (unsigned)m.rows(); *cols = (unsigned)m.columns(); *len = (unsigned)(m.rows() * m.columns());
    *vs = qlAllocateDoubles(*len);
    std::copy(m.begin(), m.end(), *vs);
  }

  // The stripper sets the real vol on this engine as it bootstraps each strike's curve
  // (interpolatedyoyoptionletstripper.hpp), so it is constructed with a deliberately null
  // vol handle -- same idiom as the upstream test (inflationvolatility.cpp's testYoYPriceSurfaceToVol).
  Handle<YoYOptionletVolatilitySurface> qlNullYoYOptionletVolatilitySurfaceHandle() {
    return Handle<YoYOptionletVolatilitySurface>(shared_ptr<YoYOptionletVolatilitySurface>(), false);
  }


// The named-index factory tables below live inside the extern "C" block with the shims that
// use them, but a template cannot be declared with C linkage, so their element constructors
// sit here instead.
// Return type spelled as the base (not the concrete subclass): alloc() takes its trace label
// from its argument's static type, and these are freed through the base -- see makeCurrency
// in qlMisc.cpp for the same reasoning spelled out in full.
template <class I> SwapIndex *makeSwapIndex(const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2) {return new I(p, h1, h2);}
// Three constructor shapes upstream: a tenor Period, a bare curve, or a plain number of months.
template <class I> IborIndex *makeIborIndex(int l, int u, const QlYieldTermStructure &ts) {return new I(Period(l, (TimeUnit)u), ts);}
template <class I> IborIndex *makeIborIndexTS(int, int, const QlYieldTermStructure &ts) {return new I(ts);}
template <class I> IborIndex *makeIborIndexMonths(int l, int, const QlYieldTermStructure &ts) {return new I(l, ts);}
template <class I> OvernightIndex *makeONIndex(const QlYieldTermStructure &ts) {return new I(ts);}
template <class I> ZeroInflationIndex *makeZeroInflationIndex() {return new I();}
template <class I> YoYInflationIndex *makeYoYInflationIndex() {return new I();}
template <class R> Region *makeRegion() {return new R();}

using makeSwapIdx = SwapIndex *(*)(const Period &p, const QlYieldTermStructure &h1, const QlYieldTermStructure &h2);
using makeIborIdx = IborIndex *(*)(int l, int u, const QlYieldTermStructure &ts);
using makeOnIdx = OvernightIndex *(*)(const QlYieldTermStructure &ts);
using makeZeroInflIdx = ZeroInflationIndex *(*)();
using makeYoYInflIdx = YoYInflationIndex *(*)();
using makeReg = Region *(*)();
}

extern "C" {
QlOptionletVolatilityStructure *qlConstantOptionletVol1(unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, int type, double displacement, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(shared_ptr<OptionletVolatilityStructure>(alloc(new ConstantOptionletVolatility(days, *arg(cal), (BusinessDayConvention) conv, *arg(q), *arg(dc), (VolatilityType)type, displacement)))));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure *>(e, er);}}
QlOptionletVolatilityStructure *qlCapletVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned volsLen, double* vols, DayCounter* dc, int type, double displacement, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(shared_ptr<OptionletVolatilityStructure>(alloc(new CapletVarianceCurve(Date(referenceDate), qlDateVector(dates, datesLen), std::vector<double>(vols, vols+volsLen), *arg(dc), (VolatilityType)type, displacement)))));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure *>(e, er);}}

void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p) {del(p);}
// Deliberate snapshot detach, same reasoning as qlBlackVolTermStructureAsVolatilityTermStructure.
QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o) {return ret(new QlVolatilityTermStructure(handlePtr(arg(o))));}

// OptionletStripper1 is never exposed to Haskell as its own type -- immediately wrapped in a
// StrippedOptionletAdapter, itself an OptionletVolatilityStructure, mirroring qlConstantOptionletVol1
// above. optionletFrequencyUnit < 0 is the ext::nullopt sentinel for optionletFrequency, same
// convention as qlOptBusinessDayConvention/qlOptFrequency (TimeUnit starts at 0, so can't self-sentinel).
QlOptionletVolatilityStructure* qlOptionletStripper1(QlCapFloorTermVolSurface* surface, QlIborIndex* index, double switchStrikes, double accuracy, unsigned maxIter, QlYieldTermStructure* discount, int type, double displacement, int dontThrow, int optionletFrequencyLen, int optionletFrequencyUnit, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(shared_ptr<OptionletVolatilityStructure>(alloc(new StrippedOptionletAdapter(
            shared_ptr<OptionletStripper1>(alloc(new OptionletStripper1(*arg(surface), *arg(index), switchStrikes, accuracy, maxIter,
              qlNullableHandle(arg(discount)), (VolatilityType)type, displacement, (bool)dontThrow,
              optionletFrequencyUnit < 0 ? ext::optional<Period>() : ext::optional<Period>(Period(optionletFrequencyLen, (TimeUnit)optionletFrequencyUnit))))))))));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure*>(e, er);}}

// A relinkable handle, empty when `initial` is null -- mirrors qlRelinkableYieldTermStructure.
QlRelinkableOptionletVolatilityStructure* qlRelinkableOptionletVolatilityStructure(QlOptionletVolatilityStructure *initial, char **e) {
  try {return ret(initial ? new QlRelinkableOptionletVolatilityStructure(handlePtr(arg(initial)))
                          : new QlRelinkableOptionletVolatilityStructure());
  } catch (std::exception& er) {return handleException<QlRelinkableOptionletVolatilityStructure*>(e, er);}}
void qlFreeRelinkableOptionletVolatilityStructure(QlRelinkableOptionletVolatilityStructure *o) {del(o);}
void qlRelinkableOptionletVolatilityStructureLinkTo(QlRelinkableOptionletVolatilityStructure *o, QlOptionletVolatilityStructure *c, char **e) {
  try {arg(o)->linkTo(handlePtr(arg(c)));} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
QlOptionletVolatilityStructure* qlRelinkableOptionletVolatilityStructureAsOptionletVolatilityStructure(QlRelinkableOptionletVolatilityStructure *o) {return ret(new QlOptionletVolatilityStructure(*arg(o)));}
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
void qlFreeBlackAtmVolCurve(QlBlackAtmVolCurve *o) {del(o);}
QlVolatilityTermStructure* qlBlackAtmVolCurveAsVolatilityTermStructure(QlBlackAtmVolCurve *o) {return ret(new QlVolatilityTermStructure(handlePtr(arg(o))));}
void qlFreeBlackVolSurface(QlBlackVolSurface *o) {del(o);}
QlBlackAtmVolCurve* qlBlackVolSurfaceAsBlackAtmVolCurve(QlBlackVolSurface *o) {return ret(new QlBlackAtmVolCurve(*arg(o)));}
void qlFreeAbcdAtmVolCurve(QlAbcdAtmVolCurve *o) {del(o);}
QlBlackAtmVolCurve* qlAbcdAtmVolCurveAsBlackAtmVolCurve(QlAbcdAtmVolCurve *o) {return ret(new QlBlackAtmVolCurve(*arg(o)));}
void qlFreeSabrVolSurface(QlSabrVolSurface *o) {del(o);}
QlBlackVolSurface* qlSabrVolSurfaceAsBlackVolSurface(QlSabrVolSurface *o) {return ret(new QlBlackVolSurface(*arg(o)));}
double qlBlackAtmVolCurveAtmVolForPeriod(QlBlackAtmVolCurve* o, int n, int u, int extrapolate, char **e) {
  try {return (*arg(o))->atmVol(Period(n, (TimeUnit)u), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackAtmVolCurveAtmVolForDate(QlBlackAtmVolCurve* o, int date, int extrapolate, char **e) {
  try {return (*arg(o))->atmVol(Date(date), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackAtmVolCurveAtmVolForTime(QlBlackAtmVolCurve* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->atmVol(t, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackAtmVolCurveAtmVarianceForPeriod(QlBlackAtmVolCurve* o, int n, int u, int extrapolate, char **e) {
  try {return (*arg(o))->atmVariance(Period(n, (TimeUnit)u), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackAtmVolCurveAtmVarianceForDate(QlBlackAtmVolCurve* o, int date, int extrapolate, char **e) {
  try {return (*arg(o))->atmVariance(Date(date), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBlackAtmVolCurveAtmVarianceForTime(QlBlackAtmVolCurve* o, double t, int extrapolate, char **e) {
  try {return (*arg(o))->atmVariance(t, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSmileSection* qlBlackVolSurfaceSmileSectionForPeriod(QlBlackVolSurface* o, int n, int u, int extrapolate, char **e) {
  try {return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Period(n, (TimeUnit)u), extrapolate))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlBlackVolSurfaceSmileSectionForDate(QlBlackVolSurface* o, int date, int extrapolate, char **e) {
  try {return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(date), extrapolate))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlBlackVolSurfaceSmileSectionForTime(QlBlackVolSurface* o, double t, int extrapolate, char **e) {
  try {return ret(new QlSmileSection(alloc((*arg(o))->smileSection(t, extrapolate))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlAbcdAtmVolCurve* qlAbcdAtmVolCurve(unsigned settlementDays, Calendar* calendar, unsigned optionTenorsLen, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, unsigned flagsLen, int *flags, int bdc, DayCounter* dc, char **e) {
  try {return ret(new QlAbcdAtmVolCurve(alloc(new AbcdAtmVolCurve(settlementDays, *arg(calendar),
              qlPeriodVector(n, u, optionTenorsLen), qlHandleVector(vols, volsLen),
              std::vector<bool>(flags, flags+flagsLen), (BusinessDayConvention)bdc, *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlAbcdAtmVolCurve*>(e, er);}}
double qlAbcdAtmVolCurveA(QlAbcdAtmVolCurve* o, char **e) {
  try {return (*arg(o))->a();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAbcdAtmVolCurveB(QlAbcdAtmVolCurve* o, char **e) {
  try {return (*arg(o))->b();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAbcdAtmVolCurveC(QlAbcdAtmVolCurve* o, char **e) {
  try {return (*arg(o))->c();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAbcdAtmVolCurveD(QlAbcdAtmVolCurve* o, char **e) {
  try {return (*arg(o))->d();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAbcdAtmVolCurveRmsError(QlAbcdAtmVolCurve* o, char **e) {
  try {return (*arg(o))->rmsError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAbcdAtmVolCurveMaxError(QlAbcdAtmVolCurve* o, char **e) {
  try {return (*arg(o))->maxError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlAbcdAtmVolCurveEndCriteria(QlAbcdAtmVolCurve* o, char **e) {
  try {return (int)(*arg(o))->endCriteria();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlAbcdAtmVolCurveKAtTime(QlAbcdAtmVolCurve* o, double t, char **e) {
  try {return (*arg(o))->k(t);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlAbcdAtmVolCurveK(QlAbcdAtmVolCurve* o, unsigned *count, double **ks, char **e) {
  try {
    std::vector<Real> k = (*arg(o))->k();
    *count = k.size(); *ks = qlAllocateDoubles(*count);
    for (size_t i = 0; i < k.size(); ++i) (*ks)[i] = k[i];
  } catch (std::exception& er) {*count = 0; *ks = 0; handleException<int>(e, er);}}
void qlAbcdAtmVolCurveOptionTenors(QlAbcdAtmVolCurve* o, unsigned *count, int **n, unsigned *count2, int **u, char **e) {
  *count = 0; *count2 = 0; *n = nullptr; *u = nullptr;
  int *lengths = nullptr, *units = nullptr;
  try {
    const std::vector<Period> &p = (*arg(o))->optionTenors();
    lengths = qlAllocateInts(p.size()); units = qlAllocateInts(p.size());
    for (size_t i = 0; i < p.size(); ++i) {lengths[i] = p[i].length(); units[i] = (int)p[i].units();}
    *count = *count2 = p.size(); *n = lengths; *u = units;
  } catch (const std::exception& er) {
    qlFreeInts(lengths); qlFreeInts(units); *e = tracedup(er.what());
  }}
void qlAbcdAtmVolCurveOptionTenorsInInterpolation(QlAbcdAtmVolCurve* o, unsigned *count, int **n, unsigned *count2, int **u, char **e) {
  *count = 0; *count2 = 0; *n = nullptr; *u = nullptr;
  int *lengths = nullptr, *units = nullptr;
  try {
    const std::vector<Period> &p = (*arg(o))->optionTenorsInInterpolation();
    lengths = qlAllocateInts(p.size()); units = qlAllocateInts(p.size());
    for (size_t i = 0; i < p.size(); ++i) {lengths[i] = p[i].length(); units[i] = (int)p[i].units();}
    *count = *count2 = p.size(); *n = lengths; *u = units;
  } catch (const std::exception& er) {
    qlFreeInts(lengths); qlFreeInts(units); *e = tracedup(er.what());
  }}
void qlAbcdAtmVolCurveOptionDates(QlAbcdAtmVolCurve* o, unsigned *count, int **days, char **e) {
  try {
    const std::vector<Date> &dates = (*arg(o))->optionDates();
    *count = dates.size(); *days = qlAllocateInts(*count);
    for (size_t i = 0; i < dates.size(); ++i) (*days)[i] = dates[i].serialNumber();
  } catch (std::exception& er) {*count = 0; *days = 0; handleException<int>(e, er);}}
void qlAbcdAtmVolCurveOptionTimes(QlAbcdAtmVolCurve* o, unsigned *count, double **times, char **e) {
  try {
    const std::vector<Time> &t = (*arg(o))->optionTimes();
    *count = t.size(); *times = qlAllocateDoubles(*count);
    for (size_t i = 0; i < t.size(); ++i) (*times)[i] = t[i];
  } catch (std::exception& er) {*count = 0; *times = 0; handleException<int>(e, er);}}
QlSabrVolSurface* qlSabrVolSurface(QlInterestRateIndex* index, QlBlackAtmVolCurve* atmCurve, unsigned tenorsLen, int *n, unsigned, int *u, unsigned spreadsLen, double *atmRateSpreads, unsigned volRows, unsigned volCols, QlQuote** volSpreads, char **e) {
  try {return ret(new QlSabrVolSurface(alloc(new SabrVolSurface(*arg(index), Handle<BlackAtmVolCurve>(*arg(atmCurve)),
      qlPeriodVector(n, u, tenorsLen), std::vector<Spread>(atmRateSpreads, atmRateSpreads+spreadsLen),
      qlHandleMatrix(volSpreads, volRows, volCols)))));
  } catch (std::exception& er) {return handleException<QlSabrVolSurface*>(e, er);}}
QlBlackAtmVolCurve* qlSabrVolSurfaceAtmCurve(QlSabrVolSurface* o, char **e) {
  try {return ret(new QlBlackAtmVolCurve((*arg(o))->atmCurve().currentLink()));
  } catch (std::exception& er) {return handleException<QlBlackAtmVolCurve*>(e, er);}}
void qlSabrVolSurfaceVolatilitySpreadsForPeriod(QlSabrVolSurface* o, int n, int u, unsigned *count, double **vols, char **e) {
  try {
    std::vector<Volatility> v = (*arg(o))->volatilitySpreads(Period(n, (TimeUnit)u));
    *count = v.size(); *vols = qlAllocateDoubles(*count);
    for (size_t i = 0; i < v.size(); ++i) (*vols)[i] = v[i];
  } catch (std::exception& er) {*count = 0; *vols = 0; handleException<int>(e, er);}}
void qlSabrVolSurfaceVolatilitySpreadsForDate(QlSabrVolSurface* o, int date, unsigned *count, double **vols, char **e) {
  try {
    std::vector<Volatility> v = (*arg(o))->volatilitySpreads(Date(date));
    *count = v.size(); *vols = qlAllocateDoubles(*count);
    for (size_t i = 0; i < v.size(); ++i) (*vols)[i] = v[i];
  } catch (std::exception& er) {*count = 0; *vols = 0; handleException<int>(e, er);}}
QlInterestRateIndex* qlSabrVolSurfaceIndex(QlSabrVolSurface* o, char **e) {
  try {return ret(new QlInterestRateIndex((*arg(o))->index()));
  } catch (std::exception& er) {return handleException<QlInterestRateIndex*>(e, er);}}
int qlSabrVolSurfaceOptionDateFromTenor(QlSabrVolSurface* o, int n, int u, char **e) {
  try {return (*arg(o))->optionDateFromTenor(Period(n, (TimeUnit)u)).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}

// OptionletStripper2 builds an OptionletStripper1 internally (never exposed to Haskell, same
// fusion as qlOptionletStripper1 above) then wraps OptionletStripper2 itself around it, keeping
// the OptionletStripper2 shared_ptr so its own diagnostic getters below are reachable with no cast.
QlOptionletStripper2* qlOptionletStripper2(QlCapFloorTermVolSurface* surface, QlIborIndex* index, double switchStrikes, double accuracy, unsigned maxIter, QlYieldTermStructure* discount, int type, double displacement, int dontThrow, int optionletFrequencyLen, int optionletFrequencyUnit, QlCapFloorTermVolCurve* atmCurve, char **e) {
  try {
    auto stripper1 = shared_ptr<OptionletStripper1>(alloc(new OptionletStripper1(*arg(surface), *arg(index),
        switchStrikes, accuracy, maxIter, qlNullableHandle(arg(discount)), (VolatilityType)type, displacement,
        (bool)dontThrow, optionletFrequencyUnit < 0 ? ext::optional<Period>() : ext::optional<Period>(Period(optionletFrequencyLen, (TimeUnit)optionletFrequencyUnit)))));
    return ret(new QlOptionletStripper2(alloc(new OptionletStripper2(stripper1, Handle<CapFloorTermVolCurve>(*arg(atmCurve))))));
  } catch (std::exception& er) {return handleException<QlOptionletStripper2*>(e, er);}}
void qlFreeOptionletStripper2(QlOptionletStripper2 *o) {del(o);}
// Fresh construction (StrippedOptionletAdapter around the OptionletStripper2 itself), never a
// cast -- same idiom as qlSabrInterpolatedSmileSectionAsSmileSection.
QlOptionletVolatilityStructure* qlOptionletStripper2AsOptionletVolatilityStructure(QlOptionletStripper2 *o, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(shared_ptr<OptionletVolatilityStructure>(
      alloc(new StrippedOptionletAdapter(*arg(o))))));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure*>(e, er);}}
void qlOptionletStripper2AtmCapFloorStrikes(QlOptionletStripper2* o, unsigned *count, double **vs, char **e) {
  try {
    const std::vector<Rate> &v = (*arg(o))->atmCapFloorStrikes();
    *count = v.size(); *vs = qlAllocateDoubles(*count);
    for (size_t i = 0; i < v.size(); ++i) (*vs)[i] = v[i];
  } catch (std::exception& er) {*count = 0; *vs = 0; handleException<int>(e, er);}}
void qlOptionletStripper2AtmCapFloorPrices(QlOptionletStripper2* o, unsigned *count, double **vs, char **e) {
  try {
    const std::vector<Real> &v = (*arg(o))->atmCapFloorPrices();
    *count = v.size(); *vs = qlAllocateDoubles(*count);
    for (size_t i = 0; i < v.size(); ++i) (*vs)[i] = v[i];
  } catch (std::exception& er) {*count = 0; *vs = 0; handleException<int>(e, er);}}
void qlOptionletStripper2SpreadsVol(QlOptionletStripper2* o, unsigned *count, double **vs, char **e) {
  try {
    const std::vector<Volatility> &v = (*arg(o))->spreadsVol();
    *count = v.size(); *vs = qlAllocateDoubles(*count);
    for (size_t i = 0; i < v.size(); ++i) (*vs)[i] = v[i];
  } catch (std::exception& er) {*count = 0; *vs = 0; handleException<int>(e, er);}}

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
  try {return ret(new QlOptionletVolatilityStructure(shared_ptr<OptionletVolatilityStructure>(alloc(new ConstantOptionletVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), (*arg(dc)), (VolatilityType)type, displacement)))));
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
QlSmileSection* qlSabrSmileSection1(int optionDate, double forward, double alpha, double beta, double nu, double rho, int referenceDate, DayCounter* dc, double shift, int volatilityType, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new SabrSmileSection(
      Date(optionDate), forward, std::vector<Real>{alpha, beta, nu, rho}, qlNullableDate(referenceDate),
      *arg(dc), shift, (VolatilityType)volatilityType)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlNoArbSabrSmileSection(double timeToExpiry, double forward, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new NoArbSabrSmileSection(
      timeToExpiry, forward, std::vector<Real>{alpha, beta, nu, rho}, shift, (VolatilityType)volatilityType)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlNoArbSabrSmileSection1(int optionDate, double forward, double alpha, double beta, double nu, double rho, DayCounter* dc, double shift, int volatilityType, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new NoArbSabrSmileSection(
      Date(optionDate), forward, std::vector<Real>{alpha, beta, nu, rho}, *arg(dc), shift, (VolatilityType)volatilityType)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
double qlSmileSectionVolatility(QlSmileSection* o, double strike, char **e) {
  try {return (*arg(o))->volatility(strike);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSmileSectionVariance(QlSmileSection* o, double strike, char **e) {
  try {return (*arg(o))->variance(strike);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSmileSectionAtmLevel(QlSmileSection* o, char **e) {
  try {return (*arg(o))->atmLevel();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSmileSectionOptionPrice(QlSmileSection* o, double strike, int type, double discount, char **e) {
  try {return (*arg(o))->optionPrice(strike, (Option::Type)type, discount);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSmileSectionDigitalOptionPrice(QlSmileSection* o, double strike, int type, double discount, double gap, char **e) {
  try {return (*arg(o))->digitalOptionPrice(strike, (Option::Type)type, discount, gap);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSmileSectionDensity(QlSmileSection* o, double strike, double discount, double gap, char **e) {
  try {return (*arg(o))->density(strike, discount, gap);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSmileSection* qlFlatSmileSection(int d, double vol, DayCounter* dc, int referenceDate, double atmLevel, int type, double shift, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new FlatSmileSection(
      Date(d), vol, *arg(dc), qlNullableDate(referenceDate), atmLevel, (VolatilityType)type, shift)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlSpreadedSmileSection(QlSmileSection* source, QlQuote* spread, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new SpreadedSmileSection(*arg(source), *arg(spread))))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlAtmSmileSection(QlSmileSection* source, double atm, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new AtmSmileSection(*arg(source), atm)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
// SviSmileSection exposes no getters beyond the SmileSection base (a/b/sigma/rho/m are
// private, no accessors), so this returns the generic QlSmileSection directly -- same
// shape as qlFlatSmileSection/qlSpreadedSmileSection/qlAtmSmileSection above, not the
// dedicated-leaf pattern used for SabrInterpolatedSmileSection.
QlSmileSection* qlSviSmileSection(int d, double forward, double a, double b, double sigma, double rho, double m, DayCounter* dc, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(new SviSmileSection(
      Date(d), forward, std::vector<Real>{a, b, sigma, rho, m}, *arg(dc))))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
// ZabrSmileSection's evaluation-tag dispatch lives in qlTermStructureAux.cpp (a runtime enum
// selects a template argument). Same generic-QlSmileSection shape as qlSviSmileSection above --
// ZabrSmileSection's only extra getter, model(), isn't exposed (no known consumer; ZabrModel
// itself isn't bound as its own type).
QlSmileSection* qlZabrSmileSection(int evaluation, double timeToExpiry, double forward, double alpha, double beta, double nu, double rho, double gamma, unsigned moneynessLen, double* moneyness, unsigned fdRefinement, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(
      qlZabrSmileSectionAux(evaluation, timeToExpiry, forward, std::vector<Real>{alpha, beta, nu, rho, gamma},
          std::vector<Real>(moneyness, moneyness + moneynessLen), fdRefinement)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlZabrSmileSection1(int evaluation, int d, double forward, double alpha, double beta, double nu, double rho, double gamma, DayCounter* dc, unsigned moneynessLen, double* moneyness, unsigned fdRefinement, char **e) {
  try {return ret(new QlSmileSection(alloc(ext::shared_ptr<SmileSection>(
      qlZabrSmileSectionAux1(evaluation, Date(d), forward, std::vector<Real>{alpha, beta, nu, rho, gamma},
          *arg(dc), std::vector<Real>(moneyness, moneyness + moneynessLen), fdRefinement)))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSabrInterpolatedSmileSection* qlSabrInterpolatedSmileSection(int optionDate, QlQuote* forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, QlQuote* atmVolatility, unsigned volsLen, QlQuote** vols, double alpha, double beta, double nu, double rho, int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed, int vegaWeighted, QlEndCriteria* endCriteria, QlOptimizationMethod* method, DayCounter* dc, double shift, char **e) {
  try {
    // endCriteria/method are nullable (NULL -> empty shared_ptr, letting SABRInterpolation's
    // own internal EndCriteria/LevenbergMarquardt defaults apply); when given, copying the
    // shared_ptr out of Haskell's QlEndCriteria/QlOptimizationMethod box into this ctor's own
    // shared_ptr member is safe regardless of when Haskell's box is later collected -- see the
    // qlaux.h comment above the QlEndCriteria/QlOptimizationMethod aliases.
    // Returns the concrete type directly (not QlSmileSection) so alpha/beta/nu/rho/etc below
    // need no dynamic_pointer_cast -- see the CLAUDE.md API-design rule on preferring a
    // dedicated leaf over a runtime downcast. qlSabrInterpolatedSmileSectionAsSmileSection
    // below is the escape hatch for callers that need the generic SmileSection interface.
    ext::shared_ptr<SabrInterpolatedSmileSection> section(new SabrInterpolatedSmileSection(
        Date(optionDate), *arg(forward), std::vector<Real>(strikes, strikes + strikesLen), hasFloatingStrikes,
        *arg(atmVolatility), qlHandleVector(vols, volsLen), alpha, beta, nu, rho,
        isAlphaFixed, isBetaFixed, isNuFixed, isRhoFixed, vegaWeighted,
        endCriteria ? *arg(endCriteria) : shared_ptr<EndCriteria>(),
        method ? *arg(method) : shared_ptr<OptimizationMethod>(), *arg(dc), shift));
    section->atmLevel(); // force calibration now, surfacing failures at construction
    return ret(new QlSabrInterpolatedSmileSection(alloc(section)));
  } catch (std::exception& er) {return handleException<QlSabrInterpolatedSmileSection*>(e, er);}}
void qlFreeSabrInterpolatedSmileSection(QlSabrInterpolatedSmileSection* p) {del(p);}
// Fresh shared_ptr construction (implicit Derived->Base conversion), not a cast -- same
// pattern as qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure.
QlSmileSection* qlSabrInterpolatedSmileSectionAsSmileSection(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return ret(new QlSmileSection(*arg(o)));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
double qlSabrInterpolatedSmileSectionAlpha(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->alpha();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionBeta(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->beta();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionNu(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->nu();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionRho(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->rho();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionRmsError(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->rmsError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrInterpolatedSmileSectionMaxError(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->maxError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlSabrInterpolatedSmileSectionEndCriteria(QlSabrInterpolatedSmileSection* o, char **e) {
  try {return (int)(*arg(o))->endCriteria();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
// SVI's aIsFixed..mIsFixed have no upstream defaults (unlike SABR's isAlphaFixed..isRhoFixed,
// which default to false) -- only vegaWeighted/endCriteria/method/dc are trailing-defaulted, so
// this widens in place rather than using a TH options record (below the 10-param threshold).
// Bind only the Quote overload, per AGENTS.md's std::variant/Handle<Quote> rule (SabrInterpolated-
// SmileSection above does the same; the flat Rate/Volatility overload stays unbound). Same
// dedicated-leaf-over-dynamic_cast reasoning and eager-calibration-at-construction convention
// (atmLevel() forces the fit now, surfacing checkSviParameters' QL_REQUIREs at construction
// rather than at first use) as qlSabrInterpolatedSmileSection.
QlSviInterpolatedSmileSection* qlSviInterpolatedSmileSection(int optionDate, QlQuote* forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, QlQuote* atmVolatility, unsigned volsLen, QlQuote** vols, double a, double b, double sigma, double rho, double m, int aIsFixed, int bIsFixed, int sigmaIsFixed, int rhoIsFixed, int mIsFixed, int vegaWeighted, QlEndCriteria* endCriteria, QlOptimizationMethod* method, DayCounter* dc, char **e) {
  try {
    ext::shared_ptr<SviInterpolatedSmileSection> section(new SviInterpolatedSmileSection(
        Date(optionDate), *arg(forward), std::vector<Real>(strikes, strikes + strikesLen), hasFloatingStrikes,
        *arg(atmVolatility), qlHandleVector(vols, volsLen), a, b, sigma, rho, m,
        aIsFixed, bIsFixed, sigmaIsFixed, rhoIsFixed, mIsFixed, vegaWeighted,
        endCriteria ? *arg(endCriteria) : shared_ptr<EndCriteria>(),
        method ? *arg(method) : shared_ptr<OptimizationMethod>(), *arg(dc)));
    section->atmLevel(); // force calibration now, surfacing failures at construction
    return ret(new QlSviInterpolatedSmileSection(alloc(section)));
  } catch (std::exception& er) {return handleException<QlSviInterpolatedSmileSection*>(e, er);}}
void qlFreeSviInterpolatedSmileSection(QlSviInterpolatedSmileSection* p) {del(p);}
// Fresh shared_ptr construction (implicit Derived->Base conversion), not a cast -- same
// pattern as qlSabrInterpolatedSmileSectionAsSmileSection.
QlSmileSection* qlSviInterpolatedSmileSectionAsSmileSection(QlSviInterpolatedSmileSection* o, char **e) {
  try {return ret(new QlSmileSection(*arg(o)));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
double qlSviInterpolatedSmileSectionA(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->a();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSviInterpolatedSmileSectionB(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->b();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSviInterpolatedSmileSectionSigma(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->sigma();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSviInterpolatedSmileSectionRho(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->rho();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSviInterpolatedSmileSectionM(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->m();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSviInterpolatedSmileSectionRmsError(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->rmsError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSviInterpolatedSmileSectionMaxError(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->maxError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlSviInterpolatedSmileSectionEndCriteria(QlSviInterpolatedSmileSection* o, char **e) {
  try {return (int)(*arg(o))->endCriteria();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
// NoArbSabrInterpolatedSmileSection's isAlphaFixed..isRhoFixed all default to false, same as
// SabrInterpolatedSmileSection's, and it has no shift parameter (unlike SabrInterpolatedSmile-
// Section) -- 8 trailing-defaulted params, still under the 10-param threshold, so this widens in
// place like qlSviInterpolatedSmileSection. Same std::variant/Handle<Quote> rule (Quote overload
// only), dedicated-leaf-over-dynamic_cast reasoning, and eager-calibration-at-construction
// convention (atmLevel() forces the fit now) as qlSabrInterpolatedSmileSection/
// qlSviInterpolatedSmileSection above.
QlNoArbSabrInterpolatedSmileSection* qlNoArbSabrInterpolatedSmileSection(int optionDate, QlQuote* forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, QlQuote* atmVolatility, unsigned volsLen, QlQuote** vols, double alpha, double beta, double nu, double rho, int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed, int vegaWeighted, QlEndCriteria* endCriteria, QlOptimizationMethod* method, DayCounter* dc, char **e) {
  try {
    ext::shared_ptr<NoArbSabrInterpolatedSmileSection> section(new NoArbSabrInterpolatedSmileSection(
        Date(optionDate), *arg(forward), std::vector<Real>(strikes, strikes + strikesLen), hasFloatingStrikes,
        *arg(atmVolatility), qlHandleVector(vols, volsLen), alpha, beta, nu, rho,
        isAlphaFixed, isBetaFixed, isNuFixed, isRhoFixed, vegaWeighted,
        endCriteria ? *arg(endCriteria) : shared_ptr<EndCriteria>(),
        method ? *arg(method) : shared_ptr<OptimizationMethod>(), *arg(dc)));
    section->atmLevel(); // force calibration now, surfacing failures at construction
    return ret(new QlNoArbSabrInterpolatedSmileSection(alloc(section)));
  } catch (std::exception& er) {return handleException<QlNoArbSabrInterpolatedSmileSection*>(e, er);}}
void qlFreeNoArbSabrInterpolatedSmileSection(QlNoArbSabrInterpolatedSmileSection* p) {del(p);}
// Fresh shared_ptr construction (implicit Derived->Base conversion), not a cast -- same pattern
// as qlSabrInterpolatedSmileSectionAsSmileSection.
QlSmileSection* qlNoArbSabrInterpolatedSmileSectionAsSmileSection(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return ret(new QlSmileSection(*arg(o)));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
double qlNoArbSabrInterpolatedSmileSectionAlpha(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->alpha();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlNoArbSabrInterpolatedSmileSectionBeta(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->beta();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlNoArbSabrInterpolatedSmileSectionNu(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->nu();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlNoArbSabrInterpolatedSmileSectionRho(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->rho();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlNoArbSabrInterpolatedSmileSectionRmsError(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->rmsError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlNoArbSabrInterpolatedSmileSectionMaxError(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (*arg(o))->maxError();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlNoArbSabrInterpolatedSmileSectionEndCriteria(QlNoArbSabrInterpolatedSmileSection* o, char **e) {
  try {return (int)(*arg(o))->endCriteria();
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
QlCapFloorTermVolCurve* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolCurve(alloc(new CapFloorTermVolCurve(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc,
              qlPeriodVector(n, u, l), qlHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolCurve*>(e, er);}}
QlCapFloorTermVolCurve* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolCurve(alloc(new CapFloorTermVolCurve(settlementDays, *arg(calendar), (BusinessDayConvention)bdc,
              qlPeriodVector(n, u, l), qlHandleVector(vols, volsLen), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolCurve*>(e, er);}}
QlCapFloorTermVolatilityStructure* qlConstantCapFloorTermVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolatilityStructure(alloc(new ConstantCapFloorTermVolatility(Date(referenceDate), *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolatilityStructure*>(e, er);}}
QlCapFloorTermVolatilityStructure* qlConstantCapFloorTermVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolatilityStructure(alloc(new ConstantCapFloorTermVolatility(settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(volatility), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolatilityStructure*>(e, er);}}
double qlCapFloorTermVolatilityStructureVolatilityForPeriod(QlCapFloorTermVolatilityStructure* o, int n, int u, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(Period(n, (TimeUnit)u), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCapFloorTermVolatilityStructureVolatilityForDate(QlCapFloorTermVolatilityStructure* o, int date, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(Date(date), strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCapFloorTermVolatilityStructureVolatilityForTime(QlCapFloorTermVolatilityStructure* o, double t, double strike, int extrapolate, char **e) {
  try {return (*arg(o))->volatility(t, strike, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSwaptionVolatilityStructure* qlSpreadedSwaptionVolatility(QlSwaptionVolatilityStructure* x0, QlQuote* spread, char **e) {
  try {return ret(new QlSwaptionVolatilityStructure(shared_ptr<SwaptionVolatilityStructure>(alloc(new SpreadedSwaptionVolatility(*arg(x0), *arg(spread))))));
  } catch (std::exception& er) {return handleException<QlSwaptionVolatilityStructure*>(e, er);}}
QlOptionletVolatilityStructure* qlSpreadedOptionletVolatility(QlOptionletVolatilityStructure* x0, QlQuote* spread, char **e) {
  try {return ret(new QlOptionletVolatilityStructure(shared_ptr<OptionletVolatilityStructure>(alloc(new SpreadedOptionletVolatility(*arg(x0), *arg(spread))))));
  } catch (std::exception& er) {return handleException<QlOptionletVolatilityStructure*>(e, er);}}

void qlFreeCapFloorTermVolatilityStructure(QlCapFloorTermVolatilityStructure *o) {del(o);}
QlVolatilityTermStructure* qlCapFloorTermVolatilityStructureAsVolatilityTermStructure(QlCapFloorTermVolatilityStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}
void qlFreeCapFloorTermVolCurve(QlCapFloorTermVolCurve *o) {del(o);}
QlCapFloorTermVolatilityStructure* qlCapFloorTermVolCurveAsCapFloorTermVolatilityStructure(QlCapFloorTermVolCurve *o) {return ret(new QlCapFloorTermVolatilityStructure(*arg(o)));}
void qlCapFloorTermVolCurveOptionDates(QlCapFloorTermVolCurve *o, unsigned *count, int **days, char **e) {
  *count = 0; *days = nullptr;
  int *out = nullptr;
  try {
    const std::vector<Date> &dates = (*arg(o))->optionDates();
    out = qlAllocateInts(dates.size());
    for (size_t i = 0; i < dates.size(); ++i) out[i] = dates[i].serialNumber();
    *count = dates.size(); *days = out;
  } catch (const std::exception& er) {qlFreeInts(out); *e = tracedup(er.what());}
}
void qlCapFloorTermVolCurveOptionTimes(QlCapFloorTermVolCurve *o, unsigned *count, double **times, char **e) {
  *count = 0; *times = nullptr;
  double *out = nullptr;
  try {
    const std::vector<Time> &t = (*arg(o))->optionTimes();
    out = qlAllocateDoubles(t.size());
    for (size_t i = 0; i < t.size(); ++i) out[i] = t[i];
    *count = t.size(); *times = out;
  } catch (const std::exception& er) {qlFreeDoubles(out); *e = tracedup(er.what());}
}

void qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o) {del(o);}
QlCapFloorTermVolatilityStructure* qlCapFloorTermVolSurfaceAsCapFloorTermVolatilityStructure(QlCapFloorTermVolSurface *o) {return ret(new QlCapFloorTermVolatilityStructure(*arg(o)));}
void qlCapFloorTermVolSurfaceOptionDates(QlCapFloorTermVolSurface *o, unsigned *count, int **days, char **e) {
  *count = 0; *days = nullptr;
  int *out = nullptr;
  try {
    const std::vector<Date> &dates = (*arg(o))->optionDates();
    out = qlAllocateInts(dates.size());
    for (size_t i = 0; i < dates.size(); ++i) out[i] = dates[i].serialNumber();
    *count = dates.size(); *days = out;
  } catch (const std::exception& er) {qlFreeInts(out); *e = tracedup(er.what());}
}
void qlCapFloorTermVolSurfaceOptionTimes(QlCapFloorTermVolSurface *o, unsigned *count, double **times, char **e) {
  *count = 0; *times = nullptr;
  double *out = nullptr;
  try {
    const std::vector<Time> &t = (*arg(o))->optionTimes();
    out = qlAllocateDoubles(t.size());
    for (size_t i = 0; i < t.size(); ++i) out[i] = t[i];
    *count = t.size(); *times = out;
  } catch (const std::exception& er) {qlFreeDoubles(out); *e = tracedup(er.what());}
}
void qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o) {del(o);}
QlVolatilityTermStructure* qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o) {return ret(new QlVolatilityTermStructure(*arg(o)));}
double qlLocalVolTermStructureLocalVol(QlLocalVolTermStructure* o, int d, double underlyingLevel, int extrapolate, char **e) {
  try {return (*arg(o))->localVol(Date(d), underlyingLevel, extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
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
QlLocalVolTermStructure* qlNoExceptLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, double illegalLocalVolOverwrite, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new NoExceptLocalVolSurface(*arg(blackTS), *arg(riskFreeTS), *arg(dividendTS), *arg(underlying), illegalLocalVolOverwrite))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
QlLocalVolTermStructure* qlFixedLocalVolSurface(int referenceDate, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned matrixRows, unsigned matrixCols, double* matrixData, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new FixedLocalVolSurface(Date(referenceDate), qlDateVector(dates, datesLen),
      std::vector<Real>(strikes, strikes+strikesLen), ext::make_shared<Matrix>(qlMatrix(matrixData, matrixRows, matrixCols)),
      *arg(dayCounter), (FixedLocalVolSurface::Extrapolation)lowerExtrapolation, (FixedLocalVolSurface::Extrapolation)upperExtrapolation))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
void qlFreeGridModelLocalVolSurface(QlGridModelLocalVolSurface *o) {del(o);}
QlLocalVolTermStructure* qlGridModelLocalVolSurfaceAsLocalVolTermStructure(QlGridModelLocalVolSurface *o) {return ret(new QlLocalVolTermStructure(*arg(o)));}
QlCalibratedModel* qlGridModelLocalVolSurfaceAsCalibratedModel(QlGridModelLocalVolSurface *o, char **e) {
  try {return ret(new QlCalibratedModel(*arg(o)));
  } catch (std::exception& er) {return handleException<QlCalibratedModel*>(e, er);}}
QlGridModelLocalVolSurface* qlGridModelLocalVolSurface(int referenceDate, unsigned datesLen, int* dates, unsigned rows, unsigned* strikeLengths, double* strikes, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation, char **e) {
  try {
    std::vector<ext::shared_ptr<std::vector<Real>>> strikeRows;
    strikeRows.reserve(rows);
    size_t offset = 0;
    for (size_t i = 0; i < rows; ++i) {
      strikeRows.push_back(ext::make_shared<std::vector<Real>>(strikes + offset, strikes + offset + strikeLengths[i]));
      offset += strikeLengths[i];
    }
    return ret(new QlGridModelLocalVolSurface(alloc(new GridModelLocalVolSurface(
        Date(referenceDate), qlDateVector(dates, datesLen), strikeRows, *arg(dayCounter),
        (FixedLocalVolSurface::Extrapolation)lowerExtrapolation,
        (FixedLocalVolSurface::Extrapolation)upperExtrapolation))));
  } catch (std::exception& er) {return handleException<QlGridModelLocalVolSurface*>(e, er);}}
QlBlackVolTermStructure* qlHestonBlackVolSurface(QlHestonModel* model, int cpxLogFormula, unsigned integrationOrder, char **e) {
  try {return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(new HestonBlackVolSurface(
      Handle<HestonModel>(*arg(model)), (AnalyticHestonEngine::ComplexLogFormula)cpxLogFormula,
      AnalyticHestonEngine::Integration::gaussLaguerre(integrationOrder))))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}
void qlFreeAndreasenHugeVolatilityInterpl(QlAndreasenHugeVolatilityInterpl *o) {del(o);}
QlAndreasenHugeVolatilityInterpl* qlAndreasenHugeVolatilityInterpl(unsigned calibrationLen, QlVanillaOption** options, QlQuote** quotes, QlQuote* spot, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int interpolationType, int calibrationType, unsigned nGridPoints, double minStrike, double maxStrike, QlOptimizationMethod* optimizationMethod, QlEndCriteria* endCriteria, char **e) {
  try {
    AndreasenHugeVolatilityInterpl::CalibrationSet calibrationSet;
    calibrationSet.reserve(calibrationLen);
    for (size_t i = 0; i < calibrationLen; ++i)
      calibrationSet.emplace_back(*arg(options[i]), handlePtr(arg(quotes[i])));
    return ret(new QlAndreasenHugeVolatilityInterpl(alloc(new AndreasenHugeVolatilityInterpl(
        calibrationSet, *arg(spot), *arg(riskFreeRate), *arg(dividendYield),
        (AndreasenHugeVolatilityInterpl::InterpolationType)interpolationType,
        (AndreasenHugeVolatilityInterpl::CalibrationType)calibrationType, nGridPoints,
        minStrike, maxStrike, *arg(optimizationMethod), **arg(endCriteria)))));
  } catch (std::exception& er) {return handleException<QlAndreasenHugeVolatilityInterpl*>(e, er);}}
void qlAndreasenHugeVolatilityInterplCalibrationError(QlAndreasenHugeVolatilityInterpl* o, unsigned* count, double** values, char **e) {
  *count = 0; *values = nullptr;
  try {
    const auto errors = (*arg(o))->calibrationError();
    auto out = qlAllocateDoubles(3); out[0] = std::get<0>(errors); out[1] = std::get<1>(errors); out[2] = std::get<2>(errors);
    *count = 3; *values = out;
  } catch (std::exception& er) {(void)handleException<void *>(e, er);}}
double qlAndreasenHugeVolatilityInterplFwd(QlAndreasenHugeVolatilityInterpl* o, double t, char **e) {
  try {return (*arg(o))->fwd(t);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAndreasenHugeVolatilityInterplOptionPrice(QlAndreasenHugeVolatilityInterpl* o, double t, double strike, int optionType, char **e) {
  try {return (*arg(o))->optionPrice(t, strike, (Option::Type)optionType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAndreasenHugeVolatilityInterplLocalVol(QlAndreasenHugeVolatilityInterpl* o, double t, double strike, char **e) {
  try {return (*arg(o))->localVol(t, strike);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlBlackVolTermStructure* qlAndreasenHugeVolatilityAdapter(QlAndreasenHugeVolatilityInterpl* o, double eps, char **e) {
  try {return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(new AndreasenHugeVolatilityAdapter(*arg(o), eps)))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}
QlLocalVolTermStructure* qlAndreasenHugeLocalVolAdapter(QlAndreasenHugeVolatilityInterpl* o, char **e) {
  try {return ret(new QlLocalVolTermStructure(alloc(new AndreasenHugeLocalVolAdapter(*arg(o)))));
  } catch (std::exception& er) {return handleException<QlLocalVolTermStructure*>(e, er);}}
QlBlackVolTermStructure* qlImpliedVolTermStructure(QlBlackVolTermStructure* origTS, int referenceDate, char **e) {
  try {return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(alloc(new ImpliedVolTermStructure(*arg(origTS), Date(referenceDate))))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}

QlBlackVarianceCurve* qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    auto c = allocShared(new BlackVarianceCurve(Date(referenceDate), qlDateVector(dates, datesLen), std::vector<double>(blackVolCurve, blackVolCurve+blackVolCurveLen), *arg(dayCounter), forceMonotoneVariance));
    if (interpolator != Null<Integer>())
      qlSetBlackVarianceCurveInterpolationAux(c.get(), interpolator, approximator, approximatorArg);
    return ret(new QlBlackVarianceCurve(c));
  } catch (std::exception& er) {
    return handleException<QlBlackVarianceCurve*>(e, er);
  }
}

QlBlackVolTermStructure* qlBlackVarianceSurface(int referenceDate, Calendar* cal, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation, int interpolator, char **e) {
  try {
    auto s = allocShared(new BlackVarianceSurface(Date(referenceDate), *arg(cal), qlDateVector(dates, datesLen), std::vector<double>(strikes, strikes+strikesLen), qlMatrix(blackVolMatrix, blackVolMatrixRows, blackVolMatrixCols), *arg(dayCounter), (BlackVarianceSurface::Extrapolation)lowerExtrapolation, (BlackVarianceSurface::Extrapolation)upperExtrapolation));
    qlSetBlackVarianceSurfaceInterpolationAux(s.get(), interpolator);
    return ret(new QlBlackVolTermStructure(s));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}
QlBlackVolTermStructure* qlPiecewiseBlackVarianceSurface(int referenceDate, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolsRows, unsigned blackVolsCols, double* blackVols, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(shared_ptr<BlackVolTermStructure>(
        PiecewiseBlackVarianceSurface::makeFromGrid(Date(referenceDate), qlDateVector(dates, datesLen),
            std::vector<Real>(strikes, strikes+strikesLen), qlMatrix(blackVols, blackVolsRows, blackVolsCols), *arg(dayCounter)))));
  } catch (std::exception& er) {return handleException<QlBlackVolTermStructure*>(e, er);}}
void qlFreeBlackVolatilitySurfaceDelta(QlBlackVolatilitySurfaceDelta *o) {del(o);}
QlBlackVolTermStructure* qlBlackVolatilitySurfaceDeltaAsBlackVolTermStructure(QlBlackVolatilitySurfaceDelta *o) {return ret(new QlBlackVolTermStructure(*arg(o)));}
QlBlackVolatilitySurfaceDelta* qlBlackVolatilitySurfaceDelta(int referenceDate, unsigned datesLen, int* dates,
    unsigned putDeltasLen, double* putDeltas, unsigned callDeltasLen, double* callDeltas,
    int hasAtm, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix,
    DayCounter* dayCounter, Calendar* cal, QlQuote* spot,
    QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS,
    int deltaType, int atmType, int atmDeltaType,
    int interpolationMethod, int flatStrikeExtrapolation, int timeExtrapolationType,
    int switchTenorLen, int switchTenorUnit,
    int longTermDeltaType, int longTermAtmType, int longTermAtmDeltaType,
    char **e) {
  try {
    return ret(new QlBlackVolatilitySurfaceDelta(alloc(new BlackVolatilitySurfaceDelta(
        Date(referenceDate), qlDateVector(dates, datesLen),
        std::vector<Real>(putDeltas, putDeltas+putDeltasLen), std::vector<Real>(callDeltas, callDeltas+callDeltasLen),
        hasAtm, qlMatrix(blackVolMatrix, blackVolMatrixRows, blackVolMatrixCols),
        *arg(dayCounter), *arg(cal), *arg(spot), *arg(domesticTS), *arg(foreignTS),
        (DeltaVolQuote::DeltaType)deltaType, (DeltaVolQuote::AtmType)atmType,
        atmDeltaType < 0 ? ext::nullopt : ext::optional<DeltaVolQuote::DeltaType>((DeltaVolQuote::DeltaType)atmDeltaType),
        (BlackVolatilitySurfaceDelta::SmileInterpolationMethod)interpolationMethod,
        flatStrikeExtrapolation, (BlackVolTimeExtrapolation::Type)timeExtrapolationType,
        Period(switchTenorLen, (TimeUnit)switchTenorUnit),
        (DeltaVolQuote::DeltaType)longTermDeltaType, (DeltaVolQuote::AtmType)longTermAtmType,
        longTermAtmDeltaType < 0 ? ext::nullopt : ext::optional<DeltaVolQuote::DeltaType>((DeltaVolQuote::DeltaType)longTermAtmDeltaType)))));
  } catch (std::exception& er) {return handleException<QlBlackVolatilitySurfaceDelta*>(e, er);}}
QlSmileSection* qlBlackVolatilitySurfaceDeltaSmile1(QlBlackVolatilitySurfaceDelta* o, double t, char **e) {
  try {return ret(new QlSmileSection((*arg(o))->blackVolSmile(t)));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlSmileSection* qlBlackVolatilitySurfaceDeltaSmile(QlBlackVolatilitySurfaceDelta* o, int d, char **e) {
  try {return ret(new QlSmileSection((*arg(o))->blackVolSmile(Date(d))));
  } catch (std::exception& er) {return handleException<QlSmileSection*>(e, er);}}
QlCapFloorTermVolSurface* qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(settlementDays, *arg(calendar), (BusinessDayConvention)bdc,
            qlPeriodVector(n, u, l), std::vector<double>(strikes, strikes+strikesLen), qlHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolSurface*>(e, er);}}
QlCapFloorTermVolSurface* qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned l, int *n, unsigned, int *u, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e) {
  try {return ret(new QlCapFloorTermVolSurface(alloc(new CapFloorTermVolSurface(Date(settlementDate), *arg(calendar), (BusinessDayConvention)bdc,
            qlPeriodVector(n, u, l), std::vector<double>(strikes, strikes+strikesLen), qlHandleMatrix(volatilities, volatilitiesRows, volatilitiesCols), *arg(dc)))));
  } catch (std::exception& er) {return handleException<QlCapFloorTermVolSurface*>(e, er);}}
QlSwaptionVolatilityStructure* qlSwaptionVolatilityMatrix(int referenceDate, Calendar* calendar, int bdc,
    unsigned optionTenorsLen, int *optionTenorsNum, unsigned, int *optionTenorsUnit,
    unsigned swapTenorsLen, int *swapTenorsNum, unsigned, int *swapTenorsUnit,
    unsigned volRows, unsigned volCols, QlQuote** vols, DayCounter* dc, int flatExtrapolation, int type,
    unsigned shiftRows, unsigned shiftCols, double* shifts, char **e) {
  try {return ret(new QlSwaptionVolatilityStructure(shared_ptr<SwaptionVolatilityStructure>(alloc(new SwaptionVolatilityMatrix(
            Date(referenceDate), *arg(calendar), (BusinessDayConvention)bdc,
            qlPeriodVector(optionTenorsNum, optionTenorsUnit, optionTenorsLen),
            qlPeriodVector(swapTenorsNum, swapTenorsUnit, swapTenorsLen),
            qlHandleMatrix(vols, volRows, volCols), *arg(dc), (bool)flatExtrapolation, (VolatilityType)type,
            qlRealMatrix(shifts, shiftRows, shiftCols))))));
  } catch (std::exception& er) {return handleException<QlSwaptionVolatilityStructure*>(e, er);}}
QlSwaptionVolatilityStructure* qlSwaptionVolatilityMatrix1(Calendar* calendar, int bdc,
    unsigned optionTenorsLen, int *optionTenorsNum, unsigned, int *optionTenorsUnit,
    unsigned swapTenorsLen, int *swapTenorsNum, unsigned, int *swapTenorsUnit,
    unsigned volRows, unsigned volCols, QlQuote** vols, DayCounter* dc, int flatExtrapolation, int type,
    unsigned shiftRows, unsigned shiftCols, double* shifts, char **e) {
  try {return ret(new QlSwaptionVolatilityStructure(shared_ptr<SwaptionVolatilityStructure>(alloc(new SwaptionVolatilityMatrix(
            *arg(calendar), (BusinessDayConvention)bdc,
            qlPeriodVector(optionTenorsNum, optionTenorsUnit, optionTenorsLen),
            qlPeriodVector(swapTenorsNum, swapTenorsUnit, swapTenorsLen),
            qlHandleMatrix(vols, volRows, volCols), *arg(dc), (bool)flatExtrapolation, (VolatilityType)type,
            qlRealMatrix(shifts, shiftRows, shiftCols))))));
  } catch (std::exception& er) {return handleException<QlSwaptionVolatilityStructure*>(e, er);}}

// SabrSwaptionVolatilityCube and InterpolatedSwaptionVolatilityCube each get their own dedicated
// Haskell-visible type (QlSabrSwaptionVolatilityCube/QlInterpolatedSwaptionVolatilityCube) rather
// than returning the generic QlSwaptionVolatilityStructure the way swaptionVolatilityMatrix'/
// constantSwaptionVolatility do: each class has its own real getters (sparseSabrParameters etc.,
// atmStrike), so per CLAUDE.md's "introduce a dedicated type when the class has its own
// calc/getter" rule it earns a leaf, and every diagnostic below takes the concrete pointer
// directly -- no QL_REQUIRE-guarded dynamic_pointer_cast anywhere in this file, for these two
// classes or for SabrInterpolatedSmileSection above (which used to need one). Use
// qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure/
// qlInterpolatedSwaptionVolatilityCubeAsSwaptionVolatilityStructure (below) to pass either into
// anything that wants the generic parent (pricing engines, relinkable handles, etc.).
//
// endCriteria/method are nullable (NULL -> empty shared_ptr, letting SABRInterpolation's own
// internal EndCriteria/LevenbergMarquardt defaults apply at every calibrated node); when given,
// `endCriteria ? *arg(endCriteria) : shared_ptr<EndCriteria>()` copies a shared reference into
// this ctor's own shared_ptr member -- safe regardless of when Haskell's own EndCriteria/
// OptimizationMethod box is collected, since QlEndCriteria/QlOptimizationMethod are themselves
// shared_ptr boxes (see qlLevenbergMarquardt/qlSimplex/qlEndCriteria in qlMisc.cpp): the
// underlying object is only freed once every shared_ptr referencing it has gone away.
//
// volSpreads and parametersGuess are both flattened over the (optionTenor x swapTenor) product as
// the OUTER index (row = j*nSwapTenors+k, j over optionTenors, k over swapTenors) -- not simply
// "one row per optionTenor" the way qlSwaptionVolatilityMatrix's grid is. volSpreadsCols is
// strikeSpreadsLen; parametersGuessCols is always 4 (SABR's alpha/beta/nu/rho).
//
// Calibration is lazy (XabrSwaptionVolatilityCube is a LazyObject): unlike
// qlSabrInterpolatedSmileSection, construction here does NOT force an eager fit, so a
// constructor call can succeed even for inputs that will later fail to calibrate -- the error
// only surfaces on the first smileSection/volatility/etc. call.
QlSabrSwaptionVolatilityCube* qlSabrSwaptionVolatilityCube(QlSwaptionVolatilityStructure* atmVolStructure,
    unsigned optionTenorsLen, int *optionTenorsNum, unsigned, int *optionTenorsUnit,
    unsigned swapTenorsLen, int *swapTenorsNum, unsigned, int *swapTenorsUnit,
    unsigned strikeSpreadsLen, double* strikeSpreads,
    unsigned volSpreadsRows, unsigned volSpreadsCols, QlQuote** volSpreads,
    QlSwapIndex* swapIndexBase, QlSwapIndex* shortSwapIndexBase,
    int vegaWeightedSmileFit,
    unsigned parametersGuessRows, unsigned parametersGuessCols, QlQuote** parametersGuess,
    int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed,
    int isAtmCalibrated,
    QlEndCriteria* endCriteria, QlOptimizationMethod* method,
    double maxErrorTolerance, double errorAccept, int useMaxError, unsigned maxGuesses,
    int backwardFlat, double cutoffStrike, char **e) {
  try {
    return ret(new QlSabrSwaptionVolatilityCube(alloc(new SabrSwaptionVolatilityCube(
            *arg(atmVolStructure),
            qlPeriodVector(optionTenorsNum, optionTenorsUnit, optionTenorsLen),
            qlPeriodVector(swapTenorsNum, swapTenorsUnit, swapTenorsLen),
            std::vector<Real>(strikeSpreads, strikeSpreads + strikeSpreadsLen),
            qlHandleMatrix(volSpreads, volSpreadsRows, volSpreadsCols),
            *arg(swapIndexBase), *arg(shortSwapIndexBase),
            (bool)vegaWeightedSmileFit,
            qlHandleMatrix(parametersGuess, parametersGuessRows, parametersGuessCols),
            std::vector<bool>{(bool)isAlphaFixed, (bool)isBetaFixed, (bool)isNuFixed, (bool)isRhoFixed},
            (bool)isAtmCalibrated,
            endCriteria ? *arg(endCriteria) : shared_ptr<EndCriteria>(), maxErrorTolerance,
            method ? *arg(method) : shared_ptr<OptimizationMethod>(),
            errorAccept, (bool)useMaxError, maxGuesses, (bool)backwardFlat, cutoffStrike))));
  } catch (std::exception& er) {return handleException<QlSabrSwaptionVolatilityCube*>(e, er);}}
void qlFreeSabrSwaptionVolatilityCube(QlSabrSwaptionVolatilityCube *o) {del(o);}
// Fresh Handle for this newly built object -- same shape as every QlXxxAsSwaptionVolatilityStructure-
// style upcast that starts from a shared_ptr leaf (e.g. qlBlackVolatilitySurfaceDeltaAsBlackVolTermStructure),
// not a rewrap of an existing Handle.
QlSwaptionVolatilityStructure* qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure(QlSabrSwaptionVolatilityCube *o) {
  return ret(new QlSwaptionVolatilityStructure(*arg(o)));}

// NoArbSabrSwaptionVolatilityCube is XabrSwaptionVolatilityCube<SwaptionVolCubeNoArbSabrModel> --
// the same class template as SabrSwaptionVolatilityCube one model policy over, with an identical
// constructor signature (both policies use the default XabrModelTraits<> nParams=4) and identical
// getters, so this is a straight copy of the SabrSwaptionVolatilityCube shims above with the type
// swapped -- no new marshalling shape. See the comment above qlSabrSwaptionVolatilityCube for the
// EndCriteria/OptimizationMethod nullability, volSpreads/parametersGuess flattening, and lazy-
// calibration notes, all identical here.
QlNoArbSabrSwaptionVolatilityCube* qlNoArbSabrSwaptionVolatilityCube(QlSwaptionVolatilityStructure* atmVolStructure,
    unsigned optionTenorsLen, int *optionTenorsNum, unsigned, int *optionTenorsUnit,
    unsigned swapTenorsLen, int *swapTenorsNum, unsigned, int *swapTenorsUnit,
    unsigned strikeSpreadsLen, double* strikeSpreads,
    unsigned volSpreadsRows, unsigned volSpreadsCols, QlQuote** volSpreads,
    QlSwapIndex* swapIndexBase, QlSwapIndex* shortSwapIndexBase,
    int vegaWeightedSmileFit,
    unsigned parametersGuessRows, unsigned parametersGuessCols, QlQuote** parametersGuess,
    int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed,
    int isAtmCalibrated,
    QlEndCriteria* endCriteria, QlOptimizationMethod* method,
    double maxErrorTolerance, double errorAccept, int useMaxError, unsigned maxGuesses,
    int backwardFlat, double cutoffStrike, char **e) {
  try {
    return ret(new QlNoArbSabrSwaptionVolatilityCube(alloc(new NoArbSabrSwaptionVolatilityCube(
            *arg(atmVolStructure),
            qlPeriodVector(optionTenorsNum, optionTenorsUnit, optionTenorsLen),
            qlPeriodVector(swapTenorsNum, swapTenorsUnit, swapTenorsLen),
            std::vector<Real>(strikeSpreads, strikeSpreads + strikeSpreadsLen),
            qlHandleMatrix(volSpreads, volSpreadsRows, volSpreadsCols),
            *arg(swapIndexBase), *arg(shortSwapIndexBase),
            (bool)vegaWeightedSmileFit,
            qlHandleMatrix(parametersGuess, parametersGuessRows, parametersGuessCols),
            std::vector<bool>{(bool)isAlphaFixed, (bool)isBetaFixed, (bool)isNuFixed, (bool)isRhoFixed},
            (bool)isAtmCalibrated,
            endCriteria ? *arg(endCriteria) : shared_ptr<EndCriteria>(), maxErrorTolerance,
            method ? *arg(method) : shared_ptr<OptimizationMethod>(),
            errorAccept, (bool)useMaxError, maxGuesses, (bool)backwardFlat, cutoffStrike))));
  } catch (std::exception& er) {return handleException<QlNoArbSabrSwaptionVolatilityCube*>(e, er);}}
void qlFreeNoArbSabrSwaptionVolatilityCube(QlNoArbSabrSwaptionVolatilityCube *o) {del(o);}
QlSwaptionVolatilityStructure* qlNoArbSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure(QlNoArbSabrSwaptionVolatilityCube *o) {
  return ret(new QlSwaptionVolatilityStructure(*arg(o)));}
void qlNoArbSabrSwaptionVolatilityCubeSparseSabrParameters(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->sparseSabrParameters(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlNoArbSabrSwaptionVolatilityCubeDenseSabrParameters(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->denseSabrParameters(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlNoArbSabrSwaptionVolatilityCubeMarketVolCube(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->marketVolCube(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlNoArbSabrSwaptionVolatilityCubeVolCubeAtmCalibrated(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->volCubeAtmCalibrated(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
double qlNoArbSabrSwaptionVolatilityCubeAtmStrike1(QlNoArbSabrSwaptionVolatilityCube* o, int optionDate, int n, int u, char **e) {
  try {return (*arg(o))->atmStrike(Date(optionDate), Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlNoArbSabrSwaptionVolatilityCubeAtmStrike(QlNoArbSabrSwaptionVolatilityCube* o, int optionN, int optionU, int n, int u, char **e) {
  try {return (*arg(o))->atmStrike(Period(optionN, (TimeUnit)optionU), Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

// No EndCriteria/OptimizationMethod hazard here: InterpolatedSwaptionVolatilityCube only
// interpolates the given volSpreads, it never calibrates anything.
QlInterpolatedSwaptionVolatilityCube* qlInterpolatedSwaptionVolatilityCube(QlSwaptionVolatilityStructure* atmVolStructure,
    unsigned optionTenorsLen, int *optionTenorsNum, unsigned, int *optionTenorsUnit,
    unsigned swapTenorsLen, int *swapTenorsNum, unsigned, int *swapTenorsUnit,
    unsigned strikeSpreadsLen, double* strikeSpreads,
    unsigned volSpreadsRows, unsigned volSpreadsCols, QlQuote** volSpreads,
    QlSwapIndex* swapIndexBase, QlSwapIndex* shortSwapIndexBase,
    int vegaWeightedSmileFit, char **e) {
  try {
    return ret(new QlInterpolatedSwaptionVolatilityCube(alloc(new InterpolatedSwaptionVolatilityCube(
            *arg(atmVolStructure),
            qlPeriodVector(optionTenorsNum, optionTenorsUnit, optionTenorsLen),
            qlPeriodVector(swapTenorsNum, swapTenorsUnit, swapTenorsLen),
            std::vector<Real>(strikeSpreads, strikeSpreads + strikeSpreadsLen),
            qlHandleMatrix(volSpreads, volSpreadsRows, volSpreadsCols),
            *arg(swapIndexBase), *arg(shortSwapIndexBase),
            (bool)vegaWeightedSmileFit))));
  } catch (std::exception& er) {return handleException<QlInterpolatedSwaptionVolatilityCube*>(e, er);}}
void qlFreeInterpolatedSwaptionVolatilityCube(QlInterpolatedSwaptionVolatilityCube *o) {del(o);}
QlSwaptionVolatilityStructure* qlInterpolatedSwaptionVolatilityCubeAsSwaptionVolatilityStructure(QlInterpolatedSwaptionVolatilityCube *o) {
  return ret(new QlSwaptionVolatilityStructure(*arg(o)));}

// Matrix-out diagnostics, direct on the concrete type -- no downcast needed. Composes the
// established 1D out-array idiom (qlAllocateDoubles + unsigned*len/double**vs, see
// qlGsrVolatility/qlCalibratedModelParams) with row/col out-params -- no prior shim in this
// codebase returns a Matrix outward, every existing Matrix use (qlMatrix/qlHandleMatrix/
// qlRealMatrix) crosses the boundary inward only.
void qlSabrSwaptionVolatilityCubeSparseSabrParameters(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->sparseSabrParameters(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlSabrSwaptionVolatilityCubeDenseSabrParameters(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->denseSabrParameters(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlSabrSwaptionVolatilityCubeMarketVolCube(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->marketVolCube(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}
void qlSabrSwaptionVolatilityCubeVolCubeAtmCalibrated(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e) {
  try {fillMatrixOut((*arg(o))->volCubeAtmCalibrated(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

// atmStrike is defined on the abstract SwaptionVolatilityCube base (both concrete subtypes
// inherit it); bound once per concrete leaf rather than via a shared abstract-base type, since
// neither subtype otherwise needs one and CLAUDE.md's "no dedicated type for a class with no
// calcs of its own" argues against adding a node just for this.
double qlSabrSwaptionVolatilityCubeAtmStrike1(QlSabrSwaptionVolatilityCube* o, int optionDate, int n, int u, char **e) {
  try {return (*arg(o))->atmStrike(Date(optionDate), Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSabrSwaptionVolatilityCubeAtmStrike(QlSabrSwaptionVolatilityCube* o, int optionN, int optionU, int n, int u, char **e) {
  try {return (*arg(o))->atmStrike(Period(optionN, (TimeUnit)optionU), Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlInterpolatedSwaptionVolatilityCubeAtmStrike1(QlInterpolatedSwaptionVolatilityCube* o, int optionDate, int n, int u, char **e) {
  try {return (*arg(o))->atmStrike(Date(optionDate), Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlInterpolatedSwaptionVolatilityCubeAtmStrike(QlInterpolatedSwaptionVolatilityCube* o, int optionN, int optionU, int n, int u, char **e) {
  try {return (*arg(o))->atmStrike(Period(optionN, (TimeUnit)optionU), Period(n, (TimeUnit)u));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

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
    auto ts = allocShared(qlInterpolatedHazardRateCurveAux(qlDateVector(dates, datesLen), std::vector<double>(hazardRates, hazardRates+hazardRatesLen), *arg(dayCounter), *arg(cal), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), interpolator, approximator, approximatorArg));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlDefaultProbabilityTermStructure(ts));
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
    auto ts = allocShared(qlPiecewiseDefaultCurveAux(Date(referenceDate), qlVector(instruments, instrumentsLen), *arg(dayCounter), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), trait, interpolator, approximator, approximatorArg));
    return ret(new QlDefaultProbabilityTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlDefaultProbabilityTermStructure*>(e, er);}}
QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve1(unsigned settlementDays, Calendar *calendar, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseDefaultCurveAux1(settlementDays, *arg(calendar), qlVector(instruments, instrumentsLen), *arg(dayCounter), qlHandleVector(jumps, jumpsLen), qlDateVector(jumpDates, jDatesLen), trait, interpolator, approximator, approximatorArg));
    return ret(new QlDefaultProbabilityTermStructure(ts));
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

/* CommodityCurve */

QlCommodityCurve* qlCommodityCurve(char *name, CommodityType *commodityType, Currency *currency,
                                   UnitOfMeasure *unitOfMeasure, Calendar *calendar,
                                   unsigned datesLen, int *dates, unsigned pricesLen, double *prices,
                                   DayCounter *dayCounter, char **e) {
  try {return ret(new QlCommodityCurve(alloc(new CommodityCurve(
      arg(name), *arg(commodityType), *arg(currency), *arg(unitOfMeasure), *arg(calendar),
      qlDateVector(dates, datesLen), std::vector<Real>(prices, prices+pricesLen), *arg(dayCounter)))));
  } catch (std::exception& er) {return handleException<QlCommodityCurve*>(e, er);}}

void qlFreeCommodityCurve(QlCommodityCurve *o) {del(o);}
QlTermStructure* qlCommodityCurveAsTermStructure(QlCommodityCurve *o) {return ret(new QlTermStructure(*arg(o)));}
char *qlCommodityCurveName(QlCommodityCurve *o) {return tracedup((*arg(o))->name().c_str());}
CommodityType *qlCommodityCurveCommodityType(QlCommodityCurve *o, char **e) {
  try {return ret(new CommodityType((*arg(o))->commodityType()));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}
UnitOfMeasure *qlCommodityCurveUnitOfMeasure(QlCommodityCurve *o, char **e) {
  try {return ret(new UnitOfMeasure((*arg(o))->unitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
Currency *qlCommodityCurveCurrency(QlCommodityCurve *o, char **e) {
  try {return ret(new Currency((*arg(o))->currency()));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}}

void qlCommodityCurveDates(QlCommodityCurve *o, unsigned *count, int **days, char **e) {
  *count = 0; *days = 0;
  try {
    const std::vector<Date> &dates = (*arg(o))->dates();
    unsigned n = (unsigned)dates.size();
    int *ds = qlAllocateInts(n);
    for (size_t i = 0; i < dates.size(); ++i)
      ds[i] = dates[i].serialNumber();
    *count = n; *days = ds;
  } catch (std::exception& er) {*e = tracedup(er.what());}
}

void qlCommodityCurvePrices(QlCommodityCurve *o, unsigned *count, double **prices, char **e) {
  *count = 0; *prices = 0;
  try {
    const std::vector<Real> &p = (*arg(o))->prices();
    unsigned n = (unsigned)p.size();
    double *ps = qlAllocateDoubles(n);
    for (size_t i = 0; i < p.size(); ++i)
      ps[i] = p[i];
    *count = n; *prices = ps;
  } catch (std::exception& er) {*e = tracedup(er.what());}
}

int qlCommodityCurveEmpty(QlCommodityCurve *o) {return (*arg(o))->empty();}

// basisOfCurve_ is a nullptr shared_ptr when unset -- returned as-is (not via ret(), nothing new
// is allocated here) so the Haskell side's peekMaybeCommodityCurve can null-check it directly.
QlCommodityCurve *qlCommodityCurveBasisOfCurve(QlCommodityCurve *o) {
  const shared_ptr<CommodityCurve> &b = (*arg(o))->basisOfCurve();
  return b ? ret(new QlCommodityCurve(b)) : nullptr;
}

// Not bad_alloc-only: setBasisOfCurve() itself calls
// CommodityPricingHelper::calculateUomConversionFactor, which QL_REQUIRE-throws via
// UnitOfMeasureConversionManager::lookup when no matching conversion is registered.
void qlCommodityCurveSetBasisOfCurve(QlCommodityCurve *o, QlCommodityCurve *basisOfCurve, char **e) {
  try {(*arg(o))->setBasisOfCurve(*arg(basisOfCurve));
  } catch (std::exception& er) {*e = tracedup(er.what());}
}

// Builds the ExchangeContracts map the nearby-rolling price()/underlyingPriceDate() calls take.
// Always constructed (even when n==0): price() only dereferences it when nearbyOffset>0, and
// underlyingPriceDate() requires nearbyOffset>0 too (QL_REQUIRE'd before any lower_bound call), so
// an empty-but-non-null map is exactly as safe as a null one for every reachable call shape here,
// and skips a conditional the two call sites would otherwise have to repeat.
static shared_ptr<ExchangeContracts> qlBuildExchangeContracts(
    unsigned n, int *ecKeys, char **ecCodes, int *ecExpirations, int *ecStarts, int *ecEnds) {
  auto ecs = ext::make_shared<ExchangeContracts>();
  for (unsigned i = 0; i < n; ++i)
    (*ecs)[Date(ecKeys[i])] = ExchangeContract(ecCodes[i], Date(ecExpirations[i]),
                                                Date(ecStarts[i]), Date(ecEnds[i]));
  return ecs;
}

// nearbyOffset<=0 never touches exchangeContracts (see commoditycurve.hpp's inline price()), so
// this also serves the plain flat-price case when called with an empty map and offset 0.
double qlCommodityCurvePrice(QlCommodityCurve *o, int date,
    unsigned ecLen1, int *ecKeys, unsigned, char **ecCodes,
    unsigned, int *ecExpirations, unsigned, int *ecStarts,
    unsigned, int *ecEnds, int nearbyOffset, char **e) {
  try {
    auto ecs = qlBuildExchangeContracts(ecLen1, ecKeys, ecCodes, ecExpirations, ecStarts, ecEnds);
    return (*arg(o))->price(Date(date), ecs, nearbyOffset);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlCommodityCurveBasisOfPrice(QlCommodityCurve *o, int date, char **e) {
  try {return (*arg(o))->basisOfPrice(Date(date));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

int qlCommodityCurveUnderlyingPriceDate(QlCommodityCurve *o, int date,
    unsigned ecLen1, int *ecKeys, unsigned, char **ecCodes,
    unsigned, int *ecExpirations, unsigned, int *ecStarts,
    unsigned, int *ecEnds, int nearbyOffset, char **e) {
  try {
    auto ecs = qlBuildExchangeContracts(ecLen1, ecKeys, ecCodes, ecExpirations, ecStarts, ecEnds);
    return (*arg(o))->underlyingPriceDate(Date(date), ecs, nearbyOffset).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}

/* CommodityIndex */

// exchangeContracts/nearbyOffset are hardcoded to null/0 -- see qlTermStructure.h's comment;
// forwardCurve is nullable, matching upstream's own nullable ext::shared_ptr<CommodityCurve>.
QlCommodityIndex* qlCommodityIndex(char *name, CommodityType *commodityType, Currency *currency,
                                   UnitOfMeasure *unitOfMeasure, Calendar *calendar,
                                   double lotQuantity, QlCommodityCurve *forwardCurve, char **e) {
  try {return ret(new QlCommodityIndex(alloc(new CommodityIndex(
      name, *arg(commodityType), *arg(currency), *arg(unitOfMeasure), *arg(calendar), lotQuantity,
      forwardCurve ? *arg(forwardCurve) : shared_ptr<CommodityCurve>(),
      shared_ptr<ExchangeContracts>(), 0))));
  } catch (std::exception& er) {return handleException<QlCommodityIndex*>(e, er);}}

void qlFreeCommodityIndex(QlCommodityIndex *o) {del(o);}
QlIndex* qlCommodityIndexAsIndex(QlCommodityIndex *o) {return ret(new QlIndex(*arg(o)));}

// commodityType()/currency()/unitOfMeasure()/lotQuantity()/forwardCurve() are all plain,
// never-mutated echoes of the constructor's own arguments (commodityindex.hpp's inline getters
// each just `return foo_;`) -- not bound, per CLAUDE.md's trivial-getter rule.

double qlCommodityIndexForwardPrice(QlCommodityIndex *o, int date, char **e) {
  try {return (*arg(o))->forwardPrice(Date(date));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

// lastQuoteDate() -> timeSeries().lastDate(), which QL_REQUIREs a non-empty historical fixing
// series -- check emptiness first (via CommodityIndex::empty(), itself just timeSeries().empty())
// rather than catching the exception, so callers can check commodityIndexEmpty first if they want.
int qlCommodityIndexLastQuoteDate(QlCommodityIndex *o, char **e) {
  try {return (*arg(o))->lastQuoteDate().serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCommodityIndexEmpty(QlCommodityIndex *o) {return (*arg(o))->empty();}

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

QlZeroCouponInflationSwap* qlZeroCouponInflationSwapHelperSwap(QlZeroCouponInflationSwapHelper* o, char **e) {try {return ret(new QlZeroCouponInflationSwap((*arg(o))->swap()));} catch (std::exception& er) {return handleException<QlZeroCouponInflationSwap*>(e, er);}}
QlYearOnYearInflationSwap* qlYearOnYearInflationSwapHelperSwap(QlYearOnYearInflationSwapHelper* o, char **e) {try {return ret(new QlYearOnYearInflationSwap((*arg(o))->swap()));} catch (std::exception& er) {return handleException<QlYearOnYearInflationSwap*>(e, er);}}

QlZeroInflationTermStructure* qlPiecewiseZeroInflationCurve(int referenceDate, int baseDate, int frequency, DayCounter* dayCounter, unsigned instrumentsLen, QlZeroCouponInflationSwapHelper** instruments, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    // instruments[i] is shared_ptr<ZeroCouponInflationSwapHelper>*; push_back upcasts each
    // element to shared_ptr<BootstrapHelper<ZeroInflationTermStructure>> (PiecewiseZeroInflationCurve's
    // helper type) -- qlVector can't do this since it deduces the vector's element type from the
    // array's pointee type, not the target parameter type.
    std::vector<shared_ptr<BootstrapHelper<ZeroInflationTermStructure> > > instr;
    instr.reserve(instrumentsLen);
    for (unsigned i = 0; i < instrumentsLen; ++i) instr.push_back(*instruments[i]);
    auto ts = allocShared(qlPiecewiseZeroInflationCurveAux(Date(referenceDate), Date(baseDate), (Frequency)frequency, *arg(dayCounter),
        instr, interpolator, approximator, approximatorArg));
    return ret(new QlZeroInflationTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlZeroInflationTermStructure*>(e, er);}}
QlYoYInflationTermStructure* qlPiecewiseYoYInflationCurve(int referenceDate, int baseDate, double baseYoYRate, int frequency, DayCounter* dayCounter, unsigned instrumentsLen, QlYearOnYearInflationSwapHelper** instruments, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    std::vector<shared_ptr<BootstrapHelper<YoYInflationTermStructure> > > instr;
    instr.reserve(instrumentsLen);
    for (unsigned i = 0; i < instrumentsLen; ++i) instr.push_back(*instruments[i]);
    auto ts = allocShared(qlPiecewiseYoYInflationCurveAux(Date(referenceDate), Date(baseDate), baseYoYRate, (Frequency)frequency, *arg(dayCounter),
        instr, interpolator, approximator, approximatorArg));
    return ret(new QlYoYInflationTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYoYInflationTermStructure*>(e, er);}}

// InterpolatedYoYInflationCurve<Interpolator> -- direct (dates, rates) curve, unlike
// qlPiecewiseYoYInflationCurve's bootstrap from swap helpers. No seasonality (unbound elsewhere
// in hasquant).
QlYoYInflationTermStructure* qlInterpolatedYoYInflationCurve(int referenceDate,
    unsigned datesLen, int *dates, double *rates, int frequency, DayCounter *dayCounter,
    int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    std::vector<Date> ds(datesLen);
    for (unsigned i = 0; i < datesLen; ++i) ds[i] = Date(dates[i]);
    auto ts = allocShared(qlInterpolatedYoYInflationCurveAux(Date(referenceDate), ds, std::vector<Rate>(rates, rates+datesLen),
        (Frequency)frequency, *arg(dayCounter), interpolator, approximator, approximatorArg));
    return ret(new QlYoYInflationTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYoYInflationTermStructure*>(e, er);}}

QlRateHelper *qlDepositRateHelper(QlQuote *quote, int l, int u, unsigned fixDays, Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e) {
  try {return ret(new QlRateHelper(alloc(new DepositRateHelper( *arg(quote), Period(l, (TimeUnit)u), fixDays,
          *arg(calendar), (BusinessDayConvention) conv, eom, *arg(dayCount)))));
  } catch (std::exception& er) {return handleException<QlRateHelper *>(e, er);}}
QlBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face,
    Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv, double redemption, int issue, char **e) {
  try {return ret(new QlBondHelper(alloc(new FixedRateBondHelper(*arg(quote), settlDays, face, *arg(sched),
          std::vector<Rate>(coupons, coupons+cLen), *arg(dayCount), (BusinessDayConvention) conv, redemption, qlNullableDate(issue)))));
  } catch (std::exception& er) {return handleException<QlBondHelper *>(e, er);}}
QlBondHelper *qlCPIBondHelper(QlQuote *quote, unsigned settlementDays, double faceAmount, double baseCPI, int obsLagLen, int obsLagUnit,
    QlZeroInflationIndex* index, int observationInterpolation, Schedule *schedule, unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter,
    int paymentConvention, int issueDate, Calendar *paymentCalendar, char **e) {
  try {return ret(new QlBondHelper(alloc(new CPIBondHelper(*arg(quote), settlementDays, faceAmount, baseCPI, Period(obsLagLen, (TimeUnit)obsLagUnit),
          *arg(index), (CPI::InterpolationType)observationInterpolation, *arg(schedule), std::vector<Rate>(coupons, coupons+couponsLen),
          *arg(accrualDayCounter), (BusinessDayConvention)paymentConvention, qlNullableDate(issueDate), *arg(paymentCalendar)))));
  } catch (std::exception& er) {return handleException<QlBondHelper *>(e, er);}}
void qlFreeRateHelper(QlRateHelper *helper) {del(helper);}

// IterativeBootstrap's own constructor defaults (ql/termstructures/iterativebootstrap.hpp),
// for the narrow entry points that don't expose the settings. Kept here rather than as
// in-class initialisers so the struct stays a POD usable from the C side.
static QlIterativeBootstrapOpts defaultBootstrapOpts() {
  QlIterativeBootstrapOpts b;
  b.accuracy = b.minValue = b.maxValue = Null<Real>();
  b.maxAttempts = 1;
  b.maxFactor = b.minFactor = 2.0;
  b.dontThrow = 0;
  b.dontThrowSteps = 10;
  b.maxEvaluations = MAX_FUNCTION_EVALUATIONS;
  return b;
}

static QlIterativeBootstrapOpts bootstrapOpts(double accuracy, double minValue, double maxValue,
    unsigned maxAttempts, double maxFactor, double minFactor, int dontThrow,
    unsigned dontThrowSteps, unsigned maxEvaluations) {
  QlIterativeBootstrapOpts b;
  b.accuracy = accuracy; b.minValue = minValue; b.maxValue = maxValue;
  b.maxAttempts = maxAttempts; b.maxFactor = maxFactor; b.minFactor = minFactor;
  b.dontThrow = dontThrow; b.dontThrowSteps = dontThrowSteps; b.maxEvaluations = maxEvaluations;
  return b;
}

static QlYieldTermStructure *piecewiseYieldCurveImpl(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, const QlIterativeBootstrapOpts& b, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveAux(Date(date), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), trait, interpolator, approximator, approximatorArg, b));
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, char **e) {
  return piecewiseYieldCurveImpl(date, rateLen, ratehelpers, dayCount, quoteLen, quotes, datesLen, dates,
      trait, interpolator, approximator, approximatorArg, defaultBootstrapOpts(), e);
}

QlYieldTermStructure *qlPiecewiseYieldCurveFull(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg,
  double accuracy, double minValue, double maxValue, unsigned maxAttempts, double maxFactor, double minFactor, int dontThrow, unsigned dontThrowSteps, unsigned maxEvaluations, char **e) {
  return piecewiseYieldCurveImpl(date, rateLen, ratehelpers, dayCount, quoteLen, quotes, datesLen, dates,
      trait, interpolator, approximator, approximatorArg,
      bootstrapOpts(accuracy, minValue, maxValue, maxAttempts, maxFactor, minFactor, dontThrow, dontThrowSteps, maxEvaluations), e);
}

using curveBuilder = YieldTermStructure *(*)( const std::vector<Date>& dates, const std::vector<double>& dfs, const DayCounter& dayCount, const Calendar& cal,
  const std::vector<Handle<Quote> >& jumps, const std::vector<Date>& jumpDates, int interpolator, int approximator, int approximatorArg);

QlYieldTermStructure *qlInterpolatedCurve(curveBuilder builder, unsigned rateLen, double *rates, unsigned rateDatesLen, int *rateDates,
  DayCounter *dayCount, Calendar *cal, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e) {
  try {
    auto ts = allocShared(builder(qlDateVector(rateDates, rateDatesLen), std::vector<double>(rates, rates+rateLen), *arg(dayCount), *arg(cal),
        qlHandleVector(quotes, quoteLen), qlDateVector(dates, datesLen), interpolator, approximator, approximatorArg));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}
QlYieldTermStructure *qlInterpolatedDiscountCurve(unsigned dfsLen, double *dfs, unsigned dfdatesLen, int *dfsDates, DayCounter *dayCount, Calendar *cal,
  unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedDiscountCurveAux, dfsLen, dfs, dfdatesLen, dfsDates,
    dayCount, cal, quoteLen, quotes, datesLen, dates, interpolator, approximator, approximatorArg, extrapolate, e);
}
QlYieldTermStructure *qlInterpolatedForwardCurve(unsigned fwdLen, double *fwds, unsigned fwddatesLen, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedForwardCurveAux, fwdLen, fwds, fwddatesLen, fwdDates,
    dayCount, cal, quoteLen, quotes, datesLen, dates, interpolator, approximator, approximatorArg, /*extrapolate=*/0, e);
}
QlYieldTermStructure *qlInterpolatedZeroCurve(unsigned yieldLen, double *yields, unsigned ydatesLen, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  return qlInterpolatedCurve(&qlInterpolatedZeroCurveAux, yieldLen, yields, ydatesLen, yieldDates,
    dayCount, cal, quoteLen, quotes,  datesLen, dates, interpolator, approximator, approximatorArg, /*extrapolate=*/0, e);
}
static QlYieldTermStructure *piecewiseYieldCurve1Impl(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, const QlIterativeBootstrapOpts& b, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), trait, interpolator, approximator, approximatorArg, /*bootstrap=*/0, /*accuracy=*/0.0,
        std::vector<double>(), b));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e) {
  return piecewiseYieldCurve1Impl(settl, cal, rateLen, ratehelpers, dayCount, quoteLen, quotes, datesLen, dates,
      trait, interpolator, approximator, approximatorArg, defaultBootstrapOpts(), extrapolate, e);
}

QlYieldTermStructure *qlPiecewiseYieldCurveFull1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg,
  double accuracy, double minValue, double maxValue, unsigned maxAttempts, double maxFactor, double minFactor, int dontThrow, unsigned dontThrowSteps, unsigned maxEvaluations, int extrapolate, char **e) {
  return piecewiseYieldCurve1Impl(settl, cal, rateLen, ratehelpers, dayCount, quoteLen, quotes, datesLen, dates,
      trait, interpolator, approximator, approximatorArg,
      bootstrapOpts(accuracy, minValue, maxValue, maxAttempts, maxFactor, minFactor, dontThrow, dontThrowSteps, maxEvaluations), extrapolate, e);
}
QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), hasquant::Discount, hasquant::LogLinear, /*approximator=*/0, /*approximatorArg=*/0, /*bootstrap=*/1, accuracy,
        std::vector<double>(weights, weights + weightsLen), defaultBootstrapOpts()));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap2(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), hasquant::SimpleZeroYield, hasquant::Linear, /*approximator=*/0, /*approximatorArg=*/0, /*bootstrap=*/1, accuracy,
        std::vector<double>(weights, weights + weightsLen), defaultBootstrapOpts()));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap4(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), hasquant::ForwardRate, hasquant::Linear, /*approximator=*/0, /*approximatorArg=*/0, /*bootstrap=*/1, accuracy,
        std::vector<double>(weights, weights + weightsLen), defaultBootstrapOpts()));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap5(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), hasquant::ZeroYield, hasquant::Linear, /*approximator=*/0, /*approximatorArg=*/0, /*bootstrap=*/1, accuracy,
        std::vector<double>(weights, weights + weightsLen), defaultBootstrapOpts()));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurveLocalBootstrap1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, int trait, unsigned localisation, int forcePositive, double accuracy,
  double quadraticity, double monotonicity, int convexForcePositive, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveLocalBootstrapAux1(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), trait, localisation, forcePositive != 0, accuracy, quadraticity, monotonicity, convexForcePositive != 0));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap3(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
  QlQuote **quotes, unsigned datesLen, int *dates, unsigned additionalRateLen, QlRateHelper **additionalRatehelpers, unsigned additionalDatesLen, int *additionalDates,
  double accuracy, int extrapolate, char **e) {
  try {
    auto ts = allocShared(qlPiecewiseYieldCurveGlobalBootstrapFullAux(settl, *arg(cal), qlVector(ratehelpers, rateLen), *arg(dayCount), qlHandleVector(quotes, quoteLen),
        qlDateVector(dates, datesLen), qlVector(additionalRatehelpers, additionalRateLen), qlDateVector(additionalDates, additionalDatesLen), accuracy));
    if (extrapolate) ts->enableExtrapolation();
    return ret(new QlYieldTermStructure(ts));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure *>(e, er);}}

// MultiCurve builds a set of curves that form a genuine dependency cycle -- see the class's own
// doc comment in multicurve.hpp for the 4-step protocol this wraps. It is bound as a standalone
// leaf (see QlMultiCurve's alias comment in qlaux.h), not part of the TermStructure hierarchy.
QlMultiCurve *qlMultiCurve(double accuracy, char **e) {
  try {return ret(new QlMultiCurve(shared_ptr<MultiCurve>(alloc(new MultiCurve(accuracy)))));
  } catch (std::exception& er) {return handleException<QlMultiCurve*>(e, er);}}
void qlFreeMultiCurve(QlMultiCurve *o) {del(o);}

// curve's underlying shared_ptr is copied out of its Handle (currentLink()) and moved into
// addBootstrappedCurve/addNonBootstrappedCurve -- the caller's own QlYieldTermStructure* still
// owns/frees its Handle independently afterward. The Handle<YieldTermStructure> this returns is
// wrapped directly, never rebuilt from a shared_ptr (see the "no Handle<YieldTermStructure>("
// invariant in CLAUDE.md) -- this is a Handle the API itself handed back, not a fresh one.
QlYieldTermStructure *qlMultiCurveAddBootstrappedCurve(QlMultiCurve *mc, QlRelinkableYieldTermStructure *internalHandle, QlYieldTermStructure *curve, char **e) {
  try {
    shared_ptr<YieldTermStructure> sp = (*arg(curve)).currentLink();
    return ret(new QlYieldTermStructure((*arg(mc))->addBootstrappedCurve(*arg(internalHandle), std::move(sp))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure *qlMultiCurveAddNonBootstrappedCurve(QlMultiCurve *mc, QlRelinkableYieldTermStructure *internalHandle, QlYieldTermStructure *curve, char **e) {
  try {
    shared_ptr<YieldTermStructure> sp = (*arg(curve)).currentLink();
    return ret(new QlYieldTermStructure((*arg(mc))->addNonBootstrappedCurve(*arg(internalHandle), std::move(sp))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

// ql/experimental/termstructures/basisswapratehelpers.hpp -- rate-helper constructors only
// (impliedQuote/accept/setTermStructure/swap() are visitor-pattern/internal plumbing, matching
// the existing FraRateHelper/SwapRateHelper precedent of leaving those unbound).
QlRateHelper *qlIborIborBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned settlementDays, Calendar *calendar, int convention, int endOfMonth,
  QlIborIndex *baseIndex, QlIborIndex *otherIndex, QlYieldTermStructure *discountHandle, int bootstrapBaseCurve, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new IborIborBasisSwapRateHelper(*arg(basis), Period(tenorLen, (TimeUnit)tenorUnit), settlementDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth,
      *arg(baseIndex), *arg(otherIndex), *arg(discountHandle), bootstrapBaseCurve))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper *qlOvernightIborBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned settlementDays, Calendar *calendar, int convention, int endOfMonth,
  QlOvernightIndex *baseIndex, QlIborIndex *otherIndex, QlYieldTermStructure *discountHandle, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new OvernightIborBasisSwapRateHelper(*arg(basis), Period(tenorLen, (TimeUnit)tenorUnit), settlementDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth,
      *arg(baseIndex), *arg(otherIndex), qlNullableHandle(arg(discountHandle))))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}

// ql/experimental/termstructures/crosscurrencyratehelpers.hpp -- CrossCurrencySwapRateHelperBase
// and CrossCurrencyBasisSwapRateHelperBase are protected-constructor bases, not directly
// constructible, so only the three concrete leaf classes are bound here.
QlRateHelper *qlConstNotionalCrossCurrencyBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth,
  QlIborIndex *baseCurrencyIndex, QlIborIndex *quoteCurrencyIndex, QlYieldTermStructure *collateralCurve,
  int isFxBaseCurrencyCollateralCurrency, int isBasisOnFxBaseCurrencyLeg,
  int paymentFrequency, int paymentLag, int quoteCurrencyPaymentFrequency, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new ConstNotionalCrossCurrencyBasisSwapRateHelper(*arg(basis), Period(tenorLen, (TimeUnit)tenorUnit), fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth,
      *arg(baseCurrencyIndex), *arg(quoteCurrencyIndex), *arg(collateralCurve),
      isFxBaseCurrencyCollateralCurrency, isBasisOnFxBaseCurrencyLeg,
      paymentFrequency < 0 ? ext::optional<Frequency>() : ext::optional<Frequency>((Frequency)paymentFrequency),
      paymentLag,
      quoteCurrencyPaymentFrequency < 0 ? ext::optional<Frequency>() : ext::optional<Frequency>((Frequency)quoteCurrencyPaymentFrequency)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper *qlMtMCrossCurrencyBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth,
  QlIborIndex *baseCurrencyIndex, QlIborIndex *quoteCurrencyIndex, QlYieldTermStructure *collateralCurve,
  int isFxBaseCurrencyCollateralCurrency, int isBasisOnFxBaseCurrencyLeg, int isFxBaseCurrencyLegResettable,
  int paymentFrequency, int paymentLag, int quoteCurrencyPaymentFrequency, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new MtMCrossCurrencyBasisSwapRateHelper(*arg(basis), Period(tenorLen, (TimeUnit)tenorUnit), fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth,
      *arg(baseCurrencyIndex), *arg(quoteCurrencyIndex), *arg(collateralCurve),
      isFxBaseCurrencyCollateralCurrency, isBasisOnFxBaseCurrencyLeg, isFxBaseCurrencyLegResettable,
      paymentFrequency < 0 ? ext::optional<Frequency>() : ext::optional<Frequency>((Frequency)paymentFrequency),
      paymentLag,
      quoteCurrencyPaymentFrequency < 0 ? ext::optional<Frequency>() : ext::optional<Frequency>((Frequency)quoteCurrencyPaymentFrequency)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper *qlConstNotionalCrossCurrencySwapRateHelper(QlQuote *fixedRate, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth,
  int fixedFrequency, DayCounter *fixedDayCount, QlIborIndex *floatIndex, QlYieldTermStructure *collateralCurve, int collateralOnFixedLeg, int paymentLag, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new ConstNotionalCrossCurrencySwapRateHelper(*arg(fixedRate), Period(tenorLen, (TimeUnit)tenorUnit), fixingDays, *arg(calendar), (BusinessDayConvention)convention, endOfMonth,
      (Frequency)fixedFrequency, *arg(fixedDayCount), *arg(floatIndex), *arg(collateralCurve), collateralOnFixedLeg, paymentLag))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper *qlFxSwapRateHelper(QlQuote *fwdPoint, QlQuote *spotFx, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth,
  int isFxBaseCurrencyCollateralCurrency, QlYieldTermStructure *collateralCurve, Calendar *tradingCalendar, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FxSwapRateHelper(*arg(fwdPoint), *arg(spotFx), Period(tenorLen, (TimeUnit)tenorUnit), fixingDays, *arg(calendar), (BusinessDayConvention)convention,
      endOfMonth, isFxBaseCurrencyCollateralCurrency, *arg(collateralCurve), *arg(tradingCalendar)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper *qlFxSwapRateHelper2(QlQuote *fwdPoint, QlQuote *spotFx, int startDate, int endDate, int isFxBaseCurrencyCollateralCurrency, QlYieldTermStructure *collateralCurve, char **e) {
  try {
    return ret(new QlRateHelper(alloc(new FxSwapRateHelper(*arg(fwdPoint), *arg(spotFx), Date(startDate), Date(endDate), isFxBaseCurrencyCollateralCurrency, *arg(collateralCurve)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}

double qlYieldTSDiscount(QlYieldTermStructure *ts, int date, int extrapolate, char **e) {
  try {return (*ts)->discount(Date(date), extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSwapRateHelper *qlSwapRateHelper1(QlQuote *q, int l, int u, Calendar *cal, int freq,
  int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, int fl, int fu, QlYieldTermStructure *ts,
  unsigned settlementDays, int pillar, int customPillarDate, int endOfMonth, int useIndexedCoupons,
  int floatConvention, QlFloatingRateCouponPricer *couponPricer, char **e) {
  try {
    return ret(new QlSwapRateHelper(alloc(new SwapRateHelper(*arg(q),
	    Period(l, (TimeUnit)u), *arg(cal), (Frequency) freq, (BusinessDayConvention) conv, *arg(dc), *arg(i),
            qlNullableHandle(arg(s)),
            Period(fl, (TimeUnit)fu), qlNullableHandle(arg(ts)),
            settlementDays, (Pillar::Choice)pillar, qlNullableDate(customPillarDate), endOfMonth,
            qlOptBool(useIndexedCoupons),
            qlOptBusinessDayConvention(floatConvention),
            couponPricer ? *arg(couponPricer) : ext::shared_ptr<FloatingRateCouponPricer>()))));
  } catch (std::exception& er) {return handleException<QlSwapRateHelper *>(e, er);}}
QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new FlatForward(Date(referenceDate), *arg(forward), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e) {
try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new FlatForward(settlementDays, *arg(calendar), *arg(forward), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure* qlCompositeZeroYieldStructure(QlYieldTermStructure* curve1, QlYieldTermStructure* curve2, double (*fn)(double, double), int compounding, int frequency, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new CompositeZeroYieldStructure<double (*)(double, double)>(*arg(curve1), *arg(curve2), fn, (Compounding)compounding, (Frequency)frequency)))));
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
// Each shim below now binds the primary ctor overload (including the leading
// `optimizationMethod` param): OptimizationMethod is a shared_ptr box
// (QlOptimizationMethod, see qlLevenbergMarquardt/qlSimplex) rather than a raw
// Haskell-finalized pointer, so `method ? *arg(method) : shared_ptr<...>()`
// safely copies a shared reference into FittingMethod's own shared_ptr member
// -- correct even though FittedBondDiscountCurve additionally clones its
// fitting method, since cloning just copies that member (bumping the
// refcount), and correct regardless of when Haskell's own box is collected,
// since the object is only actually freed once every shared_ptr referencing
// it (Haskell's box included) has gone away.
// allocAs<FittedBondDiscountCurveFittingMethod> (not a bare alloc()) in each ctor below: see
// allocAs's doc comment in qlaux.h -- alloc() alone would trace each of these under its own
// leaf type (CubicBSplinesFitting, ...) rather than the base type qlFreeFittedBondDiscount-
// CurveFittingMethod's del() traces the matching free under.
FittedBondDiscountCurveFittingMethod* qlCubicBSplinesFitting(unsigned knotVectorLen, double *knotVector, int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e) {
  try {return allocAs<FittedBondDiscountCurveFittingMethod>(new CubicBSplinesFitting(std::vector<double>(knotVector, knotVector+knotVectorLen), constrainAtZero, Array(weights, weights+weightsLen), method ? *arg(method) : shared_ptr<OptimizationMethod>(), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlExponentialSplinesFitting(int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, unsigned numCoeffs, double fixedKappa, QlOptimizationMethod* method, Constraint* constraint, char **e) {
  try {return allocAs<FittedBondDiscountCurveFittingMethod>(new ExponentialSplinesFitting(constrainAtZero, Array(weights, weights+weightsLen), method ? *arg(method) : shared_ptr<OptimizationMethod>(), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, numCoeffs, fixedKappa, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlNelsonSiegelFitting(unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e) {
  try {return allocAs<FittedBondDiscountCurveFittingMethod>(new NelsonSiegelFitting(Array(weights, weights+weightsLen), method ? *arg(method) : shared_ptr<OptimizationMethod>(), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e) {
  try {return allocAs<FittedBondDiscountCurveFittingMethod>(new SimplePolynomialFitting(degree, constrainAtZero, Array(weights, weights+weightsLen), method ? *arg(method) : shared_ptr<OptimizationMethod>(), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
  } catch (std::exception& er) {return handleException<FittedBondDiscountCurveFittingMethod*>(e, er);}}
FittedBondDiscountCurveFittingMethod* qlSvenssonFitting(unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e) {
  try {return allocAs<FittedBondDiscountCurveFittingMethod>(new SvenssonFitting(Array(weights, weights+weightsLen), method ? *arg(method) : shared_ptr<OptimizationMethod>(), Array(l2, l2+l2Len), minCutoffTime, maxCutoffTime, constraint ? *arg(constraint) : Constraint(NoConstraint())));
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
QlRateHelper* qlOvernightIndexFutureRateHelper(QlQuote* price, int valueDate, int maturityDate, QlOvernightIndex* overnightIndex, QlQuote* convexityAdjustment, int averagingMethod, int pillar, int customPillarDate, char **e) {
  try {return ret(new QlRateHelper(alloc(new OvernightIndexFutureRateHelper(*arg(price), Date(valueDate), Date(maturityDate),
      *arg(overnightIndex), qlNullableHandle(arg(convexityAdjustment)), (RateAveraging::Type)averagingMethod,
      (Pillar::Choice)pillar, qlNullableDate(customPillarDate)))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}
QlRateHelper* qlSofrFutureRateHelper(QlQuote* price, int month, int year, int freq, QlQuote* convexityAdjustment, int pillar, int customPillarDate, char **e) {
  try {return ret(new QlRateHelper(alloc(new SofrFutureRateHelper(
      std::variant<Rate, Handle<Quote>>(*arg(price)), (Month)month, year, (Frequency)freq,
      convexityAdjustment ? std::variant<Rate, Handle<Quote>>(*arg(convexityAdjustment)) : std::variant<Rate, Handle<Quote>>(Rate(0.0)),
      (Pillar::Choice)pillar, qlNullableDate(customPillarDate)))));
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

QlYieldTermStructure* qlPiecewiseZeroSpreadedTermStructure(QlYieldTermStructure* x0, unsigned spreadsLen, QlQuote** spreads, unsigned datesLen, int* dates, int comp, int freq, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    YieldTermStructure *ts = qlPiecewiseZeroSpreadedTermStructureAux(qlNullableHandle(arg(x0)), qlHandleVector(spreads, spreadsLen), qlDateVector(dates, datesLen), (Compounding)comp, (Frequency)freq, interpolator, approximator, approximatorArg);
    return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(ts))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}
QlYieldTermStructure* qlQuantoTermStructure(QlYieldTermStructure* underlyingDividendTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* foreignRiskFreeTS, QlBlackVolTermStructure* underlyingBlackVolTS, double strike, QlBlackVolTermStructure* exchRateBlackVolTS, double exchRateATMlevel, double underlyingExchRateCorrelation, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new QuantoTermStructure(*arg(underlyingDividendTS), *arg(riskFreeTS), *arg(foreignRiskFreeTS), *arg(underlyingBlackVolTS), strike, *arg(exchRateBlackVolTS), exchRateATMlevel, underlyingExchRateCorrelation)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

QlYieldTermStructure* qlUltimateForwardTermStructure(QlYieldTermStructure* x0, QlQuote* lastLiquidForwardRate, QlQuote* ultimateForwardRate, int fspLen, int fspUnit, double alpha, int roundingDigits, int compounding, int frequency, char **e) {
  try {return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(new UltimateForwardTermStructure(*arg(x0), *arg(lastLiquidForwardRate), *arg(ultimateForwardRate), Period(fspLen, (TimeUnit)fspUnit), alpha,
      roundingDigits == Null<Integer>() ? ext::optional<Integer>() : ext::optional<Integer>(roundingDigits), (Compounding)compounding, (Frequency)frequency)))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

QlYieldTermStructure* qlInterpolatedSpreadDiscountCurve(QlYieldTermStructure* baseCurve, unsigned dfsLen, double *dfs, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    YieldTermStructure *ts = qlInterpolatedSpreadDiscountCurveAux(qlNullableHandle(arg(baseCurve)), qlDateVector(dates, datesLen), std::vector<double>(dfs, dfs+dfsLen), interpolator, approximator, approximatorArg);
    return ret(new QlYieldTermStructure(shared_ptr<YieldTermStructure>(alloc(ts))));
  } catch (std::exception& er) {return handleException<QlYieldTermStructure*>(e, er);}}

QlRateHelper* qlMultipleResetsSwapRateHelper(unsigned settlementDays, int tenorLen, int tenorUnit, QlQuote* fixedRate, QlIborIndex* iborIndex, unsigned resetsPerCoupon, QlYieldTermStructure* discountingCurve, int averagingMethod, double spread, int fixedFrequency, DayCounter* fixedDayCount, int fixedConvention, char **e) {
  try {return ret(new QlRateHelper(alloc(new MultipleResetsSwapRateHelper(settlementDays, Period(tenorLen, (TimeUnit)tenorUnit), *arg(fixedRate), *arg(iborIndex), resetsPerCoupon,
      qlNullableHandle(arg(discountingCurve)), (RateAveraging::Type)averagingMethod, spread, (Frequency)fixedFrequency, *arg(fixedDayCount), (BusinessDayConvention)fixedConvention))));
  } catch (std::exception& er) {return handleException<QlRateHelper*>(e, er);}}

void qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e) {try {(*arg(i))->addFixing(Date(date), fix, overwrite);} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
double qlIndexFixing(QlIndex *i, int date, int forecastTodaysFixing, char **e) {try {return (*arg(i))->fixing(Date(date), forecastTodaysFixing);} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlIndexHasHistoricalFixing(QlIndex *i, int date, char **e) {try {return (*arg(i))->hasHistoricalFixing(Date(date));} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlIndexIsValidFixingDate(QlIndex *i, int date, char **e) {try {return (*arg(i))->isValidFixingDate(Date(date));} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlIndexAddFixings(QlIndex *i, unsigned datesLen, int *dates, double *values, int overwrite, char **e) {
  try {std::vector<Date> ds = qlDateVector(dates, datesLen);(*arg(i))->addFixings(ds.begin(), ds.end(), values, overwrite);
  } catch (std::exception& er) {(void)handleException<void *>(e, er);}}
void qlIndexClearFixings(QlIndex *i, char **e) {try {(*arg(i))->clearFixings();} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
void qlIndexFixingHistory(QlIndex *i, unsigned *datesLen, int **dates, unsigned *valuesLen, double **values, char **e) {
  int *ds = 0;
  double *vs = 0;
  *datesLen = 0; *dates = 0; *valuesLen = 0; *values = 0;
  try {
    const std::string& name = (*arg(i))->name();
    const std::vector<std::string> names = IndexManager::instance().histories();
    if (std::none_of(names.begin(), names.end(), [&](const std::string& candidate) {
          return sameIndexName(candidate, name);
        }))
      return;
    const TimeSeries<Real>& history = (*arg(i))->timeSeries();
    const std::vector<Date> historyDates = history.dates();
    const std::vector<Real> historyValues = history.values();
    ds = qlAllocateInts(historyDates.size());
    vs = qlAllocateDoubles(historyValues.size());
    for (unsigned n = 0; n < historyDates.size(); ++n) ds[n] = historyDates[n].serialNumber();
    for (unsigned n = 0; n < historyValues.size(); ++n) vs[n] = historyValues[n];
    *datesLen = historyDates.size(); *dates = ds;
    *valuesLen = historyValues.size(); *values = vs;
  } catch (std::exception& er) {
    qlFreeInts(ds); qlFreeDoubles(vs); *e = tracedup(er.what());
  }}
void qlIndexManagerHistories(unsigned *count, char ***names, char **e) {
  char **ns = 0;
  unsigned n = 0;
  *count = 0; *names = 0;
  try {
    const std::vector<std::string> histories = IndexManager::instance().histories();
    ns = ret(new char*[histories.size()]());
    for (; n < histories.size(); ++n) ns[n] = tracedup(histories[n].c_str());
    *count = histories.size(); *names = ns;
  } catch (std::exception& er) {
    qlFreeStringArray(n, ns); *e = tracedup(er.what());
  }}
void qlIndexManagerClearHistories(char **e) {
  try {IndexManager::instance().clearHistories();}
  catch (std::exception& er) {*e = tracedup(er.what());}}
// must match with the order of qlEnumObjects.h:LiborSwapIndexType
static const makeSwapIdx swapIndices[] = {
    &makeSwapIndex<ChfLiborSwapIsdaFix>
  , &makeSwapIndex<EurLiborSwapIfrFix>
  , &makeSwapIndex<EurLiborSwapIsdaFixA>
  , &makeSwapIndex<EurLiborSwapIsdaFixB>
  , &makeSwapIndex<EuriborSwapIfrFix>
  , &makeSwapIndex<EuriborSwapIsdaFixA>
  , &makeSwapIndex<EuriborSwapIsdaFixB>
  , &makeSwapIndex<GbpLiborSwapIsdaFix>
  , &makeSwapIndex<JpyLiborSwapIsdaFixAm>
  , &makeSwapIndex<JpyLiborSwapIsdaFixPm>
  , &makeSwapIndex<UsdLiborSwapIsdaFixAm>
  , &makeSwapIndex<UsdLiborSwapIsdaFixPm>
};

QlSwapIndex* qlCreateLiborSwapIndex(int index, int l, int u, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e) {
  try {
    if (index < 0 || index >= (int)std::size(swapIndices))
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

const char* qlIndexName(QlIndex *index) {std::string name = (*arg(index))->name(); return tracedup(name.c_str());}
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
QlIborIndex *qlCustomIborIndex(char *name, int l, int u, unsigned settlDays,
    Currency *ccy, Calendar *fixingCal, Calendar *valueCal, Calendar *maturityCal,
    int conv, int eom, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlIborIndex(alloc(new CustomIborIndex(name, Period(l, (TimeUnit)u),
      settlDays, *arg(ccy), *arg(fixingCal), *arg(valueCal), *arg(maturityCal),
      (BusinessDayConvention) conv, eom, *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {return handleException<QlIborIndex *>(e, er);}}
QlOvernightIndex *qlOvernightIndex(char *name, unsigned settlDays, Currency *ccy,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e) {
  try {return ret(new QlOvernightIndex(alloc(new OvernightIndex(name, settlDays,
            *arg(ccy), *arg(cal), *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {return handleException<QlOvernightIndex *>(e, er);}}

// must match the order of qlEnumObjects.h:IborIndexType (Standard block), then
// IborDailyTenorIndexType (DailyTenor block), then IborONIndexType (Overnight block) --
// see deriveIborConstructor in QuantLib/Internal/Syntax.hs for how the three Haskell-side
// enums are stitched back into a single flat offset into this array.
static const makeIborIdx iborIndices[] = {
    // -- Standard block (IborIndexType) --
    &makeIborIndex<Bbsw>
  , &makeIborIndex<Bibor>
  , &makeIborIndex<Bkbm>
  , &makeIborIndex<Cdor>
  , &makeIborIndex<EURLibor>
  , &makeIborIndex<AUDLibor>
  , &makeIborIndex<CADLibor>
  , &makeIborIndex<CHFLibor>
  , &makeIborIndex<DKKLibor>
  , &makeIborIndex<GBPLibor>
  , &makeIborIndex<JPYLibor>
  , &makeIborIndex<NZDLibor>
  , &makeIborIndex<SEKLibor>
  , &makeIborIndex<USDLibor>
  , &makeIborIndex<Euribor>
  , &makeIborIndex<Euribor365>
  , &makeIborIndex<Jibar>
  , &makeIborIndex<Mosprime>
  , &makeIborIndex<Pribor>
  , &makeIborIndex<Robor>
  , &makeIborIndex<Shibor>
  , &makeIborIndex<THBFIX>
  , &makeIborIndex<TRLibor>
  , &makeIborIndex<Tibor>
  , &makeIborIndex<Wibor>
  , &makeIborIndex<Zibor>
  , &makeIborIndex<Nibor>
    // -- DailyTenor block (IborDailyTenorIndexType) --
  , &makeIborIndexMonths<DailyTenorEURLibor>
  , &makeIborIndexMonths<DailyTenorCHFLibor>
  , &makeIborIndexMonths<DailyTenorGBPLibor>
  , &makeIborIndexMonths<DailyTenorJPYLibor>
  , &makeIborIndexMonths<DailyTenorUSDLibor>
    // -- Overnight block (IborONIndexType) --
  , &makeIborIndexTS<CADLiborON>
  , &makeIborIndexTS<EURLiborON>
  , &makeIborIndexTS<GBPLiborON>
  , &makeIborIndexTS<USDLiborON>
};

QlIborIndex *qlCreateIbor(int index, int l, int u, QlYieldTermStructure *fwd, char **e) {
  try {
    if (index < 0 || index >= (int)std::size(iborIndices))
      QL_FAIL("Invalid IBOR index index: " << index);
    QlYieldTermStructure ts = qlNullableHandle(fwd);
    IborIndex *i = iborIndices[index](l, u, ts);
    return ret(new QlIborIndex(alloc(i)));
  } catch (std::exception& er) {return handleException<QlIborIndex *>(e, er);}}

// should match the order of qlEnumObjects.h:OvernightIborIndexType
static const makeOnIdx onIndices[] = {
    &makeONIndex<Aonia>
  , &makeONIndex<Eonia>
  , &makeONIndex<Estr>
  , &makeONIndex<FedFunds>
  , &makeONIndex<Nzocr>
  , &makeONIndex<Sofr>
  , &makeONIndex<Sonia>
  , &makeONIndex<Cdi>
  , &makeONIndex<Corra>
  , &makeONIndex<Kofr>
  , &makeONIndex<Destr>
  , &makeONIndex<Swestr>
  , &makeONIndex<Shir>
  , &makeONIndex<Tonar>
  , &makeONIndex<Saron>
  , &makeONIndex<Zaronia>
};

QlOvernightIndex *qlCreateONIndex(int index, QlYieldTermStructure *fwd, char **e) {
  try {
    if (index < 0 || index >= (int)std::size(onIndices))
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
// currency()/equityInterestRateCurve()/equityDividendCurve()/spot() are all plain,
// never-mutated echoes of the constructor's own arguments (equityindex.hpp's inline getters
// each just `return foo_;`) -- not bound, per CLAUDE.md's trivial-getter rule.

// must match the order of qlEnumObjects.h:ZeroInflationIndexType
static const makeZeroInflIdx zeroInflationIndices[] = {
    []{return static_cast<ZeroInflationIndex *>(new AUCPI(Quarterly, false));} // AU CPI is published quarterly, unlike the other (monthly) named indices
  , &makeZeroInflationIndex<EUHICP>
  , &makeZeroInflationIndex<EUHICPXT>
  , &makeZeroInflationIndex<FRHICP>
  , &makeZeroInflationIndex<UKHICP>
  , &makeZeroInflationIndex<UKRPI>
  , &makeZeroInflationIndex<USCPI>
  , &makeZeroInflationIndex<ZACPI>
};

QlZeroInflationIndex *qlCreateZeroInflationIndex(int index, char **e) {
  try {
    if (index < 0 || index >= (int)std::size(zeroInflationIndices))
      QL_FAIL("Invalid zero inflation index index" << index);
    return ret(new QlZeroInflationIndex(alloc(zeroInflationIndices[index]())));
  } catch (std::exception& er) {return handleException<QlZeroInflationIndex *>(e, er);}}

// must match the order of qlEnumObjects.h:YoYInflationIndexType
static const makeYoYInflIdx yoyInflationIndices[] = {
    []{return static_cast<YoYInflationIndex *>(new YYAUCPI(Quarterly, false));}
  , &makeYoYInflationIndex<YYEUHICP>
  , &makeYoYInflationIndex<YYEUHICPXT>
  , &makeYoYInflationIndex<YYFRHICP>
  , &makeYoYInflationIndex<YYUKRPI>
  , &makeYoYInflationIndex<YYUSCPI>
  , &makeYoYInflationIndex<YYZACPI>
};

QlYoYInflationIndex *qlCreateYoYInflationIndex(int index, char **e) {
  try {
    if (index < 0 || index >= (int)std::size(yoyInflationIndices))
      QL_FAIL("Invalid year-on-year inflation index index" << index);
    return ret(new QlYoYInflationIndex(alloc(yoyInflationIndices[index]())));
  } catch (std::exception& er) {return handleException<QlYoYInflationIndex *>(e, er);}}

// must match the order of qlEnumObjects.h:RegionType
static const makeReg regions[] = {
    &makeRegion<AustraliaRegion>
  , &makeRegion<EURegion>
  , &makeRegion<FranceRegion>
  , &makeRegion<UKRegion>
  , &makeRegion<USRegion>
  , &makeRegion<ZARegion>
};
Region *qlRegion(int r, char **e) {
  try {
    if (r < 0 || r >= (int)std::size(regions)) QL_FAIL("Invalid region index " << r);
    return alloc(regions[r]());
  } catch (std::exception& er) {return handleException<Region*>(e, er);}}
Region *qlCreateRegion(char* name, char* code, char **e) {
  try {return allocAs<Region>(new CustomRegion(arg(name), arg(code)));
  } catch (std::exception& er) {return handleException<Region*>(e, er);}}
void qlFreeRegion(Region *o) {del(o);}
const char *qlRegionName(Region *o) {return tracedup(arg(o)->name().c_str());}

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

/* YoYOptionletVolatilitySurface */

QlYoYOptionletVolatilitySurface *qlConstantYoYOptionletVolatility(QlQuote *v, unsigned settlementDays,
    Calendar *cal, int bdc, DayCounter *dc, int observationLagLen, int observationLagUnit, int frequency,
    int indexIsInterpolated, double minStrike, double maxStrike, int volType, double displacement, char **e) {
  try {return ret(new QlYoYOptionletVolatilitySurface(Handle<YoYOptionletVolatilitySurface>(
      shared_ptr<YoYOptionletVolatilitySurface>(alloc(new ConstantYoYOptionletVolatility(*arg(v), settlementDays, *arg(cal), (BusinessDayConvention)bdc,
        *arg(dc), Period(observationLagLen, (TimeUnit)observationLagUnit), (Frequency)frequency,
        (bool)indexIsInterpolated, minStrike, maxStrike, (VolatilityType)volType, displacement))))));
  } catch (std::exception& er) {return handleException<QlYoYOptionletVolatilitySurface*>(e, er);}}

void qlFreeYoYOptionletVolatilitySurface(QlYoYOptionletVolatilitySurface *p) {del(p);}

// Deliberate snapshot detach, same reasoning as qlOptionletVolatilityStructureAsVolatilityTermStructure.
QlVolatilityTermStructure *qlYoYOptionletVolatilitySurfaceAsVolatilityTermStructure(QlYoYOptionletVolatilitySurface *o) {
  return ret(new QlVolatilityTermStructure(handlePtr(arg(o))));}

// obsLagUnit < 0 is the "use my own observationLag" sentinel, matching the C++ default
// Period(-1, Days) -- same convention as qlOptionletStripper1's optionletFrequency.
double qlYoYOptionletVolatilitySurfaceVolatility(QlYoYOptionletVolatilitySurface *o, int maturityDate,
    double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e) {
  try {return handleRef(arg(o)).volatility(Date(maturityDate), strike,
      obsLagUnit < 0 ? Period(-1, Days) : Period(obsLagLen, (TimeUnit)obsLagUnit), (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlYoYOptionletVolatilitySurfaceTotalVariance(QlYoYOptionletVolatilitySurface *o, int exerciseDate,
    double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e) {
  try {return handleRef(arg(o)).totalVariance(Date(exerciseDate), strike,
      obsLagUnit < 0 ? Period(-1, Days) : Period(obsLagLen, (TimeUnit)obsLagUnit), (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

/* YoY inflation cap/floor pricing engines */

QlPricingEngine *qlYoYInflationBlackCapFloorEngine(QlYoYInflationIndex *index, QlYoYOptionletVolatilitySurface *vol,
    QlYieldTermStructure *nominalTs, char **e) {
  try {return ret(new QlPricingEngine(alloc(new YoYInflationBlackCapFloorEngine(*arg(index), *arg(vol), *arg(nominalTs)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

QlPricingEngine *qlYoYInflationUnitDisplacedBlackCapFloorEngine(QlYoYInflationIndex *index,
    QlYoYOptionletVolatilitySurface *vol, QlYieldTermStructure *nominalTs, char **e) {
  try {return ret(new QlPricingEngine(alloc(new YoYInflationUnitDisplacedBlackCapFloorEngine(*arg(index), *arg(vol), *arg(nominalTs)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

QlPricingEngine *qlYoYInflationBachelierCapFloorEngine(QlYoYInflationIndex *index, QlYoYOptionletVolatilitySurface *vol,
    QlYieldTermStructure *nominalTs, char **e) {
  try {return ret(new QlPricingEngine(alloc(new YoYInflationBachelierCapFloorEngine(*arg(index), *arg(vol), *arg(nominalTs)))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

/* CPICapFloorTermPriceSurface */

void qlFreeCPICapFloorTermPriceSurface(QlCPICapFloorTermPriceSurface *o) {del(o);}
QlTermStructure *qlCPICapFloorTermPriceSurfaceAsTermStructure(QlCPICapFloorTermPriceSurface *o) {
  return ret(new QlTermStructure(*arg(o)));}

QlCPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurface(double nominal, double baseRate,
    int observationLagLen, int observationLagUnit, Calendar *cal, int bdc, DayCounter *dc,
    QlZeroInflationIndex *zii, int interpolationType, QlYieldTermStructure *yts,
    unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
    unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
    unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
    unsigned fPriceRows, unsigned fPriceCols, double *fPriceData,
    int interpolator2D, char **e) {
  try {
    const Period observationLag(observationLagLen, (TimeUnit)observationLagUnit);
    const std::vector<Rate> cStrikesVec(cStrikes, cStrikes+cStrikesLen);
    const std::vector<Rate> fStrikesVec(fStrikes, fStrikes+fStrikesLen);
    const std::vector<Period> cfMaturitiesVec = qlPeriodVector(cfMaturitiesNum, cfMaturitiesUnit, cfMaturitiesLen);
    const Matrix cPriceMat = qlMatrix(cPriceData, cPriceRows, cPriceCols);
    const Matrix fPriceMat = qlMatrix(fPriceData, fPriceRows, fPriceCols);
    CPICapFloorTermPriceSurface *s = qlCPICapFloorTermPriceSurfaceAux(nominal, baseRate, observationLag, *arg(cal),
        (BusinessDayConvention)bdc, *arg(dc), *arg(zii), (CPI::InterpolationType)interpolationType, *arg(yts),
        cStrikesVec, fStrikesVec, cfMaturitiesVec, cPriceMat, fPriceMat, interpolator2D);
    return ret(new QlCPICapFloorTermPriceSurface(alloc(s)));
  } catch (std::exception& er) {return handleException<QlCPICapFloorTermPriceSurface*>(e, er);}}

/* InterpolatingCPICapFloorEngine -- the only CPICapFloor engine in QL 1.43 */

QlPricingEngine *qlInterpolatingCPICapFloorEngine(QlCPICapFloorTermPriceSurface *surface, char **e) {
  try {return ret(new QlPricingEngine(alloc(new InterpolatingCPICapFloorEngine(Handle<CPICapFloorTermPriceSurface>(*arg(surface))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

/* CPIVolatilitySurface -- no consumer (engine/pricer) in QL 1.43, see qlaux.h/Internal.Type's own
   note; this type stands alone as a queryable surface. */

QlCPIVolatilitySurface *qlConstantCPIVolatility(QlQuote *v, unsigned settlementDays, Calendar *cal,
    int bdc, DayCounter *dc, int observationLagLen, int observationLagUnit, int frequency,
    int indexIsInterpolated, char **e) {
  try {return ret(new QlCPIVolatilitySurface(Handle<CPIVolatilitySurface>(
      shared_ptr<CPIVolatilitySurface>(alloc(new ConstantCPIVolatility(*arg(v), settlementDays, *arg(cal), (BusinessDayConvention)bdc,
        *arg(dc), Period(observationLagLen, (TimeUnit)observationLagUnit), (Frequency)frequency,
        (bool)indexIsInterpolated))))));
  } catch (std::exception& er) {return handleException<QlCPIVolatilitySurface*>(e, er);}}

void qlFreeCPIVolatilitySurface(QlCPIVolatilitySurface *p) {del(p);}

// Deliberate snapshot detach, same reasoning as qlYoYOptionletVolatilitySurfaceAsVolatilityTermStructure.
QlVolatilityTermStructure *qlCPIVolatilitySurfaceAsVolatilityTermStructure(QlCPIVolatilitySurface *o) {
  return ret(new QlVolatilityTermStructure(handlePtr(arg(o))));}

double qlCPIVolatilitySurfaceVolatility(QlCPIVolatilitySurface *o, int maturityDate,
    double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e) {
  try {return handleRef(arg(o)).volatility(Date(maturityDate), strike,
      obsLagUnit < 0 ? Period(-1, Days) : Period(obsLagLen, (TimeUnit)obsLagUnit), (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlCPIVolatilitySurfaceTotalVariance(QlCPIVolatilitySurface *o, int exerciseDate,
    double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e) {
  try {return handleRef(arg(o)).totalVariance(Date(exerciseDate), strike,
      obsLagUnit < 0 ? Period(-1, Days) : Period(obsLagLen, (TimeUnit)obsLagUnit), (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

/* YoYCapFloorTermPriceSurface */

void qlFreeYoYCapFloorTermPriceSurface(QlYoYCapFloorTermPriceSurface *o) {del(o);}
QlTermStructure *qlYoYCapFloorTermPriceSurfaceAsTermStructure(QlYoYCapFloorTermPriceSurface *o) {
  return ret(new QlTermStructure(*arg(o)));}

QlYoYCapFloorTermPriceSurface *qlYoYCapFloorTermPriceSurface(unsigned fixingDays,
    int yyLagLen, int yyLagUnit, QlYoYInflationIndex *yii, int interpolationType,
    QlYieldTermStructure *nominal, DayCounter *dc, Calendar *cal, int bdc,
    unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
    unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
    unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
    unsigned fPriceRows, unsigned fPriceCols, double *fPriceData,
    int interpolator2D, int interpolator1D, int approximator, int approximatorArg, char **e) {
  try {
    const Period yyLag(yyLagLen, (TimeUnit)yyLagUnit);
    const shared_ptr<YoYInflationIndex>& yiiRef = *arg(yii);
    const Handle<YieldTermStructure>& nominalRef = *arg(nominal);
    const std::vector<Rate> cStrikesVec(cStrikes, cStrikes+cStrikesLen);
    const std::vector<Rate> fStrikesVec(fStrikes, fStrikes+fStrikesLen);
    const std::vector<Period> cfMaturitiesVec = qlPeriodVector(cfMaturitiesNum, cfMaturitiesUnit, cfMaturitiesLen);
    const Matrix cPriceMat = qlMatrix(cPriceData, cPriceRows, cPriceCols);
    const Matrix fPriceMat = qlMatrix(fPriceData, fPriceRows, fPriceCols);
    YoYCapFloorTermPriceSurface *s = qlYoYCapFloorTermPriceSurfaceAux(fixingDays, yyLag, yiiRef,
        (CPI::InterpolationType)interpolationType, nominalRef, *arg(dc), *arg(cal), (BusinessDayConvention)bdc,
        cStrikesVec, fStrikesVec, cfMaturitiesVec, cPriceMat, fPriceMat,
        interpolator2D, interpolator1D, approximator, approximatorArg);
    return ret(new QlYoYCapFloorTermPriceSurface(alloc(s)));
  } catch (std::exception& er) {return handleException<QlYoYCapFloorTermPriceSurface*>(e, er);}}

int qlYoYCapFloorTermPriceSurfaceBaseDate(QlYoYCapFloorTermPriceSurface *o, char **e) {
  try {return qlNullableDate((*arg(o))->baseDate());
  } catch (std::exception& er) {return handleException<int>(e, er);}}

void qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates(QlYoYCapFloorTermPriceSurface *o,
    unsigned *dl, int **date, unsigned *rl, double **rate, char **e) {
  *dl = 0; *rl = 0; *date = nullptr; *rate = nullptr;
  int *dates = nullptr;
  double *rates = nullptr;
  try {
    const auto &dr = (*arg(o))->atmYoYSwapDateRates();
    dates = qlAllocateInts(dr.first.size()); rates = qlAllocateDoubles(dr.second.size());
    for (unsigned i = 0; i < dr.first.size(); ++i) dates[i] = dr.first[i].serialNumber();
    for (unsigned i = 0; i < dr.second.size(); ++i) rates[i] = dr.second[i];
    *dl = dr.first.size(); *rl = dr.second.size(); *date = dates; *rate = rates;
  } catch (const std::exception& er) {
    qlFreeInts(dates); qlFreeDoubles(rates); *e = tracedup(er.what());
  }
}

double qlYoYCapFloorTermPriceSurfaceAtmYoYSwapRate(QlYoYCapFloorTermPriceSurface *o, int d,
    int extrapolate, char **e) {
  try {return (*arg(o))->atmYoYSwapRate(Date(d), (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlYoYCapFloorTermPriceSurfaceAtmYoYRate(QlYoYCapFloorTermPriceSurface *o, int d,
    int obsLagLen, int obsLagUnit, int extrapolate, char **e) {
  try {return (*arg(o))->atmYoYRate(Date(d),
      obsLagUnit < 0 ? Period(-1, Days) : Period(obsLagLen, (TimeUnit)obsLagUnit), (bool)extrapolate);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

void qlYoYCapFloorTermPriceSurfaceStrikes(QlYoYCapFloorTermPriceSurface *o, unsigned *sl, double **strike, char **e) {
  *sl = 0; *strike = nullptr;
  double *out = nullptr;
  try {
    const std::vector<Rate> &ks = (*arg(o))->strikes();
    out = qlAllocateDoubles(ks.size());
    for (unsigned i = 0; i < ks.size(); ++i) out[i] = ks[i];
    *sl = ks.size(); *strike = out;
  } catch (const std::exception& er) {qlFreeDoubles(out); *e = tracedup(er.what());}
}

/* KInterpolatedYoYOptionletVolatilitySurface */

QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBlack(
    unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
    QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
    QlYieldTermStructure *nominalTs, double slope,
    int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    shared_ptr<YoYInflationCapFloorEngine> engine(new YoYInflationBlackCapFloorEngine(
        *arg(index), qlNullYoYOptionletVolatilitySurfaceHandle(), *arg(nominalTs)));
    YoYOptionletVolatilitySurface *s = qlKInterpolatedYoYOptionletVolatilitySurfaceAux(
        settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(dc), *arg(capFloorPrices), engine, slope,
        interpolator, approximator, approximatorArg);
    return ret(new QlYoYOptionletVolatilitySurface(Handle<YoYOptionletVolatilitySurface>(shared_ptr<YoYOptionletVolatilitySurface>(alloc(s)))));
  } catch (std::exception& er) {return handleException<QlYoYOptionletVolatilitySurface*>(e, er);}}

QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack(
    unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
    QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
    QlYieldTermStructure *nominalTs, double slope,
    int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    shared_ptr<YoYInflationCapFloorEngine> engine(new YoYInflationUnitDisplacedBlackCapFloorEngine(
        *arg(index), qlNullYoYOptionletVolatilitySurfaceHandle(), *arg(nominalTs)));
    YoYOptionletVolatilitySurface *s = qlKInterpolatedYoYOptionletVolatilitySurfaceAux(
        settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(dc), *arg(capFloorPrices), engine, slope,
        interpolator, approximator, approximatorArg);
    return ret(new QlYoYOptionletVolatilitySurface(Handle<YoYOptionletVolatilitySurface>(shared_ptr<YoYOptionletVolatilitySurface>(alloc(s)))));
  } catch (std::exception& er) {return handleException<QlYoYOptionletVolatilitySurface*>(e, er);}}

QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBachelier(
    unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
    QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
    QlYieldTermStructure *nominalTs, double slope,
    int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    shared_ptr<YoYInflationCapFloorEngine> engine(new YoYInflationBachelierCapFloorEngine(
        *arg(index), qlNullYoYOptionletVolatilitySurfaceHandle(), *arg(nominalTs)));
    YoYOptionletVolatilitySurface *s = qlKInterpolatedYoYOptionletVolatilitySurfaceAux(
        settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(dc), *arg(capFloorPrices), engine, slope,
        interpolator, approximator, approximatorArg);
    return ret(new QlYoYOptionletVolatilitySurface(Handle<YoYOptionletVolatilitySurface>(shared_ptr<YoYOptionletVolatilitySurface>(alloc(s)))));
  } catch (std::exception& er) {return handleException<QlYoYOptionletVolatilitySurface*>(e, er);}}
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
