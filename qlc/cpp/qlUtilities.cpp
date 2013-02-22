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

int *qlAllocateInts(size_t size) {
  return new int[size];
}

void qlFreeInts(int *p) {
  delete[] p;
}

double *qlAllocateDoubles(size_t size) {
  return new double[size];
}

void qlFreeDoubles(double *p) {
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

boost::optional<bool> qlOptBool(int b) {
  if (b == -1)
    return boost::none;
  else
    return b;
}

int qlOptBool(boost::optional<bool> b) {
  if (b)
    return *b;
  else
    return -1;
}

char *tracedup(const char *p) {
  TP2("Duplicating string", (void *)p);
  char *dup = strdup(p);
  TP2("Duplicated string to", (void *)dup);
  return dup;
}

std::vector<Date> qlDateVector(unsigned len, int *dates) {
  std::vector<Date> d;
  for (unsigned i = 0; i < len; ++i)
    d.push_back(Date(dates[i]));
  return d;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
