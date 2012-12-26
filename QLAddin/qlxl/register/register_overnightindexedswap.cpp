
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

// register functions in category Overnightindexedswap with Excel

void registerOvernightindexedswap(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlMakeDatedOIS"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlMakeDatedOIS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x64""ObjectId,StartDate,EndDate,OvernightIndex,FixedRate,FixDayCounter,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x54""ois start date. If missing first ECB date is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x63""ois end date. If missing first ECB date after start date is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x19""OvernightIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x32""fixed leg day counter. Default value = Actual/360."),
            TempStrNoSize("\x3A""the spread in the overnight leg rate. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x09""qlMakeOIS"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCPCPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlMakeOIS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x69""ObjectId,SwapTenor,OvernightIndex,FixedRate,ForwardStart,FixDayCounter,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""swap tenor period (e.g. 5Y)."),
            TempStrNoSize("\x19""OvernightIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x32""fixed leg day counter. Default value = Actual/360."),
            TempStrNoSize("\x3A""the spread in the overnight leg rate. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x16""qlOvernightIndexedSwap"),
            // parameter codes
            TempStrNoSize("\x0D""CCPPCPCCPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlOvernightIndexedSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x71""ObjectId,PayerReceiver,Nominal,Schedule,FixedRate,FixDayCounter,OvernightIndex,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""PAYER to pay the fixed rate, RECEIVER to receive it. Default value = Payer."),
            TempStrNoSize("\x25""Notional Amount. Default value = 100."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x28""the fixed leg rate. Default value = 0.0."),
            TempStrNoSize("\x28""fixed leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x27""overnight leg OvernightIndex object ID."),
            TempStrNoSize("\x2A""overnight leg spread. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlOvernightIndexedSwapFairRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1E""qlOvernightIndexedSwapFairRate"),
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
            TempStrNoSize("\x68""returns the fair fixed leg rate which would zero the swap NPV for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlOvernightIndexedSwapFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlOvernightIndexedSwapFairSpread"),
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
            TempStrNoSize("\x78""returns the fair spread over the overnight rate which would zero the swap NPV for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlOvernightIndexedSwapFixedDayCount"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x23""qlOvernightIndexedSwapFixedDayCount"),
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
            TempStrNoSize("\x56""returns the fixed rate day count convention for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlOvernightIndexedSwapFixedLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x26""qlOvernightIndexedSwapFixedLegAnalysis"),
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
            TempStrNoSize("\x57""returns the fixed rate leg cash flow analysis of the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::OvernightIndexedSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegBPS"),
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
            TempStrNoSize("\x50""returns the BPS of the fixed rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegNPV"),
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
            TempStrNoSize("\x50""returns the NPV of the fixed rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlOvernightIndexedSwapFixedRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1F""qlOvernightIndexedSwapFixedRate"),
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
            TempStrNoSize("\x41""returns the fixed rate for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x27""qlOvernightIndexedSwapFromOISRateHelper"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x27""qlOvernightIndexedSwapFromOISRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x32""ObjectId,OISRateHelper,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""OISRateHelper object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlOvernightIndexedSwapNominal"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlOvernightIndexedSwapNominal"),
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
            TempStrNoSize("\x43""returns the swap nominal for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlOvernightIndexedSwapOvernightLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x2A""qlOvernightIndexedSwapOvernightLegAnalysis"),
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
            TempStrNoSize("\x32""returns the overnight rate leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::OvernightIndexedSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegBPS"),
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
            TempStrNoSize("\x54""returns the BPS of the overnight rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegNPV"),
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
            TempStrNoSize("\x54""returns the NPV of the overnight rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlOvernightIndexedSwapSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1C""qlOvernightIndexedSwapSpread"),
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
            TempStrNoSize("\x51""returns the spread over overnight rate for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlOvernightIndexedSwapType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1A""qlOvernightIndexedSwapType"),
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
            TempStrNoSize("\x53""returns the swap type (Payer or Receiver) of the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Overnightindexedswap with Excel

void unregisterOvernightindexedswap(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlMakeDatedOIS"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlMakeDatedOIS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x64""ObjectId,StartDate,EndDate,OvernightIndex,FixedRate,FixDayCounter,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x54""ois start date. If missing first ECB date is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x63""ois end date. If missing first ECB date after start date is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x19""OvernightIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x32""fixed leg day counter. Default value = Actual/360."),
            TempStrNoSize("\x3A""the spread in the overnight leg rate. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlMakeDatedOIS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x09""qlMakeOIS"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCPCPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlMakeOIS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x69""ObjectId,SwapTenor,OvernightIndex,FixedRate,ForwardStart,FixDayCounter,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""swap tenor period (e.g. 5Y)."),
            TempStrNoSize("\x19""OvernightIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x32""fixed leg day counter. Default value = Actual/360."),
            TempStrNoSize("\x3A""the spread in the overnight leg rate. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlMakeOIS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x16""qlOvernightIndexedSwap"),
            // parameter codes
            TempStrNoSize("\x0D""CCPPCPCCPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlOvernightIndexedSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x71""ObjectId,PayerReceiver,Nominal,Schedule,FixedRate,FixDayCounter,OvernightIndex,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""PAYER to pay the fixed rate, RECEIVER to receive it. Default value = Payer."),
            TempStrNoSize("\x25""Notional Amount. Default value = 100."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x28""the fixed leg rate. Default value = 0.0."),
            TempStrNoSize("\x28""fixed leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x27""overnight leg OvernightIndex object ID."),
            TempStrNoSize("\x2A""overnight leg spread. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlOvernightIndexedSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlOvernightIndexedSwapFairRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1E""qlOvernightIndexedSwapFairRate"),
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
            TempStrNoSize("\x68""returns the fair fixed leg rate which would zero the swap NPV for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlOvernightIndexedSwapFairRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlOvernightIndexedSwapFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlOvernightIndexedSwapFairSpread"),
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
            TempStrNoSize("\x78""returns the fair spread over the overnight rate which would zero the swap NPV for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlOvernightIndexedSwapFairSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlOvernightIndexedSwapFixedDayCount"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x23""qlOvernightIndexedSwapFixedDayCount"),
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
            TempStrNoSize("\x56""returns the fixed rate day count convention for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlOvernightIndexedSwapFixedDayCount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlOvernightIndexedSwapFixedLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x26""qlOvernightIndexedSwapFixedLegAnalysis"),
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
            TempStrNoSize("\x57""returns the fixed rate leg cash flow analysis of the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::OvernightIndexedSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlOvernightIndexedSwapFixedLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegBPS"),
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
            TempStrNoSize("\x50""returns the BPS of the fixed rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegNPV"),
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
            TempStrNoSize("\x50""returns the NPV of the fixed rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlOvernightIndexedSwapFixedLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlOvernightIndexedSwapFixedRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1F""qlOvernightIndexedSwapFixedRate"),
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
            TempStrNoSize("\x41""returns the fixed rate for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlOvernightIndexedSwapFixedRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x27""qlOvernightIndexedSwapFromOISRateHelper"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x27""qlOvernightIndexedSwapFromOISRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x32""ObjectId,OISRateHelper,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class OvernightIndexedSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""OISRateHelper object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlOvernightIndexedSwapFromOISRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlOvernightIndexedSwapNominal"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlOvernightIndexedSwapNominal"),
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
            TempStrNoSize("\x43""returns the swap nominal for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlOvernightIndexedSwapNominal"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlOvernightIndexedSwapOvernightLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x2A""qlOvernightIndexedSwapOvernightLegAnalysis"),
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
            TempStrNoSize("\x32""returns the overnight rate leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::OvernightIndexedSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlOvernightIndexedSwapOvernightLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegBPS"),
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
            TempStrNoSize("\x54""returns the BPS of the overnight rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegNPV"),
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
            TempStrNoSize("\x54""returns the NPV of the overnight rate leg for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlOvernightIndexedSwapOvernightLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlOvernightIndexedSwapSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1C""qlOvernightIndexedSwapSpread"),
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
            TempStrNoSize("\x51""returns the spread over overnight rate for the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlOvernightIndexedSwapSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlOvernightIndexedSwapType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1A""qlOvernightIndexedSwapType"),
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
            TempStrNoSize("\x53""returns the swap type (Payer or Receiver) of the given OvernightIndexedSwap object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::OvernightIndexedSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlOvernightIndexedSwapType"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

