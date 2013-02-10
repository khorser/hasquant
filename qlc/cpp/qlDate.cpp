#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>

#include "qlaux.h"

using namespace QuantLib;

int qlMinDateSerialNumber() {
  return Date::minDate().serialNumber();
}

int qlMaxDateSerialNumber() {
  return Date::maxDate().serialNumber();
}

int qlMinYear() {
  return Date::minDate().year();
}

int qlMinMonth() {
  return Date::minDate().month();
}

int qlMinDay() {
  return Date::minDate().dayOfMonth();
}

int qlWeekday(int date) {
  return Date(date).weekday();
}

// generated code
int qlDateDayOfYear(int o, char **e) {
  try {
    return Date(o).dayOfYear();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateEndOfMonth(int d, char **e) {
  try {
    return Date::endOfMonth(Date(d)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateIsEndOfMonth(int d, char **e) {
  try {
    return Date::isEndOfMonth(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateNextWeekday(int d, int w, char **e) {
  try {
    return Date::nextWeekday(Date(d), (Weekday)w).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateNthWeekday(unsigned n, int w, int m, int y, char **e) {
  try {
    return Date::nthWeekday(n, (Weekday)w, (Month)m, y).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

char* qlIMMCode(int immDate, char **e) {
  try {
    return DUP((IMM::code(Date(immDate))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlIMMDate(char* immCode, int referenceDate, char **e) {
  try {
    return (IMM::date(std::string(arg(immCode)), qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMIsIMMcode(char* in, int mainCycle, char **e) {
  try {
    return IMM::isIMMcode(std::string(arg(in)), mainCycle);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMIsIMMdate(int d, int mainCycle, char **e) {
  try {
    return IMM::isIMMdate(Date(d), mainCycle);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return DUP(IMM::nextCode(std::string(arg(immCode)), mainCycle, qlNullableDate(referenceDate)).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
char* qlIMMNextCode(int d, int mainCycle, char **e) {
  try {
    return DUP(IMM::nextCode(qlNullableDate(d), mainCycle).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return (IMM::nextDate(std::string(arg(immCode)), mainCycle, qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMNextDate(int d, int mainCycle, char **e) {
  try {
    return (IMM::nextDate(qlNullableDate(d), mainCycle)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
