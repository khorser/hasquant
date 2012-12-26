
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

// register functions in category Processes with Excel

void registerProcesses(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x20""qlGeneralizedBlackScholesProcess"),
            // parameter codes
            TempStrNoSize("\x0C""CCCEPPEEPPL#"),
            // function display name
            TempStrNoSize("\x20""qlGeneralizedBlackScholesProcess"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6F""ObjectId,BlackVolID,Underlying,DayCounter,SettlementDate,RiskFreeRate,DividendYield,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class GeneralizedBlackScholesProcess and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""Black Vol Term Structure."),
            TempStrNoSize("\x0B""underlying."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x10""settlement date."),
            TempStrNoSize("\x0F""risk free rate."),
            TempStrNoSize("\x0F""dividend yield."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Processes with Excel

void unregisterProcesses(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x20""qlGeneralizedBlackScholesProcess"),
            // parameter codes
            TempStrNoSize("\x0C""CCCEPPEEPPL#"),
            // function display name
            TempStrNoSize("\x20""qlGeneralizedBlackScholesProcess"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6F""ObjectId,BlackVolID,Underlying,DayCounter,SettlementDate,RiskFreeRate,DividendYield,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class GeneralizedBlackScholesProcess and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""Black Vol Term Structure."),
            TempStrNoSize("\x0B""underlying."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x10""settlement date."),
            TempStrNoSize("\x0F""risk free rate."),
            TempStrNoSize("\x0F""dividend yield."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlGeneralizedBlackScholesProcess"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

