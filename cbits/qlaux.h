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

namespace QuantLib {class Swap;} using QuantLib::Swap;
typedef QuantLib::ext::shared_ptr<Swap> QlSwap;
template <> class objClassName<Swap *> { public: static const char *name() { return "Swap"; } };
template <> class objClassName<QlSwap *> { public: static const char *name() { return "QlSwap"; } };

namespace QuantLib {class VanillaSwap;} using QuantLib::VanillaSwap;
typedef QuantLib::ext::shared_ptr<VanillaSwap> QlVanillaSwap;
template <> class objClassName<VanillaSwap *> { public: static const char *name() { return "VanillaSwap"; } };
template <> class objClassName<QlVanillaSwap *> { public: static const char *name() { return "QlVanillaSwap"; } };

namespace QuantLib {class InterestRateIndex;} using QuantLib::InterestRateIndex;
typedef QuantLib::ext::shared_ptr<InterestRateIndex> QlInterestRateIndex;
template <> class objClassName<InterestRateIndex *> { public: static const char *name() { return "InterestRateIndex"; } };
template <> class objClassName<QlInterestRateIndex *> { public: static const char *name() { return "QlInterestRateIndex"; } };

namespace QuantLib {class SwapIndex;} using QuantLib::SwapIndex;
typedef QuantLib::ext::shared_ptr<SwapIndex> QlSwapIndex;
template <> class objClassName<SwapIndex *> { public: static const char *name() { return "SwapIndex"; } };
template <> class objClassName<QlSwapIndex *> { public: static const char *name() { return "QlSwapIndex"; } };

namespace QuantLib {class SimpleQuote;} using QuantLib::SimpleQuote;
typedef QuantLib::ext::shared_ptr<SimpleQuote> QlSimpleQuote;
template <> class objClassName<SimpleQuote *> { public: static const char *name() { return "SimpleQuote"; } };
template <> class objClassName<QlSimpleQuote *> { public: static const char *name() { return "QlSimpleQuote"; } };

namespace QuantLib {class OvernightIndex;} using QuantLib::OvernightIndex;
typedef QuantLib::ext::shared_ptr<OvernightIndex> QlOvernightIndex;
template <> class objClassName<OvernightIndex *> { public: static const char *name() { return "OvernightIndex"; } };
template <> class objClassName<QlOvernightIndex *> { public: static const char *name() { return "QlOvernightIndex"; } };

namespace QuantLib {class OvernightIndexedSwapIndex;} using QuantLib::OvernightIndexedSwapIndex;
typedef QuantLib::ext::shared_ptr<OvernightIndexedSwapIndex> QlOvernightIndexedSwapIndex;
template <> class objClassName<OvernightIndexedSwapIndex *> { public: static const char *name() { return "OvernightIndexedSwapIndex"; } };
template <> class objClassName<QlOvernightIndexedSwapIndex *> { public: static const char *name() { return "QlOvernightIndexedSwapIndex"; } };

namespace QuantLib {class BMAIndex;} using QuantLib::BMAIndex;
typedef QuantLib::ext::shared_ptr<BMAIndex> QlBMAIndex;
template <> class objClassName<BMAIndex *> { public: static const char *name() { return "BMAIndex"; } };
template <> class objClassName<QlBMAIndex *> { public: static const char *name() { return "QlBMAIndex"; } };

namespace QuantLib {class BMASwap;} using QuantLib::BMASwap;
typedef QuantLib::ext::shared_ptr<BMASwap> QlBMASwap;
template <> class objClassName<BMASwap *> { public: static const char *name() { return "BMASwap"; } };
template <> class objClassName<QlBMASwap *> { public: static const char *name() { return "QlBMASwap"; } };

namespace QuantLib {class OvernightIndexedSwap;} using QuantLib::OvernightIndexedSwap;
typedef QuantLib::ext::shared_ptr<OvernightIndexedSwap> QlOvernightIndexedSwap;
template <> class objClassName<OvernightIndexedSwap *> { public: static const char *name() { return "OvernightIndexedSwap"; } };
template <> class objClassName<QlOvernightIndexedSwap *> { public: static const char *name() { return "QlOvernightIndexedSwap"; } };

namespace QuantLib {class BondHelper;} using QuantLib::BondHelper;
typedef QuantLib::ext::shared_ptr<BondHelper> QlBondHelper;
template <> class objClassName<BondHelper *> { public: static const char *name() { return "BondHelper"; } };
template <> class objClassName<QlBondHelper *> { public: static const char *name() { return "QlBondHelper"; } };

namespace QuantLib {class FittedBondDiscountCurve;} using QuantLib::FittedBondDiscountCurve;
typedef QuantLib::ext::shared_ptr<FittedBondDiscountCurve> QlFittedBondDiscountCurve;
template <> class objClassName<FittedBondDiscountCurve *> { public: static const char *name() { return "FittedBondDiscountCurve"; } };
template <> class objClassName<QlFittedBondDiscountCurve *> { public: static const char *name() { return "QlFittedBondDiscountCurve"; } };

namespace QuantLib {class SwapRateHelper;} using QuantLib::SwapRateHelper;
typedef QuantLib::ext::shared_ptr<SwapRateHelper> QlSwapRateHelper;
template <> class objClassName<SwapRateHelper *> { public: static const char *name() { return "SwapRateHelper"; } };
template <> class objClassName<QlSwapRateHelper *> { public: static const char *name() { return "QlSwapRateHelper"; } };

namespace QuantLib {class BMASwapRateHelper;} using QuantLib::BMASwapRateHelper;
template <> class objClassName<BMASwapRateHelper *> { public: static const char *name() { return "BMASwapRateHelper"; } };

namespace QuantLib {class FraRateHelper;} using QuantLib::FraRateHelper;
template <> class objClassName<FraRateHelper *> { public: static const char *name() { return "FraRateHelper"; } };

namespace QuantLib {class FuturesRateHelper;} using QuantLib::FuturesRateHelper;
template <> class objClassName<FuturesRateHelper *> { public: static const char *name() { return "FuturesRateHelper"; } };

namespace QuantLib {class AssetSwap;} using QuantLib::AssetSwap;
typedef QuantLib::ext::shared_ptr<AssetSwap> QlAssetSwap;
template <> class objClassName<AssetSwap *> { public: static const char *name() { return "AssetSwap"; } };
template <> class objClassName<QlAssetSwap *> { public: static const char *name() { return "QlAssetSwap"; } };

namespace QuantLib {class OISRateHelper;} using QuantLib::OISRateHelper;
typedef QuantLib::ext::shared_ptr<OISRateHelper> QlOISRateHelper;
template <> class objClassName<OISRateHelper *> { public: static const char *name() { return "OISRateHelper"; } };
template <> class objClassName<QlOISRateHelper *> { public: static const char *name() { return "QlOISRateHelper"; } };

namespace QuantLib {class Rounding;} using QuantLib::Rounding;
template <> class objClassName<Rounding *> { public: static const char *name() { return "Rounding"; } };

namespace QuantLib {class TermStructure;} using QuantLib::TermStructure;
typedef QuantLib::ext::shared_ptr<TermStructure> QlTermStructure;
template <> class objClassName<TermStructure *> { public: static const char *name() { return "TermStructure"; } };
template <> class objClassName<QlTermStructure *> { public: static const char *name() { return "QlTermStructure"; } };

namespace QuantLib {class BasketPayoff;} using QuantLib::BasketPayoff;
typedef QuantLib::ext::shared_ptr<BasketPayoff> QlBasketPayoff;
template <> class objClassName<BasketPayoff *> { public: static const char *name() { return "BasketPayoff"; } };
template <> class objClassName<QlBasketPayoff *> { public: static const char *name() { return "QlBasketPayoff"; } };

namespace QuantLib {class Payoff;} using QuantLib::Payoff;
typedef QuantLib::ext::shared_ptr<Payoff> QlPayoff;
template <> class objClassName<Payoff *> { public: static const char *name() { return "Payoff"; } };
template <> class objClassName<QlPayoff *> { public: static const char *name() { return "QlPayoff"; } };

