#include <ql/termstructures/volatility/inflation/yoyinflationoptionletvolatilitystructure.hpp>
#include <ql/pricingengines/inflation/inflationcapfloorengines.hpp>
#include <ql/experimental/inflation/cpicapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/cpicapfloorengines.hpp>
#include <ql/termstructures/volatility/inflation/constantcpivolatility.hpp>
#include <ql/experimental/inflation/yoycapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/interpolatedyoyoptionletstripper.hpp>
#include <ql/experimental/inflation/kinterpolatedyoyoptionletvolatilitysurface.hpp>
#include <ql/math/interpolations/all.hpp>
#include "qlaux.h"
using namespace QuantLib;
namespace hasquant {
#include "qlEnumObjects.h"
}
#include "qlInflationVol.h"

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

template <class I2D>
static CPICapFloorTermPriceSurface *makeCPICapFloorTermPriceSurface(
    double nominal, double baseRate, const Period &observationLag, const Calendar &cal,
    BusinessDayConvention bdc, const DayCounter &dc, const shared_ptr<ZeroInflationIndex> &zii,
    CPI::InterpolationType interpolationType, const Handle<YieldTermStructure> &yts,
    const std::vector<Rate> &cStrikes, const std::vector<Rate> &fStrikes,
    const std::vector<Period> &cfMaturities, const Matrix &cPrice, const Matrix &fPrice) {
  return new InterpolatedCPICapFloorTermPriceSurface<I2D>(nominal, baseRate, observationLag, cal, bdc,
      dc, zii, interpolationType, yts, cStrikes, fStrikes, cfMaturities, cPrice, fPrice);
}

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
    CPICapFloorTermPriceSurface *s;
    switch (interpolator2D) {
    case hasquant::Bilinear:
      s = makeCPICapFloorTermPriceSurface<QuantLib::Bilinear>(nominal, baseRate, observationLag, *arg(cal),
          (BusinessDayConvention)bdc, *arg(dc), *arg(zii), (CPI::InterpolationType)interpolationType, *arg(yts),
          cStrikesVec, fStrikesVec, cfMaturitiesVec, cPriceMat, fPriceMat);
      break;
    case hasquant::Bicubic:
      s = makeCPICapFloorTermPriceSurface<QuantLib::Bicubic>(nominal, baseRate, observationLag, *arg(cal),
          (BusinessDayConvention)bdc, *arg(dc), *arg(zii), (CPI::InterpolationType)interpolationType, *arg(yts),
          cStrikesVec, fStrikesVec, cfMaturitiesVec, cPriceMat, fPriceMat);
      break;
    default:
      QL_FAIL("Unsupported 2-D interpolation " << interpolator2D);
    }
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

