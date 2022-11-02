#include <ql/index.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/indexes/bmaindex.hpp>
#include <ql/indexes/swap/all.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>

#include "qlaux.h"
#include "qlIndex.h"

using namespace QuantLib;

void qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e) {
  try {
    (*arg(i))->addFixing(Date(date), fix, overwrite);
  } catch (std::exception& er) {
    (void)handleException<void *>(e, er);
  }
}

void qlFreeIndex(QlIndex *i) {
  del(i);
}

typedef Handle<YieldTermStructure> YieldTermStructureHandle;

typedef SwapIndex *(*makeSwapIndex)(const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2);

// must match with the order of qlEnumObjects.h:LiborSwapIndexType
static const makeSwapIndex swapIndices[] = {
    [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new ChfLiborSwapIsdaFix(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new EurLiborSwapIfrFix(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new EurLiborSwapIsdaFixA(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new EurLiborSwapIsdaFixB(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new EuriborSwapIfrFix(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new EuriborSwapIsdaFixA(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new EuriborSwapIsdaFixB(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new GbpLiborSwapIsdaFix(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new JpyLiborSwapIsdaFixAm(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new JpyLiborSwapIsdaFixPm(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new UsdLiborSwapIsdaFixAm(p, h1, h2));}
  , [](const Period &p, const YieldTermStructureHandle &h1, const YieldTermStructureHandle &h2){return static_cast<SwapIndex *>(new UsdLiborSwapIsdaFixPm(p, h1, h2));}
};

QlSwapIndex* qlCreateLiborSwapIndex(int index, int l, int u, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(swapIndices))
      QL_FAIL("Invalid swap index index" << index);
    YieldTermStructureHandle ts1 = qlNullableHandle(h1);
    YieldTermStructureHandle ts2 = qlNullableHandle(h2);
    SwapIndex *i = swapIndices[index](Period(l, (TimeUnit)u), ts1, ts2);
    return ret(new QlSwapIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlSwapIndex*>(e, er);
  }
}

void qlFreeInterestRateIndex(QlInterestRateIndex *o) {del(o);}
QlIndex* qlInterestRateIndexAsIndex(QlInterestRateIndex *o) {return ret(new QlIndex(*arg(o)));}

void qlFreeSwapIndex(QlSwapIndex *o) {del(o);}
QlInterestRateIndex* qlSwapIndexAsInterestRateIndex(QlSwapIndex *o) {return ret(new QlInterestRateIndex(*arg(o)));}

void qlFreeBMAIndex(QlBMAIndex *o) {del(o);}
QlInterestRateIndex* qlBMAIndexAsInterestRateIndex(QlBMAIndex *o) {return ret(new QlInterestRateIndex(*arg(o)));}

void qlFreeOvernightIndexedSwapIndex(QlOvernightIndexedSwapIndex *o) {del(o);}
QlSwapIndex* qlOvernightIndexedSwapIndexAsSwapIndex(QlOvernightIndexedSwapIndex *o) {return ret(new QlSwapIndex(*arg(o)));}

QlBMAIndex* qlBMAIndex(QlYieldTermStructure* h, char **e) {
  try {
    return ret(new QlBMAIndex(alloc(new BMAIndex(qlNullableHandle(arg(h))))));
  } catch (std::exception& er) {
    return handleException<QlBMAIndex*>(e, er);
  }
}

QlOvernightIndexedSwapIndex* qlOvernightIndexedSwapIndex(char* familyName, int l, int u, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, char **e) {
  try {
    return ret(new QlOvernightIndexedSwapIndex(alloc(new OvernightIndexedSwapIndex(std::string(arg(familyName)), Period(l, (TimeUnit)u), settlementDays, *arg(currency), *arg(overnightIndex)))));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndexedSwapIndex*>(e, er);
  }
}
QlSwapIndex* qlSwapIndex1(char* familyName, int l, int u, unsigned settlementDays, Currency* currency, Calendar* calendar, int fl, int fu, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, QlYieldTermStructure* discountingTermStructure, char **e) {
  try {
    return ret(new QlSwapIndex(alloc(new SwapIndex(std::string(arg(familyName)), Period(l, (TimeUnit)u), settlementDays, *arg(currency), *arg(calendar), Period(fl, (TimeUnit)fu), (BusinessDayConvention)fixedLegConvention, *arg(fixedLegDayCounter), *arg(iborIndex), Handle<YieldTermStructure>(*arg(discountingTermStructure))))));
  } catch (std::exception& er) {
    return handleException<QlSwapIndex*>(e, er);
  }
}
QlSwapIndex* qlSwapIndex(char* familyName, int l, int u, unsigned settlementDays, Currency* currency, Calendar* calendar, int fl, int fu, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, char **e) {
  try {
    return ret(new QlSwapIndex(alloc(new SwapIndex(std::string(arg(familyName)), Period(l, (TimeUnit)u), settlementDays, *arg(currency), *arg(calendar), Period(fl, (TimeUnit)fu), (BusinessDayConvention)fixedLegConvention, *arg(fixedLegDayCounter), *arg(iborIndex)))));
  } catch (std::exception& er) {
    return handleException<QlSwapIndex*>(e, er);
  }
}

Schedule* qlBMAIndexFixingSchedule(QlBMAIndex* o, int start, int end, char **e) {
  try {
    return ret(new Schedule((*arg(o))->fixingSchedule(Date(start), Date(end))));
  } catch (std::exception& er) {
    return handleException<Schedule*>(e, er);
  }
}
QlOvernightIndexedSwap* qlOvernightIndexedSwapIndexUnderlyingSwap(QlOvernightIndexedSwapIndex* o, int fixingDate, char **e) {
  try {
    return ret(new QlOvernightIndexedSwap((*arg(o))->underlyingSwap(Date(fixingDate))));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndexedSwap*>(e, er);
  }
}
QlVanillaSwap* qlSwapIndexUnderlyingSwap(QlSwapIndex* o, int fixingDate, char **e) {
  try {
    return ret(new QlVanillaSwap((*arg(o))->underlyingSwap(Date(fixingDate))));
  } catch (std::exception& er) {
    return handleException<QlVanillaSwap*>(e, er);
  }
}

double qlInterestRateIndexForecastFixing(QlInterestRateIndex* o, int fixingDate, char **e) {
  try {
    return (*arg(o))->forecastFixing(Date(fixingDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

Calendar* qlIndexFixingCalendar(QlIndex* o, char **e) {
  try {
    return alloc(new Calendar((*arg(o))->fixingCalendar()));
  } catch (std::exception& er) {
    return handleException<Calendar*>(e, er);
  }
}
Currency* qlInterestRateIndexCurrency(QlInterestRateIndex* o, char **e) {
  try {
    return alloc(new Currency((*arg(o))->currency()));
  } catch (std::exception& er) {
    return handleException<Currency*>(e, er);
  }
}
DayCounter* qlInterestRateIndexDayCounter(QlInterestRateIndex* o, char **e) {
  try {
    return alloc(new DayCounter((*arg(o))->dayCounter()));
  } catch (std::exception& er) {
    return handleException<DayCounter*>(e, er);
  }
}
unsigned qlInterestRateIndexFixingDays(QlInterestRateIndex* o) {
  return (*arg(o))->fixingDays();
}
int qlInterestRateIndexTenor(QlInterestRateIndex* o, int *u, char **e) {
  try {
    const Period& p = (*arg(o))->tenor();
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

const char* qlIndexName(QlIndex *index) {
  std::string name = (*arg(index))->name();
  return DUP(name.c_str());
}

QlIborIndex *qlIborIndex(char *name, int l, int u, unsigned settlDays, Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
  QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlIborIndex(alloc(new IborIndex(name, Period(l, (TimeUnit)u),
	  settlDays, *arg(ccy), *arg(cal), (BusinessDayConvention) conv,
	  eom, *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

void qlFreeIborIndex(QlIborIndex *i) {
  del(i);
}

QlIborIndex *qlLibor(char *name, int l, int u, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd,
    char **e) {
  try {
    return ret(new QlIborIndex(alloc(new Libor(name, Period(l, (TimeUnit)u), settlDays,
	      *arg(ccy), *arg(cal), *arg(dc), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

QlIborIndex *qlDailyTenorLibor(char *name, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc,
    QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlIborIndex(alloc(new DailyTenorLibor(name, settlDays,
	      *arg(ccy), *arg(cal), *arg(dc), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

QlOvernightIndex *qlOvernightIndex(char *name, unsigned settlDays, Currency *ccy,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlOvernightIndex(alloc(new OvernightIndex(name, settlDays,
	      *arg(ccy), *arg(cal), *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndex *>(e, er);
  }
}

typedef Handle<YieldTermStructure> YieldTermStructureHandle;

typedef IborIndex *(*makeIborIndex)(int l, int u, const YieldTermStructureHandle& ts);

// must match with the order of qlEnumObjects:IborIndexType
static const makeIborIndex iborIndices[] = {
    [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Bbsw(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Bibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Bkbm(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Cdor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new EURLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new AUDLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new CADLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new CHFLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new DKKLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new GBPLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new JPYLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new NZDLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new SEKLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new USDLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new DailyTenorEURLibor(l, ts));}
  , [](int l, int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new DailyTenorCHFLibor(l, ts));}
  , [](int l, int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new DailyTenorGBPLibor(l, ts));}
  , [](int l, int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new DailyTenorJPYLibor(l, ts));}
  , [](int l, int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new DailyTenorUSDLibor(l, ts));}
  , [](int  , int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new CADLiborON(ts));}
  , [](int  , int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new EURLiborON(ts));}
  , [](int  , int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new GBPLiborON(ts));}
  , [](int  , int  , const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new USDLiborON(ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Euribor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Euribor365(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Jibar(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Mosprime(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Pribor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Robor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Shibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new THBFIX(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new TRLibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Tibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Wibor(Period(l, (TimeUnit)u), ts));}
  , [](int l, int u, const YieldTermStructureHandle& ts) {return static_cast<IborIndex *>(new Zibor(Period(l, (TimeUnit)u), ts));}
};

QlIborIndex *qlCreateIbor(int index, int l, int u, QlYieldTermStructure *fwd, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(iborIndices))
      QL_FAIL("Invalid IBOR index index" << index);
    YieldTermStructureHandle ts = qlNullableHandle(fwd);
    IborIndex *i = iborIndices[index](l, u, ts);
    return ret(new QlIborIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

typedef OvernightIndex *(*makeONIndex)(const YieldTermStructureHandle &ts);

// should match the order of qlEnumObjects.h:OvernightIborIndexType
static const makeONIndex onIndices[] = {
    [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new Aonia(ts));}
  , [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new Eonia(ts));}
  , [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new Estr(ts));}
  , [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new FedFunds(ts));}
  , [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new Nzocr(ts));}
  , [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new Sofr(ts));}
  , [](const YieldTermStructureHandle &ts){return static_cast<OvernightIndex *>(new Sonia(ts));}
};

QlOvernightIndex *qlCreateONIndex(int index, QlYieldTermStructure *fwd, char **e) {
  try {
    if (index < 0 || index >= (int)LENGTH(onIndices))
      QL_FAIL("Invalid O/N index index" << index);
    YieldTermStructureHandle ts = qlNullableHandle(fwd);
    OvernightIndex *i = onIndices[index](ts);
    return ret(new QlOvernightIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndex *>(e, er);
  }
}

QlInterestRateIndex* qlIborIndexAsInterestRateIndex(QlIborIndex *o) {return ret(new QlInterestRateIndex(*arg(o)));}

void qlFreeOvernightIndex(QlOvernightIndex *o) {del(o);}
QlIborIndex* qlOvernightIndexAsIborIndex(QlOvernightIndex *o) {return ret(new QlIborIndex(*arg(o)));}

int qlIborIndexBusinessDayConvention(QlIborIndex* o) {
  return (*arg(o))->businessDayConvention();
}

int qlIborIndexEndOfMonth(QlIborIndex* o) {
  return (*arg(o))->endOfMonth();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
