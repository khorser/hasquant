#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

EnumObjectInfo<Calendar> calendarInfo[] = {
  {"NoCalendar", &makeObject<Calendar, Calendar>},
  {"NullCalendar", &makeObject<Calendar, NullCalendar>},
  {"TARGET", &makeObject<Calendar, TARGET>},
  {"Argentina::Merval", &makeObject<Calendar, Argentina>},
  {"Australia", &makeObject<Calendar, Australia>},
  {"Brazil::Settlement", &makeObject<Calendar, Brazil>},
  {"Brazil::Exchange", &makeObject<Calendar, Brazil>},
  {"Canada::Settlement", &makeObject<Calendar, Canada>},
  {"Canada::TSX", &makeObject<Calendar, Canada>},
  {"China", &makeObject<Calendar, China>},
  {"CzechRepublic::PSE", &makeObject<Calendar, CzechRepublic>},
  {"Denmark", &makeObject<Calendar, Denmark>},
  {"Finland", &makeObject<Calendar, Finland>},
  {"Germany::Eurex", &makeObject<Calendar, Germany>},
  {"Germany::FrankfurtStockExchange", &makeObject<Calendar, Germany>},
  {"Germany::Settlement", &makeObject<Calendar, Germany>},
  {"Germany::Xetra", &makeObject<Calendar, Germany>},
  {"HongKong::HKEx", &makeObject<Calendar, HongKong>},
  {"Hungary", &makeObject<Calendar, Hungary>},
  {"Iceland::ICEX", &makeObject<Calendar, Iceland>},
  {"India::NSE", &makeObject<Calendar, India>},
  {"Indonesia::BEJ", &makeObject<Calendar, Indonesia>},
  {"Indonesia::JSX", &makeObject<Calendar, Indonesia>},
  {"Indonesia::IDX", &makeObject<Calendar, Indonesia>},
  {"Italy::Exchange", &makeObject<Calendar, Italy>},
  {"Italy::Settlement", &makeObject<Calendar, Italy>},
  {"Japan", &makeObject<Calendar, Japan>},
  {"Mexico::BMV", &makeObject<Calendar, Mexico>},
  {"NewZealand", &makeObject<Calendar, NewZealand>},
  {"Norway", &makeObject<Calendar, Norway>},
  {"Poland", &makeObject<Calendar, Poland>},
  {"Russia", &makeObject<Calendar, Russia>},
  {"SaudiArabia::Tadawul", &makeObject<Calendar, SaudiArabia>},
  {"Singapore::SGX", &makeObject<Calendar, Singapore>},
  {"Slovakia::BSSE", &makeObject<Calendar, Slovakia>},
  {"SouthAfrica", &makeObject<Calendar, SouthAfrica>},
  {"SouthKorea::KRX", &makeObject<Calendar, SouthKorea>},
  {"SouthKorea::Settlement", &makeObject<Calendar, SouthKorea>},
  {"Sweden", &makeObject<Calendar, Sweden>},
  {"Switzerland", &makeObject<Calendar, Switzerland>},
  {"Taiwan::TSEC", &makeObject<Calendar, Taiwan>},
  {"EUR", &makeObject<Calendar, TARGET>},
  {"Turkey", &makeObject<Calendar, Turkey>},
  {"Ukraine::USE", &makeObject<Calendar, Ukraine>},
  {"UnitedKingdom::Exchange", &makeObject<Calendar, UnitedKingdom>},
  {"London stock exchange", &makeObject<Calendar, UnitedKingdom>},
  {"LONDON", &makeObject<Calendar, UnitedKingdom>},
  {"GBP", &makeObject<Calendar, UnitedKingdom>},
  {"UnitedKingdom::Metals", &makeObject<Calendar, UnitedKingdom>},
  {"UnitedKingdom::Settlement", &makeObject<Calendar, UnitedKingdom>},
  {"UnitedStates::GovernmentBond", &makeObject<Calendar, UnitedStates>},
  {"UnitedStates::NERC", &makeObject<Calendar, UnitedStates>},
  {"UnitedStates::NYSE", &makeObject<Calendar, UnitedStates>},
  {"UnitedStates::Settlement", &makeObject<Calendar, UnitedStates>},
  {"WeekendsOnly", &makeObject<Calendar, WeekendsOnly>},
};

Calendar *qlCalendar(const char *name, char **e) {
  try {
    EnumObjectInfo<Calendar> *last = calendarInfo + LENGTH(calendarInfo);
    EnumObjectInfo<Calendar> *found = std::find_if(calendarInfo, last, EnumObjectInfoComp<Calendar>(name));
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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
