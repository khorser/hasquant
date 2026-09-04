#include <ql/time/date.hpp>
#include <ql/errors.hpp>
#include <string.h>
#include <iterator>
#include <memory>
#include <vector>
#include <boost/optional.hpp>
#include <ql/math/matrix.hpp>
#include <ql/instruments/varianceswap.hpp>
#include <ql/instruments/constnotionalcrosscurrencyswap.hpp>
#include <ql/instruments/constnotionalcrosscurrencybasisswap.hpp>
#include <ql/instruments/constnotionalcrosscurrencyfixedvsfloatingswap.hpp>
// SabrSwaptionVolatilityCube is a typedef of a template instantiation
// (XabrSwaptionVolatilityCube<SwaptionVolCubeSabrModel>), not an ordinary class -- it cannot be
// forward-declared the way every other type below is, so its full header is pulled in here
// instead. InterpolatedSwaptionVolatilityCube is an ordinary class and stays forward-declared.
#include <ql/termstructures/volatility/swaption/sabrswaptionvolatilitycube.hpp>
// NoArbSabrSwaptionVolatilityCube is the same situation one model policy over
// (XabrSwaptionVolatilityCube<SwaptionVolCubeNoArbSabrModel>) -- also a typedef of a template
// instantiation, also pulled in fully rather than forward-declared.
#include <ql/experimental/volatility/noarbsabrswaptionvolatilitycube.hpp>
// TwoFactorModel::ShortRateDynamics is a nested class -- referring to it (even just as a
// shared_ptr<> template argument below) requires TwoFactorModel to be a complete type, so
// (like SabrSwaptionVolatilityCube above) it can't be left as a forward declaration.
#include <ql/models/shortrate/twofactormodel.hpp>

struct HestonSLVFDMLogEntries;

int *qlAllocateInts(size_t size);
double *qlAllocateDoubles(size_t size);

// strdup() for the FFI boundary (Haskell releases it through qlFreeString), tracing both
// halves of the string's lifecycle. The tracing verbs themselves are at the bottom of this
// file, below the ObjClassName table they name their subjects from.
char *tracedup(const char *p);

#ifdef QLTRACK_ALLOCATIONS
# include <fstream>
#endif

namespace QuantLib {
  template <class T> class Handle;
  class Quote;
  class Bond;
  class FixedRateBond;
  class BTP;
  class RendistatoBasket;
  class RendistatoCalculator;
  class RendistatoEquivalentSwapLengthQuote;
  class RendistatoEquivalentSwapSpreadQuote;
  class FixedRateCoupon;
  class CashFlow;
  class FixedVsFloatingSwap;
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
  class CommodityType;
  class UnitOfMeasure;
  class PaymentTerm;
  class UnitOfMeasureConversion;
  class CommodityCurve;
  class CommodityIndex;
  class Commodity;
  class EnergyCommodity;
  class EnergyFuture;
  class EnergySwap;
  class EnergyVanillaSwap;
  class EnergyBasisSwap;
  class CommodityCashFlow;
  class Region;
  class InterestRate;
  class FixedRateBondHelper;
  class DepositRateHelper;
  class YieldTermStructure;
  class FlatForward;
  class PricingEngine;
  class DiscountingBondEngine;
  class Instrument;
  class CompositeInstrument;
  class CustomIborIndex;
  class IborIndex;
  class IborCoupon;
  class OvernightIndexedCoupon;
  class CPICoupon;
  class CPICouponPricer;
  class Index;
  class FloatingRateCouponPricer;
  class CmsCouponPricer;
  class FloatingRateCoupon;
  class DigitalCoupon;
  class RangeAccrualFloatersCoupon;
  class YoYInflationCoupon;
  class CmsCoupon;
  class IrregularSwap;
  class IrregularSwaption;
  class CmsSpreadCoupon;
  class DigitalCmsCoupon;
  class DigitalCmsSpreadCoupon;
  class DigitalReplication;
  class SwapSpreadIndex;
  class StrippedCappedFlooredCoupon;
  class OptionletVolatilityStructure;
  class OptionletStripper2;
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
  class BachelierCalculator;
  class BaroneAdesiWhaleyApproximationEngine;
  class BarrierOption;
  class DoubleBarrierOption;
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
  class AbcdAtmVolCurve;
  class BlackAtmVolCurve;
  class BlackCalculator;
  class BlackDeltaCalculator;
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
  class BlackVolSurface;
  class BlackVolTermStructure;
  class BlackVolatilitySurfaceDelta;
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
  class CapFloorTermVolatilityStructure;
  class CapFloorTermVolCurve;
  class CapFloorTermVolSurface;
  class CapHelper;
  class CashOrNothingPayoff;
  class CdsOption;
  class DefaultProbKey;
  class Issuer;
  class Pool;
  class Basket;
  class DefaultLossModel;
  class SyntheticCDO;
  class NthToDefault;
  class Claim;
  class CompositeConstraint;
  class Constraint;
  class ConvertibleBond;
  class ConvertibleFixedCouponBond;
  class ConvertibleFloatingRateBond;
  class ConvertibleZeroCouponBond;
  class CPIBond;
  class CPICapFloor;
  class CPICapFloorTermPriceSurface;
  class CPICashFlow;
  class CPISwap;
  class CPIVolatilitySurface;
  class CreditDefaultSwap;
  class CubicBSplinesFitting;
  class DefaultProbabilityTermStructure;
  class DeltaVolQuote;
  class DiscountingFxForwardEngine;
  class DiscountingSwapEngine;
  class DiscountingConstNotionalCrossCurrencySwapEngine;
  class Dividend;
  class EarlyExercise;
  class EndCriteria;
  class EquityCashFlow;
  class EquityCashFlowPricer;
  class EquityIndex;
  class EquityQuantoCashFlowPricer;
  class EquityTotalReturnSwap;
  class EuropeanExercise;
  class EuropeanOption;
  class EverestOption;
  class ExchangeRate;
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
  class Fdm1dMesher;
  class FdmInnerValueCalculator;
  class FdmMesher;
  class FdmQuantoHelper;
  struct FdmSchemeDesc;
  class FdmStepConditionComposite;
  class FittedBondDiscountCurve;
  class FixedDividend;
  class ForwardSpreadedTermStructure;
  class FraRateHelper;
  class FractionalDividend;
  class FuturesRateHelper;
  class FxForward;
  class G2;
  class G2ForwardProcess;
  class G2Process;
  class G2SwaptionEngine;
  class GJRGARCHModel;
  class GJRGARCHProcess;
  class GapPayoff;
  class Garch11;
  class GarmanKohlagenProcess;
  class Gaussian1dModel;
  class GeneralizedBlackScholesProcess;
  class GeneralizedHullWhite;
  class Gsr;
  class GridModelLocalVolSurface;
  class HestonBlackVolSurface;
  class HestonModel;
  class HestonModelHelper;
  class HestonProcess;
  class HestonSLVProcess;
  class HestonSLVMCModel;
  class HestonSLVFDMModel;
  class BrownianGeneratorFactory;
  class HistoricalIndexAnalysis;
  class HullWhite;
  class HullWhiteForwardProcess;
  class HullWhiteProcess;
  class HybridHestonHullWhiteProcess;
  class ImpliedTermStructure;
  class ImpliedVolTermStructure;
  class InflationIndex;
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
  class LfmHullWhiteParameterization;
  class LmCorrelationModel;
  class LmVolatilityModel;
  class LocalVolTermStructure;
  class AndreasenHugeLocalVolAdapter;
  class AndreasenHugeVolatilityAdapter;
  class AndreasenHugeVolatilityInterpl;
  class MargrabeOption;
  class MarkovFunctional;
  class Merton76Process;
  class MidPointCdsEngine;
  class MultiAssetOption;
  class MultiCurve;
  class NelsonSiegelFitting;
  class NoArbSabrInterpolatedSmileSection;
  class NoConstraint;
  class NonstandardSwap;
  class NonstandardSwaption;
  class FloatFloatSwap;
  class FloatFloatSwaption;
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
  class QuantoDoubleBarrierOption;
  class QuantoForwardVanillaOption;
  class QuantoTermStructure;
  class QuantoVanillaOption;
  class RebatedExercise;
  class ReplicatingVarianceSwapEngine;
  class Rounding;
  class SabrInterpolatedSmileSection;
  class SabrVolSurface;
  class ShortRateModel;
  class SimplePolynomialFitting;
  class SimpleQuote;
  class Simplex;
  class SmileSection;
  class SoftBarrierOption;
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
  class SviInterpolatedSmileSection;
  class InterpolatedSwaptionVolatilityCube;
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
  class VarianceOption;
  class VegaStressedBlackScholesProcess;
  class VolatilityTermStructure;
  class YearOnYearInflationSwap;
  class YearOnYearInflationSwapHelper;
  class YoYCapFloorTermPriceSurface;
  class YoYInflationCapFloor;
  class YoYInflationCouponPricer;
  class YoYInflationIndex;
  class YoYInflationTermStructure;
  class YoYOptionletVolatilitySurface;
  class ZeroCouponInflationSwap;
  class ZeroCouponInflationSwapHelper;
  class ZeroCouponSwap;
  class ZeroInflationCashFlow;
  class ZeroInflationIndex;
  class ZeroInflationTermStructure;
  class ZeroSpreadedTermStructure;
}

