#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  void DLLEXPORT qlFreeBlackProcess(QlBlackProcess *o);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o);
  void DLLEXPORT qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o);
  QlStochasticProcess1D* DLLEXPORT qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o);
  void DLLEXPORT qlFreeStochasticProcess(QlStochasticProcess *o);
  void DLLEXPORT qlFreeStochasticProcess1D(QlStochasticProcess1D *o);
  QlStochasticProcess* DLLEXPORT qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o);

  QlBlackProcess* DLLEXPORT qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, int evolDisc, char **e);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlGarmanKohlagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e);
  QlStochasticProcess1D* DLLEXPORT qlSquareRootProcess(double b, double a, double sigma, double x0, char*  d, char **e);
  QlGeneralizedBlackScholesProcess* DLLEXPORT qlVegaStressedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, double lowerTimeBorderForStressTest, double upperTimeBorderForStressTest, double lowerAssetBorderForStressTest, double upperAssetBorderForStressTest, double stressLevel, char*  d, char **e);

  void DLLEXPORT qlFreeExtOUWithJumpsProcess(QlExtOUWithJumpsProcess *o);
  QlStochasticProcess* DLLEXPORT qlExtOUWithJumpsProcessAsStochasticProcess(QlExtOUWithJumpsProcess *o);
  void DLLEXPORT qlFreeExtendedOrnsteinUhlenbeckProcess(QlExtendedOrnsteinUhlenbeckProcess *o);
  QlStochasticProcess1D* DLLEXPORT qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D(QlExtendedOrnsteinUhlenbeckProcess *o);
  void DLLEXPORT qlFreeGJRGARCHProcess(QlGJRGARCHProcess *o);
  QlStochasticProcess* DLLEXPORT qlGJRGARCHProcessAsStochasticProcess(QlGJRGARCHProcess *o);
  void DLLEXPORT qlFreeHestonProcess(QlHestonProcess *o);
  QlStochasticProcess* DLLEXPORT qlHestonProcessAsStochasticProcess(QlHestonProcess *o);
  void DLLEXPORT qlFreeBatesProcess(QlBatesProcess *o);
  QlHestonProcess* DLLEXPORT qlBatesProcessAsHestonProcess(QlBatesProcess *o);
  void DLLEXPORT qlFreeHybridHestonHullWhiteProcess(QlHybridHestonHullWhiteProcess *o);
  QlStochasticProcess* DLLEXPORT qlHybridHestonHullWhiteProcessAsStochasticProcess(QlHybridHestonHullWhiteProcess *o);
  void DLLEXPORT qlFreeKlugeExtOUProcess(QlKlugeExtOUProcess *o);
  QlStochasticProcess* DLLEXPORT qlKlugeExtOUProcessAsStochasticProcess(QlKlugeExtOUProcess *o);
  void DLLEXPORT qlFreeLiborForwardModelProcess(QlLiborForwardModelProcess *o);
  QlStochasticProcess* DLLEXPORT qlLiborForwardModelProcessAsStochasticProcess(QlLiborForwardModelProcess *o);
  void DLLEXPORT qlFreeStochasticProcessArray(QlStochasticProcessArray *o);
  QlStochasticProcess* DLLEXPORT qlStochasticProcessArrayAsStochasticProcess(QlStochasticProcessArray *o);
  void DLLEXPORT qlFreeVarianceGammaProcess(QlVarianceGammaProcess *o);
  QlStochasticProcess1D* DLLEXPORT qlVarianceGammaProcessAsStochasticProcess1D(QlVarianceGammaProcess *o);
  void DLLEXPORT qlFreeMerton76Process(QlMerton76Process *o);
  QlStochasticProcess1D* DLLEXPORT qlMerton76ProcessAsStochasticProcess1D(QlMerton76Process *o);
  void DLLEXPORT qlFreeHullWhiteProcess(QlHullWhiteProcess *o);
  QlStochasticProcess1D* DLLEXPORT qlHullWhiteProcessAsStochasticProcess1D(QlHullWhiteProcess *o);
  void DLLEXPORT qlFreeHullWhiteForwardProcess(QlHullWhiteForwardProcess *o);
  QlStochasticProcess1D* DLLEXPORT qlHullWhiteForwardProcessAsStochasticProcess1D(QlHullWhiteForwardProcess *o);

  QlBatesProcess* DLLEXPORT qlBatesProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, double lambda, double nu, double delta, int d, char **e);
  QlExtOUWithJumpsProcess* DLLEXPORT qlExtOUWithJumpsProcess(QlExtendedOrnsteinUhlenbeckProcess* process, double Y0, double beta, double jumpIntensity, double eta, char **e);
  QlStochasticProcess* DLLEXPORT qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, char **e);
  QlStochasticProcess* DLLEXPORT qlG2Process(double a, double sigma, double b, double eta, double rho, char **e);
  QlStochasticProcess1D* DLLEXPORT qlGemanRoncoroniProcess(double x0, double alpha, double beta, double gamma, double delta, double eps, double zeta, double d, double k, double tau, double sig2, double a, double b, double theta1, double theta2, double theta3, double psi, char **e);
  QlStochasticProcess1D* DLLEXPORT qlGeometricBrownianMotionProcess(double initialValue, double mue, double sigma, char **e);
  QlGJRGARCHProcess* DLLEXPORT qlGJRGARCHProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double omega, double alpha, double beta, double gamma, double lambda, double daysPerYear, int d, char **e);
  QlHestonProcess* DLLEXPORT qlHestonProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, int d, char **e);
  QlHullWhiteForwardProcess* DLLEXPORT qlHullWhiteForwardProcess(QlYieldTermStructure* h, double a, double sigma, char **e);
  QlHullWhiteProcess* DLLEXPORT qlHullWhiteProcess(QlYieldTermStructure* h, double a, double sigma, char **e);
  QlHybridHestonHullWhiteProcess* DLLEXPORT qlHybridHestonHullWhiteProcess(QlHestonProcess* hestonProcess, QlHullWhiteForwardProcess* hullWhiteProcess, double corrEquityShortRate, int discretization, char **e);
  QlKlugeExtOUProcess* DLLEXPORT qlKlugeExtOUProcess(double rho, QlExtOUWithJumpsProcess* kluge, QlExtendedOrnsteinUhlenbeckProcess* extOU, char **e);
  QlLiborForwardModelProcess* DLLEXPORT qlLiborForwardModelProcess(unsigned size, QlIborIndex* index, char **e);
  QlMerton76Process* DLLEXPORT qlMerton76Process(QlQuote* stateVariable, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, QlQuote* jumpInt, QlQuote* logJMean, QlQuote* logJVol, char*  d, char **e);
  QlStochasticProcess1D* DLLEXPORT qlOrnsteinUhlenbeckProcess(double speed, double vol, double x0, double level, char **e);
  QlVarianceGammaProcess* DLLEXPORT qlVarianceGammaProcess(QlQuote* s0, QlYieldTermStructure* dividendYield, QlYieldTermStructure* riskFreeRate, double sigma, double nu, double theta, char **e);
}
