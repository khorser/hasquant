#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <boost/shared_ptr.hpp>

#include <string.h>
//#include <stdio.h>

#include "ql.h"

using namespace QuantLib;
using namespace boost;

void *qlLeg(int len, double *amounts, int *dates, char **e) {
  Leg *leg = 0;
  try {
    leg = new Leg();
    for (int i = 0; i < len; ++i)
      leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], Date(dates[i]))));
    //printf("Allocated leg %p\n", leg);
    //QL_FAIL("Just for fun");
    return leg;
  } catch (std::exception& er) {
    if (leg)
      delete leg;
    *e = strdup(er.what());
    //printf("Duplicated string %p\n", *e);
    return 0;
  }
}

int qlLegStartDate(void *leg) {
  Leg *l = (Leg *)leg;
  Date d = CashFlows::startDate(*l);
  return d.serialNumber();
}

void qlFreeLeg(void *leg) {
  // printf("freeing leg %p\n", leg);
  delete (Leg *)leg;
}

/* vim: set ft=CPP ff=unix ts=8 sts=2 sw=2: */
