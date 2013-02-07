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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
