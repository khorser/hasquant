
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

// register functions in category Prices with Excel

void registerPrices(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlMidEquivalent"),
            // parameter codes
            TempStrNoSize("\x07""EPPPPP#"),
            // function display name
            TempStrNoSize("\x0F""qlMidEquivalent"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Bid,Ask,Last,Close,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""returns the mid price if available, or a suitable substitute otherwise."),
            // parameter descriptions
            TempStrNoSize("\x1D""bid price. Default value = 0."),
            TempStrNoSize("\x1D""ask price. Default value = 0."),
            TempStrNoSize("\x1E""last price. Default value = 0."),
            TempStrNoSize("\x1F""close price. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x09""qlMidSafe"),
            // parameter codes
            TempStrNoSize("\x05""EPPP#"),
            // function display name
            TempStrNoSize("\x09""qlMidSafe"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""Bid,Ask,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""returns the mid price only if both bid and ask are available."),
            // parameter descriptions
            TempStrNoSize("\x1D""bid price. Default value = 0."),
            TempStrNoSize("\x1D""ask price. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Prices with Excel

void unregisterPrices(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlMidEquivalent"),
            // parameter codes
            TempStrNoSize("\x07""EPPPPP#"),
            // function display name
            TempStrNoSize("\x0F""qlMidEquivalent"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Bid,Ask,Last,Close,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""returns the mid price if available, or a suitable substitute otherwise."),
            // parameter descriptions
            TempStrNoSize("\x1D""bid price. Default value = 0."),
            TempStrNoSize("\x1D""ask price. Default value = 0."),
            TempStrNoSize("\x1E""last price. Default value = 0."),
            TempStrNoSize("\x1F""close price. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlMidEquivalent"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x09""qlMidSafe"),
            // parameter codes
            TempStrNoSize("\x05""EPPP#"),
            // function display name
            TempStrNoSize("\x09""qlMidSafe"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0F""Bid,Ask,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""returns the mid price only if both bid and ask are available."),
            // parameter descriptions
            TempStrNoSize("\x1D""bid price. Default value = 0."),
            TempStrNoSize("\x1D""ask price. Default value = 0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlMidSafe"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

