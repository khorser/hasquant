
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

#ifndef qlo_vo_payoffs_hpp
#define qlo_vo_payoffs_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlDoubleStickyRatchetPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDoubleStickyRatchetPayoff() {}
        qlDoubleStickyRatchetPayoff(
            const std::string& ObjectId,
            double Type1,
            double Type2,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Type1_;
        double Type2_;
        double Gearing1_;
        double Gearing2_;
        double Gearing3_;
        double Spread1_;
        double Spread2_;
        double Spread3_;
        double InitialValue1_;
        double InitialValue2_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDoubleStickyRatchetPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Type1", Type1_)
                & boost::serialization::make_nvp("Type2", Type2_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Gearing3", Gearing3_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("Spread3", Spread3_)
                & boost::serialization::make_nvp("InitialValue1", InitialValue1_)
                & boost::serialization::make_nvp("InitialValue2", InitialValue2_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRatchetMaxPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRatchetMaxPayoff() {}
        qlRatchetMaxPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Gearing1_;
        double Gearing2_;
        double Gearing3_;
        double Spread1_;
        double Spread2_;
        double Spread3_;
        double InitialValue1_;
        double InitialValue2_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRatchetMaxPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Gearing3", Gearing3_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("Spread3", Spread3_)
                & boost::serialization::make_nvp("InitialValue1", InitialValue1_)
                & boost::serialization::make_nvp("InitialValue2", InitialValue2_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRatchetMinPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRatchetMinPayoff() {}
        qlRatchetMinPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Gearing1_;
        double Gearing2_;
        double Gearing3_;
        double Spread1_;
        double Spread2_;
        double Spread3_;
        double InitialValue1_;
        double InitialValue2_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRatchetMinPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Gearing3", Gearing3_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("Spread3", Spread3_)
                & boost::serialization::make_nvp("InitialValue1", InitialValue1_)
                & boost::serialization::make_nvp("InitialValue2", InitialValue2_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRatchetPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRatchetPayoff() {}
        qlRatchetPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Spread1,
            double Spread2,
            double InitialValue,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Gearing1_;
        double Gearing2_;
        double Spread1_;
        double Spread2_;
        double InitialValue_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRatchetPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("InitialValue", InitialValue_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlStickyMaxPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlStickyMaxPayoff() {}
        qlStickyMaxPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Gearing1_;
        double Gearing2_;
        double Gearing3_;
        double Spread1_;
        double Spread2_;
        double Spread3_;
        double InitialValue1_;
        double InitialValue2_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlStickyMaxPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Gearing3", Gearing3_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("Spread3", Spread3_)
                & boost::serialization::make_nvp("InitialValue1", InitialValue1_)
                & boost::serialization::make_nvp("InitialValue2", InitialValue2_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlStickyMinPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlStickyMinPayoff() {}
        qlStickyMinPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Gearing3,
            double Spread1,
            double Spread2,
            double Spread3,
            double InitialValue1,
            double InitialValue2,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Gearing1_;
        double Gearing2_;
        double Gearing3_;
        double Spread1_;
        double Spread2_;
        double Spread3_;
        double InitialValue1_;
        double InitialValue2_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlStickyMinPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Gearing3", Gearing3_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("Spread3", Spread3_)
                & boost::serialization::make_nvp("InitialValue1", InitialValue1_)
                & boost::serialization::make_nvp("InitialValue2", InitialValue2_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlStickyPayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlStickyPayoff() {}
        qlStickyPayoff(
            const std::string& ObjectId,
            double Gearing1,
            double Gearing2,
            double Spread1,
            double Spread2,
            double InitialValue,
            double AccrualFactor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Gearing1_;
        double Gearing2_;
        double Spread1_;
        double Spread2_;
        double InitialValue_;
        double AccrualFactor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlStickyPayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Gearing1", Gearing1_)
                & boost::serialization::make_nvp("Gearing2", Gearing2_)
                & boost::serialization::make_nvp("Spread1", Spread1_)
                & boost::serialization::make_nvp("Spread2", Spread2_)
                & boost::serialization::make_nvp("InitialValue", InitialValue_)
                & boost::serialization::make_nvp("AccrualFactor", AccrualFactor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlStrikedTypePayoff : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlStrikedTypePayoff() {}
        qlStrikedTypePayoff(
            const std::string& ObjectId,
            const std::string& PayoffID,
            const std::string& OptionType,
            double Strike,
            double ThirdParameter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PayoffID_;
        std::string OptionType_;
        double Strike_;
        double ThirdParameter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlStrikedTypePayoff, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PayoffID", PayoffID_)
                & boost::serialization::make_nvp("OptionType", OptionType_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("ThirdParameter", ThirdParameter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