namespace QuantLib {class StrikedTypePayoff;} using QuantLib::StrikedTypePayoff;
typedef QuantLib::ext::shared_ptr<StrikedTypePayoff> QlStrikedTypePayoff;
template <> class objClassName<StrikedTypePayoff *> { public: static const char *name() { return "StrikedTypePayoff"; } };
template <> class objClassName<QlStrikedTypePayoff *> { public: static const char *name() { return "QlStrikedTypePayoff"; } };

namespace QuantLib {class TypePayoff;} using QuantLib::TypePayoff;
typedef QuantLib::ext::shared_ptr<TypePayoff> QlTypePayoff;
template <> class objClassName<TypePayoff *> { public: static const char *name() { return "TypePayoff"; } };
template <> class objClassName<QlTypePayoff *> { public: static const char *name() { return "QlTypePayoff"; } };

namespace QuantLib {class PercentageStrikePayoff;} using QuantLib::PercentageStrikePayoff;
typedef QuantLib::ext::shared_ptr<PercentageStrikePayoff> QlPercentageStrikePayoff;
template <> class objClassName<PercentageStrikePayoff *> { public: static const char *name() { return "PercentageStrikePayoff"; } };
template <> class objClassName<QlPercentageStrikePayoff *> { public: static const char *name() { return "QlPercentageStrikePayoff"; } };

namespace QuantLib {class PlainVanillaPayoff;} using QuantLib::PlainVanillaPayoff;
typedef QuantLib::ext::shared_ptr<PlainVanillaPayoff> QlPlainVanillaPayoff;
template <> class objClassName<PlainVanillaPayoff *> { public: static const char *name() { return "PlainVanillaPayoff"; } };
template <> class objClassName<QlPlainVanillaPayoff *> { public: static const char *name() { return "QlPlainVanillaPayoff"; } };

namespace QuantLib {class AmericanExercise;} using QuantLib::AmericanExercise;
typedef QuantLib::ext::shared_ptr<AmericanExercise> QlAmericanExercise;
template <> class objClassName<AmericanExercise *> { public: static const char *name() { return "AmericanExercise"; } };
template <> class objClassName<QlAmericanExercise *> { public: static const char *name() { return "QlAmericanExercise"; } };

namespace QuantLib {class BermudanExercise;} using QuantLib::BermudanExercise;
typedef QuantLib::ext::shared_ptr<BermudanExercise> QlBermudanExercise;
template <> class objClassName<BermudanExercise *> { public: static const char *name() { return "BermudanExercise"; } };
template <> class objClassName<QlBermudanExercise *> { public: static const char *name() { return "QlBermudanExercise"; } };

namespace QuantLib {class EuropeanExercise;} using QuantLib::EuropeanExercise;
typedef QuantLib::ext::shared_ptr<EuropeanExercise> QlEuropeanExercise;
template <> class objClassName<EuropeanExercise *> { public: static const char *name() { return "EuropeanExercise"; } };
template <> class objClassName<QlEuropeanExercise *> { public: static const char *name() { return "QlEuropeanExercise"; } };

namespace QuantLib {class Exercise;} using QuantLib::Exercise;
typedef QuantLib::ext::shared_ptr<Exercise> QlExercise;
template <> class objClassName<Exercise *> { public: static const char *name() { return "Exercise"; } };
template <> class objClassName<QlExercise *> { public: static const char *name() { return "QlExercise"; } };

namespace QuantLib {class BlackProcess;} using QuantLib::BlackProcess;
typedef QuantLib::ext::shared_ptr<BlackProcess> QlBlackProcess;
template <> class objClassName<BlackProcess *> { public: static const char *name() { return "BlackProcess"; } };
template <> class objClassName<QlBlackProcess *> { public: static const char *name() { return "QlBlackProcess"; } };

namespace QuantLib {class GeneralizedBlackScholesProcess;} using QuantLib::GeneralizedBlackScholesProcess;
typedef QuantLib::ext::shared_ptr<GeneralizedBlackScholesProcess> QlGeneralizedBlackScholesProcess;
template <> class objClassName<GeneralizedBlackScholesProcess *> { public: static const char *name() { return "GeneralizedBlackScholesProcess"; } };
template <> class objClassName<QlGeneralizedBlackScholesProcess *> { public: static const char *name() { return "QlGeneralizedBlackScholesProcess"; } };

namespace QuantLib {class StochasticProcess;} using QuantLib::StochasticProcess;
typedef QuantLib::ext::shared_ptr<StochasticProcess> QlStochasticProcess;
template <> class objClassName<StochasticProcess *> { public: static const char *name() { return "StochasticProcess"; } };
template <> class objClassName<QlStochasticProcess *> { public: static const char *name() { return "QlStochasticProcess"; } };

namespace QuantLib {class StochasticProcess1D;} using QuantLib::StochasticProcess1D;
typedef QuantLib::ext::shared_ptr<StochasticProcess1D> QlStochasticProcess1D;
template <> class objClassName<StochasticProcess1D *> { public: static const char *name() { return "StochasticProcess1D"; } };
template <> class objClassName<QlStochasticProcess1D *> { public: static const char *name() { return "QlStochasticProcess1D"; } };

namespace QuantLib {class BlackVolTermStructure;} using QuantLib::BlackVolTermStructure;
typedef QuantLib::ext::shared_ptr<BlackVolTermStructure> QlBlackVolTermStructure;
template <> class objClassName<BlackVolTermStructure *> { public: static const char *name() { return "BlackVolTermStructure"; } };
template <> class objClassName<QlBlackVolTermStructure *> { public: static const char *name() { return "QlBlackVolTermStructure"; } };

namespace QuantLib {class VolatilityTermStructure;} using QuantLib::VolatilityTermStructure;
typedef QuantLib::ext::shared_ptr<VolatilityTermStructure> QlVolatilityTermStructure;
template <> class objClassName<VolatilityTermStructure *> { public: static const char *name() { return "VolatilityTermStructure"; } };
template <> class objClassName<QlVolatilityTermStructure *> { public: static const char *name() { return "QlVolatilityTermStructure"; } };

namespace QuantLib {class BarrierOption;} using QuantLib::BarrierOption;
typedef QuantLib::ext::shared_ptr<BarrierOption> QlBarrierOption;
template <> class objClassName<BarrierOption *> { public: static const char *name() { return "BarrierOption"; } };
template <> class objClassName<QlBarrierOption *> { public: static const char *name() { return "QlBarrierOption"; } };

namespace QuantLib {class CdsOption;} using QuantLib::CdsOption;
typedef QuantLib::ext::shared_ptr<CdsOption> QlCdsOption;
template <> class objClassName<CdsOption *> { public: static const char *name() { return "CdsOption"; } };
template <> class objClassName<QlCdsOption *> { public: static const char *name() { return "QlCdsOption"; } };

namespace QuantLib {class CreditDefaultSwap;} using QuantLib::CreditDefaultSwap;
typedef QuantLib::ext::shared_ptr<CreditDefaultSwap> QlCreditDefaultSwap;
template <> class objClassName<CreditDefaultSwap *> { public: static const char *name() { return "CreditDefaultSwap"; } };
template <> class objClassName<QlCreditDefaultSwap *> { public: static const char *name() { return "QlCreditDefaultSwap"; } };

namespace QuantLib {class DividendVanillaOption;} using QuantLib::DividendVanillaOption;
typedef QuantLib::ext::shared_ptr<DividendVanillaOption> QlDividendVanillaOption;
template <> class objClassName<DividendVanillaOption *> { public: static const char *name() { return "DividendVanillaOption"; } };
template <> class objClassName<QlDividendVanillaOption *> { public: static const char *name() { return "QlDividendVanillaOption"; } };

namespace QuantLib {class ForwardVanillaOption;} using QuantLib::ForwardVanillaOption;
typedef QuantLib::ext::shared_ptr<ForwardVanillaOption> QlForwardVanillaOption;
template <> class objClassName<ForwardVanillaOption *> { public: static const char *name() { return "ForwardVanillaOption"; } };
template <> class objClassName<QlForwardVanillaOption *> { public: static const char *name() { return "QlForwardVanillaOption"; } };

