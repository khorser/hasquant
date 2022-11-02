#include <ql/time/date.hpp>
#include <ql/errors.hpp>
#include <string.h>
#include <vector>
#include <boost/optional.hpp>
#include <ql/math/matrix.hpp>

int *qlAllocateInts(size_t size);
double *qlAllocateDoubles(size_t size);
void **qlAllocatePointerArray(size_t size);

char *tracedup(const char *p);
#define DUP(p) tracedup((p))

#ifdef QLTRACK_ALLOCATIONS
template <class T> T traceval(const char *text, T val);
/* trace a pointer */
# define TP(text, p) traceval((text), (p))
# define TP2(text, p) (void)traceval((text), (p));
# include <iostream>
#else
# define TP(text, p) (p)
# define TP2(text, p)
#endif

namespace QuantLib {
  template <class T> class Handle;
  class Quote;
  class Bond;
  class FixedRateBond;
  class FloatingRateBond;
  class ZeroCouponBond;
  class Forward;
  class BondForward;
  class ForwardRateAgreement;
  class DayCounter;
  class Business252;
  class Calendar;
  class JointCalendar;
  class BespokeCalendar;
  class Schedule;
  class Currency;
  class InterestRate;
  class FixedRateBondHelper;
  class DepositRateHelper;
  class YieldTermStructure;
  class FlatForward;
  class PricingEngine;
  class DiscountingBondEngine;
  class Instrument;
  class CompositeInstrument;
  class IborIndex;
  class Index;
  class FloatingRateCouponPricer;
  class OptionletVolatilityStructure;
  class Coupon;
  class AffineModel;
  class AmericanExercise;
  class AnalyticBSMHullWhiteEngine;
  class AnalyticBarrierEngine;
  class AnalyticCapFloorEngine;
  class AnalyticCliquetEngine;
  class AnalyticContinuousFixedLookbackEngine;
  class AnalyticContinuousFloatingLookbackEngine;
  class AnalyticContinuousGeometricAveragePriceAsianEngine;
  class AnalyticDigitalAmericanEngine;
  class AnalyticDiscreteGeometricAveragePriceAsianEngine;
  class AnalyticDiscreteGeometricAverageStrikeAsianEngine;
  class AnalyticDividendEuropeanEngine;
  class AnalyticEuropeanEngine;
  class AnalyticGJRGARCHEngine;
  class AnalyticHestonEngine;
  class AnalyticHestonHullWhiteEngine;
  class AnalyticPerformanceEngine;
  class AssetOrNothingPayoff;
  class AssetSwap;
  class BMAIndex;
  class BMASwap;
  class BMASwapRateHelper;
  class BaroneAdesiWhaleyApproximationEngine;
  class BarrierOption;
  class BasketPayoff;
  class BatesDetJumpEngine;
  class BatesDetJumpModel;
  class BatesDoubleExpDetJumpEngine;
  class BatesDoubleExpDetJumpModel;
  class BatesDoubleExpEngine;
  class BatesDoubleExpModel;
  class BatesEngine;
  class BatesModel;
  class BatesProcess;
  class BermudanExercise;
  class BjerksundStenslandApproximationEngine;
  class BlackCalculator;
  class BlackCalibrationHelper;
  class BlackCallableFixedRateBondEngine;
  class BlackCallableZeroCouponBondEngine;
  class BlackCapFloorEngine;
  class BlackConstantVol;
  class BlackKarasinski;
  class BlackProcess;
  class BlackScholesCalculator;
  class BlackScholesMertonProcess;
  class BlackScholesProcess;
  class BlackSwaptionEngine;
  class BlackVarianceCurve;
  class BlackVolTermStructure;
  class BondHelper;
  class BoundaryConstraint;
  class CalibratedModel;
  class CalibrationHelper;
  class Callability;
  class CallableBond;
  class CallableBondVolatilityStructure;
  class CallableFixedRateBond;
  class CallableZeroCouponBond;
  class CapFloor;
  class CapFloorTermVolSurface;
  class CapHelper;
  class CashOrNothingPayoff;
  class CdsOption;
  class Claim;
  class CompositeConstraint;
  class Constraint;
  class ConvertibleBond;
  class ConvertibleFixedCouponBond;
  class ConvertibleFloatingRateBond;
  class ConvertibleZeroCouponBond;
  class CreditDefaultSwap;
  class CubicBSplinesFitting;
  class DefaultProbabilityTermStructure;
  class DiscountingSwapEngine;
  class Dividend;
  class DividendVanillaOption;
  class EarlyExercise;
  class EndCriteria;
  class EuropeanExercise;
  class EuropeanOption;
  class Exercise;
  class ExponentialSplinesFitting;
  class ExtOUWithJumpsProcess;
  class ExtendedBlackScholesMertonProcess;
  class ExtendedOrnsteinUhlenbeckProcess;
  class FFTVanillaEngine;
  class FaceValueAccrualClaim;
  class FaceValueClaim;
  class FdG2SwaptionEngine;
  class FdHullWhiteSwaptionEngine;
  class FdmSchemeDesc;
  class FittedBondDiscountCurve;
  class FixedDividend;
  class ForwardSpreadedTermStructure;
  class ForwardVanillaOption;
  class FraRateHelper;
  class FractionalDividend;
  class FuturesRateHelper;
  class G2;
  class G2SwaptionEngine;
  class GJRGARCHModel;
  class GJRGARCHProcess;
  class GapPayoff;
  class GarmanKohlagenProcess;
  class GeneralizedBlackScholesProcess;
  class GeneralizedHullWhite;
  class HestonModel;
  class HestonModelHelper;
  class HestonProcess;
  class HullWhite;
  class HullWhiteForwardProcess;
  class HullWhiteProcess;
  class HybridHestonHullWhiteProcess;
  class ImpliedTermStructure;
  class ImpliedVolTermStructure;
  class IntegralCdsEngine;
  class IntegralEngine;
  class InterestRateIndex;
  class JamshidianSwaptionEngine;
  class JuQuadraticApproximationEngine;
  class JumpDiffusionEngine;
  class KirkEngine;
  class KlugeExtOUProcess;
  class LevenbergMarquardt;
  class LfmSwaptionEngine;
  class LiborForwardModel;
  class LiborForwardModelProcess;
  class LmCorrelationModel;
  class LmVolatilityModel;
  class LocalVolTermStructure;
  class MargrabeOption;
  class Merton76Process;
  class MidPointCdsEngine;
  class MultiAssetOption;
  class NelsonSiegelFitting;
  class NoConstraint;
  class OISRateHelper;
  class OneAssetOption;
  class OneFactorAffineModel;
  class OptimizationMethod;
  class Option;
  class OvernightIndex;
  class OvernightIndexedSwap;
  class OvernightIndexedSwapIndex;
  class Payoff;
  class PercentageStrikePayoff;
  class PiecewiseTimeDependentHestonModel;
  class PlainVanillaPayoff;
  class PositiveConstraint;
  class QuantoBarrierOption;
  class QuantoForwardVanillaOption;
  class QuantoTermStructure;
  class QuantoVanillaOption;
  class ReplicatingVarianceSwapEngine;
  class Rounding;
  class ShortRateModel;
  class SimplePolynomialFitting;
  class SimpleQuote;
  class Simplex;
  class SmileSection;
  class SoftCallability;
  class SpreadCdsHelper;
  class StochasticProcess;
  class StochasticProcess1D;
  class StochasticProcessArray;
  class StrikedTypePayoff;
  class StulzEngine;
  class SuperFundPayoff;
  class SuperSharePayoff;
  class SvenssonFitting;
  class Swap;
  class SwapIndex;
  class SwapRateHelper;
  class Swaption;
  class SwaptionHelper;
  class SwaptionVolatilityStructure;
  class SwingExercise;
  class TermStructure;
  class TimeGrid;
  class TreeCallableFixedRateBondEngine;
  class TreeCallableZeroCouponBondEngine;
  class TreeCapFloorEngine;
  class TreeSwaptionEngine;
  class TreeVanillaSwapEngine;
  class TypePayoff;
  class UpfrontCdsHelper;
  class VanillaOption;
  class VanillaSwap;
  class VarianceGammaEngine;
  class VarianceGammaProcess;
  class VegaStressedBlackScholesProcess;
  class VolatilityTermStructure;
  class ZeroSpreadedTermStructure;
}

