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

    return log_and_upcast<FixedRateBond, Bond>("Allocated fixed rate bond",
		new FixedRateBond(
		  settlDays,
		  face,
		  *log_and_cast<Schedule>("Pschedule", schedule),
		  cpns,
		  *log_and_cast<DayCounter>("Pcounter", counter),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue),
		  *log_and_cast<Calendar>("Pcalendar", payCal)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlFixedRateBond1(unsigned settlDays, void *cpnCal, double face,
  int start, int maturity, void *tenor, int cLen, double *coupons,
  void *dayCounter, int accrConv, int paymentConv, double redemption,
  int issue, int stub, int rule, int eom, void *payCal, char **e) {
  *e = 0;
  try {
    std::vector<Rate> cpns;
    for (int i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);

    return log_and_upcast<FixedRateBond, Bond>("Allocated fixed rate bond1",
		new FixedRateBond(
		  settlDays,
		  *log_and_cast<Calendar>("PcpnCal", cpnCal),
		  face,
		  Date(start),
		  Date(maturity),
		  *log_and_cast<Period>("Ptenor", tenor),
		  cpns,
		  *log_and_cast<DayCounter>("PdayCounter", dayCounter),
		  (BusinessDayConvention) accrConv,
		  (BusinessDayConvention) paymentConv,
		  redemption,
		  qlNullableDate(issue),
		  qlNullableDate(stub),
		  (DateGeneration::Rule) rule,
		  eom,
		  *log_and_cast<Calendar>("PpayCal", payCal)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlFixedBondFrequency(void *bond) {
  return log_and_downcast<Bond, FixedRateBond>("Pbond", bond)->frequency();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
