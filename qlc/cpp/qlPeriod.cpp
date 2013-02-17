#include <ql/time/period.hpp>
#include <ql/utilities/dataparsers.hpp>

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

Period* qlPeriodParserParse(char* str, char **e) {
  try {
    return ret(new Period(PeriodParser::parse(std::string(arg(str)))));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