using QuantLib::Handle;
using QuantLib::RelinkableHandle;
using QuantLib::Quote;
using QuantLib::BusinessDayConvention;
using QuantLib::Bond;
using QuantLib::FixedRateBond;
using QuantLib::BTP;
using QuantLib::RendistatoBasket;
using QuantLib::RendistatoCalculator;
using QuantLib::RendistatoEquivalentSwapLengthQuote;
using QuantLib::RendistatoEquivalentSwapSpreadQuote;
using QuantLib::FixedRateCoupon;
using QuantLib::FixedVsFloatingSwap;
using QuantLib::ConstNotionalCrossCurrencySwap;
using QuantLib::ConstNotionalCrossCurrencyBasisSwap;
using QuantLib::ConstNotionalCrossCurrencyFixedVsFloatingSwap;
using QuantLib::DiscountingConstNotionalCrossCurrencySwapEngine;
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
using QuantLib::CommodityType;
using QuantLib::UnitOfMeasure;
using QuantLib::PaymentTerm;
using QuantLib::UnitOfMeasureConversion;
using QuantLib::CommodityCurve;
using QuantLib::CommodityIndex;
using QuantLib::Commodity;
using QuantLib::EnergyCommodity;
using QuantLib::EnergyFuture;
using QuantLib::EnergySwap;
using QuantLib::EnergyVanillaSwap;
using QuantLib::EnergyBasisSwap;
using QuantLib::CommodityCashFlow;
using QuantLib::Region;
using QuantLib::InterestRate;
using QuantLib::FixedRateBondHelper;
using QuantLib::DepositRateHelper;
using QuantLib::YieldTermStructure;
using QuantLib::FlatForward;
using QuantLib::PricingEngine;
using QuantLib::DiscountingBondEngine;
using QuantLib::Instrument;
using QuantLib::CompositeInstrument;
using QuantLib::CustomIborIndex;
using QuantLib::IborIndex;
using QuantLib::IborCoupon;
using QuantLib::OvernightIndexedCoupon;
using QuantLib::CPICoupon;
using QuantLib::CPICouponPricer;
using QuantLib::Index;
using QuantLib::FloatingRateCouponPricer;
using QuantLib::CmsCouponPricer;
using QuantLib::FloatingRateCoupon;
using QuantLib::DigitalCoupon;
using QuantLib::RangeAccrualFloatersCoupon;
using QuantLib::YoYInflationCoupon;
using QuantLib::CmsCoupon;
using QuantLib::CmsSpreadCoupon;
using QuantLib::DigitalCmsCoupon;
using QuantLib::DigitalCmsSpreadCoupon;
using QuantLib::DigitalReplication;
using QuantLib::SwapSpreadIndex;
using QuantLib::StrippedCappedFlooredCoupon;
using QuantLib::OptionletVolatilityStructure;
using QuantLib::OptionletStripper2;
using QuantLib::Coupon;
using QuantLib::CashFlow;
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
using QuantLib::BachelierCalculator;
using QuantLib::BaroneAdesiWhaleyApproximationEngine;
using QuantLib::BarrierOption;
using QuantLib::DoubleBarrierOption;
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
using QuantLib::AbcdAtmVolCurve;
using QuantLib::BlackAtmVolCurve;
using QuantLib::BlackCalculator;
using QuantLib::BlackDeltaCalculator;
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
using QuantLib::BlackVolSurface;
using QuantLib::BlackVolTermStructure;
using QuantLib::BlackVolatilitySurfaceDelta;
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
using QuantLib::CapFloorTermVolatilityStructure;
using QuantLib::CapFloorTermVolCurve;
using QuantLib::CapFloorTermVolSurface;
using QuantLib::CapHelper;
using QuantLib::CashOrNothingPayoff;
using QuantLib::CdsOption;
using QuantLib::DefaultProbKey;
using QuantLib::Issuer;
using QuantLib::Pool;
using QuantLib::Basket;
using QuantLib::DefaultLossModel;
using QuantLib::SyntheticCDO;
using QuantLib::NthToDefault;
using QuantLib::Claim;
using QuantLib::CompositeConstraint;
using QuantLib::Constraint;
using QuantLib::ConvertibleBond;
using QuantLib::ConvertibleFixedCouponBond;
using QuantLib::ConvertibleFloatingRateBond;
using QuantLib::ConvertibleZeroCouponBond;
using QuantLib::CPIBond;
using QuantLib::CPICapFloor;
using QuantLib::CPICapFloorTermPriceSurface;
using QuantLib::CPICashFlow;
using QuantLib::CPISwap;
using QuantLib::CPIVolatilitySurface;
using QuantLib::CreditDefaultSwap;
using QuantLib::CubicBSplinesFitting;
using QuantLib::DefaultProbabilityTermStructure;
using QuantLib::DeltaVolQuote;
using QuantLib::DiscountingFxForwardEngine;
using QuantLib::DiscountingSwapEngine;
using QuantLib::Dividend;
using QuantLib::EarlyExercise;
using QuantLib::EndCriteria;
using QuantLib::EquityCashFlow;
using QuantLib::EquityCashFlowPricer;
using QuantLib::EquityIndex;
using QuantLib::EquityQuantoCashFlowPricer;
using QuantLib::EquityTotalReturnSwap;
using QuantLib::EuropeanExercise;
using QuantLib::EuropeanOption;
using QuantLib::EverestOption;
using QuantLib::ExchangeRate;
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
using QuantLib::Fdm1dMesher;
using QuantLib::FdmInnerValueCalculator;
using QuantLib::FdmMesher;
using QuantLib::FdmQuantoHelper;
using QuantLib::FdmSchemeDesc;
using QuantLib::FdmStepConditionComposite;
using QuantLib::FittedBondDiscountCurve;
using QuantLib::FixedDividend;
using QuantLib::ForwardSpreadedTermStructure;
using QuantLib::FraRateHelper;
using QuantLib::FractionalDividend;
using QuantLib::FuturesRateHelper;
using QuantLib::FxForward;
using QuantLib::G2;
using QuantLib::G2ForwardProcess;
using QuantLib::G2Process;
using QuantLib::G2SwaptionEngine;
using QuantLib::GJRGARCHModel;
using QuantLib::GJRGARCHProcess;
using QuantLib::GapPayoff;
using QuantLib::Garch11;
using QuantLib::GarmanKohlagenProcess;
using QuantLib::Gaussian1dModel;
using QuantLib::GeneralizedBlackScholesProcess;
using QuantLib::GeneralizedHullWhite;
using QuantLib::Gsr;
using QuantLib::GridModelLocalVolSurface;
using QuantLib::HestonBlackVolSurface;
using QuantLib::HestonModel;
using QuantLib::HestonModelHelper;
using QuantLib::HestonProcess;
using QuantLib::HestonSLVProcess;
using QuantLib::HestonSLVMCModel;
using QuantLib::HestonSLVFDMModel;
using QuantLib::BrownianGeneratorFactory;
using QuantLib::HistoricalIndexAnalysis;
using QuantLib::HullWhite;
using QuantLib::HullWhiteForwardProcess;
using QuantLib::HullWhiteProcess;
using QuantLib::HybridHestonHullWhiteProcess;
using QuantLib::ImpliedTermStructure;
using QuantLib::ImpliedVolTermStructure;
using QuantLib::InflationIndex;
using QuantLib::IntegralCdsEngine;
using QuantLib::IntegralEngine;
using QuantLib::InterestRateIndex;
using QuantLib::JamshidianSwaptionEngine;
using QuantLib::JuQuadraticApproximationEngine;
using QuantLib::JumpDiffusionEngine;
using QuantLib::KirkEngine;
using QuantLib::KlugeExtOUProcess;
using QuantLib::Leg;
using QuantLib::LevenbergMarquardt;
using QuantLib::LfmSwaptionEngine;
using QuantLib::LiborForwardModel;
using QuantLib::LiborForwardModelProcess;
using QuantLib::LfmHullWhiteParameterization;
using QuantLib::LmCorrelationModel;
using QuantLib::LmVolatilityModel;
using QuantLib::LocalVolTermStructure;
using QuantLib::AndreasenHugeLocalVolAdapter;
using QuantLib::AndreasenHugeVolatilityAdapter;
using QuantLib::AndreasenHugeVolatilityInterpl;
using QuantLib::MargrabeOption;
using QuantLib::MarkovFunctional;
using QuantLib::Merton76Process;
using QuantLib::MidPointCdsEngine;
using QuantLib::MultiAssetOption;
using QuantLib::MultiCurve;
using QuantLib::NelsonSiegelFitting;
using QuantLib::NoArbSabrInterpolatedSmileSection;
using QuantLib::NoArbSabrSwaptionVolatilityCube;
using QuantLib::NoConstraint;
using QuantLib::NonstandardSwap;
using QuantLib::NonstandardSwaption;
using QuantLib::FloatFloatSwap;
using QuantLib::FloatFloatSwaption;
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
using QuantLib::Period;
using QuantLib::PiecewiseTimeDependentHestonModel;
using QuantLib::PlainVanillaPayoff;
using QuantLib::PositiveConstraint;
using QuantLib::QuantoBarrierOption;
using QuantLib::QuantoDoubleBarrierOption;
using QuantLib::QuantoForwardVanillaOption;
using QuantLib::QuantoTermStructure;
using QuantLib::QuantoVanillaOption;
using QuantLib::RebatedExercise;
using QuantLib::ReplicatingVarianceSwapEngine;
using QuantLib::Rounding;
using QuantLib::SabrInterpolatedSmileSection;
using QuantLib::SabrVolSurface;
using QuantLib::ShortRateModel;
using QuantLib::SimplePolynomialFitting;
using QuantLib::SimpleQuote;
using QuantLib::Simplex;
using QuantLib::SmileSection;
using QuantLib::SoftBarrierOption;
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
using QuantLib::SviInterpolatedSmileSection;
using QuantLib::InterpolatedSwaptionVolatilityCube;
using QuantLib::SabrSwaptionVolatilityCube;
using QuantLib::Swap;
using QuantLib::SwapIndex;
using QuantLib::SwapRateHelper;
using QuantLib::Swaption;
using QuantLib::SwaptionHelper;
using QuantLib::SwaptionVolatilityStructure;
using QuantLib::SwingExercise;
using QuantLib::TermStructure;
using QuantLib::TimeGrid;
using QuantLib::TimeUnit;
using QuantLib::TreeCallableFixedRateBondEngine;
using QuantLib::TreeCallableZeroCouponBondEngine;
using QuantLib::TreeCapFloorEngine;
using QuantLib::TreeSwaptionEngine;
using QuantLib::TreeVanillaSwapEngine;
using QuantLib::TwoFactorModel;
using QuantLib::TypePayoff;
using QuantLib::UpfrontCdsHelper;
using QuantLib::VanillaOption;
using QuantLib::VanillaSwap;
using QuantLib::VarianceGammaEngine;
using QuantLib::VarianceGammaProcess;
using QuantLib::VarianceOption;
using QuantLib::VarianceSwap;
using QuantLib::VegaStressedBlackScholesProcess;
using QuantLib::VolatilityTermStructure;
using QuantLib::YearOnYearInflationSwap;
using QuantLib::YearOnYearInflationSwapHelper;
using QuantLib::YoYCapFloorTermPriceSurface;
using QuantLib::YoYInflationCapFloor;
using QuantLib::YoYInflationCouponPricer;
using QuantLib::YoYInflationIndex;
using QuantLib::YoYInflationTermStructure;
using QuantLib::YoYOptionletVolatilitySurface;
using QuantLib::ZeroCouponInflationSwap;
using QuantLib::ZeroCouponInflationSwapHelper;
using QuantLib::ZeroCouponSwap;
using QuantLib::ZeroInflationCashFlow;
using QuantLib::ZeroInflationIndex;
using QuantLib::ZeroInflationTermStructure;
using QuantLib::ZeroSpreadedTermStructure;
using QuantLib::Date;
using QuantLib::Matrix;
using QuantLib::ext::shared_ptr;
using QuantLib::ext::optional;

class PolymorphicPathGenerator;
class PolymorphicGaussianRsg;

