
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

// register functions in category Timeseries with Excel

void registerTimeseries(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlTimeSeries"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlTimeSeries"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,Dates,Values,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class TimeSeriesDef and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""dates."),
            TempStrNoSize("\x07""values."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTimeSeriesDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlTimeSeriesDates"),
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
            TempStrNoSize("\x32""Returns the dates for which historical data exist."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTimeSeriesEmpty"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x11""qlTimeSeriesEmpty"),
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
            TempStrNoSize("\x2D""Returns whether the series contains any data."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlTimeSeriesFirstDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x15""qlTimeSeriesFirstDate"),
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
            TempStrNoSize("\x3B""Returns the first date for which a historical datum exists."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlTimeSeriesFromIndex"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlTimeSeriesFromIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2A""ObjectId,Index,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class TimeSeriesDef and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""Index object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlTimeSeriesLastDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x14""qlTimeSeriesLastDate"),
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
            TempStrNoSize("\x3A""Returns the last date for which a historical datum exists."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlTimeSeriesSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x10""qlTimeSeriesSize"),
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
            TempStrNoSize("\x3B""Returns the first date for which a historical datum exists."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTimeSeriesValue"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x11""qlTimeSeriesValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Dates,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns returns the data corresponding to the given dates."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::TimeSeriesDef object"),
            TempStrNoSize("\x0F""fixing date(s)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlTimeSeriesValues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlTimeSeriesValues"),
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
            TempStrNoSize("\x1C""Returns the historical data."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Timeseries with Excel

void unregisterTimeseries(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlTimeSeries"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlTimeSeries"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,Dates,Values,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class TimeSeriesDef and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""dates."),
            TempStrNoSize("\x07""values."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlTimeSeries"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTimeSeriesDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlTimeSeriesDates"),
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
            TempStrNoSize("\x32""Returns the dates for which historical data exist."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlTimeSeriesDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTimeSeriesEmpty"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x11""qlTimeSeriesEmpty"),
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
            TempStrNoSize("\x2D""Returns whether the series contains any data."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlTimeSeriesEmpty"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlTimeSeriesFirstDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x15""qlTimeSeriesFirstDate"),
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
            TempStrNoSize("\x3B""Returns the first date for which a historical datum exists."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlTimeSeriesFirstDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlTimeSeriesFromIndex"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x15""qlTimeSeriesFromIndex"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2A""ObjectId,Index,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class TimeSeriesDef and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""Index object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlTimeSeriesFromIndex"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlTimeSeriesLastDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x14""qlTimeSeriesLastDate"),
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
            TempStrNoSize("\x3A""Returns the last date for which a historical datum exists."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlTimeSeriesLastDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlTimeSeriesSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x10""qlTimeSeriesSize"),
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
            TempStrNoSize("\x3B""Returns the first date for which a historical datum exists."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlTimeSeriesSize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTimeSeriesValue"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x11""qlTimeSeriesValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Dates,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns returns the data corresponding to the given dates."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::TimeSeriesDef object"),
            TempStrNoSize("\x0F""fixing date(s)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlTimeSeriesValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlTimeSeriesValues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlTimeSeriesValues"),
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
            TempStrNoSize("\x1C""Returns the historical data."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TimeSeriesDef object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlTimeSeriesValues"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

