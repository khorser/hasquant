
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
#include <qlo/index.hpp>
#include <qlo/valueobjects/vo_index.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBMAIndex::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlBMAIndex::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBMAIndex::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBMAIndex::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBMAIndex::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBMAIndex::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBMAIndex::qlBMAIndex(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBMAIndex", Permanent),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlEonia::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlEonia::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEonia::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEonia::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEonia::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEonia::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEonia::qlEonia(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEonia", Permanent),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlEuribor::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Tenor",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlEuribor::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEuribor::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEuribor::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEuribor::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEuribor::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEuribor::qlEuribor(
            const std::string& ObjectId,
            const std::string& Tenor,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEuribor", Permanent),
        Tenor_(Tenor),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlEuribor365::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Tenor",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlEuribor365::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEuribor365::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEuribor365::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEuribor365::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEuribor365::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEuribor365::qlEuribor365(
            const std::string& ObjectId,
            const std::string& Tenor,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEuribor365", Permanent),
        Tenor_(Tenor),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlEuriborSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FixingType",
        "Tenor",
        "FwdCurve",
        "DiscCurve",
        "Permanent"
    };

    std::set<std::string> qlEuriborSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEuriborSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEuriborSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEuriborSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FIXINGTYPE")==0)
            return FixingType_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            return FwdCurve_;
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            return DiscCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEuriborSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGTYPE")==0)
            FixingType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            FwdCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            DiscCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEuriborSwap::qlEuriborSwap(
            const std::string& ObjectId,
            const std::string& FixingType,
            const std::string& Tenor,
            const std::string& FwdCurve,
            const std::string& DiscCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEuriborSwap", Permanent),
        FixingType_(FixingType),
        Tenor_(Tenor),
        FwdCurve_(FwdCurve),
        DiscCurve_(DiscCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(FwdCurve);
            processPrecedentID(DiscCurve);
            
    }

    const char* qlEuriborSwapIsdaFixA::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Tenor",
        "FwdCurve",
        "DiscCurve",
        "Permanent"
    };

    std::set<std::string> qlEuriborSwapIsdaFixA::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEuriborSwapIsdaFixA::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEuriborSwapIsdaFixA::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEuriborSwapIsdaFixA::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            return FwdCurve_;
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            return DiscCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEuriborSwapIsdaFixA::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            FwdCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            DiscCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEuriborSwapIsdaFixA::qlEuriborSwapIsdaFixA(
            const std::string& ObjectId,
            const std::string& Tenor,
            const std::string& FwdCurve,
            const std::string& DiscCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEuriborSwapIsdaFixA", Permanent),
        Tenor_(Tenor),
        FwdCurve_(FwdCurve),
        DiscCurve_(DiscCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(FwdCurve);
            processPrecedentID(DiscCurve);
            
    }

    const char* qlIborIndex::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FamilyName",
        "Tenor",
        "FixingDays",
        "Currency",
        "Calendar",
        "BDayConvention",
        "EndOfMonth",
        "DayCounter",
        "FwdCurve",
        "Permanent"
    };

    std::set<std::string> qlIborIndex::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIborIndex::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIborIndex::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIborIndex::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            return FamilyName_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BDAYCONVENTION")==0)
            return BDayConvention_;
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            return EndOfMonth_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            return FwdCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIborIndex::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            FamilyName_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BDAYCONVENTION")==0)
            BDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            EndOfMonth_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            FwdCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIborIndex::qlIborIndex(
            const std::string& ObjectId,
            const std::string& FamilyName,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& BDayConvention,
            bool EndOfMonth,
            const std::string& DayCounter,
            const std::string& FwdCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIborIndex", Permanent),
        FamilyName_(FamilyName),
        Tenor_(Tenor),
        FixingDays_(FixingDays),
        Currency_(Currency),
        Calendar_(Calendar),
        BDayConvention_(BDayConvention),
        EndOfMonth_(EndOfMonth),
        DayCounter_(DayCounter),
        FwdCurve_(FwdCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(FwdCurve);
            
    }

    const char* qlLibor::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Currency",
        "Tenor",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlLibor::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLibor::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLibor::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLibor::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLibor::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLibor::qlLibor(
            const std::string& ObjectId,
            const std::string& Currency,
            const std::string& Tenor,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLibor", Permanent),
        Currency_(Currency),
        Tenor_(Tenor),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlLiborSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Currency",
        "FixingType",
        "Tenor",
        "FwdCurve",
        "DiscCurve",
        "Permanent"
    };

    std::set<std::string> qlLiborSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLiborSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLiborSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLiborSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "FIXINGTYPE")==0)
            return FixingType_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            return FwdCurve_;
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            return DiscCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLiborSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGTYPE")==0)
            FixingType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            FwdCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            DiscCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLiborSwap::qlLiborSwap(
            const std::string& ObjectId,
            const std::string& Currency,
            const std::string& FixingType,
            const std::string& Tenor,
            const std::string& FwdCurve,
            const std::string& DiscCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLiborSwap", Permanent),
        Currency_(Currency),
        FixingType_(FixingType),
        Tenor_(Tenor),
        FwdCurve_(FwdCurve),
        DiscCurve_(DiscCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(FwdCurve);
            processPrecedentID(DiscCurve);
            
    }

    const char* qlOvernightIndex::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FamilyName",
        "FixingDays",
        "Currency",
        "Calendar",
        "DayCounter",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlOvernightIndex::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlOvernightIndex::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlOvernightIndex::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlOvernightIndex::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            return FamilyName_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlOvernightIndex::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            FamilyName_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlOvernightIndex::qlOvernightIndex(
            const std::string& ObjectId,
            const std::string& FamilyName,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& DayCounter,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlOvernightIndex", Permanent),
        FamilyName_(FamilyName),
        FixingDays_(FixingDays),
        Currency_(Currency),
        Calendar_(Calendar),
        DayCounter_(DayCounter),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlProxyIbor::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FamilyName",
        "Tenor",
        "FixingDays",
        "Currency",
        "Calendar",
        "BDayConvention",
        "EndOfMonth",
        "DayCounter",
        "Gearing",
        "IborIndex",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlProxyIbor::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlProxyIbor::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlProxyIbor::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlProxyIbor::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            return FamilyName_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BDAYCONVENTION")==0)
            return BDayConvention_;
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            return EndOfMonth_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "GEARING")==0)
            return Gearing_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlProxyIbor::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            FamilyName_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BDAYCONVENTION")==0)
            BDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            EndOfMonth_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING")==0)
            Gearing_ = value;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlProxyIbor::qlProxyIbor(
            const std::string& ObjectId,
            const std::string& FamilyName,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& BDayConvention,
            bool EndOfMonth,
            const std::string& DayCounter,
            const ObjectHandler::property_t& Gearing,
            const std::string& IborIndex,
            const ObjectHandler::property_t& Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlProxyIbor", Permanent),
        FamilyName_(FamilyName),
        Tenor_(Tenor),
        FixingDays_(FixingDays),
        Currency_(Currency),
        Calendar_(Calendar),
        BDayConvention_(BDayConvention),
        EndOfMonth_(EndOfMonth),
        DayCounter_(DayCounter),
        Gearing_(Gearing),
        IborIndex_(IborIndex),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processVariant(Gearing);
            processPrecedentID(IborIndex);
            processVariant(Spread);
            
    }

    const char* qlSonia::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlSonia::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSonia::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSonia::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSonia::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSonia::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSonia::qlSonia(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSonia", Permanent),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlSwapIndex::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FamilyName",
        "Tenor",
        "FixingDays",
        "Currency",
        "Calendar",
        "FixedLegTenor",
        "FixedLegBDC",
        "FixedLegDayCounter",
        "IborIndex",
        "DiscCurve",
        "Permanent"
    };

    std::set<std::string> qlSwapIndex::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwapIndex::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwapIndex::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwapIndex::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            return FamilyName_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            return FixingDays_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGTENOR")==0)
            return FixedLegTenor_;
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGBDC")==0)
            return FixedLegBDC_;
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGDAYCOUNTER")==0)
            return FixedLegDayCounter_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            return DiscCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwapIndex::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FAMILYNAME")==0)
            FamilyName_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDAYS")==0)
            FixingDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGTENOR")==0)
            FixedLegTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGBDC")==0)
            FixedLegBDC_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDLEGDAYCOUNTER")==0)
            FixedLegDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            DiscCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwapIndex::qlSwapIndex(
            const std::string& ObjectId,
            const std::string& FamilyName,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& FixedLegTenor,
            const std::string& FixedLegBDC,
            const std::string& FixedLegDayCounter,
            const std::string& IborIndex,
            const std::string& DiscCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwapIndex", Permanent),
        FamilyName_(FamilyName),
        Tenor_(Tenor),
        FixingDays_(FixingDays),
        Currency_(Currency),
        Calendar_(Calendar),
        FixedLegTenor_(FixedLegTenor),
        FixedLegBDC_(FixedLegBDC),
        FixedLegDayCounter_(FixedLegDayCounter),
        IborIndex_(IborIndex),
        DiscCurve_(DiscCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processPrecedentID(DiscCurve);
            
    }

 } }
