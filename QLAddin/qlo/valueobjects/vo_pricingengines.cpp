
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
#include <qlo/pricingengines.hpp>
#include <qlo/valueobjects/vo_pricingengines.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAnalyticCapFloorEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "HandleModel",
        "Permanent"
    };

    std::set<std::string> qlAnalyticCapFloorEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAnalyticCapFloorEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAnalyticCapFloorEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAnalyticCapFloorEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "HANDLEMODEL")==0)
            return HandleModel_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAnalyticCapFloorEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "HANDLEMODEL")==0)
            HandleModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAnalyticCapFloorEngine::qlAnalyticCapFloorEngine(
            const std::string& ObjectId,
            const std::string& HandleModel,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAnalyticCapFloorEngine", Permanent),
        HandleModel_(HandleModel),
        Permanent_(Permanent) {
                  
            processPrecedentID(HandleModel);
            
    }

    const char* qlBinomialPricingEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "EngineID",
        "ProcessID",
        "TimeSteps",
        "Permanent"
    };

    std::set<std::string> qlBinomialPricingEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBinomialPricingEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBinomialPricingEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBinomialPricingEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ENGINEID")==0)
            return EngineID_;
        else if(strcmp(nameUpper.c_str(), "PROCESSID")==0)
            return ProcessID_;
        else if(strcmp(nameUpper.c_str(), "TIMESTEPS")==0)
            return TimeSteps_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBinomialPricingEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENGINEID")==0)
            EngineID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PROCESSID")==0)
            ProcessID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TIMESTEPS")==0)
            TimeSteps_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBinomialPricingEngine::qlBinomialPricingEngine(
            const std::string& ObjectId,
            const std::string& EngineID,
            const std::string& ProcessID,
            long TimeSteps,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBinomialPricingEngine", Permanent),
        EngineID_(EngineID),
        ProcessID_(ProcessID),
        TimeSteps_(TimeSteps),
        Permanent_(Permanent) {
                  
            processPrecedentID(ProcessID);
            
    }

    const char* qlBlackCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionType",
        "Strike",
        "AtmForwardValue",
        "StdDev",
        "Deflator",
        "Permanent"
    };

    std::set<std::string> qlBlackCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            return OptionType_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            return AtmForwardValue_;
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            return StdDev_;
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            return Deflator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            OptionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            AtmForwardValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            StdDev_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            Deflator_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackCalculator::qlBlackCalculator(
            const std::string& ObjectId,
            const std::string& OptionType,
            double Strike,
            double AtmForwardValue,
            double StdDev,
            double Deflator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackCalculator", Permanent),
        OptionType_(OptionType),
        Strike_(Strike),
        AtmForwardValue_(AtmForwardValue),
        StdDev_(StdDev),
        Deflator_(Deflator),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlBlackCalculator2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PayoffID",
        "AtmForwardValue",
        "StdDev",
        "Deflator",
        "Permanent"
    };

    std::set<std::string> qlBlackCalculator2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackCalculator2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackCalculator2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackCalculator2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFFID")==0)
            return PayoffID_;
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            return AtmForwardValue_;
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            return StdDev_;
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            return Deflator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackCalculator2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFFID")==0)
            PayoffID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            AtmForwardValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            StdDev_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            Deflator_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackCalculator2::qlBlackCalculator2(
            const std::string& ObjectId,
            const std::string& PayoffID,
            double AtmForwardValue,
            double StdDev,
            double Deflator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackCalculator2", Permanent),
        PayoffID_(PayoffID),
        AtmForwardValue_(AtmForwardValue),
        StdDev_(StdDev),
        Deflator_(Deflator),
        Permanent_(Permanent) {
                  
            processPrecedentID(PayoffID);
            
    }

    const char* qlBlackCapFloorEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "VolTS",
        "Permanent"
    };

    std::set<std::string> qlBlackCapFloorEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackCapFloorEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackCapFloorEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackCapFloorEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "VOLTS")==0)
            return VolTS_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackCapFloorEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLTS")==0)
            VolTS_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackCapFloorEngine::qlBlackCapFloorEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const std::string& VolTS,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackCapFloorEngine", Permanent),
        YieldCurve_(YieldCurve),
        VolTS_(VolTS),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            processPrecedentID(VolTS);
            
    }

    const char* qlBlackCapFloorEngine2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Vol",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlBlackCapFloorEngine2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackCapFloorEngine2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackCapFloorEngine2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackCapFloorEngine2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "VOL")==0)
            return Vol_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackCapFloorEngine2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOL")==0)
            Vol_ = value;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackCapFloorEngine2::qlBlackCapFloorEngine2(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const ObjectHandler::property_t& Vol,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackCapFloorEngine2", Permanent),
        YieldCurve_(YieldCurve),
        Vol_(Vol),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            processVariant(Vol);
            
    }

    const char* qlBlackScholesCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionType",
        "Strike",
        "Spot",
        "Growth",
        "StdDev",
        "Deflator",
        "Permanent"
    };

    std::set<std::string> qlBlackScholesCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackScholesCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackScholesCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackScholesCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            return OptionType_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "SPOT")==0)
            return Spot_;
        else if(strcmp(nameUpper.c_str(), "GROWTH")==0)
            return Growth_;
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            return StdDev_;
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            return Deflator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackScholesCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            OptionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPOT")==0)
            Spot_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GROWTH")==0)
            Growth_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            StdDev_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            Deflator_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackScholesCalculator::qlBlackScholesCalculator(
            const std::string& ObjectId,
            const std::string& OptionType,
            double Strike,
            double Spot,
            double Growth,
            double StdDev,
            double Deflator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackScholesCalculator", Permanent),
        OptionType_(OptionType),
        Strike_(Strike),
        Spot_(Spot),
        Growth_(Growth),
        StdDev_(StdDev),
        Deflator_(Deflator),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlBlackScholesCalculator2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PayoffID",
        "Spot",
        "Growth",
        "StdDev",
        "Deflator",
        "Permanent"
    };

    std::set<std::string> qlBlackScholesCalculator2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackScholesCalculator2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackScholesCalculator2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackScholesCalculator2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFFID")==0)
            return PayoffID_;
        else if(strcmp(nameUpper.c_str(), "SPOT")==0)
            return Spot_;
        else if(strcmp(nameUpper.c_str(), "GROWTH")==0)
            return Growth_;
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            return StdDev_;
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            return Deflator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackScholesCalculator2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFFID")==0)
            PayoffID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPOT")==0)
            Spot_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GROWTH")==0)
            Growth_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STDDEV")==0)
            StdDev_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DEFLATOR")==0)
            Deflator_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackScholesCalculator2::qlBlackScholesCalculator2(
            const std::string& ObjectId,
            const std::string& PayoffID,
            double Spot,
            double Growth,
            double StdDev,
            double Deflator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackScholesCalculator2", Permanent),
        PayoffID_(PayoffID),
        Spot_(Spot),
        Growth_(Growth),
        StdDev_(StdDev),
        Deflator_(Deflator),
        Permanent_(Permanent) {
                  
            processPrecedentID(PayoffID);
            
    }

    const char* qlBlackSwaptionEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "VolTS",
        "Permanent"
    };

    std::set<std::string> qlBlackSwaptionEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackSwaptionEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackSwaptionEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackSwaptionEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "VOLTS")==0)
            return VolTS_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackSwaptionEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLTS")==0)
            VolTS_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackSwaptionEngine::qlBlackSwaptionEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const std::string& VolTS,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackSwaptionEngine", Permanent),
        YieldCurve_(YieldCurve),
        VolTS_(VolTS),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            processPrecedentID(VolTS);
            
    }

    const char* qlBlackSwaptionEngine2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Vol",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlBlackSwaptionEngine2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackSwaptionEngine2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackSwaptionEngine2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackSwaptionEngine2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "VOL")==0)
            return Vol_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackSwaptionEngine2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOL")==0)
            Vol_ = value;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackSwaptionEngine2::qlBlackSwaptionEngine2(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const ObjectHandler::property_t& Vol,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackSwaptionEngine2", Permanent),
        YieldCurve_(YieldCurve),
        Vol_(Vol),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            processVariant(Vol);
            
    }

    const char* qlBondEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlBondEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBondEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBondEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBondEngine::getSystemProperty(const std::string& name) const {
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

    void qlBondEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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

    qlBondEngine::qlBondEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBondEngine", Permanent),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlDiscountingSwapEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "IncludeSettlDate",
        "SettlementDate",
        "NpvDate",
        "Permanent"
    };

    std::set<std::string> qlDiscountingSwapEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDiscountingSwapEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDiscountingSwapEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDiscountingSwapEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "INCLUDESETTLDATE")==0)
            return IncludeSettlDate_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            return SettlementDate_;
        else if(strcmp(nameUpper.c_str(), "NPVDATE")==0)
            return NpvDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDiscountingSwapEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INCLUDESETTLDATE")==0)
            IncludeSettlDate_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            SettlementDate_ = value;
        else if(strcmp(nameUpper.c_str(), "NPVDATE")==0)
            NpvDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDiscountingSwapEngine::qlDiscountingSwapEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool IncludeSettlDate,
            const ObjectHandler::property_t& SettlementDate,
            const ObjectHandler::property_t& NpvDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDiscountingSwapEngine", Permanent),
        YieldCurve_(YieldCurve),
        IncludeSettlDate_(IncludeSettlDate),
        SettlementDate_(SettlementDate),
        NpvDate_(NpvDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlPricingEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "EngineID",
        "ProcessID",
        "Permanent"
    };

    std::set<std::string> qlPricingEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPricingEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPricingEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPricingEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ENGINEID")==0)
            return EngineID_;
        else if(strcmp(nameUpper.c_str(), "PROCESSID")==0)
            return ProcessID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPricingEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENGINEID")==0)
            EngineID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PROCESSID")==0)
            ProcessID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPricingEngine::qlPricingEngine(
            const std::string& ObjectId,
            const std::string& EngineID,
            const std::string& ProcessID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPricingEngine", Permanent),
        EngineID_(EngineID),
        ProcessID_(ProcessID),
        Permanent_(Permanent) {
                  
            processPrecedentID(ProcessID);
            
    }

 } }
