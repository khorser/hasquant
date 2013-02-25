#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>

#include "qlaux.h"
#include "qlIborIndex.h"

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

typedef EnumObjectInfo2<IborIndex, Period&, YieldTermStructureHandle&> IborInfo;
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

QlIborIndex *qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e) {
  try {
    const IborInfo *last = LAST(iborInfo);
    const IborInfo *found =
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


typedef EnumObjectInfo1<OvernightIndex, YieldTermStructureHandle&> OnIndexInfo;
static const OnIndexInfo onIndexInfo [] = {
  {"Eonia",	  &OnIndexInfo::makeObject<Eonia>},
  {"Sonia",	  &OnIndexInfo::makeObject<Sonia>},
};

QlOvernightIndex *qlCreateONIndex(char *name, QlYieldTermStructure *fwd, char **e) {
  try {
    const OnIndexInfo *last = LAST(onIndexInfo);
    const OnIndexInfo *found =
      std::find_if(onIndexInfo, last, OnIndexInfo::Cmp(name));
    if (found != last) {
      YieldTermStructureHandle ts = qlNullableHandle(fwd);
      OvernightIndex *i = found->make(ts);
      return ret(new QlOvernightIndex(alloc(i)));
    }
    else
      QL_FAIL("Unknown ON Index " << name);
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
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
