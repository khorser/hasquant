
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
#include <qlo/piecewiseyieldcurve.hpp>
#include <qlo/valueobjects/vo_piecewiseyieldcurve.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlPiecewiseYieldCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "NDays",
        "Calendar",
        "RateHelpers",
        "DayCounter",
        "Jumps",
        "JumpDates",
        "Accuracy",
        "TraitsID",
        "InterpolatorID",
        "Permanent"
    };

    std::set<std::string> qlPiecewiseYieldCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPiecewiseYieldCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPiecewiseYieldCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPiecewiseYieldCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "NDAYS")==0)
            return NDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "RATEHELPERS")==0)
            return RateHelpers_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "JUMPS")==0)
            return Jumps_;
        else if(strcmp(nameUpper.c_str(), "JUMPDATES")==0)
            return JumpDates_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "TRAITSID")==0)
            return TraitsID_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORID")==0)
            return InterpolatorID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPiecewiseYieldCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NDAYS")==0)
            NDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATEHELPERS")==0)
            RateHelpers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "JUMPS")==0)
            Jumps_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "JUMPDATES")==0)
            JumpDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TRAITSID")==0)
            TraitsID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORID")==0)
            InterpolatorID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPiecewiseYieldCurve::qlPiecewiseYieldCurve(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const std::vector<std::string>& RateHelpers,
            const std::string& DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
            double Accuracy,
            const std::string& TraitsID,
            const std::string& InterpolatorID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPiecewiseYieldCurve", Permanent),
        NDays_(NDays),
        Calendar_(Calendar),
        RateHelpers_(RateHelpers),
        DayCounter_(DayCounter),
        Jumps_(Jumps),
        JumpDates_(JumpDates),
        Accuracy_(Accuracy),
        TraitsID_(TraitsID),
        InterpolatorID_(InterpolatorID),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = RateHelpers.begin();
                    i != RateHelpers.end(); ++i)
                processPrecedentID(*i);
            processVariant(Jumps);
            
    }

 } }
