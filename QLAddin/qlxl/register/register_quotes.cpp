
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

// register functions in category Quotes with Excel

void registerQuotes(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x10""qlBucketAnalysis"),
            // parameter codes
            TempStrNoSize("\x08""PPPPPPP#"),
            // function display name
            TempStrNoSize("\x10""qlBucketAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""SimpleQuote,Instruments,Quantities,Shift,SensitivityAnalysis,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4F""delta NPV bucket sensitivity analysis for a (single/vector/matrix) SimpleQuote."),
            // parameter descriptions
            TempStrNoSize("\x0E""simple quotes."),
            TempStrNoSize("\x0C""instruments."),
            TempStrNoSize("\x0B""quantities."),
            TempStrNoSize("\x1E""shift. Default value = 0.0001."),
            TempStrNoSize("\x33""SensitivityAnalysis type. Default value = Centered."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBucketAnalysisDelta"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlBucketAnalysisDelta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""SimpleQuote,Parameters,Shift,SensitivityAnalysis,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Parameters' bucket analysis delta for a single SimpleQuote."),
            // parameter descriptions
            TempStrNoSize("\x0D""simple quote."),
            TempStrNoSize("\x12""parameters vector."),
            TempStrNoSize("\x1E""shift. Default value = 0.0001."),
            TempStrNoSize("\x33""SensitivityAnalysis type. Default value = Centered."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBucketAnalysisDelta2"),
            // parameter codes
            TempStrNoSize("\x07""PPPPPP#"),
            // function display name
            TempStrNoSize("\x16""qlBucketAnalysisDelta2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""SimpleQuote,Parameters,Shift,SensitivityAnalysis,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Parameters' bucket analysis delta for a SimpleQuote vector."),
            // parameter descriptions
            TempStrNoSize("\x0D""simple quote."),
            TempStrNoSize("\x12""parameters vector."),
            TempStrNoSize("\x1E""shift. Default value = 0.0001."),
            TempStrNoSize("\x33""SensitivityAnalysis type. Default value = Centered."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x10""qlCompositeQuote"),
            // parameter codes
            TempStrNoSize("\x09""CCPPCPPL#"),
            // function display name
            TempStrNoSize("\x10""qlCompositeQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,Element1,Element2,Operator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class CompositeQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x32""the first, i.e. x, value in the f(x,y) expression."),
            TempStrNoSize("\x33""the second, i.e. y, value in the f(x,y) expression."),
            TempStrNoSize("\x30""the operator to be applied, e.g. ""+"" or ""-""."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x25""qlEurodollarFuturesImpliedStdDevQuote"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPEPPPPL#"),
            // function display name
            TempStrNoSize("\x25""qlEurodollarFuturesImpliedStdDevQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5D""ObjectId,AtmForwardValue,CallPrice,PutPrice,Strike,Guess,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""Construct an object of class EurodollarFuturesImpliedStdDevQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x12""call option price."),
            TempStrNoSize("\x11""put option price."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x4B""implied volatility guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x32""standard deviation accuracy. Default value = 1e-6."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x12""qlForwardSwapQuote"),
            // parameter codes
            TempStrNoSize("\x09""CCCPCPPL#"),
            // function display name
            TempStrNoSize("\x12""qlForwardSwapQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x42""ObjectId,SwapIndex,Spread,ForwardStart,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class ForwardSwapQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""floating SwapIndex object ID."),
            TempStrNoSize("\x14""floating leg spread."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlForwardValueQuote"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlForwardValueQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,IborIndex,FixingDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class ForwardValueQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x0C""Fixing Date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlFuturesConvAdjustmentQuote"),
            // parameter codes
            TempStrNoSize("\x0B""CCCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlFuturesConvAdjustmentQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5C""ObjectId,IborIndex,ImmCode,FuturesQuote,Volatility,MeanReversion,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class FuturesConvAdjustmentQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x1B""futures IMM code (e.g. H9)."),
            TempStrNoSize("\x0E""futures quote."),
            TempStrNoSize("\x15""HullWhite volatility."),
            TempStrNoSize("\x19""HullWhite mean reversion."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlFuturesConvAdjustmentQuoteFuturesValue"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlFuturesConvAdjustmentQuoteFuturesValue"),
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
            TempStrNoSize("\x27""Return the value of futures underlying."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlFuturesConvAdjustmentQuoteImmDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlFuturesConvAdjustmentQuoteImmDate"),
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
            TempStrNoSize("\x1F""Return the IMM date of futures."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlFuturesConvAdjustmentQuoteMeanReversion"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlFuturesConvAdjustmentQuoteMeanReversion"),
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
            TempStrNoSize("\x26""Return the value of HW mean reversion."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlFuturesConvAdjustmentQuoteVolatility"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlFuturesConvAdjustmentQuoteVolatility"),
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
            TempStrNoSize("\x22""Return the value of HW volatility."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x14""qlImpliedStdDevQuote"),
            // parameter codes
            TempStrNoSize("\x0C""CCCPPEPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlImpliedStdDevQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,OptionType,AtmForwardValue,OptionPrice,Strike,Guess,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class ImpliedStdDevQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x4B""implied volatility guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x22""iv accuracy. Default value = 1e-6."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLastFixingQuote"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x11""qlLastFixingQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2A""ObjectId,Index,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class LastFixingQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""Index object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlLastFixingQuoteReferenceDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1E""qlLastFixingQuoteReferenceDate"),
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
            TempStrNoSize("\x22""Return the date of the last fixing"),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::LastFixingQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlQuoteIsValid"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x0E""qlQuoteIsValid"),
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
            TempStrNoSize("\x39""Returns TRUE if the given Quote object has a valid value."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Quote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlQuoteValue"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0C""qlQuoteValue"),
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
            TempStrNoSize("\x34""Returns the current value of the given Quote object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Quote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x17""qlRelinkableHandleQuote"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlRelinkableHandleQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,CurrentLink,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6A""Construct an object of class RelinkableHandleImpl<QuantLibAddin::Quote, QuantLib::Quote> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x59""Quote object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlSimpleQuote"),
            // parameter codes
            TempStrNoSize("\x08""CCPEPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlSimpleQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,Value,TickValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class SimpleQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x38""quote. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x29""tick value used for sensitivity analysis."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSimpleQuoteReset"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x12""qlSimpleQuoteReset"),
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
            TempStrNoSize("\x3F""resets the given SimpleQuote object to the uninitialized state."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::SimpleQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSimpleQuoteSetTickValue"),
            // parameter codes
            TempStrNoSize("\x05""LCEP#"),
            // function display name
            TempStrNoSize("\x19""qlSimpleQuoteSetTickValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Value,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""sets the tick value of the given SimpleQuote object."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::SimpleQuote object"),
            TempStrNoSize("\x13""the new tick value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSimpleQuoteSetValue"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x15""qlSimpleQuoteSetValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Value,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x64""sets a new value to the given SimpleQuote object and returns the difference with the previous value."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::SimpleQuote object"),
            TempStrNoSize("\x40""the new value. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSimpleQuoteTickValue"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlSimpleQuoteTickValue"),
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
            TempStrNoSize("\x37""returns the tick value of the given SimpleQuote object."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::SimpleQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Quotes with Excel

void unregisterQuotes(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x10""qlBucketAnalysis"),
            // parameter codes
            TempStrNoSize("\x08""PPPPPPP#"),
            // function display name
            TempStrNoSize("\x10""qlBucketAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""SimpleQuote,Instruments,Quantities,Shift,SensitivityAnalysis,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4F""delta NPV bucket sensitivity analysis for a (single/vector/matrix) SimpleQuote."),
            // parameter descriptions
            TempStrNoSize("\x0E""simple quotes."),
            TempStrNoSize("\x0C""instruments."),
            TempStrNoSize("\x0B""quantities."),
            TempStrNoSize("\x1E""shift. Default value = 0.0001."),
            TempStrNoSize("\x33""SensitivityAnalysis type. Default value = Centered."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlBucketAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x15""qlBucketAnalysisDelta"),
            // parameter codes
            TempStrNoSize("\x07""PCPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlBucketAnalysisDelta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""SimpleQuote,Parameters,Shift,SensitivityAnalysis,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Parameters' bucket analysis delta for a single SimpleQuote."),
            // parameter descriptions
            TempStrNoSize("\x0D""simple quote."),
            TempStrNoSize("\x12""parameters vector."),
            TempStrNoSize("\x1E""shift. Default value = 0.0001."),
            TempStrNoSize("\x33""SensitivityAnalysis type. Default value = Centered."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlBucketAnalysisDelta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBucketAnalysisDelta2"),
            // parameter codes
            TempStrNoSize("\x07""PPPPPP#"),
            // function display name
            TempStrNoSize("\x16""qlBucketAnalysisDelta2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""SimpleQuote,Parameters,Shift,SensitivityAnalysis,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Parameters' bucket analysis delta for a SimpleQuote vector."),
            // parameter descriptions
            TempStrNoSize("\x0D""simple quote."),
            TempStrNoSize("\x12""parameters vector."),
            TempStrNoSize("\x1E""shift. Default value = 0.0001."),
            TempStrNoSize("\x33""SensitivityAnalysis type. Default value = Centered."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBucketAnalysisDelta2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x10""qlCompositeQuote"),
            // parameter codes
            TempStrNoSize("\x09""CCPPCPPL#"),
            // function display name
            TempStrNoSize("\x10""qlCompositeQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,Element1,Element2,Operator,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class CompositeQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x32""the first, i.e. x, value in the f(x,y) expression."),
            TempStrNoSize("\x33""the second, i.e. y, value in the f(x,y) expression."),
            TempStrNoSize("\x30""the operator to be applied, e.g. ""+"" or ""-""."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlCompositeQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x25""qlEurodollarFuturesImpliedStdDevQuote"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPEPPPPL#"),
            // function display name
            TempStrNoSize("\x25""qlEurodollarFuturesImpliedStdDevQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5D""ObjectId,AtmForwardValue,CallPrice,PutPrice,Strike,Guess,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""Construct an object of class EurodollarFuturesImpliedStdDevQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x12""call option price."),
            TempStrNoSize("\x11""put option price."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x4B""implied volatility guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x32""standard deviation accuracy. Default value = 1e-6."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlEurodollarFuturesImpliedStdDevQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x12""qlForwardSwapQuote"),
            // parameter codes
            TempStrNoSize("\x09""CCCPCPPL#"),
            // function display name
            TempStrNoSize("\x12""qlForwardSwapQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x42""ObjectId,SwapIndex,Spread,ForwardStart,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class ForwardSwapQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""floating SwapIndex object ID."),
            TempStrNoSize("\x14""floating leg spread."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlForwardSwapQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlForwardValueQuote"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlForwardValueQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,IborIndex,FixingDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class ForwardValueQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x0C""Fixing Date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlForwardValueQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlFuturesConvAdjustmentQuote"),
            // parameter codes
            TempStrNoSize("\x0B""CCCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlFuturesConvAdjustmentQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5C""ObjectId,IborIndex,ImmCode,FuturesQuote,Volatility,MeanReversion,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class FuturesConvAdjustmentQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""floating IborIndex object ID."),
            TempStrNoSize("\x1B""futures IMM code (e.g. H9)."),
            TempStrNoSize("\x0E""futures quote."),
            TempStrNoSize("\x15""HullWhite volatility."),
            TempStrNoSize("\x19""HullWhite mean reversion."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlFuturesConvAdjustmentQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlFuturesConvAdjustmentQuoteFuturesValue"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlFuturesConvAdjustmentQuoteFuturesValue"),
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
            TempStrNoSize("\x27""Return the value of futures underlying."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlFuturesConvAdjustmentQuoteFuturesValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlFuturesConvAdjustmentQuoteImmDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlFuturesConvAdjustmentQuoteImmDate"),
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
            TempStrNoSize("\x1F""Return the IMM date of futures."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlFuturesConvAdjustmentQuoteImmDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlFuturesConvAdjustmentQuoteMeanReversion"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlFuturesConvAdjustmentQuoteMeanReversion"),
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
            TempStrNoSize("\x26""Return the value of HW mean reversion."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlFuturesConvAdjustmentQuoteMeanReversion"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlFuturesConvAdjustmentQuoteVolatility"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlFuturesConvAdjustmentQuoteVolatility"),
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
            TempStrNoSize("\x22""Return the value of HW volatility."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::FuturesConvAdjustmentQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlFuturesConvAdjustmentQuoteVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x14""qlImpliedStdDevQuote"),
            // parameter codes
            TempStrNoSize("\x0C""CCCPPEPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlImpliedStdDevQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,OptionType,AtmForwardValue,OptionPrice,Strike,Guess,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class ImpliedStdDevQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1F""option type (i.e. Call or Put)."),
            TempStrNoSize("\x2C""underlying asset at-the-money forward value."),
            TempStrNoSize("\x0D""option price."),
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x4B""implied volatility guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x22""iv accuracy. Default value = 1e-6."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlImpliedStdDevQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLastFixingQuote"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x11""qlLastFixingQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2A""ObjectId,Index,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class LastFixingQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""Index object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlLastFixingQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlLastFixingQuoteReferenceDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1E""qlLastFixingQuoteReferenceDate"),
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
            TempStrNoSize("\x22""Return the date of the last fixing"),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::LastFixingQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlLastFixingQuoteReferenceDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlQuoteIsValid"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x0E""qlQuoteIsValid"),
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
            TempStrNoSize("\x39""Returns TRUE if the given Quote object has a valid value."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Quote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlQuoteIsValid"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlQuoteValue"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0C""qlQuoteValue"),
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
            TempStrNoSize("\x34""Returns the current value of the given Quote object."),
            // parameter descriptions
            TempStrNoSize("\x25""id of existing QuantLib::Quote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlQuoteValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x17""qlRelinkableHandleQuote"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlRelinkableHandleQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,CurrentLink,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6A""Construct an object of class RelinkableHandleImpl<QuantLibAddin::Quote, QuantLib::Quote> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x59""Quote object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlRelinkableHandleQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlSimpleQuote"),
            // parameter codes
            TempStrNoSize("\x08""CCPEPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlSimpleQuote"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,Value,TickValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class SimpleQuote and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x38""quote. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x29""tick value used for sensitivity analysis."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlSimpleQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSimpleQuoteReset"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x12""qlSimpleQuoteReset"),
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
            TempStrNoSize("\x3F""resets the given SimpleQuote object to the uninitialized state."),
            // parameter descriptions
            TempStrNoSize("\x2B""id of existing QuantLib::SimpleQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlSimpleQuoteReset"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSimpleQuoteSetTickValue"),
            // parameter codes
            TempStrNoSize("\x05""LCEP#"),
            // function display name
            TempStrNoSize("\x19""qlSimpleQuoteSetTickValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Value,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""sets the tick value of the given SimpleQuote object."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::SimpleQuote object"),
            TempStrNoSize("\x13""the new tick value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlSimpleQuoteSetTickValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSimpleQuoteSetValue"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x15""qlSimpleQuoteSetValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Value,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x64""sets a new value to the given SimpleQuote object and returns the difference with the previous value."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::SimpleQuote object"),
            TempStrNoSize("\x40""the new value. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlSimpleQuoteSetValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSimpleQuoteTickValue"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlSimpleQuoteTickValue"),
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
            TempStrNoSize("\x37""returns the tick value of the given SimpleQuote object."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLibAddin::SimpleQuote object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSimpleQuoteTickValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

