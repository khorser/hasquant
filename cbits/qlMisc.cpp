#include <ql/settings.hpp>
#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>
#include <ql/currencies/all.hpp>
#include <ql/interestrate.hpp>
#include <ql/math/optimization/all.hpp>
#include <ql/timegrid.hpp>
#include <ql/math/rounding.hpp>
#include <ql/quotes/all.hpp>
#ifdef QLTRACK_ALLOCATIONS
# include <sstream>
#endif

#include "qlaux.h"
#include "qlMisc.h"

using namespace QuantLib;

int qlSettingsEvaluationDate() {
  Date d = Settings::instance().evaluationDate();
  return d.serialNumber();
}

int qlSettingsEnforceTodaysHistoricFixings() {return Settings::instance().enforcesTodaysHistoricFixings();}

void qlSettingsSetEvaluationDate(int x, char **e) {
  try {
    Settings::instance().evaluationDate() = qlNullableDate(x);
  } catch (std::exception& er) {
    handleException<void *>(e, er);
  }
}

void qlSettingsSetEnforceTodaysHistoricFixings(int x) {Settings::instance().enforcesTodaysHistoricFixings() = x;}

int qlSettingsIncludeTodaysCashFlows() {return qlOptBool(Settings::instance().includeTodaysCashFlows());}

void qlSettingsSetIncludeTodaysCashFlows(int x) {Settings::instance().includeTodaysCashFlows() = qlOptBool(x);}

int qlSettingsIncludeReferenceDateEvents() {return Settings::instance().includeReferenceDateEvents();}

void qlSettingsSetIncludeReferenceDateEvents(int x0) {Settings::instance().includeReferenceDateEvents() = x0;}

void *qlSavedSettings() {return new SavedSettings();}

void qlFreeSavedSettings(void *settings) {delete (SavedSettings *)settings;}

const char *qlVersion() {return QL_VERSION;}

const char *qlBoostVersion() {return BOOST_LIB_VERSION;}

void qlFreeString(char *p) {
#ifdef QLTRACK_ALLOCATIONS
  std::ostringstream os; os << (void *)p;
  void *ptr = (void *)os.str().c_str();
  (void)traceval("Freeing string", ptr);
#endif
  free(p);
#ifdef QLTRACK_ALLOCATIONS
  (void)traceval("Freed string", ptr);
#endif
}

int *qlAllocateInts(size_t size) {return new int[size];}

void qlFreeInts(int *p) {delete[] p;}

void qlFreeUInts(unsigned *p) {delete[] p;}

double *qlAllocateDoubles(size_t size) {return new double[size];}

void qlFreeDoubles(double *p) {delete[] p;}

const QuantLib::Date qlNullableDate(int serialNumber) {return !serialNumber ? Date() : Date(serialNumber);}

int qlNullableDate(const QuantLib::Date &date) {return date == Date() ? 0 : date.serialNumber();}

boost::optional<bool> qlOptBool(int b) {return b == -1 ? boost::none : boost::optional<bool>(b);}

int qlOptBool(boost::optional<bool> b) {return b ? *b : -1;}

char *tracedup(const char *p) {
  TP2("Duplicating string", (void *)p);
  char *dup = strdup(p);
#ifdef QLTRACK_ALLOCATIONS
  std::ostringstream os; os << (void *)dup;
  (void)traceval("Duplicate string", (void *)os.str().c_str());
#endif
  return dup;
}

std::vector<Date> qlDateVector(unsigned len, int *dates) {
  std::vector<Date> d;
  for (unsigned i = 0; i < len; ++i)
    d.push_back(Date(dates[i]));
  return d;
}

Matrix qlBuildMatrix(double *a, unsigned r, unsigned c) {
  Matrix m (r, c);
  std::copy(a, a + r*c, m.begin());
  return m;
}

void **qlAllocatePointerArray(size_t size) {return new void*[size];}

