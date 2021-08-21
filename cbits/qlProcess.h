#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeBlackProcess(QlBlackProcess *o);
  QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o);
  void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o);
  QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o);
  void qlFreeStochasticProcess(QlStochasticProcess *o);
  void qlFreeStochasticProcess1D(QlStochasticProcess1D *o);
  QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o);

  QlBlackProcess* qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e);
  QlGeneralizedBlackScholesProcess* qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e);
  QlGeneralizedBlackScholesProcess* qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e);
  QlGeneralizedBlackScholesProcess* qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int evolDisc, char **e);
  QlGeneralizedBlackScholesProcess* qlGarmanKohlagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e);
  QlGeneralizedBlackScholesProcess* qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e);
  QlStochasticProcess1D* qlSquareRootProcess(double b, double a, double sigma, double x0, int d, char **e);
  QlGeneralizedBlackScholesProcess* qlVegaStressedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, double lowerTimeBorderForStressTest, double upperTimeBorderForStressTest, double lowerAssetBorderForStressTest, double upperAssetBorderForStressTest, double stressLevel, int d, char **e);

  void qlFreeExtOUWithJumpsProcess(QlExtOUWithJumpsProcess *o);
  QlStochasticProcess* qlExtOUWithJumpsProcessAsStochasticProcess(QlExtOUWithJumpsProcess *o);
  void qlFreeExtendedOrnsteinUhlenbeckProcess(QlExtendedOrnsteinUhlenbeckProcess *o);
  QlStochasticProcess1D* qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D(QlExtendedOrnsteinUhlenbeckProcess *o);
  void qlFreeGJRGARCHProcess(QlGJRGARCHProcess *o);
  QlStochasticProcess* qlGJRGARCHProcessAsStochasticProcess(QlGJRGARCHProcess *o);
  void qlFreeHestonProcess(QlHestonProcess *o);
  QlStochasticProcess* qlHestonProcessAsStochasticProcess(QlHestonProcess *o);
  void qlFreeBatesProcess(QlBatesProcess *o);
  QlHestonProcess* qlBatesProcessAsHestonProcess(QlBatesProcess *o);
  void qlFreeHybridHestonHullWhiteProcess(QlHybridHestonHullWhiteProcess *o);
  QlStochasticProcess* qlHybridHestonHullWhiteProcessAsStochasticProcess(QlHybridHestonHullWhiteProcess *o);
  void qlFreeKlugeExtOUProcess(QlKlugeExtOUProcess *o);
  QlStochasticProcess* qlKlugeExtOUProcessAsStochasticProcess(QlKlugeExtOUProcess *o);
  void qlFreeLiborForwardModelProcess(QlLiborForwardModelProcess *o);
  QlStochasticProcess* qlLiborForwardModelProcessAsStochasticProcess(QlLiborForwardModelProcess *o);
  void qlFreeStochasticProcessArray(QlStochasticProcessArray *o);
  QlStochasticProcess* qlStochasticProcessArrayAsStochasticProcess(QlStochasticProcessArray *o);
  void qlFreeVarianceGammaProcess(QlVarianceGammaProcess *o);
  QlStochasticProcess1D* qlVarianceGammaProcessAsStochasticProcess1D(QlVarianceGammaProcess *o);
  void qlFreeMerton76Process(QlMerton76Process *o);
  QlStochasticProcess1D* qlMerton76ProcessAsStochasticProcess1D(QlMerton76Process *o);
  void qlFreeHullWhiteProcess(QlHullWhiteProcess *o);
  QlStochasticProcess1D* qlHullWhiteProcessAsStochasticProcess1D(QlHullWhiteProcess *o);
  void qlFreeHullWhiteForwardProcess(QlHullWhiteForwardProcess *o);
  QlStochasticProcess1D* qlHullWhiteForwardProcessAsStochasticProcess1D(QlHullWhiteForwardProcess *o);

  QlBatesProcess* qlBatesProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, double lambda, double nu, double delta, int d, char **e);
  QlExtOUWithJumpsProcess* qlExtOUWithJumpsProcess(QlExtendedOrnsteinUhlenbeckProcess* process, double Y0, double beta, double jumpIntensity, double eta, char **e);
  QlStochasticProcess* qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, char **e);
  QlStochasticProcess* qlG2Process(double a, double sigma, double b, double eta, double rho, char **e);
  QlStochasticProcess1D* qlGemanRoncoroniProcess(double x0, double alpha, double beta, double gamma, double delta, double eps, double zeta, double d, double k, double tau, double sig2, double a, double b, double theta1, double theta2, double theta3, double psi, char **e);
  QlStochasticProcess1D* qlGeometricBrownianMotionProcess(double initialValue, double mue, double sigma, char **e);
  QlGJRGARCHProcess* qlGJRGARCHProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double omega, double alpha, double beta, double gamma, double lambda, double daysPerYear, int d, char **e);
  QlHestonProcess* qlHestonProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, int d, char **e);
  QlHullWhiteForwardProcess* qlHullWhiteForwardProcess(QlYieldTermStructure* h, double a, double sigma, char **e);
  QlHullWhiteProcess* qlHullWhiteProcess(QlYieldTermStructure* h, double a, double sigma, char **e);
  QlHybridHestonHullWhiteProcess* qlHybridHestonHullWhiteProcess(QlHestonProcess* hestonProcess, QlHullWhiteForwardProcess* hullWhiteProcess, double corrEquityShortRate, int discretization, char **e);
  QlKlugeExtOUProcess* qlKlugeExtOUProcess(double rho, QlExtOUWithJumpsProcess* kluge, QlExtendedOrnsteinUhlenbeckProcess* extOU, char **e);
  QlLiborForwardModelProcess* qlLiborForwardModelProcess(unsigned size, QlIborIndex* index, char **e);
  QlMerton76Process* qlMerton76Process(QlQuote* stateVariable, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, QlQuote* jumpInt, QlQuote* logJMean, QlQuote* logJVol, int d, char **e);
  QlStochasticProcess1D* qlOrnsteinUhlenbeckProcess(double speed, double vol, double x0, double level, char **e);
  QlVarianceGammaProcess* qlVarianceGammaProcess(QlQuote* s0, QlYieldTermStructure* dividendYield, QlYieldTermStructure* riskFreeRate, double sigma, double nu, double theta, char **e);
  QlStochasticProcessArray* qlStochasticProcessArray(unsigned x0Len, QlStochasticProcess1D** x0, unsigned correlationRows, unsigned correlationCols, double* correlation, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
