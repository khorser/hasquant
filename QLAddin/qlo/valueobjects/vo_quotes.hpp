
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
//      gensrc/gensrc/stubs/stub.vo.includes.decl

#ifndef qlo_vo_quotes_hpp
#define qlo_vo_quotes_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCompositeQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCompositeQuote() {}
        qlCompositeQuote(
            const std::string& ObjectId,
            const ObjectHandler::property_t& Element1,
            const ObjectHandler::property_t& Element2,
            const std::string& Operator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t Element1_;
        ObjectHandler::property_t Element2_;
        std::string Operator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCompositeQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Element1", Element1_)
                & boost::serialization::make_nvp("Element2", Element2_)
                & boost::serialization::make_nvp("Operator", Operator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEurodollarFuturesImpliedStdDevQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEurodollarFuturesImpliedStdDevQuote() {}
        qlEurodollarFuturesImpliedStdDevQuote(
            const std::string& ObjectId,
            const ObjectHandler::property_t& AtmForwardValue,
            const ObjectHandler::property_t& CallPrice,
            const ObjectHandler::property_t& PutPrice,
            double Strike,
            double Guess,
            double Accuracy,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t AtmForwardValue_;
        ObjectHandler::property_t CallPrice_;
        ObjectHandler::property_t PutPrice_;
        double Strike_;
        double Guess_;
        double Accuracy_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEurodollarFuturesImpliedStdDevQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("AtmForwardValue", AtmForwardValue_)
                & boost::serialization::make_nvp("CallPrice", CallPrice_)
                & boost::serialization::make_nvp("PutPrice", PutPrice_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("Guess", Guess_)
                & boost::serialization::make_nvp("Accuracy", Accuracy_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlForwardSwapQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlForwardSwapQuote() {}
        qlForwardSwapQuote(
            const std::string& ObjectId,
            const std::string& SwapIndex,
            const ObjectHandler::property_t& Spread,
            const std::string& ForwardStart,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapIndex_;
        ObjectHandler::property_t Spread_;
        std::string ForwardStart_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlForwardSwapQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("ForwardStart", ForwardStart_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlForwardValueQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlForwardValueQuote() {}
        qlForwardValueQuote(
            const std::string& ObjectId,
            const std::string& IborIndex,
            const ObjectHandler::property_t& FixingDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string IborIndex_;
        ObjectHandler::property_t FixingDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlForwardValueQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("FixingDate", FixingDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFuturesConvAdjustmentQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFuturesConvAdjustmentQuote() {}
        qlFuturesConvAdjustmentQuote(
            const std::string& ObjectId,
            const std::string& IborIndex,
            const std::string& ImmCode,
            const ObjectHandler::property_t& FuturesQuote,
            const ObjectHandler::property_t& Volatility,
            const ObjectHandler::property_t& MeanReversion,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string IborIndex_;
        std::string ImmCode_;
        ObjectHandler::property_t FuturesQuote_;
        ObjectHandler::property_t Volatility_;
        ObjectHandler::property_t MeanReversion_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFuturesConvAdjustmentQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("ImmCode", ImmCode_)
                & boost::serialization::make_nvp("FuturesQuote", FuturesQuote_)
                & boost::serialization::make_nvp("Volatility", Volatility_)
                & boost::serialization::make_nvp("MeanReversion", MeanReversion_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlImpliedStdDevQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlImpliedStdDevQuote() {}
        qlImpliedStdDevQuote(
            const std::string& ObjectId,
            const std::string& OptionType,
            const ObjectHandler::property_t& AtmForwardValue,
            const ObjectHandler::property_t& OptionPrice,
            double Strike,
            double Guess,
            double Accuracy,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string OptionType_;
        ObjectHandler::property_t AtmForwardValue_;
        ObjectHandler::property_t OptionPrice_;
        double Strike_;
        double Guess_;
        double Accuracy_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlImpliedStdDevQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionType", OptionType_)
                & boost::serialization::make_nvp("AtmForwardValue", AtmForwardValue_)
                & boost::serialization::make_nvp("OptionPrice", OptionPrice_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("Guess", Guess_)
                & boost::serialization::make_nvp("Accuracy", Accuracy_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLastFixingQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLastFixingQuote() {}
        qlLastFixingQuote(
            const std::string& ObjectId,
            const std::string& Index,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Index_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLastFixingQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Index", Index_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRelinkableHandleQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRelinkableHandleQuote() {}
        qlRelinkableHandleQuote(
            const std::string& ObjectId,
            const std::string& CurrentLink,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string CurrentLink_;
        bool Permanent_;
        virtual std::string processorName() { return "RelinkableHandleProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRelinkableHandleQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurrentLink", CurrentLink_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSimpleQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSimpleQuote() {}
        qlSimpleQuote(
            const std::string& ObjectId,
            double Value,
            double TickValue,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Value_;
        double TickValue_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSimpleQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Value", Value_)
                & boost::serialization::make_nvp("TickValue", TickValue_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

