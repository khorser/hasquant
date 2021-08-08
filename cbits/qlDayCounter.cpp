#include <ql/time/daycounters/all.hpp>

#include "qlaux.h"
#include "qlDayCounter.h"

using namespace QuantLib;

typedef DayCounter *(*makeDayCounter)(int convention);

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
