#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <boost/shared_ptr.hpp>

#include "qlaux.h"

using namespace QuantLib;
using namespace boost;

Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e) {
  Leg *leg = 0;
  try {
    leg = new Leg();
    for (unsigned i = 0; i < len; ++i)
      leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], Date(dates[i]))));
    return alloc(leg);
  } catch (std::exception& er) {
    return handleException(e, er, leg);
  }
}

int qlLegStartDate(Leg *leg, char **e) {
  try {
    Date d = CashFlows::startDate(*arg(leg));
    return d.serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeLeg(Leg *leg) {
  del(leg);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
