/* dates are passed as int = serial number o the date.
 * the code assumes that Haskell bindings validate date */ 

#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  /* utilities */
  const char *DLLEXPORT qlVersion();
  const char *DLLEXPORT qlBoostVersion();

  void DLLEXPORT qlFreeString(char *p);
  void DLLEXPORT qlFreeInts(int *p);

  /* date */
  int DLLEXPORT qlMinDateSerialNumber();
  int DLLEXPORT qlMaxDateSerialNumber();
  int DLLEXPORT qlMinYear();
  int DLLEXPORT qlMinMonth();
  int DLLEXPORT qlMinDay();
  int DLLEXPORT qlWeekday(int date);

#ifdef quantlib_cash_flow_hpp
  /* leg */
  Leg *DLLEXPORT qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int DLLEXPORT qlLegStartDate(Leg *leg, char **e);

  void DLLEXPORT qlFreeLeg(Leg *leg);
#endif

  /* calendar */
  Calendar *DLLEXPORT qlCalendar(const char *name, char **e);
  const char *DLLEXPORT qlCalendarName(Calendar *calendar);
  int DLLEXPORT qlCalendarAdjust(Calendar *c, int date, int conv);
  int DLLEXPORT qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);

  void DLLEXPORT qlFreeCalendar(Calendar *calendar);

  /* settings */
  int DLLEXPORT qlSettingsEvaluationDate();
  int DLLEXPORT qlSettingsEnforceTodaysHistoricFixings();
  void DLLEXPORT qlSettingsSetEvaluationDate(int x, char **e);
  void DLLEXPORT qlSettingsSetEnforceTodaysHistoricFixings(int x, char **e);

  /* bond */
#ifdef quantlib_cash_flow_hpp
  QlBond *DLLEXPORT qlBond(unsigned settlDays, Calendar *calendar, int issueDate,
    Leg *coupons, char **e);
  QlBond *DLLEXPORT qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e);
#endif
  int DLLEXPORT qlBondMaturityDate(QlBond *bond);
  QlInstrument *DLLEXPORT qlBondAsInstrument(QlBond *bond);

  QlFixedRateBond *DLLEXPORT qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule,
    unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal,
    char **e);
  QlFixedRateBond *DLLEXPORT qlFixedRateBond1(unsigned settlDays, Calendar *cpnCal, double face,
    int start, int maturity, Period *tenor, unsigned cLen, double *coupons,
    DayCounter *dayCounter, int accrConv, int paymentConv, double redemption,
    int issue, int stub, int rule, int eom, Calendar *payCal, char **e);
  QlFixedRateBond *DLLEXPORT qlFixedRateBond2(unsigned settlDays, double face, Schedule *sched,
    unsigned cLen, InterestRate **coupons, int paymentConv, double redemption,
    int issue, Calendar *cal, char **e);
  QlBond *DLLEXPORT qlZeroCouponBond(int settlDays, Calendar *cal, double face,
    int maturity, int payConv, double redemption, int issue, char **e);
  void DLLEXPORT qlBondSetCouponPricer(QlBond *b, QlFloatingRateCouponPricer *p, char **e);
  QlBond *DLLEXPORT qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched,
    QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads,
    unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, double redemption, int issue, char **e);
  QlBond *DLLEXPORT qlFixedRateBondAsBond(QlFixedRateBond *bond);

  void DLLEXPORT qlFreeBond(QlBond *bond);
  void DLLEXPORT qlFreeFixedRateBond(QlFixedRateBond *bond);

  /* daycounter */
  DayCounter *DLLEXPORT qlDayCounter(const char *name, char **e);
  DayCounter *DLLEXPORT qlDayCounterBusiness252(Calendar *cal, char **e);
  const char *DLLEXPORT qlDayCounterName(DayCounter *counter);

  void DLLEXPORT qlFreeDayCounter(DayCounter *counter);

  /* currency */
  Currency *DLLEXPORT qlCurrency(const char *name, char **e);
  const char *DLLEXPORT qlCurrencyName(Currency *currency);

  void DLLEXPORT qlFreeCurrency(Currency *currency);

  /* period */
  Period *DLLEXPORT qlPeriod(int n, int u, char **e);
  Period *DLLEXPORT qlPeriodFromFrequency(int freq, char **e);
  int DLLEXPORT qlPeriodToFrequency(Period *period, char **e);

  void DLLEXPORT qlFreePeriod(Period *period);

  /* quote */
  QlQuote *DLLEXPORT qlSimpleQuote(double value, char **e);
  double DLLEXPORT qlQuoteValue(QlQuote *quote, char **e);

  void DLLEXPORT qlFreeQuote(QlQuote *quote);

  /* schedule */
  Schedule *DLLEXPORT qlSchedule(int eff, int term, Period *tenor, Calendar *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  Schedule *DLLEXPORT qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv,
    char **e);
  Schedule *DLLEXPORT qlScheduleUntil(Schedule *sched, int date, char **e);
  int *DLLEXPORT qlScheduleDates(Schedule *sched, int *count);

  void DLLEXPORT qlFreeSchedule(Schedule *s);

  /* interest rate */
  InterestRate *DLLEXPORT qlInterestRate(double r, DayCounter *dc, int comp, int freq,
    char **e);

  void DLLEXPORT qlFreeInterestRate(InterestRate *rate);

  /* enumerations */
  int *DLLEXPORT qlEnumerationValue(const char *name, int *c);