using QuantLib::Handle;
using QuantLib::Quote;
using QuantLib::Bond;
using QuantLib::FixedRateBond;
using QuantLib::FloatingRateBond;
using QuantLib::ZeroCouponBond;
using QuantLib::Forward;
using QuantLib::BondForward;
using QuantLib::ForwardRateAgreement;
using QuantLib::DayCounter;
using QuantLib::Business252;
using QuantLib::Calendar;
using QuantLib::JointCalendar;
using QuantLib::BespokeCalendar;
using QuantLib::Schedule;
using QuantLib::Currency;
using QuantLib::InterestRate;
using QuantLib::FixedRateBondHelper;
using QuantLib::DepositRateHelper;
using QuantLib::YieldTermStructure;
using QuantLib::FlatForward;
using QuantLib::PricingEngine;
using QuantLib::DiscountingBondEngine;
using QuantLib::Instrument;
using QuantLib::CompositeInstrument;
using QuantLib::IborIndex;
using QuantLib::Index;
using QuantLib::FloatingRateCouponPricer;
using QuantLib::OptionletVolatilityStructure;
using QuantLib::Coupon;
using QuantLib::AffineModel;
using QuantLib::AmericanExercise;
using QuantLib::AnalyticBSMHullWhiteEngine;
using QuantLib::AnalyticBarrierEngine;
using QuantLib::AnalyticCapFloorEngine;
using QuantLib::AnalyticCliquetEngine;
using QuantLib::AnalyticContinuousFixedLookbackEngine;
using QuantLib::AnalyticContinuousFloatingLookbackEngine;
using QuantLib::AnalyticContinuousGeometricAveragePriceAsianEngine;
using QuantLib::AnalyticDigitalAmericanEngine;
using QuantLib::AnalyticDiscreteGeometricAveragePriceAsianEngine;
using QuantLib::AnalyticDiscreteGeometricAverageStrikeAsianEngine;
using QuantLib::AnalyticDividendEuropeanEngine;
using QuantLib::AnalyticEuropeanEngine;
using QuantLib::AnalyticGJRGARCHEngine;
using QuantLib::AnalyticHestonEngine;
using QuantLib::AnalyticHestonHullWhiteEngine;
using QuantLib::AnalyticPerformanceEngine;
using QuantLib::AssetOrNothingPayoff;
using QuantLib::AssetSwap;
using QuantLib::BMAIndex;
using QuantLib::BMASwap;
using QuantLib::BMASwapRateHelper;
using QuantLib::BaroneAdesiWhaleyApproximationEngine;
using QuantLib::BarrierOption;
using QuantLib::BasketPayoff;
using QuantLib::BatesDetJumpEngine;
using QuantLib::BatesDetJumpModel;
using QuantLib::BatesDoubleExpDetJumpEngine;
using QuantLib::BatesDoubleExpDetJumpModel;
using QuantLib::BatesDoubleExpEngine;
using QuantLib::BatesDoubleExpModel;
using QuantLib::BatesEngine;
using QuantLib::BatesModel;
using QuantLib::BatesProcess;
using QuantLib::BermudanExercise;
using QuantLib::BjerksundStenslandApproximationEngine;
using QuantLib::BlackCalculator;
using QuantLib::BlackCalibrationHelper;
using QuantLib::BlackCallableFixedRateBondEngine;
using QuantLib::BlackCallableZeroCouponBondEngine;
using QuantLib::BlackCapFloorEngine;
using QuantLib::BlackConstantVol;
using QuantLib::BlackKarasinski;
using QuantLib::BlackProcess;
using QuantLib::BlackScholesCalculator;
using QuantLib::BlackScholesMertonProcess;
using QuantLib::BlackScholesProcess;
using QuantLib::BlackSwaptionEngine;
using QuantLib::BlackVarianceCurve;
using QuantLib::BlackVolTermStructure;
using QuantLib::BondHelper;
using QuantLib::BoundaryConstraint;
using QuantLib::CalibratedModel;
using QuantLib::CalibrationHelper;
using QuantLib::Callability;
using QuantLib::CallableBond;
using QuantLib::CallableBondVolatilityStructure;
using QuantLib::CallableFixedRateBond;
using QuantLib::CallableZeroCouponBond;
using QuantLib::CapFloor;
using QuantLib::CapFloorTermVolSurface;
using QuantLib::CapHelper;
using QuantLib::CashOrNothingPayoff;
using QuantLib::CdsOption;
using QuantLib::Claim;
using QuantLib::CompositeConstraint;
using QuantLib::Constraint;
using QuantLib::ConvertibleBond;
using QuantLib::ConvertibleFixedCouponBond;
using QuantLib::ConvertibleFloatingRateBond;
using QuantLib::ConvertibleZeroCouponBond;
using QuantLib::CreditDefaultSwap;
using QuantLib::CubicBSplinesFitting;
using QuantLib::DefaultProbabilityTermStructure;
using QuantLib::DiscountingSwapEngine;
using QuantLib::Dividend;
using QuantLib::DividendVanillaOption;
using QuantLib::EarlyExercise;
using QuantLib::EndCriteria;
using QuantLib::EuropeanExercise;
using QuantLib::EuropeanOption;
using QuantLib::Exercise;
using QuantLib::ExponentialSplinesFitting;
using QuantLib::ExtOUWithJumpsProcess;
using QuantLib::ExtendedBlackScholesMertonProcess;
using QuantLib::ExtendedOrnsteinUhlenbeckProcess;
using QuantLib::FFTVanillaEngine;
using QuantLib::FaceValueAccrualClaim;
using QuantLib::FaceValueClaim;
using QuantLib::FdG2SwaptionEngine;
using QuantLib::FdHullWhiteSwaptionEngine;
using QuantLib::FdmSchemeDesc;
using QuantLib::FittedBondDiscountCurve;
using QuantLib::FixedDividend;
using QuantLib::ForwardSpreadedTermStructure;
using QuantLib::ForwardVanillaOption;
using QuantLib::FraRateHelper;
using QuantLib::FractionalDividend;
using QuantLib::FuturesRateHelper;
using QuantLib::G2;
using QuantLib::G2SwaptionEngine;
using QuantLib::GJRGARCHModel;
using QuantLib::GJRGARCHProcess;
using QuantLib::GapPayoff;
using QuantLib::GarmanKohlagenProcess;
using QuantLib::GeneralizedBlackScholesProcess;
using QuantLib::GeneralizedHullWhite;
using QuantLib::HestonModel;
using QuantLib::HestonModelHelper;
using QuantLib::HestonProcess;
using QuantLib::HullWhite;
using QuantLib::HullWhiteForwardProcess;
using QuantLib::HullWhiteProcess;
using QuantLib::HybridHestonHullWhiteProcess;
using QuantLib::ImpliedTermStructure;
using QuantLib::ImpliedVolTermStructure;
using QuantLib::IntegralCdsEngine;
using QuantLib::IntegralEngine;
using QuantLib::InterestRateIndex;
using QuantLib::JamshidianSwaptionEngine;
using QuantLib::JuQuadraticApproximationEngine;
using QuantLib::JumpDiffusionEngine;
using QuantLib::KirkEngine;
using QuantLib::KlugeExtOUProcess;
using QuantLib::LevenbergMarquardt;
using QuantLib::LfmSwaptionEngine;
using QuantLib::LiborForwardModel;
using QuantLib::LiborForwardModelProcess;
using QuantLib::LmCorrelationModel;
using QuantLib::LmVolatilityModel;
using QuantLib::LocalVolTermStructure;
using QuantLib::MargrabeOption;
using QuantLib::Merton76Process;
using QuantLib::MidPointCdsEngine;
using QuantLib::MultiAssetOption;
using QuantLib::NelsonSiegelFitting;
using QuantLib::NoConstraint;
using QuantLib::OISRateHelper;
using QuantLib::OneAssetOption;
using QuantLib::OneFactorAffineModel;
using QuantLib::OptimizationMethod;
using QuantLib::Option;
using QuantLib::OvernightIndex;
using QuantLib::OvernightIndexedSwap;
using QuantLib::OvernightIndexedSwapIndex;
using QuantLib::Payoff;
using QuantLib::PercentageStrikePayoff;
using QuantLib::PiecewiseTimeDependentHestonModel;
using QuantLib::PlainVanillaPayoff;
using QuantLib::PositiveConstraint;
using QuantLib::QuantoBarrierOption;
using QuantLib::QuantoForwardVanillaOption;
using QuantLib::QuantoTermStructure;
using QuantLib::QuantoVanillaOption;
using QuantLib::ReplicatingVarianceSwapEngine;
using QuantLib::Rounding;
using QuantLib::ShortRateModel;
using QuantLib::SimplePolynomialFitting;
using QuantLib::SimpleQuote;
using QuantLib::Simplex;
using QuantLib::SmileSection;
using QuantLib::SoftCallability;
using QuantLib::SpreadCdsHelper;
using QuantLib::StochasticProcess1D;
using QuantLib::StochasticProcess;
using QuantLib::StochasticProcessArray;
using QuantLib::StrikedTypePayoff;
using QuantLib::StulzEngine;
using QuantLib::SuperFundPayoff;
using QuantLib::SuperSharePayoff;
using QuantLib::SvenssonFitting;
using QuantLib::Swap;
using QuantLib::SwapIndex;
using QuantLib::SwapRateHelper;
using QuantLib::Swaption;
using QuantLib::SwaptionHelper;
using QuantLib::SwaptionVolatilityStructure;
using QuantLib::SwingExercise;
using QuantLib::TermStructure;
using QuantLib::TimeGrid;
using QuantLib::TreeCallableFixedRateBondEngine;
using QuantLib::TreeCallableZeroCouponBondEngine;
using QuantLib::TreeCapFloorEngine;
using QuantLib::TreeSwaptionEngine;
using QuantLib::TreeVanillaSwapEngine;
using QuantLib::TypePayoff;
using QuantLib::UpfrontCdsHelper;
using QuantLib::VanillaOption;
using QuantLib::VanillaSwap;
using QuantLib::VarianceGammaEngine;
using QuantLib::VarianceGammaProcess;
using QuantLib::VegaStressedBlackScholesProcess;
using QuantLib::VolatilityTermStructure;
using QuantLib::ZeroSpreadedTermStructure;

