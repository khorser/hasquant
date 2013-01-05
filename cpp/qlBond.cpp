#include <ql/cashflows/cashflows.hpp>
#include <ql/time/calendar.hpp>
#include <ql/instruments/bond.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons,
    char **e)
{
  try {
    return new Bond(settlDays, *static_cast<Calendar *>(calendar),
	qlNullableDate(issueDate), *static_cast<Leg *>(coupons));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlBond2(unsigned settlDays, void *calendar, double faceAmount,
    int maturityDate, int issueDate, void *cashFlows, char **e)
{
  try {
    return new Bond(settlDays, *static_cast<Calendar *>(calendar), faceAmount,
	qlNullableDate(maturityDate), qlNullableDate(issueDate),
	*static_cast<Leg *>(cashFlows));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return qlNullableDate((static_cast<Bond *>(bond))->maturityDate());
}

int qlBondIssueDate(void *bond) {
  return qlNullableDate((static_cast<Bond *>(bond))->issueDate());
}

void qlFreeBond(void *bond) {
  //printf("freeing bond %p\n", leg);
  delete static_cast<Bond *>(bond);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
