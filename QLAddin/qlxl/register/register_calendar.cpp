
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

// register functions in category Calendar with Excel

void registerCalendar(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCalendarAddHoliday"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x14""qlCalendarAddHoliday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""adds an holiday to the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlCalendarAdjust"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x10""qlCalendarAdjust"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""calendar,Date,BusinessDayConvention,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x83""Adjusts a non-business day to the appropriate near business day according to a given calendar with respect to the given convention."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x14""date to be adjusted."),
            TempStrNoSize("\x2E""rolling convention. Default value = Following."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCalendarAdvance"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlCalendarAdvance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x42""calendar,StartDate,Period,BusinessDayConvention,EndOfMonth,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""advances a date according to a given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x1A""start date to be advanced."),
            TempStrNoSize("\x65""period(s) to advance (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x2E""rolling convention. Default value = Following."),
            TempStrNoSize("\x3F""flag to enforce end of month convention. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCalendarBusinessDaysBetween"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x1D""qlCalendarBusinessDaysBetween"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""calendar,FirstDate,LastDate,IncludeFirst,IncludeLast,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Returns the number of business days between two dates."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x19""first date of the period."),
            TempStrNoSize("\x18""last date of the period."),
            TempStrNoSize("\x4A""include the first date when counting business days. Default value = false."),
            TempStrNoSize("\x49""include the last date when counting business days. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCalendarEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x14""qlCalendarEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x61""returns the last business day in the given calendar of the month to which the given date belongs."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCalendarHolidayList"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlCalendarHolidayList"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""Calendar,FromDate,ToDate,IncludeWeekEnds,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""returns the holidays in a period between two dates according to a given holiday calendar."),
            // parameter descriptions
            TempStrNoSize("\x2A""Calendar to use for holiday determination."),
            TempStrNoSize("\x19""first date of the period."),
            TempStrNoSize("\x18""last date of the period."),
            TempStrNoSize("\x34""include week-end as holidays. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCalendarIsBusinessDay"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x17""qlCalendarIsBusinessDay"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns TRUE if the date is a business day for the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCalendarIsEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x16""qlCalendarIsEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""returns TRUE if the date is last business day for the month in the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCalendarIsHoliday"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x13""qlCalendarIsHoliday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""returns TRUE if the date is a holiday for the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlCalendarName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlCalendarName"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""calendar,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""Returns the name of the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCalendarRemoveHoliday"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x17""qlCalendarRemoveHoliday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2B""removes an holiday from the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Calendar with Excel

void unregisterCalendar(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCalendarAddHoliday"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x14""qlCalendarAddHoliday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""adds an holiday to the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlCalendarAddHoliday"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlCalendarAdjust"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x10""qlCalendarAdjust"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""calendar,Date,BusinessDayConvention,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x83""Adjusts a non-business day to the appropriate near business day according to a given calendar with respect to the given convention."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x14""date to be adjusted."),
            TempStrNoSize("\x2E""rolling convention. Default value = Following."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlCalendarAdjust"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCalendarAdvance"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlCalendarAdvance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x42""calendar,StartDate,Period,BusinessDayConvention,EndOfMonth,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""advances a date according to a given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x1A""start date to be advanced."),
            TempStrNoSize("\x65""period(s) to advance (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x2E""rolling convention. Default value = Following."),
            TempStrNoSize("\x3F""flag to enforce end of month convention. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlCalendarAdvance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCalendarBusinessDaysBetween"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x1D""qlCalendarBusinessDaysBetween"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""calendar,FirstDate,LastDate,IncludeFirst,IncludeLast,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Returns the number of business days between two dates."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x19""first date of the period."),
            TempStrNoSize("\x18""last date of the period."),
            TempStrNoSize("\x4A""include the first date when counting business days. Default value = false."),
            TempStrNoSize("\x49""include the last date when counting business days. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlCalendarBusinessDaysBetween"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCalendarEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x14""qlCalendarEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x61""returns the last business day in the given calendar of the month to which the given date belongs."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlCalendarEndOfMonth"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCalendarHolidayList"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlCalendarHolidayList"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""Calendar,FromDate,ToDate,IncludeWeekEnds,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""returns the holidays in a period between two dates according to a given holiday calendar."),
            // parameter descriptions
            TempStrNoSize("\x2A""Calendar to use for holiday determination."),
            TempStrNoSize("\x19""first date of the period."),
            TempStrNoSize("\x18""last date of the period."),
            TempStrNoSize("\x34""include week-end as holidays. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlCalendarHolidayList"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCalendarIsBusinessDay"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x17""qlCalendarIsBusinessDay"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns TRUE if the date is a business day for the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCalendarIsBusinessDay"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCalendarIsEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x16""qlCalendarIsEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""returns TRUE if the date is last business day for the month in the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlCalendarIsEndOfMonth"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCalendarIsHoliday"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x13""qlCalendarIsHoliday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""returns TRUE if the date is a holiday for the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlCalendarIsHoliday"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlCalendarName"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlCalendarName"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""calendar,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""Returns the name of the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlCalendarName"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCalendarRemoveHoliday"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x17""qlCalendarRemoveHoliday"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""calendar,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2B""removes an holiday from the given calendar."),
            // parameter descriptions
            TempStrNoSize("\x2D""ID of Enumeration of class QuantLib::Calendar"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCalendarRemoveHoliday"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

