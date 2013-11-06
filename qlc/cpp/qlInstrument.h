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
  void DLLEXPORT qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
    char **e);
  double DLLEXPORT qlInstrumentNPV(QlInstrument *instr, char **e);
  void DLLEXPORT qlFreeInstrument(QlInstrument *instr);
  QlInstrument* DLLEXPORT qlCompositeInstrument(unsigned instrLen, QlInstrument **instrs, double *coeff, char **e);
  double DLLEXPORT qlInstrumentErrorEstimate(QlInstrument* o, char **e);
  int DLLEXPORT qlInstrumentIsExpired(QlInstrument* o, char **e);
  int DLLEXPORT qlInstrumentValuationDate(QlInstrument* o, char **e);
  void DLLEXPORT qlFreePayoff(QlPayoff *o);
  void DLLEXPORT qlFreeBasketPayoff(QlBasketPayoff *o);
  QlPayoff* DLLEXPORT qlBasketPayoffAsPayoff(QlBasketPayoff *o);
  void DLLEXPORT qlFreeStrikedTypePayoff(QlStrikedTypePayoff *o);
  QlTypePayoff* DLLEXPORT qlStrikedTypePayoffAsTypePayoff(QlStrikedTypePayoff *o);
  void DLLEXPORT qlFreeTypePayoff(QlTypePayoff *o);
  QlPayoff* DLLEXPORT qlTypePayoffAsPayoff(QlTypePayoff *o);
  void DLLEXPORT qlFreePercentageStrikePayoff(QlPercentageStrikePayoff *o);
  QlStrikedTypePayoff* DLLEXPORT qlPercentageStrikePayoffAsStrikedTypePayoff(QlPercentageStrikePayoff *o);
  void DLLEXPORT qlFreePlainVanillaPayoff(QlPlainVanillaPayoff *o);
  QlStrikedTypePayoff* DLLEXPORT qlPlainVanillaPayoffAsStrikedTypePayoff(QlPlainVanillaPayoff *o);

  QlStrikedTypePayoff* DLLEXPORT qlAssetOrNothingPayoff(int type, double strike, char **e);
  QlBasketPayoff* DLLEXPORT qlAverageBasketPayoff(QlPayoff* p, unsigned n, char **e);
  QlBasketPayoff* DLLEXPORT qlAverageBasketPayoff1(QlPayoff* p, unsigned aLen, double* a, char **e);
  QlStrikedTypePayoff* DLLEXPORT qlCashOrNothingPayoff(int type, double strike, double cashPayoff, char **e);
  QlPayoff* DLLEXPORT qlDoubleStickyRatchetPayoff(double type1, double type2, double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlTypePayoff* DLLEXPORT qlFloatingTypePayoff(int type, char **e);
  QlPayoff* DLLEXPORT qlForwardTypePayoff(int type, double strike, char **e);
  QlStrikedTypePayoff* DLLEXPORT qlGapPayoff(int type, double strike, double secondStrike, char **e);
  QlBasketPayoff* DLLEXPORT qlMaxBasketPayoff(QlPayoff* p, char **e);
  QlBasketPayoff* DLLEXPORT qlMinBasketPayoff(QlPayoff* p, char **e);
  QlPercentageStrikePayoff* DLLEXPORT qlPercentageStrikePayoff(int type, double moneyness, char **e);
  QlPlainVanillaPayoff* DLLEXPORT qlPlainVanillaPayoff(int type, double strike, char **e);
  QlPayoff* DLLEXPORT qlRatchetMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* DLLEXPORT qlRatchetMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* DLLEXPORT qlRatchetPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e);
  QlBasketPayoff* DLLEXPORT qlSpreadBasketPayoff(QlPayoff* p, char **e);
  QlPayoff* DLLEXPORT qlStickyMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* DLLEXPORT qlStickyMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* DLLEXPORT qlStickyPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e);
  QlStrikedTypePayoff* DLLEXPORT qlSuperFundPayoff(double strike, double secondStrike, char **e);
  QlStrikedTypePayoff* DLLEXPORT qlSuperSharePayoff(double strike, double secondStrike, double cashPayoff, char **e);

  void DLLEXPORT qlFreeAmericanExercise(QlAmericanExercise *o);
  QlExercise* DLLEXPORT qlAmericanExerciseAsExercise(QlAmericanExercise *o);
  void DLLEXPORT qlFreeBermudanExercise(QlBermudanExercise *o);
  QlExercise* DLLEXPORT qlBermudanExerciseAsExercise(QlBermudanExercise *o);
  void DLLEXPORT qlFreeEuropeanExercise(QlEuropeanExercise *o);
  QlExercise* DLLEXPORT qlEuropeanExerciseAsExercise(QlEuropeanExercise *o);
  void DLLEXPORT qlFreeExercise(QlExercise *o);
  QlAmericanExercise* DLLEXPORT qlAmericanExercise(int earliestDate, int latestDate, int payoffAtExpiry, char **e);
  QlBermudanExercise* DLLEXPORT qlBermudanExercise(unsigned datesLen, int *dates, int payoffAtExpiry, char **e);
  QlExercise* DLLEXPORT qlEarlyExercise(int type, int payoffAtExpiry, char **e);
  QlExercise* DLLEXPORT qlExercise(int type, char **e);
  QlEuropeanExercise* DLLEXPORT qlEuropeanExercise(int date, char **e);

  QlAmericanExercise* DLLEXPORT qlAmericanExercise1(int latestDate, int payoffAtExpiry, char **e);
  QlSwingExercise* DLLEXPORT qlSwingExercise(unsigned datesLen, int* dates, unsigned* seconds, char **e);
  QlSwingExercise* DLLEXPORT qlSwingExercise1(int from, int to, unsigned stepSizeSecs, char **e);
  void DLLEXPORT qlFreeCapFloor(QlCapFloor *o);
  QlInstrument* DLLEXPORT qlCapFloorAsInstrument(QlCapFloor *o);
  QlCapFloor* DLLEXPORT qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e);
  QlCapFloor* DLLEXPORT qlCollar(Leg* floatingLeg, unsigned capRatesLen, double* capRates, unsigned floorRatesLen, double* floorRates, char **e);
  QlCapFloor* DLLEXPORT qlFloor(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e);
  double DLLEXPORT qlCapFloorAtmRate(QlCapFloor* o, QlYieldTermStructure* discountCurve, char **e);
  double DLLEXPORT qlCapFloorImpliedVolatility(QlCapFloor* o, double price, QlYieldTermStructure* disc, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlCapFloor* DLLEXPORT qlCapFloorOptionlet(QlCapFloor* o, unsigned n, char **e);

  void DLLEXPORT qlFreeCallability(QlCallability *o);
  void DLLEXPORT qlFreeCallabilityPrice(QlCallabilityPrice *o);
  QlCallabilityPrice* DLLEXPORT qlCallabilityPrice(double amount, int type, char **e);
  QlCallability* DLLEXPORT qlCallability(QlCallabilityPrice* price, int type, int date, char **e);

  QlCallableBond* DLLEXPORT qlCallableFixedRateBond(unsigned settlementDays, double faceAmount, Schedule* schedule, unsigned couponsLen, double* coupons, DayCounter* accrualDayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e);
  QlCallableBond* DLLEXPORT qlCallableZeroCouponBond(unsigned settlementDays, double faceAmount, Calendar* calendar, int maturityDate, DayCounter* dayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e);
  QlConvertibleBond* DLLEXPORT qlConvertibleFixedCouponBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, unsigned couponsLen, double* coupons, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
  QlConvertibleBond* DLLEXPORT qlConvertibleFloatingRateBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, QlIborIndex* index, unsigned fixingDays, unsigned spreadsLen, double* spreads, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
  QlConvertibleBond* DLLEXPORT qlConvertibleZeroCouponBond(QlExercise* exercise, double conversionRatio, unsigned dividendsLen, QlDividend** dividends, unsigned callabilityLen, QlCallability** callability, QlQuote* creditSpread, int issueDate, unsigned settlementDays, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
