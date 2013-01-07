#include <ql/time/daycounters/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlDayCounter(const char *name, char **e)
{
  *e = 0;
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
      c = new ActualActual(ActualActual::AFB);
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
    else if (!strcmp(name, "Business252"))
      c = new Business252();
    else
      QL_FAIL("Counter not found");
    return TP("Allocated counter", c);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void  qlFreeDayCounter(void *counter) {
  delete log_and_cast<Calendar>("Pfreeing counter", counter);
}

const char *qlDayCounterName(void *counter) {
  std::string name = log_and_cast<DayCounter>("Pcounter", counter)->name();
  return DUP(name.c_str());
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
