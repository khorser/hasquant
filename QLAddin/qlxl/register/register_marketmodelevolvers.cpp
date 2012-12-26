
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

// register functions in category Marketmodelevolvers with Excel

void registerMarketmodelevolvers(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x10""qlForwardRateIpc"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlForwardRateIpc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x54""ObjectId,MarketModel,BrownianGeneratorFactory,Numeraires,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class LogNormalFwdRateIpc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""MarketModel object ID."),
            TempStrNoSize("\x1B""Brownian generator factory."),
            TempStrNoSize("\x11""numeraire vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlForwardRateNormalPc"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlForwardRateNormalPc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x54""ObjectId,MarketModel,BrownianGeneratorFactory,Numeraires,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class NormalFwdRatePc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""MarketModel object ID."),
            TempStrNoSize("\x1B""Brownian generator factory."),
            TempStrNoSize("\x11""numeraire vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlForwardRatePc"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlForwardRatePc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x54""ObjectId,MarketModel,BrownianGeneratorFactory,Numeraires,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class LogNormalFwdRatePc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""MarketModel object ID."),
            TempStrNoSize("\x1B""Brownian generator factory."),
            TempStrNoSize("\x11""numeraire vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlMarketModelEvolverAdvanceStep"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1F""qlMarketModelEvolverAdvanceStep"),
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
            TempStrNoSize("\x4C""advance a single step in the current path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlMarketModelEvolverCurrentStep"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1F""qlMarketModelEvolverCurrentStep"),
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
            TempStrNoSize("\x55""returns the current step index in the current path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlMarketModelEvolverNumeraires"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlMarketModelEvolverNumeraires"),
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
            TempStrNoSize("\x55""returns the current step index in the current path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlMarketModelEvolverStartNewPath"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlMarketModelEvolverStartNewPath"),
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
            TempStrNoSize("\x33""start a new path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Marketmodelevolvers with Excel

void unregisterMarketmodelevolvers(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x10""qlForwardRateIpc"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlForwardRateIpc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x54""ObjectId,MarketModel,BrownianGeneratorFactory,Numeraires,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class LogNormalFwdRateIpc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""MarketModel object ID."),
            TempStrNoSize("\x1B""Brownian generator factory."),
            TempStrNoSize("\x11""numeraire vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlForwardRateIpc"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlForwardRateNormalPc"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlForwardRateNormalPc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x54""ObjectId,MarketModel,BrownianGeneratorFactory,Numeraires,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class NormalFwdRatePc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""MarketModel object ID."),
            TempStrNoSize("\x1B""Brownian generator factory."),
            TempStrNoSize("\x11""numeraire vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlForwardRateNormalPc"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlForwardRatePc"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlForwardRatePc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x54""ObjectId,MarketModel,BrownianGeneratorFactory,Numeraires,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class LogNormalFwdRatePc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""MarketModel object ID."),
            TempStrNoSize("\x1B""Brownian generator factory."),
            TempStrNoSize("\x11""numeraire vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlForwardRatePc"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlMarketModelEvolverAdvanceStep"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1F""qlMarketModelEvolverAdvanceStep"),
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
            TempStrNoSize("\x4C""advance a single step in the current path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlMarketModelEvolverAdvanceStep"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlMarketModelEvolverCurrentStep"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1F""qlMarketModelEvolverCurrentStep"),
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
            TempStrNoSize("\x55""returns the current step index in the current path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlMarketModelEvolverCurrentStep"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlMarketModelEvolverNumeraires"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlMarketModelEvolverNumeraires"),
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
            TempStrNoSize("\x55""returns the current step index in the current path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlMarketModelEvolverNumeraires"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlMarketModelEvolverStartNewPath"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlMarketModelEvolverStartNewPath"),
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
            TempStrNoSize("\x33""start a new path for the MarketModelEvolver object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::MarketModelEvolver object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlMarketModelEvolverStartNewPath"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

