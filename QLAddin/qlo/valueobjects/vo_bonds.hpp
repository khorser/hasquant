
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

#ifndef qlo_vo_bonds_hpp
#define qlo_vo_bonds_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlBond : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBond() {}
        qlBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& Calendar,
            double FaceAmount,
            const ObjectHandler::property_t& MaturityDate,
            const ObjectHandler::property_t& IssueDate,
            const std::string& LegID,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Description_;
        std::string Currency_;
        long SettlementDays_;
        std::string Calendar_;
        double FaceAmount_;
        ObjectHandler::property_t MaturityDate_;
        ObjectHandler::property_t IssueDate_;
        std::string LegID_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBond, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("FaceAmount", FaceAmount_)
                & boost::serialization::make_nvp("MaturityDate", MaturityDate_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("LegID", LegID_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCmsRateBond : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCmsRateBond() {}
        qlCmsRateBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& PaymentBDC,
            double FaceAmount,
            const std::string& ScheduleID,
            long FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Description_;
        std::string Currency_;
        long SettlementDays_;
        std::string PaymentBDC_;
        double FaceAmount_;
        std::string ScheduleID_;
        long FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Floors_;
        std::vector<double> Gearings_;
        std::string SwapIndex_;
        std::vector<double> Spreads_;
        std::vector<double> Caps_;
        double Redemption_;
        ObjectHandler::property_t IssueDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCmsRateBond, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("FaceAmount", FaceAmount_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Floors", Floors_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("Caps", Caps_)
                & boost::serialization::make_nvp("Redemption", Redemption_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFixedRateBond : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFixedRateBond() {}
        qlFixedRateBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            double FaceAmount,
            const std::string& ScheduleID,
            const std::vector<double>& Coupons,
            const std::string& DayCounter,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            const std::string& PaymentCalendar,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Description_;
        std::string Currency_;
        long SettlementDays_;
        double FaceAmount_;
        std::string ScheduleID_;
        std::vector<double> Coupons_;
        std::string DayCounter_;
        std::string PaymentBDC_;
        double Redemption_;
        ObjectHandler::property_t IssueDate_;
        std::string PaymentCalendar_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFixedRateBond, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("FaceAmount", FaceAmount_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("Coupons", Coupons_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Redemption", Redemption_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("PaymentCalendar", PaymentCalendar_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFixedRateBond2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFixedRateBond2() {}
        qlFixedRateBond2(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            double FaceAmount,
            const std::string& ScheduleID,
            const std::vector<std::string>& Coupons,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            const std::string& PaymentCalendar,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Description_;
        std::string Currency_;
        long SettlementDays_;
        double FaceAmount_;
        std::string ScheduleID_;
        std::vector<std::string> Coupons_;
        std::string PaymentBDC_;
        double Redemption_;
        ObjectHandler::property_t IssueDate_;
        std::string PaymentCalendar_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFixedRateBond2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("FaceAmount", FaceAmount_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("Coupons", Coupons_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Redemption", Redemption_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("PaymentCalendar", PaymentCalendar_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFloatingRateBond : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFloatingRateBond() {}
        qlFloatingRateBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& PaymentBDC,
            double FaceAmount,
            const std::string& ScheduleID,
            long FixingDays,
            bool IsInArrears,
            const std::string& DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string& IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Description_;
        std::string Currency_;
        long SettlementDays_;
        std::string PaymentBDC_;
        double FaceAmount_;
        std::string ScheduleID_;
        long FixingDays_;
        bool IsInArrears_;
        std::string DayCounter_;
        std::vector<double> Floors_;
        std::vector<double> Gearings_;
        std::string IborIndex_;
        std::vector<double> Spreads_;
        std::vector<double> Caps_;
        double Redemption_;
        ObjectHandler::property_t IssueDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFloatingRateBond, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("FaceAmount", FaceAmount_)
                & boost::serialization::make_nvp("ScheduleID", ScheduleID_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("IsInArrears", IsInArrears_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Floors", Floors_)
                & boost::serialization::make_nvp("Gearings", Gearings_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spreads", Spreads_)
                & boost::serialization::make_nvp("Caps", Caps_)
                & boost::serialization::make_nvp("Redemption", Redemption_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlZeroCouponBond : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlZeroCouponBond() {}
        qlZeroCouponBond(
            const std::string& ObjectId,
            const std::string& Description,
            const std::string& Currency,
            long SettlementDays,
            const std::string& Calendar,
            double FaceAmount,
            const ObjectHandler::property_t& Maturity,
            const std::string& PaymentBDC,
            double Redemption,
            const ObjectHandler::property_t& IssueDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Description_;
        std::string Currency_;
        long SettlementDays_;
        std::string Calendar_;
        double FaceAmount_;
        ObjectHandler::property_t Maturity_;
        std::string PaymentBDC_;
        double Redemption_;
        ObjectHandler::property_t IssueDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlZeroCouponBond, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("FaceAmount", FaceAmount_)
                & boost::serialization::make_nvp("Maturity", Maturity_)
                & boost::serialization::make_nvp("PaymentBDC", PaymentBDC_)
                & boost::serialization::make_nvp("Redemption", Redemption_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

