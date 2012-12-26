
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

// register functions in category Capfloor with Excel

void registerCapfloor(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlCapFloor"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlCapFloor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,OptionType,LegID,Strikes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class CapFloor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1B""option type (cap or floor)."),
            TempStrNoSize("\x0E""coupon vector."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCapFloorAtmRate"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x11""qlCapFloorAtmRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,YieldCurve,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the at-the-money rate for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCapFloorCapRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlCapFloorCapRates"),
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
            TempStrNoSize("\x34""Returns the cap rates for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCapFloorFloorRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlCapFloorFloorRates"),
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
            TempStrNoSize("\x36""Returns the floor rates for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCapFloorImpliedVolatility"),
            // parameter codes
            TempStrNoSize("\x09""ECECPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlCapFloorImpliedVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""ObjectId,Price,YieldCurve,Guess,Accuracy,MaxIter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the volatility implied by the given price for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x2B""Price used to infer the implied volatility."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x27""Volatility guess. Default value = 0.10."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCapFloorLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x15""qlCapFloorLegAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,AfterDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the cash flow analysis for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLibAddin::CapFloor object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCapFloorMaturityDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x16""qlCapFloorMaturityDate"),
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
            TempStrNoSize("\x4C""Returns the maturity (i.e. last payment) date for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCapFloorStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x13""qlCapFloorStartDate"),
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
            TempStrNoSize("\x4A""Returns the start (i.e. first accrual) date for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlCapFloorType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlCapFloorType"),
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
            TempStrNoSize("\x41""Returns the type (e.g. Cap, Floor) for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlMakeCapFloor"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCCPCCPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlMakeCapFloor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x64""ObjectId,OptionType,Length,IborIndex,Strike,ForwardStart,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class CapFloor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1B""option type (Cap or Floor)."),
            TempStrNoSize("\x15""as period (e.g. 10Y)."),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x35""as period (if zero days the first caplet is removed)."),
            TempStrNoSize("\x21""CapFloor PricingEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Capfloor with Excel

void unregisterCapfloor(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlCapFloor"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlCapFloor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,OptionType,LegID,Strikes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class CapFloor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1B""option type (cap or floor)."),
            TempStrNoSize("\x0E""coupon vector."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlCapFloor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCapFloorAtmRate"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x11""qlCapFloorAtmRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,YieldCurve,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the at-the-money rate for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlCapFloorAtmRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCapFloorCapRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlCapFloorCapRates"),
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
            TempStrNoSize("\x34""Returns the cap rates for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlCapFloorCapRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCapFloorFloorRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlCapFloorFloorRates"),
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
            TempStrNoSize("\x36""Returns the floor rates for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlCapFloorFloorRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCapFloorImpliedVolatility"),
            // parameter codes
            TempStrNoSize("\x09""ECECPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlCapFloorImpliedVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""ObjectId,Price,YieldCurve,Guess,Accuracy,MaxIter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the volatility implied by the given price for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x2B""Price used to infer the implied volatility."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x27""Volatility guess. Default value = 0.10."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlCapFloorImpliedVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCapFloorLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x15""qlCapFloorLegAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,AfterDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the cash flow analysis for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLibAddin::CapFloor object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlCapFloorLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCapFloorMaturityDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x16""qlCapFloorMaturityDate"),
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
            TempStrNoSize("\x4C""Returns the maturity (i.e. last payment) date for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlCapFloorMaturityDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCapFloorStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x13""qlCapFloorStartDate"),
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
            TempStrNoSize("\x4A""Returns the start (i.e. first accrual) date for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlCapFloorStartDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlCapFloorType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlCapFloorType"),
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
            TempStrNoSize("\x41""Returns the type (e.g. Cap, Floor) for the given CapFloor object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::CapFloor object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlCapFloorType"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlMakeCapFloor"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCCPCCPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlMakeCapFloor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x64""ObjectId,OptionType,Length,IborIndex,Strike,ForwardStart,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class CapFloor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1B""option type (Cap or Floor)."),
            TempStrNoSize("\x15""as period (e.g. 10Y)."),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x35""as period (if zero days the first caplet is removed)."),
            TempStrNoSize("\x21""CapFloor PricingEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlMakeCapFloor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

