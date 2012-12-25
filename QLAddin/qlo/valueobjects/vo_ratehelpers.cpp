
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
#include <qlo/ratehelpers.hpp>
#include <qlo/valueobjects/vo_ratehelpers.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBondHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CleanPrice",
        "Bond",
        "Permanent"
    };

    std::set<std::string> qlBondHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBondHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBondHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBondHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            return CleanPrice_;
        else if(strcmp(nameUpper.c_str(), "BOND")==0)
            return Bond_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBondHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            CleanPrice_ = value;
        else if(strcmp(nameUpper.c_str(), "BOND")==0)
            Bond_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBondHelper::qlBondHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& CleanPrice,
            const std::string& Bond,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBondHelper", Permanent),
        CleanPrice_(CleanPrice),
        Bond_(Bond),
        Permanent_(Permanent) {
                  
            processVariant(CleanPrice);
            processPrecedentID(Bond);
            
    }

    const char* qlDatedOISRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "StartDate",
        "EndDate",
        "FixedRate",
        "ONIndex",
        "Permanent"
    };

    std::set<std::string> qlDatedOISRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDatedOISRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDatedOISRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDatedOISRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            return EndDate_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "ONINDEX")==0)
            return ONIndex_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDatedOISRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            EndDate_ = value;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = value;
        else if(strcmp(nameUpper.c_str(), "ONINDEX")==0)
            ONIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDatedOISRateHelper::qlDatedOISRateHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const ObjectHandler::property_t& FixedRate,
            const std::string& ONIndex,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDatedOISRateHelper", Permanent),
        StartDate_(StartDate),
        EndDate_(EndDate),
        FixedRate_(FixedRate),
        ONIndex_(ONIndex),
        Permanent_(Permanent) {
                  
            processVariant(FixedRate);
            processPrecedentID(ONIndex);
            
    }

    const char* qlDepositRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "IborIndex",
        "Permanent"
    };

    std::set<std::string> qlDepositRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDepositRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDepositRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDepositRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDepositRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDepositRateHelper::qlDepositRateHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Rate,
            const std::string& IborIndex,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDepositRateHelper", Permanent),
        Rate_(Rate),
        IborIndex_(IborIndex),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            processPrecedentID(IborIndex);
            
    }

    const char* qlDepositRateHelper2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "Tenor",
        "FixingDays",
        "Calendar",
        "Convention",
        "EndOfMonth",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlDepositRateHelper2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDepositRateHelper2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDepositRateHelper2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDepositRateHelper2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            return Convention_;
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            return EndOfMonth_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDepositRateHelper2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            Convention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            EndOfMonth_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDepositRateHelper2::qlDepositRateHelper2(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Rate,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Calendar,
            const std::string& Convention,
            bool EndOfMonth,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDepositRateHelper2", Permanent),
        Rate_(Rate),
        Tenor_(Tenor),
        FixingDays_(FixingDays),
        Calendar_(Calendar),
        Convention_(Convention),
        EndOfMonth_(EndOfMonth),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            
    }

    const char* qlFixedRateBondHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CleanPrice",
        "SettlementDays",
        "FaceAmount",
        "ScheduleID",
        "Coupons",
        "DayCounter",
        "PaymentBDC",
        "Redemption",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlFixedRateBondHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFixedRateBondHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFixedRateBondHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFixedRateBondHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            return CleanPrice_;
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFixedRateBondHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            CleanPrice_ = value;
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFixedRateBondHelper::qlFixedRateBondHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& CleanPrice,
            long SettlementDays,
            double FaceAmount,
            const std::string& ScheduleID,
            const std::vector<double>& Coupons,
            const std::string& DayCounter,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFixedRateBondHelper", Permanent),
        CleanPrice_(CleanPrice),
        SettlementDays_(SettlementDays),
        FaceAmount_(FaceAmount),
        ScheduleID_(ScheduleID),
        Coupons_(Coupons),
        DayCounter_(DayCounter),
        PaymentBDC_(PaymentBDC),
        Redemption_(Redemption),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  
            processVariant(CleanPrice);
            processPrecedentID(ScheduleID);
            
    }

    const char* qlFraRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "PeriodToStart",
        "IborIndex",
        "Permanent"
    };

    std::set<std::string> qlFraRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFraRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFraRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFraRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "PERIODTOSTART")==0)
            return PeriodToStart_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFraRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERIODTOSTART")==0)
            PeriodToStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFraRateHelper::qlFraRateHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Rate,
            const std::string& PeriodToStart,
            const std::string& IborIndex,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFraRateHelper", Permanent),
        Rate_(Rate),
        PeriodToStart_(PeriodToStart),
        IborIndex_(IborIndex),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            processPrecedentID(IborIndex);
            
    }

    const char* qlFraRateHelper2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "PeriodToStart",
        "LengthInMonths",
        "FixingDays",
        "Calendar",
        "Convention",
        "EndOfMonth",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlFraRateHelper2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFraRateHelper2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFraRateHelper2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFraRateHelper2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "PERIODTOSTART")==0)
            return PeriodToStart_;
        else if(strcmp(nameUpper.c_str(), "LENGTHINMONTHS")==0)
            return LengthInMonths_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            return Convention_;
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            return EndOfMonth_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFraRateHelper2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERIODTOSTART")==0)
            PeriodToStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LENGTHINMONTHS")==0)
            LengthInMonths_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            Convention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            EndOfMonth_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFraRateHelper2::qlFraRateHelper2(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Rate,
            const std::string& PeriodToStart,
            long LengthInMonths,
            long FixingDays,
            const std::string& Calendar,
            const std::string& Convention,
            bool EndOfMonth,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFraRateHelper2", Permanent),
        Rate_(Rate),
        PeriodToStart_(PeriodToStart),
        LengthInMonths_(LengthInMonths),
        FixingDays_(FixingDays),
        Calendar_(Calendar),
        Convention_(Convention),
        EndOfMonth_(EndOfMonth),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            
    }

    const char* qlFuturesRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Price",
        "IMM",
        "IborIndex",
        "ConvexityAdjQuote",
        "Permanent"
    };

    std::set<std::string> qlFuturesRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFuturesRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFuturesRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFuturesRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PRICE")==0)
            return Price_;
        else if(strcmp(nameUpper.c_str(), "IMM")==0)
            return IMM_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "CONVEXITYADJQUOTE")==0)
            return ConvexityAdjQuote_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFuturesRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PRICE")==0)
            Price_ = value;
        else if(strcmp(nameUpper.c_str(), "IMM")==0)
            IMM_ = value;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVEXITYADJQUOTE")==0)
            ConvexityAdjQuote_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFuturesRateHelper::qlFuturesRateHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Price,
            const ObjectHandler::property_t& IMM,
            const std::string& IborIndex,
            const ObjectHandler::property_t& ConvexityAdjQuote,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFuturesRateHelper", Permanent),
        Price_(Price),
        IMM_(IMM),
        IborIndex_(IborIndex),
        ConvexityAdjQuote_(ConvexityAdjQuote),
        Permanent_(Permanent) {
                  
            processVariant(Price);
            processPrecedentID(IborIndex);
            processVariant(ConvexityAdjQuote);
            
    }

    const char* qlFuturesRateHelper2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Price",
        "IMM",
        "LengthInMonths",
        "Calendar",
        "Convention",
        "EndOfMonth",
        "DayCounter",
        "ConvexityAdjQuote",
        "Permanent"
    };

    std::set<std::string> qlFuturesRateHelper2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFuturesRateHelper2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFuturesRateHelper2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFuturesRateHelper2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PRICE")==0)
            return Price_;
        else if(strcmp(nameUpper.c_str(), "IMM")==0)
            return IMM_;
        else if(strcmp(nameUpper.c_str(), "LENGTHINMONTHS")==0)
            return LengthInMonths_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            return Convention_;
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            return EndOfMonth_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "CONVEXITYADJQUOTE")==0)
            return ConvexityAdjQuote_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFuturesRateHelper2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PRICE")==0)
            Price_ = value;
        else if(strcmp(nameUpper.c_str(), "IMM")==0)
            IMM_ = value;
        else if(strcmp(nameUpper.c_str(), "LENGTHINMONTHS")==0)
            LengthInMonths_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            Convention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            EndOfMonth_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVEXITYADJQUOTE")==0)
            ConvexityAdjQuote_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFuturesRateHelper2::qlFuturesRateHelper2(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Price,
            const ObjectHandler::property_t& IMM,
            long LengthInMonths,
            const std::string& Calendar,
            const std::string& Convention,
            bool EndOfMonth,
            const std::string& DayCounter,
            const ObjectHandler::property_t& ConvexityAdjQuote,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFuturesRateHelper2", Permanent),
        Price_(Price),
        IMM_(IMM),
        LengthInMonths_(LengthInMonths),
        Calendar_(Calendar),
        Convention_(Convention),
        EndOfMonth_(EndOfMonth),
        DayCounter_(DayCounter),
        ConvexityAdjQuote_(ConvexityAdjQuote),
        Permanent_(Permanent) {
                  
            processVariant(Price);
            processVariant(ConvexityAdjQuote);
            
    }

    const char* qlFuturesRateHelper3::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Price",
        "IMM",
        "EndDate",
        "DayCounter",
        "ConvexityAdjQuote",
        "Permanent"
    };

    std::set<std::string> qlFuturesRateHelper3::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFuturesRateHelper3::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFuturesRateHelper3::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFuturesRateHelper3::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PRICE")==0)
            return Price_;
        else if(strcmp(nameUpper.c_str(), "IMM")==0)
            return IMM_;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            return EndDate_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "CONVEXITYADJQUOTE")==0)
            return ConvexityAdjQuote_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFuturesRateHelper3::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PRICE")==0)
            Price_ = value;
        else if(strcmp(nameUpper.c_str(), "IMM")==0)
            IMM_ = value;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            EndDate_ = value;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVEXITYADJQUOTE")==0)
            ConvexityAdjQuote_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFuturesRateHelper3::qlFuturesRateHelper3(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Price,
            const ObjectHandler::property_t& IMM,
            const ObjectHandler::property_t& EndDate,
            const std::string& DayCounter,
            const ObjectHandler::property_t& ConvexityAdjQuote,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFuturesRateHelper3", Permanent),
        Price_(Price),
        IMM_(IMM),
        EndDate_(EndDate),
        DayCounter_(DayCounter),
        ConvexityAdjQuote_(ConvexityAdjQuote),
        Permanent_(Permanent) {
                  
            processVariant(Price);
            processVariant(ConvexityAdjQuote);
            
    }

    const char* qlOISRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlDays",
        "Tenor",
        "FixedRate",
        "ONIndex",
        "Permanent"
    };

    std::set<std::string> qlOISRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlOISRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlOISRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlOISRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLDAYS")==0)
            return SettlDays_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "ONINDEX")==0)
            return ONIndex_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlOISRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLDAYS")==0)
            SettlDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = value;
        else if(strcmp(nameUpper.c_str(), "ONINDEX")==0)
            ONIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlOISRateHelper::qlOISRateHelper(
            const std::string& ObjectId,
            long SettlDays,
            const std::string& Tenor,
            const ObjectHandler::property_t& FixedRate,
            const std::string& ONIndex,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlOISRateHelper", Permanent),
        SettlDays_(SettlDays),
        Tenor_(Tenor),
        FixedRate_(FixedRate),
        ONIndex_(ONIndex),
        Permanent_(Permanent) {
                  
            processVariant(FixedRate);
            processPrecedentID(ONIndex);
            
    }

    const char* qlSwapRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "SwapIndex",
        "Spread",
        "ForwardStart",
        "DiscountingCurve",
        "Permanent"
    };

    std::set<std::string> qlSwapRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwapRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwapRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwapRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            return SwapIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            return ForwardStart_;
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            return DiscountingCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwapRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            SwapIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = value;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            ForwardStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            DiscountingCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwapRateHelper::qlSwapRateHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Rate,
            const std::string& SwapIndex,
            const ObjectHandler::property_t& Spread,
            const std::string& ForwardStart,
            const std::string& DiscountingCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwapRateHelper", Permanent),
        Rate_(Rate),
        SwapIndex_(SwapIndex),
        Spread_(Spread),
        ForwardStart_(ForwardStart),
        DiscountingCurve_(DiscountingCurve),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            processPrecedentID(SwapIndex);
            processVariant(Spread);
            processPrecedentID(DiscountingCurve);
            
    }

    const char* qlSwapRateHelper2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "Tenor",
        "Calendar",
        "FixedLegFrequency",
        "FixedLegConvention",
        "FixedLegDayCounter",
        "IborIndex",
        "Spread",
        "ForwardStart",
        "DiscountingCurve",
        "Permanent"
    };

    std::set<std::string> qlSwapRateHelper2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwapRateHelper2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwapRateHelper2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwapRateHelper2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGFREQUENCY")==0)
            return FixedLegFrequency_;
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGCONVENTION")==0)
            return FixedLegConvention_;
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGDAYCOUNTER")==0)
            return FixedLegDayCounter_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            return ForwardStart_;
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            return DiscountingCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwapRateHelper2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGFREQUENCY")==0)
            FixedLegFrequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGCONVENTION")==0)
            FixedLegConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGDAYCOUNTER")==0)
            FixedLegDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = value;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            ForwardStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            DiscountingCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwapRateHelper2::qlSwapRateHelper2(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Rate,
            const std::string& Tenor,
            const std::string& Calendar,
            const std::string& FixedLegFrequency,
            const std::string& FixedLegConvention,
            const std::string& FixedLegDayCounter,
            const std::string& IborIndex,
            const ObjectHandler::property_t& Spread,
            const std::string& ForwardStart,
            const std::string& DiscountingCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwapRateHelper2", Permanent),
        Rate_(Rate),
        Tenor_(Tenor),
        Calendar_(Calendar),
        FixedLegFrequency_(FixedLegFrequency),
        FixedLegConvention_(FixedLegConvention),
        FixedLegDayCounter_(FixedLegDayCounter),
        IborIndex_(IborIndex),
        Spread_(Spread),
        ForwardStart_(ForwardStart),
        DiscountingCurve_(DiscountingCurve),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            processPrecedentID(IborIndex);
            processVariant(Spread);
            processPrecedentID(DiscountingCurve);
            
    }

 } }
