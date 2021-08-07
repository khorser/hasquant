#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>

#include "qlaux.h"
#include "qlCalendar.h"

using namespace QuantLib;

typedef Calendar *(*makeCalendar)(int market);

static const makeCalendar calendars[] = {
  [](int){ return static_cast<Calendar *>(new Argentina()); }
  , [](int){ return static_cast<Calendar *>(new Australia()); }
  , [](int market){ return static_cast<Calendar *>(new Austria((Austria::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new Botswana()); }
  , [](int market){ return static_cast<Calendar *>(new Brazil((Brazil::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new Canada((Canada::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new China((China::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new CzechRepublic()); }
  , [](int){ return static_cast<Calendar *>(new Denmark()); }
  , [](int){ return static_cast<Calendar *>(new Finland()); }
  , [](int market){ return static_cast<Calendar *>(new France((France::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new Germany((Germany::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new HongKong()); }
  , [](int){ return static_cast<Calendar *>(new Hungary()); }
  , [](int){ return static_cast<Calendar *>(new Iceland()); }
  , [](int){ return static_cast<Calendar *>(new India()); }
  , [](int market){ return static_cast<Calendar *>(new Indonesia((Indonesia::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new Israel((Israel::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new Italy((Italy::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new Japan()); }
  , [](int){ return static_cast<Calendar *>(new Mexico()); }
  , [](int){ return static_cast<Calendar *>(new NewZealand()); }
  , [](int){ return static_cast<Calendar *>(new Norway()); }
  , [](int){ return static_cast<Calendar *>(new NullCalendar()); }
  , [](int){ return static_cast<Calendar *>(new Poland()); }
  , [](int market){ return static_cast<Calendar *>(new Romania((Romania::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new Russia((Russia::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new SaudiArabia()); }
  , [](int){ return static_cast<Calendar *>(new Singapore()); }
  , [](int){ return static_cast<Calendar *>(new Slovakia()); }
  , [](int){ return static_cast<Calendar *>(new SouthAfrica()); }
  , [](int market){ return static_cast<Calendar *>(new SouthKorea((SouthKorea::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new Sweden()); }
  , [](int){ return static_cast<Calendar *>(new Switzerland()); }
  , [](int){ return static_cast<Calendar *>(new Taiwan()); }
  , [](int){ return static_cast<Calendar *>(new TARGET()); }
  , [](int){ return static_cast<Calendar *>(new Thailand()); }
  , [](int){ return static_cast<Calendar *>(new Turkey()); }
  , [](int){ return static_cast<Calendar *>(new Ukraine()); }
  , [](int market){ return static_cast<Calendar *>(new UnitedKingdom((UnitedKingdom::Market) market)); }
  , [](int market){ return static_cast<Calendar *>(new UnitedStates((UnitedStates::Market) market)); }
  , [](int){ return static_cast<Calendar *>(new WeekendsOnly()); }
};

Calendar *qlCalendar(int country, int market, char **e) {
  try {
    if (country < 0 || country >= (int)LENGTH(calendars))
      QL_FAIL("Invalid country index " << country);
    return alloc(calendars[country](market));
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

void qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, int **days, char **e) {
  try {
    const std::vector<Date> dates = arg(calendar)->holidayList(Date(from), Date(to), includeWeekEnds);
    *len = dates.size();
    *days = qlAllocateInts(*len);
    for (size_t i = 0; i < dates.size(); ++i)
      *days[i] = dates[i].serialNumber();
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
