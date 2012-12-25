
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
#include <qlo/options.hpp>
#include <qlo/valueobjects/vo_options.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBarrierOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BarrierType",
        "Barrier",
        "Rebate",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlBarrierOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBarrierOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBarrierOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBarrierOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BARRIERTYPE")==0)
            return BarrierType_;
        else if(strcmp(nameUpper.c_str(), "BARRIER")==0)
            return Barrier_;
        else if(strcmp(nameUpper.c_str(), "REBATE")==0)
            return Rebate_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBarrierOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BARRIERTYPE")==0)
            BarrierType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BARRIER")==0)
            Barrier_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "REBATE")==0)
            Rebate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBarrierOption::qlBarrierOption(
            const std::string& ObjectId,
            const std::string& BarrierType,
            double Barrier,
            double Rebate,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBarrierOption", Permanent),
        BarrierType_(BarrierType),
        Barrier_(Barrier),
        Rebate_(Rebate),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlCaAsianOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "AverageType",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlCaAsianOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCaAsianOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCaAsianOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCaAsianOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "AVERAGETYPE")==0)
            return AverageType_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCaAsianOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "AVERAGETYPE")==0)
            AverageType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCaAsianOption::qlCaAsianOption(
            const std::string& ObjectId,
            const std::string& AverageType,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCaAsianOption", Permanent),
        AverageType_(AverageType),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlDaAsianOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "AverageType",
        "RunningAccumulator",
        "PastFixings",
        "FixingDates",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlDaAsianOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDaAsianOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDaAsianOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDaAsianOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "AVERAGETYPE")==0)
            return AverageType_;
        else if(strcmp(nameUpper.c_str(), "RUNNINGACCUMULATOR")==0)
            return RunningAccumulator_;
        else if(strcmp(nameUpper.c_str(), "PASTFIXINGS")==0)
            return PastFixings_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDATES")==0)
            return FixingDates_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDaAsianOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "AVERAGETYPE")==0)
            AverageType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RUNNINGACCUMULATOR")==0)
            RunningAccumulator_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PASTFIXINGS")==0)
            PastFixings_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDATES")==0)
            FixingDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDaAsianOption::qlDaAsianOption(
            const std::string& ObjectId,
            const std::string& AverageType,
            double RunningAccumulator,
            long PastFixings,
            const std::vector<ObjectHandler::property_t>& FixingDates,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDaAsianOption", Permanent),
        AverageType_(AverageType),
        RunningAccumulator_(RunningAccumulator),
        PastFixings_(PastFixings),
        FixingDates_(FixingDates),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlDividendVanillaOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Payoff",
        "Exercise",
        "DividendDates",
        "Dividends",
        "Permanent"
    };

    std::set<std::string> qlDividendVanillaOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDividendVanillaOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDividendVanillaOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDividendVanillaOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "DIVIDENDDATES")==0)
            return DividendDates_;
        else if(strcmp(nameUpper.c_str(), "DIVIDENDS")==0)
            return Dividends_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDividendVanillaOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DIVIDENDDATES")==0)
            DividendDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DIVIDENDS")==0)
            Dividends_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDividendVanillaOption::qlDividendVanillaOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            const std::vector<ObjectHandler::property_t>& DividendDates,
            const std::vector<double>& Dividends,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDividendVanillaOption", Permanent),
        Payoff_(Payoff),
        Exercise_(Exercise),
        DividendDates_(DividendDates),
        Dividends_(Dividends),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlEuropeanOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlEuropeanOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEuropeanOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEuropeanOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEuropeanOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEuropeanOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEuropeanOption::qlEuropeanOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEuropeanOption", Permanent),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlForwardVanillaOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Moneyness",
        "ResetDate",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlForwardVanillaOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardVanillaOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardVanillaOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardVanillaOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "MONEYNESS")==0)
            return Moneyness_;
        else if(strcmp(nameUpper.c_str(), "RESETDATE")==0)
            return ResetDate_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardVanillaOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MONEYNESS")==0)
            Moneyness_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RESETDATE")==0)
            ResetDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardVanillaOption::qlForwardVanillaOption(
            const std::string& ObjectId,
            double Moneyness,
            const ObjectHandler::property_t& ResetDate,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardVanillaOption", Permanent),
        Moneyness_(Moneyness),
        ResetDate_(ResetDate),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlQuantoForwardVanillaOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Moneyness",
        "ResetDate",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlQuantoForwardVanillaOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlQuantoForwardVanillaOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlQuantoForwardVanillaOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlQuantoForwardVanillaOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "MONEYNESS")==0)
            return Moneyness_;
        else if(strcmp(nameUpper.c_str(), "RESETDATE")==0)
            return ResetDate_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlQuantoForwardVanillaOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MONEYNESS")==0)
            Moneyness_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RESETDATE")==0)
            ResetDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlQuantoForwardVanillaOption::qlQuantoForwardVanillaOption(
            const std::string& ObjectId,
            double Moneyness,
            const ObjectHandler::property_t& ResetDate,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlQuantoForwardVanillaOption", Permanent),
        Moneyness_(Moneyness),
        ResetDate_(ResetDate),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlQuantoVanillaOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlQuantoVanillaOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlQuantoVanillaOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlQuantoVanillaOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlQuantoVanillaOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlQuantoVanillaOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlQuantoVanillaOption::qlQuantoVanillaOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlQuantoVanillaOption", Permanent),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

    const char* qlVanillaOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Payoff",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlVanillaOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlVanillaOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlVanillaOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlVanillaOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            return Payoff_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlVanillaOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFF")==0)
            Payoff_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlVanillaOption::qlVanillaOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlVanillaOption", Permanent),
        Payoff_(Payoff),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(Payoff);
            processPrecedentID(Exercise);
            
    }

 } }
