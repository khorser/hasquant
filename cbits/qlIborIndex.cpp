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

typedef EnumObjectInfo2<IborIndex, const Period&, YieldTermStructureHandle&> IborInfo;
static const IborInfo iborInfo [] = {
  {"Euribor",	  &IborInfo::makeObject<Euribor>},
  {"Euribor365",  &IborInfo::makeObject<Euribor365>},
  {"AUDLibor",	  &IborInfo::makeObject<AUDLibor>},
  {"CADLibor",	  &IborInfo::makeObject<CADLibor>},
  {"Cdor",	  &IborInfo::makeObject<Cdor>},
  {"CHFLibor",	  &IborInfo::makeObject<CHFLibor>},
  {"DKKLibor",	  &IborInfo::makeObject<DKKLibor>},
  {"EURLibor",	  &IborInfo::makeObject<EURLibor>},
  {"GBPLibor",	  &IborInfo::makeObject<GBPLibor>},
  {"Jibar",	  &IborInfo::makeObject<Jibar>},
  {"JPYLibor",	  &IborInfo::makeObject<JPYLibor>},
  {"NZDLibor",	  &IborInfo::makeObject<NZDLibor>},
  {"SEKLibor",	  &IborInfo::makeObject<SEKLibor>},
  {"Tibor",	  &IborInfo::makeObject<Tibor>},
  {"TRLibor",	  &IborInfo::makeObject<TRLibor>},
  {"USDLibor",	  &IborInfo::makeObject<USDLibor>},
  {"Zibor",	  &IborInfo::makeObject<Zibor>}
};

QlIborIndex *qlCreateIbor(char *name, int l, int u,
    QlYieldTermStructure *fwd, char **e) {
  try {
    const IborInfo *last = LAST(iborInfo);
    const IborInfo *found =
      std::find_if(iborInfo, last, IborInfo::Cmp(name));
    if (found != last) {
      YieldTermStructureHandle ts = qlNullableHandle(fwd);
      IborIndex *i = found->make(Period(l, (TimeUnit)u), ts);
      return ret(new QlIborIndex(alloc(i)));
    }
    else
      QL_FAIL("Unknown Ibor " << name);
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
      QL_FAIL("Invalid ON index index" << index);
    YieldTermStructureHandle ts = qlNullableHandle(fwd);
    OvernightIndex *i = onIndices[index](ts);
    return ret(new QlOvernightIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndex *>(e, er);
  }
}

typedef EnumObjectInfo1<IborIndex, YieldTermStructureHandle&> OnIborInfo;
static const OnIborInfo onIborInfo [] = {
  {"CADLiborON",  &OnIborInfo::makeObject<CADLiborON>},
  {"GBPLiborON",  &OnIborInfo::makeObject<GBPLiborON>},
  {"USDLiborON",  &OnIborInfo::makeObject<USDLiborON>},
  {"EURLiborON",  &OnIborInfo::makeObject<EURLiborON>},
};

QlIborIndex *qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e) {
  try {
    const OnIborInfo *last = LAST(onIborInfo);
    const OnIborInfo *found =
      std::find_if(onIborInfo, last, OnIborInfo::Cmp(name));
    if (found != last) {
      YieldTermStructureHandle ts = qlNullableHandle(fwd);
      IborIndex *i = found->make(ts);
      return ret(new QlIborIndex(alloc(i)));
    }
    else
      QL_FAIL("Unknown ON Ibor " << name);
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

typedef EnumObjectInfo2<IborIndex, unsigned, YieldTermStructureHandle&> DailyIborInfo;
static const DailyIborInfo dailyIborInfo [] = {
  {"DailyTenorCHFLibor", &DailyIborInfo::makeObject<DailyTenorCHFLibor>},
  {"DailyTenorEURLibor", &DailyIborInfo::makeObject<DailyTenorEURLibor>},
  {"DailyTenorGBPLibor", &DailyIborInfo::makeObject<DailyTenorGBPLibor>},
  {"DailyTenorJPYLibor", &DailyIborInfo::makeObject<DailyTenorJPYLibor>},
  {"DailyTenorUSDLibor", &DailyIborInfo::makeObject<DailyTenorUSDLibor>},
};

QlIborIndex *qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e) {
  try {
    const DailyIborInfo *last = LAST(dailyIborInfo);
    const DailyIborInfo *found =
      std::find_if(dailyIborInfo, last, DailyIborInfo::Cmp(name));
    if (found != last) {
      YieldTermStructureHandle ts = qlNullableHandle(fwd);
      IborIndex *i = found->make(settlDays, ts);
      return ret(new QlIborIndex(alloc(i)));
    }
    else
      QL_FAIL("Unknown Daily Tenor Ibor " << name);
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
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
