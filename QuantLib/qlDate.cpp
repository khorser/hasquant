#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>

#include <stdlib.h>
#include <string.h>
//#include <stdio.h>

#include "ql.h"

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

void * qlDate(int x, char **e) {
  try {
    Date *p = new Date(x);
    //printf("Allocated date %p\n", p);
    return p;
  } catch (Error& er) {
    *e = strdup(er.what());
    //printf("Duplicated string %p\n", *e);
    return 0;
  }
}

int qlDateSerialNumber(void *p) {
  if (p)
    ((Date *)p)->serialNumber();
  else
    return 0;
}

void qlFreeDate(void *p) {
  //for extra tests
  //memset(p, 0, sizeof(Date));
  //printf("Freeing date %p\n", p);
  delete (Date *)p;
}

/* vim: set ft=CPP ff=unix ts=8 sts=2 sw=2: */
