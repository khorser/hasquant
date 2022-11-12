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
#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/ecb.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/schedule.hpp>
#include <ql/time/period.hpp>
#include <ql/utilities/dataparsers.hpp>
#include <ql/time/daycounters/all.hpp>

#ifdef QLTRACK_ALLOCATIONS
# include <sstream>
#endif

#include "qlaux.h"
#include "qlMisc.h"

#ifdef QLTRACK_ALLOCATIONS
std::ofstream ofs(QLTRACK_ALLOCATIONS);
#endif
using namespace QuantLib;

/* dates are passed as int = serial number of the date, the code assumes that Haskell bindings validate date */

int qlSettingsEvaluationDate() {return Settings::instance().evaluationDate().operator Date().serialNumber();}
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
const char *qlCurrencyName(Currency *currency) {return DUP(arg(currency)->name().c_str());}
char* qlCurrencyCode(Currency* o) {return DUP(arg(o)->code().c_str());}
char* qlCurrencyFormat(Currency* o) {return DUP(arg(o)->format().c_str());}
int qlCurrencyFractionsPerUnit(Currency* o) {return arg(o)->fractionsPerUnit();}
char* qlCurrencyFractionSymbol(Currency* o) {return DUP(arg(o)->fractionSymbol().c_str());}
int qlCurrencyNumericCode(Currency* o) {return arg(o)->numericCode();}
char* qlCurrencySymbol(Currency* o) {return DUP(arg(o)->symbol().c_str());}
void qlFreeInterestRate(InterestRate *rate) {del(rate);}

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

