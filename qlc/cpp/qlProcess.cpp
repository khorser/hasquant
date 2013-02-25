#include <ql/processes/all.hpp>
#include <ql/experimental/processes/all.hpp>
#include <ql/experimental/variancegamma/all.hpp>
#include <ql/legacy/libormarketmodels/lfmprocess.hpp>

#include "qlaux.h"

using namespace QuantLib;

boost::shared_ptr<StochasticProcess::discretization> createDiscretization(char *n) {
  if (!strcmp(n, "EulerDiscretization"))
    return boost::shared_ptr<StochasticProcess::discretization>(new EulerDiscretization());
  else if (!strcmp(n, "EndEulerDiscretization"))
    return boost::shared_ptr<StochasticProcess::discretization>(new EndEulerDiscretization());
  else
    QL_FAIL("Invalid discretization: " << n);
}

boost::shared_ptr<StochasticProcess1D::discretization> createDiscretization1D(char *n) {
  if (!strcmp(n, "EulerDiscretization"))
    return boost::shared_ptr<StochasticProcess1D::discretization>(new EulerDiscretization());
  else if (!strcmp(n, "EndEulerDiscretization"))
    return boost::shared_ptr<StochasticProcess1D::discretization>(new EndEulerDiscretization());
  else
    QL_FAIL("Invalid discretization: " << n);
}

void qlFreeStochasticProcess1D(QlStochasticProcess1D *o) { del(o); }
QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeBlackProcess(QlBlackProcess *o) { del(o); }
QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o) { return ret(new QlGeneralizedBlackScholesProcess(*arg(o))); }
void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o) { del(o); }
QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o) { return ret(new QlStochasticProcess1D(*arg(o))); }
void qlFreeStochasticProcess(QlStochasticProcess *o) { del(o); }

QlBlackProcess* qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e) {
  try {
    return ret(new QlBlackProcess(alloc(new BlackProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlBlackProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new BlackScholesMertonProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new BlackScholesProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, int evolDisc, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new ExtendedBlackScholesMertonProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(arg(d)), (ExtendedBlackScholesMertonProcess::Discretization)evolDisc))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlGarmanKohlagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new GarmanKohlagenProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(foreignRiskFreeTS)), Handle<YieldTermStructure>(*arg(domesticRiskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, char*  d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new GeneralizedBlackScholesProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}
QlStochasticProcess1D* qlSquareRootProcess(double b, double a, double sigma, double x0, char*  d, char **e) {
  try {
    return ret(new QlStochasticProcess1D(alloc(new SquareRootProcess(b, a, sigma, x0, createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlStochasticProcess1D*>(e, er);
  }
}
QlGeneralizedBlackScholesProcess* qlVegaStressedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, double lowerTimeBorderForStressTest, double upperTimeBorderForStressTest, double lowerAssetBorderForStressTest, double upperAssetBorderForStressTest, double stressLevel, char*  d, char **e) {
  try {
    return ret(new QlGeneralizedBlackScholesProcess(alloc(new VegaStressedBlackScholesProcess(Handle<Quote>(*arg(x0)), Handle<YieldTermStructure>(*arg(dividendTS)), Handle<YieldTermStructure>(*arg(riskFreeTS)), Handle<BlackVolTermStructure>(*arg(blackVolTS)), lowerTimeBorderForStressTest, upperTimeBorderForStressTest, lowerAssetBorderForStressTest, upperAssetBorderForStressTest, stressLevel, createDiscretization1D(arg(d))))));
  } catch (std::exception& er) {
    return handleException<QlGeneralizedBlackScholesProcess*>(e, er);
  }
}

void qlFreeExtOUWithJumpsProcess(QlExtOUWithJumpsProcess *o) { del(o); }
QlStochasticProcess* qlExtOUWithJumpsProcessAsStochasticProcess(QlExtOUWithJumpsProcess *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeExtendedOrnsteinUhlenbeckProcess(QlExtendedOrnsteinUhlenbeckProcess *o) { del(o); }
QlStochasticProcess1D* qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D(QlExtendedOrnsteinUhlenbeckProcess *o) { return ret(new QlStochasticProcess1D(*arg(o))); }
void qlFreeGJRGARCHProcess(QlGJRGARCHProcess *o) { del(o); }
QlStochasticProcess* qlGJRGARCHProcessAsStochasticProcess(QlGJRGARCHProcess *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeHestonProcess(QlHestonProcess *o) { del(o); }
QlStochasticProcess* qlHestonProcessAsStochasticProcess(QlHestonProcess *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeBatesProcess(QlBatesProcess *o) { del(o); }
QlHestonProcess* qlBatesProcessAsHestonProcess(QlBatesProcess *o) { return ret(new QlHestonProcess(*arg(o))); }
void qlFreeHybridHestonHullWhiteProcess(QlHybridHestonHullWhiteProcess *o) { del(o); }
QlStochasticProcess* qlHybridHestonHullWhiteProcessAsStochasticProcess(QlHybridHestonHullWhiteProcess *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeKlugeExtOUProcess(QlKlugeExtOUProcess *o) { del(o); }
QlStochasticProcess* qlKlugeExtOUProcessAsStochasticProcess(QlKlugeExtOUProcess *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeLiborForwardModelProcess(QlLiborForwardModelProcess *o) { del(o); }
QlStochasticProcess* qlLiborForwardModelProcessAsStochasticProcess(QlLiborForwardModelProcess *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeStochasticProcessArray(QlStochasticProcessArray *o) { del(o); }
QlStochasticProcess* qlStochasticProcessArrayAsStochasticProcess(QlStochasticProcessArray *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeVarianceGammaProcess(QlVarianceGammaProcess *o) { del(o); }
QlStochasticProcess1D* qlVarianceGammaProcessAsStochasticProcess1D(QlVarianceGammaProcess *o) { return ret(new QlStochasticProcess1D(*arg(o))); }
void qlFreeMerton76Process(QlMerton76Process *o) { del(o); }
QlStochasticProcess1D* qlMerton76ProcessAsStochasticProcess1D(QlMerton76Process *o) { return ret(new QlStochasticProcess1D(*arg(o))); }
void qlFreeHullWhiteProcess(QlHullWhiteProcess *o) { del(o); }
QlStochasticProcess1D* qlHullWhiteProcessAsStochasticProcess1D(QlHullWhiteProcess *o) { return ret(new QlStochasticProcess1D(*arg(o))); }
void qlFreeHullWhiteForwardProcess(QlHullWhiteForwardProcess *o) { del(o); }
QlStochasticProcess1D* qlHullWhiteForwardProcessAsStochasticProcess1D(QlHullWhiteForwardProcess *o) { return ret(new QlStochasticProcess1D(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
