#include <ql/time/daycounters/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

template <class T, typename T::Convention conv>
DayCounter *makeDayCounter() {
  return new T(conv);
};

EnumObjectInfo<DayCounter> dayCounterInfo[] = {
  {"DayCounter", &makeObject<DayCounter, DayCounter>},
  {"NoDayCounter", &makeObject<DayCounter, DayCounter>},
  {"Actual/365 (Fixed)", &makeObject<DayCounter, Actual365Fixed>},
  {"Act/365 (Fixed)", &makeObject<DayCounter, Actual365Fixed>},
  {"A/365 (Fixed)", &makeObject<DayCounter, Actual365Fixed>},
  {"A/365F", &makeObject<DayCounter, Actual365Fixed>},
  {"1/1", &makeObject<DayCounter, OneDayCounter>},
  {"Actual/Actual (ISDA)", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"Actual/Actual", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"Actual/365", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"Act/365", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"A/365", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"Act/Act", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"Actual/360", &makeObject<DayCounter, Actual360>},
  {"Act/360", &makeObject<DayCounter, Actual360>},
  {"A/360", &makeObject<DayCounter, Actual360>},
  {"30/360 (Bond Basis)", &makeDayCounter<Thirty360, Thirty360::BondBasis>},
  {"Bond Basis", &makeDayCounter<Thirty360, Thirty360::BondBasis>},
  {"30/360", &makeDayCounter<Thirty360, Thirty360::BondBasis>},
  {"360/360", &makeDayCounter<Thirty360, Thirty360::BondBasis>},
  {"30/360 (European)", &makeDayCounter<Thirty360, Thirty360::European>},
  {"30/360 (Eurobond Basis)", &makeDayCounter<Thirty360, Thirty360::EurobondBasis>},
  {"Eurobond Basis", &makeDayCounter<Thirty360, Thirty360::EurobondBasis>},
  {"30E/360", &makeDayCounter<Thirty360, Thirty360::EurobondBasis>},
  {"30E/360 (Eurobond Basis)", &makeDayCounter<Thirty360, Thirty360::EurobondBasis>},
  {"Actual/Actual (ISMA)", &makeDayCounter<ActualActual, ActualActual::ISMA>},
  {"Actual/Actual (Bond)", &makeDayCounter<ActualActual, ActualActual::ISMA>},
  {"Actual/Actual (AFB)", &makeDayCounter<ActualActual, ActualActual::AFB>},
  {"Actual/Actual (Euro)", &makeDayCounter<ActualActual, ActualActual::Euro>},
  {"30/360 (Italian)", &makeDayCounter<Thirty360, Thirty360::Italian>},
  {"Simple", &makeObject<DayCounter, SimpleDayCounter>},
  {"LIN 30/360", &makeDayCounter<Thirty360, Thirty360::EurobondBasis>},
  {"LIN ACT/360", &makeObject<DayCounter, Actual360>},
  {"LIN ACT/365", &makeObject<DayCounter, Actual365Fixed>},
  {"LIN ACT/ACT", &makeDayCounter<ActualActual, ActualActual::AFB>},
  {"LIN ACTACT ISDA", &makeDayCounter<ActualActual, ActualActual::ISDA>},
  {"LIN ACTACT ISMA", &makeDayCounter<ActualActual, ActualActual::ISMA>},
  {"30/360 (USA)", &makeDayCounter<Thirty360, Thirty360::USA>},
  {"Actual/Actual (Historical)", &makeDayCounter<ActualActual, ActualActual::Historical>},
  {"Actual/Actual (Actual365)", &makeDayCounter<ActualActual, ActualActual::Actual365>}
};

DayCounter *qlDayCounter(const char *name, char **e) {
  try {
    EnumObjectInfo<DayCounter> *last = dayCounterInfo + LENGTH(dayCounterInfo);
    EnumObjectInfo<DayCounter> *found = std::find_if(dayCounterInfo, last, EnumObjectInfoComp<DayCounter>(name));
    if (found != last)
      return alloc(found->make());
    else
      QL_FAIL("DayCounter not found " << name);
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
