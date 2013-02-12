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
  int DLLEXPORT qlDateDayOfYear(int o, char **e);
  int DLLEXPORT qlDateEndOfMonth(int d, char **e);
  int DLLEXPORT qlDateIsEndOfMonth(int d, char **e);
  int DLLEXPORT qlDateNextWeekday(int d, int w, char **e);
  int DLLEXPORT qlDateNthWeekday(unsigned n, int w, int m, int y, char **e);

  char* DLLEXPORT qlIMMCode(int immDate, char **e);
  int DLLEXPORT qlIMMDate(char* immCode, int referenceDate, char **e);
  int DLLEXPORT qlIMMIsIMMcode(char* in, int mainCycle, char **e);
  int DLLEXPORT qlIMMIsIMMdate(int d, int mainCycle, char **e);
  char* DLLEXPORT qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e);
  char* DLLEXPORT qlIMMNextCode(int d, int mainCycle, char **e);
  int DLLEXPORT qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e);
  int DLLEXPORT qlIMMNextDate(int d, int mainCycle, char **e);

#ifdef quantlib_cash_flow_hpp
  /* leg */
  Leg *DLLEXPORT qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int DLLEXPORT qlLegStartDate(Leg *leg, char **e);

  void DLLEXPORT qlFreeLeg(Leg *leg);
  double DLLEXPORT qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
#endif

  /* calendar */
  Calendar *DLLEXPORT qlCalendar(const char *name, char **e);
  const char *DLLEXPORT qlCalendarName(Calendar *calendar);
  int DLLEXPORT qlCalendarAdjust(Calendar *c, int date, int conv);
  int DLLEXPORT qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);
  void DLLEXPORT qlCalendarAddHoliday(Calendar* o, int x0, char **e);
  int DLLEXPORT qlCalendarAdvance1(Calendar* o, int date, Period* period, int convention, int endOfMonth, char **e);
  int DLLEXPORT qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e);
  int DLLEXPORT qlCalendarEndOfMonth(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsBusinessDay(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsEndOfMonth(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsHoliday(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsWeekend(Calendar* o, int w, char **e);
  void DLLEXPORT qlCalendarRemoveHoliday(Calendar* o, int x0, char **e);
  Calendar* DLLEXPORT qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e);

  void DLLEXPORT qlFreeCalendar(Calendar *calendar);

  /* settings */
  int DLLEXPORT qlSettingsEvaluationDate();
  int DLLEXPORT qlSettingsEnforceTodaysHistoricFixings();
  void DLLEXPORT qlSettingsSetEvaluationDate(int x, char **e);
  void DLLEXPORT qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int DLLEXPORT qlSettingsIncludeTodaysCashFlows();
  void DLLEXPORT qlSettingsSetIncludeTodaysCashFlows(int x);

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

  double DLLEXPORT qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy,
    unsigned maxEvaluations, char **e);
  double DLLEXPORT qlBondAccruedAmount(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondCleanPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  double DLLEXPORT qlBondCleanPrice(QlBond* o, char **e);
  double DLLEXPORT qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  double DLLEXPORT qlBondDirtyPrice(QlBond* o, char **e);
  int DLLEXPORT qlBondNextCashFlowDate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondNextCouponRate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondNotional(QlBond* o, int d, char **e);
  int DLLEXPORT qlBondPreviousCashFlowDate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondPreviousCouponRate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondSettlementValue1(QlBond* o, double cleanPrice, char **e);
  double DLLEXPORT qlBondSettlementValue(QlBond* o, char **e);
  double DLLEXPORT qlBondYield1(QlBond* o, double cleanPrice, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, char **e);
  int DLLEXPORT qlBondIsTradable(QlBond* o, int d, char **e);

  void DLLEXPORT qlFreeBond(QlBond *bond);
  void DLLEXPORT qlFreeFixedRateBond(QlFixedRateBond *bond);

  /* daycounter */
  DayCounter *DLLEXPORT qlDayCounter(const char *name, char **e);
  DayCounter *DLLEXPORT qlDayCounterBusiness252(Calendar *cal, char **e);
  const char *DLLEXPORT qlDayCounterName(DayCounter *counter);
  int DLLEXPORT qlDayCounterDayCount(DayCounter* o, int x0, int x1, char **e);
  double DLLEXPORT qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e);

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
  QlSimpleQuote *DLLEXPORT qlSimpleQuote(double value, char **e);
  double DLLEXPORT qlQuoteValue(QlQuote *quote, char **e);

  void DLLEXPORT qlFreeQuote(QlQuote *quote);
  void DLLEXPORT qlFreeSimpleQuote(QlSimpleQuote *o);
  QlQuote* DLLEXPORT qlSimpleQuoteAsQuote(QlSimpleQuote *o);
  double DLLEXPORT qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e);

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
  double DLLEXPORT qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double DLLEXPORT qlInterestRateCompoundFactor(InterestRate* o, double t, char **e);
  double DLLEXPORT qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double DLLEXPORT qlInterestRateDiscountFactor(InterestRate* o, double t, char **e);
  InterestRate* DLLEXPORT qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* DLLEXPORT qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e);
  InterestRate* DLLEXPORT qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* DLLEXPORT qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e);
  double DLLEXPORT qlInterestRateRate(InterestRate* o);

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
  QlRateHelper* DLLEXPORT qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);
