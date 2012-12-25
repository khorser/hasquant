
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

#ifndef qlo_vo_vanillaswap_hpp
#define qlo_vo_vanillaswap_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlMakeIMMSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMakeIMMSwap() {}
        qlMakeIMMSwap(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& IborIndex,
            double FixedRate,
            const ObjectHandler::property_t& FirstImmDate,
            const std::string& FixDayCounter,
            double Spread,
            const std::string& PricingEngineID,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapTenor_;
        std::string IborIndex_;
        double FixedRate_;
        ObjectHandler::property_t FirstImmDate_;
        std::string FixDayCounter_;
        double Spread_;
        std::string PricingEngineID_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMakeIMMSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("FixedRate", FixedRate_)
                & boost::serialization::make_nvp("FirstImmDate", FirstImmDate_)
                & boost::serialization::make_nvp("FixDayCounter", FixDayCounter_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("PricingEngineID", PricingEngineID_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMakeVanillaSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMakeVanillaSwap() {}
        qlMakeVanillaSwap(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& IborIndex,
            double FixedRate,
            const std::string& ForwardStart,
            const std::string& FixDayCounter,
            double Spread,
            const std::string& PricingEngineID,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapTenor_;
        std::string IborIndex_;
        double FixedRate_;
        std::string ForwardStart_;
        std::string FixDayCounter_;
        double Spread_;
        std::string PricingEngineID_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMakeVanillaSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("FixedRate", FixedRate_)
                & boost::serialization::make_nvp("ForwardStart", ForwardStart_)
                & boost::serialization::make_nvp("FixDayCounter", FixDayCounter_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("PricingEngineID", PricingEngineID_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlVanillaSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlVanillaSwap() {}
        qlVanillaSwap(
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
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PayerReceiver_;
        double Nominal_;
        std::string FixSchedule_;
        double FixedRate_;
        std::string FixDayCounter_;
        std::string FloatingLegSchedule_;
        std::string IborIndex_;
        double Spread_;
        std::string FloatingLegDayCounter_;
        std::string PaymentConvention_;
        bool Permanent_;
        virtual std::string processorName() { return "InstrumentProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlVanillaSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PayerReceiver", PayerReceiver_)
                & boost::serialization::make_nvp("Nominal", Nominal_)
                & boost::serialization::make_nvp("FixSchedule", FixSchedule_)
                & boost::serialization::make_nvp("FixedRate", FixedRate_)
                & boost::serialization::make_nvp("FixDayCounter", FixDayCounter_)
                & boost::serialization::make_nvp("FloatingLegSchedule", FloatingLegSchedule_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("FloatingLegDayCounter", FloatingLegDayCounter_)
                & boost::serialization::make_nvp("PaymentConvention", PaymentConvention_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlVanillaSwapFromSwapIndex : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlVanillaSwapFromSwapIndex() {}
        qlVanillaSwapFromSwapIndex(
            const std::string& ObjectId,
            const std::string& SwapIndex,
            const ObjectHandler::property_t& FixingDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapIndex_;
        ObjectHandler::property_t FixingDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlVanillaSwapFromSwapIndex, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("FixingDate", FixingDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlVanillaSwapFromSwapRateHelper : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlVanillaSwapFromSwapRateHelper() {}
        qlVanillaSwapFromSwapRateHelper(
            const std::string& ObjectId,
            const std::string& SwapRateHelper,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapRateHelper_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlVanillaSwapFromSwapRateHelper, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapRateHelper", SwapRateHelper_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

