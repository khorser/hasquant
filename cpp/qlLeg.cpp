#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <boost/shared_ptr.hpp>

#include <string.h>
//#include <stdio.h>

#include "ql.h"

using namespace QuantLib;
using namespace boost;

void *qlLeg(int len, double *amounts, int *dates, char **e) {
  *e = 0;
  Leg *leg = 0;
  try {
    leg = new Leg();
    for (int i = 0; i < len; ++i)
      leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], qlDate(dates[i]))));
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

int qlLegStartDate(void *leg, char **e) {
  *e = 0;
  Leg *l = (Leg *)leg;
  try {
    Date d = CashFlows::startDate(*l);
    return d.serialNumber();
  } catch (std::exception& er) {
    *e = strdup(er.what());
    //printf("Duplicated string %p\n", *e);
    return 0;
  }
}

void qlFreeLeg(void *leg) {
  // printf("freeing leg %p\n", leg);
  delete (Leg *)leg;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
