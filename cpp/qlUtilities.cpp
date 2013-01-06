#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
# include <windows.h>
#endif

#include "ql.h"

using namespace QuantLib;

const char *qlVersion() {
  return QL_VERSION;
}

const char *boostVersion() {
  return BOOST_LIB_VERSION;
}

void qlFreeString(char *p) {
  free(TM("Pfreeing string", p));
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
void *tracemem(const char *file, int line, const char *text, void *p) {
  //fprintf(stderr, text, p);
  int thread = 0;
#ifdef _WIN32
  thread = GetCurrentThreadId();
#endif

  printf("\n%d(%s:%d)%s : %p\n", thread, file, line, text, p);
  return p;
}

char *tracedup(const char *p) {
  TM("Duplicated string", const_cast<char *>(p));
  return strdup(p);
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
