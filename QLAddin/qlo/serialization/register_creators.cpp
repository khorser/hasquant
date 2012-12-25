
/*  
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov
 
 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// This file was generated automatically by gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      gensrc/gensrc/stubs/stub.serialization.factory

#include <qlo/serialization/serializationfactory.hpp>
#include <qlo/serialization/create/create_all.hpp>

namespace QuantLibAddin {

    void SerializationFactory::registerCreators() {

        // Abcd

        registerCreator("qlAbcdCalibration", create_qlAbcdCalibration);
        registerCreator("qlAbcdFunction", create_qlAbcdFunction);

        // Accounting Engines

        registerCreator("qlAccountingEngine", create_qlAccountingEngine);

        // AlphaForm

        registerCreator("qlAlphaFormInverseLinear", create_qlAlphaFormInverseLinear);
        registerCreator("qlAlphaFormLinearHyperbolic", create_qlAlphaFormLinearHyperbolic);

        // Asset Swap

        registerCreator("qlAssetSwap", create_qlAssetSwap);
        registerCreator("qlAssetSwap2", create_qlAssetSwap2);

        // Bonds

        registerCreator("qlBond", create_qlBond);
        registerCreator("qlCmsRateBond", create_qlCmsRateBond);
        registerCreator("qlFixedRateBond", create_qlFixedRateBond);
        registerCreator("qlFixedRateBond2", create_qlFixedRateBond2);
        registerCreator("qlFloatingRateBond", create_qlFloatingRateBond);
        registerCreator("qlZeroCouponBond", create_qlZeroCouponBond);

        // Brownian Generator

        registerCreator("qlMTBrownianGeneratorFactory", create_qlMTBrownianGeneratorFactory);

        // BTP

        registerCreator("qlBTP", create_qlBTP);
        registerCreator("qlBTP2", create_qlBTP2);
        registerCreator("qlCCTEU", create_qlCCTEU);
        registerCreator("qlRendistatoBasket", create_qlRendistatoBasket);
        registerCreator("qlRendistatoCalculator", create_qlRendistatoCalculator);
        registerCreator("qlRendistatoEquivalentSwapLengthQuote", create_qlRendistatoEquivalentSwapLengthQuote);
        registerCreator("qlRendistatoEquivalentSwapSpreadQuote", create_qlRendistatoEquivalentSwapSpreadQuote);

        // Caps/Floors

        registerCreator("qlCapFloor", create_qlCapFloor);
        registerCreator("qlMakeCapFloor", create_qlMakeCapFloor);

        // Caplet Volatility Term Structures

        registerCreator("qlCapFloorTermVolCurve", create_qlCapFloorTermVolCurve);
        registerCreator("qlCapFloorTermVolSurface", create_qlCapFloorTermVolSurface);
        registerCreator("qlConstantOptionletVolatility", create_qlConstantOptionletVolatility);
        registerCreator("qlOptionletStripper1", create_qlOptionletStripper1);
        registerCreator("qlOptionletStripper2", create_qlOptionletStripper2);
        registerCreator("qlRelinkableHandleOptionletVolatilityStructure", create_qlRelinkableHandleOptionletVolatilityStructure);
        registerCreator("qlSpreadedOptionletVolatility", create_qlSpreadedOptionletVolatility);
        registerCreator("qlStrippedOptionlet", create_qlStrippedOptionlet);
        registerCreator("qlStrippedOptionletAdapter", create_qlStrippedOptionletAdapter);

        // Cms Market

        registerCreator("qlCmsMarket", create_qlCmsMarket);

        // Cms Market Calibration

        registerCreator("qlCmsMarketCalibration", create_qlCmsMarketCalibration);

        // Correlation

        registerCreator("qlCotSwapFromFwdCorrelation", create_qlCotSwapFromFwdCorrelation);
        registerCreator("qlExponentialForwardCorrelation", create_qlExponentialForwardCorrelation);
        registerCreator("qlHistoricalForwardRatesAnalysis", create_qlHistoricalForwardRatesAnalysis);
        registerCreator("qlHistoricalRatesAnalysis", create_qlHistoricalRatesAnalysis);
        registerCreator("qlMarketModelLmLinearExponentialCorrelationModel", create_qlMarketModelLmLinearExponentialCorrelationModel);
        registerCreator("qlTimeHomogeneousForwardCorrelation", create_qlTimeHomogeneousForwardCorrelation);

        // Coupon Vectors

        registerCreator("qlCmsCouponPricer", create_qlCmsCouponPricer);
        registerCreator("qlCmsLeg", create_qlCmsLeg);
        registerCreator("qlCmsZeroLeg", create_qlCmsZeroLeg);
        registerCreator("qlConundrumPricerByNumericalIntegration", create_qlConundrumPricerByNumericalIntegration);
        registerCreator("qlDigitalCmsLeg", create_qlDigitalCmsLeg);
        registerCreator("qlDigitalIborLeg", create_qlDigitalIborLeg);
        registerCreator("qlDigitalReplication", create_qlDigitalReplication);
        registerCreator("qlFixedRateLeg", create_qlFixedRateLeg);
        registerCreator("qlFixedRateLeg2", create_qlFixedRateLeg2);
        registerCreator("qlIborCouponPricer", create_qlIborCouponPricer);
        registerCreator("qlIborLeg", create_qlIborLeg);
        registerCreator("qlRangeAccrualLeg", create_qlRangeAccrualLeg);

        // QuantLib Credit

        registerCreator("qlCreditDefaultSwap", create_qlCreditDefaultSwap);
        registerCreator("qlHazardRateCurve", create_qlHazardRateCurve);
        registerCreator("qlMidPointCdsEngine", create_qlMidPointCdsEngine);
        registerCreator("qlPiecewiseFlatForwardCurve", create_qlPiecewiseFlatForwardCurve);
        registerCreator("qlPiecewiseFlatHazardRateCurve", create_qlPiecewiseFlatHazardRateCurve);
        registerCreator("qlSpreadCdsHelper", create_qlSpreadCdsHelper);
        registerCreator("qlUpfrontCdsHelper", create_qlUpfrontCdsHelper);

        // Ctsmmcapletcalibration

        registerCreator("qlCTSMMCapletAlphaFormCalibration", create_qlCTSMMCapletAlphaFormCalibration);
        registerCreator("qlCTSMMCapletMaxHomogeneityCalibration", create_qlCTSMMCapletMaxHomogeneityCalibration);
        registerCreator("qlCTSMMCapletOriginalCalibration", create_qlCTSMMCapletOriginalCalibration);

        // CurveState

        registerCreator("qlCMSwapCurveState", create_qlCMSwapCurveState);
        registerCreator("qlCoterminalSwapCurveState", create_qlCoterminalSwapCurveState);
        registerCreator("qlLMMCurveState", create_qlLMMCurveState);

        // Default Probability Term Structures

        registerCreator("qlFlatHazardRate", create_qlFlatHazardRate);
        registerCreator("qlRelinkableHandleDefaultProbabilityTermStructure", create_qlRelinkableHandleDefaultProbabilityTermStructure);

        // Driftcalculators

        registerCreator("qlCMSMMDriftCalculator", create_qlCMSMMDriftCalculator);
        registerCreator("qlLMMDriftCalculator", create_qlLMMDriftCalculator);
        registerCreator("qlLMMNormalDriftCalculator", create_qlLMMNormalDriftCalculator);
        registerCreator("qlSMMDriftCalculator", create_qlSMMDriftCalculator);

        // Evolution Description

        registerCreator("qlEvolutionDescription", create_qlEvolutionDescription);
        registerCreator("qlEvolutionDescriptionFromProduct", create_qlEvolutionDescriptionFromProduct);

        // Exercise

        registerCreator("qlAmericanExercise", create_qlAmericanExercise);
        registerCreator("qlBermudanExercise", create_qlBermudanExercise);
        registerCreator("qlEuropeanExercise", create_qlEuropeanExercise);

        // Forward Rate Agreement

        registerCreator("qlFRA", create_qlFRA);

        // Indices

        registerCreator("qlBMAIndex", create_qlBMAIndex);
        registerCreator("qlEonia", create_qlEonia);
        registerCreator("qlEuribor", create_qlEuribor);
        registerCreator("qlEuribor365", create_qlEuribor365);
        registerCreator("qlEuriborSwap", create_qlEuriborSwap);
        registerCreator("qlEuriborSwapIsdaFixA", create_qlEuriborSwapIsdaFixA);
        registerCreator("qlIborIndex", create_qlIborIndex);
        registerCreator("qlLibor", create_qlLibor);
        registerCreator("qlLiborSwap", create_qlLiborSwap);
        registerCreator("qlOvernightIndex", create_qlOvernightIndex);
        registerCreator("qlProxyIbor", create_qlProxyIbor);
        registerCreator("qlSonia", create_qlSonia);
        registerCreator("qlSwapIndex", create_qlSwapIndex);

        // Interpolation

        registerCreator("qlAbcdInterpolation", create_qlAbcdInterpolation);
        registerCreator("qlCubicInterpolation", create_qlCubicInterpolation);
        registerCreator("qlInterpolation", create_qlInterpolation);
        registerCreator("qlInterpolation2D", create_qlInterpolation2D);
        registerCreator("qlMixedLinearCubicInterpolation", create_qlMixedLinearCubicInterpolation);
        registerCreator("qlSABRInterpolation", create_qlSABRInterpolation);

        // Leg

        registerCreator("qlInterestRate", create_qlInterestRate);
        registerCreator("qlLeg", create_qlLeg);
        registerCreator("qlLegFromCapFloor", create_qlLegFromCapFloor);
        registerCreator("qlLegFromSwap", create_qlLegFromSwap);
        registerCreator("qlMultiPhaseLeg", create_qlMultiPhaseLeg);

        // Market Model Evolvers

        registerCreator("qlForwardRateIpc", create_qlForwardRateIpc);
        registerCreator("qlForwardRateNormalPc", create_qlForwardRateNormalPc);
        registerCreator("qlForwardRatePc", create_qlForwardRatePc);

        // MarketModels

        registerCreator("qlAbcdVol", create_qlAbcdVol);
        registerCreator("qlCotSwapToFwdAdapter", create_qlCotSwapToFwdAdapter);
        registerCreator("qlFlatVol", create_qlFlatVol);
        registerCreator("qlFlatVolFactory", create_qlFlatVolFactory);
        registerCreator("qlFwdPeriodAdapter", create_qlFwdPeriodAdapter);
        registerCreator("qlFwdToCotSwapAdapter", create_qlFwdToCotSwapAdapter);
        registerCreator("qlPseudoRootFacade", create_qlPseudoRootFacade);

        // Math

        registerCreator("qlCovarianceDecomposition", create_qlCovarianceDecomposition);
        registerCreator("qlSymmetricSchurDecomposition", create_qlSymmetricSchurDecomposition);

        // Optimization

        registerCreator("qlArmijoLineSearch", create_qlArmijoLineSearch);
        registerCreator("qlConjugateGradient", create_qlConjugateGradient);
        registerCreator("qlEndCriteria", create_qlEndCriteria);
        registerCreator("qlLevenbergMarquardt", create_qlLevenbergMarquardt);
        registerCreator("qlSimplex", create_qlSimplex);
        registerCreator("qlSteepestDescent", create_qlSteepestDescent);

        // Options

        registerCreator("qlBarrierOption", create_qlBarrierOption);
        registerCreator("qlCaAsianOption", create_qlCaAsianOption);
        registerCreator("qlDaAsianOption", create_qlDaAsianOption);
        registerCreator("qlDividendVanillaOption", create_qlDividendVanillaOption);
        registerCreator("qlEuropeanOption", create_qlEuropeanOption);
        registerCreator("qlForwardVanillaOption", create_qlForwardVanillaOption);
        registerCreator("qlQuantoForwardVanillaOption", create_qlQuantoForwardVanillaOption);
        registerCreator("qlQuantoVanillaOption", create_qlQuantoVanillaOption);
        registerCreator("qlVanillaOption", create_qlVanillaOption);

        // Overnight Indexed Swap

        registerCreator("qlMakeDatedOIS", create_qlMakeDatedOIS);
        registerCreator("qlMakeOIS", create_qlMakeOIS);
        registerCreator("qlOvernightIndexedSwap", create_qlOvernightIndexedSwap);
        registerCreator("qlOvernightIndexedSwapFromOISRateHelper", create_qlOvernightIndexedSwapFromOISRateHelper);

        // Payoffs

        registerCreator("qlDoubleStickyRatchetPayoff", create_qlDoubleStickyRatchetPayoff);
        registerCreator("qlRatchetMaxPayoff", create_qlRatchetMaxPayoff);
        registerCreator("qlRatchetMinPayoff", create_qlRatchetMinPayoff);
        registerCreator("qlRatchetPayoff", create_qlRatchetPayoff);
        registerCreator("qlStickyMaxPayoff", create_qlStickyMaxPayoff);
        registerCreator("qlStickyMinPayoff", create_qlStickyMinPayoff);
        registerCreator("qlStickyPayoff", create_qlStickyPayoff);
        registerCreator("qlStrikedTypePayoff", create_qlStrikedTypePayoff);

        // Piecewise Yield Curves

        registerCreator("qlPiecewiseYieldCurve", create_qlPiecewiseYieldCurve);

        // Pricing Engines

        registerCreator("qlAnalyticCapFloorEngine", create_qlAnalyticCapFloorEngine);
        registerCreator("qlBinomialPricingEngine", create_qlBinomialPricingEngine);
        registerCreator("qlBlackCalculator", create_qlBlackCalculator);
        registerCreator("qlBlackCalculator2", create_qlBlackCalculator2);
        registerCreator("qlBlackCapFloorEngine", create_qlBlackCapFloorEngine);
        registerCreator("qlBlackCapFloorEngine2", create_qlBlackCapFloorEngine2);
        registerCreator("qlBlackScholesCalculator", create_qlBlackScholesCalculator);
        registerCreator("qlBlackScholesCalculator2", create_qlBlackScholesCalculator2);
        registerCreator("qlBlackSwaptionEngine", create_qlBlackSwaptionEngine);
        registerCreator("qlBlackSwaptionEngine2", create_qlBlackSwaptionEngine2);
        registerCreator("qlBondEngine", create_qlBondEngine);
        registerCreator("qlDiscountingSwapEngine", create_qlDiscountingSwapEngine);
        registerCreator("qlPricingEngine", create_qlPricingEngine);

        // Processes

        registerCreator("qlGeneralizedBlackScholesProcess", create_qlGeneralizedBlackScholesProcess);

        // Products

        registerCreator("qlMarketModelMultiProductComposite", create_qlMarketModelMultiProductComposite);
        registerCreator("qlMarketModelMultiStepRatchet", create_qlMarketModelMultiStepRatchet);
        registerCreator("qlMarketModelOneStepForwards", create_qlMarketModelOneStepForwards);
        registerCreator("qlMarketModelOneStepOptionlets", create_qlMarketModelOneStepOptionlets);

        // Quotes

        registerCreator("qlCompositeQuote", create_qlCompositeQuote);
        registerCreator("qlEurodollarFuturesImpliedStdDevQuote", create_qlEurodollarFuturesImpliedStdDevQuote);
        registerCreator("qlForwardSwapQuote", create_qlForwardSwapQuote);
        registerCreator("qlForwardValueQuote", create_qlForwardValueQuote);
        registerCreator("qlFuturesConvAdjustmentQuote", create_qlFuturesConvAdjustmentQuote);
        registerCreator("qlImpliedStdDevQuote", create_qlImpliedStdDevQuote);
        registerCreator("qlLastFixingQuote", create_qlLastFixingQuote);
        registerCreator("qlRelinkableHandleQuote", create_qlRelinkableHandleQuote);
        registerCreator("qlSimpleQuote", create_qlSimpleQuote);

        // Random Sequence Generator

        registerCreator("qlFaureRsg", create_qlFaureRsg);
        registerCreator("qlHaltonRsg", create_qlHaltonRsg);
        registerCreator("qlMersenneTwisterRsg", create_qlMersenneTwisterRsg);
        registerCreator("qlSobolRsg", create_qlSobolRsg);

        // Range Accrual

        registerCreator("qlRangeAccrualFloatersCoupon", create_qlRangeAccrualFloatersCoupon);
        registerCreator("qlRangeAccrualFloatersCouponFromLeg", create_qlRangeAccrualFloatersCouponFromLeg);
        registerCreator("qlRangeAccrualPricerByBgm", create_qlRangeAccrualPricerByBgm);

        // RateHelper

        registerCreator("qlBondHelper", create_qlBondHelper);
        registerCreator("qlDatedOISRateHelper", create_qlDatedOISRateHelper);
        registerCreator("qlDepositRateHelper", create_qlDepositRateHelper);
        registerCreator("qlDepositRateHelper2", create_qlDepositRateHelper2);
        registerCreator("qlFixedRateBondHelper", create_qlFixedRateBondHelper);
        registerCreator("qlFraRateHelper", create_qlFraRateHelper);
        registerCreator("qlFraRateHelper2", create_qlFraRateHelper2);
        registerCreator("qlFuturesRateHelper", create_qlFuturesRateHelper);
        registerCreator("qlFuturesRateHelper2", create_qlFuturesRateHelper2);
        registerCreator("qlFuturesRateHelper3", create_qlFuturesRateHelper3);
        registerCreator("qlOISRateHelper", create_qlOISRateHelper);
        registerCreator("qlSwapRateHelper", create_qlSwapRateHelper);
        registerCreator("qlSwapRateHelper2", create_qlSwapRateHelper2);

        // Schedules

        registerCreator("qlSchedule", create_qlSchedule);
        registerCreator("qlScheduleFromDateVector", create_qlScheduleFromDateVector);
        registerCreator("qlScheduleTruncated", create_qlScheduleTruncated);

        // SequenceStatistics

        registerCreator("qlSequenceStatistics", create_qlSequenceStatistics);
        registerCreator("qlSequenceStatistics2", create_qlSequenceStatistics2);
        registerCreator("qlSequenceStatisticsInc", create_qlSequenceStatisticsInc);
        registerCreator("qlSequenceStatisticsInc2", create_qlSequenceStatisticsInc2);

        // Short Rate Models

        registerCreator("qlHullWhite", create_qlHullWhite);
        registerCreator("qlVasicek", create_qlVasicek);

        // Smile Section Structures

        registerCreator("qlFlatSmileSection", create_qlFlatSmileSection);
        registerCreator("qlInterpolatedSmileSection", create_qlInterpolatedSmileSection);
        registerCreator("qlSabrInterpolatedSmileSection", create_qlSabrInterpolatedSmileSection);
        registerCreator("qlSabrInterpolatedSmileSection1", create_qlSabrInterpolatedSmileSection1);
        registerCreator("qlSabrSmileSection", create_qlSabrSmileSection);
        registerCreator("qlSmileSectionFromSabrVolSurface", create_qlSmileSectionFromSabrVolSurface);

        // Statistics

        registerCreator("qlIncrementalStatistics", create_qlIncrementalStatistics);
        registerCreator("qlStatistics", create_qlStatistics);

        // Swap

        registerCreator("qlMakeCms", create_qlMakeCms);
        registerCreator("qlSwap", create_qlSwap);

        // Swaption

        registerCreator("qlMakeSwaption", create_qlMakeSwaption);
        registerCreator("qlSwaption", create_qlSwaption);

        // Swaption Volatility Term Structures

        registerCreator("qlConstantSwaptionVolatility", create_qlConstantSwaptionVolatility);
        registerCreator("qlRelinkableHandleSwaptionVolatilityStructure", create_qlRelinkableHandleSwaptionVolatilityStructure);
        registerCreator("qlSmileSectionByCube", create_qlSmileSectionByCube);
        registerCreator("qlSmileSectionByCube2", create_qlSmileSectionByCube2);
        registerCreator("qlSpreadedSwaptionVolatility", create_qlSpreadedSwaptionVolatility);
        registerCreator("qlSwaptionVTSMatrix", create_qlSwaptionVTSMatrix);
        registerCreator("qlSwaptionVolCube1", create_qlSwaptionVolCube1);
        registerCreator("qlSwaptionVolCube2", create_qlSwaptionVolCube2);

        // Yield Term Structures

        registerCreator("qlDiscountCurve", create_qlDiscountCurve);
        registerCreator("qlFlatForward", create_qlFlatForward);
        registerCreator("qlForwardCurve", create_qlForwardCurve);
        registerCreator("qlForwardSpreadedTermStructure", create_qlForwardSpreadedTermStructure);
        registerCreator("qlImpliedTermStructure", create_qlImpliedTermStructure);
        registerCreator("qlInterpolatedYieldCurve", create_qlInterpolatedYieldCurve);
        registerCreator("qlRelinkableHandleYieldTermStructure", create_qlRelinkableHandleYieldTermStructure);
        registerCreator("qlZeroCurve", create_qlZeroCurve);

        // TimeSeries

        registerCreator("qlTimeSeries", create_qlTimeSeries);
        registerCreator("qlTimeSeriesFromIndex", create_qlTimeSeriesFromIndex);

        // Vanilla Swap

        registerCreator("qlMakeIMMSwap", create_qlMakeIMMSwap);
        registerCreator("qlMakeVanillaSwap", create_qlMakeVanillaSwap);
        registerCreator("qlVanillaSwap", create_qlVanillaSwap);
        registerCreator("qlVanillaSwapFromSwapIndex", create_qlVanillaSwapFromSwapIndex);
        registerCreator("qlVanillaSwapFromSwapRateHelper", create_qlVanillaSwapFromSwapRateHelper);

        // Volatilities

        registerCreator("qlAbcdAtmVolCurve", create_qlAbcdAtmVolCurve);
        registerCreator("qlBlackConstantVol", create_qlBlackConstantVol);
        registerCreator("qlBlackVarianceSurface", create_qlBlackVarianceSurface);
        registerCreator("qlSabrVolSurface", create_qlSabrVolSurface);

        // Market Model Volatility

        registerCreator("qlMarketModelLmExtLinearExponentialVolModel", create_qlMarketModelLmExtLinearExponentialVolModel);
        registerCreator("qlPiecewiseConstantAbcdVariance", create_qlPiecewiseConstantAbcdVariance);

    }

}

