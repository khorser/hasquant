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

  /* CPICapFloorTermPriceSurface -- hardcoded to InterpolatedCPICapFloorTermPriceSurface<Bilinear>,
     the only Interpolator2D instantiation upstream's own test-suite (inflationcpicapfloor.cpp)
     uses; widen to a dispatch table only if a concrete need for another interpolator shows up. */
  QlCPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurface(double nominal, double baseRate,
      int observationLagLen, int observationLagUnit, Calendar *cal, int bdc, DayCounter *dc,
      QlZeroInflationIndex *zii, int interpolationType, QlYieldTermStructure *yts,
      unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
      unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
      unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
      unsigned fPriceRows, unsigned fPriceCols, double *fPriceData, char **e);
  void qlFreeCPICapFloorTermPriceSurface(QlCPICapFloorTermPriceSurface *o);
  QlTermStructure *qlCPICapFloorTermPriceSurfaceAsTermStructure(QlCPICapFloorTermPriceSurface *o);

  /* The only CPICapFloor pricing engine in QL 1.43: prices purely by interpolating a price
     surface, no stochastic-vol model (see plan Item 3's note on the CPI/YoY asymmetry). */
  QlPricingEngine *qlInterpolatingCPICapFloorEngine(QlCPICapFloorTermPriceSurface *surface, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
