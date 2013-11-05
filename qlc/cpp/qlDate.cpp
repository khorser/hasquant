#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>

#include "qlaux.h"
#include "qlDate.h"

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
int qlDateDayOfYear(int o) {
    return Date(o).dayOfYear();
}

int qlDateEndOfMonth(int d) {
    return Date::endOfMonth(Date(d)).serialNumber();
}

int qlDateIsEndOfMonth(int d) {
    return Date::isEndOfMonth(Date(d));
}

int qlDateNextWeekday(int d, int w) {
    return Date::nextWeekday(Date(d), (Weekday)w).serialNumber();
}

int qlDateNthWeekday(unsigned n, int w, int m, int y) {
    return Date::nthWeekday(n, (Weekday)w, (Month)m, y).serialNumber();
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
    return (IMM::date(std::string(arg(immCode)), Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMIsIMMcode(char* in, int mainCycle) {
    return IMM::isIMMcode(std::string(arg(in)), mainCycle);
}
int qlIMMIsIMMdate(int d, int mainCycle) {
    return IMM::isIMMdate(Date(d), mainCycle);
}
char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return DUP(IMM::nextCode(std::string(arg(immCode)), mainCycle, Date(referenceDate)).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
char* qlIMMNextCode(int d, int mainCycle) {
    return DUP(IMM::nextCode(Date(d), mainCycle).c_str());
}
int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return (IMM::nextDate(std::string(arg(immCode)), mainCycle, Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlIMMNextDate(int d, int mainCycle) {
    return IMM::nextDate(Date(d), mainCycle).serialNumber();
}

int qlAddPeriod(int d, Period *p, char **e) {
  try {
    return (Date(d)+*arg(p)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlSubtractPeriod(int d, Period *p, char **e) {
  try {
    return (Date(d)-*arg(p)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
