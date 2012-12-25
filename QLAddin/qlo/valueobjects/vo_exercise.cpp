
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
#include <qlo/exercise.hpp>
#include <qlo/valueobjects/vo_exercise.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAmericanExercise::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "EarliestDate",
        "LatestDate",
        "PayoffAtExpiry",
        "Permanent"
    };

    std::set<std::string> qlAmericanExercise::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAmericanExercise::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAmericanExercise::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAmericanExercise::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EARLIESTDATE")==0)
            return EarliestDate_;
        else if(strcmp(nameUpper.c_str(), "LATESTDATE")==0)
            return LatestDate_;
        else if(strcmp(nameUpper.c_str(), "PAYOFFATEXPIRY")==0)
            return PayoffAtExpiry_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAmericanExercise::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EARLIESTDATE")==0)
            EarliestDate_ = value;
        else if(strcmp(nameUpper.c_str(), "LATESTDATE")==0)
            LatestDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYOFFATEXPIRY")==0)
            PayoffAtExpiry_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAmericanExercise::qlAmericanExercise(
            const std::string& ObjectId,
            const ObjectHandler::property_t& EarliestDate,
            const ObjectHandler::property_t& LatestDate,
            bool PayoffAtExpiry,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAmericanExercise", Permanent),
        EarliestDate_(EarliestDate),
        LatestDate_(LatestDate),
        PayoffAtExpiry_(PayoffAtExpiry),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlBermudanExercise::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Dates",
        "PayoffAtExpiry",
        "Permanent"
    };

    std::set<std::string> qlBermudanExercise::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBermudanExercise::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBermudanExercise::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBermudanExercise::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            return Dates_;
        else if(strcmp(nameUpper.c_str(), "PAYOFFATEXPIRY")==0)
            return PayoffAtExpiry_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBermudanExercise::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            Dates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYOFFATEXPIRY")==0)
            PayoffAtExpiry_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBermudanExercise::qlBermudanExercise(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& Dates,
            bool PayoffAtExpiry,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBermudanExercise", Permanent),
        Dates_(Dates),
        PayoffAtExpiry_(PayoffAtExpiry),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlEuropeanExercise::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ExpiryDate",
        "Permanent"
    };

    std::set<std::string> qlEuropeanExercise::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEuropeanExercise::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEuropeanExercise::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEuropeanExercise::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EXPIRYDATE")==0)
            return ExpiryDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEuropeanExercise::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXPIRYDATE")==0)
            ExpiryDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEuropeanExercise::qlEuropeanExercise(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ExpiryDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEuropeanExercise", Permanent),
        ExpiryDate_(ExpiryDate),
        Permanent_(Permanent) {
                  

            
    }

 } }