namespace QuantLib {class MargrabeOption;} using QuantLib::MargrabeOption;
typedef QuantLib::ext::shared_ptr<MargrabeOption> QlMargrabeOption;
template <> class objClassName<MargrabeOption *> { public: static const char *name() { return "MargrabeOption"; } };
template <> class objClassName<QlMargrabeOption *> { public: static const char *name() { return "QlMargrabeOption"; } };

namespace QuantLib {class MultiAssetOption;} using QuantLib::MultiAssetOption;
typedef QuantLib::ext::shared_ptr<MultiAssetOption> QlMultiAssetOption;
template <> class objClassName<MultiAssetOption *> { public: static const char *name() { return "MultiAssetOption"; } };
template <> class objClassName<QlMultiAssetOption *> { public: static const char *name() { return "QlMultiAssetOption"; } };

namespace QuantLib {class OneAssetOption;} using QuantLib::OneAssetOption;
typedef QuantLib::ext::shared_ptr<OneAssetOption> QlOneAssetOption;
template <> class objClassName<OneAssetOption *> { public: static const char *name() { return "OneAssetOption"; } };
template <> class objClassName<QlOneAssetOption *> { public: static const char *name() { return "QlOneAssetOption"; } };

namespace QuantLib {class Option;} using QuantLib::Option;
typedef QuantLib::ext::shared_ptr<Option> QlOption;
template <> class objClassName<Option *> { public: static const char *name() { return "Option"; } };
template <> class objClassName<QlOption *> { public: static const char *name() { return "QlOption"; } };

namespace QuantLib {class QuantoVanillaOption;} using QuantLib::QuantoVanillaOption;
typedef QuantLib::ext::shared_ptr<QuantoVanillaOption> QlQuantoVanillaOption;
template <> class objClassName<QuantoVanillaOption *> { public: static const char *name() { return "QuantoVanillaOption"; } };
template <> class objClassName<QlQuantoVanillaOption *> { public: static const char *name() { return "QlQuantoVanillaOption"; } };

namespace QuantLib {class Swaption;} using QuantLib::Swaption;
typedef QuantLib::ext::shared_ptr<Swaption> QlSwaption;
template <> class objClassName<Swaption *> { public: static const char *name() { return "Swaption"; } };
template <> class objClassName<QlSwaption *> { public: static const char *name() { return "QlSwaption"; } };

namespace QuantLib {class SwingExercise;} using QuantLib::SwingExercise;
typedef QuantLib::ext::shared_ptr<SwingExercise> QlSwingExercise;
template <> class objClassName<SwingExercise *> { public: static const char *name() { return "SwingExercise"; } };
template <> class objClassName<QlSwingExercise *> { public: static const char *name() { return "QlSwingExercise"; } };

namespace QuantLib {class VanillaOption;} using QuantLib::VanillaOption;
typedef QuantLib::ext::shared_ptr<VanillaOption> QlVanillaOption;
template <> class objClassName<VanillaOption *> { public: static const char *name() { return "VanillaOption"; } };
template <> class objClassName<QlVanillaOption *> { public: static const char *name() { return "QlVanillaOption"; } };
namespace QuantLib {class EuropeanOption;} using QuantLib::EuropeanOption;
template <> class objClassName<EuropeanOption *> { public: static const char *name() { return "EuropeanOption"; } };

namespace QuantLib {class Claim;} using QuantLib::Claim;
typedef QuantLib::ext::shared_ptr<Claim> QlClaim;
template <> class objClassName<Claim *> { public: static const char *name() { return "Claim"; } };
template <> class objClassName<QlClaim *> { public: static const char *name() { return "QlClaim"; } };

namespace QuantLib {class DefaultProbabilityTermStructure;} using QuantLib::DefaultProbabilityTermStructure;
typedef QuantLib::ext::shared_ptr<DefaultProbabilityTermStructure> QlDefaultProbabilityTermStructure;
template <> class objClassName<DefaultProbabilityTermStructure *> { public: static const char *name() { return "DefaultProbabilityTermStructure"; } };
template <> class objClassName<QlDefaultProbabilityTermStructure *> { public: static const char *name() { return "QlDefaultProbabilityTermStructure"; } };

namespace QuantLib {class SwaptionVolatilityStructure;} using QuantLib::SwaptionVolatilityStructure;
typedef QuantLib::ext::shared_ptr<SwaptionVolatilityStructure> QlSwaptionVolatilityStructure;
template <> class objClassName<SwaptionVolatilityStructure *> { public: static const char *name() { return "SwaptionVolatilityStructure"; } };
template <> class objClassName<QlSwaptionVolatilityStructure *> { public: static const char *name() { return "QlSwaptionVolatilityStructure"; } };

namespace QuantLib {class SmileSection;} using QuantLib::SmileSection;
typedef QuantLib::ext::shared_ptr<SmileSection> QlSmileSection;
template <> class objClassName<SmileSection *> { public: static const char *name() { return "SmileSection"; } };
template <> class objClassName<QlSmileSection *> { public: static const char *name() { return "QlSmileSection"; } };

namespace QuantLib {class QuantoBarrierOption;} using QuantLib::QuantoBarrierOption;
typedef QuantLib::ext::shared_ptr<QuantoBarrierOption> QlQuantoBarrierOption;
template <> class objClassName<QuantoBarrierOption *> { public: static const char *name() { return "QuantoBarrierOption"; } };
template <> class objClassName<QlQuantoBarrierOption *> { public: static const char *name() { return "QlQuantoBarrierOption"; } };

namespace QuantLib {class QuantoForwardVanillaOption;} using QuantLib::QuantoForwardVanillaOption;
typedef QuantLib::ext::shared_ptr<QuantoForwardVanillaOption> QlQuantoForwardVanillaOption;
template <> class objClassName<QuantoForwardVanillaOption *> { public: static const char *name() { return "QuantoForwardVanillaOption"; } };
template <> class objClassName<QlQuantoForwardVanillaOption *> { public: static const char *name() { return "QlQuantoForwardVanillaOption"; } };

namespace QuantLib {class BlackCalculator;} using QuantLib::BlackCalculator;
typedef QuantLib::ext::shared_ptr<BlackCalculator> QlBlackCalculator;
template <> class objClassName<BlackCalculator *> { public: static const char *name() { return "BlackCalculator"; } };
template <> class objClassName<QlBlackCalculator *> { public: static const char *name() { return "QlBlackCalculator"; } };

namespace QuantLib {class BlackScholesCalculator;} using QuantLib::BlackScholesCalculator;
typedef QuantLib::ext::shared_ptr<BlackScholesCalculator> QlBlackScholesCalculator;
template <> class objClassName<BlackScholesCalculator *> { public: static const char *name() { return "BlackScholesCalculator"; } };
template <> class objClassName<QlBlackScholesCalculator *> { public: static const char *name() { return "QlBlackScholesCalculator"; } };

// processes
namespace QuantLib {class ExtOUWithJumpsProcess;} using QuantLib::ExtOUWithJumpsProcess;
typedef QuantLib::ext::shared_ptr<ExtOUWithJumpsProcess> QlExtOUWithJumpsProcess;
template <> class objClassName<ExtOUWithJumpsProcess *> { public: static const char *name() { return "ExtOUWithJumpsProcess"; } };
template <> class objClassName<QlExtOUWithJumpsProcess *> { public: static const char *name() { return "QlExtOUWithJumpsProcess"; } };

namespace QuantLib {class GJRGARCHProcess;} using QuantLib::GJRGARCHProcess;
typedef QuantLib::ext::shared_ptr<GJRGARCHProcess> QlGJRGARCHProcess;
template <> class objClassName<GJRGARCHProcess *> { public: static const char *name() { return "GJRGARCHProcess"; } };
template <> class objClassName<QlGJRGARCHProcess *> { public: static const char *name() { return "QlGJRGARCHProcess"; } };

namespace QuantLib {class HestonProcess;} using QuantLib::HestonProcess;
typedef QuantLib::ext::shared_ptr<HestonProcess> QlHestonProcess;
template <> class objClassName<HestonProcess *> { public: static const char *name() { return "HestonProcess"; } };
template <> class objClassName<QlHestonProcess *> { public: static const char *name() { return "QlHestonProcess"; } };

