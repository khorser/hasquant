#include <ql/settings.hpp>
#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>
#include <ql/currencies/all.hpp>
#include <ql/currencies/exchangeratemanager.hpp>
#include <ql/exchangerate.hpp>
#include <ql/money.hpp>
#include <ql/interestrate.hpp>
#include <ql/math/optimization/all.hpp>
#include <ql/timegrid.hpp>
#include <ql/math/rounding.hpp>
#include <ql/quotes/all.hpp>
#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/ecb.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/schedule.hpp>
#include <ql/time/period.hpp>
#include <ql/utilities/dataparsers.hpp>
#include <ql/time/daycounters/all.hpp>
#include <ql/experimental/commodities/commoditytype.hpp>
#include <ql/experimental/commodities/unitofmeasure.hpp>
#include <ql/experimental/commodities/petroleumunitsofmeasure.hpp>
#include <ql/experimental/commodities/paymentterm.hpp>
#include <ql/experimental/commodities/quantity.hpp>
#include <ql/experimental/commodities/unitofmeasureconversion.hpp>
#include <ql/experimental/commodities/unitofmeasureconversionmanager.hpp>
#include <ql/experimental/commodities/commoditysettings.hpp>
#include <ql/index.hpp>
#include <ql/math/statistics/sequencestatistics.hpp>
#include <ql/math/statistics/riskstatistics.hpp>
#include <ql/math/array.hpp>
#include <ql/prices.hpp>
#include <ql/models/volatility/garch.hpp>
#include <ql/models/volatility/garmanklass.hpp>
#include <ql/models/volatility/constantestimator.hpp>
#include <ql/models/volatility/simplelocalestimator.hpp>

#include <numeric>
#include <functional>

#include <cstdint>

#ifdef QLTRACK_ALLOCATIONS
# include <cstdlib>
#endif

#include "qlaux.h"
#include "qlMisc.h"
namespace hasquant {
#include "qlEnumObjects.h"
}

using namespace QuantLib;

// Wraps a Haskell-defined cost function -- passed down as a C function pointer produced by
// Haskell's `foreign import ccall "wrapper"` (QuantLib.Internal.Type.withCostFunction) -- as a
// QuantLib CostFunction. value() crosses back into Haskell once per outer optimizer iteration,
// over the whole parameter vector, mirroring QuantLib-SWIG's PyCostFunction (SWIG/functions.i)
// rather than a per-component callback; see the CLAUDE.md "coarsen the language-boundary
// crossing" bullet. values() (the Jacobian-style multi-output variant) is left unimplemented,
// same as PyCostFunction's own -- no bound caller needs it yet.
namespace {
  class HsCostFunction : public CostFunction {
    public:
      explicit HsCostFunction(double (*fn)(double*, unsigned)) : fn_(fn) {}
      Real value(const Array& x) const override {
        std::vector<double> xs(x.begin(), x.end());
        return fn_(xs.data(), (unsigned)xs.size());
      }
      Array values(const Array&) const override {
        QL_FAIL("HsCostFunction::values not implemented");
      }
    private:
      double (*fn_)(double*, unsigned);
  };

// Quote composition. DerivedQuote/CompositeQuote/MultiCompositeQuote are templates over an
// arbitrary functor; each is instantiated exactly twice here -- once over a functor that
// switches on a QuoteOp/MultiQuoteOp at runtime (the fixed catalogue), once over a plain C
// function pointer (an arbitrary Haskell function). The enum does *not* select a template
// argument, so this needs no generic-lambda dispatcher in an *Aux.cpp: one instantiation
// covers the whole catalogue.
//
// These are the only quotes here that are not leaf values: they registerWith() their inputs and
// notifyObservers() on update, which is the entire reason they are bound at all -- a Haskell-side
// recomputation cannot join QuantLib's Observer graph, so a curve bootstrapped off one would
// silently keep a stale number when the underlying quote moves.
  struct QuoteUnaryOp {
    int op;
    Real operand;
    Real operator()(Real x) const {
      switch (op) {
      case hasquant::QuoteAdd: return x + operand;
      case hasquant::QuoteSubtract: return x - operand;
      case hasquant::QuoteMultiply: return x * operand;
      case hasquant::QuoteDivide: return x / operand;
      }
      QL_FAIL("unknown QuoteOp " << op);
    }
  };

  struct QuoteBinaryOp {
    int op;
    Real operator()(Real x, Real y) const {
      switch (op) {
      case hasquant::QuoteAdd: return x + y;
      case hasquant::QuoteSubtract: return x - y;
      case hasquant::QuoteMultiply: return x * y;
      case hasquant::QuoteDivide: return x / y;
      }
      QL_FAIL("unknown QuoteOp " << op);
    }
  };

  // MultiCompositeQuote imposes no non-empty requirement (isValid() is all_of over the elements,
  // vacuously true), so an empty input is accepted and yields the fold's identity.
  struct QuoteArrayOp {
    int op;
    Real operator()(const Array& a) const {
      switch (op) {
      case hasquant::QuoteSum: return std::accumulate(a.begin(), a.end(), Real(0.0));
      case hasquant::QuoteProduct: return std::accumulate(a.begin(), a.end(), Real(1.0), std::multiplies<Real>());
      case hasquant::QuoteNorm2: return Norm2(a);
      }
      QL_FAIL("unknown MultiQuoteOp " << op);
    }
  };

  // Named aliases rather than the instantiations spelled inline, because QL_TRACE_NAME is a macro
  // and CompositeQuote<double (*)(double, double)> reads as two macro arguments.
  using OpDerivedQuote = DerivedQuote<QuoteUnaryOp>;
  using OpCompositeQuote = CompositeQuote<QuoteBinaryOp>;
  using OpMultiCompositeQuote = MultiCompositeQuote<QuoteArrayOp>;
  using HsDerivedQuote = DerivedQuote<double (*)(double)>;
  using HsCompositeQuote = CompositeQuote<double (*)(double, double)>;
  // MultiCompositeQuote calls its ArrayFunction with an Array, so unlike the unary/binary cases
  // (where a plain double(*)(double...) is already a usable functor) the C function pointer needs
  // a thin adapter. It is still handed the whole state vector per evaluation, so this crosses the
  // language boundary once per value(), not once per element.
  struct HsArrayFun {
    double (*fn)(const double*, unsigned);
    Real operator()(const Array& a) const {return fn(a.begin(), (unsigned)a.size());}
  };
  using HsMultiCompositeQuote = MultiCompositeQuote<HsArrayFun>;

  RiskStatistics riskStats(unsigned n, double *xs) {
    RiskStatistics s;
    s.addSequence(xs, xs+n);
    return s;
  }
}

#ifdef QLTRACK_ALLOCATIONS
// Destination is the QLTRACK_ALLOCATIONS env var when set, else the compile-time
// default the flag bakes in (stderr, spelled differently per platform). Without the
// env var the only way to send a trace to a file was to recompile with a different
// -DQLTRACK_ALLOCATIONS, and redirecting stderr also swallows the program's own
// output -- which matters here because a trace is only useful next to the values it
// explains.
static const char *qlTrackDestination() {
  const char *env = std::getenv("QLTRACK_ALLOCATIONS");
  return env && *env ? env : QLTRACK_ALLOCATIONS;
}
std::ostream &traceStream() {
  // Opened on first use, so it cannot lose a race with another translation unit's static
  // initialization -- which a plain global std::ofstream, constructed in this one, could.
  // Deliberately never destroyed: a trace emitted from a late static destructor must not
  // write to an already-closed stream, and the process is exiting anyway.
  static std::ofstream *stream = new std::ofstream(qlTrackDestination());
  return *stream;
}
// Same reason as qlInstrument.cpp's Hs* labels: these live in the anonymous namespace above and
// so cannot be named in qlaux.h's table, and without a specialization ObjClassName falls back to
// typeid().name() -- which for a template instantiation is especially unreadable. All six are
// shared_ptr payloads, alloc()-only and never explicitly freed, so alloc-summary.py shows them
// with no matching del by design.
QL_TRACE_NAME(OpDerivedQuote)
QL_TRACE_NAME(OpCompositeQuote)
QL_TRACE_NAME(OpMultiCompositeQuote)
QL_TRACE_NAME(HsDerivedQuote)
QL_TRACE_NAME(HsCompositeQuote)
QL_TRACE_NAME(HsMultiCompositeQuote)
#endif

int *qlAllocateInts(size_t size) {return ret(new int[size]);}
double *qlAllocateDoubles(size_t size) {return ret(new double[size]);}
const QuantLib::Date qlNullableDate(int serialNumber) {return !serialNumber ? Date() : Date(serialNumber);}
int qlNullableDate(const QuantLib::Date &date) {return date == Date() ? 0 : date.serialNumber();}
ext::optional<bool> qlOptBool(int b) {return b == -1 ? ext::nullopt : ext::optional<bool>(b);}
int qlOptBool(optional<bool> b) {return b ? *b : -1;}
ext::optional<BusinessDayConvention> qlOptBusinessDayConvention(int c) {return c == -1 ? ext::nullopt : ext::optional<BusinessDayConvention>((BusinessDayConvention)c);}

char *tracedup(const char *p) {
  trace("Duplicating string", (void *)p);
  char *dup = strdup(p);
  trace("Duplicate string", (void *)dup);
  return dup;
}

