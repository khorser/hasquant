
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
#include <qlo/volatility.hpp>
#include <qlo/valueobjects/vo_volatility.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlMarketModelLmExtLinearExponentialVolModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FixingTimes",
        "A",
        "B",
        "C",
        "D",
        "Permanent"
    };

    std::set<std::string> qlMarketModelLmExtLinearExponentialVolModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMarketModelLmExtLinearExponentialVolModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMarketModelLmExtLinearExponentialVolModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMarketModelLmExtLinearExponentialVolModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FIXINGTIMES")==0)
            return FixingTimes_;
        else if(strcmp(nameUpper.c_str(), "A")==0)
            return A_;
        else if(strcmp(nameUpper.c_str(), "B")==0)
            return B_;
        else if(strcmp(nameUpper.c_str(), "C")==0)
            return C_;
        else if(strcmp(nameUpper.c_str(), "D")==0)
            return D_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMarketModelLmExtLinearExponentialVolModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGTIMES")==0)
            FixingTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "A")==0)
            A_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "B")==0)
            B_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "C")==0)
            C_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "D")==0)
            D_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMarketModelLmExtLinearExponentialVolModel::qlMarketModelLmExtLinearExponentialVolModel(
            const std::string& ObjectId,
            const std::vector<double>& FixingTimes,
            double A,
            double B,
            double C,
            double D,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMarketModelLmExtLinearExponentialVolModel", Permanent),
        FixingTimes_(FixingTimes),
        A_(A),
        B_(B),
        C_(C),
        D_(D),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlPiecewiseConstantAbcdVariance::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "A",
        "B",
        "C",
        "D",
        "ResetIndex",
        "RateTimes",
        "Permanent"
    };

    std::set<std::string> qlPiecewiseConstantAbcdVariance::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPiecewiseConstantAbcdVariance::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPiecewiseConstantAbcdVariance::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPiecewiseConstantAbcdVariance::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "A")==0)
            return A_;
        else if(strcmp(nameUpper.c_str(), "B")==0)
            return B_;
        else if(strcmp(nameUpper.c_str(), "C")==0)
            return C_;
        else if(strcmp(nameUpper.c_str(), "D")==0)
            return D_;
        else if(strcmp(nameUpper.c_str(), "RESETINDEX")==0)
            return ResetIndex_;
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            return RateTimes_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPiecewiseConstantAbcdVariance::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "A")==0)
            A_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "B")==0)
            B_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "C")==0)
            C_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "D")==0)
            D_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RESETINDEX")==0)
            ResetIndex_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            RateTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPiecewiseConstantAbcdVariance::qlPiecewiseConstantAbcdVariance(
            const std::string& ObjectId,
            double A,
            double B,
            double C,
            double D,
            long ResetIndex,
            const std::vector<double>& RateTimes,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPiecewiseConstantAbcdVariance", Permanent),
        A_(A),
        B_(B),
        C_(C),
        D_(D),
        ResetIndex_(ResetIndex),
        RateTimes_(RateTimes),
        Permanent_(Permanent) {
                  

            
    }

 } }
