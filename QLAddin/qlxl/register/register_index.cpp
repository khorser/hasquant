
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

// register functions in category Index with Excel

void registerIndex(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlBMAIndex"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlBMAIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class BMAIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x07""qlEonia"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x07""qlEonia"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Construct an object of class Eonia and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x09""qlEuribor"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlEuribor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,Tenor,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class Euribor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x55""index tenor: SW (1W), 2W, 3W, 1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M, 11M, 12M (1Y)."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlEuribor365"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlEuribor365"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,Tenor,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class Euribor365 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x55""index tenor: SW (1W), 2W, 3W, 1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M, 11M, 12M (1Y)."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlEuriborSwap"),
            // parameter codes
            TempStrNoSize("\x0A""CCPCPPPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlEuriborSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,FixingType,Tenor,FwdCurve,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class EuriborSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x68""Swap index fixing type (e.g. IsdaFixA, IsdaFixB, IfrFix, IsdaFixAm, IsdaFixPm). Default value = Default."),
            TempStrNoSize("\x23""index tenor (e.g. 1Y for one year)."),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlEuriborSwapIsdaFixA"),
            // parameter codes
            TempStrNoSize("\x09""CCCPPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlEuriborSwapIsdaFixA"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Tenor,FwdCurve,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class EuriborSwapIsdaFixA and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""index tenor (e.g. 1Y for one year)"),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlIborIndex"),
            // parameter codes
            TempStrNoSize("\x0F""CCCCNCCCLCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlIborIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x80""ObjectId,FamilyName,Tenor,FixingDays,Currency,Calendar,BDayConvention,EndOfMonth,DayCounter,FwdCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class IborIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""index family name."),
            TempStrNoSize("\x5C""index tenor (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x37""TRUE if the index follow the 'end of month' convention."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlIborIndexBusinessDayConv"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1A""qlIborIndexBusinessDayConv"),
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
            TempStrNoSize("\x5D""Returns the business day convention (e.g. Modified Following) for the given IborIndex object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::IborIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlIborIndexEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x15""qlIborIndexEndOfMonth"),
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
            TempStrNoSize("\x51""Returns TRUE if the given IborIndex object follows the 'end of month' convention."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::IborIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlIndexAddFixings"),
            // parameter codes
            TempStrNoSize("\x07""LCPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlIndexAddFixings"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""ObjectId,FixingDates,FixingValues,ForceOverwrite,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""Adds fixings for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLibAddin::Index object"),
            TempStrNoSize("\x0D""fixing dates."),
            TempStrNoSize("\x0E""fixing values."),
            TempStrNoSize("\x54""Set to TRUE to force overwriting of existing fixings, if any. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlIndexAddFixings2"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x12""qlIndexAddFixings2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,TimeSeriesID,ForceOverwrite,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""Adds fixings for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x15""TimeSeries object ID."),
            TempStrNoSize("\x54""Set to TRUE to force overwriting of existing fixings, if any. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlIndexClearFixings"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x13""qlIndexClearFixings"),
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
            TempStrNoSize("\x2D""Clear all fixings for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlIndexFixing"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlIndexFixing"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,FixingDate,ForecastToday,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x85""Returns the fixing for the given Index object. The fixing is retrieved from the time series if available, otherways it is forecasted."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x0F""fixing date(s)."),
            TempStrNoSize("\x94""If set to TRUE it forces the forecasting of today's fixing even if the actual fixing is already available in the time series. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlIndexFixingCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x15""qlIndexFixingCalendar"),
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
            TempStrNoSize("\x3E""Returns the calendar (e.g. TARGET) for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlIndexIsValidFixingDate"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlIndexIsValidFixingDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,FixingDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Returns TRUE if the fixing date is a valid one for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x0F""fixing date(s)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlIndexName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0B""qlIndexName"),
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
            TempStrNoSize("\x2C""Returns the name for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlInterestRateIndexCurrency"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1B""qlInterestRateIndexCurrency"),
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
            TempStrNoSize("\x47""Returns the currency (e.g. EUR) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexDayCounter"),
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
            TempStrNoSize("\x50""Returns the DayCounter (e.g. Actual/360) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexFamilyName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexFamilyName"),
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
            TempStrNoSize("\x4E""Returns the family name (e.g. EURIBOR) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDate"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,ValueDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the fixing date for the given value date for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x0B""value date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDays"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDays"),
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
            TempStrNoSize("\x48""Returns the fixing days (e.g. 2) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlInterestRateIndexMaturity"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1B""qlInterestRateIndexMaturity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,ValueDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5A""Returns the maturity date for the given value date for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x0B""value date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterestRateIndexTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterestRateIndexTenor"),
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
            TempStrNoSize("\x55""Returns the tenor (i.e. length, e.g. 6M, 10Y) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateIndexValueDate"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateIndexValueDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,FixingDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the value date for the given fixing date for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x0C""fixing date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x07""qlLibor"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x07""qlLibor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,Currency,Tenor,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Construct an object of class Libor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""Libor index currency."),
            TempStrNoSize("\x5E""index tenor: ON (1D), SW (1W), 2W, 3W, 1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M, 11M, 12M (1Y)."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlLiborSwap"),
            // parameter codes
            TempStrNoSize("\x0B""CCCPCPPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlLiborSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x51""ObjectId,Currency,FixingType,Tenor,FwdCurve,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class LiborSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""Libor swap index currency."),
            TempStrNoSize("\x68""Swap index fixing type (e.g. IsdaFixA, IsdaFixB, IfrFix, IsdaFixAm, IsdaFixPm). Default value = Default."),
            TempStrNoSize("\x23""index tenor (e.g. 1Y for one year)."),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x10""qlOvernightIndex"),
            // parameter codes
            TempStrNoSize("\x0C""CCCNCCCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlOvernightIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x62""ObjectId,FamilyName,FixingDays,Currency,Calendar,DayCounter,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class OvernightIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""index family name."),
            TempStrNoSize("\x15""fixing days (e.g. 0)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlProxyIbor"),
            // parameter codes
            TempStrNoSize("\x11""CCCCNCCCLCPCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlProxyIbor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x90""ObjectId,FamilyName,Tenor,FixingDays,Currency,Calendar,BDayConvention,EndOfMonth,DayCounter,Gearing,IborIndex,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class ProxyIbor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""index family name."),
            TempStrNoSize("\x5C""index tenor (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x37""TRUE if the index follow the 'end of month' convention."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x08""gearing."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x15""floating rate spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x07""qlSonia"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x07""qlSonia"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Construct an object of class Sonia and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlSwapIndex"),
            // parameter codes
            TempStrNoSize("\x10""CCCCNCCCCCCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlSwapIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x93""ObjectId,FamilyName,Tenor,FixingDays,Currency,Calendar,FixedLegTenor,FixedLegBDC,FixedLegDayCounter,IborIndex,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class SwapIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""index name."),
            TempStrNoSize("\x5B""index tenor (e.g. 2D for two days, 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x1F""swap rate fixing days (e.g. 2)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x3B""tenor of the underlying swap's fixed leg (e.g. 6M, 1Y, 3M)."),
            TempStrNoSize("\x54""business day convention of the underlying swap's fixed leg (e.g. ModifiedFollowing)."),
            TempStrNoSize("\x48""day counter of the underlying swap's fixed leg (e.g. 30/360::BondBasis)."),
            TempStrNoSize("\x25""swap's floating ibor index object ID."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSwapIndexFixedLegBDC"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x16""qlSwapIndexFixedLegBDC"),
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
            TempStrNoSize("\x5D""Returns the business day convention (e.g. Modified Following) for the given SwapIndex object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::SwapIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwapIndexFixedLegTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlSwapIndexFixedLegTenor"),
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
            TempStrNoSize("\x45""Returns the fixed leg tenor (e.g. 1Y) for the given SwapIndex object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::SwapIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Index with Excel

void unregisterIndex(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlBMAIndex"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlBMAIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class BMAIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlBMAIndex"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x07""qlEonia"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x07""qlEonia"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Construct an object of class Eonia and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x07""qlEonia"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x09""qlEuribor"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlEuribor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,Tenor,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class Euribor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x55""index tenor: SW (1W), 2W, 3W, 1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M, 11M, 12M (1Y)."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlEuribor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlEuribor365"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlEuribor365"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,Tenor,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class Euribor365 and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x55""index tenor: SW (1W), 2W, 3W, 1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M, 11M, 12M (1Y)."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlEuribor365"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlEuriborSwap"),
            // parameter codes
            TempStrNoSize("\x0A""CCPCPPPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlEuriborSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,FixingType,Tenor,FwdCurve,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class EuriborSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x68""Swap index fixing type (e.g. IsdaFixA, IsdaFixB, IfrFix, IsdaFixAm, IsdaFixPm). Default value = Default."),
            TempStrNoSize("\x23""index tenor (e.g. 1Y for one year)."),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlEuriborSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlEuriborSwapIsdaFixA"),
            // parameter codes
            TempStrNoSize("\x09""CCCPPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlEuriborSwapIsdaFixA"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Tenor,FwdCurve,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class EuriborSwapIsdaFixA and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""index tenor (e.g. 1Y for one year)"),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlEuriborSwapIsdaFixA"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlIborIndex"),
            // parameter codes
            TempStrNoSize("\x0F""CCCCNCCCLCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlIborIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x80""ObjectId,FamilyName,Tenor,FixingDays,Currency,Calendar,BDayConvention,EndOfMonth,DayCounter,FwdCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class IborIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""index family name."),
            TempStrNoSize("\x5C""index tenor (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x37""TRUE if the index follow the 'end of month' convention."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlIborIndex"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlIborIndexBusinessDayConv"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1A""qlIborIndexBusinessDayConv"),
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
            TempStrNoSize("\x5D""Returns the business day convention (e.g. Modified Following) for the given IborIndex object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::IborIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlIborIndexBusinessDayConv"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlIborIndexEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x15""qlIborIndexEndOfMonth"),
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
            TempStrNoSize("\x51""Returns TRUE if the given IborIndex object follows the 'end of month' convention."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::IborIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlIborIndexEndOfMonth"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlIndexAddFixings"),
            // parameter codes
            TempStrNoSize("\x07""LCPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlIndexAddFixings"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""ObjectId,FixingDates,FixingValues,ForceOverwrite,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""Adds fixings for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLibAddin::Index object"),
            TempStrNoSize("\x0D""fixing dates."),
            TempStrNoSize("\x0E""fixing values."),
            TempStrNoSize("\x54""Set to TRUE to force overwriting of existing fixings, if any. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlIndexAddFixings"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlIndexAddFixings2"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x12""qlIndexAddFixings2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,TimeSeriesID,ForceOverwrite,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""Adds fixings for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x15""TimeSeries object ID."),
            TempStrNoSize("\x54""Set to TRUE to force overwriting of existing fixings, if any. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlIndexAddFixings2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlIndexClearFixings"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x13""qlIndexClearFixings"),
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
            TempStrNoSize("\x2D""Clear all fixings for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlIndexClearFixings"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlIndexFixing"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlIndexFixing"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,FixingDate,ForecastToday,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x85""Returns the fixing for the given Index object. The fixing is retrieved from the time series if available, otherways it is forecasted."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x0F""fixing date(s)."),
            TempStrNoSize("\x94""If set to TRUE it forces the forecasting of today's fixing even if the actual fixing is already available in the time series. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlIndexFixing"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlIndexFixingCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x15""qlIndexFixingCalendar"),
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
            TempStrNoSize("\x3E""Returns the calendar (e.g. TARGET) for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlIndexFixingCalendar"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlIndexIsValidFixingDate"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlIndexIsValidFixingDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,FixingDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Returns TRUE if the fixing date is a valid one for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x0F""fixing date(s)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlIndexIsValidFixingDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlIndexName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0B""qlIndexName"),
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
            TempStrNoSize("\x2C""Returns the name for the given Index object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Index object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlIndexName"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlInterestRateIndexCurrency"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1B""qlInterestRateIndexCurrency"),
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
            TempStrNoSize("\x47""Returns the currency (e.g. EUR) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlInterestRateIndexCurrency"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexDayCounter"),
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
            TempStrNoSize("\x50""Returns the DayCounter (e.g. Actual/360) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlInterestRateIndexDayCounter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexFamilyName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexFamilyName"),
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
            TempStrNoSize("\x4E""Returns the family name (e.g. EURIBOR) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlInterestRateIndexFamilyName"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDate"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,ValueDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the fixing date for the given value date for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x0B""value date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDays"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDays"),
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
            TempStrNoSize("\x48""Returns the fixing days (e.g. 2) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlInterestRateIndexFixingDays"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlInterestRateIndexMaturity"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1B""qlInterestRateIndexMaturity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,ValueDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5A""Returns the maturity date for the given value date for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x0B""value date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlInterestRateIndexMaturity"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterestRateIndexTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterestRateIndexTenor"),
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
            TempStrNoSize("\x55""Returns the tenor (i.e. length, e.g. 6M, 10Y) for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterestRateIndexTenor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateIndexValueDate"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateIndexValueDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,FixingDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the value date for the given fixing date for the given InterestRateIndex object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::InterestRateIndex object"),
            TempStrNoSize("\x0C""fixing date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInterestRateIndexValueDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x07""qlLibor"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x07""qlLibor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,Currency,Tenor,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Construct an object of class Libor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""Libor index currency."),
            TempStrNoSize("\x5E""index tenor: ON (1D), SW (1W), 2W, 3W, 1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M, 11M, 12M (1Y)."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x07""qlLibor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlLiborSwap"),
            // parameter codes
            TempStrNoSize("\x0B""CCCPCPPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlLiborSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x51""ObjectId,Currency,FixingType,Tenor,FwdCurve,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class LiborSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1A""Libor swap index currency."),
            TempStrNoSize("\x68""Swap index fixing type (e.g. IsdaFixA, IsdaFixB, IfrFix, IsdaFixAm, IsdaFixPm). Default value = Default."),
            TempStrNoSize("\x23""index tenor (e.g. 1Y for one year)."),
            TempStrNoSize("\x3A""forwarding YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlLiborSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x10""qlOvernightIndex"),
            // parameter codes
            TempStrNoSize("\x0C""CCCNCCCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlOvernightIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x62""ObjectId,FamilyName,FixingDays,Currency,Calendar,DayCounter,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class OvernightIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""index family name."),
            TempStrNoSize("\x15""fixing days (e.g. 0)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlOvernightIndex"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlProxyIbor"),
            // parameter codes
            TempStrNoSize("\x11""CCCCNCCCLCPCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlProxyIbor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x90""ObjectId,FamilyName,Tenor,FixingDays,Currency,Calendar,BDayConvention,EndOfMonth,DayCounter,Gearing,IborIndex,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class ProxyIbor and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""index family name."),
            TempStrNoSize("\x5C""index tenor (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x37""TRUE if the index follow the 'end of month' convention."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x08""gearing."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x15""floating rate spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlProxyIbor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x07""qlSonia"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x07""qlSonia"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Construct an object of class Sonia and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""forecasting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x07""qlSonia"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlSwapIndex"),
            // parameter codes
            TempStrNoSize("\x10""CCCCNCCCCCCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlSwapIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x93""ObjectId,FamilyName,Tenor,FixingDays,Currency,Calendar,FixedLegTenor,FixedLegBDC,FixedLegDayCounter,IborIndex,DiscCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class SwapIndex and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""index name."),
            TempStrNoSize("\x5B""index tenor (e.g. 2D for two days, 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x1F""swap rate fixing days (e.g. 2)."),
            TempStrNoSize("\x0F""Index Currency."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x3B""tenor of the underlying swap's fixed leg (e.g. 6M, 1Y, 3M)."),
            TempStrNoSize("\x54""business day convention of the underlying swap's fixed leg (e.g. ModifiedFollowing)."),
            TempStrNoSize("\x48""day counter of the underlying swap's fixed leg (e.g. 30/360::BondBasis)."),
            TempStrNoSize("\x25""swap's floating ibor index object ID."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlSwapIndex"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSwapIndexFixedLegBDC"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x16""qlSwapIndexFixedLegBDC"),
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
            TempStrNoSize("\x5D""Returns the business day convention (e.g. Modified Following) for the given SwapIndex object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::SwapIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSwapIndexFixedLegBDC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSwapIndexFixedLegTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlSwapIndexFixedLegTenor"),
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
            TempStrNoSize("\x45""Returns the fixed leg tenor (e.g. 1Y) for the given SwapIndex object."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::SwapIndex object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSwapIndexFixedLegTenor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

