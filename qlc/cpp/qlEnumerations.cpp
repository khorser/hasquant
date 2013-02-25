#include <ql/cashflows/duration.hpp>
#include <ql/compounding.hpp>
#include <ql/default.hpp>
#include <ql/exercise.hpp>
#include <ql/experimental/credit/defaulttype.hpp>
#include <ql/experimental/processes/extendedblackscholesprocess.hpp>
#include <ql/instruments/averagetype.hpp>
#include <ql/instruments/barriertype.hpp>
#include <ql/instruments/bmaswap.hpp>
#include <ql/instruments/capfloor.hpp>
#include <ql/instruments/overnightindexedswap.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/math/rounding.hpp>
#include <ql/option.hpp>
#include <ql/position.hpp>
#include <ql/prices.hpp>
#include <ql/time/businessdayconvention.hpp>
#include <ql/time/calendars/jointcalendar.hpp>
#include <ql/time/dategenerationrule.hpp>
#include <ql/time/frequency.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/timeunit.hpp>
#include <ql/processes/hestonprocess.hpp>
#include <ql/processes/gjrgarchprocess.hpp>
#include <ql/processes/hybridhestonhullwhiteprocess.hpp>
#include <ql/pricingengines/vanilla/analytichestonengine.hpp>
#include <ql/methods/montecarlo/lsmbasissystem.hpp>

#include <string.h>

#include "qlaux.h"
#include "qlEnumerations.h"

using namespace QuantLib;

// The order of enumeration values should be the same
// as in corresponding Haskell code!

static const int businessDayConventionValues[] = {
    Following
  , ModifiedFollowing
  , Preceding
  , ModifiedPreceding
  , Unadjusted
};

static const int dateGenerationRuleValues[] = {
    DateGeneration::Backward
  , DateGeneration::Forward
  , DateGeneration::Zero
  , DateGeneration::ThirdWednesday
  , DateGeneration::Twentieth
  , DateGeneration::TwentiethIMM
  , DateGeneration::OldCDS
  , DateGeneration::CDS
};

