#include <ql/time/businessdayconvention.hpp>
#include <ql/time/dategenerationrule.hpp>
#include <ql/time/frequency.hpp>
#include <ql/time/timeunit.hpp>
#include <ql/compounding.hpp>
#include <ql/position.hpp>
#include <ql/experimental/credit/defaulttype.hpp>
#include <ql/exercise.hpp>
#include <ql/option.hpp>
#include <ql/instruments/overnightindexedswap.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/prices.hpp>
#include <ql/experimental/risk/sensitivityanalysis.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/calendars/jointcalendar.hpp>

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

static int weekdayValues[] =
  {
    Sunday
  , Monday
  , Tuesday
  , Wednesday
  , Thursday
  , Friday
  , Saturday
  };

static int monthValues[] =
  {
    January
  , February
  , March
  , April
  , May
  , June
  , July
  , August
  , September
  , October
  , November
  , December
  };

static int positionValues[] =
  {
    Position::Long
  , Position::Short
  };

static int seniorityValues[] =
  {
    SecDom
  , SnrFor
  , SubLT2
  , JrSubT2
  , PrefT1
  , NoSeniority
  , SeniorSec
  , SeniorUnSec
  , SubTier1
  , SubUpperTier2
  , SubLoweTier2
  };

static int exerciseTypeValues[] =
  {
    Exercise::American
  , Exercise::Bermudan
  , Exercise::European
  };

static int optionTypeValues[] =
  {
    Option::Put
  , Option::Call
  };

static int overnightIndexedSwapTypeValues[] =
  {
    OvernightIndexedSwap::Receiver
  , OvernightIndexedSwap::Payer
  };

static int vanillaSwapTypeValues[] =
  {
    VanillaSwap::Receiver
  , VanillaSwap::Payer
  };

static int priceTypeValues[] =
  {
    Bid
  , Ask
  , Last
  , Close
  , Mid
  , MidEquivalent
  , MidSafe
  };

static int sensitivityAnalysisValues[] =
  {
    OneSide
  , Centered
  };

static int settlementTypeValues[] =
  {
    Settlement::Physical
  , Settlement::Cash
  };

static int immMonthValues[] =
  {
    IMM::F
  , IMM::G
  , IMM::H
  , IMM::J
  , IMM::K
  , IMM::M
  , IMM::N
  , IMM::Q
  , IMM::U
  , IMM::V
  , IMM::X
  , IMM::Z
  };

static int jointCalendarRuleValues[] =
  {
    JoinHolidays
  , JoinBusinessDays
  };

int *qlEnumerationValue(const char *name, int *c) {
  if (!strcmp(name, "QuantLib.Time.BusinessDayConvention.BusinessDayConvention")) {
    *c = sizeof(businessDayConventionValues)/sizeof(businessDayConventionValues[0]);
    return businessDayConventionValues;
  }
  else if (!strcmp(name, "QuantLib.Time.DateGenerationRule.DateGenerationRule")) {
    *c = sizeof(dateGenerationRuleValues)/sizeof(dateGenerationRuleValues[0]);
    return dateGenerationRuleValues;
  }
  else if (!strcmp(name, "QuantLib.Time.Frequency.Frequency")) {
    *c = sizeof(frequencyValues)/sizeof(frequencyValues[0]);
    return frequencyValues;
  } else if (!strcmp(name, "QuantLib.Time.Unit.Unit")) {
    *c = sizeof(timeUnitValues)/sizeof(timeUnitValues[0]);
    return timeUnitValues;
  } else if (!strcmp(name, "QuantLib.Compounding.Compounding")) {
    *c = sizeof(compoundingValues)/sizeof(compoundingValues[0]);
    return compoundingValues;
  } else if (!strcmp(name, "QuantLib.Time.Date.Weekday")) {
    *c = sizeof(weekdayValues)/sizeof(weekdayValues[0]);
    return weekdayValues;
  } else if (!strcmp(name, "QuantLib.Time.Date.Month")) {
    *c = sizeof(monthValues)/sizeof(monthValues[0]);
    return monthValues;
  } else if (!strcmp(name, "QuantLib.Side.Side")) {
    *c = sizeof(positionValues)/sizeof(positionValues[0]);
    return positionValues;
  } else if (!strcmp(name, "QuantLib.Credit.Seniority.Seniority")) {
    *c = sizeof(seniorityValues)/sizeof(seniorityValues[0]);
    return seniorityValues;
  } else if (!strcmp(name, "QuantLib.ExerciseType.ExerciseType")) {
    *c = sizeof(exerciseTypeValues)/sizeof(exerciseTypeValues[0]);
    return exerciseTypeValues;
  } else if (!strcmp(name, "QuantLib.Instrument.OptionType.OptionType")) {
    *c = sizeof(optionTypeValues)/sizeof(optionTypeValues[0]);
    return optionTypeValues;
  } else if (!strcmp(name,
	"QuantLib.Instrument.OvernightIndexedSwapType.OvernightIndexedSwapType")) {
    *c = sizeof(overnightIndexedSwapTypeValues)/sizeof(overnightIndexedSwapTypeValues[0]);
    return overnightIndexedSwapTypeValues;
  } else if (!strcmp(name, "QuantLib.Instrument.VanillaSwapType.VanillaSwapType")) {
    *c = sizeof(vanillaSwapTypeValues)/sizeof(vanillaSwapTypeValues[0]);
    return vanillaSwapTypeValues;
  } else if (!strcmp(name, "QuantLib.PriceType.PriceType")) {
    *c = sizeof(priceTypeValues)/sizeof(priceTypeValues[0]);
    return priceTypeValues;
  } else if (!strcmp(name, "QuantLib.Risk.SensitivityAnalysis.SensitivityAnalysis")) {
    *c = sizeof(sensitivityAnalysisValues)/sizeof(sensitivityAnalysisValues[0]);
    return sensitivityAnalysisValues;
  } else if (!strcmp(name, "QuantLib.SettlementType.SettlementType")) {
    *c = sizeof(settlementTypeValues)/sizeof(settlementTypeValues[0]);
    return settlementTypeValues;
  } else if (!strcmp(name, "QuantLib.Time.IMMMonth.IMMMonth")) {
    *c = sizeof(immMonthValues)/sizeof(immMonthValues[0]);
    return immMonthValues;
  } else if (!strcmp(name, "QuantLib.Time.JointCalendarRule.JointCalendarRule")) {
    *c = sizeof(jointCalendarRuleValues)/sizeof(jointCalendarRuleValues[0]);
    return jointCalendarRuleValues;
  } else {
    *c = 0;
    return 0;
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
