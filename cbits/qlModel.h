#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeGJRGARCHModel(QlGJRGARCHModel *o);
  void qlFreeHestonModel(QlHestonModel *o);
  void qlFreeBatesModel(QlBatesModel *o);
  void qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o);
  void qlFreeShortRateModel(QlShortRateModel *o);
  void qlFreeAffineModel(QlAffineModel *o);
  void qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o);
  QlAffineModel* qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o);
  void qlFreeLiborForwardModel(QlLiborForwardModel *o);
  QlAffineModel* qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o);
  void qlFreeHullWhite(QlHullWhite *o);
  QlOneFactorAffineModel* qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o);
  void qlFreeCalibratedModel(QlCalibratedModel *o);
//  QlBatesModel* qlBatesModel(QlBatesProcess* process, char **e);
//  QlShortRateModel* qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, char **e);
//  QlOneFactorAffineModel* qlCoxIngersollRoss(double r0, double theta, double k, double sigma, char **e);
//  QlOneFactorAffineModel* qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, char **e);
//  QlG2* qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, char **e);
//  QlShortRateModel* qlGeneralizedHullWhite1(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, char **e);
//  QlShortRateModel* qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, char **e);
//  QlGJRGARCHModel* qlGJRGARCHModel(QlGJRGARCHProcess* process, char **e);
//  QlHestonModel* qlHestonModel(QlHestonProcess* process, char **e);
//  QlHullWhite* qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, char **e);
//  QlCalibratedModel* qlVarianceGammaModel(QlVarianceGammaProcess* process, char **e);
//  QlOneFactorAffineModel* qlVasicek(double r0, double a, double b, double sigma, double lambda, char **e);
  void qlFreeG2(QlG2 *o);
  QlAffineModel* qlG2AsAffineModel(QlG2 *o);
  QlShortRateModel* qlG2AsShortRateModel(QlG2 *o);
  void qlFreeBatesDetJumpModel(QlBatesDetJumpModel *o);
  QlBatesModel* qlBatesDetJumpModelAsBatesModel(QlBatesDetJumpModel *o);
  void qlFreeBatesDoubleExpDetJumpModel(QlBatesDoubleExpDetJumpModel *o);
  QlBatesDoubleExpModel* qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel(QlBatesDoubleExpDetJumpModel *o);
  void qlFreeBatesDoubleExpModel(QlBatesDoubleExpModel *o);
  QlHestonModel* qlBatesDoubleExpModelAsHestonModel(QlBatesDoubleExpModel *o);

  void qlFreeLmCorrelationModel(QlLmCorrelationModel *o);
  void qlFreeLmVolatilityModel(QlLmVolatilityModel *o);
//  QlLmCorrelationModel* qlLmConstWrapperCorrelationModel(QlLmCorrelationModel* corrModel, char **e);
//  QlLmVolatilityModel* qlLmConstWrapperVolatilityModel(QlLmVolatilityModel* volaModel, char **e);
//  QlLmCorrelationModel* qlLmExponentialCorrelationModel(unsigned size, double rho, char **e);
//  QlLmVolatilityModel* qlLmFixedVolatilityModel(unsigned volatilitiesLen, double* volatilities, unsigned startTimesLen, double * startTimes, char **e);
//  QlLmCorrelationModel* qlLmLinearExponentialCorrelationModel(unsigned size, double rho, double beta, unsigned factors, char **e);
//  QlLmVolatilityModel* qlLmLinearExponentialVolatilityModel(unsigned fixingTimesLen, double * fixingTimes, double a, double b, double c, double d, char **e);
//  QlLiborForwardModel* qlLiborForwardModel(QlLiborForwardModelProcess* process, QlLmVolatilityModel* volaModel, QlLmCorrelationModel* corrModel, char **e);

  QlCalibratedModel* qlGJRGARCHModelAsCalibratedModel(QlGJRGARCHModel *o);
  QlCalibratedModel* qlHestonModelAsCalibratedModel(QlHestonModel *o);
  QlHestonModel* qlBatesModelAsHestonModel(QlBatesModel *o);
  QlCalibratedModel* qlLiborForwardModelAsCalibratedModel(QlLiborForwardModel *o);
  QlCalibratedModel* qlPiecewiseTimeDependentHestonModelAsCalibratedModel(QlPiecewiseTimeDependentHestonModel *o);
  QlCalibratedModel* qlShortRateModelAsCalibratedModel(QlShortRateModel *o);
  QlShortRateModel* qlOneFactorAffineModelAsShortRateModel(QlOneFactorAffineModel *o);

  void qlFreeCalibrationHelper(QlCalibrationHelper *o);
//  void qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, double *weights, OptimizationMethod* method, EndCriteria* endCriteria, Constraint* constraint, char **e);
//  void qlCalibrationHelperSetPricingEngine(QlCalibrationHelper* o, QlPricingEngine* engine, char **e);
//  QlCalibrationHelper* qlCapHelper(int, int, QlQuote* volatility, QlIborIndex* index, int fixedLegFrequency, DayCounter* fixedLegDayCounter, int includeFirstSwaplet, QlYieldTermStructure* termStructure, int errorType, char **e);
//  QlCalibrationHelper* qlHestonModelHelper(int, int, Calendar* calendar, double s0, double strikePrice, QlQuote* volatility, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int errorType, char **e);
//  QlCalibrationHelper* qlSwaptionHelper(int, int, int, int, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, char **e);
//  double* qlCalibrationHelperTimes(QlCalibrationHelper* o, unsigned *len, char **e);
//
//  double* qlCalibratedModelParams(QlCalibratedModel* o, unsigned *len, char **e);
//  double qlCalibrationHelperBlackPrice(QlCalibrationHelper* o, double volatility, char **e);
//  double qlCalibrationHelperCalibrationError(QlCalibrationHelper* o, char **e);
//  double qlCalibrationHelperImpliedVolatility(QlCalibrationHelper* o, double targetValue, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
//  double qlCalibrationHelperMarketValue(QlCalibrationHelper* o, char **e);
//  double qlCalibrationHelperModelValue(QlCalibrationHelper* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
