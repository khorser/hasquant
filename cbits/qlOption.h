#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeBarrierOption(QlBarrierOption *o);
  QlOneAssetOption* qlBarrierOptionAsOneAssetOption(QlBarrierOption *o);
  void qlFreeDividendVanillaOption(QlDividendVanillaOption *o);
  QlOneAssetOption* qlDividendVanillaOptionAsOneAssetOption(QlDividendVanillaOption *o);
  void qlFreeForwardVanillaOption(QlForwardVanillaOption *o);
  QlOneAssetOption* qlForwardVanillaOptionAsOneAssetOption(QlForwardVanillaOption *o);
  void qlFreeMargrabeOption(QlMargrabeOption *o);
  QlMultiAssetOption* qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o);
  void qlFreeMultiAssetOption(QlMultiAssetOption *o);
  QlOption* qlMultiAssetOptionAsOption(QlMultiAssetOption *o);
  void qlFreeOneAssetOption(QlOneAssetOption *o);
  QlOption* qlOneAssetOptionAsOption(QlOneAssetOption *o);
  void qlFreeOption(QlOption *o);
  QlInstrument* qlOptionAsInstrument(QlOption *o);
  void qlFreeQuantoVanillaOption(QlQuantoVanillaOption *o);
  QlOneAssetOption* qlQuantoVanillaOptionAsOneAssetOption(QlQuantoVanillaOption *o);
  void qlFreeSwaption(QlSwaption *o);
  QlOption* qlSwaptionAsOption(QlSwaption *o);
  void qlFreeSwingExercise(QlSwingExercise *o);
  QlBermudanExercise* qlSwingExerciseAsBermudanExercise(QlSwingExercise *o);
  void qlFreeVanillaOption(QlVanillaOption *o);
  QlOneAssetOption* qlVanillaOptionAsOneAssetOption(QlVanillaOption *o);
  double qlCdsOptionAtmRate(QlCdsOption* o, char **e);
  QlCdsOption* qlCdsOption(QlCreditDefaultSwap* swap, QlExercise* exercise, int knocksOut, char **e);
  double qlCdsOptionImpliedVolatility(QlCdsOption* o, double price, QlYieldTermStructure* termStructure, QlDefaultProbabilityTermStructure* x3, double recoveryRate, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  double qlCdsOptionRiskyAnnuity(QlCdsOption* o, char **e);
  double qlSwaptionImpliedVolatility(QlSwaption* o, double price, QlYieldTermStructure* discountCurve, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlSwaption* qlSwaption(QlVanillaSwap* swap, QlExercise* exercise, int delivery, char **e);
  void qlFreeQuantoBarrierOption(QlQuantoBarrierOption *o);
  QlBarrierOption* qlQuantoBarrierOptionAsBarrierOption(QlQuantoBarrierOption *o);
  void qlFreeQuantoForwardVanillaOption(QlQuantoForwardVanillaOption *o);
  QlForwardVanillaOption* qlQuantoForwardVanillaOptionAsForwardVanillaOption(QlQuantoForwardVanillaOption *o);

  QlBarrierOption* qlBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double qlBarrierOptionImpliedVolatility(QlBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlDividendVanillaOption* qlDividendVanillaOption(QlStrikedTypePayoff* payoff, QlExercise* exercise, unsigned dividendDatesLen, int* dividendDates, unsigned dividendsLen, double* dividends, char **e);
  double qlDividendVanillaOptionImpliedVolatility(QlDividendVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlForwardVanillaOption* qlForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double qlMargrabeOptionDelta1(QlMargrabeOption* o, char **e);
  double qlMargrabeOptionDelta2(QlMargrabeOption* o, char **e);
  double qlMargrabeOptionGamma1(QlMargrabeOption* o, char **e);
  double qlMargrabeOptionGamma2(QlMargrabeOption* o, char **e);
  QlMargrabeOption* qlMargrabeOption(int Q1, int Q2, QlExercise* x2, char **e);
  double qlMultiAssetOptionDelta(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionDividendRho(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionGamma(QlMultiAssetOption* o, char **e);
  QlMultiAssetOption* qlMultiAssetOption(QlPayoff* x0, QlExercise* x1, char **e);
  double qlMultiAssetOptionRho(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionTheta(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionVega(QlMultiAssetOption* o, char **e);
  double qlOneAssetOptionDelta(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionDeltaForward(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionDividendRho(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionElasticity(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionGamma(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionItmCashProbability(QlOneAssetOption* o, char **e);
  QlOneAssetOption* qlOneAssetOption(QlPayoff* x0, QlExercise* x1, char **e);
  double qlOneAssetOptionRho(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionStrikeSensitivity(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionTheta(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionThetaPerDay(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionVega(QlOneAssetOption* o, char **e);
  double qlQuantoBarrierOptionQlambda(QlQuantoBarrierOption* o, char **e);
  double qlQuantoBarrierOptionQrho(QlQuantoBarrierOption* o, char **e);
  QlQuantoBarrierOption* qlQuantoBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double qlQuantoBarrierOptionQvega(QlQuantoBarrierOption* o, char **e);
  double qlQuantoForwardVanillaOptionQlambda(QlQuantoForwardVanillaOption* o, char **e);
  double qlQuantoForwardVanillaOptionQrho(QlQuantoForwardVanillaOption* o, char **e);
  QlQuantoForwardVanillaOption* qlQuantoForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* x2, QlExercise* x3, char **e);
  double qlQuantoForwardVanillaOptionQvega(QlQuantoForwardVanillaOption* o, char **e);
  double qlQuantoVanillaOptionQlambda(QlQuantoVanillaOption* o, char **e);
  double qlQuantoVanillaOptionQrho(QlQuantoVanillaOption* o, char **e);
  QlQuantoVanillaOption* qlQuantoVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
  double qlQuantoVanillaOptionQvega(QlQuantoVanillaOption* o, char **e);
  double qlVanillaOptionImpliedVolatility(QlVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlVanillaOption* qlVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
  QlBarrierOption* qlDividendBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, unsigned dividendDatesLen, int* dividendDates, unsigned dividendsLen, double* dividends, char **e);
  QlMultiAssetOption* qlBasketOption(QlBasketPayoff* x0, QlExercise* x1, char **e);
  QlMultiAssetOption* qlHimalayaOption(unsigned fixingDatesLen, int* fixingDates, double strike, char **e);
  QlMultiAssetOption* qlPagodaOption(unsigned fixingDatesLen, int* fixingDates, double roof, double fraction, char **e);
  QlMultiAssetOption* qlSpreadOption(QlPlainVanillaPayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlCliquetOption(QlPercentageStrikePayoff* x0, QlEuropeanExercise* maturity, unsigned resetDatesLen, int* resetDates, char **e);
  QlOneAssetOption* qlContinuousAveragingAsianOption(int averageType, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlContinuousFixedLookbackOption(double currentMinmax, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlContinuousFloatingLookbackOption(double currentMinmax, QlTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlDiscreteAveragingAsianOption(int averageType, double runningAccumulator, unsigned pastFixings, unsigned fixingDatesLen, int* fixingDates, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlVanillaStorageOption(QlBermudanExercise* ex, double capacity, double load, double changeRate, char **e);
  QlOneAssetOption* qlVanillaSwingOption(QlStrikedTypePayoff* payoff, QlSwingExercise* ex, unsigned minExerciseRights, unsigned maxExerciseRights, char **e);
  QlVanillaOption* qlEuropeanOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
