#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/coupon.hpp>
#include <ql/cashflows/averagebmacoupon.hpp>
#include <ql/cashflows/fixedratecoupon.hpp>
#include <ql/cashflows/iborcoupon.hpp>
#include <ql/cashflows/overnightindexedcoupon.hpp>
#include <ql/cashflows/rangeaccrual.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/dividend.hpp>
#include <boost/shared_ptr.hpp>

#include "qlaux.h"
#include "qlLeg.h"
#include "qlUtilities.h"

using namespace QuantLib;
using namespace boost;

Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e) {
  Leg *leg = 0;
  try {
    leg = new Leg();
    for (unsigned i = 0; i < len; ++i)
      leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], Date(dates[i]))));
    return alloc(leg);
  } catch (std::exception& er) {
    return handleException(e, er, leg);
  }
}

int qlLegStartDate(Leg *leg, char **e) {
  try {
    Date d = CashFlows::startDate(*arg(leg));
    return d.serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeLeg(Leg *leg) {
  del(leg);
}

Leg *qlNextCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    const Leg &l = *arg(leg);
    Leg::const_iterator i = CashFlows::nextCashFlow(l,
        includeSettlementDateFlows, qlNullableDate(settlementDate));
    return new Leg(i, l.end());
  } catch (std::exception& er) {
    return handleException<Leg *>(e, er);
  }
}

Leg *qlPreviousCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    const Leg &l = *arg(leg);
    Leg::const_reverse_iterator i = CashFlows::previousCashFlow(l,
        includeSettlementDateFlows, qlNullableDate(settlementDate));
    return new Leg(l.begin(), i.base());
  } catch (std::exception& er) {
    return handleException<Leg *>(e, er);
  }
}

unsigned qlLegCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate,
    double **amount, int **date, int **hasOccurred, char **e) {
  *amount = 0; *date = 0; *hasOccurred = 0;
  try {
    const Leg& l = *arg(leg);
    *amount = qlAllocateDoubles(l.size());
    *date = qlAllocateInts(l.size());
    *hasOccurred = qlAllocateInts(l.size());
    for (unsigned i = 0; i < l.size(); ++i) {
      (*amount)[i] = l[i]->amount();
      (*date)[i] = l[i]->date().serialNumber();
      (*hasOccurred)[i] = l[i]->hasOccurred(qlNullableDate(settlementDate), qlOptBool(includeSettlementDateFlows));
    }
    return l.size();
  } catch (std::exception& er) {
    qlFreeDoubles(*amount);
    qlFreeInts(*date);
    qlFreeInts(*hasOccurred);
    *e = DUP(er.what());
    return 0;
  }
}

double qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::duration(*arg(leg), *arg(yield), (Duration::Type)type, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

// generated code

int qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::accrualDays(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return qlNullableDate(CashFlows::accrualEndDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::accrualPeriod(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {
    return qlNullableDate(CashFlows::accrualStartDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::accruedAmount(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::accruedDays(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::accruedPeriod(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, char **e) {
  try {
    return CashFlows::atmRate(*arg(leg), **arg(discountCurve), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate), npv);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsBasisPointValue1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::basisPointValue(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::basisPointValue(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::bps(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsBps2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::bps(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::bps(*arg(leg), *(*arg(discountCurve)), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsConvexity1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::convexity(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::convexity(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsDuration1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::duration(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, (Duration::Type)type, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::isExpired(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlCashFlowsMaturityDate(Leg* leg, char **e) {
  try {
    return (CashFlows::maturityDate(*arg(leg))).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::nextCashFlowAmount(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return qlNullableDate(CashFlows::nextCashFlowDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::nextCouponRate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {
    return CashFlows::nominal(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::npv(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsNpv2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::npv(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::npv(*arg(leg), *arg(discount), zSpread, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::npv(*arg(leg), **arg(discountCurve), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
void qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, char **e) {
  try {
    CashFlows::npvbps(*arg(leg), **arg(discountCurve), includeSettlementDateFlows, Date(settlementDate), Date(npvDate), *npv, *bps);
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
double qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::previousCashFlowAmount(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return qlNullableDate(CashFlows::previousCashFlowDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {
    return CashFlows::previousCouponRate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {
    return qlNullableDate(CashFlows::referencePeriodEnd(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {
    return qlNullableDate(CashFlows::referencePeriodStart(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate)));
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {
    return CashFlows::yield(*arg(leg), npv, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsYieldValueBasisPoint1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::yieldValueBasisPoint(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return CashFlows::yieldValueBasisPoint(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {
    return CashFlows::zSpread(*arg(leg), npv, *arg(x2), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
void qlQuantLibSetCouponPricer(Leg* leg, QlFloatingRateCouponPricer* x1, char **e) {
  try {
    return setCouponPricer(*arg(leg), *arg(x1));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
void qlQuantLibSetCouponPricers(Leg* leg, unsigned x1Len, QlFloatingRateCouponPricer** x1, char **e) {
  try {
    return setCouponPricers(*arg(leg), qlBuildVector(x1, x1Len));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

void qlFreeCoupon(QlCoupon *o) { del(o); }

QlCoupon **qlLegCoupons(Leg *leg, unsigned *len, char **e) {
  *len = leg->size();
  QlCoupon **coupons = 0;
  try {
    coupons = reinterpret_cast<QlCoupon **>(qlAllocatePointerArray(*len));
    unsigned i;
    for (i = 0; i < leg->size(); ++i) {
      QlCoupon c = boost::dynamic_pointer_cast<Coupon>((*leg)[i]);
      if (c)
        coupons[i] = new QlCoupon(c);
      else
        break;
    }
    if (i < leg->size()) {
      for (unsigned j = 0; j < i; ++j)
        delete coupons[j];
      QL_FAIL("Not all cash flows are coupons");
    }
    return coupons;
  } catch (std::exception& er) {
    qlFreePointerArray(reinterpret_cast<void **>(coupons));
    return handleException<QlCoupon **>(e, er);
  }
}

int qlCouponAccrualStartDate(QlCoupon* o, char **e) {
  try {
    return ((*arg(o))->accrualStartDate()).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreeDividend(QlDividend *o) { del(o); }

QlDividend* qlFixedDividend(double amount, int date, char **e) {
  try {
    return ret(new QlDividend(alloc(new FixedDividend(amount, Date(date)))));
  } catch (std::exception& er) {
    return handleException<QlDividend*>(e, er);
  }
}
QlDividend* qlFractionalDividend1(double rate, double nominal, int date, char **e) {
  try {
    return ret(new QlDividend(alloc(new FractionalDividend(rate, nominal, Date(date)))));
  } catch (std::exception& er) {
    return handleException<QlDividend*>(e, er);
  }
}
QlDividend* qlFractionalDividend(double rate, int date, char **e) {
  try {
    return ret(new QlDividend(alloc(new FractionalDividend(rate, Date(date)))));
  } catch (std::exception& er) {
    return handleException<QlDividend*>(e, er);
  }
}

Leg* qlAverageBMALeg(Schedule* schedule, QlBMAIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e) {
  try {
    return alloc(new Leg(AverageBMALeg(*arg(schedule), *arg(index)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
          .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
Leg* qlFixedRateLeg(Schedule* schedule, unsigned NotionalsLen, double* Notionals, unsigned couponRatesLen, InterestRate** couponRates, int paymentAdjustment, DayCounter* firstPeriodDayCounter, Calendar* paymentCalendar, char **e) {
  try {
    return alloc(new Leg(FixedRateLeg(*arg(schedule)).withNotionals(std::vector<double>(Notionals, Notionals+NotionalsLen)).withCouponRates(qlBuildVector(couponRates, couponRatesLen))
          .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFirstPeriodDayCounter(*arg(firstPeriodDayCounter)).withPaymentCalendar(*arg(paymentCalendar))));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
Leg* qlIborLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments, char **e) {
  try {
    return alloc(new Leg(IborLeg(*arg(schedule), *arg(index)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
          .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFixingDays(std::vector<unsigned>(fixingDays, fixingDays+fixingDaysLen))
          .withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))
          .withCaps(std::vector<double>(caps, caps+capsLen)).withFloors(std::vector<double>(floors, floors+floorsLen)).inArrears(inArrears).withZeroPayments(zeroPayments)));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
Leg* qlOvernightLeg(Schedule* schedule, QlOvernightIndex* overnightIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e) {
  try {
    return alloc(new Leg(OvernightLeg(*arg(schedule), *arg(overnightIndex)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
          .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
Leg* qlRangeAccrualLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned lowerTriggersLen, double* lowerTriggers, unsigned upperTriggersLen, double* upperTriggers, Period* observationTenor, int observationConvention, char **e) {
  try {
    return alloc(new Leg(RangeAccrualLeg(*arg(schedule), *arg(index)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
            .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFixingDays(std::vector<unsigned>(fixingDays, fixingDays+fixingDaysLen))
            .withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen)).
            withLowerTriggers(std::vector<double>(lowerTriggers, lowerTriggers+lowerTriggersLen)).withUpperTriggers(std::vector<double>(upperTriggers, upperTriggers+upperTriggersLen))
            .withObservationTenor(*arg(observationTenor)).withObservationConvention((BusinessDayConvention)observationConvention)));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
