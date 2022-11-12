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
  unsigned qlTimeGridSize(TimeGrid* t);
  double qlTimeGridAt(TimeGrid* t, unsigned i, char **e);
  void qlTimeGridPoints(TimeGrid *t, unsigned *len, double **p, char **e);

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

  int qlMinDateSerialNumber();
  int qlMaxDateSerialNumber();
  int qlMinYear();
  int qlMinMonth();
  int qlMinDay();
  int qlWeekday(int date);
  int qlDateDayOfYear(int o);
  int qlDateEndOfMonth(int d);
  int qlDateIsEndOfMonth(int d);
  int qlDateNextWeekday(int d, int w);
  int qlDateNthWeekday(unsigned n, int w, int m, int y);

  char* qlIMMCode(int immDate, char **e);
  int qlIMMDate(char* immCode, int referenceDate, char **e);
  int qlIMMIsIMMcode(char* in, int mainCycle);
  int qlIMMIsIMMdate(int d, int mainCycle);
  char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e);
  char* qlIMMNextCode(int d, int mainCycle);
  int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e);
  int qlIMMNextDate(int d, int mainCycle);

  int qlAddPeriod(int d, int, int, char **e);

  void qlECBAddDate(int d, char **e);
  char* qlECBCode(int ecbDate, char **e);
  int qlECBDate1(char* ecbCode, int referenceDate, char **e);
  int qlECBDate(int m, int y, char **e);
  int qlECBIsECBcode(char* in, char **e);
  int qlECBIsECBdate(int d, char **e);
  void qlECBKnownDates(unsigned *count, int **ds, char **e);
  char* qlECBNextCode1(char* ecbCode, char **e);
  char* qlECBNextCode(int d, char **e);
  int qlECBNextDate1(char* ecbCode, int referenceDate, char **e);
  int qlECBNextDate(int d, char **e);
  void qlECBNextDates(int d, unsigned *count, int **ds, char **e);
  void qlECBNextDates1(char* ecbCode, int referenceDate, unsigned *count, int **ds, char **e);
  void qlECBRemoveDate(int d, char **e);

  Calendar *qlCalendar(int country, int market, char **e);
  const char *qlCalendarName(Calendar *calendar);
  int qlCalendarAdjust(Calendar *c, int date, int conv);
  int qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);
  void qlCalendarAddHoliday(Calendar* o, int x0, char **e);
  int qlCalendarAdvance1(Calendar* o, int date, int, int, int convention, int endOfMonth, char **e);
  int qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e);
  int qlCalendarEndOfMonth(Calendar* o, int d, char **e);
  int qlCalendarIsBusinessDay(Calendar* o, int d, char **e);
  int qlCalendarIsEndOfMonth(Calendar* o, int d, char **e);
  int qlCalendarIsHoliday(Calendar* o, int d, char **e);
  int qlCalendarIsWeekend(Calendar* o, int w, char **e);
  void qlCalendarRemoveHoliday(Calendar* o, int x0, char **e);
  Calendar* qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e);
  Calendar* qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e);
  Calendar* qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e);
  Calendar* qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e);

  void qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, int **days, char **e);
  void qlFreeCalendar(Calendar *calendar);

  Schedule *qlSchedule(int eff, int term, int, int, Calendar *cal, int conv, int termConv, int rule, int eom, int first, int nextToLast, char **e);
  Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv, char **e);
  Schedule *qlScheduleUntil(Schedule *sched, int date, char **e);
  void qlScheduleDates(Schedule *sched, unsigned *count, int **days);
  void qlFreeSchedule(Schedule *s);

  int qlPeriodFromFrequency1(int freq, int *, char **e);
  int qlPeriodToFrequency1(int l, int u, char **e);
  int qlPeriodParserParse1(char* str, int *u, char **e);
  int qlPeriodAdd1(int, int u1, int, int u2, int *u, char **e);
  int qlPeriodDivide1(int, int u1, int n2, int *u, char **e);
  int qlPeriodNormalize1(int, int u, int *, char **e);
  int qlPeriodsLT1(int, int u1, int, int u2, char **e);

  DayCounter *qlDayCounter(int type, int convention, char **e);
  DayCounter *qlDayCounterBusiness252(Calendar *cal, char **e);
  const char *qlDayCounterName(DayCounter *counter);
  int qlDayCounterDayCount(DayCounter* o, int x0, int x1);
  double qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e);

  void qlFreeDayCounter(DayCounter *counter);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
