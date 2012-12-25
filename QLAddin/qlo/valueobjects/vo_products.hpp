
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

#ifndef qlo_vo_products_hpp
#define qlo_vo_products_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlMarketModelMultiProductComposite : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMarketModelMultiProductComposite() {}
        qlMarketModelMultiProductComposite(
            const std::string& ObjectId,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMarketModelMultiProductComposite, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMarketModelMultiStepRatchet : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMarketModelMultiStepRatchet() {}
        qlMarketModelMultiStepRatchet(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            double GearingOfFloor,
            double GearingOfFixing,
            double SpreadOfFloor,
            double SpreadOfFixing,
            double InitialFloor,
            bool Payer,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> RateTimes_;
        std::vector<double> Accruals_;
        std::vector<double> PaymentTimes_;
        double GearingOfFloor_;
        double GearingOfFixing_;
        double SpreadOfFloor_;
        double SpreadOfFixing_;
        double InitialFloor_;
        bool Payer_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMarketModelMultiStepRatchet, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RateTimes", RateTimes_)
                & boost::serialization::make_nvp("Accruals", Accruals_)
                & boost::serialization::make_nvp("PaymentTimes", PaymentTimes_)
                & boost::serialization::make_nvp("GearingOfFloor", GearingOfFloor_)
                & boost::serialization::make_nvp("GearingOfFixing", GearingOfFixing_)
                & boost::serialization::make_nvp("SpreadOfFloor", SpreadOfFloor_)
                & boost::serialization::make_nvp("SpreadOfFixing", SpreadOfFixing_)
                & boost::serialization::make_nvp("InitialFloor", InitialFloor_)
                & boost::serialization::make_nvp("Payer", Payer_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMarketModelOneStepForwards : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMarketModelOneStepForwards() {}
        qlMarketModelOneStepForwards(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<double>& Strikes,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> RateTimes_;
        std::vector<double> Accruals_;
        std::vector<double> PaymentTimes_;
        std::vector<double> Strikes_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMarketModelOneStepForwards, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RateTimes", RateTimes_)
                & boost::serialization::make_nvp("Accruals", Accruals_)
                & boost::serialization::make_nvp("PaymentTimes", PaymentTimes_)
                & boost::serialization::make_nvp("Strikes", Strikes_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMarketModelOneStepOptionlets : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMarketModelOneStepOptionlets() {}
        qlMarketModelOneStepOptionlets(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<std::string>& Payoffs,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> RateTimes_;
        std::vector<double> Accruals_;
        std::vector<double> PaymentTimes_;
        std::vector<std::string> Payoffs_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMarketModelOneStepOptionlets, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RateTimes", RateTimes_)
                & boost::serialization::make_nvp("Accruals", Accruals_)
                & boost::serialization::make_nvp("PaymentTimes", PaymentTimes_)
                & boost::serialization::make_nvp("Payoffs", Payoffs_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

