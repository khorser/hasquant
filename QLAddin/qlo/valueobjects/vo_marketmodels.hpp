
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

#ifndef qlo_vo_marketmodels_hpp
#define qlo_vo_marketmodels_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlAbcdVol : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAbcdVol() {}
        qlAbcdVol(
            const std::string& ObjectId,
            double A,
            double B,
            double C,
            double D,
            const std::vector<double>& Ks,
            const std::string& Correlations,
            const std::string& EvolutionDescription,
            long Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double A_;
        double B_;
        double C_;
        double D_;
        std::vector<double> Ks_;
        std::string Correlations_;
        std::string EvolutionDescription_;
        long Factors_;
        std::vector<double> InitialRates_;
        std::vector<double> Displacements_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAbcdVol, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("A", A_)
                & boost::serialization::make_nvp("B", B_)
                & boost::serialization::make_nvp("C", C_)
                & boost::serialization::make_nvp("D", D_)
                & boost::serialization::make_nvp("Ks", Ks_)
                & boost::serialization::make_nvp("Correlations", Correlations_)
                & boost::serialization::make_nvp("EvolutionDescription", EvolutionDescription_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("InitialRates", InitialRates_)
                & boost::serialization::make_nvp("Displacements", Displacements_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCotSwapToFwdAdapter : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCotSwapToFwdAdapter() {}
        qlCotSwapToFwdAdapter(
            const std::string& ObjectId,
            const std::string& CoterminalModel,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string CoterminalModel_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCotSwapToFwdAdapter, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CoterminalModel", CoterminalModel_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFlatVol : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFlatVol() {}
        qlFlatVol(
            const std::string& ObjectId,
            const std::vector<double>& Volatilities,
            const std::string& Correlations,
            const std::string& EvolutionDescription,
            long Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> Volatilities_;
        std::string Correlations_;
        std::string EvolutionDescription_;
        long Factors_;
        std::vector<double> InitialRates_;
        std::vector<double> Displacements_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFlatVol, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("Correlations", Correlations_)
                & boost::serialization::make_nvp("EvolutionDescription", EvolutionDescription_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("InitialRates", InitialRates_)
                & boost::serialization::make_nvp("Displacements", Displacements_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFlatVolFactory : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFlatVolFactory() {}
        qlFlatVolFactory(
            const std::string& ObjectId,
            double LongTermCorr,
            double Beta,
            const std::vector<double>& Times,
            const std::vector<double>& Volatilities,
            const std::string& YieldCurve,
            double Displacement,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double LongTermCorr_;
        double Beta_;
        std::vector<double> Times_;
        std::vector<double> Volatilities_;
        std::string YieldCurve_;
        double Displacement_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFlatVolFactory, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("LongTermCorr", LongTermCorr_)
                & boost::serialization::make_nvp("Beta", Beta_)
                & boost::serialization::make_nvp("Times", Times_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Displacement", Displacement_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFwdPeriodAdapter : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFwdPeriodAdapter() {}
        qlFwdPeriodAdapter(
            const std::string& ObjectId,
            const std::string& LargeModel,
            long Period,
            long Offset,
            const std::vector<double>& Displacements,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string LargeModel_;
        long Period_;
        long Offset_;
        std::vector<double> Displacements_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFwdPeriodAdapter, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("LargeModel", LargeModel_)
                & boost::serialization::make_nvp("Period", Period_)
                & boost::serialization::make_nvp("Offset", Offset_)
                & boost::serialization::make_nvp("Displacements", Displacements_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFwdToCotSwapAdapter : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFwdToCotSwapAdapter() {}
        qlFwdToCotSwapAdapter(
            const std::string& ObjectId,
            const std::string& ForwardModel,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string ForwardModel_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFwdToCotSwapAdapter, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("ForwardModel", ForwardModel_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlPseudoRootFacade : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlPseudoRootFacade() {}
        qlPseudoRootFacade(
            const std::string& ObjectId,
            const std::string& Calibrator,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Calibrator_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlPseudoRootFacade, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Calibrator", Calibrator_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

