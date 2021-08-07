#include <ql/time/daycounters/all.hpp>

#include "qlaux.h"
#include "qlDayCounter.h"

using namespace QuantLib;

// for an alternative approach see qlCalendar.cpp
template <class T, typename T::Convention conv>
DayCounter *makeDayCounter() {
  return new T(conv);
}

template <class T>
struct EnumObjectInfo {
  const char *const name;
  T *(* const make)();

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {}
    bool operator()(const EnumObjectInfo<T> &i) {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };

  template <class A>
  static T *makeObject() {
    return new A();
  }
};

typedef EnumObjectInfo<DayCounter> DayCounterInfo;
static const DayCounterInfo dayCounterInfo[] = {
  {"Actual/365 (Fixed)", &DayCounterInfo::makeObject<Actual365Fixed>},

  {"1/1", &DayCounterInfo::makeObject<OneDayCounter>},

  {"Actual/Actual (ISMA)", &makeDayCounter<ActualActual, ActualActual::ISMA>},
  {"Actual/Actual (Bond)", &makeDayCounter<ActualActual, ActualActual::Bond>},
  {"Actual/Actual (ISDA)", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"Actual/Actual (Historical)", &makeDayCounter<ActualActual, ActualActual::Historical>},
  {"Actual/Actual (Actual365)", &makeDayCounter<ActualActual, ActualActual::Actual365>},
  {"Actual/Actual (AFB)", &makeDayCounter<ActualActual, ActualActual::AFB>},
  {"Actual/Actual (Euro)", &makeDayCounter<ActualActual, ActualActual::Euro>},

  {"Actual/360", &DayCounterInfo::makeObject<Actual360>},

  {"30/360 (USA)", &makeDayCounter<Thirty360, Thirty360::USA>},
  {"30/360 (Bond Basis)", &makeDayCounter<Thirty360, Thirty360::BondBasis>},
  {"30/360 (European)", &makeDayCounter<Thirty360, Thirty360::European>},
  {"30/360 (Eurobond Basis)", &makeDayCounter<Thirty360, Thirty360::EurobondBasis>},
  {"30/360 (Italian)", &makeDayCounter<Thirty360, Thirty360::Italian>},

  {"Simple", &DayCounterInfo::makeObject<SimpleDayCounter>},
};

DayCounter *qlDayCounter(const char *name, char **e) {
  try {
    const DayCounterInfo *last = LAST(dayCounterInfo);
    const DayCounterInfo *found = std::find_if(dayCounterInfo, last, DayCounterInfo::Cmp(name));
    if (found != last)
      return alloc(found->make());
    else
      QL_FAIL("DayCounter not found " << name);
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
