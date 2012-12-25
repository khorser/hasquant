
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
#include <qlo/credit.hpp>
#include <qlo/valueobjects/vo_credit.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCreditDefaultSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BuyerSeller",
        "Notional",
        "Upfront",
        "Spread",
        "PremiumSchedule",
        "PaymentConvention",
        "DayCounter",
        "SettlesAccrual",
        "PayAtDefault",
        "ProtectionStart",
        "UpfrontDate",
        "Permanent"
    };

    std::set<std::string> qlCreditDefaultSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCreditDefaultSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCreditDefaultSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCreditDefaultSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            return BuyerSeller_;
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            return Notional_;
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            return Upfront_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            return PremiumSchedule_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "SETTLESACCRUAL")==0)
            return SettlesAccrual_;
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            return PayAtDefault_;
        else if(strcmp(nameUpper.c_str(), "PROTECTIONSTART")==0)
            return ProtectionStart_;
        else if(strcmp(nameUpper.c_str(), "UPFRONTDATE")==0)
            return UpfrontDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCreditDefaultSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            BuyerSeller_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            Notional_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            Upfront_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            PremiumSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLESACCRUAL")==0)
            SettlesAccrual_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            PayAtDefault_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PROTECTIONSTART")==0)
            ProtectionStart_ = value;
        else if(strcmp(nameUpper.c_str(), "UPFRONTDATE")==0)
            UpfrontDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCreditDefaultSwap::qlCreditDefaultSwap(
            const std::string& ObjectId,
            const std::string& BuyerSeller,
            double Notional,
            double Upfront,
            double Spread,
            const std::string& PremiumSchedule,
            const std::string& PaymentConvention,
            const std::string& DayCounter,
            bool SettlesAccrual,
            bool PayAtDefault,
            const ObjectHandler::property_t& ProtectionStart,
            const ObjectHandler::property_t& UpfrontDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCreditDefaultSwap", Permanent),
        BuyerSeller_(BuyerSeller),
        Notional_(Notional),
        Upfront_(Upfront),
        Spread_(Spread),
        PremiumSchedule_(PremiumSchedule),
        PaymentConvention_(PaymentConvention),
        DayCounter_(DayCounter),
        SettlesAccrual_(SettlesAccrual),
        PayAtDefault_(PayAtDefault),
        ProtectionStart_(ProtectionStart),
        UpfrontDate_(UpfrontDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(PremiumSchedule);
            
    }

    const char* qlHazardRateCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurveDates",
        "CurveRates",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlHazardRateCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlHazardRateCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlHazardRateCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlHazardRateCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            return CurveDates_;
        else if(strcmp(nameUpper.c_str(), "CURVERATES")==0)
            return CurveRates_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlHazardRateCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            CurveDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVERATES")==0)
            CurveRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlHazardRateCurve::qlHazardRateCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveRates,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlHazardRateCurve", Permanent),
        CurveDates_(CurveDates),
        CurveRates_(CurveRates),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlMidPointCdsEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "DefaultCurve",
        "RecoveryRate",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlMidPointCdsEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMidPointCdsEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMidPointCdsEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMidPointCdsEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            return DefaultCurve_;
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            return RecoveryRate_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMidPointCdsEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            DefaultCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            RecoveryRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMidPointCdsEngine::qlMidPointCdsEngine(
            const std::string& ObjectId,
            const std::string& DefaultCurve,
            double RecoveryRate,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMidPointCdsEngine", Permanent),
        DefaultCurve_(DefaultCurve),
        RecoveryRate_(RecoveryRate),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(DefaultCurve);
            processPrecedentID(YieldCurve);
            
    }

    const char* qlPiecewiseFlatForwardCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ReferenceDate",
        "RateHelpers",
        "DayCounter",
        "Accuracy",
        "Permanent"
    };

    std::set<std::string> qlPiecewiseFlatForwardCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPiecewiseFlatForwardCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPiecewiseFlatForwardCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPiecewiseFlatForwardCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            return ReferenceDate_;
        else if(strcmp(nameUpper.c_str(), "RATEHELPERS")==0)
            return RateHelpers_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPiecewiseFlatForwardCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            ReferenceDate_ = value;
        else if(strcmp(nameUpper.c_str(), "RATEHELPERS")==0)
            RateHelpers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPiecewiseFlatForwardCurve::qlPiecewiseFlatForwardCurve(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ReferenceDate,
            const std::vector<std::string>& RateHelpers,
            const std::string& DayCounter,
            double Accuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPiecewiseFlatForwardCurve", Permanent),
        ReferenceDate_(ReferenceDate),
        RateHelpers_(RateHelpers),
        DayCounter_(DayCounter),
        Accuracy_(Accuracy),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = RateHelpers.begin();
                    i != RateHelpers.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlPiecewiseFlatHazardRateCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ReferenceDate",
        "Helpers",
        "DayCounter",
        "Accuracy",
        "Permanent"
    };

    std::set<std::string> qlPiecewiseFlatHazardRateCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPiecewiseFlatHazardRateCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPiecewiseFlatHazardRateCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPiecewiseFlatHazardRateCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            return ReferenceDate_;
        else if(strcmp(nameUpper.c_str(), "HELPERS")==0)
            return Helpers_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPiecewiseFlatHazardRateCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            ReferenceDate_ = value;
        else if(strcmp(nameUpper.c_str(), "HELPERS")==0)
            Helpers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPiecewiseFlatHazardRateCurve::qlPiecewiseFlatHazardRateCurve(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ReferenceDate,
            const std::vector<std::string>& Helpers,
            const std::string& DayCounter,
            double Accuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPiecewiseFlatHazardRateCurve", Permanent),
        ReferenceDate_(ReferenceDate),
        Helpers_(Helpers),
        DayCounter_(DayCounter),
        Accuracy_(Accuracy),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = Helpers.begin();
                    i != Helpers.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlSpreadCdsHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RunningSpread",
        "Tenor",
        "SettlementDays",
        "Calendar",
        "Frequency",
        "PaymentConvention",
        "GenRule",
        "DayCounter",
        "RecoveryRate",
        "DiscountingCurve",
        "SettleAccrual",
        "PayAtDefault",
        "Permanent"
    };

    std::set<std::string> qlSpreadCdsHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSpreadCdsHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSpreadCdsHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSpreadCdsHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            return RunningSpread_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            return Frequency_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            return GenRule_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            return RecoveryRate_;
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            return DiscountingCurve_;
        else if(strcmp(nameUpper.c_str(), "SETTLEACCRUAL")==0)
            return SettleAccrual_;
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            return PayAtDefault_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSpreadCdsHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            RunningSpread_ = value;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            Frequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            GenRule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            RecoveryRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            DiscountingCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEACCRUAL")==0)
            SettleAccrual_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            PayAtDefault_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSpreadCdsHelper::qlSpreadCdsHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& RunningSpread,
            const std::string& Tenor,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Frequency,
            const std::string& PaymentConvention,
            const std::string& GenRule,
            const std::string& DayCounter,
            double RecoveryRate,
            const std::string& DiscountingCurve,
            bool SettleAccrual,
            bool PayAtDefault,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSpreadCdsHelper", Permanent),
        RunningSpread_(RunningSpread),
        Tenor_(Tenor),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        Frequency_(Frequency),
        PaymentConvention_(PaymentConvention),
        GenRule_(GenRule),
        DayCounter_(DayCounter),
        RecoveryRate_(RecoveryRate),
        DiscountingCurve_(DiscountingCurve),
        SettleAccrual_(SettleAccrual),
        PayAtDefault_(PayAtDefault),
        Permanent_(Permanent) {
                  
            processVariant(RunningSpread);
            processPrecedentID(DiscountingCurve);
            
    }

    const char* qlUpfrontCdsHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "UpfrontSpread",
        "RunningSpread",
        "Tenor",
        "SettlementDays",
        "Calendar",
        "Frequency",
        "PaymentConvention",
        "GenRule",
        "DayCounter",
        "RecoveryRate",
        "DiscountingCurve",
        "UpfrontSettlementDays",
        "SettleAccrual",
        "PayAtDefault",
        "Permanent"
    };

    std::set<std::string> qlUpfrontCdsHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlUpfrontCdsHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlUpfrontCdsHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlUpfrontCdsHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "UPFRONTSPREAD")==0)
            return UpfrontSpread_;
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            return RunningSpread_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            return Frequency_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            return GenRule_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            return RecoveryRate_;
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            return DiscountingCurve_;
        else if(strcmp(nameUpper.c_str(), "UPFRONTSETTLEMENTDAYS")==0)
            return UpfrontSettlementDays_;
        else if(strcmp(nameUpper.c_str(), "SETTLEACCRUAL")==0)
            return SettleAccrual_;
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            return PayAtDefault_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlUpfrontCdsHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONTSPREAD")==0)
            UpfrontSpread_ = value;
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            RunningSpread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            Frequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            GenRule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            RecoveryRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            DiscountingCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONTSETTLEMENTDAYS")==0)
            UpfrontSettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEACCRUAL")==0)
            SettleAccrual_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            PayAtDefault_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlUpfrontCdsHelper::qlUpfrontCdsHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& UpfrontSpread,
            double RunningSpread,
            const std::string& Tenor,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Frequency,
            const std::string& PaymentConvention,
            const std::string& GenRule,
            const std::string& DayCounter,
            double RecoveryRate,
            const std::string& DiscountingCurve,
            long UpfrontSettlementDays,
            bool SettleAccrual,
            bool PayAtDefault,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlUpfrontCdsHelper", Permanent),
        UpfrontSpread_(UpfrontSpread),
        RunningSpread_(RunningSpread),
        Tenor_(Tenor),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        Frequency_(Frequency),
        PaymentConvention_(PaymentConvention),
        GenRule_(GenRule),
        DayCounter_(DayCounter),
        RecoveryRate_(RecoveryRate),
        DiscountingCurve_(DiscountingCurve),
        UpfrontSettlementDays_(UpfrontSettlementDays),
        SettleAccrual_(SettleAccrual),
        PayAtDefault_(PayAtDefault),
        Permanent_(Permanent) {
                  
            processVariant(UpfrontSpread);
            processPrecedentID(DiscountingCurve);
            
    }

 } }
