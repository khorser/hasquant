#include <ql/time/date.hpp>
#include <ql/errors.hpp>
#include <string.h>

//including because Leg and RateHelpers are actually typedefs
#include <ql/cashflow.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>

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


namespace QuantLib {
  class Quote;
  class SimpleQuote;
  class Bond;
  class FixedRateBond;
  class Period;
  class DayCounter;
  class Calendar;
  class Schedule;
  class Currency;
  class InterestRate;
  class FixedRateBondHelper;
  class DepositRateHelper;
  class YieldTermStructure;
}

using QuantLib::Quote;
using QuantLib::SimpleQuote;
using QuantLib::Bond;
using QuantLib::FixedRateBond;
using QuantLib::Period;
using QuantLib::DayCounter;
using QuantLib::Calendar;
using QuantLib::Schedule;
using QuantLib::Currency;
using QuantLib::InterestRate;
using QuantLib::Leg;
using QuantLib::RateHelper;
using QuantLib::FixedRateBondHelper;
using QuantLib::DepositRateHelper;
using QuantLib::YieldTermStructure;

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
class objClassName<FixedRateBond *> {
public:
  static const char *name() {
    return "FixedRateBond";
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
class objClassName<InterestRate *> {
public:
  static const char *name() {
    return "InterestRate";
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
class objClassName<SimpleQuote *> {
public:
  static const char *name() {
    return "SimpleQuote";
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

template <>
class objClassName<Currency *> {
public:
  static const char *name() {
    return "Currency";
  }
};

template <>
class objClassName<Leg *> {
public:
  static const char *name() {
    return "Leg";
  }
};

template <>
class objClassName<RateHelper *> {
public:
  static const char *name() {
    return "RateHelper";
  }
};

template <>
class objClassName<DepositRateHelper *> {
public:
  static const char *name() {
    return "DepositRateHelper";
  }
};

template <>
class objClassName<FixedRateBondHelper *> {
public:
  static const char *name() {
    return "FixedRateBondHelper";
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
  Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int   qlLegStartDate(Leg *leg, char **e);

  void  qlFreeLeg(Leg *leg);

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
  Bond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate,
    Leg *coupons, char **e);
  Bond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e);
  int   qlBondMaturityDate(Bond *bond);
  int   qlBondIssueDate(Bond *bond);

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

  void qlFreeBond(Bond *bond);

  /* daycounter */
  DayCounter *qlDayCounter(const char *name, char **e);
  const char *qlDayCounterName(DayCounter *counter);

  void qlFreeDayCounter(DayCounter *counter);

  /* currency */
  Currency *qlCurrency(const char *name, char **e);
  const char *qlCurrencyName(Currency *currency);

  void  qlFreeCurrency(Currency *currency);

  /* period */
  Period *qlPeriod(int n, int u, char **e);
  Period *qlPeriodFromFrequency(int freq, char **e);
  int qlPeriodToFrequency(Period *period, char **e);

  void  qlFreePeriod(Period *period);

  /* quote */
  Quote *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(Quote *quote, char **e);

  void qlFreeQuote(Quote *quote);

  /* schedule */
  Schedule *qlSchedule(int eff, int term, Period *tenor, Calendar *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv, char **e);
  Schedule *qlScheduleUntil(Schedule *sched, int date, char **e);
  int  *qlScheduleDates(Schedule *sched, int *count);

  void qlFreeSchedule(Schedule *s);

  /* interest rate */
  InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq, char **e);

  void qlFreeInterestRate(InterestRate *rate);

  /* enumerations */
  int *qlEnumerationValue(const char *name, int *c);

  /* yield term structure */
  RateHelper *qlDepositRateHelper(Quote *quote, Period *period,
    unsigned fixDays, Calendar *calendar, int conv, int eom,
    DayCounter *dayCount, char **e);
  RateHelper *qlFixedRateBondHelper(Quote *quote, unsigned settlDays,
    double face, Schedule *sched, unsigned cLen, double *coupons,
    DayCounter *dayCount, int conv, double redemption, int issue, char **e);
  YieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen,
    RateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    Quote **quotes, int *dates, double accuracy, char *interpolator,
    char *boostrap, char **e);

  void qlFreeRateHelper(RateHelper *helper);
  void qlFreeYieldTermStructure(YieldTermStructure *ts);
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
