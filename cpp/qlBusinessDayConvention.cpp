#include <ql/time/businessdayconvention.hpp>

#include "ql.h"

using namespace QuantLib;

static int values[] = 
  {
    Following
  , ModifiedFollowing
  , Preceding
  , ModifiedPreceding
  , Unadjusted
  };

int *qlBusinessDayConvention(int *c) {
  *c = sizeof(values)/sizeof(values[0]);
  return values;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
