
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

#ifndef qlo_vo_index_hpp
#define qlo_vo_index_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlBMAIndex : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBMAIndex() {}
        qlBMAIndex(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBMAIndex, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEonia : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEonia() {}
        qlEonia(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEonia, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEuribor : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEuribor() {}
        qlEuribor(
            const std::string& ObjectId,
            const std::string& Tenor,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Tenor_;
        std::string YieldCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEuribor, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEuribor365 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEuribor365() {}
        qlEuribor365(
            const std::string& ObjectId,
            const std::string& Tenor,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Tenor_;
        std::string YieldCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEuribor365, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEuriborSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEuriborSwap() {}
        qlEuriborSwap(
            const std::string& ObjectId,
            const std::string& FixingType,
            const std::string& Tenor,
            const std::string& FwdCurve,
            const std::string& DiscCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string FixingType_;
        std::string Tenor_;
        std::string FwdCurve_;
        std::string DiscCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEuriborSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FixingType", FixingType_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("FwdCurve", FwdCurve_)
                & boost::serialization::make_nvp("DiscCurve", DiscCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlEuriborSwapIsdaFixA : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlEuriborSwapIsdaFixA() {}
        qlEuriborSwapIsdaFixA(
            const std::string& ObjectId,
            const std::string& Tenor,
            const std::string& FwdCurve,
            const std::string& DiscCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Tenor_;
        std::string FwdCurve_;
        std::string DiscCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlEuriborSwapIsdaFixA, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("FwdCurve", FwdCurve_)
                & boost::serialization::make_nvp("DiscCurve", DiscCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlIborIndex : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlIborIndex() {}
        qlIborIndex(
            const std::string& ObjectId,
            const std::string& FamilyName,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& BDayConvention,
            bool EndOfMonth,
            const std::string& DayCounter,
            const std::string& FwdCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string FamilyName_;
        std::string Tenor_;
        long FixingDays_;
        std::string Currency_;
        std::string Calendar_;
        std::string BDayConvention_;
        bool EndOfMonth_;
        std::string DayCounter_;
        std::string FwdCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlIborIndex, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FamilyName", FamilyName_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BDayConvention", BDayConvention_)
                & boost::serialization::make_nvp("EndOfMonth", EndOfMonth_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("FwdCurve", FwdCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLibor : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLibor() {}
        qlLibor(
            const std::string& ObjectId,
            const std::string& Currency,
            const std::string& Tenor,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Currency_;
        std::string Tenor_;
        std::string YieldCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLibor, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLiborSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLiborSwap() {}
        qlLiborSwap(
            const std::string& ObjectId,
            const std::string& Currency,
            const std::string& FixingType,
            const std::string& Tenor,
            const std::string& FwdCurve,
            const std::string& DiscCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Currency_;
        std::string FixingType_;
        std::string Tenor_;
        std::string FwdCurve_;
        std::string DiscCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLiborSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("FixingType", FixingType_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("FwdCurve", FwdCurve_)
                & boost::serialization::make_nvp("DiscCurve", DiscCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlOvernightIndex : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlOvernightIndex() {}
        qlOvernightIndex(
            const std::string& ObjectId,
            const std::string& FamilyName,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& DayCounter,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string FamilyName_;
        long FixingDays_;
        std::string Currency_;
        std::string Calendar_;
        std::string DayCounter_;
        std::string YieldCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlOvernightIndex, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FamilyName", FamilyName_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlProxyIbor : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlProxyIbor() {}
        qlProxyIbor(
            const std::string& ObjectId,
            const std::string& FamilyName,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& BDayConvention,
            bool EndOfMonth,
            const std::string& DayCounter,
            const ObjectHandler::property_t& Gearing,
            const std::string& IborIndex,
            const ObjectHandler::property_t& Spread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string FamilyName_;
        std::string Tenor_;
        long FixingDays_;
        std::string Currency_;
        std::string Calendar_;
        std::string BDayConvention_;
        bool EndOfMonth_;
        std::string DayCounter_;
        ObjectHandler::property_t Gearing_;
        std::string IborIndex_;
        ObjectHandler::property_t Spread_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlProxyIbor, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FamilyName", FamilyName_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BDayConvention", BDayConvention_)
                & boost::serialization::make_nvp("EndOfMonth", EndOfMonth_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Gearing", Gearing_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSonia : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSonia() {}
        qlSonia(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSonia, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSwapIndex : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSwapIndex() {}
        qlSwapIndex(
            const std::string& ObjectId,
            const std::string& FamilyName,
            const std::string& Tenor,
            long FixingDays,
            const std::string& Currency,
            const std::string& Calendar,
            const std::string& FixedLegTenor,
            const std::string& FixedLegBDC,
            const std::string& FixedLegDayCounter,
            const std::string& IborIndex,
            const std::string& DiscCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string FamilyName_;
        std::string Tenor_;
        long FixingDays_;
        std::string Currency_;
        std::string Calendar_;
        std::string FixedLegTenor_;
        std::string FixedLegBDC_;
        std::string FixedLegDayCounter_;
        std::string IborIndex_;
        std::string DiscCurve_;
        bool Permanent_;
        virtual std::string processorName() { return "IndexProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSwapIndex, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FamilyName", FamilyName_)
                & boost::serialization::make_nvp("Tenor", Tenor_)
                & boost::serialization::make_nvp("FixingDays", FixingDays_)
                & boost::serialization::make_nvp("Currency", Currency_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("FixedLegTenor", FixedLegTenor_)
                & boost::serialization::make_nvp("FixedLegBDC", FixedLegBDC_)
                & boost::serialization::make_nvp("FixedLegDayCounter", FixedLegDayCounter_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("DiscCurve", DiscCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

