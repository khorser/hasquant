#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>

#include <stdlib.h>
#include <string.h>
//#include <stdio.h>

#include "ql.h"

using namespace QuantLib;

const char *qlVersion() {
  return QL_VERSION;
}

const char *boostVersion() {
  return BOOST_LIB_VERSION;
}

void qlFreeString(char *p) {
  // for extra tests
  //*p = 0;
  //printf("Freeing string %p\n", p);
  free(p);
}
/* vim: set ft=CPP ff=unix ts=8 sts=2 sw=2: */
