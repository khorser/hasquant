#include <ql/processes/all.hpp>
#include <ql/experimental/processes/all.hpp>
#include <ql/experimental/variancegamma/all.hpp>
#include <ql/legacy/libormarketmodels/lfmprocess.hpp>

#include "qlaux.h"
#include "qlProcess.h"

namespace hasquant {
#include "qlEnumObjects.h"
};

using namespace QuantLib;

shared_ptr<StochasticProcess::discretization> createDiscretization(int n) {
  switch (n) {
  case hasquant::EulerDiscretization:
    return shared_ptr<StochasticProcess::discretization>(new EulerDiscretization());
  case hasquant::EndEulerDiscretization:
    return shared_ptr<StochasticProcess::discretization>(new EndEulerDiscretization());
  default:
      QL_FAIL("Invalid discretization: " << n);
  }
}

shared_ptr<StochasticProcess1D::discretization> createDiscretization1D(int n) {
  switch (n) {
  case hasquant::EulerDiscretization:
    return shared_ptr<StochasticProcess1D::discretization>(new EulerDiscretization());
  case hasquant::EndEulerDiscretization:
    return shared_ptr<StochasticProcess1D::discretization>(new EndEulerDiscretization());
  default:
    QL_FAIL("Invalid discretization: " << n);
  }
}

void qlFreeStochasticProcess1D(QlStochasticProcess1D *o) {del(o);}
QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeBlackProcess(QlBlackProcess *o) {del(o);}
QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o) {return ret(new QlGeneralizedBlackScholesProcess(*arg(o)));}
void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o) {del(o);}
QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeStochasticProcess(QlStochasticProcess *o) {del(o);}