// Haskell CQuote and CRateHelper are actually pointers to shared_ptr's
// because quotes and rate helpers are used via smart pointers (Handle
// and shared_ptr) in QuantLib
// Alternatively we could clone passed quotes/helpers and put them into
// the containers each time we call QuantLib
typedef QuantLib::ext::shared_ptr<Quote> QlQuote;
typedef QuantLib::ext::shared_ptr<YieldTermStructure> QlYieldTermStructure;
typedef QuantLib::ext::shared_ptr<PricingEngine> QlPricingEngine;
typedef QuantLib::ext::shared_ptr<IborIndex> QlIborIndex;
typedef QuantLib::ext::shared_ptr<Index> QlIndex;
typedef QuantLib::ext::shared_ptr<FloatingRateCouponPricer> QlFloatingRateCouponPricer;
typedef QuantLib::ext::shared_ptr<OptionletVolatilityStructure> QlOptionletVolatilityStructure;
typedef QuantLib::ext::shared_ptr<Instrument> QlInstrument;
typedef QuantLib::ext::shared_ptr<Bond> QlBond;
typedef QuantLib::ext::shared_ptr<FixedRateBond> QlFixedRateBond;
typedef QuantLib::ext::shared_ptr<Forward> QlForward;
typedef QuantLib::ext::shared_ptr<BondForward> QlBondForward;
typedef QuantLib::ext::shared_ptr<ForwardRateAgreement> QlForwardRateAgreement;

// Leg and RateHelper are typedefs so we cannot use forward declaration
// for them. Using them only when corresponding headers have been included
// to save some time on compilation
#ifdef quantlib_ratehelpers_hpp
using QuantLib::RateHelper;
typedef QuantLib::ext::shared_ptr<RateHelper> QlRateHelper;
#endif

#ifdef quantlib_cash_flow_hpp
using QuantLib::Leg;
#endif

using QuantLib::Date;

template <class T> class objClassName { public: static const char *name() { return "Unknown"; } };
template <> class objClassName<void *> { public: static const char *name() { return "Ptr"; } };
template <> class objClassName<Instrument *> { public: static const char *name() { return "Instrument"; } };
template <> class objClassName<QlInstrument *> { public: static const char *name() { return "QlInstrument"; } };
template <> class objClassName<CompositeInstrument *> { public: static const char *name() { return "CompositeInstrument"; } };
template <> class objClassName<Bond *> { public: static const char *name() { return "Bond"; } };
template <> class objClassName<QlBond *> { public: static const char *name() { return "QlBond"; } };
template <> class objClassName<FixedRateBond *> { public: static const char *name() { return "FixedRateBond"; } };
template <> class objClassName<QlFixedRateBond *> { public: static const char *name() { return "QlFixedRateBond"; } };
template <> class objClassName<FloatingRateBond *> { public: static const char *name() { return "FloatingRateBond"; } };
template <> class objClassName<ZeroCouponBond *> { public: static const char *name() { return "ZeroCouponBond"; } };
template <> class objClassName<Forward *> { public: static const char *name() { return "Forward"; } };
template <> class objClassName<QlForward *> { public: static const char *name() { return "QlForward"; } };
template <> class objClassName<BondForward *> { public: static const char *name() { return "BondForward"; } };
template <> class objClassName<QlBondForward *> { public: static const char *name() { return "QlBondForward"; } };
template <> class objClassName<ForwardRateAgreement *> { public: static const char *name() { return "ForwardRateAgreement"; } };
template <> class objClassName<QlForwardRateAgreement *> { public: static const char *name() { return "QlForwardRateAgreement"; } };
template <> class objClassName<FloatingRateCouponPricer *> { public: static const char *name() { return "FloatingRateCouponPricer"; } };
template <> class objClassName<QlFloatingRateCouponPricer *> { public: static const char *name() { return "QlFloatingRateCouponPricer"; } };
template <> class objClassName<DayCounter *> { public: static const char *name() { return "DayCounter"; } };
template <> class objClassName<Business252 *> { public: static const char *name() { return "Business252"; } };
template <> class objClassName<InterestRate *> { public: static const char *name() { return "InterestRate"; } };
template <> class objClassName<Calendar *> { public: static const char *name() { return "Calendar"; } };
template <> class objClassName<JointCalendar *> { public: static const char *name() { return "JointCalendar"; } };
template <> class objClassName<BespokeCalendar *> { public: static const char *name() { return "BespokeCalendar"; } };
template <> class objClassName<Quote *> { public: static const char *name() { return "Quote"; } };
template <> class objClassName<QlQuote *> { public: static const char *name() { return "QlQuote"; } };
template <> class objClassName<QlIborIndex *> { public: static const char *name() { return "QlIborIndex"; } };
template <> class objClassName<IborIndex *> { public: static const char *name() { return "IborIndex"; } };
template <> class objClassName<QlIndex *> { public: static const char *name() { return "QlIndex"; } };
template <> class objClassName<Index *> { public: static const char *name() { return "Index"; } };
template <> class objClassName<PricingEngine *> { public: static const char *name() { return "PricingEngine"; } };
template <> class objClassName<DiscountingBondEngine *> { public: static const char *name() { return "DiscountingBondEngine"; } };
template <> class objClassName<QlPricingEngine *> { public: static const char *name() { return "QlPricingEngine"; } };
template <> class objClassName<Schedule *> { public: static const char *name() { return "Schedule"; } };
template <> class objClassName<Currency *> { public: static const char *name() { return "Currency"; } };
template <> class objClassName<YieldTermStructure *> { public: static const char *name() { return "YieldTermStructure"; } };
template <> class objClassName<FlatForward *> { public: static const char *name() { return "FlatForward"; } };
template <> class objClassName<QlYieldTermStructure *> { public: static const char *name() { return "QlYieldTermStructure"; } };
#ifdef quantlib_cash_flow_hpp
template <> class objClassName<Leg *> { public: static const char *name() { return "Leg"; } };
#endif
#ifdef quantlib_ratehelpers_hpp
template <> class objClassName<RateHelper *> { public: static const char *name() { return "RateHelper"; } };
template <> class objClassName<QlRateHelper *> { public: static const char *name() { return "QlRateHelper"; } };
#endif
template <> class objClassName<DepositRateHelper *> { public: static const char *name() { return "DepositRateHelper"; } };
template <> class objClassName<FixedRateBondHelper *> { public: static const char *name() { return "FixedRateBondHelper"; } };
template <> class objClassName<OptionletVolatilityStructure *> { public: static const char *name() { return "OptionletVolatilityStructure"; } };
template <> class objClassName<QlOptionletVolatilityStructure *> { public: static const char *name() { return "QlOptionletVolatilityStructure"; } };

template <class T> T arg(T p) { return TP("arg", p); }
template <class T> void del(T p) { delete TP("deleting", p); TP2("deleted", p); }
template <class T> T alloc(T p) { return TP("allocated", p); }
template <class T> T ret(T p) { return TP("returned", p); }

const Date qlNullableDate(int serialNumber);
int qlNullableDate(const Date &date);
std::vector<Date> qlDateVector(unsigned len, int *dates);

boost::optional<bool> qlOptBool(int b);
int qlOptBool(boost::optional<bool> b);

template <class T>
Handle<T> qlNullableHandle(QuantLib::ext::shared_ptr<T> *p) {
  return p
    ? Handle<T>(*(arg(p)))
    : Handle<T>();
}

QuantLib::Matrix qlBuildMatrix(double *a, unsigned r, unsigned c);

template <class T>
std::vector<T> qlBuildVector(T **vals, size_t len) {
  std::vector<T> r;
  for (size_t i = 0; i < len; ++i) {
    r.push_back(*vals[i]);
  }
  return r;
}

template <class T>
std::vector<Handle<T> > qlBuildHandleVector(QuantLib::ext::shared_ptr<T> **vals, size_t len) {
  std::vector<Handle<T> > r;
  for (size_t i = 0; i < len; ++i) {
    r.push_back(Handle<T>(*vals[i]));
  }
  return r;
}

template <class T>
std::vector< std::vector<Handle<T> > > qlBuildHandleMatrix(QuantLib::ext::shared_ptr<T> **vals, size_t rows, size_t cols) {
  std::vector< std::vector<Handle<T> > > r;
  for (size_t i = 0; i < rows; ++i) {
    std::vector<Handle<T> > row;
    for (size_t j = 0; j < cols; ++j) {
      row.push_back(Handle<T>(*vals[i * cols + j]));
    }
    r.push_back(row);
  }
  return r;
}

/* some useful helpers ... well ... I hope they are... */
template <class T>
T *handleException(char **msg, std::exception &e, T *t) {
  *msg = DUP(e.what());
  if (t)
    delete t;
  return 0;
}

