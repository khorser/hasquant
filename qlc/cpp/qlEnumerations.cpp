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
#include <ql/instruments/bmaswap.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/prices.hpp>
#include <ql/experimental/risk/sensitivityanalysis.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/calendars/jointcalendar.hpp>
#include <ql/cashflows/duration.hpp>

#include <string.h>

#include "qlaux.h"

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

static int bmaSwapTypeValues[] =
  {
    BMASwap::Receiver
  , BMASwap::Payer
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

static int durationValues[] =
  {
    Duration::Simple
  , Duration::Macaulay
  , Duration::Modified
  };

struct EnumInfo {
  const char *name;
  size_t len;
  int *data;

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {};
    bool operator() (const EnumInfo& i) const {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };
};

static EnumInfo enumInfo[] = {
  {"QuantLib.Time.BusinessDayConvention.BusinessDayConvention",
    LENGTH(businessDayConventionValues),
    businessDayConventionValues},
  {"QuantLib.Time.DateGenerationRule.DateGenerationRule",
    LENGTH(dateGenerationRuleValues),
    dateGenerationRuleValues},
  {"QuantLib.Time.Frequency.Frequency",
    LENGTH(frequencyValues),
    frequencyValues},
  {"QuantLib.Time.Unit.Unit",
    LENGTH(timeUnitValues),
    timeUnitValues},
  {"QuantLib.Compounding.Compounding",
    LENGTH(compoundingValues),
    compoundingValues},
  {"QuantLib.Time.Weekday.Weekday",
    LENGTH(weekdayValues),
    weekdayValues},
  {"QuantLib.Time.Month.Month",
    LENGTH(monthValues),
    monthValues},
  {"QuantLib.PositionType.PositionType",
    LENGTH(positionValues),
    positionValues},
  {"QuantLib.Credit.Seniority.Seniority",
    LENGTH(seniorityValues),
    seniorityValues},
  {"QuantLib.ExerciseType.ExerciseType",
    LENGTH(exerciseTypeValues),
    exerciseTypeValues},
  {"QuantLib.Instrument.OptionType.OptionType",
    LENGTH(optionTypeValues),
    optionTypeValues},
  {"QuantLib.Instrument.OvernightIndexedSwapType.OvernightIndexedSwapType",
    LENGTH(overnightIndexedSwapTypeValues),
    overnightIndexedSwapTypeValues},
  {"QuantLib.Instrument.VanillaSwapType.VanillaSwapType",
    LENGTH(vanillaSwapTypeValues),
    vanillaSwapTypeValues},
  {"QuantLib.Instrument.BMASwapType.BMASwapType",
    LENGTH(bmaSwapTypeValues),
    bmaSwapTypeValues},
  {"QuantLib.PriceType.PriceType",
    LENGTH(priceTypeValues),
    priceTypeValues},
  {"QuantLib.Risk.SensitivityAnalysis.SensitivityAnalysis",
    LENGTH(sensitivityAnalysisValues),
    sensitivityAnalysisValues},
  {"QuantLib.SettlementType.SettlementType",
    LENGTH(settlementTypeValues),
    settlementTypeValues},
  {"QuantLib.Time.IMMMonth.IMMMonth",
    LENGTH(immMonthValues),
    immMonthValues},
  {"QuantLib.Time.JointCalendarRule.JointCalendarRule",
    LENGTH(jointCalendarRuleValues),
    jointCalendarRuleValues},
  {"QuantLib.CashFlow.DurationType.DurationType",
    LENGTH(durationValues),
    durationValues},
};

int *qlEnumerationValue(const char *name, unsigned *c) {
  EnumInfo *last = LAST(enumInfo);
  EnumInfo *found = std::find_if(enumInfo, last, EnumInfo::Cmp(name));
  if (found != last) {
    *c = found->len;
    return found->data;
  } else {
    *c = 0;
    return 0;
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