// The named-currency table. Each entry is a function pointer that heap-allocates one
// QuantLib currency subclass; the enum index into it is what Haskell passes.
//
// The return type is spelled `Currency *', not `C *': alloc() takes its trace label from its
// argument's static type, and the matching qlFreeCurrency frees through a `Currency *'. A
// deduced or derived return type here would silently label every allocation with its concrete
// subclass and leave all of them unmatched in alloc-summary.py.
template <class C> Currency *makeCurrency() {return new C();}

using makeCcy = Currency *(*)();

// The calendar table, in two flavours: a calendar with no market variants ignores the market
// argument, one with them maps it onto its own nested Market enum. Return type spelled as the
// base for the same reason as makeCurrency above.
template <class C> Calendar *makeCalendar(int) {return new C();}
template <class C> Calendar *makeMarketCalendar(int market) {return new C(static_cast<typename C::Market>(market));}

using makeCal = Calendar *(*)(int market);

// The day counter table: three constructor shapes -- no argument, a bool flag, or the class's
// own nested Convention enum. Return type spelled as the base, as with makeCurrency above.
template <class D> DayCounter *makeDayCounter(int) {return new D();}
template <class D> DayCounter *makeFlagDayCounter(int flag) {return new D(flag != 0);}
template <class D> DayCounter *makeConvDayCounter(int convention) {return new D(static_cast<typename D::Convention>(convention));}

using makeDc = DayCounter *(*)(int convention);

// must match the order of qlEnumObjects.h:Ccy
static const makeCcy ccys[] = {
    &makeCurrency<ARSCurrency>
  , &makeCurrency<ATSCurrency>
  , &makeCurrency<AUDCurrency>
  , &makeCurrency<BCHCurrency>
  , &makeCurrency<BDTCurrency>
  , &makeCurrency<BEFCurrency>
  , &makeCurrency<BGLCurrency>
  , &makeCurrency<BRLCurrency>
  , &makeCurrency<BTCCurrency>
  , &makeCurrency<BYRCurrency>
  , &makeCurrency<CADCurrency>
  , &makeCurrency<CHFCurrency>
  , &makeCurrency<CLPCurrency>
  , &makeCurrency<CNYCurrency>
  , &makeCurrency<COPCurrency>
  , &makeCurrency<CYPCurrency>
  , &makeCurrency<CZKCurrency>
  , &makeCurrency<DASHCurrency>
  , &makeCurrency<DEMCurrency>
  , &makeCurrency<DKKCurrency>
  , &makeCurrency<EEKCurrency>
  , &makeCurrency<ESPCurrency>
  , &makeCurrency<ETCCurrency>
  , &makeCurrency<ETHCurrency>
  , &makeCurrency<EURCurrency>
  , &makeCurrency<FIMCurrency>
  , &makeCurrency<FRFCurrency>
  , &makeCurrency<GBPCurrency>
  , &makeCurrency<GRDCurrency>
  , &makeCurrency<HKDCurrency>
  , &makeCurrency<HUFCurrency>
  , &makeCurrency<IDRCurrency>
  , &makeCurrency<IEPCurrency>
  , &makeCurrency<ILSCurrency>
  , &makeCurrency<INRCurrency>
  , &makeCurrency<IQDCurrency>
  , &makeCurrency<IRRCurrency>
  , &makeCurrency<ISKCurrency>
  , &makeCurrency<ITLCurrency>
  , &makeCurrency<JPYCurrency>
  , &makeCurrency<KRWCurrency>
  , &makeCurrency<KWDCurrency>
  , &makeCurrency<KZTCurrency>
  , &makeCurrency<LTCCurrency>
  , &makeCurrency<LTLCurrency>
  , &makeCurrency<LUFCurrency>
  , &makeCurrency<LVLCurrency>
  , &makeCurrency<MTLCurrency>
  , &makeCurrency<MXNCurrency>
  , &makeCurrency<MYRCurrency>
  , &makeCurrency<NGNCurrency>
  , &makeCurrency<NLGCurrency>
  , &makeCurrency<NOKCurrency>
  , &makeCurrency<NPRCurrency>
  , &makeCurrency<NZDCurrency>
  , &makeCurrency<PEHCurrency>
  , &makeCurrency<PEICurrency>
  , &makeCurrency<PENCurrency>
  , &makeCurrency<PKRCurrency>
  , &makeCurrency<PLNCurrency>
  , &makeCurrency<PTECurrency>
  , &makeCurrency<ROLCurrency>
  , &makeCurrency<RONCurrency>
  , &makeCurrency<RUBCurrency>
  , &makeCurrency<SARCurrency>
  , &makeCurrency<SEKCurrency>
  , &makeCurrency<SGDCurrency>
  , &makeCurrency<SITCurrency>
  , &makeCurrency<SKKCurrency>
  , &makeCurrency<THBCurrency>
  , &makeCurrency<TRLCurrency>
  , &makeCurrency<TRYCurrency>
  , &makeCurrency<TTDCurrency>
  , &makeCurrency<TWDCurrency>
  , &makeCurrency<UAHCurrency>
  , &makeCurrency<USDCurrency>
  , &makeCurrency<VEBCurrency>
  , &makeCurrency<VNDCurrency>
  , &makeCurrency<XRPCurrency>
  , &makeCurrency<ZARCurrency>
  , &makeCurrency<ZECCurrency>
  , &makeCurrency<AEDCurrency>
  , &makeCurrency<AOACurrency>
  , &makeCurrency<BGNCurrency>
  , &makeCurrency<BHDCurrency>
  , &makeCurrency<BWPCurrency>
  , &makeCurrency<CLFCurrency>
  , &makeCurrency<CNHCurrency>
  , &makeCurrency<COUCurrency>
  , &makeCurrency<EGPCurrency>
  , &makeCurrency<ETBCurrency>
  , &makeCurrency<GELCurrency>
  , &makeCurrency<GHSCurrency>
  , &makeCurrency<HRKCurrency>
  , &makeCurrency<JODCurrency>
  , &makeCurrency<KESCurrency>
  , &makeCurrency<LKRCurrency>
  , &makeCurrency<MADCurrency>
  , &makeCurrency<MKDCurrency>
  , &makeCurrency<MURCurrency>
  , &makeCurrency<MXVCurrency>
  , &makeCurrency<OMRCurrency>
  , &makeCurrency<PHPCurrency>
  , &makeCurrency<QARCurrency>
  , &makeCurrency<RSDCurrency>
  , &makeCurrency<TNDCurrency>
  , &makeCurrency<UGXCurrency>
  , &makeCurrency<UYUCurrency>
  , &makeCurrency<UZSCurrency>
  , &makeCurrency<XOFCurrency>
  , &makeCurrency<ZMWCurrency>
};

namespace {
  // Marshals a real-valued TimeSeries<Real> in from parallel date/value arrays, and a
  // TimeSeries<Volatility> result back out through the four out-params -- shared by
  // Garch11::calculate, ConstantEstimator, and SimpleLocalEstimator (Volatility and Real are
  // the same type, ql/types.hpp).
  void realSeriesCalculate(const std::function<TimeSeries<Volatility>(const TimeSeries<Real>&)>& calc,
                            unsigned len, int *dates, double *values,
                            unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
    int *ds = 0;
    double *vs = 0;
    *outDatesLen = 0; *outDates = 0; *outValuesLen = 0; *outValues = 0;
    try {
      TimeSeries<Real> ts;
      for (unsigned n = 0; n < len; ++n) ts[Date(dates[n])] = values[n];
      TimeSeries<Volatility> out = calc(ts);
      const std::vector<Date> outDs = out.dates();
      const std::vector<Volatility> outVs = out.values();
      ds = qlAllocateInts(outDs.size());
      vs = qlAllocateDoubles(outVs.size());
      for (unsigned n = 0; n < outDs.size(); ++n) ds[n] = outDs[n].serialNumber();
      for (unsigned n = 0; n < outVs.size(); ++n) vs[n] = outVs[n];
      *outDatesLen = outDs.size(); *outDates = ds; *outValuesLen = outVs.size(); *outValues = vs;
    } catch (std::exception& er) {
      qlFreeInts(ds); qlFreeDoubles(vs); *e = tracedup(er.what());
    }}

  // Same shape, for the GarmanKlass family's TimeSeries<IntervalPrice> input.
  void intervalPriceSeriesCalculate(const std::function<TimeSeries<Volatility>(const TimeSeries<IntervalPrice>&)>& calc,
                                     unsigned len, int *dates, double *opens, double *closes, double *highs, double *lows,
                                     unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
    int *ds = 0;
    double *vs = 0;
    *outDatesLen = 0; *outDates = 0; *outValuesLen = 0; *outValues = 0;
    try {
      TimeSeries<IntervalPrice> ts;
      for (unsigned n = 0; n < len; ++n) ts[Date(dates[n])] = IntervalPrice(opens[n], closes[n], highs[n], lows[n]);
      TimeSeries<Volatility> out = calc(ts);
      const std::vector<Date> outDs = out.dates();
      const std::vector<Volatility> outVs = out.values();
      ds = qlAllocateInts(outDs.size());
      vs = qlAllocateDoubles(outVs.size());
      for (unsigned n = 0; n < outDs.size(); ++n) ds[n] = outDs[n].serialNumber();
      for (unsigned n = 0; n < outVs.size(); ++n) vs[n] = outVs[n];
      *outDatesLen = outDs.size(); *outDates = ds; *outValuesLen = outVs.size(); *outValues = vs;
    } catch (std::exception& er) {
      qlFreeInts(ds); qlFreeDoubles(vs); *e = tracedup(er.what());
    }}
}

