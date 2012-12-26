
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

// register functions in category Instruments with Excel

void registerInstruments(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInstrumentErrorEstimate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlInstrumentErrorEstimate"),
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
            TempStrNoSize("\x63""Returns the NPV error estimation (for e.g. Monte Carlo simulation) for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInstrumentIsExpired"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x15""qlInstrumentIsExpired"),
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
            TempStrNoSize("\x37""Returns TRUE if the given Instrument object is expired."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlInstrumentNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlInstrumentNPV"),
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
            TempStrNoSize("\x30""Returns the NPV for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlInstrumentResults"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x13""qlInstrumentResults"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,ResultType,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the required result (if available) for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1A""result type (e.g. 'vega')."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInstrumentSetPricingEngine"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x1C""qlInstrumentSetPricingEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1E""ObjectId,PricingEngine,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Sets a new pricing engine to the given Instrument pbject."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLibAddin::Instrument object"),
            TempStrNoSize("\x18""PricingEngine object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInstrumentValuationDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x19""qlInstrumentValuationDate"),
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
            TempStrNoSize("\x30""Returns the NPV for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Instruments with Excel

void unregisterInstruments(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInstrumentErrorEstimate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlInstrumentErrorEstimate"),
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
            TempStrNoSize("\x63""Returns the NPV error estimation (for e.g. Monte Carlo simulation) for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlInstrumentErrorEstimate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInstrumentIsExpired"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x15""qlInstrumentIsExpired"),
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
            TempStrNoSize("\x37""Returns TRUE if the given Instrument object is expired."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlInstrumentIsExpired"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlInstrumentNPV"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlInstrumentNPV"),
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
            TempStrNoSize("\x30""Returns the NPV for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlInstrumentNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlInstrumentResults"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x13""qlInstrumentResults"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,ResultType,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the required result (if available) for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1A""result type (e.g. 'vega')."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlInstrumentResults"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInstrumentSetPricingEngine"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x1C""qlInstrumentSetPricingEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1E""ObjectId,PricingEngine,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Sets a new pricing engine to the given Instrument pbject."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLibAddin::Instrument object"),
            TempStrNoSize("\x18""PricingEngine object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInstrumentSetPricingEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInstrumentValuationDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x19""qlInstrumentValuationDate"),
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
            TempStrNoSize("\x30""Returns the NPV for the given Instrument object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Instrument object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlInstrumentValuationDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

