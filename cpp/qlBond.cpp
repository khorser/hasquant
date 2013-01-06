#include <ql/cashflows/cashflows.hpp>
#include <ql/time/calendar.hpp>
#include <ql/instruments/bond.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons,
    char **e)
{
  try {
    return TM("Allocated bond",
	      new Bond(settlDays,
			*static_cast<Calendar *>(TM("calendar", calendar)),
			qlNullableDate(issueDate),
			*static_cast<Leg *>(TM("coupons", coupons))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlBond2(unsigned settlDays, void *calendar, double faceAmount,
    int maturityDate, int issueDate, void *cashFlows, char **e)
{
  try {
    return TM("Allocated bond2",
	      new Bond(settlDays,
			*static_cast<Calendar *>(TM("calendar", calendar)),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*static_cast<Leg *>(TM("cashFlows", cashFlows))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return qlNullableDate(static_cast<Bond *>(TM("bond", bond))->maturityDate());
}

int qlBondIssueDate(void *bond) {
  return qlNullableDate(static_cast<Bond *>(TM("bond", bond))->issueDate());
}

void qlFreeBond(void *bond) {
  delete static_cast<Bond *>(TM("freeing bond", bond));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
