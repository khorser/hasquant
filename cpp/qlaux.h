#include <ql/time/date.hpp>
#include <ql/errors.hpp>
#include <string.h>

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
  class Quote;
  class SimpleQuote;
  class Bond;
  class FixedRateBond;
  class ZeroCouponBond;
  class Period;
  class DayCounter;
  class Calendar;
  class Schedule;
  class Currency;
  class InterestRate;
  class FixedRateBondHelper;
  class DepositRateHelper;
  class YieldTermStructure;
  class PricingEngine;
  class DiscountingBondEngine;
  class Instrument;
  class IborIndex;
  class Index;
}

using QuantLib::Quote;
using QuantLib::SimpleQuote;
using QuantLib::Bond;
using QuantLib::FixedRateBond;
using QuantLib::ZeroCouponBond;
using QuantLib::Period;
using QuantLib::DayCounter;
using QuantLib::Calendar;
using QuantLib::Schedule;
using QuantLib::Currency;
using QuantLib::InterestRate;
using QuantLib::FixedRateBondHelper;
using QuantLib::DepositRateHelper;
using QuantLib::YieldTermStructure;
using QuantLib::PricingEngine;
using QuantLib::DiscountingBondEngine;
using QuantLib::Instrument;
using QuantLib::IborIndex;
using QuantLib::Index;

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

template <>
class objClassName<Instrument *> {
public:
  static const char *name() {
    return "Instrument";
  }
};

template <>
class objClassName<Bond *> {
public:
  static const char *name() {
    return "Bond";
  }
};

template <>
class objClassName<FixedRateBond *> {
public:
  static const char *name() {
    return "FixedRateBond";
  }
};

template <>
class objClassName<ZeroCouponBond *> {
public:
  static const char *name() {
    return "ZeroCouponBond";
  }
};

template <>
class objClassName<DayCounter *> {
public:
  static const char *name() {
    return "DayCounter";
  }
};

template <>
class objClassName<InterestRate *> {
public:
  static const char *name() {
    return "InterestRate";
  }
};

template <>
class objClassName<Calendar *> {
public:
  static const char *name() {
    return "Calendar";
  }
};

template <>
class objClassName<SimpleQuote *> {
public:
  static const char *name() {
    return "SimpleQuote";
  }
};

template <>
class objClassName<Quote *> {
public:
  static const char *name() {
    return "Quote";
  }
};

template <>
class objClassName<QlQuote *> {
public:
  static const char *name() {
    return "QlQuote";
  }
};

template <>
class objClassName<QlIborIndex *> {
public:
  static const char *name() {
    return "QlIborIndex";
  }
};

template <>
class objClassName<IborIndex *> {
public:
  static const char *name() {
    return "IborIndex";
  }
};

template <>
class objClassName<QlIndex *> {
public:
  static const char *name() {
    return "QlIndex";
  }
};

template <>
class objClassName<Index *> {
public:
  static const char *name() {
    return "Index";
  }
};

template <>
class objClassName<Period *> {
public:
  static const char *name() {
    return "Period";
  }
};

template <>
class objClassName<PricingEngine *> {
public:
  static const char *name() {
    return "PricingEngine";
  }
};

template <>
class objClassName<DiscountingBondEngine *> {
public:
  static const char *name() {
    return "DiscountingBondEngine";
  }
};

template <>
class objClassName<QlPricingEngine *> {
public:
  static const char *name() {
    return "QlPricingEngine";
  }
};

template <>
class objClassName<Schedule *> {
public:
  static const char *name() {
    return "Schedule";
  }
};

template <>
class objClassName<Currency *> {
public:
  static const char *name() {
    return "Currency";
  }
};

template <>
class objClassName<YieldTermStructure *> {
public:
  static const char *name() {
    return "YieldTermStructure";
  }
};

#ifdef quantlib_cash_flow_hpp
template <>
class objClassName<Leg *> {
public:
  static const char *name() {
    return "Leg";
  }
};
#endif

#ifdef quantlib_ratehelpers_hpp
template <>
class objClassName<RateHelper *> {
public:
  static const char *name() {
    return "RateHelper";
  }
};

template <>
class objClassName<QlRateHelper *> {
public:
  static const char *name() {
    return "QlRateHelper";
  }
};
#endif

template <>
class objClassName<DepositRateHelper *> {
public:
  static const char *name() {
    return "DepositRateHelper";
  }
};

template <>
class objClassName<FixedRateBondHelper *> {
public:
  static const char *name() {
    return "FixedRateBondHelper";
  }
};

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

class QuoteWrapper;
template <>
class objClassName<QuoteWrapper *> {
public:
  static const char *name() {
    return "QuoteWrapper";
  }
};

# ifdef quantlib_ratehelpers_hpp
class RateHelperWrapper;

template <>
class objClassName<RateHelperWrapper *> {
public:
  static const char *name() {
    return "RateHelperWrapper";
  }
};
# endif
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