#endif
  void DLLEXPORT qlFreeYieldTermStructure(QlYieldTermStructure *ts);
  double DLLEXPORT qlYieldTSDiscount(QlYieldTermStructure *ts, int date,
    int extrapolate, char **e);
  QlYieldTermStructure* DLLEXPORT qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  QlYieldTermStructure* DLLEXPORT qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, Period* p, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e);
  double DLLEXPORT qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e);

  /* pricing engine */
  QlPricingEngine *DLLEXPORT qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e);
  QlPricingEngine* DLLEXPORT qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);

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
  QlOvernightIndex *DLLEXPORT qlOvernightIndex(char *name, unsigned settlDays, Currency *cur,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *DLLEXPORT qlCreateONIndex(char *name, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e);

  void DLLEXPORT qlFreeIborIndex(QlIborIndex *i);
  QlInterestRateIndex* DLLEXPORT qlIborIndexAsInterestRateIndex(QlIborIndex *o);
  void DLLEXPORT qlFreeOvernightIndex(QlOvernightIndex *o);
  QlIborIndex* DLLEXPORT qlOvernightIndexAsIborIndex(QlOvernightIndex *o);

  /* index */
  void DLLEXPORT qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e);
  void DLLEXPORT qlFreeIndex(QlIndex *i);
  void DLLEXPORT qlFreeInterestRateIndex(QlInterestRateIndex *o);
  QlIndex* DLLEXPORT qlInterestRateIndexAsIndex(QlInterestRateIndex *o);
  void DLLEXPORT qlFreeSwapIndex(QlSwapIndex *o);
  QlInterestRateIndex* DLLEXPORT qlSwapIndexAsInterestRateIndex(QlSwapIndex *o);

  /* forward */
  void DLLEXPORT qlFreeFixedRateBondForward(QlFixedRateBondForward *fwd);
  QlForward* DLLEXPORT qlFixedRateBondForwardAsForward(QlFixedRateBondForward *fwd);
  QlFixedRateBondForward* DLLEXPORT qlFixedRateBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlFixedRateBond* fixedCouponBond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double DLLEXPORT qlFixedRateBondForwardCleanForwardPrice(QlFixedRateBondForward* o, char **e);
  double DLLEXPORT qlFixedRateBondForwardForwardPrice(QlFixedRateBondForward* o, char **e);
  void DLLEXPORT qlFreeForward(QlForward *fwd);
  QlInstrument* DLLEXPORT qlForwardAsInstrument(QlForward *fwd);
  double DLLEXPORT qlForwardForwardValue(QlForward* o, char **e);
  InterestRate* DLLEXPORT qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, char **e);
  int DLLEXPORT qlForwardSettlementDate(QlForward* o, char **e);
  double DLLEXPORT qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double DLLEXPORT qlForwardSpotValue(QlForward* o, char **e);
  void DLLEXPORT qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd);
  QlForward* DLLEXPORT qlForwardRateAgreementAsForward(QlForwardRateAgreement *fwd);
  QlForwardRateAgreement* DLLEXPORT qlForwardRateAgreement(int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlIborIndex* index, QlYieldTermStructure* discountCurve, char **e);

  /* coupon pricer */
  QlFloatingRateCouponPricer *DLLEXPORT qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e);
  void DLLEXPORT qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);

  /* volatility */
  QlOptionletVolatilityStructure *DLLEXPORT qlConstantOptionletVol(
    unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e);
  void DLLEXPORT qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p);

  /* swap */
  void DLLEXPORT qlFreeSwap(QlSwap *o);
  QlInstrument* DLLEXPORT qlSwapAsInstrument(QlSwap *o);
  void DLLEXPORT qlFreeVanillaSwap(QlVanillaSwap *o);
  QlSwap* DLLEXPORT qlVanillaSwapAsSwap(QlVanillaSwap *o);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
