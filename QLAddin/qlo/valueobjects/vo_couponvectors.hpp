
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

#ifndef qlo_vo_couponvectors_hpp
#define qlo_vo_couponvectors_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCmsCouponPricer : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCmsCouponPricer() {}
        qlCmsCouponPricer(
            const std::string& ObjectId,
            const std::string& Volatility,
            const std::string& CmsCouponPricerType,
            const std::string& YieldCurveModel,
            const ObjectHandler::property_t& MeanReversion,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Volatility_;
        std::string CmsCouponPricerType_;
        std::string YieldCurveModel_;
        ObjectHandler::property_t MeanReversion_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCmsCouponPricer, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Volatility", Volatility_)
                & boost::serialization::make_nvp("CmsCouponPricerType", CmsCouponPricerType_)
                & boost::serialization::make_nvp("YieldCurveModel", YieldCurveModel_)
                & boost::serialization::make_nvp("MeanReversion", MeanReversion_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCmsLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCmsLeg() {}
        qlCmsLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<long> FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Floors_;
        std::vector<double> Gearings_;
        std::string SwapIndex_;
        std::vector<double> Spreads_;
        std::vector<double> Caps_;
        bool Permanent_;
        virtual std::string processorName() { return "LegProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCmsLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Floors", Floors_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("Caps", Caps_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCmsZeroLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCmsZeroLeg() {}
        qlCmsZeroLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<long> FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Floors_;
        std::vector<double> Gearings_;
        std::string SwapIndex_;
        std::vector<double> Spreads_;
        std::vector<double> Caps_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCmsZeroLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Floors", Floors_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("Caps", Caps_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlConundrumPricerByNumericalIntegration : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlConundrumPricerByNumericalIntegration() {}
        qlConundrumPricerByNumericalIntegration(
            const std::string& ObjectId,
            const std::string& SwaptionVol,
            const std::string& YieldCurveModel,
            const ObjectHandler::property_t& MeanReversion,
            double LowerLimit,
            double UpperLimit,
            double Precision,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwaptionVol_;
        std::string YieldCurveModel_;
        ObjectHandler::property_t MeanReversion_;
        double LowerLimit_;
        double UpperLimit_;
        double Precision_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlConundrumPricerByNumericalIntegration, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwaptionVol", SwaptionVol_)
                & boost::serialization::make_nvp("YieldCurveModel", YieldCurveModel_)
                & boost::serialization::make_nvp("MeanReversion", MeanReversion_)
                & boost::serialization::make_nvp("LowerLimit", LowerLimit_)
                & boost::serialization::make_nvp("UpperLimit", UpperLimit_)
                & boost::serialization::make_nvp("Precision", Precision_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlDigitalCmsLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDigitalCmsLeg() {}
        qlDigitalCmsLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string& CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string& PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string& Replication,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<long> FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Gearings_;
        std::string SwapIndex_;
        std::vector<double> Spreads_;
        std::vector<double> CallStrikes_;
        std::string CallSpecs_;
        std::vector<double> CallPayoff_;
        std::vector<double> PutStrikes_;
        std::string PutSpecs_;
        std::vector<double> PutPayoff_;
        std::string Replication_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDigitalCmsLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("CallStrikes", CallStrikes_)
                & boost::serialization::make_nvp("CallSpecs", CallSpecs_)
                & boost::serialization::make_nvp("CallPayoff", CallPayoff_)
                & boost::serialization::make_nvp("PutStrikes", PutStrikes_)
                & boost::serialization::make_nvp("PutSpecs", PutSpecs_)
                & boost::serialization::make_nvp("PutPayoff", PutPayoff_)
                & boost::serialization::make_nvp("Replication", Replication_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlDigitalIborLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDigitalIborLeg() {}
        qlDigitalIborLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string& CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string& PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string& Replication,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<long> FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Gearings_;
        std::string IborIndex_;
        std::vector<double> Spreads_;
        std::vector<double> CallStrikes_;
        std::string CallSpecs_;
        std::vector<double> CallPayoff_;
        std::vector<double> PutStrikes_;
        std::string PutSpecs_;
        std::vector<double> PutPayoff_;
        std::string Replication_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDigitalIborLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("CallStrikes", CallStrikes_)
                & boost::serialization::make_nvp("CallSpecs", CallSpecs_)
                & boost::serialization::make_nvp("CallPayoff", CallPayoff_)
                & boost::serialization::make_nvp("PutStrikes", PutStrikes_)
                & boost::serialization::make_nvp("PutSpecs", PutSpecs_)
                & boost::serialization::make_nvp("PutPayoff", PutPayoff_)
                & boost::serialization::make_nvp("Replication", Replication_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlDigitalReplication : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDigitalReplication() {}
        qlDigitalReplication(
            const std::string& ObjectId,
            const std::string& Replication,
            double Gap,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Replication_;
        double Gap_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDigitalReplication, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Replication", Replication_)
                & boost::serialization::make_nvp("Gap", Gap_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFixedRateLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFixedRateLeg() {}
        qlFixedRateLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<double>& Coupons,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<double> Coupons_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFixedRateLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("Coupons", Coupons_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFixedRateLeg2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFixedRateLeg2() {}
        qlFixedRateLeg2(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<std::string>& Coupons,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<std::string> Coupons_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFixedRateLeg2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("Coupons", Coupons_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlIborCouponPricer : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlIborCouponPricer() {}
        qlIborCouponPricer(
            const std::string& ObjectId,
            const std::string& Volatility,
            const std::string& IborCouponPricerType,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Volatility_;
        std::string IborCouponPricerType_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlIborCouponPricer, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Volatility", Volatility_)
                & boost::serialization::make_nvp("IborCouponPricerType", IborCouponPricerType_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlIborLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlIborLeg() {}
        qlIborLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<long> FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Floors_;
        std::vector<double> Gearings_;
        std::string IborIndex_;
        std::vector<double> Spreads_;
        std::vector<double> Caps_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlIborLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Floors", Floors_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("Caps", Caps_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRangeAccrualLeg : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRangeAccrualLeg() {}
        qlRangeAccrualLeg(
            const std::string& ObjectId,
            const std::string& PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string& ScheduleID,
            const std::vector<long>& FixingDays,
            const std::string& DayCounter,
            const std::vector<double>& LowerStrikes,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& UpperStrikes,
            const std::string& ObservationsTenor,
            const std::string& ObservationsBDC,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PaymentBDC_;
        std::vector<double> Nominals_;
        std::string ScheduleID_;
        std::vector<long> FixingDays_;
        std::string DayCounter_;
        std::vector<double> LowerStrikes_;
        std::vector<double> Gearings_;
        std::string IborIndex_;
        std::vector<double> Spreads_;
        std::vector<double> UpperStrikes_;
        std::string ObservationsTenor_;
        std::string ObservationsBDC_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRangeAccrualLeg, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Nominals", Nominals_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("LowerStrikes", LowerStrikes_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("UpperStrikes", UpperStrikes_)
                & boost::serialization::make_nvp("ObservationsTenor", ObservationsTenor_)
                & boost::serialization::make_nvp("ObservationsBDC", ObservationsBDC_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

