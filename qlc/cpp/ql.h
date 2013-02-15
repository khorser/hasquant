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
  void DLLEXPORT qlFreeDoubles(double *p);

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
  int DLLEXPORT qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double DLLEXPORT qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, char **e);
  double DLLEXPORT qlCashFlowsBasisPointValue1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBps2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsConvexity1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsDuration1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int DLLEXPORT qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsMaturityDate(Leg* leg, char **e);
  double DLLEXPORT qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double DLLEXPORT qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsNpv2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  void DLLEXPORT qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, char **e);
  double DLLEXPORT qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  int DLLEXPORT qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double DLLEXPORT qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double DLLEXPORT qlCashFlowsYieldValueBasisPoint1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsZSpread1(Leg* leg, QlYieldTermStructure* d, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double DLLEXPORT qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);
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
  Calendar* DLLEXPORT qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e);
  Calendar* DLLEXPORT qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e);
  Calendar* DLLEXPORT qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e);

  int* DLLEXPORT qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, char **e);
  void DLLEXPORT qlFreeCalendar(Calendar *calendar);

  /* settings */
  int DLLEXPORT qlSettingsEvaluationDate();
  int DLLEXPORT qlSettingsEnforceTodaysHistoricFixings();
  void DLLEXPORT qlSettingsSetEvaluationDate(int x, char **e);
  void DLLEXPORT qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int DLLEXPORT qlSettingsIncludeTodaysCashFlows();
  void DLLEXPORT qlSettingsSetIncludeTodaysCashFlows(int x);
  void DLLEXPORT qlSettingsAnchorEvaluationDate();
  int DLLEXPORT qlSettingsIncludeReferenceDateCashFlows();
  int DLLEXPORT qlSettingsIncludeReferenceDateEvents();
  void DLLEXPORT qlSettingsResetEvaluationDate(char **e);
  void DLLEXPORT qlSettingsSetIncludeReferenceDateCashFlows(int x0);
  void DLLEXPORT qlSettingsSetIncludeReferenceDateEvents(int x0);

  /* bond */
