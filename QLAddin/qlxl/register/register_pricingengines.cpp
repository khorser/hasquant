
/*  
 Copyright (C) 2004, 2005, 2006, 2007, 2008 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.excel.register.file

#include <xlsdk/xlsdkdefines.hpp>

// register functions in category Pricingengines with Excel

void registerPricingengines(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAnalyticCapFloorEngine"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x18""qlAnalyticCapFloorEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,HandleModel,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class AnalyticCapFloorEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4A""affine model (providing a discount bond option pricing formula) object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlBachelierBlackFormula"),
            // parameter codes
            TempStrNoSize("\x08""PCEEEPP#"),
            // function display name
            TempStrNoSize("\x17""qlBachelierBlackFormula"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""OptionType,Strike,AtmForwardValue,StdDev,Deflator,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6B""Black style formula when forward is normal rather than log-normal, i.e. essentially the model of Bachelier."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x67""standard deviation, i.e. annualized ABSOLUTE volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlBachelierBlackFormula2"),
            // parameter codes
            TempStrNoSize("\x07""PCEEPP#"),
            // function display name
            TempStrNoSize("\x18""qlBachelierBlackFormula2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""Payoff,AtmForwardValue,StdDev,Deflator,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x99""Black style formula when forward is normal rather than log-normal, i.e. essentially the model of Bachelier. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x67""standard deviation, i.e. annualized ABSOLUTE volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x17""qlBinomialPricingEngine"),
            // parameter codes
            TempStrNoSize("\x09""CCCCNPPL#"),
            // function display name
            TempStrNoSize("\x17""qlBinomialPricingEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,EngineID,ProcessID,TimeSteps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class PricingEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""engine type."),
            TempStrNoSize("\x29""GeneralizedBlackScholesProcess object ID."),
            TempStrNoSize("\x0D""#/time steps."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x11""qlBlackCalculator"),
            // parameter codes
            TempStrNoSize("\x0B""CCCEEEPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlBlackCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,OptionType,Strike,AtmForwardValue,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class BlackCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x12""qlBlackCalculator2"),
            // parameter codes
            TempStrNoSize("\x0A""CCCEEPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlBlackCalculator2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4D""ObjectId,PayoffID,AtmForwardValue,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class BlackCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""StrikedTypePayoff ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorAlpha"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorAlpha"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""returns the alpha of the internal formulation of the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackCalculatorBeta"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x15""qlBlackCalculatorBeta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""returns the beta of the internal formulation of the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorDelta"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorDelta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Spot,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x64""returns the sensitivity to change in the underlying spot price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackCalculatorDeltaForward"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackCalculatorDeltaForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x67""returns the sensitivity to change in the underlying forward price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlBlackCalculatorDividendRho"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x1C""qlBlackCalculatorDividendRho"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""returns the sensitivity to dividend/growth rate for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlBlackCalculatorElasticity"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x1B""qlBlackCalculatorElasticity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Spot,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x79""returns the sensitivity in percent to a percent change in the underlying spot price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlBlackCalculatorElasticityForward"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlBlackCalculatorElasticityForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7C""returns the sensitivity in percent to a percent change in the underlying forward price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorGamma"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorGamma"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Spot,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7D""returns the second order derivative with respect to change in the underlying spot price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackCalculatorGammaForward"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackCalculatorGammaForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x80""returns the second order derivative with respect to change in the underlying forward price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlBlackCalculatorItmAssetProbability"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x24""qlBlackCalculatorItmAssetProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB5""returns the probability of being in the money in the asset martingale measure for the given BlackCalculator object. It is a risk-neutral probability, not the real world probability."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlBlackCalculatorItmCashProbability"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x23""qlBlackCalculatorItmCashProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB4""returns the probability of being in the money in the bond martingale measure for the given BlackCalculator object. It is a risk-neutral probability, not the real world probability."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlBlackCalculatorRho"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x14""qlBlackCalculatorRho"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""returns the sensitivity to discounting rate for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlBlackCalculatorStrikeSensitivity"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlBlackCalculatorStrikeSensitivity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""returns the sensitivity to strike for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorTheta"),
            // parameter codes
            TempStrNoSize("\x06""ECEEP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorTheta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,Spot,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""returns the sensitivity to time to maturity for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlBlackCalculatorThetaPerDay"),
            // parameter codes
            TempStrNoSize("\x06""ECEEP#"),
            // function display name
            TempStrNoSize("\x1C""qlBlackCalculatorThetaPerDay"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,Spot,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x76""returns the sensitivity to time to maturity per day, assuming 365 days per year, for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorValue"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""returns the option value for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackCalculatorVega"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x15""qlBlackCalculatorVega"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""returns the sensitivity to volatility for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackCapFloorEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlBlackCapFloorEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,YieldCurve,VolTS,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackCapFloorEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x27""OptionletVolatilityStructure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCapFloorEngine2"),
            // parameter codes
            TempStrNoSize("\x09""CCCPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCapFloorEngine2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,YieldCurve,Vol,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackCapFloorEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x1C""Term (i.e. flat) volatility."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlBlackFormula"),
            // parameter codes
            TempStrNoSize("\x09""PCEEEPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlBlackFormula"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""OptionType,Strike,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Black 1976 formula for option pricing, using displacement."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlBlackFormula2"),
            // parameter codes
            TempStrNoSize("\x08""PCEEPPP#"),
            // function display name
            TempStrNoSize("\x0F""qlBlackFormula2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""Payoff,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x66""Black 1976 formula for option pricing with displacement. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x20""qlBlackFormulaCashItmProbability"),
            // parameter codes
            TempStrNoSize("\x08""PCEEEPP#"),
            // function display name
            TempStrNoSize("\x20""qlBlackFormulaCashItmProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""OptionType,Strike,AtmForwardValue,StdDev,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x94""Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x21""qlBlackFormulaCashItmProbability2"),
            // parameter codes
            TempStrNoSize("\x07""PCEEPP#"),
            // function display name
            TempStrNoSize("\x21""qlBlackFormulaCashItmProbability2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x32""Payoff,AtmForwardValue,StdDev,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xC2""Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1E""PlainVanillaPayoff  object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlBlackFormulaImpliedStdDev"),
            // parameter codes
            TempStrNoSize("\x0C""PCEEEPPPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlBlackFormulaImpliedStdDev"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x62""OptionType,Strike,AtmForwardValue,OptionPrice,Deflator,Displacement,Guess,Accuracy,MaxIter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x99""Standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula with displacement."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x4B""standard deviation guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlBlackFormulaImpliedStdDev2"),
            // parameter codes
            TempStrNoSize("\x0B""PCEEPPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlBlackFormulaImpliedStdDev2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x59""PayoffID,AtmForwardValue,OptionPrice,Deflator,Displacement,Guess,Accuracy,MaxIter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB5""Standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x4B""standard deviation guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x34""standard deviation accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x28""qlBlackFormulaImpliedStdDevApproximation"),
            // parameter codes
            TempStrNoSize("\x09""PCEEEPPP#"),
            // function display name
            TempStrNoSize("\x28""qlBlackFormulaImpliedStdDevApproximation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4B""OptionType,Strike,AtmForwardValue,OptionPrice,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x9D""Approximation for the standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x29""qlBlackFormulaImpliedStdDevApproximation2"),
            // parameter codes
            TempStrNoSize("\x08""PCEEPPP#"),
            // function display name
            TempStrNoSize("\x29""qlBlackFormulaImpliedStdDevApproximation2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""Payoff,AtmForwardValue,OptionPrice,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xCB""Approximation for the standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBlackFormulaStdDevDerivative"),
            // parameter codes
            TempStrNoSize("\x08""PEEEPPP#"),
            // function display name
            TempStrNoSize("\x1E""qlBlackFormulaStdDevDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""Strike,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB2""Black 1976 formula for the derivative with respect to the standard deviation (annualized percentage volatility times the square root of time to option expiry), with displacement."),
            // parameter descriptions
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlBlackFormulaStdDevDerivative2"),
            // parameter codes
            TempStrNoSize("\x08""PCEEPPP#"),
            // function display name
            TempStrNoSize("\x1F""qlBlackFormulaStdDevDerivative2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""PayoffID,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xCD""Black 1976 formula for the derivative with respect to the standard deviation (annualized percentage volatility times the square root of time to option expiry). It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x18""qlBlackScholesCalculator"),
            // parameter codes
            TempStrNoSize("\x0C""CCCEEPEPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlBlackScholesCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,OptionType,Strike,Spot,Growth,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class BlackScholesCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x2C""growth discount factor. Default value = 1.0."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlBlackScholesCalculator2"),
            // parameter codes
            TempStrNoSize("\x0B""CCCEPEPPPL#"),
            // function display name
            TempStrNoSize("\x19""qlBlackScholesCalculator2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,PayoffID,Spot,Growth,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class BlackScholesCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""StrikedTypePayoff ID."),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x2C""growth discount factor. Default value = 1.0."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorDelta"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorDelta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6B""returns the sensitivity to change in the underlying spot price for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlBlackScholesCalculatorElasticity"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlBlackScholesCalculatorElasticity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x80""returns the sensitivity in percent to a percent change in the underlying spot price for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorGamma"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorGamma"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x84""returns the second order derivative with respect to change in the underlying spot price for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorTheta"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorTheta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""returns the sensitivity to time to maturity for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlBlackScholesCalculatorThetaPerDay"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x23""qlBlackScholesCalculatorThetaPerDay"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7D""returns the sensitivity to time to maturity per day, assuming 365 days per year, for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackSwaptionEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlBlackSwaptionEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,YieldCurve,VolTS,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackSwaptionEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x26""SwaptionVolatilityStructure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackSwaptionEngine2"),
            // parameter codes
            TempStrNoSize("\x09""CCCPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackSwaptionEngine2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,YieldCurve,Vol,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackSwaptionEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1A""cap/floor term volatility."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlBondEngine"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlBondEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class BondEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x17""qlDiscountingSwapEngine"),
            // parameter codes
            TempStrNoSize("\x0A""CCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlDiscountingSwapEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x57""ObjectId,YieldCurve,IncludeSettlDate,SettlementDate,NpvDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class DiscountingSwapEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\xB1""cashflows before this date are not taken into account. If missing it is assumed equal to the discounting yield term structure's reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\xA5""all cashflows are discounted to this date. If missing it is assumed equal to the discounting yield term structure's reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlPricingEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlPricingEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x37""ObjectId,EngineID,ProcessID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class PricingEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""engine type."),
            TempStrNoSize("\x29""GeneralizedBlackScholesProcess object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Pricingengines with Excel

void unregisterPricingengines(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAnalyticCapFloorEngine"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x18""qlAnalyticCapFloorEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,HandleModel,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class AnalyticCapFloorEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4A""affine model (providing a discount bond option pricing formula) object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlAnalyticCapFloorEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlBachelierBlackFormula"),
            // parameter codes
            TempStrNoSize("\x08""PCEEEPP#"),
            // function display name
            TempStrNoSize("\x17""qlBachelierBlackFormula"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""OptionType,Strike,AtmForwardValue,StdDev,Deflator,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6B""Black style formula when forward is normal rather than log-normal, i.e. essentially the model of Bachelier."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x67""standard deviation, i.e. annualized ABSOLUTE volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlBachelierBlackFormula"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlBachelierBlackFormula2"),
            // parameter codes
            TempStrNoSize("\x07""PCEEPP#"),
            // function display name
            TempStrNoSize("\x18""qlBachelierBlackFormula2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""Payoff,AtmForwardValue,StdDev,Deflator,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x99""Black style formula when forward is normal rather than log-normal, i.e. essentially the model of Bachelier. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x67""standard deviation, i.e. annualized ABSOLUTE volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlBachelierBlackFormula2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x17""qlBinomialPricingEngine"),
            // parameter codes
            TempStrNoSize("\x09""CCCCNPPL#"),
            // function display name
            TempStrNoSize("\x17""qlBinomialPricingEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,EngineID,ProcessID,TimeSteps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class PricingEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""engine type."),
            TempStrNoSize("\x29""GeneralizedBlackScholesProcess object ID."),
            TempStrNoSize("\x0D""#/time steps."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlBinomialPricingEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x11""qlBlackCalculator"),
            // parameter codes
            TempStrNoSize("\x0B""CCCEEEPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlBlackCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,OptionType,Strike,AtmForwardValue,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class BlackCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlBlackCalculator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x12""qlBlackCalculator2"),
            // parameter codes
            TempStrNoSize("\x0A""CCCEEPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlBlackCalculator2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4D""ObjectId,PayoffID,AtmForwardValue,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class BlackCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""StrikedTypePayoff ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlBlackCalculator2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorAlpha"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorAlpha"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""returns the alpha of the internal formulation of the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCalculatorAlpha"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackCalculatorBeta"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x15""qlBlackCalculatorBeta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""returns the beta of the internal formulation of the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlBlackCalculatorBeta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorDelta"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorDelta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Spot,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x64""returns the sensitivity to change in the underlying spot price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCalculatorDelta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackCalculatorDeltaForward"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackCalculatorDeltaForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x67""returns the sensitivity to change in the underlying forward price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlBlackCalculatorDeltaForward"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlBlackCalculatorDividendRho"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x1C""qlBlackCalculatorDividendRho"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""returns the sensitivity to dividend/growth rate for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlBlackCalculatorDividendRho"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlBlackCalculatorElasticity"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x1B""qlBlackCalculatorElasticity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Spot,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x79""returns the sensitivity in percent to a percent change in the underlying spot price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlBlackCalculatorElasticity"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlBlackCalculatorElasticityForward"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlBlackCalculatorElasticityForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7C""returns the sensitivity in percent to a percent change in the underlying forward price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlBlackCalculatorElasticityForward"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorGamma"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorGamma"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Spot,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7D""returns the second order derivative with respect to change in the underlying spot price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCalculatorGamma"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackCalculatorGammaForward"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackCalculatorGammaForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x80""returns the second order derivative with respect to change in the underlying forward price for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlBlackCalculatorGammaForward"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlBlackCalculatorItmAssetProbability"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x24""qlBlackCalculatorItmAssetProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB5""returns the probability of being in the money in the asset martingale measure for the given BlackCalculator object. It is a risk-neutral probability, not the real world probability."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlBlackCalculatorItmAssetProbability"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlBlackCalculatorItmCashProbability"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x23""qlBlackCalculatorItmCashProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB4""returns the probability of being in the money in the bond martingale measure for the given BlackCalculator object. It is a risk-neutral probability, not the real world probability."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlBlackCalculatorItmCashProbability"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlBlackCalculatorRho"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x14""qlBlackCalculatorRho"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""returns the sensitivity to discounting rate for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlBlackCalculatorRho"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlBlackCalculatorStrikeSensitivity"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlBlackCalculatorStrikeSensitivity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""returns the sensitivity to strike for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlBlackCalculatorStrikeSensitivity"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorTheta"),
            // parameter codes
            TempStrNoSize("\x06""ECEEP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorTheta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,Spot,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""returns the sensitivity to time to maturity for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCalculatorTheta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlBlackCalculatorThetaPerDay"),
            // parameter codes
            TempStrNoSize("\x06""ECEEP#"),
            // function display name
            TempStrNoSize("\x1C""qlBlackCalculatorThetaPerDay"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,Spot,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x76""returns the sensitivity to time to maturity per day, assuming 365 days per year, for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlBlackCalculatorThetaPerDay"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCalculatorValue"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCalculatorValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""returns the option value for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCalculatorValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackCalculatorVega"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x15""qlBlackCalculatorVega"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""returns the sensitivity to volatility for the given BlackCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::BlackCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlBlackCalculatorVega"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackCapFloorEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlBlackCapFloorEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,YieldCurve,VolTS,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackCapFloorEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x27""OptionletVolatilityStructure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlBlackCapFloorEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCapFloorEngine2"),
            // parameter codes
            TempStrNoSize("\x09""CCCPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCapFloorEngine2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,YieldCurve,Vol,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackCapFloorEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x1C""Term (i.e. flat) volatility."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCapFloorEngine2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlBlackFormula"),
            // parameter codes
            TempStrNoSize("\x09""PCEEEPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlBlackFormula"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""OptionType,Strike,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Black 1976 formula for option pricing, using displacement."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlBlackFormula"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlBlackFormula2"),
            // parameter codes
            TempStrNoSize("\x08""PCEEPPP#"),
            // function display name
            TempStrNoSize("\x0F""qlBlackFormula2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""Payoff,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x66""Black 1976 formula for option pricing with displacement. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlBlackFormula2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x20""qlBlackFormulaCashItmProbability"),
            // parameter codes
            TempStrNoSize("\x08""PCEEEPP#"),
            // function display name
            TempStrNoSize("\x20""qlBlackFormulaCashItmProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""OptionType,Strike,AtmForwardValue,StdDev,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x94""Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlBlackFormulaCashItmProbability"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x21""qlBlackFormulaCashItmProbability2"),
            // parameter codes
            TempStrNoSize("\x07""PCEEPP#"),
            // function display name
            TempStrNoSize("\x21""qlBlackFormulaCashItmProbability2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x32""Payoff,AtmForwardValue,StdDev,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xC2""Black 1976 probability of being in the money (in the bond martingale measure), i.e. N(d2). It is a risk-neutral probability, not the real world one. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1E""PlainVanillaPayoff  object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlBlackFormulaCashItmProbability2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlBlackFormulaImpliedStdDev"),
            // parameter codes
            TempStrNoSize("\x0C""PCEEEPPPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlBlackFormulaImpliedStdDev"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x62""OptionType,Strike,AtmForwardValue,OptionPrice,Deflator,Displacement,Guess,Accuracy,MaxIter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x99""Standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula with displacement."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x4B""standard deviation guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlBlackFormulaImpliedStdDev"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlBlackFormulaImpliedStdDev2"),
            // parameter codes
            TempStrNoSize("\x0B""PCEEPPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlBlackFormulaImpliedStdDev2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x59""PayoffID,AtmForwardValue,OptionPrice,Deflator,Displacement,Guess,Accuracy,MaxIter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB5""Standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x4B""standard deviation guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x34""standard deviation accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlBlackFormulaImpliedStdDev2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x28""qlBlackFormulaImpliedStdDevApproximation"),
            // parameter codes
            TempStrNoSize("\x09""PCEEEPPP#"),
            // function display name
            TempStrNoSize("\x28""qlBlackFormulaImpliedStdDevApproximation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4B""OptionType,Strike,AtmForwardValue,OptionPrice,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x9D""Approximation for the standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula."),
            // parameter descriptions
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlBlackFormulaImpliedStdDevApproximation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x29""qlBlackFormulaImpliedStdDevApproximation2"),
            // parameter codes
            TempStrNoSize("\x08""PCEEPPP#"),
            // function display name
            TempStrNoSize("\x29""qlBlackFormulaImpliedStdDevApproximation2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""Payoff,AtmForwardValue,OptionPrice,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xCB""Approximation for the standard deviation (annualized percentage volatility times the square root of time to option expiry) implied by the Black 1976 formula. It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlBlackFormulaImpliedStdDevApproximation2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBlackFormulaStdDevDerivative"),
            // parameter codes
            TempStrNoSize("\x08""PEEEPPP#"),
            // function display name
            TempStrNoSize("\x1E""qlBlackFormulaStdDevDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""Strike,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xB2""Black 1976 formula for the derivative with respect to the standard deviation (annualized percentage volatility times the square root of time to option expiry), with displacement."),
            // parameter descriptions
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlBlackFormulaStdDevDerivative"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlBlackFormulaStdDevDerivative2"),
            // parameter codes
            TempStrNoSize("\x08""PCEEPPP#"),
            // function display name
            TempStrNoSize("\x1F""qlBlackFormulaStdDevDerivative2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""PayoffID,AtmForwardValue,StdDev,Deflator,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xCD""Black 1976 formula for the derivative with respect to the standard deviation (annualized percentage volatility times the square root of time to option expiry). It uses a PlainVanillaPayoff object as input."),
            // parameter descriptions
            TempStrNoSize("\x1D""PlainVanillaPayoff object ID."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x41""displacement in a displaced diffusion model. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlBlackFormulaStdDevDerivative2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x18""qlBlackScholesCalculator"),
            // parameter codes
            TempStrNoSize("\x0C""CCCEEPEPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlBlackScholesCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,OptionType,Strike,Spot,Growth,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class BlackScholesCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x2C""growth discount factor. Default value = 1.0."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlBlackScholesCalculator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlBlackScholesCalculator2"),
            // parameter codes
            TempStrNoSize("\x0B""CCCEPEPPPL#"),
            // function display name
            TempStrNoSize("\x19""qlBlackScholesCalculator2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,PayoffID,Spot,Growth,StdDev,Deflator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class BlackScholesCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""StrikedTypePayoff ID."),
            TempStrNoSize("\x0B""spot value."),
            TempStrNoSize("\x2C""growth discount factor. Default value = 1.0."),
            TempStrNoSize("\x69""standard deviation, i.e. annualized percentage volatility times the square root of time to option expiry."),
            TempStrNoSize("\x52""Deflator (usually the discount factor, or the annuity, etc.). Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlBlackScholesCalculator2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorDelta"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorDelta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6B""returns the sensitivity to change in the underlying spot price for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlBlackScholesCalculatorDelta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlBlackScholesCalculatorElasticity"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlBlackScholesCalculatorElasticity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x80""returns the sensitivity in percent to a percent change in the underlying spot price for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlBlackScholesCalculatorElasticity"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorGamma"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorGamma"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x84""returns the second order derivative with respect to change in the underlying spot price for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlBlackScholesCalculatorGamma"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorTheta"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackScholesCalculatorTheta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""returns the sensitivity to time to maturity for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlBlackScholesCalculatorTheta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlBlackScholesCalculatorThetaPerDay"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x23""qlBlackScholesCalculatorThetaPerDay"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,TimeToMaturity,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7D""returns the sensitivity to time to maturity per day, assuming 365 days per year, for the given BlackScholesCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::BlackScholesCalculator object"),
            TempStrNoSize("\x1A""time to maturity in years."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlBlackScholesCalculatorThetaPerDay"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBlackSwaptionEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlBlackSwaptionEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,YieldCurve,VolTS,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackSwaptionEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x26""SwaptionVolatilityStructure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlBlackSwaptionEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackSwaptionEngine2"),
            // parameter codes
            TempStrNoSize("\x09""CCCPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackSwaptionEngine2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,YieldCurve,Vol,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class BlackSwaptionEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1A""cap/floor term volatility."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackSwaptionEngine2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlBondEngine"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlBondEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class BondEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlBondEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x17""qlDiscountingSwapEngine"),
            // parameter codes
            TempStrNoSize("\x0A""CCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlDiscountingSwapEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x57""ObjectId,YieldCurve,IncludeSettlDate,SettlementDate,NpvDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class DiscountingSwapEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\xB1""cashflows before this date are not taken into account. If missing it is assumed equal to the discounting yield term structure's reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\xA5""all cashflows are discounted to this date. If missing it is assumed equal to the discounting yield term structure's reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlDiscountingSwapEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlPricingEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlPricingEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x37""ObjectId,EngineID,ProcessID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class PricingEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""engine type."),
            TempStrNoSize("\x29""GeneralizedBlackScholesProcess object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlPricingEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

