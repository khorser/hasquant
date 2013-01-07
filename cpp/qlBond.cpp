#include <ql/cashflows/cashflows.hpp>
#include <ql/time/calendar.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/instruments/bonds/all.hpp>

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

void *qlFixedRateBond(unsigned settlDays, double face, void *schedule,
    int cLen, double *coupons, void *counter,
    int payConv, double redemption, int issue, void *payCal,
    char **e)
{
  *e = 0;
  try {
    std::vector<Rate> cpns;
    for (int i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);

    return TP("Allocated fixed rate bond",
	      static_cast<Bond *>(
		new FixedRateBond(
		  settlDays,
		  face,
		  *static_cast<Schedule *>(TP("Pschedule", schedule)),
		  cpns,
		  *static_cast<DayCounter *>(TP("Pcounter", counter)),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue),
		  *static_cast<Calendar *>(TP("Pcalendar", payCal)))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
