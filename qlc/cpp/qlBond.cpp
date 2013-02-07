#include <ql/instruments/bonds/all.hpp>
#include <ql/cashflows/couponpricer.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlBond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate, Leg *coupons,
  char **e) {
  try {
    return ret(new QlBond(alloc(new Bond(settlDays,
			*arg(calendar),
			qlNullableDate(issueDate),
			*arg(coupons)))));
  } catch (std::exception& er) {
    return handleException<QlBond *>(e, er);
  }
}

QlBond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e) {
  try {
    return ret(new QlBond(alloc(new Bond(settlDays,
			*arg(calendar),
			faceAmount,
			qlNullableDate(maturityDate),
			qlNullableDate(issueDate),
			*arg(cashFlows)))));
  } catch (std::exception& er) {
    return handleException<QlBond *>(e, er);
  }
}

int qlBondMaturityDate(QlBond *bond) {
  return qlNullableDate((*arg(bond))->maturityDate());
}

void qlFreeBond(QlBond *bond) {
  del(bond);
}

void qlFreeFixedRateBond(QlFixedRateBond *bond) {
  del(bond);
}

QlBond *qlFixedRateBondAsBond(QlFixedRateBond *bond) {
  return ret(new QlBond(*arg(bond)));
}

QlFixedRateBond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule,
    unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal,
    char **e) {
  try {
    std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlFixedRateBond(alloc(new FixedRateBond(
		  settlDays,
		  face,
		  *arg(schedule),
		  cpns,
		  *arg(counter),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue),
		  *arg(payCal)))));
  } catch (std::exception& er) {
    return handleException<QlFixedRateBond *>(e, er);
  }
}

QlFixedRateBond *qlFixedRateBond1(unsigned settlDays, Calendar *cpnCal, double face,
  int start, int maturity, Period *tenor, unsigned cLen, double *coupons,
  DayCounter *dayCounter, int accrConv, int paymentConv, double redemption,
  int issue, int stub, int rule, int eom, Calendar *payCal, char **e) {
  try {
    std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlFixedRateBond(alloc(new FixedRateBond(
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
		  *arg(payCal)))));
  } catch (std::exception& er) {
    return handleException<QlFixedRateBond *>(e, er);
  }
}

QlFixedRateBond *qlFixedRateBond2(unsigned settlDays, double face, Schedule *sched,
  unsigned cLen, InterestRate **coupons, int paymentConv, double redemption, int issue,
  Calendar *cal, char **e) {
  try {
    std::vector<InterestRate> cpns;
    for (unsigned i = 0; i < cLen; ++i)
      cpns.push_back(*coupons[i]);

    return ret(new QlFixedRateBond(alloc(new FixedRateBond(
		  settlDays,
		  face,
		  *arg(sched),
		  cpns,
		  (BusinessDayConvention) paymentConv,
		  redemption,
		  qlNullableDate(issue),
		  *arg(cal)))));
  } catch (std::exception& er) {
    return handleException<QlFixedRateBond *>(e, er);
  }
}

QlInstrument *qlBondAsInstrument(QlBond *b) {
  return ret(new QlInstrument(*arg(b)));
}

QlBond *qlZeroCouponBond(int settlDays, Calendar *cal, double face,
  int maturity, int payConv, double redemption, int issue, char **e) {
  try {
    return ret(new QlBond(alloc(new ZeroCouponBond(
		  settlDays,
		  *arg(cal),
		  face,
		  Date(maturity),
		  (BusinessDayConvention) payConv,
		  redemption,
		  qlNullableDate(issue)))));
  } catch (std::exception& er) {
    return handleException<QlBond *>(e, er);
  }
}

void qlBondSetCouponPricer(QlBond *b, QlFloatingRateCouponPricer *p, char **e) {
  try {
    return setCouponPricer((*arg(b))->cashflows(), *p);
  } catch (std::exception& er) {
    (void)handleException<void *>(e, er);
  }
}

QlBond *qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched,
  QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
  unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads,
  unsigned nCaps, double *caps, unsigned nFloors, double *floors,
  int inArrears, double redemption, int issue, char **e) {
  try {
    std::vector<Real> gs(gearings, gearings+nGearings);
    std::vector<Spread> sps(spreads, spreads+nSpreads);
    std::vector<Rate> cs(caps, caps+nCaps);
    std::vector<Rate> fs(floors, floors+nFloors);
    return ret(new QlBond(alloc(new FloatingRateBond(settlDays, face, *arg(sched),
	  *arg(index), *arg(dc), (BusinessDayConvention) payConv, fixDays, gs,
	  sps, cs, fs, inArrears, redemption, qlNullableDate(issue)))));
  } catch (std::exception& er) {
    return handleException<QlBond *>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