// Inner (1-D, per-maturity) interpolator dispatch, templated on the already-resolved 2-D
// (cap/floor price grid) interpolator -- mirrors qlInterpolatedZeroCurveAux's switch shape.
template <class I2D>
YoYCapFloorTermPriceSurface *makeYoYCapFloorTermPriceSurface(
    Natural fixingDays, const Period &yyLag, const shared_ptr<YoYInflationIndex>& yii,
    CPI::InterpolationType interpolation, const Handle<YieldTermStructure> &nominal,
    const DayCounter &dc, const Calendar &cal, BusinessDayConvention bdc,
    const std::vector<Rate> &cStrikes, const std::vector<Rate> &fStrikes,
    const std::vector<Period> &cfMaturities, const Matrix &cPrice, const Matrix &fPrice,
    int interpolator1D, int approximator, int approximatorArg) {
  switch (interpolator1D) {
  case hasquant::BackwardFlat:
    return new InterpolatedYoYCapFloorTermPriceSurface<I2D, BackwardFlat>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice);
  case hasquant::ForwardFlat:
    return new InterpolatedYoYCapFloorTermPriceSurface<I2D, ForwardFlat>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice);
  case hasquant::Linear:
    return new InterpolatedYoYCapFloorTermPriceSurface<I2D, Linear>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice);
  case hasquant::LogLinear:
    return new InterpolatedYoYCapFloorTermPriceSurface<I2D, LogLinear>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice);
  case hasquant::Cubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, Cubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, Cubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), Cubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, Cubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), Cubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, Cubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), Cubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  case hasquant::LogCubic:
    switch (approximator) {
    case hasquant::NaturalSpline:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, LogCubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), LogCubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
    case hasquant::Kruger:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, LogCubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), LogCubic(CubicInterpolation::Kruger));
    case hasquant::FritschButland:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, LogCubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), LogCubic(CubicInterpolation::FritschButland));
    case hasquant::Parabolic:
      return new InterpolatedYoYCapFloorTermPriceSurface<I2D, LogCubic>(fixingDays, yyLag, yii, interpolation, nominal, dc, cal, bdc, cStrikes, fStrikes, cfMaturities, cPrice, fPrice,
          I2D(), LogCubic(CubicInterpolation::Parabolic, approximatorArg));
    default:
      QL_FAIL("Unsupported approximation " << approximator);
    }
  default:
    QL_FAIL("Unsupported interpolation " << interpolator1D);
  }
}

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
    YoYCapFloorTermPriceSurface *s;
    switch (interpolator2D) {
    case hasquant::Bilinear:
      s = makeYoYCapFloorTermPriceSurface<QuantLib::Bilinear>(fixingDays, yyLag, yiiRef, (CPI::InterpolationType)interpolationType,
          nominalRef, *arg(dc), *arg(cal), (BusinessDayConvention)bdc, cStrikesVec, fStrikesVec, cfMaturitiesVec, cPriceMat, fPriceMat,
          interpolator1D, approximator, approximatorArg);
      break;
    case hasquant::Bicubic:
      s = makeYoYCapFloorTermPriceSurface<QuantLib::Bicubic>(fixingDays, yyLag, yiiRef, (CPI::InterpolationType)interpolationType,
          nominalRef, *arg(dc), *arg(cal), (BusinessDayConvention)bdc, cStrikesVec, fStrikesVec, cfMaturitiesVec, cPriceMat, fPriceMat,
          interpolator1D, approximator, approximatorArg);
      break;
    default:
      QL_FAIL("Unsupported 2-D interpolation " << interpolator2D);
    }
    return ret(new QlYoYCapFloorTermPriceSurface(alloc(s)));
  } catch (std::exception& er) {return handleException<QlYoYCapFloorTermPriceSurface*>(e, er);}}

int qlYoYCapFloorTermPriceSurfaceBaseDate(QlYoYCapFloorTermPriceSurface *o, char **e) {
  try {return qlNullableDate((*arg(o))->baseDate());
  } catch (std::exception& er) {return handleException<int>(e, er);}}

void qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates(QlYoYCapFloorTermPriceSurface *o,
    unsigned *dl, int **date, unsigned *rl, double **rate) {
  *date = 0; *rate = 0;
  const auto &dr = (*arg(o))->atmYoYSwapDateRates();
  *dl = dr.first.size(); *rl = dr.second.size();
  *date = qlAllocateInts(*dl); *rate = qlAllocateDoubles(*rl);
  for (unsigned i = 0; i < *dl; ++i) (*date)[i] = dr.first[i].serialNumber();
  for (unsigned i = 0; i < *rl; ++i) (*rate)[i] = dr.second[i];
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

void qlYoYCapFloorTermPriceSurfaceStrikes(QlYoYCapFloorTermPriceSurface *o, unsigned *sl, double **strike) {
  *strike = 0;
  const std::vector<Rate> &ks = (*arg(o))->strikes();
  *sl = ks.size(); *strike = qlAllocateDoubles(*sl);
  for (unsigned i = 0; i < *sl; ++i) (*strike)[i] = ks[i];
}

/* KInterpolatedYoYOptionletVolatilitySurface */

namespace {
  // The stripper sets the real vol on this engine as it bootstraps each strike's curve
  // (interpolatedyoyoptionletstripper.hpp), so it is constructed with a deliberately null
  // vol handle -- same idiom as the upstream test (inflationvolatility.cpp's testYoYPriceSurfaceToVol).
  Handle<YoYOptionletVolatilitySurface> qlNullYoYOptionletVolatilitySurfaceHandle() {
    return Handle<YoYOptionletVolatilitySurface>(shared_ptr<YoYOptionletVolatilitySurface>(), false);
  }

  // The stripper's own internal PiecewiseYoYOptionletVolatilityCurve<Interpolator1D> always
  // default-constructs its interpolator (interpolatedyoyoptionletstripper.hpp's initialize()
  // never passes one) -- only the surface's own K-direction interpolator (factory1D_) takes an
  // explicit instance, so only that one needs the Cubic/LogCubic approximator-specific
  // construction, mirroring makeYoYCapFloorTermPriceSurface's shape above.
  template <class Interpolator1D>
  YoYOptionletVolatilitySurface *makeKInterpolatedYoYOptionletVolatilitySurface(
      unsigned settlementDays, const Calendar &cal, BusinessDayConvention bdc, const DayCounter &dc,
      const shared_ptr<YoYCapFloorTermPriceSurface> &capFloorPrices,
      const shared_ptr<YoYInflationCapFloorEngine> &engine,
      const shared_ptr<YoYOptionletStripper> &stripper, double slope,
      const Interpolator1D &interpolator) {
    return new KInterpolatedYoYOptionletVolatilitySurface<Interpolator1D>(
        settlementDays, cal, bdc, dc, capFloorPrices->observationLag(), capFloorPrices, engine, stripper,
        slope, interpolator);
  }

  YoYOptionletVolatilitySurface *dispatchKInterpolatedYoYOptionletVolatilitySurface(
      unsigned settlementDays, const Calendar &cal, BusinessDayConvention bdc, const DayCounter &dc,
      const shared_ptr<YoYCapFloorTermPriceSurface> &capFloorPrices,
      const shared_ptr<YoYInflationCapFloorEngine> &engine, double slope,
      int interpolator1D, int approximator, int approximatorArg) {
    switch (interpolator1D) {
    case hasquant::BackwardFlat:
      return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine,
          shared_ptr<YoYOptionletStripper>(new InterpolatedYoYOptionletStripper<BackwardFlat>()), slope, BackwardFlat());
    case hasquant::ForwardFlat:
      return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine,
          shared_ptr<YoYOptionletStripper>(new InterpolatedYoYOptionletStripper<ForwardFlat>()), slope, ForwardFlat());
    case hasquant::Linear:
      return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine,
          shared_ptr<YoYOptionletStripper>(new InterpolatedYoYOptionletStripper<Linear>()), slope, Linear());
    case hasquant::LogLinear:
      return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine,
          shared_ptr<YoYOptionletStripper>(new InterpolatedYoYOptionletStripper<LogLinear>()), slope, LogLinear());
    case hasquant::Cubic: {
      shared_ptr<YoYOptionletStripper> stripper(new InterpolatedYoYOptionletStripper<Cubic>());
      switch (approximator) {
      case hasquant::NaturalSpline:
        return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine, stripper, slope,
            Cubic(CubicInterpolation::Spline, approximatorArg, CubicInterpolation::SecondDerivative, 0.0, CubicInterpolation::SecondDerivative, 0.0));
      case hasquant::Kruger:
        return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine, stripper, slope,
            Cubic(CubicInterpolation::Kruger));
      case hasquant::FritschButland:
        return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine, stripper, slope,
            Cubic(CubicInterpolation::FritschButland));
      case hasquant::Parabolic:
        return makeKInterpolatedYoYOptionletVolatilitySurface(settlementDays, cal, bdc, dc, capFloorPrices, engine, stripper, slope,
            Cubic(CubicInterpolation::Parabolic, approximatorArg));
      default:
        QL_FAIL("Unsupported approximation " << approximator);
      }
    }
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
}

QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBlack(
    unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
    QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
    QlYieldTermStructure *nominalTs, double slope,
    int interpolator, int approximator, int approximatorArg, char **e) {
  try {
    shared_ptr<YoYInflationCapFloorEngine> engine(new YoYInflationBlackCapFloorEngine(
        *arg(index), qlNullYoYOptionletVolatilitySurfaceHandle(), *arg(nominalTs)));
    YoYOptionletVolatilitySurface *s = dispatchKInterpolatedYoYOptionletVolatilitySurface(
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
    YoYOptionletVolatilitySurface *s = dispatchKInterpolatedYoYOptionletVolatilitySurface(
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
    YoYOptionletVolatilitySurface *s = dispatchKInterpolatedYoYOptionletVolatilitySurface(
        settlementDays, *arg(cal), (BusinessDayConvention)bdc, *arg(dc), *arg(capFloorPrices), engine, slope,
        interpolator, approximator, approximatorArg);
    return ret(new QlYoYOptionletVolatilitySurface(Handle<YoYOptionletVolatilitySurface>(shared_ptr<YoYOptionletVolatilitySurface>(alloc(s)))));
  } catch (std::exception& er) {return handleException<QlYoYOptionletVolatilitySurface*>(e, er);}}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
