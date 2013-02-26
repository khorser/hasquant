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
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
