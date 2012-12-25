
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
#include <qlo/volatilities.hpp>
#include <qlo/valueobjects/vo_volatilities.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAbcdAtmVolCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlementDays",
        "Calendar",
        "OptionTenors",
        "VolatilitiesQuotes",
        "InclusionInInterpolation",
        "Convention",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlAbcdAtmVolCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAbcdAtmVolCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAbcdAtmVolCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAbcdAtmVolCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            return OptionTenors_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIESQUOTES")==0)
            return VolatilitiesQuotes_;
        else if(strcmp(nameUpper.c_str(), "INCLUSIONININTERPOLATION")==0)
            return InclusionInInterpolation_;
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            return Convention_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAbcdAtmVolCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            OptionTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIESQUOTES")==0)
            VolatilitiesQuotes_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "INCLUSIONININTERPOLATION")==0)
            InclusionInInterpolation_ = ObjectHandler::vector::convert2<bool>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            Convention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAbcdAtmVolCurve::qlAbcdAtmVolCurve(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& VolatilitiesQuotes,
            const std::vector<bool>& InclusionInInterpolation,
            const std::string& Convention,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAbcdAtmVolCurve", Permanent),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        OptionTenors_(OptionTenors),
        VolatilitiesQuotes_(VolatilitiesQuotes),
        InclusionInInterpolation_(InclusionInInterpolation),
        Convention_(Convention),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(VolatilitiesQuotes);
            
    }

    const char* qlBlackConstantVol::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlementDate",
        "Calendar",
        "Volatility",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlBlackConstantVol::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackConstantVol::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackConstantVol::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackConstantVol::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            return SettlementDate_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            return Volatility_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackConstantVol::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            SettlementDate_ = value;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            Volatility_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackConstantVol::qlBlackConstantVol(
            const std::string& ObjectId,
            const ObjectHandler::property_t& SettlementDate,
            const std::string& Calendar,
            double Volatility,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackConstantVol", Permanent),
        SettlementDate_(SettlementDate),
        Calendar_(Calendar),
        Volatility_(Volatility),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlBlackVarianceSurface::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SettlementDate",
        "Calendar",
        "Dates",
        "Strikes",
        "Volatilities",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlBlackVarianceSurface::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackVarianceSurface::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackVarianceSurface::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackVarianceSurface::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            return SettlementDate_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            return Dates_;
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

    void qlBlackVarianceSurface::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            SettlementDate_ = value;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DATES")==0)
            Dates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackVarianceSurface::qlBlackVarianceSurface(
            const std::string& ObjectId,
            const ObjectHandler::property_t& SettlementDate,
            const std::string& Calendar,
            const std::vector<ObjectHandler::property_t>& Dates,
            const std::vector<double>& Strikes,
            const std::vector<std::vector<double> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackVarianceSurface", Permanent),
        SettlementDate_(SettlementDate),
        Calendar_(Calendar),
        Dates_(Dates),
        Strikes_(Strikes),
        Volatilities_(Volatilities),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlSabrVolSurface::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "InterestRateIndex",
        "BlackAtmVolCurve",
        "OptionTenors",
        "AtmRateSpreads",
        "VolatilitiesQuotes",
        "Permanent"
    };

    std::set<std::string> qlSabrVolSurface::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSabrVolSurface::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSabrVolSurface::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSabrVolSurface::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "INTERESTRATEINDEX")==0)
            return InterestRateIndex_;
        else if(strcmp(nameUpper.c_str(), "BLACKATMVOLCURVE")==0)
            return BlackAtmVolCurve_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            return OptionTenors_;
        else if(strcmp(nameUpper.c_str(), "ATMRATESPREADS")==0)
            return AtmRateSpreads_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIESQUOTES")==0)
            return VolatilitiesQuotes_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSabrVolSurface::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERESTRATEINDEX")==0)
            InterestRateIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BLACKATMVOLCURVE")==0)
            BlackAtmVolCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            OptionTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ATMRATESPREADS")==0)
            AtmRateSpreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIESQUOTES")==0)
            VolatilitiesQuotes_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSabrVolSurface::qlSabrVolSurface(
            const std::string& ObjectId,
            const std::string& InterestRateIndex,
            const std::string& BlackAtmVolCurve,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<double>& AtmRateSpreads,
            const std::vector<std::vector<ObjectHandler::property_t> >& VolatilitiesQuotes,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSabrVolSurface", Permanent),
        InterestRateIndex_(InterestRateIndex),
        BlackAtmVolCurve_(BlackAtmVolCurve),
        OptionTenors_(OptionTenors),
        AtmRateSpreads_(AtmRateSpreads),
        VolatilitiesQuotes_(VolatilitiesQuotes),
        Permanent_(Permanent) {
                  
            processPrecedentID(InterestRateIndex);
            processPrecedentID(BlackAtmVolCurve);
            processVariant(VolatilitiesQuotes);
            
    }

 } }
