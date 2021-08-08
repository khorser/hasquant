#ifdef __cplusplus
extern "C" {
#endif
  QlRateHelper *qlDepositRateHelper(QlQuote *quote, int, int,
    unsigned fixDays, Calendar *calendar, int conv, int eom,
    DayCounter *dayCount, char **e);
  QlBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays,
    double face, Schedule *sched, unsigned cLen, double *coupons,
    DayCounter *dayCount, int conv, double redemption, int issue, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen,
    QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *trait,
    char *interpolator, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal,
    unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *trait,
    char *interpolator, char **e);
  QlSwapRateHelper *qlSwapRateHelper1(QlQuote *q, int, int, Calendar *cal, int freq,
    int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, int, int,
    QlYieldTermStructure *ts, char **e);
  void qlFreeSwapRateHelper(QlSwapRateHelper *o);
  QlRateHelper* qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o);

  void qlFreeBondHelper(QlBondHelper *o);
  QlRateHelper* qlBondHelperAsRateHelper(QlBondHelper *o);

  void qlFreeRateHelper(QlRateHelper *helper);
  QlRateHelper* qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);

  void qlFreeOISRateHelper(QlOISRateHelper *o);
  QlRateHelper* qlOISRateHelperAsRateHelper(QlOISRateHelper *o);
  QlBondHelper* qlBondHelper(QlQuote* cleanPrice, QlBond* bond, char **e);
  QlOISRateHelper* qlOISRateHelper(unsigned settlementDays, int, int, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e);
  QlSwapRateHelper* qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, int, int, QlYieldTermStructure* discountingCurve, char **e);
  QlRateHelper* qlBMASwapRateHelper(QlQuote* liborFraction, int, int, unsigned settlementDays, Calendar* calendar, int, int, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e);
  QlRateHelper* qlDatedOISRateHelper(int startDate, int endDate, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e);
  QlRateHelper* qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e);
  QlRateHelper* qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, char **e);
  QlRateHelper* qlFraRateHelper2(QlQuote* rate, int, int, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);
  QlRateHelper* qlFraRateHelper3(QlQuote* rate, int, int, QlIborIndex* iborIndex, char **e);
  QlRateHelper* qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e);
  double qlRateHelperImpliedQuote(QlRateHelper* o, char **e);
  QlBond* qlBondHelperBond(QlBondHelper* o, char **e);
  QlOvernightIndexedSwap* qlOISRateHelperSwap(QlOISRateHelper* o, char **e);
  QlVanillaSwap* qlSwapRateHelperSwap(QlSwapRateHelper* o, char **e);
  void qlFreeYieldTermStructure(QlYieldTermStructure *ts);
  double qlYieldTSDiscount(QlYieldTermStructure *ts, int date,
    int extrapolate, char **e);
  QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  InterestRate* qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, int, int, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e);
  double qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e);

  QlYieldTermStructure *qlInterpolatedDiscountCurve(unsigned dfsLen,
    double *dfs, int *dfsDates, DayCounter *dayCount, Calendar *cal,
    unsigned quoteLen, QlQuote **quotes, int *dates, char *interpolator, char **e);
  QlYieldTermStructure *qlInterpolatedForwardCurve(unsigned fwdLen,
    double *fwds, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *interpolator, char **e);
  QlYieldTermStructure *qlInterpolatedZeroCurve(unsigned yieldLen,
    double *yields, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *interpolator, char **e);
  void qlFreeFittedBondDiscountCurveFittingMethod(FittedBondDiscountCurveFittingMethod *o);
  FittedBondDiscountCurveFittingMethod* qlCubicBSplinesFitting(unsigned knotVectorLen, double * knotVector, int constrainAtZero, char **e);
  FittedBondDiscountCurveFittingMethod* qlExponentialSplinesFitting(int constrainAtZero, char **e);
  FittedBondDiscountCurveFittingMethod* qlNelsonSiegelFitting(char **e);
  FittedBondDiscountCurveFittingMethod* qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, char **e);
  FittedBondDiscountCurveFittingMethod* qlSvenssonFitting(char **e);
  QlFittedBondDiscountCurve* qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurveFittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e);
  QlFittedBondDiscountCurve* qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurveFittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e);

  void qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o);
  QlYieldTermStructure* qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o);

  double qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve* o, char **e);
  int qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve* o, char **e);
  QlYieldTermStructure* qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e);
  QlYieldTermStructure* qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, DayCounter* dc, char **e);
  int qlTermStructureReferenceDate(QlTermStructure* o, char **e);
  int qlTermStructureMaxDate(QlTermStructure* o, char **e);
  void qlFreeTermStructure(QlTermStructure *o);
  QlTermStructure* qlYieldTermStructureAsTermStructure(QlYieldTermStructure *o);
  QlYieldTermStructure* qlImpliedTermStructure(QlYieldTermStructure* x0, int referenceDate, char **e);
  QlYieldTermStructure* qlDriftTermStructure(QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlBlackVolTermStructure* blackVolTS, char **e);
  QlYieldTermStructure* qlPiecewiseZeroSpreadedTermStructure(QlYieldTermStructure* x0, unsigned spreadsLen, QlQuote** spreads, int* dates, int comp, int freq, DayCounter* dc, char **e);
  QlYieldTermStructure* qlQuantoTermStructure(QlYieldTermStructure* underlyingDividendTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* foreignRiskFreeTS, QlBlackVolTermStructure* underlyingBlackVolTS, double strike, QlBlackVolTermStructure* exchRateBlackVolTS, double exchRateATMlevel, double underlyingExchRateCorrelation, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
