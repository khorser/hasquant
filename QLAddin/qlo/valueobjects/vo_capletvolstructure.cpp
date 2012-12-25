
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
#include <qlo/capletvolstructure.hpp>
#include <qlo/valueobjects/vo_capletvolstructure.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCapFloorTermVolCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlementDays",
        "Calendar",
        "BusinessDayConvention",
        "OptionTenors",
        "Volatilities",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlCapFloorTermVolCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCapFloorTermVolCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCapFloorTermVolCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCapFloorTermVolCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            return BusinessDayConvention_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            return OptionTenors_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            return Volatilities_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCapFloorTermVolCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            BusinessDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            OptionTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCapFloorTermVolCurve::qlCapFloorTermVolCurve(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& Volatilities,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCapFloorTermVolCurve", Permanent),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        BusinessDayConvention_(BusinessDayConvention),
        OptionTenors_(OptionTenors),
        Volatilities_(Volatilities),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Volatilities);
            
    }

    const char* qlCapFloorTermVolSurface::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlementDays",
        "Calendar",
        "BusinessDayConvention",
        "OptionTenors",
        "Strikes",
        "Volatilities",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlCapFloorTermVolSurface::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCapFloorTermVolSurface::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCapFloorTermVolSurface::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCapFloorTermVolSurface::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            return BusinessDayConvention_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            return OptionTenors_;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            return Strikes_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            return Volatilities_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCapFloorTermVolSurface::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            BusinessDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            OptionTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCapFloorTermVolSurface::qlCapFloorTermVolSurface(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<double>& Strikes,
            const std::vector<std::vector<ObjectHandler::property_t> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCapFloorTermVolSurface", Permanent),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        BusinessDayConvention_(BusinessDayConvention),
        OptionTenors_(OptionTenors),
        Strikes_(Strikes),
        Volatilities_(Volatilities),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Volatilities);
            
    }

    const char* qlConstantOptionletVolatility::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "NDays",
        "Calendar",
        "BusinessDayConvention",
        "Volatility",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlConstantOptionletVolatility::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlConstantOptionletVolatility::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlConstantOptionletVolatility::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlConstantOptionletVolatility::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "NDAYS")==0)
            return NDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            return BusinessDayConvention_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            return Volatility_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlConstantOptionletVolatility::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NDAYS")==0)
            NDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            BusinessDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            Volatility_ = value;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlConstantOptionletVolatility::qlConstantOptionletVolatility(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const ObjectHandler::property_t& Volatility,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlConstantOptionletVolatility", Permanent),
        NDays_(NDays),
        Calendar_(Calendar),
        BusinessDayConvention_(BusinessDayConvention),
        Volatility_(Volatility),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Volatility);
            
    }

    const char* qlOptionletStripper1::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "TermVolSurface",
        "IborIndex",
        "SwitchStrike",
        "Accuracy",
        "MaxIter",
        "Permanent"
    };

    std::set<std::string> qlOptionletStripper1::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlOptionletStripper1::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlOptionletStripper1::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlOptionletStripper1::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TERMVOLSURFACE")==0)
            return TermVolSurface_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SWITCHSTRIKE")==0)
            return SwitchStrike_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "MAXITER")==0)
            return MaxIter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlOptionletStripper1::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TERMVOLSURFACE")==0)
            TermVolSurface_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWITCHSTRIKE")==0)
            SwitchStrike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "MAXITER")==0)
            MaxIter_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlOptionletStripper1::qlOptionletStripper1(
            const std::string& ObjectId,
            const std::string& TermVolSurface,
            const std::string& IborIndex,
            double SwitchStrike,
            double Accuracy,
            long MaxIter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlOptionletStripper1", Permanent),
        TermVolSurface_(TermVolSurface),
        IborIndex_(IborIndex),
        SwitchStrike_(SwitchStrike),
        Accuracy_(Accuracy),
        MaxIter_(MaxIter),
        Permanent_(Permanent) {
                  
            processPrecedentID(TermVolSurface);
            processPrecedentID(IborIndex);
            
    }

    const char* qlOptionletStripper2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionletStripper1",
        "TermVolCurve",
        "Permanent"
    };

    std::set<std::string> qlOptionletStripper2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlOptionletStripper2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlOptionletStripper2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlOptionletStripper2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONLETSTRIPPER1")==0)
            return OptionletStripper1_;
        else if(strcmp(nameUpper.c_str(), "TERMVOLCURVE")==0)
            return TermVolCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlOptionletStripper2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONLETSTRIPPER1")==0)
            OptionletStripper1_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TERMVOLCURVE")==0)
            TermVolCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlOptionletStripper2::qlOptionletStripper2(
            const std::string& ObjectId,
            const std::string& OptionletStripper1,
            const std::string& TermVolCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlOptionletStripper2", Permanent),
        OptionletStripper1_(OptionletStripper1),
        TermVolCurve_(TermVolCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(OptionletStripper1);
            processPrecedentID(TermVolCurve);
            
    }

    const char* qlRelinkableHandleOptionletVolatilityStructure::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurrentLink",
        "Permanent"
    };

    std::set<std::string> qlRelinkableHandleOptionletVolatilityStructure::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRelinkableHandleOptionletVolatilityStructure::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRelinkableHandleOptionletVolatilityStructure::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRelinkableHandleOptionletVolatilityStructure::getSystemProperty(const std::string& name) const {
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

    void qlRelinkableHandleOptionletVolatilityStructure::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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

    qlRelinkableHandleOptionletVolatilityStructure::qlRelinkableHandleOptionletVolatilityStructure(
            const std::string& ObjectId,
            const std::string& CurrentLink,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRelinkableHandleOptionletVolatilityStructure", Permanent),
        CurrentLink_(CurrentLink),
        Permanent_(Permanent) {
                  
            processPrecedentID(CurrentLink);
            
    }

    const char* qlSpreadedOptionletVolatility::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BaseVolStructure",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlSpreadedOptionletVolatility::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSpreadedOptionletVolatility::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSpreadedOptionletVolatility::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSpreadedOptionletVolatility::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASEVOLSTRUCTURE")==0)
            return BaseVolStructure_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSpreadedOptionletVolatility::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASEVOLSTRUCTURE")==0)
            BaseVolStructure_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSpreadedOptionletVolatility::qlSpreadedOptionletVolatility(
            const std::string& ObjectId,
            const std::string& BaseVolStructure,
            const ObjectHandler::property_t& Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSpreadedOptionletVolatility", Permanent),
        BaseVolStructure_(BaseVolStructure),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processPrecedentID(BaseVolStructure);
            processVariant(Spread);
            
    }

    const char* qlStrippedOptionlet::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlementDays",
        "Calendar",
        "BusinessDayConvention",
        "IborIndex",
        "OptionletDates",
        "Strikes",
        "Volatilities",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlStrippedOptionlet::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlStrippedOptionlet::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlStrippedOptionlet::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlStrippedOptionlet::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            return BusinessDayConvention_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "OPTIONLETDATES")==0)
            return OptionletDates_;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            return Strikes_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            return Volatilities_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlStrippedOptionlet::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            BusinessDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONLETDATES")==0)
            OptionletDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlStrippedOptionlet::qlStrippedOptionlet(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::string& IborIndex,
            const std::vector<ObjectHandler::property_t>& OptionletDates,
            const std::vector<double>& Strikes,
            const std::vector<std::vector<ObjectHandler::property_t> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlStrippedOptionlet", Permanent),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        BusinessDayConvention_(BusinessDayConvention),
        IborIndex_(IborIndex),
        OptionletDates_(OptionletDates),
        Strikes_(Strikes),
        Volatilities_(Volatilities),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processVariant(Volatilities);
            
    }

    const char* qlStrippedOptionletAdapter::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "StrippedOptionletBase",
        "Permanent"
    };

    std::set<std::string> qlStrippedOptionletAdapter::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlStrippedOptionletAdapter::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlStrippedOptionletAdapter::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlStrippedOptionletAdapter::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "STRIPPEDOPTIONLETBASE")==0)
            return StrippedOptionletBase_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlStrippedOptionletAdapter::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STRIPPEDOPTIONLETBASE")==0)
            StrippedOptionletBase_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlStrippedOptionletAdapter::qlStrippedOptionletAdapter(
            const std::string& ObjectId,
            const std::string& StrippedOptionletBase,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlStrippedOptionletAdapter", Permanent),
        StrippedOptionletBase_(StrippedOptionletBase),
        Permanent_(Permanent) {
                  
            processPrecedentID(StrippedOptionletBase);
            
    }

 } }
