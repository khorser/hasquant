
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

// register functions in category Utilities with Excel

void registerUtilities(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlAddinVersion"),
            // parameter codes
            TempStrNoSize("\x03""CP#"),
            // function display name
            TempStrNoSize("\x0E""qlAddinVersion"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""returns the version number of QuantLibAddin (a.k.a QuantLibObject)."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlFunctionCount"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x0F""qlFunctionCount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""returns the number of functions in this Addin."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x09""qlVersion"),
            // parameter codes
            TempStrNoSize("\x03""CP#"),
            // function display name
            TempStrNoSize("\x09""qlVersion"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns the version number of QuantLib."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlxlVersion"),
            // parameter codes
            TempStrNoSize("\x04""CPP#"),
            // function display name
            TempStrNoSize("\x0B""qlxlVersion"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""Verbose,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x29""returns the version number of QuantLibXL."),
            // parameter descriptions
            TempStrNoSize("\x3E""TRUE to get the verbose version string. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Utilities with Excel

void unregisterUtilities(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlAddinVersion"),
            // parameter codes
            TempStrNoSize("\x03""CP#"),
            // function display name
            TempStrNoSize("\x0E""qlAddinVersion"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""returns the version number of QuantLibAddin (a.k.a QuantLibObject)."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlAddinVersion"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlFunctionCount"),
            // parameter codes
            TempStrNoSize("\x03""NP#"),
            // function display name
            TempStrNoSize("\x0F""qlFunctionCount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""returns the number of functions in this Addin."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlFunctionCount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x09""qlVersion"),
            // parameter codes
            TempStrNoSize("\x03""CP#"),
            // function display name
            TempStrNoSize("\x09""qlVersion"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns the version number of QuantLib."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlVersion"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlxlVersion"),
            // parameter codes
            TempStrNoSize("\x04""CPP#"),
            // function display name
            TempStrNoSize("\x0B""qlxlVersion"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""Verbose,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x29""returns the version number of QuantLibXL."),
            // parameter descriptions
            TempStrNoSize("\x3E""TRUE to get the verbose version string. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlxlVersion"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

