#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/ibor/all.hpp>

#include "ql.h"

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

QlIborIndex *qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e) {
  try {
    Handle <YieldTermStructure> ts = qlNullableHandle(fwd);
    IborIndex *i = 0;
    if (!strcmp(name, "Euribor"))
      i = new Euribor(*arg(tenor), ts);
    else if (!strcmp(name, "Euribor365"))
      i = new Euribor365(*arg(tenor), ts);
    else if (!strcmp(name, "AUDLibor"))
      i = new AUDLibor(*arg(tenor), ts);
    else if (!strcmp(name, "CADLibor"))
      i = new CADLibor(*arg(tenor), ts);
    else if (!strcmp(name, "Cdor"))
      i = new Cdor(*arg(tenor), ts);
    else if (!strcmp(name, "CHFLibor"))
      i = new CHFLibor(*arg(tenor), ts);
    else if (!strcmp(name, "DKKLibor"))
      i = new DKKLibor(*arg(tenor), ts);
    else if (!strcmp(name, "EURLibor"))
      i = new EURLibor(*arg(tenor), ts);
    else if (!strcmp(name, "GBPLibor"))
      i = new GBPLibor(*arg(tenor), ts);
    else if (!strcmp(name, "Jibar"))
      i = new Jibar(*arg(tenor), ts);
    else if (!strcmp(name, "JPYLibor"))
      i = new JPYLibor(*arg(tenor), ts);
    else if (!strcmp(name, "NZDLibor"))
      i = new NZDLibor(*arg(tenor), ts);
    else if (!strcmp(name, "SEKLibor"))
      i = new SEKLibor(*arg(tenor), ts);
    else if (!strcmp(name, "Tibor"))
      i = new Tibor(*arg(tenor), ts);
    else if (!strcmp(name, "TRLibor"))
      i = new TRLibor(*arg(tenor), ts);
    else if (!strcmp(name, "USDLibor"))
      i = new USDLibor(*arg(tenor), ts);
    else if (!strcmp(name, "Zibor"))
      i = new Zibor(*arg(tenor), ts);
    else
      QL_FAIL("Unknown Ibor " << name);
    return ret(new QlIborIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

QlIborIndex *qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e) {
  try {
    Handle <YieldTermStructure> ts = qlNullableHandle(fwd);
    IborIndex *i = 0;
    if (!strcmp(name, "CADLiborON"))
      i = new CADLiborON(ts);
    else if (!strcmp(name, "Eonia"))
      i = new Eonia(ts);
    else if (!strcmp(name, "Sonia"))
      i = new Sonia(ts);
    else if (!strcmp(name, "GBPLiborON"))
      i = new GBPLiborON(ts);
    else if (!strcmp(name, "USDLiborON"))
      i = new USDLiborON(ts);
    else if (!strcmp(name, "EURLiborON"))
      i = new EURLiborON(ts);
    else
      QL_FAIL("Unknown ON Ibor " << name);
    return ret(new QlIborIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

QlIborIndex *qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e) {
  try {
    Handle <YieldTermStructure> ts = qlNullableHandle(fwd);
    IborIndex *i = 0;
    if (!strcmp(name, "DailyTenorCHFLibor"))
      i = new DailyTenorCHFLibor(settlDays, ts);
    else if (!strcmp(name, "DailyTenorEURLibor"))
      i = new DailyTenorEURLibor(settlDays, ts);
    else if (!strcmp(name, "DailyTenorGBPLibor"))
      i = new DailyTenorGBPLibor(settlDays, ts);
    else if (!strcmp(name, "DailyTenorJPYLibor"))
      i = new DailyTenorJPYLibor(settlDays, ts);
    else if (!strcmp(name, "DailyTenorUSDLibor"))
      i = new DailyTenorUSDLibor(settlDays, ts);
    else
      QL_FAIL("Unknown Daily Tenor Ibor " << name);
    return ret(new QlIborIndex(alloc(i)));
  } catch (std::exception& er) {
    return handleException<QlIborIndex *>(e, er);
  }
}

Index *qlIborAsIndex(QlIborIndex *i) {
  // the pointer can be used only as long as `i' as alive
  return (*i).get();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
