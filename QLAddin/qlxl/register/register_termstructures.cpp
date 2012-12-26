
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

// register functions in category Termstructures with Excel

void registerTermstructures(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlDiscountCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlDiscountCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,CurveDates,CurveDiscounts,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class DiscountCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x25""discount factors for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlFlatForward"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlFlatForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x59""ObjectId,NDays,Calendar,Rate,DayCounter,Compounding,Frequency,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class FlatForward and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x8D""number of days to advance from EvaluationDate (usually zero or two): it fixes the date at which the discount factor = 1.0. Default value = 0."),
            TempStrNoSize("\x63""holiday calendar (e.g. TARGET) to advance from global EvaluationDate. Default value = NullCalendar."),
            TempStrNoSize("\x10""the curve level."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlForwardCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlForwardCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,CurveDates,ForwardYields,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class ForwardCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x23""forwards rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlForwardSpreadedTermStructure"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlForwardSpreadedTermStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3A""ObjectId,BaseYieldCurve,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class ForwardSpreadedTermStructure and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Base YieldTermStructure object ID."),
            TempStrNoSize("\x07""spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlImpliedTermStructure"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlImpliedTermStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,BaseYieldCurve,ReferenceDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class ImpliedTermStructure and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Base YieldTermStructure object ID."),
            TempStrNoSize("\x44""the reference date the base YieldTermStructure should be shifted to."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolatedYieldCurve"),
            // parameter codes
            TempStrNoSize("\x0E""CCPPCPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolatedYieldCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6B""ObjectId,Dates,Data,Calendar,DayCounter,Jumps,JumpDates,TraitsID,InterpolatorID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class InterpolatedYieldCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""vector of dates, the first one being the one at which discount factor = 1.0"),
            TempStrNoSize("\x44""data vector. Each element should be of the type selected by TraitsID"),
            TempStrNoSize("\x45""holiday calendar (e.g. TARGET) to advance from global EvaluationDate."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x13""Jump quotes vector."),
            TempStrNoSize("\x12""Jump dates vector."),
            TempStrNoSize("\x3E""Discount, ZeroYield, or ForwardRate. Default value = Discount."),
            TempStrNoSize("\x80""BackwardFlat, ForwardFlat, Linear, LogLinear, LogParabolic, KrugerLogCubic, etc. Default value = MonotonicLogCubicNaturalSpline."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterpolatedYieldCurveData"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterpolatedYieldCurveData"),
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
            TempStrNoSize("\x33""Retrieve Data for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveDates"),
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
            TempStrNoSize("\x3C""Retrieve list of Dates for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpDates"),
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
            TempStrNoSize("\x41""Retrieve list of jump dates for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpTimes"),
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
            TempStrNoSize("\x41""Retrieve list of jump times for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveTimes"),
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
            TempStrNoSize("\x3C""Retrieve list of Times for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x24""qlRelinkableHandleYieldTermStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x24""qlRelinkableHandleYieldTermStructure"),
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
            TempStrNoSize("\x84""Construct an object of class RelinkableHandleImpl<QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x66""YieldTermStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlTermStructureCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x17""qlTermStructureCalendar"),
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
            TempStrNoSize("\x3C""Returns the calendar used by the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlTermStructureDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x19""qlTermStructureDayCounter"),
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
            TempStrNoSize("\x3E""Returns the DayCounter used by the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlTermStructureMaxDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x16""qlTermStructureMaxDate"),
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
            TempStrNoSize("\x38""Returns the max date for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlTermStructureReferenceDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1C""qlTermStructureReferenceDate"),
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
            TempStrNoSize("\x3E""Returns the reference date for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlTermStructureSettlementDays"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1D""qlTermStructureSettlementDays"),
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
            TempStrNoSize("\x49""Returns the number of settlement days for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlTermStructureTimeFromReference"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlTermStructureTimeFromReference"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the time from the reference date for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x10""vector of dates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlYieldTSDiscount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x11""qlYieldTSDiscount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,DfDates,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns a discount factor from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x10""vector of dates."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x14""qlYieldTSForwardRate"),
            // parameter codes
            TempStrNoSize("\x0A""PCPPCPPPP#"),
            // function display name
            TempStrNoSize("\x14""qlYieldTSForwardRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,D1,D2,ResultDayCounter,Compounding,Frequency,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the forward interest rate from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x0B""first date."),
            TempStrNoSize("\x0C""second date."),
            TempStrNoSize("\x12""result DayCounter."),
            TempStrNoSize("\x6C""Interest rate compounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Simple."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x15""qlYieldTSForwardRate2"),
            // parameter codes
            TempStrNoSize("\x0A""PCPCCPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlYieldTSForwardRate2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,Date,Period,ResultDayCounter,Compounding,Frequency,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the forward interest rate from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x0B""first date."),
            TempStrNoSize("\x24""Period (e.g. '7D', '3M', '1Y', etc)."),
            TempStrNoSize("\x12""result DayCounter."),
            TempStrNoSize("\x6C""Interest rate compounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Simple."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x11""qlYieldTSZeroRate"),
            // parameter codes
            TempStrNoSize("\x09""PCPCPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlYieldTSZeroRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,Dates,ResultDayCounter,Compounding,Frequency,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the zero interest rate from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x11""resultDayCounter."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlZeroCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlZeroCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,CurveDates,CurveYields,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class ZeroCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x1F""zero rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Termstructures with Excel

void unregisterTermstructures(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlDiscountCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlDiscountCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,CurveDates,CurveDiscounts,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class DiscountCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x25""discount factors for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlDiscountCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlFlatForward"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlFlatForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x59""ObjectId,NDays,Calendar,Rate,DayCounter,Compounding,Frequency,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Construct an object of class FlatForward and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x8D""number of days to advance from EvaluationDate (usually zero or two): it fixes the date at which the discount factor = 1.0. Default value = 0."),
            TempStrNoSize("\x63""holiday calendar (e.g. TARGET) to advance from global EvaluationDate. Default value = NullCalendar."),
            TempStrNoSize("\x10""the curve level."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlFlatForward"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlForwardCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlForwardCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,CurveDates,ForwardYields,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class ForwardCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x23""forwards rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlForwardCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlForwardSpreadedTermStructure"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlForwardSpreadedTermStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3A""ObjectId,BaseYieldCurve,Spread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class ForwardSpreadedTermStructure and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Base YieldTermStructure object ID."),
            TempStrNoSize("\x07""spread."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlForwardSpreadedTermStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlImpliedTermStructure"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlImpliedTermStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,BaseYieldCurve,ReferenceDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class ImpliedTermStructure and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Base YieldTermStructure object ID."),
            TempStrNoSize("\x44""the reference date the base YieldTermStructure should be shifted to."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlImpliedTermStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolatedYieldCurve"),
            // parameter codes
            TempStrNoSize("\x0E""CCPPCPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolatedYieldCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6B""ObjectId,Dates,Data,Calendar,DayCounter,Jumps,JumpDates,TraitsID,InterpolatorID,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class InterpolatedYieldCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""vector of dates, the first one being the one at which discount factor = 1.0"),
            TempStrNoSize("\x44""data vector. Each element should be of the type selected by TraitsID"),
            TempStrNoSize("\x45""holiday calendar (e.g. TARGET) to advance from global EvaluationDate."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x13""Jump quotes vector."),
            TempStrNoSize("\x12""Jump dates vector."),
            TempStrNoSize("\x3E""Discount, ZeroYield, or ForwardRate. Default value = Discount."),
            TempStrNoSize("\x80""BackwardFlat, ForwardFlat, Linear, LogLinear, LogParabolic, KrugerLogCubic, etc. Default value = MonotonicLogCubicNaturalSpline."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterpolatedYieldCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterpolatedYieldCurveData"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterpolatedYieldCurveData"),
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
            TempStrNoSize("\x33""Retrieve Data for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInterpolatedYieldCurveData"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveDates"),
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
            TempStrNoSize("\x3C""Retrieve list of Dates for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpDates"),
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
            TempStrNoSize("\x41""Retrieve list of jump dates for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpTimes"),
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
            TempStrNoSize("\x41""Retrieve list of jump times for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlInterpolatedYieldCurveJumpTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveTimes"),
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
            TempStrNoSize("\x3C""Retrieve list of Times for the given InterpolatedYieldCurve."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLibAddin::InterpolatedYieldCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlInterpolatedYieldCurveTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x24""qlRelinkableHandleYieldTermStructure"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x24""qlRelinkableHandleYieldTermStructure"),
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
            TempStrNoSize("\x84""Construct an object of class RelinkableHandleImpl<QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure> and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x66""YieldTermStructure object ID. If omitted, nothing is linked by the RelinkableHandle. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlRelinkableHandleYieldTermStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlTermStructureCalendar"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x17""qlTermStructureCalendar"),
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
            TempStrNoSize("\x3C""Returns the calendar used by the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlTermStructureCalendar"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlTermStructureDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x19""qlTermStructureDayCounter"),
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
            TempStrNoSize("\x3E""Returns the DayCounter used by the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlTermStructureDayCounter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlTermStructureMaxDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x16""qlTermStructureMaxDate"),
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
            TempStrNoSize("\x38""Returns the max date for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlTermStructureMaxDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlTermStructureReferenceDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1C""qlTermStructureReferenceDate"),
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
            TempStrNoSize("\x3E""Returns the reference date for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlTermStructureReferenceDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlTermStructureSettlementDays"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1D""qlTermStructureSettlementDays"),
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
            TempStrNoSize("\x49""Returns the number of settlement days for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlTermStructureSettlementDays"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlTermStructureTimeFromReference"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlTermStructureTimeFromReference"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Date,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the time from the reference date for the given TermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::TermStructure object"),
            TempStrNoSize("\x10""vector of dates."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlTermStructureTimeFromReference"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlYieldTSDiscount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x11""qlYieldTSDiscount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,DfDates,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns a discount factor from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x10""vector of dates."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlYieldTSDiscount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x14""qlYieldTSForwardRate"),
            // parameter codes
            TempStrNoSize("\x0A""PCPPCPPPP#"),
            // function display name
            TempStrNoSize("\x14""qlYieldTSForwardRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,D1,D2,ResultDayCounter,Compounding,Frequency,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the forward interest rate from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x0B""first date."),
            TempStrNoSize("\x0C""second date."),
            TempStrNoSize("\x12""result DayCounter."),
            TempStrNoSize("\x6C""Interest rate compounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Simple."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlYieldTSForwardRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x15""qlYieldTSForwardRate2"),
            // parameter codes
            TempStrNoSize("\x0A""PCPCCPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlYieldTSForwardRate2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,Date,Period,ResultDayCounter,Compounding,Frequency,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the forward interest rate from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x0B""first date."),
            TempStrNoSize("\x24""Period (e.g. '7D', '3M', '1Y', etc)."),
            TempStrNoSize("\x12""result DayCounter."),
            TempStrNoSize("\x6C""Interest rate compounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Simple."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlYieldTSForwardRate2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x11""qlYieldTSZeroRate"),
            // parameter codes
            TempStrNoSize("\x09""PCPCPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlYieldTSZeroRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,Dates,ResultDayCounter,Compounding,Frequency,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the zero interest rate from the given YieldTermStructure object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::YieldTermStructure object"),
            TempStrNoSize("\x05""date."),
            TempStrNoSize("\x11""resultDayCounter."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x31""TRUE allows extrapolation. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlYieldTSZeroRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlZeroCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlZeroCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,CurveDates,CurveYields,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class ZeroCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x1F""zero rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlZeroCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

