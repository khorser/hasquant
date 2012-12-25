
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

#ifndef qlo_vo_credit_hpp
#define qlo_vo_credit_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCreditDefaultSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCreditDefaultSwap() {}
        qlCreditDefaultSwap(
            const std::string& ObjectId,
            const std::string& BuyerSeller,
            double Notional,
            double Upfront,
            double Spread,
            const std::string& PremiumSchedule,
            const std::string& PaymentConvention,
            const std::string& DayCounter,
            bool SettlesAccrual,
            bool PayAtDefault,
            const ObjectHandler::property_t& ProtectionStart,
            const ObjectHandler::property_t& UpfrontDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string BuyerSeller_;
        double Notional_;
        double Upfront_;
        double Spread_;
        std::string PremiumSchedule_;
        std::string PaymentConvention_;
        std::string DayCounter_;
        bool SettlesAccrual_;
        bool PayAtDefault_;
        ObjectHandler::property_t ProtectionStart_;
        ObjectHandler::property_t UpfrontDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCreditDefaultSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BuyerSeller", BuyerSeller_)
                & boost::serialization::make_nvp("Notional", Notional_)
                & boost::serialization::make_nvp("Upfront", Upfront_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("PremiumSchedule", PremiumSchedule_)
                & boost::serialization::make_nvp("PaymentConvention", PaymentConvention_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("SettlesAccrual", SettlesAccrual_)
                & boost::serialization::make_nvp("PayAtDefault", PayAtDefault_)
                & boost::serialization::make_nvp("ProtectionStart", ProtectionStart_)
                & boost::serialization::make_nvp("UpfrontDate", UpfrontDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlHazardRateCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlHazardRateCurve() {}
        qlHazardRateCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveRates,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<ObjectHandler::property_t> CurveDates_;
        std::vector<double> CurveRates_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlHazardRateCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurveDates", CurveDates_)
                & boost::serialization::make_nvp("CurveRates", CurveRates_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMidPointCdsEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMidPointCdsEngine() {}
        qlMidPointCdsEngine(
            const std::string& ObjectId,
            const std::string& DefaultCurve,
            double RecoveryRate,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string DefaultCurve_;
        double RecoveryRate_;
        std::string YieldCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMidPointCdsEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("DefaultCurve", DefaultCurve_)
                & boost::serialization::make_nvp("RecoveryRate", RecoveryRate_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlPiecewiseFlatForwardCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlPiecewiseFlatForwardCurve() {}
        qlPiecewiseFlatForwardCurve(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ReferenceDate,
            const std::vector<std::string>& RateHelpers,
            const std::string& DayCounter,
            double Accuracy,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t ReferenceDate_;
        std::vector<std::string> RateHelpers_;
        std::string DayCounter_;
        double Accuracy_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlPiecewiseFlatForwardCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("ReferenceDate", ReferenceDate_)
                & boost::serialization::make_nvp("RateHelpers", RateHelpers_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Accuracy", Accuracy_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlPiecewiseFlatHazardRateCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlPiecewiseFlatHazardRateCurve() {}
        qlPiecewiseFlatHazardRateCurve(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ReferenceDate,
            const std::vector<std::string>& Helpers,
            const std::string& DayCounter,
            double Accuracy,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t ReferenceDate_;
        std::vector<std::string> Helpers_;
        std::string DayCounter_;
        double Accuracy_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlPiecewiseFlatHazardRateCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("ReferenceDate", ReferenceDate_)
                & boost::serialization::make_nvp("Helpers", Helpers_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Accuracy", Accuracy_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSpreadCdsHelper : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSpreadCdsHelper() {}
        qlSpreadCdsHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& RunningSpread,
            const std::string& Tenor,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Frequency,
            const std::string& PaymentConvention,
            const std::string& GenRule,
            const std::string& DayCounter,
            double RecoveryRate,
            const std::string& DiscountingCurve,
            bool SettleAccrual,
            bool PayAtDefault,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t RunningSpread_;
        std::string Tenor_;
        long SettlementDays_;
        std::string Calendar_;
        std::string Frequency_;
        std::string PaymentConvention_;
        std::string GenRule_;
        std::string DayCounter_;
        double RecoveryRate_;
        std::string DiscountingCurve_;
        bool SettleAccrual_;
        bool PayAtDefault_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSpreadCdsHelper, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RunningSpread", RunningSpread_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("Frequency", Frequency_)
                & boost::serialization::make_nvp("PaymentConvention", PaymentConvention_)
                & boost::serialization::make_nvp("GenRule", GenRule_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("RecoveryRate", RecoveryRate_)
                & boost::serialization::make_nvp("DiscountingCurve", DiscountingCurve_)
                & boost::serialization::make_nvp("SettleAccrual", SettleAccrual_)
                & boost::serialization::make_nvp("PayAtDefault", PayAtDefault_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlUpfrontCdsHelper : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlUpfrontCdsHelper() {}
        qlUpfrontCdsHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& UpfrontSpread,
            double RunningSpread,
            const std::string& Tenor,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Frequency,
            const std::string& PaymentConvention,
            const std::string& GenRule,
            const std::string& DayCounter,
            double RecoveryRate,
            const std::string& DiscountingCurve,
            long UpfrontSettlementDays,
            bool SettleAccrual,
            bool PayAtDefault,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t UpfrontSpread_;
        double RunningSpread_;
        std::string Tenor_;
        long SettlementDays_;
        std::string Calendar_;
        std::string Frequency_;
        std::string PaymentConvention_;
        std::string GenRule_;
        std::string DayCounter_;
        double RecoveryRate_;
        std::string DiscountingCurve_;
        long UpfrontSettlementDays_;
        bool SettleAccrual_;
        bool PayAtDefault_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlUpfrontCdsHelper, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("UpfrontSpread", UpfrontSpread_)
                & boost::serialization::make_nvp("RunningSpread", RunningSpread_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("Frequency", Frequency_)
                & boost::serialization::make_nvp("PaymentConvention", PaymentConvention_)
                & boost::serialization::make_nvp("GenRule", GenRule_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("RecoveryRate", RecoveryRate_)
                & boost::serialization::make_nvp("DiscountingCurve", DiscountingCurve_)
                & boost::serialization::make_nvp("UpfrontSettlementDays", UpfrontSettlementDays_)
                & boost::serialization::make_nvp("SettleAccrual", SettleAccrual_)
                & boost::serialization::make_nvp("PayAtDefault", PayAtDefault_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

