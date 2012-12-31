#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <boost/shared_ptr.hpp>

//#include <stdio.h>

#include "ql.h"

using namespace QuantLib;
using namespace boost;

void *qlLeg(int len, double *amounts, void **dates) {
    Leg *leg = new Leg();
    Date **d = (Date **)dates;
    for (int i = 0; i < len; ++i)
	leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], *d[i])));
    //printf("Allocated leg %p\n", leg);
    return leg;
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
