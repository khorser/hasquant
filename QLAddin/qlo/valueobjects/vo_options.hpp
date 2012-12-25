
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

#ifndef qlo_vo_options_hpp
#define qlo_vo_options_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlBarrierOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBarrierOption() {}
        qlBarrierOption(
            const std::string& ObjectId,
            const std::string& BarrierType,
            double Barrier,
            double Rebate,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string BarrierType_;
        double Barrier_;
        double Rebate_;
        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBarrierOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BarrierType", BarrierType_)
                & boost::serialization::make_nvp("Barrier", Barrier_)
                & boost::serialization::make_nvp("Rebate", Rebate_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCaAsianOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCaAsianOption() {}
        qlCaAsianOption(
            const std::string& ObjectId,
            const std::string& AverageType,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string AverageType_;
        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCaAsianOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("AverageType", AverageType_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlDaAsianOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDaAsianOption() {}
        qlDaAsianOption(
            const std::string& ObjectId,
            const std::string& AverageType,
            double RunningAccumulator,
            long PastFixings,
            const std::vector<ObjectHandler::property_t>& FixingDates,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string AverageType_;
        double RunningAccumulator_;
        long PastFixings_;
        std::vector<ObjectHandler::property_t> FixingDates_;
        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDaAsianOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("AverageType", AverageType_)
                & boost::serialization::make_nvp("RunningAccumulator", RunningAccumulator_)
                & boost::serialization::make_nvp("PastFixings", PastFixings_)
                & boost::serialization::make_nvp("FixingDates", FixingDates_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlDividendVanillaOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDividendVanillaOption() {}
        qlDividendVanillaOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            const std::vector<ObjectHandler::property_t>& DividendDates,
            const std::vector<double>& Dividends,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Payoff_;
        std::string Exercise_;
        std::vector<ObjectHandler::property_t> DividendDates_;
        std::vector<double> Dividends_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDividendVanillaOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("DividendDates", DividendDates_)
                & boost::serialization::make_nvp("Dividends", Dividends_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEuropeanOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEuropeanOption() {}
        qlEuropeanOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEuropeanOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlForwardVanillaOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlForwardVanillaOption() {}
        qlForwardVanillaOption(
            const std::string& ObjectId,
            double Moneyness,
            const ObjectHandler::property_t& ResetDate,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Moneyness_;
        ObjectHandler::property_t ResetDate_;
        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlForwardVanillaOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Moneyness", Moneyness_)
                & boost::serialization::make_nvp("ResetDate", ResetDate_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlQuantoForwardVanillaOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlQuantoForwardVanillaOption() {}
        qlQuantoForwardVanillaOption(
            const std::string& ObjectId,
            double Moneyness,
            const ObjectHandler::property_t& ResetDate,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Moneyness_;
        ObjectHandler::property_t ResetDate_;
        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlQuantoForwardVanillaOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Moneyness", Moneyness_)
                & boost::serialization::make_nvp("ResetDate", ResetDate_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlQuantoVanillaOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlQuantoVanillaOption() {}
        qlQuantoVanillaOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlQuantoVanillaOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlVanillaOption : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlVanillaOption() {}
        qlVanillaOption(
            const std::string& ObjectId,
            const std::string& Payoff,
            const std::string& Exercise,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Payoff_;
        std::string Exercise_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlVanillaOption, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Payoff", Payoff_)
                & boost::serialization::make_nvp("Exercise", Exercise_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

