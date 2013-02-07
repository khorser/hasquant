#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlIborIndex *qlIborIndex(char *name, Period *period, unsigned settlDays,
  Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
  QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlIborIndex(alloc(new IborIndex(name, *arg(period),
	  settlDays, *arg(ccy), *arg(cal), (BusinessDayConvention) conv,
	  eom, *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

void qlFreeIborIndex(QlIborIndex *i) {
  del(i);
}

QlIborIndex *qlLibor(char *name, Period *tenor, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd,
    char **e) {
  try {
    return ret(new QlIborIndex(alloc(new Libor(name, *arg(tenor), settlDays,
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

QlIborIndex *qlOvernightIndex(char *name, unsigned settlDays, Currency *ccy,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e) {
  try {
    return ret(new QlIborIndex(alloc(new OvernightIndex(name, settlDays,
	      *arg(ccy), *arg(cal), *arg(dayCount), qlNullableHandle(fwd)))));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

typedef Handle<YieldTermStructure> YieldTermStructureHandle;

typedef EnumObjectInfo2<IborIndex, Period&, YieldTermStructureHandle&> IborInfo;
static IborInfo iborInfo [] = {
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

QlIborIndex *qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e) {
  try {
    IborInfo *last = LAST(iborInfo);
    IborInfo *found =
      std::find_if(iborInfo, last, IborInfo::Cmp(name));
    if (found != last) {
      YieldTermStructureHandle ts = qlNullableHandle(fwd);
      IborIndex *i = found->make(*arg(tenor), ts);
      return ret(new QlIborIndex(alloc(i)));
    }
    else
      QL_FAIL("Unknown Ibor " << name);
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}


typedef EnumObjectInfo1<IborIndex, YieldTermStructureHandle&> OnIborInfo;
static OnIborInfo onIborInfo [] = {
  {"CADLiborON",  &OnIborInfo::makeObject<CADLiborON>},
  {"Eonia",	  &OnIborInfo::makeObject<Eonia>},
  {"Sonia",	  &OnIborInfo::makeObject<Sonia>},
  {"GBPLiborON",  &OnIborInfo::makeObject<GBPLiborON>},
  {"USDLiborON",  &OnIborInfo::makeObject<USDLiborON>},
  {"EURLiborON",  &OnIborInfo::makeObject<EURLiborON>},
};

QlIborIndex *qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e) {
  try {
    OnIborInfo *last = LAST(onIborInfo);
    OnIborInfo *found =
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
static DailyIborInfo dailyIborInfo [] = {
  {"DailyTenorCHFLibor", &DailyIborInfo::makeObject<DailyTenorCHFLibor>},
  {"DailyTenorEURLibor", &DailyIborInfo::makeObject<DailyTenorEURLibor>},
  {"DailyTenorGBPLibor", &DailyIborInfo::makeObject<DailyTenorGBPLibor>},
  {"DailyTenorJPYLibor", &DailyIborInfo::makeObject<DailyTenorJPYLibor>},
  {"DailyTenorUSDLibor", &DailyIborInfo::makeObject<DailyTenorUSDLibor>},
};

QlIborIndex *qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e) {
  try {
    DailyIborInfo *last = LAST(dailyIborInfo);
    DailyIborInfo *found =
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

QlIndex *qlIborAsIndex(QlIborIndex *i) {
  return ret(new QlIndex(*(arg(i))));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
