#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>

#include <stdlib.h>
#include <string.h>

#include "ql.h"

using namespace QuantLib;

const char *qlVersion() {
  return QL_VERSION;
}

const char *boostVersion() {
  return BOOST_LIB_VERSION;
}

void qlFreeString(char *p) {
  free(TP("Pfreeing string", p));
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

#ifdef QLTRACK_ALLOCATIONS
char *tracedup(const char *p) {
  TP("Duplicating string", const_cast<char *>(p));
  return (char *)TP("Duplicated string to", strdup(p));
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
