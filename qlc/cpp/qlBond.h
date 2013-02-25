#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  QlBond *DLLEXPORT qlBond(unsigned settlDays, Calendar *calendar, int issueDate,
    Leg *coupons, char **e);
  QlBond *DLLEXPORT qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount,
    int maturityDate, int issueDate, Leg *cashFlows, char **e);
  Leg* DLLEXPORT qlBondCashflows(QlBond* o, char **e);
  Leg* DLLEXPORT qlBondRedemptions(QlBond* o, char **e);
  int DLLEXPORT qlBondSettlementDate(QlBond* o, int d, char **e);
  int DLLEXPORT qlBondStartDate(QlBond* o, char **e);
  int DLLEXPORT qlBondMaturityDate(QlBond *bond);
  QlInstrument *DLLEXPORT qlBondAsInstrument(QlBond *bond);

  QlFixedRateBond *DLLEXPORT qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule,
    unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal,
    char **e);
  QlFixedRateBond *DLLEXPORT qlFixedRateBond1(unsigned settlDays, Calendar *cpnCal, double face,
    int start, int maturity, Period *tenor, unsigned cLen, double *coupons,
    DayCounter *dayCounter, int accrConv, int paymentConv, double redemption,
    int issue, int stub, int rule, int eom, Calendar *payCal, char **e);
  QlFixedRateBond *DLLEXPORT qlFixedRateBond2(unsigned settlDays, double face, Schedule *sched,
    unsigned cLen, InterestRate **coupons, int paymentConv, double redemption,
    int issue, Calendar *cal, char **e);
  QlBond *DLLEXPORT qlZeroCouponBond(int settlDays, Calendar *cal, double face,
    int maturity, int payConv, double redemption, int issue, char **e);
  QlBond *DLLEXPORT qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched,
    QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads,
    unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, double redemption, int issue, char **e);
  QlBond* DLLEXPORT qlFloatingRateBond1(unsigned settlementDays, double faceAmount, int startDate, int maturityDate, int couponFrequency, Calendar* calendar, QlIborIndex* iborIndex, DayCounter* accrualDayCounter, int accrualConvention, int paymentConvention, unsigned fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, double redemption, int issueDate, int stubDate, int rule, int endOfMonth, char **e);

  QlBond *DLLEXPORT qlFixedRateBondAsBond(QlFixedRateBond *bond);

  double DLLEXPORT qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy,
    unsigned maxEvaluations, char **e);
  double DLLEXPORT qlBondAccruedAmount(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondCleanPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  double DLLEXPORT qlBondCleanPrice(QlBond* o, char **e);
  double DLLEXPORT qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  double DLLEXPORT qlBondDirtyPrice(QlBond* o, char **e);
  int DLLEXPORT qlBondNextCashFlowDate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondNextCouponRate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondNotional(QlBond* o, int d, char **e);
  int DLLEXPORT qlBondPreviousCashFlowDate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondPreviousCouponRate(QlBond* o, int d, char **e);
  double DLLEXPORT qlBondSettlementValue1(QlBond* o, double cleanPrice, char **e);
  double DLLEXPORT qlBondSettlementValue(QlBond* o, char **e);
  double DLLEXPORT qlBondYield1(QlBond* o, double cleanPrice, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, char **e);
  int DLLEXPORT qlBondIsTradable(QlBond* o, int d, char **e);
  double* DLLEXPORT qlBondNotionals(QlBond* o, unsigned *len, char **e);

  int DLLEXPORT qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double cleanPrice, char **e);
  double DLLEXPORT qlBondFunctionsBasisPointValue1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBps2(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsConvexity1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsDuration1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, char **e);
  double DLLEXPORT qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, char **e);
  int DLLEXPORT qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, char **e);
  int DLLEXPORT qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsYield2(QlBond* bond, double cleanPrice, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double DLLEXPORT qlBondFunctionsYieldValueBasisPoint1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double DLLEXPORT qlBondFunctionsZSpread(QlBond* bond, double cleanPrice, QlYieldTermStructure* x2, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);

  void DLLEXPORT qlFreeBond(QlBond *bond);
  void DLLEXPORT qlFreeFixedRateBond(QlFixedRateBond *bond);
}