// Haskell CRateHelper is actually a pointer to a shared_ptr, because rate helpers are used via
// shared_ptr in QuantLib and have no Handle-based counterpart upstream.
// A Quote is a Handle, not a bare shared_ptr, so that a RelinkableHandle can be passed wherever
// a quote is expected: copies of a Handle share one Link, which is what makes a linkTo()
// propagate to everything already built on it. Handle constructs implicitly from nothing (the
// ctor is explicit) but *arg(x) recovers the shared_ptr where one is needed. Mirrors
// QlYieldTermStructure below; see the invariant note there before touching either.
using QlQuote = Handle<Quote>;
// RelinkableHandle publicly inherits Handle, so a relinkable quote IS a QlQuote and needs no
// separate parameter type -- same reasoning as QlRelinkableYieldTermStructure below.
using QlRelinkableQuote = RelinkableHandle<Quote>;
// A curve is a Handle, not a bare shared_ptr, so that a RelinkableHandle can be passed
// wherever a curve is expected: copies of a Handle share one Link, which is what makes a
// linkTo() propagate to everything already built on it. Handle constructs implicitly from
// nothing (the ctor is explicit) but *arg(x) recovers the shared_ptr where one is needed.
using QlYieldTermStructure = Handle<YieldTermStructure>;
// RelinkableHandle publicly inherits Handle, so a relinkable curve IS a QlYieldTermStructure
// and needs no separate parameter type: it goes wherever a curve goes, through the ordinary
// Upcastable machinery, and the upcast copy shares its Link so relinking still propagates.
using QlRelinkableYieldTermStructure = RelinkableHandle<YieldTermStructure>;
using QlPricingEngine = shared_ptr<PricingEngine>;
using QlIborIndex = shared_ptr<IborIndex>;
using QlIndex = shared_ptr<Index>;
using QlFloatingRateCouponPricer = shared_ptr<FloatingRateCouponPricer>;
using QlCmsCouponPricer = shared_ptr<CmsCouponPricer>;
using QlFloatingRateCoupon = shared_ptr<FloatingRateCoupon>;
using QlDigitalCoupon = shared_ptr<DigitalCoupon>;
using QlRangeAccrualFloatersCoupon = shared_ptr<RangeAccrualFloatersCoupon>;
using QlYoYInflationCoupon = shared_ptr<YoYInflationCoupon>;
using QlCmsCoupon = shared_ptr<CmsCoupon>;
using QlIborCoupon = shared_ptr<IborCoupon>;
using QlOvernightIndexedCoupon = shared_ptr<OvernightIndexedCoupon>;
using QlCPICoupon = shared_ptr<CPICoupon>;
using QlCPICouponPricer = shared_ptr<CPICouponPricer>;
using QlDigitalCmsCoupon = shared_ptr<DigitalCmsCoupon>;
using QlDigitalCmsSpreadCoupon = shared_ptr<DigitalCmsSpreadCoupon>;
using QlDigitalReplication = shared_ptr<DigitalReplication>;
using QlSwapSpreadIndex = shared_ptr<SwapSpreadIndex>;
using QlStrippedCappedFlooredCoupon = shared_ptr<StrippedCappedFlooredCoupon>;
// A vol structure is a Handle, same reasoning as QlBlackVolTermStructure/QlSwaptionVolatilityStructure below.
using QlOptionletVolatilityStructure = Handle<OptionletVolatilityStructure>;
using QlRelinkableOptionletVolatilityStructure = RelinkableHandle<OptionletVolatilityStructure>;
using QlInstrument = shared_ptr<Instrument>;
using QlBond = shared_ptr<Bond>;
using QlFixedRateBond = shared_ptr<FixedRateBond>;
using QlBTP = shared_ptr<BTP>;
using QlRendistatoBasket = shared_ptr<RendistatoBasket>;
using QlRendistatoCalculator = shared_ptr<RendistatoCalculator>;
using QlForward = shared_ptr<Forward>;
using QlBondForward = shared_ptr<BondForward>;
using QlForwardRateAgreement = shared_ptr<ForwardRateAgreement>;
using QlAffineModel = shared_ptr<AffineModel>;
using QlAmericanExercise = shared_ptr<AmericanExercise>;
using QlAssetSwap = shared_ptr<AssetSwap>;
using QlBMAIndex = shared_ptr<BMAIndex>;
using QlBMASwap = shared_ptr<BMASwap>;
using QlBarrierOption = shared_ptr<BarrierOption>;
using QlDoubleBarrierOption = shared_ptr<DoubleBarrierOption>;
using QlBachelierCalculator = shared_ptr<BachelierCalculator>;
using QlBasketPayoff = shared_ptr<BasketPayoff>;
using QlBatesDetJumpModel = shared_ptr<BatesDetJumpModel>;
using QlBatesDoubleExpDetJumpModel = shared_ptr<BatesDoubleExpDetJumpModel>;
using QlBatesDoubleExpModel = shared_ptr<BatesDoubleExpModel>;
using QlBatesModel = shared_ptr<BatesModel>;
using QlBatesProcess = shared_ptr<BatesProcess>;
using QlBermudanExercise = shared_ptr<BermudanExercise>;
// BlackAtmVolCurve is the family root: upstream speaks Handle<BlackAtmVolCurve> itself
// (SabrVolSurface's ctor/atmCurve(), VolatilityCube), same reasoning as
// QlOptionletVolatilityStructure/QlSwaptionVolatilityStructure/QlBlackVolTermStructure above --
// Handle, not shared_ptr. AbcdAtmVolCurve/SabrVolSurface are dedicated leaves with their own
// calc/getters (per CLAUDE.md), so each gets its own shared_ptr-wrapped type, same as
// QlSabrSwaptionVolatilityCube/QlInterpolatedSwaptionVolatilityCube under the Handle-wrapped
// QlSwaptionVolatilityStructure root.
using QlBlackAtmVolCurve = Handle<BlackAtmVolCurve>;
using QlAbcdAtmVolCurve = shared_ptr<AbcdAtmVolCurve>;
// BlackVolSurface itself is never spoken of as Handle<BlackVolSurface> upstream (grep confirms),
// so it's a plain shared_ptr intermediate -- only used to route SabrVolSurface's Upcastable chain
// through its own smileSection getter, exactly like QlFixedVsFloatingSwap routes VanillaSwap's
// upcast chain up to QlSwap.
using QlBlackVolSurface = shared_ptr<BlackVolSurface>;
using QlSabrVolSurface = shared_ptr<SabrVolSurface>;
using QlBlackCalculator = shared_ptr<BlackCalculator>;
using QlBlackCalibrationHelper = shared_ptr<BlackCalibrationHelper>;
using QlBlackProcess = shared_ptr<BlackProcess>;
using QlBlackScholesCalculator = shared_ptr<BlackScholesCalculator>;
using QlBlackVarianceCurve = shared_ptr<BlackVarianceCurve>;
using QlBlackVolatilitySurfaceDelta = shared_ptr<BlackVolatilitySurfaceDelta>;
// A vol structure is a Handle, same reasoning as QlYieldTermStructure/QlQuote above -- upstream
// itself speaks Handle<BlackVolTermStructure> throughout, unlike the VolatilityTermStructure
// base (never a Handle upstream, confirmed by grep; stays shared_ptr, same as QlTermStructure).
using QlBlackVolTermStructure = Handle<BlackVolTermStructure>;
using QlRelinkableBlackVolTermStructure = RelinkableHandle<BlackVolTermStructure>;
using QlBondHelper = shared_ptr<BondHelper>;
using QlCalibratedModel = shared_ptr<CalibratedModel>;
using QlCalibrationHelper = shared_ptr<CalibrationHelper>;
using QlCallability = shared_ptr<Callability>;
using QlCallableBond = shared_ptr<CallableBond>;
using QlCallableBondVolatilityStructure = shared_ptr<CallableBondVolatilityStructure>;
using QlCapFloor = shared_ptr<CapFloor>;
// Unlike QlOptionletVolatilityStructure/QlSwaptionVolatilityStructure/QlBlackVolTermStructure,
// upstream never speaks Handle<CapFloorTermVolatilityStructure> anywhere (grep confirms only
// Handle<CapFloorTermVolCurve>, in the still-unbound OptionletStripper2, and
// shared_ptr<CapFloorTermVolSurface>, in OptionletStripper1) -- shared_ptr, like
// QlVolatilityTermStructure/QlCapFloorTermVolSurface themselves.
using QlCapFloorTermVolatilityStructure = shared_ptr<CapFloorTermVolatilityStructure>;
using QlCapFloorTermVolCurve = shared_ptr<CapFloorTermVolCurve>;
using QlCapFloorTermVolSurface = shared_ptr<CapFloorTermVolSurface>;
using QlCashFlow = shared_ptr<CashFlow>;
// CommodityCurve is a plain TermStructure subclass, constructed and consumed directly by value
// (basisOfCurve_ is a shared_ptr<CommodityCurve>, never a Handle) -- shared_ptr-wrapped, same
// reasoning as QlTermStructure/QlCallableBondVolatilityStructure/QlDefaultProbabilityTermStructure.
using QlCommodityCurve = shared_ptr<CommodityCurve>;
// CommodityIndex is likewise shared_ptr-wrapped: Index leaves in general are (QlIndex,
// QlEquityIndex above), and CommodityIndex's own forwardCurve_ member is the shared_ptr
// QlCommodityCurve above, never a Handle.
using QlCommodityIndex = shared_ptr<CommodityIndex>;
// Commodity/EnergyCommodity are abstract-here (no bindable constructor -- Commodity is never
// constructed directly upstream, and EnergyCommodity::quantity() is pure virtual), reachable only
// as an upcast target once a Stage-6 leaf (EnergyFuture, EnergyVanillaSwap, EnergyBasisSwap) exists.
using QlCommodity = shared_ptr<Commodity>;
using QlEnergyCommodity = shared_ptr<EnergyCommodity>;
using QlEnergyFuture = shared_ptr<EnergyFuture>;
// EnergySwap binds no constructor (its own performCalculations is never overridden, so calling it
// falls through to Instrument::performCalculations's QL_REQUIRE(engine_, ...) and throws) --
// reachable only as an upcast target from EnergyVanillaSwap/EnergyBasisSwap, exactly like
// FixedVsFloatingSwap/VanillaSwap.
using QlEnergySwap = shared_ptr<EnergySwap>;
using QlEnergyVanillaSwap = shared_ptr<EnergyVanillaSwap>;
using QlEnergyBasisSwap = shared_ptr<EnergyBasisSwap>;
using QlCommodityCashFlow = shared_ptr<CommodityCashFlow>;
using QlCdsOption = shared_ptr<CdsOption>;
using QlPool = shared_ptr<Pool>;
using QlBasket = shared_ptr<Basket>;
using QlDefaultLossModel = shared_ptr<DefaultLossModel>;
using QlSyntheticCDO = shared_ptr<SyntheticCDO>;
using QlNthToDefault = shared_ptr<NthToDefault>;
using QlClaim = shared_ptr<Claim>;
using QlConvertibleBond = shared_ptr<ConvertibleBond>;
using QlCPIBond = shared_ptr<CPIBond>;
using QlCPICapFloor = shared_ptr<CPICapFloor>;
// A plain TermStructure leaf like CommodityCurve/ZeroInflationTermStructure -- shared_ptr, not
// a Handle; wrapped into Handle<CPICapFloorTermPriceSurface> at the point of use
// (InterpolatingCPICapFloorEngine's ctor).
using QlCPICapFloorTermPriceSurface = shared_ptr<CPICapFloorTermPriceSurface>;
using QlCPICashFlow = shared_ptr<CPICashFlow>;
using QlCPISwap = shared_ptr<CPISwap>;
// A VolatilityTermStructure family member like YoYOptionletVolatilitySurface -- Handle, not a
// plain shared_ptr.
using QlCPIVolatilitySurface = Handle<CPIVolatilitySurface>;
using QlCreditDefaultSwap = shared_ptr<CreditDefaultSwap>;
using QlDefaultProbabilityTermStructure = shared_ptr<DefaultProbabilityTermStructure>;
using QlDeltaVolQuote = shared_ptr<DeltaVolQuote>;
using QlDividend = shared_ptr<Dividend>;
using QlEquityCashFlow = shared_ptr<EquityCashFlow>;
using QlEquityCashFlowPricer = shared_ptr<EquityCashFlowPricer>;
using QlEquityIndex = shared_ptr<EquityIndex>;
using QlEquityQuantoCashFlowPricer = shared_ptr<EquityQuantoCashFlowPricer>;
using QlEquityTotalReturnSwap = shared_ptr<EquityTotalReturnSwap>;
using QlEuropeanExercise = shared_ptr<EuropeanExercise>;
using QlExercise = shared_ptr<Exercise>;
using QlRebatedExercise = shared_ptr<RebatedExercise>;
using QlExtOUWithJumpsProcess = shared_ptr<ExtOUWithJumpsProcess>;
using QlExtendedOrnsteinUhlenbeckProcess = shared_ptr<ExtendedOrnsteinUhlenbeckProcess>;
using QlFdm1dMesher = shared_ptr<Fdm1dMesher>;
using QlFdmInnerValueCalculator = shared_ptr<FdmInnerValueCalculator>;
using QlFdmMesher = shared_ptr<FdmMesher>;
using QlFdmQuantoHelper = shared_ptr<FdmQuantoHelper>;
using QlFittedBondDiscountCurve = shared_ptr<FittedBondDiscountCurve>;
using QlFxForward = shared_ptr<FxForward>;
using QlG2 = shared_ptr<G2>;
using QlG2ForwardProcess = shared_ptr<G2ForwardProcess>;
using QlG2Process = shared_ptr<G2Process>;
using QlGJRGARCHModel = shared_ptr<GJRGARCHModel>;
using QlGJRGARCHProcess = shared_ptr<GJRGARCHProcess>;
using QlGaussian1dModel = shared_ptr<Gaussian1dModel>;
using QlGeneralizedBlackScholesProcess = shared_ptr<GeneralizedBlackScholesProcess>;
using QlGsr = shared_ptr<Gsr>;
using QlGridModelLocalVolSurface = shared_ptr<GridModelLocalVolSurface>;
using QlHestonModel = shared_ptr<HestonModel>;
using QlHestonProcess = shared_ptr<HestonProcess>;
using QlHestonSLVProcess = shared_ptr<HestonSLVProcess>;
using QlHestonSLVMCModel = shared_ptr<HestonSLVMCModel>;
using QlHestonSLVFDMModel = shared_ptr<HestonSLVFDMModel>;
using QlBrownianGeneratorFactory = shared_ptr<BrownianGeneratorFactory>;
using QlHistoricalIndexAnalysis = shared_ptr<HistoricalIndexAnalysis>;
using QlHullWhite = shared_ptr<HullWhite>;
using QlHullWhiteForwardProcess = shared_ptr<HullWhiteForwardProcess>;
using QlHullWhiteProcess = shared_ptr<HullWhiteProcess>;
using QlHybridHestonHullWhiteProcess = shared_ptr<HybridHestonHullWhiteProcess>;
using QlInflationIndex = shared_ptr<InflationIndex>;
using QlInterestRateIndex = shared_ptr<InterestRateIndex>;
using QlKlugeExtOUProcess = shared_ptr<KlugeExtOUProcess>;
using QlLiborForwardModel = shared_ptr<LiborForwardModel>;
using QlLiborForwardModelProcess = shared_ptr<LiborForwardModelProcess>;
using QlLfmHullWhiteParameterization = shared_ptr<LfmHullWhiteParameterization>;
using QlLmCorrelationModel = shared_ptr<LmCorrelationModel>;
using QlLmVolatilityModel = shared_ptr<LmVolatilityModel>;
using QlLocalVolTermStructure = shared_ptr<LocalVolTermStructure>;
using QlAndreasenHugeVolatilityInterpl = shared_ptr<AndreasenHugeVolatilityInterpl>;
using QlEverestOption = shared_ptr<EverestOption>;
using QlMargrabeOption = shared_ptr<MargrabeOption>;
using QlMarkovFunctional = shared_ptr<MarkovFunctional>;
using QlMerton76Process = shared_ptr<Merton76Process>;
using QlMultiAssetOption = shared_ptr<MultiAssetOption>;
// MultiCurve is enable_shared_from_this and upstream's own doc comment says "This must be a
// shared pointer" -- bound as a standalone leaf type (own Finalizable instance, no Upcastable
// parent: it isn't a TermStructure), same shape as e.g. QlSwapRateHelper.
using QlMultiCurve = shared_ptr<MultiCurve>;
using QlNonstandardSwap = shared_ptr<NonstandardSwap>;
using QlNonstandardSwaption = shared_ptr<NonstandardSwaption>;
using QlFloatFloatSwap = shared_ptr<FloatFloatSwap>;
using QlFloatFloatSwaption = shared_ptr<FloatFloatSwaption>;
using QlOISRateHelper = shared_ptr<OISRateHelper>;
using QlOneAssetOption = shared_ptr<OneAssetOption>;
using QlOneFactorAffineModel = shared_ptr<OneFactorAffineModel>;
using QlOption = shared_ptr<Option>;
// OptionletStripper1 is never exposed to Haskell (see qlOptionletStripper1 above), but
// OptionletStripper2 has its own diagnostic getters (atmCapFloorStrikes/atmCapFloorPrices/
// spreadsVol), so it gets its own shared_ptr-wrapped leaf, same as QlSabrInterpolatedSmileSection.
using QlOptionletStripper2 = shared_ptr<OptionletStripper2>;
using QlOvernightIndex = shared_ptr<OvernightIndex>;
using QlOvernightIndexedSwap = shared_ptr<OvernightIndexedSwap>;
using QlOvernightIndexedSwapIndex = shared_ptr<OvernightIndexedSwapIndex>;
using QlPayoff = shared_ptr<Payoff>;
using QlPercentageStrikePayoff = shared_ptr<PercentageStrikePayoff>;
using QlPiecewiseTimeDependentHestonModel = shared_ptr<PiecewiseTimeDependentHestonModel>;
using QlPlainVanillaPayoff = shared_ptr<PlainVanillaPayoff>;
using QlQuantoBarrierOption = shared_ptr<QuantoBarrierOption>;
using QlQuantoDoubleBarrierOption = shared_ptr<QuantoDoubleBarrierOption>;
using QlQuantoForwardVanillaOption = shared_ptr<QuantoForwardVanillaOption>;
using QlQuantoVanillaOption = shared_ptr<QuantoVanillaOption>;
using QlSabrInterpolatedSmileSection = shared_ptr<SabrInterpolatedSmileSection>;
using QlShortRateDynamics = shared_ptr<TwoFactorModel::ShortRateDynamics>;
using QlShortRateModel = shared_ptr<ShortRateModel>;
using QlSimpleQuote = shared_ptr<SimpleQuote>;
using QlSmileSection = shared_ptr<SmileSection>;
using QlSoftBarrierOption = shared_ptr<SoftBarrierOption>;
using QlStochasticProcess1D = shared_ptr<StochasticProcess1D>;
using QlStochasticProcess = shared_ptr<StochasticProcess>;
using QlStochasticProcessArray = shared_ptr<StochasticProcessArray>;
using QlStrikedTypePayoff = shared_ptr<StrikedTypePayoff>;
using QlSwap = shared_ptr<Swap>;
using QlIrregularSwap = shared_ptr<QuantLib::IrregularSwap>;
using QlIrregularSwaption = shared_ptr<QuantLib::IrregularSwaption>;
using QlFixedVsFloatingSwap = shared_ptr<FixedVsFloatingSwap>;
using QlConstNotionalCrossCurrencySwap = shared_ptr<ConstNotionalCrossCurrencySwap>;
using QlConstNotionalCrossCurrencyBasisSwap = shared_ptr<ConstNotionalCrossCurrencyBasisSwap>;
using QlConstNotionalCrossCurrencyFixedVsFloatingSwap = shared_ptr<ConstNotionalCrossCurrencyFixedVsFloatingSwap>;
// SviInterpolatedSmileSection is a dedicated leaf, same shape/reasoning as
// QlSabrInterpolatedSmileSection above.
using QlSviInterpolatedSmileSection = shared_ptr<SviInterpolatedSmileSection>;
// NoArbSabrInterpolatedSmileSection is a dedicated leaf, same shape/reasoning as
// QlSabrInterpolatedSmileSection above.
using QlNoArbSabrInterpolatedSmileSection = shared_ptr<NoArbSabrInterpolatedSmileSection>;
using QlSwapIndex = shared_ptr<SwapIndex>;
using QlSwapRateHelper = shared_ptr<SwapRateHelper>;
using QlSwaption = shared_ptr<Swaption>;
using QlSwaptionHelper = shared_ptr<SwaptionHelper>;
using QlSabrSwaptionVolatilityCube = shared_ptr<SabrSwaptionVolatilityCube>;
using QlNoArbSabrSwaptionVolatilityCube = shared_ptr<NoArbSabrSwaptionVolatilityCube>;
using QlInterpolatedSwaptionVolatilityCube = shared_ptr<InterpolatedSwaptionVolatilityCube>;
// A vol structure is a Handle, same reasoning as QlBlackVolTermStructure above.
using QlSwaptionVolatilityStructure = Handle<SwaptionVolatilityStructure>;
using QlRelinkableSwaptionVolatilityStructure = RelinkableHandle<SwaptionVolatilityStructure>;
using QlSwingExercise = shared_ptr<SwingExercise>;
using QlTermStructure = shared_ptr<TermStructure>;
// EndCriteria/OptimizationMethod are boxed as shared_ptr (not left raw/single-owner) because
// FittedBondDiscountCurve's fitting methods, SabrInterpolatedSmileSection, and
// SabrSwaptionVolatilityCube all store one as a shared_ptr member for their own full lifetime --
// a raw Haskell-finalized pointer handed into that slot would dangle once Haskell's own
// ForeignPtr is collected. The two purely-synchronous consumers (qlOptimize,
// qlGsrCalibrateVolatilitiesIterative/qlCalibratedModelCalibrate's method/endCriteria args) are
// unaffected -- they only ever dereference the box within one call.
using QlOptimizationMethod = shared_ptr<OptimizationMethod>;
using QlEndCriteria = shared_ptr<EndCriteria>;
using QlTypePayoff = shared_ptr<TypePayoff>;
using QlVanillaOption = shared_ptr<VanillaOption>;
using QlVanillaSwap = shared_ptr<VanillaSwap>;
using QlVarianceGammaProcess = shared_ptr<VarianceGammaProcess>;
using QlVarianceOption = shared_ptr<VarianceOption>;
using QlVarianceSwap = shared_ptr<VarianceSwap>;
using QlVolatilityTermStructure = shared_ptr<VolatilityTermStructure>;
using QlYearOnYearInflationSwap = shared_ptr<YearOnYearInflationSwap>;
using QlYearOnYearInflationSwapHelper = shared_ptr<YearOnYearInflationSwapHelper>;
// A plain TermStructure leaf like CPICapFloorTermPriceSurface -- shared_ptr, not a Handle.
using QlYoYCapFloorTermPriceSurface = shared_ptr<YoYCapFloorTermPriceSurface>;
using QlYoYInflationCapFloor = shared_ptr<YoYInflationCapFloor>;
// A standalone pricer type like FloatingRateCouponPricer -- shared_ptr, not a Handle.
using QlYoYInflationCouponPricer = shared_ptr<YoYInflationCouponPricer>;
using QlYoYInflationIndex = shared_ptr<YoYInflationIndex>;
using QlYoYInflationTermStructure = shared_ptr<YoYInflationTermStructure>;
// A vol structure is a Handle, same reasoning as QlOptionletVolatilityStructure above.
using QlYoYOptionletVolatilitySurface = Handle<YoYOptionletVolatilitySurface>;
using QlZeroCouponInflationSwap = shared_ptr<ZeroCouponInflationSwap>;
using QlZeroCouponInflationSwapHelper = shared_ptr<ZeroCouponInflationSwapHelper>;
using QlZeroCouponSwap = shared_ptr<ZeroCouponSwap>;
using QlZeroInflationCashFlow = shared_ptr<ZeroInflationCashFlow>;
using QlZeroInflationIndex = shared_ptr<ZeroInflationIndex>;
using QlZeroInflationTermStructure = shared_ptr<ZeroInflationTermStructure>;
using CouponLeg = std::vector<shared_ptr<Coupon> >;

