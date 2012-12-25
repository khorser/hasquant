
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
#include <qlo/overnightindexedswap.hpp>
#include <qlo/valueobjects/vo_overnightindexedswap.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlMakeDatedOIS::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "StartDate",
        "EndDate",
        "OvernightIndex",
        "FixedRate",
        "FixDayCounter",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlMakeDatedOIS::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMakeDatedOIS::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMakeDatedOIS::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMakeDatedOIS::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            return EndDate_;
        else if(strcmp(nameUpper.c_str(), "OVERNIGHTINDEX")==0)
            return OvernightIndex_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            return FixDayCounter_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMakeDatedOIS::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            EndDate_ = value;
        else if(strcmp(nameUpper.c_str(), "OVERNIGHTINDEX")==0)
            OvernightIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            FixDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMakeDatedOIS::qlMakeDatedOIS(
            const std::string& ObjectId,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const std::string& OvernightIndex,
            double FixedRate,
            const std::string& FixDayCounter,
            double Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMakeDatedOIS", Permanent),
        StartDate_(StartDate),
        EndDate_(EndDate),
        OvernightIndex_(OvernightIndex),
        FixedRate_(FixedRate),
        FixDayCounter_(FixDayCounter),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processPrecedentID(OvernightIndex);
            
    }

    const char* qlMakeOIS::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapTenor",
        "OvernightIndex",
        "FixedRate",
        "ForwardStart",
        "FixDayCounter",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlMakeOIS::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMakeOIS::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMakeOIS::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMakeOIS::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            return SwapTenor_;
        else if(strcmp(nameUpper.c_str(), "OVERNIGHTINDEX")==0)
            return OvernightIndex_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            return ForwardStart_;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            return FixDayCounter_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMakeOIS::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            SwapTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OVERNIGHTINDEX")==0)
            OvernightIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            ForwardStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            FixDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMakeOIS::qlMakeOIS(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& OvernightIndex,
            double FixedRate,
            const std::string& ForwardStart,
            const std::string& FixDayCounter,
            double Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMakeOIS", Permanent),
        SwapTenor_(SwapTenor),
        OvernightIndex_(OvernightIndex),
        FixedRate_(FixedRate),
        ForwardStart_(ForwardStart),
        FixDayCounter_(FixDayCounter),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processPrecedentID(OvernightIndex);
            
    }

    const char* qlOvernightIndexedSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PayerReceiver",
        "Nominal",
        "Schedule",
        "FixedRate",
        "FixDayCounter",
        "OvernightIndex",
        "Spread",
        "Permanent"
    };

    std::set<std::string> qlOvernightIndexedSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlOvernightIndexedSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlOvernightIndexedSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlOvernightIndexedSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYERRECEIVER")==0)
            return PayerReceiver_;
        else if(strcmp(nameUpper.c_str(), "NOMINAL")==0)
            return Nominal_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULE")==0)
            return Schedule_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            return FixDayCounter_;
        else if(strcmp(nameUpper.c_str(), "OVERNIGHTINDEX")==0)
            return OvernightIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlOvernightIndexedSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYERRECEIVER")==0)
            PayerReceiver_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINAL")==0)
            Nominal_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SCHEDULE")==0)
            Schedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            FixDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OVERNIGHTINDEX")==0)
            OvernightIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlOvernightIndexedSwap::qlOvernightIndexedSwap(
            const std::string& ObjectId,
            const std::string& PayerReceiver,
            const std::vector<double>& Nominal,
            const std::string& Schedule,
            double FixedRate,
            const std::string& FixDayCounter,
            const std::string& OvernightIndex,
            double Spread,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlOvernightIndexedSwap", Permanent),
        PayerReceiver_(PayerReceiver),
        Nominal_(Nominal),
        Schedule_(Schedule),
        FixedRate_(FixedRate),
        FixDayCounter_(FixDayCounter),
        OvernightIndex_(OvernightIndex),
        Spread_(Spread),
        Permanent_(Permanent) {
                  
            processPrecedentID(Schedule);
            processPrecedentID(OvernightIndex);
            
    }

    const char* qlOvernightIndexedSwapFromOISRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OISRateHelper",
        "Permanent"
    };

    std::set<std::string> qlOvernightIndexedSwapFromOISRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlOvernightIndexedSwapFromOISRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlOvernightIndexedSwapFromOISRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlOvernightIndexedSwapFromOISRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OISRATEHELPER")==0)
            return OISRateHelper_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlOvernightIndexedSwapFromOISRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OISRATEHELPER")==0)
            OISRateHelper_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlOvernightIndexedSwapFromOISRateHelper::qlOvernightIndexedSwapFromOISRateHelper(
            const std::string& ObjectId,
            const std::string& OISRateHelper,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlOvernightIndexedSwapFromOISRateHelper", Permanent),
        OISRateHelper_(OISRateHelper),
        Permanent_(Permanent) {
                  
            processPrecedentID(OISRateHelper);
            
    }

 } }
