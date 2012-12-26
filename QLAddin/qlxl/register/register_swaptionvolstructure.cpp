
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

// register functions in category Swaptionvolstructure with Excel

void registerSwaptionvolstructure(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlConstantSwaptionVolatility"),
            // parameter codes
            TempStrNoSize("\x0B""CCPCCPPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlConstantSwaptionVolatility"),
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
            TempStrNoSize("\x49""Construct an object of class ConstantSwaptionVolatility and return its id"),
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

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlDenseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlDenseSabrParameters"),
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
            TempStrNoSize("\x4A""returns results of Sabr calibration for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlMarketVolCube"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlMarketVolCube"),
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
            TempStrNoSize("\x49""returns the market volatility cube for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x2D""qlRelinkableHandleSwaptionVolatilityStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x2D""qlRelinkableHandleSwaptionVolatilityStructure"),
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
            TempStrNoSize("\x96""Construct an object of class RelinkableHandleImpl<QuantLibAddin::SwaptionVolatilityStructure, QuantLib::SwaptionVolatilityStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x6F""SwaptionVolatilityStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSmileSectionByCube"),
            // parameter codes
            TempStrNoSize("\x09""CCCPCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlSmileSectionByCube"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,VolCube,OptionDate,SwapTenor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SmileSectionByCube and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x23""Swaption volatility cube object ID."),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x1F""smile's underlying swap length."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSmileSectionByCube2"),
            // parameter codes
            TempStrNoSize("\x09""CCCCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlSmileSectionByCube2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,VolCube,OptionDate,SwapTenor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SmileSectionByCube and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x23""Swaption volatility cube object ID."),
            TempStrNoSize("\x19""smile's expiry as period."),
            TempStrNoSize("\x1F""smile's underlying swap length."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSparseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlSparseSabrParameters"),
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
            TempStrNoSize("\x4A""returns results of Sabr calibration for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSpreadedSwaptionVolatility"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlSpreadedSwaptionVolatility"),
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
            TempStrNoSize("\x49""Construct an object of class SpreadedSwaptionVolatility and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""Base SwaptionVolatilityStructure object ID."),
            TempStrNoSize("\x07""spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSwaptionVTSBlackVariance"),
            // parameter codes
            TempStrNoSize("\x08""PCPCEPP#"),
            // function display name
            TempStrNoSize("\x1A""qlSwaptionVTSBlackVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,OptionDate,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns variance from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x16""underlying swap tenor."),
            TempStrNoSize("\x17""swaption strike vector."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSwaptionVTSBlackVariance2"),
            // parameter codes
            TempStrNoSize("\x08""PCPCEPP#"),
            // function display name
            TempStrNoSize("\x1B""qlSwaptionVTSBlackVariance2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""ObjectId,OptionTenor,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns variance from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x16""swaption option tenor."),
            TempStrNoSize("\x16""underlying swap tenor."),
            TempStrNoSize("\x17""swaption strike vector."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlSwaptionVTSBusinessDayConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x22""qlSwaptionVTSBusinessDayConvention"),
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
            TempStrNoSize("\x75""Returns the business day convention used for option date calculation by the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x13""qlSwaptionVTSMatrix"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlSwaptionVTSMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x73""ObjectId,Calendar,BusinessDayConvention,OptionTenors,SwapTenors,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class SwaptionVolatilityMatrix and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x59""holiday calendar (e.g. TARGET) used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x1D""swaption expiries as periods."),
            TempStrNoSize("\x18""underlying swap lengths."),
            TempStrNoSize("\x0B""vol quotes."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSwaptionVTSMatrixLocate"),
            // parameter codes
            TempStrNoSize("\x06""PCPCP#"),
            // function display name
            TempStrNoSize("\x19""qlSwaptionVTSMatrixLocate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x25""ObjectId,OptionDate,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns the lower indexes of surrounding volatility matrix corners for the given SwaptionVolatilityMatrix object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::SwaptionVolatilityMatrix object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSwaptionVTSMatrixOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlSwaptionVTSMatrixOptionDates"),
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
            TempStrNoSize("\x5E""Returns the vector of swaption exercise dates for the given SwaptionVolatilityDiscrete object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::SwaptionVolatilityDiscrete object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSwaptionVTSMatrixOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlSwaptionVTSMatrixOptionTenors"),
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
            TempStrNoSize("\x5F""Returns the vector of swaption exercise tenors for the given SwaptionVolatilityDiscrete object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::SwaptionVolatilityDiscrete object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSwaptionVTSMatrixSwapTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlSwaptionVTSMatrixSwapTenors"),
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
            TempStrNoSize("\x5D""Returns the vector of underlying swap tenors for the given SwaptionVolatilityDiscrete object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::SwaptionVolatilityDiscrete object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSwaptionVTSMaxSwapTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x19""qlSwaptionVTSMaxSwapTenor"),
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
            TempStrNoSize("\x70""Returns the max swap tenor (i.e. length) for which the given SwaptionVolatilityStructure object can return vols."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSwaptionVTSOptionDateFromTenor"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlSwaptionVTSOptionDateFromTenor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,OptionTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xAA""Returns the option date corresponding to a given option tenor, taking calendar and business day convention into account, for the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x16""swaption option tenor."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSwaptionVTSSwapLength"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x17""qlSwaptionVTSSwapLength"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6D""Returns the swap length corresponding to a given swap tenor for the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x0B""swap tenor."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwaptionVTSSwapLength2"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x18""qlSwaptionVTSSwapLength2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x22""ObjectId,SwapStart,SwapEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x77""Returns the swap length corresponding to a given swap start/end dates for the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x10""swap start date."),
            TempStrNoSize("\x0E""swap end date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSwaptionVTSVolatility"),
            // parameter codes
            TempStrNoSize("\x08""PCPCPPP#"),
            // function display name
            TempStrNoSize("\x17""qlSwaptionVTSVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,OptionDate,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns volatility from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x10""swaption strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwaptionVTSVolatility2"),
            // parameter codes
            TempStrNoSize("\x08""PCCCPPP#"),
            // function display name
            TempStrNoSize("\x18""qlSwaptionVTSVolatility2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""ObjectId,OptionTenor,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns volatility from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x16""swaption option tenor."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x10""swaption strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSwaptionVTSatmStrike"),
            // parameter codes
            TempStrNoSize("\x06""PCPCP#"),
            // function display name
            TempStrNoSize("\x16""qlSwaptionVTSatmStrike"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x25""ObjectId,OptionDate,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8C""Returns the at-the-money swaption strike, for a given exercise date and underlying swap length, for the given SwaptionVolatilityCube object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::SwaptionVolatilityCube object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSwaptionVTSatmStrike2"),
            // parameter codes
            TempStrNoSize("\x06""PCPCP#"),
            // function display name
            TempStrNoSize("\x17""qlSwaptionVTSatmStrike2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,OptionTenor,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8B""Returns the at-the-money swaption strike, for a given option tenor and underlying swap length, for the given SwaptionVolatilityCube object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::SwaptionVolatilityCube object"),
            TempStrNoSize("\x18""swaption's option tenor."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSwaptionVolCube1"),
            // parameter codes
            TempStrNoSize("\x14""CCCPPPPCCPPPLPPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlSwaptionVolCube1"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDB""ObjectId,AtmVolStructure,OptionTenors,SwapTenors,StrikeSpreads,SpreadVols,SwapIndexBase,ShortSwapIndexBase,VegaWeightedSmileFit,Guess,IsFixed,IsAtmCalibrated,EndCriteria,MaxErrorTol,OptMethod,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class SwaptionVolCube1 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""At-the-money volatility structure."),
            TempStrNoSize("\x21""smile cube's expiries as periods."),
            TempStrNoSize("\x25""smile cube's underlying swap lengths."),
            TempStrNoSize("\x35""smile cube's strike spreads over the ATM strike rate."),
            TempStrNoSize("\x1C""matrix of spread vol quotes."),
            TempStrNoSize("\x19""Base SwapIndex object ID."),
            TempStrNoSize("\x1F""Short base SwapIndex object ID."),
            TempStrNoSize("\x4C""if TRUE the smile fit is weighted using options' vega. Default value = true."),
            TempStrNoSize("\x22""matrix of parameters guess quotes."),
            TempStrNoSize("\x2A""if TRUE parameter guess is not calibrated."),
            TempStrNoSize("\x2E""if TRUE the cube is calibrated to atm matrix ."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x46""max error tolerance. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x2F""Optmization method object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSwaptionVolCube2"),
            // parameter codes
            TempStrNoSize("\x0E""CCCPPPPCCPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlSwaptionVolCube2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x99""ObjectId,AtmVolStructure,OptionTenor,SwapTenor,StrikeSpreads,SpreadVols,SwapIndexBase,ShortSwapIndexBase,VegaWeightedSmileFit,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class SwaptionVolCube2 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""At-the-money volatility structure."),
            TempStrNoSize("\x21""smile cube's expiries as periods."),
            TempStrNoSize("\x25""smile cube's underlying swap lengths."),
            TempStrNoSize("\x35""smile cube's strike spreads over the ATM strike rate."),
            TempStrNoSize("\x1C""matrix of spread vol quotes."),
            TempStrNoSize("\x19""Base SwapIndex object ID."),
            TempStrNoSize("\x1F""Short base SwapIndex object ID."),
            TempStrNoSize("\x4C""if TRUE the smile fit is weighted using options' vega. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlVolCubeAtmCalibrated"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlVolCubeAtmCalibrated"),
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
            TempStrNoSize("\x5B""returns the volatility cube calibrated to ATM matrix for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Swaptionvolstructure with Excel

void unregisterSwaptionvolstructure(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlConstantSwaptionVolatility"),
            // parameter codes
            TempStrNoSize("\x0B""CCPCCPPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlConstantSwaptionVolatility"),
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
            TempStrNoSize("\x49""Construct an object of class ConstantSwaptionVolatility and return its id"),
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
            TempStrNoSize("\x1C""qlConstantSwaptionVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlDenseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlDenseSabrParameters"),
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
            TempStrNoSize("\x4A""returns results of Sabr calibration for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlDenseSabrParameters"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlMarketVolCube"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlMarketVolCube"),
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
            TempStrNoSize("\x49""returns the market volatility cube for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlMarketVolCube"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x2D""qlRelinkableHandleSwaptionVolatilityStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x2D""qlRelinkableHandleSwaptionVolatilityStructure"),
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
            TempStrNoSize("\x96""Construct an object of class RelinkableHandleImpl<QuantLibAddin::SwaptionVolatilityStructure, QuantLib::SwaptionVolatilityStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x6F""SwaptionVolatilityStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2D""qlRelinkableHandleSwaptionVolatilityStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSmileSectionByCube"),
            // parameter codes
            TempStrNoSize("\x09""CCCPCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlSmileSectionByCube"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,VolCube,OptionDate,SwapTenor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SmileSectionByCube and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x23""Swaption volatility cube object ID."),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x1F""smile's underlying swap length."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlSmileSectionByCube"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSmileSectionByCube2"),
            // parameter codes
            TempStrNoSize("\x09""CCCCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlSmileSectionByCube2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,VolCube,OptionDate,SwapTenor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SmileSectionByCube and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x23""Swaption volatility cube object ID."),
            TempStrNoSize("\x19""smile's expiry as period."),
            TempStrNoSize("\x1F""smile's underlying swap length."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlSmileSectionByCube2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSparseSabrParameters"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlSparseSabrParameters"),
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
            TempStrNoSize("\x4A""returns results of Sabr calibration for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSparseSabrParameters"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSpreadedSwaptionVolatility"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlSpreadedSwaptionVolatility"),
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
            TempStrNoSize("\x49""Construct an object of class SpreadedSwaptionVolatility and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""Base SwaptionVolatilityStructure object ID."),
            TempStrNoSize("\x07""spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlSpreadedSwaptionVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSwaptionVTSBlackVariance"),
            // parameter codes
            TempStrNoSize("\x08""PCPCEPP#"),
            // function display name
            TempStrNoSize("\x1A""qlSwaptionVTSBlackVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,OptionDate,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns variance from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x16""underlying swap tenor."),
            TempStrNoSize("\x17""swaption strike vector."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlSwaptionVTSBlackVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSwaptionVTSBlackVariance2"),
            // parameter codes
            TempStrNoSize("\x08""PCPCEPP#"),
            // function display name
            TempStrNoSize("\x1B""qlSwaptionVTSBlackVariance2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""ObjectId,OptionTenor,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns variance from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x16""swaption option tenor."),
            TempStrNoSize("\x16""underlying swap tenor."),
            TempStrNoSize("\x17""swaption strike vector."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSwaptionVTSBlackVariance2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlSwaptionVTSBusinessDayConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x22""qlSwaptionVTSBusinessDayConvention"),
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
            TempStrNoSize("\x75""Returns the business day convention used for option date calculation by the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlSwaptionVTSBusinessDayConvention"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x13""qlSwaptionVTSMatrix"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlSwaptionVTSMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x73""ObjectId,Calendar,BusinessDayConvention,OptionTenors,SwapTenors,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class SwaptionVolatilityMatrix and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x59""holiday calendar (e.g. TARGET) used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x52""Business day convention used for calculating the exercise dates from the expiries."),
            TempStrNoSize("\x1D""swaption expiries as periods."),
            TempStrNoSize("\x18""underlying swap lengths."),
            TempStrNoSize("\x0B""vol quotes."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlSwaptionVTSMatrix"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSwaptionVTSMatrixLocate"),
            // parameter codes
            TempStrNoSize("\x06""PCPCP#"),
            // function display name
            TempStrNoSize("\x19""qlSwaptionVTSMatrixLocate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x25""ObjectId,OptionDate,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns the lower indexes of surrounding volatility matrix corners for the given SwaptionVolatilityMatrix object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::SwaptionVolatilityMatrix object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlSwaptionVTSMatrixLocate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSwaptionVTSMatrixOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlSwaptionVTSMatrixOptionDates"),
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
            TempStrNoSize("\x5E""Returns the vector of swaption exercise dates for the given SwaptionVolatilityDiscrete object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::SwaptionVolatilityDiscrete object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlSwaptionVTSMatrixOptionDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSwaptionVTSMatrixOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlSwaptionVTSMatrixOptionTenors"),
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
            TempStrNoSize("\x5F""Returns the vector of swaption exercise tenors for the given SwaptionVolatilityDiscrete object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::SwaptionVolatilityDiscrete object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlSwaptionVTSMatrixOptionTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSwaptionVTSMatrixSwapTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlSwaptionVTSMatrixSwapTenors"),
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
            TempStrNoSize("\x5D""Returns the vector of underlying swap tenors for the given SwaptionVolatilityDiscrete object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::SwaptionVolatilityDiscrete object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlSwaptionVTSMatrixSwapTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSwaptionVTSMaxSwapTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x19""qlSwaptionVTSMaxSwapTenor"),
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
            TempStrNoSize("\x70""Returns the max swap tenor (i.e. length) for which the given SwaptionVolatilityStructure object can return vols."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlSwaptionVTSMaxSwapTenor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSwaptionVTSOptionDateFromTenor"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlSwaptionVTSOptionDateFromTenor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,OptionTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xAA""Returns the option date corresponding to a given option tenor, taking calendar and business day convention into account, for the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x16""swaption option tenor."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlSwaptionVTSOptionDateFromTenor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSwaptionVTSSwapLength"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x17""qlSwaptionVTSSwapLength"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6D""Returns the swap length corresponding to a given swap tenor for the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x0B""swap tenor."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSwaptionVTSSwapLength"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwaptionVTSSwapLength2"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x18""qlSwaptionVTSSwapLength2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x22""ObjectId,SwapStart,SwapEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x77""Returns the swap length corresponding to a given swap start/end dates for the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x10""swap start date."),
            TempStrNoSize("\x0E""swap end date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSwaptionVTSSwapLength2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSwaptionVTSVolatility"),
            // parameter codes
            TempStrNoSize("\x08""PCPCPPP#"),
            // function display name
            TempStrNoSize("\x17""qlSwaptionVTSVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,OptionDate,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns volatility from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x10""swaption strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSwaptionVTSVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwaptionVTSVolatility2"),
            // parameter codes
            TempStrNoSize("\x08""PCCCPPP#"),
            // function display name
            TempStrNoSize("\x18""qlSwaptionVTSVolatility2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""ObjectId,OptionTenor,SwapTenor,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns volatility from the given SwaptionVolatilityStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SwaptionVolatilityStructure object"),
            TempStrNoSize("\x16""swaption option tenor."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x10""swaption strike."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSwaptionVTSVolatility2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSwaptionVTSatmStrike"),
            // parameter codes
            TempStrNoSize("\x06""PCPCP#"),
            // function display name
            TempStrNoSize("\x16""qlSwaptionVTSatmStrike"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x25""ObjectId,OptionDate,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8C""Returns the at-the-money swaption strike, for a given exercise date and underlying swap length, for the given SwaptionVolatilityCube object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::SwaptionVolatilityCube object"),
            TempStrNoSize("\x15""swaption expiry date."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSwaptionVTSatmStrike"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSwaptionVTSatmStrike2"),
            // parameter codes
            TempStrNoSize("\x06""PCPCP#"),
            // function display name
            TempStrNoSize("\x17""qlSwaptionVTSatmStrike2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,OptionTenor,SwapTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8B""Returns the at-the-money swaption strike, for a given option tenor and underlying swap length, for the given SwaptionVolatilityCube object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::SwaptionVolatilityCube object"),
            TempStrNoSize("\x18""swaption's option tenor."),
            TempStrNoSize("\x2B""Underlying swap length as period (e.g. 5Y)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSwaptionVTSatmStrike2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSwaptionVolCube1"),
            // parameter codes
            TempStrNoSize("\x14""CCCPPPPCCPPPLPPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlSwaptionVolCube1"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDB""ObjectId,AtmVolStructure,OptionTenors,SwapTenors,StrikeSpreads,SpreadVols,SwapIndexBase,ShortSwapIndexBase,VegaWeightedSmileFit,Guess,IsFixed,IsAtmCalibrated,EndCriteria,MaxErrorTol,OptMethod,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class SwaptionVolCube1 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""At-the-money volatility structure."),
            TempStrNoSize("\x21""smile cube's expiries as periods."),
            TempStrNoSize("\x25""smile cube's underlying swap lengths."),
            TempStrNoSize("\x35""smile cube's strike spreads over the ATM strike rate."),
            TempStrNoSize("\x1C""matrix of spread vol quotes."),
            TempStrNoSize("\x19""Base SwapIndex object ID."),
            TempStrNoSize("\x1F""Short base SwapIndex object ID."),
            TempStrNoSize("\x4C""if TRUE the smile fit is weighted using options' vega. Default value = true."),
            TempStrNoSize("\x22""matrix of parameters guess quotes."),
            TempStrNoSize("\x2A""if TRUE parameter guess is not calibrated."),
            TempStrNoSize("\x2E""if TRUE the cube is calibrated to atm matrix ."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x46""max error tolerance. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x2F""Optmization method object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlSwaptionVolCube1"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSwaptionVolCube2"),
            // parameter codes
            TempStrNoSize("\x0E""CCCPPPPCCPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlSwaptionVolCube2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x99""ObjectId,AtmVolStructure,OptionTenor,SwapTenor,StrikeSpreads,SpreadVols,SwapIndexBase,ShortSwapIndexBase,VegaWeightedSmileFit,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class SwaptionVolCube2 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""At-the-money volatility structure."),
            TempStrNoSize("\x21""smile cube's expiries as periods."),
            TempStrNoSize("\x25""smile cube's underlying swap lengths."),
            TempStrNoSize("\x35""smile cube's strike spreads over the ATM strike rate."),
            TempStrNoSize("\x1C""matrix of spread vol quotes."),
            TempStrNoSize("\x19""Base SwapIndex object ID."),
            TempStrNoSize("\x1F""Short base SwapIndex object ID."),
            TempStrNoSize("\x4C""if TRUE the smile fit is weighted using options' vega. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlSwaptionVolCube2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlVolCubeAtmCalibrated"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlVolCubeAtmCalibrated"),
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
            TempStrNoSize("\x5B""returns the volatility cube calibrated to ATM matrix for the given SwaptionVolCube1 object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLibAddin::SwaptionVolCube1 object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlVolCubeAtmCalibrated"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

