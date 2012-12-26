
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

// register functions in category Couponvectors with Excel

void registerCouponvectors(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCmsCouponPricer"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlCmsCouponPricer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,Volatility,CmsCouponPricerType,YieldCurveModel,MeanReversion,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class CmsCouponPricer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x28""Swaption Volatility Structure object ID."),
            TempStrNoSize("\x6B""Cms Coupon Pricer Type (e.g ConundrumByBlack, ConundrumByNumericalIntegration, ClassicalAnaliticalFormula)."),
            TempStrNoSize("\x57""model of the yield curve (e.g Standard, ExactYield, ParallelShifts, NonParallelShifts)."),
            TempStrNoSize("\x15""mean reversion quote."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x08""qlCmsLeg"),
            // parameter codes
            TempStrNoSize("\x11""CCPPCPPCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x08""qlCmsLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8C""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Floors,Gearings,SwapIndex,Spreads,Caps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Construct an object of class CmsLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""floor strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x1F""underlying SwapIndex object ID."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3B""cap strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlCmsZeroLeg"),
            // parameter codes
            TempStrNoSize("\x11""CCPPCPPCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlCmsZeroLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8C""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Floors,Gearings,SwapIndex,Spreads,Caps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class CmsZeroLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""floor strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x1F""underlying SwapIndex object ID."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3B""cap strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x27""qlConundrumPricerByNumericalIntegration"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x27""qlConundrumPricerByNumericalIntegration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6E""ObjectId,SwaptionVol,YieldCurveModel,MeanReversion,LowerLimit,UpperLimit,Precision,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class NumericHaganPricer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""Volatility Cube by Sabr."),
            TempStrNoSize("\x57""model of the yield curve (e.g Standard, ExactYield, ParallelShifts, NonParallelShifts)."),
            TempStrNoSize("\x0F""mean reversion."),
            TempStrNoSize("\x21""lower limit. Default value = 0.0."),
            TempStrNoSize("\x21""upper limit. Default value = 1.0."),
            TempStrNoSize("\x22""precision. Default value = 1.0e-6."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x31""qlConundrumPricerByNumericalIntegrationUpperLimit"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x31""qlConundrumPricerByNumericalIntegrationUpperLimit"),
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
            TempStrNoSize("\x28""Returns the upper limit of the integral."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::NumericHaganPricer object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlDigitalCmsLeg"),
            // parameter codes
            TempStrNoSize("\x16""CCPPCPPCPCPPCPPCPCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlDigitalCmsLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xCB""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Gearings,SwapIndex,Spreads,CallStrikes,CallSpecs,CallPayoff,PutStrikes,PutSpecs,PutPayoff,Replication,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class DigitalCmsLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""nominal amount vector."),
            TempStrNoSize("\x13""schedule object ID."),
            TempStrNoSize("\x3E""fixing days. Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x10""swap rate index."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x5E""option strikes. If omitted, no call is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2E""call position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7B""payoff if the call ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x5D""option strikes. If omitted, no put is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2D""put position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7A""payoff if the put ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x16""replication object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDigitalIborLeg"),
            // parameter codes
            TempStrNoSize("\x16""CCPPCPPCPCPPCPPCPCPPL#"),
            // function display name
            TempStrNoSize("\x10""qlDigitalIborLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xCB""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Gearings,IborIndex,Spreads,CallStrikes,CallSpecs,CallPayoff,PutStrikes,PutSpecs,PutPayoff,Replication,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class DigitalIborLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""nominal amount vector."),
            TempStrNoSize("\x13""schedule object ID."),
            TempStrNoSize("\x3E""fixing days. Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x5E""option strikes. If omitted, no call is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2E""call position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7B""payoff if the call ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x5D""option strikes. If omitted, no put is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2D""put position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7A""payoff if the put ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x16""replication object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDigitalReplication"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlDigitalReplication"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,Replication,Gap,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class DigitalReplication and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""Replication type (Sub, Central or Super)."),
            TempStrNoSize("\x47""spread in strikes used in call/put replication. Default value = 0.0001."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlFixedRateLeg"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPCPCPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlFixedRateLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,PaymentBDC,Nominals,ScheduleID,Coupons,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class FixedRateLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x13""coupon fixed rates."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlFixedRateLeg2"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPCPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlFixedRateLeg2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4B""ObjectId,PaymentBDC,Nominals,ScheduleID,Coupons,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class FixedRateLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x18""coupon InterestRate IDs."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x12""qlIborCouponPricer"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x12""qlIborCouponPricer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,Volatility,IborCouponPricerType,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class IborCouponPricer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x26""Caplet Volatility Structure object ID."),
            TempStrNoSize("\x2E""Ibor Coupon Pricer Type (e.g IborByBlack, ..)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x09""qlIborLeg"),
            // parameter codes
            TempStrNoSize("\x11""CCPPCPPCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlIborLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8C""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Floors,Gearings,IborIndex,Spreads,Caps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class IborLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""floor strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3B""cap strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 26, &xDll,
            // function code name
            TempStrNoSize("\x11""qlRangeAccrualLeg"),
            // parameter codes
            TempStrNoSize("\x12""CCPPCPCPPCPPCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlRangeAccrualLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB0""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,DayCounter,LowerStrikes,Gearings,IborIndex,Spreads,UpperStrikes,ObservationsTenor,ObservationsBDC,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class RangeAccrualLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""lower strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x1F""underlying IborIndex object ID."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3D""upper strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1A""observations tenor period."),
            TempStrNoSize("\x49""observations business day convention. Default value = Modified Following."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Couponvectors with Excel

void unregisterCouponvectors(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCmsCouponPricer"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlCmsCouponPricer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x61""ObjectId,Volatility,CmsCouponPricerType,YieldCurveModel,MeanReversion,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class CmsCouponPricer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x28""Swaption Volatility Structure object ID."),
            TempStrNoSize("\x6B""Cms Coupon Pricer Type (e.g ConundrumByBlack, ConundrumByNumericalIntegration, ClassicalAnaliticalFormula)."),
            TempStrNoSize("\x57""model of the yield curve (e.g Standard, ExactYield, ParallelShifts, NonParallelShifts)."),
            TempStrNoSize("\x15""mean reversion quote."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlCmsCouponPricer"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x08""qlCmsLeg"),
            // parameter codes
            TempStrNoSize("\x11""CCPPCPPCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x08""qlCmsLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8C""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Floors,Gearings,SwapIndex,Spreads,Caps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Construct an object of class CmsLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""floor strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x1F""underlying SwapIndex object ID."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3B""cap strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x08""qlCmsLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlCmsZeroLeg"),
            // parameter codes
            TempStrNoSize("\x11""CCPPCPPCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlCmsZeroLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8C""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Floors,Gearings,SwapIndex,Spreads,Caps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class CmsZeroLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""floor strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x1F""underlying SwapIndex object ID."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3B""cap strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlCmsZeroLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x27""qlConundrumPricerByNumericalIntegration"),
            // parameter codes
            TempStrNoSize("\x0C""CCCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x27""qlConundrumPricerByNumericalIntegration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6E""ObjectId,SwaptionVol,YieldCurveModel,MeanReversion,LowerLimit,UpperLimit,Precision,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class NumericHaganPricer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""Volatility Cube by Sabr."),
            TempStrNoSize("\x57""model of the yield curve (e.g Standard, ExactYield, ParallelShifts, NonParallelShifts)."),
            TempStrNoSize("\x0F""mean reversion."),
            TempStrNoSize("\x21""lower limit. Default value = 0.0."),
            TempStrNoSize("\x21""upper limit. Default value = 1.0."),
            TempStrNoSize("\x22""precision. Default value = 1.0e-6."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlConundrumPricerByNumericalIntegration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x31""qlConundrumPricerByNumericalIntegrationUpperLimit"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x31""qlConundrumPricerByNumericalIntegrationUpperLimit"),
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
            TempStrNoSize("\x28""Returns the upper limit of the integral."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::NumericHaganPricer object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x31""qlConundrumPricerByNumericalIntegrationUpperLimit"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlDigitalCmsLeg"),
            // parameter codes
            TempStrNoSize("\x16""CCPPCPPCPCPPCPPCPCPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlDigitalCmsLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xCB""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Gearings,SwapIndex,Spreads,CallStrikes,CallSpecs,CallPayoff,PutStrikes,PutSpecs,PutPayoff,Replication,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class DigitalCmsLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""nominal amount vector."),
            TempStrNoSize("\x13""schedule object ID."),
            TempStrNoSize("\x3E""fixing days. Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x10""swap rate index."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x5E""option strikes. If omitted, no call is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2E""call position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7B""payoff if the call ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x5D""option strikes. If omitted, no put is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2D""put position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7A""payoff if the put ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x16""replication object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlDigitalCmsLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x10""qlDigitalIborLeg"),
            // parameter codes
            TempStrNoSize("\x16""CCPPCPPCPCPPCPPCPCPPL#"),
            // function display name
            TempStrNoSize("\x10""qlDigitalIborLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xCB""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Gearings,IborIndex,Spreads,CallStrikes,CallSpecs,CallPayoff,PutStrikes,PutSpecs,PutPayoff,Replication,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class DigitalIborLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""nominal amount vector."),
            TempStrNoSize("\x13""schedule object ID."),
            TempStrNoSize("\x3E""fixing days. Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x5E""option strikes. If omitted, no call is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2E""call position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7B""payoff if the call ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x5D""option strikes. If omitted, no put is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2D""put position (Short, Long) and ATM inclusion."),
            TempStrNoSize("\x7A""payoff if the put ends ITM. If omitted, asset-or-nothing option is assumed. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x16""replication object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlDigitalIborLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlDigitalReplication"),
            // parameter codes
            TempStrNoSize("\x08""CCCPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlDigitalReplication"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,Replication,Gap,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class DigitalReplication and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""Replication type (Sub, Central or Super)."),
            TempStrNoSize("\x47""spread in strikes used in call/put replication. Default value = 0.0001."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlDigitalReplication"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlFixedRateLeg"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPCPCPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlFixedRateLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,PaymentBDC,Nominals,ScheduleID,Coupons,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class FixedRateLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x13""coupon fixed rates."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlFixedRateLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlFixedRateLeg2"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPCPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlFixedRateLeg2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4B""ObjectId,PaymentBDC,Nominals,ScheduleID,Coupons,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class FixedRateLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x18""coupon InterestRate IDs."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlFixedRateLeg2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x12""qlIborCouponPricer"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x12""qlIborCouponPricer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,Volatility,IborCouponPricerType,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class IborCouponPricer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x26""Caplet Volatility Structure object ID."),
            TempStrNoSize("\x2E""Ibor Coupon Pricer Type (e.g IborByBlack, ..)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlIborCouponPricer"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x09""qlIborLeg"),
            // parameter codes
            TempStrNoSize("\x11""CCPPCPPCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x09""qlIborLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8C""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,IsInArrears,DayCounter,Floors,Gearings,IborIndex,Spreads,Caps,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x36""Construct an object of class IborLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x38""TRUE if the fixing is in arrears. Default value = false."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""floor strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3B""cap strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlIborLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 26, &xDll,
            // function code name
            TempStrNoSize("\x11""qlRangeAccrualLeg"),
            // parameter codes
            TempStrNoSize("\x12""CCPPCPCPPCPPCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlRangeAccrualLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB0""ObjectId,PaymentBDC,Nominals,ScheduleID,FixingDays,DayCounter,LowerStrikes,Gearings,IborIndex,Spreads,UpperStrikes,ObservationsTenor,ObservationsBDC,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class RangeAccrualLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x3B""payment business day convention. Default value = Following."),
            TempStrNoSize("\x16""Nominal amount vector."),
            TempStrNoSize("\x13""Schedule object ID."),
            TempStrNoSize("\x47""fixing days (e.g. 2). Default value = std::vector<QuantLib::Natural>()."),
            TempStrNoSize("\x16""Payment DayCounter ID."),
            TempStrNoSize("\x3D""lower strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x2C""floating rate gearings. Default value = 1.0."),
            TempStrNoSize("\x1F""underlying IborIndex object ID."),
            TempStrNoSize("\x2B""floating rate spreads. Default value = 0.0."),
            TempStrNoSize("\x3D""upper strikes. Default value = std::vector<QuantLib::Rate>()."),
            TempStrNoSize("\x1A""observations tenor period."),
            TempStrNoSize("\x49""observations business day convention. Default value = Modified Following."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlRangeAccrualLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

