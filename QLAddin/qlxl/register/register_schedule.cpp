
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

// register functions in category Schedule with Excel

void registerSchedule(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlSchedule"),
            // parameter codes
            TempStrNoSize("\x10""CCPPCPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlSchedule"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x95""ObjectId,EffectiveDate,TerminationDate,Tenor,Calendar,Convention,TermDateConv,GenRule,EndOfMonth,FirstDate,NextToLastDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Schedule and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x31""effective date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x11""termination date."),
            TempStrNoSize("\x56""tenor (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x3D""holiday calendar (e.g. TARGET). Default value = NullCalendar."),
            TempStrNoSize("\x42""accrual dates business day convention. Default value = Unadjusted."),
            TempStrNoSize("\x45""termination date business day convention. Default value = Unadjusted."),
            TempStrNoSize("\x72""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero). Default value = Backward."),
            TempStrNoSize("\x2F""end of month convention. Default value = false."),
            TempStrNoSize("\x56""stub date, if there is an irregular starting period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x50""stub date, if there an irregular final period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlScheduleBDC"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0D""qlScheduleBDC"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""returns the business day convention used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlScheduleCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x12""qlScheduleCalendar"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""returns the Calendar used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlScheduleDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlScheduleDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""returns the dates for the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlScheduleEmpty"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x0F""qlScheduleEmpty"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""returns TRUE if the given Schedule object is empty."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlScheduleEndDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x11""qlScheduleEndDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""returns the end date of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlScheduleEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x14""qlScheduleEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5D""returns TRUE if end-of-month convention has been used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlScheduleFromDateVector"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlScheduleFromDateVector"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x32""ObjectId,EffectiveDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Schedule and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2E""date vector. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlScheduleIsRegular"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x13""qlScheduleIsRegular"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""returns TRUE if the selected period in the given Schedule object is regular."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x2A""one based period index. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x12""qlScheduleNextDate"),
            // parameter codes
            TempStrNoSize("\x05""NCPP#"),
            // function display name
            TempStrNoSize("\x12""qlScheduleNextDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""returns the lowest date in the given Schedule object following the input reference date."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x31""reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSchedulePreviousDate"),
            // parameter codes
            TempStrNoSize("\x05""NCPP#"),
            // function display name
            TempStrNoSize("\x16""qlSchedulePreviousDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""returns the highest date in the given Schedule object preceding the input reference date."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x31""reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlScheduleRule"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlScheduleRule"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""returns the DateGeneration::Rule of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlScheduleSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0E""qlScheduleSize"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""returns the number of dates in the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlScheduleStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x13""qlScheduleStartDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""returns the start date of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlScheduleTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0F""qlScheduleTenor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""returns the tenor used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlScheduleTerminationDateBDC"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1C""qlScheduleTerminationDateBDC"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x68""returns the business day convention used to calculate the termination date of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlScheduleTruncated"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlScheduleTruncated"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,OriginalSchedule,TruncationDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Schedule and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""original schedule object ID."),
            TempStrNoSize("\x10""truncation date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Schedule with Excel

void unregisterSchedule(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlSchedule"),
            // parameter codes
            TempStrNoSize("\x10""CCPPCPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlSchedule"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x95""ObjectId,EffectiveDate,TerminationDate,Tenor,Calendar,Convention,TermDateConv,GenRule,EndOfMonth,FirstDate,NextToLastDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Schedule and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x31""effective date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x11""termination date."),
            TempStrNoSize("\x56""tenor (e.g. 2D for two days , 3W for three weeks, 6M for six months, 1Y for one year)."),
            TempStrNoSize("\x3D""holiday calendar (e.g. TARGET). Default value = NullCalendar."),
            TempStrNoSize("\x42""accrual dates business day convention. Default value = Unadjusted."),
            TempStrNoSize("\x45""termination date business day convention. Default value = Unadjusted."),
            TempStrNoSize("\x72""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero). Default value = Backward."),
            TempStrNoSize("\x2F""end of month convention. Default value = false."),
            TempStrNoSize("\x56""stub date, if there is an irregular starting period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x50""stub date, if there an irregular final period. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlSchedule"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlScheduleBDC"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0D""qlScheduleBDC"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""returns the business day convention used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlScheduleBDC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlScheduleCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x12""qlScheduleCalendar"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""returns the Calendar used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlScheduleCalendar"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlScheduleDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlScheduleDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""returns the dates for the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlScheduleDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlScheduleEmpty"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x0F""qlScheduleEmpty"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""returns TRUE if the given Schedule object is empty."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlScheduleEmpty"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlScheduleEndDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x11""qlScheduleEndDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""returns the end date of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlScheduleEndDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlScheduleEndOfMonth"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x14""qlScheduleEndOfMonth"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5D""returns TRUE if end-of-month convention has been used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlScheduleEndOfMonth"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlScheduleFromDateVector"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlScheduleFromDateVector"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x32""ObjectId,EffectiveDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Schedule and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2E""date vector. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlScheduleFromDateVector"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlScheduleIsRegular"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x13""qlScheduleIsRegular"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""returns TRUE if the selected period in the given Schedule object is regular."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x2A""one based period index. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlScheduleIsRegular"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x12""qlScheduleNextDate"),
            // parameter codes
            TempStrNoSize("\x05""NCPP#"),
            // function display name
            TempStrNoSize("\x12""qlScheduleNextDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""returns the lowest date in the given Schedule object following the input reference date."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x31""reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlScheduleNextDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSchedulePreviousDate"),
            // parameter codes
            TempStrNoSize("\x05""NCPP#"),
            // function display name
            TempStrNoSize("\x16""qlSchedulePreviousDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,RefDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""returns the highest date in the given Schedule object preceding the input reference date."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x31""reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSchedulePreviousDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlScheduleRule"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0E""qlScheduleRule"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""returns the DateGeneration::Rule of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlScheduleRule"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlScheduleSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0E""qlScheduleSize"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""returns the number of dates in the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlScheduleSize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlScheduleStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x13""qlScheduleStartDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""returns the start date of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlScheduleStartDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlScheduleTenor"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0F""qlScheduleTenor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""returns the tenor used to calculate the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlScheduleTenor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlScheduleTerminationDateBDC"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1C""qlScheduleTerminationDateBDC"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x68""returns the business day convention used to calculate the termination date of the given Schedule object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLib::Schedule object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlScheduleTerminationDateBDC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlScheduleTruncated"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlScheduleTruncated"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,OriginalSchedule,TruncationDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class Schedule and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""original schedule object ID."),
            TempStrNoSize("\x10""truncation date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlScheduleTruncated"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

