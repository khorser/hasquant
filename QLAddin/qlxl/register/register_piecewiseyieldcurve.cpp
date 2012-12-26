
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

// register functions in category Piecewiseyieldcurve with Excel

void registerPiecewiseyieldcurve(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x15""qlPiecewiseYieldCurve"),
            // parameter codes
            TempStrNoSize("\x0F""CCPCPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlPiecewiseYieldCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7B""ObjectId,NDays,Calendar,RateHelpers,DayCounter,Jumps,JumpDates,Accuracy,TraitsID,InterpolatorID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class PiecewiseYieldCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x8D""number of days to advance from EvaluationDate (usually zero or two): it fixes the date at which the discount factor = 1.0. Default value = 0."),
            TempStrNoSize("\x45""holiday calendar (e.g. TARGET) to advance from global EvaluationDate."),
            TempStrNoSize("\x17""vector of rate-helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x13""Jump quotes vector."),
            TempStrNoSize("\x12""Jump dates vector."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x3D""Discount, ZeroRate, or ForwardRate. Default value = Discount."),
            TempStrNoSize("\x62""BackwardFlat, ForwardFlat, Linear, LogLinear, CubicSpline, or LogCubic. Default value = LogLinear."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlPiecewiseYieldCurveData"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlPiecewiseYieldCurveData"),
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
            TempStrNoSize("\x46""Retrieve Data for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveDates"),
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
            TempStrNoSize("\x4F""Retrieve list of Dates for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpDates"),
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
            TempStrNoSize("\x54""Retrieve list of jump dates for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpTimes"),
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
            TempStrNoSize("\x54""Retrieve list of jump times for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveTimes"),
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
            TempStrNoSize("\x4F""Retrieve list of Times for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Piecewiseyieldcurve with Excel

void unregisterPiecewiseyieldcurve(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x15""qlPiecewiseYieldCurve"),
            // parameter codes
            TempStrNoSize("\x0F""CCPCPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlPiecewiseYieldCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7B""ObjectId,NDays,Calendar,RateHelpers,DayCounter,Jumps,JumpDates,Accuracy,TraitsID,InterpolatorID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class PiecewiseYieldCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x8D""number of days to advance from EvaluationDate (usually zero or two): it fixes the date at which the discount factor = 1.0. Default value = 0."),
            TempStrNoSize("\x45""holiday calendar (e.g. TARGET) to advance from global EvaluationDate."),
            TempStrNoSize("\x17""vector of rate-helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x13""Jump quotes vector."),
            TempStrNoSize("\x12""Jump dates vector."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x3D""Discount, ZeroRate, or ForwardRate. Default value = Discount."),
            TempStrNoSize("\x62""BackwardFlat, ForwardFlat, Linear, LogLinear, CubicSpline, or LogCubic. Default value = LogLinear."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlPiecewiseYieldCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlPiecewiseYieldCurveData"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlPiecewiseYieldCurveData"),
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
            TempStrNoSize("\x46""Retrieve Data for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlPiecewiseYieldCurveData"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveDates"),
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
            TempStrNoSize("\x4F""Retrieve list of Dates for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpDates"),
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
            TempStrNoSize("\x54""Retrieve list of jump dates for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpTimes"),
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
            TempStrNoSize("\x54""Retrieve list of jump times for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlPiecewiseYieldCurveJumpTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveTimes"),
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
            TempStrNoSize("\x4F""Retrieve list of Times for the given PiecewiseYieldCurve<Traits, Interpolator>."),
            // parameter descriptions
            TempStrNoSize("\x38""id of existing QuantLibAddin::PiecewiseYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlPiecewiseYieldCurveTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