#ifdef QLTRACK_ALLOCATIONS
// The trace label for a pointer type. The primary template's typeid() fallback is what makes a
// missing specialization degrade the trace rather than break the build -- alloc-summary.py runs
// the resulting mangled names through c++filt. Specializations are written through the macros
// below rather than spelled out: stringizing the type is what guarantees the label and the type
// cannot drift apart, which a hand-written pair of them silently can.
template <class T> struct ObjClassName {static const char *name() {return typeid(T).name();}};
#define QL_TRACE_NAME_AS(T, S) template <> struct ObjClassName<T*> {static constexpr const char *name() {return S;}};
#define QL_TRACE_NAME(T) QL_TRACE_NAME_AS(T, #T)
QL_TRACE_NAME(AffineModel)
QL_TRACE_NAME(AmericanExercise)
QL_TRACE_NAME(AnalyticBSMHullWhiteEngine)
QL_TRACE_NAME(AnalyticBarrierEngine)
QL_TRACE_NAME(AnalyticCapFloorEngine)
QL_TRACE_NAME(AnalyticCliquetEngine)
QL_TRACE_NAME(AnalyticContinuousFixedLookbackEngine)
QL_TRACE_NAME(AnalyticContinuousFloatingLookbackEngine)
QL_TRACE_NAME(AnalyticContinuousGeometricAveragePriceAsianEngine)
QL_TRACE_NAME(AnalyticDigitalAmericanEngine)
QL_TRACE_NAME(AnalyticDiscreteGeometricAveragePriceAsianEngine)
QL_TRACE_NAME(AnalyticDiscreteGeometricAverageStrikeAsianEngine)
QL_TRACE_NAME(AnalyticDividendEuropeanEngine)
QL_TRACE_NAME(AnalyticEuropeanEngine)
QL_TRACE_NAME(AnalyticGJRGARCHEngine)
QL_TRACE_NAME(AnalyticHestonEngine)
QL_TRACE_NAME(AnalyticHestonHullWhiteEngine)
QL_TRACE_NAME(AnalyticPerformanceEngine)
QL_TRACE_NAME(AssetOrNothingPayoff)
QL_TRACE_NAME(AssetSwap)
QL_TRACE_NAME(BMAIndex)
QL_TRACE_NAME(BMASwap)
QL_TRACE_NAME(BMASwapRateHelper)
QL_TRACE_NAME(BachelierCalculator)
QL_TRACE_NAME(BaroneAdesiWhaleyApproximationEngine)
QL_TRACE_NAME(BarrierOption)
QL_TRACE_NAME(DoubleBarrierOption)
QL_TRACE_NAME(BasketPayoff)
QL_TRACE_NAME(BatesDetJumpEngine)
QL_TRACE_NAME(BatesDetJumpModel)
QL_TRACE_NAME(BatesDoubleExpDetJumpEngine)
QL_TRACE_NAME(BatesDoubleExpDetJumpModel)
QL_TRACE_NAME(BatesDoubleExpEngine)
QL_TRACE_NAME(BatesDoubleExpModel)
QL_TRACE_NAME(BatesEngine)
QL_TRACE_NAME(BatesModel)
QL_TRACE_NAME(BatesProcess)
QL_TRACE_NAME(BermudanExercise)
QL_TRACE_NAME(BespokeCalendar)
QL_TRACE_NAME(BjerksundStenslandApproximationEngine)
QL_TRACE_NAME(BlackCalculator)
QL_TRACE_NAME(BlackDeltaCalculator)
QL_TRACE_NAME(BlackCalibrationHelper)
QL_TRACE_NAME(BlackCallableFixedRateBondEngine)
QL_TRACE_NAME(BlackCallableZeroCouponBondEngine)
QL_TRACE_NAME(BlackCapFloorEngine)
QL_TRACE_NAME(BlackConstantVol)
QL_TRACE_NAME(BlackKarasinski)
QL_TRACE_NAME(BlackProcess)
QL_TRACE_NAME(BlackScholesCalculator)
QL_TRACE_NAME(BlackScholesMertonProcess)
QL_TRACE_NAME(BlackScholesProcess)
QL_TRACE_NAME(BlackSwaptionEngine)
QL_TRACE_NAME(BlackVarianceCurve)
QL_TRACE_NAME(BlackVolTermStructure)
QL_TRACE_NAME(Bond)
QL_TRACE_NAME(BondForward)
QL_TRACE_NAME(BondHelper)
QL_TRACE_NAME(BoundaryConstraint)
QL_TRACE_NAME(Business252)
QL_TRACE_NAME(Calendar)
QL_TRACE_NAME(CalibratedModel)
QL_TRACE_NAME(CalibrationHelper)
QL_TRACE_NAME(Callability)
QL_TRACE_NAME(CallableBond)
QL_TRACE_NAME(CallableBondVolatilityStructure)
QL_TRACE_NAME(CallableFixedRateBond)
QL_TRACE_NAME(CallableZeroCouponBond)
QL_TRACE_NAME(CapFloor)
QL_TRACE_NAME(CapFloorTermVolatilityStructure)
QL_TRACE_NAME(CapFloorTermVolCurve)
QL_TRACE_NAME(CapFloorTermVolSurface)
QL_TRACE_NAME(CashFlow)
QL_TRACE_NAME(CapHelper)
QL_TRACE_NAME(CashOrNothingPayoff)
QL_TRACE_NAME(CdsOption)
QL_TRACE_NAME(DefaultProbKey)
QL_TRACE_NAME(Issuer)
QL_TRACE_NAME(Pool)
QL_TRACE_NAME(Basket)
QL_TRACE_NAME(DefaultLossModel)
QL_TRACE_NAME(SyntheticCDO)
QL_TRACE_NAME(NthToDefault)
QL_TRACE_NAME(Claim)
QL_TRACE_NAME(CommodityType)
QL_TRACE_NAME(CompositeConstraint)
QL_TRACE_NAME(CompositeInstrument)
QL_TRACE_NAME(Constraint)
QL_TRACE_NAME(ConvertibleBond)
QL_TRACE_NAME(ConvertibleFixedCouponBond)
QL_TRACE_NAME(ConvertibleFloatingRateBond)
QL_TRACE_NAME(ConvertibleZeroCouponBond)
QL_TRACE_NAME(CouponLeg)
QL_TRACE_NAME(CPIBond)
QL_TRACE_NAME(CPICapFloor)
QL_TRACE_NAME(CPICapFloorTermPriceSurface)
QL_TRACE_NAME(CPISwap)
QL_TRACE_NAME(CPIVolatilitySurface)
QL_TRACE_NAME(CreditDefaultSwap)
QL_TRACE_NAME(CubicBSplinesFitting)
QL_TRACE_NAME(Currency)
QL_TRACE_NAME(DayCounter)
QL_TRACE_NAME(DefaultProbabilityTermStructure)
QL_TRACE_NAME(DeltaVolQuote)
QL_TRACE_NAME(DepositRateHelper)
QL_TRACE_NAME(DiscountingBondEngine)
QL_TRACE_NAME(DiscountingFxForwardEngine)
QL_TRACE_NAME(DiscountingSwapEngine)
QL_TRACE_NAME(DiscountingConstNotionalCrossCurrencySwapEngine)
QL_TRACE_NAME(Dividend)
QL_TRACE_NAME(EarlyExercise)
QL_TRACE_NAME(EndCriteria)
QL_TRACE_NAME(EquityCashFlow)
QL_TRACE_NAME(EquityCashFlowPricer)
QL_TRACE_NAME(EquityIndex)
QL_TRACE_NAME(EquityQuantoCashFlowPricer)
QL_TRACE_NAME(EquityTotalReturnSwap)
QL_TRACE_NAME(EuropeanExercise)
QL_TRACE_NAME(EuropeanOption)
QL_TRACE_NAME(Exercise)
QL_TRACE_NAME(ExponentialSplinesFitting)
QL_TRACE_NAME(ExtOUWithJumpsProcess)
QL_TRACE_NAME(ExtendedBlackScholesMertonProcess)
QL_TRACE_NAME(ExtendedOrnsteinUhlenbeckProcess)
QL_TRACE_NAME(FdmQuantoHelper)
QL_TRACE_NAME(FFTVanillaEngine)
QL_TRACE_NAME(FaceValueAccrualClaim)
QL_TRACE_NAME(FaceValueClaim)
QL_TRACE_NAME(FdG2SwaptionEngine)
QL_TRACE_NAME(FdHullWhiteSwaptionEngine)
QL_TRACE_NAME(FdmSchemeDesc)
QL_TRACE_NAME(FdmStepConditionComposite)
QL_TRACE_NAME(FittedBondDiscountCurve)
QL_TRACE_NAME(FixedDividend)
QL_TRACE_NAME(FixedRateBond)
QL_TRACE_NAME(BTP)
QL_TRACE_NAME(RendistatoBasket)
QL_TRACE_NAME(RendistatoCalculator)
QL_TRACE_NAME(RendistatoEquivalentSwapLengthQuote)
QL_TRACE_NAME(RendistatoEquivalentSwapSpreadQuote)
QL_TRACE_NAME(FixedRateBondHelper)
QL_TRACE_NAME(FlatForward)
QL_TRACE_NAME(FloatingRateBond)
QL_TRACE_NAME(FloatingRateCouponPricer)
QL_TRACE_NAME(FloatingRateCoupon)
QL_TRACE_NAME(CmsCoupon)
QL_TRACE_NAME(IborCoupon)
QL_TRACE_NAME(OvernightIndexedCoupon)
QL_TRACE_NAME(CPICoupon)
QL_TRACE_NAME(CPICouponPricer)
QL_TRACE_NAME(DigitalCmsCoupon)
QL_TRACE_NAME(DigitalCmsSpreadCoupon)
QL_TRACE_NAME(DigitalReplication)
QL_TRACE_NAME(StrippedCappedFlooredCoupon)
QL_TRACE_NAME(Forward)
QL_TRACE_NAME(ForwardRateAgreement)
QL_TRACE_NAME(ForwardSpreadedTermStructure)
QL_TRACE_NAME(FraRateHelper)
QL_TRACE_NAME(FractionalDividend)
QL_TRACE_NAME(FuturesRateHelper)
QL_TRACE_NAME(FxForward)
QL_TRACE_NAME(G2)
QL_TRACE_NAME(G2SwaptionEngine)
QL_TRACE_NAME(GJRGARCHModel)
QL_TRACE_NAME(GJRGARCHProcess)
QL_TRACE_NAME(GapPayoff)
QL_TRACE_NAME(Garch11)
QL_TRACE_NAME(GarmanKohlagenProcess)
QL_TRACE_NAME(Gaussian1dModel)
QL_TRACE_NAME(GeneralizedBlackScholesProcess)
QL_TRACE_NAME(GeneralizedHullWhite)
QL_TRACE_NAME(Gsr)
QL_TRACE_NAME(GridModelLocalVolSurface)
QL_TRACE_NAME(HestonBlackVolSurface)
QL_TRACE_NAME(HestonModel)
QL_TRACE_NAME(HestonModelHelper)
QL_TRACE_NAME(HestonProcess)
QL_TRACE_NAME(HestonSLVProcess)
QL_TRACE_NAME(HestonSLVMCModel)
QL_TRACE_NAME(HestonSLVFDMModel)
QL_TRACE_NAME(BrownianGeneratorFactory)
QL_TRACE_NAME(HullWhite)
QL_TRACE_NAME(HullWhiteForwardProcess)
QL_TRACE_NAME(HullWhiteProcess)
QL_TRACE_NAME(HybridHestonHullWhiteProcess)
QL_TRACE_NAME(IborIndex)
QL_TRACE_NAME(ImpliedTermStructure)
QL_TRACE_NAME(ImpliedVolTermStructure)
QL_TRACE_NAME(Index)
QL_TRACE_NAME(InflationIndex)
QL_TRACE_NAME(Instrument)
QL_TRACE_NAME(IntegralCdsEngine)
QL_TRACE_NAME(IntegralEngine)
QL_TRACE_NAME(InterestRate)
QL_TRACE_NAME(InterestRateIndex)
QL_TRACE_NAME(JamshidianSwaptionEngine)
QL_TRACE_NAME(JointCalendar)
QL_TRACE_NAME(JuQuadraticApproximationEngine)
QL_TRACE_NAME(JumpDiffusionEngine)
QL_TRACE_NAME(KirkEngine)
QL_TRACE_NAME(KlugeExtOUProcess)
QL_TRACE_NAME(LevenbergMarquardt)
QL_TRACE_NAME(LfmSwaptionEngine)
QL_TRACE_NAME(LiborForwardModel)
QL_TRACE_NAME(LiborForwardModelProcess)
QL_TRACE_NAME(LmCorrelationModel)
QL_TRACE_NAME(LmVolatilityModel)
QL_TRACE_NAME(LocalVolTermStructure)
QL_TRACE_NAME(AndreasenHugeLocalVolAdapter)
QL_TRACE_NAME(AndreasenHugeVolatilityAdapter)
QL_TRACE_NAME(AndreasenHugeVolatilityInterpl)
QL_TRACE_NAME(MargrabeOption)
QL_TRACE_NAME(MarkovFunctional)
QL_TRACE_NAME(Merton76Process)
QL_TRACE_NAME(MidPointCdsEngine)
QL_TRACE_NAME(MultiAssetOption)
QL_TRACE_NAME(MultiCurve)
QL_TRACE_NAME(NelsonSiegelFitting)
QL_TRACE_NAME(NoConstraint)
QL_TRACE_NAME(OISRateHelper)
QL_TRACE_NAME(OneAssetOption)
QL_TRACE_NAME(OneFactorAffineModel)
QL_TRACE_NAME(OptimizationMethod)
QL_TRACE_NAME(Option)
QL_TRACE_NAME(OptionletVolatilityStructure)
QL_TRACE_NAME(OptionletStripper2)
QL_TRACE_NAME(OvernightIndex)
QL_TRACE_NAME(OvernightIndexedSwap)
QL_TRACE_NAME(OvernightIndexedSwapIndex)
QL_TRACE_NAME(PaymentTerm)
QL_TRACE_NAME(Payoff)
QL_TRACE_NAME(PercentageStrikePayoff)
QL_TRACE_NAME(PiecewiseTimeDependentHestonModel)
QL_TRACE_NAME(PlainVanillaPayoff)
QL_TRACE_NAME(PolymorphicPathGenerator)
QL_TRACE_NAME(PolymorphicGaussianRsg)
QL_TRACE_NAME(PositiveConstraint)
QL_TRACE_NAME(PricingEngine)
QL_TRACE_NAME(QlAffineModel)
QL_TRACE_NAME(QlAmericanExercise)
QL_TRACE_NAME(QlAssetSwap)
QL_TRACE_NAME(QlBMAIndex)
QL_TRACE_NAME(QlBMASwap)
QL_TRACE_NAME(QlBarrierOption)
QL_TRACE_NAME(QlDoubleBarrierOption)
QL_TRACE_NAME(QlBachelierCalculator)
QL_TRACE_NAME(QlBasketPayoff)
QL_TRACE_NAME(QlBatesDetJumpModel)
QL_TRACE_NAME(QlBatesDoubleExpDetJumpModel)
QL_TRACE_NAME(QlBatesDoubleExpModel)
QL_TRACE_NAME(QlBatesModel)
QL_TRACE_NAME(QlBatesProcess)
QL_TRACE_NAME(QlBermudanExercise)
QL_TRACE_NAME(QlBlackAtmVolCurve)
QL_TRACE_NAME(QlAbcdAtmVolCurve)
QL_TRACE_NAME(QlBlackVolSurface)
QL_TRACE_NAME(QlSabrVolSurface)
QL_TRACE_NAME(QlBlackCalculator)
QL_TRACE_NAME(QlBlackCalibrationHelper)
QL_TRACE_NAME(QlBlackProcess)
QL_TRACE_NAME(QlBlackScholesCalculator)
QL_TRACE_NAME(QlBlackVarianceCurve)
QL_TRACE_NAME(QlBlackVolatilitySurfaceDelta)
QL_TRACE_NAME(QlBlackVolTermStructure)
QL_TRACE_NAME(QlBond)
QL_TRACE_NAME(QlBondForward)
QL_TRACE_NAME(QlBondHelper)
QL_TRACE_NAME(QlCalibratedModel)
QL_TRACE_NAME(QlCalibrationHelper)
QL_TRACE_NAME(QlCallability)
QL_TRACE_NAME(QlCallableBond)
QL_TRACE_NAME(QlCallableBondVolatilityStructure)
QL_TRACE_NAME(QlCapFloor)
QL_TRACE_NAME(QlCapFloorTermVolatilityStructure)
QL_TRACE_NAME(QlCapFloorTermVolCurve)
QL_TRACE_NAME(QlCapFloorTermVolSurface)
QL_TRACE_NAME(QlCashFlow)
QL_TRACE_NAME(QlCommodityCurve)
QL_TRACE_NAME(QlCommodityIndex)
QL_TRACE_NAME(QlCommodity)
QL_TRACE_NAME(QlEnergyCommodity)
QL_TRACE_NAME(QlEnergyFuture)
QL_TRACE_NAME(QlEnergySwap)
QL_TRACE_NAME(QlEnergyVanillaSwap)
QL_TRACE_NAME(QlEnergyBasisSwap)
QL_TRACE_NAME(QlCommodityCashFlow)
QL_TRACE_NAME(QlCdsOption)
QL_TRACE_NAME(QlPool)
QL_TRACE_NAME(QlBasket)
QL_TRACE_NAME(QlDefaultLossModel)
QL_TRACE_NAME(QlSyntheticCDO)
QL_TRACE_NAME(QlNthToDefault)
QL_TRACE_NAME(QlClaim)
QL_TRACE_NAME(QlConvertibleBond)
QL_TRACE_NAME(QlCPIBond)
QL_TRACE_NAME(QlCPICapFloor)
QL_TRACE_NAME(QlCPICapFloorTermPriceSurface)
QL_TRACE_NAME(QlCPICashFlow)
QL_TRACE_NAME(QlCPISwap)
QL_TRACE_NAME(QlCPIVolatilitySurface)
QL_TRACE_NAME(QlCreditDefaultSwap)
QL_TRACE_NAME(QlDefaultProbabilityTermStructure)
QL_TRACE_NAME(QlDeltaVolQuote)
QL_TRACE_NAME(QlDividend)
QL_TRACE_NAME(QlEndCriteria)
QL_TRACE_NAME(QlEquityCashFlow)
QL_TRACE_NAME(QlEquityCashFlowPricer)
QL_TRACE_NAME(QlEquityIndex)
QL_TRACE_NAME(QlEquityQuantoCashFlowPricer)
QL_TRACE_NAME(QlEquityTotalReturnSwap)
QL_TRACE_NAME(QlEuropeanExercise)
QL_TRACE_NAME(QlExercise)
QL_TRACE_NAME(QlExtOUWithJumpsProcess)
QL_TRACE_NAME(QlExtendedOrnsteinUhlenbeckProcess)
QL_TRACE_NAME(QlFdm1dMesher)
QL_TRACE_NAME(QlFdmInnerValueCalculator)
QL_TRACE_NAME(QlFdmMesher)
QL_TRACE_NAME(QlFdmQuantoHelper)
QL_TRACE_NAME(QlFittedBondDiscountCurve)
QL_TRACE_NAME(QlFixedRateBond)
QL_TRACE_NAME(QlBTP)
QL_TRACE_NAME(QlRendistatoBasket)
QL_TRACE_NAME(QlRendistatoCalculator)
QL_TRACE_NAME(QlFloatingRateCouponPricer)
QL_TRACE_NAME(QlFloatingRateCoupon)
QL_TRACE_NAME(QlCmsCoupon)
QL_TRACE_NAME(QlDigitalCmsCoupon)
QL_TRACE_NAME(QlDigitalCmsSpreadCoupon)
QL_TRACE_NAME(QlDigitalReplication)
QL_TRACE_NAME(QlStrippedCappedFlooredCoupon)
QL_TRACE_NAME(QlForward)
QL_TRACE_NAME(QlForwardRateAgreement)
QL_TRACE_NAME(QlFxForward)
QL_TRACE_NAME(QlG2)
QL_TRACE_NAME(QlGJRGARCHModel)
QL_TRACE_NAME(QlGJRGARCHProcess)
QL_TRACE_NAME(QlGaussian1dModel)
QL_TRACE_NAME(QlGeneralizedBlackScholesProcess)
QL_TRACE_NAME(QlGsr)
QL_TRACE_NAME(QlGridModelLocalVolSurface)
QL_TRACE_NAME(QlHestonModel)
QL_TRACE_NAME(QlHestonProcess)
QL_TRACE_NAME(QlHestonSLVProcess)
QL_TRACE_NAME(QlHestonSLVMCModel)
QL_TRACE_NAME(QlHestonSLVFDMModel)
QL_TRACE_NAME(QlBrownianGeneratorFactory)
QL_TRACE_NAME(QlHistoricalIndexAnalysis)
QL_TRACE_NAME(QlHullWhite)
QL_TRACE_NAME(QlHullWhiteForwardProcess)
QL_TRACE_NAME(QlHullWhiteProcess)
QL_TRACE_NAME(QlHybridHestonHullWhiteProcess)
QL_TRACE_NAME(QlIborIndex)
QL_TRACE_NAME(QlIndex)
QL_TRACE_NAME(QlInflationIndex)
QL_TRACE_NAME(QlInstrument)
QL_TRACE_NAME(QlInterestRateIndex)
QL_TRACE_NAME(QlKlugeExtOUProcess)
QL_TRACE_NAME(QlLiborForwardModel)
QL_TRACE_NAME(QlLiborForwardModelProcess)
QL_TRACE_NAME(LfmHullWhiteParameterization)
QL_TRACE_NAME(QlLfmHullWhiteParameterization)
QL_TRACE_NAME(QlLmCorrelationModel)
QL_TRACE_NAME(QlLmVolatilityModel)
QL_TRACE_NAME(QlLocalVolTermStructure)
QL_TRACE_NAME(QlAndreasenHugeVolatilityInterpl)
QL_TRACE_NAME(QlEverestOption)
QL_TRACE_NAME(QlMargrabeOption)
QL_TRACE_NAME(QlMarkovFunctional)
QL_TRACE_NAME(QlMerton76Process)
QL_TRACE_NAME(QlMultiAssetOption)
QL_TRACE_NAME(QlMultiCurve)
QL_TRACE_NAME(QlNonstandardSwap)
QL_TRACE_NAME(QlNonstandardSwaption)
QL_TRACE_NAME(QlFloatFloatSwap)
QL_TRACE_NAME(QlFloatFloatSwaption)
QL_TRACE_NAME(QlOISRateHelper)
QL_TRACE_NAME(QlOneAssetOption)
QL_TRACE_NAME(QlOneFactorAffineModel)
QL_TRACE_NAME(QlOption)
QL_TRACE_NAME(QlOptionletVolatilityStructure)
QL_TRACE_NAME(QlOptionletStripper2)
QL_TRACE_NAME(QlOptimizationMethod)
QL_TRACE_NAME(QlOvernightIndex)
QL_TRACE_NAME(QlOvernightIndexedSwap)
QL_TRACE_NAME(QlOvernightIndexedSwapIndex)
QL_TRACE_NAME(QlPayoff)
QL_TRACE_NAME(QlPercentageStrikePayoff)
QL_TRACE_NAME(QlPiecewiseTimeDependentHestonModel)
QL_TRACE_NAME(QlPlainVanillaPayoff)
QL_TRACE_NAME(QlPricingEngine)
QL_TRACE_NAME(QlQuantoBarrierOption)
QL_TRACE_NAME(QlQuantoDoubleBarrierOption)
QL_TRACE_NAME(QlQuantoForwardVanillaOption)
QL_TRACE_NAME(QlQuantoVanillaOption)
QL_TRACE_NAME(QlQuote)
QL_TRACE_NAME(QlSabrInterpolatedSmileSection)
QL_TRACE_NAME(QlShortRateDynamics)
QL_TRACE_NAME(QlShortRateModel)
QL_TRACE_NAME(QlSimpleQuote)
QL_TRACE_NAME(QlSmileSection)
QL_TRACE_NAME(QlSoftBarrierOption)
QL_TRACE_NAME(QlStochasticProcess)
QL_TRACE_NAME(QlStochasticProcess1D)
QL_TRACE_NAME(QlStochasticProcessArray)
QL_TRACE_NAME(QlStrikedTypePayoff)
QL_TRACE_NAME(QlSviInterpolatedSmileSection)
QL_TRACE_NAME(QlNoArbSabrInterpolatedSmileSection)
QL_TRACE_NAME(QlSwap)
QL_TRACE_NAME(QlFixedVsFloatingSwap)
QL_TRACE_NAME(QlSwapIndex)
QL_TRACE_NAME(QlSwapRateHelper)
QL_TRACE_NAME(QlSwaption)
QL_TRACE_NAME(QlSwaptionHelper)
QL_TRACE_NAME(QlSwaptionVolatilityStructure)
QL_TRACE_NAME(QlSabrSwaptionVolatilityCube)
QL_TRACE_NAME(QlNoArbSabrSwaptionVolatilityCube)
QL_TRACE_NAME(QlInterpolatedSwaptionVolatilityCube)
QL_TRACE_NAME(QlSwingExercise)
QL_TRACE_NAME(QlTermStructure)
QL_TRACE_NAME(QlTypePayoff)
QL_TRACE_NAME(QlVanillaOption)
QL_TRACE_NAME(QlVanillaSwap)
QL_TRACE_NAME(QlVarianceGammaProcess)
QL_TRACE_NAME(QlVarianceOption)
QL_TRACE_NAME(QlVarianceSwap)
QL_TRACE_NAME(QlVolatilityTermStructure)
QL_TRACE_NAME(QlYearOnYearInflationSwap)
QL_TRACE_NAME(QlYearOnYearInflationSwapHelper)
QL_TRACE_NAME(QlYieldTermStructure)
QL_TRACE_NAME(QlYoYCapFloorTermPriceSurface)
QL_TRACE_NAME(QlYoYInflationCapFloor)
QL_TRACE_NAME(QlYoYInflationCouponPricer)
QL_TRACE_NAME(QlYoYInflationIndex)
QL_TRACE_NAME(QlYoYInflationTermStructure)
QL_TRACE_NAME(QlYoYOptionletVolatilitySurface)
QL_TRACE_NAME(QlZeroCouponInflationSwap)
QL_TRACE_NAME(QlZeroCouponSwap)
QL_TRACE_NAME(QlZeroCouponInflationSwapHelper)
QL_TRACE_NAME(QlZeroInflationCashFlow)
QL_TRACE_NAME(QlZeroInflationIndex)
QL_TRACE_NAME(QlZeroInflationTermStructure)
QL_TRACE_NAME(QuantoBarrierOption)
QL_TRACE_NAME(QuantoForwardVanillaOption)
QL_TRACE_NAME(QuantoTermStructure)
QL_TRACE_NAME(QuantoVanillaOption)
QL_TRACE_NAME(Quote)
QL_TRACE_NAME(Region)
QL_TRACE_NAME(ReplicatingVarianceSwapEngine)
QL_TRACE_NAME(Rounding)
QL_TRACE_NAME(Schedule)
QL_TRACE_NAME(ShortRateModel)
QL_TRACE_NAME(SimplePolynomialFitting)
QL_TRACE_NAME(SimpleQuote)
QL_TRACE_NAME(Simplex)
QL_TRACE_NAME(SmileSection)
QL_TRACE_NAME(SoftBarrierOption)
QL_TRACE_NAME(SoftCallability)
QL_TRACE_NAME(SpreadCdsHelper)
QL_TRACE_NAME(StochasticProcess)
QL_TRACE_NAME(StochasticProcess1D)
QL_TRACE_NAME(StochasticProcessArray)
QL_TRACE_NAME(StrikedTypePayoff)
QL_TRACE_NAME(StulzEngine)
QL_TRACE_NAME(SuperFundPayoff)
QL_TRACE_NAME(SuperSharePayoff)
QL_TRACE_NAME(SvenssonFitting)
QL_TRACE_NAME(Swap)
QL_TRACE_NAME(ConstNotionalCrossCurrencySwap)
QL_TRACE_NAME(ConstNotionalCrossCurrencyBasisSwap)
QL_TRACE_NAME(ConstNotionalCrossCurrencyFixedVsFloatingSwap)
QL_TRACE_NAME(SwapIndex)
QL_TRACE_NAME(SwapRateHelper)
QL_TRACE_NAME(Swaption)
QL_TRACE_NAME(SwaptionHelper)
QL_TRACE_NAME(SwaptionVolatilityStructure)
QL_TRACE_NAME(SwingExercise)
QL_TRACE_NAME(TermStructure)
QL_TRACE_NAME(TimeGrid)
QL_TRACE_NAME(TreeCallableFixedRateBondEngine)
QL_TRACE_NAME(TreeCallableZeroCouponBondEngine)
QL_TRACE_NAME(TreeCapFloorEngine)
QL_TRACE_NAME(TreeSwaptionEngine)
QL_TRACE_NAME(TreeVanillaSwapEngine)
QL_TRACE_NAME(TypePayoff)
QL_TRACE_NAME(UpfrontCdsHelper)
QL_TRACE_NAME(UnitOfMeasure)
QL_TRACE_NAME(UnitOfMeasureConversion)
QL_TRACE_NAME(VanillaOption)
QL_TRACE_NAME(VanillaSwap)
QL_TRACE_NAME(VarianceGammaEngine)
QL_TRACE_NAME(VarianceGammaProcess)
QL_TRACE_NAME(VarianceSwap)
QL_TRACE_NAME(VegaStressedBlackScholesProcess)
QL_TRACE_NAME(VolatilityTermStructure)
QL_TRACE_NAME(YearOnYearInflationSwap)
QL_TRACE_NAME(YearOnYearInflationSwapHelper)
QL_TRACE_NAME(YieldTermStructure)
QL_TRACE_NAME(YoYCapFloorTermPriceSurface)
QL_TRACE_NAME(YoYInflationCapFloor)
QL_TRACE_NAME(YoYInflationCouponPricer)
QL_TRACE_NAME(YoYInflationIndex)
QL_TRACE_NAME(YoYInflationTermStructure)
QL_TRACE_NAME(YoYOptionletVolatilitySurface)
QL_TRACE_NAME(ZeroCouponBond)
QL_TRACE_NAME(ZeroCouponInflationSwap)
QL_TRACE_NAME(ZeroCouponSwap)
QL_TRACE_NAME(ZeroCouponInflationSwapHelper)
QL_TRACE_NAME(ZeroInflationIndex)
QL_TRACE_NAME(ZeroInflationTermStructure)
QL_TRACE_NAME(ZeroSpreadedTermStructure)
QL_TRACE_NAME_AS(void, "Ptr")

