
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

#ifndef qlo_vo_schedule_hpp
#define qlo_vo_schedule_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlSchedule : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSchedule() {}
        qlSchedule(
            const std::string& ObjectId,
            const ObjectHandler::property_t& EffectiveDate,
            const ObjectHandler::property_t& TerminationDate,
            const std::string& Tenor,
            const std::string& Calendar,
            const std::string& Convention,
            const std::string& TermDateConv,
            const std::string& GenRule,
            bool EndOfMonth,
            const ObjectHandler::property_t& FirstDate,
            const ObjectHandler::property_t& NextToLastDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t EffectiveDate_;
        ObjectHandler::property_t TerminationDate_;
        std::string Tenor_;
        std::string Calendar_;
        std::string Convention_;
        std::string TermDateConv_;
        std::string GenRule_;
        bool EndOfMonth_;
        ObjectHandler::property_t FirstDate_;
        ObjectHandler::property_t NextToLastDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSchedule, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("EffectiveDate", EffectiveDate_)
                & boost::serialization::make_nvp("TerminationDate", TerminationDate_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("Convention", Convention_)
                & boost::serialization::make_nvp("TermDateConv", TermDateConv_)
                & boost::serialization::make_nvp("GenRule", GenRule_)
                & boost::serialization::make_nvp("EndOfMonth", EndOfMonth_)
                & boost::serialization::make_nvp("FirstDate", FirstDate_)
                & boost::serialization::make_nvp("NextToLastDate", NextToLastDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlScheduleFromDateVector : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlScheduleFromDateVector() {}
        qlScheduleFromDateVector(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& EffectiveDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<ObjectHandler::property_t> EffectiveDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlScheduleFromDateVector, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("EffectiveDate", EffectiveDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlScheduleTruncated : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlScheduleTruncated() {}
        qlScheduleTruncated(
            const std::string& ObjectId,
            const std::string& OriginalSchedule,
            const ObjectHandler::property_t& TruncationDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string OriginalSchedule_;
        ObjectHandler::property_t TruncationDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlScheduleTruncated, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OriginalSchedule", OriginalSchedule_)
                & boost::serialization::make_nvp("TruncationDate", TruncationDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

