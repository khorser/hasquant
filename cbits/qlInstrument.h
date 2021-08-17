#ifdef __cplusplus
extern "C" {
#endif
  void qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
    char **e);
  double qlInstrumentNPV(QlInstrument *instr, char **e);
  void qlFreeInstrument(QlInstrument *instr);
  QlInstrument* qlCompositeInstrument(unsigned instrLen, QlInstrument **instrs, double *coeff, char **e);
  double qlInstrumentErrorEstimate(QlInstrument* o, char **e);
  int qlInstrumentIsExpired(QlInstrument* o, char **e);
  int qlInstrumentValuationDate(QlInstrument* o, char **e);
  void qlFreePayoff(QlPayoff *o);
  void qlFreeBasketPayoff(QlBasketPayoff *o);
  QlPayoff* qlBasketPayoffAsPayoff(QlBasketPayoff *o);
  void qlFreeStrikedTypePayoff(QlStrikedTypePayoff *o);
  QlTypePayoff* qlStrikedTypePayoffAsTypePayoff(QlStrikedTypePayoff *o);
  void qlFreeTypePayoff(QlTypePayoff *o);
  QlPayoff* qlTypePayoffAsPayoff(QlTypePayoff *o);
  void qlFreePercentageStrikePayoff(QlPercentageStrikePayoff *o);
  QlStrikedTypePayoff* qlPercentageStrikePayoffAsStrikedTypePayoff(QlPercentageStrikePayoff *o);
  void qlFreePlainVanillaPayoff(QlPlainVanillaPayoff *o);
  QlStrikedTypePayoff* qlPlainVanillaPayoffAsStrikedTypePayoff(QlPlainVanillaPayoff *o);

  QlStrikedTypePayoff* qlAssetOrNothingPayoff(int type, double strike, char **e);
  QlBasketPayoff* qlAverageBasketPayoff(QlPayoff* p, unsigned n, char **e);
  QlBasketPayoff* qlAverageBasketPayoff1(QlPayoff* p, unsigned aLen, double* a, char **e);
  QlStrikedTypePayoff* qlCashOrNothingPayoff(int type, double strike, double cashPayoff, char **e);
  QlPayoff* qlDoubleStickyRatchetPayoff(double type1, double type2, double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlTypePayoff* qlFloatingTypePayoff(int type, char **e);
  QlPayoff* qlForwardTypePayoff(int type, double strike, char **e);
  QlStrikedTypePayoff* qlGapPayoff(int type, double strike, double secondStrike, char **e);
  QlBasketPayoff* qlMaxBasketPayoff(QlPayoff* p, char **e);
  QlBasketPayoff* qlMinBasketPayoff(QlPayoff* p, char **e);
  QlPercentageStrikePayoff* qlPercentageStrikePayoff(int type, double moneyness, char **e);
  QlPlainVanillaPayoff* qlPlainVanillaPayoff(int type, double strike, char **e);
  QlPayoff* qlRatchetMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlRatchetMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlRatchetPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e);
  QlBasketPayoff* qlSpreadBasketPayoff(QlPayoff* p, char **e);
  QlPayoff* qlStickyMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlStickyMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlStickyPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e);
  QlStrikedTypePayoff* qlSuperFundPayoff(double strike, double secondStrike, char **e);
  QlStrikedTypePayoff* qlSuperSharePayoff(double strike, double secondStrike, double cashPayoff, char **e);

  void qlFreeAmericanExercise(QlAmericanExercise *o);
  QlExercise* qlAmericanExerciseAsExercise(QlAmericanExercise *o);
  void qlFreeBermudanExercise(QlBermudanExercise *o);
  QlExercise* qlBermudanExerciseAsExercise(QlBermudanExercise *o);
  void qlFreeEuropeanExercise(QlEuropeanExercise *o);
  QlExercise* qlEuropeanExerciseAsExercise(QlEuropeanExercise *o);
  void qlFreeExercise(QlExercise *o);
  QlAmericanExercise* qlAmericanExercise(int earliestDate, int latestDate, int payoffAtExpiry, char **e);
  QlBermudanExercise* qlBermudanExercise(unsigned datesLen, int *dates, int payoffAtExpiry, char **e);
  QlExercise* qlEarlyExercise(int type, int payoffAtExpiry, char **e);
  QlExercise* qlExercise(int type, char **e);
  QlEuropeanExercise* qlEuropeanExercise(int date, char **e);

  QlAmericanExercise* qlAmericanExercise1(int latestDate, int payoffAtExpiry, char **e);
  QlSwingExercise* qlSwingExercise(unsigned datesLen, int* dates, unsigned* seconds, char **e);
  QlSwingExercise* qlSwingExercise1(int from, int to, unsigned stepSizeSecs, char **e);
  void qlFreeCapFloor(QlCapFloor *o);
  QlInstrument* qlCapFloorAsInstrument(QlCapFloor *o);
  QlCapFloor* qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e);
  QlCapFloor* qlCollar(Leg* floatingLeg, unsigned capRatesLen, double* capRates, unsigned floorRatesLen, double* floorRates, char **e);
  QlCapFloor* qlFloor(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e);
  double qlCapFloorAtmRate(QlCapFloor* o, QlYieldTermStructure* discountCurve, char **e);
  double qlCapFloorImpliedVolatility(QlCapFloor* o, double price, QlYieldTermStructure* disc, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlCapFloor* qlCapFloorOptionlet(QlCapFloor* o, unsigned n, char **e);

  void qlFreeCallability(QlCallability *o);
  QlCallability* qlCallability(double price, int priceType, int type, int date, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
