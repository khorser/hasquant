
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
#include <qlo/forwardrateagreement.hpp>
#include <qlo/valueobjects/vo_forwardrateagreement.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlFRA::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ValueDate",
        "MaturityDate",
        "Position",
        "Strike",
        "Notional",
        "IborIndex",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlFRA::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFRA::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFRA::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFRA::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VALUEDATE")==0)
            return ValueDate_;
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            return MaturityDate_;
        else if(strcmp(nameUpper.c_str(), "POSITION")==0)
            return Position_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            return Notional_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFRA::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VALUEDATE")==0)
            ValueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            MaturityDate_ = value;
        else if(strcmp(nameUpper.c_str(), "POSITION")==0)
            Position_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            Notional_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFRA::qlFRA(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ValueDate,
            const ObjectHandler::property_t& MaturityDate,
            const std::string& Position,
            double Strike,
            double Notional,
            const std::string& IborIndex,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFRA", Permanent),
        ValueDate_(ValueDate),
        MaturityDate_(MaturityDate),
        Position_(Position),
        Strike_(Strike),
        Notional_(Notional),
        IborIndex_(IborIndex),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processPrecedentID(YieldCurve);
            
    }

 } }
