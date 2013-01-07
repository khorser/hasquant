#include <ql/time/date.hpp>
#include <ql/errors.hpp>

#include <string.h>

/* dates are passed as int = serial number o the date.
 * the code assumes that Haskell bindings validate date */ 

#ifdef QLTRACK_ALLOCATIONS
/* trace pointer */
# define TP(text, p) traceval(__FILE__, __LINE__, (text), (void *)(p))
# define DUP(p) tracedup((p))
/* trace val */
# define TV(f, v) traceval(__FILE__, __LINE__, (f), (v))

#include <iostream>

int getThread();
template <class T>
T traceval(const char *file, int line, const char *text, T val) {
  std::cout << std::endl << getThread() << "(" << file << ":" << line
    << ")" << text << ": " << val << std::endl;
  return val;
}
char *tracedup(const char *p);
#else
# define TP(text, p) (p)
# define DUP(p) strdup((p))
# define TV(f, v) (v)
#endif

extern "C"
{
  /* utilities */
  const char *qlVersion();
  const char *boostVersion();

  void	qlFreeString(char *p);

  /* date */
  int	qlMinDateSerialNumber();
  int	qlMaxDateSerialNumber();
  int	qlMinYear();
  int	qlMinMonth();
  int	qlMinDay();

  /* leg */
  void *qlLeg(int len, double *amounts, int *dates, char **e);
  int   qlLegStartDate(void *leg, char **e);

  void  qlFreeLeg(void *leg);

  /* calendar */
  void *qlCalendar(const char *name, char **e);
  const char *qlCalendarName(void *calendar);
  int	qlCalendarAdjust(void *c, int date, int conv);
  int	qlCalendarAdvance(void *c, int date, int n, int unit, int conv, int eom);

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
  void *qlFixedRateBond(unsigned settlDays, double face, void *schedule,
    int cLen, double *coupons, void *counter,
    int payConv, double redemption, int issue, void *payCal,
    char **e);

  void qlFreeBond(void *bond);

  /* daycounter */
  void *qlDayCounter(const char *name, char **e);
  const char *qlDayCounterName(void *counter);

  void  qlFreeDayCounter(void *counter);

  /* currency */
  void *qlCurrency(const char *name, char **e);
  const char *qlCurrencyName(void *currency);

  void  qlFreeCurrency(void *currency);

  /* period */
  void *qlPeriod(int n, int u, char **e);
  void *qlPeriodFromFrequency(int freq, char **e);
  int qlPeriodToFrequency(void *period, char **e);

  void  qlFreePeriod(void *period);

  /* quote */
  void *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(void *quote, char **e);

  void qlFreeQuote(void *quote);

  /* schedule */
  void *qlSchedule(int len, int *dates, void *cal, int conv, char **e);
  void *qlSchedule2(int eff, int term, void *tenor, void *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  void *qlScheduleUntil(void *sched, int date, char **e);

  void qlFreeSchedule(void *s);

  /* enumerations */
  int *qlEnumerationValue(const char *name, int *c);
}

const QuantLib::Date qlNullableDate(int serialNumber);
int qlNullableDate(const QuantLib::Date &date);

/* some useful helpers ... well ... I hope they are... */
  template <class T>
T *handleException(char **msg, std::exception &e, T *t)
{
  *msg = DUP(e.what());
  if (t)
    delete t;
  return 0;
}

  template <class T>
T handleException(char **msg, std::exception &e)
{
  *msg = DUP(e.what());
  return 0;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