void qlFreePointerArray(void **p) {delete[] p;}

int qlNullInteger() {return QL_NULL_INTEGER;}

double qlNullReal() {return QL_NULL_REAL;}

double qlEpsilon() {return QL_EPSILON;}

typedef Currency *(*makeCcy)();

// must match the order of qlEnumObjects.h:Ccy
static const makeCcy ccys[] = {
    [](){return static_cast<Currency *>(new ARSCurrency());}
  , [](){return static_cast<Currency *>(new ATSCurrency());}
  , [](){return static_cast<Currency *>(new AUDCurrency());}
  , [](){return static_cast<Currency *>(new BCHCurrency());}
  , [](){return static_cast<Currency *>(new BDTCurrency());}
  , [](){return static_cast<Currency *>(new BEFCurrency());}
  , [](){return static_cast<Currency *>(new BGLCurrency());}
  , [](){return static_cast<Currency *>(new BRLCurrency());}
  , [](){return static_cast<Currency *>(new BTCCurrency());}
  , [](){return static_cast<Currency *>(new BYRCurrency());}
  , [](){return static_cast<Currency *>(new CADCurrency());}
  , [](){return static_cast<Currency *>(new CHFCurrency());}
  , [](){return static_cast<Currency *>(new CLPCurrency());}
  , [](){return static_cast<Currency *>(new CNYCurrency());}
  , [](){return static_cast<Currency *>(new COPCurrency());}
  , [](){return static_cast<Currency *>(new CYPCurrency());}
  , [](){return static_cast<Currency *>(new CZKCurrency());}
  , [](){return static_cast<Currency *>(new DASHCurrency());}
  , [](){return static_cast<Currency *>(new DEMCurrency());}
  , [](){return static_cast<Currency *>(new DKKCurrency());}
  , [](){return static_cast<Currency *>(new EEKCurrency());}
  , [](){return static_cast<Currency *>(new ESPCurrency());}
  , [](){return static_cast<Currency *>(new ETCCurrency());}
  , [](){return static_cast<Currency *>(new ETHCurrency());}
  , [](){return static_cast<Currency *>(new EURCurrency());}
  , [](){return static_cast<Currency *>(new FIMCurrency());}
  , [](){return static_cast<Currency *>(new FRFCurrency());}
  , [](){return static_cast<Currency *>(new GBPCurrency());}
  , [](){return static_cast<Currency *>(new GRDCurrency());}
  , [](){return static_cast<Currency *>(new HKDCurrency());}
  , [](){return static_cast<Currency *>(new HUFCurrency());}
  , [](){return static_cast<Currency *>(new IDRCurrency());}
  , [](){return static_cast<Currency *>(new IEPCurrency());}
  , [](){return static_cast<Currency *>(new ILSCurrency());}
  , [](){return static_cast<Currency *>(new INRCurrency());}
  , [](){return static_cast<Currency *>(new IQDCurrency());}
  , [](){return static_cast<Currency *>(new IRRCurrency());}
  , [](){return static_cast<Currency *>(new ISKCurrency());}
  , [](){return static_cast<Currency *>(new ITLCurrency());}
  , [](){return static_cast<Currency *>(new JPYCurrency());}
  , [](){return static_cast<Currency *>(new KRWCurrency());}
  , [](){return static_cast<Currency *>(new KWDCurrency());}
  , [](){return static_cast<Currency *>(new KZTCurrency());}
  , [](){return static_cast<Currency *>(new LTCCurrency());}
  , [](){return static_cast<Currency *>(new LTLCurrency());}
  , [](){return static_cast<Currency *>(new LUFCurrency());}
  , [](){return static_cast<Currency *>(new LVLCurrency());}
  , [](){return static_cast<Currency *>(new MTLCurrency());}
  , [](){return static_cast<Currency *>(new MXNCurrency());}
  , [](){return static_cast<Currency *>(new MYRCurrency());}
  , [](){return static_cast<Currency *>(new NGNCurrency());}
  , [](){return static_cast<Currency *>(new NLGCurrency());}
  , [](){return static_cast<Currency *>(new NOKCurrency());}
  , [](){return static_cast<Currency *>(new NPRCurrency());}
  , [](){return static_cast<Currency *>(new NZDCurrency());}
  , [](){return static_cast<Currency *>(new PEHCurrency());}
  , [](){return static_cast<Currency *>(new PEICurrency());}
  , [](){return static_cast<Currency *>(new PENCurrency());}
  , [](){return static_cast<Currency *>(new PKRCurrency());}
  , [](){return static_cast<Currency *>(new PLNCurrency());}
  , [](){return static_cast<Currency *>(new PTECurrency());}
  , [](){return static_cast<Currency *>(new ROLCurrency());}
  , [](){return static_cast<Currency *>(new RONCurrency());}
  , [](){return static_cast<Currency *>(new RUBCurrency());}
  , [](){return static_cast<Currency *>(new SARCurrency());}
  , [](){return static_cast<Currency *>(new SEKCurrency());}
  , [](){return static_cast<Currency *>(new SGDCurrency());}
  , [](){return static_cast<Currency *>(new SITCurrency());}
  , [](){return static_cast<Currency *>(new SKKCurrency());}
  , [](){return static_cast<Currency *>(new THBCurrency());}
  , [](){return static_cast<Currency *>(new TRLCurrency());}
  , [](){return static_cast<Currency *>(new TRYCurrency());}
  , [](){return static_cast<Currency *>(new TTDCurrency());}
  , [](){return static_cast<Currency *>(new TWDCurrency());}
  , [](){return static_cast<Currency *>(new UAHCurrency());}
  , [](){return static_cast<Currency *>(new USDCurrency());}
  , [](){return static_cast<Currency *>(new VEBCurrency());}
  , [](){return static_cast<Currency *>(new VNDCurrency());}
  , [](){return static_cast<Currency *>(new XRPCurrency());}
  , [](){return static_cast<Currency *>(new ZARCurrency());}
  , [](){return static_cast<Currency *>(new ZECCurrency());}
};

