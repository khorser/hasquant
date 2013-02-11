#include <ql/index.hpp>
#include <ql/indexes/swapindex.hpp>

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

void qlFreeInterestRateIndex(QlInterestRateIndex *o) { del(o); }
QlIndex* qlInterestRateIndexAsIndex(QlInterestRateIndex *o) { return ret(new QlIndex(*arg(o))); }

void qlFreeSwapIndex(QlSwapIndex *o) { del(o); }
QlInterestRateIndex* qlSwapIndexAsInterestRateIndex(QlSwapIndex *o) { return ret(new QlInterestRateIndex(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
