#ifdef _WIN32
# if defined(DLLSOURCE)
#  define DLLEXPORT __declspec(dllexport)
# elif defined(DLLUSE)
#  define DLLEXPORT __declspec(dllimport)
# else
#  define DLLEXPORT
# endif
#else
# define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void DLLEXPORT qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o);
  QlTermStructure* DLLEXPORT qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
  void DLLEXPORT qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o);
  QlDefaultProbabilityHelper* DLLEXPORT qlSpreadCdsHelper(QlQuote* runningSpread, Period* tenor, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, char **e);
  QlDefaultProbabilityHelper* DLLEXPORT qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, Period* tenor, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
