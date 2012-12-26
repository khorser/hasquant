
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

// register functions in category Marketmodels with Excel

void registerMarketmodels(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x09""qlAbcdVol"),
            // parameter codes
            TempStrNoSize("\x10""CCEEEEPCCNPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlAbcdVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x74""ObjectId,A,B,C,D,Ks,Correlations,EvolutionDescription,Factors,InitialRates,Displacements,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class AbcdVol and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x32""the a coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x32""the b coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x32""the c coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x32""the d coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x37""K_i adjustment factors in the abcd vol parametrization."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1C""EvolutionDescription object."),
            TempStrNoSize("\x33""number of factors to be retained in the simulation."),
            TempStrNoSize("\x0E""initial rates."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x09""qlAnnuity"),
            // parameter codes
            TempStrNoSize("\x07""PCNNPP#"),
            // function display name
            TempStrNoSize("\x09""qlAnnuity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""CurveState,StartIndex,EndIndex,NumeraireIndex,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns annuity of arbitrary swap-rate."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x0C""start index."),
            TempStrNoSize("\x0A""end index."),
            TempStrNoSize("\x23""numeraire index. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCmSwapForwardJacobian"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlCmSwapForwardJacobian"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x23""CurveState,SpanningForwards,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the jacobian between constant maturity swap rates and forward rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCmSwapZedMatrix"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x11""qlCmSwapZedMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""CurveState,SpanningForwards,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""Returns the Z matrix to switch base from forward to constant maturity swap rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlCoinitialSwapForwardJacobian"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlCoinitialSwapForwardJacobian"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the jacobian between coinitial swap rates and forward rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCoinitialSwapZedMatrix"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlCoinitialSwapZedMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""CurveState,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the Z matrix to switch base from forward to coinitial swap rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCotSwapToFwdAdapter"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlCotSwapToFwdAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,CoterminalModel,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class CotSwapToFwdAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x20""CoTerminal Swap Market Model ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlCoterminalSwapForwardJacobian"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlCoterminalSwapForwardJacobian"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns the jacobian between coterminal swap rates and forward rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x19""qlCoterminalSwapZedMatrix"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x19""qlCoterminalSwapZedMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""CurveState,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Returns the Z matrix to switch base from forward to coterminal swap rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x09""qlFlatVol"),
            // parameter codes
            TempStrNoSize("\x0C""CCPCCNPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlFlatVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x76""ObjectId,Volatilities,Correlations,EvolutionDescription,Factors,InitialRates,Displacements,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class FlatVol and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1C""EvolutionDescription object."),
            TempStrNoSize("\x33""number of factors to be retained in the simulation."),
            TempStrNoSize("\x0E""initial rates."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x10""qlFlatVolFactory"),
            // parameter codes
            TempStrNoSize("\x0C""CCEEPPCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlFlatVolFactory"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,LongTermCorr,Beta,Times,Volatilities,YieldCurve,Displacement,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class FlatVolFactory and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3D""Long term correlation L in rho=L+(1-L)*exp(-beta*abs(Ti-Tj))."),
            TempStrNoSize("\x2A""beta in rho=L+(1-L)*exp(-beta*abs(Ti-Tj))."),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x12""qlFwdPeriodAdapter"),
            // parameter codes
            TempStrNoSize("\x0A""CCCNNPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlFwdPeriodAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4B""ObjectId,LargeModel,Period,Offset,Displacements,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class FwdPeriodAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""large MarketModel ID."),
            TempStrNoSize("\x42""target period (e.g. 2 if going from semiannual LMM to annual LMM)."),
            TempStrNoSize("\x52""rate index offset, in order to pin down swaption coterminal to the last rate time."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlFwdToCotSwapAdapter"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlFwdToCotSwapAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,ForwardModel,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class FwdToCotSwapAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""Forward Rate Market Model ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlMarketModelCovariance"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlMarketModelCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the covariance matrix for the i-th step."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x15""evolution step index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlMarketModelDisplacements"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlMarketModelDisplacements"),
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
            TempStrNoSize("\x2F""rates' displacemets for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlMarketModelInitialRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlMarketModelInitialRates"),
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
            TempStrNoSize("\x29""initial rates for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMarketModelNumberOfFactors"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1C""qlMarketModelNumberOfFactors"),
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
            TempStrNoSize("\x2D""number of factors for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlMarketModelNumberOfRates"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1A""qlMarketModelNumberOfRates"),
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
            TempStrNoSize("\x2B""number of rates for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlMarketModelNumberOfSteps"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1A""qlMarketModelNumberOfSteps"),
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
            TempStrNoSize("\x2B""number of steps for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlMarketModelPseudoRoot"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlMarketModelPseudoRoot"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2A""Returns the pseudo root for the i-th step."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x15""evolution step index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x24""qlMarketModelTimeDependentVolatility"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x24""qlMarketModelTimeDependentVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2A""Returns the time dependent vol for rate i."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x0B""rate index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMarketModelTotalCovariance"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x1C""qlMarketModelTotalCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the covariance matrix from start up to the i-th step."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x15""evolution step index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x12""qlPseudoRootFacade"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x12""qlPseudoRootFacade"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,Calibrator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class PseudoRootFacade and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""CTSMMCapletCalibration ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateInstVolDifferences"),
            // parameter codes
            TempStrNoSize("\x06""PCCNP#"),
            // function display name
            TempStrNoSize("\x18""qlRateInstVolDifferences"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""MarketModel1,MarketModel2,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Compute the differences between volatilities at each evolution step."),
            // parameter descriptions
            TempStrNoSize("\x13""First Market Model."),
            TempStrNoSize("\x14""Second Market Model."),
            TempStrNoSize("\x13""Forward Rate index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlRateVolDifferences"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x14""qlRateVolDifferences"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""MarketModel1,MarketModel2,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Compute the differences between all implied forwards volatilities."),
            // parameter descriptions
            TempStrNoSize("\x13""First Market Model."),
            TempStrNoSize("\x14""Second Market Model."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSwapDerivative"),
            // parameter codes
            TempStrNoSize("\x07""PCNNPP#"),
            // function display name
            TempStrNoSize("\x10""qlSwapDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""CurveState,StartIndex,EndIndex,FwdRateIndex,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""returns derivative of swap-rate to underlying forward rate."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x0C""start index."),
            TempStrNoSize("\x0A""end index."),
            TempStrNoSize("\x26""forward rate index. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Marketmodels with Excel

void unregisterMarketmodels(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x09""qlAbcdVol"),
            // parameter codes
            TempStrNoSize("\x10""CCEEEEPCCNPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlAbcdVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x74""ObjectId,A,B,C,D,Ks,Correlations,EvolutionDescription,Factors,InitialRates,Displacements,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class AbcdVol and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x32""the a coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x32""the b coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x32""the c coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x32""the d coefficient in the abcd vol parametrization."),
            TempStrNoSize("\x37""K_i adjustment factors in the abcd vol parametrization."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1C""EvolutionDescription object."),
            TempStrNoSize("\x33""number of factors to be retained in the simulation."),
            TempStrNoSize("\x0E""initial rates."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlAbcdVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x09""qlAnnuity"),
            // parameter codes
            TempStrNoSize("\x07""PCNNPP#"),
            // function display name
            TempStrNoSize("\x09""qlAnnuity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""CurveState,StartIndex,EndIndex,NumeraireIndex,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns annuity of arbitrary swap-rate."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x0C""start index."),
            TempStrNoSize("\x0A""end index."),
            TempStrNoSize("\x23""numeraire index. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlAnnuity"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCmSwapForwardJacobian"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlCmSwapForwardJacobian"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x23""CurveState,SpanningForwards,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the jacobian between constant maturity swap rates and forward rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCmSwapForwardJacobian"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCmSwapZedMatrix"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x11""qlCmSwapZedMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""CurveState,SpanningForwards,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""Returns the Z matrix to switch base from forward to constant maturity swap rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlCmSwapZedMatrix"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlCoinitialSwapForwardJacobian"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlCoinitialSwapForwardJacobian"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the jacobian between coinitial swap rates and forward rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlCoinitialSwapForwardJacobian"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCoinitialSwapZedMatrix"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlCoinitialSwapZedMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""CurveState,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the Z matrix to switch base from forward to coinitial swap rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlCoinitialSwapZedMatrix"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCotSwapToFwdAdapter"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlCotSwapToFwdAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,CoterminalModel,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class CotSwapToFwdAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x20""CoTerminal Swap Market Model ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlCotSwapToFwdAdapter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlCoterminalSwapForwardJacobian"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlCoterminalSwapForwardJacobian"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns the jacobian between coterminal swap rates and forward rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlCoterminalSwapForwardJacobian"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x19""qlCoterminalSwapZedMatrix"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x19""qlCoterminalSwapZedMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""CurveState,Displacement,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Returns the Z matrix to switch base from forward to coterminal swap rates."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlCoterminalSwapZedMatrix"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x09""qlFlatVol"),
            // parameter codes
            TempStrNoSize("\x0C""CCPCCNPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlFlatVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x76""ObjectId,Volatilities,Correlations,EvolutionDescription,Factors,InitialRates,Displacements,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class FlatVol and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1C""EvolutionDescription object."),
            TempStrNoSize("\x33""number of factors to be retained in the simulation."),
            TempStrNoSize("\x0E""initial rates."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlFlatVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x10""qlFlatVolFactory"),
            // parameter codes
            TempStrNoSize("\x0C""CCEEPPCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlFlatVolFactory"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,LongTermCorr,Beta,Times,Volatilities,YieldCurve,Displacement,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class FlatVolFactory and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3D""Long term correlation L in rho=L+(1-L)*exp(-beta*abs(Ti-Tj))."),
            TempStrNoSize("\x2A""beta in rho=L+(1-L)*exp(-beta*abs(Ti-Tj))."),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlFlatVolFactory"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x12""qlFwdPeriodAdapter"),
            // parameter codes
            TempStrNoSize("\x0A""CCCNNPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlFwdPeriodAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4B""ObjectId,LargeModel,Period,Offset,Displacements,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class FwdPeriodAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""large MarketModel ID."),
            TempStrNoSize("\x42""target period (e.g. 2 if going from semiannual LMM to annual LMM)."),
            TempStrNoSize("\x52""rate index offset, in order to pin down swaption coterminal to the last rate time."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlFwdPeriodAdapter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlFwdToCotSwapAdapter"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlFwdToCotSwapAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,ForwardModel,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class FwdToCotSwapAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""Forward Rate Market Model ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlFwdToCotSwapAdapter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlMarketModelCovariance"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlMarketModelCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the covariance matrix for the i-th step."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x15""evolution step index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlMarketModelCovariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlMarketModelDisplacements"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlMarketModelDisplacements"),
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
            TempStrNoSize("\x2F""rates' displacemets for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlMarketModelDisplacements"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlMarketModelInitialRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlMarketModelInitialRates"),
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
            TempStrNoSize("\x29""initial rates for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlMarketModelInitialRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMarketModelNumberOfFactors"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1C""qlMarketModelNumberOfFactors"),
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
            TempStrNoSize("\x2D""number of factors for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlMarketModelNumberOfFactors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlMarketModelNumberOfRates"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1A""qlMarketModelNumberOfRates"),
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
            TempStrNoSize("\x2B""number of rates for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlMarketModelNumberOfRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlMarketModelNumberOfSteps"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1A""qlMarketModelNumberOfSteps"),
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
            TempStrNoSize("\x2B""number of steps for the MarketModel object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlMarketModelNumberOfSteps"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlMarketModelPseudoRoot"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlMarketModelPseudoRoot"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2A""Returns the pseudo root for the i-th step."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x15""evolution step index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlMarketModelPseudoRoot"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x24""qlMarketModelTimeDependentVolatility"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x24""qlMarketModelTimeDependentVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2A""Returns the time dependent vol for rate i."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x0B""rate index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlMarketModelTimeDependentVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMarketModelTotalCovariance"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x1C""qlMarketModelTotalCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the covariance matrix from start up to the i-th step."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::MarketModel object"),
            TempStrNoSize("\x15""evolution step index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlMarketModelTotalCovariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x12""qlPseudoRootFacade"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x12""qlPseudoRootFacade"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,Calibrator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class PseudoRootFacade and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""CTSMMCapletCalibration ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlPseudoRootFacade"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateInstVolDifferences"),
            // parameter codes
            TempStrNoSize("\x06""PCCNP#"),
            // function display name
            TempStrNoSize("\x18""qlRateInstVolDifferences"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""MarketModel1,MarketModel2,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Compute the differences between volatilities at each evolution step."),
            // parameter descriptions
            TempStrNoSize("\x13""First Market Model."),
            TempStrNoSize("\x14""Second Market Model."),
            TempStrNoSize("\x13""Forward Rate index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlRateInstVolDifferences"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlRateVolDifferences"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x14""qlRateVolDifferences"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""MarketModel1,MarketModel2,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Compute the differences between all implied forwards volatilities."),
            // parameter descriptions
            TempStrNoSize("\x13""First Market Model."),
            TempStrNoSize("\x14""Second Market Model."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlRateVolDifferences"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSwapDerivative"),
            // parameter codes
            TempStrNoSize("\x07""PCNNPP#"),
            // function display name
            TempStrNoSize("\x10""qlSwapDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""CurveState,StartIndex,EndIndex,FwdRateIndex,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""returns derivative of swap-rate to underlying forward rate."),
            // parameter descriptions
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x0C""start index."),
            TempStrNoSize("\x0A""end index."),
            TempStrNoSize("\x26""forward rate index. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlSwapDerivative"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

