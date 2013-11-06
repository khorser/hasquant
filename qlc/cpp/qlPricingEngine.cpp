#include <ql/experimental/callablebonds/blackcallablebondengine.hpp>
#include <ql/experimental/callablebonds/treecallablebondengine.hpp>
#include <ql/experimental/math/zigguratrng.hpp>
#include <ql/experimental/variancegamma/all.hpp>
#include <ql/legacy/libormarketmodels/lfmswaptionengine.hpp>
#include <ql/methods/montecarlo/lsmbasissystem.hpp>
#include <ql/pricingengines/asian/analytic_cont_geom_av_price.hpp>
#include <ql/pricingengines/asian/analytic_discr_geom_av_strike.hpp>
#include <ql/pricingengines/asian/mc_discr_arith_av_price.hpp>
#include <ql/pricingengines/barrier/analyticbarrierengine.hpp>
#include <ql/pricingengines/basket/kirkengine.hpp>
#include <ql/pricingengines/basket/stulzengine.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/pricingengines/capfloor/analyticcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/blackcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/treecapfloorengine.hpp>
#include <ql/pricingengines/cliquet/analyticcliquetengine.hpp>
#include <ql/pricingengines/cliquet/analyticperformanceengine.hpp>
#include <ql/pricingengines/credit/integralcdsengine.hpp>
#include <ql/pricingengines/credit/midpointcdsengine.hpp>
#include <ql/pricingengines/forward/replicatingvarianceswapengine.hpp>
#include <ql/pricingengines/greeks.hpp>
#include <ql/pricingengines/lookback/analyticcontinuousfixedlookback.hpp>
#include <ql/pricingengines/lookback/analyticcontinuousfloatinglookback.hpp>
#include <ql/pricingengines/swap/treeswapengine.hpp>
#include <ql/pricingengines/swaption/blackswaptionengine.hpp>
#include <ql/pricingengines/swaption/fdg2swaptionengine.hpp>
#include <ql/pricingengines/swaption/fdg2swaptionengine.hpp>
#include <ql/pricingengines/swaption/fdhullwhiteswaptionengine.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/pricingengines/swaption/treeswaptionengine.hpp>
#include <ql/pricingengines/vanilla/analyticbsmhullwhiteengine.hpp>
#include <ql/pricingengines/vanilla/analyticdigitalamericanengine.hpp>
#include <ql/pricingengines/vanilla/analyticdividendeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analyticgjrgarchengine.hpp>
#include <ql/pricingengines/vanilla/analytichestonhullwhiteengine.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/batesengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/integralengine.hpp>
#include <ql/pricingengines/vanilla/jumpdiffusionengine.hpp>
#include <ql/pricingengines/vanilla/juquadraticengine.hpp>

#include "qlaux.h"
#include "qlPricingEngine.h"
#include "qlPricingEngineAux.h"

using namespace QuantLib;

QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(
                    new DiscountingBondEngine(
                        Handle<YieldTermStructure>(*arg(ts)), qlOptBool(f)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine *>(e, er);
  }
}

void qlFreePricingEngine(QlPricingEngine *engine) {
  del(engine);
}

QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new DiscountingSwapEngine(Handle<YieldTermStructure>(*arg(discountCurve)), qlOptBool(includeSettlementDateFlows), qlNullableDate(settlementDate), qlNullableDate(npvDate)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticBarrierEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticCliquetEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousFixedLookbackEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousFloatingLookbackEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousGeometricAveragePriceAsianEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDigitalAmericanEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAveragePriceAsianEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAverageStrikeAsianEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDividendEuropeanEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticEuropeanEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticPerformanceEngine(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCapFloorEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<OptionletVolatilityStructure>(*arg(vol))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCapFloorEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<Quote>(*arg(vol)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackSwaptionEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<Quote>(*arg(vol)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackSwaptionEngine(Handle<YieldTermStructure>(*arg(discountCurve)), Handle<SwaptionVolatilityStructure>(*arg(vol))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

void qlFreeBlackCalculator(QlBlackCalculator *o) { del(o); }
void qlFreeBlackScholesCalculator(QlBlackScholesCalculator *o) { del(o); }
QlBlackCalculator* qlBlackScholesCalculatorAsBlackCalculator(QlBlackScholesCalculator *o) { return ret(new QlBlackCalculator(*arg(o))); }

double qlBlackCalculatorAlpha(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->alpha();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorBeta(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->beta();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlBlackCalculator* qlBlackCalculator1(int optionType, double strike, double forward, double stdDev, double discount, char **e) {
  try {
    return ret(new QlBlackCalculator(alloc(new BlackCalculator((Option::Type)optionType, strike, forward, stdDev, discount))));
  } catch (std::exception& er) {
    return handleException<QlBlackCalculator*>(e, er);
  }
}
QlBlackCalculator* qlBlackCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, char **e) {
  try {
    return ret(new QlBlackCalculator(alloc(new BlackCalculator(*arg(payoff), forward, stdDev, discount))));
  } catch (std::exception& er) {
    return handleException<QlBlackCalculator*>(e, er);
  }
}
double qlBlackCalculatorDelta(QlBlackCalculator* o, double spot, char **e) {
  try {
    return (*arg(o))->delta(spot);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorDeltaForward(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->deltaForward();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorDividendRho(QlBlackCalculator* o, double maturity, char **e) {
  try {
    return (*arg(o))->dividendRho(maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorElasticity(QlBlackCalculator* o, double spot, char **e) {
  try {
    return (*arg(o))->elasticity(spot);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorElasticityForward(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->elasticityForward();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorGamma(QlBlackCalculator* o, double spot, char **e) {
  try {
    return (*arg(o))->gamma(spot);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorGammaForward(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->gammaForward();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorItmAssetProbability(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->itmAssetProbability();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorItmCashProbability(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->itmCashProbability();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorRho(QlBlackCalculator* o, double maturity, char **e) {
  try {
    return (*arg(o))->rho(maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorStrikeSensitivity(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->strikeSensitivity();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorTheta(QlBlackCalculator* o, double spot, double maturity, char **e) {
  try {
    return (*arg(o))->theta(spot, maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorThetaPerDay(QlBlackCalculator* o, double spot, double maturity, char **e) {
  try {
    return (*arg(o))->thetaPerDay(spot, maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorValue(QlBlackCalculator* o, char **e) {
  try {
    return (*arg(o))->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalculatorVega(QlBlackCalculator* o, double maturity, char **e) {
  try {
    return (*arg(o))->vega(maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlBlackScholesCalculator* qlBlackScholesCalculator1(int optionType, double strike, double spot, double growth, double stdDev, double discount, char **e) {
  try {
    return ret(new QlBlackScholesCalculator(alloc(new BlackScholesCalculator((Option::Type)optionType, strike, spot, growth, stdDev, discount))));
  } catch (std::exception& er) {
    return handleException<QlBlackScholesCalculator*>(e, er);
  }
}
QlBlackScholesCalculator* qlBlackScholesCalculator(QlStrikedTypePayoff* payoff, double spot, double growth, double stdDev, double discount, char **e) {
  try {
    return ret(new QlBlackScholesCalculator(alloc(new BlackScholesCalculator(*arg(payoff), spot, growth, stdDev, discount))));
  } catch (std::exception& er) {
    return handleException<QlBlackScholesCalculator*>(e, er);
  }
}
double qlBlackScholesCalculatorDelta(QlBlackScholesCalculator* o, char **e) {
  try {
    return (*arg(o))->delta();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackScholesCalculatorElasticity(QlBlackScholesCalculator* o, char **e) {
  try {
    return (*arg(o))->elasticity();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackScholesCalculatorGamma(QlBlackScholesCalculator* o, char **e) {
  try {
    return (*arg(o))->gamma();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackScholesCalculatorTheta(QlBlackScholesCalculator* o, double maturity, char **e) {
  try {
    return (*arg(o))->theta(maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackScholesCalculatorThetaPerDay(QlBlackScholesCalculator* o, double maturity, char **e) {
  try {
    return (*arg(o))->thetaPerDay(maturity);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormula(*arg(payoff), forward, stdDev, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormula((Option::Type)optionType, strike, forward, stdDev, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaCashItmProbability1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaCashItmProbability(*arg(payoff), forward, stdDev, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaCashItmProbability(int optionType, double strike, double forward, double stdDev, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaCashItmProbability((Option::Type)optionType, strike, forward, stdDev, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaImpliedStdDev1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e) {
  try {
    return QuantLib::blackFormulaImpliedStdDev(*arg(payoff), forward, blackPrice, discount, displacement, guess, accuracy, maxIterations);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaImpliedStdDev(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e) {
  try {
    return QuantLib::blackFormulaImpliedStdDev((Option::Type)optionType, strike, forward, blackPrice, discount, displacement, guess, accuracy, maxIterations);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaImpliedStdDevApproximation1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaImpliedStdDevApproximation(*arg(payoff), forward, blackPrice, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaImpliedStdDevApproximation(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaImpliedStdDevApproximation((Option::Type)optionType, strike, forward, blackPrice, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaStdDevDerivative1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaStdDevDerivative(*arg(payoff), forward, stdDev, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaStdDevDerivative(double strike, double forward, double stdDev, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaStdDevDerivative(strike, forward, stdDev, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackFormulaVolDerivative(double strike, double forward, double stdDev, double expiry, double discount, double displacement, char **e) {
  try {
    return QuantLib::blackFormulaVolDerivative(strike, forward, stdDev, expiry, discount, displacement);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBlackScholesTheta(QlGeneralizedBlackScholesProcess* x0, double value, double delta, double gamma, char **e) {
  try {
    return QuantLib::blackScholesTheta(*arg(x0), value, delta, gamma);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBachelierBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, char **e) {
  try {
    return QuantLib::bachelierBlackFormula(*arg(payoff), forward, stdDev, discount);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBachelierBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, char **e) {
  try {
    return QuantLib::bachelierBlackFormula((Option::Type)optionType, strike, forward, stdDev, discount);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibDefaultThetaPerDay(double theta, char **e) {
  try {
    return QuantLib::defaultThetaPerDay(theta);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlPricingEngine* qlAnalyticBSMHullWhiteEngine(double equityShortRateCorrelation, QlGeneralizedBlackScholesProcess* x1, QlHullWhite* x2, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticBSMHullWhiteEngine(equityShortRateCorrelation, *arg(x1), *arg(x2)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticCapFloorEngine(QlAffineModel* model, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticCapFloorEngine(*arg(model), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticGJRGARCHEngine(QlGJRGARCHModel* model, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticGJRGARCHEngine(*arg(model)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonEngine(QlHestonModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonHullWhiteEngine(QlHestonModel* hestonModel, QlHullWhite* hullWhiteModel, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonHullWhiteEngine(*arg(hestonModel), *arg(hullWhiteModel), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesEngine(QlBatesModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlFFTVanillaEngine(QlGeneralizedBlackScholesProcess* process, double logStrikeSpacing, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new FFTVanillaEngine(*arg(process), logStrikeSpacing))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlG2SwaptionEngine(QlG2* model, double range, unsigned intervals, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new G2SwaptionEngine(*arg(model), range, intervals))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlJumpDiffusionEngine(QlMerton76Process* x0, double relativeAccuracy_, unsigned maxIterations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new JumpDiffusionEngine(*arg(x0), relativeAccuracy_, maxIterations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCapFloorEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCapFloorEngine(*arg(model), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeSwaptionEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeSwaptionEngine(*arg(x0), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeVanillaSwapEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeVanillaSwapEngine(*arg(x0), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlVarianceGammaEngine(QlVarianceGammaProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new VarianceGammaEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonEngine1(QlHestonModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonHullWhiteEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonHullWhiteEngine(*arg(model), *arg(hullWhiteModel), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesEngine1(QlBatesModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBaroneAdesiWhaleyApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BaroneAdesiWhaleyApproximationEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesDetJumpEngine1(QlBatesDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesDetJumpEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesDetJumpEngine(QlBatesDetJumpModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesDetJumpEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesDoubleExpDetJumpEngine1(QlBatesDoubleExpDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesDoubleExpDetJumpEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesDoubleExpDetJumpEngine(QlBatesDoubleExpDetJumpModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesDoubleExpDetJumpEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesDoubleExpEngine1(QlBatesDoubleExpModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesDoubleExpEngine(*arg(model), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesDoubleExpEngine(QlBatesDoubleExpModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesDoubleExpEngine(*arg(model), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBjerksundStenslandApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BjerksundStenslandApproximationEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlIntegralCdsEngine(Period* integrationStep, QlDefaultProbabilityTermStructure* x1, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new IntegralCdsEngine(*arg(integrationStep), Handle<DefaultProbabilityTermStructure>(*arg(x1)), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), qlOptBool(includeSettlementDateFlows)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlIntegralEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new IntegralEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlJamshidianSwaptionEngine(QlOneFactorAffineModel* model, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new JamshidianSwaptionEngine(*arg(model), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlJuQuadraticApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new JuQuadraticApproximationEngine(*arg(x0)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlKirkEngine(QlBlackProcess* process1, QlBlackProcess* process2, double correlation, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new KirkEngine(*arg(process1), *arg(process2), correlation))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMidPointCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MidPointCdsEngine(Handle<DefaultProbabilityTermStructure>(*arg(x0)), recoveryRate, Handle<YieldTermStructure>(*arg(discountCurve)), qlOptBool(includeSettlementDateFlows)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlReplicatingVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, double dk, unsigned callStrikesLen, double* callStrikes, unsigned putStrikesLen, double* putStrikes, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new ReplicatingVarianceSwapEngine(*arg(process), dk, std::vector<double>(callStrikes, callStrikes+callStrikesLen), std::vector<double>(putStrikes, putStrikes+putStrikesLen)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlStulzEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new StulzEngine(*arg(process1), *arg(process2), correlation))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlLfmSwaptionEngine(QlLiborForwardModel* model, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new LfmSwaptionEngine(*arg(model), Handle<YieldTermStructure>(*arg(discountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCapFloorEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCapFloorEngine(*arg(model), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeSwaptionEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeSwaptionEngine(*arg(x0), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeVanillaSwapEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeVanillaSwapEngine(*arg(x0), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlFdG2SwaptionEngine(QlG2* model, unsigned tGrid, unsigned xGrid, unsigned yGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new FdG2SwaptionEngine(*arg(model), tGrid, xGrid, yGrid, dampingSteps, invEps, *arg(schemeDesc)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlFdHullWhiteSwaptionEngine(QlHullWhite* model, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new FdHullWhiteSwaptionEngine(*arg(model), tGrid, xGrid, dampingSteps, invEps, *arg(schemeDesc)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlMCVarianceSwapEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCVarianceSwapEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCHestonHullWhiteEngine1(const char *rngtrait, QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCHestonHullWhiteEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCAmericanEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCAmericanEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, (LsmBasisSystem::PolynomType)polynomType, nCalibrationSamples))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCBarrierEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCBarrierEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDigitalEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCDigitalEngine1Aux(rngtrait, *arg(x0), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDiscreteArithmeticAPEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCDiscreteArithmeticAPEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDiscreteArithmeticASEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCDiscreteArithmeticASEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDiscreteGeometricAPEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCDiscreteGeometricAPEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCEuropeanEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCEuropeanEngine1Aux(rngtrait, *arg(process), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCEuropeanGJRGARCHEngine1(const char *rngtrait, QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCEuropeanGJRGARCHEngine1Aux(rngtrait, *arg(x0), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCEuropeanHestonEngine1(const char *rngtrait, QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCEuropeanHestonEngine1Aux(rngtrait, *arg(x0), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCHullWhiteCapFloorEngine1(const char *rngtrait, QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCHullWhiteCapFloorEngine1Aux(rngtrait, *arg(model), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCPerformanceEngine1(const char *rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlMCPerformanceEngine1Aux(rngtrait, *arg(process), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlBinomialVanillaEngine(const char *tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlBinomialVanillaEngineAux(tree, *arg(process), timeSteps))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlFDAmericanEngine(const char *fdscheme, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned gridPoints, int timeDependent, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlFDAmericanEngineAux(fdscheme, *arg(process), timeSteps, gridPoints, timeDependent))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlFDBermudanEngine(const char *fdscheme, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned gridPoints, int timeDependent, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlFDBermudanEngineAux(fdscheme, *arg(process), timeSteps, gridPoints, timeDependent))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlFDEuropeanEngine(const char *fdscheme, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned gridPoints, int timeDependent, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlFDEuropeanEngineAux(fdscheme, *arg(process), timeSteps, gridPoints, timeDependent))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlBinomialConvertibleEngine(const char *tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(qlBinomialConvertibleEngineAux(tree, *arg(process), timeSteps))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCallableFixedRateBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCallableFixedRateBondEngine(Handle<CallableBondVolatilityStructure>(*arg(yieldVolStructure)), Handle<YieldTermStructure>(*arg(discountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCallableFixedRateBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCallableFixedRateBondEngine(Handle<Quote>(*arg(fwdYieldVol)), Handle<YieldTermStructure>(*arg(discountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCallableZeroCouponBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCallableZeroCouponBondEngine(Handle<CallableBondVolatilityStructure>(*arg(yieldVolStructure)), Handle<YieldTermStructure>(*arg(discountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBlackCallableZeroCouponBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BlackCallableZeroCouponBondEngine(Handle<Quote>(*arg(fwdYieldVol)), Handle<YieldTermStructure>(*arg(discountCurve))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCallableFixedRateBondEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCallableFixedRateBondEngine(*arg(x0), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCallableFixedRateBondEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCallableFixedRateBondEngine(*arg(x0), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCallableZeroCouponBondEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCallableZeroCouponBondEngine(*arg(model), *arg(timeGrid), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCallableZeroCouponBondEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCallableZeroCouponBondEngine(*arg(model), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