Currency *qlCurrency(int ccy, char **e) {
  try {
    if (ccy < 0 || ccy >= (int)LENGTH(ccys))
      QL_FAIL("Invalid currency index " << ccy);
    return alloc(ccys[ccy]());
  } catch (std::exception& er) {
    return handleException<Currency *>(e, er);
  }
}

void qlFreeCurrency(Currency *currency) {del(currency);}

const char *qlCurrencyName(Currency *currency) {
  std::string name = arg(currency)->name();
  return DUP(name.c_str());
}

char* qlCurrencyCode(Currency* o) {return DUP(arg(o)->code().c_str());}
char* qlCurrencyFormat(Currency* o) {return DUP(arg(o)->format().c_str());}
int qlCurrencyFractionsPerUnit(Currency* o) {return arg(o)->fractionsPerUnit();}
char* qlCurrencyFractionSymbol(Currency* o) {return DUP(arg(o)->fractionSymbol().c_str());}
int qlCurrencyNumericCode(Currency* o) {return arg(o)->numericCode();}
char* qlCurrencySymbol(Currency* o) {return DUP(arg(o)->symbol().c_str());}

class CustomCurrency : public Currency {
public:
  CustomCurrency(const char* name, const char* code, int numericCode,
      const char* symbol, const char* fractionSymbol, int fractionsPerUnit,
      Rounding* rounding, const char* formatString,
      Currency* triangulationCurrency) {
    shared_ptr<Data> data(new Data(name, code, numericCode,
          symbol, fractionSymbol, fractionsPerUnit,
          rounding ? *rounding : Rounding(),
          formatString,
          triangulationCurrency ? *triangulationCurrency : Currency()));
    data_ = data;
  }
};

