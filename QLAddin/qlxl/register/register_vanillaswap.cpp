
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

// register functions in category Vanillaswap with Excel

void registerVanillaswap(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlMakeIMMSwap"),
            // parameter codes
            TempStrNoSize("\x0D""CCCCPPPPCPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlMakeIMMSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x74""ObjectId,SwapTenor,IborIndex,FixedRate,FirstImmDate,FixDayCounter,Spread,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""swap tenor period (e.g. 2Y)."),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x33""First (IMM) date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x3B""fixed leg day counter. Default value = 30/360 (Bond Basis)."),
            TempStrNoSize("\x29""floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x1D""DiscountSwapEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x11""qlMakeVanillaSwap"),
            // parameter codes
            TempStrNoSize("\x0D""CCCCPCPPCPPL#"),
            // function display name
            TempStrNoSize("\x11""qlMakeVanillaSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x74""ObjectId,SwapTenor,IborIndex,FixedRate,ForwardStart,FixDayCounter,Spread,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""swap tenor period (e.g. 5Y)."),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x32""fixed leg day counter. Default value = DayCounter."),
            TempStrNoSize("\x29""floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x1D""DiscountSwapEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlVanillaSwap"),
            // parameter codes
            TempStrNoSize("\x10""CCPPCPCCCPCPPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlVanillaSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAB""ObjectId,PayerReceiver,Nominal,FixSchedule,FixedRate,FixDayCounter,FloatingLegSchedule,IborIndex,Spread,FloatingLegDayCounter,PaymentConvention,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""PAYER to pay the fixed rate, RECEIVER to receive it. Default value = Payer."),
            TempStrNoSize("\x25""Notional Amount. Default value = 100."),
            TempStrNoSize("\x1D""fixed leg Schedule object ID."),
            TempStrNoSize("\x28""the fixed leg rate. Default value = 0.0."),
            TempStrNoSize("\x28""fixed leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x20""floating leg Schedule object ID."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x29""floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x27""floating day counter (e.g. Actual/360)."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlVanillaSwapFairRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x15""qlVanillaSwapFairRate"),
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
            TempStrNoSize("\x5F""returns the fair fixed leg rate which would zero the swap NPV for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlVanillaSwapFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x17""qlVanillaSwapFairSpread"),
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
            TempStrNoSize("\x6E""returns the fair spread over the floating rate which would zero the swap NPV for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlVanillaSwapFixedDayCount"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1A""qlVanillaSwapFixedDayCount"),
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
            TempStrNoSize("\x4D""returns the fixed rate day count convention for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlVanillaSwapFixedLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1D""qlVanillaSwapFixedLegAnalysis"),
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
            TempStrNoSize("\x4E""returns the fixed rate leg cash flow analysis of the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::VanillaSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegBPS"),
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
            TempStrNoSize("\x47""returns the BPS of the fixed rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegNPV"),
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
            TempStrNoSize("\x47""returns the NPV of the fixed rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlVanillaSwapFixedRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlVanillaSwapFixedRate"),
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
            TempStrNoSize("\x3C""returns the fixed leg rate for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlVanillaSwapFloatingDayCount"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1D""qlVanillaSwapFloatingDayCount"),
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
            TempStrNoSize("\x4F""returns the floating leg day count convention for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlVanillaSwapFloatingLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlVanillaSwapFloatingLegAnalysis"),
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
            TempStrNoSize("\x31""returns the floating rate leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::VanillaSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegBPS"),
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
            TempStrNoSize("\x4A""returns the BPS of the floating rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegNPV"),
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
            TempStrNoSize("\x4A""returns the NPV of the floating rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlVanillaSwapFromSwapIndex"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlVanillaSwapFromSwapIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,SwapIndex,FixingDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x0C""fixing date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlVanillaSwapFromSwapRateHelper"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlVanillaSwapFromSwapRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,SwapRateHelper,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""SwapRateHelper object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlVanillaSwapNominal"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x14""qlVanillaSwapNominal"),
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
            TempStrNoSize("\x3A""returns the swap nominal for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlVanillaSwapPaymentConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1E""qlVanillaSwapPaymentConvention"),
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
            TempStrNoSize("\x4D""returns the payment business day convention for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlVanillaSwapSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x13""qlVanillaSwapSpread"),
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
            TempStrNoSize("\x47""returns the spread over floating rate for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlVanillaSwapType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x11""qlVanillaSwapType"),
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
            TempStrNoSize("\x4A""returns the swap type (Payer or Receiver) of the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Vanillaswap with Excel

void unregisterVanillaswap(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlMakeIMMSwap"),
            // parameter codes
            TempStrNoSize("\x0D""CCCCPPPPCPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlMakeIMMSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x74""ObjectId,SwapTenor,IborIndex,FixedRate,FirstImmDate,FixDayCounter,Spread,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""swap tenor period (e.g. 2Y)."),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x33""First (IMM) date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x3B""fixed leg day counter. Default value = 30/360 (Bond Basis)."),
            TempStrNoSize("\x29""floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x1D""DiscountSwapEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlMakeIMMSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x11""qlMakeVanillaSwap"),
            // parameter codes
            TempStrNoSize("\x0D""CCCCPCPPCPPL#"),
            // function display name
            TempStrNoSize("\x11""qlMakeVanillaSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x74""ObjectId,SwapTenor,IborIndex,FixedRate,ForwardStart,FixDayCounter,Spread,PricingEngineID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""swap tenor period (e.g. 5Y)."),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x62""the fixed leg rate. If missing atm rate is used. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x32""fixed leg day counter. Default value = DayCounter."),
            TempStrNoSize("\x29""floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x1D""DiscountSwapEngine object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlMakeVanillaSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlVanillaSwap"),
            // parameter codes
            TempStrNoSize("\x10""CCPPCPCCCPCPPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlVanillaSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAB""ObjectId,PayerReceiver,Nominal,FixSchedule,FixedRate,FixDayCounter,FloatingLegSchedule,IborIndex,Spread,FloatingLegDayCounter,PaymentConvention,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""PAYER to pay the fixed rate, RECEIVER to receive it. Default value = Payer."),
            TempStrNoSize("\x25""Notional Amount. Default value = 100."),
            TempStrNoSize("\x1D""fixed leg Schedule object ID."),
            TempStrNoSize("\x28""the fixed leg rate. Default value = 0.0."),
            TempStrNoSize("\x28""fixed leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x20""floating leg Schedule object ID."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x29""floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x27""floating day counter (e.g. Actual/360)."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlVanillaSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlVanillaSwapFairRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x15""qlVanillaSwapFairRate"),
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
            TempStrNoSize("\x5F""returns the fair fixed leg rate which would zero the swap NPV for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlVanillaSwapFairRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlVanillaSwapFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x17""qlVanillaSwapFairSpread"),
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
            TempStrNoSize("\x6E""returns the fair spread over the floating rate which would zero the swap NPV for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlVanillaSwapFairSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlVanillaSwapFixedDayCount"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1A""qlVanillaSwapFixedDayCount"),
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
            TempStrNoSize("\x4D""returns the fixed rate day count convention for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlVanillaSwapFixedDayCount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlVanillaSwapFixedLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1D""qlVanillaSwapFixedLegAnalysis"),
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
            TempStrNoSize("\x4E""returns the fixed rate leg cash flow analysis of the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::VanillaSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlVanillaSwapFixedLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegBPS"),
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
            TempStrNoSize("\x47""returns the BPS of the fixed rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlVanillaSwapFixedLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlVanillaSwapFixedLegNPV"),
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
            TempStrNoSize("\x47""returns the NPV of the fixed rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlVanillaSwapFixedLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlVanillaSwapFixedRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlVanillaSwapFixedRate"),
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
            TempStrNoSize("\x3C""returns the fixed leg rate for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlVanillaSwapFixedRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlVanillaSwapFloatingDayCount"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1D""qlVanillaSwapFloatingDayCount"),
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
            TempStrNoSize("\x4F""returns the floating leg day count convention for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlVanillaSwapFloatingDayCount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlVanillaSwapFloatingLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlVanillaSwapFloatingLegAnalysis"),
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
            TempStrNoSize("\x31""returns the floating rate leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::VanillaSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlVanillaSwapFloatingLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegBPS"),
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
            TempStrNoSize("\x4A""returns the BPS of the floating rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegNPV"),
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
            TempStrNoSize("\x4A""returns the NPV of the floating rate leg for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlVanillaSwapFloatingLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlVanillaSwapFromSwapIndex"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlVanillaSwapFromSwapIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,SwapIndex,FixingDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x0C""fixing date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlVanillaSwapFromSwapIndex"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlVanillaSwapFromSwapRateHelper"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlVanillaSwapFromSwapRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,SwapRateHelper,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class VanillaSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""SwapRateHelper object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlVanillaSwapFromSwapRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlVanillaSwapNominal"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x14""qlVanillaSwapNominal"),
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
            TempStrNoSize("\x3A""returns the swap nominal for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlVanillaSwapNominal"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlVanillaSwapPaymentConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1E""qlVanillaSwapPaymentConvention"),
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
            TempStrNoSize("\x4D""returns the payment business day convention for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlVanillaSwapPaymentConvention"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlVanillaSwapSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x13""qlVanillaSwapSpread"),
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
            TempStrNoSize("\x47""returns the spread over floating rate for the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlVanillaSwapSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlVanillaSwapType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x11""qlVanillaSwapType"),
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
            TempStrNoSize("\x4A""returns the swap type (Payer or Receiver) of the given VanillaSwap object."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::VanillaSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlVanillaSwapType"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

