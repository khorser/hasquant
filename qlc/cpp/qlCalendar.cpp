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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
