#include <ql/time/period.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlPeriod(int n, int u, char **e) {
  try {
    return uncast("Allocated period", new Period(n, (TimeUnit) u));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlPeriodFromFrequency(int freq, char **e) {
  try {
    return uncast("Created period from frequency", new Period((Frequency) freq));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlPeriodToFrequency(void *period, char **e) {
  try {
    return (Frequency)(cast<Period>("Pperiod", period))->frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void  qlFreePeriod(void *period) {
  delete cast<Period>("Pfreeing period", period);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
