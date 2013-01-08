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
			*log_and_cast<Calendar>("Pcalendar", calendar),
			qlNullableDate(issueDate),
			*log_and_cast<Leg>("Pcoupons", coupons)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlBond1(unsigned settlDays, void *calendar, double faceAmount,
    int maturityDate, int issueDate, void *cashFlows, char **e)
{
  *e = 0;
  try {
    return TP("Allocated bond2",
	      new Bond(settlDays,
			*log_and_cast<Calendar>("Pcalendar", calendar),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*log_and_cast<Leg>("PcashFlows", cashFlows)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return qlNullableDate(log_and_cast<Bond>("Pbond", bond)->maturityDate());
}

int qlBondIssueDate(void *bond) {
  return qlNullableDate(log_and_cast<Bond>("Pbond", bond)->issueDate());
}

void qlFreeBond(void *bond) {
  delete log_and_cast<Bond>("Pfreeing bond", bond);
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
		  *log_and_cast<Schedule>("Pschedule", schedule),
		  cpns,
		  *log_and_cast<DayCounter>("Pcounter", counter),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue),
		  *log_and_cast<Calendar>("Pcalendar", payCal))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlFixedBondFrequency(void *bond) {
  return log_and_downcast<Bond, FixedRateBond>("Pbond", bond)->frequency();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
