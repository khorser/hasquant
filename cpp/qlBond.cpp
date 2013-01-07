#include <ql/cashflows/cashflows.hpp>
#include <ql/time/calendar.hpp>
#include <ql/instruments/bond.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons,
    char **e)
{
  *e = 0;
  try {
    return TP("Allocated bond",
	      new Bond(settlDays,
			*static_cast<Calendar *>(TP("Pcalendar", calendar)),
			qlNullableDate(issueDate),
			*static_cast<Leg *>(TP("Pcoupons", coupons))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlBond2(unsigned settlDays, void *calendar, double faceAmount,
    int maturityDate, int issueDate, void *cashFlows, char **e)
{
  *e = 0;
  try {
    return TP("Allocated bond2",
	      new Bond(settlDays,
			*static_cast<Calendar *>(TP("Pcalendar", calendar)),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*static_cast<Leg *>(TP("PcashFlows", cashFlows))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return qlNullableDate(static_cast<Bond *>(TP("Pbond", bond))
      ->maturityDate());
}

int qlBondIssueDate(void *bond) {
  return qlNullableDate(static_cast<Bond *>(TP("Pbond", bond))
      ->issueDate());
}

void qlFreeBond(void *bond) {
  delete static_cast<Bond *>(TP("Pfreeing bond", bond));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
