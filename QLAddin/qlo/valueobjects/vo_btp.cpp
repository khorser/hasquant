
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
#include <qlo/btp.hpp>
#include <qlo/valueobjects/vo_btp.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBTP::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "MaturityDate",
        "Coupon",
        "StartDate",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlBTP::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBTP::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBTP::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBTP::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            return MaturityDate_;
        else if(strcmp(nameUpper.c_str(), "COUPON")==0)
            return Coupon_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBTP::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            MaturityDate_ = value;
        else if(strcmp(nameUpper.c_str(), "COUPON")==0)
            Coupon_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBTP::qlBTP(
            const std::string& ObjectId,
            const std::string& Description,
            const ObjectHandler::property_t& MaturityDate,
            double Coupon,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBTP", Permanent),
        Description_(Description),
        MaturityDate_(MaturityDate),
        Coupon_(Coupon),
        StartDate_(StartDate),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlBTP2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "MaturityDate",
        "Coupon",
        "Redemption",
        "StartDate",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlBTP2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBTP2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBTP2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBTP2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            return MaturityDate_;
        else if(strcmp(nameUpper.c_str(), "COUPON")==0)
            return Coupon_;
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            return Redemption_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBTP2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            MaturityDate_ = value;
        else if(strcmp(nameUpper.c_str(), "COUPON")==0)
            Coupon_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "REDEMPTION")==0)
            Redemption_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBTP2::qlBTP2(
            const std::string& ObjectId,
            const std::string& Description,
            const ObjectHandler::property_t& MaturityDate,
            double Coupon,
            double Redemption,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBTP2", Permanent),
        Description_(Description),
        MaturityDate_(MaturityDate),
        Coupon_(Coupon),
        Redemption_(Redemption),
        StartDate_(StartDate),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlCCTEU::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Description",
        "MaturityDate",
        "Spread",
        "FwdCurve",
        "StartDate",
        "IssueDate",
        "Permanent"
    };

    std::set<std::string> qlCCTEU::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCCTEU::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCCTEU::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCCTEU::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            return Description_;
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            return MaturityDate_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            return FwdCurve_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            return IssueDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCCTEU::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DESCRIPTION")==0)
            Description_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MATURITYDATE")==0)
            MaturityDate_ = value;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCURVE")==0)
            FwdCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ISSUEDATE")==0)
            IssueDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCCTEU::qlCCTEU(
            const std::string& ObjectId,
            const std::string& Description,
            const ObjectHandler::property_t& MaturityDate,
            double Spread,
            const std::string& FwdCurve,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCCTEU", Permanent),
        Description_(Description),
        MaturityDate_(MaturityDate),
        Spread_(Spread),
        FwdCurve_(FwdCurve),
        StartDate_(StartDate),
        IssueDate_(IssueDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(FwdCurve);
            
    }

    const char* qlRendistatoBasket::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BTPs",
        "Outstandings",
        "Prices",
        "Permanent"
    };

    std::set<std::string> qlRendistatoBasket::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRendistatoBasket::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRendistatoBasket::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRendistatoBasket::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BTPS")==0)
            return BTPs_;
        else if(strcmp(nameUpper.c_str(), "OUTSTANDINGS")==0)
            return Outstandings_;
        else if(strcmp(nameUpper.c_str(), "PRICES")==0)
            return Prices_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRendistatoBasket::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BTPS")==0)
            BTPs_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "OUTSTANDINGS")==0)
            Outstandings_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PRICES")==0)
            Prices_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRendistatoBasket::qlRendistatoBasket(
            const std::string& ObjectId,
            const std::vector<std::string>& BTPs,
            const std::vector<double>& Outstandings,
            const std::vector<ObjectHandler::property_t>& Prices,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRendistatoBasket", Permanent),
        BTPs_(BTPs),
        Outstandings_(Outstandings),
        Prices_(Prices),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = BTPs.begin();
                    i != BTPs.end(); ++i)
                processPrecedentID(*i);
            processVariant(Prices);
            
    }

    const char* qlRendistatoCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RendistatoBasket",
        "Euribor",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlRendistatoCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRendistatoCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRendistatoCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRendistatoCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RENDISTATOBASKET")==0)
            return RendistatoBasket_;
        else if(strcmp(nameUpper.c_str(), "EURIBOR")==0)
            return Euribor_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRendistatoCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RENDISTATOBASKET")==0)
            RendistatoBasket_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EURIBOR")==0)
            Euribor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRendistatoCalculator::qlRendistatoCalculator(
            const std::string& ObjectId,
            const std::string& RendistatoBasket,
            const std::string& Euribor,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRendistatoCalculator", Permanent),
        RendistatoBasket_(RendistatoBasket),
        Euribor_(Euribor),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(RendistatoBasket);
            processPrecedentID(Euribor);
            processPrecedentID(YieldCurve);
            
    }

    const char* qlRendistatoEquivalentSwapLengthQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RendistatoCalculator",
        "Permanent"
    };

    std::set<std::string> qlRendistatoEquivalentSwapLengthQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRendistatoEquivalentSwapLengthQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRendistatoEquivalentSwapLengthQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRendistatoEquivalentSwapLengthQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RENDISTATOCALCULATOR")==0)
            return RendistatoCalculator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRendistatoEquivalentSwapLengthQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RENDISTATOCALCULATOR")==0)
            RendistatoCalculator_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRendistatoEquivalentSwapLengthQuote::qlRendistatoEquivalentSwapLengthQuote(
            const std::string& ObjectId,
            const std::string& RendistatoCalculator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRendistatoEquivalentSwapLengthQuote", Permanent),
        RendistatoCalculator_(RendistatoCalculator),
        Permanent_(Permanent) {
                  
            processPrecedentID(RendistatoCalculator);
            
    }

    const char* qlRendistatoEquivalentSwapSpreadQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RendistatoCalculator",
        "Permanent"
    };

    std::set<std::string> qlRendistatoEquivalentSwapSpreadQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRendistatoEquivalentSwapSpreadQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRendistatoEquivalentSwapSpreadQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRendistatoEquivalentSwapSpreadQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RENDISTATOCALCULATOR")==0)
            return RendistatoCalculator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRendistatoEquivalentSwapSpreadQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RENDISTATOCALCULATOR")==0)
            RendistatoCalculator_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRendistatoEquivalentSwapSpreadQuote::qlRendistatoEquivalentSwapSpreadQuote(
            const std::string& ObjectId,
            const std::string& RendistatoCalculator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRendistatoEquivalentSwapSpreadQuote", Permanent),
        RendistatoCalculator_(RendistatoCalculator),
        Permanent_(Permanent) {
                  
            processPrecedentID(RendistatoCalculator);
            
    }

 } }