template <class T>
T handleException(char **msg, std::exception &e) {
  *msg = DUP(e.what());
  return 0;
}

#ifdef QLTRACK_ALLOCATIONS
template <class T>
T traceval(const char *text, T val) {
  std::cout << std::endl << text << " " << objClassName<T>::name() << ": " << val << std::endl;
  return val;
}
#endif

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
#define LAST(a) (a + sizeof(a)/sizeof(a[0]))

typedef QuantLib::ext::shared_ptr<Swap> QlSwap;
template <> class objClassName<Swap *> { public: static const char *name() { return "Swap"; } };
template <> class objClassName<QlSwap *> { public: static const char *name() { return "QlSwap"; } };
typedef QuantLib::ext::shared_ptr<VanillaSwap> QlVanillaSwap;
template <> class objClassName<VanillaSwap *> { public: static const char *name() { return "VanillaSwap"; } };
template <> class objClassName<QlVanillaSwap *> { public: static const char *name() { return "QlVanillaSwap"; } };
typedef QuantLib::ext::shared_ptr<InterestRateIndex> QlInterestRateIndex;
template <> class objClassName<InterestRateIndex *> { public: static const char *name() { return "InterestRateIndex"; } };
template <> class objClassName<QlInterestRateIndex *> { public: static const char *name() { return "QlInterestRateIndex"; } };
typedef QuantLib::ext::shared_ptr<SwapIndex> QlSwapIndex;
template <> class objClassName<SwapIndex *> { public: static const char *name() { return "SwapIndex"; } };
template <> class objClassName<QlSwapIndex *> { public: static const char *name() { return "QlSwapIndex"; } };
typedef QuantLib::ext::shared_ptr<SimpleQuote> QlSimpleQuote;
template <> class objClassName<SimpleQuote *> { public: static const char *name() { return "SimpleQuote"; } };
template <> class objClassName<QlSimpleQuote *> { public: static const char *name() { return "QlSimpleQuote"; } };
typedef QuantLib::ext::shared_ptr<OvernightIndex> QlOvernightIndex;
template <> class objClassName<OvernightIndex *> { public: static const char *name() { return "OvernightIndex"; } };
template <> class objClassName<QlOvernightIndex *> { public: static const char *name() { return "QlOvernightIndex"; } };
typedef QuantLib::ext::shared_ptr<OvernightIndexedSwapIndex> QlOvernightIndexedSwapIndex;
template <> class objClassName<OvernightIndexedSwapIndex *> { public: static const char *name() { return "OvernightIndexedSwapIndex"; } };
template <> class objClassName<QlOvernightIndexedSwapIndex *> { public: static const char *name() { return "QlOvernightIndexedSwapIndex"; } };
typedef QuantLib::ext::shared_ptr<BMAIndex> QlBMAIndex;
template <> class objClassName<BMAIndex *> { public: static const char *name() { return "BMAIndex"; } };
template <> class objClassName<QlBMAIndex *> { public: static const char *name() { return "QlBMAIndex"; } };
typedef QuantLib::ext::shared_ptr<BMASwap> QlBMASwap;
template <> class objClassName<BMASwap *> { public: static const char *name() { return "BMASwap"; } };
template <> class objClassName<QlBMASwap *> { public: static const char *name() { return "QlBMASwap"; } };
typedef QuantLib::ext::shared_ptr<OvernightIndexedSwap> QlOvernightIndexedSwap;
template <> class objClassName<OvernightIndexedSwap *> { public: static const char *name() { return "OvernightIndexedSwap"; } };
template <> class objClassName<QlOvernightIndexedSwap *> { public: static const char *name() { return "QlOvernightIndexedSwap"; } };
typedef QuantLib::ext::shared_ptr<BondHelper> QlBondHelper;
template <> class objClassName<BondHelper *> { public: static const char *name() { return "BondHelper"; } };
template <> class objClassName<QlBondHelper *> { public: static const char *name() { return "QlBondHelper"; } };
typedef QuantLib::ext::shared_ptr<FittedBondDiscountCurve> QlFittedBondDiscountCurve;
template <> class objClassName<FittedBondDiscountCurve *> { public: static const char *name() { return "FittedBondDiscountCurve"; } };
template <> class objClassName<QlFittedBondDiscountCurve *> { public: static const char *name() { return "QlFittedBondDiscountCurve"; } };
typedef QuantLib::ext::shared_ptr<SwapRateHelper> QlSwapRateHelper;
template <> class objClassName<SwapRateHelper *> { public: static const char *name() { return "SwapRateHelper"; } };
template <> class objClassName<QlSwapRateHelper *> { public: static const char *name() { return "QlSwapRateHelper"; } };
template <> class objClassName<BMASwapRateHelper *> { public: static const char *name() { return "BMASwapRateHelper"; } };
template <> class objClassName<FraRateHelper *> { public: static const char *name() { return "FraRateHelper"; } };
template <> class objClassName<FuturesRateHelper *> { public: static const char *name() { return "FuturesRateHelper"; } };
typedef QuantLib::ext::shared_ptr<AssetSwap> QlAssetSwap;
template <> class objClassName<AssetSwap *> { public: static const char *name() { return "AssetSwap"; } };
template <> class objClassName<QlAssetSwap *> { public: static const char *name() { return "QlAssetSwap"; } };
typedef QuantLib::ext::shared_ptr<OISRateHelper> QlOISRateHelper;
template <> class objClassName<OISRateHelper *> { public: static const char *name() { return "OISRateHelper"; } };
template <> class objClassName<QlOISRateHelper *> { public: static const char *name() { return "QlOISRateHelper"; } };
template <> class objClassName<Rounding *> { public: static const char *name() { return "Rounding"; } };
typedef QuantLib::ext::shared_ptr<TermStructure> QlTermStructure;
template <> class objClassName<TermStructure *> { public: static const char *name() { return "TermStructure"; } };
template <> class objClassName<QlTermStructure *> { public: static const char *name() { return "QlTermStructure"; } };
typedef QuantLib::ext::shared_ptr<BasketPayoff> QlBasketPayoff;
template <> class objClassName<BasketPayoff *> { public: static const char *name() { return "BasketPayoff"; } };
template <> class objClassName<QlBasketPayoff *> { public: static const char *name() { return "QlBasketPayoff"; } };
typedef QuantLib::ext::shared_ptr<Payoff> QlPayoff;
template <> class objClassName<Payoff *> { public: static const char *name() { return "Payoff"; } };
template <> class objClassName<QlPayoff *> { public: static const char *name() { return "QlPayoff"; } };
typedef QuantLib::ext::shared_ptr<StrikedTypePayoff> QlStrikedTypePayoff;
template <> class objClassName<StrikedTypePayoff *> { public: static const char *name() { return "StrikedTypePayoff"; } };
template <> class objClassName<QlStrikedTypePayoff *> { public: static const char *name() { return "QlStrikedTypePayoff"; } };
typedef QuantLib::ext::shared_ptr<TypePayoff> QlTypePayoff;
template <> class objClassName<TypePayoff *> { public: static const char *name() { return "TypePayoff"; } };
template <> class objClassName<QlTypePayoff *> { public: static const char *name() { return "QlTypePayoff"; } };
typedef QuantLib::ext::shared_ptr<PercentageStrikePayoff> QlPercentageStrikePayoff;
template <> class objClassName<PercentageStrikePayoff *> { public: static const char *name() { return "PercentageStrikePayoff"; } };
template <> class objClassName<QlPercentageStrikePayoff *> { public: static const char *name() { return "QlPercentageStrikePayoff"; } };
typedef QuantLib::ext::shared_ptr<PlainVanillaPayoff> QlPlainVanillaPayoff;
template <> class objClassName<PlainVanillaPayoff *> { public: static const char *name() { return "PlainVanillaPayoff"; } };
template <> class objClassName<QlPlainVanillaPayoff *> { public: static const char *name() { return "QlPlainVanillaPayoff"; } };
typedef QuantLib::ext::shared_ptr<AmericanExercise> QlAmericanExercise;
template <> class objClassName<AmericanExercise *> { public: static const char *name() { return "AmericanExercise"; } };
template <> class objClassName<QlAmericanExercise *> { public: static const char *name() { return "QlAmericanExercise"; } };
typedef QuantLib::ext::shared_ptr<BermudanExercise> QlBermudanExercise;
template <> class objClassName<BermudanExercise *> { public: static const char *name() { return "BermudanExercise"; } };
template <> class objClassName<QlBermudanExercise *> { public: static const char *name() { return "QlBermudanExercise"; } };
typedef QuantLib::ext::shared_ptr<EuropeanExercise> QlEuropeanExercise;
template <> class objClassName<EuropeanExercise *> { public: static const char *name() { return "EuropeanExercise"; } };
template <> class objClassName<QlEuropeanExercise *> { public: static const char *name() { return "QlEuropeanExercise"; } };
typedef QuantLib::ext::shared_ptr<Exercise> QlExercise;
template <> class objClassName<Exercise *> { public: static const char *name() { return "Exercise"; } };
template <> class objClassName<QlExercise *> { public: static const char *name() { return "QlExercise"; } };
typedef QuantLib::ext::shared_ptr<BlackProcess> QlBlackProcess;
template <> class objClassName<BlackProcess *> { public: static const char *name() { return "BlackProcess"; } };
template <> class objClassName<QlBlackProcess *> { public: static const char *name() { return "QlBlackProcess"; } };
typedef QuantLib::ext::shared_ptr<GeneralizedBlackScholesProcess> QlGeneralizedBlackScholesProcess;
template <> class objClassName<GeneralizedBlackScholesProcess *> { public: static const char *name() { return "GeneralizedBlackScholesProcess"; } };
template <> class objClassName<QlGeneralizedBlackScholesProcess *> { public: static const char *name() { return "QlGeneralizedBlackScholesProcess"; } };
typedef QuantLib::ext::shared_ptr<StochasticProcess> QlStochasticProcess;
template <> class objClassName<StochasticProcess *> { public: static const char *name() { return "StochasticProcess"; } };
template <> class objClassName<QlStochasticProcess *> { public: static const char *name() { return "QlStochasticProcess"; } };
typedef QuantLib::ext::shared_ptr<StochasticProcess1D> QlStochasticProcess1D;
template <> class objClassName<StochasticProcess1D *> { public: static const char *name() { return "StochasticProcess1D"; } };
template <> class objClassName<QlStochasticProcess1D *> { public: static const char *name() { return "QlStochasticProcess1D"; } };
typedef QuantLib::ext::shared_ptr<BlackVolTermStructure> QlBlackVolTermStructure;
template <> class objClassName<BlackVolTermStructure *> { public: static const char *name() { return "BlackVolTermStructure"; } };
template <> class objClassName<QlBlackVolTermStructure *> { public: static const char *name() { return "QlBlackVolTermStructure"; } };
typedef QuantLib::ext::shared_ptr<VolatilityTermStructure> QlVolatilityTermStructure;
template <> class objClassName<VolatilityTermStructure *> { public: static const char *name() { return "VolatilityTermStructure"; } };
template <> class objClassName<QlVolatilityTermStructure *> { public: static const char *name() { return "QlVolatilityTermStructure"; } };
typedef QuantLib::ext::shared_ptr<BarrierOption> QlBarrierOption;
template <> class objClassName<BarrierOption *> { public: static const char *name() { return "BarrierOption"; } };
template <> class objClassName<QlBarrierOption *> { public: static const char *name() { return "QlBarrierOption"; } };
typedef QuantLib::ext::shared_ptr<CdsOption> QlCdsOption;
template <> class objClassName<CdsOption *> { public: static const char *name() { return "CdsOption"; } };
template <> class objClassName<QlCdsOption *> { public: static const char *name() { return "QlCdsOption"; } };
typedef QuantLib::ext::shared_ptr<CreditDefaultSwap> QlCreditDefaultSwap;
template <> class objClassName<CreditDefaultSwap *> { public: static const char *name() { return "CreditDefaultSwap"; } };
template <> class objClassName<QlCreditDefaultSwap *> { public: static const char *name() { return "QlCreditDefaultSwap"; } };
typedef QuantLib::ext::shared_ptr<DividendVanillaOption> QlDividendVanillaOption;
template <> class objClassName<DividendVanillaOption *> { public: static const char *name() { return "DividendVanillaOption"; } };
template <> class objClassName<QlDividendVanillaOption *> { public: static const char *name() { return "QlDividendVanillaOption"; } };
typedef QuantLib::ext::shared_ptr<ForwardVanillaOption> QlForwardVanillaOption;
template <> class objClassName<ForwardVanillaOption *> { public: static const char *name() { return "ForwardVanillaOption"; } };
template <> class objClassName<QlForwardVanillaOption *> { public: static const char *name() { return "QlForwardVanillaOption"; } };
typedef QuantLib::ext::shared_ptr<MargrabeOption> QlMargrabeOption;
template <> class objClassName<MargrabeOption *> { public: static const char *name() { return "MargrabeOption"; } };
template <> class objClassName<QlMargrabeOption *> { public: static const char *name() { return "QlMargrabeOption"; } };
typedef QuantLib::ext::shared_ptr<MultiAssetOption> QlMultiAssetOption;
template <> class objClassName<MultiAssetOption *> { public: static const char *name() { return "MultiAssetOption"; } };
template <> class objClassName<QlMultiAssetOption *> { public: static const char *name() { return "QlMultiAssetOption"; } };
typedef QuantLib::ext::shared_ptr<OneAssetOption> QlOneAssetOption;
template <> class objClassName<OneAssetOption *> { public: static const char *name() { return "OneAssetOption"; } };
template <> class objClassName<QlOneAssetOption *> { public: static const char *name() { return "QlOneAssetOption"; } };
typedef QuantLib::ext::shared_ptr<Option> QlOption;
template <> class objClassName<Option *> { public: static const char *name() { return "Option"; } };
template <> class objClassName<QlOption *> { public: static const char *name() { return "QlOption"; } };
typedef QuantLib::ext::shared_ptr<QuantoVanillaOption> QlQuantoVanillaOption;
template <> class objClassName<QuantoVanillaOption *> { public: static const char *name() { return "QuantoVanillaOption"; } };
template <> class objClassName<QlQuantoVanillaOption *> { public: static const char *name() { return "QlQuantoVanillaOption"; } };
typedef QuantLib::ext::shared_ptr<Swaption> QlSwaption;
template <> class objClassName<Swaption *> { public: static const char *name() { return "Swaption"; } };
template <> class objClassName<QlSwaption *> { public: static const char *name() { return "QlSwaption"; } };
typedef QuantLib::ext::shared_ptr<SwingExercise> QlSwingExercise;
template <> class objClassName<SwingExercise *> { public: static const char *name() { return "SwingExercise"; } };
template <> class objClassName<QlSwingExercise *> { public: static const char *name() { return "QlSwingExercise"; } };
typedef QuantLib::ext::shared_ptr<VanillaOption> QlVanillaOption;
template <> class objClassName<VanillaOption *> { public: static const char *name() { return "VanillaOption"; } };
template <> class objClassName<QlVanillaOption *> { public: static const char *name() { return "QlVanillaOption"; } };
template <> class objClassName<EuropeanOption *> { public: static const char *name() { return "EuropeanOption"; } };
typedef QuantLib::ext::shared_ptr<Claim> QlClaim;
template <> class objClassName<Claim *> { public: static const char *name() { return "Claim"; } };
template <> class objClassName<QlClaim *> { public: static const char *name() { return "QlClaim"; } };
typedef QuantLib::ext::shared_ptr<DefaultProbabilityTermStructure> QlDefaultProbabilityTermStructure;
template <> class objClassName<DefaultProbabilityTermStructure *> { public: static const char *name() { return "DefaultProbabilityTermStructure"; } };
template <> class objClassName<QlDefaultProbabilityTermStructure *> { public: static const char *name() { return "QlDefaultProbabilityTermStructure"; } };
typedef QuantLib::ext::shared_ptr<SwaptionVolatilityStructure> QlSwaptionVolatilityStructure;
template <> class objClassName<SwaptionVolatilityStructure *> { public: static const char *name() { return "SwaptionVolatilityStructure"; } };
template <> class objClassName<QlSwaptionVolatilityStructure *> { public: static const char *name() { return "QlSwaptionVolatilityStructure"; } };
typedef QuantLib::ext::shared_ptr<SmileSection> QlSmileSection;
template <> class objClassName<SmileSection *> { public: static const char *name() { return "SmileSection"; } };
template <> class objClassName<QlSmileSection *> { public: static const char *name() { return "QlSmileSection"; } };
typedef QuantLib::ext::shared_ptr<QuantoBarrierOption> QlQuantoBarrierOption;
template <> class objClassName<QuantoBarrierOption *> { public: static const char *name() { return "QuantoBarrierOption"; } };
template <> class objClassName<QlQuantoBarrierOption *> { public: static const char *name() { return "QlQuantoBarrierOption"; } };
typedef QuantLib::ext::shared_ptr<QuantoForwardVanillaOption> QlQuantoForwardVanillaOption;
template <> class objClassName<QuantoForwardVanillaOption *> { public: static const char *name() { return "QuantoForwardVanillaOption"; } };
template <> class objClassName<QlQuantoForwardVanillaOption *> { public: static const char *name() { return "QlQuantoForwardVanillaOption"; } };
typedef QuantLib::ext::shared_ptr<BlackCalculator> QlBlackCalculator;
template <> class objClassName<BlackCalculator *> { public: static const char *name() { return "BlackCalculator"; } };
template <> class objClassName<QlBlackCalculator *> { public: static const char *name() { return "QlBlackCalculator"; } };
typedef QuantLib::ext::shared_ptr<BlackScholesCalculator> QlBlackScholesCalculator;
template <> class objClassName<BlackScholesCalculator *> { public: static const char *name() { return "BlackScholesCalculator"; } };
template <> class objClassName<QlBlackScholesCalculator *> { public: static const char *name() { return "QlBlackScholesCalculator"; } };
typedef QuantLib::ext::shared_ptr<ExtOUWithJumpsProcess> QlExtOUWithJumpsProcess;
template <> class objClassName<ExtOUWithJumpsProcess *> { public: static const char *name() { return "ExtOUWithJumpsProcess"; } };
template <> class objClassName<QlExtOUWithJumpsProcess *> { public: static const char *name() { return "QlExtOUWithJumpsProcess"; } };
typedef QuantLib::ext::shared_ptr<GJRGARCHProcess> QlGJRGARCHProcess;
template <> class objClassName<GJRGARCHProcess *> { public: static const char *name() { return "GJRGARCHProcess"; } };
template <> class objClassName<QlGJRGARCHProcess *> { public: static const char *name() { return "QlGJRGARCHProcess"; } };
typedef QuantLib::ext::shared_ptr<HestonProcess> QlHestonProcess;
template <> class objClassName<HestonProcess *> { public: static const char *name() { return "HestonProcess"; } };
template <> class objClassName<QlHestonProcess *> { public: static const char *name() { return "QlHestonProcess"; } };
typedef QuantLib::ext::shared_ptr<BatesProcess> QlBatesProcess;
template <> class objClassName<BatesProcess *> { public: static const char *name() { return "BatesProcess"; } };
template <> class objClassName<QlBatesProcess *> { public: static const char *name() { return "QlBatesProcess"; } };
typedef QuantLib::ext::shared_ptr<HybridHestonHullWhiteProcess> QlHybridHestonHullWhiteProcess;
template <> class objClassName<HybridHestonHullWhiteProcess *> { public: static const char *name() { return "HybridHestonHullWhiteProcess"; } };
template <> class objClassName<QlHybridHestonHullWhiteProcess *> { public: static const char *name() { return "QlHybridHestonHullWhiteProcess"; } };
typedef QuantLib::ext::shared_ptr<KlugeExtOUProcess> QlKlugeExtOUProcess;
template <> class objClassName<KlugeExtOUProcess *> { public: static const char *name() { return "KlugeExtOUProcess"; } };
template <> class objClassName<QlKlugeExtOUProcess *> { public: static const char *name() { return "QlKlugeExtOUProcess"; } };
typedef QuantLib::ext::shared_ptr<LiborForwardModelProcess> QlLiborForwardModelProcess;
template <> class objClassName<LiborForwardModelProcess *> { public: static const char *name() { return "LiborForwardModelProcess"; } };
template <> class objClassName<QlLiborForwardModelProcess *> { public: static const char *name() { return "QlLiborForwardModelProcess"; } };
typedef QuantLib::ext::shared_ptr<StochasticProcessArray> QlStochasticProcessArray;
template <> class objClassName<StochasticProcessArray *> { public: static const char *name() { return "StochasticProcessArray"; } };
template <> class objClassName<QlStochasticProcessArray *> { public: static const char *name() { return "QlStochasticProcessArray"; } };
typedef QuantLib::ext::shared_ptr<VarianceGammaProcess> QlVarianceGammaProcess;
template <> class objClassName<VarianceGammaProcess *> { public: static const char *name() { return "VarianceGammaProcess"; } };
template <> class objClassName<QlVarianceGammaProcess *> { public: static const char *name() { return "QlVarianceGammaProcess"; } };
typedef QuantLib::ext::shared_ptr<Merton76Process> QlMerton76Process;
template <> class objClassName<Merton76Process *> { public: static const char *name() { return "Merton76Process"; } };
template <> class objClassName<QlMerton76Process *> { public: static const char *name() { return "QlMerton76Process"; } };
typedef QuantLib::ext::shared_ptr<HullWhiteProcess> QlHullWhiteProcess;
template <> class objClassName<HullWhiteProcess *> { public: static const char *name() { return "HullWhiteProcess"; } };
template <> class objClassName<QlHullWhiteProcess *> { public: static const char *name() { return "QlHullWhiteProcess"; } };
typedef QuantLib::ext::shared_ptr<HullWhiteForwardProcess> QlHullWhiteForwardProcess;
template <> class objClassName<HullWhiteForwardProcess *> { public: static const char *name() { return "HullWhiteForwardProcess"; } };
template <> class objClassName<QlHullWhiteForwardProcess *> { public: static const char *name() { return "QlHullWhiteForwardProcess"; } };
typedef QuantLib::ext::shared_ptr<ExtendedOrnsteinUhlenbeckProcess> QlExtendedOrnsteinUhlenbeckProcess;
template <> class objClassName<ExtendedOrnsteinUhlenbeckProcess *> { public: static const char *name() { return "ExtendedOrnsteinUhlenbeckProcess"; } };
template <> class objClassName<QlExtendedOrnsteinUhlenbeckProcess *> { public: static const char *name() { return "QlExtendedOrnsteinUhlenbeckProcess"; } };
typedef QuantLib::ext::shared_ptr<CalibratedModel> QlCalibratedModel;
template <> class objClassName<CalibratedModel *> { public: static const char *name() { return "CalibratedModel"; } };
template <> class objClassName<QlCalibratedModel *> { public: static const char *name() { return "QlCalibratedModel"; } };
typedef QuantLib::ext::shared_ptr<G2> QlG2;
template <> class objClassName<G2 *> { public: static const char *name() { return "G2"; } };
template <> class objClassName<QlG2 *> { public: static const char *name() { return "QlG2"; } };
typedef QuantLib::ext::shared_ptr<LmCorrelationModel> QlLmCorrelationModel;
template <> class objClassName<LmCorrelationModel *> { public: static const char *name() { return "LmCorrelationModel"; } };
template <> class objClassName<QlLmCorrelationModel *> { public: static const char *name() { return "QlLmCorrelationModel"; } };
typedef QuantLib::ext::shared_ptr<LmVolatilityModel> QlLmVolatilityModel;
template <> class objClassName<LmVolatilityModel *> { public: static const char *name() { return "LmVolatilityModel"; } };
template <> class objClassName<QlLmVolatilityModel *> { public: static const char *name() { return "QlLmVolatilityModel"; } };
typedef QuantLib::ext::shared_ptr<BatesDetJumpModel> QlBatesDetJumpModel;
template <> class objClassName<BatesDetJumpModel *> { public: static const char *name() { return "BatesDetJumpModel"; } };
template <> class objClassName<QlBatesDetJumpModel *> { public: static const char *name() { return "QlBatesDetJumpModel"; } };
typedef QuantLib::ext::shared_ptr<BatesDoubleExpDetJumpModel> QlBatesDoubleExpDetJumpModel;
template <> class objClassName<BatesDoubleExpDetJumpModel *> { public: static const char *name() { return "BatesDoubleExpDetJumpModel"; } };
template <> class objClassName<QlBatesDoubleExpDetJumpModel *> { public: static const char *name() { return "QlBatesDoubleExpDetJumpModel"; } };
typedef QuantLib::ext::shared_ptr<BatesDoubleExpModel> QlBatesDoubleExpModel;
template <> class objClassName<BatesDoubleExpModel *> { public: static const char *name() { return "BatesDoubleExpModel"; } };
template <> class objClassName<QlBatesDoubleExpModel *> { public: static const char *name() { return "QlBatesDoubleExpModel"; } };
typedef QuantLib::ext::shared_ptr<GJRGARCHModel> QlGJRGARCHModel;
template <> class objClassName<GJRGARCHModel *> { public: static const char *name() { return "GJRGARCHModel"; } };
template <> class objClassName<QlGJRGARCHModel *> { public: static const char *name() { return "QlGJRGARCHModel"; } };
typedef QuantLib::ext::shared_ptr<HestonModel> QlHestonModel;
template <> class objClassName<HestonModel *> { public: static const char *name() { return "HestonModel"; } };
template <> class objClassName<QlHestonModel *> { public: static const char *name() { return "QlHestonModel"; } };
typedef QuantLib::ext::shared_ptr<BatesModel> QlBatesModel;
template <> class objClassName<BatesModel *> { public: static const char *name() { return "BatesModel"; } };
template <> class objClassName<QlBatesModel *> { public: static const char *name() { return "QlBatesModel"; } };
typedef QuantLib::ext::shared_ptr<PiecewiseTimeDependentHestonModel> QlPiecewiseTimeDependentHestonModel;
template <> class objClassName<PiecewiseTimeDependentHestonModel *> { public: static const char *name() { return "PiecewiseTimeDependentHestonModel"; } };
template <> class objClassName<QlPiecewiseTimeDependentHestonModel *> { public: static const char *name() { return "QlPiecewiseTimeDependentHestonModel"; } };
typedef QuantLib::ext::shared_ptr<ShortRateModel> QlShortRateModel;
template <> class objClassName<ShortRateModel *> { public: static const char *name() { return "ShortRateModel"; } };
template <> class objClassName<QlShortRateModel *> { public: static const char *name() { return "QlShortRateModel"; } };
typedef QuantLib::ext::shared_ptr<AffineModel> QlAffineModel;
template <> class objClassName<AffineModel *> { public: static const char *name() { return "AffineModel"; } };
template <> class objClassName<QlAffineModel *> { public: static const char *name() { return "QlAffineModel"; } };
typedef QuantLib::ext::shared_ptr<OneFactorAffineModel> QlOneFactorAffineModel;
template <> class objClassName<OneFactorAffineModel *> { public: static const char *name() { return "OneFactorAffineModel"; } };
template <> class objClassName<QlOneFactorAffineModel *> { public: static const char *name() { return "QlOneFactorAffineModel"; } };
typedef QuantLib::ext::shared_ptr<LiborForwardModel> QlLiborForwardModel;
template <> class objClassName<LiborForwardModel *> { public: static const char *name() { return "LiborForwardModel"; } };
template <> class objClassName<QlLiborForwardModel *> { public: static const char *name() { return "QlLiborForwardModel"; } };
typedef QuantLib::ext::shared_ptr<HullWhite> QlHullWhite;
template <> class objClassName<HullWhite *> { public: static const char *name() { return "HullWhite"; } };
template <> class objClassName<QlHullWhite *> { public: static const char *name() { return "QlHullWhite"; } };
template <> class objClassName<Constraint *> { public: static const char *name() { return "Constraint"; } };
template <> class objClassName<OptimizationMethod *> { public: static const char *name() { return "OptimizationMethod"; } };
typedef QuantLib::ext::shared_ptr<CalibrationHelper> QlCalibrationHelper;
template <> class objClassName<CalibrationHelper *> { public: static const char *name() { return "CalibrationHelper"; } };
template <> class objClassName<QlCalibrationHelper *> { public: static const char *name() { return "QlCalibrationHelper"; } };
typedef QuantLib::ext::shared_ptr<BlackCalibrationHelper> QlBlackCalibrationHelper;
template <> class objClassName<BlackCalibrationHelper *> { public: static const char *name() { return "BlackCalibrationHelper"; } };
template <> class objClassName<QlBlackCalibrationHelper *> { public: static const char *name() { return "QlBlackCalibrationHelper"; } };
template <> class objClassName<EndCriteria *> { public: static const char *name() { return "EndCriteria"; } };
typedef QuantLib::ext::shared_ptr<CapFloor> QlCapFloor;
template <> class objClassName<CapFloor *> { public: static const char *name() { return "CapFloor"; } };
template <> class objClassName<QlCapFloor *> { public: static const char *name() { return "QlCapFloor"; } };
typedef QuantLib::ext::shared_ptr<CapFloorTermVolSurface> QlCapFloorTermVolSurface;
template <> class objClassName<CapFloorTermVolSurface *> { public: static const char *name() { return "CapFloorTermVolSurface"; } };
template <> class objClassName<QlCapFloorTermVolSurface *> { public: static const char *name() { return "QlCapFloorTermVolSurface"; } };
typedef QuantLib::ext::shared_ptr<LocalVolTermStructure> QlLocalVolTermStructure;
template <> class objClassName<LocalVolTermStructure *> { public: static const char *name() { return "LocalVolTermStructure"; } };
template <> class objClassName<QlLocalVolTermStructure *> { public: static const char *name() { return "QlLocalVolTermStructure"; } };
typedef QuantLib::ext::shared_ptr<BlackVarianceCurve> QlBlackVarianceCurve;
template <> class objClassName<BlackVarianceCurve *> { public: static const char *name() { return "BlackVarianceCurve"; } };
template <> class objClassName<QlBlackVarianceCurve *> { public: static const char *name() { return "QlBlackVarianceCurve"; } };
template <> class objClassName<FdmSchemeDesc *> { public: static const char *name() { return "FdmSchemeDesc"; } };
template <> class objClassName<TimeGrid *> { public: static const char *name() { return "TimeGrid"; } };
typedef QuantLib::ext::shared_ptr<Dividend> QlDividend;
template <> class objClassName<Dividend *> { public: static const char *name() { return "Dividend"; } };
template <> class objClassName<QlDividend *> { public: static const char *name() { return "QlDividend"; } };
typedef QuantLib::ext::shared_ptr<Callability> QlCallability;
template <> class objClassName<Callability *> { public: static const char *name() { return "Callability"; } };
template <> class objClassName<QlCallability *> { public: static const char *name() { return "QlCallability"; } };
typedef QuantLib::ext::shared_ptr<CallableBond> QlCallableBond;
template <> class objClassName<CallableBond *> { public: static const char *name() { return "CallableBond"; } };
template <> class objClassName<QlCallableBond *> { public: static const char *name() { return "QlCallableBond"; } };
typedef QuantLib::ext::shared_ptr<ConvertibleBond> QlConvertibleBond;
template <> class objClassName<ConvertibleBond *> { public: static const char *name() { return "ConvertibleBond"; } };
template <> class objClassName<QlConvertibleBond *> { public: static const char *name() { return "QlConvertibleBond"; } };
typedef QuantLib::ext::shared_ptr<CallableBondVolatilityStructure> QlCallableBondVolatilityStructure;
template <> class objClassName<CallableBondVolatilityStructure *> { public: static const char *name() { return "CallableBondVolatilityStructure"; } };
template <> class objClassName<QlCallableBondVolatilityStructure *> { public: static const char *name() { return "QlCallableBondVolatilityStructure"; } };
typedef std::vector<QuantLib::ext::shared_ptr<Coupon> > CouponLeg;
template <> class objClassName<CouponLeg *> { public: static const char *name() { return "CouponLeg"; } };
template <> class objClassName<AnalyticBSMHullWhiteEngine *> {public: static const char *name() {return "AnalyticBSMHullWhiteEngine"; } };
template <> class objClassName<AnalyticBarrierEngine *> {public: static const char *name() {return "AnalyticBarrierEngine"; } };
template <> class objClassName<AnalyticCapFloorEngine *> {public: static const char *name() {return "AnalyticCapFloorEngine"; } };
template <> class objClassName<AnalyticCliquetEngine *> {public: static const char *name() {return "AnalyticCliquetEngine"; } };
template <> class objClassName<AnalyticContinuousFixedLookbackEngine *> {public: static const char *name() {return "AnalyticContinuousFixedLookbackEngine"; } };
template <> class objClassName<AnalyticContinuousFloatingLookbackEngine *> {public: static const char *name() {return "AnalyticContinuousFloatingLookbackEngine"; } };
template <> class objClassName<AnalyticContinuousGeometricAveragePriceAsianEngine *> {public: static const char *name() {return "AnalyticContinuousGeometricAveragePriceAsianEngine"; } };
template <> class objClassName<AnalyticDigitalAmericanEngine *> {public: static const char *name() {return "AnalyticDigitalAmericanEngine"; } };
template <> class objClassName<AnalyticDiscreteGeometricAveragePriceAsianEngine *> {public: static const char *name() {return "AnalyticDiscreteGeometricAveragePriceAsianEngine"; } };
template <> class objClassName<AnalyticDiscreteGeometricAverageStrikeAsianEngine *> {public: static const char *name() {return "AnalyticDiscreteGeometricAverageStrikeAsianEngine"; } };
template <> class objClassName<AnalyticDividendEuropeanEngine *> {public: static const char *name() {return "AnalyticDividendEuropeanEngine"; } };
template <> class objClassName<AnalyticEuropeanEngine *> {public: static const char *name() {return "AnalyticEuropeanEngine"; } };
template <> class objClassName<AnalyticGJRGARCHEngine *> {public: static const char *name() {return "AnalyticGJRGARCHEngine"; } };
template <> class objClassName<AnalyticHestonEngine *> {public: static const char *name() {return "AnalyticHestonEngine"; } };
template <> class objClassName<AnalyticHestonHullWhiteEngine *> {public: static const char *name() {return "AnalyticHestonHullWhiteEngine"; } };
template <> class objClassName<AnalyticPerformanceEngine *> {public: static const char *name() {return "AnalyticPerformanceEngine"; } };
template <> class objClassName<BaroneAdesiWhaleyApproximationEngine *> {public: static const char *name() {return "BaroneAdesiWhaleyApproximationEngine"; } };
template <> class objClassName<BatesDetJumpEngine *> {public: static const char *name() {return "BatesDetJumpEngine"; } };
template <> class objClassName<BatesDoubleExpDetJumpEngine *> {public: static const char *name() {return "BatesDoubleExpDetJumpEngine"; } };
template <> class objClassName<BatesDoubleExpEngine *> {public: static const char *name() {return "BatesDoubleExpEngine"; } };
template <> class objClassName<BatesEngine *> {public: static const char *name() {return "BatesEngine"; } };
template <> class objClassName<BjerksundStenslandApproximationEngine *> {public: static const char *name() {return "BjerksundStenslandApproximationEngine"; } };
template <> class objClassName<BlackCallableFixedRateBondEngine *> {public: static const char *name() {return "BlackCallableFixedRateBondEngine"; } };
template <> class objClassName<BlackCallableZeroCouponBondEngine *> {public: static const char *name() {return "BlackCallableZeroCouponBondEngine"; } };
template <> class objClassName<BlackCapFloorEngine *> {public: static const char *name() {return "BlackCapFloorEngine"; } };
template <> class objClassName<BlackSwaptionEngine *> {public: static const char *name() {return "BlackSwaptionEngine"; } };
template <> class objClassName<DiscountingSwapEngine *> {public: static const char *name() {return "DiscountingSwapEngine"; } };
template <> class objClassName<FFTVanillaEngine *> {public: static const char *name() {return "FFTVanillaEngine"; } };
template <> class objClassName<FdG2SwaptionEngine *> {public: static const char *name() {return "FdG2SwaptionEngine"; } };
template <> class objClassName<FdHullWhiteSwaptionEngine *> {public: static const char *name() {return "FdHullWhiteSwaptionEngine"; } };
template <> class objClassName<G2SwaptionEngine *> {public: static const char *name() {return "G2SwaptionEngine"; } };
template <> class objClassName<IntegralCdsEngine *> {public: static const char *name() {return "IntegralCdsEngine"; } };
template <> class objClassName<IntegralEngine *> {public: static const char *name() {return "IntegralEngine"; } };
template <> class objClassName<JamshidianSwaptionEngine *> {public: static const char *name() {return "JamshidianSwaptionEngine"; } };
template <> class objClassName<JuQuadraticApproximationEngine *> {public: static const char *name() {return "JuQuadraticApproximationEngine"; } };
template <> class objClassName<JumpDiffusionEngine *> {public: static const char *name() {return "JumpDiffusionEngine"; } };
template <> class objClassName<KirkEngine *> {public: static const char *name() {return "KirkEngine"; } };
template <> class objClassName<LfmSwaptionEngine *> {public: static const char *name() {return "LfmSwaptionEngine"; } };
template <> class objClassName<MidPointCdsEngine *> {public: static const char *name() {return "MidPointCdsEngine"; } };
template <> class objClassName<ReplicatingVarianceSwapEngine *> {public: static const char *name() {return "ReplicatingVarianceSwapEngine"; } };
template <> class objClassName<StulzEngine *> {public: static const char *name() {return "StulzEngine"; } };
template <> class objClassName<TreeCallableFixedRateBondEngine *> {public: static const char *name() {return "TreeCallableFixedRateBondEngine"; } };
template <> class objClassName<TreeCallableZeroCouponBondEngine *> {public: static const char *name() {return "TreeCallableZeroCouponBondEngine"; } };
template <> class objClassName<TreeCapFloorEngine *> {public: static const char *name() {return "TreeCapFloorEngine"; } };
template <> class objClassName<TreeSwaptionEngine *> {public: static const char *name() {return "TreeSwaptionEngine"; } };
template <> class objClassName<TreeVanillaSwapEngine *> {public: static const char *name() {return "TreeVanillaSwapEngine"; } };
template <> class objClassName<VarianceGammaEngine *> {public: static const char *name() {return "VarianceGammaEngine"; } };
template <> class objClassName<ConvertibleFloatingRateBond *> {public: static const char *name() {return "ConvertibleFloatingRateBond"; } };
template <> class objClassName<ConvertibleFixedCouponBond *> {public: static const char *name() {return "ConvertibleFixedCouponBond"; } };
template <> class objClassName<ConvertibleZeroCouponBond *> {public: static const char *name() {return "ConvertibleZeroCouponBond"; } };
template <> class objClassName<SoftCallability *> {public: static const char *name() {return "SoftCallability"; } };
template <> class objClassName<EarlyExercise *> {public: static const char *name() {return "EarlyExercise"; } };
template <> class objClassName<BlackScholesMertonProcess *> {public: static const char *name() {return "BlackScholesMertonProcess"; } };
template <> class objClassName<BlackScholesProcess *> {public: static const char *name() {return "BlackScholesProcess"; } };
template <> class objClassName<ExtendedBlackScholesMertonProcess *> {public: static const char *name() {return "ExtendedBlackScholesMertonProcess"; } };
template <> class objClassName<GarmanKohlagenProcess *> {public: static const char *name() {return "GarmanKohlagenProcess"; } };
template <> class objClassName<VegaStressedBlackScholesProcess *> {public: static const char *name() {return "VegaStressedBlackScholesProcess"; } };
template <> class objClassName<BlackConstantVol *> {public: static const char *name() {return "BlackConstantVol"; } };
template <> class objClassName<ImpliedVolTermStructure *> {public: static const char *name() {return "ImpliedVolTermStructure"; } };
template <> class objClassName<FixedDividend *> {public: static const char *name() {return "FixedDividend"; } };
template <> class objClassName<FractionalDividend *> {public: static const char *name() {return "FractionalDividend"; } };
template <> class objClassName<FaceValueAccrualClaim *> {public: static const char *name() {return "FaceValueAccrualClaim"; } };
template <> class objClassName<FaceValueClaim *> {public: static const char *name() {return "FaceValueClaim"; } };
template <> class objClassName<SpreadCdsHelper *> {public: static const char *name() {return "SpreadCdsHelper"; } };
template <> class objClassName<UpfrontCdsHelper *> {public: static const char *name() {return "UpfrontCdsHelper"; } };
template <> class objClassName<BlackKarasinski *> {public: static const char *name() {return "BlackKarasinski"; } };
template <> class objClassName<GeneralizedHullWhite *> {public: static const char *name() {return "GeneralizedHullWhite"; } };
template <> class objClassName<CapHelper *> {public: static const char *name() {return "CapHelper"; } };
template <> class objClassName<HestonModelHelper *> {public: static const char *name() {return "HestonModelHelper"; } };
template <> class objClassName<SwaptionHelper *> {public: static const char *name() {return "SwaptionHelper"; } };
template <> class objClassName<AssetOrNothingPayoff *> {public: static const char *name() {return "AssetOrNothingPayoff"; } };
template <> class objClassName<CashOrNothingPayoff *> {public: static const char *name() {return "CashOrNothingPayoff"; } };
template <> class objClassName<GapPayoff *> {public: static const char *name() {return "GapPayoff"; } };
template <> class objClassName<SuperFundPayoff *> {public: static const char *name() {return "SuperFundPayoff"; } };
template <> class objClassName<SuperSharePayoff *> {public: static const char *name() {return "SuperSharePayoff"; } };
template <> class objClassName<CubicBSplinesFitting *> {public: static const char *name() {return "CubicBSplinesFitting"; } };
template <> class objClassName<ExponentialSplinesFitting *> {public: static const char *name() {return "ExponentialSplinesFitting"; } };
template <> class objClassName<NelsonSiegelFitting *> {public: static const char *name() {return "NelsonSiegelFitting"; } };
template <> class objClassName<SimplePolynomialFitting *> {public: static const char *name() {return "SimplePolynomialFitting"; } };
template <> class objClassName<SvenssonFitting *> {public: static const char *name() {return "SvenssonFitting"; } };
template <> class objClassName<LevenbergMarquardt *> {public: static const char *name() {return "LevenbergMarquardt"; } };
template <> class objClassName<Simplex *> {public: static const char *name() {return "Simplex"; } };
template <> class objClassName<PositiveConstraint *> {public: static const char *name() {return "PositiveConstraint"; } };
template <> class objClassName<NoConstraint *> {public: static const char *name() {return "NoConstraint"; } };
template <> class objClassName<CompositeConstraint *> {public: static const char *name() {return "CompositeConstraint"; } };
template <> class objClassName<BoundaryConstraint *> {public: static const char *name() {return "BoundaryConstraint"; } };
template <> class objClassName<CallableFixedRateBond *> {public: static const char *name() {return "CallableFixedRateBond"; } };
template <> class objClassName<CallableZeroCouponBond *> {public: static const char *name() {return "CallableZeroCouponBond"; } };
template <> class objClassName<ForwardSpreadedTermStructure *> {public: static const char *name() {return "ForwardSpreadedTermStructure"; } };
template <> class objClassName<ZeroSpreadedTermStructure *> {public: static const char *name() {return "ZeroSpreadedTermStructure"; } };
template <> class objClassName<QuantoTermStructure *> {public: static const char *name() {return "QuantoTermStructure"; } };
template <> class objClassName<ImpliedTermStructure *> {public: static const char *name() {return "ImpliedTermStructure"; } };

// DefaultProbabilityHelper is a typedef so we cannot use forward declaration
#ifdef quantlib_default_probability_helpers_hpp
using QuantLib::DefaultProbabilityHelper;
typedef QuantLib::ext::shared_ptr<DefaultProbabilityHelper> QlDefaultProbabilityHelper;
template <> class objClassName<DefaultProbabilityHelper *> { public: static const char *name() { return "DefaultProbabilityHelper"; } };
template <> class objClassName<QlDefaultProbabilityHelper *> { public: static const char *name() { return "QlDefaultProbabilityHelper"; } };
#endif
#ifdef quantlib_fitted_bond_discount_curve_hpp
typedef FittedBondDiscountCurve::FittingMethod FittedBondDiscountCurveFittingMethod;
template <> class objClassName<FittedBondDiscountCurveFittingMethod *> { public: static const char *name() { return "FittedBondDiscountCurveFittingMethod"; } };
#endif
#ifdef quantlib_piecewise_zero_spreaded_term_structure_hpp
using QuantLib::PiecewiseZeroSpreadedTermStructure;
template <> class objClassName<PiecewiseZeroSpreadedTermStructure *> {public: static const char *name() {return "PiecewiseZeroSpreadedTermStructure"; } };
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
