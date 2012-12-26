
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

// register functions in category Browniangenerators with Excel

void registerBrowniangenerators(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMTBrownianGeneratorFactory"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlMTBrownianGeneratorFactory"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class MTBrownianGeneratorFactory and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x36""seed for random sequence generator. Default value = 0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Browniangenerators with Excel

void unregisterBrowniangenerators(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMTBrownianGeneratorFactory"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlMTBrownianGeneratorFactory"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class MTBrownianGeneratorFactory and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x36""seed for random sequence generator. Default value = 0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlMTBrownianGeneratorFactory"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

