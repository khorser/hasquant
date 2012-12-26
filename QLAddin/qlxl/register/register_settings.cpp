
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

// register functions in category Settings with Excel

void registerSettings(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x26""qlSettingsEnforceTodaysHistoricFixings"),
            // parameter codes
            TempStrNoSize("\x03""LP#"),
            // function display name
            TempStrNoSize("\x26""qlSettingsEnforceTodaysHistoricFixings"),
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
            TempStrNoSize("\x66""returns the current value of the boolean which enforce the usage of historic fixings for today's date."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSettingsEvaluationDate"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x18""qlSettingsEvaluationDate"),
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
            TempStrNoSize("\x31""returns the current value of the Evaluation Date."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlSettingsSetEnforceTodaysHistoricFixings"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x29""qlSettingsSetEnforceTodaysHistoricFixings"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""Boolean,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5B""sets the value of the boolean which enforce the usage of historic fixings for today's date."),
            // parameter descriptions
            TempStrNoSize("\x6D""new value for the boolean which enforce the usage of historic fixings for today's date. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSettingsSetEvaluationDate"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x1B""qlSettingsSetEvaluationDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""EvalDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""sets the value of the Evaluation Date."),
            // parameter descriptions
            TempStrNoSize("\xA8""new value for the evaluation date. If a null date is provided the current date wiil be used and midnight date change will be detected. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Settings with Excel

void unregisterSettings(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x26""qlSettingsEnforceTodaysHistoricFixings"),
            // parameter codes
            TempStrNoSize("\x03""LP#"),
            // function display name
            TempStrNoSize("\x26""qlSettingsEnforceTodaysHistoricFixings"),
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
            TempStrNoSize("\x66""returns the current value of the boolean which enforce the usage of historic fixings for today's date."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlSettingsEnforceTodaysHistoricFixings"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSettingsEvaluationDate"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x18""qlSettingsEvaluationDate"),
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
            TempStrNoSize("\x31""returns the current value of the Evaluation Date."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSettingsEvaluationDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlSettingsSetEnforceTodaysHistoricFixings"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x29""qlSettingsSetEnforceTodaysHistoricFixings"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""Boolean,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5B""sets the value of the boolean which enforce the usage of historic fixings for today's date."),
            // parameter descriptions
            TempStrNoSize("\x6D""new value for the boolean which enforce the usage of historic fixings for today's date. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlSettingsSetEnforceTodaysHistoricFixings"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSettingsSetEvaluationDate"),
            // parameter codes
            TempStrNoSize("\x04""LPP#"),
            // function display name
            TempStrNoSize("\x1B""qlSettingsSetEvaluationDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""EvalDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Date"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""sets the value of the Evaluation Date."),
            // parameter descriptions
            TempStrNoSize("\xA8""new value for the evaluation date. If a null date is provided the current date wiil be used and midnight date change will be detected. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSettingsSetEvaluationDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

