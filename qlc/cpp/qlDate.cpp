#include <ql/time/date.hpp>

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

int qlDateEndOfMonth(int o, int d, char **e) {
  try {
    return (Date(o).endOfMonth(Date(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateIsEndOfMonth(int o, int d, char **e) {
  try {
    return Date(o).isEndOfMonth(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateNextWeekday(int o, int d, int w, char **e) {
  try {
    return (Date(o).nextWeekday(Date(d), (Weekday)w)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlDateNthWeekday(int o, unsigned n, int w, int m, int y, char **e) {
  try {
    return (Date(o).nthWeekday(n, (Weekday)w, (Month)m, y)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
