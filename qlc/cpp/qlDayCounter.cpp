#include <ql/time/daycounters/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

DayCounter *qlDayCounter(const char *name, char **e) {
  try {
    DayCounter *c = 0;
    if (!strcmp(name, "DayCounter"))
      c = new DayCounter();
    else if (!strcmp(name, "NoDayCounter"))
      c = new DayCounter();
    else if (!strcmp(name, "Actual/365 (Fixed)"))
      c = new Actual365Fixed();
    else if (!strcmp(name, "Act/365 (Fixed)"))
      c = new Actual365Fixed();
    else if (!strcmp(name, "A/365 (Fixed)"))
      c = new Actual365Fixed();
    else if (!strcmp(name, "A/365F"))
      c = new Actual365Fixed();
    else if (!strcmp(name, "1/1"))
      c = new OneDayCounter();
    else if (!strcmp(name, "Actual/Actual (ISDA)"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Actual/Actual"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Actual/365"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Act/365"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "A/365"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Act/Act"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Actual/360"))
      c = new Actual360();
    else if (!strcmp(name, "Act/360"))
      c = new Actual360();
    else if (!strcmp(name, "A/360"))
      c = new Actual360();
    else if (!strcmp(name, "30/360 (Bond Basis)"))
      c = new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "Bond Basis"))
      c = new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "30/360"))
      c = new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "360/360"))
      c = new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "30/360 (European)"))
      c = new Thirty360(Thirty360::European);
    else if (!strcmp(name, "30/360 (Eurobond Basis)"))
      c = new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "Eurobond Basis"))
      c = new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "30E/360"))
      c = new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "30E/360 (Eurobond Basis)"))
      c = new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "Actual/Actual (ISMA)"))
      c = new ActualActual(ActualActual::ISMA);
    else if (!strcmp(name, "Actual/Actual (Bond)"))
      c = new ActualActual(ActualActual::ISMA);
    else if (!strcmp(name, "Actual/Actual (AFB)"))
      c = new ActualActual(ActualActual::AFB);
    else if (!strcmp(name, "Actual/Actual (Euro)"))
      c = new ActualActual(ActualActual::Euro);
    else if (!strcmp(name, "30/360 (Italian)"))
      c = new Thirty360(Thirty360::Italian);
    else if (!strcmp(name, "Simple"))
      c = new SimpleDayCounter();
    else if (!strcmp(name, "LIN 30/360"))
      c = new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "LIN ACT/360"))
      c = new Actual360();
    else if (!strcmp(name, "LIN ACT/365"))
      c = new Actual365Fixed();
    else if (!strcmp(name, "LIN ACT/ACT"))
      c = new ActualActual(ActualActual::AFB);
    else if (!strcmp(name, "LIN ACTACT ISDA"))
      c = new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "LIN ACTACT ISMA"))
      c = new ActualActual(ActualActual::ISMA);
    else if (!strcmp(name, "30/360 (USA)"))
      c = new Thirty360(Thirty360::USA);
    else if (!strcmp(name, "Actual/Actual (Historical)"))
      c = new ActualActual(ActualActual::Historical);
    else if (!strcmp(name, "Actual/Actual (Actual365)"))
      c = new ActualActual(ActualActual::Actual365);
    else
      QL_FAIL("Counter not found " << name);
    return alloc(c);
  } catch (std::exception& er) {
    return handleException<DayCounter *>(e, er);
  }
}

DayCounter *DLLEXPORT qlDayCounterBusiness252(Calendar *cal, char **e) {
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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
