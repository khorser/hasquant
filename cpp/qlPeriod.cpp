#include <ql/time/period.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlPeriod(int n, int u, char **e) {
  *e = 0;
  try {
    return new Period(n, (TimeUnit) u);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlPeriodFromFrequency(int freq, char **e) {
  *e = 0;
  try {
    return new Period((Frequency) freq);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlPeriodToFrequency(void *period, char **e) {
  *e = 0;
  try {
    return (Frequency)((Period *) period)->frequency() ;
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void  qlFreePeriod(void *period) {
  //printf("freeing period %p\n", leg);
  delete static_cast<Period *>(period);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
