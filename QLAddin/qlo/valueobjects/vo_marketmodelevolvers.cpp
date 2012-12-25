
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
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/valueobjects/vo_marketmodelevolvers.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlForwardRateIpc::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "MarketModel",
        "BrownianGeneratorFactory",
        "Numeraires",
        "Permanent"
    };

    std::set<std::string> qlForwardRateIpc::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardRateIpc::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardRateIpc::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardRateIpc::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "MARKETMODEL")==0)
            return MarketModel_;
        else if(strcmp(nameUpper.c_str(), "BROWNIANGENERATORFACTORY")==0)
            return BrownianGeneratorFactory_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRES")==0)
            return Numeraires_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardRateIpc::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MARKETMODEL")==0)
            MarketModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BROWNIANGENERATORFACTORY")==0)
            BrownianGeneratorFactory_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRES")==0)
            Numeraires_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardRateIpc::qlForwardRateIpc(
            const std::string& ObjectId,
            const std::string& MarketModel,
            const std::string& BrownianGeneratorFactory,
            const std::vector<long>& Numeraires,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardRateIpc", Permanent),
        MarketModel_(MarketModel),
        BrownianGeneratorFactory_(BrownianGeneratorFactory),
        Numeraires_(Numeraires),
        Permanent_(Permanent) {
                  
            processPrecedentID(MarketModel);
            processPrecedentID(BrownianGeneratorFactory);
            
    }

    const char* qlForwardRateNormalPc::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "MarketModel",
        "BrownianGeneratorFactory",
        "Numeraires",
        "Permanent"
    };

    std::set<std::string> qlForwardRateNormalPc::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardRateNormalPc::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardRateNormalPc::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardRateNormalPc::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "MARKETMODEL")==0)
            return MarketModel_;
        else if(strcmp(nameUpper.c_str(), "BROWNIANGENERATORFACTORY")==0)
            return BrownianGeneratorFactory_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRES")==0)
            return Numeraires_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardRateNormalPc::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MARKETMODEL")==0)
            MarketModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BROWNIANGENERATORFACTORY")==0)
            BrownianGeneratorFactory_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRES")==0)
            Numeraires_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardRateNormalPc::qlForwardRateNormalPc(
            const std::string& ObjectId,
            const std::string& MarketModel,
            const std::string& BrownianGeneratorFactory,
            const std::vector<long>& Numeraires,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardRateNormalPc", Permanent),
        MarketModel_(MarketModel),
        BrownianGeneratorFactory_(BrownianGeneratorFactory),
        Numeraires_(Numeraires),
        Permanent_(Permanent) {
                  
            processPrecedentID(MarketModel);
            processPrecedentID(BrownianGeneratorFactory);
            
    }

    const char* qlForwardRatePc::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "MarketModel",
        "BrownianGeneratorFactory",
        "Numeraires",
        "Permanent"
    };

    std::set<std::string> qlForwardRatePc::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardRatePc::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardRatePc::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardRatePc::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "MARKETMODEL")==0)
            return MarketModel_;
        else if(strcmp(nameUpper.c_str(), "BROWNIANGENERATORFACTORY")==0)
            return BrownianGeneratorFactory_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRES")==0)
            return Numeraires_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardRatePc::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MARKETMODEL")==0)
            MarketModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BROWNIANGENERATORFACTORY")==0)
            BrownianGeneratorFactory_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRES")==0)
            Numeraires_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardRatePc::qlForwardRatePc(
            const std::string& ObjectId,
            const std::string& MarketModel,
            const std::string& BrownianGeneratorFactory,
            const std::vector<long>& Numeraires,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardRatePc", Permanent),
        MarketModel_(MarketModel),
        BrownianGeneratorFactory_(BrownianGeneratorFactory),
        Numeraires_(Numeraires),
        Permanent_(Permanent) {
                  
            processPrecedentID(MarketModel);
            processPrecedentID(BrownianGeneratorFactory);
            
    }

 } }
