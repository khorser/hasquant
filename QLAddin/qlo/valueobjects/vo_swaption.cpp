
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
#include <qlo/swaption.hpp>
#include <qlo/valueobjects/vo_swaption.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlMakeSwaption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapIndex",
        "OptionTenor",
        "Strike",
        "PricingEngineID",
        "Permanent"
    };

    std::set<std::string> qlMakeSwaption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMakeSwaption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMakeSwaption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMakeSwaption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            return SwapIndex_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENOR")==0)
            return OptionTenor_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            return PricingEngineID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMakeSwaption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            SwapIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENOR")==0)
            OptionTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            PricingEngineID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMakeSwaption::qlMakeSwaption(
            const std::string& ObjectId,
            const std::string& SwapIndex,
            const std::string& OptionTenor,
            double Strike,
            const std::string& PricingEngineID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMakeSwaption", Permanent),
        SwapIndex_(SwapIndex),
        OptionTenor_(OptionTenor),
        Strike_(Strike),
        PricingEngineID_(PricingEngineID),
        Permanent_(Permanent) {
                  
            processPrecedentID(SwapIndex);
            processPrecedentID(PricingEngineID);
            
    }

    const char* qlSwaption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "VanillaSwap",
        "Exercise",
        "SettlementType",
        "Permanent"
    };

    std::set<std::string> qlSwaption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwaption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwaption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwaption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VANILLASWAP")==0)
            return VanillaSwap_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTTYPE")==0)
            return SettlementType_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwaption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VANILLASWAP")==0)
            VanillaSwap_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTTYPE")==0)
            SettlementType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwaption::qlSwaption(
            const std::string& ObjectId,
            const std::string& VanillaSwap,
            const std::string& Exercise,
            const std::string& SettlementType,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwaption", Permanent),
        VanillaSwap_(VanillaSwap),
        Exercise_(Exercise),
        SettlementType_(SettlementType),
        Permanent_(Permanent) {
                  
            processPrecedentID(VanillaSwap);
            processPrecedentID(Exercise);
            
    }

 } }
