#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <boost/shared_ptr.hpp>

#include "ql.h"

using namespace QuantLib;
using namespace boost;

void *qlLeg(int len, double *amounts, int *dates, char **e) {
  *e = 0;
  Leg *leg = 0;
  try {
    leg = new Leg();
    for (int i = 0; i < len; ++i)
      leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], Date(dates[i]))));
    //printf("Allocated leg %p\n", leg);
    //QL_FAIL("Just for fun");
    return leg;
  } catch (std::exception& er) {
    return handleException(e, er, leg);
  }
}

int qlLegStartDate(void *leg, char **e) {
  *e = 0;
  Leg *l = (Leg *)leg;
  try {
    Date d = CashFlows::startDate(*l);
    return d.serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeLeg(void *leg) {
  // printf("freeing leg %p\n", leg);
  delete (Leg *)leg;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
