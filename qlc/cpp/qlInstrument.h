#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  void DLLEXPORT qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
    char **e);
  double DLLEXPORT qlInstrumentNPV(QlInstrument *instr, char **e);
  void DLLEXPORT qlFreeInstrument(QlInstrument *instr);
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
}
