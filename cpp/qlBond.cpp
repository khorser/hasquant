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
			*static_cast<Calendar *>(TM("Pcalendar", calendar)),
			qlNullableDate(issueDate),
			*static_cast<Leg *>(TM("Pcoupons", coupons))));
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
			*static_cast<Calendar *>(TM("Pcalendar", calendar)),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*static_cast<Leg *>(TM("PcashFlows", cashFlows))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return qlNullableDate(static_cast<Bond *>(TM("Pbond", bond))
      ->maturityDate());
}

int qlBondIssueDate(void *bond) {
  return qlNullableDate(static_cast<Bond *>(TM("Pbond", bond))
      ->issueDate());
}

void qlFreeBond(void *bond) {
  delete static_cast<Bond *>(TM("Pfreeing bond", bond));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
