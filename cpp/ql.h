#include <ql/time/date.hpp>
#include <ql/errors.hpp>

#include <string.h>

/* dates are passed as int = serial number o the date.
 * the code assumes that Haskell bindings validate date */ 

#ifdef QLTRACK_ALLOCATIONS
/* trace pointer */
# define TP(text, p) traceval((text), (void *)(p))
# define TP2(text, str, p) traceval2((text), (str), (void *)(p))
# define DUP(p) tracedup((p))
/* trace val */
# define TV(f, v) traceval((f), (v))
# define TPP(text, p) (void)traceval((text), (void *)(p));
# define TPP2(text, str, p) (void)traceval2((text), (str), (void *)(p));

#include <iostream>

template <class T>
T traceval(const char *text, T val) {
  std::cout << std::endl << text << ": " << val << std::endl;
  return val;
}
template <class T>
T traceval2(const char *text, const char *kind, T val) {
  std::cout << std::endl << kind << "" << text << ": " << val << std::endl;
  return val;
}
char *tracedup(const char *p);
#else
# define TP(text, p) (p)
# define TP2(text, str, p) (p)
# define DUP(p) strdup((p))
# define TV(f, v) (v)
# define TPP(text, p)
# define TPP2(text, str, p)
#endif

template <class T>
T *cast(const char *msg, void *p) {
  return static_cast<T *>(TP(msg, p));
}

template <class T>
T *log(T *p, const char *msg) {
  TPP(msg, p);
  return p;
}

namespace QuantLib {
  class Quote;
  class Bond;
  class FixedRateBond;
  class Period;
  class DayCounter;
  class Calendar;
  class Schedule;
  class Currency;
}

using QuantLib::Quote;
using QuantLib::Bond;
using QuantLib::FixedRateBond;
using QuantLib::Period;
using QuantLib::DayCounter;
using QuantLib::Calendar;
using QuantLib::Schedule;
using QuantLib::Currency;

using QuantLib::Date;


template <class T>
class objClassName {
public:
  static const char *name() {
    return "Unknown";
  }
};

template <>
class objClassName<void *> {
public:
  static const char *name() {
    return "Ptr";
  }
};

template <>
class objClassName<Bond *> {
public:
  static const char *name() {
    return "Bond";
  }
};

template <>
class objClassName<DayCounter *> {
public:
  static const char *name() {
    return "DayCounter";
  }
};

template <>
class objClassName<Calendar *> {
public:
  static const char *name() {
    return "Calendar";
  }
};

template <>
class objClassName<Quote *> {
public:
  static const char *name() {
    return "Quote";
  }
};

template <>
class objClassName<Period *> {
public:
  static const char *name() {
    return "Period";
  }
};

template <>
class objClassName<Schedule *> {
public:
  static const char *name() {
    return "Schedule";
  }
};

template <class T>
T arg(T p) {
  TPP2(objClassName<T>::name(), "arg", p);
  return p;
}

template <class T>
void del(T p) {
  TPP2(objClassName<T>::name(), "freeing", p);
  delete p;
}

template <class T>
T alloc(T p) {
  TPP2(objClassName<T>::name(), "allocated", p);
  return p;
}

template <class T>
void *uncast(const char *msg, T *p) {
  return static_cast<void *>(TP(msg, p));
}

template <class T1, class T2>
T2 *upcast(const char *msg, T1 *p) {
  TPP(msg, p)
  return static_cast<T2 *>(p);
}

template <class T1, class T2>
T2 *downcast(const char *msg, void *p) {
  return dynamic_cast<T2 *>(static_cast<T1 *>(TP(msg, p)));
}

