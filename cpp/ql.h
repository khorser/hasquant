#include "qlaux.h"

/* dates are passed as int = serial number o the date.
 * the code assumes that Haskell bindings validate date */ 

extern "C" {
  /* utilities */
  const char *qlVersion();
  const char *boostVersion();

  void qlFreeString(char *p);
  int *qlAllocateInts(int size);
  void qlFreeInts(int *p);

  /* date */
  int qlMinDateSerialNumber();
  int qlMaxDateSerialNumber();
  int qlMinYear();
  int qlMinMonth();
  int qlMinDay();

#ifdef quantlib_cash_flow_hpp
  /* leg */
  Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int qlLegStartDate(Leg *leg, char **e);

  void qlFreeLeg(Leg *leg);
#endif

  /* calendar */
  Calendar *qlCalendar(const char *name, char **e);
  const char *qlCalendarName(Calendar *calendar);
  int qlCalendarAdjust(Calendar *c, int date, int conv);
  int qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);

  void qlFreeCalendar(Calendar *calendar);

  /* settings */
  int qlSettingsEvaluationDate();
  int qlSettingsEnforceTodaysHistoricFixings();
  void qlSettingsSetEvaluationDate(int x, char **e);
  void qlSettingsSetEnforceTodaysHistoricFixings(int x, char **e);

  /* bond */
#ifdef quantlib_cash_flow_hpp
  Bond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate,
    Leg *coupons, char **e);
  Bond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e);
#endif
  int qlBondMaturityDate(Bond *bond);
  int qlBondIssueDate(Bond *bond);
  Instrument *qlBondAsInstrument(Bond *bond);

  Bond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule,
    unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal,
    char **e);
  Bond *qlFixedRateBond1(unsigned settlDays, Calendar *cpnCal, double face,
    int start, int maturity, Period *tenor, unsigned cLen, double *coupons,
    DayCounter *dayCounter, int accrConv, int paymentConv, double redemption,
    int issue, int stub, int rule, int eom, Calendar *payCal, char **e);
  Bond *qlFixedRateBond2(unsigned settlDays, double face, Schedule *sched,
    unsigned cLen, InterestRate **coupons, int paymentConv, double redemption,
    int issue, Calendar *cal, char **e);
  int qlFixedBondFrequency(Bond *bond);
  Bond *qlZeroCouponBond(int settlDays, Calendar *cal, double face,
    int maturity, int payConv, double redemption, int issue, char **e);

  void qlFreeBond(Bond *bond);

  /* daycounter */
  DayCounter *qlDayCounter(const char *name, char **e);
  const char *qlDayCounterName(DayCounter *counter);

  void qlFreeDayCounter(DayCounter *counter);

  /* currency */
  Currency *qlCurrency(const char *name, char **e);
  const char *qlCurrencyName(Currency *currency);

  void qlFreeCurrency(Currency *currency);

  /* period */
  Period *qlPeriod(int n, int u, char **e);
  Period *qlPeriodFromFrequency(int freq, char **e);
  int qlPeriodToFrequency(Period *period, char **e);

  void qlFreePeriod(Period *period);

  /* quote */
  QlQuote *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(QlQuote *quote, char **e);

  void qlFreeQuote(QlQuote *quote);

  /* schedule */
  Schedule *qlSchedule(int eff, int term, Period *tenor, Calendar *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv, char **e);
  Schedule *qlScheduleUntil(Schedule *sched, int date, char **e);
  int *qlScheduleDates(Schedule *sched, int *count);

  void qlFreeSchedule(Schedule *s);

  /* interest rate */
  InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq, char **e);

  void qlFreeInterestRate(InterestRate *rate);

  /* enumerations */
  int *qlEnumerationValue(const char *name, int *c);

#ifdef quantlib_ratehelpers_hpp
  /* yield term structure */
  QlRateHelper *qlDepositRateHelper(QlQuote *quote, Period *period,
    unsigned fixDays, Calendar *calendar, int conv, int eom,
    DayCounter *dayCount, char **e);
  QlRateHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays,
    double face, Schedule *sched, unsigned cLen, double *coupons,
    DayCounter *dayCount, int conv, double redemption, int issue, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen,
    QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, double accuracy, char *trait,
    char *interpolator, char **e);

  void qlFreeRateHelper(QlRateHelper *helper);
#endif
  void qlFreeYieldTermStructure(QlYieldTermStructure *ts);
  double qlYieldTSDiscount(QlYieldTermStructure *ts, int date, int extrapolate, char **e);

  /* pricing engine */
  QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, char **e);

  void qlFreePricingEngine(QlPricingEngine *engine);

  /* instrument */
  void qlInstrumentSetPricingEngine(Instrument *instr, QlPricingEngine eng, char **e);
  double qlInstrumentNPV(Instrument *instr, char **e);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
