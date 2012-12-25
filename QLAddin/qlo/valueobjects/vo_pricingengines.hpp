
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

#ifndef qlo_vo_pricingengines_hpp
#define qlo_vo_pricingengines_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlAnalyticCapFloorEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAnalyticCapFloorEngine() {}
        qlAnalyticCapFloorEngine(
            const std::string& ObjectId,
            const std::string& HandleModel,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string HandleModel_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAnalyticCapFloorEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("HandleModel", HandleModel_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBinomialPricingEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBinomialPricingEngine() {}
        qlBinomialPricingEngine(
            const std::string& ObjectId,
            const std::string& EngineID,
            const std::string& ProcessID,
            long TimeSteps,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string EngineID_;
        std::string ProcessID_;
        long TimeSteps_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBinomialPricingEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("EngineID", EngineID_)
                & boost::serialization::make_nvp("ProcessID", ProcessID_)
                & boost::serialization::make_nvp("TimeSteps", TimeSteps_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackCalculator() {}
        qlBlackCalculator(
            const std::string& ObjectId,
            const std::string& OptionType,
            double Strike,
            double AtmForwardValue,
            double StdDev,
            double Deflator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string OptionType_;
        double Strike_;
        double AtmForwardValue_;
        double StdDev_;
        double Deflator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionType", OptionType_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("AtmForwardValue", AtmForwardValue_)
                & boost::serialization::make_nvp("StdDev", StdDev_)
                & boost::serialization::make_nvp("Deflator", Deflator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackCalculator2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackCalculator2() {}
        qlBlackCalculator2(
            const std::string& ObjectId,
            const std::string& PayoffID,
            double AtmForwardValue,
            double StdDev,
            double Deflator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PayoffID_;
        double AtmForwardValue_;
        double StdDev_;
        double Deflator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackCalculator2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PayoffID", PayoffID_)
                & boost::serialization::make_nvp("AtmForwardValue", AtmForwardValue_)
                & boost::serialization::make_nvp("StdDev", StdDev_)
                & boost::serialization::make_nvp("Deflator", Deflator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackCapFloorEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackCapFloorEngine() {}
        qlBlackCapFloorEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const std::string& VolTS,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        std::string VolTS_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackCapFloorEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("VolTS", VolTS_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackCapFloorEngine2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackCapFloorEngine2() {}
        qlBlackCapFloorEngine2(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const ObjectHandler::property_t& Vol,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        ObjectHandler::property_t Vol_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackCapFloorEngine2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Vol", Vol_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackScholesCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackScholesCalculator() {}
        qlBlackScholesCalculator(
            const std::string& ObjectId,
            const std::string& OptionType,
            double Strike,
            double Spot,
            double Growth,
            double StdDev,
            double Deflator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string OptionType_;
        double Strike_;
        double Spot_;
        double Growth_;
        double StdDev_;
        double Deflator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackScholesCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionType", OptionType_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("Spot", Spot_)
                & boost::serialization::make_nvp("Growth", Growth_)
                & boost::serialization::make_nvp("StdDev", StdDev_)
                & boost::serialization::make_nvp("Deflator", Deflator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackScholesCalculator2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackScholesCalculator2() {}
        qlBlackScholesCalculator2(
            const std::string& ObjectId,
            const std::string& PayoffID,
            double Spot,
            double Growth,
            double StdDev,
            double Deflator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PayoffID_;
        double Spot_;
        double Growth_;
        double StdDev_;
        double Deflator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackScholesCalculator2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PayoffID", PayoffID_)
                & boost::serialization::make_nvp("Spot", Spot_)
                & boost::serialization::make_nvp("Growth", Growth_)
                & boost::serialization::make_nvp("StdDev", StdDev_)
                & boost::serialization::make_nvp("Deflator", Deflator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackSwaptionEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackSwaptionEngine() {}
        qlBlackSwaptionEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const std::string& VolTS,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        std::string VolTS_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackSwaptionEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("VolTS", VolTS_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackSwaptionEngine2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackSwaptionEngine2() {}
        qlBlackSwaptionEngine2(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            const ObjectHandler::property_t& Vol,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        ObjectHandler::property_t Vol_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackSwaptionEngine2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Vol", Vol_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBondEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBondEngine() {}
        qlBondEngine(
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
        boost::serialization::void_cast_register<qlBondEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlDiscountingSwapEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDiscountingSwapEngine() {}
        qlDiscountingSwapEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool IncludeSettlDate,
            const ObjectHandler::property_t& SettlementDate,
            const ObjectHandler::property_t& NpvDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string YieldCurve_;
        bool IncludeSettlDate_;
        ObjectHandler::property_t SettlementDate_;
        ObjectHandler::property_t NpvDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDiscountingSwapEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("IncludeSettlDate", IncludeSettlDate_)
                & boost::serialization::make_nvp("SettlementDate", SettlementDate_)
                & boost::serialization::make_nvp("NpvDate", NpvDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlPricingEngine : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlPricingEngine() {}
        qlPricingEngine(
            const std::string& ObjectId,
            const std::string& EngineID,
            const std::string& ProcessID,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string EngineID_;
        std::string ProcessID_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlPricingEngine, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("EngineID", EngineID_)
                & boost::serialization::make_nvp("ProcessID", ProcessID_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

