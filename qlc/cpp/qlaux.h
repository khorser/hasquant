#include <ql/time/date.hpp>
#include <ql/errors.hpp>
#include <string.h>
#include <vector>
#include <boost/optional.hpp>

int * qlAllocateInts(size_t size);
double * qlAllocateDoubles(size_t size);

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
  template <class T>
  class Handle;
  class Quote;
  class Bond;
  class FixedRateBond;
  class ZeroCouponBond;
  class Forward;
  class FixedRateBondForward;
  class ForwardRateAgreement;
  class Period;
  class DayCounter;
  class Calendar;
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
  class IborIndex;
  class Index;
  class FloatingRateCouponPricer;
  class OptionletVolatilityStructure;
}

using QuantLib::Handle;
using QuantLib::Quote;
using QuantLib::Bond;
using QuantLib::FixedRateBond;
using QuantLib::ZeroCouponBond;
using QuantLib::Forward;
using QuantLib::FixedRateBondForward;
using QuantLib::ForwardRateAgreement;
using QuantLib::Period;
using QuantLib::DayCounter;
using QuantLib::Calendar;
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
using QuantLib::IborIndex;
using QuantLib::Index;
using QuantLib::FloatingRateCouponPricer;
using QuantLib::OptionletVolatilityStructure;

// Haskell CQuote and CRateHelper are actually pointers to shared_ptr's
// because quotes and rate helpers are used via smart pointers (Handle
// and shared_ptr) in QuantLib
// Alternatively we could clone passed quotes/helpers and put them into
// the containers each time we call QuantLib
// To make things more complex, I added wrapper classes used when tracing
// is activated to track that objects are really destroyed, yes, I'm paranoid
typedef boost::shared_ptr<Quote> QlQuote;
typedef boost::shared_ptr<YieldTermStructure> QlYieldTermStructure;
typedef boost::shared_ptr<PricingEngine> QlPricingEngine;
typedef boost::shared_ptr<IborIndex> QlIborIndex;
typedef boost::shared_ptr<Index> QlIndex;
typedef boost::shared_ptr<FloatingRateCouponPricer> QlFloatingRateCouponPricer;
typedef boost::shared_ptr<OptionletVolatilityStructure> QlOptionletVolatilityStructure;
typedef boost::shared_ptr<Instrument> QlInstrument;
typedef boost::shared_ptr<Bond> QlBond;
typedef boost::shared_ptr<FixedRateBond> QlFixedRateBond;
typedef boost::shared_ptr<Forward> QlForward;
typedef boost::shared_ptr<FixedRateBondForward> QlFixedRateBondForward;
typedef boost::shared_ptr<ForwardRateAgreement> QlForwardRateAgreement;

// Leg and RateHelper are typedefs so we cannot use forward declaration
// for them. Using them only when corresponding headers have been included
// to save some time on compilation
#ifdef quantlib_ratehelpers_hpp
using QuantLib::RateHelper;
typedef boost::shared_ptr<RateHelper> QlRateHelper;
#endif

#ifdef quantlib_cash_flow_hpp
using QuantLib::Leg;
#endif

using QuantLib::Date;

template <class T>
class objClassName {
public:
  static const char *name() {
    return "Unknown";
  }
};

template <>
class objClassName<void *> {
public:
  static const char *name() {
    return "Ptr";
  }
};

