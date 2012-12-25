
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
#include <qlo/capfloor.hpp>
#include <qlo/valueobjects/vo_capfloor.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCapFloor::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionType",
        "LegID",
        "Strikes",
        "Permanent"
    };

    std::set<std::string> qlCapFloor::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCapFloor::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCapFloor::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCapFloor::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            return OptionType_;
        else if(strcmp(nameUpper.c_str(), "LEGID")==0)
            return LegID_;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            return Strikes_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCapFloor::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            OptionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LEGID")==0)
            LegID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCapFloor::qlCapFloor(
            const std::string& ObjectId,
            const std::string& OptionType,
            const std::string& LegID,
            const std::vector<double>& Strikes,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCapFloor", Permanent),
        OptionType_(OptionType),
        LegID_(LegID),
        Strikes_(Strikes),
        Permanent_(Permanent) {
                  
            processPrecedentID(LegID);
            
    }

    const char* qlMakeCapFloor::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionType",
        "Length",
        "IborIndex",
        "Strike",
        "ForwardStart",
        "PricingEngineID",
        "Permanent"
    };

    std::set<std::string> qlMakeCapFloor::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMakeCapFloor::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMakeCapFloor::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMakeCapFloor::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            return OptionType_;
        else if(strcmp(nameUpper.c_str(), "LENGTH")==0)
            return Length_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            return ForwardStart_;
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            return PricingEngineID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMakeCapFloor::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            OptionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LENGTH")==0)
            Length_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            ForwardStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            PricingEngineID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMakeCapFloor::qlMakeCapFloor(
            const std::string& ObjectId,
            const std::string& OptionType,
            const std::string& Length,
            const std::string& IborIndex,
            double Strike,
            const std::string& ForwardStart,
            const std::string& PricingEngineID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMakeCapFloor", Permanent),
        OptionType_(OptionType),
        Length_(Length),
        IborIndex_(IborIndex),
        Strike_(Strike),
        ForwardStart_(ForwardStart),
        PricingEngineID_(PricingEngineID),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processPrecedentID(PricingEngineID);
            
    }

 } }
