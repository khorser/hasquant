
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
#include <qlo/payoffs.hpp>
#include <qlo/valueobjects/vo_payoffs.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlDoubleStickyRatchetPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Type1",
        "Type2",
        "Gearing1",
        "Gearing2",
        "Gearing3",
        "Spread1",
        "Spread2",
        "Spread3",
        "InitialValue1",
        "InitialValue2",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlDoubleStickyRatchetPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDoubleStickyRatchetPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDoubleStickyRatchetPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDoubleStickyRatchetPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TYPE1")==0)
            return Type1_;
        else if(strcmp(nameUpper.c_str(), "TYPE2")==0)
            return Type2_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            return Gearing3_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            return Spread3_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            return InitialValue1_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            return InitialValue2_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDoubleStickyRatchetPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TYPE1")==0)
            Type1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TYPE2")==0)
            Type2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            Gearing3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            Spread3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            InitialValue1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            InitialValue2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDoubleStickyRatchetPayoff::qlDoubleStickyRatchetPayoff(
            const std::string& ObjectId,
            double Type1,
            double Type2,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDoubleStickyRatchetPayoff", Permanent),
        Type1_(Type1),
        Type2_(Type2),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Gearing3_(Gearing3),
        Spread1_(Spread1),
        Spread2_(Spread2),
        Spread3_(Spread3),
        InitialValue1_(InitialValue1),
        InitialValue2_(InitialValue2),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlRatchetMaxPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Gearing1",
        "Gearing2",
        "Gearing3",
        "Spread1",
        "Spread2",
        "Spread3",
        "InitialValue1",
        "InitialValue2",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlRatchetMaxPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRatchetMaxPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRatchetMaxPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRatchetMaxPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            return Gearing3_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            return Spread3_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            return InitialValue1_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            return InitialValue2_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRatchetMaxPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            Gearing3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            Spread3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            InitialValue1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            InitialValue2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRatchetMaxPayoff::qlRatchetMaxPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRatchetMaxPayoff", Permanent),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Gearing3_(Gearing3),
        Spread1_(Spread1),
        Spread2_(Spread2),
        Spread3_(Spread3),
        InitialValue1_(InitialValue1),
        InitialValue2_(InitialValue2),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlRatchetMinPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Gearing1",
        "Gearing2",
        "Gearing3",
        "Spread1",
        "Spread2",
        "Spread3",
        "InitialValue1",
        "InitialValue2",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlRatchetMinPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRatchetMinPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRatchetMinPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRatchetMinPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            return Gearing3_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            return Spread3_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            return InitialValue1_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            return InitialValue2_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRatchetMinPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            Gearing3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            Spread3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            InitialValue1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            InitialValue2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRatchetMinPayoff::qlRatchetMinPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRatchetMinPayoff", Permanent),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Gearing3_(Gearing3),
        Spread1_(Spread1),
        Spread2_(Spread2),
        Spread3_(Spread3),
        InitialValue1_(InitialValue1),
        InitialValue2_(InitialValue2),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlRatchetPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Gearing1",
        "Gearing2",
        "Spread1",
        "Spread2",
        "InitialValue",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlRatchetPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRatchetPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRatchetPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRatchetPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE")==0)
            return InitialValue_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRatchetPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE")==0)
            InitialValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRatchetPayoff::qlRatchetPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Spread1,
            double Spread2,
            double InitialValue,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRatchetPayoff", Permanent),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Spread1_(Spread1),
        Spread2_(Spread2),
        InitialValue_(InitialValue),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlStickyMaxPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Gearing1",
        "Gearing2",
        "Gearing3",
        "Spread1",
        "Spread2",
        "Spread3",
        "InitialValue1",
        "InitialValue2",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlStickyMaxPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlStickyMaxPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlStickyMaxPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlStickyMaxPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            return Gearing3_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            return Spread3_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            return InitialValue1_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            return InitialValue2_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlStickyMaxPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            Gearing3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            Spread3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            InitialValue1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            InitialValue2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlStickyMaxPayoff::qlStickyMaxPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlStickyMaxPayoff", Permanent),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Gearing3_(Gearing3),
        Spread1_(Spread1),
        Spread2_(Spread2),
        Spread3_(Spread3),
        InitialValue1_(InitialValue1),
        InitialValue2_(InitialValue2),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlStickyMinPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Gearing1",
        "Gearing2",
        "Gearing3",
        "Spread1",
        "Spread2",
        "Spread3",
        "InitialValue1",
        "InitialValue2",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlStickyMinPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlStickyMinPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlStickyMinPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlStickyMinPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            return Gearing3_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            return Spread3_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            return InitialValue1_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            return InitialValue2_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlStickyMinPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING3")==0)
            Gearing3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD3")==0)
            Spread3_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE1")==0)
            InitialValue1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE2")==0)
            InitialValue2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlStickyMinPayoff::qlStickyMinPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlStickyMinPayoff", Permanent),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Gearing3_(Gearing3),
        Spread1_(Spread1),
        Spread2_(Spread2),
        Spread3_(Spread3),
        InitialValue1_(InitialValue1),
        InitialValue2_(InitialValue2),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlStickyPayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Gearing1",
        "Gearing2",
        "Spread1",
        "Spread2",
        "InitialValue",
        "AccrualFactor",
        "Permanent"
    };

    std::set<std::string> qlStickyPayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlStickyPayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlStickyPayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlStickyPayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            return Gearing1_;
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            return Gearing2_;
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            return Spread1_;
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            return Spread2_;
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE")==0)
            return InitialValue_;
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            return AccrualFactor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlStickyPayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING1")==0)
            Gearing1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING2")==0)
            Gearing2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD1")==0)
            Spread1_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD2")==0)
            Spread2_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALVALUE")==0)
            InitialValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCRUALFACTOR")==0)
            AccrualFactor_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlStickyPayoff::qlStickyPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Spread1,
            double Spread2,
            double InitialValue,
            double AccrualFactor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlStickyPayoff", Permanent),
        Gearing1_(Gearing1),
        Gearing2_(Gearing2),
        Spread1_(Spread1),
        Spread2_(Spread2),
        InitialValue_(InitialValue),
        AccrualFactor_(AccrualFactor),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlStrikedTypePayoff::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PayoffID",
        "OptionType",
        "Strike",
        "ThirdParameter",
        "Permanent"
    };

    std::set<std::string> qlStrikedTypePayoff::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlStrikedTypePayoff::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlStrikedTypePayoff::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlStrikedTypePayoff::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYOFFID")==0)
            return PayoffID_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            return OptionType_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "THIRDPARAMETER")==0)
            return ThirdParameter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlStrikedTypePayoff::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYOFFID")==0)
            PayoffID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            OptionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "THIRDPARAMETER")==0)
            ThirdParameter_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlStrikedTypePayoff::qlStrikedTypePayoff(
            const std::string& ObjectId,
            const std::string& PayoffID,
            const std::string& OptionType,
            double Strike,
            double ThirdParameter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlStrikedTypePayoff", Permanent),
        PayoffID_(PayoffID),
        OptionType_(OptionType),
        Strike_(Strike),
        ThirdParameter_(ThirdParameter),
        Permanent_(Permanent) {
                  

            
    }

 } }
