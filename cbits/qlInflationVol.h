#ifdef __cplusplus
extern "C" {
#endif
  /* YoYOptionletVolatilitySurface */
  QlYoYOptionletVolatilitySurface *qlConstantYoYOptionletVolatility(QlQuote *v, unsigned settlementDays,
      Calendar *cal, int bdc, DayCounter *dc, int observationLagLen, int observationLagUnit, int frequency,
      int indexIsInterpolated, double minStrike, double maxStrike, int volType, double displacement, char **e);
  void qlFreeYoYOptionletVolatilitySurface(QlYoYOptionletVolatilitySurface *p);
  QlVolatilityTermStructure *qlYoYOptionletVolatilitySurfaceAsVolatilityTermStructure(QlYoYOptionletVolatilitySurface *o);
  double qlYoYOptionletVolatilitySurfaceVolatility(QlYoYOptionletVolatilitySurface *o, int maturityDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);
  double qlYoYOptionletVolatilitySurfaceTotalVariance(QlYoYOptionletVolatilitySurface *o, int exerciseDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);

  /* YoY inflation cap/floor pricing engines -- all three share the same ctor shape
     (index, vol surface handle, nominal discount curve handle). */
  QlPricingEngine *qlYoYInflationBlackCapFloorEngine(QlYoYInflationIndex *index, QlYoYOptionletVolatilitySurface *vol,
      QlYieldTermStructure *nominalTs, char **e);
  QlPricingEngine *qlYoYInflationUnitDisplacedBlackCapFloorEngine(QlYoYInflationIndex *index,
      QlYoYOptionletVolatilitySurface *vol, QlYieldTermStructure *nominalTs, char **e);
  QlPricingEngine *qlYoYInflationBachelierCapFloorEngine(QlYoYInflationIndex *index, QlYoYOptionletVolatilitySurface *vol,
      QlYieldTermStructure *nominalTs, char **e);

  /* CPICapFloorTermPriceSurface */
  QlCPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurface(double nominal, double baseRate,
      int observationLagLen, int observationLagUnit, Calendar *cal, int bdc, DayCounter *dc,
      QlZeroInflationIndex *zii, int interpolationType, QlYieldTermStructure *yts,
      unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
      unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
      unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
      unsigned fPriceRows, unsigned fPriceCols, double *fPriceData,
      int interpolator2D, char **e);
  void qlFreeCPICapFloorTermPriceSurface(QlCPICapFloorTermPriceSurface *o);
  QlTermStructure *qlCPICapFloorTermPriceSurfaceAsTermStructure(QlCPICapFloorTermPriceSurface *o);

  /* The only CPICapFloor pricing engine in QL 1.43: prices purely by interpolating a price
     surface, no stochastic-vol model (see plan Item 3's note on the CPI/YoY asymmetry). */
  QlPricingEngine *qlInterpolatingCPICapFloorEngine(QlCPICapFloorTermPriceSurface *surface, char **e);

  /* CPIVolatilitySurface -- no consumer (engine/pricer) in QL 1.43, see this type's own haddock
     in QuantLib.Internal.Type; stands alone as a queryable surface. */
  QlCPIVolatilitySurface *qlConstantCPIVolatility(QlQuote *v, unsigned settlementDays, Calendar *cal,
      int bdc, DayCounter *dc, int observationLagLen, int observationLagUnit, int frequency,
      int indexIsInterpolated, char **e);
  void qlFreeCPIVolatilitySurface(QlCPIVolatilitySurface *p);
  QlVolatilityTermStructure *qlCPIVolatilitySurfaceAsVolatilityTermStructure(QlCPIVolatilitySurface *o);
  double qlCPIVolatilitySurfaceVolatility(QlCPIVolatilitySurface *o, int maturityDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);
  double qlCPIVolatilitySurfaceTotalVariance(QlCPIVolatilitySurface *o, int exerciseDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);

  /* YoYCapFloorTermPriceSurface */
  QlYoYCapFloorTermPriceSurface *qlYoYCapFloorTermPriceSurface(unsigned fixingDays,
      int yyLagLen, int yyLagUnit, QlYoYInflationIndex *yii, int interpolationType,
      QlYieldTermStructure *nominal, DayCounter *dc, Calendar *cal, int bdc,
      unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
      unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
      unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
      unsigned fPriceRows, unsigned fPriceCols, double *fPriceData,
      int interpolator2D, int interpolator1D, int approximator, int approximatorArg, char **e);
  void qlFreeYoYCapFloorTermPriceSurface(QlYoYCapFloorTermPriceSurface *o);
  QlTermStructure *qlYoYCapFloorTermPriceSurfaceAsTermStructure(QlYoYCapFloorTermPriceSurface *o);
  int qlYoYCapFloorTermPriceSurfaceBaseDate(QlYoYCapFloorTermPriceSurface *o, char **e);
  void qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates(QlYoYCapFloorTermPriceSurface *o,
      unsigned *dl, int **date, unsigned *rl, double **rate);
  double qlYoYCapFloorTermPriceSurfaceAtmYoYSwapRate(QlYoYCapFloorTermPriceSurface *o, int d,
      int extrapolate, char **e);
  double qlYoYCapFloorTermPriceSurfaceAtmYoYRate(QlYoYCapFloorTermPriceSurface *o, int d,
      int obsLagLen, int obsLagUnit, int extrapolate, char **e);
  void qlYoYCapFloorTermPriceSurfaceStrikes(QlYoYCapFloorTermPriceSurface *o, unsigned *sl, double **strike);

  /* KInterpolatedYoYOptionletVolatilitySurface<Linear> -- another concrete leaf constructor for
     YoYOptionletVolatilitySurface (Item 1), built by internally wiring up an
     InterpolatedYoYOptionletStripper<Linear> and one of the 3 YoYInflationCapFloorEngine
     descendants (constructed here with a null vol handle -- the stripper sets the real vol as
     it bootstraps each strike's curve, see interpolatedyoyoptionletstripper.hpp). Neither the
     stripper nor the per-strike PiecewiseYoYOptionletVolatilityCurve/YoYOptionletHelper it
     builds internally are ever exposed: nothing in upstream reaches them from outside
     YoYOptionletStripper::initialize, so there is nothing for a Haskell binding to return. */
  QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBlack(
      unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
      QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
      QlYieldTermStructure *nominalTs, double slope, char **e);
  QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack(
      unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
      QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
      QlYieldTermStructure *nominalTs, double slope, char **e);
  QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBachelier(
      unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
      QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
      QlYieldTermStructure *nominalTs, double slope, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
