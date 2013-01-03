#include <ql/time/frequency.hpp>

#include "ql.h"

using namespace QuantLib;

int qlFrequencyNoFrequency() {
  return NoFrequency;
}

int qlFrequencyAnnual() {
  return Annual;
}

int qlFrequencySemiannual() {
  return Semiannual;
}

int qlFrequencyEveryFourthMonth() {
  return EveryFourthMonth;
}

int qlFrequencyQuarterly() {
  return Quarterly;
}

int qlFrequencyBimonthly() {
  return Bimonthly;
}

int qlFrequencyMonthly() {
  return Monthly;
}

int qlFrequencyBiweekly() {
  return Biweekly;
}

int qlFrequencyEveryFourthWeek() {
  return EveryFourthWeek;
}

int qlFrequencyWeekly() {
  return Weekly;
}

int qlFrequencyDaily() {
  return Daily;
}

int qlFrequencyOnce() {
  return Once;
}

int qlFrequencyOtherFrequency() {
  return OtherFrequency;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
