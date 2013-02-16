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

double qlPeriodDays(Period* x1, char **e) {
  try {
    return days(*arg(x1));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlPeriodLength(Period* o, char **e) {
  try {
    return arg(o)->length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlPeriodMonths(Period* x1, char **e) {
  try {
    return months(*arg(x1));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Period* qlPeriodNormalize(Period* o, char **e) {
  Period *p = 0;
  try {
    p = new Period(*arg(o));
    p->normalize();
    return p;
  } catch (std::exception& er) {
    return handleException(e, er, p);
  }
}
int qlPeriodUnits(Period* o, char **e) {
  try {
    return arg(o)->units();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlPeriodWeeks(Period* x1, char **e) {
  try {
    return weeks(*arg(x1));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlPeriodYears(Period* x1, char **e) {
  try {
    return years(*arg(x1));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Period* qlPeriodParserParse(char* str, char **e) {
  try {
    return ret(new Period(PeriodParser::parse(std::string(arg(str)))));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
