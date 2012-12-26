
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

// register functions in category Randomsequencegenerator with Excel

void registerRandomsequencegenerator(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlFaureRsg"),
            // parameter codes
            TempStrNoSize("\x07""CCNPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlFaureRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,Dimension,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class FaureRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlHaltonRsg"),
            // parameter codes
            TempStrNoSize("\x08""CCNNPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlHaltonRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Dimension,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class HaltonRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x05""seed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlMersenneTwisterRsg"),
            // parameter codes
            TempStrNoSize("\x08""CCNNPPL#"),
            // function display name
            TempStrNoSize("\x14""qlMersenneTwisterRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Dimension,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class MersenneTwisterRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x05""seed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x06""qlRand"),
            // parameter codes
            TempStrNoSize("\x03""EP#"),
            // function display name
            TempStrNoSize("\x06""qlRand"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""returns a random number between 0 and 1."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlRandomize"),
            // parameter codes
            TempStrNoSize("\x04""LNP#"),
            // function display name
            TempStrNoSize("\x0B""qlRandomize"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Seed,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""initialize with the given seed the random number generator used by qlRand()."),
            // parameter descriptions
            TempStrNoSize("\x38""the seed used to initialize the random number generator."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlSobolRsg"),
            // parameter codes
            TempStrNoSize("\x08""CCNNPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlSobolRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Dimension,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class SobolRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x05""seed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlVariates"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x0A""qlVariates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,Samples,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x12""generate variates."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLibAddin::RandomSequenceGenerator object"),
            TempStrNoSize("\x12""number of samples."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Randomsequencegenerator with Excel

void unregisterRandomsequencegenerator(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlFaureRsg"),
            // parameter codes
            TempStrNoSize("\x07""CCNPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlFaureRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,Dimension,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class FaureRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlFaureRsg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlHaltonRsg"),
            // parameter codes
            TempStrNoSize("\x08""CCNNPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlHaltonRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Dimension,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class HaltonRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x05""seed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlHaltonRsg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlMersenneTwisterRsg"),
            // parameter codes
            TempStrNoSize("\x08""CCNNPPL#"),
            // function display name
            TempStrNoSize("\x14""qlMersenneTwisterRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Dimension,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class MersenneTwisterRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x05""seed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlMersenneTwisterRsg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 11, &xDll,
            // function code name
            TempStrNoSize("\x06""qlRand"),
            // parameter codes
            TempStrNoSize("\x03""EP#"),
            // function display name
            TempStrNoSize("\x06""qlRand"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x07""Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x28""returns a random number between 0 and 1."),
            // parameter descriptions
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x06""qlRand"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlRandomize"),
            // parameter codes
            TempStrNoSize("\x04""LNP#"),
            // function display name
            TempStrNoSize("\x0B""qlRandomize"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x0C""Seed,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""initialize with the given seed the random number generator used by qlRand()."),
            // parameter descriptions
            TempStrNoSize("\x38""the seed used to initialize the random number generator."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlRandomize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlSobolRsg"),
            // parameter codes
            TempStrNoSize("\x08""CCNNPPL#"),
            // function display name
            TempStrNoSize("\x0A""qlSobolRsg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Dimension,Seed,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Construct an object of class SobolRsg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0A""dimension."),
            TempStrNoSize("\x05""seed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlSobolRsg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlVariates"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x0A""qlVariates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,Samples,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x12""generate variates."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLibAddin::RandomSequenceGenerator object"),
            TempStrNoSize("\x12""number of samples."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlVariates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

