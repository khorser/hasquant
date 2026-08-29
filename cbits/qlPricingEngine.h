#ifdef __cplusplus
extern "C" {
#endif
  QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e);
  QlPricingEngine* qlRiskyBondEngine(QlDefaultProbabilityTermStructure* defaultTS, double recoveryRate, QlYieldTermStructure* yieldTS, char **e);
  QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  QlPricingEngine* qlDiscountingFxForwardEngine(QlYieldTermStructure* sourceCurrencyDiscountCurve, QlYieldTermStructure* targetCurrencyDiscountCurve, QlQuote* spotFx, char **e);
  QlPricingEngine* qlDiscountingConstNotionalCrossCurrencySwapEngine(Currency* domesticCcy, QlYieldTermStructure* domesticCcyDiscountCurve, Currency* foreignCcy, QlYieldTermStructure* foreignCcyDiscountCurve, QlQuote* spotFX, int includeSettlementDateFlows, int settlementDate, int npvDate, int spotFXSettleDate, char **e);
  QlPricingEngine* qlCounterpartyAdjSwapEngine(QlYieldTermStructure* discountCurve, QlQuote* blackVol, QlDefaultProbabilityTermStructure* ctptyDTS, double ctptyRecoveryRate, QlDefaultProbabilityTermStructure* invstDTS, double invstRecoveryRate, char **e);
  QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticSoftBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticSimpleChooserEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticTwoAssetCorrelationEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, QlQuote* correlation, char **e);
  QlPricingEngine* qlAnalyticWriterExtensibleOptionEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticPartialTimeBarrierOptionEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticBinaryBarrierEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlFdBlackScholesBarrierEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, char **e);
  QlPricingEngine* qlFdHestonBarrierEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlFdHestonBarrierEngine1(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlFdHestonDoubleBarrierEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlBinomialBarrierEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned maxTimeSteps, char **e);
  QlPricingEngine* qlVannaVolgaBarrierEngine(QlDeltaVolQuote* atmVol, QlDeltaVolQuote* vol25Put, QlDeltaVolQuote* vol25Call, QlQuote* spotFX, QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS, int adaptVanDelta, double bsPriceWithSmile, char **e);
  QlPricingEngine* qlAnalyticDoubleBarrierEngine(QlGeneralizedBlackScholesProcess* process, int series, char **e);
  QlPricingEngine* qlVannaVolgaDoubleBarrierEngine(QlDeltaVolQuote* atmVol, QlDeltaVolQuote* vol25Put, QlDeltaVolQuote* vol25Call, QlQuote* spotFX, QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS, int adaptVanDelta, double bsPriceWithSmile, int series, char **e);
  QlPricingEngine* qlBinomialDoubleBarrierEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, char **e);
  QlPricingEngine* qlMCDoubleBarrierEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticCompoundOptionEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlAnalyticDigitalAmericanKOEngine(QlGeneralizedBlackScholesProcess* x0, char **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlTurnbullWakemanAsianEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlFdBlackScholesAsianEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned aGrid, FdmSchemeDesc *fdScheme, char **e);
  QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, unsigned dividendsLen, QlDividend** dividends, char **e);
  QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlForwardEuropeanEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlForwardBaroneAdesiWhaleyEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlForwardBjerksundStenslandEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlForwardFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, char **e);
  QlPricingEngine* qlMCForwardEuropeanBSEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlAnalyticHestonForwardEuropeanEngine(QlHestonProcess* process, unsigned integrationOrder, char **e);
  QlPricingEngine* qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e);
  QlPricingEngine* qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, double displacement, char **e);
  QlPricingEngine* qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, double displacement, int model, char **e);
  QlPricingEngine* qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e);
  QlPricingEngine* qlBachelierCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, char **e);
  QlPricingEngine* qlBachelierCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, char **e);
  QlPricingEngine* qlBachelierSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, int model, char **e);
  QlPricingEngine* qlBachelierSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, char **e);

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
  double qlBlackCalculatorStrikeGamma(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorTheta(QlBlackCalculator* o, double spot, double maturity, char **e);
  double qlBlackCalculatorThetaPerDay(QlBlackCalculator* o, double spot, double maturity, char **e);
  double qlBlackCalculatorValue(QlBlackCalculator* o, char **e);
  double qlBlackCalculatorVanna(QlBlackCalculator* o, double spot, double maturity, char **e);
  double qlBlackCalculatorVega(QlBlackCalculator* o, double maturity, char **e);
  double qlBlackCalculatorVolga(QlBlackCalculator* o, double maturity, char **e);

  void qlFreeBachelierCalculator(QlBachelierCalculator *o);
  double qlBachelierCalculatorAlpha(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorBeta(QlBachelierCalculator* o, char **e);
  QlBachelierCalculator* qlBachelierCalculator1(int optionType, double strike, double forward, double stdDev, double discount, char **e);
  QlBachelierCalculator* qlBachelierCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, char **e);
  double qlBachelierCalculatorDelta(QlBachelierCalculator* o, double spot, char **e);
  double qlBachelierCalculatorDeltaForward(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorDividendRho(QlBachelierCalculator* o, double maturity, char **e);
  double qlBachelierCalculatorElasticity(QlBachelierCalculator* o, double spot, char **e);
  double qlBachelierCalculatorElasticityForward(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorGamma(QlBachelierCalculator* o, double spot, char **e);
  double qlBachelierCalculatorGammaForward(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorItmAssetProbability(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorItmCashProbability(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorRho(QlBachelierCalculator* o, double maturity, char **e);
  double qlBachelierCalculatorStrikeSensitivity(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorStrikeGamma(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorTheta(QlBachelierCalculator* o, double spot, double maturity, char **e);
  double qlBachelierCalculatorThetaPerDay(QlBachelierCalculator* o, double spot, double maturity, char **e);
  double qlBachelierCalculatorValue(QlBachelierCalculator* o, char **e);
  double qlBachelierCalculatorVanna(QlBachelierCalculator* o, double maturity, char **e);
  double qlBachelierCalculatorVega(QlBachelierCalculator* o, double maturity, char **e);
  double qlBachelierCalculatorVolga(QlBachelierCalculator* o, double maturity, char **e);

  QlBlackScholesCalculator* qlBlackScholesCalculator1(int optionType, double strike, double spot, double growth, double stdDev, double discount, char **e);
  QlBlackScholesCalculator* qlBlackScholesCalculator(QlStrikedTypePayoff* payoff, double spot, double growth, double stdDev, double discount, char **e);
  double qlBlackScholesCalculatorDelta(QlBlackScholesCalculator* o, char **e);
  double qlBlackScholesCalculatorElasticity(QlBlackScholesCalculator* o, char **e);
  double qlBlackScholesCalculatorGamma(QlBlackScholesCalculator* o, char **e);
  double qlBlackScholesCalculatorTheta(QlBlackScholesCalculator* o, double maturity, char **e);
  double qlBlackScholesCalculatorThetaPerDay(QlBlackScholesCalculator* o, double maturity, char **e);
  void qlFreeBlackDeltaCalculator(BlackDeltaCalculator *o);
  BlackDeltaCalculator* qlBlackDeltaCalculator(int optionType, int deltaType, double spot, double dDiscount, double fDiscount, double stdDev, char **e);
  double qlBlackDeltaCalculatorDeltaFromStrike(BlackDeltaCalculator* o, double strike, char **e);
  double qlBlackDeltaCalculatorStrikeFromDelta(BlackDeltaCalculator* o, double delta, char **e);
  double qlBlackDeltaCalculatorAtmStrike(BlackDeltaCalculator* o, int atmType, char **e);
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
  QlPricingEngine* qlVarianceGammaEngine(QlVarianceGammaProcess* x0, double absoluteError, char **e);
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
  QlPricingEngine* qlIsdaCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int numericalFix, int accrualBias, int forwardsInCouponPeriod, char **e);
  QlPricingEngine* qlMidPointCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, char **e);
  QlPricingEngine* qlReplicatingVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, double dk, unsigned callStrikesLen, double* callStrikes, unsigned putStrikesLen, double* putStrikes, char **e);
  QlPricingEngine* qlStulzEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, char **e);
  QlPricingEngine* qlLfmSwaptionEngine(QlLiborForwardModel* model, QlYieldTermStructure* discountCurve, char **e);
  QlPricingEngine* qlTreeCapFloorEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeSwaptionEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlTreeVanillaSwapEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, char **e);
  QlPricingEngine* qlFdG2SwaptionEngine(QlG2* model, unsigned tGrid, unsigned xGrid, unsigned yGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e);
  QlPricingEngine* qlFdHullWhiteSwaptionEngine(QlHullWhite* model, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, char **e);

  QlPricingEngine* qlMCVarianceSwapEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCHestonHullWhiteEngine1(int rngtrait, int stattrait, QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCAmericanEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, int antitheticVariateCalibration, unsigned seedCalibration, char **e);
  QlPricingEngine* qlMCBarrierEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, char **e);
  QlPricingEngine* qlMCDigitalEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCDiscreteArithmeticAPEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCDiscreteArithmeticASEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCDiscreteGeometricAPEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanGJRGARCHEngine1(int rngtrait, int stattrait, QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanHestonEngine1(int rngtrait, int stattrait, QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlIntegralHestonVarianceOptionEngine(QlHestonProcess* process, char **e);
  QlPricingEngine* qlMCHullWhiteCapFloorEngine1(int rngtrait, int stattrait, QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCHimalayaEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCPagodaEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCEuropeanBasketEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);
  QlPricingEngine* qlMCAmericanBasketEngine1(int rngtrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, int polynomialType, char **e);
  QlPricingEngine* qlMCPerformanceEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, char **e);

  QlPricingEngine* qlFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, char **e);
  QlPricingEngine* qlFdHestonVanillaEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlFdHestonVanillaEngine1(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlFdHestonVanillaEngine2(QlHestonModel* model, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlFdHestonVanillaEngine3(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, char **e);
  QlPricingEngine* qlFdHestonHullWhiteVanillaEngine(QlHestonModel* model, QlHullWhiteProcess* hwProcess, double corrEquityShortRate, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned rGrid, unsigned dampingSteps, int controlVariate, FdmSchemeDesc *fdScheme, char **e);
  QlPricingEngine* qlFdHestonHullWhiteVanillaEngine1(QlHestonModel* model, QlHullWhiteProcess* hwProcess, unsigned dividendsLen, QlDividend** dividends, double corrEquityShortRate, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned rGrid, unsigned dampingSteps, int controlVariate, FdmSchemeDesc *fdScheme, char **e);
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

  void qlFreeFdmSchemeDesc(FdmSchemeDesc *o);
  void qlFdmRollback(unsigned opSize,
    void (*applyFn)(const double* in, unsigned n, double t1, double t2, double* out),
    void (*applyDirFn)(const double* in, unsigned n, unsigned direction, double t1, double t2, double* out),
    void (*solveSplitFn)(const double* in, unsigned n, unsigned direction, double s, double t1, double t2, double* out),
    void (*stepCondFn)(const double* in, unsigned n, double t, double* out),
    unsigned stoppingTimesLen, double* stoppingTimes,
    FdmSchemeDesc* schemeDesc,
    unsigned gridLen, double* grid,
    double from, double to, unsigned steps, unsigned dampingSteps,
    unsigned* outLen, double** outValues, char **e);
  FdmSchemeDesc* qlFdmSchemeDesc(int type, double theta, double mu, char **e);
  FdmSchemeDesc* qlFdmSchemeDescCraigSneyd(char **e);
  FdmSchemeDesc* qlFdmSchemeDescDouglas(char **e);
  FdmSchemeDesc* qlFdmSchemeDescExplicitEuler(char **e);
  FdmSchemeDesc* qlFdmSchemeDescHundsdorfer(char **e);
  FdmSchemeDesc* qlFdmSchemeDescImplicitEuler(char **e);
  FdmSchemeDesc* qlFdmSchemeDescModifiedCraigSneyd(char **e);
  FdmSchemeDesc* qlFdmSchemeDescModifiedHundsdorfer(char **e);

  void qlFreeFdm1dMesher(QlFdm1dMesher *o);
  void qlFreeFdmMesher(QlFdmMesher *o);
  QlFdm1dMesher* qlPredefined1dMesher(unsigned len, double* points, char **e);
  QlFdm1dMesher* qlUniform1dMesher(double start, double end, unsigned size, char **e);
  QlFdm1dMesher* qlConcentrating1dMesher(double start, double end, unsigned size, double cPointLoc, double cPointDensity, int requireCPoint, char **e);
  QlFdm1dMesher* qlConcentrating1dMesherMulti(double start, double end, unsigned size, unsigned cPointsLen, double* cPointLoc, double* cPointDensity, int* cPointRequire, double tol, char **e);
  QlFdm1dMesher* qlGluedMesher(QlFdm1dMesher* left, QlFdm1dMesher* right, char **e);
  QlFdm1dMesher* qlFdmBlackScholesMesher(unsigned size, QlGeneralizedBlackScholesProcess* process, double maturity, double strike,
    double xMinConstraint, double xMaxConstraint, double eps, double scaleFactor, double cPointLoc, double cPointDensity,
    unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* fdmQuantoHelper, double spotAdjustment, char **e);
  QlFdm1dMesher* qlFdmCev1dMesher(unsigned size, double f0, double alpha, double beta, double maturity, double eps, double scaleFactor, double cPointLoc, double cPointDensity, char **e);
  QlFdm1dMesher* qlExponentialJump1dMesher(unsigned steps, double beta, double jumpIntensity, double eta, double eps, char **e);
  QlFdm1dMesher* qlFdmSimpleProcess1dMesher(unsigned size, QlStochasticProcess1D* process, double maturity, unsigned tAvgSteps, double epsilon, double mandatoryPoint, char **e);
  QlFdm1dMesher* qlFdmHestonVarianceMesher(unsigned size, QlHestonProcess* process, double maturity, unsigned tAvgSteps, double epsilon, double mixingFactor, char **e);
  QlFdm1dMesher* qlFdmHestonLocalVolatilityVarianceMesher(unsigned size, QlHestonProcess* process, QlLocalVolTermStructure* leverageFct, double maturity, unsigned tAvgSteps, double epsilon, double mixingFactor, char **e);
  QlFdmMesher* qlFdmMesherComposite(unsigned meshersLen, QlFdm1dMesher** meshers, char **e);
  void qlFdmMesherLocations(QlFdmMesher* mesher, unsigned direction, unsigned* outLen, double** outValues, char **e);

  // Genuine per-grid-node Haskell callback -- see QuantLib.Method's haddock ("coarsen the
  // language-boundary crossing" exception case) and HsFdmInnerValueCalculator in
  // qlPricingEngine.cpp. Unlike qlFdmRollback's callbacks, these cross once per mesher node
  // (there is no batched "whole-grid inner value" shape, mirroring QuantLib-SWIG's own
  // FdmInnerValueCalculatorDelegate).
  void qlFreeFdmInnerValueCalculator(QlFdmInnerValueCalculator *o);
  QlFdmInnerValueCalculator* qlFdmInnerValueCalculatorFromFunctions(QlFdmMesher* mesher,
    double (*innerValueFn)(const double* loc, unsigned n, double t),
    double (*avgInnerValueFn)(const double* loc, unsigned n, double t),
    char **e);
  // Evaluates calc->innerValue/avgInnerValue at the node given by coords (one index per
  // dimension), building the FdmLinearOpIterator from mesher's own layout.
  double qlFdmInnerValueCalculatorEval(QlFdmInnerValueCalculator* calc, QlFdmMesher* mesher, unsigned ndims, unsigned* coords, double t, char **e);
  double qlFdmInnerValueCalculatorAvgEval(QlFdmInnerValueCalculator* calc, QlFdmMesher* mesher, unsigned ndims, unsigned* coords, double t, char **e);

  // Native FdmInnerValueCalculator subclasses -- see qlPricingEngine.cpp for why none need a
  // dedicated leaf type.
  QlFdmInnerValueCalculator* qlFdmZeroInnerValue(char **e);
  QlFdmInnerValueCalculator* qlFdmCellAveragingInnerValue(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, char **e);
  QlFdmInnerValueCalculator* qlFdmCellAveragingInnerValueMapped(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, double (*mappingFn)(double x), char **e);
  QlFdmInnerValueCalculator* qlFdmLogInnerValue(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, char **e);
  QlFdmInnerValueCalculator* qlFdmLogBasketInnerValue(QlBasketPayoff* payoff, QlFdmMesher* mesher, char **e);
  // exerciseTimes/exerciseDates are parallel arrays of length exDatesLen, zipped into upstream's
  // std::map<Time, Date> exerciseDates argument.
  QlFdmInnerValueCalculator* qlFdmAffineG2ModelSwapInnerValue(QlG2* disModel, QlG2* fwdModel, QlFixedVsFloatingSwap* swap,
    unsigned exDatesLen, double* exerciseTimes, int* exerciseDates, QlFdmMesher* mesher, unsigned direction, char **e);
  QlFdmInnerValueCalculator* qlFdmAffineHullWhiteModelSwapInnerValue(QlHullWhite* disModel, QlHullWhite* fwdModel, QlFixedVsFloatingSwap* swap,
    unsigned exDatesLen, double* exerciseTimes, int* exerciseDates, QlFdmMesher* mesher, unsigned direction, char **e);

  void qlFdmSolve(QlFdmMesher* mesher,
    QlFdmInnerValueCalculator* calculator,
    unsigned opSize,
    void (*applyFn)(const double* in, unsigned n, double t1, double t2, double* out),
    void (*applyDirFn)(const double* in, unsigned n, unsigned direction, double t1, double t2, double* out),
    void (*solveSplitFn)(const double* in, unsigned n, unsigned direction, double s, double t1, double t2, double* out),
    void (*stepCondFn)(const double* in, unsigned n, double t, double* out),
    unsigned stoppingTimesLen, double* stoppingTimes,
    FdmSchemeDesc* schemeDesc,
    double maturity, double to, unsigned steps, unsigned dampingSteps,
    unsigned* outLen, double** outValues, char **e);

  void qlFreeFdmQuantoHelper(QlFdmQuantoHelper *o);
  QlFdmQuantoHelper* qlFdmQuantoHelper(QlYieldTermStructure* rTS, QlYieldTermStructure* fTS, QlBlackVolTermStructure* fxVolTS, double equityFxCorrelation, double exchRateATMlevel, char **e);

  void qlFreeGJRGARCHModel(QlGJRGARCHModel *o);
  void qlFreeHestonModel(QlHestonModel *o);
  void qlFreeBatesModel(QlBatesModel *o);
  void qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o);
  void qlFreeShortRateModel(QlShortRateModel *o);
  void qlFreeAffineModel(QlAffineModel *o);
  void qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o);
  double qlOneFactorAffineModelDiscountBond(QlOneFactorAffineModel* o, double now, double maturity, double rate, char **e);
  double qlHullWhiteConvexityBias(double futurePrice, double t, double T, double sigma, double a, char **e);
  QlAffineModel* qlHullWhiteAsAffineModel(QlHullWhite *o);
  QlAffineModel* qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o);
  void qlFreeLiborForwardModel(QlLiborForwardModel *o);
  QlAffineModel* qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o);
  void qlFreeHullWhite(QlHullWhite *o);
  QlOneFactorAffineModel* qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o);
  void qlFreeCalibratedModel(QlCalibratedModel *o);
  QlBatesModel* qlBatesModel(QlBatesProcess* process, char **e);
  QlShortRateModel* qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, char **e);
  QlOneFactorAffineModel* qlCoxIngersollRoss(double r0, double theta, double k, double sigma, int withFellerConstraint, char **e);
  QlOneFactorAffineModel* qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, int withFellerConstraint, char **e);
  QlG2* qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, char **e);
  QlShortRateModel* qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, char **e);
  QlGJRGARCHModel* qlGJRGARCHModel(QlGJRGARCHProcess* process, char **e);
  QlHestonModel* qlHestonModel(QlHestonProcess* process, char **e);
  QlHullWhite* qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, char **e);
  QlCalibratedModel* qlVarianceGammaModel(QlVarianceGammaProcess* process, char **e);
  QlOneFactorAffineModel* qlVasicek(double r0, double a, double b, double sigma, double lambda, char **e);
  void qlFreeG2(QlG2 *o);
  QlAffineModel* qlG2AsAffineModel(QlG2 *o);
  QlShortRateModel* qlG2AsShortRateModel(QlG2 *o);
  void qlFreeBatesDetJumpModel(QlBatesDetJumpModel *o);
  QlBatesModel* qlBatesDetJumpModelAsBatesModel(QlBatesDetJumpModel *o);
  void qlFreeBatesDoubleExpDetJumpModel(QlBatesDoubleExpDetJumpModel *o);
  QlBatesDoubleExpModel* qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel(QlBatesDoubleExpDetJumpModel *o);
  void qlFreeBatesDoubleExpModel(QlBatesDoubleExpModel *o);
  QlHestonModel* qlBatesDoubleExpModelAsHestonModel(QlBatesDoubleExpModel *o);

  void qlFreeLmCorrelationModel(QlLmCorrelationModel *o);
  void qlFreeLmVolatilityModel(QlLmVolatilityModel *o);
  QlLmCorrelationModel* qlLmConstWrapperCorrelationModel(QlLmCorrelationModel* corrModel, char **e);
  QlLmVolatilityModel* qlLmConstWrapperVolatilityModel(QlLmVolatilityModel* volaModel, char **e);
  QlLmCorrelationModel* qlLmExponentialCorrelationModel(unsigned size, double rho, char **e);
  QlLmVolatilityModel* qlLmFixedVolatilityModel(unsigned volatilitiesLen, double* volatilities, unsigned startTimesLen, double * startTimes, char **e);
  QlLmCorrelationModel* qlLmLinearExponentialCorrelationModel(unsigned size, double rho, double beta, unsigned factors, char **e);
  QlLmVolatilityModel* qlLmLinearExponentialVolatilityModel(unsigned fixingTimesLen, double * fixingTimes, double a, double b, double c, double d, char **e);
  QlLiborForwardModel* qlLiborForwardModel(QlLiborForwardModelProcess* process, QlLmVolatilityModel* volaModel, QlLmCorrelationModel* corrModel, char **e);

  void qlFreeGsr(QlGsr *o);
  void qlFreeMarkovFunctional(QlMarkovFunctional *o);
  void qlFreeGaussian1dModel(QlGaussian1dModel *o);
  QlCalibratedModel* qlGsrAsCalibratedModel(QlGsr *o);
  QlCalibratedModel* qlMarkovFunctionalAsCalibratedModel(QlMarkovFunctional *o);
  QlGaussian1dModel* qlGsrAsGaussian1dModel(QlGsr *o);
  QlGaussian1dModel* qlMarkovFunctionalAsGaussian1dModel(QlMarkovFunctional *o);
  QlGsr* qlGsr(QlYieldTermStructure* termStructure, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, QlQuote** volatilities, QlQuote* reversion, double T, char **e);
  void qlGsrVolatility(QlGsr* o, unsigned *len, double **vs, char **e);
  void qlGsrCalibrateVolatilitiesIterative(QlGsr* o, unsigned helpersLen, QlBlackCalibrationHelper** helpers, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned weightsLen, double* weights, char **e);
  QlMarkovFunctional* qlMarkovFunctional(QlYieldTermStructure* termStructure, double reversion, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, double* volatilities, QlSwaptionVolatilityStructure* swaptionVol, unsigned expiriesLen, int* swaptionExpiries, unsigned tenorsLen, int* tenorQuantity, unsigned, int* tenorUnit, QlSwapIndex* swapIndexBase, unsigned yGridPoints, char **e);
  QlMarkovFunctional* qlMarkovFunctionalCaplet(QlYieldTermStructure* termStructure, double reversion, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, double* volatilities, QlOptionletVolatilityStructure* capletVol, unsigned expiriesLen, int* capletExpiries, QlIborIndex* iborIndex, unsigned yGridPoints, char **e);
  void qlMarkovFunctionalVolatility(QlMarkovFunctional* o, unsigned *len, double **vs, char **e);
  QlPricingEngine* qlGaussian1dSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlYieldTermStructure* discountCurve, int probabilities, char **e);
  QlPricingEngine* qlGaussian1dNonstandardSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlQuote* oas, QlYieldTermStructure* discountCurve, int probabilities, char **e);
  QlPricingEngine* qlGaussian1dFloatFloatSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlQuote* oas, QlYieldTermStructure* discountCurve, int includeTodaysExercise, int probabilities, char **e);
  QlPricingEngine* qlGaussian1dJamshidianSwaptionEngine(QlGaussian1dModel* model, char **e);
  QlPricingEngine* qlGaussian1dCapFloorEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlYieldTermStructure* discountCurve, char **e);

  QlCalibratedModel* qlGJRGARCHModelAsCalibratedModel(QlGJRGARCHModel *o);
  QlCalibratedModel* qlHestonModelAsCalibratedModel(QlHestonModel *o);
  QlHestonModel* qlBatesModelAsHestonModel(QlBatesModel *o);
  QlCalibratedModel* qlLiborForwardModelAsCalibratedModel(QlLiborForwardModel *o);
  QlCalibratedModel* qlPiecewiseTimeDependentHestonModelAsCalibratedModel(QlPiecewiseTimeDependentHestonModel *o);
  QlCalibratedModel* qlShortRateModelAsCalibratedModel(QlShortRateModel *o);
  QlShortRateModel* qlOneFactorAffineModelAsShortRateModel(QlOneFactorAffineModel *o);

  void qlFreeCalibrationHelper(QlCalibrationHelper *o);
  void qlFreeBlackCalibrationHelper(QlBlackCalibrationHelper *o);
  QlCalibrationHelper* qlBlackCalibrationHelperAsCalibrationHelper(QlBlackCalibrationHelper *o);
  void qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, unsigned wLen, double *weights, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned fpLen, int* fixParameters, char **e);
  double qlCalibratedModelValue(QlCalibratedModel* o, unsigned pLen, double* p, unsigned hLen, QlCalibrationHelper** h, char **e);

  void qlBlackCalibrationHelperSetPricingEngine(QlBlackCalibrationHelper* o, QlPricingEngine* engine, char **e);
  QlBlackCalibrationHelper* qlCapHelper(int, int, QlQuote* volatility, QlIborIndex* index, int fixedLegFrequency, DayCounter* fixedLegDayCounter, int includeFirstSwaplet, QlYieldTermStructure* termStructure, int errorType, int type, double shift, char **e);
  QlBlackCalibrationHelper* qlHestonModelHelper(int, int, Calendar* calendar, QlQuote* s0, double strikePrice, QlQuote* volatility, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int errorType, char **e);
  void qlFreeSwaptionHelper(QlSwaptionHelper *o);
  QlBlackCalibrationHelper* qlSwaptionHelperAsBlackCalibrationHelper(QlSwaptionHelper *o);
  QlSwaptionHelper* qlSwaptionHelper(int, int, int, int, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, char **e);
  QlSwaptionHelper* qlSwaptionHelperFromDate(int exerciseDate, int, int, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, char **e);
  QlSwaptionHelper* qlSwaptionHelperFromDates(int exerciseDate, int endDate, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, char **e);
  QlFixedVsFloatingSwap* qlSwaptionHelperUnderlying(QlSwaptionHelper* o, char **e);
  QlSwaption* qlSwaptionHelperSwaption(QlSwaptionHelper* o, char **e);
  void qlBlackCalibrationHelperTimes(QlBlackCalibrationHelper* o, unsigned *len, double **ts, char **e);

  void qlCalibratedModelParams(QlCalibratedModel* o, unsigned *len, double** ps, char **e);
  double qlBlackCalibrationHelperBlackPrice(QlBlackCalibrationHelper* o, double volatility, char **e);
  double qlBlackCalibrationHelperCalibrationError(QlBlackCalibrationHelper* o, char **e);
  double qlBlackCalibrationHelperImpliedVolatility(QlBlackCalibrationHelper* o, double targetValue, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  double qlBlackCalibrationHelperMarketValue(QlBlackCalibrationHelper* o, char **e);
  double qlBlackCalibrationHelperModelValue(QlBlackCalibrationHelper* o, char **e);
  QlQuote* qlBlackCalibrationHelperVolatility(QlBlackCalibrationHelper* o, char **e);

  void qlFreeBlackProcess(QlBlackProcess *o);
  QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o);
  void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o);
  QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o);
  void qlFreeStochasticProcess(QlStochasticProcess *o);
  void qlFreeStochasticProcess1D(QlStochasticProcess1D *o);
  QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o);

  QlBlackProcess* qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e);
  QlGeneralizedBlackScholesProcess* qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e);
  QlGeneralizedBlackScholesProcess* qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e);
  QlGeneralizedBlackScholesProcess* qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int evolDisc, char **e);
  QlGeneralizedBlackScholesProcess* qlGarmanKohlagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e);
  QlGeneralizedBlackScholesProcess* qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, char **e);
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
  QlStochasticProcess* qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, char **e);
  QlStochasticProcess* qlG2Process(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, char **e);
  QlStochasticProcess1D* qlGemanRoncoroniProcess(double x0, double alpha, double beta, double gamma, double delta, double eps, double zeta, double d, double k, double tau, double sig2, double a, double b, double theta1, double theta2, double theta3, double psi, char **e);
  QlStochasticProcess1D* qlGeometricBrownianMotionProcess(double initialValue, double mue, double sigma, char **e);
  QlGJRGARCHProcess* qlGJRGARCHProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double omega, double alpha, double beta, double gamma, double lambda, double daysPerYear, int d, char **e);
  QlHestonProcess* qlHestonProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, int d, char **e);
  QlHullWhiteForwardProcess* qlHullWhiteForwardProcess(QlYieldTermStructure* h, double a, double sigma, char **e);
  QlHullWhiteProcess* qlHullWhiteProcess(QlYieldTermStructure* h, double a, double sigma, char **e);
  QlHybridHestonHullWhiteProcess* qlHybridHestonHullWhiteProcess(QlHestonProcess* hestonProcess, QlHullWhiteForwardProcess* hullWhiteProcess, double corrEquityShortRate, int discretization, char **e);
  QlKlugeExtOUProcess* qlKlugeExtOUProcess(double rho, QlExtOUWithJumpsProcess* kluge, QlExtendedOrnsteinUhlenbeckProcess* extOU, char **e);
  QlLiborForwardModelProcess* qlLiborForwardModelProcess(unsigned size, QlIborIndex* index, char **e);
  void qlLiborForwardModelProcessFixingDates(QlLiborForwardModelProcess* o, unsigned *len, int **dates, char **e);
  void qlLiborForwardModelProcessFixingTimes(QlLiborForwardModelProcess* o, unsigned *len, double **times, char **e);
  Leg* qlLiborForwardModelProcessCashFlows(QlLiborForwardModelProcess* o, double amount, char **e);
  QlIborIndex* qlLiborForwardModelProcessIndex(QlLiborForwardModelProcess* o, char **e);
  QlMerton76Process* qlMerton76Process(QlQuote* stateVariable, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, QlQuote* jumpInt, QlQuote* logJMean, QlQuote* logJVol, int d, char **e);
  QlStochasticProcess1D* qlOrnsteinUhlenbeckProcess(double speed, double vol, double x0, double level, char **e);
  QlVarianceGammaProcess* qlVarianceGammaProcess(QlQuote* s0, QlYieldTermStructure* dividendYield, QlYieldTermStructure* riskFreeRate, double sigma, double nu, double theta, char **e);
  QlStochasticProcessArray* qlStochasticProcessArray(unsigned x0Len, QlStochasticProcess1D** x0, unsigned correlationRows, unsigned correlationCols, double* correlation, char **e);

  void qlFreePathGenerator(PolymorphicPathGenerator *gen);
  PolymorphicPathGenerator *qlPathGenerator(int rngtrait, QlStochasticProcess *p, TimeGrid *t, unsigned seed, unsigned dim, int brownianBridge, char **e);
  PolymorphicPathGenerator *qlSobolPathGenerator(int dir, QlStochasticProcess *p, TimeGrid *t, unsigned seed, unsigned dim, int brownianBridge, char **e);
  SamplePath *qlPathGeneratorNext(PolymorphicPathGenerator *pgen, char **e);
  SamplePath *qlPathGeneratorAntithetic(PolymorphicPathGenerator *pgen, char **e);
  double qlSamplePathWeight(SamplePath *p);
  unsigned qlSamplePathAssetNumber(SamplePath *p);
  unsigned qlSamplePathSize(SamplePath *p);
  void qlFreeSamplePath(SamplePath *p);
  double qlSamplePathAt(SamplePath *p, unsigned asset, unsigned point, char **e);
  void qlSamplePathAssetPath(SamplePath *s, unsigned asset, unsigned *len, double **p, char **e);

  // Standalone gaussian sequence generator -- the primitive MultiPathGenerator consumes, exposed
  // on its own so a Haskell-defined SDE can be evolved in Haskell with no callback per timestep.
  void qlFreeGaussianRsg(PolymorphicGaussianRsg *g);
  PolymorphicGaussianRsg *qlGaussianRsg(int rngtrait, unsigned dimension, unsigned seed, char **e);
  PolymorphicGaussianRsg *qlSobolGaussianRsg(int dir, unsigned dimension, unsigned seed, char **e);
  unsigned qlGaussianRsgDimension(PolymorphicGaussianRsg *g);
  // Draws the next sequence: *values is a fresh qlAllocateDoubles array of *len draws, *weight
  // the sample's weight (1 for every trait bound here, carried through for completeness).
  void qlGaussianRsgNextSequence(PolymorphicGaussianRsg *g, unsigned *len, double **values, double *weight, char **e);
  // Re-reads the sequence last drawn, without advancing the generator.
  void qlGaussianRsgLastSequence(PolymorphicGaussianRsg *g, unsigned *len, double **values, double *weight, char **e);

  void qlLsmRegress(int polynomType, unsigned order, unsigned fitStatesLen, double *fitStates, unsigned fitTargetsLen, double *fitTargets, unsigned evalLen, double *evalStates, unsigned *outLen, double **outValues, char **e);
  void qlLsmRegressMulti(int polynomType, unsigned order, unsigned fitRows, unsigned fitCols, double *fitStates, unsigned fitTargetsLen, double *fitTargets, unsigned evalRows, unsigned evalCols, double *evalStates, unsigned *outLen, double **outValues, char **e);

  double qlUnsafeSabrLogNormalVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, char **e);
  double qlUnsafeShiftedSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e);
  double qlUnsafeSabrNormalVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, char **e);
  double qlUnsafeSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, int volatilityType, char **e);
  double qlSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, int volatilityType, char **e);
  double qlShiftedSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e);
  double qlSabrFlochKennedyVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, char **e);
  void qlValidateSabrParameters(double alpha, double beta, double nu, double rho, char **e);
  void qlSabrGuess(double k_m, double vol_m, double k_0, double vol_0, double k_p, double vol_p, double forward, double expiryTime, double beta, double shift, int volatilityType, unsigned *len, double **out, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
