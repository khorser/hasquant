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
  QlRateHelper *DLLEXPORT qlDepositRateHelper(QlQuote *quote, Period *period,
    unsigned fixDays, Calendar *calendar, int conv, int eom,
    DayCounter *dayCount, char **e);
  QlBondHelper *DLLEXPORT qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays,
    double face, Schedule *sched, unsigned cLen, double *coupons,
    DayCounter *dayCount, int conv, double redemption, int issue, char **e);
  QlYieldTermStructure *DLLEXPORT qlPiecewiseYieldCurve(int date, unsigned rateLen,
    QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, double accuracy, char *trait,
    char *interpolator, char **e);
  QlYieldTermStructure *DLLEXPORT qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal,
    unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen,
    QlQuote **quotes, int *dates, double accuracy, char *trait,
    char *interpolator, char **e);
  QlSwapRateHelper *DLLEXPORT qlSwapRateHelper1(QlQuote *q, Period *t, Calendar *cal, int freq,
    int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, Period *fwdStart,
    QlYieldTermStructure *ts, char **e);
  void DLLEXPORT qlFreeSwapRateHelper(QlSwapRateHelper *o);
  QlRateHelper* DLLEXPORT qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o);

  void DLLEXPORT qlFreeBondHelper(QlBondHelper *o);
  QlRateHelper* DLLEXPORT qlBondHelperAsRateHelper(QlBondHelper *o);

  void DLLEXPORT qlFreeRateHelper(QlRateHelper *helper);
  QlRateHelper* DLLEXPORT qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);

  void DLLEXPORT qlFreeOISRateHelper(QlOISRateHelper *o);
  QlRateHelper* DLLEXPORT qlOISRateHelperAsRateHelper(QlOISRateHelper *o);
  QlBondHelper* DLLEXPORT qlBondHelper(QlQuote* cleanPrice, QlBond* bond, char **e);
  QlOISRateHelper* DLLEXPORT qlOISRateHelper(unsigned settlementDays, Period* tenor, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e);
  QlSwapRateHelper* DLLEXPORT qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, Period* fwdStart, QlYieldTermStructure* discountingCurve, char **e);
  QlRateHelper* DLLEXPORT qlBMASwapRateHelper(QlQuote* liborFraction, Period* tenor, unsigned settlementDays, Calendar* calendar, Period* bmaPeriod, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e);
  QlRateHelper* DLLEXPORT qlDatedOISRateHelper(int startDate, int endDate, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve, char **e);
  QlRateHelper* DLLEXPORT qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e);
  QlRateHelper* DLLEXPORT qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, char **e);
  QlRateHelper* DLLEXPORT qlFraRateHelper2(QlQuote* rate, Period* periodToStart, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, char **e);
  QlRateHelper* DLLEXPORT qlFraRateHelper3(QlQuote* rate, Period* periodToStart, QlIborIndex* iborIndex, char **e);
  QlRateHelper* DLLEXPORT qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* DLLEXPORT qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* DLLEXPORT qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, char **e);
  double DLLEXPORT qlRateHelperImpliedQuote(QlRateHelper* o, char **e);
  QlBond* DLLEXPORT qlBondHelperBond(QlBondHelper* o, char **e);
  QlOvernightIndexedSwap* DLLEXPORT qlOISRateHelperSwap(QlOISRateHelper* o, char **e);
  QlVanillaSwap* DLLEXPORT qlSwapRateHelperSwap(QlSwapRateHelper* o, char **e);
  void DLLEXPORT qlFreeYieldTermStructure(QlYieldTermStructure *ts);
  double DLLEXPORT qlYieldTSDiscount(QlYieldTermStructure *ts, int date,
    int extrapolate, char **e);
  QlYieldTermStructure* DLLEXPORT qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  QlYieldTermStructure* DLLEXPORT qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, Period* p, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e);
  InterestRate* DLLEXPORT qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e);
  double DLLEXPORT qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e);

  QlYieldTermStructure *DLLEXPORT qlInterpolatedDiscountCurve(unsigned dfsLen,
    double *dfs, int *dfsDates, DayCounter *dayCount, Calendar *cal,
    unsigned quoteLen, QlQuote **quotes, int *dates, char *interpolator, char **e);
  QlYieldTermStructure *DLLEXPORT qlInterpolatedForwardCurve(unsigned fwdLen,
    double *fwds, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *interpolator, char **e);
  QlYieldTermStructure *DLLEXPORT qlInterpolatedZeroCurve(unsigned yieldLen,
    double *yields, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, int *dates, char *interpolator, char **e);
  void DLLEXPORT qlFreeFittedBondDiscountCurveFittingMethod(FittedBondDiscountCurve::FittingMethod *o);
  FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlCubicBSplinesFitting(unsigned knotVectorLen, double * knotVector, int constrainAtZero, char **e);
  FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlExponentialSplinesFitting(int constrainAtZero, char **e);
  FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlNelsonSiegelFitting(char **e);
  FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, char **e);
  FittedBondDiscountCurve::FittingMethod* DLLEXPORT qlSvenssonFitting(char **e);
  QlFittedBondDiscountCurve* DLLEXPORT qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e);
  QlFittedBondDiscountCurve* DLLEXPORT qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurve::FittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e);

  void DLLEXPORT qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o);
  QlYieldTermStructure* DLLEXPORT qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o);

  double DLLEXPORT qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve* o, char **e);
  int DLLEXPORT qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve* o, char **e);
  QlYieldTermStructure* DLLEXPORT qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e);
  QlYieldTermStructure* DLLEXPORT qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, DayCounter* dc, char **e);
  int DLLEXPORT qlTermStructureReferenceDate(QlTermStructure* o, char **e);
  void DLLEXPORT qlFreeTermStructure(QlTermStructure *o);
  QlTermStructure* DLLEXPORT qlYieldTermStructureAsTermStructure(QlYieldTermStructure *o);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
