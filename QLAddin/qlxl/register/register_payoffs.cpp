
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

// register functions in category Payoffs with Excel

void registerPayoffs(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlDoubleStickyRatchetPayoff"),
            // parameter codes
            TempStrNoSize("\x11""CCEEEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlDoubleStickyRatchetPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8D""ObjectId,Type1,Type2,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class DoubleStickyRatchetPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x30"" Sticky (type1=1) or Ratchet (type1=-1) payoff ."),
            TempStrNoSize("\x55"" Strike type (type2=1 for Min, type2=-1 for Max, type2=0 for single sticky/ratchet) ."),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlPayoffDescription"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x13""qlPayoffDescription"),
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
            TempStrNoSize("\x67""returns the description (e.g. CashOrNothing, strike 32.2, cash payoff 2.5) for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Payoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlPayoffName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0C""qlPayoffName"),
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
            TempStrNoSize("\x51""returns the type (e.g. Vanilla, CashOrNothing, etc.) for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Payoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlPayoffOptionType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x12""qlPayoffOptionType"),
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
            TempStrNoSize("\x45""returns the option-type (e.g. Call, Put) for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TypePayoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlPayoffStrike"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0E""qlPayoffStrike"),
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
            TempStrNoSize("\x2F""returns the strike for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::StrikedTypePayoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlPayoffThirdParameter"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlPayoffThirdParameter"),
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
            TempStrNoSize("\x34""returns the third parameter of a StrikedType payoff."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::StrikedTypePayoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlPayoffValue"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x0D""qlPayoffValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,Underlying,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""returns the payoff value given an underlying reference level for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Payoff object"),
            TempStrNoSize("\x1B""underlying reference level."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x12""qlRatchetMaxPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x12""qlRatchetMaxPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class RatchetMaxPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x12""qlRatchetMinPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x12""qlRatchetMinPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class RatchetMinPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlRatchetPayoff"),
            // parameter codes
            TempStrNoSize("\x0C""CCEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlRatchetPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,Gearing1,Gearing2,Spread1,Spread2,InitialValue,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class RatchetPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x40""initial value for strike (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x11""qlStickyMaxPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x11""qlStickyMaxPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class StickyMaxPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x11""qlStickyMinPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x11""qlStickyMinPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class StickyMinPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlStickyPayoff"),
            // parameter codes
            TempStrNoSize("\x0C""CCEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlStickyPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,Gearing1,Gearing2,Spread1,Spread2,InitialValue,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class StickyPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x40""initial value for strike (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x13""qlStrikedTypePayoff"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCEPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlStrikedTypePayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4E""ObjectId,PayoffID,OptionType,Strike,ThirdParameter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class StrikedTypePayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x5B""payoff ID (e.g. Vanilla, PercentageStrike, AssetOrNothing, CashOrNothing, Gap, SuperShare)."),
            TempStrNoSize("\x0C""option type."),
            TempStrNoSize("\x07""strike."),
            TempStrNoSize("\xBB""the 3rd paramenter for the payoff definition of CashOrNothing (cash), Gap (determines the size of the payoff), SuperFund (second strike). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Payoffs with Excel

void unregisterPayoffs(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlDoubleStickyRatchetPayoff"),
            // parameter codes
            TempStrNoSize("\x11""CCEEEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlDoubleStickyRatchetPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8D""ObjectId,Type1,Type2,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class DoubleStickyRatchetPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x30"" Sticky (type1=1) or Ratchet (type1=-1) payoff ."),
            TempStrNoSize("\x55"" Strike type (type2=1 for Min, type2=-1 for Max, type2=0 for single sticky/ratchet) ."),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlDoubleStickyRatchetPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlPayoffDescription"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x13""qlPayoffDescription"),
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
            TempStrNoSize("\x67""returns the description (e.g. CashOrNothing, strike 32.2, cash payoff 2.5) for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Payoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlPayoffDescription"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlPayoffName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0C""qlPayoffName"),
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
            TempStrNoSize("\x51""returns the type (e.g. Vanilla, CashOrNothing, etc.) for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Payoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlPayoffName"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlPayoffOptionType"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x12""qlPayoffOptionType"),
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
            TempStrNoSize("\x45""returns the option-type (e.g. Call, Put) for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TypePayoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlPayoffOptionType"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlPayoffStrike"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0E""qlPayoffStrike"),
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
            TempStrNoSize("\x2F""returns the strike for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::StrikedTypePayoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlPayoffStrike"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlPayoffThirdParameter"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlPayoffThirdParameter"),
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
            TempStrNoSize("\x34""returns the third parameter of a StrikedType payoff."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::StrikedTypePayoff object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlPayoffThirdParameter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlPayoffValue"),
            // parameter codes
            TempStrNoSize("\x05""ECEP#"),
            // function display name
            TempStrNoSize("\x0D""qlPayoffValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,Underlying,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""returns the payoff value given an underlying reference level for the given Payoff object."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Payoff object"),
            TempStrNoSize("\x1B""underlying reference level."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlPayoffValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x12""qlRatchetMaxPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x12""qlRatchetMaxPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class RatchetMaxPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlRatchetMaxPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x12""qlRatchetMinPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x12""qlRatchetMinPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class RatchetMinPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlRatchetMinPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlRatchetPayoff"),
            // parameter codes
            TempStrNoSize("\x0C""CCEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlRatchetPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,Gearing1,Gearing2,Spread1,Spread2,InitialValue,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class RatchetPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x40""initial value for strike (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlRatchetPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x11""qlStickyMaxPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x11""qlStickyMaxPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class StickyMaxPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlStickyMaxPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x11""qlStickyMinPayoff"),
            // parameter codes
            TempStrNoSize("\x0F""CCEEEEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x11""qlStickyMinPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,Gearing1,Gearing2,Gearing3,Spread1,Spread2,Spread3,InitialValue1,InitialValue2,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class StickyMinPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x1F""gearing 3 (for forward rate 3)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x1E""spread 3 (for forward rate 3)."),
            TempStrNoSize("\x42""initial value for strike 1 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x42""initial value for strike 2 (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlStickyMinPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlStickyPayoff"),
            // parameter codes
            TempStrNoSize("\x0C""CCEEEEEEPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlStickyPayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,Gearing1,Gearing2,Spread1,Spread2,InitialValue,AccrualFactor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class StickyPayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""gearing 1 (for strike 1)."),
            TempStrNoSize("\x19""gearing 2 (for strike 2)."),
            TempStrNoSize("\x18""spread 1 (for strike 1)."),
            TempStrNoSize("\x18""spread 2 (for strike 2)."),
            TempStrNoSize("\x40""initial value for strike (forward rate or coupon/accrualFactor)."),
            TempStrNoSize("\x0F""accrual factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlStickyPayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x13""qlStrikedTypePayoff"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCEPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlStrikedTypePayoff"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4E""ObjectId,PayoffID,OptionType,Strike,ThirdParameter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class StrikedTypePayoff and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x5B""payoff ID (e.g. Vanilla, PercentageStrike, AssetOrNothing, CashOrNothing, Gap, SuperShare)."),
            TempStrNoSize("\x0C""option type."),
            TempStrNoSize("\x07""strike."),
            TempStrNoSize("\xBB""the 3rd paramenter for the payoff definition of CashOrNothing (cash), Gap (determines the size of the payoff), SuperFund (second strike). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlStrikedTypePayoff"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

