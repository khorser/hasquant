
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
#include <qlo/smilesection.hpp>
#include <qlo/valueobjects/vo_smilesection.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlFlatSmileSection::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionDate",
        "Volatility",
        "DayCounter",
        "RefDate",
        "AtmValue",
        "Permanent"
    };

    std::set<std::string> qlFlatSmileSection::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFlatSmileSection::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFlatSmileSection::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFlatSmileSection::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            return OptionDate_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            return Volatility_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "REFDATE")==0)
            return RefDate_;
        else if(strcmp(nameUpper.c_str(), "ATMVALUE")==0)
            return AtmValue_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFlatSmileSection::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            OptionDate_ = value;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            Volatility_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REFDATE")==0)
            RefDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ATMVALUE")==0)
            AtmValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFlatSmileSection::qlFlatSmileSection(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            double Volatility,
            const std::string& DayCounter,
            const ObjectHandler::property_t& RefDate,
            double AtmValue,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFlatSmileSection", Permanent),
        OptionDate_(OptionDate),
        Volatility_(Volatility),
        DayCounter_(DayCounter),
        RefDate_(RefDate),
        AtmValue_(AtmValue),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlInterpolatedSmileSection::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionDate",
        "Strikes",
        "StdDevs",
        "AtmLevel",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlInterpolatedSmileSection::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlInterpolatedSmileSection::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlInterpolatedSmileSection::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlInterpolatedSmileSection::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            return OptionDate_;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            return Strikes_;
        else if(strcmp(nameUpper.c_str(), "STDDEVS")==0)
            return StdDevs_;
        else if(strcmp(nameUpper.c_str(), "ATMLEVEL")==0)
            return AtmLevel_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlInterpolatedSmileSection::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            OptionDate_ = value;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STDDEVS")==0)
            StdDevs_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ATMLEVEL")==0)
            AtmLevel_ = value;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlInterpolatedSmileSection::qlInterpolatedSmileSection(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t& AtmLevel,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlInterpolatedSmileSection", Permanent),
        OptionDate_(OptionDate),
        Strikes_(Strikes),
        StdDevs_(StdDevs),
        AtmLevel_(AtmLevel),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(StdDevs);
            processVariant(AtmLevel);
            
    }

    const char* qlSabrInterpolatedSmileSection::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionDate",
        "ForwardRate",
        "Strike",
        "FloatingStrike",
        "AtmVolatility",
        "VolatilitySpreads",
        "Alpha",
        "Beta",
        "Nu",
        "Rho",
        "AlphaIsFixed",
        "BetaIsFixed",
        "NuIsFixed",
        "RhoIsFixed",
        "VegaWeighted",
        "EndCriteria",
        "Method",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlSabrInterpolatedSmileSection::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSabrInterpolatedSmileSection::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSabrInterpolatedSmileSection::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSabrInterpolatedSmileSection::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            return OptionDate_;
        else if(strcmp(nameUpper.c_str(), "FORWARDRATE")==0)
            return ForwardRate_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGSTRIKE")==0)
            return FloatingStrike_;
        else if(strcmp(nameUpper.c_str(), "ATMVOLATILITY")==0)
            return AtmVolatility_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITYSPREADS")==0)
            return VolatilitySpreads_;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            return Alpha_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            return Nu_;
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            return Rho_;
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            return AlphaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            return BetaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            return NuIsFixed_;
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            return RhoIsFixed_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            return VegaWeighted_;
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            return EndCriteria_;
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            return Method_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSabrInterpolatedSmileSection::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            OptionDate_ = value;
        else if(strcmp(nameUpper.c_str(), "FORWARDRATE")==0)
            ForwardRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "FLOATINGSTRIKE")==0)
            FloatingStrike_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ATMVOLATILITY")==0)
            AtmVolatility_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "VOLATILITYSPREADS")==0)
            VolatilitySpreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            Alpha_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            Nu_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            Rho_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            AlphaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            BetaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            NuIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            RhoIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            VegaWeighted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            EndCriteria_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            Method_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSabrInterpolatedSmileSection::qlSabrInterpolatedSmileSection(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            double ForwardRate,
            const std::vector<double>& Strike,
            bool FloatingStrike,
            double AtmVolatility,
            const std::vector<double>& VolatilitySpreads,
            double Alpha,
            double Beta,
            double Nu,
            double Rho,
            bool AlphaIsFixed,
            bool BetaIsFixed,
            bool NuIsFixed,
            bool RhoIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& Method,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSabrInterpolatedSmileSection", Permanent),
        OptionDate_(OptionDate),
        ForwardRate_(ForwardRate),
        Strike_(Strike),
        FloatingStrike_(FloatingStrike),
        AtmVolatility_(AtmVolatility),
        VolatilitySpreads_(VolatilitySpreads),
        Alpha_(Alpha),
        Beta_(Beta),
        Nu_(Nu),
        Rho_(Rho),
        AlphaIsFixed_(AlphaIsFixed),
        BetaIsFixed_(BetaIsFixed),
        NuIsFixed_(NuIsFixed),
        RhoIsFixed_(RhoIsFixed),
        VegaWeighted_(VegaWeighted),
        EndCriteria_(EndCriteria),
        Method_(Method),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processPrecedentID(EndCriteria);
            processPrecedentID(Method);
            
    }

    const char* qlSabrInterpolatedSmileSection1::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionDate",
        "ForwardRate",
        "Strike",
        "FloatingStrike",
        "AtmVolatility",
        "VolatilitySpreads",
        "Alpha",
        "Beta",
        "Nu",
        "Rho",
        "AlphaIsFixed",
        "BetaIsFixed",
        "NuIsFixed",
        "RhoIsFixed",
        "VegaWeighted",
        "EndCriteria",
        "Method",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlSabrInterpolatedSmileSection1::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSabrInterpolatedSmileSection1::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSabrInterpolatedSmileSection1::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSabrInterpolatedSmileSection1::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            return OptionDate_;
        else if(strcmp(nameUpper.c_str(), "FORWARDRATE")==0)
            return ForwardRate_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGSTRIKE")==0)
            return FloatingStrike_;
        else if(strcmp(nameUpper.c_str(), "ATMVOLATILITY")==0)
            return AtmVolatility_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITYSPREADS")==0)
            return VolatilitySpreads_;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            return Alpha_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            return Nu_;
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            return Rho_;
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            return AlphaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            return BetaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            return NuIsFixed_;
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            return RhoIsFixed_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            return VegaWeighted_;
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            return EndCriteria_;
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            return Method_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSabrInterpolatedSmileSection1::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            OptionDate_ = value;
        else if(strcmp(nameUpper.c_str(), "FORWARDRATE")==0)
            ForwardRate_ = value;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "FLOATINGSTRIKE")==0)
            FloatingStrike_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ATMVOLATILITY")==0)
            AtmVolatility_ = value;
        else if(strcmp(nameUpper.c_str(), "VOLATILITYSPREADS")==0)
            VolatilitySpreads_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            Alpha_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            Nu_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            Rho_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            AlphaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            BetaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            NuIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            RhoIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            VegaWeighted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            EndCriteria_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            Method_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSabrInterpolatedSmileSection1::qlSabrInterpolatedSmileSection1(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            const ObjectHandler::property_t& ForwardRate,
            const std::vector<double>& Strike,
            bool FloatingStrike,
            const ObjectHandler::property_t& AtmVolatility,
            const std::vector<ObjectHandler::property_t>& VolatilitySpreads,
            double Alpha,
            double Beta,
            double Nu,
            double Rho,
            bool AlphaIsFixed,
            bool BetaIsFixed,
            bool NuIsFixed,
            bool RhoIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& Method,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSabrInterpolatedSmileSection1", Permanent),
        OptionDate_(OptionDate),
        ForwardRate_(ForwardRate),
        Strike_(Strike),
        FloatingStrike_(FloatingStrike),
        AtmVolatility_(AtmVolatility),
        VolatilitySpreads_(VolatilitySpreads),
        Alpha_(Alpha),
        Beta_(Beta),
        Nu_(Nu),
        Rho_(Rho),
        AlphaIsFixed_(AlphaIsFixed),
        BetaIsFixed_(BetaIsFixed),
        NuIsFixed_(NuIsFixed),
        RhoIsFixed_(RhoIsFixed),
        VegaWeighted_(VegaWeighted),
        EndCriteria_(EndCriteria),
        Method_(Method),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(ForwardRate);
            processVariant(AtmVolatility);
            processVariant(VolatilitySpreads);
            processPrecedentID(EndCriteria);
            processPrecedentID(Method);
            
    }

    const char* qlSabrSmileSection::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionTime",
        "Strikes",
        "StdDevs",
        "Forward",
        "Alpha",
        "Beta",
        "Nu",
        "Rho",
        "AlphaIsFixed",
        "BetaIsFixed",
        "NuIsFixed",
        "RhoIsFixed",
        "VegaWeighted",
        "EndCriteria",
        "Method",
        "Permanent"
    };

    std::set<std::string> qlSabrSmileSection::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSabrSmileSection::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSabrSmileSection::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSabrSmileSection::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTIME")==0)
            return OptionTime_;
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            return Strikes_;
        else if(strcmp(nameUpper.c_str(), "STDDEVS")==0)
            return StdDevs_;
        else if(strcmp(nameUpper.c_str(), "FORWARD")==0)
            return Forward_;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            return Alpha_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            return Nu_;
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            return Rho_;
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            return AlphaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            return BetaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            return NuIsFixed_;
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            return RhoIsFixed_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            return VegaWeighted_;
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            return EndCriteria_;
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            return Method_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSabrSmileSection::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTIME")==0)
            OptionTime_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STRIKES")==0)
            Strikes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STDDEVS")==0)
            StdDevs_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "FORWARD")==0)
            Forward_ = value;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            Alpha_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            Nu_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            Rho_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            AlphaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            BetaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            NuIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            RhoIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            VegaWeighted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            EndCriteria_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            Method_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSabrSmileSection::qlSabrSmileSection(
            const std::string& ObjectId,
            double OptionTime,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t& Forward,
            double Alpha,
            double Beta,
            double Nu,
            double Rho,
            bool AlphaIsFixed,
            bool BetaIsFixed,
            bool NuIsFixed,
            bool RhoIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& Method,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSabrSmileSection", Permanent),
        OptionTime_(OptionTime),
        Strikes_(Strikes),
        StdDevs_(StdDevs),
        Forward_(Forward),
        Alpha_(Alpha),
        Beta_(Beta),
        Nu_(Nu),
        Rho_(Rho),
        AlphaIsFixed_(AlphaIsFixed),
        BetaIsFixed_(BetaIsFixed),
        NuIsFixed_(NuIsFixed),
        RhoIsFixed_(RhoIsFixed),
        VegaWeighted_(VegaWeighted),
        EndCriteria_(EndCriteria),
        Method_(Method),
        Permanent_(Permanent) {
                  
            processVariant(StdDevs);
            processVariant(Forward);
            processPrecedentID(EndCriteria);
            processPrecedentID(Method);
            
    }

    const char* qlSmileSectionFromSabrVolSurface::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SabrVolSurface",
        "OptionTime",
        "Permanent"
    };

    std::set<std::string> qlSmileSectionFromSabrVolSurface::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSmileSectionFromSabrVolSurface::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSmileSectionFromSabrVolSurface::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSmileSectionFromSabrVolSurface::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SABRVOLSURFACE")==0)
            return SabrVolSurface_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTIME")==0)
            return OptionTime_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSmileSectionFromSabrVolSurface::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SABRVOLSURFACE")==0)
            SabrVolSurface_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTIME")==0)
            OptionTime_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSmileSectionFromSabrVolSurface::qlSmileSectionFromSabrVolSurface(
            const std::string& ObjectId,
            const std::string& SabrVolSurface,
            double OptionTime,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSmileSectionFromSabrVolSurface", Permanent),
        SabrVolSurface_(SabrVolSurface),
        OptionTime_(OptionTime),
        Permanent_(Permanent) {
                  
            processPrecedentID(SabrVolSurface);
            
    }

 } }
