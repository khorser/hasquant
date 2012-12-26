
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

// register functions in category Ratehelpers with Excel

void registerRatehelpers(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlBondHelper"),
            // parameter codes
            TempStrNoSize("\x08""CCPCPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlBondHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,CleanPrice,Bond,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class BondHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""cleanPrice."),
            TempStrNoSize("\x0F""Bond object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDatedOISRateHelper"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlDatedOISRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,StartDate,EndDate,FixedRate,ONIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class DatedOISRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""swap start date."),
            TempStrNoSize("\x0E""swap end date."),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x26""floating leg OvernightIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlDepositRateHelper"),
            // parameter codes
            TempStrNoSize("\x08""CCPCPPL#"),
            // function display name
            TempStrNoSize("\x13""qlDepositRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Rate,IborIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class DepositRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0E""deposit quote."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDepositRateHelper2"),
            // parameter codes
            TempStrNoSize("\x0D""CCPCNCCLCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlDepositRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x64""ObjectId,Rate,Tenor,FixingDays,Calendar,Convention,EndOfMonth,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class DepositRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0E""deposit quote."),
            TempStrNoSize("\x2A""deposit length (e.g. 3M for three months)."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x5C""End of Month rule (TRUE for end of month to end of month termination date, FALSE otherwise)."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x15""qlFixedRateBondHelper"),
            // parameter codes
            TempStrNoSize("\x0F""CCPNPCPCPPPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlFixedRateBondHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x87""ObjectId,CleanPrice,SettlementDays,FaceAmount,ScheduleID,Coupons,DayCounter,PaymentBDC,Redemption,IssueDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class FixedRateBondHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""cleanPrice."),
            TempStrNoSize("\x10""settlement days."),
            TempStrNoSize("\x2B""Face nominal amount. Default value = 100.0."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x13""coupon fixed rates."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x28""redemption value. Default value = 100.0."),
            TempStrNoSize("\x52""issue date: the bond can't be traded until then. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlFraRateHelper"),
            // parameter codes
            TempStrNoSize("\x09""CCPCCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlFraRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,Rate,PeriodToStart,IborIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class FraRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x15""Period to start date."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x10""qlFraRateHelper2"),
            // parameter codes
            TempStrNoSize("\x0E""CCPCNNCCLCPPL#"),
            // function display name
            TempStrNoSize("\x10""qlFraRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7B""ObjectId,Rate,PeriodToStart,LengthInMonths,FixingDays,Calendar,Convention,EndOfMonth,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class FraRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x15""Period to start date."),
            TempStrNoSize("\x0E""months to end."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x5C""End of Month rule (TRUE for end of month to end of month termination date, FALSE otherwise)."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x13""qlFuturesRateHelper"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlFuturesRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4A""ObjectId,Price,IMM,IborIndex,ConvexityAdjQuote,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class FuturesRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""price quote."),
            TempStrNoSize("\x13""IMM date (or code)."),
            TempStrNoSize("\x2F""IborIndex object ID. Default value = Euribor3M."),
            TempStrNoSize("\x55""convexity adjustment quote (i.e. Forward rate = Futures rate - convexity adjustment)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x14""qlFuturesRateHelper2"),
            // parameter codes
            TempStrNoSize("\x0E""CCPPPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlFuturesRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x79""ObjectId,Price,IMM,LengthInMonths,Calendar,Convention,EndOfMonth,DayCounter,ConvexityAdjQuote,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class FuturesRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""price quote."),
            TempStrNoSize("\x13""IMM date (or code)."),
            TempStrNoSize("\x34""future contract length in months. Default value = 3."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x56""business day convention (e.g. Modified Following). Default value = Modified Following."),
            TempStrNoSize("\x72""End of Month rule (TRUE for end of month to end of month termination date, FALSE otherwise). Default value = true."),
            TempStrNoSize("\x2A""DayCounter ID. Default value = Actual/360."),
            TempStrNoSize("\x55""convexity adjustment quote (i.e. Forward rate = Futures rate - convexity adjustment)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlFuturesRateHelper3"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlFuturesRateHelper3"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x53""ObjectId,Price,IMM,EndDate,DayCounter,ConvexityAdjQuote,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class FuturesRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""price quote."),
            TempStrNoSize("\x13""IMM date (or code)."),
            TempStrNoSize("\x2B""end date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x2A""DayCounter ID. Default value = Actual/360."),
            TempStrNoSize("\x55""convexity adjustment quote (i.e. Forward rate = Futures rate - convexity adjustment)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlFuturesRateHelperConvexityAdjustment"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x26""qlFuturesRateHelperConvexityAdjustment"),
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
            TempStrNoSize("\x48""returns the convexity adjustment for the given FuturesRateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::FuturesRateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlOISRateHelper"),
            // parameter codes
            TempStrNoSize("\x0A""CCNCPCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlOISRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,SettlDays,Tenor,FixedRate,ONIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class OISRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""swap settlement days."),
            TempStrNoSize("\x25""swap length (e.g. 5Y for five years)."),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x26""floating leg OvernightIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateHelperEarliestDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x18""qlRateHelperEarliestDate"),
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
            TempStrNoSize("\x3A""returns the earliest date for the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateHelperImpliedQuote"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlRateHelperImpliedQuote"),
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
            TempStrNoSize("\x3F""returns the curve implied quote of the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlRateHelperLatestDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x16""qlRateHelperLatestDate"),
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
            TempStrNoSize("\x38""returns the latest date for the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlRateHelperQuoteError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlRateHelperQuoteError"),
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
            TempStrNoSize("\x74""returns the error between the curve implied quote and the value of the Quote wrapped in the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateHelperQuoteIsValid"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlRateHelperQuoteIsValid"),
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
            TempStrNoSize("\x50""returns the isValid boolean of the Quote wrapped in the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlRateHelperQuoteValue"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlRateHelperQuoteValue"),
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
            TempStrNoSize("\x46""returns the value of the Quote wrapped in the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlRateHelperRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x10""qlRateHelperRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""RateHelper,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""returns the rate (if any) associated to a rate helper."),
            // parameter descriptions
            TempStrNoSize("\x0E""RateHelper ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x15""qlRateHelperSelection"),
            // parameter codes
            TempStrNoSize("\x0A""PPPNNPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlRateHelperSelection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x60""RateHelpers,Priority,NImmFutures,NSerialFutures,FutureRollDays,DepoInclusion,MinDistance,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""selects rate helpers for bootstrapping."),
            // parameter descriptions
            TempStrNoSize("\x19""vector of RateHelper IDs."),
            TempStrNoSize("\x40""vector of priority integers (higher number for higher priority)."),
            TempStrNoSize("\x4C""max number of IMM (March, June, September, December) Futures to be included."),
            TempStrNoSize("\x6D""max number of Serial (January, February, April, May, July, August, October, November) Futures to be included."),
            TempStrNoSize("\xA9""discard the front Futures the given number of (positive) days before its expiry (e.g zero implies the use of the front Futures during its expiry day). Default value = 2."),
            TempStrNoSize("\x32""Depo inclusion criteria. Default value = AllDepos."),
            TempStrNoSize("\x4D""minimum distance in (positive) days from near instruments. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSwapRateHelper"),
            // parameter codes
            TempStrNoSize("\x0B""CCPCPCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlSwapRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x58""ObjectId,Rate,SwapIndex,Spread,ForwardStart,DiscountingCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class SwapRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x14""floating leg spread."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSwapRateHelper2"),
            // parameter codes
            TempStrNoSize("\x10""CCPCCCCCCPCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlSwapRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9F""ObjectId,Rate,Tenor,Calendar,FixedLegFrequency,FixedLegConvention,FixedLegDayCounter,IborIndex,Spread,ForwardStart,DiscountingCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class SwapRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x25""swap length (e.g. 5Y for five years)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x5A""fixed leg frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x27""fixed leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x14""floating leg spread."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSwapRateHelperForwardStart"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSwapRateHelperForwardStart"),
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
            TempStrNoSize("\x45""returns the forward start period for the given SwapRateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SwapRateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSwapRateHelperSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlSwapRateHelperSpread"),
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
            TempStrNoSize("\x37""returns the spread for the given SwapRateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SwapRateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Ratehelpers with Excel

void unregisterRatehelpers(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlBondHelper"),
            // parameter codes
            TempStrNoSize("\x08""CCPCPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlBondHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,CleanPrice,Bond,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class BondHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""cleanPrice."),
            TempStrNoSize("\x0F""Bond object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlBondHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDatedOISRateHelper"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlDatedOISRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,StartDate,EndDate,FixedRate,ONIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class DatedOISRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""swap start date."),
            TempStrNoSize("\x0E""swap end date."),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x26""floating leg OvernightIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlDatedOISRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlDepositRateHelper"),
            // parameter codes
            TempStrNoSize("\x08""CCPCPPL#"),
            // function display name
            TempStrNoSize("\x13""qlDepositRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Rate,IborIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class DepositRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0E""deposit quote."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlDepositRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDepositRateHelper2"),
            // parameter codes
            TempStrNoSize("\x0D""CCPCNCCLCPPL#"),
            // function display name
            TempStrNoSize("\x14""qlDepositRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x64""ObjectId,Rate,Tenor,FixingDays,Calendar,Convention,EndOfMonth,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class DepositRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0E""deposit quote."),
            TempStrNoSize("\x2A""deposit length (e.g. 3M for three months)."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x5C""End of Month rule (TRUE for end of month to end of month termination date, FALSE otherwise)."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlDepositRateHelper2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x15""qlFixedRateBondHelper"),
            // parameter codes
            TempStrNoSize("\x0F""CCPNPCPCPPPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlFixedRateBondHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x87""ObjectId,CleanPrice,SettlementDays,FaceAmount,ScheduleID,Coupons,DayCounter,PaymentBDC,Redemption,IssueDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Construct an object of class FixedRateBondHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""cleanPrice."),
            TempStrNoSize("\x10""settlement days."),
            TempStrNoSize("\x2B""Face nominal amount. Default value = 100.0."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x13""coupon fixed rates."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x28""redemption value. Default value = 100.0."),
            TempStrNoSize("\x52""issue date: the bond can't be traded until then. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlFixedRateBondHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlFraRateHelper"),
            // parameter codes
            TempStrNoSize("\x09""CCPCCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlFraRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,Rate,PeriodToStart,IborIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class FraRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x15""Period to start date."),
            TempStrNoSize("\x14""IborIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlFraRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x10""qlFraRateHelper2"),
            // parameter codes
            TempStrNoSize("\x0E""CCPCNNCCLCPPL#"),
            // function display name
            TempStrNoSize("\x10""qlFraRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7B""ObjectId,Rate,PeriodToStart,LengthInMonths,FixingDays,Calendar,Convention,EndOfMonth,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class FraRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x15""Period to start date."),
            TempStrNoSize("\x0E""months to end."),
            TempStrNoSize("\x15""fixing days (e.g. 2)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x32""business day convention (e.g. Modified Following)."),
            TempStrNoSize("\x5C""End of Month rule (TRUE for end of month to end of month termination date, FALSE otherwise)."),
            TempStrNoSize("\x0E""DayCounter ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlFraRateHelper2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x13""qlFuturesRateHelper"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlFuturesRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4A""ObjectId,Price,IMM,IborIndex,ConvexityAdjQuote,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class FuturesRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""price quote."),
            TempStrNoSize("\x13""IMM date (or code)."),
            TempStrNoSize("\x2F""IborIndex object ID. Default value = Euribor3M."),
            TempStrNoSize("\x55""convexity adjustment quote (i.e. Forward rate = Futures rate - convexity adjustment)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlFuturesRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x14""qlFuturesRateHelper2"),
            // parameter codes
            TempStrNoSize("\x0E""CCPPPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlFuturesRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x79""ObjectId,Price,IMM,LengthInMonths,Calendar,Convention,EndOfMonth,DayCounter,ConvexityAdjQuote,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class FuturesRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""price quote."),
            TempStrNoSize("\x13""IMM date (or code)."),
            TempStrNoSize("\x34""future contract length in months. Default value = 3."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x56""business day convention (e.g. Modified Following). Default value = Modified Following."),
            TempStrNoSize("\x72""End of Month rule (TRUE for end of month to end of month termination date, FALSE otherwise). Default value = true."),
            TempStrNoSize("\x2A""DayCounter ID. Default value = Actual/360."),
            TempStrNoSize("\x55""convexity adjustment quote (i.e. Forward rate = Futures rate - convexity adjustment)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlFuturesRateHelper2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlFuturesRateHelper3"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlFuturesRateHelper3"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x53""ObjectId,Price,IMM,EndDate,DayCounter,ConvexityAdjQuote,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class FuturesRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""price quote."),
            TempStrNoSize("\x13""IMM date (or code)."),
            TempStrNoSize("\x2B""end date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x2A""DayCounter ID. Default value = Actual/360."),
            TempStrNoSize("\x55""convexity adjustment quote (i.e. Forward rate = Futures rate - convexity adjustment)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlFuturesRateHelper3"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlFuturesRateHelperConvexityAdjustment"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x26""qlFuturesRateHelperConvexityAdjustment"),
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
            TempStrNoSize("\x48""returns the convexity adjustment for the given FuturesRateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::FuturesRateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlFuturesRateHelperConvexityAdjustment"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlOISRateHelper"),
            // parameter codes
            TempStrNoSize("\x0A""CCNCPCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlOISRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,SettlDays,Tenor,FixedRate,ONIndex,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class OISRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""swap settlement days."),
            TempStrNoSize("\x25""swap length (e.g. 5Y for five years)."),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x26""floating leg OvernightIndex object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlOISRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateHelperEarliestDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x18""qlRateHelperEarliestDate"),
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
            TempStrNoSize("\x3A""returns the earliest date for the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlRateHelperEarliestDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateHelperImpliedQuote"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlRateHelperImpliedQuote"),
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
            TempStrNoSize("\x3F""returns the curve implied quote of the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlRateHelperImpliedQuote"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlRateHelperLatestDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x16""qlRateHelperLatestDate"),
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
            TempStrNoSize("\x38""returns the latest date for the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlRateHelperLatestDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlRateHelperQuoteError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlRateHelperQuoteError"),
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
            TempStrNoSize("\x74""returns the error between the curve implied quote and the value of the Quote wrapped in the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlRateHelperQuoteError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlRateHelperQuoteIsValid"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x18""qlRateHelperQuoteIsValid"),
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
            TempStrNoSize("\x50""returns the isValid boolean of the Quote wrapped in the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlRateHelperQuoteIsValid"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlRateHelperQuoteValue"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlRateHelperQuoteValue"),
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
            TempStrNoSize("\x46""returns the value of the Quote wrapped in the given RateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::RateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlRateHelperQuoteValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlRateHelperRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x10""qlRateHelperRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""RateHelper,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""returns the rate (if any) associated to a rate helper."),
            // parameter descriptions
            TempStrNoSize("\x0E""RateHelper ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlRateHelperRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x15""qlRateHelperSelection"),
            // parameter codes
            TempStrNoSize("\x0A""PPPNNPPPP#"),
            // function display name
            TempStrNoSize("\x15""qlRateHelperSelection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x60""RateHelpers,Priority,NImmFutures,NSerialFutures,FutureRollDays,DepoInclusion,MinDistance,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x27""selects rate helpers for bootstrapping."),
            // parameter descriptions
            TempStrNoSize("\x19""vector of RateHelper IDs."),
            TempStrNoSize("\x40""vector of priority integers (higher number for higher priority)."),
            TempStrNoSize("\x4C""max number of IMM (March, June, September, December) Futures to be included."),
            TempStrNoSize("\x6D""max number of Serial (January, February, April, May, July, August, October, November) Futures to be included."),
            TempStrNoSize("\xA9""discard the front Futures the given number of (positive) days before its expiry (e.g zero implies the use of the front Futures during its expiry day). Default value = 2."),
            TempStrNoSize("\x32""Depo inclusion criteria. Default value = AllDepos."),
            TempStrNoSize("\x4D""minimum distance in (positive) days from near instruments. Default value = 1."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlRateHelperSelection"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSwapRateHelper"),
            // parameter codes
            TempStrNoSize("\x0B""CCPCPCPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlSwapRateHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x58""ObjectId,Rate,SwapIndex,Spread,ForwardStart,DiscountingCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class SwapRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x14""SwapIndex object ID."),
            TempStrNoSize("\x14""floating leg spread."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlSwapRateHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSwapRateHelper2"),
            // parameter codes
            TempStrNoSize("\x10""CCPCCCCCCPCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlSwapRateHelper2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9F""ObjectId,Rate,Tenor,Calendar,FixedLegFrequency,FixedLegConvention,FixedLegDayCounter,IborIndex,Spread,ForwardStart,DiscountingCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class SwapRateHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x25""swap length (e.g. 5Y for five years)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x5A""fixed leg frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x27""fixed leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x14""floating leg spread."),
            TempStrNoSize("\x15""forward start period."),
            TempStrNoSize("\x3B""discounting YieldTermStructure object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlSwapRateHelper2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSwapRateHelperForwardStart"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSwapRateHelperForwardStart"),
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
            TempStrNoSize("\x45""returns the forward start period for the given SwapRateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SwapRateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlSwapRateHelperForwardStart"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSwapRateHelperSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlSwapRateHelperSpread"),
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
            TempStrNoSize("\x37""returns the spread for the given SwapRateHelper object."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SwapRateHelper object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSwapRateHelperSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

