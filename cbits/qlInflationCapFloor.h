#ifdef __cplusplus
extern "C" {
#endif
  /* YoYInflationCapFloor -- constructed directly at the given Type (Cap/Floor/Collar are thin
     ctor-only subclasses upstream with no logic of their own, so there's no need to touch them). */
  QlYoYInflationCapFloor *qlYoYInflationCap(Leg *yoyLeg, unsigned exerciseRatesLen, double *exerciseRates, char **e);
  QlYoYInflationCapFloor *qlYoYInflationFloor(Leg *yoyLeg, unsigned exerciseRatesLen, double *exerciseRates, char **e);
  QlYoYInflationCapFloor *qlYoYInflationCollar(Leg *yoyLeg, unsigned capRatesLen, double *capRates,
      unsigned floorRatesLen, double *floorRates, char **e);
  void qlFreeYoYInflationCapFloor(QlYoYInflationCapFloor *o);
  QlInstrument *qlYoYInflationCapFloorAsInstrument(QlYoYInflationCapFloor *o);
  double qlYoYInflationCapFloorAtmRate(QlYoYInflationCapFloor *o, QlYieldTermStructure *discountCurve, char **e);
  QlYoYInflationCapFloor *qlYoYInflationCapFloorOptionlet(QlYoYInflationCapFloor *o, unsigned n, char **e);

  /* CPICapFloor -- a single cumulative option, unlike YoYInflationCapFloor; no impliedVolatility
     (no vol-driven engine exists for it in QL 1.43, see qlInterpolatingCPICapFloorEngine below). */
  QlCPICapFloor *qlCPICapFloor(int type, double nominal, int startDate, double baseCPI, int maturity,
      Calendar *fixCalendar, int fixConvention, Calendar *payCalendar, int payConvention, double strike,
      QlZeroInflationIndex *index, int observationLagLen, int observationLagUnit, int observationInterpolation,
      char **e);
  void qlFreeCPICapFloor(QlCPICapFloor *o);
  QlInstrument *qlCPICapFloorAsInstrument(QlCPICapFloor *o);
#ifdef __cplusplus
}
#endif

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