// The trace destination, opened on first use -- see qlMisc.cpp.
std::ostream &traceStream();

// One line of trace: the verb, the label ObjClassName gives `Label', and the pointer.
template <class Label, class T> void emit(const char *what, T p) {
  traceStream() << what << " " << ObjClassName<Label>::name() << ": " << p << std::endl;
}
inline constexpr bool trackAllocations = true;
#else
// Never called when tracing is off (every caller guards with `if constexpr'); declared so that
// nothing outside this header needs to know whether the flag is set.
template <class Label, class T> void emit(const char *, T) {}
inline constexpr bool trackAllocations = false;
#endif

// The one place tracing is switched on or off. `if constexpr' discards the entire body when the
// flag is off -- and because these are templates, the discarded statement is never instantiated,
// so the null test below does not merely optimize away, it is never compiled. That is why the
// guard lives here and not in each free function: a non-template caller hosting the `if constexpr'
// itself would still have its discarded branch fully checked.
//
// A null pointer is never traced: alloc()/ret() only ever wrap a freshly-constructed object, so a
// traced null free would be permanently unmatched noise in alloc-summary.py. (Every free below
// still runs unconditionally -- delete/delete[] on null is a no-op anyway.)
template <class Label, class T> void traceAs(const char *what, T p) {
  if constexpr (trackAllocations) {if (p) emit<Label>(what, p);}
  else {(void)what; (void)p;}
}
// Trace under the pointer's own static type -- the usual case.
template <class T> void trace(const char *what, T p) {traceAs<T>(what, p);}

