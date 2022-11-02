#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/ecb.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/schedule.hpp>
#include <ql/time/period.hpp>
#include <ql/utilities/dataparsers.hpp>
#include <ql/time/daycounters/all.hpp>

#include "qlaux.h"
#include "qlTime.h"

using namespace QuantLib;

int qlMinDateSerialNumber() {return Date::minDate().serialNumber();}

int qlMaxDateSerialNumber() {return Date::maxDate().serialNumber();}

int qlMinYear() {return Date::minDate().year();}

int qlMinMonth() {return Date::minDate().month();}

int qlMinDay() {return Date::minDate().dayOfMonth();}

int qlWeekday(int date) {return Date(date).weekday();}

// generated code
int qlDateDayOfYear(int o) {return Date(o).dayOfYear();}

int qlDateEndOfMonth(int d) {return Date::endOfMonth(Date(d)).serialNumber();}

int qlDateIsEndOfMonth(int d) {return Date::isEndOfMonth(Date(d));}

int qlDateNextWeekday(int d, int w) {return Date::nextWeekday(Date(d), (Weekday)w).serialNumber();}

int qlDateNthWeekday(unsigned n, int w, int m, int y) {return Date::nthWeekday(n, (Weekday)w, (Month)m, y).serialNumber();}

char* qlIMMCode(int immDate, char **e) {
  try {
    return DUP((IMM::code(Date(immDate))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlIMMDate(char* immCode, int referenceDate, char **e) {
  try {
    return (IMM::date(std::string(immCode), Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMIsIMMcode(char* in, int mainCycle) {return IMM::isIMMcode(std::string(arg(in)), mainCycle);}

int qlIMMIsIMMdate(int d, int mainCycle) {return IMM::isIMMdate(Date(d), mainCycle);}

char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return DUP(IMM::nextCode(std::string(arg(immCode)), mainCycle, Date(referenceDate)).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
char* qlIMMNextCode(int d, int mainCycle) {return DUP(IMM::nextCode(Date(d), mainCycle).c_str());}

int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return (IMM::nextDate(std::string(arg(immCode)), mainCycle, Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMNextDate(int d, int mainCycle) {return IMM::nextDate(Date(d), mainCycle).serialNumber();}

int qlAddPeriod(int d, int n, int u, char **e) {
  try {
    return (Date(d) + Period(n, (TimeUnit)u)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlECBAddDate(int d, char **e) {
  try {
    ECB::addDate(Date(d));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
char* qlECBCode(int ecbDate, char **e) {
  try {
    return DUP((ECB::code(Date(ecbDate))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlECBDate1(char* ecbCode, int referenceDate, char **e) {
  try {
    return (ECB::date(std::string(arg(ecbCode)), qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBDate(int m, int y, char **e) {
  try {
    return (ECB::date((Month)m, y)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBIsECBcode(char* in, char **e) {
  try {
    return ECB::isECBcode(arg(in));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBIsECBdate(int d, char **e) {
  try {
    return ECB::isECBdate(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
void qlECBKnownDates(unsigned *count, int **ds, char **e) {
  try {
    const std::set<Date> &dates = ECB::knownDates();
    *count = dates.size();
    *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds,
        std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
char* qlECBNextCode1(char* ecbCode, char **e) {
  try {
    return DUP((ECB::nextCode(std::string(arg(ecbCode)))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
char* qlECBNextCode(int d, char **e) {
  try {
    return DUP((ECB::nextCode(qlNullableDate(d))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlECBNextDate1(char* ecbCode, int referenceDate, char **e) {
  try {
    return (ECB::nextDate(std::string(arg(ecbCode)), qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBNextDate(int d, char **e) {
  try {
    return (ECB::nextDate(qlNullableDate(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
void qlECBNextDates1(char* ecbCode, int referenceDate, unsigned *count, int **ds, char **e) {
  try {
    const std::vector<Date> &dates = ECB::nextDates(ecbCode, qlNullableDate(referenceDate));
    *count = dates.size();
    *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds,
        std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}
void qlECBNextDates(int d, unsigned *count, int **ds, char **e) {
  try {
    const std::vector<Date> &dates = ECB::nextDates(qlNullableDate(d));
    *count = dates.size();
    *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds,
        std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}
void qlECBRemoveDate(int d, char **e) {
  try {
    ECB::removeDate(Date(d));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

typedef Calendar *(*makeCalendar)(int market);

// must match with the order of qlEnumObjects.h:CalendarCountry
static const makeCalendar calendars[] = {
  [](int){return static_cast<Calendar *>(new Argentina());}
  , [](int){return static_cast<Calendar *>(new Australia());}
  , [](int market){return static_cast<Calendar *>(new Austria((Austria::Market) market));}
  , [](int){return static_cast<Calendar *>(new Botswana());}
  , [](int market){return static_cast<Calendar *>(new Brazil((Brazil::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Canada((Canada::Market) market));}
  , [](int market){return static_cast<Calendar *>(new China((China::Market) market));}
  , [](int){return static_cast<Calendar *>(new CzechRepublic());}
  , [](int){return static_cast<Calendar *>(new Denmark());}
  , [](int){return static_cast<Calendar *>(new Finland());}
  , [](int market){return static_cast<Calendar *>(new France((France::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Germany((Germany::Market) market));}
  , [](int){return static_cast<Calendar *>(new HongKong());}
  , [](int){return static_cast<Calendar *>(new Hungary());}
  , [](int){return static_cast<Calendar *>(new Iceland());}
  , [](int){return static_cast<Calendar *>(new India());}
  , [](int market){return static_cast<Calendar *>(new Indonesia((Indonesia::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Israel((Israel::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Italy((Italy::Market) market));}
  , [](int){return static_cast<Calendar *>(new Japan());}
  , [](int){return static_cast<Calendar *>(new Mexico());}
  , [](int){return static_cast<Calendar *>(new NewZealand());}
  , [](int){return static_cast<Calendar *>(new Norway());}
  , [](int){return static_cast<Calendar *>(new NullCalendar());}
  , [](int){return static_cast<Calendar *>(new Poland());}
  , [](int market){return static_cast<Calendar *>(new Romania((Romania::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Russia((Russia::Market) market));}
  , [](int){return static_cast<Calendar *>(new SaudiArabia());}
  , [](int){return static_cast<Calendar *>(new Singapore());}
  , [](int){return static_cast<Calendar *>(new Slovakia());}
  , [](int){return static_cast<Calendar *>(new SouthAfrica());}
  , [](int market){return static_cast<Calendar *>(new SouthKorea((SouthKorea::Market) market));}
  , [](int){return static_cast<Calendar *>(new Sweden());}
  , [](int){return static_cast<Calendar *>(new Switzerland());}
  , [](int){return static_cast<Calendar *>(new Taiwan());}
  , [](int){return static_cast<Calendar *>(new TARGET());}
  , [](int){return static_cast<Calendar *>(new Thailand());}
  , [](int){return static_cast<Calendar *>(new Turkey());}
  , [](int){return static_cast<Calendar *>(new Ukraine());}
  , [](int market){return static_cast<Calendar *>(new UnitedKingdom((UnitedKingdom::Market) market));}
  , [](int market){return static_cast<Calendar *>(new UnitedStates((UnitedStates::Market) market));}
  , [](int){return static_cast<Calendar *>(new WeekendsOnly());}
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

void qlFreeCalendar(Calendar *calendar) {del(calendar);}

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
    cal = new BespokeCalendar(std::string(name));
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
      (*days)[i] = dates[i].serialNumber();
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}

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

void qlFreeSchedule(Schedule *s) {del(s);}

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
  [](int) {return static_cast<DayCounter *>(new Actual360());}
  , [](int) {return static_cast<DayCounter *>(new Actual364());}
  , [](int conv) {return static_cast<DayCounter *>(new Actual365Fixed((Actual365Fixed::Convention) conv));}
  , [](int conv) {return static_cast<DayCounter *>(new ActualActual((ActualActual::Convention) conv));}
  , [](int) {return static_cast<DayCounter *>(new OneDayCounter());}
  , [](int) {return static_cast<DayCounter *>(new SimpleDayCounter());}
  , [](int conv) {return static_cast<DayCounter *>(new Thirty360((Thirty360::Convention) conv));}
  , [](int) {return static_cast<DayCounter *>(new Thirty365());}
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

void  qlFreeDayCounter(DayCounter *counter) {del(counter);}

const char *qlDayCounterName(DayCounter *counter) {
  std::string name = arg(counter)->name();
  return DUP(name.c_str());
}

// generated code
int qlDayCounterDayCount(DayCounter* o, int x0, int x1) {return arg(o)->dayCount(Date(x0), Date(x1));}

double qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e) {
  try {
    return arg(o)->yearFraction(Date(x0), Date(x1), qlNullableDate(refPeriodStart), qlNullableDate(refPeriodEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
