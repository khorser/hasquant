#ifdef __cplusplus
extern "C" {
#endif
  QlBond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate,
    Leg *coupons, char **e);
  QlBond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e);
  Leg* qlBondCashflows(QlBond* o, char **e);
  Leg* qlBondRedemptions(QlBond* o, char **e);
  int qlBondSettlementDate(QlBond* o, int d, char **e);
  int qlBondStartDate(QlBond* o, char **e);
  int qlBondMaturityDate(QlBond *bond);
  QlInstrument *qlBondAsInstrument(QlBond *bond);

  QlFixedRateBond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule,
    unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal,
    char **e);
  QlFixedRateBond *qlFixedRateBond1(unsigned settlDays, Calendar *cpnCal, double face,
    int start, int maturity, int, int, unsigned cLen, double *coupons,
    DayCounter *dayCounter, int accrConv, int paymentConv, double redemption,
    int issue, int stub, int rule, int eom, Calendar *payCal, char **e);
  QlFixedRateBond *qlFixedRateBond2(unsigned settlDays, double face, Schedule *sched,
    unsigned cLen, InterestRate **coupons, int paymentConv, double redemption,
    int issue, Calendar *cal, char **e);
  QlBond *qlZeroCouponBond(int settlDays, Calendar *cal, double face,
    int maturity, int payConv, double redemption, int issue, char **e);
//  QlBond *qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched,
//    QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
//    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads,
//    unsigned nCaps, double *caps, unsigned nFloors, double *floors,
//    int inArrears, double redemption, int issue, char **e);
//  QlBond* qlFloatingRateBond1(unsigned settlementDays, double faceAmount, int startDate, int maturityDate, int couponFrequency, Calendar* calendar, QlIborIndex* iborIndex, DayCounter* accrualDayCounter, int accrualConvention, int paymentConvention, unsigned fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, double redemption, int issueDate, int stubDate, int rule, int endOfMonth, char **e);

  QlBond *qlFixedRateBondAsBond(QlFixedRateBond *bond);

  double qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy,
    unsigned maxEvaluations, char **e);
  double qlBondAccruedAmount(QlBond* o, int d, char **e);
  double qlBondCleanPrice(QlBond* o, char **e);
  double qlBondCleanPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  double qlBondDirtyPrice(QlBond* o, char **e);
  double qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  int qlBondNextCashFlowDate(QlBond* o, int d, char **e);
  double qlBondNextCouponRate(QlBond* o, int d, char **e);
  double qlBondNotional(QlBond* o, int d, char **e);
  int qlBondPreviousCashFlowDate(QlBond* o, int d, char **e);
  double qlBondPreviousCouponRate(QlBond* o, int d, char **e);
  double qlBondSettlementValue1(QlBond* o, double cleanPrice, char **e);
  double qlBondSettlementValue(QlBond* o, char **e);
  double qlBondYield1(QlBond* o, double cleanPrice, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, char **e);
  int qlBondIsTradable(QlBond* o, int d, char **e);
  double* qlBondNotionals(QlBond* o, unsigned *len, char **e);

  int qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double cleanPrice, char **e);
  double qlBondFunctionsBasisPointValue1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsBps2(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
//  double qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsConvexity1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsDuration1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int settlementDate, char **e);
  double qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, char **e);
  double qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, char **e);
  double qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, char **e);
  int qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsYield2(QlBond* bond, double cleanPrice, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double qlBondFunctionsYieldValueBasisPoint1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
//  double qlBondFunctionsZSpread(QlBond* bond, double cleanPrice, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);

  void qlFreeBond(QlBond *bond);
  void qlFreeFixedRateBond(QlFixedRateBond *bond);
  void qlFreeCallableBond(QlCallableBond *o);
  QlBond* qlCallableBondAsBond(QlCallableBond *o);
  void qlFreeConvertibleBond(QlConvertibleBond *o);
  QlBond* qlConvertibleBondAsBond(QlConvertibleBond *o);

//  QlCallableBond* qlCallableFixedRateBond(unsigned settlementDays, double faceAmount, Schedule* schedule, unsigned couponsLen, double* coupons, DayCounter* accrualDayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e);
//  QlCallableBond* qlCallableZeroCouponBond(unsigned settlementDays, double faceAmount, Calendar* calendar, int maturityDate, DayCounter* dayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e);
//  QlConvertibleBond* qlConvertibleFixedCouponBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, unsigned couponsLen, double* coupons, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
//  QlConvertibleBond* qlConvertibleFloatingRateBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, QlIborIndex* index, unsigned fixingDays, unsigned spreadsLen, double* spreads, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
//  QlConvertibleBond* qlConvertibleZeroCouponBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
//  QlCallability* qlSoftCallability(QlBondPrice* price, int date, double trigger, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
