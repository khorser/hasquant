#include "qlCallback.h"
#ifdef __cplusplus
extern "C" {
#endif
  typedef QlCallbackArgs FdmCallbackArgs;
  QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, QlError **e);
  QlPricingEngine* qlDiscountingPerpetualFuturesEngine(
    QlYieldTermStructure* domesticDiscountCurve, QlYieldTermStructure* foreignDiscountCurve,
    QlQuote* assetSpot, unsigned fundingTimesLen, double* fundingTimes,
    unsigned fundingRatesLen, double* fundingRates, unsigned interestRateDiffsLen,
    double* interestRateDiffs, int fundingInterpType, double maxT, QlError **e);
  QlPricingEngine* qlRiskyBondEngine(QlDefaultProbabilityTermStructure* defaultTS, double recoveryRate, QlYieldTermStructure* yieldTS, QlError **e);
  QlPricingEngine* qlDiscountingSwapEngine(QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  QlPricingEngine* qlDiscountingFxForwardEngine(QlYieldTermStructure* sourceCurrencyDiscountCurve, QlYieldTermStructure* targetCurrencyDiscountCurve, QlQuote* spotFx, QlError **e);
  QlPricingEngine* qlDiscountingConstNotionalCrossCurrencySwapEngine(Currency* domesticCcy, QlYieldTermStructure* domesticCcyDiscountCurve, Currency* foreignCcy, QlYieldTermStructure* foreignCcyDiscountCurve, QlQuote* spotFX, int includeSettlementDateFlows, int settlementDate, int npvDate, int spotFXSettleDate, QlError **e);
  QlPricingEngine* qlCounterpartyAdjSwapEngine(QlYieldTermStructure* discountCurve, QlQuote* blackVol, QlDefaultProbabilityTermStructure* ctptyDTS, double ctptyRecoveryRate, QlDefaultProbabilityTermStructure* invstDTS, double invstRecoveryRate, QlError **e);
  QlPricingEngine* qlAnalyticBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticTwoAssetBarrierEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, QlQuote* rho, QlError **e);
  QlPricingEngine* qlAnalyticSoftBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticSimpleChooserEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticComplexChooserEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticTwoAssetCorrelationEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, QlQuote* correlation, QlError **e);
  QlPricingEngine* qlAnalyticEuropeanMargrabeEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, QlError **e);
  QlPricingEngine* qlAnalyticAmericanMargrabeEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, QlError **e);
  QlPricingEngine* qlAnalyticWriterExtensibleOptionEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticHolderExtensibleOptionEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticPartialTimeBarrierOptionEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticBinaryBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlFdBlackScholesBarrierEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, QlError **e);
  QlPricingEngine* qlFdHestonBarrierEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlFdHestonBarrierEngine1(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlFdHestonDoubleBarrierEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlBinomialBarrierEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned maxTimeSteps, QlError **e);
  QlPricingEngine* qlVannaVolgaBarrierEngine(QlDeltaVolQuote* atmVol, QlDeltaVolQuote* vol25Put, QlDeltaVolQuote* vol25Call, QlQuote* spotFX, QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS, int adaptVanDelta, double bsPriceWithSmile, QlError **e);
  QlPricingEngine* qlAnalyticDoubleBarrierEngine(QlGeneralizedBlackScholesProcess* process, int series, QlError **e);
  QlPricingEngine* qlVannaVolgaDoubleBarrierEngine(QlDeltaVolQuote* atmVol, QlDeltaVolQuote* vol25Put, QlDeltaVolQuote* vol25Call, QlQuote* spotFX, QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS, int adaptVanDelta, double bsPriceWithSmile, int series, QlError **e);
  QlPricingEngine* qlBinomialDoubleBarrierEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, QlError **e);
  QlPricingEngine* qlMCDoubleBarrierEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlAnalyticCliquetEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticCompoundOptionEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticContinuousFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticContinuousFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticContinuousPartialFloatingLookbackEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticContinuousPartialFixedLookbackEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticContinuousGeometricAveragePriceAsianHestonEngine(QlHestonProcess* process, unsigned summationCutoff, double xiRightLimit, QlError **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianHestonEngine(QlHestonProcess* process, double xiRightLimit, QlError **e);
  QlPricingEngine* qlMCLookbackFixedEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCLookbackFloatingEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCLookbackPartialFixedEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCLookbackPartialFloatingEngine(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlAnalyticDigitalAmericanEngine(QlGeneralizedBlackScholesProcess* x0, QlError **e);
  QlPricingEngine* qlAnalyticDigitalAmericanKOEngine(QlGeneralizedBlackScholesProcess* x0, QlError **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAveragePriceAsianEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlAnalyticDiscreteGeometricAverageStrikeAsianEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlTurnbullWakemanAsianEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlFdBlackScholesAsianEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned aGrid, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlAnalyticDividendEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, unsigned dividendsLen, QlDividend** dividends, QlError **e);
  QlPricingEngine* qlAnalyticEuropeanEngine(QlGeneralizedBlackScholesProcess* x0, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlAnalyticPerformanceEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlForwardEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlForwardBaroneAdesiWhaleyEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlForwardBjerksundStenslandEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlForwardFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, QlError **e);
  QlPricingEngine* qlQuantoEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, QlError **e);
  QlPricingEngine* qlQuantoForwardEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, QlError **e);
  QlPricingEngine* qlQuantoForwardPerformanceEuropeanEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, QlError **e);
  QlPricingEngine* qlQuantoBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, QlError **e);
  QlPricingEngine* qlQuantoDoubleBarrierEngine(QlGeneralizedBlackScholesProcess* process, QlYieldTermStructure* foreignRiskFreeRate, QlBlackVolTermStructure* exchangeRateVolatility, QlQuote* correlation, QlError **e);
  QlPricingEngine* qlMCForwardEuropeanBSEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCForwardEuropeanHestonEngine1(int rngtrait, int stattrait, QlHestonProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, int controlVariate, QlError **e);
  QlPricingEngine* qlAnalyticHestonForwardEuropeanEngine(QlHestonProcess* process, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlBlackCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, QlError **e);
  QlPricingEngine* qlBlackCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, double displacement, QlError **e);
  QlPricingEngine* qlBlackSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, double displacement, int model, QlError **e);
  QlPricingEngine* qlHaganIrregularSwaptionEngine(QlSwaptionVolatilityStructure*, QlYieldTermStructure*, QlError **e);
  QlPricingEngine* qlBlackSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, QlError **e);
  QlPricingEngine* qlBachelierCapFloorEngine1(QlYieldTermStructure* discountCurve, QlOptionletVolatilityStructure* vol, QlError **e);
  QlPricingEngine* qlBachelierCapFloorEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, QlError **e);
  QlPricingEngine* qlBachelierSwaptionEngine(QlYieldTermStructure* discountCurve, QlQuote* vol, DayCounter* dc, int model, QlError **e);
  QlPricingEngine* qlBachelierSwaptionEngine1(QlYieldTermStructure* discountCurve, QlSwaptionVolatilityStructure* vol, QlError **e);

  void qlFreePricingEngine(QlPricingEngine *engine);
  void qlFreeBlackCalculator(QlBlackCalculator *o);
  void qlFreeBlackScholesCalculator(QlBlackScholesCalculator *o);
  QlBlackCalculator* qlBlackScholesCalculatorAsBlackCalculator(QlBlackScholesCalculator *o);

  double qlBlackCalculatorAlpha(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorBeta(QlBlackCalculator* o, QlError **e);
  QlBlackCalculator* qlBlackCalculator1(int optionType, double strike, double forward, double stdDev, double discount, QlError **e);
  QlBlackCalculator* qlBlackCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, QlError **e);
  double qlBlackCalculatorDelta(QlBlackCalculator* o, double spot, QlError **e);
  double qlBlackCalculatorDeltaForward(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorDividendRho(QlBlackCalculator* o, double maturity, QlError **e);
  double qlBlackCalculatorElasticity(QlBlackCalculator* o, double spot, QlError **e);
  double qlBlackCalculatorElasticityForward(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorGamma(QlBlackCalculator* o, double spot, QlError **e);
  double qlBlackCalculatorGammaForward(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorItmAssetProbability(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorItmCashProbability(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorRho(QlBlackCalculator* o, double maturity, QlError **e);
  double qlBlackCalculatorStrikeSensitivity(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorStrikeGamma(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorTheta(QlBlackCalculator* o, double spot, double maturity, QlError **e);
  double qlBlackCalculatorThetaPerDay(QlBlackCalculator* o, double spot, double maturity, QlError **e);
  double qlBlackCalculatorValue(QlBlackCalculator* o, QlError **e);
  double qlBlackCalculatorVanna(QlBlackCalculator* o, double spot, double maturity, QlError **e);
  double qlBlackCalculatorVega(QlBlackCalculator* o, double maturity, QlError **e);
  double qlBlackCalculatorVolga(QlBlackCalculator* o, double maturity, QlError **e);

  void qlFreeBachelierCalculator(QlBachelierCalculator *o);
  double qlBachelierCalculatorAlpha(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorBeta(QlBachelierCalculator* o, QlError **e);
  QlBachelierCalculator* qlBachelierCalculator1(int optionType, double strike, double forward, double stdDev, double discount, QlError **e);
  QlBachelierCalculator* qlBachelierCalculator(QlStrikedTypePayoff* payoff, double forward, double stdDev, double discount, QlError **e);
  double qlBachelierCalculatorDelta(QlBachelierCalculator* o, double spot, QlError **e);
  double qlBachelierCalculatorDeltaForward(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorDividendRho(QlBachelierCalculator* o, double maturity, QlError **e);
  double qlBachelierCalculatorElasticity(QlBachelierCalculator* o, double spot, QlError **e);
  double qlBachelierCalculatorElasticityForward(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorGamma(QlBachelierCalculator* o, double spot, QlError **e);
  double qlBachelierCalculatorGammaForward(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorItmAssetProbability(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorItmCashProbability(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorRho(QlBachelierCalculator* o, double maturity, QlError **e);
  double qlBachelierCalculatorStrikeSensitivity(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorStrikeGamma(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorTheta(QlBachelierCalculator* o, double spot, double maturity, QlError **e);
  double qlBachelierCalculatorThetaPerDay(QlBachelierCalculator* o, double spot, double maturity, QlError **e);
  double qlBachelierCalculatorValue(QlBachelierCalculator* o, QlError **e);
  double qlBachelierCalculatorVanna(QlBachelierCalculator* o, double maturity, QlError **e);
  double qlBachelierCalculatorVega(QlBachelierCalculator* o, double maturity, QlError **e);
  double qlBachelierCalculatorVolga(QlBachelierCalculator* o, double maturity, QlError **e);

  QlBlackScholesCalculator* qlBlackScholesCalculator1(int optionType, double strike, double spot, double growth, double stdDev, double discount, QlError **e);
  QlBlackScholesCalculator* qlBlackScholesCalculator(QlStrikedTypePayoff* payoff, double spot, double growth, double stdDev, double discount, QlError **e);
  double qlBlackScholesCalculatorDelta(QlBlackScholesCalculator* o, QlError **e);
  double qlBlackScholesCalculatorElasticity(QlBlackScholesCalculator* o, QlError **e);
  double qlBlackScholesCalculatorGamma(QlBlackScholesCalculator* o, QlError **e);
  double qlBlackScholesCalculatorTheta(QlBlackScholesCalculator* o, double maturity, QlError **e);
  double qlBlackScholesCalculatorThetaPerDay(QlBlackScholesCalculator* o, double maturity, QlError **e);
  void qlFreeBlackDeltaCalculator(BlackDeltaCalculator *o);
  BlackDeltaCalculator* qlBlackDeltaCalculator(int optionType, int deltaType, double spot, double dDiscount, double fDiscount, double stdDev, QlError **e);
  double qlBlackDeltaCalculatorDeltaFromStrike(BlackDeltaCalculator* o, double strike, QlError **e);
  double qlBlackDeltaCalculatorStrikeFromDelta(BlackDeltaCalculator* o, double delta, QlError **e);
  double qlBlackDeltaCalculatorAtmStrike(BlackDeltaCalculator* o, int atmType, QlError **e);
  double qlQuantLibBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, double displacement, QlError **e);
  double qlQuantLibBlackFormulaCashItmProbability(int optionType, double strike, double forward, double stdDev, double displacement, QlError **e);
  double qlQuantLibBlackFormulaImpliedStdDev(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, double guess, double accuracy, unsigned maxIterations, QlError **e);
  double qlQuantLibBlackFormulaImpliedStdDevApproximation(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, QlError **e);
  double qlQuantLibBlackFormulaStdDevDerivative(double strike, double forward, double stdDev, double discount, double displacement, QlError **e);
  double qlQuantLibBlackFormulaVolDerivative(double strike, double forward, double stdDev, double expiry, double discount, double displacement, QlError **e);
  double qlQuantLibBlackScholesTheta(QlGeneralizedBlackScholesProcess* x0, double value, double delta, double gamma, QlError **e);
  double qlQuantLibBachelierBlackFormula(int optionType, double strike, double forward, double stdDev, double discount, QlError **e);
  double qlQuantLibBlackFormulaForwardDerivative(int optionType, double strike, double forward, double stdDev, double discount, double displacement, QlError **e);
  double qlQuantLibBlackFormulaImpliedStdDevChambers(int optionType, double strike, double forward, double blackPrice, double blackAtmPrice, double discount, double displacement, QlError **e);
  double qlQuantLibBlackFormulaImpliedStdDevApproximationRS(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, QlError **e);
  double qlQuantLibBlackFormulaImpliedStdDevLiRS(int optionType, double strike, double forward, double blackPrice, double discount, double displacement, double guess, double omega, double accuracy, unsigned maxIterations, QlError **e);
  double qlQuantLibBlackFormulaAssetItmProbability(int optionType, double strike, double forward, double stdDev, double displacement, QlError **e);
  double qlQuantLibBlackFormulaStdDevSecondDerivative(double strike, double forward, double stdDev, double discount, double displacement, QlError **e);
  double qlQuantLibBachelierBlackFormulaForwardDerivative(int optionType, double strike, double forward, double stdDev, double discount, QlError **e);
  double qlQuantLibBachelierBlackFormulaImpliedVol(int optionType, double strike, double forward, double tte, double bachelierPrice, double discount, QlError **e);
  double qlQuantLibBachelierBlackFormulaImpliedVolChoi(int optionType, double strike, double forward, double tte, double bachelierPrice, double discount, QlError **e);
  double qlQuantLibBachelierBlackFormulaStdDevDerivative(double strike, double forward, double stdDev, double discount, QlError **e);
  double qlQuantLibBachelierBlackFormulaAssetItmProbability(int optionType, double strike, double forward, double stdDev, QlError **e);
  double qlQuantLibDefaultThetaPerDay(double theta, QlError **e);

  QlPricingEngine* qlAnalyticBSMHullWhiteEngine(double equityShortRateCorrelation, QlGeneralizedBlackScholesProcess* x1, QlHullWhite* x2, QlError **e);
  QlPricingEngine* qlAnalyticCapFloorEngine(QlAffineModel* model, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlAnalyticGJRGARCHEngine(QlGJRGARCHModel* model, QlError **e);
  QlPricingEngine* qlAnalyticHestonEngine(QlHestonModel* model, double relTolerance, unsigned maxEvaluations, QlError **e);
  QlPricingEngine* qlAnalyticH1HWEngine(QlHestonModel* model, QlHullWhite* hullWhiteModel, double rhoSr, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlAnalyticHestonHullWhiteEngine(QlHestonModel* hestonModel, QlHullWhite* hullWhiteModel, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlBatesEngine(QlBatesModel* model, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlFFTVanillaEngine(QlGeneralizedBlackScholesProcess* process, double logStrikeSpacing, QlError **e);
  QlPricingEngine* qlG2SwaptionEngine(QlG2* model, double range, unsigned intervals, QlError **e);
  QlPricingEngine* qlJumpDiffusionEngine(QlMerton76Process* x0, double relativeAccuracy_, unsigned maxIterations, QlError **e);
  QlPricingEngine* qlTreeCapFloorEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeSwaptionEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeVanillaSwapEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlVarianceGammaEngine(QlVarianceGammaProcess* x0, double absoluteError, QlError **e);
  QlPricingEngine* qlAnalyticHestonEngine1(QlHestonModel* model, unsigned integrationOrder, QlError **e);
  int qlAnalyticHestonEngineOptimalControlVariate(double t, double v0, double kappa, double theta, double sigma, double rho);
  QlPricingEngine* qlAnalyticHestonHullWhiteEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double relTolerance, unsigned maxEvaluations, QlError **e);
  QlPricingEngine* qlAnalyticH1HWEngine1(QlHestonModel* model, QlHullWhite* hullWhiteModel, double rhoSr, double relTolerance, unsigned maxEvaluations, QlError **e);
  QlPricingEngine* qlBatesEngine1(QlBatesModel* model, double relTolerance, unsigned maxEvaluations, QlError **e);

  QlPricingEngine* qlBaroneAdesiWhaleyApproximationEngine(QlGeneralizedBlackScholesProcess* x0, QlError **e);
  QlPricingEngine* qlBatesDetJumpEngine1(QlBatesDetJumpModel* model, double relTolerance, unsigned maxEvaluations, QlError **e);
  QlPricingEngine* qlBatesDetJumpEngine(QlBatesDetJumpModel* model, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlBatesDoubleExpDetJumpEngine1(QlBatesDoubleExpDetJumpModel* model, double relTolerance, unsigned maxEvaluations, QlError **e);
  QlPricingEngine* qlBatesDoubleExpDetJumpEngine(QlBatesDoubleExpDetJumpModel* model, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlBatesDoubleExpEngine1(QlBatesDoubleExpModel* model, double relTolerance, unsigned maxEvaluations, QlError **e);
  QlPricingEngine* qlBatesDoubleExpEngine(QlBatesDoubleExpModel* model, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlBjerksundStenslandApproximationEngine(QlGeneralizedBlackScholesProcess* x0, QlError **e);
  QlPricingEngine* qlQdPlusAmericanEngine(QlGeneralizedBlackScholesProcess* process, unsigned interpolationPoints, int solverType, double eps, unsigned maxIter, QlError **e);
  QlPricingEngine* qlQdFpAmericanEngine(QlGeneralizedBlackScholesProcess* process, int scheme, int fpEquation, QlError **e);
  QlPricingEngine* qlContinuousArithmeticAsianVecerEngine(QlGeneralizedBlackScholesProcess* process, QlQuote* currentAverage, int startDate, unsigned timeSteps, unsigned assetSteps, double zMin, double zMax, QlError **e);
  QlPricingEngine* qlBlackCdsOptionEngine(QlDefaultProbabilityTermStructure* probability, double recoveryRate, QlYieldTermStructure* termStructure, QlQuote* vol, QlError **e);
  QlPricingEngine* qlIntegralCdsEngine(int, int, QlDefaultProbabilityTermStructure* x1, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, QlError **e);
  QlPricingEngine* qlIntegralEngine(QlGeneralizedBlackScholesProcess* x0, QlError **e);
  QlPricingEngine* qlJamshidianSwaptionEngine(QlOneFactorAffineModel* model, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlJuQuadraticApproximationEngine(QlGeneralizedBlackScholesProcess* x0, QlError **e);
  QlPricingEngine* qlKirkEngine(QlBlackProcess* process1, QlBlackProcess* process2, double correlation, QlError **e);
  QlPricingEngine* qlIsdaCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int numericalFix, int accrualBias, int forwardsInCouponPeriod, QlError **e);
  QlPricingEngine* qlMidPointCdsEngine(QlDefaultProbabilityTermStructure* x0, double recoveryRate, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, QlError **e);
  // ql/experimental/credit/midpointcdoengine.hpp, integralcdoengine.hpp
  QlPricingEngine* qlMidPointCDOEngine(QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlIntegralCDOEngine(QlYieldTermStructure* discountCurve, int stepLen, int stepUnit, QlError **e);
  // ql/experimental/credit/integralntdengine.hpp -- note integrationStep comes first upstream
  // (opposite order from IntegralCDOEngine's discountCurve-first constructor).
  QlPricingEngine* qlIntegralNtdEngine(int stepLen, int stepUnit, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlReplicatingVarianceSwapEngine(QlGeneralizedBlackScholesProcess* process, double dk, unsigned callStrikesLen, double* callStrikes, unsigned putStrikesLen, double* putStrikes, QlError **e);
  QlPricingEngine* qlStulzEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, QlError **e);
  QlPricingEngine* qlBjerksundStenslandSpreadEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, QlError **e);
  QlPricingEngine* qlOperatorSplittingSpreadEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, int order, QlError **e);
  QlPricingEngine* qlPearsonSpreadEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, double integrationTolerance, unsigned maxIntegrationIterations, double nStd, QlError **e);
  QlPricingEngine* qlGaussianCopulaSpreadEngine(QlGeneralizedBlackScholesProcess* process1, QlGeneralizedBlackScholesProcess* process2, double correlation, unsigned nPoints, QlError **e);
  QlPricingEngine* qlFd2dBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* p1, QlGeneralizedBlackScholesProcess* p2, double correlation, unsigned xGrid, unsigned yGrid, unsigned tGrid, unsigned dampingSteps, FdmSchemeDesc *schemeDesc, int localVol, double illegalLocalVolOverwrite, QlError **e);
  QlPricingEngine* qlChoiBasketEngine(unsigned processesLen, QlGeneralizedBlackScholesProcess** processes, unsigned rhoRows, unsigned rhoCols, double* rho, double lambda, unsigned maxNrIntegrationSteps, int calcfwdDelta, int controlVariate, QlError **e);
  QlPricingEngine* qlDengLiZhouBasketEngine(unsigned processesLen, QlGeneralizedBlackScholesProcess** processes, unsigned rhoRows, unsigned rhoCols, double* rho, QlError **e);
  QlPricingEngine* qlFdndimBlackScholesVanillaEngine(unsigned processesLen, QlGeneralizedBlackScholesProcess** processes, unsigned rhoRows, unsigned rhoCols, double* rho, unsigned xGridsLen, unsigned* xGrids, unsigned tGrid, unsigned dampingSteps, FdmSchemeDesc *schemeDesc, QlError **e);
  QlPricingEngine* qlFdndimBlackScholesVanillaEngine1(unsigned processesLen, QlGeneralizedBlackScholesProcess** processes, unsigned rhoRows, unsigned rhoCols, double* rho, unsigned xGrid, unsigned tGrid, unsigned dampingSteps, FdmSchemeDesc *schemeDesc, QlError **e);
  QlPricingEngine* qlSingleFactorBsmBasketEngine(unsigned processesLen, QlGeneralizedBlackScholesProcess** processes, double xTol, QlError **e);
  QlPricingEngine* qlLfmSwaptionEngine(QlLiborForwardModel* model, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlTreeCapFloorEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeSwaptionEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeVanillaSwapEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlFdG2SwaptionEngine(QlG2* model, unsigned tGrid, unsigned xGrid, unsigned yGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, QlError **e);
  QlPricingEngine* qlFdHullWhiteSwaptionEngine(QlHullWhite* model, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, double invEps, FdmSchemeDesc *schemeDesc, QlError **e);

  QlPricingEngine* qlMCVarianceSwapEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCHestonHullWhiteEngine1(int rngtrait, int stattrait, QlHybridHestonHullWhiteProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCAmericanEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, int polynomType, unsigned nCalibrationSamples, int antitheticVariateCalibration, unsigned seedCalibration, QlError **e);
  QlPricingEngine* qlMCBarrierEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed, QlError **e);
  QlPricingEngine* qlMCDigitalEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCDiscreteArithmeticAPEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCDiscreteArithmeticASEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCDiscreteGeometricAPEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCDiscreteArithmeticAPHestonEngine1(int rngtrait, int stattrait, QlHestonProcess* process, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned timeSteps, unsigned timeStepsPerYear, int controlVariate, QlError **e);
  QlPricingEngine* qlMCDiscreteGeometricAPHestonEngine1(int rngtrait, int stattrait, QlHestonProcess* process, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned timeSteps, unsigned timeStepsPerYear, QlError **e);
  QlPricingEngine* qlMCEuropeanEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCEuropeanGJRGARCHEngine1(int rngtrait, int stattrait, QlGJRGARCHProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCEuropeanHestonEngine1(int rngtrait, int stattrait, QlHestonProcess* x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlIntegralHestonVarianceOptionEngine(QlHestonProcess* process, QlError **e);
  QlPricingEngine* qlMCHullWhiteCapFloorEngine1(int rngtrait, int stattrait, QlHullWhite* model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCHimalayaEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCPagodaEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCEverestEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCEuropeanBasketEngine1(int rngtrait, int stattrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);
  QlPricingEngine* qlMCAmericanBasketEngine1(int rngtrait, QlStochasticProcessArray* processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, int polynomialType, QlError **e);
  QlPricingEngine* qlMCPerformanceEngine1(int rngtrait, int stattrait, QlGeneralizedBlackScholesProcess* process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, QlError **e);

  QlPricingEngine* qlFdBlackScholesVanillaEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, QlError **e);
  QlPricingEngine* qlFdBlackScholesVanillaEngine1(QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, QlError **e);
  QlPricingEngine* qlFdBlackScholesVanillaEngine2(QlGeneralizedBlackScholesProcess* process, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, QlError **e);
  QlPricingEngine* qlFdBlackScholesVanillaEngine3(QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, int localVol, double illegalLocalVolOverwrite, int cashDividendModel, QlError **e);
  QlPricingEngine* qlFdHestonVanillaEngine(QlHestonModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlFdHestonVanillaEngine1(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlCOSHestonEngine(QlHestonModel* model, double L, unsigned N, QlError **e);
  QlPricingEngine* qlAnalyticPDFHestonEngine(QlHestonModel* model, double eps, unsigned integrationOrder, QlError **e);
  QlPricingEngine* qlFdBatesVanillaEngine(QlBatesModel* model, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlFdBatesVanillaEngine1(QlBatesModel* model, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlFdBlackScholesShoutEngine(QlGeneralizedBlackScholesProcess* process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlFdBlackScholesShoutEngine1(QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlFdHestonVanillaEngine2(QlHestonModel* model, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlFdHestonVanillaEngine3(QlHestonModel* model, unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* quantoHelper, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned dampingSteps, FdmSchemeDesc *fdScheme, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  QlPricingEngine* qlFdHestonHullWhiteVanillaEngine(QlHestonModel* model, QlHullWhiteProcess* hwProcess, double corrEquityShortRate, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned rGrid, unsigned dampingSteps, int controlVariate, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlFdHestonHullWhiteVanillaEngine1(QlHestonModel* model, QlHullWhiteProcess* hwProcess, unsigned dividendsLen, QlDividend** dividends, double corrEquityShortRate, unsigned tGrid, unsigned xGrid, unsigned vGrid, unsigned rGrid, unsigned dampingSteps, int controlVariate, FdmSchemeDesc *fdScheme, QlError **e);
  QlPricingEngine* qlBinomialVanillaEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, QlError **e);
  QlPricingEngine* qlBinomialConvertibleEngine(int tree, QlGeneralizedBlackScholesProcess* process, unsigned timeSteps, QlQuote* creditSpread, unsigned dividendsLen, QlDividend** dividends, QlError **e);
  QlPricingEngine* qlBlackCallableFixedRateBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlBlackCallableFixedRateBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlBlackCallableZeroCouponBondEngine1(QlCallableBondVolatilityStructure* yieldVolStructure, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlBlackCallableZeroCouponBondEngine(QlQuote* fwdYieldVol, QlYieldTermStructure* discountCurve, QlError **e);
  QlPricingEngine* qlTreeCallableFixedRateBondEngine1(QlShortRateModel* x0, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeCallableFixedRateBondEngine(QlShortRateModel* x0, unsigned timeSteps, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeCallableZeroCouponBondEngine1(QlShortRateModel* model, TimeGrid* timeGrid, QlYieldTermStructure* termStructure, QlError **e);
  QlPricingEngine* qlTreeCallableZeroCouponBondEngine(QlShortRateModel* model, unsigned timeSteps, QlYieldTermStructure* termStructure, QlError **e);

  void qlFreeFdmSchemeDesc(FdmSchemeDesc *o);
  void qlFdmRollback(unsigned opSize,
    QlCallback* applyFn,
    QlCallback* applyDirFn,
    QlCallback* solveSplitFn,
    QlCallback* stepCondFn,
    unsigned stoppingTimesLen, double* stoppingTimes,
    FdmSchemeDesc* schemeDesc,
    unsigned gridLen, double* grid,
    double from, double to, unsigned steps, unsigned dampingSteps,
    unsigned* outLen, double** outValues, QlError **e);
  FdmSchemeDesc* qlFdmSchemeDesc(int type, double theta, double mu, QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescCraigSneyd(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescDouglas(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescExplicitEuler(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescHundsdorfer(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescImplicitEuler(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescModifiedCraigSneyd(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescModifiedHundsdorfer(QlError **e);
  FdmSchemeDesc* qlFdmSchemeDescMethodOfLines(double eps, double relInitStepSize, QlError **e);

  void qlFreeFdm1dMesher(QlFdm1dMesher *o);
  void qlFreeFdmMesher(QlFdmMesher *o);
  QlFdm1dMesher* qlPredefined1dMesher(unsigned len, double* points, QlError **e);
  QlFdm1dMesher* qlUniform1dMesher(double start, double end, unsigned size, QlError **e);
  QlFdm1dMesher* qlConcentrating1dMesher(double start, double end, unsigned size, double cPointLoc, double cPointDensity, int requireCPoint, QlError **e);
  QlFdm1dMesher* qlConcentrating1dMesherMulti(double start, double end, unsigned size, unsigned cPointsLen, double* cPointLoc, double* cPointDensity, int* cPointRequire, double tol, QlError **e);
  QlFdm1dMesher* qlGluedMesher(QlFdm1dMesher* left, QlFdm1dMesher* right, QlError **e);
  QlFdm1dMesher* qlFdmBlackScholesMesher(unsigned size, QlGeneralizedBlackScholesProcess* process, double maturity, double strike,
    double xMinConstraint, double xMaxConstraint, double eps, double scaleFactor, double cPointLoc, double cPointDensity,
    unsigned dividendsLen, QlDividend** dividends, QlFdmQuantoHelper* fdmQuantoHelper, double spotAdjustment, QlError **e);
  QlFdm1dMesher* qlFdmCev1dMesher(unsigned size, double f0, double alpha, double beta, double maturity, double eps, double scaleFactor, double cPointLoc, double cPointDensity, QlError **e);
  QlFdm1dMesher* qlExponentialJump1dMesher(unsigned steps, double beta, double jumpIntensity, double eta, double eps, QlError **e);
  QlFdm1dMesher* qlFdmSimpleProcess1dMesher(unsigned size, QlStochasticProcess1D* process, double maturity, unsigned tAvgSteps, double epsilon, double mandatoryPoint, QlError **e);
  QlFdm1dMesher* qlFdmHestonVarianceMesher(unsigned size, QlHestonProcess* process, double maturity, unsigned tAvgSteps, double epsilon, double mixingFactor, QlError **e);
  QlFdm1dMesher* qlFdmHestonLocalVolatilityVarianceMesher(unsigned size, QlHestonProcess* process, QlLocalVolTermStructure* leverageFct, double maturity, unsigned tAvgSteps, double epsilon, double mixingFactor, QlError **e);
  QlFdmMesher* qlFdmMesherComposite(unsigned meshersLen, QlFdm1dMesher** meshers, QlError **e);
  void qlFdmMesherLocations(QlFdmMesher* mesher, unsigned direction, unsigned* outLen, double** outValues, QlError **e);

  // Genuine per-grid-node Haskell callback -- see QuantLib.Method's haddock ("coarsen the
  // language-boundary crossing" exception case) and HsFdmInnerValueCalculator in
  // qlPricingEngine.cpp. Unlike qlFdmRollback's callbacks, these cross once per mesher node
  // (there is no batched "whole-grid inner value" shape, mirroring QuantLib-SWIG's own
  // FdmInnerValueCalculatorDelegate).
  void qlFreeFdmInnerValueCalculator(QlFdmInnerValueCalculator *o);
  QlFdmInnerValueCalculator* qlFdmInnerValueCalculatorFromFunctions(QlFdmMesher* mesher,
    QlCallback* innerValueFn,
    QlCallback* avgInnerValueFn,
    QlError **e);
  // Evaluates calc->innerValue/avgInnerValue at the node given by coords (one index per
  // dimension), building the FdmLinearOpIterator from mesher's own layout.
  double qlFdmInnerValueCalculatorEval(QlFdmInnerValueCalculator* calc, QlFdmMesher* mesher, unsigned ndims, unsigned* coords, double t, QlError **e);
  double qlFdmInnerValueCalculatorAvgEval(QlFdmInnerValueCalculator* calc, QlFdmMesher* mesher, unsigned ndims, unsigned* coords, double t, QlError **e);

  // Native FdmInnerValueCalculator subclasses -- see qlPricingEngine.cpp for why none need a
  // dedicated leaf type.
  QlFdmInnerValueCalculator* qlFdmZeroInnerValue(QlError **e);
  QlFdmInnerValueCalculator* qlFdmCellAveragingInnerValue(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, QlError **e);
  QlFdmInnerValueCalculator* qlFdmCellAveragingInnerValueMapped(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, QlCallback* mappingFn, QlError **e);
  QlFdmInnerValueCalculator* qlFdmLogInnerValue(QlPayoff* payoff, QlFdmMesher* mesher, unsigned direction, QlError **e);
  QlFdmInnerValueCalculator* qlFdmLogBasketInnerValue(QlBasketPayoff* payoff, QlFdmMesher* mesher, QlError **e);
  // exerciseTimes/exerciseDates are parallel arrays of length exDatesLen, zipped into upstream's
  // std::map<Time, Date> exerciseDates argument.
  QlFdmInnerValueCalculator* qlFdmAffineG2ModelSwapInnerValue(QlG2* disModel, QlG2* fwdModel, QlFixedVsFloatingSwap* swap,
    unsigned exDatesLen, double* exerciseTimes, int* exerciseDates, QlFdmMesher* mesher, unsigned direction, QlError **e);
  QlFdmInnerValueCalculator* qlFdmAffineHullWhiteModelSwapInnerValue(QlHullWhite* disModel, QlHullWhite* fwdModel, QlFixedVsFloatingSwap* swap,
    unsigned exDatesLen, double* exerciseTimes, int* exerciseDates, QlFdmMesher* mesher, unsigned direction, QlError **e);

  void qlFdmSolve(QlFdmMesher* mesher,
    QlFdmInnerValueCalculator* calculator,
    unsigned opSize,
    QlCallback* applyFn,
    QlCallback* applyDirFn,
    QlCallback* solveSplitFn,
    QlCallback* stepCondFn,
    unsigned stoppingTimesLen, double* stoppingTimes,
    FdmSchemeDesc* schemeDesc,
    double maturity, double to, unsigned steps, unsigned dampingSteps,
    unsigned* outLen, double** outValues, QlError **e);

  void qlFreeFdmQuantoHelper(QlFdmQuantoHelper *o);
  QlFdmQuantoHelper* qlFdmQuantoHelper(QlYieldTermStructure* rTS, QlYieldTermStructure* fTS, QlBlackVolTermStructure* fxVolTS, double equityFxCorrelation, double exchRateATMlevel, QlError **e);
  double qlFdmQuantoHelperQuantoAdjustment(QlFdmQuantoHelper* helper, double equityVol, double t1, double t2, QlError **e);

  void qlFreeGJRGARCHModel(QlGJRGARCHModel *o);
  void qlFreeHestonModel(QlHestonModel *o);
  void qlFreeBatesModel(QlBatesModel *o);
  void qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o);
  void qlFreeShortRateModel(QlShortRateModel *o);
  void qlFreeAffineModel(QlAffineModel *o);
  double qlAffineModelDiscount(QlAffineModel* o, double t, QlError **e);
  double qlAffineModelDiscountBond(QlAffineModel* o, double now, double maturity, unsigned factorsLen, double* factors, QlError **e);
  double qlAffineModelDiscountBondOption(QlAffineModel* o, int type, double strike, double maturity, int haveBondStart, double bondStart, double bondMaturity, QlError **e);
  void qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o);
  double qlHullWhiteConvexityBias(double futurePrice, double t, double T, double sigma, double a, QlError **e);
  QlAffineModel* qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o);
  void qlFreeLiborForwardModel(QlLiborForwardModel *o);
  QlAffineModel* qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o);
  double qlLiborForwardModelS0(QlLiborForwardModel *o, unsigned alpha, unsigned beta, QlError **e);
  void qlFreeHullWhite(QlHullWhite *o);
  QlOneFactorAffineModel* qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o);
  void qlFreeCalibratedModel(QlCalibratedModel *o);
  QlBatesModel* qlBatesModel(QlBatesProcess* process, QlError **e);
  QlShortRateModel* qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, QlError **e);
  QlOneFactorAffineModel* qlCoxIngersollRoss(double r0, double theta, double k, double sigma, int withFellerConstraint, QlError **e);
  QlOneFactorAffineModel* qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, int withFellerConstraint, QlError **e);
  QlG2* qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, QlError **e);
  QlShortRateModel* qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, QlError **e);
  QlGJRGARCHModel* qlGJRGARCHModel(QlGJRGARCHProcess* process, QlError **e);
  QlHestonModel* qlHestonModel(QlHestonProcess* process, QlError **e);
  QlHullWhite* qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, QlError **e);
  QlCalibratedModel* qlVarianceGammaModel(QlVarianceGammaProcess* process, QlError **e);
  QlOneFactorAffineModel* qlVasicek(double r0, double a, double b, double sigma, double lambda, QlError **e);
  void qlFreeG2(QlG2 *o);
  QlAffineModel* qlG2AsAffineModel(QlG2 *o);
  QlShortRateModel* qlG2AsShortRateModel(QlG2 *o);
  void qlFreeShortRateDynamics(QlShortRateDynamics *o);
  QlShortRateDynamics* qlG2Dynamics(QlG2 *o, QlError **e);
  double qlShortRateDynamicsShortRate(QlShortRateDynamics *o, double t, double x, double y, QlError **e);
  void qlFreeBatesDetJumpModel(QlBatesDetJumpModel *o);
  QlBatesModel* qlBatesDetJumpModelAsBatesModel(QlBatesDetJumpModel *o);
  void qlFreeBatesDoubleExpDetJumpModel(QlBatesDoubleExpDetJumpModel *o);
  QlBatesDoubleExpModel* qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel(QlBatesDoubleExpDetJumpModel *o);
  void qlFreeBatesDoubleExpModel(QlBatesDoubleExpModel *o);
  QlHestonModel* qlBatesDoubleExpModelAsHestonModel(QlBatesDoubleExpModel *o);

  void qlFreeLmCorrelationModel(QlLmCorrelationModel *o);
  void qlFreeLmVolatilityModel(QlLmVolatilityModel *o);
  QlLmCorrelationModel* qlLmConstWrapperCorrelationModel(QlLmCorrelationModel* corrModel, QlError **e);
  QlLmVolatilityModel* qlLmConstWrapperVolatilityModel(QlLmVolatilityModel* volaModel, QlError **e);
  QlLmCorrelationModel* qlLmExponentialCorrelationModel(unsigned size, double rho, QlError **e);
  QlLmVolatilityModel* qlLmFixedVolatilityModel(unsigned volatilitiesLen, double* volatilities, unsigned startTimesLen, double * startTimes, QlError **e);
  QlLmCorrelationModel* qlLmLinearExponentialCorrelationModel(unsigned size, double rho, double beta, unsigned factors, QlError **e);
  QlLmVolatilityModel* qlLmLinearExponentialVolatilityModel(unsigned fixingTimesLen, double * fixingTimes, double a, double b, double c, double d, QlError **e);
  QlLiborForwardModel* qlLiborForwardModel(QlLiborForwardModelProcess* process, QlLmVolatilityModel* volaModel, QlLmCorrelationModel* corrModel, QlError **e);
  void qlFreeLfmHullWhiteParameterization(QlLfmHullWhiteParameterization *o);
  QlLfmHullWhiteParameterization* qlLfmHullWhiteParameterization(QlLiborForwardModelProcess* process, QlOptionletVolatilityStructure* capletVol, unsigned correlationRows, unsigned correlationCols, double* correlation, unsigned factors, QlError **e);
  void qlLfmHullWhiteCovariance(QlLfmHullWhiteParameterization* o, double t, unsigned xLen, double* x, unsigned *rows, unsigned *cols, unsigned *len, double **vs, QlError **e);

  void qlFreeGsr(QlGsr *o);
  void qlFreeMarkovFunctional(QlMarkovFunctional *o);
  void qlFreeGaussian1dModel(QlGaussian1dModel *o);
  QlCalibratedModel* qlGsrAsCalibratedModel(QlGsr *o);
  QlCalibratedModel* qlMarkovFunctionalAsCalibratedModel(QlMarkovFunctional *o);
  QlGaussian1dModel* qlGsrAsGaussian1dModel(QlGsr *o);
  QlGaussian1dModel* qlMarkovFunctionalAsGaussian1dModel(QlMarkovFunctional *o);
  QlGsr* qlGsr(QlYieldTermStructure* termStructure, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, QlQuote** volatilities, unsigned reversionsLen, QlQuote** reversions, double T, QlError **e);
  void qlGsrVolatility(QlGsr* o, unsigned *len, double **vs, QlError **e);
  void qlGsrReversion(QlGsr* o, unsigned *len, double **vs, QlError **e);
  void qlGsrMoveVolatility(QlGsr* o, unsigned i, unsigned *len, int **fp, QlError **e);
  void qlGsrMoveReversion(QlGsr* o, unsigned i, unsigned *len, int **fp, QlError **e);
  void qlGsrCalibrateVolatilitiesIterative(QlGsr* o, unsigned helpersLen, QlBlackCalibrationHelper** helpers, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned weightsLen, double* weights, QlError **e);
  void qlGsrCalibrateReversionsIterative(QlGsr* o, unsigned helpersLen, QlBlackCalibrationHelper** helpers, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned weightsLen, double* weights, QlError **e);
  QlMarkovFunctional* qlMarkovFunctional(QlYieldTermStructure* termStructure, double reversion, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, double* volatilities, QlSwaptionVolatilityStructure* swaptionVol, unsigned expiriesLen, int* swaptionExpiries, unsigned tenorsLen, int* tenorQuantity, unsigned, int* tenorUnit, QlSwapIndex* swapIndexBase, unsigned yGridPoints, QlError **e);
  QlMarkovFunctional* qlMarkovFunctionalCaplet(QlYieldTermStructure* termStructure, double reversion, unsigned volstepdatesLen, int* volstepdates, unsigned volatilitiesLen, double* volatilities, QlOptionletVolatilityStructure* capletVol, unsigned expiriesLen, int* capletExpiries, QlIborIndex* iborIndex, unsigned yGridPoints, QlError **e);
  void qlMarkovFunctionalVolatility(QlMarkovFunctional* o, unsigned *len, double **vs, QlError **e);
  double qlGaussian1dModelNumeraire(QlGaussian1dModel* o, int referenceDate, double y, QlYieldTermStructure* yts, QlError **e);
  double qlGaussian1dModelZerobond(QlGaussian1dModel* o, int maturity, int referenceDate, double y, QlYieldTermStructure* yts, QlError **e);
  double qlGaussian1dModelZerobondOption(QlGaussian1dModel* o, int type, int expiry, int valueDate, int maturity, double strike, int referenceDate, double y, QlYieldTermStructure* yts, double yStdDevs, unsigned yGridPoints, int extrapolatePayoff, int flatPayoffExtrapolation, QlError **e);
  double qlGaussian1dModelForwardRate(QlGaussian1dModel* o, int fixing, int referenceDate, double y, QlIborIndex* iborIdx, QlError **e);
  double qlGaussian1dModelSwapRate(QlGaussian1dModel* o, int fixing, int tenorLen, int tenorUnit, int referenceDate, double y, QlSwapIndex* swapIdx, QlError **e);
  double qlGaussian1dModelSwapAnnuity(QlGaussian1dModel* o, int fixing, int tenorLen, int tenorUnit, int referenceDate, double y, QlSwapIndex* swapIdx, QlError **e);
  void qlGaussian1dModelYGrid(QlGaussian1dModel* o, double yStdDevs, int gridPoints, double bigT, double t, double y, unsigned *len, double **out, QlError **e);
  QlStochasticProcess1D* qlGaussian1dModelStateProcess(QlGaussian1dModel* o, QlError **e);
  QlPricingEngine* qlGaussian1dSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlYieldTermStructure* discountCurve, int probabilities, QlError **e);
  QlPricingEngine* qlGaussian1dNonstandardSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlQuote* oas, QlYieldTermStructure* discountCurve, int probabilities, QlError **e);
  QlPricingEngine* qlGaussian1dFloatFloatSwaptionEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlQuote* oas, QlYieldTermStructure* discountCurve, int includeTodaysExercise, int probabilities, QlError **e);
  QlPricingEngine* qlGaussian1dJamshidianSwaptionEngine(QlGaussian1dModel* model, QlError **e);
  QlPricingEngine* qlGaussian1dCapFloorEngine(QlGaussian1dModel* model, int integrationPoints, double stddevs, int extrapolatePayoff, int flatPayoffExtrapolation, QlYieldTermStructure* discountCurve, QlError **e);

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
  void qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, unsigned wLen, double *weights, QlOptimizationMethod* method, QlEndCriteria* endCriteria, Constraint* constraint, unsigned fpLen, int* fixParameters, QlError **e);
  double qlCalibratedModelValue(QlCalibratedModel* o, unsigned pLen, double* p, unsigned hLen, QlCalibrationHelper** h, QlError **e);

  void qlBlackCalibrationHelperSetPricingEngine(QlBlackCalibrationHelper* o, QlPricingEngine* engine, QlError **e);
  QlBlackCalibrationHelper* qlCapHelper(int, int, QlQuote* volatility, QlIborIndex* index, int fixedLegFrequency, DayCounter* fixedLegDayCounter, int includeFirstSwaplet, QlYieldTermStructure* termStructure, int errorType, int type, double shift, QlError **e);
  QlBlackCalibrationHelper* qlHestonModelHelper(int, int, Calendar* calendar, QlQuote* s0, double strikePrice, QlQuote* volatility, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int errorType, QlError **e);
  void qlFreeSwaptionHelper(QlSwaptionHelper *o);
  QlBlackCalibrationHelper* qlSwaptionHelperAsBlackCalibrationHelper(QlSwaptionHelper *o);
  QlSwaptionHelper* qlSwaptionHelper(int, int, int, int, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, QlError **e);
  QlSwaptionHelper* qlSwaptionHelperFromDate(int exerciseDate, int, int, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, QlError **e);
  QlSwaptionHelper* qlSwaptionHelperFromDates(int exerciseDate, int endDate, QlQuote* volatility, QlIborIndex* index, int, int, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, double strike, double nominal, int volatilityType, double shift, unsigned settlementDays, int averagingMethod, QlError **e);
  QlFixedVsFloatingSwap* qlSwaptionHelperUnderlying(QlSwaptionHelper* o, QlError **e);
  QlSwaption* qlSwaptionHelperSwaption(QlSwaptionHelper* o, QlError **e);
  void qlBlackCalibrationHelperTimes(QlBlackCalibrationHelper* o, unsigned *len, double **ts, QlError **e);

  void qlCalibratedModelParams(QlCalibratedModel* o, unsigned *len, double** ps, QlError **e);
  void qlCalibratedModelSetParams(QlCalibratedModel* o, unsigned pLen, double* p, QlError **e);
  double qlBlackCalibrationHelperBlackPrice(QlBlackCalibrationHelper* o, double volatility, QlError **e);
  double qlBlackCalibrationHelperCalibrationError(QlBlackCalibrationHelper* o, QlError **e);
  double qlBlackCalibrationHelperImpliedVolatility(QlBlackCalibrationHelper* o, double targetValue, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, QlError **e);
  double qlBlackCalibrationHelperMarketValue(QlBlackCalibrationHelper* o, QlError **e);
  double qlBlackCalibrationHelperModelValue(QlBlackCalibrationHelper* o, QlError **e);
  QlQuote* qlBlackCalibrationHelperVolatility(QlBlackCalibrationHelper* o, QlError **e);

  void qlFreeBlackProcess(QlBlackProcess *o);
  QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o);
  void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o);
  QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o);
  void qlFreeStochasticProcess(QlStochasticProcess *o);
  void qlFreeStochasticProcess1D(QlStochasticProcess1D *o);
  QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o);
  unsigned qlStochasticProcessFactors(QlStochasticProcess* o, QlError **e);
  void qlStochasticProcessInitialValues(QlStochasticProcess* o, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessDrift(QlStochasticProcess* o, double t, unsigned xLen, double *x, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessDiffusion(QlStochasticProcess* o, double t, unsigned xLen, double *x, unsigned *rows, unsigned *cols, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessExpectation(QlStochasticProcess* o, double t0, unsigned x0Len, double *x0, double dt, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessStdDeviation(QlStochasticProcess* o, double t0, unsigned x0Len, double *x0, double dt, unsigned *rows, unsigned *cols, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessCovariance(QlStochasticProcess* o, double t0, unsigned x0Len, double *x0, double dt, unsigned *rows, unsigned *cols, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessApply(QlStochasticProcess* o, unsigned x0Len, double *x0, unsigned dxLen, double *dx, unsigned *len, double **vs, QlError **e);
  void qlStochasticProcessEvolve(QlStochasticProcess* o, double t0, unsigned x0Len, double *x0, double dt, unsigned dwLen, double *dw, unsigned *len, double **vs, QlError **e);

  QlBlackProcess* qlBlackProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, QlError **e);
  QlGeneralizedBlackScholesProcess* qlBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, QlError **e);
  QlGeneralizedBlackScholesProcess* qlBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, QlError **e);
  QlGeneralizedBlackScholesProcess* qlExtendedBlackScholesMertonProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int evolDisc, QlError **e);
  QlGeneralizedBlackScholesProcess* qlGarmanKohlhagenProcess(QlQuote* x0, QlYieldTermStructure* foreignRiskFreeTS, QlYieldTermStructure* domesticRiskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, QlError **e);
  QlGeneralizedBlackScholesProcess* qlGeneralizedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, int d, int forceDiscretization, QlError **e);
  QlStochasticProcess1D* qlSquareRootProcess(double b, double a, double sigma, double x0, int d, QlError **e);
  QlGeneralizedBlackScholesProcess* qlVegaStressedBlackScholesProcess(QlQuote* x0, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, double lowerTimeBorderForStressTest, double upperTimeBorderForStressTest, double lowerAssetBorderForStressTest, double upperAssetBorderForStressTest, double stressLevel, int d, QlError **e);

  void qlFreeExtOUWithJumpsProcess(QlExtOUWithJumpsProcess *o);
  QlStochasticProcess* qlExtOUWithJumpsProcessAsStochasticProcess(QlExtOUWithJumpsProcess *o);
  void qlFreeExtendedOrnsteinUhlenbeckProcess(QlExtendedOrnsteinUhlenbeckProcess *o);
  QlStochasticProcess1D* qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D(QlExtendedOrnsteinUhlenbeckProcess *o);
  // The returned process retains shared ownership of b.
  QlExtendedOrnsteinUhlenbeckProcess* qlExtendedOrnsteinUhlenbeckProcess(double speed, double sigma, double x0, QlCallback* b, int discretization, double intEps, QlError **e);
  QlExtendedOrnsteinUhlenbeckProcess* qlLinearSeasonalOrnsteinUhlenbeckProcess(double speed, double sigma, double x0, double a, double k, double c, double phase, int discretization, double intEps, QlError **e);
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
  void qlHullWhiteForwardProcessSetForwardMeasureTime(QlHullWhiteForwardProcess* o, double t, QlError **e);
  double qlHullWhiteProcessAlpha(QlHullWhiteProcess* o, double t, QlError **e);
  double qlHullWhiteForwardProcessAlpha(QlHullWhiteForwardProcess* o, double t, QlError **e);
  double qlHullWhiteForwardProcessB(QlHullWhiteForwardProcess* o, double t, double T, QlError **e);
  double qlHullWhiteForwardProcessMT(QlHullWhiteForwardProcess* o, double s, double t, double T, QlError **e);
  double qlHybridHestonHullWhiteProcessNumeraire(QlHybridHestonHullWhiteProcess* o, double t, unsigned xLen, double *x, QlError **e);

  void qlFreeG2Process(QlG2Process *o);
  QlStochasticProcess* qlG2ProcessAsStochasticProcess(QlG2Process *o);
  double qlG2ProcessPhi(QlG2Process* o, double t, QlError **e);
  double qlG2ProcessShortRate(QlG2Process* o, double t, double x, double y);
  void qlFreeG2ForwardProcess(QlG2ForwardProcess *o);
  QlStochasticProcess* qlG2ForwardProcessAsStochasticProcess(QlG2ForwardProcess *o);
  double qlG2ForwardProcessPhi(QlG2ForwardProcess* o, double t, QlError **e);
  double qlG2ForwardProcessShortRate(QlG2ForwardProcess* o, double t, double x, double y);
  void qlG2ForwardProcessSetForwardMeasureTime(QlG2ForwardProcess* o, double t, QlError **e);

  QlBatesProcess* qlBatesProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, double lambda, double nu, double delta, int d, QlError **e);
  QlExtOUWithJumpsProcess* qlExtOUWithJumpsProcess(QlExtendedOrnsteinUhlenbeckProcess* process, double Y0, double beta, double jumpIntensity, double eta, QlError **e);
  QlG2ForwardProcess* qlG2ForwardProcess(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, QlError **e);
  QlG2Process* qlG2Process(double a, double sigma, double b, double eta, double rho, QlYieldTermStructure* termStructure, QlError **e);
  QlStochasticProcess1D* qlGemanRoncoroniProcess(double x0, double alpha, double beta, double gamma, double delta, double eps, double zeta, double d, double k, double tau, double sig2, double a, double b, double theta1, double theta2, double theta3, double psi, QlError **e);
  QlStochasticProcess1D* qlGeometricBrownianMotionProcess(double initialValue, double mue, double sigma, QlError **e);
  QlGJRGARCHProcess* qlGJRGARCHProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double omega, double alpha, double beta, double gamma, double lambda, double daysPerYear, int d, QlError **e);
  QlHestonProcess* qlHestonProcess(QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, QlQuote* s0, double v0, double kappa, double theta, double sigma, double rho, int d, QlError **e);
  double qlHestonProcessPdf(QlHestonProcess* o, double x, double v, double t, double eps, QlError **e);
  void qlFreeHestonSLVProcess(QlHestonSLVProcess *o);
  QlStochasticProcess* qlHestonSLVProcessAsStochasticProcess(QlHestonSLVProcess *o);
  QlHestonSLVProcess* qlHestonSLVProcess(QlHestonProcess* hestonProcess, QlLocalVolTermStructure* leverageFct, double mixingFactor, QlError **e);
  void qlFreeBrownianGeneratorFactory(QlBrownianGeneratorFactory *o);
  QlBrownianGeneratorFactory* qlMTBrownianGeneratorFactory(unsigned long seed, QlError **e);
  QlBrownianGeneratorFactory* qlSobolBrownianGeneratorFactory(int ordering, unsigned long seed, int directionIntegers, QlError **e);
  void qlFreeHestonSLVMCModel(QlHestonSLVMCModel *o);
  QlHestonSLVMCModel* qlHestonSLVMCModel(QlLocalVolTermStructure* localVol, QlHestonModel* hestonModel, QlBrownianGeneratorFactory* factory, int endDate, unsigned timeStepsPerYear, unsigned nBins, unsigned calibrationPaths, unsigned mandatoryDatesLen, int* mandatoryDates, double mixingFactor, QlError **e);
  QlLocalVolTermStructure* qlHestonSLVMCModelLeverageFunction(QlHestonSLVMCModel* o, QlError **e);
  void qlFreeHestonSLVFDMModel(QlHestonSLVFDMModel *o);
  QlHestonSLVFDMModel* qlHestonSLVFDMModel(QlLocalVolTermStructure* localVol, QlHestonModel* hestonModel, int endDate,
    unsigned xGrid, unsigned vGrid, unsigned tMaxStepsPerYear, unsigned tMinStepsPerYear, double tStepNumberDecay,
    unsigned nRannacherTimeSteps, unsigned predictionCorretionSteps, double x0Density, double localVolEpsProb,
    unsigned maxIntegrationIterations, double vLowerEps, double vUpperEps, double vMin, double v0Density,
    double vLowerBoundDensity, double vUpperBoundDensity, double leverageFctPropEps, int greensAlgorithm,
    int trafoType, FdmSchemeDesc* schemeDesc, int logging, unsigned mandatoryDatesLen, int* mandatoryDates,
    double mixingFactor, QlError **e);
  QlLocalVolTermStructure* qlHestonSLVFDMModelLeverageFunction(QlHestonSLVFDMModel* o, QlError **e);
  HestonSLVFDMLogEntries* qlHestonSLVFDMModelLogEntries(QlHestonSLVFDMModel* o, QlError **e);
  void qlFreeHestonSLVFDMLogEntries(HestonSLVFDMLogEntries* o);
  unsigned qlHestonSLVFDMLogEntriesSize(HestonSLVFDMLogEntries* o);
  double qlHestonSLVFDMLogEntriesTime(HestonSLVFDMLogEntries* o, unsigned i, QlError **e);
  void qlHestonSLVFDMLogEntriesSpotGrid(HestonSLVFDMLogEntries* o, unsigned i, unsigned* len, double** values, QlError **e);
  void qlHestonSLVFDMLogEntriesVarianceGrid(HestonSLVFDMLogEntries* o, unsigned i, unsigned* len, double** values, QlError **e);
  void qlHestonSLVFDMLogEntriesDensity(HestonSLVFDMLogEntries* o, unsigned i, unsigned* rows, unsigned* cols, unsigned* len, double** values, QlError **e);
  QlHullWhiteForwardProcess* qlHullWhiteForwardProcess(QlYieldTermStructure* h, double a, double sigma, QlError **e);
  QlHullWhiteProcess* qlHullWhiteProcess(QlYieldTermStructure* h, double a, double sigma, QlError **e);
  QlHybridHestonHullWhiteProcess* qlHybridHestonHullWhiteProcess(QlHestonProcess* hestonProcess, QlHullWhiteForwardProcess* hullWhiteProcess, double corrEquityShortRate, int discretization, QlError **e);
  QlKlugeExtOUProcess* qlKlugeExtOUProcess(double rho, QlExtOUWithJumpsProcess* kluge, QlExtendedOrnsteinUhlenbeckProcess* extOU, QlError **e);
  QlLiborForwardModelProcess* qlLiborForwardModelProcess(unsigned size, QlIborIndex* index, QlError **e);
  void qlLiborForwardModelProcessFixingDates(QlLiborForwardModelProcess* o, unsigned *len, int **dates, QlError **e);
  void qlLiborForwardModelProcessFixingTimes(QlLiborForwardModelProcess* o, unsigned *len, double **times, QlError **e);
  Leg* qlLiborForwardModelProcessCashFlows(QlLiborForwardModelProcess* o, double amount, QlError **e);
  QlIborIndex* qlLiborForwardModelProcessIndex(QlLiborForwardModelProcess* o, QlError **e);
  void qlLiborForwardModelProcessSetCovarParam(QlLiborForwardModelProcess* o, QlLfmHullWhiteParameterization* param, QlError **e);
  void qlLiborForwardModelProcessDiscountBond(QlLiborForwardModelProcess* o, unsigned ratesLen, double *rates, unsigned *len, double **dfs, QlError **e);
  void qlLiborForwardModelProcessAccrualTimes(QlLiborForwardModelProcess* o, unsigned *startLen, double **start, unsigned *endLen, double **end, QlError **e);
  QlMerton76Process* qlMerton76Process(QlQuote* stateVariable, QlYieldTermStructure* dividendTS, QlYieldTermStructure* riskFreeTS, QlBlackVolTermStructure* blackVolTS, QlQuote* jumpInt, QlQuote* logJMean, QlQuote* logJVol, int d, QlError **e);
  QlStochasticProcess1D* qlOrnsteinUhlenbeckProcess(double speed, double vol, double x0, double level, QlError **e);
  QlVarianceGammaProcess* qlVarianceGammaProcess(QlQuote* s0, QlYieldTermStructure* dividendYield, QlYieldTermStructure* riskFreeRate, double sigma, double nu, double theta, QlError **e);
  QlStochasticProcessArray* qlStochasticProcessArray(unsigned x0Len, QlStochasticProcess1D** x0, unsigned correlationRows, unsigned correlationCols, double* correlation, QlError **e);

  void qlFreePathGenerator(PolymorphicPathGenerator *gen);
  PolymorphicPathGenerator *qlPathGenerator(int rngtrait, QlStochasticProcess *p, TimeGrid *t, unsigned seed, unsigned dim, int brownianBridge, QlError **e);
  PolymorphicPathGenerator *qlSobolPathGenerator(int dir, QlStochasticProcess *p, TimeGrid *t, unsigned seed, unsigned dim, int brownianBridge, QlError **e);
  SamplePath *qlPathGeneratorNext(PolymorphicPathGenerator *pgen, QlError **e);
  SamplePath *qlPathGeneratorAntithetic(PolymorphicPathGenerator *pgen, QlError **e);
  double qlSamplePathWeight(SamplePath *p);
  unsigned qlSamplePathAssetNumber(SamplePath *p);
  unsigned qlSamplePathSize(SamplePath *p);
  void qlFreeSamplePath(SamplePath *p);
  double qlSamplePathAt(SamplePath *p, unsigned asset, unsigned point, QlError **e);
  void qlSamplePathAssetPath(SamplePath *s, unsigned asset, unsigned *len, double **p, QlError **e);

  // Standalone gaussian sequence generator -- the primitive MultiPathGenerator consumes, exposed
  // on its own so a Haskell-defined SDE can be evolved in Haskell with no callback per timestep.
  void qlFreeGaussianRsg(PolymorphicGaussianRsg *g);
  PolymorphicGaussianRsg *qlGaussianRsg(int rngtrait, unsigned dimension, unsigned seed, QlError **e);
  PolymorphicGaussianRsg *qlSobolGaussianRsg(int dir, unsigned dimension, unsigned seed, QlError **e);
  unsigned qlGaussianRsgDimension(PolymorphicGaussianRsg *g);
  // Draws the next sequence: *values is a fresh qlAllocateDoubles array of *len draws, *weight
  // the sample's weight (1 for every trait bound here, carried through for completeness).
  void qlGaussianRsgNextSequence(PolymorphicGaussianRsg *g, unsigned *len, double **values, double *weight, QlError **e);
  // Re-reads the sequence last drawn, without advancing the generator.
  void qlGaussianRsgLastSequence(PolymorphicGaussianRsg *g, unsigned *len, double **values, double *weight, QlError **e);

  void qlLsmRegress(int polynomType, unsigned order, unsigned fitStatesLen, double *fitStates, unsigned fitTargetsLen, double *fitTargets, unsigned evalLen, double *evalStates, unsigned *outLen, double **outValues, QlError **e);
  void qlLsmRegressMulti(int polynomType, unsigned order, unsigned fitRows, unsigned fitCols, double *fitStates, unsigned fitTargetsLen, double *fitTargets, unsigned evalRows, unsigned evalCols, double *evalStates, unsigned *outLen, double **outValues, QlError **e);

  double qlUnsafeSabrLogNormalVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, QlError **e);
  double qlUnsafeShiftedSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, double shift, int volatilityType, QlError **e);
  double qlUnsafeSabrNormalVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, QlError **e);
  double qlUnsafeSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, int volatilityType, QlError **e);
  double qlSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, int volatilityType, QlError **e);
  double qlShiftedSabrVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, double shift, int volatilityType, QlError **e);
  double qlSabrFlochKennedyVolatility(double strike, double forward, double expiryTime, double alpha, double beta, double nu, double rho, QlError **e);
  void qlValidateSabrParameters(double alpha, double beta, double nu, double rho, QlError **e);
  void qlSabrGuess(double k_m, double vol_m, double k_0, double vol_0, double k_p, double vol_p, double forward, double expiryTime, double beta, double shift, int volatilityType, unsigned *len, double **out, QlError **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