namespace QuantLib {class BatesProcess;} using QuantLib::BatesProcess;
typedef QuantLib::ext::shared_ptr<BatesProcess> QlBatesProcess;
template <> class objClassName<BatesProcess *> { public: static const char *name() { return "BatesProcess"; } };
template <> class objClassName<QlBatesProcess *> { public: static const char *name() { return "QlBatesProcess"; } };

namespace QuantLib {class HybridHestonHullWhiteProcess;} using QuantLib::HybridHestonHullWhiteProcess;
typedef QuantLib::ext::shared_ptr<HybridHestonHullWhiteProcess> QlHybridHestonHullWhiteProcess;
template <> class objClassName<HybridHestonHullWhiteProcess *> { public: static const char *name() { return "HybridHestonHullWhiteProcess"; } };
template <> class objClassName<QlHybridHestonHullWhiteProcess *> { public: static const char *name() { return "QlHybridHestonHullWhiteProcess"; } };

namespace QuantLib {class KlugeExtOUProcess;} using QuantLib::KlugeExtOUProcess;
typedef QuantLib::ext::shared_ptr<KlugeExtOUProcess> QlKlugeExtOUProcess;
template <> class objClassName<KlugeExtOUProcess *> { public: static const char *name() { return "KlugeExtOUProcess"; } };
template <> class objClassName<QlKlugeExtOUProcess *> { public: static const char *name() { return "QlKlugeExtOUProcess"; } };

namespace QuantLib {class LiborForwardModelProcess;} using QuantLib::LiborForwardModelProcess;
typedef QuantLib::ext::shared_ptr<LiborForwardModelProcess> QlLiborForwardModelProcess;
template <> class objClassName<LiborForwardModelProcess *> { public: static const char *name() { return "LiborForwardModelProcess"; } };
template <> class objClassName<QlLiborForwardModelProcess *> { public: static const char *name() { return "QlLiborForwardModelProcess"; } };

namespace QuantLib {class StochasticProcessArray;} using QuantLib::StochasticProcessArray;
typedef QuantLib::ext::shared_ptr<StochasticProcessArray> QlStochasticProcessArray;
template <> class objClassName<StochasticProcessArray *> { public: static const char *name() { return "StochasticProcessArray"; } };
template <> class objClassName<QlStochasticProcessArray *> { public: static const char *name() { return "QlStochasticProcessArray"; } };

namespace QuantLib {class VarianceGammaProcess;} using QuantLib::VarianceGammaProcess;
typedef QuantLib::ext::shared_ptr<VarianceGammaProcess> QlVarianceGammaProcess;
template <> class objClassName<VarianceGammaProcess *> { public: static const char *name() { return "VarianceGammaProcess"; } };
template <> class objClassName<QlVarianceGammaProcess *> { public: static const char *name() { return "QlVarianceGammaProcess"; } };

namespace QuantLib {class Merton76Process;} using QuantLib::Merton76Process;
typedef QuantLib::ext::shared_ptr<Merton76Process> QlMerton76Process;
template <> class objClassName<Merton76Process *> { public: static const char *name() { return "Merton76Process"; } };
template <> class objClassName<QlMerton76Process *> { public: static const char *name() { return "QlMerton76Process"; } };

namespace QuantLib {class HullWhiteProcess;} using QuantLib::HullWhiteProcess;
typedef QuantLib::ext::shared_ptr<HullWhiteProcess> QlHullWhiteProcess;
template <> class objClassName<HullWhiteProcess *> { public: static const char *name() { return "HullWhiteProcess"; } };
template <> class objClassName<QlHullWhiteProcess *> { public: static const char *name() { return "QlHullWhiteProcess"; } };

namespace QuantLib {class HullWhiteForwardProcess;} using QuantLib::HullWhiteForwardProcess;
typedef QuantLib::ext::shared_ptr<HullWhiteForwardProcess> QlHullWhiteForwardProcess;
template <> class objClassName<HullWhiteForwardProcess *> { public: static const char *name() { return "HullWhiteForwardProcess"; } };
template <> class objClassName<QlHullWhiteForwardProcess *> { public: static const char *name() { return "QlHullWhiteForwardProcess"; } };

namespace QuantLib {class ExtendedOrnsteinUhlenbeckProcess;} using QuantLib::ExtendedOrnsteinUhlenbeckProcess;
typedef QuantLib::ext::shared_ptr<ExtendedOrnsteinUhlenbeckProcess> QlExtendedOrnsteinUhlenbeckProcess;
template <> class objClassName<ExtendedOrnsteinUhlenbeckProcess *> { public: static const char *name() { return "ExtendedOrnsteinUhlenbeckProcess"; } };
template <> class objClassName<QlExtendedOrnsteinUhlenbeckProcess *> { public: static const char *name() { return "QlExtendedOrnsteinUhlenbeckProcess"; } };

// models
namespace QuantLib {class CalibratedModel;} using QuantLib::CalibratedModel;
typedef QuantLib::ext::shared_ptr<CalibratedModel> QlCalibratedModel;
template <> class objClassName<CalibratedModel *> { public: static const char *name() { return "CalibratedModel"; } };
template <> class objClassName<QlCalibratedModel *> { public: static const char *name() { return "QlCalibratedModel"; } };

namespace QuantLib {class G2;} using QuantLib::G2;
typedef QuantLib::ext::shared_ptr<G2> QlG2;
template <> class objClassName<G2 *> { public: static const char *name() { return "G2"; } };
template <> class objClassName<QlG2 *> { public: static const char *name() { return "QlG2"; } };

namespace QuantLib {class LmCorrelationModel;} using QuantLib::LmCorrelationModel;
typedef QuantLib::ext::shared_ptr<LmCorrelationModel> QlLmCorrelationModel;
template <> class objClassName<LmCorrelationModel *> { public: static const char *name() { return "LmCorrelationModel"; } };
template <> class objClassName<QlLmCorrelationModel *> { public: static const char *name() { return "QlLmCorrelationModel"; } };

namespace QuantLib {class LmVolatilityModel;} using QuantLib::LmVolatilityModel;
typedef QuantLib::ext::shared_ptr<LmVolatilityModel> QlLmVolatilityModel;
template <> class objClassName<LmVolatilityModel *> { public: static const char *name() { return "LmVolatilityModel"; } };
template <> class objClassName<QlLmVolatilityModel *> { public: static const char *name() { return "QlLmVolatilityModel"; } };

namespace QuantLib {class BatesDetJumpModel;} using QuantLib::BatesDetJumpModel;
typedef QuantLib::ext::shared_ptr<BatesDetJumpModel> QlBatesDetJumpModel;
template <> class objClassName<BatesDetJumpModel *> { public: static const char *name() { return "BatesDetJumpModel"; } };
template <> class objClassName<QlBatesDetJumpModel *> { public: static const char *name() { return "QlBatesDetJumpModel"; } };

namespace QuantLib {class BatesDoubleExpDetJumpModel;} using QuantLib::BatesDoubleExpDetJumpModel;
typedef QuantLib::ext::shared_ptr<BatesDoubleExpDetJumpModel> QlBatesDoubleExpDetJumpModel;
template <> class objClassName<BatesDoubleExpDetJumpModel *> { public: static const char *name() { return "BatesDoubleExpDetJumpModel"; } };
template <> class objClassName<QlBatesDoubleExpDetJumpModel *> { public: static const char *name() { return "QlBatesDoubleExpDetJumpModel"; } };

namespace QuantLib {class BatesDoubleExpModel;} using QuantLib::BatesDoubleExpModel;
typedef QuantLib::ext::shared_ptr<BatesDoubleExpModel> QlBatesDoubleExpModel;
template <> class objClassName<BatesDoubleExpModel *> { public: static const char *name() { return "BatesDoubleExpModel"; } };
template <> class objClassName<QlBatesDoubleExpModel *> { public: static const char *name() { return "QlBatesDoubleExpModel"; } };

namespace QuantLib {class GJRGARCHModel;} using QuantLib::GJRGARCHModel;
typedef QuantLib::ext::shared_ptr<GJRGARCHModel> QlGJRGARCHModel;
template <> class objClassName<GJRGARCHModel *> { public: static const char *name() { return "GJRGARCHModel"; } };
template <> class objClassName<QlGJRGARCHModel *> { public: static const char *name() { return "QlGJRGARCHModel"; } };

