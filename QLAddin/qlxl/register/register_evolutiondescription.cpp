
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

// register functions in category Evolutiondescription with Excel

void registerEvolutiondescription(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlEvolutionDescription"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlEvolutionDescription"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,RateTimes,EvolutionTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class EvolutionDescription and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x22""evolution times in the simulation."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlEvolutionDescriptionEvolutionTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlEvolutionDescriptionEvolutionTimes"),
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
            TempStrNoSize("\x34""evolution times for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlEvolutionDescriptionFirstAliveRate"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlEvolutionDescriptionFirstAliveRate"),
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
            TempStrNoSize("\x4C""first alive rate at each evolution time for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x21""qlEvolutionDescriptionFromProduct"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x21""qlEvolutionDescriptionFromProduct"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,Product,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class EvolutionDescription and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""ID of product object."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfRates"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfRates"),
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
            TempStrNoSize("\x34""number of rates for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfSteps"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfSteps"),
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
            TempStrNoSize("\x34""number of steps for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlEvolutionDescriptionRateTaus"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlEvolutionDescriptionRateTaus"),
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
            TempStrNoSize("\x2E""rate taus for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlEvolutionDescriptionRateTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlEvolutionDescriptionRateTimes"),
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
            TempStrNoSize("\x37""rates fixing times for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlIsInMoneyMarketMeasure"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x18""qlIsInMoneyMarketMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""EvolutionDescription,Numeraires,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x67""Returns TRUE if the numeraire vector is money market measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x15""vector of numeraires."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlIsInMoneyMarketPlusMeasure"),
            // parameter codes
            TempStrNoSize("\x06""LCPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlIsInMoneyMarketPlusMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""EvolutionDescription,Numeraires,Offset,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6C""Returns TRUE if the numeraire vector is money market measure plus for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x15""vector of numeraires."),
            TempStrNoSize("\x3D""offset applied to the MoneyMarket measure. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlIsInTerminalMeasure"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x15""qlIsInTerminalMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""EvolutionDescription,Numeraires,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x63""Returns TRUE if the numeraire vector is Terminal measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x15""vector of numeraires."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlMoneyMarketMeasure"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlMoneyMarketMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""EvolutionDescription,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x61""Returns the discretely compounded money market measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlMoneyMarketPlusMeasure"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlMoneyMarketPlusMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x23""EvolutionDescription,Offset,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x61""Returns the discretely compounded money market measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x3D""offset applied to the MoneyMarket measure. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTerminalMeasure"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlTerminalMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""EvolutionDescription,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the terminal measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Evolutiondescription with Excel

void unregisterEvolutiondescription(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlEvolutionDescription"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlEvolutionDescription"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,RateTimes,EvolutionTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class EvolutionDescription and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x22""evolution times in the simulation."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlEvolutionDescription"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlEvolutionDescriptionEvolutionTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlEvolutionDescriptionEvolutionTimes"),
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
            TempStrNoSize("\x34""evolution times for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlEvolutionDescriptionEvolutionTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlEvolutionDescriptionFirstAliveRate"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlEvolutionDescriptionFirstAliveRate"),
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
            TempStrNoSize("\x4C""first alive rate at each evolution time for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlEvolutionDescriptionFirstAliveRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x21""qlEvolutionDescriptionFromProduct"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x21""qlEvolutionDescriptionFromProduct"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,Product,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class EvolutionDescription and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""ID of product object."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlEvolutionDescriptionFromProduct"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfRates"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfRates"),
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
            TempStrNoSize("\x34""number of rates for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfSteps"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfSteps"),
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
            TempStrNoSize("\x34""number of steps for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlEvolutionDescriptionNumberOfSteps"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlEvolutionDescriptionRateTaus"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlEvolutionDescriptionRateTaus"),
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
            TempStrNoSize("\x2E""rate taus for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlEvolutionDescriptionRateTaus"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlEvolutionDescriptionRateTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlEvolutionDescriptionRateTimes"),
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
            TempStrNoSize("\x37""rates fixing times for the EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x34""id of existing QuantLib::EvolutionDescription object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlEvolutionDescriptionRateTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlIsInMoneyMarketMeasure"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x18""qlIsInMoneyMarketMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""EvolutionDescription,Numeraires,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x67""Returns TRUE if the numeraire vector is money market measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x15""vector of numeraires."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlIsInMoneyMarketMeasure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlIsInMoneyMarketPlusMeasure"),
            // parameter codes
            TempStrNoSize("\x06""LCPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlIsInMoneyMarketPlusMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""EvolutionDescription,Numeraires,Offset,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6C""Returns TRUE if the numeraire vector is money market measure plus for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x15""vector of numeraires."),
            TempStrNoSize("\x3D""offset applied to the MoneyMarket measure. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlIsInMoneyMarketPlusMeasure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlIsInTerminalMeasure"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x15""qlIsInTerminalMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""EvolutionDescription,Numeraires,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x63""Returns TRUE if the numeraire vector is Terminal measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x15""vector of numeraires."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlIsInTerminalMeasure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlMoneyMarketMeasure"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlMoneyMarketMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""EvolutionDescription,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x61""Returns the discretely compounded money market measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlMoneyMarketMeasure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlMoneyMarketPlusMeasure"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlMoneyMarketPlusMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x23""EvolutionDescription,Offset,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x61""Returns the discretely compounded money market measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x3D""offset applied to the MoneyMarket measure. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlMoneyMarketPlusMeasure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlTerminalMeasure"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlTerminalMeasure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""EvolutionDescription,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the terminal measure for the given EvolutionDescription object."),
            // parameter descriptions
            TempStrNoSize("\x22""ID of EvolutionDescription object."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlTerminalMeasure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

