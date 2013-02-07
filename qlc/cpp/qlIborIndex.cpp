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

IborInfo iborInfo [] = {
  {"Euribor", &makeObject2<IborIndex, Euribor, Period&, YieldTermStructureHandle&>},
  {"Euribor365", &makeObject2<IborIndex, Euribor365, Period&, YieldTermStructureHandle&>},
  {"AUDLibor", &makeObject2<IborIndex, AUDLibor, Period&, YieldTermStructureHandle&>},
  {"CADLibor", &makeObject2<IborIndex, CADLibor, Period&, YieldTermStructureHandle&>},
  {"Cdor", &makeObject2<IborIndex, Cdor, Period&, YieldTermStructureHandle&>},
  {"CHFLibor", &makeObject2<IborIndex, CHFLibor, Period&, YieldTermStructureHandle&>},
  {"DKKLibor", &makeObject2<IborIndex, DKKLibor, Period&, YieldTermStructureHandle&>},
  {"EURLibor", &makeObject2<IborIndex, EURLibor, Period&, YieldTermStructureHandle&>},
  {"GBPLibor", &makeObject2<IborIndex, GBPLibor, Period&, YieldTermStructureHandle&>},
  {"Jibar", &makeObject2<IborIndex, Jibar, Period&, YieldTermStructureHandle&>},
  {"JPYLibor", &makeObject2<IborIndex, JPYLibor, Period&, YieldTermStructureHandle&>},
  {"NZDLibor", &makeObject2<IborIndex, NZDLibor, Period&, YieldTermStructureHandle&>},
  {"SEKLibor", &makeObject2<IborIndex, SEKLibor, Period&, YieldTermStructureHandle&>},
  {"Tibor", &makeObject2<IborIndex, Tibor, Period&, YieldTermStructureHandle&>},
  {"TRLibor", &makeObject2<IborIndex, TRLibor, Period&, YieldTermStructureHandle&>},
  {"USDLibor", &makeObject2<IborIndex, USDLibor, Period&, YieldTermStructureHandle&>},
  {"Zibor", &makeObject2<IborIndex, Zibor, Period&, YieldTermStructureHandle&>}
};

QlIborIndex *qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e) {
  try {
    IborInfo *last = LAST(iborInfo);
    IborInfo *found =
      std::find_if(iborInfo, last, IborInfo::Comp(name));
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

OnIborInfo onIborInfo [] = {
  {"CADLiborON", &makeObject1<IborIndex, CADLiborON, YieldTermStructureHandle&>},
  {"Eonia", &makeObject1<IborIndex, Eonia, YieldTermStructureHandle&>},
  {"Sonia", &makeObject1<IborIndex, Sonia, YieldTermStructureHandle&>},
  {"GBPLiborON", &makeObject1<IborIndex, GBPLiborON, YieldTermStructureHandle&>},
  {"USDLiborON", &makeObject1<IborIndex, USDLiborON, YieldTermStructureHandle&>},
  {"EURLiborON", &makeObject1<IborIndex, EURLiborON, YieldTermStructureHandle&>},
};

QlIborIndex *qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e) {
  try {
    OnIborInfo *last = LAST(onIborInfo);
    OnIborInfo *found =
      std::find_if(onIborInfo, last, OnIborInfo::Comp(name));
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
DailyIborInfo dailyIborInfo [] = {
  {"DailyTenorCHFLibor", &makeObject2<IborIndex, 
    DailyTenorCHFLibor, unsigned, YieldTermStructureHandle&>},
  {"DailyTenorEURLibor", &makeObject2<IborIndex, 
    DailyTenorEURLibor, unsigned, YieldTermStructureHandle&>},
  {"DailyTenorGBPLibor", &makeObject2<IborIndex, 
    DailyTenorGBPLibor, unsigned, YieldTermStructureHandle&>},
  {"DailyTenorJPYLibor", &makeObject2<IborIndex, 
    DailyTenorJPYLibor, unsigned, YieldTermStructureHandle&>},
  {"DailyTenorUSDLibor", &makeObject2<IborIndex, 
    DailyTenorUSDLibor, unsigned, YieldTermStructureHandle&>},
};

QlIborIndex *qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e) {
  try {
    DailyIborInfo *last = LAST(dailyIborInfo);
    DailyIborInfo *found =
      std::find_if(dailyIborInfo, last, DailyIborInfo::Comp(name));
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
