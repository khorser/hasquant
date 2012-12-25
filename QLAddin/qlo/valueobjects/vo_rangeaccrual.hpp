
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

#ifndef qlo_vo_rangeaccrual_hpp
#define qlo_vo_rangeaccrual_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlRangeAccrualFloatersCoupon : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRangeAccrualFloatersCoupon() {}
        qlRangeAccrualFloatersCoupon(
            const std::string& ObjectId,
            double Nominal,
            const ObjectHandler::property_t& PaymentDate,
            const std::string& IborIndex,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            long FixingDays,
            const std::string& DayCountID,
            double Gearings,
            double Spreads,
            const ObjectHandler::property_t& RefPeriodStart,
            const ObjectHandler::property_t& RefPeriodEnd,
            const std::string& ObserSchedID,
            double LowerTrigger,
            double UpperTrigger,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Nominal_;
        ObjectHandler::property_t PaymentDate_;
        std::string IborIndex_;
        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t EndDate_;
        long FixingDays_;
        std::string DayCountID_;
        double Gearings_;
        double Spreads_;
        ObjectHandler::property_t RefPeriodStart_;
        ObjectHandler::property_t RefPeriodEnd_;
        std::string ObserSchedID_;
        double LowerTrigger_;
        double UpperTrigger_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRangeAccrualFloatersCoupon, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Nominal", Nominal_)
                & boost::serialization::make_nvp("PaymentDate", PaymentDate_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("EndDate", EndDate_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("DayCountID", DayCountID_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("RefPeriodStart", RefPeriodStart_)
                & boost::serialization::make_nvp("RefPeriodEnd", RefPeriodEnd_)
                & boost::serialization::make_nvp("ObserSchedID", ObserSchedID_)
                & boost::serialization::make_nvp("LowerTrigger", LowerTrigger_)
                & boost::serialization::make_nvp("UpperTrigger", UpperTrigger_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRangeAccrualFloatersCouponFromLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRangeAccrualFloatersCouponFromLeg() {}
        qlRangeAccrualFloatersCouponFromLeg(
            const std::string& ObjectId,
            const std::string& RangeAccrualLeg,
            long Position,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string RangeAccrualLeg_;
        long Position_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRangeAccrualFloatersCouponFromLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RangeAccrualLeg", RangeAccrualLeg_)
                & boost::serialization::make_nvp("Position", Position_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRangeAccrualPricerByBgm : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRangeAccrualPricerByBgm() {}
        qlRangeAccrualPricerByBgm(
            const std::string& ObjectId,
            double Correlation,
            const std::string& SmileOnStartDateID,
            const std::string& SmileOnEndDateID,
            bool WithSmile,
            bool ByCallSpread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Correlation_;
        std::string SmileOnStartDateID_;
        std::string SmileOnEndDateID_;
        bool WithSmile_;
        bool ByCallSpread_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRangeAccrualPricerByBgm, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Correlation", Correlation_)
                & boost::serialization::make_nvp("SmileOnStartDateID", SmileOnStartDateID_)
                & boost::serialization::make_nvp("SmileOnEndDateID", SmileOnEndDateID_)
                & boost::serialization::make_nvp("WithSmile", WithSmile_)
                & boost::serialization::make_nvp("ByCallSpread", ByCallSpread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