EndCriteria* qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e) {
  try {
    return alloc(new EndCriteria(maxIterations, maxStationaryStateIterations, rootEpsilon, functionEpsilon, gradientNormEpsilon));
  } catch (std::exception& er) {
    return handleException<EndCriteria*>(e, er);
  }
}

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
unsigned qlTimeGridSize(TimeGrid* t) {return arg(t)->size();}
double qlTimeGridAt(TimeGrid* t, unsigned i, char **e) {
  try {
    return arg(t)->at(i);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

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

void qlFreeEndCriteria(EndCriteria *o) {del(o);}
double qlInterestRateRate(InterestRate* o) {return arg(o)->rate();}
void qlFreeConstraint(Constraint *o) {del(o);}
void qlFreeOptimizationMethod(OptimizationMethod *o) {del(o);}
void qlFreeTimeGrid(TimeGrid *o) {del(o);}
void qlFreeRounding(Rounding *o) {del(o);}
double qlRound(Rounding *r, double val) {return (*r)(val);}
void qlFreeQuote(QlQuote *quote) {del(quote);}
void qlFreeSimpleQuote(QlSimpleQuote *o) {del(o);}
QlQuote* qlSimpleQuoteAsQuote(QlSimpleQuote *o) {return ret(new QlQuote(*arg(o)));}

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
char* qlIMMNextCode(int d, int mainCycle) {return DUP(IMM::nextCode(Date(d), mainCycle).c_str());}
int qlIMMNextDate(int d, int mainCycle) {return IMM::nextDate(Date(d), mainCycle).serialNumber();}

char* qlIMMCode(int immDate, char **e) {
  try {
    return DUP((IMM::code(Date(immDate))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlIMMDate(char* immCode, int referenceDate, char **e) {
  try {
    return (IMM::date(std::string(immCode), Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return DUP(IMM::nextCode(std::string(arg(immCode)), mainCycle, Date(referenceDate)).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}

int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e) {
  try {
    return (IMM::nextDate(std::string(arg(immCode)), mainCycle, Date(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlAddPeriod(int d, int n, int u, char **e) {
  try {
    return (Date(d) + Period(n, (TimeUnit)u)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlECBAddDate(int d, char **e) {
  try {
    ECB::addDate(Date(d));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
char* qlECBCode(int ecbDate, char **e) {
  try {
    return DUP((ECB::code(Date(ecbDate))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlECBDate1(char* ecbCode, int referenceDate, char **e) {
  try {
    return (ECB::date(std::string(arg(ecbCode)), qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBDate(int m, int y, char **e) {
  try {
    return (ECB::date((Month)m, y)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBIsECBcode(char* in, char **e) {
  try {
    return ECB::isECBcode(arg(in));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBIsECBdate(int d, char **e) {
  try {
    return ECB::isECBdate(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
void qlECBKnownDates(unsigned *count, int **ds, char **e) {
  try {
    const std::set<Date> &dates = ECB::knownDates();
    *count = dates.size();
    *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds,
        std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
char* qlECBNextCode1(char* ecbCode, char **e) {
  try {
    return DUP((ECB::nextCode(std::string(arg(ecbCode)))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
char* qlECBNextCode(int d, char **e) {
  try {
    return DUP((ECB::nextCode(qlNullableDate(d))).c_str());
  } catch (std::exception& er) {
    return handleException<char*>(e, er);
  }
}
int qlECBNextDate1(char* ecbCode, int referenceDate, char **e) {
  try {
    return (ECB::nextDate(std::string(arg(ecbCode)), qlNullableDate(referenceDate))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlECBNextDate(int d, char **e) {
  try {
    return (ECB::nextDate(qlNullableDate(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
void qlECBNextDates1(char* ecbCode, int referenceDate, unsigned *count, int **ds, char **e) {
  try {
    const std::vector<Date> &dates = ECB::nextDates(ecbCode, qlNullableDate(referenceDate));
    *count = dates.size();
    *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds,
        std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}
void qlECBNextDates(int d, unsigned *count, int **ds, char **e) {
  try {
    const std::vector<Date> &dates = ECB::nextDates(qlNullableDate(d));
    *count = dates.size();
    *ds = qlAllocateInts(*count);
    std::transform(dates.begin(), dates.end(), *ds,
        std::mem_fn(&Date::serialNumber));
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}
void qlECBRemoveDate(int d, char **e) {
  try {
    ECB::removeDate(Date(d));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

const char *qlCalendarName(Calendar *calendar) {std::string name = arg(calendar)->name(); return DUP(name.c_str());}
typedef Calendar *(*makeCalendar)(int market);
// must match with the order of qlEnumObjects.h:CalendarCountry
static const makeCalendar calendars[] = {
  [](int){return static_cast<Calendar *>(new Argentina());}
  , [](int){return static_cast<Calendar *>(new Australia());}
  , [](int market){return static_cast<Calendar *>(new Austria((Austria::Market) market));}
  , [](int){return static_cast<Calendar *>(new Botswana());}
  , [](int market){return static_cast<Calendar *>(new Brazil((Brazil::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Canada((Canada::Market) market));}
  , [](int market){return static_cast<Calendar *>(new China((China::Market) market));}
  , [](int){return static_cast<Calendar *>(new CzechRepublic());}
  , [](int){return static_cast<Calendar *>(new Denmark());}
  , [](int){return static_cast<Calendar *>(new Finland());}
  , [](int market){return static_cast<Calendar *>(new France((France::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Germany((Germany::Market) market));}
  , [](int){return static_cast<Calendar *>(new HongKong());}
  , [](int){return static_cast<Calendar *>(new Hungary());}
  , [](int){return static_cast<Calendar *>(new Iceland());}
  , [](int){return static_cast<Calendar *>(new India());}
  , [](int market){return static_cast<Calendar *>(new Indonesia((Indonesia::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Israel((Israel::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Italy((Italy::Market) market));}
  , [](int){return static_cast<Calendar *>(new Japan());}
  , [](int){return static_cast<Calendar *>(new Mexico());}
  , [](int){return static_cast<Calendar *>(new NewZealand());}
  , [](int){return static_cast<Calendar *>(new Norway());}
  , [](int){return static_cast<Calendar *>(new NullCalendar());}
  , [](int){return static_cast<Calendar *>(new Poland());}
  , [](int market){return static_cast<Calendar *>(new Romania((Romania::Market) market));}
  , [](int market){return static_cast<Calendar *>(new Russia((Russia::Market) market));}
  , [](int){return static_cast<Calendar *>(new SaudiArabia());}
  , [](int){return static_cast<Calendar *>(new Singapore());}
  , [](int){return static_cast<Calendar *>(new Slovakia());}
  , [](int){return static_cast<Calendar *>(new SouthAfrica());}
  , [](int market){return static_cast<Calendar *>(new SouthKorea((SouthKorea::Market) market));}
  , [](int){return static_cast<Calendar *>(new Sweden());}
  , [](int){return static_cast<Calendar *>(new Switzerland());}
  , [](int){return static_cast<Calendar *>(new Taiwan());}
  , [](int){return static_cast<Calendar *>(new TARGET());}
  , [](int){return static_cast<Calendar *>(new Thailand());}
  , [](int){return static_cast<Calendar *>(new Turkey());}
  , [](int){return static_cast<Calendar *>(new Ukraine());}
  , [](int market){return static_cast<Calendar *>(new UnitedKingdom((UnitedKingdom::Market) market));}
  , [](int market){return static_cast<Calendar *>(new UnitedStates((UnitedStates::Market) market));}
  , [](int){return static_cast<Calendar *>(new WeekendsOnly());}
};

Calendar *qlCalendar(int country, int market, char **e) {
  try {
    if (country < 0 || country >= (int)LENGTH(calendars))
      QL_FAIL("Invalid country index " << country);
    return alloc(calendars[country](market));
  } catch (std::exception& er) {
    return handleException<Calendar *>(e, er);
  }
}

int qlCalendarAdjust(Calendar *c, int date, int conv) {
  return arg(c)->adjust(Date(date), (BusinessDayConvention) conv)
      .serialNumber();
}

int qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv,
  int eom) {
  return arg(c)->advance(Date(date), n, (TimeUnit) unit,
      (BusinessDayConvention) conv, eom).serialNumber();
}

// generated code
void qlCalendarAddHoliday(Calendar* o, int x0, char **e) {
  try {
    arg(o)->addHoliday(Date(x0));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

int qlCalendarAdvance1(Calendar* o, int date, int n, int u, int convention, int endOfMonth, char **e) {
  try {
    return (arg(o)->advance(Date(date), Period(n, (TimeUnit)u), (BusinessDayConvention)convention, endOfMonth)).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e) {
  try {
    return arg(o)->businessDaysBetween(Date(from), Date(to), includeFirst, includeLast);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarEndOfMonth(Calendar* o, int d, char **e) {
  try {
    return (arg(o)->endOfMonth(Date(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsBusinessDay(Calendar* o, int d, char **e) {
  try {
    return arg(o)->isBusinessDay(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsEndOfMonth(Calendar* o, int d, char **e) {
  try {
    return arg(o)->isEndOfMonth(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsHoliday(Calendar* o, int d, char **e) {
  try {
    return arg(o)->isHoliday(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlCalendarIsWeekend(Calendar* o, int w, char **e) {
  try {
    return arg(o)->isWeekend((Weekday) w);
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlCalendarRemoveHoliday(Calendar* o, int x0, char **e) {
  try {
    arg(o)->removeHoliday(Date(x0));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

Calendar* qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e) {
  BespokeCalendar *cal = 0;
  try {
    cal = new BespokeCalendar(std::string(name));
    for (unsigned i = 0; i < len; i++)
      cal->addWeekend((Weekday)weekends[i]);
    return ret(cal);
  } catch (std::exception& er) {
    return handleException(e, er, cal);
  }
}

Calendar* qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e) {
  try {
    return alloc(new JointCalendar(*arg(x_1), *arg(x0), *arg(x1), *arg(x2), (JointCalendarRule)x3));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

Calendar* qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e) {
  try {
    return alloc(new JointCalendar(*arg(x_1), *arg(x0), *arg(x1), (JointCalendarRule)x2));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

Calendar* qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e) {
  try {
    return alloc(new JointCalendar(*arg(x_1), *arg(x0), (JointCalendarRule)x1));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}

void qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, int **days, char **e) {
  try {
    const std::vector<Date> dates = arg(calendar)->holidayList(Date(from), Date(to), includeWeekEnds);
    *len = dates.size();
    *days = qlAllocateInts(*len);
    for (size_t i = 0; i < dates.size(); ++i)
      (*days)[i] = dates[i].serialNumber();
  } catch (std::exception& er) {
    (void)handleException<int*>(e, er);
  }
}

Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv, char **e) {
  try {
    std::vector<Date> d; d.reserve(len);
    for (unsigned i = 0; i < len; ++i)
      d.push_back(Date(dates[i]));
    return alloc(new Schedule(d, *arg(cal), (BusinessDayConvention) conv));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

Schedule *qlSchedule(int eff, int term, int l, int u, Calendar *cal, int conv, int termConv, int rule, int eom, int first, int nextToLast, char **e) {
  try {
    return alloc(new Schedule(qlNullableDate(eff), Date(term), Period(l, (TimeUnit)u), *arg(cal),
			    (BusinessDayConvention) conv, (BusinessDayConvention) termConv, (DateGeneration::Rule) rule,
			    eom, qlNullableDate(first), qlNullableDate(nextToLast)));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

Schedule *qlScheduleUntil(Schedule *sched, int date, char **e) {
  try {
    return alloc(new Schedule(arg(sched)->until(Date(date))));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

void qlScheduleDates(Schedule *sched, unsigned *count, int **days) {
  const std::vector<Date> &dates = arg(sched)->dates();
  *count = dates.size();
  *days = qlAllocateInts(*count);
  for (size_t i = 0; i < dates.size(); ++i)
    (*days)[i] = dates[i].serialNumber();
}

int qlPeriodFromFrequency1(int freq, int *u, char **e) {
  try {
    Period p((Frequency) freq);
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodToFrequency1(int l, int u, char **e) {
  try {
    return Period(l, (TimeUnit)u).frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodParserParse1(char* str, int* u, char **e) {
  try {
    const Period &p = (PeriodParser::parse(std::string(arg(str))));
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodAdd1(int n1, int u1, int n2, int u2, int *u, char **e) {
  try {
    Period p = Period(n1, (TimeUnit)u1) + Period(n2, (TimeUnit)u2);
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodDivide1(int n1, int u1, int n, int *u, char **e) {
  try {
    Period p = Period(n1, (TimeUnit)u1)/n;
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodNormalize1(int n1, int u1, int *u, char **e) {
  try {
    Period p(n1, (TimeUnit)u1);
    p.normalize();
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodsLT1(int n1, int u1, int n2, int u2, char **e) {
  try {
    Period p1(n1, (TimeUnit)u1);
    Period p2(n2, (TimeUnit)u2);
    return p1 < p2;
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

typedef DayCounter *(*makeDayCounter)(int convention);

// must match with the order of qlEnumObjects.h:DayCounterType
static const makeDayCounter dayCounters[] = {
  [](int) {return static_cast<DayCounter *>(new Actual360());}
  , [](int) {return static_cast<DayCounter *>(new Actual364());}
  , [](int conv) {return static_cast<DayCounter *>(new Actual365Fixed((Actual365Fixed::Convention) conv));}
  , [](int conv) {return static_cast<DayCounter *>(new ActualActual((ActualActual::Convention) conv));}
  , [](int) {return static_cast<DayCounter *>(new OneDayCounter());}
  , [](int) {return static_cast<DayCounter *>(new SimpleDayCounter());}
  , [](int conv) {return static_cast<DayCounter *>(new Thirty360((Thirty360::Convention) conv));}
  , [](int) {return static_cast<DayCounter *>(new Thirty365());}
};

DayCounter *qlDayCounter(int type, int convention, char **e) {
  try {
    if (type < 0 || type >= (int)LENGTH(dayCounters))
      QL_FAIL("Invalid DayCounter type " << type);
    return alloc(dayCounters[type](convention));
  } catch (std::exception& er) {
    return handleException<DayCounter *>(e, er);
  }
}

DayCounter *qlDayCounterBusiness252(Calendar *cal, char **e) {
  try {
    return alloc(new Business252(*arg(cal)));
  } catch (std::exception& er) {
    return handleException<DayCounter *>(e, er);
  }
}

void qlFreeCalendar(Calendar *calendar) {del(calendar);}
void qlFreeSchedule(Schedule *s) {del(s);}
void  qlFreeDayCounter(DayCounter *counter) {del(counter);}
const char *qlDayCounterName(DayCounter *counter) {std::string name = arg(counter)->name(); return DUP(name.c_str());}
int qlDayCounterDayCount(DayCounter* o, int x0, int x1) {return arg(o)->dayCount(Date(x0), Date(x1));}

double qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e) {
  try {
    return arg(o)->yearFraction(Date(x0), Date(x1), qlNullableDate(refPeriodStart), qlNullableDate(refPeriodEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
