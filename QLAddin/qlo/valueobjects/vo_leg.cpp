
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
#include <qlo/leg.hpp>
#include <qlo/valueobjects/vo_leg.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlInterestRate::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Rate",
        "DayCounter",
        "Compounding",
        "Frequency",
        "Permanent"
    };

    std::set<std::string> qlInterestRate::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlInterestRate::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlInterestRate::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlInterestRate::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "COMPOUNDING")==0)
            return Compounding_;
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            return Frequency_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlInterestRate::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COMPOUNDING")==0)
            Compounding_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            Frequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlInterestRate::qlInterestRate(
            const std::string& ObjectId,
            double Rate,
            const std::string& DayCounter,
            const std::string& Compounding,
            const std::string& Frequency,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlInterestRate", Permanent),
        Rate_(Rate),
        DayCounter_(DayCounter),
        Compounding_(Compounding),
        Frequency_(Frequency),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Amounts",
        "Dates",
        "ToBeSorted",
        "Permanent"
    };

    std::set<std::string> qlLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "AMOUNTS")==0)
            return Amounts_;
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            return Dates_;
        else if(strcmp(nameUpper.c_str(), "TOBESORTED")==0)
            return ToBeSorted_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "AMOUNTS")==0)
            Amounts_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            Dates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TOBESORTED")==0)
            ToBeSorted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLeg::qlLeg(
            const std::string& ObjectId,
            const std::vector<double>& Amounts,
            const std::vector<ObjectHandler::property_t>& Dates,
            bool ToBeSorted,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLeg", Permanent),
        Amounts_(Amounts),
        Dates_(Dates),
        ToBeSorted_(ToBeSorted),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlLegFromCapFloor::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CapFloor",
        "Permanent"
    };

    std::set<std::string> qlLegFromCapFloor::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLegFromCapFloor::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLegFromCapFloor::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLegFromCapFloor::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CAPFLOOR")==0)
            return CapFloor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLegFromCapFloor::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CAPFLOOR")==0)
            CapFloor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLegFromCapFloor::qlLegFromCapFloor(
            const std::string& ObjectId,
            const std::string& CapFloor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLegFromCapFloor", Permanent),
        CapFloor_(CapFloor),
        Permanent_(Permanent) {
                  
            processPrecedentID(CapFloor);
            
    }

    const char* qlLegFromSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Swap",
        "LegNumber",
        "Permanent"
    };

    std::set<std::string> qlLegFromSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLegFromSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLegFromSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLegFromSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAP")==0)
            return Swap_;
        else if(strcmp(nameUpper.c_str(), "LEGNUMBER")==0)
            return LegNumber_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLegFromSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAP")==0)
            Swap_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LEGNUMBER")==0)
            LegNumber_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLegFromSwap::qlLegFromSwap(
            const std::string& ObjectId,
            const std::string& Swap,
            long LegNumber,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLegFromSwap", Permanent),
        Swap_(Swap),
        LegNumber_(LegNumber),
        Permanent_(Permanent) {
                  
            processPrecedentID(Swap);
            
    }

    const char* qlMultiPhaseLeg::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "LegIDs",
        "ToBeSorted",
        "Permanent"
    };

    std::set<std::string> qlMultiPhaseLeg::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMultiPhaseLeg::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMultiPhaseLeg::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMultiPhaseLeg::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "LEGIDS")==0)
            return LegIDs_;
        else if(strcmp(nameUpper.c_str(), "TOBESORTED")==0)
            return ToBeSorted_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMultiPhaseLeg::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LEGIDS")==0)
            LegIDs_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TOBESORTED")==0)
            ToBeSorted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMultiPhaseLeg::qlMultiPhaseLeg(
            const std::string& ObjectId,
            const std::vector<std::string>& LegIDs,
            bool ToBeSorted,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMultiPhaseLeg", Permanent),
        LegIDs_(LegIDs),
        ToBeSorted_(ToBeSorted),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = LegIDs.begin();
                    i != LegIDs.end(); ++i)
                processPrecedentID(*i);
            
    }

 } }
