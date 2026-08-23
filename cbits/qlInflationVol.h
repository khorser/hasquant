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
#ifdef __cplusplus
}
#endif

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
