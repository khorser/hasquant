#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>

#include <stdlib.h>
#include <string.h>

#include "qlaux.h"

using namespace QuantLib;

const char *qlVersion() {
  return QL_VERSION;
}

const char *qlBoostVersion() {
  return BOOST_LIB_VERSION;
}

void qlFreeString(char *p) {
  TP2("Freeing string", (void *)p);
  free(p);
  TP2("Freed string", (void *)p);
}

int *qlAllocateInts(int size) {
  return new int[size];
}

void qlFreeInts(int *p) {
  delete[] p;
}

const QuantLib::Date qlNullableDate(int serialNumber) {
  if (!serialNumber)
    return Date(); /* special null date value */
  else
    return Date(serialNumber);
}

int qlNullableDate(const QuantLib::Date &date) {
  if (date == Date())
    return 0;
  else
    return date.serialNumber();
}

char *tracedup(const char *p) {
  TP2("Duplicating string", (void *)p);
  char *dup = strdup(p);
  TP2("Duplicated string to", (void *)dup);
  return dup;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