extern "C"
{
  /* utilities */
  const char *qlVersion();
  const char *boostVersion();

  void	qlFreeString(char *p);
  int  *qlAllocateInts(int size);
  void  qlFreeInts(int *p);

  /* date */
  int	qlMinDateSerialNumber();
  int	qlMaxDateSerialNumber();
  int	qlMinYear();
  int	qlMinMonth();
  int	qlMinDay();

  /* leg */
  void *qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int   qlLegStartDate(void *leg, char **e);

  void  qlFreeLeg(void *leg);

  /* calendar */
  Calendar *qlCalendar(const char *name, char **e);
  const char *qlCalendarName(Calendar *calendar);
  int	qlCalendarAdjust(Calendar *c, int date, int conv);
  int	qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);

  void  qlFreeCalendar(Calendar *calendar);

  /* settings */
  int	qlSettingsEvaluationDate();
  int	qlSettingsEnforceTodaysHistoricFixings();
  void	qlSettingsSetEvaluationDate(int x, char **e);
  void	qlSettingsSetEnforceTodaysHistoricFixings(int x, char **e);

  /* bond */
  Bond *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons, char **e);
  Bond *qlBond1(unsigned settlDays, void *calendar, double faceAmount, int maturityDate, int issueDate, void *cashFlows, char **e);
  int   qlBondMaturityDate(void *bond);
  int   qlBondIssueDate(void *bond);

  Bond *qlFixedRateBond(unsigned settlDays, double face, void *schedule,
    unsigned cLen, double *coupons, void *counter,
    int payConv, double redemption, int issue, void *payCal,
    char **e);
  Bond *qlFixedRateBond1(unsigned settlDays, void *cpnCal, double face, int start,
    int maturity, void *tenor, unsigned cLen, double *coupons, void *dayCounter,
    int accrConv, int paymentConv, double redemption, int issue, int stub,
    int rule, int eom, void *payCal, char **e);
  Bond *qlFixedRateBond2(unsigned settlDays, double face, void *sched,
    unsigned cLen, void **coupons, int paymentConv, double redemption, int issue,
    void *cal, char **e);
  int qlFixedBondFrequency(Bond *bond);

  void qlFreeBond(Bond *bond);

  /* daycounter */
  void *qlDayCounter(const char *name, char **e);
  const char *qlDayCounterName(void *counter);

  void  qlFreeDayCounter(void *counter);

  /* currency */
  Currency *qlCurrency(const char *name, char **e);
  const char *qlCurrencyName(Currency *currency);

  void  qlFreeCurrency(Currency *currency);

  /* period */
  void *qlPeriod(int n, int u, char **e);
  void *qlPeriodFromFrequency(int freq, char **e);
  int qlPeriodToFrequency(void *period, char **e);

  void  qlFreePeriod(void *period);

  /* quote */
  Quote *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(Quote *quote, char **e);

  void qlFreeQuote(Quote *quote);

  /* schedule */
  void *qlSchedule(int eff, int term, void *tenor, void *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  void *qlSchedule1(unsigned len, int *dates, void *cal, int conv, char **e);
  void *qlScheduleUntil(void *sched, int date, char **e);
  int  *qlScheduleDates(void *sched, int *count);

  void qlFreeSchedule(void *s);

  /* interest rate */
  void *qlInterestRate(double r, void *dc, int comp, int freq, char **e);

  void qlFreeInterestRate(void *rate);

  /* enumerations */
  int *qlEnumerationValue(const char *name, int *c);

  /* yield term structure */
  void qlFreeRateHelper(void *helper);
  void *qlDepositRateHelper(void *quote, void *period, unsigned fixDays,
    void *calendar, int conv, int eom, void *dayCount, char **e);
  void *qlFixedRateBondHelper(void *quote, unsigned settlDays, double face,
    void *sched, unsigned cLen, double *coupons, void *dayCount, int conv,
    double redemption, int issue, char **e);
  void *qlPiecewiseYieldCurve(int date, unsigned rateLen, void **ratehelpers,
    void *dayCount, unsigned quoteLen, void **quotes, void *dates,
    double accuracy, char *interpolator, char *boostrap, char **e);

  void qlFreeTermStructure(void *ts);
}

const Date qlNullableDate(int serialNumber);
int qlNullableDate(const Date &date);

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

template <class T>
T handleException2(char **msg, std::exception &e)
{
  *msg = DUP(e.what());
  return 0;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