namespace QuantLib {class HestonModel;} using QuantLib::HestonModel;
typedef QuantLib::ext::shared_ptr<HestonModel> QlHestonModel;
template <> class objClassName<HestonModel *> { public: static const char *name() { return "HestonModel"; } };
template <> class objClassName<QlHestonModel *> { public: static const char *name() { return "QlHestonModel"; } };

namespace QuantLib {class BatesModel;} using QuantLib::BatesModel;
typedef QuantLib::ext::shared_ptr<BatesModel> QlBatesModel;
template <> class objClassName<BatesModel *> { public: static const char *name() { return "BatesModel"; } };
template <> class objClassName<QlBatesModel *> { public: static const char *name() { return "QlBatesModel"; } };

namespace QuantLib {class PiecewiseTimeDependentHestonModel;} using QuantLib::PiecewiseTimeDependentHestonModel;
typedef QuantLib::ext::shared_ptr<PiecewiseTimeDependentHestonModel> QlPiecewiseTimeDependentHestonModel;
template <> class objClassName<PiecewiseTimeDependentHestonModel *> { public: static const char *name() { return "PiecewiseTimeDependentHestonModel"; } };
template <> class objClassName<QlPiecewiseTimeDependentHestonModel *> { public: static const char *name() { return "QlPiecewiseTimeDependentHestonModel"; } };

namespace QuantLib {class ShortRateModel;} using QuantLib::ShortRateModel;
typedef QuantLib::ext::shared_ptr<ShortRateModel> QlShortRateModel;
template <> class objClassName<ShortRateModel *> { public: static const char *name() { return "ShortRateModel"; } };
template <> class objClassName<QlShortRateModel *> { public: static const char *name() { return "QlShortRateModel"; } };

namespace QuantLib {class AffineModel;} using QuantLib::AffineModel;
typedef QuantLib::ext::shared_ptr<AffineModel> QlAffineModel;
template <> class objClassName<AffineModel *> { public: static const char *name() { return "AffineModel"; } };
template <> class objClassName<QlAffineModel *> { public: static const char *name() { return "QlAffineModel"; } };

namespace QuantLib {class OneFactorAffineModel;} using QuantLib::OneFactorAffineModel;
typedef QuantLib::ext::shared_ptr<OneFactorAffineModel> QlOneFactorAffineModel;
template <> class objClassName<OneFactorAffineModel *> { public: static const char *name() { return "OneFactorAffineModel"; } };
template <> class objClassName<QlOneFactorAffineModel *> { public: static const char *name() { return "QlOneFactorAffineModel"; } };

namespace QuantLib {class LiborForwardModel;} using QuantLib::LiborForwardModel;
typedef QuantLib::ext::shared_ptr<LiborForwardModel> QlLiborForwardModel;
template <> class objClassName<LiborForwardModel *> { public: static const char *name() { return "LiborForwardModel"; } };
template <> class objClassName<QlLiborForwardModel *> { public: static const char *name() { return "QlLiborForwardModel"; } };

namespace QuantLib {class HullWhite;} using QuantLib::HullWhite;
typedef QuantLib::ext::shared_ptr<HullWhite> QlHullWhite;
template <> class objClassName<HullWhite *> { public: static const char *name() { return "HullWhite"; } };
template <> class objClassName<QlHullWhite *> { public: static const char *name() { return "QlHullWhite"; } };

namespace QuantLib {class Constraint;} using QuantLib::Constraint;
template <> class objClassName<Constraint *> { public: static const char *name() { return "Constraint"; } };

namespace QuantLib {class OptimizationMethod;} using QuantLib::OptimizationMethod;
template <> class objClassName<OptimizationMethod *> { public: static const char *name() { return "OptimizationMethod"; } };

namespace QuantLib {class CalibrationHelper;} using QuantLib::CalibrationHelper;
typedef QuantLib::ext::shared_ptr<CalibrationHelper> QlCalibrationHelper;
template <> class objClassName<CalibrationHelper *> { public: static const char *name() { return "CalibrationHelper"; } };
template <> class objClassName<QlCalibrationHelper *> { public: static const char *name() { return "QlCalibrationHelper"; } };

namespace QuantLib {class BlackCalibrationHelper;} using QuantLib::BlackCalibrationHelper;
typedef QuantLib::ext::shared_ptr<BlackCalibrationHelper> QlBlackCalibrationHelper;
template <> class objClassName<BlackCalibrationHelper *> { public: static const char *name() { return "BlackCalibrationHelper"; } };
template <> class objClassName<QlBlackCalibrationHelper *> { public: static const char *name() { return "QlBlackCalibrationHelper"; } };

namespace QuantLib {class EndCriteria;} using QuantLib::EndCriteria;
namespace QuantLib {class EndCriteria;} using QuantLib::EndCriteria;
template <> class objClassName<EndCriteria *> { public: static const char *name() { return "EndCriteria"; } };

namespace QuantLib {class CapFloor;} using QuantLib::CapFloor;
typedef QuantLib::ext::shared_ptr<CapFloor> QlCapFloor;
template <> class objClassName<CapFloor *> { public: static const char *name() { return "CapFloor"; } };
template <> class objClassName<QlCapFloor *> { public: static const char *name() { return "QlCapFloor"; } };

namespace QuantLib {class CapFloorTermVolSurface;} using QuantLib::CapFloorTermVolSurface;
typedef QuantLib::ext::shared_ptr<CapFloorTermVolSurface> QlCapFloorTermVolSurface;
template <> class objClassName<CapFloorTermVolSurface *> { public: static const char *name() { return "CapFloorTermVolSurface"; } };
template <> class objClassName<QlCapFloorTermVolSurface *> { public: static const char *name() { return "QlCapFloorTermVolSurface"; } };

namespace QuantLib {class LocalVolTermStructure;} using QuantLib::LocalVolTermStructure;
typedef QuantLib::ext::shared_ptr<LocalVolTermStructure> QlLocalVolTermStructure;
template <> class objClassName<LocalVolTermStructure *> { public: static const char *name() { return "LocalVolTermStructure"; } };
template <> class objClassName<QlLocalVolTermStructure *> { public: static const char *name() { return "QlLocalVolTermStructure"; } };

namespace QuantLib {class BlackVarianceCurve;} using QuantLib::BlackVarianceCurve;
typedef QuantLib::ext::shared_ptr<BlackVarianceCurve> QlBlackVarianceCurve;
template <> class objClassName<BlackVarianceCurve *> { public: static const char *name() { return "BlackVarianceCurve"; } };
template <> class objClassName<QlBlackVarianceCurve *> { public: static const char *name() { return "QlBlackVarianceCurve"; } };

namespace QuantLib {class FdmSchemeDesc;} using QuantLib::FdmSchemeDesc;
template <> class objClassName<FdmSchemeDesc *> { public: static const char *name() { return "FdmSchemeDesc"; } };

namespace QuantLib {class TimeGrid;} using QuantLib::TimeGrid;
template <> class objClassName<TimeGrid *> { public: static const char *name() { return "TimeGrid"; } };

// DefaultProbabilityHelper is a typedef so we cannot use forward declaration
#ifdef quantlib_default_probability_helpers_hpp
using QuantLib::DefaultProbabilityHelper;
typedef QuantLib::ext::shared_ptr<DefaultProbabilityHelper> QlDefaultProbabilityHelper;
template <> class objClassName<DefaultProbabilityHelper *> { public: static const char *name() { return "DefaultProbabilityHelper"; } };
template <> class objClassName<QlDefaultProbabilityHelper *> { public: static const char *name() { return "QlDefaultProbabilityHelper"; } };
#endif

namespace QuantLib {class Dividend;} using QuantLib::Dividend;
typedef QuantLib::ext::shared_ptr<Dividend> QlDividend;
template <> class objClassName<Dividend *> { public: static const char *name() { return "Dividend"; } };
template <> class objClassName<QlDividend *> { public: static const char *name() { return "QlDividend"; } };

