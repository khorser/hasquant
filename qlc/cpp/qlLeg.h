#ifdef _WIN32
# if defined(DLLSOURCE)
#  define DLLEXPORT __declspec(dllexport)
# elif defined(DLLUSE)
#  define DLLEXPORT __declspec(dllimport)
# else
#  define DLLEXPORT
# endif
#else
# define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
  Leg *DLLEXPORT qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int DLLEXPORT qlLegStartDate(Leg *leg, char **e);

  void DLLEXPORT qlFreeLeg(Leg *leg);
  Leg *DLLEXPORT qlNextCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e);
  Leg *DLLEXPORT qlPreviousCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e);
  unsigned DLLEXPORT qlLegCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate,
    double **amount, int **date, int **hasOccurred, char **e);

  double DLLEXPORT qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int DLLEXPORT qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double DLLEXPORT qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, char **e);
  double DLLEXPORT qlCashFlowsBasisPointValue1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBps2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsConvexity1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsDuration1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int DLLEXPORT qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsMaturityDate(Leg* leg, char **e);
  double DLLEXPORT qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double DLLEXPORT qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsNpv2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  void DLLEXPORT qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, char **e);
  double DLLEXPORT qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double DLLEXPORT qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int DLLEXPORT qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  int DLLEXPORT qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double DLLEXPORT qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double DLLEXPORT qlCashFlowsYieldValueBasisPoint1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double DLLEXPORT qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);

  void DLLEXPORT qlQuantLibSetCouponPricer(Leg* leg, QlFloatingRateCouponPricer* x1, char **e);
  void DLLEXPORT qlQuantLibSetCouponPricers(Leg* leg, unsigned x1Len, QlFloatingRateCouponPricer** x1, char **e);

  int* DLLEXPORT qlCouponAccrualStartDates(CouponLeg* o, unsigned *len, char **e);

  void DLLEXPORT qlFreeDividend(QlDividend *o);
  QlDividend* DLLEXPORT qlFixedDividend(double amount, int date, char **e);
  QlDividend* DLLEXPORT qlFractionalDividend1(double rate, double nominal, int date, char **e);
  QlDividend* DLLEXPORT qlFractionalDividend(double rate, int date, char **e);

  Leg* DLLEXPORT qlAverageBMALeg(Schedule* schedule, QlBMAIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);
  Leg* DLLEXPORT qlFixedRateLeg(Schedule* schedule, unsigned NotionalsLen, double* Notionals, unsigned couponRatesLen, InterestRate** couponRates, int paymentAdjustment, DayCounter* firstPeriodDayCounter, Calendar* paymentCalendar, char **e);
  Leg* DLLEXPORT qlIborLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments, char **e);
  Leg* DLLEXPORT qlOvernightLeg(Schedule* schedule, QlOvernightIndex* overnightIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);
  Leg* DLLEXPORT qlRangeAccrualLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned lowerTriggersLen, double* lowerTriggers, unsigned upperTriggersLen, double* upperTriggers, int, int, int observationConvention, char **e);

  void DLLEXPORT qlFreeCouponLeg(CouponLeg *o);
  Leg* DLLEXPORT qlCouponLegAsLeg(CouponLeg *o);
  CouponLeg* DLLEXPORT qlLegToCouponLeg(Leg *o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
