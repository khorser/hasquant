#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o);
  QlTermStructure* qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o);
//  QlDefaultProbabilityTermStructure* qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
//  QlDefaultProbabilityTermStructure* qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e);
  QlDefaultProbabilityTermStructure* qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e);
//  QlDefaultProbabilityTermStructure* qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
//  QlDefaultProbabilityTermStructure* qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
//  QlDefaultProbabilityTermStructure* qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
//  QlDefaultProbabilityTermStructure* qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
  void qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o);
//  QlDefaultProbabilityHelper* qlSpreadCdsHelper(QlQuote* runningSpread, int, int, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, char **e);
//  QlDefaultProbabilityHelper* qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, int, int, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, char **e);
//  QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve(int referenceDate, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, double accuracy, char *trait, char* interpolator, char **e);
//  QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve1(unsigned settlementDays, Calendar *calendar, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, double accuracy, char *trait, char* interpolator, char **e);

  double qlDefaultProbabilityTermStructureDefaultDensity1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultDensity(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability2(QlDefaultProbabilityTermStructure* o, int x1, int x2, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability3(QlDefaultProbabilityTermStructure* o, double x1, double x2, int extrapo, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureHazardRate1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureHazardRate(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureSurvivalProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureSurvivalProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
