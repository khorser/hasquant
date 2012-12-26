
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

// register functions in category Defaulttermstructures with Excel

void registerDefaulttermstructures(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlDefaultTSDefaultProbability"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1D""qlDefaultTSDefaultProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,Dates,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x87""Returns the probability of default between the reference date and the given date from the given DefaultProbabilityTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::DefaultProbabilityTermStructure object"),
            TempStrNoSize("\x10""vector of dates."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x10""qlFlatHazardRate"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlFlatHazardRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x43""ObjectId,NDays,Calendar,Rate,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class FlatHazardRate and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x8D""number of days to advance from EvaluationDate (usually zero or two): it fixes the date at which the discount factor = 1.0. Default value = 0."),
            TempStrNoSize("\x63""holiday calendar (e.g. TARGET) to advance from global EvaluationDate. Default value = NullCalendar."),
            TempStrNoSize("\x10""the curve level."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x31""qlRelinkableHandleDefaultProbabilityTermStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x31""qlRelinkableHandleDefaultProbabilityTermStructure"),
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
            TempStrNoSize("\x9E""Construct an object of class RelinkableHandleImpl<QuantLibAddin::DefaultProbabilityTermStructure, QuantLib::DefaultProbabilityTermStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x73""DefaultProbabilityTermStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Defaulttermstructures with Excel

void unregisterDefaulttermstructures(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlDefaultTSDefaultProbability"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1D""qlDefaultTSDefaultProbability"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,Dates,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x87""Returns the probability of default between the reference date and the given date from the given DefaultProbabilityTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::DefaultProbabilityTermStructure object"),
            TempStrNoSize("\x10""vector of dates."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlDefaultTSDefaultProbability"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x10""qlFlatHazardRate"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlFlatHazardRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x43""ObjectId,NDays,Calendar,Rate,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class FlatHazardRate and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x8D""number of days to advance from EvaluationDate (usually zero or two): it fixes the date at which the discount factor = 1.0. Default value = 0."),
            TempStrNoSize("\x63""holiday calendar (e.g. TARGET) to advance from global EvaluationDate. Default value = NullCalendar."),
            TempStrNoSize("\x10""the curve level."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlFlatHazardRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x31""qlRelinkableHandleDefaultProbabilityTermStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x31""qlRelinkableHandleDefaultProbabilityTermStructure"),
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
            TempStrNoSize("\x9E""Construct an object of class RelinkableHandleImpl<QuantLibAddin::DefaultProbabilityTermStructure, QuantLib::DefaultProbabilityTermStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x73""DefaultProbabilityTermStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x31""qlRelinkableHandleDefaultProbabilityTermStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

