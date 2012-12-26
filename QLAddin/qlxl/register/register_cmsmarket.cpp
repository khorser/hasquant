
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

// register functions in category Cmsmarket with Excel

void registerCmsmarket(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlBrowseCmsMarket"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlBrowseCmsMarket"),
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
            TempStrNoSize("\x2D""return the market and implied spreads matrix."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLibAddin::CmsMarket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlCmsMarket"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPCPPCPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlCmsMarket"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x70""ObjectId,SwapLengths,SwapIndexes,IborIndex,BidAskSpreads,CmsCouponPricers,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class CmsMarket and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""vector of swap lengths."),
            TempStrNoSize("\x1F""vector of SwapIndex object IDs."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x34""matrix of bid/ask cms quotes (spread over ibor leg)."),
            TempStrNoSize("\x21""vector of HaganPricer object IDs."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Cmsmarket with Excel

void unregisterCmsmarket(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlBrowseCmsMarket"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlBrowseCmsMarket"),
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
            TempStrNoSize("\x2D""return the market and implied spreads matrix."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLibAddin::CmsMarket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlBrowseCmsMarket"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlCmsMarket"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPCPPCPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlCmsMarket"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x70""ObjectId,SwapLengths,SwapIndexes,IborIndex,BidAskSpreads,CmsCouponPricers,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class CmsMarket and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""vector of swap lengths."),
            TempStrNoSize("\x1F""vector of SwapIndex object IDs."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x34""matrix of bid/ask cms quotes (spread over ibor leg)."),
            TempStrNoSize("\x21""vector of HaganPricer object IDs."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlCmsMarket"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

