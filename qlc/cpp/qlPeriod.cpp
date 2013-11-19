#include <ql/time/period.hpp>
#include <ql/utilities/dataparsers.hpp>

#include "qlaux.h"
#include "qlPeriod.h"

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

int qlPeriodFromFrequency1(int freq, int *u, char **e) {
  try {
    Period p((Frequency) freq);
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodToFrequency1(int l, int u, char **e) {
  try {
    return Period(l, (TimeUnit)u).frequency();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
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

int qlPeriodParserParse1(char* str, int* u, char **e) {
  try {
    const Period &p = (PeriodParser::parse(std::string(arg(str))));
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlPeriodUnits(Period *p) {
  return p->units();
}

int qlPeriodLength(Period *p) {
  return p->length();
}

Period* qlPeriodAdd(Period *p1, Period *p2, char **e) {
  try {
    return ret(new Period(*p1 + *p2));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}

Period* qlPeriodSubtract(Period *p1, Period *p2, char **e) {
  try {
    return ret(new Period(*p1 - *p2));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}

int qlPeriodAdd1(int n1, int u1, int n2, int u2, int *u, char **e) {
  try {
    Period p = Period(n1, (TimeUnit)u1) + Period(n2, (TimeUnit)u2);
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

Period* qlPeriodDivide(Period *p1, int n, char **e) {
  try {
    return ret(new Period(*p1/n));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}

int qlPeriodDivide1(int n1, int u1, int n, int *u, char **e) {
  try {
    Period p = Period(n1, (TimeUnit)u1)/n;
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

Period* qlPeriodNormalize(Period *p1, char **e) {
  Period *p = 0;
  try {
    p = new Period(*p1);
    p->normalize();
    return ret(p);
  } catch (std::exception& er) {
    return handleException(e, er, p);
  }
}

int qlPeriodNormalize1(int n1, int u1, int *u, char **e) {
  try {
    Period p(n1, (TimeUnit)u1);
    p.normalize();
    *u = p.units();
    return p.length();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int DLLEXPORT qlPeriodsEQ(Period *p1, Period *p2, char **e) {
  try {
    return *p1 == *p2;
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int DLLEXPORT qlPeriodsLT(Period *p1, Period *p2, char **e) {
  try {
    return *p1 < *p2;
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int DLLEXPORT qlPeriodsLT1(int n1, int u1, int n2, int u2, char **e) {
  try {
    Period p1(n1, (TimeUnit)u1);
    Period p2(n2, (TimeUnit)u2);
    return p1 < p2;
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