#ifdef quantlib_ratehelpers_hpp
  /* yield term structure */
  QlRateHelper *DLLEXPORT qlDepositRateHelper(QlQuote *quote, Period *period,
    unsigned fixDays, Calendar *calendar, int conv, int eom,
    DayCounter *dayCount, char **e);
  QlRateHelper *DLLEXPORT qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays,
    double face, Schedule *sched, unsigned cLen, double *coupons,
    DayCounter *dayCount, int conv, double redemption, int issue, char **e);
  QlYieldTermStructure *DLLEXPORT qlPiecewiseYieldCurve(int date, unsigned rateLen,
    QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, double accuracy, char *trait,
    char *interpolator, char **e);
  QlYieldTermStructure *DLLEXPORT qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal,
    unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, double accuracy, char *trait,
    char *interpolator, char **e);
  QlRateHelper *DLLEXPORT qlSwapRateHelper1(QlQuote *q, Period *t, Calendar *cal, int freq,
    int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, Period *fwdStart,
    QlYieldTermStructure *ts, char **e);

  void DLLEXPORT qlFreeRateHelper(QlRateHelper *helper);
#endif
  void DLLEXPORT qlFreeYieldTermStructure(QlYieldTermStructure *ts);
  double DLLEXPORT qlYieldTSDiscount(QlYieldTermStructure *ts, int date,
    int extrapolate, char **e);

  /* pricing engine */
  QlPricingEngine *DLLEXPORT qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e);

  void DLLEXPORT qlFreePricingEngine(QlPricingEngine *engine);

  /* instrument */
  void DLLEXPORT qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
    char **e);
  double DLLEXPORT qlInstrumentNPV(QlInstrument *instr, char **e);
  void DLLEXPORT qlFreeInstrument(QlInstrument *instr);

  /* ibor index */
  QlIborIndex *DLLEXPORT qlIborIndex(char *name, Period *period, unsigned settlDays,
    Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlLibor(char *name, Period *tenor, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd,
    char **e);
  QlIborIndex *DLLEXPORT qlDailyTenorLibor(char *name, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dayCount,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlOvernightIndex(char *name, unsigned settlDays, Currency *cur,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateIborON(char *name,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e);

  void DLLEXPORT qlFreeIborIndex(QlIborIndex *i);
  QlIndex *DLLEXPORT qlIborAsIndex(QlIborIndex *i);

  /* index */
  void DLLEXPORT qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e);
  void DLLEXPORT qlFreeIndex(QlIndex *i);

  /* coupon pricer */
  QlFloatingRateCouponPricer *DLLEXPORT qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e);
  void DLLEXPORT qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);

  /* volatility */
  QlOptionletVolatilityStructure *DLLEXPORT qlConstantOptionletVol(
    unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e);
  void DLLEXPORT qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
