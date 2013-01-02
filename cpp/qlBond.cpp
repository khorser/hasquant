#include <ql/cashflows/cashflows.hpp>
#include <ql/time/calendar.hpp>
#include <ql/instruments/bond.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlBond(unsigned settlDays, void *calendar, double faceAmount, int maturityDate, int issueDate, void *cashFlows, char **e)
{
  try {
    return new Bond(settlDays, *(Calendar *)calendar, faceAmount, Date(maturityDate), Date(issueDate), *(Leg *)cashFlows);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return ((Bond *)bond)->maturityDate().serialNumber();
}

int qlBondIssueDate(void *bond) {
  return ((Bond *)bond)->issueDate().serialNumber();
}

void qlFreeBond(void *bond) {
  //printf("freeing bond %p\n", leg);
  delete (Bond *)bond;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
