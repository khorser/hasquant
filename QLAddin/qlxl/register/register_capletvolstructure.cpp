
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

// register functions in category Capletvolstructure with Excel

void registerCapletvolstructure(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCapFloorTermVTSVolatility"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlCapFloorTermVTSVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns volatility from the given CapFloorTermVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::CapFloorTermVolatilityStructure object"),
            TempStrNoSize("\x1C""caplet/floorlet expiry date."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlCapFloorTermVTSVolatility2"),
            // parameter codes
            TempStrNoSize("\x07""PCCPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlCapFloorTermVTSVolatility2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,OptionTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns volatility from the given CapFloorTermVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::CapFloorTermVolatilityStructure object"),
            TempStrNoSize("\x1D""caplet/floorlet option tenor."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCapFloorTermVolCurve"),
            // parameter codes
            TempStrNoSize("\x0C""CCNCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlCapFloorTermVolCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x77""ObjectId,SettlementDays,Calendar,BusinessDayConvention,OptionTenors,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class CapFloorTermVolCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""number of settlement days."),
            TempStrNoSize("\x51""holiday calendar used for calculating the exercise dates from the expiries tenor."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x0E""option tenors."),
            TempStrNoSize("\x12""vol quotes vector."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCapFloorTermVolCurveOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCapFloorTermVolCurveOptionDates"),
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
            TempStrNoSize("\x46""Returns the option dates from the given CapFloorTermVolCurve object. ."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CapFloorTermVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlCapFloorTermVolCurveOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x22""qlCapFloorTermVolCurveOptionTenors"),
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
            TempStrNoSize("\x45""Returns the option tenors from the given CapFloorTermVolCurve object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CapFloorTermVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCapFloorTermVolSurface"),
            // parameter codes
            TempStrNoSize("\x0D""CCNCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlCapFloorTermVolSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7F""ObjectId,SettlementDays,Calendar,BusinessDayConvention,OptionTenors,Strikes,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class CapFloorTermVolSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""number of settlement days."),
            TempStrNoSize("\x51""holiday calendar used for calculating the exercise dates from the expiries tenor."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x0E""option tenors."),
            TempStrNoSize("\x0C""cap strikes."),
            TempStrNoSize("\x12""vol quotes matrix."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlCapFloorTermVolSurfaceOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x23""qlCapFloorTermVolSurfaceOptionDates"),
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
            TempStrNoSize("\x46""Returns the option dates from the given CapFloorTermVolSurface object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CapFloorTermVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlCapFloorTermVolSurfaceOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlCapFloorTermVolSurfaceOptionTenors"),
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
            TempStrNoSize("\x47""Returns the option tenors from the given CapFloorTermVolSurface object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CapFloorTermVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlCapFloorTermVolSurfaceStrikes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlCapFloorTermVolSurfaceStrikes"),
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
            TempStrNoSize("\x48""Returns the option strikes from the given CapFloorTermVolSurface object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CapFloorTermVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlConstantOptionletVolatility"),
            // parameter codes
            TempStrNoSize("\x0B""CCPCCPPPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlConstantOptionletVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,NDays,Calendar,BusinessDayConvention,Volatility,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Construct an object of class ConstantOptionletVolatility and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x70""number of days to advance from EvaluationDate: it fixes the date at which the variance = 0.0. Default value = 0."),
            TempStrNoSize("\x59""holiday calendar (e.g. TARGET) used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x24""cap/floor constant volatility Quote."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlOptionletStripper1"),
            // parameter codes
            TempStrNoSize("\x0B""CCCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlOptionletStripper1"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5B""ObjectId,TermVolSurface,IborIndex,SwitchStrike,Accuracy,MaxIter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class OptionletStripper1 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""CapFloorTermVolSurface object ID."),
            TempStrNoSize("\x14""cap index object ID."),
            TempStrNoSize("\x40""switch strike. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlOptionletStripper1CapFloorPrices"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x22""qlOptionletStripper1CapFloorPrices"),
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
            TempStrNoSize("\x46""Returns option prices matrix from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlOptionletStripper1CapFloorVolatilities"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlOptionletStripper1CapFloorVolatilities"),
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
            TempStrNoSize("\x4C""Returns option volatilities matrix from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlOptionletStripper1OptionletPrices"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x23""qlOptionletStripper1OptionletPrices"),
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
            TempStrNoSize("\x49""Returns optionlet prices matrix from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlOptionletStripper1SwitchStrike"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlOptionletStripper1SwitchStrike"),
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
            TempStrNoSize("\x46""Returns option switch strike from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlOptionletStripper2"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlOptionletStripper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,OptionletStripper1,TermVolCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class OptionletStripper2 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""OptionletStripper1 object id."),
            TempStrNoSize("\x1F""CapFloorTermVolCurve object id."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlOptionletStripper2AtmCapFloorPrices"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlOptionletStripper2AtmCapFloorPrices"),
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
            TempStrNoSize("\x43""Returns ATM option prices from the given OptionletStripper2 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper2 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlOptionletStripper2AtmCapFloorStrikes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlOptionletStripper2AtmCapFloorStrikes"),
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
            TempStrNoSize("\x44""Returns option ATM strikes from the given OptionletStripper2 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper2 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlOptionletStripper2SpreadsVol"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlOptionletStripper2SpreadsVol"),
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
            TempStrNoSize("\x5D""Returns optionlet spread (with respect to ATM) vols from the given OptionletStripper2 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper2 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlOptionletStripperOptionletAccrualPeriods"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlOptionletStripperOptionletAccrualPeriods"),
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
            TempStrNoSize("\x4A""Returns optionlet accrual periods from the given OptionletStripper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::OptionletStripper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlOptionletStripperOptionletFixingTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlOptionletStripperOptionletFixingTenors"),
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
            TempStrNoSize("\x48""Returns optionlet fixing tenors from the given OptionletStripper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::OptionletStripper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlOptionletStripperOptionletPaymentDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlOptionletStripperOptionletPaymentDates"),
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
            TempStrNoSize("\x48""Returns optionlet payment dates from the given OptionletStripper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::OptionletStripper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlOptionletVTSBlackVariance"),
            // parameter codes
            TempStrNoSize("\x07""PCPELP#"),
            // function display name
            TempStrNoSize("\x1B""qlOptionletVTSBlackVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the black variance corresponding to a given strike for a given exercise date."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x16""cap/floor expiry date."),
            TempStrNoSize("\x18""cap/floor strike vector."),
            TempStrNoSize("\x2F""Extrapolation Flag (TRUE allows extrapolation)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlOptionletVTSBlackVariance2"),
            // parameter codes
            TempStrNoSize("\x07""PCPELP#"),
            // function display name
            TempStrNoSize("\x1C""qlOptionletVTSBlackVariance2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,OptionTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the black variance corresponding to a given strike for a given exercise date."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x16""cap/floor expiry date."),
            TempStrNoSize("\x18""cap/floor strike vector."),
            TempStrNoSize("\x2F""Extrapolation Flag (TRUE allows extrapolation)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlOptionletVTSVolatility"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x18""qlOptionletVTSVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns volatility from the given OptionletVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x1C""caplet/floorlet expiry date."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x19""qlOptionletVTSVolatility2"),
            // parameter codes
            TempStrNoSize("\x07""PCCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlOptionletVTSVolatility2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,OptionTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns volatility from the given OptionletVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x1D""caplet/floorlet option tenor."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x2E""qlRelinkableHandleOptionletVolatilityStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x2E""qlRelinkableHandleOptionletVolatilityStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,CurrentLink,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x98""Construct an object of class RelinkableHandleImpl<QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x70""OptionletVolatilityStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSpreadedOptionletVolatility"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlSpreadedOptionletVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""ObjectId,BaseVolStructure,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Construct an object of class SpreadedOptionletVolatility and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Base OptionletVolatilityStructure object ID."),
            TempStrNoSize("\x07""spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x13""qlStrippedOptionlet"),
            // parameter codes
            TempStrNoSize("\x0E""CCPCCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlStrippedOptionlet"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8B""ObjectId,SettlementDays,Calendar,BusinessDayConvention,IborIndex,OptionletDates,Strikes,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class StrippedOptionlet and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2D""number of settlement days. Default value = 0."),
            TempStrNoSize("\x59""holiday calendar (e.g. TARGET) used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x10""optionlet dates."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x0B""vol quotes."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlStrippedOptionletAdapter"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlStrippedOptionletAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3A""ObjectId,StrippedOptionletBase,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class StrippedOptionletAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""Stripped Optionlet object id."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlStrippedOptionletBaseAtmOptionletRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlStrippedOptionletBaseAtmOptionletRates"),
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
            TempStrNoSize("\x48""Returns atm optionlet rates from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseBusinessDayConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseBusinessDayConvention"),
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
            TempStrNoSize("\x45""Returns the business day convention used in tenor to date conversion."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlStrippedOptionletBaseCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1F""qlStrippedOptionletBaseCalendar"),
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
            TempStrNoSize("\x44""Returns the calendar used by the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlStrippedOptionletBaseDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x21""qlStrippedOptionletBaseDayCounter"),
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
            TempStrNoSize("\x46""Returns the DayCounter used by the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingDates"),
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
            TempStrNoSize("\x4B""Returns optionlet fixing dates from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingTimes"),
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
            TempStrNoSize("\x4B""Returns optionlet fixing times from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseOptionletVolatilities"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseOptionletVolatilities"),
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
            TempStrNoSize("\x4B""Returns optionlet volatilities from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x10""optionlet index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlStrippedOptionletBaseSettlementDays"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x25""qlStrippedOptionletBaseSettlementDays"),
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
            TempStrNoSize("\x51""Returns the number of settlement days for the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlStrippedOptionletBaseStrikes"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x1E""qlStrippedOptionletBaseStrikes"),
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
            TempStrNoSize("\x45""Returns optionlet strike from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x10""optionlet index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Capletvolstructure with Excel

void unregisterCapletvolstructure(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCapFloorTermVTSVolatility"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlCapFloorTermVTSVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns volatility from the given CapFloorTermVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::CapFloorTermVolatilityStructure object"),
            TempStrNoSize("\x1C""caplet/floorlet expiry date."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlCapFloorTermVTSVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlCapFloorTermVTSVolatility2"),
            // parameter codes
            TempStrNoSize("\x07""PCCPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlCapFloorTermVTSVolatility2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,OptionTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns volatility from the given CapFloorTermVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::CapFloorTermVolatilityStructure object"),
            TempStrNoSize("\x1D""caplet/floorlet option tenor."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlCapFloorTermVTSVolatility2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCapFloorTermVolCurve"),
            // parameter codes
            TempStrNoSize("\x0C""CCNCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlCapFloorTermVolCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x77""ObjectId,SettlementDays,Calendar,BusinessDayConvention,OptionTenors,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class CapFloorTermVolCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""number of settlement days."),
            TempStrNoSize("\x51""holiday calendar used for calculating the exercise dates from the expiries tenor."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x0E""option tenors."),
            TempStrNoSize("\x12""vol quotes vector."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlCapFloorTermVolCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCapFloorTermVolCurveOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCapFloorTermVolCurveOptionDates"),
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
            TempStrNoSize("\x46""Returns the option dates from the given CapFloorTermVolCurve object. ."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CapFloorTermVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCapFloorTermVolCurveOptionDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlCapFloorTermVolCurveOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x22""qlCapFloorTermVolCurveOptionTenors"),
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
            TempStrNoSize("\x45""Returns the option tenors from the given CapFloorTermVolCurve object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::CapFloorTermVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlCapFloorTermVolCurveOptionTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCapFloorTermVolSurface"),
            // parameter codes
            TempStrNoSize("\x0D""CCNCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlCapFloorTermVolSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7F""ObjectId,SettlementDays,Calendar,BusinessDayConvention,OptionTenors,Strikes,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class CapFloorTermVolSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""number of settlement days."),
            TempStrNoSize("\x51""holiday calendar used for calculating the exercise dates from the expiries tenor."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x0E""option tenors."),
            TempStrNoSize("\x0C""cap strikes."),
            TempStrNoSize("\x12""vol quotes matrix."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlCapFloorTermVolSurface"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlCapFloorTermVolSurfaceOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x23""qlCapFloorTermVolSurfaceOptionDates"),
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
            TempStrNoSize("\x46""Returns the option dates from the given CapFloorTermVolSurface object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CapFloorTermVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlCapFloorTermVolSurfaceOptionDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlCapFloorTermVolSurfaceOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlCapFloorTermVolSurfaceOptionTenors"),
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
            TempStrNoSize("\x47""Returns the option tenors from the given CapFloorTermVolSurface object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CapFloorTermVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlCapFloorTermVolSurfaceOptionTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlCapFloorTermVolSurfaceStrikes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlCapFloorTermVolSurfaceStrikes"),
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
            TempStrNoSize("\x48""Returns the option strikes from the given CapFloorTermVolSurface object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CapFloorTermVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlCapFloorTermVolSurfaceStrikes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlConstantOptionletVolatility"),
            // parameter codes
            TempStrNoSize("\x0B""CCPCCPPPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlConstantOptionletVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,NDays,Calendar,BusinessDayConvention,Volatility,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Construct an object of class ConstantOptionletVolatility and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x70""number of days to advance from EvaluationDate: it fixes the date at which the variance = 0.0. Default value = 0."),
            TempStrNoSize("\x59""holiday calendar (e.g. TARGET) used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x24""cap/floor constant volatility Quote."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlConstantOptionletVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlOptionletStripper1"),
            // parameter codes
            TempStrNoSize("\x0B""CCCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlOptionletStripper1"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5B""ObjectId,TermVolSurface,IborIndex,SwitchStrike,Accuracy,MaxIter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class OptionletStripper1 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""CapFloorTermVolSurface object ID."),
            TempStrNoSize("\x14""cap index object ID."),
            TempStrNoSize("\x40""switch strike. Default value = QuantLib::Null<QuantLib::Rate>()."),
            TempStrNoSize("\x28""solver accuracy. Default value = 1.0e-6."),
            TempStrNoSize("\x2B""solver max iterations. Default value = 100."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlOptionletStripper1"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlOptionletStripper1CapFloorPrices"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x22""qlOptionletStripper1CapFloorPrices"),
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
            TempStrNoSize("\x46""Returns option prices matrix from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlOptionletStripper1CapFloorPrices"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlOptionletStripper1CapFloorVolatilities"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlOptionletStripper1CapFloorVolatilities"),
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
            TempStrNoSize("\x4C""Returns option volatilities matrix from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlOptionletStripper1CapFloorVolatilities"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlOptionletStripper1OptionletPrices"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x23""qlOptionletStripper1OptionletPrices"),
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
            TempStrNoSize("\x49""Returns optionlet prices matrix from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlOptionletStripper1OptionletPrices"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlOptionletStripper1SwitchStrike"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlOptionletStripper1SwitchStrike"),
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
            TempStrNoSize("\x46""Returns option switch strike from the given OptionletStripper1 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlOptionletStripper1SwitchStrike"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlOptionletStripper2"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlOptionletStripper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,OptionletStripper1,TermVolCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class OptionletStripper2 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""OptionletStripper1 object id."),
            TempStrNoSize("\x1F""CapFloorTermVolCurve object id."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlOptionletStripper2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlOptionletStripper2AtmCapFloorPrices"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlOptionletStripper2AtmCapFloorPrices"),
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
            TempStrNoSize("\x43""Returns ATM option prices from the given OptionletStripper2 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper2 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlOptionletStripper2AtmCapFloorPrices"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlOptionletStripper2AtmCapFloorStrikes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlOptionletStripper2AtmCapFloorStrikes"),
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
            TempStrNoSize("\x44""Returns option ATM strikes from the given OptionletStripper2 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper2 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlOptionletStripper2AtmCapFloorStrikes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlOptionletStripper2SpreadsVol"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlOptionletStripper2SpreadsVol"),
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
            TempStrNoSize("\x5D""Returns optionlet spread (with respect to ATM) vols from the given OptionletStripper2 object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::OptionletStripper2 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlOptionletStripper2SpreadsVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlOptionletStripperOptionletAccrualPeriods"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlOptionletStripperOptionletAccrualPeriods"),
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
            TempStrNoSize("\x4A""Returns optionlet accrual periods from the given OptionletStripper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::OptionletStripper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlOptionletStripperOptionletAccrualPeriods"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlOptionletStripperOptionletFixingTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlOptionletStripperOptionletFixingTenors"),
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
            TempStrNoSize("\x48""Returns optionlet fixing tenors from the given OptionletStripper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::OptionletStripper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlOptionletStripperOptionletFixingTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlOptionletStripperOptionletPaymentDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlOptionletStripperOptionletPaymentDates"),
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
            TempStrNoSize("\x48""Returns optionlet payment dates from the given OptionletStripper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::OptionletStripper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlOptionletStripperOptionletPaymentDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlOptionletVTSBlackVariance"),
            // parameter codes
            TempStrNoSize("\x07""PCPELP#"),
            // function display name
            TempStrNoSize("\x1B""qlOptionletVTSBlackVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the black variance corresponding to a given strike for a given exercise date."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x16""cap/floor expiry date."),
            TempStrNoSize("\x18""cap/floor strike vector."),
            TempStrNoSize("\x2F""Extrapolation Flag (TRUE allows extrapolation)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlOptionletVTSBlackVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlOptionletVTSBlackVariance2"),
            // parameter codes
            TempStrNoSize("\x07""PCPELP#"),
            // function display name
            TempStrNoSize("\x1C""qlOptionletVTSBlackVariance2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,OptionTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the black variance corresponding to a given strike for a given exercise date."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x16""cap/floor expiry date."),
            TempStrNoSize("\x18""cap/floor strike vector."),
            TempStrNoSize("\x2F""Extrapolation Flag (TRUE allows extrapolation)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlOptionletVTSBlackVariance2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlOptionletVTSVolatility"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x18""qlOptionletVTSVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns volatility from the given OptionletVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x1C""caplet/floorlet expiry date."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlOptionletVTSVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x19""qlOptionletVTSVolatility2"),
            // parameter codes
            TempStrNoSize("\x07""PCCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlOptionletVTSVolatility2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,OptionTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns volatility from the given OptionletVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::OptionletVolatilityStructure object"),
            TempStrNoSize("\x1D""caplet/floorlet option tenor."),
            TempStrNoSize("\x17""caplet/floorlet strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlOptionletVTSVolatility2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x2E""qlRelinkableHandleOptionletVolatilityStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x2E""qlRelinkableHandleOptionletVolatilityStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,CurrentLink,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x98""Construct an object of class RelinkableHandleImpl<QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x70""OptionletVolatilityStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2E""qlRelinkableHandleOptionletVolatilityStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSpreadedOptionletVolatility"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlSpreadedOptionletVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""ObjectId,BaseVolStructure,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Construct an object of class SpreadedOptionletVolatility and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Base OptionletVolatilityStructure object ID."),
            TempStrNoSize("\x07""spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlSpreadedOptionletVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x13""qlStrippedOptionlet"),
            // parameter codes
            TempStrNoSize("\x0E""CCPCCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlStrippedOptionlet"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8B""ObjectId,SettlementDays,Calendar,BusinessDayConvention,IborIndex,OptionletDates,Strikes,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class StrippedOptionlet and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2D""number of settlement days. Default value = 0."),
            TempStrNoSize("\x59""holiday calendar (e.g. TARGET) used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x10""optionlet dates."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x0B""vol quotes."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlStrippedOptionlet"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlStrippedOptionletAdapter"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlStrippedOptionletAdapter"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3A""ObjectId,StrippedOptionletBase,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class StrippedOptionletAdapter and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""Stripped Optionlet object id."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlStrippedOptionletAdapter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlStrippedOptionletBaseAtmOptionletRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlStrippedOptionletBaseAtmOptionletRates"),
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
            TempStrNoSize("\x48""Returns atm optionlet rates from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlStrippedOptionletBaseAtmOptionletRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseBusinessDayConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseBusinessDayConvention"),
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
            TempStrNoSize("\x45""Returns the business day convention used in tenor to date conversion."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlStrippedOptionletBaseBusinessDayConvention"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlStrippedOptionletBaseCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1F""qlStrippedOptionletBaseCalendar"),
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
            TempStrNoSize("\x44""Returns the calendar used by the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlStrippedOptionletBaseCalendar"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlStrippedOptionletBaseDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x21""qlStrippedOptionletBaseDayCounter"),
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
            TempStrNoSize("\x46""Returns the DayCounter used by the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlStrippedOptionletBaseDayCounter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingDates"),
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
            TempStrNoSize("\x4B""Returns optionlet fixing dates from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingTimes"),
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
            TempStrNoSize("\x4B""Returns optionlet fixing times from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlStrippedOptionletBaseOptionletFixingTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseOptionletVolatilities"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x2C""qlStrippedOptionletBaseOptionletVolatilities"),
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
            TempStrNoSize("\x4B""Returns optionlet volatilities from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x10""optionlet index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlStrippedOptionletBaseOptionletVolatilities"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlStrippedOptionletBaseSettlementDays"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x25""qlStrippedOptionletBaseSettlementDays"),
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
            TempStrNoSize("\x51""Returns the number of settlement days for the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlStrippedOptionletBaseSettlementDays"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlStrippedOptionletBaseStrikes"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x1E""qlStrippedOptionletBaseStrikes"),
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
            TempStrNoSize("\x45""Returns optionlet strike from the given StrippedOptionletBase object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::StrippedOptionletBase object"),
            TempStrNoSize("\x10""optionlet index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlStrippedOptionletBaseStrikes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

