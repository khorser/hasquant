#include <ql/pricingengines/all.hpp>
#include <ql/experimental/variancegamma/all.hpp>

#include "qlaux.h"
#include "qlPricingEngine.h"

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

QlPricingEngine* qlAnalyticBSMHullWhiteEngine(double equityShortRateCorrelation, QlGeneralizedBlackScholesProcess* x1, QlHullWhite* x2, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticBSMHullWhiteEngine(equityShortRateCorrelation, (*arg(x1)), (*arg(x2))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticCapFloorEngine(QlAffineModel* model, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticCapFloorEngine((*arg(model)), qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticGJRGARCHEngine(QlGJRGARCHModel* model, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticGJRGARCHEngine((*arg(model))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonEngine(QlHestonModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonEngine((*arg(model)), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonHullWhiteEngine(QlHestonModel* hestonModel, QlHullWhite* hullWhiteModel, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonHullWhiteEngine((*arg(hestonModel)), (*arg(hullWhiteModel)), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesEngine(QlBatesModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesEngine((*arg(model)), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlFFTVanillaEngine(QlGeneralizedBlackScholesProcess* process, double logStrikeSpacing, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new FFTVanillaEngine((*arg(process)), logStrikeSpacing))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlG2SwaptionEngine(QlG2* model, double range, unsigned intervals, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new G2SwaptionEngine((*arg(model)), range, intervals))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlJumpDiffusionEngine(QlMerton76Process* x0, double relativeAccuracy_, unsigned maxIterations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new JumpDiffusionEngine((*arg(x0)), relativeAccuracy_, maxIterations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeCapFloorEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeCapFloorEngine((*arg(model)), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeSwaptionEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeSwaptionEngine((*arg(x0)), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlTreeVanillaSwapEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new TreeVanillaSwapEngine((*arg(x0)), timeSteps, qlNullableHandle(arg(termStructure))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlVarianceGammaEngine(QlVarianceGammaProcess* x0, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new VarianceGammaEngine((*arg(x0))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonEngine1(QlHestonModel* model, unsigned integrationOrder, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonEngine((*arg(model)), integrationOrder))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlAnalyticHestonHullWhiteEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new AnalyticHestonHullWhiteEngine((*arg(model)), (*arg(hullWhiteModel)), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlBatesEngine1(QlBatesModel* model, double relTolerance, unsigned maxEvaluations, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new BatesEngine((*arg(model)), relTolerance, maxEvaluations))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCHestonHullWhiteEngine(QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCHestonHullWhiteEngine<>((*arg(process)), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

QlPricingEngine* qlMCAmericanEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCAmericanEngine<>((*arg(process)), timeSteps, timeStepsPerYear, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed, polynomOrder, (LsmBasisSystem::PolynomType)polynomType, nCalibrationSamples))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCBarrierEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCBarrierEngine<>((*arg(process)), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, isBiased, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDigitalEngine(QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCDigitalEngine<>((*arg(x0)), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDiscreteArithmeticAPEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCDiscreteArithmeticAPEngine<>((*arg(process)), brownianBridge, antitheticVariate, controlVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDiscreteArithmeticASEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCDiscreteArithmeticASEngine<>((*arg(process)), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCDiscreteGeometricAPEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCDiscreteGeometricAPEngine<>((*arg(process)), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCEuropeanEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCEuropeanEngine<>((*arg(process)), timeSteps, timeStepsPerYear, brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCEuropeanGJRGARCHEngine(QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCEuropeanGJRGARCHEngine<>((*arg(x0)), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCEuropeanHestonEngine(QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCEuropeanHestonEngine<>((*arg(x0)), timeSteps, timeStepsPerYear, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCHullWhiteCapFloorEngine(QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCHullWhiteCapFloorEngine<>((*arg(model)), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}
QlPricingEngine* qlMCPerformanceEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(new MCPerformanceEngine<>((*arg(process)), brownianBridge, antitheticVariate, requiredSamples, requiredTolerance, maxSamples, seed))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
