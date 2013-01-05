#include <ql/time/frequency.hpp>

#include "ql.h"

using namespace QuantLib;

static int values[] = 
  {
    NoFrequency
  , Annual
  , Semiannual
  , EveryFourthMonth
  , Quarterly
  , Bimonthly
  , Monthly
  , Biweekly
  , EveryFourthWeek
  , Weekly
  , Daily
  , Once
  , OtherFrequency
  };

int *qlFrequency(int *c) {
  *c = sizeof(values)/sizeof(values[0]);
  return values;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
