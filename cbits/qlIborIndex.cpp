#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>

#include "qlaux.h"
#include "qlIborIndex.h"

using namespace QuantLib;

QlIborIndex *qlIborIndex(char *name, int l, int u, unsigned settlDays,
  Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
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

static const makeIborIndex iborIndices[] = {
    [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Bbsw(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Bibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Bkbm(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Cdor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new EURLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new AUDLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new CADLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new CHFLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new DKKLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new GBPLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new JPYLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new NZDLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new SEKLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new USDLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new DailyTenorEURLibor(l, ts)); }
  , [](int l, int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new DailyTenorCHFLibor(l, ts)); }
  , [](int l, int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new DailyTenorGBPLibor(l, ts)); }
  , [](int l, int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new DailyTenorJPYLibor(l, ts)); }
  , [](int l, int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new DailyTenorUSDLibor(l, ts)); }
  , [](int  , int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new CADLiborON(ts)); }
  , [](int  , int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new EURLiborON(ts)); }
  , [](int  , int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new GBPLiborON(ts)); }
  , [](int  , int  , const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new USDLiborON(ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Euribor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Euribor365(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Jibar(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Mosprime(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Pribor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Robor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Shibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new THBFIX(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new TRLibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Tibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Wibor(Period(l, (TimeUnit)u), ts)); }
  , [](int l, int u, const YieldTermStructureHandle& ts) { return static_cast<IborIndex *>(new Zibor(Period(l, (TimeUnit)u), ts)); }
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

// should match the order in qlEnumObjects.h
static const makeONIndex onIndices[] = {
    [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new Aonia(ts)); }
  , [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new Eonia(ts)); }
  , [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new Estr(ts)); }
  , [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new FedFunds(ts)); }
  , [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new Nzocr(ts)); }
  , [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new Sofr(ts)); }
  , [](const YieldTermStructureHandle &ts){ return static_cast<OvernightIndex *>(new Sonia(ts)); }
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

QlInterestRateIndex* qlIborIndexAsInterestRateIndex(QlIborIndex *o) { return ret(new QlInterestRateIndex(*arg(o))); }

void qlFreeOvernightIndex(QlOvernightIndex *o) { del(o); }
QlIborIndex* qlOvernightIndexAsIborIndex(QlOvernightIndex *o) { return ret(new QlIborIndex(*arg(o))); }

int qlIborIndexBusinessDayConvention(QlIborIndex* o) {
  return (*arg(o))->businessDayConvention();
}

int qlIborIndexEndOfMonth(QlIborIndex* o) {
  return (*arg(o))->endOfMonth();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
