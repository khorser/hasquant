
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
#include <qlo/products.hpp>
#include <qlo/valueobjects/vo_products.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlMarketModelMultiProductComposite::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Permanent"
    };

    std::set<std::string> qlMarketModelMultiProductComposite::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMarketModelMultiProductComposite::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMarketModelMultiProductComposite::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMarketModelMultiProductComposite::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMarketModelMultiProductComposite::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMarketModelMultiProductComposite::qlMarketModelMultiProductComposite(
            const std::string& ObjectId,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMarketModelMultiProductComposite", Permanent),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlMarketModelMultiStepRatchet::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RateTimes",
        "Accruals",
        "PaymentTimes",
        "GearingOfFloor",
        "GearingOfFixing",
        "SpreadOfFloor",
        "SpreadOfFixing",
        "InitialFloor",
        "Payer",
        "Permanent"
    };

    std::set<std::string> qlMarketModelMultiStepRatchet::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMarketModelMultiStepRatchet::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMarketModelMultiStepRatchet::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMarketModelMultiStepRatchet::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            return RateTimes_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALS")==0)
            return Accruals_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTTIMES")==0)
            return PaymentTimes_;
        else if(strcmp(nameUpper.c_str(), "GEARINGOFFLOOR")==0)
            return GearingOfFloor_;
        else if(strcmp(nameUpper.c_str(), "GEARINGOFFIXING")==0)
            return GearingOfFixing_;
        else if(strcmp(nameUpper.c_str(), "SPREADOFFLOOR")==0)
            return SpreadOfFloor_;
        else if(strcmp(nameUpper.c_str(), "SPREADOFFIXING")==0)
            return SpreadOfFixing_;
        else if(strcmp(nameUpper.c_str(), "INITIALFLOOR")==0)
            return InitialFloor_;
        else if(strcmp(nameUpper.c_str(), "PAYER")==0)
            return Payer_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMarketModelMultiStepRatchet::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            RateTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ACCRUALS")==0)
            Accruals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYMENTTIMES")==0)
            PaymentTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "GEARINGOFFLOOR")==0)
            GearingOfFloor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARINGOFFIXING")==0)
            GearingOfFixing_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADOFFLOOR")==0)
            SpreadOfFloor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREADOFFIXING")==0)
            SpreadOfFixing_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALFLOOR")==0)
            InitialFloor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PAYER")==0)
            Payer_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMarketModelMultiStepRatchet::qlMarketModelMultiStepRatchet(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            double GearingOfFloor,
            double GearingOfFixing,
            double SpreadOfFloor,
            double SpreadOfFixing,
            double InitialFloor,
            bool Payer,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMarketModelMultiStepRatchet", Permanent),
        RateTimes_(RateTimes),
        Accruals_(Accruals),
        PaymentTimes_(PaymentTimes),
        GearingOfFloor_(GearingOfFloor),
        GearingOfFixing_(GearingOfFixing),
        SpreadOfFloor_(SpreadOfFloor),
        SpreadOfFixing_(SpreadOfFixing),
        InitialFloor_(InitialFloor),
        Payer_(Payer),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlMarketModelOneStepForwards::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RateTimes",
        "Accruals",
        "PaymentTimes",
        "Strikes",
        "Permanent"
    };

    std::set<std::string> qlMarketModelOneStepForwards::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMarketModelOneStepForwards::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMarketModelOneStepForwards::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMarketModelOneStepForwards::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            return RateTimes_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALS")==0)
            return Accruals_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTTIMES")==0)
            return PaymentTimes_;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            return Strikes_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMarketModelOneStepForwards::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            RateTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ACCRUALS")==0)
            Accruals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYMENTTIMES")==0)
            PaymentTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMarketModelOneStepForwards::qlMarketModelOneStepForwards(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<double>& Strikes,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMarketModelOneStepForwards", Permanent),
        RateTimes_(RateTimes),
        Accruals_(Accruals),
        PaymentTimes_(PaymentTimes),
        Strikes_(Strikes),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlMarketModelOneStepOptionlets::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RateTimes",
        "Accruals",
        "PaymentTimes",
        "Payoffs",
        "Permanent"
    };

    std::set<std::string> qlMarketModelOneStepOptionlets::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMarketModelOneStepOptionlets::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMarketModelOneStepOptionlets::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMarketModelOneStepOptionlets::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            return RateTimes_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALS")==0)
            return Accruals_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTTIMES")==0)
            return PaymentTimes_;
        else if(strcmp(nameUpper.c_str(), "PAYOFFS")==0)
            return Payoffs_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMarketModelOneStepOptionlets::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            RateTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ACCRUALS")==0)
            Accruals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYMENTTIMES")==0)
            PaymentTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PAYOFFS")==0)
            Payoffs_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMarketModelOneStepOptionlets::qlMarketModelOneStepOptionlets(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<std::string>& Payoffs,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMarketModelOneStepOptionlets", Permanent),
        RateTimes_(RateTimes),
        Accruals_(Accruals),
        PaymentTimes_(PaymentTimes),
        Payoffs_(Payoffs),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = Payoffs.begin();
                    i != Payoffs.end(); ++i)
                processPrecedentID(*i);
            
    }

 } }
