#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/pricingengines/barrier/analyticbarrierengine.hpp>
#include <ql/pricingengines/cliquet/all.hpp>
#include <ql/pricingengines/lookback/all.hpp>
#include <ql/pricingengines/vanilla/analyticdigitalamericanengine.hpp>
#include <ql/pricingengines/vanilla/analyticdividendeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/asian/all.hpp>
#include <ql/pricingengines/capfloor/blackcapfloorengine.hpp>
#include <ql/pricingengines/swaption/blackswaptionengine.hpp>
#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/pricingengines/greeks.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(
                    new DiscountingBondEngine(
                        Handle<YieldTermStructure>(*(arg(ts))),
                        qlOptBool((f))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine *>(e, er);
  }
}

void qlFreePricingEngine(QlPricingEngine *engine) {
  del(engine);
}

QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new DiscountingSwapEngine(qlNullableHandle(arg(discountCurve)), qlOptBool(includeSettlementDateFlows), qlNullableDate(settlementDate), qlNullableDate(npvDate)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticBarrierEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticCliquetEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousFixedLookbackEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousFloatingLookbackEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticContinuousGeometricAveragePriceAsianEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDigitalAmericanEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAveragePriceAsianEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDiscreteGeometricAverageStrikeAsianEngine((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticDividendEuropeanEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticEuropeanEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticPerformanceEngine((*arg(process))))));
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
    return ret(new QlBlackCalculator(alloc(new BlackCalculator((*arg(payoff)), forward, stdDev, discount))));
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
    return ret(new QlBlackScholesCalculator(alloc(new BlackScholesCalculator((*arg(payoff)), spot, growth, stdDev, discount))));
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
    return QuantLib::blackFormula((*arg(payoff)), forward, stdDev, discount, displacement);
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
    return QuantLib::blackFormulaCashItmProbability((*arg(payoff)), forward, stdDev, displacement);
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
    return QuantLib::blackFormulaImpliedStdDev((*arg(payoff)), forward, blackPrice, discount, displacement, guess, accuracy, maxIterations);
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
    return QuantLib::blackFormulaImpliedStdDevApproximation((*arg(payoff)), forward, blackPrice, discount, displacement);
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
    return QuantLib::blackFormulaStdDevDerivative((*arg(payoff)), forward, stdDev, discount, displacement);
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
    return QuantLib::blackScholesTheta((*arg(x0)), value, delta, gamma);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlQuantLibBachelierBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, char **e) {
  try {
    return QuantLib::bachelierBlackFormula((*arg(payoff)), forward, stdDev, discount);
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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