extern "C" {
void qlFreeInts(int *p) {delArray(p);}
// Every unsigned* out-array is actually allocated as int* via qlAllocateInts (there is no
// qlAllocateUInts) -- delegate rather than duplicate so it's traced under the type it was
// really allocated as.
void qlFreeUInts(unsigned *p) {qlFreeInts(reinterpret_cast<int*>(p));}
void qlFreeDoubles(double *p) {delArray(p);}
void qlFreePointerArray(void **p) {delArray(p);}
void qlFreeStringArray(unsigned n, char **p) {
  if (!p) return;
  for (unsigned i = 0; i < n; ++i) qlFreeString(p[i]);
  delArray(p);
}
int qlNullInteger() {return Null<Integer>();}
double qlNullReal() {return Null<Real>();}
double qlEpsilon() {return QL_EPSILON;}

Currency *qlCurrency(int ccy, char **e) {
  try {
    if (ccy < 0 || ccy >= (int)std::size(ccys))
      QL_FAIL("Invalid currency index: " << ccy);
    return alloc(ccys[ccy]());
  } catch (std::exception& er) {return handleException<Currency *>(e, er);}}

void qlFreeString(char *p) {
  // The address is captured as an integer *before* the free and cast back only for printing.
  // Reading a freed pointer's value is implementation-defined ([basic.stc]/4 -- printing it is
  // the benign case, not UB), but GCC's -Wuse-after-free rejects it anyway, and a plain
  // `void *addr = p;' copy does not help: every copy of the pointer goes invalid too, and GCC
  // flags that form as well. Only the integer round trip satisfies it. Both spellings reach
  // operator<<(const void*), so the printed form stays byte-identical to every other trace
  // line. (del()/delArray() keep the plain `trace("deleted", p)' -- same implementation-defined
  // read, but after `delete' rather than free(), which GCC does not track.)
  const auto addr = reinterpret_cast<std::uintptr_t>(p);
  trace("Freeing string", reinterpret_cast<void *>(addr));
  free(p);
  trace("Freed string", reinterpret_cast<void *>(addr));
}

/* dates are passed as int = serial number of the date, the code assumes that Haskell bindings validate date */
int qlSettingsEvaluationDate() {return Settings::instance().evaluationDate().operator Date().serialNumber();}
int qlSettingsEnforceTodaysHistoricFixings() {return Settings::instance().enforcesTodaysHistoricFixings();}

void qlSettingsSetEvaluationDate(int x, char **e) {
  try {Settings::instance().evaluationDate() = qlNullableDate(x);
  } catch (std::exception& er) {handleException<void *>(e, er);}}

void qlSettingsSetEnforceTodaysHistoricFixings(int x) {Settings::instance().enforcesTodaysHistoricFixings() = x;}
int qlSettingsIncludeTodaysCashFlows() {return qlOptBool(Settings::instance().includeTodaysCashFlows());}
void qlSettingsSetIncludeTodaysCashFlows(int x) {Settings::instance().includeTodaysCashFlows() = qlOptBool(x);}
int qlSettingsIncludeReferenceDateEvents() {return Settings::instance().includeReferenceDateEvents();}
void qlSettingsSetIncludeReferenceDateEvents(int x0) {Settings::instance().includeReferenceDateEvents() = x0;}
void *qlSavedSettings() {return ret(new SavedSettings());}
void qlFreeSavedSettings(void *settings) {del((SavedSettings *)settings);}
const char *qlVersion() {return QL_VERSION;}
const char *qlBoostVersion() {return BOOST_LIB_VERSION;}

void qlSetExtendedPrecision() {setX87ExtendedPrecision();}


void qlFreeCurrency(Currency *currency) {del(currency);}
const char *qlCurrencyName(Currency *currency) {return tracedup(arg(currency)->name().c_str());}
char* qlCurrencyCode(Currency* o) {return tracedup(arg(o)->code().c_str());}
int qlCurrencyFractionsPerUnit(Currency* o) {return arg(o)->fractionsPerUnit();}
char* qlCurrencyFractionSymbol(Currency* o) {return tracedup(arg(o)->fractionSymbol().c_str());}
int qlCurrencyNumericCode(Currency* o) {return arg(o)->numericCode();}
char* qlCurrencySymbol(Currency* o) {return tracedup(arg(o)->symbol().c_str());}
void qlFreeInterestRate(InterestRate *rate) {del(rate);}

class CustomCurrency : public Currency {
  public:
    CustomCurrency(const char* name, const char* code, int numericCode,
        const char* symbol, const char* fractionSymbol, int fractionsPerUnit,
        Rounding* rounding,
        Currency* triangulationCurrency) {
      shared_ptr<Data> data(new Data(name, code, numericCode, symbol, fractionSymbol, fractionsPerUnit,
            rounding ? *rounding : Rounding(), triangulationCurrency ? *triangulationCurrency : Currency()));
      data_ = data;
    }
};

Currency* qlCreateCurrency(char* name, char* code, int numericCode, char* symbol, char* fractionSymbol, int fractionsPerUnit, Rounding* rounding, Currency* triangulationCurrency, char **e) {
  try {
    return alloc(new CustomCurrency(arg(name), arg(code), numericCode,
          arg(symbol), arg(fractionSymbol), fractionsPerUnit,
          rounding, triangulationCurrency));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}}

ExchangeRate *qlExchangeRate(Currency *source, Currency *target, double rate, char **e) {
  try {return alloc(new ExchangeRate(*arg(source), *arg(target), rate));
  } catch (std::exception& er) {return handleException<ExchangeRate*>(e, er);}
}
void qlFreeExchangeRate(ExchangeRate *o) {del(o);}
double qlExchangeRateRate(ExchangeRate *o) {return arg(o)->rate();}
int qlExchangeRateType_(ExchangeRate *o) {return arg(o)->type();}

double qlExchangeRateExchange(ExchangeRate *o, double amount, Currency *ccy, Currency **outCcy, char **e) {
  *outCcy = 0;
  try {
    Money m = arg(o)->exchange(Money(amount, *arg(ccy)));
    *outCcy = ret(new Currency(m.currency()));
    return m.value();
  } catch (std::exception& er) {return handleException<double>(e, er);}
}

ExchangeRate *qlExchangeRateChain(ExchangeRate *r1, ExchangeRate *r2, char **e) {
  try {
    return ret(new ExchangeRate(ExchangeRate::chain(*arg(r1), *arg(r2))));
  } catch (std::exception& er) {return handleException<ExchangeRate*>(e, er);}
}

void qlExchangeRateManagerAdd(ExchangeRate *rate, int startSerial, int endSerial, char **e) {
  try {ExchangeRateManager::instance().add(*arg(rate), qlNullableDate(startSerial), qlNullableDate(endSerial));
  } catch (std::exception& er) {*e = tracedup(er.what());}
}

ExchangeRate *qlExchangeRateManagerLookup(Currency *source, Currency *target, int dateSerial, int type, char **e) {
  try {
    return ret(new ExchangeRate(ExchangeRateManager::instance().lookup(
        *arg(source), *arg(target), qlNullableDate(dateSerial), (ExchangeRate::Type)type)));
  } catch (std::exception& er) {return handleException<ExchangeRate*>(e, er);}
}

void qlExchangeRateManagerClear() {ExchangeRateManager::instance().clear();}

int qlMoneySettingsConversionType() {return Money::Settings::instance().conversionType();}
void qlMoneySettingsSetConversionType(int t) {Money::Settings::instance().conversionType() = (Money::ConversionType)t;}
Currency *qlMoneySettingsBaseCurrency(char **e) {
  try {
    const Currency &base = Money::Settings::instance().baseCurrency();
    return base.empty() ? 0 : ret(new Currency(base));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}
}
void qlMoneySettingsSetBaseCurrency(Currency *c) {Money::Settings::instance().baseCurrency() = *arg(c);}

double qlConvertToBaseCurrency(double amount, Currency *ccy, Currency **outCcy, char **e) {
  *outCcy = 0;
  try {
    const Currency &base = Money::Settings::instance().baseCurrency();
    QL_REQUIRE(!base.empty(), "no base currency set");
    Money m(amount, *arg(ccy));
    if (m.currency() != base) {
      ExchangeRate rate = ExchangeRateManager::instance().lookup(m.currency(), base);
      m = rate.exchange(m).rounded();
    }
    *outCcy = ret(new Currency(m.currency()));
    return m.value();
  } catch (std::exception& er) {return handleException<double>(e, er);}
}

InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq, char **e) {
  try {return alloc(new InterestRate(r, *arg(dc), (Compounding) comp, (Frequency) freq));
  } catch (std::exception& er) {return handleException<InterestRate *>(e, er);}}