Currency* qlCreateCurrency(char* name, char* code, int numericCode, char* symbol, char* fractionSymbol, int fractionsPerUnit, Rounding* rounding, char* formatString, Currency* triangulationCurrency, char **e) {
  try {
    return alloc(new CustomCurrency(arg(name), arg(code), numericCode,
          arg(symbol), arg(fractionSymbol), fractionsPerUnit,
          rounding, arg(formatString), triangulationCurrency));
  } catch (std::exception& er) {
    return handleException<Currency*>(e, er);
  }
}

InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq, char **e) {
  try {
    return alloc(new InterestRate(r, *arg(dc), (Compounding) comp, (Frequency) freq));
  } catch (std::exception& er) {
    return handleException<InterestRate *>(e, er);
  }
}

void qlFreeInterestRate(InterestRate *rate) {del(rate);}

// generated code
double qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return (arg(o))->compoundFactor(Date(d1), Date(d2), Date(refStart), Date(refEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlInterestRateCompoundFactor(InterestRate* o, double t, char **e) {
  try {
    return (arg(o))->compoundFactor(t);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return (arg(o))->discountFactor(Date(d1), Date(d2), Date(refStart), Date(refEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlInterestRateDiscountFactor(InterestRate* o, double t, char **e) {
  try {
    return (arg(o))->discountFactor(t);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

InterestRate* qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return ret(new InterestRate(arg(o)->equivalentRate(*arg(resultDC), (Compounding)comp, (Frequency)freq, Date(d1), Date(d2), Date(refStart), Date(refEnd))));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e) {
  try {
    return ret(new InterestRate(arg(o)->equivalentRate((Compounding)comp, (Frequency)freq, t)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return ret(new InterestRate(arg(o)->impliedRate(compound, *arg(resultDC), (Compounding)comp, (Frequency)freq, Date(d1), Date(d2), Date(refStart), Date(refEnd))));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e) {
  try {
    return ret(new InterestRate(arg(o)->impliedRate(compound, *arg(resultDC), (Compounding)comp, (Frequency)freq, t)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

double qlInterestRateRate(InterestRate* o) {return arg(o)->rate();}

void qlFreeConstraint(Constraint *o) {del(o);}

Constraint* qlBoundaryConstraint(double low, double high, char **e) {
  try {
    return alloc(new BoundaryConstraint(low, high));
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
Constraint* qlCompositeConstraint(Constraint* c1, Constraint* c2, char **e) {
  try {
    return alloc(new CompositeConstraint(*arg(c1), *arg(c2)));
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
Constraint* qlNoConstraint(char **e) {
  try {
    return alloc(new NoConstraint());
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
Constraint* qlPositiveConstraint(char **e) {
  try {
    return alloc(new PositiveConstraint());
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
void qlFreeOptimizationMethod(OptimizationMethod *o) {del(o);}

OptimizationMethod* qlLevenbergMarquardt(double epsfcn, double xtol, double gtol, char **e) {
  try {
    return alloc(new LevenbergMarquardt(epsfcn, xtol, gtol));
  } catch (std::exception& er) {
    return handleException<OptimizationMethod*>(e, er);
  }
}
OptimizationMethod* qlSimplex(double lambda, char **e) {
  try {
    return alloc(new Simplex(lambda));
  } catch (std::exception& er) {
    return handleException<OptimizationMethod*>(e, er);
  }
}

void qlFreeEndCriteria(EndCriteria *o) {del(o);}
EndCriteria* qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e) {
  try {
    return alloc(new EndCriteria(maxIterations, maxStationaryStateIterations, rootEpsilon, functionEpsilon, gradientNormEpsilon));
  } catch (std::exception& er) {
    return handleException<EndCriteria*>(e, er);
  }
}

void qlFreeTimeGrid(TimeGrid *o) {del(o);}

TimeGrid* qlTimeGrid1(double end, unsigned steps, char **e) {
  try {
    return alloc(new TimeGrid(end, steps));
  } catch (std::exception& er) {
    return handleException<TimeGrid*>(e, er);
  }
}
TimeGrid* qlTimeGrid2(unsigned x0Len, double* x0, char **e) {
  try {
    return alloc(new TimeGrid(x0, x0+x0Len));
  } catch (std::exception& er) {
    return handleException<TimeGrid*>(e, er);
  }
}
TimeGrid* qlTimeGrid3(unsigned x0Len, double* x0, unsigned steps, char **e) {
  try {
    return alloc(new TimeGrid(x0, x0+x0Len, steps));
  } catch (std::exception& er) {
    return handleException<TimeGrid*>(e, er);
  }
}

void qlFreeRounding(Rounding *o) {del(o);}

Rounding* qlRounding(char **e) {
  try {
    return alloc(new Rounding());
  } catch (std::exception& er) {
    return handleException<Rounding*>(e, er);
  }
}

Rounding* qlRounding1(int precision, int type, int digit, char **e) {
  try {
    return alloc(new Rounding(precision, (Rounding::Type)type, digit));
  } catch (std::exception& er) {
    return handleException<Rounding*>(e, er);
  }
}

double qlRound(Rounding *r, double val) {return (*r)(val);}

QlSimpleQuote *qlSimpleQuote(double value, char **e) {
  try {
    return ret(new QlSimpleQuote(new SimpleQuote(value)));
  } catch (std::exception& er) {
    return handleException<QlSimpleQuote *>(e, er);
  }
}

double qlQuoteValue(QlQuote *quote, char **e) {
  try {
    return (*arg(quote))->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(QlQuote *quote) {del(quote);}

void qlFreeSimpleQuote(QlSimpleQuote *o) {del(o);}
QlQuote* qlSimpleQuoteAsQuote(QlSimpleQuote *o) {return ret(new QlQuote(*arg(o)));}

double qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e) {
  try {
    return (*arg(o))->setValue(value);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlQuote* qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e) {
  try {
    return ret(new QlQuote(alloc(new EurodollarFuturesImpliedStdDevQuote(Handle<Quote>(*arg(forward)), Handle<Quote>(*arg(callPrice)), Handle<Quote>(*arg(putPrice)), strike, guess, accuracy, maxIter))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, int l, int u, char **e) {
  try {
    return ret(new QlQuote(alloc(new ForwardSwapQuote(*arg(swapIndex), Handle<Quote>(*arg(spread)), Period(l, (TimeUnit)u)))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlForwardValueQuote(QlIndex* index, int fixingDate, char **e) {
  try {
    return ret(new QlQuote(alloc(new ForwardValueQuote(*arg(index), Date(fixingDate)))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e) {
  try {
    return ret(new QlQuote(alloc(new FuturesConvAdjustmentQuote(*arg(index), std::string(arg(immCode)), Handle<Quote>(*arg(futuresQuote)), Handle<Quote>(*arg(volatility)), Handle<Quote>(*arg(meanReversion))))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e) {
  try {
    return ret(new QlQuote(alloc(new FuturesConvAdjustmentQuote(*arg(index), Date(futuresDate), Handle<Quote>(*arg(futuresQuote)), Handle<Quote>(*arg(volatility)), Handle<Quote>(*arg(meanReversion))))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e) {
  try {
    return ret(new QlQuote(alloc(new ImpliedStdDevQuote((Option::Type)optionType, Handle<Quote>(*arg(forward)), Handle<Quote>(*arg(price)), strike, guess, accuracy, maxIter))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlLastFixingQuote(QlIndex* index, char **e) {
  try {
    return ret(new QlQuote(alloc(new LastFixingQuote(*arg(index)))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
int qlQuoteIsValid(QlQuote* o, char **e) {
  try {
    return (*arg(o))->isValid();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
