#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

typedef EnumObjectInfo<Calendar> CalendarInfo;
static CalendarInfo calendarInfo[] = {
  {"NoCalendar", &CalendarInfo::makeObject<Calendar>},
  {"NullCalendar", &CalendarInfo::makeObject<NullCalendar>},
  {"TARGET", &CalendarInfo::makeObject<TARGET>},
  {"Argentina::Merval", &CalendarInfo::makeObject<Argentina>},
  {"Australia", &CalendarInfo::makeObject<Australia>},
  {"Brazil::Settlement", &CalendarInfo::makeObject<Brazil>},
  {"Brazil::Exchange", &CalendarInfo::makeObject<Brazil>},
  {"Canada::Settlement", &CalendarInfo::makeObject<Canada>},
  {"Canada::TSX", &CalendarInfo::makeObject<Canada>},
  {"China", &CalendarInfo::makeObject<China>},
  {"CzechRepublic::PSE", &CalendarInfo::makeObject<CzechRepublic>},
  {"Denmark", &CalendarInfo::makeObject<Denmark>},
  {"Finland", &CalendarInfo::makeObject<Finland>},
  {"Germany::Eurex", &CalendarInfo::makeObject<Germany>},
  {"Germany::FrankfurtStockExchange", &CalendarInfo::makeObject<Germany>},
  {"Germany::Settlement", &CalendarInfo::makeObject<Germany>},
  {"Germany::Xetra", &CalendarInfo::makeObject<Germany>},
  {"HongKong::HKEx", &CalendarInfo::makeObject<HongKong>},
  {"Hungary", &CalendarInfo::makeObject<Hungary>},
  {"Iceland::ICEX", &CalendarInfo::makeObject<Iceland>},
  {"India::NSE", &CalendarInfo::makeObject<India>},
  {"Indonesia::BEJ", &CalendarInfo::makeObject<Indonesia>},
  {"Indonesia::JSX", &CalendarInfo::makeObject<Indonesia>},
  {"Indonesia::IDX", &CalendarInfo::makeObject<Indonesia>},
  {"Italy::Exchange", &CalendarInfo::makeObject<Italy>},
  {"Italy::Settlement", &CalendarInfo::makeObject<Italy>},
  {"Japan", &CalendarInfo::makeObject<Japan>},
  {"Mexico::BMV", &CalendarInfo::makeObject<Mexico>},
  {"NewZealand", &CalendarInfo::makeObject<NewZealand>},
  {"Norway", &CalendarInfo::makeObject<Norway>},
  {"Poland", &CalendarInfo::makeObject<Poland>},
  {"Russia", &CalendarInfo::makeObject<Russia>},
  {"SaudiArabia::Tadawul", &CalendarInfo::makeObject<SaudiArabia>},
  {"Singapore::SGX", &CalendarInfo::makeObject<Singapore>},
  {"Slovakia::BSSE", &CalendarInfo::makeObject<Slovakia>},
  {"SouthAfrica", &CalendarInfo::makeObject<SouthAfrica>},
  {"SouthKorea::KRX", &CalendarInfo::makeObject<SouthKorea>},
  {"SouthKorea::Settlement", &CalendarInfo::makeObject<SouthKorea>},
  {"Sweden", &CalendarInfo::makeObject<Sweden>},
  {"Switzerland", &CalendarInfo::makeObject<Switzerland>},
  {"Taiwan::TSEC", &CalendarInfo::makeObject<Taiwan>},
  {"EUR", &CalendarInfo::makeObject<TARGET>},
  {"Turkey", &CalendarInfo::makeObject<Turkey>},
  {"Ukraine::USE", &CalendarInfo::makeObject<Ukraine>},
  {"UnitedKingdom::Exchange", &CalendarInfo::makeObject<UnitedKingdom>},
  {"London stock exchange", &CalendarInfo::makeObject<UnitedKingdom>},
  {"LONDON", &CalendarInfo::makeObject<UnitedKingdom>},
  {"GBP", &CalendarInfo::makeObject<UnitedKingdom>},
  {"UnitedKingdom::Metals", &CalendarInfo::makeObject<UnitedKingdom>},
  {"UnitedKingdom::Settlement", &CalendarInfo::makeObject<UnitedKingdom>},
  {"UnitedStates::GovernmentBond", &CalendarInfo::makeObject<UnitedStates>},
  {"UnitedStates::NERC", &CalendarInfo::makeObject<UnitedStates>},
  {"UnitedStates::NYSE", &CalendarInfo::makeObject<UnitedStates>},
  {"UnitedStates::Settlement", &CalendarInfo::makeObject<UnitedStates>},
  {"WeekendsOnly", &CalendarInfo::makeObject<WeekendsOnly>},
};

Calendar *qlCalendar(const char *name, char **e) {
  try {
    CalendarInfo *last = LAST(calendarInfo);
    CalendarInfo *found = std::find_if(calendarInfo, last, CalendarInfo::Cmp(name));
    if (found != last)
      return alloc(found->make());
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
    (arg(o))->addHoliday(Date(x0));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

int qlCalendarAdvance1(Calendar* o, int date, Period* period, int convention, int endOfMonth, char **e) {
  try {
    return ((arg(o))->advance(Date(date), (*arg(period)), (BusinessDayConvention)convention, endOfMonth)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e) {
  try {
    return (arg(o))->businessDaysBetween(Date(from), Date(to), includeFirst, includeLast);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarEndOfMonth(Calendar* o, int d, char **e) {
  try {
    return ((arg(o))->endOfMonth(Date(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsBusinessDay(Calendar* o, int d, char **e) {
  try {
    return (arg(o))->isBusinessDay(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsEndOfMonth(Calendar* o, int d, char **e) {
  try {
    return (arg(o))->isEndOfMonth(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsHoliday(Calendar* o, int d, char **e) {
  try {
    return (arg(o))->isHoliday(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsWeekend(Calendar* o, int w, char **e) {
  try {
    return (arg(o))->isWeekend((Weekday) w);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlCalendarRemoveHoliday(Calendar* o, int x0, char **e) {
  try {
    (arg(o))->removeHoliday(Date(x0));
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
    return alloc(new JointCalendar((*arg(x_1)), (*arg(x0)), (*arg(x1)), (*arg(x2)), (JointCalendarRule)x3));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

Calendar* qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e) {
  try {
    return alloc(new JointCalendar((*arg(x_1)), (*arg(x0)), (*arg(x1)), (JointCalendarRule)x2));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

Calendar* qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e) {
  try {
    return alloc(new JointCalendar((*arg(x_1)), (*arg(x0)), (JointCalendarRule)x1));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

int* qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, char **e) {
  try {
    const std::vector<Date> dates = Calendar::holidayList(*arg(calendar), Date(from), Date(to), includeWeekEnds);
    *len = dates.size();
    int *days = qlAllocateInts(*len);
    for (size_t i = 0; i < dates.size(); ++i)
      days[i] = dates[i].serialNumber();
    return days;
  } catch (std::exception& er) {
    return handleException<int*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
