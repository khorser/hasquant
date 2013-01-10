#include <ql/instruments/bonds/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons,
    char **e)
{
  try {
    return uncast("Allocated bond",
	      new Bond(settlDays,
			*cast<Calendar>("Pcalendar", calendar),
			qlNullableDate(issueDate),
			*cast<Leg>("Pcoupons", coupons)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlBond1(unsigned settlDays, void *calendar, double faceAmount,
    int maturityDate, int issueDate, void *cashFlows, char **e)
{
  try {
    return uncast("Allocated bond2",
	      new Bond(settlDays,
			*cast<Calendar>("Pcalendar", calendar),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*cast<Leg>("PcashFlows", cashFlows)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlBondMaturityDate(void *bond) {
  return qlNullableDate(cast<Bond>("Pbond", bond)->maturityDate());
}

int qlBondIssueDate(void *bond) {
  return qlNullableDate(cast<Bond>("Pbond", bond)->issueDate());
}

void qlFreeBond(void *bond) {
  delete cast<Bond>("Pfreeing bond", bond);
}

void *qlFixedRateBond(unsigned settlDays, double face, void *schedule,
    unsigned cLen, double *coupons, void *counter,
    int payConv, double redemption, int issue, void *payCal,
    char **e)
{
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);

    return upcast<FixedRateBond, Bond>("Allocated fixed rate bond",
		new FixedRateBond(
		  settlDays,
		  face,
		  *cast<Schedule>("Pschedule", schedule),
		  cpns,
		  *cast<DayCounter>("Pcounter", counter),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue),
		  *cast<Calendar>("Pcalendar", payCal)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlFixedRateBond1(unsigned settlDays, void *cpnCal, double face,
  int start, int maturity, void *tenor, unsigned cLen, double *coupons,
  void *dayCounter, int accrConv, int paymentConv, double redemption,
  int issue, int stub, int rule, int eom, void *payCal, char **e) {
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);

    return upcast<FixedRateBond, Bond>("Allocated fixed rate bond1",
		new FixedRateBond(
		  settlDays,
		  *cast<Calendar>("PcpnCal", cpnCal),
		  face,
		  Date(start),
		  Date(maturity),
		  *cast<Period>("Ptenor", tenor),
		  cpns,
		  *cast<DayCounter>("PdayCounter", dayCounter),
		  (BusinessDayConvention) accrConv,
		  (BusinessDayConvention) paymentConv,
		  redemption,
		  qlNullableDate(issue),
		  qlNullableDate(stub),
		  (DateGeneration::Rule) rule,
		  eom,
		  *cast<Calendar>("PpayCal", payCal)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlFixedRateBond2(unsigned settlDays, double face, void *sched,
  unsigned cLen, void **coupons, int paymentConv, double redemption, int issue,
  void *cal, char **e) {
  try {
    std::vector<InterestRate> cpns;
    InterestRate **rates = reinterpret_cast<InterestRate **>(coupons);
    for (unsigned i = 0; i < cLen; ++i) {
      TPP("Prate", rates[i]);
      cpns.push_back(*rates[i]);
    }
    return upcast<FixedRateBond, Bond>("Allocated fixed rate bond2",
		new FixedRateBond(
		  settlDays,
		  face,
		  *cast<Schedule>("Pschedule", sched),
		  cpns,
		  (BusinessDayConvention) paymentConv,
		  redemption,
		  qlNullableDate(issue),
		  *cast<Calendar>("Pcalendar", cal)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int qlFixedBondFrequency(void *bond) {
  return downcast<Bond, FixedRateBond>("Pbond", bond)->frequency();
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
