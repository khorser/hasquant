#include <ql/time/date.hpp>
#include <ql/errors.hpp>

#include <string.h>
#include <stdio.h>

/* dates are passed as int = serial number o the date.
 * the code assumes that Haskell bindings validate date */ 

extern "C"
{
  /* utilities */
  const char *qlVersion();
  const char *boostVersion();
      /* internal */
  void	qlFreeString(char *p);

  /* date */
      /* internal */
  int	qlMinDateSerialNumber();
  int	qlMaxDateSerialNumber();
  int	qlMinYear();
  int	qlMinMonth();
  int	qlMinDay();

  /* leg */
  void *qlLeg(int len, double *amounts, int *dates, char **e);
  int   qlLegStartDate(void *leg, char **e);
      /* internal */
  void  qlFreeLeg(void *leg);

  /* calendar */
  void *qlCalendar(const char *name, char **e);
  const char *qlCalendarName(void *calendar);
  int	qlCalendarAdjust(void *c, int date, int conv);
  int	qlCalendarAdvance(void *c, int date, int n, int unit, int conv, int eom);
      /* internal */
  void  qlFreeCalendar(void *calendar);

  /* settings */
  int	qlSettingsEvaluationDate();
  void	qlSettingsSetEvaluationDate(int x);
  void	qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int	qlSettingsEnforceTodaysHistoricFixings();

  /* bond */
  void *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons, char **e);
  void *qlBond2(unsigned settlDays, void *calendar, double faceAmount, int maturityDate, int issueDate, void *cashFlows, char **e);
  int   qlBondMaturityDate(void *bond);
  int   qlBondIssueDate(void *bond);
      /* internal */
  void qlFreeBond(void *bond);

  /* daycounter */
  void *qlDayCounter(const char *name, char **e);
  const char *qlDayCounterName(void *counter);
      /* internal */
  void  qlFreeDayCounter(void *counter);

  /* businessdayconvention */
    /* enumeration */
  int qlBusinessDayConventionFollowing();
  int qlBusinessDayConventionModifiedFollowing();
  int qlBusinessDayConventionPreceding();
  int qlBusinessDayConventionModifiedPreceding();
  int qlBusinessDayConventionUnadjusted();

  /* dategenerationrule */
    /* enumeration */
  int qlDateGenerationRuleBackward();
  int qlDateGenerationRuleForward();
  int qlDateGenerationRuleZero();
  int qlDateGenerationRuleThirdWednesday();
  int qlDateGenerationRuleTwentieth();
  int qlDateGenerationRuleTwentiethIMM();
  int qlDateGenerationRuleOldCDS();
  int qlDateGenerationRuleCDS();

  /* timeunit */
    /* enumeration */
  int qlTimeUnitMonths();
  int qlTimeUnitDays();
  int qlTimeUnitWeeks();
  int qlTimeUnitYears();

  /* frequency */
    /* enumeration */
  int qlFrequencyFrequency();
  int qlFrequencyNoFrequency();
  int qlFrequencyAnnual();
  int qlFrequencySemiannual();
  int qlFrequencyEveryFourthMonth();
  int qlFrequencyQuarterly();
  int qlFrequencyBimonthly();
  int qlFrequencyMonthly();
  int qlFrequencyBiweekly();
  int qlFrequencyEveryFourthWeek();
  int qlFrequencyWeekly();
  int qlFrequencyDaily();
  int qlFrequencyOnce();
  int qlFrequencyOtherFrequency();

  /* currency */
  void *qlCurrency(const char *name, char **e);
  const char *qlCurrencyName(void *currency);
      /* internal */
  void  qlFreeCurrency(void *currency);

  /* period */
  void *qlPeriod(int n, int u, char **e);
  void *qlPeriodFromFrequency(int freq, char **e);
  int qlPeriodToFrequency(void *period, char **e);
      /* internal */
  void  qlFreePeriod(void *period);

  /* quote */
  void *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(void *quote, char **e);
      /* internal */
  void qlFreeQuote(void *quote);

  /* schedule */
  void *qlSchedule(int len, int *dates, void *cal, int conv, char **e);
  void *qlSchedule2(int eff, int term, void *tenor, void *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  void *qlScheduleUntil(void *sched, int date, char **e);
      /* internal */
  void qlFreeSchedule(void *s);
}

const QuantLib::Date qlNullableDate(int serialNumber);
int qlNullableDate(const QuantLib::Date &date);

/* some useful helpers ... well ... I hope they are... */
  template <class T>
T *handleException(char **msg, std::exception &e, T *t)
{
  *msg = strdup(e.what());
  //printf("Duplicated exception message to a string %p", *msg);
  if (t)
    delete t;
  return 0;
}

  template <class T>
T handleException(char **msg, std::exception &e)
{
  *msg = strdup(e.what());
  //printf("Duplicated exception message to a string %p", *msg);
  return 0;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
