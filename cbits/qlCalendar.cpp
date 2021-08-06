#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>

#include "qlaux.h"
#include "qlCalendar.h"

using namespace QuantLib;

// extended version of EnumObjectInfo1
// I could have stored a closure instead of int (lambda or an extra object) but this seems overkill here
// for an alternative solution see qlDayCounter.cpp
struct CalendarObjectInfo {
  const char *name;
  Calendar *(*make)(int x);
  int market;

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {}
    bool operator()(const CalendarObjectInfo &i) {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };

  template <class A>
  static Calendar *makeObject(int x1) {
    return new A((typename A::Market) x1);
  }

  template <class A>
  static Calendar *makeDefaultObject(int) { //ignoring the argument
    return new A();
  }
};

typedef CalendarObjectInfo CalendarInfo;
static const CalendarInfo calendarInfo[] = {
  {"NullCalendar",                &CalendarInfo::makeDefaultObject<NullCalendar>, 0},
  {"TARGET",                      &CalendarInfo::makeDefaultObject<TARGET>, 0},
  {"Argentina::Merval",           &CalendarInfo::makeObject<Argentina>, Argentina::Merval},
  {"Australia",                   &CalendarInfo::makeDefaultObject<Australia>, 0},
  {"Brazil::Settlement",          &CalendarInfo::makeObject<Brazil>, Brazil::Settlement},
  {"Brazil::Exchange",            &CalendarInfo::makeObject<Brazil>, Brazil::Exchange},
  {"Canada::Settlement",          &CalendarInfo::makeObject<Canada>, Canada::Settlement},
  {"Canada::TSX",                 &CalendarInfo::makeObject<Canada>, Canada::TSX},
  {"China",                       &CalendarInfo::makeDefaultObject<China>, 0},
  {"CzechRepublic::PSE",          &CalendarInfo::makeObject<CzechRepublic>, CzechRepublic::PSE},
  {"Denmark",                     &CalendarInfo::makeDefaultObject<Denmark>, 0},
  {"Finland",                     &CalendarInfo::makeDefaultObject<Finland>, 0},
  {"Germany::Eurex",              &CalendarInfo::makeObject<Germany>, Germany::Eurex},
  {"Germany::FrankfurtStockExchange", &CalendarInfo::makeObject<Germany>, Germany::FrankfurtStockExchange},
  {"Germany::Settlement",         &CalendarInfo::makeObject<Germany>, Germany::Settlement},
  {"Germany::Xetra",              &CalendarInfo::makeObject<Germany>, Germany::Xetra},
  {"HongKong::HKEx",              &CalendarInfo::makeObject<HongKong>, HongKong::HKEx},
  {"Hungary",                     &CalendarInfo::makeDefaultObject<Hungary>, 0},
  {"Iceland::ICEX",               &CalendarInfo::makeObject<Iceland>, Iceland::ICEX},
  {"India::NSE",                  &CalendarInfo::makeObject<India>, India::NSE},
  {"Indonesia::BEJ",              &CalendarInfo::makeObject<Indonesia>, Indonesia::BEJ},
  {"Indonesia::JSX",              &CalendarInfo::makeObject<Indonesia>, Indonesia::JSX},
  {"Indonesia::IDX",              &CalendarInfo::makeObject<Indonesia>, Indonesia::IDX},
  {"Italy::Exchange",             &CalendarInfo::makeObject<Italy>, Italy::Exchange},
  {"Italy::Settlement",           &CalendarInfo::makeObject<Italy>, Italy::Settlement},
  {"Japan",                       &CalendarInfo::makeDefaultObject<Japan>, 0},
  {"Mexico::BMV",                 &CalendarInfo::makeObject<Mexico>, Mexico::BMV},
  {"NewZealand",                  &CalendarInfo::makeDefaultObject<NewZealand>, 0},
  {"Norway",                      &CalendarInfo::makeDefaultObject<Norway>, 0},
  {"Poland",                      &CalendarInfo::makeDefaultObject<Poland>, 0},
  {"Russia",                      &CalendarInfo::makeDefaultObject<Russia>, 0},
  {"SaudiArabia::Tadawul",        &CalendarInfo::makeObject<SaudiArabia>, SaudiArabia::Tadawul},
  {"Singapore::SGX",              &CalendarInfo::makeObject<Singapore>, Singapore::SGX},
  {"Slovakia::BSSE",              &CalendarInfo::makeObject<Slovakia>, Slovakia::BSSE},
  {"SouthAfrica",                 &CalendarInfo::makeDefaultObject<SouthAfrica>, 0},
  {"SouthKorea::KRX",             &CalendarInfo::makeObject<SouthKorea>, SouthKorea::KRX},
  {"SouthKorea::Settlement",      &CalendarInfo::makeObject<SouthKorea>, SouthKorea::Settlement},
  {"Sweden",                      &CalendarInfo::makeDefaultObject<Sweden>, 0},
  {"Switzerland",                 &CalendarInfo::makeDefaultObject<Switzerland>, 0},
  {"Taiwan::TSEC",                &CalendarInfo::makeObject<Taiwan>, Taiwan::TSEC},
  {"Turkey",                      &CalendarInfo::makeDefaultObject<Turkey>, 0},
  {"Ukraine::USE",                &CalendarInfo::makeObject<Ukraine>, Ukraine::USE},
  {"UnitedKingdom::Exchange",     &CalendarInfo::makeObject<UnitedKingdom>, UnitedKingdom::Exchange},
  {"UnitedKingdom::Metals",       &CalendarInfo::makeObject<UnitedKingdom>, UnitedKingdom::Metals},
  {"UnitedKingdom::Settlement",   &CalendarInfo::makeObject<UnitedKingdom>, UnitedKingdom::Settlement},
  {"UnitedStates::GovernmentBond",&CalendarInfo::makeObject<UnitedStates>, UnitedStates::GovernmentBond},
  {"UnitedStates::NERC",          &CalendarInfo::makeObject<UnitedStates>, UnitedStates::NERC},
  {"UnitedStates::NYSE",          &CalendarInfo::makeObject<UnitedStates>, UnitedStates::NYSE},
  {"UnitedStates::Settlement",    &CalendarInfo::makeObject<UnitedStates>, UnitedStates::Settlement},
  {"WeekendsOnly",                &CalendarInfo::makeDefaultObject<WeekendsOnly>, 0},
};