// arg() is the pass-through read of a pointer received from Haskell, not a lifecycle event: it
// traces unconditionally, nulls included, since alloc-summary.py ignores "arg" lines outright.
template <class T> T arg(T p) {
  if constexpr (trackAllocations) emit<T>("arg", p);
  return p;
}
template <class T> T alloc(T p) {trace("allocated", p); return p;}
// alloc() for an object that is about to be owned by a shared_ptr: the adoption happens in the
// same full-expression as the `new', so no exception between the two can leak it. Prefer this
// over a raw pointer held across a try block -- the trace label is still taken from the argument's
// static type, so the pointer handed in must already have the type the object is freed through
// (see makeCurrency in qlMisc.cpp for what goes wrong otherwise).
template <class T> shared_ptr<T> allocShared(T *p) {return shared_ptr<T>(alloc(p));}
template <class T> T ret(T p) {trace("returned", p); return p;}
template <class T> void del(T p) {trace("deleting", p); delete p; trace("deleted", p);}
// The delete[] counterpart of del(), for the array types Haskell frees through qlFreeInts and
// friends. Separate rather than a flag on del() because the array/scalar delete form has to be
// chosen at the call site anyway.
template <class T> void delArray(T p) {trace("deleting", p); delete[] p; trace("deleted", p);}
// RAII guard for allocated out-arrays: on failure, frees partial output and restores null/zero.
template <class T> class OutArrayGuard {
  T **out_;
  unsigned *len_;
public:
  OutArrayGuard(T **out, unsigned *len) : out_(out), len_(len) {}
  ~OutArrayGuard() {if (out_) {delArray(*out_); *out_ = nullptr; if (len_) *len_ = 0;}}
  void commit() {out_ = nullptr; len_ = nullptr;}
};
// del() for an object whose actual `delete' has to happen elsewhere -- a type only
// forward-declared here, freed through a function in the translation unit that defines it. The
// null test here is real (freeFn need not be null-safe), unlike the tracing-only one in traceAs.
template <class T, class F> void delWith(T p, F freeFn) {
  trace("deleting", p);
  if (p) freeFn(p);
  trace("deleted", p);
}

