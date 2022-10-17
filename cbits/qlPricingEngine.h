#ifdef __cplusplus
extern "C" {
#endif
  QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e);
  QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e);
  QlPricingEngine* qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e);
  QlPricingEngine* qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e);
  QlPricingEngine* qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e);

  void qlFreePricingEngine(QlPricingEngine *engine);
  void qlFreeBlackCalculator(QlBlackCalculator *o);
  void qlFreeBlackScholesCalculator(QlBlackScholesCalculator *o);
  QlBlackCalculator* qlBlackScholesCalculatorAsBlackCalculator(QlBlackScholesCalculator *o);

  double qlBlackCalculatorAlpha(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorBeta(QlBlackCalculator* o, char **e);
  QlBlackCalculator* qlBlackCalculator1(int optionType, double strike, double forward, double stdDev, double discount, char **e);
  QlBlackCalculator* qlBlackCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, char **e);
  double qlBlackCalculatorDelta(QlBlackCalculator* o, double spot, char **e);
  double qlBlackCalculatorDeltaForward(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorDividendRho(QlBlackCalculator* o, double maturity, char **e);
  double qlBlackCalculatorElasticity(QlBlackCalculator* o, double spot, char **e);
  double qlBlackCalculatorElasticityForward(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorGamma(QlBlackCalculator* o, double spot, char **e);
  double qlBlackCalculatorGammaForward(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorItmAssetProbability(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorItmCashProbability(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorRho(QlBlackCalculator* o, double maturity, char **e);
  double qlBlackCalculatorStrikeSensitivity(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorTheta(QlBlackCalculator* o, double spot, double maturity, char **e);
  double qlBlackCalculatorThetaPerDay(QlBlackCalculator* o, double spot, double maturity, char **e);
  double qlBlackCalculatorValue(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorVega(QlBlackCalculator* o, double maturity, char **e);
  QlBlackScholesCalculator* qlBlackScholesCalculator1(int optionType, double strike, double spot, double growth, double stdDev, double discount, char **e);
  QlBlackScholesCalculator* qlBlackScholesCalculator(QlStrikedTypePayoff* payoff, double spot, double growth, double stdDev, double discount, char **e);
  double qlBlackScholesCalculatorDelta(QlBlackScholesCalculator* o, char **e);
  double qlBlackScholesCalculatorElasticity(QlBlackScholesCalculator* o, char **e);
  double qlBlackScholesCalculatorGamma(QlBlackScholesCalculator* o, char **e);
  double qlBlackScholesCalculatorTheta(QlBlackScholesCalculator* o, double maturity, char **e);
  double qlBlackScholesCalculatorThetaPerDay(QlBlackScholesCalculator* o, double maturity, char **e);
  double qlQuantLibBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e);
  double qlQuantLibBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, double displacement, char **e);
  double qlQuantLibBlackFormulaCashItmProbability1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double displacement, char **e);
  double qlQuantLibBlackFormulaCashItmProbability(int optionType, double strike, double forward, double stdDev, double displacement, char **e);
  double qlQuantLibBlackFormulaImpliedStdDev1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e);
  double qlQuantLibBlackFormulaImpliedStdDev(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, char **e);
  double qlQuantLibBlackFormulaImpliedStdDevApproximation1(QlPlainVanillaPayoff* payoff, double forward, double blackPrice, double discount, double displacement, char **e);
  double qlQuantLibBlackFormulaImpliedStdDevApproximation(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, char **e);
  double qlQuantLibBlackFormulaStdDevDerivative1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, double displacement, char **e);
  double qlQuantLibBlackFormulaStdDevDerivative(double strike, double forward, double stdDev, double discount, double displacement, char **e);
  double qlQuantLibBlackFormulaVolDerivative(double strike, double forward, double stdDev, double expiry, double discount, double displacement, char **e);
  double qlQuantLibBlackScholesTheta(QlGeneralizedBlackScholesProcess* x0, double value, double delta, double gamma, char **e);
  double qlQuantLibBachelierBlackFormula1(QlPlainVanillaPayoff* payoff, double forward, double stdDev, double discount, char **e);
  double qlQuantLibBachelierBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, char **e);
  double qlQuantLibDefaultThetaPerDay(double theta, char **e);

  QlPricingEngine* qlAnalyticBSMHullWhiteEngine(double equityShortRateCorrelation, QlGeneralizedBlackScholesProcess* x1, QlHullWhite* x2, char **e);
  QlPricingEngine* qlAnalyticCapFloorEngine(QlAffineModel* model, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlAnalyticGJRGARCHEngine(QlGJRGARCHModel* model, char **e);
  QlPricingEngine* qlAnalyticHestonEngine(QlHestonModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* qlAnalyticHestonHullWhiteEngine(QlHestonModel* hestonModel, QlHullWhite* hullWhiteModel, unsigned integrationOrder, char **e);
  QlPricingEngine* qlBatesEngine(QlBatesModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* qlFFTVanillaEngine(QlGeneralizedBlackScholesProcess* process, double logStrikeSpacing, char **e);
  QlPricingEngine* qlG2SwaptionEngine(QlG2* model, double range, unsigned intervals, char **e);
  QlPricingEngine* qlJumpDiffusionEngine(QlMerton76Process* x0, double relativeAccuracy_, unsigned maxIterations, char **e);
  QlPricingEngine* qlTreeCapFloorEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeSwaptionEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeVanillaSwapEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlVarianceGammaEngine(QlVarianceGammaProcess* x0, char **e);
  QlPricingEngine* qlAnalyticHestonEngine1(QlHestonModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* qlAnalyticHestonHullWhiteEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* qlBatesEngine1(QlBatesModel* model, double relTolerance, unsigned maxEvaluations, char **e);

  QlPricingEngine* qlBaroneAdesiWhaleyApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlBatesDetJumpEngine1(QlBatesDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* qlBatesDetJumpEngine(QlBatesDetJumpModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* qlBatesDoubleExpDetJumpEngine1(QlBatesDoubleExpDetJumpModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* qlBatesDoubleExpDetJumpEngine(QlBatesDoubleExpDetJumpModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* qlBatesDoubleExpEngine1(QlBatesDoubleExpModel* model, double relTolerance, unsigned maxEvaluations, char **e);
  QlPricingEngine* qlBatesDoubleExpEngine(QlBatesDoubleExpModel* model, unsigned integrationOrder, char **e);
  QlPricingEngine* qlBjerksundStenslandApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlIntegralCdsEngine(int, int, QlDefaultProbabilityTermStructure* x1, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e);
  QlPricingEngine* qlIntegralEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlJamshidianSwaptionEngine(QlOneFactorAffineModel* model, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlJuQuadraticApproximationEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlKirkEngine(QlBlackProcess* process1, QlBlackProcess* process2, double correlation, char **e);
  QlPricingEngine* qlMidPointCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e);
  QlPricingEngine* qlReplicatingVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, double dk, unsigned callStrikesLen, double* callStrikes, unsigned putStrikesLen, double* putStrikes, char **e);
  QlPricingEngine* qlStulzEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, char **e);
  QlPricingEngine* qlLfmSwaptionEngine(QlLiborForwardModel* model, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlTreeCapFloorEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeSwaptionEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeVanillaSwapEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlFdG2SwaptionEngine(QlG2* model, unsigned tGrid, unsigned xGrid, unsigned yGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e);
  QlPricingEngine* qlFdHullWhiteSwaptionEngine(QlHullWhite* model, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e);

  QlPricingEngine* qlMCVarianceSwapEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCHestonHullWhiteEngine1(int rngtrait, QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCAmericanEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, char **e);
  QlPricingEngine* qlMCBarrierEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e);
  QlPricingEngine* qlMCDigitalEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCDiscreteArithmeticAPEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCDiscreteArithmeticASEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCDiscreteGeometricAPEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanGJRGARCHEngine1(int rngtrait, QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanHestonEngine1(int rngtrait, QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCHullWhiteCapFloorEngine1(int rngtrait, QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCPerformanceEngine1(int rngtrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);

//  QlPricingEngine* qlFDAmericanEngine(const char *fdscheme, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned gridPoints, int timeDependent, char **e);
//  QlPricingEngine* qlFDBermudanEngine(const char *fdscheme, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned gridPoints, int timeDependent, char **e);
//  QlPricingEngine* qlFDEuropeanEngine(const char *fdscheme, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned gridPoints, int timeDependent, char **e);

  QlPricingEngine* qlBinomialVanillaEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e);
  QlPricingEngine* qlBinomialConvertibleEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, QlQuote* creditSpread, unsigned dividendsLen, QlDividend** dividends, char **e);
  QlPricingEngine* qlBlackCallableFixedRateBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlBlackCallableFixedRateBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlBlackCallableZeroCouponBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlBlackCallableZeroCouponBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlTreeCallableFixedRateBondEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeCallableFixedRateBondEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeCallableZeroCouponBondEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeCallableZeroCouponBondEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
