
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
#include <qlo/processes.hpp>
#include <qlo/valueobjects/vo_processes.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlGeneralizedBlackScholesProcess::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BlackVolID",
        "Underlying",
        "DayCounter",
        "SettlementDate",
        "RiskFreeRate",
        "DividendYield",
        "Permanent"
    };

    std::set<std::string> qlGeneralizedBlackScholesProcess::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGeneralizedBlackScholesProcess::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGeneralizedBlackScholesProcess::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGeneralizedBlackScholesProcess::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BLACKVOLID")==0)
            return BlackVolID_;
        else if(strcmp(nameUpper.c_str(), "UNDERLYING")==0)
            return Underlying_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            return SettlementDate_;
        else if(strcmp(nameUpper.c_str(), "RISKFREERATE")==0)
            return RiskFreeRate_;
        else if(strcmp(nameUpper.c_str(), "DIVIDENDYIELD")==0)
            return DividendYield_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGeneralizedBlackScholesProcess::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BLACKVOLID")==0)
            BlackVolID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UNDERLYING")==0)
            Underlying_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            SettlementDate_ = value;
        else if(strcmp(nameUpper.c_str(), "RISKFREERATE")==0)
            RiskFreeRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DIVIDENDYIELD")==0)
            DividendYield_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGeneralizedBlackScholesProcess::qlGeneralizedBlackScholesProcess(
            const std::string& ObjectId,
            const std::string& BlackVolID,
            double Underlying,
            const std::string& DayCounter,
            const ObjectHandler::property_t& SettlementDate,
            double RiskFreeRate,
            double DividendYield,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGeneralizedBlackScholesProcess", Permanent),
        BlackVolID_(BlackVolID),
        Underlying_(Underlying),
        DayCounter_(DayCounter),
        SettlementDate_(SettlementDate),
        RiskFreeRate_(RiskFreeRate),
        DividendYield_(DividendYield),
        Permanent_(Permanent) {
                  
            processPrecedentID(BlackVolID);
            
    }

 } }