namespace QuantLib {class Callability;} using QuantLib::Callability;
typedef QuantLib::ext::shared_ptr<Callability> QlCallability;
template <> class objClassName<Callability *> { public: static const char *name() { return "Callability"; } };
template <> class objClassName<QlCallability *> { public: static const char *name() { return "QlCallability"; } };

namespace QuantLib {class CallableBond;} using QuantLib::CallableBond;
typedef QuantLib::ext::shared_ptr<CallableBond> QlCallableBond;
template <> class objClassName<CallableBond *> { public: static const char *name() { return "CallableBond"; } };
template <> class objClassName<QlCallableBond *> { public: static const char *name() { return "QlCallableBond"; } };

namespace QuantLib {class ConvertibleBond;} using QuantLib::ConvertibleBond;
typedef QuantLib::ext::shared_ptr<ConvertibleBond> QlConvertibleBond;
template <> class objClassName<ConvertibleBond *> { public: static const char *name() { return "ConvertibleBond"; } };
template <> class objClassName<QlConvertibleBond *> { public: static const char *name() { return "QlConvertibleBond"; } };

namespace QuantLib {class CallableBondVolatilityStructure;} using QuantLib::CallableBondVolatilityStructure;
typedef QuantLib::ext::shared_ptr<CallableBondVolatilityStructure> QlCallableBondVolatilityStructure;
template <> class objClassName<CallableBondVolatilityStructure *> { public: static const char *name() { return "CallableBondVolatilityStructure"; } };
template <> class objClassName<QlCallableBondVolatilityStructure *> { public: static const char *name() { return "QlCallableBondVolatilityStructure"; } };

typedef std::vector<QuantLib::ext::shared_ptr<Coupon> > CouponLeg;
template <> class objClassName<CouponLeg *> { public: static const char *name() { return "CouponLeg"; } };

#ifdef quantlib_fitted_bond_discount_curve_hpp
typedef FittedBondDiscountCurve::FittingMethod FittedBondDiscountCurveFittingMethod;
template <> class objClassName<FittedBondDiscountCurveFittingMethod *> { public: static const char *name() { return "FittedBondDiscountCurveFittingMethod"; } };
#endif

namespace QuantLib {class AnalyticBSMHullWhiteEngine;} using QuantLib::AnalyticBSMHullWhiteEngine;
template <> class objClassName<AnalyticBSMHullWhiteEngine *> {public: static const char *name() {return "AnalyticBSMHullWhiteEngine"; } };
namespace QuantLib {class AnalyticBarrierEngine;} using QuantLib::AnalyticBarrierEngine;
template <> class objClassName<AnalyticBarrierEngine *> {public: static const char *name() {return "AnalyticBarrierEngine"; } };
namespace QuantLib {class AnalyticCapFloorEngine;} using QuantLib::AnalyticCapFloorEngine;
template <> class objClassName<AnalyticCapFloorEngine *> {public: static const char *name() {return "AnalyticCapFloorEngine"; } };
namespace QuantLib {class AnalyticCliquetEngine;} using QuantLib::AnalyticCliquetEngine;
template <> class objClassName<AnalyticCliquetEngine *> {public: static const char *name() {return "AnalyticCliquetEngine"; } };
namespace QuantLib {class AnalyticContinuousFixedLookbackEngine;} using QuantLib::AnalyticContinuousFixedLookbackEngine;
template <> class objClassName<AnalyticContinuousFixedLookbackEngine *> {public: static const char *name() {return "AnalyticContinuousFixedLookbackEngine"; } };
namespace QuantLib {class AnalyticContinuousFloatingLookbackEngine;} using QuantLib::AnalyticContinuousFloatingLookbackEngine;
template <> class objClassName<AnalyticContinuousFloatingLookbackEngine *> {public: static const char *name() {return "AnalyticContinuousFloatingLookbackEngine"; } };
namespace QuantLib {class AnalyticContinuousGeometricAveragePriceAsianEngine;} using QuantLib::AnalyticContinuousGeometricAveragePriceAsianEngine;
template <> class objClassName<AnalyticContinuousGeometricAveragePriceAsianEngine *> {public: static const char *name() {return "AnalyticContinuousGeometricAveragePriceAsianEngine"; } };
namespace QuantLib {class AnalyticDigitalAmericanEngine;} using QuantLib::AnalyticDigitalAmericanEngine;
template <> class objClassName<AnalyticDigitalAmericanEngine *> {public: static const char *name() {return "AnalyticDigitalAmericanEngine"; } };
namespace QuantLib {class AnalyticDiscreteGeometricAveragePriceAsianEngine;} using QuantLib::AnalyticDiscreteGeometricAveragePriceAsianEngine;
template <> class objClassName<AnalyticDiscreteGeometricAveragePriceAsianEngine *> {public: static const char *name() {return "AnalyticDiscreteGeometricAveragePriceAsianEngine"; } };
namespace QuantLib {class AnalyticDiscreteGeometricAverageStrikeAsianEngine;} using QuantLib::AnalyticDiscreteGeometricAverageStrikeAsianEngine;
template <> class objClassName<AnalyticDiscreteGeometricAverageStrikeAsianEngine *> {public: static const char *name() {return "AnalyticDiscreteGeometricAverageStrikeAsianEngine"; } };
namespace QuantLib {class AnalyticDividendEuropeanEngine;} using QuantLib::AnalyticDividendEuropeanEngine;
template <> class objClassName<AnalyticDividendEuropeanEngine *> {public: static const char *name() {return "AnalyticDividendEuropeanEngine"; } };
namespace QuantLib {class AnalyticEuropeanEngine;} using QuantLib::AnalyticEuropeanEngine;
template <> class objClassName<AnalyticEuropeanEngine *> {public: static const char *name() {return "AnalyticEuropeanEngine"; } };
namespace QuantLib {class AnalyticGJRGARCHEngine;} using QuantLib::AnalyticGJRGARCHEngine;
template <> class objClassName<AnalyticGJRGARCHEngine *> {public: static const char *name() {return "AnalyticGJRGARCHEngine"; } };
namespace QuantLib {class AnalyticHestonEngine;} using QuantLib::AnalyticHestonEngine;
template <> class objClassName<AnalyticHestonEngine *> {public: static const char *name() {return "AnalyticHestonEngine"; } };
namespace QuantLib {class AnalyticHestonHullWhiteEngine;} using QuantLib::AnalyticHestonHullWhiteEngine;
template <> class objClassName<AnalyticHestonHullWhiteEngine *> {public: static const char *name() {return "AnalyticHestonHullWhiteEngine"; } };
namespace QuantLib {class AnalyticPerformanceEngine;} using QuantLib::AnalyticPerformanceEngine;
template <> class objClassName<AnalyticPerformanceEngine *> {public: static const char *name() {return "AnalyticPerformanceEngine"; } };
namespace QuantLib {class BaroneAdesiWhaleyApproximationEngine;} using QuantLib::BaroneAdesiWhaleyApproximationEngine;
template <> class objClassName<BaroneAdesiWhaleyApproximationEngine *> {public: static const char *name() {return "BaroneAdesiWhaleyApproximationEngine"; } };
namespace QuantLib {class BatesDetJumpEngine;} using QuantLib::BatesDetJumpEngine;
template <> class objClassName<BatesDetJumpEngine *> {public: static const char *name() {return "BatesDetJumpEngine"; } };
namespace QuantLib {class BatesDoubleExpDetJumpEngine;} using QuantLib::BatesDoubleExpDetJumpEngine;
template <> class objClassName<BatesDoubleExpDetJumpEngine *> {public: static const char *name() {return "BatesDoubleExpDetJumpEngine"; } };
namespace QuantLib {class BatesDoubleExpEngine;} using QuantLib::BatesDoubleExpEngine;
template <> class objClassName<BatesDoubleExpEngine *> {public: static const char *name() {return "BatesDoubleExpEngine"; } };
namespace QuantLib {class BatesEngine;} using QuantLib::BatesEngine;
template <> class objClassName<BatesEngine *> {public: static const char *name() {return "BatesEngine"; } };
namespace QuantLib {class BjerksundStenslandApproximationEngine;} using QuantLib::BjerksundStenslandApproximationEngine;
template <> class objClassName<BjerksundStenslandApproximationEngine *> {public: static const char *name() {return "BjerksundStenslandApproximationEngine"; } };
namespace QuantLib {class BlackCallableFixedRateBondEngine;} using QuantLib::BlackCallableFixedRateBondEngine;
template <> class objClassName<BlackCallableFixedRateBondEngine *> {public: static const char *name() {return "BlackCallableFixedRateBondEngine"; } };
namespace QuantLib {class BlackCallableZeroCouponBondEngine;} using QuantLib::BlackCallableZeroCouponBondEngine;
template <> class objClassName<BlackCallableZeroCouponBondEngine *> {public: static const char *name() {return "BlackCallableZeroCouponBondEngine"; } };
namespace QuantLib {class BlackCapFloorEngine;} using QuantLib::BlackCapFloorEngine;
template <> class objClassName<BlackCapFloorEngine *> {public: static const char *name() {return "BlackCapFloorEngine"; } };
namespace QuantLib {class BlackSwaptionEngine;} using QuantLib::BlackSwaptionEngine;
template <> class objClassName<BlackSwaptionEngine *> {public: static const char *name() {return "BlackSwaptionEngine"; } };
namespace QuantLib {class DiscountingSwapEngine;} using QuantLib::DiscountingSwapEngine;
template <> class objClassName<DiscountingSwapEngine *> {public: static const char *name() {return "DiscountingSwapEngine"; } };
namespace QuantLib {class FFTVanillaEngine;} using QuantLib::FFTVanillaEngine;
template <> class objClassName<FFTVanillaEngine *> {public: static const char *name() {return "FFTVanillaEngine"; } };
namespace QuantLib {class FdG2SwaptionEngine;} using QuantLib::FdG2SwaptionEngine;
template <> class objClassName<FdG2SwaptionEngine *> {public: static const char *name() {return "FdG2SwaptionEngine"; } };
namespace QuantLib {class FdHullWhiteSwaptionEngine;} using QuantLib::FdHullWhiteSwaptionEngine;
template <> class objClassName<FdHullWhiteSwaptionEngine *> {public: static const char *name() {return "FdHullWhiteSwaptionEngine"; } };
namespace QuantLib {class G2SwaptionEngine;} using QuantLib::G2SwaptionEngine;
template <> class objClassName<G2SwaptionEngine *> {public: static const char *name() {return "G2SwaptionEngine"; } };
namespace QuantLib {class IntegralCdsEngine;} using QuantLib::IntegralCdsEngine;
template <> class objClassName<IntegralCdsEngine *> {public: static const char *name() {return "IntegralCdsEngine"; } };
namespace QuantLib {class IntegralEngine;} using QuantLib::IntegralEngine;
template <> class objClassName<IntegralEngine *> {public: static const char *name() {return "IntegralEngine"; } };
namespace QuantLib {class JamshidianSwaptionEngine;} using QuantLib::JamshidianSwaptionEngine;
template <> class objClassName<JamshidianSwaptionEngine *> {public: static const char *name() {return "JamshidianSwaptionEngine"; } };
namespace QuantLib {class JuQuadraticApproximationEngine;} using QuantLib::JuQuadraticApproximationEngine;
template <> class objClassName<JuQuadraticApproximationEngine *> {public: static const char *name() {return "JuQuadraticApproximationEngine"; } };
namespace QuantLib {class JumpDiffusionEngine;} using QuantLib::JumpDiffusionEngine;
template <> class objClassName<JumpDiffusionEngine *> {public: static const char *name() {return "JumpDiffusionEngine"; } };
namespace QuantLib {class KirkEngine;} using QuantLib::KirkEngine;
template <> class objClassName<KirkEngine *> {public: static const char *name() {return "KirkEngine"; } };
namespace QuantLib {class LfmSwaptionEngine;} using QuantLib::LfmSwaptionEngine;
template <> class objClassName<LfmSwaptionEngine *> {public: static const char *name() {return "LfmSwaptionEngine"; } };
namespace QuantLib {class MidPointCdsEngine;} using QuantLib::MidPointCdsEngine;
template <> class objClassName<MidPointCdsEngine *> {public: static const char *name() {return "MidPointCdsEngine"; } };
namespace QuantLib {class ReplicatingVarianceSwapEngine;} using QuantLib::ReplicatingVarianceSwapEngine;
template <> class objClassName<ReplicatingVarianceSwapEngine *> {public: static const char *name() {return "ReplicatingVarianceSwapEngine"; } };
namespace QuantLib {class StulzEngine;} using QuantLib::StulzEngine;
template <> class objClassName<StulzEngine *> {public: static const char *name() {return "StulzEngine"; } };
namespace QuantLib {class TreeCallableFixedRateBondEngine;} using QuantLib::TreeCallableFixedRateBondEngine;
template <> class objClassName<TreeCallableFixedRateBondEngine *> {public: static const char *name() {return "TreeCallableFixedRateBondEngine"; } };
namespace QuantLib {class TreeCallableZeroCouponBondEngine;} using QuantLib::TreeCallableZeroCouponBondEngine;
template <> class objClassName<TreeCallableZeroCouponBondEngine *> {public: static const char *name() {return "TreeCallableZeroCouponBondEngine"; } };
namespace QuantLib {class TreeCapFloorEngine;} using QuantLib::TreeCapFloorEngine;
template <> class objClassName<TreeCapFloorEngine *> {public: static const char *name() {return "TreeCapFloorEngine"; } };
namespace QuantLib {class TreeSwaptionEngine;} using QuantLib::TreeSwaptionEngine;
template <> class objClassName<TreeSwaptionEngine *> {public: static const char *name() {return "TreeSwaptionEngine"; } };
namespace QuantLib {class TreeVanillaSwapEngine;} using QuantLib::TreeVanillaSwapEngine;
template <> class objClassName<TreeVanillaSwapEngine *> {public: static const char *name() {return "TreeVanillaSwapEngine"; } };
namespace QuantLib {class VarianceGammaEngine;} using QuantLib::VarianceGammaEngine;
template <> class objClassName<VarianceGammaEngine *> {public: static const char *name() {return "VarianceGammaEngine"; } };

