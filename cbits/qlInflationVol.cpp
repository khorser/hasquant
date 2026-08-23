#include <ql/termstructures/volatility/inflation/yoyinflationoptionletvolatilitystructure.hpp>
#include <ql/pricingengines/inflation/inflationcapfloorengines.hpp>
#include <ql/experimental/inflation/cpicapfloortermpricesurface.hpp>
#include <ql/experimental/inflation/cpicapfloorengines.hpp>
#include "qlaux.h"
using namespace QuantLib;
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

QlCPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurface(double nominal, double baseRate,
    int observationLagLen, int observationLagUnit, Calendar *cal, int bdc, DayCounter *dc,
    QlZeroInflationIndex *zii, int interpolationType, QlYieldTermStructure *yts,
    unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
    unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
    unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
    unsigned fPriceRows, unsigned fPriceCols, double *fPriceData, char **e) {
  try {return ret(new QlCPICapFloorTermPriceSurface(alloc(new InterpolatedCPICapFloorTermPriceSurface<Bilinear>(
      nominal, baseRate, Period(observationLagLen, (TimeUnit)observationLagUnit), *arg(cal), (BusinessDayConvention)bdc,
      *arg(dc), *arg(zii), (CPI::InterpolationType)interpolationType, *arg(yts),
      std::vector<Rate>(cStrikes, cStrikes+cStrikesLen), std::vector<Rate>(fStrikes, fStrikes+fStrikesLen),
      qlPeriodVector(cfMaturitiesNum, cfMaturitiesUnit, cfMaturitiesLen),
      qlMatrix(cPriceData, cPriceRows, cPriceCols), qlMatrix(fPriceData, fPriceRows, fPriceCols)))));
  } catch (std::exception& er) {return handleException<QlCPICapFloorTermPriceSurface*>(e, er);}}

/* InterpolatingCPICapFloorEngine -- the only CPICapFloor engine in QL 1.43 */

QlPricingEngine *qlInterpolatingCPICapFloorEngine(QlCPICapFloorTermPriceSurface *surface, char **e) {
  try {return ret(new QlPricingEngine(alloc(new InterpolatingCPICapFloorEngine(Handle<CPICapFloorTermPriceSurface>(*arg(surface))))));
  } catch (std::exception& er) {return handleException<QlPricingEngine*>(e, er);}}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
