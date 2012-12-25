
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

#ifndef qlo_vo_leg_hpp
#define qlo_vo_leg_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlInterestRate : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlInterestRate() {}
        qlInterestRate(
            const std::string& ObjectId,
            double Rate,
            const std::string& DayCounter,
            const std::string& Compounding,
            const std::string& Frequency,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Rate_;
        std::string DayCounter_;
        std::string Compounding_;
        std::string Frequency_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlInterestRate, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Rate", Rate_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Compounding", Compounding_)
                & boost::serialization::make_nvp("Frequency", Frequency_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLeg() {}
        qlLeg(
            const std::string& ObjectId,
            const std::vector<double>& Amounts,
            const std::vector<ObjectHandler::property_t>& Dates,
            bool ToBeSorted,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> Amounts_;
        std::vector<ObjectHandler::property_t> Dates_;
        bool ToBeSorted_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Amounts", Amounts_)
                & boost::serialization::make_nvp("Dates", Dates_)
                & boost::serialization::make_nvp("ToBeSorted", ToBeSorted_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLegFromCapFloor : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLegFromCapFloor() {}
        qlLegFromCapFloor(
            const std::string& ObjectId,
            const std::string& CapFloor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string CapFloor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLegFromCapFloor, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CapFloor", CapFloor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLegFromSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLegFromSwap() {}
        qlLegFromSwap(
            const std::string& ObjectId,
            const std::string& Swap,
            long LegNumber,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Swap_;
        long LegNumber_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLegFromSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Swap", Swap_)
                & boost::serialization::make_nvp("LegNumber", LegNumber_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMultiPhaseLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMultiPhaseLeg() {}
        qlMultiPhaseLeg(
            const std::string& ObjectId,
            const std::vector<std::string>& LegIDs,
            bool ToBeSorted,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::string> LegIDs_;
        bool ToBeSorted_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMultiPhaseLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("LegIDs", LegIDs_)
                & boost::serialization::make_nvp("ToBeSorted", ToBeSorted_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

