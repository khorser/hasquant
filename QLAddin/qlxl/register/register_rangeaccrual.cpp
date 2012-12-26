
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

// register functions in category Rangeaccrual with Excel

void registerRangeaccrual(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlRangeAccrualFloatersCoupon"),
            // parameter codes
            TempStrNoSize("\x14""CCEPCPPNCEEPPCEEPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlRangeAccrualFloatersCoupon"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xBE""ObjectId,Nominal,PaymentDate,IborIndex,StartDate,EndDate,FixingDays,DayCountID,Gearings,Spreads,RefPeriodStart,RefPeriodEnd,ObserSchedID,LowerTrigger,UpperTrigger,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class RangeAccrualFloatersCoupon and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0F""coupon nominal."),
            TempStrNoSize("\x0D""payment Date."),
            TempStrNoSize("\x16""underlying ibor index."),
            TempStrNoSize("\x0B""start Date."),
            TempStrNoSize("\x09""end Date."),
            TempStrNoSize("\x0B""fixingDays."),
            TempStrNoSize("\x0C""day counter."),
            TempStrNoSize("\x09""gearings."),
            TempStrNoSize("\x08""spreads."),
            TempStrNoSize("\x0F""refPeriodStart."),
            TempStrNoSize("\x0D""refPeriodEnd."),
            TempStrNoSize("\x16""observations schedule."),
            TempStrNoSize("\x0D""lowerTrigger."),
            TempStrNoSize("\x0D""upperTrigger."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponEndDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponEndDate"),
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
            TempStrNoSize("\x1C""Return the accrual end Date."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponFromLeg"),
            // parameter codes
            TempStrNoSize("\x08""CCCNPPL#"),
            // function display name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponFromLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,RangeAccrualLeg,Position,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class RangeAccrualFloatersCoupon and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""range accrual leg object ID."),
            TempStrNoSize("\x09""position."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlRangeAccrualFloatersCouponObservationDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlRangeAccrualFloatersCouponObservationDates"),
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
            TempStrNoSize("\x1D""Return the observation Dates."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlRangeAccrualFloatersCouponObservationsNo"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x2A""qlRangeAccrualFloatersCouponObservationsNo"),
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
            TempStrNoSize("\x1F""Return the observations number."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlRangeAccrualFloatersCouponSetPricer"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x25""qlRangeAccrualFloatersCouponSetPricer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x23""ObjectId,RangeAccrualPricer,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""Set the coupon pricer at the given coupon object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x25""RangeAccrual coupon pricer object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlRangeAccrualFloatersCouponStarDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x24""qlRangeAccrualFloatersCouponStarDate"),
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
            TempStrNoSize("\x1E""Return the accrual start Date."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlRangeAccrualFloatersPrice"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x1B""qlRangeAccrualFloatersPrice"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,YieldCurve,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""return the price of Range Accrual Floater Coupon."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x0C""yield curve."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlRangeAccrualPricerByBgm"),
            // parameter codes
            TempStrNoSize("\x0B""CCECCLLPPL#"),
            // function display name
            TempStrNoSize("\x19""qlRangeAccrualPricerByBgm"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6B""ObjectId,Correlation,SmileOnStartDateID,SmileOnEndDateID,WithSmile,ByCallSpread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class RangeAccrualPricerByBgm and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""correlation."),
            TempStrNoSize("\x25""ID of the smile on start date object."),
            TempStrNoSize("\x23""ID of the smile on end date object."),
            TempStrNoSize("\x0C""with Smile?."),
            TempStrNoSize("\x1B""replicated by Call spread?."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSimpleFloaterPrice"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x14""qlSimpleFloaterPrice"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,YieldCurve,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2A""return the price of Simple Floater Coupon."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x0C""yield curve."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Rangeaccrual with Excel

void unregisterRangeaccrual(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlRangeAccrualFloatersCoupon"),
            // parameter codes
            TempStrNoSize("\x14""CCEPCPPNCEEPPCEEPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlRangeAccrualFloatersCoupon"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xBE""ObjectId,Nominal,PaymentDate,IborIndex,StartDate,EndDate,FixingDays,DayCountID,Gearings,Spreads,RefPeriodStart,RefPeriodEnd,ObserSchedID,LowerTrigger,UpperTrigger,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class RangeAccrualFloatersCoupon and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0F""coupon nominal."),
            TempStrNoSize("\x0D""payment Date."),
            TempStrNoSize("\x16""underlying ibor index."),
            TempStrNoSize("\x0B""start Date."),
            TempStrNoSize("\x09""end Date."),
            TempStrNoSize("\x0B""fixingDays."),
            TempStrNoSize("\x0C""day counter."),
            TempStrNoSize("\x09""gearings."),
            TempStrNoSize("\x08""spreads."),
            TempStrNoSize("\x0F""refPeriodStart."),
            TempStrNoSize("\x0D""refPeriodEnd."),
            TempStrNoSize("\x16""observations schedule."),
            TempStrNoSize("\x0D""lowerTrigger."),
            TempStrNoSize("\x0D""upperTrigger."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlRangeAccrualFloatersCoupon"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponEndDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponEndDate"),
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
            TempStrNoSize("\x1C""Return the accrual end Date."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponEndDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponFromLeg"),
            // parameter codes
            TempStrNoSize("\x08""CCCNPPL#"),
            // function display name
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponFromLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,RangeAccrualLeg,Position,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Construct an object of class RangeAccrualFloatersCoupon and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1C""range accrual leg object ID."),
            TempStrNoSize("\x09""position."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlRangeAccrualFloatersCouponFromLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlRangeAccrualFloatersCouponObservationDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlRangeAccrualFloatersCouponObservationDates"),
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
            TempStrNoSize("\x1D""Return the observation Dates."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlRangeAccrualFloatersCouponObservationDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlRangeAccrualFloatersCouponObservationsNo"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x2A""qlRangeAccrualFloatersCouponObservationsNo"),
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
            TempStrNoSize("\x1F""Return the observations number."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlRangeAccrualFloatersCouponObservationsNo"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlRangeAccrualFloatersCouponSetPricer"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x25""qlRangeAccrualFloatersCouponSetPricer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x23""ObjectId,RangeAccrualPricer,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""Set the coupon pricer at the given coupon object."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x25""RangeAccrual coupon pricer object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlRangeAccrualFloatersCouponSetPricer"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlRangeAccrualFloatersCouponStarDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x24""qlRangeAccrualFloatersCouponStarDate"),
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
            TempStrNoSize("\x1E""Return the accrual start Date."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlRangeAccrualFloatersCouponStarDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlRangeAccrualFloatersPrice"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x1B""qlRangeAccrualFloatersPrice"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,YieldCurve,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""return the price of Range Accrual Floater Coupon."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x0C""yield curve."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlRangeAccrualFloatersPrice"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlRangeAccrualPricerByBgm"),
            // parameter codes
            TempStrNoSize("\x0B""CCECCLLPPL#"),
            // function display name
            TempStrNoSize("\x19""qlRangeAccrualPricerByBgm"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6B""ObjectId,Correlation,SmileOnStartDateID,SmileOnEndDateID,WithSmile,ByCallSpread,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class RangeAccrualPricerByBgm and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0C""correlation."),
            TempStrNoSize("\x25""ID of the smile on start date object."),
            TempStrNoSize("\x23""ID of the smile on end date object."),
            TempStrNoSize("\x0C""with Smile?."),
            TempStrNoSize("\x1B""replicated by Call spread?."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlRangeAccrualPricerByBgm"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSimpleFloaterPrice"),
            // parameter codes
            TempStrNoSize("\x05""ECCP#"),
            // function display name
            TempStrNoSize("\x14""qlSimpleFloaterPrice"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,YieldCurve,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2A""return the price of Simple Floater Coupon."),
            // parameter descriptions
            TempStrNoSize("\x3A""id of existing QuantLib::RangeAccrualFloatersCoupon object"),
            TempStrNoSize("\x0C""yield curve."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlSimpleFloaterPrice"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