QlBlackProcess* qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e) {
  try {
    return ret(new QlBlackProcess(alloc(new BlackProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlBlackProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new BlackScholesMertonProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new BlackScholesProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int evolDisc, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new ExtendedBlackScholesMertonProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(d), (ExtendedBlackScholesMertonProcess::Discretization)evolDisc))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlGarmanKohlagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new GarmanKohlagenProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(foreignRiskFreeTS)), Handle<YieldTermStructure>(*arg(domesticRiskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new GeneralizedBlackScholesProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlStochasticProcess1D* qlSquareRootProcess(double b, double a, double sigma, double x0, int d, char **e) {
  try {
    return ret(new QlStochasticProcess1D(alloc(new SquareRootProcess(b, a, sigma, x0, createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess1D*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlVegaStressedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, double lowerTimeBorderForStressTest, double upperTimeBorderForStressTest, double lowerAssetBorderForStressTest, double upperAssetBorderForStressTest, double stressLevel, int d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new VegaStressedBlackScholesProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), lowerTimeBorderForStressTest, upperTimeBorderForStressTest, lowerAssetBorderForStressTest, upperAssetBorderForStressTest, stressLevel, createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}

void qlFreeExtOUWithJumpsProcess(QlExtOUWithJumpsProcess *o) {del(o);}
QlStochasticProcess* qlExtOUWithJumpsProcessAsStochasticProcess(QlExtOUWithJumpsProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeExtendedOrnsteinUhlenbeckProcess(QlExtendedOrnsteinUhlenbeckProcess *o) {del(o);}
QlStochasticProcess1D* qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D(QlExtendedOrnsteinUhlenbeckProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeGJRGARCHProcess(QlGJRGARCHProcess *o) {del(o);}
QlStochasticProcess* qlGJRGARCHProcessAsStochasticProcess(QlGJRGARCHProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeHestonProcess(QlHestonProcess *o) {del(o);}
QlStochasticProcess* qlHestonProcessAsStochasticProcess(QlHestonProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeBatesProcess(QlBatesProcess *o) {del(o);}
QlHestonProcess* qlBatesProcessAsHestonProcess(QlBatesProcess *o) {return ret(new QlHestonProcess(*arg(o)));}
void qlFreeHybridHestonHullWhiteProcess(QlHybridHestonHullWhiteProcess *o) {del(o);}
QlStochasticProcess* qlHybridHestonHullWhiteProcessAsStochasticProcess(QlHybridHestonHullWhiteProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeKlugeExtOUProcess(QlKlugeExtOUProcess *o) {del(o);}
QlStochasticProcess* qlKlugeExtOUProcessAsStochasticProcess(QlKlugeExtOUProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeLiborForwardModelProcess(QlLiborForwardModelProcess *o) {del(o);}
QlStochasticProcess* qlLiborForwardModelProcessAsStochasticProcess(QlLiborForwardModelProcess *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeStochasticProcessArray(QlStochasticProcessArray *o) {del(o);}
QlStochasticProcess* qlStochasticProcessArrayAsStochasticProcess(QlStochasticProcessArray *o) {return ret(new QlStochasticProcess(*arg(o)));}
void qlFreeVarianceGammaProcess(QlVarianceGammaProcess *o) {del(o);}
QlStochasticProcess1D* qlVarianceGammaProcessAsStochasticProcess1D(QlVarianceGammaProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeMerton76Process(QlMerton76Process *o) {del(o);}
QlStochasticProcess1D* qlMerton76ProcessAsStochasticProcess1D(QlMerton76Process *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeHullWhiteProcess(QlHullWhiteProcess *o) {del(o);}
QlStochasticProcess1D* qlHullWhiteProcessAsStochasticProcess1D(QlHullWhiteProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}
void qlFreeHullWhiteForwardProcess(QlHullWhiteForwardProcess *o) {del(o);}
QlStochasticProcess1D* qlHullWhiteForwardProcessAsStochasticProcess1D(QlHullWhiteForwardProcess *o) {return ret(new QlStochasticProcess1D(*arg(o)));}

QlBatesProcess* qlBatesProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, double lambda, double nu, double delta, int d, char **e) {
  try {
    return ret(new QlBatesProcess(alloc(new BatesProcess(Handle<YieldTermStructure>(*arg(riskFreeRate)), Handle<YieldTermStructure>(*arg(dividendYield)), Handle<Quote>(*arg(s0)), v0, kappa, theta, sigma, rho, lambda, nu, delta, (HestonProcess::Discretization)d))));
  } catch (std::exception& er) {
    return handleException<QlBatesProcess*>(e, er);
  }
}
QlExtOUWithJumpsProcess* qlExtOUWithJumpsProcess(QlExtendedOrnsteinUhlenbeckProcess* process, double Y0, double beta, double jumpIntensity, double eta, char **e) {
  try {
    return ret(new QlExtOUWithJumpsProcess(alloc(new ExtOUWithJumpsProcess(*arg(process), Y0, beta, jumpIntensity, eta))));
  } catch (std::exception& er) {
    return handleException<QlExtOUWithJumpsProcess*>(e, er);
  }
}
QlStochasticProcess* qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, char **e) {
  try {
    return ret(new QlStochasticProcess(alloc(new G2ForwardProcess(a, sigma, b, eta, rho))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess*>(e, er);
  }
}
QlStochasticProcess* qlG2Process(double a, double sigma, double b, double eta, double rho, char **e) {
  try {
    return ret(new QlStochasticProcess(alloc(new G2Process(a, sigma, b, eta, rho))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess*>(e, er);
  }
}
QlStochasticProcess1D* qlGemanRoncoroniProcess(double x0, double alpha, double beta, double gamma, double delta, double eps, double zeta, double d, double k, double tau, double sig2, double a, double b, double theta1, double theta2, double theta3, double psi, char **e) {
  try {
    return ret(new QlStochasticProcess1D(alloc(new GemanRoncoroniProcess(x0, alpha, beta, gamma, delta, eps, zeta, d, k, tau, sig2, a, b, theta1, theta2, theta3, psi))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess1D*>(e, er);
  }
}
QlStochasticProcess1D* qlGeometricBrownianMotionProcess(double initialValue, double mue, double sigma, char **e) {
  try {
    return ret(new QlStochasticProcess1D(alloc(new GeometricBrownianMotionProcess(initialValue, mue, sigma))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess1D*>(e, er);
  }
}
QlGJRGARCHProcess* qlGJRGARCHProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double omega, double alpha, double beta, double gamma, double lambda, double daysPerYear, int d, char **e) {
  try {
    return ret(new QlGJRGARCHProcess(alloc(new GJRGARCHProcess(Handle<YieldTermStructure>(*arg(riskFreeRate)), Handle<YieldTermStructure>(*arg(dividendYield)), Handle<Quote>(*arg(s0)), v0, omega, alpha, beta, gamma, lambda, daysPerYear, (GJRGARCHProcess::Discretization)d))));
  } catch (std::exception& er) {
    return handleException<QlGJRGARCHProcess*>(e, er);
  }
}
QlHestonProcess* qlHestonProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, int d, char **e) {
  try {
    return ret(new QlHestonProcess(alloc(new HestonProcess(Handle<YieldTermStructure>(*arg(riskFreeRate)), Handle<YieldTermStructure>(*arg(dividendYield)), Handle<Quote>(*arg(s0)), v0, kappa, theta, sigma, rho, (HestonProcess::Discretization)d))));
  } catch (std::exception& er) {
    return handleException<QlHestonProcess*>(e, er);
  }
}
QlHullWhiteForwardProcess* qlHullWhiteForwardProcess(QlYieldTermStructure* h, double a, double sigma, char **e) {
  try {
    return ret(new QlHullWhiteForwardProcess(alloc(new HullWhiteForwardProcess(Handle<YieldTermStructure>(*arg(h)), a, sigma))));
  } catch (std::exception& er) {
    return handleException<QlHullWhiteForwardProcess*>(e, er);
  }
}
QlHullWhiteProcess* qlHullWhiteProcess(QlYieldTermStructure* h, double a, double sigma, char **e) {
  try {
    return ret(new QlHullWhiteProcess(alloc(new HullWhiteProcess(Handle<YieldTermStructure>(*arg(h)), a, sigma))));
  } catch (std::exception& er) {
    return handleException<QlHullWhiteProcess*>(e, er);
  }
}
QlHybridHestonHullWhiteProcess* qlHybridHestonHullWhiteProcess(QlHestonProcess* hestonProcess, QlHullWhiteForwardProcess* hullWhiteProcess, double corrEquityShortRate, int discretization, char **e) {
  try {
    return ret(new QlHybridHestonHullWhiteProcess(alloc(new HybridHestonHullWhiteProcess(*arg(hestonProcess), *arg(hullWhiteProcess), corrEquityShortRate, (HybridHestonHullWhiteProcess::Discretization)discretization))));
  } catch (std::exception& er) {
    return handleException<QlHybridHestonHullWhiteProcess*>(e, er);
  }
}
QlKlugeExtOUProcess* qlKlugeExtOUProcess(double rho, QlExtOUWithJumpsProcess* kluge, QlExtendedOrnsteinUhlenbeckProcess* extOU, char **e) {
  try {
    return ret(new QlKlugeExtOUProcess(alloc(new KlugeExtOUProcess(rho, *arg(kluge), (*arg(extOU))))));
  } catch (std::exception& er) {
    return handleException<QlKlugeExtOUProcess*>(e, er);
  }
}
QlLiborForwardModelProcess* qlLiborForwardModelProcess(unsigned size, QlIborIndex* index, char **e) {
  try {
    return ret(new QlLiborForwardModelProcess(alloc(new LiborForwardModelProcess(size, (*arg(index))))));
  } catch (std::exception& er) {
    return handleException<QlLiborForwardModelProcess*>(e, er);
  }
}
QlMerton76Process* qlMerton76Process(QlQuote* stateVariable, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, QlQuote* jumpInt, QlQuote* logJMean, QlQuote* logJVol, int d, char **e) {
  try {
    return ret(new QlMerton76Process(alloc(new Merton76Process(Handle<Quote>(*arg(stateVariable)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), Handle<Quote>(*arg(jumpInt)), Handle<Quote>(*arg(logJMean)), Handle<Quote>(*arg(logJVol)), createDiscretization1D(d)))));
  } catch (std::exception& er) {
    return handleException<QlMerton76Process*>(e, er);
  }
}
QlStochasticProcess1D* qlOrnsteinUhlenbeckProcess(double speed, double vol, double x0, double level, char **e) {
  try {
    return ret(new QlStochasticProcess1D(alloc(new OrnsteinUhlenbeckProcess(speed, vol, x0, level))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess1D*>(e, er);
  }
}
QlVarianceGammaProcess* qlVarianceGammaProcess(QlQuote* s0, QlYieldTermStructure* dividendYield, QlYieldTermStructure* riskFreeRate, double sigma, double nu, double theta, char **e) {
  try {
    return ret(new QlVarianceGammaProcess(alloc(new VarianceGammaProcess(Handle<Quote>(*arg(s0)), Handle<YieldTermStructure>(*arg(dividendYield)), Handle<YieldTermStructure>(*arg(riskFreeRate)), sigma, nu, theta))));
  } catch (std::exception& er) {
    return handleException<QlVarianceGammaProcess*>(e, er);
  }
}

QlStochasticProcessArray* qlStochasticProcessArray(unsigned x0Len, QlStochasticProcess1D** x0, unsigned correlationRows, unsigned correlationCols, double* correlation, char **e) {
  try {
    return ret(new QlStochasticProcessArray(alloc(new StochasticProcessArray(qlBuildVector(x0, x0Len), qlBuildMatrix(correlation, correlationRows, correlationCols)))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcessArray*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
