
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

// register functions in category Swap with Excel

void registerSwap(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x09""qlMakeCms"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCCPCCPPL#"),
            // function display name
            TempStrNoSize("\x09""qlMakeCms"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6A""ObjectId,SwapTenor,SwapIndex,IborIndex,IborSpread,ForwardStart,CmsCouponPricer,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""Construct an object of class Swap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""swap tenor period."),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x4D""spread over the ibor leg. Default value = QuantLib::Null<QuantLib::Spread>()."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x1A""CmsCouponPricer object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x06""qlSwap"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x06""qlSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,LegIDs,Payer,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""Construct an object of class Swap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0F""leg object IDs."),
            TempStrNoSize("\x13""TRUE for payed leg."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSwapLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x11""qlSwapLegAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,LegNumber,AfterDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the cash flow analysis of the i-th leg for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLibAddin::Swap object"),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlSwapLegBPS"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x0C""qlSwapLegBPS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,LegNumber,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""returns the BPS of the i-th leg for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlSwapLegNPV"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x0C""qlSwapLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,LegNumber,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""returns the NPV of the i-th leg for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSwapMaturityDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x12""qlSwapMaturityDate"),
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
            TempStrNoSize("\x48""Returns the maturity (i.e. last payment) date for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlSwapStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0F""qlSwapStartDate"),
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
            TempStrNoSize("\x46""Returns the start (i.e. first accrual) date for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Swap with Excel

void unregisterSwap(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x09""qlMakeCms"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCCPCCPPL#"),
            // function display name
            TempStrNoSize("\x09""qlMakeCms"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6A""ObjectId,SwapTenor,SwapIndex,IborIndex,IborSpread,ForwardStart,CmsCouponPricer,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""Construct an object of class Swap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""swap tenor period."),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x4D""spread over the ibor leg. Default value = QuantLib::Null<QuantLib::Spread>()."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x1A""CmsCouponPricer object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlMakeCms"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x06""qlSwap"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x06""qlSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,LegIDs,Payer,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""Construct an object of class Swap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0F""leg object IDs."),
            TempStrNoSize("\x13""TRUE for payed leg."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x06""qlSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSwapLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x11""qlSwapLegAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,LegNumber,AfterDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the cash flow analysis of the i-th leg for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLibAddin::Swap object"),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlSwapLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlSwapLegBPS"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x0C""qlSwapLegBPS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,LegNumber,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""returns the BPS of the i-th leg for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlSwapLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlSwapLegNPV"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x0C""qlSwapLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,LegNumber,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""returns the NPV of the i-th leg for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlSwapLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSwapMaturityDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x12""qlSwapMaturityDate"),
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
            TempStrNoSize("\x48""Returns the maturity (i.e. last payment) date for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlSwapMaturityDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlSwapStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0F""qlSwapStartDate"),
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
            TempStrNoSize("\x46""Returns the start (i.e. first accrual) date for the given Swap object."),
            // parameter descriptions
            TempStrNoSize("\x24""id of existing QuantLib::Swap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlSwapStartDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