template <> class objClassName<Instrument *> { public: static const char *name() { return "Instrument"; } };
template <> class objClassName<QlInstrument *> { public: static const char *name() { return "QlInstrument"; } };
template <> class objClassName<Bond *> { public: static const char *name() { return "Bond"; } };
template <> class objClassName<QlBond *> { public: static const char *name() { return "QlBond"; } };
template <> class objClassName<FixedRateBond *> { public: static const char *name() { return "FixedRateBond"; } };
template <> class objClassName<QlFixedRateBond *> { public: static const char *name() { return "QlFixedRateBond"; } };
template <> class objClassName<ZeroCouponBond *> { public: static const char *name() { return "ZeroCouponBond"; } };
template <> class objClassName<Forward *> { public: static const char *name() { return "Forward"; } };
template <> class objClassName<QlForward *> { public: static const char *name() { return "QlForward"; } };
template <> class objClassName<FixedRateBondForward *> { public: static const char *name() { return "FixedRateBondForward"; } };
template <> class objClassName<QlFixedRateBondForward *> { public: static const char *name() { return "QlFixedRateBondForward"; } };
template <> class objClassName<ForwardRateAgreement *> { public: static const char *name() { return "ForwardRateAgreement"; } };
template <> class objClassName<QlForwardRateAgreement *> { public: static const char *name() { return "QlForwardRateAgreement"; } };
template <> class objClassName<FloatingRateCouponPricer *> { public: static const char *name() { return "FloatingRateCouponPricer"; } };
template <> class objClassName<QlFloatingRateCouponPricer *> { public: static const char *name() { return "QlFloatingRateCouponPricer"; } };
template <> class objClassName<DayCounter *> { public: static const char *name() { return "DayCounter"; } };
template <> class objClassName<InterestRate *> { public: static const char *name() { return "InterestRate"; } };
template <> class objClassName<Calendar *> { public: static const char *name() { return "Calendar"; } };
template <> class objClassName<Quote *> { public: static const char *name() { return "Quote"; } };
template <> class objClassName<QlQuote *> { public: static const char *name() { return "QlQuote"; } };
template <> class objClassName<QlIborIndex *> { public: static const char *name() { return "QlIborIndex"; } };
template <> class objClassName<IborIndex *> { public: static const char *name() { return "IborIndex"; } };
template <> class objClassName<QlIndex *> { public: static const char *name() { return "QlIndex"; } };
template <> class objClassName<Index *> { public: static const char *name() { return "Index"; } };
template <> class objClassName<Period *> { public: static const char *name() { return "Period"; } };
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

template <class T>
T arg(T p) {
  return TP("arg", p);
}

template <class T>
void del(T p) {
  delete TP("deleting", p);
  TP2("deleted", p);
}

template <class T>
T alloc(T p) {
  return TP("allocated", p);
}

template <class T>
T ret(T p) {
  return TP("returned", p);
}

const Date qlNullableDate(int serialNumber);
int qlNullableDate(const Date &date);
std::vector<Date> qlDateVector(unsigned len, int *dates);

boost::optional<bool> qlOptBool(int b);
int qlOptBool(boost::optional<bool> b);

template <class T>
Handle<T> qlNullableHandle(boost::shared_ptr<T> *p) {
  return p
    ? Handle<T>(*(arg(p)))
    : Handle<T>();
}

// XXX suboptimal
template <class T>
std::vector<T> qlBuildVector(T **vals, size_t len) {
  std::vector<T> r;
  for (size_t i = 0; i < len; ++i) {
    r.push_back(*vals[i]);
  }
  return r;
}