#ifdef quantlib_cash_flow_hpp
  QlBond *DLLEXPORT qlBond(unsigned settlDays, Calendar *calendar, int issueDate,
    Leg *coupons, char **e);
  QlBond *DLLEXPORT qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e);
  Leg* DLLEXPORT qlBondCashflows(QlBond* o, char **e);
  Leg* DLLEXPORT qlBondRedemptions(QlBond* o, char **e);
  int DLLEXPORT qlBondSettlementDate(QlBond* o, int d, char **e);
  int DLLEXPORT qlBondStartDate(QlBond* o, char **e);
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
  QlBond* DLLEXPORT qlFloatingRateBond1(unsigned settlementDays, double faceAmount, int startDate, int maturityDate, int couponFrequency, Calendar* calendar, QlIborIndex* iborIndex, DayCounter* accrualDayCounter, int accrualConvention, int paymentConvention, unsigned fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, double redemption, int issueDate, int stubDate, int rule, int endOfMonth, char **e);

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
  double* DLLEXPORT qlBondNotionals(QlBond* o, unsigned *len, char **e);

  int DLLEXPORT qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double cleanPrice, char **e);
  double DLLEXPORT qlBondFunctionsBasisPointValue1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBps2(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsConvexity1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsDuration1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, char **e);
  double DLLEXPORT qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, char **e);
  int DLLEXPORT qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsYield2(QlBond* bond, double cleanPrice, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double DLLEXPORT qlBondFunctionsYieldValueBasisPoint1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsZSpread(QlBond* bond, double cleanPrice, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);

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
  int *DLLEXPORT qlScheduleDates(Schedule *sched, unsigned *count);

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
  int *DLLEXPORT qlEnumerationValue(const char *name, unsigned *c);

#ifdef quantlib_ratehelpers_hpp
  /* yield term structure */
  QlRateHelper *DLLEXPORT qlDepositRateHelper(QlQuote *quote, Period *period,
    unsigned fixDays, Calendar *calendar, int conv, int eom,
    DayCounter *dayCount, char **e);
  QlBondHelper *DLLEXPORT qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays,
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
  QlSwapRateHelper *DLLEXPORT qlSwapRateHelper1(QlQuote *q, Period *t, Calendar *cal, int freq,
    int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, Period *fwdStart,
    QlYieldTermStructure *ts, char **e);
  void DLLEXPORT qlFreeSwapRateHelper(QlSwapRateHelper *o);
  QlRateHelper* DLLEXPORT qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o);

  void DLLEXPORT qlFreeBondHelper(QlBondHelper *o);
  QlRateHelper* DLLEXPORT qlBondHelperAsRateHelper(QlBondHelper *o);

  void DLLEXPORT qlFreeRateHelper(QlRateHelper *helper);
  QlRateHelper* DLLEXPORT qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);
  
  void DLLEXPORT qlFreeOISRateHelper(QlOISRateHelper *o);
  QlRateHelper* DLLEXPORT qlOISRateHelperAsRateHelper(QlOISRateHelper *o);
  QlBondHelper* DLLEXPORT qlBondHelper(QlQuote* cleanPrice, QlBond* bond, char **e);
  QlOISRateHelper* DLLEXPORT qlOISRateHelper(unsigned settlementDays, Period* tenor, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e);
  QlSwapRateHelper* DLLEXPORT qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, Period* fwdStart, QlYieldTermStructure* discountingCurve, char **e);
  QlRateHelper* DLLEXPORT qlBMASwapRateHelper(QlQuote* liborFraction, Period* tenor, unsigned settlementDays, Calendar* calendar, Period* bmaPeriod, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e);
  QlRateHelper* DLLEXPORT qlDatedOISRateHelper(int startDate, int endDate, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e);
  QlRateHelper* DLLEXPORT qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e);
  QlRateHelper* DLLEXPORT qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, char **e);
  QlRateHelper* DLLEXPORT qlFraRateHelper2(QlQuote* rate, Period* periodToStart, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);
  QlRateHelper* DLLEXPORT qlFraRateHelper3(QlQuote* rate, Period* periodToStart, QlIborIndex* iborIndex, char **e);
  QlRateHelper* DLLEXPORT qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* DLLEXPORT qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* DLLEXPORT qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e);
  double DLLEXPORT qlRateHelperImpliedQuote(QlRateHelper* o, char **e);
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

  QlYieldTermStructure *DLLEXPORT qlInterpolatedDiscountCurve(unsigned dfsLen,
    double *dfs, int *dfsDates, DayCounter *dayCount, Calendar *cal,
    unsigned quoteLen, QlQuote **quotes, int *dates, char *interpolator, char **e);
  QlYieldTermStructure *DLLEXPORT qlInterpolatedForwardCurve(unsigned fwdLen,
    double *fwds, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *interpolator, char **e);
  QlYieldTermStructure *DLLEXPORT qlInterpolatedZeroCurve(unsigned yieldLen,
    double *yields, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *interpolator, char **e);
#ifdef quantlib_fitted_bond_discount_curve_hpp
  void DLLEXPORT qlFreeFittedBondDiscountCurveFittingMethod(QuantLib::FittedBondDiscountCurve::FittingMethod *o);
  QuantLib::FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlCubicBSplinesFitting(unsigned knotVectorLen, double * knotVector, int constrainAtZero, char **e);
  QuantLib::FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlExponentialSplinesFitting(int constrainAtZero, char **e);
  QuantLib::FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlNelsonSiegelFitting(char **e);
  QuantLib::FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, char **e);
  QuantLib::FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlSvenssonFitting(char **e);
  QlFittedBondDiscountCurve* DLLEXPORT qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, char **e);
  QlFittedBondDiscountCurve* DLLEXPORT qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, char **e);

  void DLLEXPORT qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o);
  QlYieldTermStructure* DLLEXPORT qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o);

  double DLLEXPORT qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve* o, char **e);
  int DLLEXPORT qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve* o, char **e);
