#include <ql/index.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/indexes/bmaindex.hpp>
#include <ql/indexes/swap/all.hpp>

#include "qlaux.h"

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

typedef EnumObjectInfo3<SwapIndex, Period&, YieldTermStructureHandle&, YieldTermStructureHandle&> SwapIndexInfo;
static SwapIndexInfo swapIndexInfo [] = {
  {"ChfLiborSwapIsdaFix", &SwapIndexInfo::makeObject<ChfLiborSwapIsdaFix>},
  {"EurLiborSwapIfrFix", &SwapIndexInfo::makeObject<EurLiborSwapIfrFix>},
  {"EurLiborSwapIsdaFixA", &SwapIndexInfo::makeObject<EurLiborSwapIsdaFixA>},
  {"EurLiborSwapIsdaFixB", &SwapIndexInfo::makeObject<EurLiborSwapIsdaFixB>},
  {"EuriborSwapIfrFix", &SwapIndexInfo::makeObject<EuriborSwapIfrFix>},
  {"EuriborSwapIsdaFixA", &SwapIndexInfo::makeObject<EuriborSwapIsdaFixA>},
  {"EuriborSwapIsdaFixB", &SwapIndexInfo::makeObject<EuriborSwapIsdaFixB>},
  {"GbpLiborSwapIsdaFix", &SwapIndexInfo::makeObject<GbpLiborSwapIsdaFix>},
  {"JpyLiborSwapIsdaFixAm", &SwapIndexInfo::makeObject<JpyLiborSwapIsdaFixAm>},
  {"JpyLiborSwapIsdaFixPm", &SwapIndexInfo::makeObject<JpyLiborSwapIsdaFixPm>},
  {"UsdLiborSwapIsdaFixAm", &SwapIndexInfo::makeObject<UsdLiborSwapIsdaFixAm>},
  {"UsdLiborSwapIsdaFixPm", &SwapIndexInfo::makeObject<UsdLiborSwapIsdaFixPm>}
};

QlSwapIndex* qlCreateLiborSwapIndex(char *name, Period* tenor, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e) {
  try {
    SwapIndexInfo *last = LAST(swapIndexInfo);
    SwapIndexInfo *found =
      std::find_if(swapIndexInfo, last, SwapIndexInfo::Cmp(name));
    if (found != last) {
      YieldTermStructureHandle ts1 = qlNullableHandle(h1);
      YieldTermStructureHandle ts2 = qlNullableHandle(h2);
      return ret(new QlSwapIndex(alloc(found->make(*arg(tenor), ts1, ts2))));
    }
    else
      QL_FAIL("Unknown Swap Index " << name);
  } catch (std::exception& er) {
    return handleException<QlSwapIndex*>(e, er);
  }
}

void qlFreeInterestRateIndex(QlInterestRateIndex *o) { del(o); }
QlIndex* qlInterestRateIndexAsIndex(QlInterestRateIndex *o) { return ret(new QlIndex(*arg(o))); }

void qlFreeSwapIndex(QlSwapIndex *o) { del(o); }
QlInterestRateIndex* qlSwapIndexAsInterestRateIndex(QlSwapIndex *o) { return ret(new QlInterestRateIndex(*arg(o))); }

void qlFreeBMAIndex(QlBMAIndex *o) { del(o); }
QlInterestRateIndex* qlBMAIndexAsInterestRateIndex(QlBMAIndex *o) { return ret(new QlInterestRateIndex(*arg(o))); }

void qlFreeOvernightIndexedSwapIndex(QlOvernightIndexedSwapIndex *o) { del(o); }
QlSwapIndex* qlOvernightIndexedSwapIndexAsSwapIndex(QlOvernightIndexedSwapIndex *o) { return ret(new QlSwapIndex(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
