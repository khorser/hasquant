#include <ql/time/daycounters/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlDayCounter(const char *name, char **e)
{
  *e = 0;
  try {
    // use enumerations instead?
    if (!strcmp(name, "DayCounter"))
      return new DayCounter();
    else if (!strcmp(name, "NoDayCounter"))
      return new DayCounter();
    else if (!strcmp(name, "Actual/365 (Fixed)"))
      return new Actual365Fixed();
    else if (!strcmp(name, "Act/365 (Fixed)"))
      return new Actual365Fixed();
    else if (!strcmp(name, "A/365 (Fixed)"))
      return new Actual365Fixed();
    else if (!strcmp(name, "A/365F"))
      return new Actual365Fixed();
    else if (!strcmp(name, "1/1"))
      return new OneDayCounter();
    else if (!strcmp(name, "Actual/Actual (ISDA)"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Actual/Actual"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Actual/365"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Act/365"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "A/365"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Act/Act"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "Actual/360"))
      return new Actual360();
    else if (!strcmp(name, "Act/360"))
      return new Actual360();
    else if (!strcmp(name, "A/360"))
      return new Actual360();
    else if (!strcmp(name, "30/360 (Bond Basis)"))
      return new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "Bond Basis"))
      return new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "30/360"))
      return new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "360/360"))
      return new Thirty360(Thirty360::BondBasis);
    else if (!strcmp(name, "30/360 (Eurobond Basis)"))
      return new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "Eurobond Basis"))
      return new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "30E/360"))
      return new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "30E/360 (Eurobond Basis)"))
      return new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "Actual/Actual (ISMA)"))
      return new ActualActual(ActualActual::ISMA);
    else if (!strcmp(name, "Actual/Actual (Bond)"))
      return new ActualActual(ActualActual::ISMA);
    else if (!strcmp(name, "Actual/Actual (AFB)"))
      return new ActualActual(ActualActual::AFB);
    else if (!strcmp(name, "Actual/Actual (Euro)"))
      return new ActualActual(ActualActual::AFB);
    else if (!strcmp(name, "30/360 (Italian)"))
      return new Thirty360(Thirty360::Italian);
    else if (!strcmp(name, "Simple"))
      return new SimpleDayCounter();
    else if (!strcmp(name, "LIN 30/360"))
      return new Thirty360(Thirty360::EurobondBasis);
    else if (!strcmp(name, "LIN ACT/360"))
      return new Actual360();
    else if (!strcmp(name, "LIN ACT/365"))
      return new Actual365Fixed();
    else if (!strcmp(name, "LIN ACT/ACT"))
      return new ActualActual(ActualActual::AFB);
    else if (!strcmp(name, "LIN ACTACT ISDA"))
      return new ActualActual(ActualActual::ISDA);
    else if (!strcmp(name, "LIN ACTACT ISMA"))
      return new ActualActual(ActualActual::ISMA);
    else if (!strcmp(name, "Business252"))
      return new Business252();
    else
      QL_FAIL("Counter not found");
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void  qlFreeDayCounter(void *counter) {
  //printf("freeing counter %p", counter);
  delete static_cast<Calendar *>(counter);
}

const char *qlDayCounterName(void *counter) {
  std::string name = static_cast<DayCounter *>(counter)->name();
  return strdup(name.c_str());
}


/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