#endif
  QlYieldTermStructure* DLLEXPORT qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e);
  QlYieldTermStructure* DLLEXPORT qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, DayCounter* dc, char **e);

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

  void DLLEXPORT qlFreeBMAIndex(QlBMAIndex *o);
  QlInterestRateIndex* DLLEXPORT qlBMAIndexAsInterestRateIndex(QlBMAIndex *o);
  void DLLEXPORT qlFreeOvernightIndexedSwapIndex(QlOvernightIndexedSwapIndex *o);
  QlSwapIndex* DLLEXPORT qlOvernightIndexedSwapIndexAsSwapIndex(QlOvernightIndexedSwapIndex *o);
  QlBMAIndex* DLLEXPORT qlBMAIndex(QlYieldTermStructure* h, char **e);

  QlSwapIndex* DLLEXPORT qlCreateLiborSwapIndex(char *name, Period* tenor, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e);
  QlOvernightIndexedSwapIndex* DLLEXPORT qlOvernightIndexedSwapIndex(char* familyName, Period* tenor, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, char **e);
  QlSwapIndex* DLLEXPORT qlSwapIndex1(char* familyName, Period* tenor, unsigned settlementDays, Currency* currency, Calendar* calendar, Period* fixedLegTenor, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, QlYieldTermStructure* discountingTermStructure, char **e);
  QlSwapIndex* DLLEXPORT qlSwapIndex(char* familyName, Period* tenor, unsigned settlementDays, Currency* currency, Calendar* calendar, Period* fixedLegTenor, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, char **e);

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

  InterestRate* DLLEXPORT qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, char **e);
  int DLLEXPORT qlForwardRateAgreementIsExpired(QlForwardRateAgreement* o, char **e);

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
  void DLLEXPORT qlFreeBMASwap(QlBMASwap *o);
  QlSwap* DLLEXPORT qlBMASwapAsSwap(QlBMASwap *o);
  void DLLEXPORT qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o);
  QlSwap* DLLEXPORT qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o);
  void DLLEXPORT qlFreeAssetSwap(QlAssetSwap *o);
  QlSwap* DLLEXPORT qlAssetSwapAsSwap(QlAssetSwap *o);
  QlOvernightIndexedSwap* DLLEXPORT qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e);
  QlOvernightIndexedSwap* DLLEXPORT qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e);
#ifdef quantlib_cash_flow_hpp
  QlSwap* DLLEXPORT qlSwap1(unsigned legsLen, Leg** legs, int *payer, char **e);
#endif
  QlAssetSwap* DLLEXPORT qlAssetSwap1(int parAssetSwap, QlBond* bond, double bondCleanPrice, double nonParRepayment, double gearing, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int dealMaturity, int payBondCoupon, char **e);
  QlAssetSwap* DLLEXPORT qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, char **e);
  QlBMASwap* DLLEXPORT qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, char **e);
  QlVanillaSwap* DLLEXPORT qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, char **e);
#ifdef quantlib_cash_flow_hpp
  QlSwap* DLLEXPORT qlSwap(Leg* firstLeg, Leg* secondLeg, char **e);
  Leg* DLLEXPORT qlSwapLeg(QlSwap* o, unsigned j, char **e);
  Leg* DLLEXPORT qlVanillaSwapFixedLeg(QlVanillaSwap* o, char **e);
  Leg* DLLEXPORT qlVanillaSwapFloatingLeg(QlVanillaSwap* o, char **e);
  Leg* DLLEXPORT qlAssetSwapBondLeg(QlAssetSwap* o, char **e);
  Leg* DLLEXPORT qlAssetSwapFloatingLeg(QlAssetSwap* o, char **e);
  Leg* DLLEXPORT qlBMASwapBmaLeg(QlBMASwap* o, char **e);
  Leg* DLLEXPORT qlBMASwapLiborLeg(QlBMASwap* o, char **e);
  Leg* DLLEXPORT qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, char **e);
  Leg* DLLEXPORT qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, char **e);
#endif
  double DLLEXPORT qlAssetSwapCleanPrice(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFairCleanPrice(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFairNonParRepayment(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFairSpread(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFloatingLegBPS(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFloatingLegNPV(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapNonParRepayment(QlAssetSwap* o, char **e);
  int DLLEXPORT qlAssetSwapParSwap(QlAssetSwap* o, char **e);
  int DLLEXPORT qlAssetSwapPayBondCoupon(QlAssetSwap* o, char **e);
  double DLLEXPORT qlBMASwapBmaLegBPS(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapBmaLegNPV(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapFairLiborFraction(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapFairLiborSpread(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapLiborFraction(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapLiborLegBPS(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapLiborLegNPV(QlBMASwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlSwapEndDiscounts(QlSwap* o, unsigned j, char **e);
  double DLLEXPORT qlSwapLegBPS(QlSwap* o, unsigned j, char **e);
  double DLLEXPORT qlSwapLegNPV(QlSwap* o, unsigned j, char **e);
  int DLLEXPORT qlSwapMaturityDate(QlSwap* o, char **e);
  double DLLEXPORT qlSwapNpvDateDiscount(QlSwap* o, char **e);
  int DLLEXPORT qlSwapStartDate(QlSwap* o, char **e);
  double DLLEXPORT qlSwapStartDiscounts(QlSwap* o, unsigned j, char **e);
  double DLLEXPORT qlVanillaSwapFairRate(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFairSpread(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFixedLegBPS(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFixedLegNPV(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFloatingLegBPS(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFloatingLegNPV(QlVanillaSwap* o, char **e);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
