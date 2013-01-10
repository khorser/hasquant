#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlCalendar(const char *name, char **e)
{
  // use enumerations instead?
  try {
    Calendar *c = 0;
    if (!strcmp(name, "NoCalendar"))
      c = new Calendar();
    else if (!strcmp(name, "NullCalendar"))
      c = new NullCalendar();
    else if (!strcmp(name, "TARGET"))
      c = new TARGET();
    else if (!strcmp(name, "Argentina::Merval"))
      c = new Argentina(Argentina::Merval);
    else if (!strcmp(name, "Australia"))
      c = new Australia();
    else if (!strcmp(name, "Brazil::Settlement"))
      c = new Brazil(Brazil::Settlement);
    else if (!strcmp(name, "Brazil::Exchange"))
      c = new Brazil(Brazil::Exchange);
    else if (!strcmp(name, "Canada::Settlement"))
      c = new Canada(Canada::Settlement);
    else if (!strcmp(name, "Canada::TSX"))
      c = new Canada(Canada::TSX);
    else if (!strcmp(name, "China"))
      c = new China();
    else if (!strcmp(name, "CzechRepublic::PSE"))
      c = new CzechRepublic(CzechRepublic::PSE);
    else if (!strcmp(name, "Denmark"))
      c = new Denmark();
    else if (!strcmp(name, "Finland"))
      c = new Finland();
    else if (!strcmp(name, "Germany::Eurex"))
      c = new Germany(Germany::Eurex);
    else if (!strcmp(name, "Germany::FrankfurtStockExchange"))
      c = new Germany(Germany::FrankfurtStockExchange);
    else if (!strcmp(name, "Germany::Settlement"))
      c = new Germany(Germany::Settlement);
    else if (!strcmp(name, "Germany::Xetra"))
      c = new Germany(Germany::Xetra);
    else if (!strcmp(name, "HongKong::HKEx"))
      c = new HongKong(HongKong::HKEx);
    else if (!strcmp(name, "Hungary"))
      c = new Hungary();
    else if (!strcmp(name, "Iceland::ICEX"))
      c = new Iceland(Iceland::ICEX);
    else if (!strcmp(name, "India::NSE"))
      c = new India(India::NSE);
    else if (!strcmp(name, "Indonesia::BEJ"))
      c = new Indonesia(Indonesia::BEJ);
    else if (!strcmp(name, "Indonesia::JSX"))
      c = new Indonesia(Indonesia::JSX);
    else if (!strcmp(name, "Italy::Exchange"))
      c = new Italy(Italy::Exchange);
    else if (!strcmp(name, "Italy::Settlement"))
      c = new Italy(Italy::Settlement);
    else if (!strcmp(name, "Japan"))
      c = new Japan();
    else if (!strcmp(name, "Mexico::BMV"))
      c = new Mexico(Mexico::BMV);
    else if (!strcmp(name, "NewZealand"))
      c = new NewZealand();
    else if (!strcmp(name, "Norway"))
      c = new Norway();
    else if (!strcmp(name, "Poland"))
      c = new Poland();
    else if (!strcmp(name, "Russia"))
      c = new Russia();
    else if (!strcmp(name, "SaudiArabia::Tadawul"))
      c = new SaudiArabia(SaudiArabia::Tadawul);
    else if (!strcmp(name, "Singapore::SGX"))
      c = new Singapore(Singapore::SGX);
    else if (!strcmp(name, "Slovakia::BSSE"))
      c = new Slovakia(Slovakia::BSSE);
    else if (!strcmp(name, "SouthAfrica"))
      c = new SouthAfrica();
    else if (!strcmp(name, "SouthKorea::KRX"))
      c = new SouthKorea(SouthKorea::KRX);
    else if (!strcmp(name, "Sweden"))
      c = new Sweden();
    else if (!strcmp(name, "Switzerland"))
      c = new Switzerland();
    else if (!strcmp(name, "Taiwan::TSEC"))
      c = new Taiwan(Taiwan::TSEC);
    else if (!strcmp(name, "EUR"))
      c = new TARGET();
    else if (!strcmp(name, "Turkey"))
      c = new Turkey();
    else if (!strcmp(name, "Ukraine::USE"))
      c = new Ukraine(Ukraine::USE);
    else if (!strcmp(name, "UnitedKingdom::Exchange"))
      c = new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "London stock exchange"))
      c = new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "LONDON"))
      c = new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "GBP"))
      c = new UnitedKingdom(UnitedKingdom::Exchange);
    else if (!strcmp(name, "UnitedKingdom::Metals"))
      c = new UnitedKingdom(UnitedKingdom::Metals);
    else if (!strcmp(name, "UnitedKingdom::Settlement"))
      c = new UnitedKingdom(UnitedKingdom::Settlement);
    else if (!strcmp(name, "UnitedStates::GovernmentBond"))
      c = new UnitedStates(UnitedStates::GovernmentBond);
    else if (!strcmp(name, "UnitedStates::NERC"))
      c = new UnitedStates(UnitedStates::NERC);
    else if (!strcmp(name, "UnitedStates::NYSE"))
      c = new UnitedStates(UnitedStates::NYSE);
    else if (!strcmp(name, "UnitedStates::Settlement"))
      c = new UnitedStates(UnitedStates::Settlement);
    else
      QL_FAIL("Calendar not found");
    return uncast("Allocated calendar", c);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void  qlFreeCalendar(void *calendar) {
  delete cast<Calendar>("Pfreeing calendar", calendar);
}

const char *qlCalendarName(void *calendar) {
  std::string name = cast<Calendar>("Pcalendar", calendar)->name();
  return DUP(name.c_str());
}

int qlCalendarAdjust(void *c, int date, int conv) {
  return cast<Calendar>("Pcalendar", c)
    ->adjust(Date(date), (BusinessDayConvention) conv).serialNumber();
}

int qlCalendarAdvance(void *c, int date, int n, int unit, int conv, int eom) {
  return cast<Calendar>("Pcalendar", c)
    ->advance(Date(date), n, (TimeUnit) unit, (BusinessDayConvention) conv, eom).serialNumber();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
