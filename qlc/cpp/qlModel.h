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
  void DLLEXPORT qlFreeGJRGARCHModel(QlGJRGARCHModel *o);
  void DLLEXPORT qlFreeHestonModel(QlHestonModel *o);
  void DLLEXPORT qlFreeBatesModel(QlBatesModel *o);
  void DLLEXPORT qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o);
  void DLLEXPORT qlFreeShortRateModel(QlShortRateModel *o);
  void DLLEXPORT qlFreeAffineModel(QlAffineModel *o);
  void DLLEXPORT qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o);
  QlAffineModel* DLLEXPORT qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o);
  void DLLEXPORT qlFreeLiborForwardModel(QlLiborForwardModel *o);
  QlAffineModel* DLLEXPORT qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o);
  void DLLEXPORT qlFreeHullWhite(QlHullWhite *o);
  QlOneFactorAffineModel* DLLEXPORT qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o);
  void DLLEXPORT qlFreeCalibratedModel(QlCalibratedModel *o);
  QlBatesModel* DLLEXPORT qlBatesModel(QlBatesProcess* process, char **e);
  QlShortRateModel* DLLEXPORT qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, char **e);
  QlOneFactorAffineModel* DLLEXPORT qlCoxIngersollRoss(double r0, double theta, double k, double sigma, char **e);
  QlOneFactorAffineModel* DLLEXPORT qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, char **e);
  QlG2* DLLEXPORT qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, char **e);
  QlShortRateModel* DLLEXPORT qlGeneralizedHullWhite1(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, char **e);
  QlShortRateModel* DLLEXPORT qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, char **e);
  QlGJRGARCHModel* DLLEXPORT qlGJRGARCHModel(QlGJRGARCHProcess* process, char **e);
  QlHestonModel* DLLEXPORT qlHestonModel(QlHestonProcess* process, char **e);
  QlHullWhite* DLLEXPORT qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, char **e);
  QlCalibratedModel* DLLEXPORT qlVarianceGammaModel(QlVarianceGammaProcess* process, char **e);
  QlOneFactorAffineModel* DLLEXPORT qlVasicek(double r0, double a, double b, double sigma, double lambda, char **e);
  void DLLEXPORT qlFreeG2(QlG2 *o);
  QlAffineModel* DLLEXPORT qlG2AsAffineModel(QlG2 *o);
  QlShortRateModel* DLLEXPORT qlG2AsShortRateModel(QlG2 *o);
  void DLLEXPORT qlFreeBatesDetJumpModel(QlBatesDetJumpModel *o);
  QlBatesModel* DLLEXPORT qlBatesDetJumpModelAsBatesModel(QlBatesDetJumpModel *o);
  void DLLEXPORT qlFreeBatesDoubleExpDetJumpModel(QlBatesDoubleExpDetJumpModel *o);
  QlBatesDoubleExpModel* DLLEXPORT qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel(QlBatesDoubleExpDetJumpModel *o);
  void DLLEXPORT qlFreeBatesDoubleExpModel(QlBatesDoubleExpModel *o);
  QlHestonModel* DLLEXPORT qlBatesDoubleExpModelAsHestonModel(QlBatesDoubleExpModel *o);

  void DLLEXPORT qlFreeLmCorrelationModel(QlLmCorrelationModel *o);
  void DLLEXPORT qlFreeLmVolatilityModel(QlLmVolatilityModel *o);
  QlLmCorrelationModel* DLLEXPORT qlLmConstWrapperCorrelationModel(QlLmCorrelationModel* corrModel, char **e);
  QlLmVolatilityModel* DLLEXPORT qlLmConstWrapperVolatilityModel(QlLmVolatilityModel* volaModel, char **e);
  QlLmCorrelationModel* DLLEXPORT qlLmExponentialCorrelationModel(unsigned size, double rho, char **e);
  QlLmVolatilityModel* DLLEXPORT qlLmFixedVolatilityModel(unsigned volatilitiesLen, double* volatilities, unsigned startTimesLen, double * startTimes, char **e);
  QlLmCorrelationModel* DLLEXPORT qlLmLinearExponentialCorrelationModel(unsigned size, double rho, double beta, unsigned factors, char **e);
  QlLmVolatilityModel* DLLEXPORT qlLmLinearExponentialVolatilityModel(unsigned fixingTimesLen, double * fixingTimes, double a, double b, double c, double d, char **e);
  QlLiborForwardModel* DLLEXPORT qlLiborForwardModel(QlLiborForwardModelProcess* process, QlLmVolatilityModel* volaModel, QlLmCorrelationModel* corrModel, char **e);

  QlCalibratedModel* DLLEXPORT qlGJRGARCHModelAsCalibratedModel(QlGJRGARCHModel *o);
  QlCalibratedModel* DLLEXPORT qlHestonModelAsCalibratedModel(QlHestonModel *o);
  QlHestonModel* DLLEXPORT qlBatesModelAsHestonModel(QlBatesModel *o);
  QlCalibratedModel* DLLEXPORT qlLiborForwardModelAsCalibratedModel(QlLiborForwardModel *o);
  QlCalibratedModel* DLLEXPORT qlPiecewiseTimeDependentHestonModelAsCalibratedModel(QlPiecewiseTimeDependentHestonModel *o);
  QlCalibratedModel* DLLEXPORT qlShortRateModelAsCalibratedModel(QlShortRateModel *o);
  QlShortRateModel* DLLEXPORT qlOneFactorAffineModelAsShortRateModel(QlOneFactorAffineModel *o);

  void DLLEXPORT qlFreeCalibrationHelper(QlCalibrationHelper *o);
  void DLLEXPORT qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, double *weights, OptimizationMethod* method, EndCriteria* endCriteria, Constraint* constraint, char **e);
  void DLLEXPORT qlCalibrationHelperSetPricingEngine(QlCalibrationHelper* o, QlPricingEngine* engine, char **e);
  QlCalibrationHelper* DLLEXPORT qlCapHelper(Period* length, QlQuote* volatility, QlIborIndex* index, int fixedLegFrequency, DayCounter* fixedLegDayCounter, int includeFirstSwaplet, QlYieldTermStructure* termStructure, int errorType, char **e);
  QlCalibrationHelper* DLLEXPORT qlHestonModelHelper(Period* maturity, Calendar* calendar, double s0, double strikePrice, QlQuote* volatility, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int errorType, char **e);
  QlCalibrationHelper* DLLEXPORT qlSwaptionHelper(Period* maturity, Period* length, QlQuote* volatility, QlIborIndex* index, Period* fixedLegTenor, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
