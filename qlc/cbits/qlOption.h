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
  void DLLEXPORT qlFreeBarrierOption(QlBarrierOption *o);
  QlOneAssetOption* DLLEXPORT qlBarrierOptionAsOneAssetOption(QlBarrierOption *o);
  void DLLEXPORT qlFreeDividendVanillaOption(QlDividendVanillaOption *o);
  QlOneAssetOption* DLLEXPORT qlDividendVanillaOptionAsOneAssetOption(QlDividendVanillaOption *o);
  void DLLEXPORT qlFreeForwardVanillaOption(QlForwardVanillaOption *o);
  QlOneAssetOption* DLLEXPORT qlForwardVanillaOptionAsOneAssetOption(QlForwardVanillaOption *o);
  void DLLEXPORT qlFreeMargrabeOption(QlMargrabeOption *o);
  QlMultiAssetOption* DLLEXPORT qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o);
  void DLLEXPORT qlFreeMultiAssetOption(QlMultiAssetOption *o);
  QlOption* DLLEXPORT qlMultiAssetOptionAsOption(QlMultiAssetOption *o);
  void DLLEXPORT qlFreeOneAssetOption(QlOneAssetOption *o);
  QlOption* DLLEXPORT qlOneAssetOptionAsOption(QlOneAssetOption *o);
  void DLLEXPORT qlFreeOption(QlOption *o);
  QlInstrument* DLLEXPORT qlOptionAsInstrument(QlOption *o);
  void DLLEXPORT qlFreeQuantoVanillaOption(QlQuantoVanillaOption *o);
  QlOneAssetOption* DLLEXPORT qlQuantoVanillaOptionAsOneAssetOption(QlQuantoVanillaOption *o);
  void DLLEXPORT qlFreeSwaption(QlSwaption *o);
  QlOption* DLLEXPORT qlSwaptionAsOption(QlSwaption *o);
  void DLLEXPORT qlFreeSwingExercise(QlSwingExercise *o);
  QlBermudanExercise* DLLEXPORT qlSwingExerciseAsBermudanExercise(QlSwingExercise *o);
  void DLLEXPORT qlFreeVanillaOption(QlVanillaOption *o);
  QlOneAssetOption* DLLEXPORT qlVanillaOptionAsOneAssetOption(QlVanillaOption *o);
  double DLLEXPORT qlCdsOptionAtmRate(QlCdsOption* o, char **e);
  QlCdsOption* DLLEXPORT qlCdsOption(QlCreditDefaultSwap* swap, QlExercise* exercise, int knocksOut, char **e);
  double DLLEXPORT qlCdsOptionImpliedVolatility(QlCdsOption* o, double price, QlYieldTermStructure* termStructure, QlDefaultProbabilityTermStructure* x3, double recoveryRate, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  double DLLEXPORT qlCdsOptionRiskyAnnuity(QlCdsOption* o, char **e);
  double DLLEXPORT qlSwaptionImpliedVolatility(QlSwaption* o, double price, QlYieldTermStructure* discountCurve, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlSwaption* DLLEXPORT qlSwaption(QlVanillaSwap* swap, QlExercise* exercise, int delivery, char **e);
  void DLLEXPORT qlFreeQuantoBarrierOption(QlQuantoBarrierOption *o);
  QlBarrierOption* DLLEXPORT qlQuantoBarrierOptionAsBarrierOption(QlQuantoBarrierOption *o);
  void DLLEXPORT qlFreeQuantoForwardVanillaOption(QlQuantoForwardVanillaOption *o);
  QlForwardVanillaOption* DLLEXPORT qlQuantoForwardVanillaOptionAsForwardVanillaOption(QlQuantoForwardVanillaOption *o);

  QlBarrierOption* DLLEXPORT qlBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double DLLEXPORT qlBarrierOptionImpliedVolatility(QlBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlDividendVanillaOption* DLLEXPORT qlDividendVanillaOption(QlStrikedTypePayoff* payoff, QlExercise* exercise, unsigned dividendDatesLen, int* dividendDates, unsigned dividendsLen, double* dividends, char **e);
  double DLLEXPORT qlDividendVanillaOptionImpliedVolatility(QlDividendVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlForwardVanillaOption* DLLEXPORT qlForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double DLLEXPORT qlMargrabeOptionDelta1(QlMargrabeOption* o, char **e);
  double DLLEXPORT qlMargrabeOptionDelta2(QlMargrabeOption* o, char **e);
  double DLLEXPORT qlMargrabeOptionGamma1(QlMargrabeOption* o, char **e);
  double DLLEXPORT qlMargrabeOptionGamma2(QlMargrabeOption* o, char **e);
  QlMargrabeOption* DLLEXPORT qlMargrabeOption(int Q1, int Q2, QlExercise* x2, char **e);
  double DLLEXPORT qlMultiAssetOptionDelta(QlMultiAssetOption* o, char **e);
  double DLLEXPORT qlMultiAssetOptionDividendRho(QlMultiAssetOption* o, char **e);
  double DLLEXPORT qlMultiAssetOptionGamma(QlMultiAssetOption* o, char **e);
  QlMultiAssetOption* DLLEXPORT qlMultiAssetOption(QlPayoff* x0, QlExercise* x1, char **e);
  double DLLEXPORT qlMultiAssetOptionRho(QlMultiAssetOption* o, char **e);
  double DLLEXPORT qlMultiAssetOptionTheta(QlMultiAssetOption* o, char **e);
  double DLLEXPORT qlMultiAssetOptionVega(QlMultiAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionDelta(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionDeltaForward(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionDividendRho(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionElasticity(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionGamma(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionItmCashProbability(QlOneAssetOption* o, char **e);
  QlOneAssetOption* DLLEXPORT qlOneAssetOption(QlPayoff* x0, QlExercise* x1, char **e);
  double DLLEXPORT qlOneAssetOptionRho(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionStrikeSensitivity(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionTheta(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionThetaPerDay(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlOneAssetOptionVega(QlOneAssetOption* o, char **e);
  double DLLEXPORT qlQuantoBarrierOptionQlambda(QlQuantoBarrierOption* o, char **e);
  double DLLEXPORT qlQuantoBarrierOptionQrho(QlQuantoBarrierOption* o, char **e);
  QlQuantoBarrierOption* DLLEXPORT qlQuantoBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double DLLEXPORT qlQuantoBarrierOptionQvega(QlQuantoBarrierOption* o, char **e);
  double DLLEXPORT qlQuantoForwardVanillaOptionQlambda(QlQuantoForwardVanillaOption* o, char **e);
  double DLLEXPORT qlQuantoForwardVanillaOptionQrho(QlQuantoForwardVanillaOption* o, char **e);
  QlQuantoForwardVanillaOption* DLLEXPORT qlQuantoForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* x2, QlExercise* x3, char **e);
  double DLLEXPORT qlQuantoForwardVanillaOptionQvega(QlQuantoForwardVanillaOption* o, char **e);
  double DLLEXPORT qlQuantoVanillaOptionQlambda(QlQuantoVanillaOption* o, char **e);
  double DLLEXPORT qlQuantoVanillaOptionQrho(QlQuantoVanillaOption* o, char **e);
  QlQuantoVanillaOption* DLLEXPORT qlQuantoVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
  double DLLEXPORT qlQuantoVanillaOptionQvega(QlQuantoVanillaOption* o, char **e);
  double DLLEXPORT qlVanillaOptionImpliedVolatility(QlVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlVanillaOption* DLLEXPORT qlVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
  QlBarrierOption* DLLEXPORT qlDividendBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, unsigned dividendDatesLen, int* dividendDates, unsigned dividendsLen, double* dividends, char **e);
  QlMultiAssetOption* DLLEXPORT qlBasketOption(QlBasketPayoff* x0, QlExercise* x1, char **e);
  QlMultiAssetOption* DLLEXPORT qlHimalayaOption(unsigned fixingDatesLen, int* fixingDates, double strike, char **e);
  QlMultiAssetOption* DLLEXPORT qlPagodaOption(unsigned fixingDatesLen, int* fixingDates, double roof, double fraction, char **e);
  QlMultiAssetOption* DLLEXPORT qlSpreadOption(QlPlainVanillaPayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* DLLEXPORT qlCliquetOption(QlPercentageStrikePayoff* x0, QlEuropeanExercise* maturity, unsigned resetDatesLen, int* resetDates, char **e);
  QlOneAssetOption* DLLEXPORT qlContinuousAveragingAsianOption(int averageType, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* DLLEXPORT qlContinuousFixedLookbackOption(double currentMinmax, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* DLLEXPORT qlContinuousFloatingLookbackOption(double currentMinmax, QlTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* DLLEXPORT qlDiscreteAveragingAsianOption(int averageType, double runningAccumulator, unsigned pastFixings, unsigned fixingDatesLen, int* fixingDates, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* DLLEXPORT qlVanillaStorageOption(QlBermudanExercise* ex, double capacity, double load, double changeRate, char **e);
  QlOneAssetOption* DLLEXPORT qlVanillaSwingOption(QlStrikedTypePayoff* payoff, QlSwingExercise* ex, unsigned minExerciseRights, unsigned maxExerciseRights, char **e);
  QlVanillaOption* DLLEXPORT qlEuropeanOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
