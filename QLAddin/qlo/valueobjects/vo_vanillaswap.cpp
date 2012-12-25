
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
#include <qlo/vanillaswap.hpp>
#include <qlo/valueobjects/vo_vanillaswap.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlMakeIMMSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapTenor",
        "IborIndex",
        "FixedRate",
        "FirstImmDate",
        "FixDayCounter",
        "Spread",
        "PricingEngineID",
        "Permanent"
    };

    std::set<std::string> qlMakeIMMSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMakeIMMSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMakeIMMSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMakeIMMSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            return SwapTenor_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "FIRSTIMMDATE")==0)
            return FirstImmDate_;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            return FixDayCounter_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            return PricingEngineID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMakeIMMSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            SwapTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FIRSTIMMDATE")==0)
            FirstImmDate_ = value;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            FixDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            PricingEngineID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMakeIMMSwap::qlMakeIMMSwap(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& IborIndex,
            double FixedRate,
            const ObjectHandler::property_t& FirstImmDate,
            const std::string& FixDayCounter,
            double Spread,
            const std::string& PricingEngineID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMakeIMMSwap", Permanent),
        SwapTenor_(SwapTenor),
        IborIndex_(IborIndex),
        FixedRate_(FixedRate),
        FirstImmDate_(FirstImmDate),
        FixDayCounter_(FixDayCounter),
        Spread_(Spread),
        PricingEngineID_(PricingEngineID),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processPrecedentID(PricingEngineID);
            
    }

    const char* qlMakeVanillaSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapTenor",
        "IborIndex",
        "FixedRate",
        "ForwardStart",
        "FixDayCounter",
        "Spread",
        "PricingEngineID",
        "Permanent"
    };

    std::set<std::string> qlMakeVanillaSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMakeVanillaSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMakeVanillaSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMakeVanillaSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            return SwapTenor_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            return ForwardStart_;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            return FixDayCounter_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            return PricingEngineID_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMakeVanillaSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPTENOR")==0)
            SwapTenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            ForwardStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            FixDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PRICINGENGINEID")==0)
            PricingEngineID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMakeVanillaSwap::qlMakeVanillaSwap(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& IborIndex,
            double FixedRate,
            const std::string& ForwardStart,
            const std::string& FixDayCounter,
            double Spread,
            const std::string& PricingEngineID,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMakeVanillaSwap", Permanent),
        SwapTenor_(SwapTenor),
        IborIndex_(IborIndex),
        FixedRate_(FixedRate),
        ForwardStart_(ForwardStart),
        FixDayCounter_(FixDayCounter),
        Spread_(Spread),
        PricingEngineID_(PricingEngineID),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processPrecedentID(PricingEngineID);
            
    }

    const char* qlVanillaSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PayerReceiver",
        "Nominal",
        "FixSchedule",
        "FixedRate",
        "FixDayCounter",
        "FloatingLegSchedule",
        "IborIndex",
        "Spread",
        "FloatingLegDayCounter",
        "PaymentConvention",
        "Permanent"
    };

    std::set<std::string> qlVanillaSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlVanillaSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlVanillaSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlVanillaSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYERRECEIVER")==0)
            return PayerReceiver_;
        else if(strcmp(nameUpper.c_str(), "NOMINAL")==0)
            return Nominal_;
        else if(strcmp(nameUpper.c_str(), "FIXSCHEDULE")==0)
            return FixSchedule_;
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            return FixedRate_;
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            return FixDayCounter_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGSCHEDULE")==0)
            return FloatingLegSchedule_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGDAYCOUNTER")==0)
            return FloatingLegDayCounter_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlVanillaSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYERRECEIVER")==0)
            PayerReceiver_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOMINAL")==0)
            Nominal_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FIXSCHEDULE")==0)
            FixSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXEDRATE")==0)
            FixedRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FIXDAYCOUNTER")==0)
            FixDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGSCHEDULE")==0)
            FloatingLegSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGDAYCOUNTER")==0)
            FloatingLegDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlVanillaSwap::qlVanillaSwap(
            const std::string& ObjectId,
            const std::string& PayerReceiver,
            double Nominal,
            const std::string& FixSchedule,
            double FixedRate,
            const std::string& FixDayCounter,
            const std::string& FloatingLegSchedule,
            const std::string& IborIndex,
            double Spread,
            const std::string& FloatingLegDayCounter,
            const std::string& PaymentConvention,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlVanillaSwap", Permanent),
        PayerReceiver_(PayerReceiver),
        Nominal_(Nominal),
        FixSchedule_(FixSchedule),
        FixedRate_(FixedRate),
        FixDayCounter_(FixDayCounter),
        FloatingLegSchedule_(FloatingLegSchedule),
        IborIndex_(IborIndex),
        Spread_(Spread),
        FloatingLegDayCounter_(FloatingLegDayCounter),
        PaymentConvention_(PaymentConvention),
        Permanent_(Permanent) {
                  
            processPrecedentID(FixSchedule);
            processPrecedentID(FloatingLegSchedule);
            processPrecedentID(IborIndex);
            
    }

    const char* qlVanillaSwapFromSwapIndex::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapIndex",
        "FixingDate",
        "Permanent"
    };

    std::set<std::string> qlVanillaSwapFromSwapIndex::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlVanillaSwapFromSwapIndex::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlVanillaSwapFromSwapIndex::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlVanillaSwapFromSwapIndex::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            return SwapIndex_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDATE")==0)
            return FixingDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlVanillaSwapFromSwapIndex::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            SwapIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDATE")==0)
            FixingDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlVanillaSwapFromSwapIndex::qlVanillaSwapFromSwapIndex(
            const std::string& ObjectId,
            const std::string& SwapIndex,
            const ObjectHandler::property_t& FixingDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlVanillaSwapFromSwapIndex", Permanent),
        SwapIndex_(SwapIndex),
        FixingDate_(FixingDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(SwapIndex);
            
    }

    const char* qlVanillaSwapFromSwapRateHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapRateHelper",
        "Permanent"
    };

    std::set<std::string> qlVanillaSwapFromSwapRateHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlVanillaSwapFromSwapRateHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlVanillaSwapFromSwapRateHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlVanillaSwapFromSwapRateHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPRATEHELPER")==0)
            return SwapRateHelper_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlVanillaSwapFromSwapRateHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPRATEHELPER")==0)
            SwapRateHelper_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlVanillaSwapFromSwapRateHelper::qlVanillaSwapFromSwapRateHelper(
            const std::string& ObjectId,
            const std::string& SwapRateHelper,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlVanillaSwapFromSwapRateHelper", Permanent),
        SwapRateHelper_(SwapRateHelper),
        Permanent_(Permanent) {
                  
            processPrecedentID(SwapRateHelper);
            
    }

 } }
