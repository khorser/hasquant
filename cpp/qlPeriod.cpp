#include <ql/time/period.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlPeriod(int n, int u, char **e) {
  *e = 0;
  try {
    return TP("Allocated period", new Period(n, (TimeUnit) u));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlPeriodFromFrequency(int freq, char **e) {
  *e = 0;
  try {
    return TP("Created period from frequency", new Period((Frequency) freq));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlPeriodToFrequency(void *period, char **e) {
  *e = 0;
  try {
    return (Frequency)(log_and_cast<Period>("Pperiod", period))->frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void  qlFreePeriod(void *period) {
  delete log_and_cast<Period>("Pfreeing period", period);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
