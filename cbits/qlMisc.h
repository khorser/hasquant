#ifdef __cplusplus
extern "C" {
#endif
  int qlSettingsEvaluationDate();
  int qlSettingsEnforceTodaysHistoricFixings();
  void qlSettingsSetEvaluationDate(int x, char **e);
  void qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int qlSettingsIncludeTodaysCashFlows();
  void qlSettingsSetIncludeTodaysCashFlows(int x);
  int qlSettingsIncludeReferenceDateEvents();
  void qlSettingsSetIncludeReferenceDateEvents(int x0);
  void *qlSavedSettings();
  void qlFreeSavedSettings(void *settings);

  const char *qlVersion();
  const char *qlBoostVersion();
  void qlFreeString(char *p);
  void qlFreeInts(int *p);
  void qlFreeUInts(unsigned *p);
  void qlFreeDoubles(double *p);
  void qlFreePointerArray(void **p);
  int qlNullInteger();
  double qlNullReal();
  double qlEpsilon();

  Currency *qlCurrency(int ccy, char **e);
  const char *qlCurrencyName(Currency *currency);

  void qlFreeCurrency(Currency *currency);
  char* qlCurrencyCode(Currency* o);
  char* qlCurrencyFormat(Currency* o);
  int qlCurrencyFractionsPerUnit(Currency* o);
  char* qlCurrencyFractionSymbol(Currency* o);
  int qlCurrencyNumericCode(Currency* o);
  char* qlCurrencySymbol(Currency* o);
  Currency* qlCreateCurrency(char* name, char* code, int numericCode, char* symbol, char* fractionSymbol, int fractionsPerUnit, Rounding* rounding, char* formatString, Currency* triangulationCurrency, char **e);

  InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq, char **e);
  double qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double qlInterestRateCompoundFactor(InterestRate* o, double t, char **e);
  double qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double qlInterestRateDiscountFactor(InterestRate* o, double t, char **e);
  InterestRate* qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e);
  InterestRate* qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e);
  double qlInterestRateRate(InterestRate* o);
  void qlFreeInterestRate(InterestRate *rate);

  void qlFreeConstraint(Constraint *o);
  Constraint* qlBoundaryConstraint(double low, double high, char **e);
  Constraint* qlCompositeConstraint(Constraint* c1, Constraint* c2, char **e);
  Constraint* qlNoConstraint(char **e);
  Constraint* qlPositiveConstraint(char **e);

  void qlFreeOptimizationMethod(OptimizationMethod *o);
  OptimizationMethod* qlSimplex(double lambda, char **e);
  OptimizationMethod* qlLevenbergMarquardt(double epsfcn, double xtol, double gtol, char **e);
  void qlFreeEndCriteria(EndCriteria *o);
  EndCriteria* qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e);
  void qlFreeTimeGrid(TimeGrid *o);
  TimeGrid* qlTimeGrid1(double end, unsigned steps, char **e);
  TimeGrid* qlTimeGrid2(unsigned x0Len, double* x0, char **e);
  TimeGrid* qlTimeGrid3(unsigned x0Len, double* x0, unsigned steps, char **e);

  void qlFreeRounding(Rounding *o);
  Rounding* qlRounding(char **e);
  Rounding* qlRounding1(int precision, int type, int digit, char **e);
  double qlRound(Rounding *r, double val);
  QlSimpleQuote *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(QlQuote *quote, char **e);

  void qlFreeQuote(QlQuote *quote);
  void qlFreeSimpleQuote(QlSimpleQuote *o);
  QlQuote* qlSimpleQuoteAsQuote(QlSimpleQuote *o);
  double qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e);
  QlQuote* qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e);
  QlQuote* qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, int, int, char **e);
  QlQuote* qlForwardValueQuote(QlIndex* index, int fixingDate, char **e);
  QlQuote* qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
  QlQuote* qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
  QlQuote* qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e);
  QlQuote* qlLastFixingQuote(QlIndex* index, char **e);
  int qlQuoteIsValid(QlQuote* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
