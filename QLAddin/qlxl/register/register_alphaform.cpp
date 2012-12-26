
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

// register functions in category Alphaform with Excel

void registerAlphaform(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAlphaFormInverseLinear"),
            // parameter codes
            TempStrNoSize("\x08""CCPEPPL#"),
            // function display name
            TempStrNoSize("\x18""qlAlphaFormInverseLinear"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,RateTimes,Alpha,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class AlphaFormInverseLinear and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x12""alpha coefficient."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlAlphaFormLinearHyperbolic"),
            // parameter codes
            TempStrNoSize("\x08""CCPEPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlAlphaFormLinearHyperbolic"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,RateTimes,Alpha,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class AlphaFormLinearHyperbolic and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x12""alpha coefficient."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlAlphaFormOperator"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x13""qlAlphaFormOperator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Time,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns the Alpha Form value at time i."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AlphaForm object"),
            TempStrNoSize("\x23""integer corresponding to i-th time."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlAlphaFormSetAlpha"),
            // parameter codes
            TempStrNoSize("\x05""LCEP#"),
            // function display name
            TempStrNoSize("\x13""qlAlphaFormSetAlpha"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Alpha,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2C""set the Alpha parameter value to Alpha Form."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AlphaForm object"),
            TempStrNoSize("\x25""Alpha parameter value for Alpha Form."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Alphaform with Excel

void unregisterAlphaform(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAlphaFormInverseLinear"),
            // parameter codes
            TempStrNoSize("\x08""CCPEPPL#"),
            // function display name
            TempStrNoSize("\x18""qlAlphaFormInverseLinear"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,RateTimes,Alpha,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class AlphaFormInverseLinear and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x12""alpha coefficient."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlAlphaFormInverseLinear"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlAlphaFormLinearHyperbolic"),
            // parameter codes
            TempStrNoSize("\x08""CCPEPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlAlphaFormLinearHyperbolic"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,RateTimes,Alpha,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class AlphaFormLinearHyperbolic and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x12""alpha coefficient."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlAlphaFormLinearHyperbolic"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlAlphaFormOperator"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x13""qlAlphaFormOperator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Time,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""returns the Alpha Form value at time i."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AlphaForm object"),
            TempStrNoSize("\x23""integer corresponding to i-th time."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlAlphaFormOperator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlAlphaFormSetAlpha"),
            // parameter codes
            TempStrNoSize("\x05""LCEP#"),
            // function display name
            TempStrNoSize("\x13""qlAlphaFormSetAlpha"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Alpha,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2C""set the Alpha parameter value to Alpha Form."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AlphaForm object"),
            TempStrNoSize("\x25""Alpha parameter value for Alpha Form."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlAlphaFormSetAlpha"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