// Trace a `new T*[n]` pointer-array spine under void** -- the type it is actually freed as via
// qlFreePointerArray (declared `void**`, which can't recover the original element type), so
// tracing it under T** here would leave the allocation forever unmatched to its own free. `p`
// itself stays T** throughout -- only the trace label is void**, no cast involved.
template <class T> T** retPtrArray(T **p) {traceAs<void**>("returned", p); return p;}

// Trace `new Derived(...)` under a Base* label (Base named unstarred at the call site, e.g.
// allocAs<FittedBondDiscountCurveFittingMethod>(new CubicBSplinesFitting(...))) while returning
// it as Derived* -- the caller's own `return` then upcasts it to Base* itself, a compiler-
// checked conversion, not a cast here. alloc()'s label would otherwise come from the argument's
// own static type, so a bare `alloc(new Derived(...))` returned as `Base*` traces the allocation
// under Derived while the matching qlFreeBase's del() (parameter-typed as Base*) traces the free
// under Base -- a spurious leak/over-free pair in alloc-summary.py despite correct actual memory
// behavior.
template <class Base, class Derived> Derived* allocAs(Derived *p) {traceAs<Base*>("allocated", p); return p;}

const Date qlNullableDate(int serialNumber);
int qlNullableDate(const Date &date);

