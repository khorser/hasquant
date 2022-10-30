#include <ql/time/schedule.hpp>
#include <ql/time/period.hpp>
#include <ql/utilities/dataparsers.hpp>
#include <ql/time/daycounters/all.hpp>

#include "qlaux.h"
#include "qlSchedule.h"

using namespace QuantLib;

Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv,
  char **e) {
  try {
    std::vector<Date> d;
    for (unsigned i = 0; i < len; ++i)
      d.push_back(Date(dates[i]));
    return alloc(new Schedule(d, *arg(cal), (BusinessDayConvention) conv));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

Schedule *qlSchedule(int eff, int term, int l, int u, Calendar *cal,
    int conv, int termConv, int rule, int eom, int first, int nextToLast,
    char **e) {
  try {
    return alloc(new Schedule(qlNullableDate(eff),
			    Date(term),
			    Period(l, (TimeUnit)u),
			    *arg(cal),
			    (BusinessDayConvention) conv,
			    (BusinessDayConvention) termConv,
			    (DateGeneration::Rule) rule,
			    eom,
			    qlNullableDate(first),
			    qlNullableDate(nextToLast)));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

Schedule *qlScheduleUntil(Schedule *sched, int date, char **e) {
  try {
    return alloc(new Schedule(arg(sched)->until(Date(date))));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

void qlScheduleDates(Schedule *sched, unsigned *count, int **days) {
  const std::vector<Date> &dates = arg(sched)->dates();
  *count = dates.size();
  *days = qlAllocateInts(*count);
  for (size_t i = 0; i < dates.size(); ++i)
    (*days)[i] = dates[i].serialNumber();
}

void qlFreeSchedule(Schedule *s) {
  del(s);
}

int qlPeriodFromFrequency1(int freq, int *u, char **e) {
  try {
    Period p((Frequency) freq);
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodToFrequency1(int l, int u, char **e) {
  try {
    return Period(l, (TimeUnit)u).frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodParserParse1(char* str, int* u, char **e) {
  try {
    const Period &p = (PeriodParser::parse(std::string(arg(str))));
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodAdd1(int n1, int u1, int n2, int u2, int *u, char **e) {
  try {
    Period p = Period(n1, (TimeUnit)u1) + Period(n2, (TimeUnit)u2);
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodDivide1(int n1, int u1, int n, int *u, char **e) {
  try {
    Period p = Period(n1, (TimeUnit)u1)/n;
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodNormalize1(int n1, int u1, int *u, char **e) {
  try {
    Period p(n1, (TimeUnit)u1);
    p.normalize();
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodsLT1(int n1, int u1, int n2, int u2, char **e) {
  try {
    Period p1(n1, (TimeUnit)u1);
    Period p2(n2, (TimeUnit)u2);
    return p1 < p2;
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

typedef DayCounter *(*makeDayCounter)(int convention);

// must match with the order of qlEnumObjects.h:DayCounterType
static const makeDayCounter dayCounters[] = {
  [](int) { return static_cast<DayCounter *>(new Actual360()); }
  , [](int) { return static_cast<DayCounter *>(new Actual364()); }
  , [](int conv) { return static_cast<DayCounter *>(new Actual365Fixed((Actual365Fixed::Convention) conv)); }
  , [](int conv) { return static_cast<DayCounter *>(new ActualActual((ActualActual::Convention) conv)); }
  , [](int) { return static_cast<DayCounter *>(new OneDayCounter()); }
  , [](int) { return static_cast<DayCounter *>(new SimpleDayCounter()); }
  , [](int conv) { return static_cast<DayCounter *>(new Thirty360((Thirty360::Convention) conv)); }
  , [](int) { return static_cast<DayCounter *>(new Thirty365()); }
};

DayCounter *qlDayCounter(int type, int convention, char **e) {
  try {
    if (type < 0 || type >= (int)LENGTH(dayCounters))
      QL_FAIL("Invalid DayCounter type " << type);
    return alloc(dayCounters[type](convention));
  } catch (std::exception& er) {
    return handleException<DayCounter *>(e, er);
  }
}

DayCounter *qlDayCounterBusiness252(Calendar *cal, char **e) {
  try {
    return alloc(new Business252(*arg(cal)));
  } catch (std::exception& er) {
    return handleException<DayCounter *>(e, er);
  }
}

void  qlFreeDayCounter(DayCounter *counter) {
  del(counter);
}

const char *qlDayCounterName(DayCounter *counter) {
  std::string name = arg(counter)->name();
  return DUP(name.c_str());
}

// generated code
int qlDayCounterDayCount(DayCounter* o, int x0, int x1) {
    return arg(o)->dayCount(Date(x0), Date(x1));
}
double qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e) {
  try {
    return arg(o)->yearFraction(Date(x0), Date(x1), qlNullableDate(refPeriodStart), qlNullableDate(refPeriodEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
