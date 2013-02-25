#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  void DLLEXPORT qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o);
  QlTermStructure* DLLEXPORT qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
  QlDefaultProbabilityTermStructure* DLLEXPORT qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, int* jumpDates, char*  interpolator, char **e);
}
