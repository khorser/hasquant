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
  QlPricingEngine *DLLEXPORT qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e);
  QlPricingEngine* DLLEXPORT qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* DLLEXPORT qlBinomialVanillaEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e);
  QlPricingEngine* DLLEXPORT qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e);
  QlPricingEngine* DLLEXPORT qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e);
  QlPricingEngine* DLLEXPORT qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e);
  QlPricingEngine* DLLEXPORT qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e);

  void DLLEXPORT qlFreePricingEngine(QlPricingEngine *engine);
  void DLLEXPORT qlFreeBlackCalculator(QlBlackCalculator *o);
  void DLLEXPORT qlFreeBlackScholesCalculator(QlBlackScholesCalculator *o);
  QlBlackCalculator* DLLEXPORT qlBlackScholesCalculatorAsBlackCalculator(QlBlackScholesCalculator *o);

  double DLLEXPORT qlBlackCalculatorAlpha(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorBeta(QlBlackCalculator* o, char **e);
  QlBlackCalculator* DLLEXPORT qlBlackCalculator1(int optionType, double strike, double forward, double stdDev, double discount, char **e);
  QlBlackCalculator* DLLEXPORT qlBlackCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, char **e);
  double DLLEXPORT qlBlackCalculatorDelta(QlBlackCalculator* o, double spot, char **e);
  double DLLEXPORT qlBlackCalculatorDeltaForward(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorDividendRho(QlBlackCalculator* o, double maturity, char **e);
  double DLLEXPORT qlBlackCalculatorElasticity(QlBlackCalculator* o, double spot, char **e);
  double DLLEXPORT qlBlackCalculatorElasticityForward(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorGamma(QlBlackCalculator* o, double spot, char **e);
  double DLLEXPORT qlBlackCalculatorGammaForward(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorItmAssetProbability(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorItmCashProbability(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorRho(QlBlackCalculator* o, double maturity, char **e);
  double DLLEXPORT qlBlackCalculatorStrikeSensitivity(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorTheta(QlBlackCalculator* o, double spot, double maturity, char **e);
  double DLLEXPORT qlBlackCalculatorThetaPerDay(QlBlackCalculator* o, double spot, double maturity, char **e);
  double DLLEXPORT qlBlackCalculatorValue(QlBlackCalculator* o, char **e);
  double DLLEXPORT qlBlackCalculatorVega(QlBlackCalculator* o, double maturity, char **e);
  QlBlackScholesCalculator* DLLEXPORT qlBlackScholesCalculator1(int optionType, double strike, double spot, double growth, double stdDev, double discount, char **e);
  QlBlackScholesCalculator* DLLEXPORT qlBlackScholesCalculator(QlStrikedTypePayoff* payoff, double spot, double growth, double stdDev, double discount, char **e);
  double DLLEXPORT qlBlackScholesCalculatorDelta(QlBlackScholesCalculator* o, char **e);
  double DLLEXPORT qlBlackScholesCalculatorElasticity(QlBlackScholesCalculator* o, char **e);
  double DLLEXPORT qlBlackScholesCalculatorGamma(QlBlackScholesCalculator* o, char **e);
  double DLLEXPORT qlBlackScholesCalculatorTheta(QlBlackScholesCalculator* o, double maturity, char **e);
  double DLLEXPORT qlBlackScholesCalculatorThetaPerDay(QlBlackScholesCalculator* o, double maturity, char **e);
  double DLLEXPORT qlQuantLibBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaCashItmProbability1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaCashItmProbability(int optionType, double strike, double forward, double stdDev, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaImpliedStdDev1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaImpliedStdDev(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaImpliedStdDevApproximation1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaImpliedStdDevApproximation(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaStdDevDerivative1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaStdDevDerivative(double strike, double forward, double stdDev, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackFormulaVolDerivative(double strike, double forward, double stdDev, double expiry, double discount, double displacement, char **e);
  double DLLEXPORT qlQuantLibBlackScholesTheta(QlGeneralizedBlackScholesProcess* x0, double value, double delta, double gamma, char **e);
  double DLLEXPORT qlQuantLibBachelierBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, char **e);
  double DLLEXPORT qlQuantLibBachelierBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, char **e);
  double DLLEXPORT qlQuantLibDefaultThetaPerDay(double theta, char **e);

  QlPricingEngine* DLLEXPORT qlAnalyticBSMHullWhiteEngine(double equityShortRateCorrelation, QlGeneralizedBlackScholesProcess* x1, QlHullWhite* x2, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticCapFloorEngine(QlAffineModel* model, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticGJRGARCHEngine(QlGJRGARCHModel* model, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticHestonEngine(QlHestonModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticHestonHullWhiteEngine(QlHestonModel* hestonModel, QlHullWhite* hullWhiteModel, unsigned integrationOrder, char **e);
  QlPricingEngine* DLLEXPORT qlBatesEngine(QlBatesModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* DLLEXPORT qlFFTVanillaEngine(QlGeneralizedBlackScholesProcess* process, double logStrikeSpacing, char **e);
  QlPricingEngine* DLLEXPORT qlG2SwaptionEngine(QlG2* model, double range, unsigned intervals, char **e);
  QlPricingEngine* DLLEXPORT qlJumpDiffusionEngine(QlMerton76Process* x0, double relativeAccuracy_, unsigned maxIterations, char **e);
  QlPricingEngine* DLLEXPORT qlTreeCapFloorEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* DLLEXPORT qlTreeSwaptionEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* DLLEXPORT qlTreeVanillaSwapEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* DLLEXPORT qlVarianceGammaEngine(QlVarianceGammaProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticHestonEngine1(QlHestonModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* DLLEXPORT qlAnalyticHestonHullWhiteEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* DLLEXPORT qlBatesEngine1(QlBatesModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* DLLEXPORT qlMCHestonHullWhiteEngine(QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);

  QlPricingEngine* DLLEXPORT qlMCAmericanEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, char **e);
  QlPricingEngine* DLLEXPORT qlMCBarrierEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCDigitalEngine(QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCDiscreteArithmeticAPEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCDiscreteArithmeticASEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCDiscreteGeometricAPEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCEuropeanEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCEuropeanGJRGARCHEngine(QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCEuropeanHestonEngine(QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCHullWhiteCapFloorEngine(QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMCPerformanceEngine(QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);

  QlPricingEngine* DLLEXPORT qlBaroneAdesiWhaleyApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlBatesDetJumpEngine1(QlBatesDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* DLLEXPORT qlBatesDetJumpEngine(QlBatesDetJumpModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* DLLEXPORT qlBatesDoubleExpDetJumpEngine1(QlBatesDoubleExpDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* DLLEXPORT qlBatesDoubleExpDetJumpEngine(QlBatesDoubleExpDetJumpModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* DLLEXPORT qlBatesDoubleExpEngine1(QlBatesDoubleExpModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* DLLEXPORT qlBatesDoubleExpEngine(QlBatesDoubleExpModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* DLLEXPORT qlBjerksundStenslandApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlIntegralCdsEngine(Period* integrationStep, QlDefaultProbabilityTermStructure* x1, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e);
  QlPricingEngine* DLLEXPORT qlIntegralEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlJamshidianSwaptionEngine(QlOneFactorAffineModel* model, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* DLLEXPORT qlJuQuadraticApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* DLLEXPORT qlKirkEngine(QlBlackProcess* process1, QlBlackProcess* process2, double correlation, char **e);
  QlPricingEngine* DLLEXPORT qlMCVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* DLLEXPORT qlMidPointCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e);
  QlPricingEngine* DLLEXPORT qlReplicatingVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, double dk, unsigned callStrikesLen, double* callStrikes, unsigned putStrikesLen, double* putStrikes, char **e);
  QlPricingEngine* DLLEXPORT qlStulzEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, char **e);
  QlPricingEngine* DLLEXPORT qlLfmSwaptionEngine(QlLiborForwardModel* model, QlYieldTermStructure* discountCurve, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
