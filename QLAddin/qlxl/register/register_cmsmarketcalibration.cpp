
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

// register functions in category Cmsmarketcalibration with Excel

void registerCmsmarketcalibration(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCmsMarketCalibration"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCKCPPL#"),
            // function display name
            TempStrNoSize("\x16""qlCmsMarketCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4E""ObjectId,VolCube,CmsMarket,Weights,CalibrationType,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class CmsMarketCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""Volatility Cube by Sabr."),
            TempStrNoSize("\x14""CmsMarket object ID."),
            TempStrNoSize("\x23""weights for cms market calibration."),
            TempStrNoSize("\x3A""calibration type (e.g. OnSpread, OnPrice, OnForwardPrice)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationCompute"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPLP#"),
            // function display name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,EndCriteria,OptimizationMethod,Guess,IsMeanRevFixed,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""Return the best beta and mean reversion."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x06""guess."),
            TempStrNoSize("\x46""if TRUE mean reversion parameter is not calibrated, the guess is used."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlCmsMarketCalibrationDenseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlCmsMarketCalibrationDenseSabrParameters"),
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
            TempStrNoSize("\x24""returns results of Sabr calibration."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationElapsed"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationElapsed"),
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
            TempStrNoSize("\x39""Returns the elapsed time of the simultaneous calibration."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCmsMarketCalibrationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x21""qlCmsMarketCalibrationEndCriteria"),
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
            TempStrNoSize("\x46""Returns the optimization end criteria of the simultaneous calibration."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCmsMarketCalibrationError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1B""qlCmsMarketCalibrationError"),
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
            TempStrNoSize("\x32""Returns the error of the simultaneous calibration."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlCmsMarketCalibrationSparseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlCmsMarketCalibrationSparseSabrParameters"),
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
            TempStrNoSize("\x24""returns results of Sabr calibration."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlSimultaneousCalibrationBrowseCmsMarket"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlSimultaneousCalibrationBrowseCmsMarket"),
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
            TempStrNoSize("\x2D""return the market and implied spreads matrix."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Cmsmarketcalibration with Excel

void unregisterCmsmarketcalibration(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCmsMarketCalibration"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCKCPPL#"),
            // function display name
            TempStrNoSize("\x16""qlCmsMarketCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4E""ObjectId,VolCube,CmsMarket,Weights,CalibrationType,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class CmsMarketCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""Volatility Cube by Sabr."),
            TempStrNoSize("\x14""CmsMarket object ID."),
            TempStrNoSize("\x23""weights for cms market calibration."),
            TempStrNoSize("\x3A""calibration type (e.g. OnSpread, OnPrice, OnForwardPrice)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlCmsMarketCalibration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationCompute"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPLP#"),
            // function display name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,EndCriteria,OptimizationMethod,Guess,IsMeanRevFixed,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""Return the best beta and mean reversion."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x06""guess."),
            TempStrNoSize("\x46""if TRUE mean reversion parameter is not calibrated, the guess is used."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlCmsMarketCalibrationCompute"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlCmsMarketCalibrationDenseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlCmsMarketCalibrationDenseSabrParameters"),
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
            TempStrNoSize("\x24""returns results of Sabr calibration."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlCmsMarketCalibrationDenseSabrParameters"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationElapsed"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlCmsMarketCalibrationElapsed"),
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
            TempStrNoSize("\x39""Returns the elapsed time of the simultaneous calibration."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlCmsMarketCalibrationElapsed"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCmsMarketCalibrationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x21""qlCmsMarketCalibrationEndCriteria"),
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
            TempStrNoSize("\x46""Returns the optimization end criteria of the simultaneous calibration."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCmsMarketCalibrationEndCriteria"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCmsMarketCalibrationError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1B""qlCmsMarketCalibrationError"),
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
            TempStrNoSize("\x32""Returns the error of the simultaneous calibration."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlCmsMarketCalibrationError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlCmsMarketCalibrationSparseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlCmsMarketCalibrationSparseSabrParameters"),
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
            TempStrNoSize("\x24""returns results of Sabr calibration."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlCmsMarketCalibrationSparseSabrParameters"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlSimultaneousCalibrationBrowseCmsMarket"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlSimultaneousCalibrationBrowseCmsMarket"),
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
            TempStrNoSize("\x2D""return the market and implied spreads matrix."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CmsMarketCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlSimultaneousCalibrationBrowseCmsMarket"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

