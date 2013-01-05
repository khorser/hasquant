#include <ql/time/timeunit.hpp>

#include "ql.h"

using namespace QuantLib;

static int values[] = 
  {
    Months
  , Days
  , Weeks
  , Years
  };

int *qlTimeUnit(int *c) {
  *c = sizeof(values)/sizeof(values[0]);
  return values;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