inline std::vector<Date> qlDateVector(int *dates, unsigned len) {
  std::vector<Date> d; d.reserve(len);
  for (unsigned i = 0; i < len; ++i)
    d.push_back(Date(dates[i]));
  return d;
}

inline std::vector<Period> qlPeriodVector(int *num, int *unit, unsigned len) {
  std::vector<Period> periods; periods.reserve(len);
  for (unsigned i = 0; i < len; ++i)
    periods.push_back(Period(num[i], (TimeUnit)unit[i]));
  return periods;
}

inline Matrix qlMatrix(double *a, unsigned r, unsigned c) {
  Matrix m (r, c); std::copy(a, a+r*c, m.begin());
  return m;
}

// Some constructors (e.g. SwaptionVolatilityMatrix's Handle<Quote>-vols overload) take a plain
// vector<vector<Real>> rather than a Matrix for a same-shaped Real-only argument (shifts).
inline std::vector<std::vector<double> > qlRealMatrix(double *a, unsigned r, unsigned c) {
  std::vector<std::vector<double> > m; m.reserve(r);
  for (unsigned i = 0; i < r; ++i)
    m.push_back(std::vector<double>(a + i*c, a + (i+1)*c));
  return m;
}

optional<bool> qlOptBool(int b);
int qlOptBool(optional<bool> b);

optional<BusinessDayConvention> qlOptBusinessDayConvention(int c);

template <class T> Handle<T> qlNullableHandle(shared_ptr<T> *p) {return p ? Handle<T>(*(arg(p))) : Handle<T>();}
// Handle form: pass the caller's Handle straight through, so a relinkable handle keeps its
// Link (rewrapping it via Handle<T>(shared_ptr) would make a fresh one and silently detach
// relinking). Null means an empty handle, as with the shared_ptr form above.
template <class T> Handle<T> qlNullableHandle(Handle<T> *p) {return p ? *(arg(p)) : Handle<T>();}

// Same as the Handle form above, but null means "construct this default" (via the caller's
// `make`, returning shared_ptr<T>) rather than an empty handle. Still the one accepted shape of
// Handle<T>(shared_ptr<...>) construction: the default branch has no pre-existing Link to
// detach from, since `make` builds the object fresh right here. Named and centralised so a
// call site never has to spell Handle<T>(...) itself -- see qlBlackIborCouponPricer's
// default-correlation SimpleQuote for the motivating case.
template <class T, class F> Handle<T> qlNullableHandleOr(Handle<T> *p, F make) {return p ? *(arg(p)) : Handle<T>(make());}

// Accessors for the QuantLib free functions (BondFunctions::, CashFlows::) that want the
// pointee rather than the handle. Named rather than spelled with stars because *arg(h),
// **arg(h) and ***arg(h) are all well-formed here and differ by a single character inside
// very long argument lists -- and picking the wrong one is the failure mode this whole design
// has to guard against. Both throw on an empty handle, per Handle::operator*. Generic over T
// (not curve-specific) so every Handle-shaped type -- Quote, the vol structures -- reuses these
// rather than growing its own same-shaped spelling.
template <class T> const shared_ptr<T>& handlePtr(Handle<T> *p) {return **arg(p);}
template <class T> const T& handleRef(Handle<T> *p) {return ***arg(p);}

template <class T>
inline std::vector<T> qlVector(T **vals, size_t len) {
  std::vector<T> r; r.reserve(len);
  for (size_t i = 0; i < len; ++i)
    r.push_back(*vals[i]);
  return r;
}

// vals elements are already Handle<T>*, since a Quote/vol-structure array is an array of the
// same Handle-backed pointer type used everywhere else -- copying *arg(vals[i]) into the
// vector shares its Link like any other Handle copy, so a relinkable element stays tracked.
template <class T>
inline std::vector<Handle<T> > qlHandleVector(Handle<T> **vals, size_t len) {
  std::vector<Handle<T> > r; r.reserve(len);
  for (size_t i = 0; i < len; ++i)
    r.push_back(*arg(vals[i]));
  return r;
}

template <class T>
T handleException(char **msg, std::exception &e) {
  *msg = tracedup(e.what());
  return 0;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
