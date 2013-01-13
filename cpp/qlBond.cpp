#include <ql/instruments/bonds/all.hpp>
#include <ql/cashflows/couponpricer.hpp>

#include "ql.h"

using namespace QuantLib;

Bond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate, Leg *coupons,
  char **e) {
  try {
    return alloc(new Bond(settlDays,
			*arg(calendar),
			qlNullableDate(issueDate),
			*arg(coupons)));
  } catch (std::exception& er) {
    return handleException<Bond *>(e, er);
  }
}

Bond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e) {
  try {
    return alloc(new Bond(settlDays,
			*arg(calendar),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*arg(cashFlows)));
  } catch (std::exception& er) {
    return handleException<Bond *>(e, er);
  }
}

int qlBondMaturityDate(Bond *bond) {
  return qlNullableDate(arg(bond)->maturityDate());
}

int qlBondIssueDate(Bond *bond) {
  return qlNullableDate(arg(bond)->issueDate());
}

void qlFreeBond(Bond *bond) {
  del(bond);
}

Bond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule,
    unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal,
    char **e) {
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);

    return alloc(new FixedRateBond(
		  settlDays,
		  face,
		  *arg(schedule),
		  cpns,
		  *arg(counter),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue),
		  *arg(payCal)));
  } catch (std::exception& er) {
    return handleException<Bond *>(e, er);
  }
}

Bond *qlFixedRateBond1(unsigned settlDays, Calendar *cpnCal, double face,
  int start, int maturity, Period *tenor, unsigned cLen, double *coupons,
  DayCounter *dayCounter, int accrConv, int paymentConv, double redemption,
  int issue, int stub, int rule, int eom, Calendar *payCal, char **e) {
  try {
    std::vector<Rate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(coupons[i]);

    return alloc(new FixedRateBond(
		  settlDays,
		  *arg(cpnCal),
		  face,
		  Date(start),
		  Date(maturity),
		  *arg(tenor),
		  cpns,
		  *arg(dayCounter),
		  (BusinessDayConvention) accrConv,
		  (BusinessDayConvention) paymentConv,
		  redemption,
		  qlNullableDate(issue),
		  qlNullableDate(stub),
		  (DateGeneration::Rule) rule,
		  eom,
		  *arg(payCal)));
  } catch (std::exception& er) {
    return handleException<Bond *>(e, er);
  }
}

Bond *qlFixedRateBond2(unsigned settlDays, double face, Schedule *sched,
  unsigned cLen, InterestRate **coupons, int paymentConv, double redemption, int issue,
  Calendar *cal, char **e) {
  try {
    std::vector<InterestRate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(*coupons[i]);

    return alloc(new FixedRateBond(
		  settlDays,
		  face,
		  *arg(sched),
		  cpns,
		  (BusinessDayConvention) paymentConv,
		  redemption,
		  qlNullableDate(issue),
		  *arg(cal)));
  } catch (std::exception& er) {
    return handleException<Bond *>(e, er);
  }
}

int qlFixedBondFrequency(Bond *bond) {
  return arg(dynamic_cast<FixedRateBond *>(arg(bond)))->frequency();
}

Instrument *qlBondAsInstrument(Bond *bond) {
  return bond;
}

Bond *qlZeroCouponBond(int settlDays, Calendar *cal, double face,
  int maturity, int payConv, double redemption, int issue, char **e) {
  try {
    return alloc(new ZeroCouponBond(
		  settlDays,
		  *arg(cal),
		  face,
		  Date(maturity),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue)));
  } catch (std::exception& er) {
    return handleException<Bond *>(e, er);
  }
}

void qlBondSetCouponPricer(Bond *b, QlFloatingRateCouponPricer *p, char **e) {
  try {
    return setCouponPricer(arg(b)->cashflows(), *p);
  } catch (std::exception& er) {
    (void)handleException<void *>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
