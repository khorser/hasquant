
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
#include <qlo/swaptionvolstructure.hpp>
#include <qlo/valueobjects/vo_swaptionvolstructure.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlConstantSwaptionVolatility::mPropertyNames[] = {
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

    std::set<std::string> qlConstantSwaptionVolatility::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlConstantSwaptionVolatility::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlConstantSwaptionVolatility::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlConstantSwaptionVolatility::getSystemProperty(const std::string& name) const {
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

    void qlConstantSwaptionVolatility::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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

    qlConstantSwaptionVolatility::qlConstantSwaptionVolatility(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const ObjectHandler::property_t& Volatility,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlConstantSwaptionVolatility", Permanent),
        NDays_(NDays),
        Calendar_(Calendar),
        BusinessDayConvention_(BusinessDayConvention),
        Volatility_(Volatility),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Volatility);
            
    }

    const char* qlRelinkableHandleSwaptionVolatilityStructure::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurrentLink",
        "Permanent"
    };

    std::set<std::string> qlRelinkableHandleSwaptionVolatilityStructure::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRelinkableHandleSwaptionVolatilityStructure::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRelinkableHandleSwaptionVolatilityStructure::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRelinkableHandleSwaptionVolatilityStructure::getSystemProperty(const std::string& name) const {
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

    void qlRelinkableHandleSwaptionVolatilityStructure::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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

    qlRelinkableHandleSwaptionVolatilityStructure::qlRelinkableHandleSwaptionVolatilityStructure(
            const std::string& ObjectId,
            const std::string& CurrentLink,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRelinkableHandleSwaptionVolatilityStructure", Permanent),
        CurrentLink_(CurrentLink),
        Permanent_(Permanent) {
                  
            processPrecedentID(CurrentLink);
            
    }

    const char* qlSmileSectionByCube::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "VolCube",
        "OptionDate",
        "SwapTenor",
        "Permanent"
    };

    std::set<std::string> qlSmileSectionByCube::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSmileSectionByCube::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSmileSectionByCube::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSmileSectionByCube::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VOLCUBE")==0)
            return VolCube_;
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            return OptionDate_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            return SwapTenor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSmileSectionByCube::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLCUBE")==0)
            VolCube_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            OptionDate_ = value;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            SwapTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSmileSectionByCube::qlSmileSectionByCube(
            const std::string& ObjectId,
            const std::string& VolCube,
            const ObjectHandler::property_t& OptionDate,
            const std::string& SwapTenor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSmileSectionByCube", Permanent),
        VolCube_(VolCube),
        OptionDate_(OptionDate),
        SwapTenor_(SwapTenor),
        Permanent_(Permanent) {
                  
            processPrecedentID(VolCube);
            
    }

    const char* qlSmileSectionByCube2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "VolCube",
        "OptionDate",
        "SwapTenor",
        "Permanent"
    };

    std::set<std::string> qlSmileSectionByCube2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSmileSectionByCube2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSmileSectionByCube2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSmileSectionByCube2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VOLCUBE")==0)
            return VolCube_;
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            return OptionDate_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            return SwapTenor_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSmileSectionByCube2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLCUBE")==0)
            VolCube_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONDATE")==0)
            OptionDate_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            SwapTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSmileSectionByCube2::qlSmileSectionByCube2(
            const std::string& ObjectId,
            const std::string& VolCube,
            const std::string& OptionDate,
            const std::string& SwapTenor,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSmileSectionByCube2", Permanent),
        VolCube_(VolCube),
        OptionDate_(OptionDate),
        SwapTenor_(SwapTenor),
        Permanent_(Permanent) {
                  
            processPrecedentID(VolCube);
            
    }

    const char* qlSpreadedSwaptionVolatility::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BaseVolStructure",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlSpreadedSwaptionVolatility::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSpreadedSwaptionVolatility::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSpreadedSwaptionVolatility::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSpreadedSwaptionVolatility::getSystemProperty(const std::string& name) const {
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

    void qlSpreadedSwaptionVolatility::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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

    qlSpreadedSwaptionVolatility::qlSpreadedSwaptionVolatility(
            const std::string& ObjectId,
            const std::string& BaseVolStructure,
            const ObjectHandler::property_t& Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSpreadedSwaptionVolatility", Permanent),
        BaseVolStructure_(BaseVolStructure),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processPrecedentID(BaseVolStructure);
            processVariant(Spread);
            
    }

    const char* qlSwaptionVTSMatrix::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Calendar",
        "BusinessDayConvention",
        "OptionTenors",
        "SwapTenors",
        "Volatilities",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlSwaptionVTSMatrix::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwaptionVTSMatrix::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwaptionVTSMatrix::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwaptionVTSMatrix::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            return BusinessDayConvention_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            return OptionTenors_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENORS")==0)
            return SwapTenors_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            return Volatilities_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwaptionVTSMatrix::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUSINESSDAYCONVENTION")==0)
            BusinessDayConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            OptionTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPTENORS")==0)
            SwapTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwaptionVTSMatrix::qlSwaptionVTSMatrix(
            const std::string& ObjectId,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& SwapTenors,
            const std::vector<std::vector<ObjectHandler::property_t> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwaptionVTSMatrix", Permanent),
        Calendar_(Calendar),
        BusinessDayConvention_(BusinessDayConvention),
        OptionTenors_(OptionTenors),
        SwapTenors_(SwapTenors),
        Volatilities_(Volatilities),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Volatilities);
            
    }

    const char* qlSwaptionVolCube1::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "AtmVolStructure",
        "OptionTenors",
        "SwapTenors",
        "StrikeSpreads",
        "SpreadVols",
        "SwapIndexBase",
        "ShortSwapIndexBase",
        "VegaWeightedSmileFit",
        "Guess",
        "IsFixed",
        "IsAtmCalibrated",
        "EndCriteria",
        "MaxErrorTol",
        "OptMethod",
        "Permanent"
    };

    std::set<std::string> qlSwaptionVolCube1::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwaptionVolCube1::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwaptionVolCube1::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwaptionVolCube1::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ATMVOLSTRUCTURE")==0)
            return AtmVolStructure_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            return OptionTenors_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENORS")==0)
            return SwapTenors_;
        else if(strcmp(nameUpper.c_str(), "STRIKESPREADS")==0)
            return StrikeSpreads_;
        else if(strcmp(nameUpper.c_str(), "SPREADVOLS")==0)
            return SpreadVols_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXBASE")==0)
            return SwapIndexBase_;
        else if(strcmp(nameUpper.c_str(), "SHORTSWAPINDEXBASE")==0)
            return ShortSwapIndexBase_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTEDSMILEFIT")==0)
            return VegaWeightedSmileFit_;
        else if(strcmp(nameUpper.c_str(), "GUESS")==0)
            return Guess_;
        else if(strcmp(nameUpper.c_str(), "ISFIXED")==0)
            return IsFixed_;
        else if(strcmp(nameUpper.c_str(), "ISATMCALIBRATED")==0)
            return IsAtmCalibrated_;
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            return EndCriteria_;
        else if(strcmp(nameUpper.c_str(), "MAXERRORTOL")==0)
            return MaxErrorTol_;
        else if(strcmp(nameUpper.c_str(), "OPTMETHOD")==0)
            return OptMethod_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwaptionVolCube1::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ATMVOLSTRUCTURE")==0)
            AtmVolStructure_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENORS")==0)
            OptionTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPTENORS")==0)
            SwapTenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STRIKESPREADS")==0)
            StrikeSpreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SPREADVOLS")==0)
            SpreadVols_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXBASE")==0)
            SwapIndexBase_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SHORTSWAPINDEXBASE")==0)
            ShortSwapIndexBase_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTEDSMILEFIT")==0)
            VegaWeightedSmileFit_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "GUESS")==0)
            Guess_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ISFIXED")==0)
            IsFixed_ = ObjectHandler::vector::convert2<bool>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ISATMCALIBRATED")==0)
            IsAtmCalibrated_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            EndCriteria_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MAXERRORTOL")==0)
            MaxErrorTol_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "OPTMETHOD")==0)
            OptMethod_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwaptionVolCube1::qlSwaptionVolCube1(
            const std::string& ObjectId,
            const std::string& AtmVolStructure,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& SwapTenors,
            const std::vector<double>& StrikeSpreads,
            const std::vector<std::vector<ObjectHandler::property_t> >& SpreadVols,
            const std::string& SwapIndexBase,
            const std::string& ShortSwapIndexBase,
            bool VegaWeightedSmileFit,
            const std::vector<std::vector<ObjectHandler::property_t> >& Guess,
            const std::vector<bool>& IsFixed,
            bool IsAtmCalibrated,
            const std::string& EndCriteria,
            double MaxErrorTol,
            const std::string& OptMethod,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwaptionVolCube1", Permanent),
        AtmVolStructure_(AtmVolStructure),
        OptionTenors_(OptionTenors),
        SwapTenors_(SwapTenors),
        StrikeSpreads_(StrikeSpreads),
        SpreadVols_(SpreadVols),
        SwapIndexBase_(SwapIndexBase),
        ShortSwapIndexBase_(ShortSwapIndexBase),
        VegaWeightedSmileFit_(VegaWeightedSmileFit),
        Guess_(Guess),
        IsFixed_(IsFixed),
        IsAtmCalibrated_(IsAtmCalibrated),
        EndCriteria_(EndCriteria),
        MaxErrorTol_(MaxErrorTol),
        OptMethod_(OptMethod),
        Permanent_(Permanent) {
                  
            processPrecedentID(AtmVolStructure);
            processVariant(SpreadVols);
            processPrecedentID(SwapIndexBase);
            processPrecedentID(ShortSwapIndexBase);
            processVariant(Guess);
            processPrecedentID(EndCriteria);
            processPrecedentID(OptMethod);
            
    }

    const char* qlSwaptionVolCube2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "AtmVolStructure",
        "OptionTenor",
        "SwapTenor",
        "StrikeSpreads",
        "SpreadVols",
        "SwapIndexBase",
        "ShortSwapIndexBase",
        "VegaWeightedSmileFit",
        "Permanent"
    };

    std::set<std::string> qlSwaptionVolCube2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSwaptionVolCube2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSwaptionVolCube2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSwaptionVolCube2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ATMVOLSTRUCTURE")==0)
            return AtmVolStructure_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTENOR")==0)
            return OptionTenor_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            return SwapTenor_;
        else if(strcmp(nameUpper.c_str(), "STRIKESPREADS")==0)
            return StrikeSpreads_;
        else if(strcmp(nameUpper.c_str(), "SPREADVOLS")==0)
            return SpreadVols_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXBASE")==0)
            return SwapIndexBase_;
        else if(strcmp(nameUpper.c_str(), "SHORTSWAPINDEXBASE")==0)
            return ShortSwapIndexBase_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTEDSMILEFIT")==0)
            return VegaWeightedSmileFit_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSwaptionVolCube2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ATMVOLSTRUCTURE")==0)
            AtmVolStructure_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTENOR")==0)
            OptionTenor_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            SwapTenor_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "STRIKESPREADS")==0)
            StrikeSpreads_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SPREADVOLS")==0)
            SpreadVols_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXBASE")==0)
            SwapIndexBase_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SHORTSWAPINDEXBASE")==0)
            ShortSwapIndexBase_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTEDSMILEFIT")==0)
            VegaWeightedSmileFit_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSwaptionVolCube2::qlSwaptionVolCube2(
            const std::string& ObjectId,
            const std::string& AtmVolStructure,
            const std::vector<ObjectHandler::property_t>& OptionTenor,
            const std::vector<ObjectHandler::property_t>& SwapTenor,
            const std::vector<double>& StrikeSpreads,
            const std::vector<std::vector<ObjectHandler::property_t> >& SpreadVols,
            const std::string& SwapIndexBase,
            const std::string& ShortSwapIndexBase,
            bool VegaWeightedSmileFit,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSwaptionVolCube2", Permanent),
        AtmVolStructure_(AtmVolStructure),
        OptionTenor_(OptionTenor),
        SwapTenor_(SwapTenor),
        StrikeSpreads_(StrikeSpreads),
        SpreadVols_(SpreadVols),
        SwapIndexBase_(SwapIndexBase),
        ShortSwapIndexBase_(ShortSwapIndexBase),
        VegaWeightedSmileFit_(VegaWeightedSmileFit),
        Permanent_(Permanent) {
                  
            processPrecedentID(AtmVolStructure);
            processVariant(SpreadVols);
            processPrecedentID(SwapIndexBase);
            processPrecedentID(ShortSwapIndexBase);
            
    }

 } }
