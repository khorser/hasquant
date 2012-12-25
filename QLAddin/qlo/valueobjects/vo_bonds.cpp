
/*  
 Copyright (C) 2005, 2006 Plamen Neykov
 Copyright (C) 2007 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.vo.includes.body

#include <oh/ohdefines.hpp>
#include <qlo/bonds.hpp>
#include <qlo/valueobjects/vo_bonds.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBond::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "Currency",
        "SettlementDays",
        "Calendar",
        "FaceAmount",
        "MaturityDate",
        "IssueDate",
        "LegID",
        "Permanent"
    };

    std::set<std::string> qlBond::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBond::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBond::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBond::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            return FaceAmount_;
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            return MaturityDate_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "LEGID")==0)
            return LegID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBond::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            FaceAmount_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            MaturityDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "LEGID")==0)
            LegID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBond::qlBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& Calendar,
            double FaceAmount,
            const ObjectHandler::property_t& MaturityDate,
            const ObjectHandler::property_t& IssueDate,
            const std::string& LegID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBond", Permanent),
        Description_(Description),
        Currency_(Currency),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        FaceAmount_(FaceAmount),
        MaturityDate_(MaturityDate),
        IssueDate_(IssueDate),
        LegID_(LegID),
        Permanent_(Permanent) {
                  
            processPrecedentID(LegID);
            
    }

    const char* qlCmsRateBond::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "Currency",
        "SettlementDays",
        "PaymentBDC",
        "FaceAmount",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Floors",
        "Gearings",
        "SwapIndex",
        "Spreads",
        "Caps",
        "Redemption",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlCmsRateBond::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCmsRateBond::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCmsRateBond::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCmsRateBond::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            return FaceAmount_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            return IsInArrears_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "FLOORS")==0)
            return Floors_;
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            return Gearings_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            return SwapIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            return Spreads_;
        else if(strcmp(nameUpper.c_str(), "CAPS")==0)
            return Caps_;
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            return Redemption_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCmsRateBond::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            FaceAmount_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            IsInArrears_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FLOORS")==0)
            Floors_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            Gearings_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            SwapIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            Spreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CAPS")==0)
            Caps_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            Redemption_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCmsRateBond::qlCmsRateBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& PaymentBDC,
            double FaceAmount,
            const std::string& ScheduleID,
            long FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCmsRateBond", Permanent),
        Description_(Description),
        Currency_(Currency),
        SettlementDays_(SettlementDays),
        PaymentBDC_(PaymentBDC),
        FaceAmount_(FaceAmount),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Floors_(Floors),
        Gearings_(Gearings),
        SwapIndex_(SwapIndex),
        Spreads_(Spreads),
        Caps_(Caps),
        Redemption_(Redemption),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(SwapIndex);
            
    }

    const char* qlFixedRateBond::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "Currency",
        "SettlementDays",
        "FaceAmount",
        "ScheduleID",
        "Coupons",
        "DayCounter",
        "PaymentBDC",
        "Redemption",
        "IssueDate",
        "PaymentCalendar",
        "Permanent"
    };

    std::set<std::string> qlFixedRateBond::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFixedRateBond::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFixedRateBond::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFixedRateBond::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            return FaceAmount_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            return Coupons_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            return Redemption_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCALENDAR")==0)
            return PaymentCalendar_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFixedRateBond::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            FaceAmount_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            Coupons_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            Redemption_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCALENDAR")==0)
            PaymentCalendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFixedRateBond::qlFixedRateBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            double FaceAmount,
            const std::string& ScheduleID,
            const std::vector<double>& Coupons,
            const std::string& DayCounter,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            const std::string& PaymentCalendar,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFixedRateBond", Permanent),
        Description_(Description),
        Currency_(Currency),
        SettlementDays_(SettlementDays),
        FaceAmount_(FaceAmount),
        ScheduleID_(ScheduleID),
        Coupons_(Coupons),
        DayCounter_(DayCounter),
        PaymentBDC_(PaymentBDC),
        Redemption_(Redemption),
        IssueDate_(IssueDate),
        PaymentCalendar_(PaymentCalendar),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            
    }

    const char* qlFixedRateBond2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "Currency",
        "SettlementDays",
        "FaceAmount",
        "ScheduleID",
        "Coupons",
        "PaymentBDC",
        "Redemption",
        "IssueDate",
        "PaymentCalendar",
        "Permanent"
    };

    std::set<std::string> qlFixedRateBond2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFixedRateBond2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFixedRateBond2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFixedRateBond2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            return FaceAmount_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            return Coupons_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            return Redemption_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCALENDAR")==0)
            return PaymentCalendar_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFixedRateBond2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            FaceAmount_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            Coupons_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            Redemption_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCALENDAR")==0)
            PaymentCalendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFixedRateBond2::qlFixedRateBond2(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            double FaceAmount,
            const std::string& ScheduleID,
            const std::vector<std::string>& Coupons,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            const std::string& PaymentCalendar,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFixedRateBond2", Permanent),
        Description_(Description),
        Currency_(Currency),
        SettlementDays_(SettlementDays),
        FaceAmount_(FaceAmount),
        ScheduleID_(ScheduleID),
        Coupons_(Coupons),
        PaymentBDC_(PaymentBDC),
        Redemption_(Redemption),
        IssueDate_(IssueDate),
        PaymentCalendar_(PaymentCalendar),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            for (std::vector<std::string>::const_iterator i = Coupons.begin();
                    i != Coupons.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlFloatingRateBond::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "Currency",
        "SettlementDays",
        "PaymentBDC",
        "FaceAmount",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Floors",
        "Gearings",
        "IborIndex",
        "Spreads",
        "Caps",
        "Redemption",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlFloatingRateBond::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFloatingRateBond::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFloatingRateBond::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFloatingRateBond::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            return FaceAmount_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            return IsInArrears_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "FLOORS")==0)
            return Floors_;
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            return Gearings_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            return Spreads_;
        else if(strcmp(nameUpper.c_str(), "CAPS")==0)
            return Caps_;
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            return Redemption_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFloatingRateBond::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            FaceAmount_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            IsInArrears_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FLOORS")==0)
            Floors_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            Gearings_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            Spreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CAPS")==0)
            Caps_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            Redemption_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFloatingRateBond::qlFloatingRateBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& PaymentBDC,
            double FaceAmount,
            const std::string& ScheduleID,
            long FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFloatingRateBond", Permanent),
        Description_(Description),
        Currency_(Currency),
        SettlementDays_(SettlementDays),
        PaymentBDC_(PaymentBDC),
        FaceAmount_(FaceAmount),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Floors_(Floors),
        Gearings_(Gearings),
        IborIndex_(IborIndex),
        Spreads_(Spreads),
        Caps_(Caps),
        Redemption_(Redemption),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(IborIndex);
            
    }

    const char* qlZeroCouponBond::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "Currency",
        "SettlementDays",
        "Calendar",
        "FaceAmount",
        "Maturity",
        "PaymentBDC",
        "Redemption",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlZeroCouponBond::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlZeroCouponBond::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlZeroCouponBond::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlZeroCouponBond::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            return FaceAmount_;
        else if(strcmp(nameUpper.c_str(), "MATURITY")==0)
            return Maturity_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            return Redemption_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlZeroCouponBond::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACEAMOUNT")==0)
            FaceAmount_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "MATURITY")==0)
            Maturity_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            Redemption_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlZeroCouponBond::qlZeroCouponBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& Calendar,
            double FaceAmount,
            const ObjectHandler::property_t& Maturity,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlZeroCouponBond", Permanent),
        Description_(Description),
        Currency_(Currency),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        FaceAmount_(FaceAmount),
        Maturity_(Maturity),
        PaymentBDC_(PaymentBDC),
        Redemption_(Redemption),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  

            
    }

 } }
