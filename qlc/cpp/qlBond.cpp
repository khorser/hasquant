#include <ql/instruments/bonds/all.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/pricingengines/bond/bondfunctions.hpp>
#include <ql/experimental/callablebonds/callablebond.hpp>
#include <ql/experimental/convertiblebonds/convertiblebond.hpp>

#include "qlaux.h"
#include "qlBond.h"

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

double* qlBondNotionals(QlBond* o, unsigned *len, char **e) {
  try {
    const std::vector<double> notionals = (*arg(o))->notionals();
    *len = notionals.size();
    double *ns = qlAllocateDoubles(*len);
    std::copy(notionals.begin(), notionals.end(), ns);
    return ns;
  } catch (std::exception& er) {
    return handleException<double*>(e, er);
  }
}

// generated code and thus not necessarilly tested
double qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy,
    unsigned maxEvaluations, char **e) {
  try {
    return (*arg(o))->yield(*arg(dc), (Compounding)comp, (Frequency)freq, accuracy, maxEvaluations);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondAccruedAmount(QlBond* o, int d, char **e) {
  try {
    return (*arg(o))->accruedAmount(Date(d));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondCleanPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e) {
  try {
    return (*arg(o))->cleanPrice(yield, *arg(dc), (Compounding)comp, (Frequency)freq, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e) {
  try {
    return (*arg(o))->dirtyPrice(yield, *arg(dc), (Compounding)comp, (Frequency)freq, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

int qlBondNextCashFlowDate(QlBond* o, int d, char **e) {
  try {
    return qlNullableDate((*arg(o))->nextCashFlowDate(Date(d)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

double qlBondNextCouponRate(QlBond* o, int d, char **e) {
  try {
    return (*arg(o))->nextCouponRate(Date(d));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondNotional(QlBond* o, int d, char **e) {
  try {
    return (*arg(o))->notional(Date(d));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

int qlBondPreviousCashFlowDate(QlBond* o, int d, char **e) {
  try {
    return qlNullableDate((*arg(o))->previousCashFlowDate(Date(d)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

double qlBondPreviousCouponRate(QlBond* o, int d, char **e) {
  try {
    return (*arg(o))->previousCouponRate(Date(d));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondSettlementValue1(QlBond* o, double cleanPrice, char **e) {
  try {
    return (*arg(o))->settlementValue(cleanPrice);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondSettlementValue(QlBond* o, char **e) {
  try {
    return (*arg(o))->settlementValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondYield1(QlBond* o, double cleanPrice, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, char **e) {
  try {
    return (*arg(o))->yield(cleanPrice, *arg(dc), (Compounding)comp, (Frequency)freq, Date(settlementDate), accuracy, maxEvaluations);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

int qlBondIsTradable(QlBond* o, int d, char **e) {
  try {
    return (*arg(o))->isTradable(Date(d));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

Leg* qlBondCashflows(QlBond* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->cashflows()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
Leg* qlBondRedemptions(QlBond* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->redemptions()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
int qlBondSettlementDate(QlBond* o, int d, char **e) {
  try {
    return ((*arg(o))->settlementDate(Date(d))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlBondStartDate(QlBond* o, char **e) {
  try {
    return ((*arg(o))->startDate()).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

int qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, char **e) {
  try {
    return BondFunctions::accrualDays(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, char **e) {
  try {
    return qlNullableDate(BondFunctions::accrualEndDate(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, char **e) {
  try {
    return BondFunctions::accrualPeriod(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, char **e) {
  try {
    return qlNullableDate(BondFunctions::accrualStartDate(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, char **e) {
  try {
    return BondFunctions::accruedDays(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, char **e) {
  try {
    return BondFunctions::accruedPeriod(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double cleanPrice, char **e) {
  try {
    return BondFunctions::atmRate(**arg(bond), **arg(discountCurve), Date(settlementDate), cleanPrice);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsBasisPointValue1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {
    return BondFunctions::basisPointValue(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {
    return BondFunctions::basisPointValue(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {
    return BondFunctions::bps(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsBps2(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {
    return BondFunctions::bps(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e) {
  try {
    return BondFunctions::bps(**arg(bond), **arg(discountCurve), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e) {
  try {
    return BondFunctions::cleanPrice(**arg(bond), **arg(discountCurve), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {
    return BondFunctions::cleanPrice(**arg(bond), *arg(discount), zSpread, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {
    return BondFunctions::cleanPrice(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsConvexity1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {
    return BondFunctions::convexity(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {
    return BondFunctions::convexity(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsDuration1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int settlementDate, char **e) {
  try {
    return BondFunctions::duration(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, (Duration::Type)type, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, char **e) {
  try {
    return BondFunctions::duration(**arg(bond), *arg(yield), (Duration::Type)type, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, char **e) {
  try {
    return BondFunctions::nextCashFlowAmount(**arg(bond), Date(refDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, char **e) {
  try {
    return BondFunctions::previousCashFlowAmount(**arg(bond), Date(refDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, char **e) {
  try {
    return qlNullableDate(BondFunctions::referencePeriodEnd(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, char **e) {
  try {
    return qlNullableDate(BondFunctions::referencePeriodStart(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlBondFunctionsYield2(QlBond* bond, double cleanPrice, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {
    return BondFunctions::yield(**arg(bond), cleanPrice, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsYieldValueBasisPoint1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {
    return BondFunctions::yieldValueBasisPoint(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {
    return BondFunctions::yieldValueBasisPoint(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBondFunctionsZSpread(QlBond* bond, double cleanPrice, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {
    return BondFunctions::zSpread(**arg(bond), cleanPrice, *arg(x2), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlBond* qlFloatingRateBond1(unsigned settlementDays, double faceAmount, int startDate, int maturityDate, int couponFrequency, Calendar* calendar, QlIborIndex* iborIndex, DayCounter* accrualDayCounter, int accrualConvention, int paymentConvention, unsigned fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, double redemption, int issueDate, int stubDate, int rule, int endOfMonth, char **e) {
  try {
    return ret(new QlBond(alloc(new FloatingRateBond(settlementDays, faceAmount, Date(startDate), Date(maturityDate), (Frequency)couponFrequency, *arg(calendar), *arg(iborIndex), *arg(accrualDayCounter), (BusinessDayConvention)accrualConvention, (BusinessDayConvention)paymentConvention, fixingDays, std::vector<double>(gearings, gearings+gearingsLen), std::vector<double>(spreads, spreads+spreadsLen), std::vector<double>(caps, caps+capsLen), std::vector<double>(floors, floors+floorsLen), inArrears, redemption, qlNullableDate(issueDate), qlNullableDate(stubDate), (DateGeneration::Rule)rule, endOfMonth))));
  } catch (std::exception& er) {
    return handleException<QlBond*>(e, er);
  }
}

double qlBondCleanPrice(QlBond* o, char **e) {
  try {
    return (*arg(o))->cleanPrice();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlBondDirtyPrice(QlBond* o, char **e) {
  try {
    return (*arg(o))->dirtyPrice();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeCallableBond(QlCallableBond *o) { del(o); }
QlBond* qlCallableBondAsBond(QlCallableBond *o) { return ret(new QlBond(*arg(o))); }
void qlFreeConvertibleBond(QlConvertibleBond *o) { del(o); }
QlBond* qlConvertibleBondAsBond(QlConvertibleBond *o) { return ret(new QlBond(*arg(o))); }

QlCallableBond* qlCallableFixedRateBond(unsigned settlementDays, double faceAmount, Schedule* schedule, unsigned couponsLen, double* coupons, DayCounter* accrualDayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e) {
  try {
    return ret(new QlCallableBond(alloc(new CallableFixedRateBond(settlementDays, faceAmount, *arg(schedule), std::vector<double>(coupons, coupons+couponsLen), *arg(accrualDayCounter), (BusinessDayConvention)paymentConvention, redemption, qlNullableDate(issueDate), qlBuildVector(putCallSchedule, putCallScheduleLen)))));
  } catch (std::exception& er) {
    return handleException<QlCallableBond*>(e, er);
  }
}
QlCallableBond* qlCallableZeroCouponBond(unsigned settlementDays, double faceAmount, Calendar* calendar, int maturityDate, DayCounter* dayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e) {
  try {
    return ret(new QlCallableBond(alloc(new CallableZeroCouponBond(settlementDays, faceAmount, *arg(calendar), Date(maturityDate), *arg(dayCounter), (BusinessDayConvention)paymentConvention, redemption, qlNullableDate(issueDate), qlBuildVector(putCallSchedule, putCallScheduleLen)))));
  } catch (std::exception& er) {
    return handleException<QlCallableBond*>(e, er);
  }
}
QlConvertibleBond* qlConvertibleFixedCouponBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, unsigned couponsLen, double* coupons, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e) {
  try {
    return ret(new QlConvertibleBond(alloc(new ConvertibleFixedCouponBond(*arg(exercise), conversionRatio, qlBuildVector(dividends, dividendsLen), qlBuildVector(callability, callabilityLen), Handle<Quote>(*arg(creditSpread)), Date(issueDate), settlementDays, std::vector<double>(coupons, coupons+couponsLen), *arg(dayCounter), *arg(schedule), redemption))));
  } catch (std::exception& er) {
    return handleException<QlConvertibleBond*>(e, er);
  }
}
QlConvertibleBond* qlConvertibleFloatingRateBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, QlIborIndex* index, unsigned fixingDays, unsigned spreadsLen, double* spreads, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e) {
  try {
    return ret(new QlConvertibleBond(alloc(new ConvertibleFloatingRateBond(*arg(exercise), conversionRatio, qlBuildVector(dividends, dividendsLen), qlBuildVector(callability, callabilityLen), Handle<Quote>(*arg(creditSpread)), Date(issueDate), settlementDays, (*arg(index)), fixingDays, std::vector<double>(spreads, spreads+spreadsLen), *arg(dayCounter), *arg(schedule), redemption))));
  } catch (std::exception& er) {
    return handleException<QlConvertibleBond*>(e, er);
  }
}
QlConvertibleBond* qlConvertibleZeroCouponBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e) {
  try {
    return ret(new QlConvertibleBond(alloc(new ConvertibleZeroCouponBond(*arg(exercise), conversionRatio, qlBuildVector(dividends, dividendsLen), qlBuildVector(callability, callabilityLen), Handle<Quote>(*arg(creditSpread)), Date(issueDate), settlementDays, *arg(dayCounter), *arg(schedule), redemption))));
  } catch (std::exception& er) {
    return handleException<QlConvertibleBond*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
