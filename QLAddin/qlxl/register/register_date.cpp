
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

// register functions in category Date with Excel

void registerDate(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDateEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x10""qlDateEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""returns the last day of the month to which the given date belongs."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlDateIsEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x12""qlDateIsEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""returns TRUE if a date is the last day of its month."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlDateIsLeap"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0C""qlDateIsLeap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Year,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1F""returns TRUE if a year is leap."),
            // parameter descriptions
            TempStrNoSize("\x11""year (e.g. 2006)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlDateMaxDate"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x0D""qlDateMaxDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2C""returns the latest date allowed in QuantLib."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlDateMinDate"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x0D""qlDateMinDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""returns the earliest date allowed in QuantLib."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlDateNextWeekday"),
            // parameter codes
            TempStrNoSize("\x05""PPCP#"),
            // function display name
            TempStrNoSize("\x11""qlDateNextWeekday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x14""Date,Weekday,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x94""Returns the next given weekday following or equal to the given date (e.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002)."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x21""Weekday (e.g. Wednesday, or Wed)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDateNthWeekday"),
            // parameter codes
            TempStrNoSize("\x07""NNCCNP#"),
            // function display name
            TempStrNoSize("\x10""qlDateNthWeekday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1E""Nth,Weekday,Month,Year,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x78""Returns the n-th given weekday in the given month and year (e.g., the 4th Thursday of March, 1998 was March 26th, 1998)."),
            // parameter descriptions
            TempStrNoSize("\x30""ordinal number (greater than zero, less than 6)."),
            TempStrNoSize("\x21""Weekday (e.g. Wednesday, or Wed)."),
            TempStrNoSize("\x25""Month (e.g. January, or Jan, or '1')."),
            TempStrNoSize("\x11""year (e.g. 2007)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlECBAddDate"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x0C""qlECBAddDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""add an ECB date to the list of known ECB dates."),
            // parameter descriptions
            TempStrNoSize("\x2B""to be added to the list of known ECB dates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBIsECBcode"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBIsECBcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Code,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""returns whether or not the given code is an ECB code."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBIsECBdate"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBIsECBdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""returns whether or not the given date is an ECB maintenance period start date."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlECBKnownDates"),
            // parameter codes
            TempStrNoSize("\x03""PP#"),
            // function display name
            TempStrNoSize("\x0F""qlECBKnownDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""returns all the known ECB maintenance period start dates."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlECBNextCode"),
            // parameter codes
            TempStrNoSize("\x04""CPP#"),
            // function display name
            TempStrNoSize("\x0D""qlECBNextCode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""returns the code for the first ECB date."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBNextCode2"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBNextCode2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Code,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns the code for the next ECB date."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlECBNextDate"),
            // parameter codes
            TempStrNoSize("\x04""NPP#"),
            // function display name
            TempStrNoSize("\x0D""qlECBNextDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""returns the next ECB maintenance period start date following the given date."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBNextDate2"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBNextDate2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Code,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""returns the next ECB maintenance period start date following the given date."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBNextDates"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBNextDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""returns all the known ECB maintenance period start dates following the given date."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlECBRemoveDate"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x0F""qlECBRemoveDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""remove an ECB date from the list of known ECB dates."),
            // parameter descriptions
            TempStrNoSize("\x2F""to be removed from the list of known ECB dates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x09""qlECBcode"),
            // parameter codes
            TempStrNoSize("\x04""CPP#"),
            // function display name
            TempStrNoSize("\x09""qlECBcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""ECBdate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8F""returns the code corresponding to a given ECB date (e.g. MAR10 for Wednesday, March xxth, 2010). It fails if the input date is not an ECB date."),
            // parameter descriptions
            TempStrNoSize("\x09""ECB date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x09""qlECBdate"),
            // parameter codes
            TempStrNoSize("\x05""NCPP#"),
            // function display name
            TempStrNoSize("\x09""qlECBdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ECBcode,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""returns the ECB maintenance period start date for the given ECB code."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlECBdate2"),
            // parameter codes
            TempStrNoSize("\x05""NCNP#"),
            // function display name
            TempStrNoSize("\x0A""qlECBdate2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""Month,Year,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""returns the ECB maintenance period start date in the given month/year."),
            // parameter descriptions
            TempStrNoSize("\x25""month (e.g. January, or Jan, or '1')."),
            TempStrNoSize("\x11""year (e.g. 2010)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlFrequencyFromPeriod"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x15""qlFrequencyFromPeriod"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0E""Period,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""returns a Frequency from a given Period (e.g. SemiAnnual from 6M)."),
            // parameter descriptions
            TempStrNoSize("\x65""period(s) to advance (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMIsIMMcode"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMIsIMMcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""Code,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""returns whether or not the given code is an IMM code."),
            // parameter descriptions
            TempStrNoSize("\x1A""2 letter string (e.g. H6)."),
            TempStrNoSize("\x8F""FALSE to consider all futures (serial ones included), not just the main March/June/September/December (H, M, U, Z) cycle. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMIsIMMdate"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMIsIMMdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""Date,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""returns whether or not the given date is an IMM date."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x66""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlIMMNextCode"),
            // parameter codes
            TempStrNoSize("\x05""CPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlIMMNextCode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7C""returns the code for the first contract listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x66""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMNextCodes"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMNextCodes"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7D""returns the codes for the next contracts listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x7D""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = std::vector<bool>(40, true)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlIMMNextDate"),
            // parameter codes
            TempStrNoSize("\x05""NPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlIMMNextDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x85""returns the delivery date for the first contract listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x66""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMNextDates"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMNextDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x86""returns the delivery dates for the next contracts listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x7D""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = std::vector<bool>(40, true)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x09""qlIMMcode"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x09""qlIMMcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""IMMdate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8C""returns the code corresponding to a given IMM date (e.g. H6 for Wednesday, March 15th, 2006). It fails if the input date is not an IMM date."),
            // parameter descriptions
            TempStrNoSize("\x09""IMM date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x09""qlIMMdate"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x09""qlIMMdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""IMMcode,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x63""returns the IMM date corresponding to the given IMM code (e.g. Wednesday, March 15th, 2006 for H6)."),
            // parameter descriptions
            TempStrNoSize("\x1C""2 letter IMM code (e.g. H6)."),
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlPeriodEquivalent"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x12""qlPeriodEquivalent"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0E""Period,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Returns the period equivalent to the input (e.g. 11M for 1Y-1M)."),
            // parameter descriptions
            TempStrNoSize("\x1A""input period (e.g. 1Y-1M)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlPeriodFromFrequency"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x15""qlPeriodFromFrequency"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x11""Frequency,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""returns a Period from a given Frequency (e.g. 6M from SemiAnnual)."),
            // parameter descriptions
            TempStrNoSize("\x50""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x10""qlPeriodLessThan"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x10""qlPeriodLessThan"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""Period1,Period2,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns TRUE if the first period is less than the second."),
            // parameter descriptions
            TempStrNoSize("\x0F""left hand side."),
            TempStrNoSize("\x10""right hand side."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Date with Excel

void unregisterDate(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDateEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x10""qlDateEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""returns the last day of the month to which the given date belongs."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlDateEndOfMonth"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlDateIsEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x12""qlDateIsEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""returns TRUE if a date is the last day of its month."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlDateIsEndOfMonth"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlDateIsLeap"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0C""qlDateIsLeap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Year,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1F""returns TRUE if a year is leap."),
            // parameter descriptions
            TempStrNoSize("\x11""year (e.g. 2006)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlDateIsLeap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlDateMaxDate"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x0D""qlDateMaxDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2C""returns the latest date allowed in QuantLib."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlDateMaxDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlDateMinDate"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x0D""qlDateMinDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""returns the earliest date allowed in QuantLib."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlDateMinDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlDateNextWeekday"),
            // parameter codes
            TempStrNoSize("\x05""PPCP#"),
            // function display name
            TempStrNoSize("\x11""qlDateNextWeekday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x14""Date,Weekday,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x94""Returns the next given weekday following or equal to the given date (e.g., the Friday following Tuesday, January 15th, 2002 was January 18th, 2002)."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x21""Weekday (e.g. Wednesday, or Wed)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlDateNextWeekday"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDateNthWeekday"),
            // parameter codes
            TempStrNoSize("\x07""NNCCNP#"),
            // function display name
            TempStrNoSize("\x10""qlDateNthWeekday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1E""Nth,Weekday,Month,Year,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x78""Returns the n-th given weekday in the given month and year (e.g., the 4th Thursday of March, 1998 was March 26th, 1998)."),
            // parameter descriptions
            TempStrNoSize("\x30""ordinal number (greater than zero, less than 6)."),
            TempStrNoSize("\x21""Weekday (e.g. Wednesday, or Wed)."),
            TempStrNoSize("\x25""Month (e.g. January, or Jan, or '1')."),
            TempStrNoSize("\x11""year (e.g. 2007)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlDateNthWeekday"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlECBAddDate"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x0C""qlECBAddDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""add an ECB date to the list of known ECB dates."),
            // parameter descriptions
            TempStrNoSize("\x2B""to be added to the list of known ECB dates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlECBAddDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBIsECBcode"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBIsECBcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Code,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""returns whether or not the given code is an ECB code."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlECBIsECBcode"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBIsECBdate"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBIsECBdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""returns whether or not the given date is an ECB maintenance period start date."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlECBIsECBdate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlECBKnownDates"),
            // parameter codes
            TempStrNoSize("\x03""PP#"),
            // function display name
            TempStrNoSize("\x0F""qlECBKnownDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""returns all the known ECB maintenance period start dates."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlECBKnownDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlECBNextCode"),
            // parameter codes
            TempStrNoSize("\x04""CPP#"),
            // function display name
            TempStrNoSize("\x0D""qlECBNextCode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""returns the code for the first ECB date."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlECBNextCode"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBNextCode2"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBNextCode2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Code,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns the code for the next ECB date."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlECBNextCode2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlECBNextDate"),
            // parameter codes
            TempStrNoSize("\x04""NPP#"),
            // function display name
            TempStrNoSize("\x0D""qlECBNextDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""returns the next ECB maintenance period start date following the given date."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlECBNextDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBNextDate2"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBNextDate2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Code,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""returns the next ECB maintenance period start date following the given date."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlECBNextDate2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlECBNextDates"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x0E""qlECBNextDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""returns all the known ECB maintenance period start dates following the given date."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlECBNextDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlECBRemoveDate"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x0F""qlECBRemoveDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""remove an ECB date from the list of known ECB dates."),
            // parameter descriptions
            TempStrNoSize("\x2F""to be removed from the list of known ECB dates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlECBRemoveDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x09""qlECBcode"),
            // parameter codes
            TempStrNoSize("\x04""CPP#"),
            // function display name
            TempStrNoSize("\x09""qlECBcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""ECBdate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8F""returns the code corresponding to a given ECB date (e.g. MAR10 for Wednesday, March xxth, 2010). It fails if the input date is not an ECB date."),
            // parameter descriptions
            TempStrNoSize("\x09""ECB date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlECBcode"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x09""qlECBdate"),
            // parameter codes
            TempStrNoSize("\x05""NCPP#"),
            // function display name
            TempStrNoSize("\x09""qlECBdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ECBcode,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""returns the ECB maintenance period start date for the given ECB code."),
            // parameter descriptions
            TempStrNoSize("\x1F""5 letter ECB code (e.g. MAR10)."),
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlECBdate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlECBdate2"),
            // parameter codes
            TempStrNoSize("\x05""NCNP#"),
            // function display name
            TempStrNoSize("\x0A""qlECBdate2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""Month,Year,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""returns the ECB maintenance period start date in the given month/year."),
            // parameter descriptions
            TempStrNoSize("\x25""month (e.g. January, or Jan, or '1')."),
            TempStrNoSize("\x11""year (e.g. 2010)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlECBdate2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlFrequencyFromPeriod"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x15""qlFrequencyFromPeriod"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0E""Period,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""returns a Frequency from a given Period (e.g. SemiAnnual from 6M)."),
            // parameter descriptions
            TempStrNoSize("\x65""period(s) to advance (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlFrequencyFromPeriod"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMIsIMMcode"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMIsIMMcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""Code,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""returns whether or not the given code is an IMM code."),
            // parameter descriptions
            TempStrNoSize("\x1A""2 letter string (e.g. H6)."),
            TempStrNoSize("\x8F""FALSE to consider all futures (serial ones included), not just the main March/June/September/December (H, M, U, Z) cycle. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlIMMIsIMMcode"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMIsIMMdate"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMIsIMMdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""Date,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""returns whether or not the given date is an IMM date."),
            // parameter descriptions
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x66""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlIMMIsIMMdate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlIMMNextCode"),
            // parameter codes
            TempStrNoSize("\x05""CPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlIMMNextCode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7C""returns the code for the first contract listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x66""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlIMMNextCode"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMNextCodes"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMNextCodes"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7D""returns the codes for the next contracts listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x7D""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = std::vector<bool>(40, true)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlIMMNextCodes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlIMMNextDate"),
            // parameter codes
            TempStrNoSize("\x05""NPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlIMMNextDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x85""returns the delivery date for the first contract listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x66""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlIMMNextDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlIMMNextDates"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlIMMNextDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x19""RefDate,MainCycle,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x86""returns the delivery dates for the next contracts listed in the International Money Market section of the Chicago Mercantile Exchange."),
            // parameter descriptions
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x7D""TRUE to consider the main March/June/September/December (H, M, U, Z) cycle only. Default value = std::vector<bool>(40, true)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlIMMNextDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x09""qlIMMcode"),
            // parameter codes
            TempStrNoSize("\x04""PPP#"),
            // function display name
            TempStrNoSize("\x09""qlIMMcode"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""IMMdate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x8C""returns the code corresponding to a given IMM date (e.g. H6 for Wednesday, March 15th, 2006). It fails if the input date is not an IMM date."),
            // parameter descriptions
            TempStrNoSize("\x09""IMM date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlIMMcode"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x09""qlIMMdate"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x09""qlIMMdate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""IMMcode,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x63""returns the IMM date corresponding to the given IMM code (e.g. Wednesday, March 15th, 2006 for H6)."),
            // parameter descriptions
            TempStrNoSize("\x1C""2 letter IMM code (e.g. H6)."),
            TempStrNoSize("\x5C""date with respect to which the calculations are performed. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlIMMdate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlPeriodEquivalent"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x12""qlPeriodEquivalent"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0E""Period,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Returns the period equivalent to the input (e.g. 11M for 1Y-1M)."),
            // parameter descriptions
            TempStrNoSize("\x1A""input period (e.g. 1Y-1M)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlPeriodEquivalent"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlPeriodFromFrequency"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x15""qlPeriodFromFrequency"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x11""Frequency,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""returns a Period from a given Frequency (e.g. 6M from SemiAnnual)."),
            // parameter descriptions
            TempStrNoSize("\x50""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlPeriodFromFrequency"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x10""qlPeriodLessThan"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x10""qlPeriodLessThan"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""Period1,Period2,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns TRUE if the first period is less than the second."),
            // parameter descriptions
            TempStrNoSize("\x0F""left hand side."),
            TempStrNoSize("\x10""right hand side."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlPeriodLessThan"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

