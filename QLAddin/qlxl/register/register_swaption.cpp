
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

// register functions in category Swaption with Excel

void registerSwaption(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlMakeSwaption"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCPCPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlMakeSwaption"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x51""ObjectId,SwapIndex,OptionTenor,Strike,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Swaption and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x23""option tenor as Period (e.g. '5Y')."),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x21""Swaption PricingEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlSwaption"),
            // parameter codes
            TempStrNoSize("\x09""CCCCCPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlSwaption"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,VanillaSwap,Exercise,SettlementType,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Swaption and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x24""underlying (vanilla) swap object ID."),
            TempStrNoSize("\x13""Exercise object ID."),
            TempStrNoSize("\x35""settlement type (PhysicalSettlement, CashSettlement)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSwaptionImpliedVolatility"),
            // parameter codes
            TempStrNoSize("\x09""ECECPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlSwaptionImpliedVolatility"),
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
            TempStrNoSize("\x50""Returns the volatility implied by the given price for the given Swaption object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Swaption object"),
            TempStrNoSize("\x2B""Price used to infer the implied volatility."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x27""Volatility guess. Default value = 0.10."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwaptionSettlementType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlSwaptionSettlementType"),
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
            TempStrNoSize("\x4D""returns the settlement type (Cash or Delivery) for the given Swaption object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Swaption object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlSwaptionType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlSwaptionType"),
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
            TempStrNoSize("\x43""returns the type (Payer or Receiver) for the given Swaption object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Swaption object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Swaption with Excel

void unregisterSwaption(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlMakeSwaption"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCPCPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlMakeSwaption"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x51""ObjectId,SwapIndex,OptionTenor,Strike,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Swaption and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x23""option tenor as Period (e.g. '5Y')."),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x21""Swaption PricingEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlMakeSwaption"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlSwaption"),
            // parameter codes
            TempStrNoSize("\x09""CCCCCPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlSwaption"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,VanillaSwap,Exercise,SettlementType,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Swaption and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x24""underlying (vanilla) swap object ID."),
            TempStrNoSize("\x13""Exercise object ID."),
            TempStrNoSize("\x35""settlement type (PhysicalSettlement, CashSettlement)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlSwaption"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSwaptionImpliedVolatility"),
            // parameter codes
            TempStrNoSize("\x09""ECECPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlSwaptionImpliedVolatility"),
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
            TempStrNoSize("\x50""Returns the volatility implied by the given price for the given Swaption object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Swaption object"),
            TempStrNoSize("\x2B""Price used to infer the implied volatility."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x27""Volatility guess. Default value = 0.10."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSwaptionImpliedVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwaptionSettlementType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlSwaptionSettlementType"),
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
            TempStrNoSize("\x4D""returns the settlement type (Cash or Delivery) for the given Swaption object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Swaption object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSwaptionSettlementType"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlSwaptionType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlSwaptionType"),
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
            TempStrNoSize("\x43""returns the type (Payer or Receiver) for the given Swaption object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Swaption object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlSwaptionType"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

