
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
#include <qlo/couponvectors.hpp>
#include <qlo/valueobjects/vo_couponvectors.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCmsCouponPricer::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Volatility",
        "CmsCouponPricerType",
        "YieldCurveModel",
        "MeanReversion",
        "Permanent"
    };

    std::set<std::string> qlCmsCouponPricer::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCmsCouponPricer::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCmsCouponPricer::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCmsCouponPricer::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            return Volatility_;
        else if(strcmp(nameUpper.c_str(), "CMSCOUPONPRICERTYPE")==0)
            return CmsCouponPricerType_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVEMODEL")==0)
            return YieldCurveModel_;
        else if(strcmp(nameUpper.c_str(), "MEANREVERSION")==0)
            return MeanReversion_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCmsCouponPricer::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            Volatility_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CMSCOUPONPRICERTYPE")==0)
            CmsCouponPricerType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVEMODEL")==0)
            YieldCurveModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MEANREVERSION")==0)
            MeanReversion_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCmsCouponPricer::qlCmsCouponPricer(
            const std::string& ObjectId,
            const std::string& Volatility,
            const std::string& CmsCouponPricerType,
            const std::string& YieldCurveModel,
            const ObjectHandler::property_t& MeanReversion,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCmsCouponPricer", Permanent),
        Volatility_(Volatility),
        CmsCouponPricerType_(CmsCouponPricerType),
        YieldCurveModel_(YieldCurveModel),
        MeanReversion_(MeanReversion),
        Permanent_(Permanent) {
                  
            processPrecedentID(Volatility);
            processVariant(MeanReversion);
            
    }

    const char* qlCmsLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Floors",
        "Gearings",
        "SwapIndex",
        "Spreads",
        "Caps",
        "Permanent"
    };

    std::set<std::string> qlCmsLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCmsLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCmsLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCmsLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCmsLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCmsLeg::qlCmsLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCmsLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Floors_(Floors),
        Gearings_(Gearings),
        SwapIndex_(SwapIndex),
        Spreads_(Spreads),
        Caps_(Caps),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(SwapIndex);
            
    }

    const char* qlCmsZeroLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Floors",
        "Gearings",
        "SwapIndex",
        "Spreads",
        "Caps",
        "Permanent"
    };

    std::set<std::string> qlCmsZeroLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCmsZeroLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCmsZeroLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCmsZeroLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCmsZeroLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCmsZeroLeg::qlCmsZeroLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCmsZeroLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Floors_(Floors),
        Gearings_(Gearings),
        SwapIndex_(SwapIndex),
        Spreads_(Spreads),
        Caps_(Caps),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(SwapIndex);
            
    }

    const char* qlConundrumPricerByNumericalIntegration::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwaptionVol",
        "YieldCurveModel",
        "MeanReversion",
        "LowerLimit",
        "UpperLimit",
        "Precision",
        "Permanent"
    };

    std::set<std::string> qlConundrumPricerByNumericalIntegration::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlConundrumPricerByNumericalIntegration::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlConundrumPricerByNumericalIntegration::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlConundrumPricerByNumericalIntegration::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPTIONVOL")==0)
            return SwaptionVol_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVEMODEL")==0)
            return YieldCurveModel_;
        else if(strcmp(nameUpper.c_str(), "MEANREVERSION")==0)
            return MeanReversion_;
        else if(strcmp(nameUpper.c_str(), "LOWERLIMIT")==0)
            return LowerLimit_;
        else if(strcmp(nameUpper.c_str(), "UPPERLIMIT")==0)
            return UpperLimit_;
        else if(strcmp(nameUpper.c_str(), "PRECISION")==0)
            return Precision_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlConundrumPricerByNumericalIntegration::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPTIONVOL")==0)
            SwaptionVol_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVEMODEL")==0)
            YieldCurveModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MEANREVERSION")==0)
            MeanReversion_ = value;
        else if(strcmp(nameUpper.c_str(), "LOWERLIMIT")==0)
            LowerLimit_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "UPPERLIMIT")==0)
            UpperLimit_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PRECISION")==0)
            Precision_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlConundrumPricerByNumericalIntegration::qlConundrumPricerByNumericalIntegration(
            const std::string& ObjectId,
            const std::string& SwaptionVol,
            const std::string& YieldCurveModel,
            const ObjectHandler::property_t& MeanReversion,
            double LowerLimit,
            double UpperLimit,
            double Precision,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlConundrumPricerByNumericalIntegration", Permanent),
        SwaptionVol_(SwaptionVol),
        YieldCurveModel_(YieldCurveModel),
        MeanReversion_(MeanReversion),
        LowerLimit_(LowerLimit),
        UpperLimit_(UpperLimit),
        Precision_(Precision),
        Permanent_(Permanent) {
                  
            processPrecedentID(SwaptionVol);
            processVariant(MeanReversion);
            
    }

    const char* qlDigitalCmsLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Gearings",
        "SwapIndex",
        "Spreads",
        "CallStrikes",
        "CallSpecs",
        "CallPayoff",
        "PutStrikes",
        "PutSpecs",
        "PutPayoff",
        "Replication",
        "Permanent"
    };

    std::set<std::string> qlDigitalCmsLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDigitalCmsLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDigitalCmsLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDigitalCmsLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            return IsInArrears_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            return Gearings_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            return SwapIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            return Spreads_;
        else if(strcmp(nameUpper.c_str(), "CALLSTRIKES")==0)
            return CallStrikes_;
        else if(strcmp(nameUpper.c_str(), "CALLSPECS")==0)
            return CallSpecs_;
        else if(strcmp(nameUpper.c_str(), "CALLPAYOFF")==0)
            return CallPayoff_;
        else if(strcmp(nameUpper.c_str(), "PUTSTRIKES")==0)
            return PutStrikes_;
        else if(strcmp(nameUpper.c_str(), "PUTSPECS")==0)
            return PutSpecs_;
        else if(strcmp(nameUpper.c_str(), "PUTPAYOFF")==0)
            return PutPayoff_;
        else if(strcmp(nameUpper.c_str(), "REPLICATION")==0)
            return Replication_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDigitalCmsLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            IsInArrears_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            Gearings_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            SwapIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            Spreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CALLSTRIKES")==0)
            CallStrikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CALLSPECS")==0)
            CallSpecs_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALLPAYOFF")==0)
            CallPayoff_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PUTSTRIKES")==0)
            PutStrikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PUTSPECS")==0)
            PutSpecs_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PUTPAYOFF")==0)
            PutPayoff_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "REPLICATION")==0)
            Replication_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDigitalCmsLeg::qlDigitalCmsLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string& CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string& PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string& Replication,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDigitalCmsLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Gearings_(Gearings),
        SwapIndex_(SwapIndex),
        Spreads_(Spreads),
        CallStrikes_(CallStrikes),
        CallSpecs_(CallSpecs),
        CallPayoff_(CallPayoff),
        PutStrikes_(PutStrikes),
        PutSpecs_(PutSpecs),
        PutPayoff_(PutPayoff),
        Replication_(Replication),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(SwapIndex);
            processPrecedentID(Replication);
            
    }

    const char* qlDigitalIborLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Gearings",
        "IborIndex",
        "Spreads",
        "CallStrikes",
        "CallSpecs",
        "CallPayoff",
        "PutStrikes",
        "PutSpecs",
        "PutPayoff",
        "Replication",
        "Permanent"
    };

    std::set<std::string> qlDigitalIborLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDigitalIborLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDigitalIborLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDigitalIborLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            return IsInArrears_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            return Gearings_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            return Spreads_;
        else if(strcmp(nameUpper.c_str(), "CALLSTRIKES")==0)
            return CallStrikes_;
        else if(strcmp(nameUpper.c_str(), "CALLSPECS")==0)
            return CallSpecs_;
        else if(strcmp(nameUpper.c_str(), "CALLPAYOFF")==0)
            return CallPayoff_;
        else if(strcmp(nameUpper.c_str(), "PUTSTRIKES")==0)
            return PutStrikes_;
        else if(strcmp(nameUpper.c_str(), "PUTSPECS")==0)
            return PutSpecs_;
        else if(strcmp(nameUpper.c_str(), "PUTPAYOFF")==0)
            return PutPayoff_;
        else if(strcmp(nameUpper.c_str(), "REPLICATION")==0)
            return Replication_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDigitalIborLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ISINARREARS")==0)
            IsInArrears_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            Gearings_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            Spreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CALLSTRIKES")==0)
            CallStrikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CALLSPECS")==0)
            CallSpecs_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALLPAYOFF")==0)
            CallPayoff_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PUTSTRIKES")==0)
            PutStrikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PUTSPECS")==0)
            PutSpecs_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PUTPAYOFF")==0)
            PutPayoff_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "REPLICATION")==0)
            Replication_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDigitalIborLeg::qlDigitalIborLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string& CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string& PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string& Replication,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDigitalIborLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Gearings_(Gearings),
        IborIndex_(IborIndex),
        Spreads_(Spreads),
        CallStrikes_(CallStrikes),
        CallSpecs_(CallSpecs),
        CallPayoff_(CallPayoff),
        PutStrikes_(PutStrikes),
        PutSpecs_(PutSpecs),
        PutPayoff_(PutPayoff),
        Replication_(Replication),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(IborIndex);
            processPrecedentID(Replication);
            
    }

    const char* qlDigitalReplication::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Replication",
        "Gap",
        "Permanent"
    };

    std::set<std::string> qlDigitalReplication::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDigitalReplication::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDigitalReplication::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDigitalReplication::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "REPLICATION")==0)
            return Replication_;
        else if(strcmp(nameUpper.c_str(), "GAP")==0)
            return Gap_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDigitalReplication::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REPLICATION")==0)
            Replication_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GAP")==0)
            Gap_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDigitalReplication::qlDigitalReplication(
            const std::string& ObjectId,
            const std::string& Replication,
            double Gap,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDigitalReplication", Permanent),
        Replication_(Replication),
        Gap_(Gap),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlFixedRateLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "Coupons",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlFixedRateLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFixedRateLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFixedRateLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFixedRateLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            return Coupons_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFixedRateLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            Coupons_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFixedRateLeg::qlFixedRateLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<double>& Coupons,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFixedRateLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        Coupons_(Coupons),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            
    }

    const char* qlFixedRateLeg2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "Coupons",
        "Permanent"
    };

    std::set<std::string> qlFixedRateLeg2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFixedRateLeg2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFixedRateLeg2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFixedRateLeg2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            return Coupons_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFixedRateLeg2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COUPONS")==0)
            Coupons_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFixedRateLeg2::qlFixedRateLeg2(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<std::string>& Coupons,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFixedRateLeg2", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        Coupons_(Coupons),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            for (std::vector<std::string>::const_iterator i = Coupons.begin();
                    i != Coupons.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlIborCouponPricer::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Volatility",
        "IborCouponPricerType",
        "Permanent"
    };

    std::set<std::string> qlIborCouponPricer::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIborCouponPricer::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIborCouponPricer::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIborCouponPricer::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            return Volatility_;
        else if(strcmp(nameUpper.c_str(), "IBORCOUPONPRICERTYPE")==0)
            return IborCouponPricerType_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIborCouponPricer::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            Volatility_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORCOUPONPRICERTYPE")==0)
            IborCouponPricerType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIborCouponPricer::qlIborCouponPricer(
            const std::string& ObjectId,
            const std::string& Volatility,
            const std::string& IborCouponPricerType,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIborCouponPricer", Permanent),
        Volatility_(Volatility),
        IborCouponPricerType_(IborCouponPricerType),
        Permanent_(Permanent) {
                  
            processPrecedentID(Volatility);
            
    }

    const char* qlIborLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "FixingDays",
        "IsInArrears",
        "DayCounter",
        "Floors",
        "Gearings",
        "IborIndex",
        "Spreads",
        "Caps",
        "Permanent"
    };

    std::set<std::string> qlIborLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIborLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIborLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIborLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIborLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
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
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIborLeg::qlIborLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIborLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        IsInArrears_(IsInArrears),
        DayCounter_(DayCounter),
        Floors_(Floors),
        Gearings_(Gearings),
        IborIndex_(IborIndex),
        Spreads_(Spreads),
        Caps_(Caps),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(IborIndex);
            
    }

    const char* qlRangeAccrualLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PaymentBDC",
        "Nominals",
        "ScheduleID",
        "FixingDays",
        "DayCounter",
        "LowerStrikes",
        "Gearings",
        "IborIndex",
        "Spreads",
        "UpperStrikes",
        "ObservationsTenor",
        "ObservationsBDC",
        "Permanent"
    };

    std::set<std::string> qlRangeAccrualLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRangeAccrualLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRangeAccrualLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRangeAccrualLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            return PaymentBDC_;
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            return Nominals_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            return ScheduleID_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "LOWERSTRIKES")==0)
            return LowerStrikes_;
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            return Gearings_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            return Spreads_;
        else if(strcmp(nameUpper.c_str(), "UPPERSTRIKES")==0)
            return UpperStrikes_;
        else if(strcmp(nameUpper.c_str(), "OBSERVATIONSTENOR")==0)
            return ObservationsTenor_;
        else if(strcmp(nameUpper.c_str(), "OBSERVATIONSBDC")==0)
            return ObservationsBDC_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRangeAccrualLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTBDC")==0)
            PaymentBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINALS")==0)
            Nominals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULEID")==0)
            ScheduleID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LOWERSTRIKES")==0)
            LowerStrikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "GEARINGS")==0)
            Gearings_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADS")==0)
            Spreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "UPPERSTRIKES")==0)
            UpperStrikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "OBSERVATIONSTENOR")==0)
            ObservationsTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OBSERVATIONSBDC")==0)
            ObservationsBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRangeAccrualLeg::qlRangeAccrualLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            const std::string& DayCounter,
            const std::vector<double>& LowerStrikes,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& UpperStrikes,
            const std::string& ObservationsTenor,
            const std::string& ObservationsBDC,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRangeAccrualLeg", Permanent),
        PaymentBDC_(PaymentBDC),
        Nominals_(Nominals),
        ScheduleID_(ScheduleID),
        FixingDays_(FixingDays),
        DayCounter_(DayCounter),
        LowerStrikes_(LowerStrikes),
        Gearings_(Gearings),
        IborIndex_(IborIndex),
        Spreads_(Spreads),
        UpperStrikes_(UpperStrikes),
        ObservationsTenor_(ObservationsTenor),
        ObservationsBDC_(ObservationsBDC),
        Permanent_(Permanent) {
                  
            processPrecedentID(ScheduleID);
            processPrecedentID(IborIndex);
            
    }

 } }