namespace QuantLib{class ConvertibleFloatingRateBond;} using QuantLib::ConvertibleFloatingRateBond;
template <> class objClassName<ConvertibleFloatingRateBond *> {public: static const char *name() {return "ConvertibleFloatingRateBond"; } };
namespace QuantLib{class ConvertibleFixedCouponBond;} using QuantLib::ConvertibleFixedCouponBond;
template <> class objClassName<ConvertibleFixedCouponBond *> {public: static const char *name() {return "ConvertibleFixedCouponBond"; } };
namespace QuantLib{class ConvertibleZeroCouponBond;} using QuantLib::ConvertibleZeroCouponBond;
template <> class objClassName<ConvertibleZeroCouponBond *> {public: static const char *name() {return "ConvertibleZeroCouponBond"; } };
namespace QuantLib{class SoftCallability;} using QuantLib::SoftCallability;
template <> class objClassName<SoftCallability *> {public: static const char *name() {return "SoftCallability"; } };
namespace QuantLib{class EarlyExercise;} using QuantLib::EarlyExercise;
template <> class objClassName<EarlyExercise *> {public: static const char *name() {return "EarlyExercise"; } };
namespace QuantLib{class BlackScholesMertonProcess;} using QuantLib::BlackScholesMertonProcess;
template <> class objClassName<BlackScholesMertonProcess *> {public: static const char *name() {return "BlackScholesMertonProcess"; } };
namespace QuantLib{class BlackScholesProcess;} using QuantLib::BlackScholesProcess;
template <> class objClassName<BlackScholesProcess *> {public: static const char *name() {return "BlackScholesProcess"; } };
namespace QuantLib{class ExtendedBlackScholesMertonProcess;} using QuantLib::ExtendedBlackScholesMertonProcess;
template <> class objClassName<ExtendedBlackScholesMertonProcess *> {public: static const char *name() {return "ExtendedBlackScholesMertonProcess"; } };
namespace QuantLib{class GarmanKohlagenProcess;} using QuantLib::GarmanKohlagenProcess;
template <> class objClassName<GarmanKohlagenProcess *> {public: static const char *name() {return "GarmanKohlagenProcess"; } };
namespace QuantLib{class VegaStressedBlackScholesProcess;} using QuantLib::VegaStressedBlackScholesProcess;
template <> class objClassName<VegaStressedBlackScholesProcess *> {public: static const char *name() {return "VegaStressedBlackScholesProcess"; } };
namespace QuantLib{class BlackConstantVol;} using QuantLib::BlackConstantVol;
template <> class objClassName<BlackConstantVol *> {public: static const char *name() {return "BlackConstantVol"; } };
namespace QuantLib{class ImpliedVolTermStructure;} using QuantLib::ImpliedVolTermStructure;
template <> class objClassName<ImpliedVolTermStructure *> {public: static const char *name() {return "ImpliedVolTermStructure"; } };
namespace QuantLib{class FixedDividend;} using QuantLib::FixedDividend;
template <> class objClassName<FixedDividend *> {public: static const char *name() {return "FixedDividend"; } };
namespace QuantLib{class FractionalDividend;} using QuantLib::FractionalDividend;
template <> class objClassName<FractionalDividend *> {public: static const char *name() {return "FractionalDividend"; } };
namespace QuantLib{class FaceValueAccrualClaim;} using QuantLib::FaceValueAccrualClaim;
template <> class objClassName<FaceValueAccrualClaim *> {public: static const char *name() {return "FaceValueAccrualClaim"; } };
namespace QuantLib{class FaceValueClaim;} using QuantLib::FaceValueClaim;
template <> class objClassName<FaceValueClaim *> {public: static const char *name() {return "FaceValueClaim"; } };
namespace QuantLib{class SpreadCdsHelper;} using QuantLib::SpreadCdsHelper;
template <> class objClassName<SpreadCdsHelper *> {public: static const char *name() {return "SpreadCdsHelper"; } };
namespace QuantLib{class UpfrontCdsHelper;} using QuantLib::UpfrontCdsHelper;
template <> class objClassName<UpfrontCdsHelper *> {public: static const char *name() {return "UpfrontCdsHelper"; } };
namespace QuantLib{class BlackKarasinski;} using QuantLib::BlackKarasinski;
template <> class objClassName<BlackKarasinski *> {public: static const char *name() {return "BlackKarasinski"; } };
namespace QuantLib{class GeneralizedHullWhite;} using QuantLib::GeneralizedHullWhite;
template <> class objClassName<GeneralizedHullWhite *> {public: static const char *name() {return "GeneralizedHullWhite"; } };
namespace QuantLib{class CapHelper;} using QuantLib::CapHelper;
template <> class objClassName<CapHelper *> {public: static const char *name() {return "CapHelper"; } };
namespace QuantLib{class HestonModelHelper;} using QuantLib::HestonModelHelper;
template <> class objClassName<HestonModelHelper *> {public: static const char *name() {return "HestonModelHelper"; } };
namespace QuantLib{class SwaptionHelper;} using QuantLib::SwaptionHelper;
template <> class objClassName<SwaptionHelper *> {public: static const char *name() {return "SwaptionHelper"; } };
namespace QuantLib{class AssetOrNothingPayoff;} using QuantLib::AssetOrNothingPayoff;
template <> class objClassName<AssetOrNothingPayoff *> {public: static const char *name() {return "AssetOrNothingPayoff"; } };
namespace QuantLib{class CashOrNothingPayoff;} using QuantLib::CashOrNothingPayoff;
template <> class objClassName<CashOrNothingPayoff *> {public: static const char *name() {return "CashOrNothingPayoff"; } };
namespace QuantLib{class GapPayoff;} using QuantLib::GapPayoff;
template <> class objClassName<GapPayoff *> {public: static const char *name() {return "GapPayoff"; } };
namespace QuantLib{class SuperFundPayoff;} using QuantLib::SuperFundPayoff;
template <> class objClassName<SuperFundPayoff *> {public: static const char *name() {return "SuperFundPayoff"; } };
namespace QuantLib{class SuperSharePayoff;} using QuantLib::SuperSharePayoff;
template <> class objClassName<SuperSharePayoff *> {public: static const char *name() {return "SuperSharePayoff"; } };
namespace QuantLib{class CubicBSplinesFitting;} using QuantLib::CubicBSplinesFitting;
template <> class objClassName<CubicBSplinesFitting *> {public: static const char *name() {return "CubicBSplinesFitting"; } };
namespace QuantLib{class ExponentialSplinesFitting;} using QuantLib::ExponentialSplinesFitting;
template <> class objClassName<ExponentialSplinesFitting *> {public: static const char *name() {return "ExponentialSplinesFitting"; } };
namespace QuantLib{class NelsonSiegelFitting;} using QuantLib::NelsonSiegelFitting;
template <> class objClassName<NelsonSiegelFitting *> {public: static const char *name() {return "NelsonSiegelFitting"; } };
namespace QuantLib{class SimplePolynomialFitting;} using QuantLib::SimplePolynomialFitting;
template <> class objClassName<SimplePolynomialFitting *> {public: static const char *name() {return "SimplePolynomialFitting"; } };
namespace QuantLib{class SvenssonFitting;} using QuantLib::SvenssonFitting;
template <> class objClassName<SvenssonFitting *> {public: static const char *name() {return "SvenssonFitting"; } };
namespace QuantLib{class LevenbergMarquardt;} using QuantLib::LevenbergMarquardt;
template <> class objClassName<LevenbergMarquardt *> {public: static const char *name() {return "LevenbergMarquardt"; } };
namespace QuantLib{class Simplex;} using QuantLib::Simplex;
template <> class objClassName<Simplex *> {public: static const char *name() {return "Simplex"; } };
namespace QuantLib{class PositiveConstraint;} using QuantLib::PositiveConstraint;
template <> class objClassName<PositiveConstraint *> {public: static const char *name() {return "PositiveConstraint"; } };
namespace QuantLib{class NoConstraint;} using QuantLib::NoConstraint;
template <> class objClassName<NoConstraint *> {public: static const char *name() {return "NoConstraint"; } };
namespace QuantLib{class CompositeConstraint;} using QuantLib::CompositeConstraint;
template <> class objClassName<CompositeConstraint *> {public: static const char *name() {return "CompositeConstraint"; } };
namespace QuantLib{class BoundaryConstraint;} using QuantLib::BoundaryConstraint;
template <> class objClassName<BoundaryConstraint *> {public: static const char *name() {return "BoundaryConstraint"; } };
namespace QuantLib{class CallableFixedRateBond;} using QuantLib::CallableFixedRateBond;
template <> class objClassName<CallableFixedRateBond *> {public: static const char *name() {return "CallableFixedRateBond"; } };
namespace QuantLib{class CallableZeroCouponBond;} using QuantLib::CallableZeroCouponBond;
template <> class objClassName<CallableZeroCouponBond *> {public: static const char *name() {return "CallableZeroCouponBond"; } };
namespace QuantLib{class ForwardSpreadedTermStructure;} using QuantLib::ForwardSpreadedTermStructure;
template <> class objClassName<ForwardSpreadedTermStructure *> {public: static const char *name() {return "ForwardSpreadedTermStructure"; } };
namespace QuantLib{class ZeroSpreadedTermStructure;} using QuantLib::ZeroSpreadedTermStructure;
template <> class objClassName<ZeroSpreadedTermStructure *> {public: static const char *name() {return "ZeroSpreadedTermStructure"; } };
#ifdef quantlib_piecewise_zero_spreaded_term_structure_hpp
using QuantLib::PiecewiseZeroSpreadedTermStructure;
template <> class objClassName<PiecewiseZeroSpreadedTermStructure *> {public: static const char *name() {return "PiecewiseZeroSpreadedTermStructure"; } };
#endif
namespace QuantLib{class QuantoTermStructure;} using QuantLib::QuantoTermStructure;
template <> class objClassName<QuantoTermStructure *> {public: static const char *name() {return "QuantoTermStructure"; } };
namespace QuantLib{class ImpliedTermStructure;} using QuantLib::ImpliedTermStructure;
template <> class objClassName<ImpliedTermStructure *> {public: static const char *name() {return "ImpliedTermStructure"; } };

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
