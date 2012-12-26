
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

// register functions in category Daycounter with Excel

void registerDaycounter(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDayCounterDayCount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x14""qlDayCounterDayCount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""daycounter,StartDate,EndDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x53""calculate the number of days in a period according to a given day count convention."),
            // parameter descriptions
            TempStrNoSize("\x2F""ID of Enumeration of class QuantLib::DayCounter"),
            TempStrNoSize("\x0B""start date."),
            TempStrNoSize("\x09""end date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDayCounterName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x10""qlDayCounterName"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""daycounter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x29""returns the name of the given DayCounter."),
            // parameter descriptions
            TempStrNoSize("\x2F""ID of Enumeration of class QuantLib::DayCounter"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlDayCounterYearFraction"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x18""qlDayCounterYearFraction"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""daycounter,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1A""calculate a year fraction."),
            // parameter descriptions
            TempStrNoSize("\x2F""ID of Enumeration of class QuantLib::DayCounter"),
            TempStrNoSize("\x0B""start date."),
            TempStrNoSize("\x09""end date."),
            TempStrNoSize("\x42""start date for reference period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x40""end date for reference period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Daycounter with Excel

void unregisterDaycounter(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDayCounterDayCount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x14""qlDayCounterDayCount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""daycounter,StartDate,EndDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x53""calculate the number of days in a period according to a given day count convention."),
            // parameter descriptions
            TempStrNoSize("\x2F""ID of Enumeration of class QuantLib::DayCounter"),
            TempStrNoSize("\x0B""start date."),
            TempStrNoSize("\x09""end date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlDayCounterDayCount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDayCounterName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x10""qlDayCounterName"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""daycounter,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x29""returns the name of the given DayCounter."),
            // parameter descriptions
            TempStrNoSize("\x2F""ID of Enumeration of class QuantLib::DayCounter"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlDayCounterName"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlDayCounterYearFraction"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x18""qlDayCounterYearFraction"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""daycounter,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1A""calculate a year fraction."),
            // parameter descriptions
            TempStrNoSize("\x2F""ID of Enumeration of class QuantLib::DayCounter"),
            TempStrNoSize("\x0B""start date."),
            TempStrNoSize("\x09""end date."),
            TempStrNoSize("\x42""start date for reference period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x40""end date for reference period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlDayCounterYearFraction"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

