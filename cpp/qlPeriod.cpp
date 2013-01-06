#include <ql/time/period.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlPeriod(int n, int u, char **e) {
  *e = 0;
  try {
    return TM("Allocated period", new Period(n, (TimeUnit) u));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlPeriodFromFrequency(int freq, char **e) {
  *e = 0;
  try {
    return TM("Created period from frequency", new Period((Frequency) freq));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlPeriodToFrequency(void *period, char **e) {
  *e = 0;
  try {
    return (Frequency)(static_cast<Period *>(TM("Period", period)))->frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void  qlFreePeriod(void *period) {
  delete static_cast<Period *>(TM("Freeing period", period));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
