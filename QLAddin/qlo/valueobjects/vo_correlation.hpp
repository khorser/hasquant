
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

#ifndef qlo_vo_correlation_hpp
#define qlo_vo_correlation_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCotSwapFromFwdCorrelation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCotSwapFromFwdCorrelation() {}
        qlCotSwapFromFwdCorrelation(
            const std::string& ObjectId,
            const std::string& FwdCorr,
            const std::string& CurveState,
            double Displacement,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string FwdCorr_;
        std::string CurveState_;
        double Displacement_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCotSwapFromFwdCorrelation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FwdCorr", FwdCorr_)
                & boost::serialization::make_nvp("CurveState", CurveState_)
                & boost::serialization::make_nvp("Displacement", Displacement_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlExponentialForwardCorrelation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlExponentialForwardCorrelation() {}
        qlExponentialForwardCorrelation(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            double LongTermCorr,
            double Beta,
            double Gamma,
            const std::vector<double>& Times,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> RateTimes_;
        double LongTermCorr_;
        double Beta_;
        double Gamma_;
        std::vector<double> Times_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlExponentialForwardCorrelation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("RateTimes", RateTimes_)
                & boost::serialization::make_nvp("LongTermCorr", LongTermCorr_)
                & boost::serialization::make_nvp("Beta", Beta_)
                & boost::serialization::make_nvp("Gamma", Gamma_)
                & boost::serialization::make_nvp("Times", Times_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlHistoricalForwardRatesAnalysis : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlHistoricalForwardRatesAnalysis() {}
        qlHistoricalForwardRatesAnalysis(
            const std::string& ObjectId,
            const std::string& SequenceStats,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const std::string& Step,
            const std::string& IborIndex,
            const std::string& InitialGap,
            const std::string& Horizon,
            const std::vector<std::string>& IborIndexes,
            const std::vector<std::string>& SwapIndexes,
            const std::string& DayCounter,
            const std::string& TraitsID,
            const std::string& InterpolatorID,
            double BootstrapAccuracy,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SequenceStats_;
        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t EndDate_;
        std::string Step_;
        std::string IborIndex_;
        std::string InitialGap_;
        std::string Horizon_;
        std::vector<std::string> IborIndexes_;
        std::vector<std::string> SwapIndexes_;
        std::string DayCounter_;
        std::string TraitsID_;
        std::string InterpolatorID_;
        double BootstrapAccuracy_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlHistoricalForwardRatesAnalysis, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SequenceStats", SequenceStats_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("EndDate", EndDate_)
                & boost::serialization::make_nvp("Step", Step_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("InitialGap", InitialGap_)
                & boost::serialization::make_nvp("Horizon", Horizon_)
                & boost::serialization::make_nvp("IborIndexes", IborIndexes_)
                & boost::serialization::make_nvp("SwapIndexes", SwapIndexes_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("TraitsID", TraitsID_)
                & boost::serialization::make_nvp("InterpolatorID", InterpolatorID_)
                & boost::serialization::make_nvp("BootstrapAccuracy", BootstrapAccuracy_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlHistoricalRatesAnalysis : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlHistoricalRatesAnalysis() {}
        qlHistoricalRatesAnalysis(
            const std::string& ObjectId,
            const std::string& SequenceStats,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const std::string& Step,
            const std::vector<std::string>& InterestRateIndexes,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SequenceStats_;
        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t EndDate_;
        std::string Step_;
        std::vector<std::string> InterestRateIndexes_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlHistoricalRatesAnalysis, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SequenceStats", SequenceStats_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("EndDate", EndDate_)
                & boost::serialization::make_nvp("Step", Step_)
                & boost::serialization::make_nvp("InterestRateIndexes", InterestRateIndexes_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMarketModelLmLinearExponentialCorrelationModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMarketModelLmLinearExponentialCorrelationModel() {}
        qlMarketModelLmLinearExponentialCorrelationModel(
            const std::string& ObjectId,
            long Size,
            double Rho,
            double Beta,
            long Factors,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        long Size_;
        double Rho_;
        double Beta_;
        long Factors_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMarketModelLmLinearExponentialCorrelationModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Size", Size_)
                & boost::serialization::make_nvp("Rho", Rho_)
                & boost::serialization::make_nvp("Beta", Beta_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlTimeHomogeneousForwardCorrelation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlTimeHomogeneousForwardCorrelation() {}
        qlTimeHomogeneousForwardCorrelation(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& FwdCorrMatrix,
            const std::vector<double>& RateTimes,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > FwdCorrMatrix_;
        std::vector<double> RateTimes_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlTimeHomogeneousForwardCorrelation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FwdCorrMatrix", FwdCorrMatrix_)
                & boost::serialization::make_nvp("RateTimes", RateTimes_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