template <class T>
std::vector<Handle<T> > qlBuildHandleVector(boost::shared_ptr<T> **vals, size_t len) {
  std::vector<Handle<T> > r;
  for (size_t i = 0; i < len; ++i) {
    r.push_back(Handle<T>(*vals[i]));
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
  std::cout << std::endl << text << objClassName<T>::name() << ": " << val << std::endl;
  return val;
}
#endif

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
#define LAST(a) (a + sizeof(a)/sizeof(a[0]))

template <class T>
struct EnumObjectInfo {
  const char *name;
  T *(*make)();

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {}
    bool operator()(const EnumObjectInfo<T> &i) {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };

  template <class A>
  static T *makeObject() {
    return new A();
  }
};

template <class T, class T1>
struct EnumObjectInfo1 {
  const char *name;
  T *(*make)(T1 x);

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {}
    bool operator()(const EnumObjectInfo1<T, T1> &i) {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };

  template <class A>
  static T *makeObject(T1 x1) {
    return new A(x1);
  }
};

template <class T, class T1, class T2>
struct EnumObjectInfo2 {
  const char *name;
  T *(*make)(T1 x1, T2 x2);

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {}
    bool operator()(const EnumObjectInfo2<T, T1, T2> &i) {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };

  template <class A>
  static T *makeObject(T1 x1, T2 x2) {
    return new A(x1, x2);
  }
};

template <class T, class T1, class T2, class T3>
struct EnumObjectInfo3 {
  const char *name;
  T *(*make)(T1 x1, T2 x2, T3 x3);

  class Cmp {
  public:
    Cmp(const char *n) : n_(n) {}
    bool operator()(const EnumObjectInfo3<T, T1, T2, T3> &i) {
      return !strcmp(i.name, n_);
    }
  private:
    const char *n_;
  };

  template <class A>
  static T *makeObject(T1 x1, T2 x2, T3 x3) {
    return new A(x1, x2, x3);
  }
};

namespace QuantLib {class Swap;} using QuantLib::Swap;
typedef boost::shared_ptr<Swap> QlSwap;
template <> class objClassName<Swap *> { public: static const char *name() { return "Swap"; } };
template <> class objClassName<QlSwap *> { public: static const char *name() { return "QlSwap"; } };

namespace QuantLib {class VanillaSwap;} using QuantLib::VanillaSwap;
typedef boost::shared_ptr<VanillaSwap> QlVanillaSwap;
template <> class objClassName<VanillaSwap *> { public: static const char *name() { return "VanillaSwap"; } };
template <> class objClassName<QlVanillaSwap *> { public: static const char *name() { return "QlVanillaSwap"; } };

namespace QuantLib {class InterestRateIndex;} using QuantLib::InterestRateIndex;
typedef boost::shared_ptr<InterestRateIndex> QlInterestRateIndex;
template <> class objClassName<InterestRateIndex *> { public: static const char *name() { return "InterestRateIndex"; } };
template <> class objClassName<QlInterestRateIndex *> { public: static const char *name() { return "QlInterestRateIndex"; } };

namespace QuantLib {class SwapIndex;} using QuantLib::SwapIndex;
typedef boost::shared_ptr<SwapIndex> QlSwapIndex;
template <> class objClassName<SwapIndex *> { public: static const char *name() { return "SwapIndex"; } };
template <> class objClassName<QlSwapIndex *> { public: static const char *name() { return "QlSwapIndex"; } };

namespace QuantLib {class SimpleQuote;} using QuantLib::SimpleQuote;
typedef boost::shared_ptr<SimpleQuote> QlSimpleQuote;
template <> class objClassName<SimpleQuote *> { public: static const char *name() { return "SimpleQuote"; } };
template <> class objClassName<QlSimpleQuote *> { public: static const char *name() { return "QlSimpleQuote"; } };

namespace QuantLib {class OvernightIndex;} using QuantLib::OvernightIndex;
typedef boost::shared_ptr<OvernightIndex> QlOvernightIndex;
template <> class objClassName<OvernightIndex *> { public: static const char *name() { return "OvernightIndex"; } };
template <> class objClassName<QlOvernightIndex *> { public: static const char *name() { return "QlOvernightIndex"; } };

namespace QuantLib {class OvernightIndexedSwapIndex;} using QuantLib::OvernightIndexedSwapIndex;
typedef boost::shared_ptr<OvernightIndexedSwapIndex> QlOvernightIndexedSwapIndex;
template <> class objClassName<OvernightIndexedSwapIndex *> { public: static const char *name() { return "OvernightIndexedSwapIndex"; } };
template <> class objClassName<QlOvernightIndexedSwapIndex *> { public: static const char *name() { return "QlOvernightIndexedSwapIndex"; } };

namespace QuantLib {class BMAIndex;} using QuantLib::BMAIndex;
typedef boost::shared_ptr<BMAIndex> QlBMAIndex;
template <> class objClassName<BMAIndex *> { public: static const char *name() { return "BMAIndex"; } };
template <> class objClassName<QlBMAIndex *> { public: static const char *name() { return "QlBMAIndex"; } };

namespace QuantLib {class BMASwap;} using QuantLib::BMASwap;
typedef boost::shared_ptr<BMASwap> QlBMASwap;
template <> class objClassName<BMASwap *> { public: static const char *name() { return "BMASwap"; } };
template <> class objClassName<QlBMASwap *> { public: static const char *name() { return "QlBMASwap"; } };

namespace QuantLib {class OvernightIndexedSwap;} using QuantLib::OvernightIndexedSwap;
typedef boost::shared_ptr<OvernightIndexedSwap> QlOvernightIndexedSwap;
template <> class objClassName<OvernightIndexedSwap *> { public: static const char *name() { return "OvernightIndexedSwap"; } };
template <> class objClassName<QlOvernightIndexedSwap *> { public: static const char *name() { return "QlOvernightIndexedSwap"; } };

namespace QuantLib {class BondHelper;} using QuantLib::BondHelper;
typedef boost::shared_ptr<BondHelper> QlBondHelper;
template <> class objClassName<BondHelper *> { public: static const char *name() { return "BondHelper"; } };
template <> class objClassName<QlBondHelper *> { public: static const char *name() { return "QlBondHelper"; } };

namespace QuantLib {class FittedBondDiscountCurve;} using QuantLib::FittedBondDiscountCurve;
typedef boost::shared_ptr<FittedBondDiscountCurve> QlFittedBondDiscountCurve;
template <> class objClassName<FittedBondDiscountCurve *> { public: static const char *name() { return "FittedBondDiscountCurve"; } };
template <> class objClassName<QlFittedBondDiscountCurve *> { public: static const char *name() { return "QlFittedBondDiscountCurve"; } };

namespace QuantLib {class SwapRateHelper;} using QuantLib::SwapRateHelper;
typedef boost::shared_ptr<SwapRateHelper> QlSwapRateHelper;
template <> class objClassName<SwapRateHelper *> { public: static const char *name() { return "SwapRateHelper"; } };
template <> class objClassName<QlSwapRateHelper *> { public: static const char *name() { return "QlSwapRateHelper"; } };

namespace QuantLib {class AssetSwap;} using QuantLib::AssetSwap;
typedef boost::shared_ptr<AssetSwap> QlAssetSwap;
template <> class objClassName<AssetSwap *> { public: static const char *name() { return "AssetSwap"; } };
template <> class objClassName<QlAssetSwap *> { public: static const char *name() { return "QlAssetSwap"; } };

namespace QuantLib {class OISRateHelper;} using QuantLib::OISRateHelper;
typedef boost::shared_ptr<OISRateHelper> QlOISRateHelper;
template <> class objClassName<OISRateHelper *> { public: static const char *name() { return "OISRateHelper"; } };
template <> class objClassName<QlOISRateHelper *> { public: static const char *name() { return "QlOISRateHelper"; } };

namespace QuantLib {class Rounding;} using QuantLib::Rounding;
template <> class objClassName<Rounding *> { public: static const char *name() { return "Rounding"; } };

namespace QuantLib {class TermStructure;} using QuantLib::TermStructure;
typedef boost::shared_ptr<TermStructure> QlTermStructure;
template <> class objClassName<TermStructure *> { public: static const char *name() { return "TermStructure"; } };
template <> class objClassName<QlTermStructure *> { public: static const char *name() { return "QlTermStructure"; } };

namespace QuantLib {class BasketPayoff;} using QuantLib::BasketPayoff;
typedef boost::shared_ptr<BasketPayoff> QlBasketPayoff;
template <> class objClassName<BasketPayoff *> { public: static const char *name() { return "BasketPayoff"; } };
template <> class objClassName<QlBasketPayoff *> { public: static const char *name() { return "QlBasketPayoff"; } };

namespace QuantLib {class Payoff;} using QuantLib::Payoff;
typedef boost::shared_ptr<Payoff> QlPayoff;
template <> class objClassName<Payoff *> { public: static const char *name() { return "Payoff"; } };
template <> class objClassName<QlPayoff *> { public: static const char *name() { return "QlPayoff"; } };

namespace QuantLib {class StrikedTypePayoff;} using QuantLib::StrikedTypePayoff;
typedef boost::shared_ptr<StrikedTypePayoff> QlStrikedTypePayoff;
template <> class objClassName<StrikedTypePayoff *> { public: static const char *name() { return "StrikedTypePayoff"; } };
template <> class objClassName<QlStrikedTypePayoff *> { public: static const char *name() { return "QlStrikedTypePayoff"; } };

namespace QuantLib {class TypePayoff;} using QuantLib::TypePayoff;
typedef boost::shared_ptr<TypePayoff> QlTypePayoff;
template <> class objClassName<TypePayoff *> { public: static const char *name() { return "TypePayoff"; } };
template <> class objClassName<QlTypePayoff *> { public: static const char *name() { return "QlTypePayoff"; } };

namespace QuantLib {class PercentageStrikePayoff;} using QuantLib::PercentageStrikePayoff;
typedef boost::shared_ptr<PercentageStrikePayoff> QlPercentageStrikePayoff;
template <> class objClassName<PercentageStrikePayoff *> { public: static const char *name() { return "PercentageStrikePayoff"; } };
template <> class objClassName<QlPercentageStrikePayoff *> { public: static const char *name() { return "QlPercentageStrikePayoff"; } };

namespace QuantLib {class PlainVanillaPayoff;} using QuantLib::PlainVanillaPayoff;
typedef boost::shared_ptr<PlainVanillaPayoff> QlPlainVanillaPayoff;
template <> class objClassName<PlainVanillaPayoff *> { public: static const char *name() { return "PlainVanillaPayoff"; } };
template <> class objClassName<QlPlainVanillaPayoff *> { public: static const char *name() { return "QlPlainVanillaPayoff"; } };

namespace QuantLib {class AmericanExercise;} using QuantLib::AmericanExercise;
typedef boost::shared_ptr<AmericanExercise> QlAmericanExercise;
template <> class objClassName<AmericanExercise *> { public: static const char *name() { return "AmericanExercise"; } };
template <> class objClassName<QlAmericanExercise *> { public: static const char *name() { return "QlAmericanExercise"; } };

namespace QuantLib {class BermudanExercise;} using QuantLib::BermudanExercise;
typedef boost::shared_ptr<BermudanExercise> QlBermudanExercise;
template <> class objClassName<BermudanExercise *> { public: static const char *name() { return "BermudanExercise"; } };
template <> class objClassName<QlBermudanExercise *> { public: static const char *name() { return "QlBermudanExercise"; } };

namespace QuantLib {class EuropeanExercise;} using QuantLib::EuropeanExercise;
typedef boost::shared_ptr<EuropeanExercise> QlEuropeanExercise;
template <> class objClassName<EuropeanExercise *> { public: static const char *name() { return "EuropeanExercise"; } };
template <> class objClassName<QlEuropeanExercise *> { public: static const char *name() { return "QlEuropeanExercise"; } };

namespace QuantLib {class Exercise;} using QuantLib::Exercise;
typedef boost::shared_ptr<Exercise> QlExercise;
template <> class objClassName<Exercise *> { public: static const char *name() { return "Exercise"; } };
template <> class objClassName<QlExercise *> { public: static const char *name() { return "QlExercise"; } };

namespace QuantLib {class BlackProcess;} using QuantLib::BlackProcess;
typedef boost::shared_ptr<BlackProcess> QlBlackProcess;
template <> class objClassName<BlackProcess *> { public: static const char *name() { return "BlackProcess"; } };
template <> class objClassName<QlBlackProcess *> { public: static const char *name() { return "QlBlackProcess"; } };

namespace QuantLib {class GeneralizedBlackScholesProcess;} using QuantLib::GeneralizedBlackScholesProcess;
typedef boost::shared_ptr<GeneralizedBlackScholesProcess> QlGeneralizedBlackScholesProcess;
template <> class objClassName<GeneralizedBlackScholesProcess *> { public: static const char *name() { return "GeneralizedBlackScholesProcess"; } };
template <> class objClassName<QlGeneralizedBlackScholesProcess *> { public: static const char *name() { return "QlGeneralizedBlackScholesProcess"; } };

namespace QuantLib {class StochasticProcess;} using QuantLib::StochasticProcess;
typedef boost::shared_ptr<StochasticProcess> QlStochasticProcess;
template <> class objClassName<StochasticProcess *> { public: static const char *name() { return "StochasticProcess"; } };
template <> class objClassName<QlStochasticProcess *> { public: static const char *name() { return "QlStochasticProcess"; } };

namespace QuantLib {class StochasticProcess1D;} using QuantLib::StochasticProcess1D;
typedef boost::shared_ptr<StochasticProcess1D> QlStochasticProcess1D;
template <> class objClassName<StochasticProcess1D *> { public: static const char *name() { return "StochasticProcess1D"; } };
template <> class objClassName<QlStochasticProcess1D *> { public: static const char *name() { return "QlStochasticProcess1D"; } };

namespace QuantLib {class BlackVolTermStructure;} using QuantLib::BlackVolTermStructure;
typedef boost::shared_ptr<BlackVolTermStructure> QlBlackVolTermStructure;
template <> class objClassName<BlackVolTermStructure *> { public: static const char *name() { return "BlackVolTermStructure"; } };
template <> class objClassName<QlBlackVolTermStructure *> { public: static const char *name() { return "QlBlackVolTermStructure"; } };

namespace QuantLib {class VolatilityTermStructure;} using QuantLib::VolatilityTermStructure;
typedef boost::shared_ptr<VolatilityTermStructure> QlVolatilityTermStructure;
template <> class objClassName<VolatilityTermStructure *> { public: static const char *name() { return "VolatilityTermStructure"; } };
template <> class objClassName<QlVolatilityTermStructure *> { public: static const char *name() { return "QlVolatilityTermStructure"; } };

namespace QuantLib {class BarrierOption;} using QuantLib::BarrierOption;
typedef boost::shared_ptr<BarrierOption> QlBarrierOption;
template <> class objClassName<BarrierOption *> { public: static const char *name() { return "BarrierOption"; } };
template <> class objClassName<QlBarrierOption *> { public: static const char *name() { return "QlBarrierOption"; } };

namespace QuantLib {class CdsOption;} using QuantLib::CdsOption;
typedef boost::shared_ptr<CdsOption> QlCdsOption;
template <> class objClassName<CdsOption *> { public: static const char *name() { return "CdsOption"; } };
template <> class objClassName<QlCdsOption *> { public: static const char *name() { return "QlCdsOption"; } };

namespace QuantLib {class CreditDefaultSwap;} using QuantLib::CreditDefaultSwap;
typedef boost::shared_ptr<CreditDefaultSwap> QlCreditDefaultSwap;
template <> class objClassName<CreditDefaultSwap *> { public: static const char *name() { return "CreditDefaultSwap"; } };
template <> class objClassName<QlCreditDefaultSwap *> { public: static const char *name() { return "QlCreditDefaultSwap"; } };

namespace QuantLib {class DividendVanillaOption;} using QuantLib::DividendVanillaOption;
typedef boost::shared_ptr<DividendVanillaOption> QlDividendVanillaOption;
template <> class objClassName<DividendVanillaOption *> { public: static const char *name() { return "DividendVanillaOption"; } };
template <> class objClassName<QlDividendVanillaOption *> { public: static const char *name() { return "QlDividendVanillaOption"; } };

namespace QuantLib {class ForwardVanillaOption;} using QuantLib::ForwardVanillaOption;
typedef boost::shared_ptr<ForwardVanillaOption> QlForwardVanillaOption;
template <> class objClassName<ForwardVanillaOption *> { public: static const char *name() { return "ForwardVanillaOption"; } };
template <> class objClassName<QlForwardVanillaOption *> { public: static const char *name() { return "QlForwardVanillaOption"; } };

namespace QuantLib {class MargrabeOption;} using QuantLib::MargrabeOption;
typedef boost::shared_ptr<MargrabeOption> QlMargrabeOption;
template <> class objClassName<MargrabeOption *> { public: static const char *name() { return "MargrabeOption"; } };
template <> class objClassName<QlMargrabeOption *> { public: static const char *name() { return "QlMargrabeOption"; } };

namespace QuantLib {class MultiAssetOption;} using QuantLib::MultiAssetOption;
typedef boost::shared_ptr<MultiAssetOption> QlMultiAssetOption;
template <> class objClassName<MultiAssetOption *> { public: static const char *name() { return "MultiAssetOption"; } };
template <> class objClassName<QlMultiAssetOption *> { public: static const char *name() { return "QlMultiAssetOption"; } };

namespace QuantLib {class OneAssetOption;} using QuantLib::OneAssetOption;
typedef boost::shared_ptr<OneAssetOption> QlOneAssetOption;
template <> class objClassName<OneAssetOption *> { public: static const char *name() { return "OneAssetOption"; } };
template <> class objClassName<QlOneAssetOption *> { public: static const char *name() { return "QlOneAssetOption"; } };

namespace QuantLib {class Option;} using QuantLib::Option;
typedef boost::shared_ptr<Option> QlOption;
template <> class objClassName<Option *> { public: static const char *name() { return "Option"; } };
template <> class objClassName<QlOption *> { public: static const char *name() { return "QlOption"; } };

namespace QuantLib {class QuantoVanillaOption;} using QuantLib::QuantoVanillaOption;
typedef boost::shared_ptr<QuantoVanillaOption> QlQuantoVanillaOption;
template <> class objClassName<QuantoVanillaOption *> { public: static const char *name() { return "QuantoVanillaOption"; } };
template <> class objClassName<QlQuantoVanillaOption *> { public: static const char *name() { return "QlQuantoVanillaOption"; } };

namespace QuantLib {class Swaption;} using QuantLib::Swaption;
typedef boost::shared_ptr<Swaption> QlSwaption;
template <> class objClassName<Swaption *> { public: static const char *name() { return "Swaption"; } };
template <> class objClassName<QlSwaption *> { public: static const char *name() { return "QlSwaption"; } };

namespace QuantLib {class SwingExercise;} using QuantLib::SwingExercise;
typedef boost::shared_ptr<SwingExercise> QlSwingExercise;
template <> class objClassName<SwingExercise *> { public: static const char *name() { return "SwingExercise"; } };
template <> class objClassName<QlSwingExercise *> { public: static const char *name() { return "QlSwingExercise"; } };

namespace QuantLib {class VanillaOption;} using QuantLib::VanillaOption;
typedef boost::shared_ptr<VanillaOption> QlVanillaOption;
template <> class objClassName<VanillaOption *> { public: static const char *name() { return "VanillaOption"; } };
template <> class objClassName<QlVanillaOption *> { public: static const char *name() { return "QlVanillaOption"; } };

namespace QuantLib {class Claim;} using QuantLib::Claim;
typedef boost::shared_ptr<Claim> QlClaim;
template <> class objClassName<Claim *> { public: static const char *name() { return "Claim"; } };
template <> class objClassName<QlClaim *> { public: static const char *name() { return "QlClaim"; } };

namespace QuantLib {class DefaultProbabilityTermStructure;} using QuantLib::DefaultProbabilityTermStructure;
typedef boost::shared_ptr<DefaultProbabilityTermStructure> QlDefaultProbabilityTermStructure;
template <> class objClassName<DefaultProbabilityTermStructure *> { public: static const char *name() { return "DefaultProbabilityTermStructure"; } };
template <> class objClassName<QlDefaultProbabilityTermStructure *> { public: static const char *name() { return "QlDefaultProbabilityTermStructure"; } };

namespace QuantLib {class SwaptionVolatilityStructure;} using QuantLib::SwaptionVolatilityStructure;
typedef boost::shared_ptr<SwaptionVolatilityStructure> QlSwaptionVolatilityStructure;
template <> class objClassName<SwaptionVolatilityStructure *> { public: static const char *name() { return "SwaptionVolatilityStructure"; } };
template <> class objClassName<QlSwaptionVolatilityStructure *> { public: static const char *name() { return "QlSwaptionVolatilityStructure"; } };

namespace QuantLib {class SmileSection;} using QuantLib::SmileSection;
typedef boost::shared_ptr<SmileSection> QlSmileSection;
template <> class objClassName<SmileSection *> { public: static const char *name() { return "SmileSection"; } };
template <> class objClassName<QlSmileSection *> { public: static const char *name() { return "QlSmileSection"; } };

namespace QuantLib {class QuantoBarrierOption;} using QuantLib::QuantoBarrierOption;
typedef boost::shared_ptr<QuantoBarrierOption> QlQuantoBarrierOption;
template <> class objClassName<QuantoBarrierOption *> { public: static const char *name() { return "QuantoBarrierOption"; } };
template <> class objClassName<QlQuantoBarrierOption *> { public: static const char *name() { return "QlQuantoBarrierOption"; } };

namespace QuantLib {class QuantoForwardVanillaOption;} using QuantLib::QuantoForwardVanillaOption;
typedef boost::shared_ptr<QuantoForwardVanillaOption> QlQuantoForwardVanillaOption;
template <> class objClassName<QuantoForwardVanillaOption *> { public: static const char *name() { return "QuantoForwardVanillaOption"; } };
template <> class objClassName<QlQuantoForwardVanillaOption *> { public: static const char *name() { return "QlQuantoForwardVanillaOption"; } };

namespace QuantLib {class BlackCalculator;} using QuantLib::BlackCalculator;
typedef boost::shared_ptr<BlackCalculator> QlBlackCalculator;
template <> class objClassName<BlackCalculator *> { public: static const char *name() { return "BlackCalculator"; } };
template <> class objClassName<QlBlackCalculator *> { public: static const char *name() { return "QlBlackCalculator"; } };

namespace QuantLib {class BlackScholesCalculator;} using QuantLib::BlackScholesCalculator;
typedef boost::shared_ptr<BlackScholesCalculator> QlBlackScholesCalculator;
template <> class objClassName<BlackScholesCalculator *> { public: static const char *name() { return "BlackScholesCalculator"; } };
template <> class objClassName<QlBlackScholesCalculator *> { public: static const char *name() { return "QlBlackScholesCalculator"; } };

#include "ql.h"

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
