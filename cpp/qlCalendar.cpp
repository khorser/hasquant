#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlCalendar(const char *name, char **e)
{
  *e = 0;
  // use enumerations instead?
  try {
    if (!strcmp(name, "NoCalendar"))
     return new Calendar();
    else if (!strcmp(name, "NullCalendar"))
     return new NullCalendar();
    else if (!strcmp(name, "TARGET"))
     return new TARGET();
    else if (!strcmp(name, "Argentina::Merval"))
     return new Argentina(Argentina::Merval);
    else if (!strcmp(name, "Australia"))
     return new Australia();
    else if (!strcmp(name, "Brazil::Settlement"))
     return new Brazil(Brazil::Settlement);
    else if (!strcmp(name, "Brazil::Exchange"))
     return new Brazil(Brazil::Exchange);
    else if (!strcmp(name, "Canada::Settlement"))
     return new Canada(Canada::Settlement);
    else if (!strcmp(name, "Canada::TSX"))
     return new Canada(Canada::TSX);
    else if (!strcmp(name, "China"))
     return new China();
    else if (!strcmp(name, "CzechRepublic::PSE"))
     return new CzechRepublic(CzechRepublic::PSE);
    else if (!strcmp(name, "Denmark"))
     return new Denmark();
    else if (!strcmp(name, "Finland"))
     return new Finland();
    else if (!strcmp(name, "Germany::Eurex"))
     return new Germany(Germany::Eurex);
    else if (!strcmp(name, "Germany::FrankfurtStockExchange"))
     return new Germany(Germany::FrankfurtStockExchange);
    else if (!strcmp(name, "Germany::Settlement"))
     return new Germany(Germany::Settlement);
    else if (!strcmp(name, "Germany::Xetra"))
     return new Germany(Germany::Xetra);
    else if (!strcmp(name, "HongKong::HKEx"))
     return new HongKong(HongKong::HKEx);
    else if (!strcmp(name, "Hungary"))
     return new Hungary();
    else if (!strcmp(name, "Iceland::ICEX"))
     return new Iceland(Iceland::ICEX);
    else if (!strcmp(name, "India::NSE"))
     return new India(India::NSE);
    else if (!strcmp(name, "Indonesia::BEJ"))
     return new Indonesia(Indonesia::BEJ);
    else if (!strcmp(name, "Indonesia::JSX"))
     return new Indonesia(Indonesia::JSX);
    else if (!strcmp(name, "Italy::Exchange"))
     return new Italy(Italy::Exchange);
    else if (!strcmp(name, "Italy::Settlement"))
     return new Italy(Italy::Settlement);
    else if (!strcmp(name, "Japan"))
     return new Japan();
    else if (!strcmp(name, "Mexico::BMV"))
     return new Mexico(Mexico::BMV);
    else if (!strcmp(name, "NewZealand"))
     return new NewZealand();
    else if (!strcmp(name, "Norway"))
     return new Norway();
    else if (!strcmp(name, "Poland"))
     return new Poland();
    else if (!strcmp(name, "Russia"))
     return new Russia();
    else if (!strcmp(name, "SaudiArabia::Tadawul"))
     return new SaudiArabia(SaudiArabia::Tadawul);
    else if (!strcmp(name, "Singapore::SGX"))
     return new Singapore(Singapore::SGX);
    else if (!strcmp(name, "Slovakia::BSSE"))
     return new Slovakia(Slovakia::BSSE);
    else if (!strcmp(name, "SouthAfrica"))
     return new SouthAfrica();
    else if (!strcmp(name, "SouthKorea::KRX"))
     return new SouthKorea(SouthKorea::KRX);
    else if (!strcmp(name, "Sweden"))
     return new Sweden();
    else if (!strcmp(name, "Switzerland"))
     return new Switzerland();
    else if (!strcmp(name, "Taiwan::TSEC"))
     return new Taiwan(Taiwan::TSEC);
    else if (!strcmp(name, "EUR"))
     return new TARGET();
    else if (!strcmp(name, "Turkey"))
     return new Turkey();
    else if (!strcmp(name, "Ukraine::USE"))
     return new Ukraine(Ukraine::USE);
    else if (!strcmp(name, "UnitedKingdom::Exchange"))
     return new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "London stock exchange"))
     return new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "LONDON"))
     return new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "GBP"))
     return new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "UnitedKingdom::Metals"))
     return new UnitedKingdom(UnitedKingdom::Metals);
    else if (!strcmp(name, "UnitedKingdom::Settlement"))
     return new UnitedKingdom(UnitedKingdom::Settlement);
    else if (!strcmp(name, "UnitedStates::GovernmentBond"))
     return new UnitedStates(UnitedStates::GovernmentBond);
    else if (!strcmp(name, "UnitedStates::NERC"))
     return new UnitedStates(UnitedStates::NERC);
    else if (!strcmp(name, "UnitedStates::NYSE"))
     return new UnitedStates(UnitedStates::NYSE);
    else if (!strcmp(name, "UnitedStates::Settlement"))
     return new UnitedStates(UnitedStates::Settlement);
    else
      QL_FAIL("Calendar not found");
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void  qlFreeCalendar(void *calendar) {
  //printf("freeing calendar %p", calendar);
  delete static_cast<Calendar *>(calendar);
}

const char *qlCalendarName(void *calendar) {
  std::string name = static_cast<Calendar *>(calendar)->name();
  return strdup(name.c_str());
}

int qlCalendarAdjust(void *c, int date, int conv) {
  return static_cast<Calendar *>(c)->adjust(Date(date), (BusinessDayConvention) conv).serialNumber();
}

int qlCalendarAdvance(void *c, int date, int n, int unit, int conv, int eom) {
  return static_cast<Calendar *>(c)->advance(Date(date), n, (TimeUnit) unit, (BusinessDayConvention) conv, eom).serialNumber();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
