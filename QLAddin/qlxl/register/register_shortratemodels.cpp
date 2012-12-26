
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

// register functions in category Shortratemodels with Excel

void registerShortratemodels(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlFuturesConvexityBias"),
            // parameter codes
            TempStrNoSize("\x08""EEEEEPP#"),
            // function display name
            TempStrNoSize("\x16""qlFuturesConvexityBias"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x22""FuturesPrice,T1,T2,Sigma,A,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xAB""Returns Futures convexity bias (ForwardRate = FuturesImpliedRate - ConvexityBias) calculated as in G. Kirikos, D. Novak, 'Convexity Conundrums', Risk Magazine, March 1997."),
            // parameter descriptions
            TempStrNoSize("\x1B""Futures price (e.g. 94.56)."),
            TempStrNoSize("\x39""Maturity date of the futures contract in years(e.g. 5.0)."),
            TempStrNoSize("\x3E""Maturity of the underlying Libor deposit in years (e.g. 5.25)."),
            TempStrNoSize("\x23""Hull-White volatility (e.g. 0.015)."),
            TempStrNoSize("\x30""Hull-White mean reversion. Default value = 0.03."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlHullWhite"),
            // parameter codes
            TempStrNoSize("\x09""CCCEEPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlHullWhite"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x37""ObjectId,YieldCurve,A,Sigma,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class HullWhite and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""YieldTermStructure object ID."),
            TempStrNoSize("\x02""a."),
            TempStrNoSize("\x0B""volatility."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x09""qlVasicek"),
            // parameter codes
            TempStrNoSize("\x0A""CCEEEEPPL#"),
            // function display name
            TempStrNoSize("\x09""qlVasicek"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,A,B,Lambda,Sigma,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class Vasicek and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""mean reverting speed."),
            TempStrNoSize("\x17""short-rate limit value."),
            TempStrNoSize("\x0D""risk premium."),
            TempStrNoSize("\x0B""volatility."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Shortratemodels with Excel

void unregisterShortratemodels(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlFuturesConvexityBias"),
            // parameter codes
            TempStrNoSize("\x08""EEEEEPP#"),
            // function display name
            TempStrNoSize("\x16""qlFuturesConvexityBias"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x22""FuturesPrice,T1,T2,Sigma,A,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xAB""Returns Futures convexity bias (ForwardRate = FuturesImpliedRate - ConvexityBias) calculated as in G. Kirikos, D. Novak, 'Convexity Conundrums', Risk Magazine, March 1997."),
            // parameter descriptions
            TempStrNoSize("\x1B""Futures price (e.g. 94.56)."),
            TempStrNoSize("\x39""Maturity date of the futures contract in years(e.g. 5.0)."),
            TempStrNoSize("\x3E""Maturity of the underlying Libor deposit in years (e.g. 5.25)."),
            TempStrNoSize("\x23""Hull-White volatility (e.g. 0.015)."),
            TempStrNoSize("\x30""Hull-White mean reversion. Default value = 0.03."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlFuturesConvexityBias"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlHullWhite"),
            // parameter codes
            TempStrNoSize("\x09""CCCEEPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlHullWhite"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x37""ObjectId,YieldCurve,A,Sigma,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class HullWhite and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""YieldTermStructure object ID."),
            TempStrNoSize("\x02""a."),
            TempStrNoSize("\x0B""volatility."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlHullWhite"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x09""qlVasicek"),
            // parameter codes
            TempStrNoSize("\x0A""CCEEEEPPL#"),
            // function display name
            TempStrNoSize("\x09""qlVasicek"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,A,B,Lambda,Sigma,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class Vasicek and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""mean reverting speed."),
            TempStrNoSize("\x17""short-rate limit value."),
            TempStrNoSize("\x0D""risk premium."),
            TempStrNoSize("\x0B""volatility."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlVasicek"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

