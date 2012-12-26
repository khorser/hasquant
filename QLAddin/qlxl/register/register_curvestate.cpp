
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

// register functions in category Curvestate with Excel

void registerCurvestate(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCMSwapCurveState"),
            // parameter codes
            TempStrNoSize("\x08""CCPNPPL#"),
            // function display name
            TempStrNoSize("\x12""qlCMSwapCurveState"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,RateTimes,SpanningForwards,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class CMSwapCurveState and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x22""qlCMSwapCurveStateSetOnCMSwapRates"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x22""qlCMSwapCurveStateSetOnCMSwapRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,CMSwapRates,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""set the CurveState object on given vector of coterminal swaps."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::CMSwapCurveState object"),
            TempStrNoSize("\x16""Coterminal swap rates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x31""qlConstantMaturitySwapAnnuitiesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x07""PNNPPP#"),
            // function display name
            TempStrNoSize("\x31""qlConstantMaturitySwapAnnuitiesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""SpanningForwards,FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns constant maturity swap annuities from discount ratios."),
            // parameter descriptions
            TempStrNoSize("\x3E""number of forward rates spanned by the constant maturity swap."),
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x2D""qlConstantMaturitySwapRatesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x07""PNNPPP#"),
            // function display name
            TempStrNoSize("\x2D""qlConstantMaturitySwapRatesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""SpanningForwards,FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns constant maturity swap rates from discount ratios."),
            // parameter descriptions
            TempStrNoSize("\x3E""number of forward rates spanned by the constant maturity swap."),
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlCoterminalSwapAnnuitiesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x06""PNPPP#"),
            // function display name
            TempStrNoSize("\x2B""qlCoterminalSwapAnnuitiesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the coterminal swap annuities implied from discount bond ratios."),
            // parameter descriptions
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCoterminalSwapCurveState"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlCoterminalSwapCurveState"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class CoterminalSwapCurveState and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x32""qlCoterminalSwapCurveStateSetOnCoterminalSwapRates"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x32""qlCoterminalSwapCurveStateSetOnCoterminalSwapRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x20""ObjectId,CoterminalSwaps,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""set the CurveState object on given vector of coterminal swaps."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLib::CoterminalSwapCurveState object"),
            TempStrNoSize("\x16""Coterminal swap rates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x27""qlCoterminalSwapRatesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x06""PNPPP#"),
            // function display name
            TempStrNoSize("\x27""qlCoterminalSwapRatesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the coterminal swap rates implied from discount bond ratios."),
            // parameter descriptions
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCurveStateCMSwapRates"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlCurveStateCMSwapRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""ObjectId,SpanningForwards,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Returns the current swap rates of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlCurveStateCoterminalSwapRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlCurveStateCoterminalSwapRates"),
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
            TempStrNoSize("\x38""Returns the current swap rates of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCurveStateForwardRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlCurveStateForwardRates"),
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
            TempStrNoSize("\x3B""Returns the current forward rates of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCurveStateRateTaus"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlCurveStateRateTaus"),
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
            TempStrNoSize("\x2E""return the rate taus of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCurveStateRateTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlCurveStateRateTimes"),
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
            TempStrNoSize("\x2F""return the rate times of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlForwardsFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x06""PNPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlForwardsFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the forward rates implied from discount bond ratios."),
            // parameter descriptions
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlLMMCurveState"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlLMMCurveState"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class LMMCurveState and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x22""qlLMMCurveStateSetOnDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x22""qlLMMCurveStateSetOnDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,DiscountRatios,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""set the CurveState object on given vector of discount ratios."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::LMMCurveState object"),
            TempStrNoSize("\x10""discount ratios."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlLMMCurveStateSetOnForwardRates"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x20""qlLMMCurveStateSetOnForwardRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Rates,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""set the CurveState object on given vector of forward rates."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::LMMCurveState object"),
            TempStrNoSize("\x0E""forward rates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Curvestate with Excel

void unregisterCurvestate(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCMSwapCurveState"),
            // parameter codes
            TempStrNoSize("\x08""CCPNPPL#"),
            // function display name
            TempStrNoSize("\x12""qlCMSwapCurveState"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,RateTimes,SpanningForwards,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class CMSwapCurveState and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlCMSwapCurveState"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x22""qlCMSwapCurveStateSetOnCMSwapRates"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x22""qlCMSwapCurveStateSetOnCMSwapRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,CMSwapRates,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""set the CurveState object on given vector of coterminal swaps."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::CMSwapCurveState object"),
            TempStrNoSize("\x16""Coterminal swap rates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlCMSwapCurveStateSetOnCMSwapRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x31""qlConstantMaturitySwapAnnuitiesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x07""PNNPPP#"),
            // function display name
            TempStrNoSize("\x31""qlConstantMaturitySwapAnnuitiesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""SpanningForwards,FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns constant maturity swap annuities from discount ratios."),
            // parameter descriptions
            TempStrNoSize("\x3E""number of forward rates spanned by the constant maturity swap."),
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x31""qlConstantMaturitySwapAnnuitiesFromDiscountRatios"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x2D""qlConstantMaturitySwapRatesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x07""PNNPPP#"),
            // function display name
            TempStrNoSize("\x2D""qlConstantMaturitySwapRatesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""SpanningForwards,FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns constant maturity swap rates from discount ratios."),
            // parameter descriptions
            TempStrNoSize("\x3E""number of forward rates spanned by the constant maturity swap."),
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2D""qlConstantMaturitySwapRatesFromDiscountRatios"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlCoterminalSwapAnnuitiesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x06""PNPPP#"),
            // function display name
            TempStrNoSize("\x2B""qlCoterminalSwapAnnuitiesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the coterminal swap annuities implied from discount bond ratios."),
            // parameter descriptions
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlCoterminalSwapAnnuitiesFromDiscountRatios"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCoterminalSwapCurveState"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlCoterminalSwapCurveState"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class CoterminalSwapCurveState and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlCoterminalSwapCurveState"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x32""qlCoterminalSwapCurveStateSetOnCoterminalSwapRates"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x32""qlCoterminalSwapCurveStateSetOnCoterminalSwapRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x20""ObjectId,CoterminalSwaps,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""set the CurveState object on given vector of coterminal swaps."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLib::CoterminalSwapCurveState object"),
            TempStrNoSize("\x16""Coterminal swap rates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x32""qlCoterminalSwapCurveStateSetOnCoterminalSwapRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x27""qlCoterminalSwapRatesFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x06""PNPPP#"),
            // function display name
            TempStrNoSize("\x27""qlCoterminalSwapRatesFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the coterminal swap rates implied from discount bond ratios."),
            // parameter descriptions
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlCoterminalSwapRatesFromDiscountRatios"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCurveStateCMSwapRates"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x17""qlCurveStateCMSwapRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""ObjectId,SpanningForwards,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Returns the current swap rates of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x26""number of forwards underlying the CMS."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCurveStateCMSwapRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlCurveStateCoterminalSwapRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlCurveStateCoterminalSwapRates"),
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
            TempStrNoSize("\x38""Returns the current swap rates of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlCurveStateCoterminalSwapRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCurveStateForwardRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlCurveStateForwardRates"),
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
            TempStrNoSize("\x3B""Returns the current forward rates of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlCurveStateForwardRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCurveStateRateTaus"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlCurveStateRateTaus"),
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
            TempStrNoSize("\x2E""return the rate taus of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlCurveStateRateTaus"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCurveStateRateTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlCurveStateRateTimes"),
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
            TempStrNoSize("\x2F""return the rate times of the CurveState object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::CurveState object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlCurveStateRateTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlForwardsFromDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x06""PNPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlForwardsFromDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""FirstValidIndex,DiscountRatios,Taus,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the forward rates implied from discount bond ratios."),
            // parameter descriptions
            TempStrNoSize("\x2A""marks the first non expired discount bond."),
            TempStrNoSize("\x1F""vector of discount bond ratios."),
            TempStrNoSize("\x14""rate time intervals."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlForwardsFromDiscountRatios"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlLMMCurveState"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlLMMCurveState"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class LMMCurveState and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlLMMCurveState"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x22""qlLMMCurveStateSetOnDiscountRatios"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x22""qlLMMCurveStateSetOnDiscountRatios"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,DiscountRatios,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""set the CurveState object on given vector of discount ratios."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::LMMCurveState object"),
            TempStrNoSize("\x10""discount ratios."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlLMMCurveStateSetOnDiscountRatios"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlLMMCurveStateSetOnForwardRates"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x20""qlLMMCurveStateSetOnForwardRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Rates,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""set the CurveState object on given vector of forward rates."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::LMMCurveState object"),
            TempStrNoSize("\x0E""forward rates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlLMMCurveStateSetOnForwardRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

