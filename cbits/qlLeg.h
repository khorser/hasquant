#ifdef __cplusplus
extern "C" {
#endif
  Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int qlLegStartDate(Leg *leg, char **e);

  void qlFreeLeg(Leg *leg);
  Leg *qlNextCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e);
  Leg *qlPreviousCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e);
  void qlLegCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate,
    unsigned *al, double **amount, unsigned *dl, int **date, unsigned *hl, int **hasOccurred, char **e);

  double qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, char **e);
  double qlCashFlowsBasisPointValue1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBps2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsConvexity1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsDuration1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsMaturityDate(Leg* leg, char **e);
  double qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsNpv2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  void qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, char **e);
  double qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  int qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double qlCashFlowsYieldValueBasisPoint1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);

  void qlQuantLibSetCouponPricer(Leg* leg, QlFloatingRateCouponPricer* x1, char **e);
  void qlQuantLibSetCouponPricers(Leg* leg, unsigned x1Len, QlFloatingRateCouponPricer** x1, char **e);

  void qlCouponAccrualStartDates(CouponLeg* o, unsigned *len, int **days, char **e);

  void qlFreeDividend(QlDividend *o);
  QlDividend* qlFixedDividend(double amount, int date, char **e);
  QlDividend* qlFractionalDividend1(double rate, double nominal, int date, char **e);
  QlDividend* qlFractionalDividend(double rate, int date, char **e);

  Leg* qlAverageBMALeg(Schedule* schedule, QlBMAIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);
  Leg* qlFixedRateLeg(Schedule* schedule, unsigned NotionalsLen, double* Notionals, unsigned couponRatesLen, InterestRate** couponRates, int paymentAdjustment, DayCounter* firstPeriodDayCounter, Calendar* paymentCalendar, char **e);
  Leg* qlIborLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments, char **e);
  Leg* qlOvernightLeg(Schedule* schedule, QlOvernightIndex* overnightIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);
  Leg* qlRangeAccrualLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned lowerTriggersLen, double* lowerTriggers, unsigned upperTriggersLen, double* upperTriggers, int, int, int observationConvention, char **e);

  void qlFreeCouponLeg(CouponLeg *o);
  Leg* qlCouponLegAsLeg(CouponLeg *o);
  CouponLeg* qlLegToCouponLeg(Leg *o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