Calendar *qlCalendar(const char *name, char **e) {
  try {
    const CalendarInfo *last = LAST(calendarInfo);
    const CalendarInfo *found = std::find_if(calendarInfo, last, CalendarInfo::Cmp(name));
    if (found != last)
      return alloc(found->make(found->market));
    else
      QL_FAIL("Calendar not found " << name);
  } catch (std::exception& er) {
    return handleException<Calendar *>(e, er);
  }
}

void qlFreeCalendar(Calendar *calendar) {
  del(calendar);
}

const char *qlCalendarName(Calendar *calendar) {
  std::string name = arg(calendar)->name();
  return DUP(name.c_str());
}

int qlCalendarAdjust(Calendar *c, int date, int conv) {
  return arg(c)->adjust(Date(date), (BusinessDayConvention) conv)
      .serialNumber();
}

int qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv,
  int eom) {
  return arg(c)->advance(Date(date), n, (TimeUnit) unit,
      (BusinessDayConvention) conv, eom).serialNumber();
}

// generated code
void qlCalendarAddHoliday(Calendar* o, int x0, char **e) {
  try {
    arg(o)->addHoliday(Date(x0));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

int qlCalendarAdvance1(Calendar* o, int date, int n, int u, int convention, int endOfMonth, char **e) {
  try {
    return (arg(o)->advance(Date(date), Period(n, (TimeUnit)u), (BusinessDayConvention)convention, endOfMonth)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e) {
  try {
    return arg(o)->businessDaysBetween(Date(from), Date(to), includeFirst, includeLast);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarEndOfMonth(Calendar* o, int d, char **e) {
  try {
    return (arg(o)->endOfMonth(Date(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsBusinessDay(Calendar* o, int d, char **e) {
  try {
    return arg(o)->isBusinessDay(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsEndOfMonth(Calendar* o, int d, char **e) {
  try {
    return arg(o)->isEndOfMonth(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsHoliday(Calendar* o, int d, char **e) {
  try {
    return arg(o)->isHoliday(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsWeekend(Calendar* o, int w, char **e) {
  try {
    return arg(o)->isWeekend((Weekday) w);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlCalendarRemoveHoliday(Calendar* o, int x0, char **e) {
  try {
    arg(o)->removeHoliday(Date(x0));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

Calendar* qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e) {
  BespokeCalendar *cal = 0;
  try {
    cal = new BespokeCalendar(std::string(arg(name)));
    for (unsigned i = 0; i < len; i++)
      cal->addWeekend((Weekday)weekends[i]);
    return ret(cal);
  } catch (std::exception& er) {
    return handleException(e, er, cal);
  }
}

Calendar* qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e) {
  try {
    return alloc(new JointCalendar(*arg(x_1), *arg(x0), *arg(x1), *arg(x2), (JointCalendarRule)x3));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

Calendar* qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e) {
  try {
    return alloc(new JointCalendar(*arg(x_1), *arg(x0), *arg(x1), (JointCalendarRule)x2));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

Calendar* qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e) {
  try {
    return alloc(new JointCalendar(*arg(x_1), *arg(x0), (JointCalendarRule)x1));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

//int* qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, char **e) {
//  try {
//    const std::vector<Date> dates = Calendar::holidayList(*arg(calendar), Date(from), Date(to), includeWeekEnds);
//    *len = dates.size();
//    int *days = qlAllocateInts(*len);
//    for (size_t i = 0; i < dates.size(); ++i)
//      days[i] = dates[i].serialNumber();
//    return days;
//  } catch (std::exception& er) {
//    return handleException<int*>(e, er);
//  }
//}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
