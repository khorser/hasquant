
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
#include <qlo/quotes.hpp>
#include <qlo/valueobjects/vo_quotes.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCompositeQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Element1",
        "Element2",
        "Operator",
        "Permanent"
    };

    std::set<std::string> qlCompositeQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCompositeQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCompositeQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCompositeQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ELEMENT1")==0)
            return Element1_;
        else if(strcmp(nameUpper.c_str(), "ELEMENT2")==0)
            return Element2_;
        else if(strcmp(nameUpper.c_str(), "OPERATOR")==0)
            return Operator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCompositeQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ELEMENT1")==0)
            Element1_ = value;
        else if(strcmp(nameUpper.c_str(), "ELEMENT2")==0)
            Element2_ = value;
        else if(strcmp(nameUpper.c_str(), "OPERATOR")==0)
            Operator_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCompositeQuote::qlCompositeQuote(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Element1,
            const ObjectHandler::property_t& Element2,
            const std::string& Operator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCompositeQuote", Permanent),
        Element1_(Element1),
        Element2_(Element2),
        Operator_(Operator),
        Permanent_(Permanent) {
                  
            processVariant(Element1);
            processVariant(Element2);
            
    }

    const char* qlEurodollarFuturesImpliedStdDevQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "AtmForwardValue",
        "CallPrice",
        "PutPrice",
        "Strike",
        "Guess",
        "Accuracy",
        "Permanent"
    };

    std::set<std::string> qlEurodollarFuturesImpliedStdDevQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEurodollarFuturesImpliedStdDevQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEurodollarFuturesImpliedStdDevQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEurodollarFuturesImpliedStdDevQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            return AtmForwardValue_;
        else if(strcmp(nameUpper.c_str(), "CALLPRICE")==0)
            return CallPrice_;
        else if(strcmp(nameUpper.c_str(), "PUTPRICE")==0)
            return PutPrice_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "GUESS")==0)
            return Guess_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEurodollarFuturesImpliedStdDevQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            AtmForwardValue_ = value;
        else if(strcmp(nameUpper.c_str(), "CALLPRICE")==0)
            CallPrice_ = value;
        else if(strcmp(nameUpper.c_str(), "PUTPRICE")==0)
            PutPrice_ = value;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GUESS")==0)
            Guess_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEurodollarFuturesImpliedStdDevQuote::qlEurodollarFuturesImpliedStdDevQuote(
            const std::string& ObjectId,
            const ObjectHandler::property_t& AtmForwardValue,
            const ObjectHandler::property_t& CallPrice,
            const ObjectHandler::property_t& PutPrice,
            double Strike,
            double Guess,
            double Accuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEurodollarFuturesImpliedStdDevQuote", Permanent),
        AtmForwardValue_(AtmForwardValue),
        CallPrice_(CallPrice),
        PutPrice_(PutPrice),
        Strike_(Strike),
        Guess_(Guess),
        Accuracy_(Accuracy),
        Permanent_(Permanent) {
                  
            processVariant(AtmForwardValue);
            processVariant(CallPrice);
            processVariant(PutPrice);
            
    }

    const char* qlForwardSwapQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapIndex",
        "Spread",
        "ForwardStart",
        "Permanent"
    };

    std::set<std::string> qlForwardSwapQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardSwapQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardSwapQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardSwapQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            return SwapIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            return ForwardStart_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardSwapQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEX")==0)
            SwapIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = value;
        else if(strcmp(nameUpper.c_str(), "FORWARDSTART")==0)
            ForwardStart_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardSwapQuote::qlForwardSwapQuote(
            const std::string& ObjectId,
            const std::string& SwapIndex,
            const ObjectHandler::property_t& Spread,
            const std::string& ForwardStart,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardSwapQuote", Permanent),
        SwapIndex_(SwapIndex),
        Spread_(Spread),
        ForwardStart_(ForwardStart),
        Permanent_(Permanent) {
                  
            processPrecedentID(SwapIndex);
            processVariant(Spread);
            
    }

    const char* qlForwardValueQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "IborIndex",
        "FixingDate",
        "Permanent"
    };

    std::set<std::string> qlForwardValueQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlForwardValueQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlForwardValueQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlForwardValueQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "FIXINGDATE")==0)
            return FixingDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlForwardValueQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FIXINGDATE")==0)
            FixingDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlForwardValueQuote::qlForwardValueQuote(
            const std::string& ObjectId,
            const std::string& IborIndex,
            const ObjectHandler::property_t& FixingDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlForwardValueQuote", Permanent),
        IborIndex_(IborIndex),
        FixingDate_(FixingDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            
    }

    const char* qlFuturesConvAdjustmentQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "IborIndex",
        "ImmCode",
        "FuturesQuote",
        "Volatility",
        "MeanReversion",
        "Permanent"
    };

    std::set<std::string> qlFuturesConvAdjustmentQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFuturesConvAdjustmentQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFuturesConvAdjustmentQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFuturesConvAdjustmentQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "IMMCODE")==0)
            return ImmCode_;
        else if(strcmp(nameUpper.c_str(), "FUTURESQUOTE")==0)
            return FuturesQuote_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            return Volatility_;
        else if(strcmp(nameUpper.c_str(), "MEANREVERSION")==0)
            return MeanReversion_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFuturesConvAdjustmentQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IMMCODE")==0)
            ImmCode_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FUTURESQUOTE")==0)
            FuturesQuote_ = value;
        else if(strcmp(nameUpper.c_str(), "VOLATILITY")==0)
            Volatility_ = value;
        else if(strcmp(nameUpper.c_str(), "MEANREVERSION")==0)
            MeanReversion_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFuturesConvAdjustmentQuote::qlFuturesConvAdjustmentQuote(
            const std::string& ObjectId,
            const std::string& IborIndex,
            const std::string& ImmCode,
            const ObjectHandler::property_t& FuturesQuote,
            const ObjectHandler::property_t& Volatility,
            const ObjectHandler::property_t& MeanReversion,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFuturesConvAdjustmentQuote", Permanent),
        IborIndex_(IborIndex),
        ImmCode_(ImmCode),
        FuturesQuote_(FuturesQuote),
        Volatility_(Volatility),
        MeanReversion_(MeanReversion),
        Permanent_(Permanent) {
                  
            processPrecedentID(IborIndex);
            processVariant(FuturesQuote);
            processVariant(Volatility);
            processVariant(MeanReversion);
            
    }

    const char* qlImpliedStdDevQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OptionType",
        "AtmForwardValue",
        "OptionPrice",
        "Strike",
        "Guess",
        "Accuracy",
        "Permanent"
    };

    std::set<std::string> qlImpliedStdDevQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlImpliedStdDevQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlImpliedStdDevQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlImpliedStdDevQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            return OptionType_;
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            return AtmForwardValue_;
        else if(strcmp(nameUpper.c_str(), "OPTIONPRICE")==0)
            return OptionPrice_;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            return Strike_;
        else if(strcmp(nameUpper.c_str(), "GUESS")==0)
            return Guess_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlImpliedStdDevQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIONTYPE")==0)
            OptionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ATMFORWARDVALUE")==0)
            AtmForwardValue_ = value;
        else if(strcmp(nameUpper.c_str(), "OPTIONPRICE")==0)
            OptionPrice_ = value;
        else if(strcmp(nameUpper.c_str(), "STRIKE")==0)
            Strike_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GUESS")==0)
            Guess_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlImpliedStdDevQuote::qlImpliedStdDevQuote(
            const std::string& ObjectId,
            const std::string& OptionType,
            const ObjectHandler::property_t& AtmForwardValue,
            const ObjectHandler::property_t& OptionPrice,
            double Strike,
            double Guess,
            double Accuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlImpliedStdDevQuote", Permanent),
        OptionType_(OptionType),
        AtmForwardValue_(AtmForwardValue),
        OptionPrice_(OptionPrice),
        Strike_(Strike),
        Guess_(Guess),
        Accuracy_(Accuracy),
        Permanent_(Permanent) {
                  
            processVariant(AtmForwardValue);
            processVariant(OptionPrice);
            
    }

    const char* qlLastFixingQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Index",
        "Permanent"
    };

    std::set<std::string> qlLastFixingQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLastFixingQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLastFixingQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLastFixingQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "INDEX")==0)
            return Index_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLastFixingQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INDEX")==0)
            Index_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLastFixingQuote::qlLastFixingQuote(
            const std::string& ObjectId,
            const std::string& Index,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLastFixingQuote", Permanent),
        Index_(Index),
        Permanent_(Permanent) {
                  
            processPrecedentID(Index);
            
    }

    const char* qlRelinkableHandleQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurrentLink",
        "Permanent"
    };

    std::set<std::string> qlRelinkableHandleQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRelinkableHandleQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRelinkableHandleQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRelinkableHandleQuote::getSystemProperty(const std::string& name) const {
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

    void qlRelinkableHandleQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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

    qlRelinkableHandleQuote::qlRelinkableHandleQuote(
            const std::string& ObjectId,
            const std::string& CurrentLink,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRelinkableHandleQuote", Permanent),
        CurrentLink_(CurrentLink),
        Permanent_(Permanent) {
                  
            processPrecedentID(CurrentLink);
            
    }

    const char* qlSimpleQuote::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Value",
        "TickValue",
        "Permanent"
    };

    std::set<std::string> qlSimpleQuote::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSimpleQuote::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSimpleQuote::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSimpleQuote::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VALUE")==0)
            return Value_;
        else if(strcmp(nameUpper.c_str(), "TICKVALUE")==0)
            return TickValue_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSimpleQuote::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VALUE")==0)
            Value_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TICKVALUE")==0)
            TickValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSimpleQuote::qlSimpleQuote(
            const std::string& ObjectId,
            double Value,
            double TickValue,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSimpleQuote", Permanent),
        Value_(Value),
        TickValue_(TickValue),
        Permanent_(Permanent) {
                  

            
    }

 } }