static const int frequencyValues[] = {
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

static const int timeUnitValues[] = {
    Months
  , Days
  , Weeks
  , Years
};

static const int compoundingValues[] = {
    Simple
  , Compounded
  , Continuous
  , SimpleThenCompounded
};

static const int weekdayValues[] = {
    Sunday
  , Monday
  , Tuesday
  , Wednesday
  , Thursday
  , Friday
  , Saturday
};

static const int monthValues[] = {
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

static const int positionValues[] = {
    Position::Long
  , Position::Short
};

static const int seniorityValues[] = {
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

static const int exerciseTypeValues[] = {
    Exercise::American
  , Exercise::Bermudan
  , Exercise::European
};

static const int optionTypeValues[] = {
    Option::Put
  , Option::Call
};

static const int overnightIndexedSwapTypeValues[] = {
    OvernightIndexedSwap::Receiver
  , OvernightIndexedSwap::Payer
};

static const int vanillaSwapTypeValues[] = {
    VanillaSwap::Receiver
  , VanillaSwap::Payer
};

static const int bmaSwapTypeValues[] = {
    BMASwap::Receiver
  , BMASwap::Payer
};

static const int priceTypeValues[] = {
    Bid
  , Ask
  , Last
  , Close
  , Mid
  , MidEquivalent
  , MidSafe
};

static const int settlementTypeValues[] = {
    Settlement::Physical
  , Settlement::Cash
};

static const int immMonthValues[] = {
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

static const int jointCalendarRuleValues[] = {
    JoinHolidays
  , JoinBusinessDays
};

static const int durationValues[] = {
    Duration::Simple
  , Duration::Macaulay
  , Duration::Modified
};

static const int roundingValues[] = {
    Rounding::None,
    Rounding::Up,
    Rounding::Down,
    Rounding::Closest,
    Rounding::Floor,
    Rounding::Ceiling
};

static const int extDiscretizationValues[] = {
    ExtendedBlackScholesMertonProcess::Euler
  , ExtendedBlackScholesMertonProcess::Milstein
  , ExtendedBlackScholesMertonProcess::PredictorCorrector
};

static const int protectionSideValues[] = {
    Protection::Buyer
  , Protection::Seller
};

static const int averageTypeValues[] = {
    Average::Arithmetic
  , Average::Geometric
};

static const int barrierTypeValues[] = {
    Barrier::DownIn
  , Barrier::UpIn
  , Barrier::DownOut
  , Barrier::UpOut
};

static const int capFloorTypeValues[] = {
    CapFloor::Cap
  , CapFloor::Floor
  , CapFloor::Collar
};

static const int hestonProcessDiscretizationValues[] = {
    HestonProcess::PartialTruncation
  , HestonProcess::FullTruncation
  , HestonProcess::Reflection
  , HestonProcess::NonCentralChiSquareVariance
  , HestonProcess::QuadraticExponential
  , HestonProcess::QuadraticExponentialMartingale
};

static const int gjrgarchProcessDiscretizationValues[] = {
    GJRGARCHProcess::PartialTruncation
  , GJRGARCHProcess::FullTruncation
  , GJRGARCHProcess::Reflection
};

static const int hybridHestonHullWhiteProcessDiscretizationValues[] = {
    HybridHestonHullWhiteProcess::Euler
  , HybridHestonHullWhiteProcess::BSMHullWhite
};

static const int intervalPriceTypeValues[] = {
    IntervalPrice::Open
  , IntervalPrice::Close
  , IntervalPrice::High
  , IntervalPrice::Low
};

static const int analyticHestonEngineComplexLogFormulaValues[] = {
    AnalyticHestonEngine::Gatheral
  , AnalyticHestonEngine::BranchCorrection
};

static const int lsmBasisSystemPolynomTypeValues[] = {
    LsmBasisSystem::Monomial
  , LsmBasisSystem::Laguerre
  , LsmBasisSystem::Hermite
  , LsmBasisSystem::Hyperbolic
  , LsmBasisSystem::Legendre
  , LsmBasisSystem::Chebyshev
  , LsmBasisSystem::Chebyshev2nd
};

struct EnumInfo {
  const char *const name;
  size_t len;
  const int *const data;

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

static const EnumInfo enumInfo[] = {
  {"QuantLib.Time.BusinessDayConvention.BusinessDayConvention",
    LENGTH(businessDayConventionValues), businessDayConventionValues},
  {"QuantLib.Time.DateGenerationRule.DateGenerationRule",
    LENGTH(dateGenerationRuleValues), dateGenerationRuleValues},
  {"QuantLib.Time.Frequency.Frequency",
    LENGTH(frequencyValues), frequencyValues},
  {"QuantLib.Time.Unit.Unit",
    LENGTH(timeUnitValues), timeUnitValues},
  {"QuantLib.Compounding.Compounding",
    LENGTH(compoundingValues), compoundingValues},
  {"QuantLib.Time.Weekday.Weekday",
    LENGTH(weekdayValues), weekdayValues},
  {"QuantLib.Time.Month.Month",
    LENGTH(monthValues), monthValues},
  {"QuantLib.PositionType.PositionType",
    LENGTH(positionValues), positionValues},
  {"QuantLib.Credit.Seniority.Seniority",
    LENGTH(seniorityValues), seniorityValues},
  {"QuantLib.Credit.ProtectionSide.ProtectionSide",
    LENGTH(protectionSideValues), protectionSideValues},
  {"QuantLib.ExerciseType.ExerciseType",
    LENGTH(exerciseTypeValues), exerciseTypeValues},
  {"QuantLib.Instrument.OptionType.OptionType",
    LENGTH(optionTypeValues), optionTypeValues},
  {"QuantLib.Instrument.OvernightIndexedSwapType.OvernightIndexedSwapType",
    LENGTH(overnightIndexedSwapTypeValues), overnightIndexedSwapTypeValues},
  {"QuantLib.Instrument.VanillaSwapType.VanillaSwapType",
    LENGTH(vanillaSwapTypeValues), vanillaSwapTypeValues},
  {"QuantLib.Instrument.BMASwapType.BMASwapType",
    LENGTH(bmaSwapTypeValues), bmaSwapTypeValues},
  {"QuantLib.PriceType.PriceType",
    LENGTH(priceTypeValues), priceTypeValues},
  {"QuantLib.SettlementType.SettlementType",
    LENGTH(settlementTypeValues), settlementTypeValues},
  {"QuantLib.Time.IMMMonth.IMMMonth",
    LENGTH(immMonthValues), immMonthValues},
  {"QuantLib.Time.JointCalendarRule.JointCalendarRule",
    LENGTH(jointCalendarRuleValues), jointCalendarRuleValues},
  {"QuantLib.CashFlow.DurationType.DurationType",
    LENGTH(durationValues), durationValues},
  {"QuantLib.Math.RoundingType.RoundingType",
    LENGTH(roundingValues), roundingValues},
  {"QuantLib.ProcessDiscretization.ExtendedDiscretization",
    LENGTH(extDiscretizationValues), extDiscretizationValues},
  {"QuantLib.Instrument.BarrierType.BarrierType",
    LENGTH(barrierTypeValues), barrierTypeValues},
  {"QuantLib.Instrument.AverageType.AverageType",
    LENGTH(averageTypeValues), averageTypeValues},
  {"QuantLib.Instrument.CapFloorType.CapFloorType",
    LENGTH(capFloorTypeValues), capFloorTypeValues},
  {"QuantLib.ProcessDiscretization.HestonProcessDiscretization",
    LENGTH(hestonProcessDiscretizationValues), hestonProcessDiscretizationValues},
  {"QuantLib.ProcessDiscretization.GJRGARCHProcessDiscretization",
    LENGTH(gjrgarchProcessDiscretizationValues), gjrgarchProcessDiscretizationValues},
  {"QuantLib.ProcessDiscretization.HybridHestonHullWhiteProcessDiscretization",
    LENGTH(hybridHestonHullWhiteProcessDiscretizationValues), hybridHestonHullWhiteProcessDiscretizationValues},
  {"QuantLib.PriceType.IntervalPriceType",
    LENGTH(intervalPriceTypeValues), intervalPriceTypeValues},
  {"QuantLib.PricingEngine.Parameter.ComplexLogFormula",
    LENGTH(analyticHestonEngineComplexLogFormulaValues), analyticHestonEngineComplexLogFormulaValues},
  {"QuantLib.Method.LsmBasisSystemPolynomType.LsmBasisSystemPolynomType",
    LENGTH(lsmBasisSystemPolynomTypeValues), lsmBasisSystemPolynomTypeValues},
};

const int *qlEnumerationValue(const char *name, unsigned *c) {
  const EnumInfo *last = LAST(enumInfo);
  const EnumInfo *found = std::find_if(enumInfo, last, EnumInfo::Cmp(name));
  if (found != last) {
    *c = found->len;
    return found->data;
  } else {
    *c = 0;
    return 0;
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
