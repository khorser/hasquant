
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
#include <qlo/rangeaccrual.hpp>
#include <qlo/valueobjects/vo_rangeaccrual.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlRangeAccrualFloatersCoupon::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Nominal",
        "PaymentDate",
        "IborIndex",
        "StartDate",
        "EndDate",
        "FixingDays",
        "DayCountID",
        "Gearings",
        "Spreads",
        "RefPeriodStart",
        "RefPeriodEnd",
        "ObserSchedID",
        "LowerTrigger",
        "UpperTrigger",
        "Permanent"
    };

    std::set<std::string> qlRangeAccrualFloatersCoupon::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRangeAccrualFloatersCoupon::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRangeAccrualFloatersCoupon::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRangeAccrualFloatersCoupon::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "NOMINAL")==0)
            return Nominal_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTDATE")==0)
            return PaymentDate_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            return EndDate_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTID")==0)
            return DayCountID_;
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            return Gearings_;
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            return Spreads_;
        else if(strcmp(nameUpper.c_str(), "REFPERIODSTART")==0)
            return RefPeriodStart_;
        else if(strcmp(nameUpper.c_str(), "REFPERIODEND")==0)
            return RefPeriodEnd_;
        else if(strcmp(nameUpper.c_str(), "OBSERSCHEDID")==0)
            return ObserSchedID_;
        else if(strcmp(nameUpper.c_str(), "LOWERTRIGGER")==0)
            return LowerTrigger_;
        else if(strcmp(nameUpper.c_str(), "UPPERTRIGGER")==0)
            return UpperTrigger_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRangeAccrualFloatersCoupon::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINAL")==0)
            Nominal_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTDATE")==0)
            PaymentDate_ = value;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            EndDate_ = value;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTID")==0)
            DayCountID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            Gearings_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            Spreads_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "REFPERIODSTART")==0)
            RefPeriodStart_ = value;
        else if(strcmp(nameUpper.c_str(), "REFPERIODEND")==0)
            RefPeriodEnd_ = value;
        else if(strcmp(nameUpper.c_str(), "OBSERSCHEDID")==0)
            ObserSchedID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LOWERTRIGGER")==0)
            LowerTrigger_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "UPPERTRIGGER")==0)
            UpperTrigger_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRangeAccrualFloatersCoupon::qlRangeAccrualFloatersCoupon(
            const std::string& ObjectId,
            double Nominal,
            const ObjectHandler::property_t& PaymentDate,
            const std::string& IborIndex,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            long FixingDays,
            const std::string& DayCountID,
            double Gearings,
            double Spreads,
            const ObjectHandler::property_t& RefPeriodStart,
            const ObjectHandler::property_t& RefPeriodEnd,
            const std::string& ObserSchedID,
            double LowerTrigger,
            double UpperTrigger,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRangeAccrualFloatersCoupon", Permanent),
        Nominal_(Nominal),
        PaymentDate_(PaymentDate),
        IborIndex_(IborIndex),
        StartDate_(StartDate),
        EndDate_(EndDate),
        FixingDays_(FixingDays),
        DayCountID_(DayCountID),
        Gearings_(Gearings),
        Spreads_(Spreads),
        RefPeriodStart_(RefPeriodStart),
        RefPeriodEnd_(RefPeriodEnd),
        ObserSchedID_(ObserSchedID),
        LowerTrigger_(LowerTrigger),
        UpperTrigger_(UpperTrigger),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processPrecedentID(ObserSchedID);
            
    }

    const char* qlRangeAccrualFloatersCouponFromLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RangeAccrualLeg",
        "Position",
        "Permanent"
    };

    std::set<std::string> qlRangeAccrualFloatersCouponFromLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRangeAccrualFloatersCouponFromLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRangeAccrualFloatersCouponFromLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRangeAccrualFloatersCouponFromLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RANGEACCRUALLEG")==0)
            return RangeAccrualLeg_;
        else if(strcmp(nameUpper.c_str(), "POSITION")==0)
            return Position_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRangeAccrualFloatersCouponFromLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RANGEACCRUALLEG")==0)
            RangeAccrualLeg_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "POSITION")==0)
            Position_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRangeAccrualFloatersCouponFromLeg::qlRangeAccrualFloatersCouponFromLeg(
            const std::string& ObjectId,
            const std::string& RangeAccrualLeg,
            long Position,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRangeAccrualFloatersCouponFromLeg", Permanent),
        RangeAccrualLeg_(RangeAccrualLeg),
        Position_(Position),
        Permanent_(Permanent) {
                  
            processPrecedentID(RangeAccrualLeg);
            
    }

    const char* qlRangeAccrualPricerByBgm::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Correlation",
        "SmileOnStartDateID",
        "SmileOnEndDateID",
        "WithSmile",
        "ByCallSpread",
        "Permanent"
    };

    std::set<std::string> qlRangeAccrualPricerByBgm::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRangeAccrualPricerByBgm::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRangeAccrualPricerByBgm::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRangeAccrualPricerByBgm::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            return Correlation_;
        else if(strcmp(nameUpper.c_str(), "SMILEONSTARTDATEID")==0)
            return SmileOnStartDateID_;
        else if(strcmp(nameUpper.c_str(), "SMILEONENDDATEID")==0)
            return SmileOnEndDateID_;
        else if(strcmp(nameUpper.c_str(), "WITHSMILE")==0)
            return WithSmile_;
        else if(strcmp(nameUpper.c_str(), "BYCALLSPREAD")==0)
            return ByCallSpread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRangeAccrualPricerByBgm::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            Correlation_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SMILEONSTARTDATEID")==0)
            SmileOnStartDateID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SMILEONENDDATEID")==0)
            SmileOnEndDateID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "WITHSMILE")==0)
            WithSmile_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BYCALLSPREAD")==0)
            ByCallSpread_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRangeAccrualPricerByBgm::qlRangeAccrualPricerByBgm(
            const std::string& ObjectId,
            double Correlation,
            const std::string& SmileOnStartDateID,
            const std::string& SmileOnEndDateID,
            bool WithSmile,
            bool ByCallSpread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRangeAccrualPricerByBgm", Permanent),
        Correlation_(Correlation),
        SmileOnStartDateID_(SmileOnStartDateID),
        SmileOnEndDateID_(SmileOnEndDateID),
        WithSmile_(WithSmile),
        ByCallSpread_(ByCallSpread),
        Permanent_(Permanent) {
                  
            processPrecedentID(SmileOnStartDateID);
            processPrecedentID(SmileOnEndDateID);
            
    }

 } }
