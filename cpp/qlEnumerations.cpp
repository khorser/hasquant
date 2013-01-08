#include <ql/time/businessdayconvention.hpp>
#include <ql/time/dategenerationrule.hpp>
#include <ql/time/frequency.hpp>
#include <ql/time/timeunit.hpp>
#include <ql/compounding.hpp>

#include <string.h>

#include "ql.h"

using namespace QuantLib;

// The order of enumeration values should be the same
// as in corresponding Haskell code!

static int businessDayConventionValues[] = 
  {
    Following
  , ModifiedFollowing
  , Preceding
  , ModifiedPreceding
  , Unadjusted
  };

static int dateGenerationRuleValues[] = 
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

static int frequencyValues[] = 
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

static int timeUnitValues[] = 
  {
    Months
  , Days
  , Weeks
  , Years
  };

static int compoundingValues[] =
  {
    Simple
  , Compounded
  , Continuous
  , SimpleThenCompounded
  };

int *qlEnumerationValue(const char *name, int *c) {
  if (!strcmp(name, "BusinessDayConvention")) {
    *c = sizeof(businessDayConventionValues)/sizeof(businessDayConventionValues[0]);
    return businessDayConventionValues;
  }
  else if (!strcmp(name, "DateGenerationRule")) {
    *c = sizeof(dateGenerationRuleValues)/sizeof(dateGenerationRuleValues[0]);
    return dateGenerationRuleValues;
  }
  else if (!strcmp(name, "Frequency")) {
    *c = sizeof(frequencyValues)/sizeof(frequencyValues[0]);
    return frequencyValues;
  } else if (!strcmp(name, "Unit")) {
    *c = sizeof(timeUnitValues)/sizeof(timeUnitValues[0]);
    return timeUnitValues;
  } else if (!strcmp(name, "Compounding")) {
    *c = sizeof(compoundingValues)/sizeof(compoundingValues[0]);
    return compoundingValues;
  } else {
    *c = 0;
    return 0;
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
