
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
#include <qlo/shortratemodels.hpp>
#include <qlo/valueobjects/vo_shortratemodels.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlHullWhite::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "A",
        "Sigma",
        "Permanent"
    };

    std::set<std::string> qlHullWhite::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlHullWhite::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlHullWhite::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlHullWhite::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "A")==0)
            return A_;
        else if(strcmp(nameUpper.c_str(), "SIGMA")==0)
            return Sigma_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlHullWhite::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "A")==0)
            A_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SIGMA")==0)
            Sigma_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlHullWhite::qlHullWhite(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            double A,
            double Sigma,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlHullWhite", Permanent),
        YieldCurve_(YieldCurve),
        A_(A),
        Sigma_(Sigma),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlVasicek::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "A",
        "B",
        "Lambda",
        "Sigma",
        "Permanent"
    };

    std::set<std::string> qlVasicek::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlVasicek::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlVasicek::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlVasicek::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "A")==0)
            return A_;
        else if(strcmp(nameUpper.c_str(), "B")==0)
            return B_;
        else if(strcmp(nameUpper.c_str(), "LAMBDA")==0)
            return Lambda_;
        else if(strcmp(nameUpper.c_str(), "SIGMA")==0)
            return Sigma_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlVasicek::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "A")==0)
            A_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "B")==0)
            B_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "LAMBDA")==0)
            Lambda_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SIGMA")==0)
            Sigma_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlVasicek::qlVasicek(
            const std::string& ObjectId,
            double A,
            double B,
            double Lambda,
            double Sigma,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlVasicek", Permanent),
        A_(A),
        B_(B),
        Lambda_(Lambda),
        Sigma_(Sigma),
        Permanent_(Permanent) {
                  

            
    }

 } }
