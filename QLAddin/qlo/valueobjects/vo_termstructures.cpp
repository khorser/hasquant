
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
#include <qlo/termstructures.hpp>
#include <qlo/valueobjects/vo_termstructures.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlDiscountCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurveDates",
        "CurveDiscounts",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlDiscountCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDiscountCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDiscountCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDiscountCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            return CurveDates_;
        else if(strcmp(nameUpper.c_str(), "CURVEDISCOUNTS")==0)
            return CurveDiscounts_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDiscountCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            CurveDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVEDISCOUNTS")==0)
            CurveDiscounts_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDiscountCurve::qlDiscountCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveDiscounts,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDiscountCurve", Permanent),
        CurveDates_(CurveDates),
        CurveDiscounts_(CurveDiscounts),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlFlatForward::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "NDays",
        "Calendar",
        "Rate",
        "DayCounter",
        "Compounding",
        "Frequency",
        "Permanent"
    };

    std::set<std::string> qlFlatForward::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFlatForward::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFlatForward::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFlatForward::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "NDAYS")==0)
            return NDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "COMPOUNDING")==0)
            return Compounding_;
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            return Frequency_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFlatForward::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NDAYS")==0)
            NDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = value;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COMPOUNDING")==0)
            Compounding_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            Frequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFlatForward::qlFlatForward(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const ObjectHandler::property_t& Rate,
            const std::string& DayCounter,
            const std::string& Compounding,
            const std::string& Frequency,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFlatForward", Permanent),
        NDays_(NDays),
        Calendar_(Calendar),
        Rate_(Rate),
        DayCounter_(DayCounter),
        Compounding_(Compounding),
        Frequency_(Frequency),
        Permanent_(Permanent) {
                  
            processVariant(Rate);
            
    }

    const char* qlForwardCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurveDates",
        "ForwardYields",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlForwardCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            return CurveDates_;
        else if(strcmp(nameUpper.c_str(), "FORWARDYIELDS")==0)
            return ForwardYields_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            CurveDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "FORWARDYIELDS")==0)
            ForwardYields_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardCurve::qlForwardCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& ForwardYields,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardCurve", Permanent),
        CurveDates_(CurveDates),
        ForwardYields_(ForwardYields),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlForwardSpreadedTermStructure::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BaseYieldCurve",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlForwardSpreadedTermStructure::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardSpreadedTermStructure::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardSpreadedTermStructure::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardSpreadedTermStructure::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASEYIELDCURVE")==0)
            return BaseYieldCurve_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardSpreadedTermStructure::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASEYIELDCURVE")==0)
            BaseYieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardSpreadedTermStructure::qlForwardSpreadedTermStructure(
            const std::string& ObjectId,
            const std::string& BaseYieldCurve,
            const ObjectHandler::property_t& Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardSpreadedTermStructure", Permanent),
        BaseYieldCurve_(BaseYieldCurve),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processPrecedentID(BaseYieldCurve);
            processVariant(Spread);
            
    }

    const char* qlImpliedTermStructure::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BaseYieldCurve",
        "ReferenceDate",
        "Permanent"
    };

    std::set<std::string> qlImpliedTermStructure::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlImpliedTermStructure::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlImpliedTermStructure::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlImpliedTermStructure::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASEYIELDCURVE")==0)
            return BaseYieldCurve_;
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            return ReferenceDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlImpliedTermStructure::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASEYIELDCURVE")==0)
            BaseYieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            ReferenceDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlImpliedTermStructure::qlImpliedTermStructure(
            const std::string& ObjectId,
            const std::string& BaseYieldCurve,
            const ObjectHandler::property_t& ReferenceDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlImpliedTermStructure", Permanent),
        BaseYieldCurve_(BaseYieldCurve),
        ReferenceDate_(ReferenceDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(BaseYieldCurve);
            
    }

    const char* qlInterpolatedYieldCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Dates",
        "Data",
        "Calendar",
        "DayCounter",
        "Jumps",
        "JumpDates",
        "TraitsID",
        "InterpolatorID",
        "Permanent"
    };

    std::set<std::string> qlInterpolatedYieldCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlInterpolatedYieldCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlInterpolatedYieldCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlInterpolatedYieldCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            return Dates_;
        else if(strcmp(nameUpper.c_str(), "DATA")==0)
            return Data_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "JUMPS")==0)
            return Jumps_;
        else if(strcmp(nameUpper.c_str(), "JUMPDATES")==0)
            return JumpDates_;
        else if(strcmp(nameUpper.c_str(), "TRAITSID")==0)
            return TraitsID_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORID")==0)
            return InterpolatorID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlInterpolatedYieldCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            Dates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DATA")==0)
            Data_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "JUMPS")==0)
            Jumps_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "JUMPDATES")==0)
            JumpDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TRAITSID")==0)
            TraitsID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORID")==0)
            InterpolatorID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlInterpolatedYieldCurve::qlInterpolatedYieldCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& Dates,
            const std::vector<double>& Data,
            const std::string& Calendar,
            const std::string& DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
            const std::string& TraitsID,
            const std::string& InterpolatorID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlInterpolatedYieldCurve", Permanent),
        Dates_(Dates),
        Data_(Data),
        Calendar_(Calendar),
        DayCounter_(DayCounter),
        Jumps_(Jumps),
        JumpDates_(JumpDates),
        TraitsID_(TraitsID),
        InterpolatorID_(InterpolatorID),
        Permanent_(Permanent) {
                  
            processVariant(Jumps);
            
    }

    const char* qlRelinkableHandleYieldTermStructure::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurrentLink",
        "Permanent"
    };

    std::set<std::string> qlRelinkableHandleYieldTermStructure::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRelinkableHandleYieldTermStructure::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRelinkableHandleYieldTermStructure::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRelinkableHandleYieldTermStructure::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURRENTLINK")==0)
            return CurrentLink_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRelinkableHandleYieldTermStructure::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENTLINK")==0)
            CurrentLink_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRelinkableHandleYieldTermStructure::qlRelinkableHandleYieldTermStructure(
            const std::string& ObjectId,
            const std::string& CurrentLink,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRelinkableHandleYieldTermStructure", Permanent),
        CurrentLink_(CurrentLink),
        Permanent_(Permanent) {
                  
            processPrecedentID(CurrentLink);
            
    }

    const char* qlZeroCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurveDates",
        "CurveYields",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlZeroCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlZeroCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlZeroCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlZeroCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            return CurveDates_;
        else if(strcmp(nameUpper.c_str(), "CURVEYIELDS")==0)
            return CurveYields_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlZeroCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            CurveDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVEYIELDS")==0)
            CurveYields_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlZeroCurve::qlZeroCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveYields,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlZeroCurve", Permanent),
        CurveDates_(CurveDates),
        CurveYields_(CurveYields),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

 } }
