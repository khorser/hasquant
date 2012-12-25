
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

#ifndef qlo_vo_btp_hpp
#define qlo_vo_btp_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlBTP : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBTP() {}
        qlBTP(
            const std::string& ObjectId,
            const std::string& Description,
            const ObjectHandler::property_t& MaturityDate,
            double Coupon,
            const ObjectHandler::property_t& StartDate,
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
        ObjectHandler::property_t MaturityDate_;
        double Coupon_;
        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t IssueDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBTP, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("MaturityDate", MaturityDate_)
                & boost::serialization::make_nvp("Coupon", Coupon_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBTP2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBTP2() {}
        qlBTP2(
            const std::string& ObjectId,
            const std::string& Description,
            const ObjectHandler::property_t& MaturityDate,
            double Coupon,
            double Redemption,
            const ObjectHandler::property_t& StartDate,
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
        ObjectHandler::property_t MaturityDate_;
        double Coupon_;
        double Redemption_;
        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t IssueDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBTP2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("MaturityDate", MaturityDate_)
                & boost::serialization::make_nvp("Coupon", Coupon_)
                & boost::serialization::make_nvp("Redemption", Redemption_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCCTEU : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCCTEU() {}
        qlCCTEU(
            const std::string& ObjectId,
            const std::string& Description,
            const ObjectHandler::property_t& MaturityDate,
            double Spread,
            const std::string& FwdCurve,
            const ObjectHandler::property_t& StartDate,
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
        ObjectHandler::property_t MaturityDate_;
        double Spread_;
        std::string FwdCurve_;
        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t IssueDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCCTEU, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Description", Description_)
                & boost::serialization::make_nvp("MaturityDate", MaturityDate_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("FwdCurve", FwdCurve_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("IssueDate", IssueDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRendistatoBasket : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRendistatoBasket() {}
        qlRendistatoBasket(
            const std::string& ObjectId,
            const std::vector<std::string>& BTPs,
            const std::vector<double>& Outstandings,
            const std::vector<ObjectHandler::property_t>& Prices,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::string> BTPs_;
        std::vector<double> Outstandings_;
        std::vector<ObjectHandler::property_t> Prices_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRendistatoBasket, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BTPs", BTPs_)
                & boost::serialization::make_nvp("Outstandings", Outstandings_)
                & boost::serialization::make_nvp("Prices", Prices_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRendistatoCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRendistatoCalculator() {}
        qlRendistatoCalculator(
            const std::string& ObjectId,
            const std::string& RendistatoBasket,
            const std::string& Euribor,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string RendistatoBasket_;
        std::string Euribor_;
        std::string YieldCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRendistatoCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RendistatoBasket", RendistatoBasket_)
                & boost::serialization::make_nvp("Euribor", Euribor_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRendistatoEquivalentSwapLengthQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRendistatoEquivalentSwapLengthQuote() {}
        qlRendistatoEquivalentSwapLengthQuote(
            const std::string& ObjectId,
            const std::string& RendistatoCalculator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string RendistatoCalculator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRendistatoEquivalentSwapLengthQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RendistatoCalculator", RendistatoCalculator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRendistatoEquivalentSwapSpreadQuote : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRendistatoEquivalentSwapSpreadQuote() {}
        qlRendistatoEquivalentSwapSpreadQuote(
            const std::string& ObjectId,
            const std::string& RendistatoCalculator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string RendistatoCalculator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRendistatoEquivalentSwapSpreadQuote, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RendistatoCalculator", RendistatoCalculator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

