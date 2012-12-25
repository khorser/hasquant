
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

#ifndef qlo_vo_smilesection_hpp
#define qlo_vo_smilesection_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlFlatSmileSection : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFlatSmileSection() {}
        qlFlatSmileSection(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            double Volatility,
            const std::string& DayCounter,
            const ObjectHandler::property_t& RefDate,
            double AtmValue,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t OptionDate_;
        double Volatility_;
        std::string DayCounter_;
        ObjectHandler::property_t RefDate_;
        double AtmValue_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFlatSmileSection, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionDate", OptionDate_)
                & boost::serialization::make_nvp("Volatility", Volatility_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("RefDate", RefDate_)
                & boost::serialization::make_nvp("AtmValue", AtmValue_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlInterpolatedSmileSection : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlInterpolatedSmileSection() {}
        qlInterpolatedSmileSection(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t& AtmLevel,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t OptionDate_;
        std::vector<double> Strikes_;
        std::vector<ObjectHandler::property_t> StdDevs_;
        ObjectHandler::property_t AtmLevel_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlInterpolatedSmileSection, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionDate", OptionDate_)
                & boost::serialization::make_nvp("Strikes", Strikes_)
                & boost::serialization::make_nvp("StdDevs", StdDevs_)
                & boost::serialization::make_nvp("AtmLevel", AtmLevel_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSabrInterpolatedSmileSection : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSabrInterpolatedSmileSection() {}
        qlSabrInterpolatedSmileSection(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            double ForwardRate,
            const std::vector<double>& Strike,
            bool FloatingStrike,
            double AtmVolatility,
            const std::vector<double>& VolatilitySpreads,
            double Alpha,
            double Beta,
            double Nu,
            double Rho,
            bool AlphaIsFixed,
            bool BetaIsFixed,
            bool NuIsFixed,
            bool RhoIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& Method,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t OptionDate_;
        double ForwardRate_;
        std::vector<double> Strike_;
        bool FloatingStrike_;
        double AtmVolatility_;
        std::vector<double> VolatilitySpreads_;
        double Alpha_;
        double Beta_;
        double Nu_;
        double Rho_;
        bool AlphaIsFixed_;
        bool BetaIsFixed_;
        bool NuIsFixed_;
        bool RhoIsFixed_;
        bool VegaWeighted_;
        std::string EndCriteria_;
        std::string Method_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSabrInterpolatedSmileSection, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionDate", OptionDate_)
                & boost::serialization::make_nvp("ForwardRate", ForwardRate_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("FloatingStrike", FloatingStrike_)
                & boost::serialization::make_nvp("AtmVolatility", AtmVolatility_)
                & boost::serialization::make_nvp("VolatilitySpreads", VolatilitySpreads_)
                & boost::serialization::make_nvp("Alpha", Alpha_)
                & boost::serialization::make_nvp("Beta", Beta_)
                & boost::serialization::make_nvp("Nu", Nu_)
                & boost::serialization::make_nvp("Rho", Rho_)
                & boost::serialization::make_nvp("AlphaIsFixed", AlphaIsFixed_)
                & boost::serialization::make_nvp("BetaIsFixed", BetaIsFixed_)
                & boost::serialization::make_nvp("NuIsFixed", NuIsFixed_)
                & boost::serialization::make_nvp("RhoIsFixed", RhoIsFixed_)
                & boost::serialization::make_nvp("VegaWeighted", VegaWeighted_)
                & boost::serialization::make_nvp("EndCriteria", EndCriteria_)
                & boost::serialization::make_nvp("Method", Method_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSabrInterpolatedSmileSection1 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSabrInterpolatedSmileSection1() {}
        qlSabrInterpolatedSmileSection1(
            const std::string& ObjectId,
            const ObjectHandler::property_t& OptionDate,
            const ObjectHandler::property_t& ForwardRate,
            const std::vector<double>& Strike,
            bool FloatingStrike,
            const ObjectHandler::property_t& AtmVolatility,
            const std::vector<ObjectHandler::property_t>& VolatilitySpreads,
            double Alpha,
            double Beta,
            double Nu,
            double Rho,
            bool AlphaIsFixed,
            bool BetaIsFixed,
            bool NuIsFixed,
            bool RhoIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& Method,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t OptionDate_;
        ObjectHandler::property_t ForwardRate_;
        std::vector<double> Strike_;
        bool FloatingStrike_;
        ObjectHandler::property_t AtmVolatility_;
        std::vector<ObjectHandler::property_t> VolatilitySpreads_;
        double Alpha_;
        double Beta_;
        double Nu_;
        double Rho_;
        bool AlphaIsFixed_;
        bool BetaIsFixed_;
        bool NuIsFixed_;
        bool RhoIsFixed_;
        bool VegaWeighted_;
        std::string EndCriteria_;
        std::string Method_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSabrInterpolatedSmileSection1, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionDate", OptionDate_)
                & boost::serialization::make_nvp("ForwardRate", ForwardRate_)
                & boost::serialization::make_nvp("Strike", Strike_)
                & boost::serialization::make_nvp("FloatingStrike", FloatingStrike_)
                & boost::serialization::make_nvp("AtmVolatility", AtmVolatility_)
                & boost::serialization::make_nvp("VolatilitySpreads", VolatilitySpreads_)
                & boost::serialization::make_nvp("Alpha", Alpha_)
                & boost::serialization::make_nvp("Beta", Beta_)
                & boost::serialization::make_nvp("Nu", Nu_)
                & boost::serialization::make_nvp("Rho", Rho_)
                & boost::serialization::make_nvp("AlphaIsFixed", AlphaIsFixed_)
                & boost::serialization::make_nvp("BetaIsFixed", BetaIsFixed_)
                & boost::serialization::make_nvp("NuIsFixed", NuIsFixed_)
                & boost::serialization::make_nvp("RhoIsFixed", RhoIsFixed_)
                & boost::serialization::make_nvp("VegaWeighted", VegaWeighted_)
                & boost::serialization::make_nvp("EndCriteria", EndCriteria_)
                & boost::serialization::make_nvp("Method", Method_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSabrSmileSection : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSabrSmileSection() {}
        qlSabrSmileSection(
            const std::string& ObjectId,
            double OptionTime,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t& Forward,
            double Alpha,
            double Beta,
            double Nu,
            double Rho,
            bool AlphaIsFixed,
            bool BetaIsFixed,
            bool NuIsFixed,
            bool RhoIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& Method,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double OptionTime_;
        std::vector<double> Strikes_;
        std::vector<ObjectHandler::property_t> StdDevs_;
        ObjectHandler::property_t Forward_;
        double Alpha_;
        double Beta_;
        double Nu_;
        double Rho_;
        bool AlphaIsFixed_;
        bool BetaIsFixed_;
        bool NuIsFixed_;
        bool RhoIsFixed_;
        bool VegaWeighted_;
        std::string EndCriteria_;
        std::string Method_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSabrSmileSection, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionTime", OptionTime_)
                & boost::serialization::make_nvp("Strikes", Strikes_)
                & boost::serialization::make_nvp("StdDevs", StdDevs_)
                & boost::serialization::make_nvp("Forward", Forward_)
                & boost::serialization::make_nvp("Alpha", Alpha_)
                & boost::serialization::make_nvp("Beta", Beta_)
                & boost::serialization::make_nvp("Nu", Nu_)
                & boost::serialization::make_nvp("Rho", Rho_)
                & boost::serialization::make_nvp("AlphaIsFixed", AlphaIsFixed_)
                & boost::serialization::make_nvp("BetaIsFixed", BetaIsFixed_)
                & boost::serialization::make_nvp("NuIsFixed", NuIsFixed_)
                & boost::serialization::make_nvp("RhoIsFixed", RhoIsFixed_)
                & boost::serialization::make_nvp("VegaWeighted", VegaWeighted_)
                & boost::serialization::make_nvp("EndCriteria", EndCriteria_)
                & boost::serialization::make_nvp("Method", Method_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSmileSectionFromSabrVolSurface : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSmileSectionFromSabrVolSurface() {}
        qlSmileSectionFromSabrVolSurface(
            const std::string& ObjectId,
            const std::string& SabrVolSurface,
            double OptionTime,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SabrVolSurface_;
        double OptionTime_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSmileSectionFromSabrVolSurface, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SabrVolSurface", SabrVolSurface_)
                & boost::serialization::make_nvp("OptionTime", OptionTime_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