// generated code
double qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e) {
  try {return (arg(o))->compoundFactor(Date(d1), Date(d2), Date(refStart), Date(refEnd));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlInterestRateCompoundFactor(InterestRate* o, double t, char **e) {
  try {return (arg(o))->compoundFactor(t);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e) {
  try {return (arg(o))->discountFactor(Date(d1), Date(d2), Date(refStart), Date(refEnd));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlInterestRateDiscountFactor(InterestRate* o, double t, char **e) {
  try {return (arg(o))->discountFactor(t);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

InterestRate* qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e) {
  try {return ret(new InterestRate(arg(o)->equivalentRate(*arg(resultDC), (Compounding)comp, (Frequency)freq, Date(d1), Date(d2), Date(refStart), Date(refEnd))));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}

InterestRate* qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e) {
  try {return ret(new InterestRate(arg(o)->equivalentRate((Compounding)comp, (Frequency)freq, t)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}

InterestRate* qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e) {
  try {return ret(new InterestRate(arg(o)->impliedRate(compound, *arg(resultDC), (Compounding)comp, (Frequency)freq, Date(d1), Date(d2), Date(refStart), Date(refEnd))));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}

InterestRate* qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e) {
  try {return ret(new InterestRate(arg(o)->impliedRate(compound, *arg(resultDC), (Compounding)comp, (Frequency)freq, t)));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}

Constraint* qlBoundaryConstraint(double low, double high, char **e) {
  try {return alloc(new BoundaryConstraint(low, high));
  } catch (std::exception& er) {return handleException<Constraint*>(e, er);}}
Constraint* qlCompositeConstraint(Constraint* c1, Constraint* c2, char **e) {
  try {return alloc(new CompositeConstraint(*arg(c1), *arg(c2)));
  } catch (std::exception& er) {return handleException<Constraint*>(e, er);}}
Constraint* qlNoConstraint(char **e) {
  try {return alloc(new NoConstraint());
  } catch (std::exception& er) {return handleException<Constraint*>(e, er);}}
Constraint* qlPositiveConstraint(char **e) {
  try {return alloc(new PositiveConstraint());
  } catch (std::exception& er) {return handleException<Constraint*>(e, er);}}

QlOptimizationMethod* qlLevenbergMarquardt(double epsfcn, double xtol, double gtol, int useCostFunctionsJacobian, char **e) {
  try {return ret(new QlOptimizationMethod(shared_ptr<OptimizationMethod>(alloc(new LevenbergMarquardt(epsfcn, xtol, gtol, useCostFunctionsJacobian)))));
  } catch (std::exception& er) {return handleException<QlOptimizationMethod*>(e, er);}}
QlOptimizationMethod* qlSimplex(double lambda, char **e) {
  try {return ret(new QlOptimizationMethod(shared_ptr<OptimizationMethod>(alloc(new Simplex(lambda)))));
  } catch (std::exception& er) {return handleException<QlOptimizationMethod*>(e, er);}}

QlEndCriteria* qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e) {
  try {return ret(new QlEndCriteria(shared_ptr<EndCriteria>(alloc(new EndCriteria(maxIterations, maxStationaryStateIterations, rootEpsilon, functionEpsilon, gradientNormEpsilon)))));
  } catch (std::exception& er) {return handleException<QlEndCriteria*>(e, er);}}

void qlOptimize(double (*costFn)(double*, unsigned), unsigned x0Len, double* x0, Constraint* constraint, QlOptimizationMethod* method, QlEndCriteria* endCriteria, unsigned* outLen, double** outValues, double* outCost, int* outEndCriteriaType, char **e) {
  try {
    HsCostFunction cf(costFn);
    NoConstraint noConstraint;
    Problem problem(cf, constraint ? *arg(constraint) : static_cast<Constraint&>(noConstraint), Array(x0, x0+x0Len));
    *outEndCriteriaType = (int)(*arg(method))->minimize(problem, **arg(endCriteria));
    const Array& sol = problem.currentValue();
    *outCost = problem.functionValue();
    *outLen = (unsigned)sol.size();
    *outValues = qlAllocateDoubles(*outLen);
    std::copy(sol.begin(), sol.end(), *outValues);
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}

TimeGrid* qlTimeGrid1(double end, unsigned steps, char **e) {
  try {return alloc(new TimeGrid(end, steps));
  } catch (std::exception& er) {return handleException<TimeGrid*>(e, er);}}
TimeGrid* qlTimeGrid2(unsigned x0Len, double* x0, char **e) {
  try {return alloc(new TimeGrid(x0, x0+x0Len));
  } catch (std::exception& er) {return handleException<TimeGrid*>(e, er);}}
TimeGrid* qlTimeGrid3(unsigned x0Len, double* x0, unsigned steps, char **e) {
  try {return alloc(new TimeGrid(x0, x0+x0Len, steps));
  } catch (std::exception& er) {return handleException<TimeGrid*>(e, er);}}
unsigned qlTimeGridSize(TimeGrid* t) {return arg(t)->size();}
double qlTimeGridAt(TimeGrid* t, unsigned i, char **e) {try {return arg(t)->at(i);} catch (std::exception& er) {return handleException<double>(e, er);}}
void qlTimeGridPoints(TimeGrid *t, unsigned *len, double **p, char **e) {
  try {*len = arg(t)->size(); *p = qlAllocateDoubles(*len); std::copy(t->begin(), t->end(), *p);
  } catch (std::exception& er) {(void)handleException<double*>(e, er);}}

double qlRiskStatisticsMean(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).mean();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsStandardDeviation(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).standardDeviation();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsVariance(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).variance();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsSkewness(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).skewness();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsKurtosis(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).kurtosis();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsMin(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).min();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsMax(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).max();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsSemiVariance(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).semiVariance();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsSemiDeviation(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).semiDeviation();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsDownsideVariance(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).downsideVariance();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsDownsideDeviation(unsigned n, double *xs, char **e) {
  try {return riskStats(n, xs).downsideDeviation();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsPercentile(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).percentile(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsGaussianPercentile(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).gaussianPercentile(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsValueAtRisk(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).valueAtRisk(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsGaussianValueAtRisk(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).gaussianValueAtRisk(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsExpectedShortfall(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).expectedShortfall(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsGaussianExpectedShortfall(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).gaussianExpectedShortfall(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsPotentialUpside(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).potentialUpside(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsGaussianPotentialUpside(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).gaussianPotentialUpside(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsRegret(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).regret(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsShortfall(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).shortfall(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlRiskStatisticsAverageShortfall(unsigned n, double *xs, double y, char **e) {
  try {return riskStats(n, xs).averageShortfall(y);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

Rounding* qlRounding(char **e) {try {return alloc(new Rounding());} catch (std::exception& er) {return handleException<Rounding*>(e, er);}}
Rounding* qlRounding1(int precision, int type, int digit, char **e) {try {return alloc(new Rounding(precision, (Rounding::Type)type, digit));} catch (std::exception& er) {return handleException<Rounding*>(e, er);}}

QlSimpleQuote *qlSimpleQuote(double value, char **e) {try {return ret(new QlSimpleQuote(alloc(new SimpleQuote(value))));} catch (std::exception& er) {return handleException<QlSimpleQuote *>(e, er);}}
double qlQuoteValue(QlQuote *quote, char **e) {try {return (*arg(quote))->value();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e) {try {return (*arg(o))->setValue(value);} catch (std::exception& er) {return handleException<double>(e, er);}}

QlQuote* qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new EurodollarFuturesImpliedStdDevQuote(*arg(forward), *arg(callPrice), *arg(putPrice), strike, guess, accuracy, maxIter)))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, int l, int u, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new ForwardSwapQuote(*arg(swapIndex), *arg(spread), Period(l, (TimeUnit)u))))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlForwardValueQuote(QlIndex* index, int fixingDate, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new ForwardValueQuote(*arg(index), Date(fixingDate))))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new FuturesConvAdjustmentQuote(*arg(index), std::string(arg(immCode)), *arg(futuresQuote), *arg(volatility), *arg(meanReversion))))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new FuturesConvAdjustmentQuote(*arg(index), Date(futuresDate), *arg(futuresQuote), *arg(volatility), *arg(meanReversion))))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new ImpliedStdDevQuote((Option::Type)optionType, *arg(forward), *arg(price), strike, guess, accuracy, maxIter)))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlLastFixingQuote(QlIndex* index, char **e) {try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new LastFixingQuote(*arg(index))))));} catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
int qlQuoteIsValid(QlQuote* o, char **e) {try {return (*arg(o))->isValid();} catch (std::exception& er) {return handleException<int>(e, er);}}
QlQuote* qlDerivedQuote(int op, QlQuote* element, double operand, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new OpDerivedQuote(*arg(element), QuoteUnaryOp{op, operand})))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlCompositeQuote(int op, QlQuote* element1, QlQuote* element2, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new OpCompositeQuote(*arg(element1), *arg(element2), QuoteBinaryOp{op})))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlMultiCompositeQuote(int op, unsigned elementsLen, QlQuote** elements, char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new OpMultiCompositeQuote(qlHandleVector(elements, elementsLen), QuoteArrayOp{op})))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}

QlQuote* qlDerivedQuoteFromFunction(QlQuote* element, double (*fn)(double), char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new HsDerivedQuote(*arg(element), fn)))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlCompositeQuoteFromFunction(QlQuote* element1, QlQuote* element2, double (*fn)(double, double), char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new HsCompositeQuote(*arg(element1), *arg(element2), fn)))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}
QlQuote* qlMultiCompositeQuoteFromFunction(unsigned elementsLen, QlQuote** elements, double (*fn)(const double*, unsigned), char **e) {
  try {return ret(new QlQuote(shared_ptr<Quote>(alloc(new HsMultiCompositeQuote(qlHandleVector(elements, elementsLen), HsArrayFun{fn})))));
  } catch (std::exception& er) {return handleException<QlQuote*>(e, er);}}

// A relinkable handle, empty when `initial` is null -- mirrors qlRelinkableYieldTermStructure
// in cbits/qlTermStructure.cpp; see its comments for the rationale.
QlRelinkableQuote* qlRelinkableQuote(QlQuote *initial, char **e) {
  try {return ret(initial ? new QlRelinkableQuote(handlePtr(arg(initial)))
                          : new QlRelinkableQuote());
  } catch (std::exception& er) {return handleException<QlRelinkableQuote*>(e, er);}}
void qlFreeRelinkableQuote(QlRelinkableQuote *o) {del(o);}
void qlRelinkableQuoteLinkTo(QlRelinkableQuote *o, QlQuote *c, char **e) {
  try {arg(o)->linkTo(handlePtr(arg(c)));} catch (std::exception& er) {(void)handleException<void *>(e, er);}}
// The hierarchy upcast. Copy-constructing Handle<Quote> from RelinkableHandle<Quote> is the
// same T, so link_ is shared and relinking through the original still reaches everything built
// on the upcast copy.
QlQuote* qlRelinkableQuoteAsQuote(QlRelinkableQuote *o) {return ret(new QlQuote(*arg(o)));}
void qlFreeEndCriteria(QlEndCriteria *o) {del(o);}
double qlInterestRateRate(InterestRate* o) {return arg(o)->rate();}
void qlFreeConstraint(Constraint *o) {del(o);}
void qlFreeOptimizationMethod(QlOptimizationMethod *o) {del(o);}
void qlFreeTimeGrid(TimeGrid *o) {del(o);}
void qlFreeRounding(Rounding *o) {del(o);}
double qlRound(Rounding *r, double val) {return (*r)(val);}
void qlFreeQuote(QlQuote *quote) {del(quote);}
void qlFreeSimpleQuote(QlSimpleQuote *o) {del(o);}
QlQuote* qlSimpleQuoteAsQuote(QlSimpleQuote *o) {return ret(new QlQuote(*arg(o)));}
QlDeltaVolQuote *qlDeltaVolQuote1(double delta, QlQuote *vol, double maturity, int deltaType, char **e) {
  try {return ret(new QlDeltaVolQuote(alloc(new DeltaVolQuote(delta, *arg(vol), maturity, (DeltaVolQuote::DeltaType)deltaType))));
  } catch (std::exception& er) {return handleException<QlDeltaVolQuote*>(e, er);}}
QlDeltaVolQuote *qlDeltaVolQuote2(QlQuote *vol, int deltaType, double maturity, int atmType, char **e) {
  try {return ret(new QlDeltaVolQuote(alloc(new DeltaVolQuote(*arg(vol), (DeltaVolQuote::DeltaType)deltaType, maturity, (DeltaVolQuote::AtmType)atmType))));
  } catch (std::exception& er) {return handleException<QlDeltaVolQuote*>(e, er);}}
void qlFreeDeltaVolQuote(QlDeltaVolQuote *o) {del(o);}
QlQuote* qlDeltaVolQuoteAsQuote(QlDeltaVolQuote *o) {return ret(new QlQuote(*arg(o)));}

int qlMinDateSerialNumber() {return Date::minDate().serialNumber();}
int qlMaxDateSerialNumber() {return Date::maxDate().serialNumber();}
int qlMinYear() {return Date::minDate().year();}
int qlMinMonth() {return Date::minDate().month();}
int qlMinDay() {return Date::minDate().dayOfMonth();}
int qlWeekday(int date) {return Date(date).weekday();}
int qlDateDayOfYear(int o) {return Date(o).dayOfYear();}
int qlDateEndOfMonth(int d) {return Date::endOfMonth(Date(d)).serialNumber();}
int qlDateIsEndOfMonth(int d) {return Date::isEndOfMonth(Date(d));}
int qlDateNextWeekday(int d, int w) {return Date::nextWeekday(Date(d), (Weekday)w).serialNumber();}
int qlDateNthWeekday(unsigned n, int w, int m, int y) {return Date::nthWeekday(n, (Weekday)w, (Month)m, y).serialNumber();}
int qlIMMIsIMMcode(char* in, int mainCycle) {return IMM::isIMMcode(std::string(arg(in)), mainCycle);}
int qlIMMIsIMMdate(int d, int mainCycle) {return IMM::isIMMdate(Date(d), mainCycle);}
char* qlIMMNextCode(int d, int mainCycle) {return tracedup(IMM::nextCode(Date(d), mainCycle).c_str());}
int qlIMMNextDate(int d, int mainCycle) {return IMM::nextDate(Date(d), mainCycle).serialNumber();}

char* qlIMMCode(int immDate, char **e) {try {return tracedup((IMM::code(Date(immDate))).c_str());} catch (std::exception& er) {return handleException<char*>(e, er);}}
int qlIMMDate(char* immCode, int referenceDate, char **e) {
  try {return (IMM::date(std::string(immCode), Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {return tracedup(IMM::nextCode(std::string(arg(immCode)), mainCycle, Date(referenceDate)).c_str());
  } catch (std::exception& er) {return handleException<char*>(e, er);}}

int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e) {try {return (IMM::nextDate(std::string(arg(immCode)), mainCycle, Date(referenceDate))).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlAddPeriod(int d, int n, int u, char **e) {try {return (Date(d) + Period(n, (TimeUnit)u)).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlECBAddDate(int d, char **e) {try {ECB::addDate(Date(d));} catch (std::exception& er) {(void)handleException<int>(e, er);}}
char* qlECBCode(int ecbDate, char **e) {try {return tracedup((ECB::code(Date(ecbDate))).c_str());} catch (std::exception& er) {return handleException<char*>(e, er);}}
int qlECBDate1(char* ecbCode, int referenceDate, char **e) {try {return (ECB::date(std::string(arg(ecbCode)), qlNullableDate(referenceDate))).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlECBDate(int m, int y, char **e) {try {return (ECB::date((Month)m, y)).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlECBIsECBcode(char* in, char **e) {try {return ECB::isECBcode(arg(in));} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlECBIsECBdate(int d, char **e) {try {return ECB::isECBdate(Date(d));} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlECBKnownDates(unsigned *count, int **ds, char **e) {
  try { const std::set<Date> &dates = ECB::knownDates(); *count = dates.size(); *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds, std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}
char* qlECBNextCode1(char* ecbCode, char **e) {try {return tracedup((ECB::nextCode(std::string(arg(ecbCode)))).c_str());} catch (std::exception& er) {return handleException<char*>(e, er);}}
char* qlECBNextCode(int d, char **e) {try {return tracedup((ECB::nextCode(qlNullableDate(d))).c_str());} catch (std::exception& er) {return handleException<char*>(e, er);}}
int qlECBNextDate1(char* ecbCode, int referenceDate, char **e) {
  try {return (ECB::nextDate(std::string(arg(ecbCode)), qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlECBNextDate(int d, char **e) {try {return (ECB::nextDate(qlNullableDate(d))).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlECBNextDates1(char* ecbCode, int referenceDate, unsigned *count, int **ds, char **e) {
  try {const std::vector<Date> &dates = ECB::nextDates(ecbCode, qlNullableDate(referenceDate));
    *count = dates.size(); *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds, std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {(void)handleException<int*>(e, er);}}
void qlECBNextDates(int d, unsigned *count, int **ds, char **e) {
  try {const std::vector<Date> &dates = ECB::nextDates(qlNullableDate(d));
    *count = dates.size(); *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds, std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {(void)handleException<int*>(e, er);}}
void qlECBRemoveDate(int d, char **e) {try {ECB::removeDate(Date(d));} catch (std::exception& er) {(void)handleException<int>(e, er);}}

const char *qlCalendarName(Calendar *calendar) {std::string name = arg(calendar)->name(); return tracedup(name.c_str());}
// must match with the order of qlEnumObjects.h:CalendarCountry
static const makeCal calendars[] = {
  &makeCalendar<Argentina>
  , &makeMarketCalendar<Australia>
  , &makeMarketCalendar<Austria>
  , &makeCalendar<Botswana>
  , &makeMarketCalendar<Brazil>
  , &makeMarketCalendar<Canada>
  , &makeMarketCalendar<China>
  , &makeCalendar<CzechRepublic>
  , &makeCalendar<Denmark>
  , &makeCalendar<Finland>
  , &makeMarketCalendar<France>
  , &makeMarketCalendar<Germany>
  , &makeCalendar<HongKong>
  , &makeCalendar<Hungary>
  , &makeCalendar<Iceland>
  , &makeCalendar<India>
  , &makeMarketCalendar<Indonesia>
  , &makeMarketCalendar<Israel>
  , &makeMarketCalendar<Italy>
  , &makeCalendar<Japan>
  , &makeCalendar<Mexico>
  , &makeMarketCalendar<NewZealand>
  , &makeCalendar<Norway>
  , &makeCalendar<NullCalendar>
  , &makeMarketCalendar<Poland>
  , &makeMarketCalendar<Romania>
  , &makeMarketCalendar<Russia>
  , &makeCalendar<SaudiArabia>
  , &makeCalendar<Singapore>
  , &makeCalendar<Slovakia>
  , &makeCalendar<SouthAfrica>
  , &makeMarketCalendar<SouthKorea>
  , &makeCalendar<Sweden>
  , &makeCalendar<Switzerland>
  , &makeCalendar<Taiwan>
  , &makeCalendar<TARGET>
  , &makeCalendar<Thailand>
  , &makeCalendar<Turkey>
  , &makeCalendar<Ukraine>
  , &makeMarketCalendar<UnitedKingdom>
  , &makeMarketCalendar<UnitedStates>
  , &makeCalendar<WeekendsOnly>
  , &makeCalendar<Chile>
  , &makeCalendar<Croatia>
  , &makeCalendar<Malta>
  , &makeCalendar<Montenegro>
  , &makeCalendar<NorthMacedonia>
  , &makeCalendar<Serbia>
  , &makeCalendar<Slovenia>
  , &makeCalendar<Uzbekistan>
};

Calendar *qlCalendar(int country, int market, char **e) {
  try {
    if (country < 0 || country >= (int)std::size(calendars))
      QL_FAIL("Invalid country index: " << country);
    return alloc(calendars[country](market));
  } catch (std::exception& er) {return handleException<Calendar *>(e, er);}}

int qlCalendarAdjust(Calendar *c, int date, int conv, char **e) {
  try {return arg(c)->adjust(Date(date), (BusinessDayConvention) conv).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom, char **e) {
  try {return arg(c)->advance(Date(date), n, (TimeUnit) unit,(BusinessDayConvention) conv, eom).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
void qlCalendarAddHoliday(Calendar* o, int x0, char **e) {try {arg(o)->addHoliday(Date(x0));} catch (std::exception& er) {(void)handleException<int>(e, er);}}

int qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e) {
  try {return arg(o)->businessDaysBetween(Date(from), Date(to), includeFirst, includeLast);
  } catch (std::exception& er) {return handleException<int>(e, er);}}

int qlCalendarEndOfMonth(Calendar* o, int d, char **e) {try {return (arg(o)->endOfMonth(Date(d))).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCalendarIsBusinessDay(Calendar* o, int d, char **e) {try {return arg(o)->isBusinessDay(Date(d));} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCalendarIsEndOfMonth(Calendar* o, int d, char **e) {try {return arg(o)->isEndOfMonth(Date(d));} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCalendarIsHoliday(Calendar* o, int d, char **e) {try {return arg(o)->isHoliday(Date(d));} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCalendarIsWeekend(Calendar* o, int w, char **e) {try {return arg(o)->isWeekend((Weekday) w);} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlCalendarRemoveHoliday(Calendar* o, int x0, char **e) {try {arg(o)->removeHoliday(Date(x0));} catch (std::exception& er) {(void)handleException<int>(e, er);}}

Calendar* qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e) {
  try {
    // BespokeCalendar keeps its own extra shared_ptr member (bespokeImpl_,
    // aliased to the same control block as the inherited impl_) alongside
    // Calendar's. qlFreeCalendar deletes through a bare Calendar*, and
    // Calendar has no virtual destructor -- deleting a *BespokeCalendar
    // through Calendar* would only run ~Calendar(), leaking bespokeImpl_'s
    // refcount share and the Impl object with it. So finish building it here
    // as a BespokeCalendar (needs addWeekend, only on that type), then heap-
    // allocate a plain Calendar sliced from it: same underlying Impl control
    // block (Calendar's copy ctor just copies impl_), but now the object
    // qlFreeCalendar deletes really is a Calendar, so slicing never happens.
    BespokeCalendar cal{std::string(name)};
    for (unsigned i = 0; i < len; i++)
      cal.addWeekend((Weekday)weekends[i]);
    return ret(new Calendar(cal));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}

Calendar* qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e) {
  try {return allocAs<Calendar>(new JointCalendar(*arg(x_1), *arg(x0), *arg(x1), *arg(x2), (JointCalendarRule)x3));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}
Calendar* qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e) {
  try {return allocAs<Calendar>(new JointCalendar(*arg(x_1), *arg(x0), *arg(x1), (JointCalendarRule)x2));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}
Calendar* qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e) {
  try {return allocAs<Calendar>(new JointCalendar(*arg(x_1), *arg(x0), (JointCalendarRule)x1));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}
void qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, int **days, char **e) {
  try {const std::vector<Date> dates = arg(calendar)->holidayList(Date(from), Date(to), includeWeekEnds);
    *len = dates.size(); *days = qlAllocateInts(*len);
    for (size_t i = 0; i < dates.size(); ++i)
      (*days)[i] = dates[i].serialNumber();
  } catch (std::exception& er) {(void)handleException<int*>(e, er);}}
Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv, int termConv, int tenorLen, int tenorUnit, int rule, int eom, char **e) {
  try {std::vector<Date> d; d.reserve(len);
    for (unsigned i = 0; i < len; ++i)
      d.push_back(Date(dates[i]));
    return alloc(new Schedule(d, *arg(cal), (BusinessDayConvention) conv,
      qlOptBusinessDayConvention(termConv),
      tenorUnit < 0 ? ext::optional<Period>() : ext::optional<Period>(Period(tenorLen, (TimeUnit)tenorUnit)),
      rule < 0 ? ext::optional<DateGeneration::Rule>() : ext::optional<DateGeneration::Rule>((DateGeneration::Rule)rule),
      qlOptBool(eom)));
  } catch (std::exception& er) {return handleException<Schedule *>(e, er);}}
Schedule *qlSchedule(int eff, int term, int l, int u, Calendar *cal, int conv, int termConv, int rule, int eom, int first, int nextToLast, char **e) {
  try {return alloc(new Schedule(qlNullableDate(eff), Date(term), Period(l, (TimeUnit)u), *arg(cal),
        (BusinessDayConvention) conv, (BusinessDayConvention) termConv, (DateGeneration::Rule) rule,
        eom, qlNullableDate(first), qlNullableDate(nextToLast)));
  } catch (std::exception& er) {return handleException<Schedule *>(e, er);}}
Schedule *qlScheduleUntil(Schedule *sched, int date, char **e) {
  try {return alloc(new Schedule(arg(sched)->until(Date(date))));
  } catch (std::exception& er) {return handleException<Schedule *>(e, er);}}
void qlScheduleDates(Schedule *sched, unsigned *count, int **days, char **e) {
  *count = 0; *days = nullptr;
  int *out = nullptr;
  try {
    const std::vector<Date> &dates = arg(sched)->dates();
    out = qlAllocateInts(dates.size());
    for (size_t i = 0; i < dates.size(); ++i)
      out[i] = dates[i].serialNumber();
    *count = dates.size(); *days = out;
  } catch (std::exception& er) {qlFreeInts(out); *e = tracedup(er.what());}
}

int qlPeriodFromFrequency1(int freq, int *u, char **e) {
  try {Period p((Frequency) freq); *u = p.units(); return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlPeriodToFrequency1(int l, int u, char **e) {
  try {return Period(l, (TimeUnit)u).frequency();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlPeriodParserParse1(char* str, int* u, char **e) {
  try {const Period &p = (PeriodParser::parse(std::string(arg(str)))); *u = p.units(); return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlPeriodAdd1(int n1, int u1, int n2, int u2, int *u, char **e) {
  try {Period p = Period(n1, (TimeUnit)u1) + Period(n2, (TimeUnit)u2); *u = p.units(); return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlPeriodDivide1(int n1, int u1, int n, int *u, char **e) {
  try {Period p = Period(n1, (TimeUnit)u1)/n; *u = p.units(); return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlPeriodNormalize1(int n1, int u1, int *u, char **e) {
  try {Period p(n1, (TimeUnit)u1); p.normalize(); *u = p.units(); return p.length();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlPeriodsLT1(int n1, int u1, int n2, int u2, char **e) {
  try {Period p1(n1, (TimeUnit)u1); Period p2(n2, (TimeUnit)u2); return p1 < p2;
  } catch (std::exception& er) {return handleException<int>(e, er);}}


// must match with the order of qlEnumObjects.h:DayCounterType
static const makeDc dayCounters[] = {
  &makeFlagDayCounter<Actual360>
  , &makeDayCounter<Actual364>
  , &makeConvDayCounter<Actual365Fixed>
  , &makeConvDayCounter<ActualActual>
  , &makeDayCounter<OneDayCounter>
  , &makeDayCounter<SimpleDayCounter>
  , &makeConvDayCounter<Thirty360>
  , &makeDayCounter<Thirty365>
  , &makeFlagDayCounter<Actual36525>
  , &makeFlagDayCounter<Actual366>
};

DayCounter *qlDayCounter(int type, int convention, char **e) {
  try {
    if (type < 0 || type >= (int)std::size(dayCounters))
      QL_FAIL("Invalid DayCounter type: " << type);
    return alloc(dayCounters[type](convention));
  } catch (std::exception& er) {return handleException<DayCounter *>(e, er);}}

DayCounter *qlDayCounterBusiness252(Calendar *cal, char **e) {try {return allocAs<DayCounter>(new Business252(*arg(cal)));} catch (std::exception& er) {return handleException<DayCounter *>(e, er);}}
DayCounter *qlDayCounterActualActualBond(Schedule *schedule, char **e) {try {return allocAs<DayCounter>(new ActualActual(ActualActual::Bond, *arg(schedule)));} catch (std::exception& er) {return handleException<DayCounter *>(e, er);}}
DayCounter *qlDayCounterActualActualISMA(Schedule *schedule, char **e) {try {return allocAs<DayCounter>(new ActualActual(ActualActual::ISMA, *arg(schedule)));} catch (std::exception& er) {return handleException<DayCounter *>(e, er);}}
void qlFreeCalendar(Calendar *calendar) {del(calendar);}
void qlFreeSchedule(Schedule *s) {del(s);}
void  qlFreeDayCounter(DayCounter *counter) {del(counter);}
const char *qlDayCounterName(DayCounter *counter) {std::string name = arg(counter)->name(); return tracedup(name.c_str());}
int qlDayCounterDayCount(DayCounter* o, int x0, int x1) {return arg(o)->dayCount(Date(x0), Date(x1));}

double qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e) {
  try {return arg(o)->yearFraction(Date(x0), Date(x1), qlNullableDate(refPeriodStart), qlNullableDate(refPeriodEnd));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

/* CommodityType */

CommodityType *qlCommodityType(char *code, char *name, char **e) {
  // commoditytype.hpp's declaration names its params (code, name), but the out-of-line
  // definition in commoditytype.cpp takes (name, code) -- and that's what actually executes.
  try {return alloc(new CommodityType(arg(name), arg(code)));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}

CommodityType *qlNullCommodityType(char **e) {
  try {return alloc(new CommodityType(NullCommodityType()));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}

void qlFreeCommodityType(CommodityType *o) {del(o);}
char *qlCommodityTypeCode(CommodityType *o) {return tracedup(arg(o)->code().c_str());}
char *qlCommodityTypeName(CommodityType *o) {return tracedup(arg(o)->name().c_str());}
int qlCommodityTypeEmpty(CommodityType *o) {return arg(o)->empty();}

/* UnitOfMeasure */

UnitOfMeasure *qlUnitOfMeasure(char *name, char *code, int unitType, char **e) {
  try {return alloc(new UnitOfMeasure(arg(name), arg(code), (UnitOfMeasure::Type)unitType));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}

void qlFreeUnitOfMeasure(UnitOfMeasure *o) {del(o);}
char *qlUnitOfMeasureName(UnitOfMeasure *o) {return tracedup(arg(o)->name().c_str());}
char *qlUnitOfMeasureCode(UnitOfMeasure *o) {return tracedup(arg(o)->code().c_str());}
int qlUnitOfMeasureUnitType(UnitOfMeasure *o) {return arg(o)->unitType();}
int qlUnitOfMeasureEmpty(UnitOfMeasure *o) {return arg(o)->empty();}

UnitOfMeasure *qlLotUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(LotUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlBarrelUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(BarrelUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlMTUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(MTUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlMBUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(MBUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlGallonUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(GallonUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlLitreUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(LitreUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlKilolitreUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(KilolitreUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlTokyoKilolitreUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(TokyoKilolitreUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}

/* PaymentTerm */

PaymentTerm *qlPaymentTerm(char *name, int eventType, int offsetDays, Calendar *calendar, char **e) {
  try {return alloc(new PaymentTerm(arg(name), (PaymentTerm::EventType)eventType, offsetDays, *arg(calendar)));
  } catch (std::exception& er) {return handleException<PaymentTerm*>(e, er);}}

void qlFreePaymentTerm(PaymentTerm *o) {del(o);}
char *qlPaymentTermName(PaymentTerm *o) {return tracedup(arg(o)->name().c_str());}
int qlPaymentTermEventType_(PaymentTerm *o) {return arg(o)->eventType();}
int qlPaymentTermOffsetDays(PaymentTerm *o) {return arg(o)->offsetDays();}
Calendar *qlPaymentTermCalendar(PaymentTerm *o, char **e) {
  try {return ret(new Calendar(arg(o)->calendar()));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}
int qlPaymentTermEmpty(PaymentTerm *o) {return arg(o)->empty();}

int qlPaymentTermGetPaymentDate(PaymentTerm *o, int date, char **e) {
  try {return arg(o)->getPaymentDate(qlNullableDate(date)).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}

/* Quantity -- see qlCommodity.h on why this is three flat arguments, not one tuple. */

double qlQuantityRoundedAmount(UnitOfMeasure *uom, double amount) {
  return arg(uom)->rounding()(amount);}

int qlQuantityClose(CommodityType *ct1, UnitOfMeasure *uom1, double amount1,
                    CommodityType *ct2, UnitOfMeasure *uom2, double amount2, int n, char **e) {
  try {return close(Quantity(*arg(ct1), *arg(uom1), amount1),
                    Quantity(*arg(ct2), *arg(uom2), amount2), n);
  } catch (std::exception& er) {return handleException<int>(e, er);}}

int qlQuantityCloseEnough(CommodityType *ct1, UnitOfMeasure *uom1, double amount1,
                          CommodityType *ct2, UnitOfMeasure *uom2, double amount2, int n, char **e) {
  try {return close_enough(Quantity(*arg(ct1), *arg(uom1), amount1),
                           Quantity(*arg(ct2), *arg(uom2), amount2), n);
  } catch (std::exception& er) {return handleException<int>(e, er);}}

/* UnitOfMeasureConversion */

UnitOfMeasureConversion *qlUnitOfMeasureConversion(CommodityType *commodityType, UnitOfMeasure *source,
                                                   UnitOfMeasure *target, double conversionFactor, char **e) {
  try {return alloc(new UnitOfMeasureConversion(*arg(commodityType), *arg(source), *arg(target), conversionFactor));
  } catch (std::exception& er) {return handleException<UnitOfMeasureConversion*>(e, er);}}

void qlFreeUnitOfMeasureConversion(UnitOfMeasureConversion *o) {del(o);}
UnitOfMeasure *qlUnitOfMeasureConversionSource(UnitOfMeasureConversion *o, char **e) {
  try {return ret(new UnitOfMeasure(arg(o)->source()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlUnitOfMeasureConversionTarget(UnitOfMeasureConversion *o, char **e) {
  try {return ret(new UnitOfMeasure(arg(o)->target()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
CommodityType *qlUnitOfMeasureConversionCommodityType(UnitOfMeasureConversion *o, char **e) {
  try {return ret(new CommodityType(arg(o)->commodityType()));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}
int qlUnitOfMeasureConversionType_(UnitOfMeasureConversion *o) {return arg(o)->type();}
double qlUnitOfMeasureConversionFactor(UnitOfMeasureConversion *o) {return arg(o)->conversionFactor();}
char *qlUnitOfMeasureConversionCode(UnitOfMeasureConversion *o) {return tracedup(arg(o)->code().c_str());}

double qlUnitOfMeasureConversionConvert(UnitOfMeasureConversion *o, CommodityType *ct, UnitOfMeasure *uom,
                                        double amount, CommodityType **outCt, UnitOfMeasure **outUom, char **e) {
  *outCt = 0; *outUom = 0;
  try {
    Quantity r = arg(o)->convert(Quantity(*arg(ct), *arg(uom), amount));
    // unique_ptr until both allocations have succeeded -- same shape as qlEnergyCommodityQuantity
    // (qlInstrument.cpp): a throw from the second releases the first with no cleanup in the catch,
    // and ret() runs only on the pointers actually handed out.
    std::unique_ptr<CommodityType> ct2(new CommodityType(r.commodityType()));
    std::unique_ptr<UnitOfMeasure> uom2(new UnitOfMeasure(r.unitOfMeasure()));
    *outCt = ret(ct2.release());
    *outUom = ret(uom2.release());
    return r.amount();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }}

UnitOfMeasureConversion *qlUnitOfMeasureConversionChain(UnitOfMeasureConversion *r1, UnitOfMeasureConversion *r2, char **e) {
  try {return alloc(new UnitOfMeasureConversion(UnitOfMeasureConversion::chain(*arg(r1), *arg(r2))));
  } catch (std::exception& er) {return handleException<UnitOfMeasureConversion*>(e, er);}}

/* UnitOfMeasureConversionManager */

UnitOfMeasureConversion *qlUnitOfMeasureConversionManagerLookup(
    CommodityType *commodityType, UnitOfMeasure *source, UnitOfMeasure *target, int type, char **e) {
  try {return alloc(new UnitOfMeasureConversion(UnitOfMeasureConversionManager::instance().lookup(
      *arg(commodityType), *arg(source), *arg(target), (UnitOfMeasureConversion::Type)type)));
  } catch (std::exception& er) {return handleException<UnitOfMeasureConversion*>(e, er);}}

void qlUnitOfMeasureConversionManagerAdd(UnitOfMeasureConversion *c) {
  UnitOfMeasureConversionManager::instance().add(*arg(c));}

void qlUnitOfMeasureConversionManagerClear() {UnitOfMeasureConversionManager::instance().clear();}

/* CommoditySettings */

Currency *qlCommoditySettingsCurrency(char **e) {
  try {return ret(new Currency(CommoditySettings::instance().currency()));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}}
void qlCommoditySettingsSetCurrency(Currency *c) {CommoditySettings::instance().currency() = *arg(c);}
UnitOfMeasure *qlCommoditySettingsUnitOfMeasure(char **e) {
  try {return ret(new UnitOfMeasure(CommoditySettings::instance().unitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
void qlCommoditySettingsSetUnitOfMeasure(UnitOfMeasure *u) {CommoditySettings::instance().unitOfMeasure() = *arg(u);}

/* HistoricalIndexAnalysis */

namespace QuantLib {
  // hasquant-local: generalizes upstream's HistoricalRatesAnalysis (InterestRateIndex-only,
  // ql/models/marketmodels/historicalratesanalysis.hpp) to any Index. Mirrors that class's own
  // accessor shape (stats()/skippedDates()/skippedDatesErrorMessage()) so the shim functions
  // below read identically to how they read the upstream class before this generalization.
  class HistoricalIndexAnalysis {
    public:
      HistoricalIndexAnalysis(shared_ptr<SequenceStatistics> stats,
                               std::vector<Date> skippedDates,
                               std::vector<std::string> skippedDatesErrorMessage)
        : stats_(std::move(stats)), skippedDates_(std::move(skippedDates)),
          skippedDatesErrorMessage_(std::move(skippedDatesErrorMessage)) {}
      const shared_ptr<SequenceStatistics>& stats() const {return stats_;}
      const std::vector<Date>& skippedDates() const {return skippedDates_;}
      const std::vector<std::string>& skippedDatesErrorMessage() const {return skippedDatesErrorMessage_;}
    private:
      shared_ptr<SequenceStatistics> stats_;
      std::vector<Date> skippedDates_;
      std::vector<std::string> skippedDatesErrorMessage_;
  };
}

static void fillVectorOut(const std::vector<Real>& a, unsigned* len, double** vs) {
  *len = (unsigned)a.size();
  *vs = qlAllocateDoubles(*len);
  std::copy(a.begin(), a.end(), *vs);
}

static void fillMatrixOut(const Matrix& m, unsigned* rows, unsigned* cols, unsigned* len, double** vs) {
  *rows = (unsigned)m.rows(); *cols = (unsigned)m.columns(); *len = (unsigned)(m.rows() * m.columns());
  *vs = qlAllocateDoubles(*len);
  std::copy(m.begin(), m.end(), *vs);
}

QlHistoricalIndexAnalysis *qlHistoricalIndexAnalysis(int startDate, int endDate,
    int stepLen, int stepUnit, unsigned indexesLen, QlIndex **indexes, char **e) {
  try {
    Size nIdx = indexesLen;
    shared_ptr<SequenceStatistics> stats = ext::make_shared<SequenceStatistics>(nIdx);
    std::vector<Date> skippedDates;
    std::vector<std::string> skippedDatesErrorMessage;

    // Transcribed from ql/models/marketmodels/historicalratesanalysis.cpp's free function,
    // generalized from InterestRateIndex to the generic Index base (fixing/fixingCalendar are
    // both declared there already) so it isn't limited to interest-rate underlyings.
    std::vector<Real> sample(nIdx), prevSample(nIdx), sampleDiff(nIdx);
    Calendar cal = (*arg(indexes[0]))->fixingCalendar();
    Date currentDate = cal.advance(Date(startDate), 1*Days, Following);
    bool isFirst = true;
    for (; currentDate <= Date(endDate);
        currentDate = cal.advance(currentDate, Period(stepLen, (TimeUnit)stepUnit), Following)) {
      try {
        for (Size i = 0; i < nIdx; ++i)
          sample[i] = (*arg(indexes[i]))->fixing(currentDate, false);
      } catch (std::exception& er) {
        skippedDates.push_back(currentDate);
        skippedDatesErrorMessage.emplace_back(er.what());
        continue;
      }
      if (!isFirst) {
        for (Size i = 0; i < nIdx; ++i)
          sampleDiff[i] = sample[i]/prevSample[i] - 1.0;
        stats->add(sampleDiff.begin(), sampleDiff.end());
      } else isFirst = false;
      std::swap(prevSample, sample);
    }

    return ret(new QlHistoricalIndexAnalysis(alloc(new HistoricalIndexAnalysis(
        stats, skippedDates, skippedDatesErrorMessage))));
  } catch (std::exception& er) {return handleException<QlHistoricalIndexAnalysis*>(e, er);}}

void qlFreeHistoricalIndexAnalysis(QlHistoricalIndexAnalysis *o) {del(o);}

void qlHistoricalIndexAnalysisSkippedDates(QlHistoricalIndexAnalysis *o, unsigned *count, int **days, char **e) {
  *count = 0; *days = nullptr;
  int *out = nullptr;
  try {
    const std::vector<Date> &dates = (*arg(o))->skippedDates();
    out = qlAllocateInts(dates.size());
    for (unsigned i = 0; i < dates.size(); ++i) out[i] = dates[i].serialNumber();
    *count = dates.size(); *days = out;
  } catch (std::exception& er) {qlFreeInts(out); *e = tracedup(er.what());}
}

void qlHistoricalIndexAnalysisSkippedDatesErrorMessage(QlHistoricalIndexAnalysis *o, unsigned *count, char ***msgs, char **e) {
  *count = 0; *msgs = 0;
  unsigned n = 0;
  char **ms = nullptr;
  try {
    const std::vector<std::string> &m = (*arg(o))->skippedDatesErrorMessage();
    n = (unsigned)m.size();
    // ret() (not retPtrArray()): this spine is released by qlFreeStringArray, whose char**
    // parameter is what its own trace names -- see qlCommodityPricingErrors for the same pairing.
    ms = ret(new char*[n]());
    for (unsigned i = 0; i < n; ++i) ms[i] = tracedup(m[i].c_str());
    *msgs = ms; *count = n;
  } catch (std::exception& er) {qlFreeStringArray(n, ms); *e = tracedup(er.what());}
}

void qlHistoricalIndexAnalysisMean(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->mean(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisStandardDeviation(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->standardDeviation(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisSkewness(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->skewness(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisKurtosis(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->kurtosis(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisMin(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->min(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisMax(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->max(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisSemiVariance(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->semiVariance(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisSemiDeviation(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->semiDeviation(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisDownsideVariance(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->downsideVariance(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisDownsideDeviation(QlHistoricalIndexAnalysis *o, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->downsideDeviation(), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisPercentile(QlHistoricalIndexAnalysis *o, double y, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->percentile(y), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisGaussianPercentile(QlHistoricalIndexAnalysis *o, double y, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->gaussianPercentile(y), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisValueAtRisk(QlHistoricalIndexAnalysis *o, double centile, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->valueAtRisk(centile), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisGaussianValueAtRisk(QlHistoricalIndexAnalysis *o, double centile, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->gaussianValueAtRisk(centile), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisExpectedShortfall(QlHistoricalIndexAnalysis *o, double centile, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->expectedShortfall(centile), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisGaussianExpectedShortfall(QlHistoricalIndexAnalysis *o, double centile, unsigned *len, double **vs, char **e) {
  try {fillVectorOut((*arg(o))->stats()->gaussianExpectedShortfall(centile), len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisCovariance(QlHistoricalIndexAnalysis *o, unsigned *rows, unsigned *cols, unsigned *len, double **vs, char **e) {
  try {fillMatrixOut((*arg(o))->stats()->covariance(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

void qlHistoricalIndexAnalysisCorrelation(QlHistoricalIndexAnalysis *o, unsigned *rows, unsigned *cols, unsigned *len, double **vs, char **e) {
  try {fillMatrixOut((*arg(o))->stats()->correlation(), rows, cols, len, vs);
  } catch (std::exception& er) {handleException<double*>(e, er);}}

Garch11 *qlGarch11(double alpha, double beta, double vl) {return alloc(new Garch11(alpha, beta, vl));}
Garch11 *qlGarch11Calibrated(unsigned datesLen, int *dates, unsigned /*valuesLen*/, double *values, int mode, char **e) {
  try {
    Garch11::time_series ts;
    for (unsigned n = 0; n < datesLen; ++n) ts[Date(dates[n])] = values[n];
    return alloc(new Garch11(ts, (Garch11::Mode)mode));
  } catch (std::exception& er) {return handleException<Garch11*>(e, er);}}
void qlFreeGarch11(Garch11 *o) {del(o);}
double qlGarch11Alpha(Garch11 *o) {return arg(o)->alpha();}
double qlGarch11Beta(Garch11 *o) {return arg(o)->beta();}
double qlGarch11Omega(Garch11 *o) {return arg(o)->omega();}
double qlGarch11LtVol(Garch11 *o) {return arg(o)->ltVol();}
double qlGarch11LogLikelihood(Garch11 *o) {return arg(o)->logLikelihood();}
double qlGarch11Forecast(Garch11 *o, double r, double sigma2) {return arg(o)->forecast(r, sigma2);}
void qlGarch11Calculate(Garch11 *o, unsigned datesLen, int *dates, unsigned /*valuesLen*/, double *values,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  Garch11 *g = arg(o);
  realSeriesCalculate([g](const TimeSeries<Real>& ts){return g->calculate(ts);},
      datesLen, dates, values, outDatesLen, outDates, outValuesLen, outValues, e);
}

void qlGarmanKlassSimpleSigma(double yearFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  GarmanKlassSimpleSigma est(yearFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlGarmanKlassSigma1(double yearFraction, double marketOpenFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  GarmanKlassSigma1 est(yearFraction, marketOpenFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlParkinsonSigma(double yearFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  ParkinsonSigma est(yearFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlGarmanKlassSigma3(double yearFraction, double marketOpenFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  GarmanKlassSigma3 est(yearFraction, marketOpenFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlGarmanKlassSigma4(double yearFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  GarmanKlassSigma4 est(yearFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlGarmanKlassSigma5(double yearFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  GarmanKlassSigma5 est(yearFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlGarmanKlassSigma6(double yearFraction, double marketOpenFraction,
    unsigned datesLen, int *dates, unsigned /*opensLen*/, double *opens, unsigned /*closesLen*/, double *closes,
    unsigned /*highsLen*/, double *highs, unsigned /*lowsLen*/, double *lows,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  GarmanKlassSigma6 est(yearFraction, marketOpenFraction);
  intervalPriceSeriesCalculate([&est](const TimeSeries<IntervalPrice>& ts){return est.calculate(ts);},
      datesLen, dates, opens, closes, highs, lows, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlConstantVolatilityEstimator(unsigned windowSize,
    unsigned datesLen, int *dates, unsigned /*valuesLen*/, double *values,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  ConstantEstimator est(windowSize);
  realSeriesCalculate([&est](const TimeSeries<Real>& ts){return est.calculate(ts);},
      datesLen, dates, values, outDatesLen, outDates, outValuesLen, outValues, e);
}
void qlSimpleLocalVolatilityEstimator(double yearFraction,
    unsigned datesLen, int *dates, unsigned /*valuesLen*/, double *values,
    unsigned *outDatesLen, int **outDates, unsigned *outValuesLen, double **outValues, char **e) {
  SimpleLocalEstimator est(yearFraction);
  realSeriesCalculate([&est](const TimeSeries<Real>& ts){return est.calculate(ts);},
      datesLen, dates, values, outDatesLen, outDates, outValuesLen, outValues, e);
}
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
