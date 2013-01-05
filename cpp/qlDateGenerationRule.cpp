#include <ql/time/dategenerationrule.hpp>

#include "ql.h"

using namespace QuantLib;

static int values[] = 
  {
    DateGeneration::Backward
  , DateGeneration::Forward
  , DateGeneration::Zero
  , DateGeneration::ThirdWednesday
  , DateGeneration::Twentieth
  , DateGeneration::TwentiethIMM
  , DateGeneration::OldCDS
  , DateGeneration::CDS
  };

int *qlDateGenerationRule(int *c)
{
  *c = sizeof(values)/sizeof(values[0]);
  return values;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
