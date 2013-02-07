#include <ql/time/period.hpp>

#include "qlaux.h"

using namespace QuantLib;

Period *qlPeriod(int n, int u, char **e) {
  try {
    return alloc(new Period(n, (TimeUnit) u));
  } catch (std::exception& er) {
    return handleException<Period *>(e, er);
  }
}

Period *qlPeriodFromFrequency(int freq, char **e) {
  try {
    return alloc(new Period((Frequency) freq));
  } catch (std::exception& er) {
    return handleException<Period *>(e, er);
  }
}

int qlPeriodToFrequency(Period *period, char **e) {
  try {
    return arg(period)->frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void  qlFreePeriod(Period *period) {
  del(period);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
