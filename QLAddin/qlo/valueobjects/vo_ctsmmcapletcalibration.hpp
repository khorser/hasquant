
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

#ifndef qlo_vo_ctsmmcapletcalibration_hpp
#define qlo_vo_ctsmmcapletcalibration_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCTSMMCapletAlphaFormCalibration : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCTSMMCapletAlphaFormCalibration() {}
        qlCTSMMCapletAlphaFormCalibration(
            const std::string& ObjectId,
            const std::string& Evolution,
            const std::string& Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string& CurveState,
            double Displacement,
            const std::vector<double>& AlphaInitial,
            const std::vector<double>& AlphaMax,
            const std::vector<double>& AlphaMin,
            bool MaximizeHomogeneity,
            const std::string& AlphaForm,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Evolution_;
        std::string Correlations_;
        std::vector<std::string> SwapPiecewiseConstantVariances_;
        std::vector<double> CapletVols_;
        std::string CurveState_;
        double Displacement_;
        std::vector<double> AlphaInitial_;
        std::vector<double> AlphaMax_;
        std::vector<double> AlphaMin_;
        bool MaximizeHomogeneity_;
        std::string AlphaForm_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCTSMMCapletAlphaFormCalibration, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Evolution", Evolution_)
                & boost::serialization::make_nvp("Correlations", Correlations_)
                & boost::serialization::make_nvp("SwapPiecewiseConstantVariances", SwapPiecewiseConstantVariances_)
                & boost::serialization::make_nvp("CapletVols", CapletVols_)
                & boost::serialization::make_nvp("CurveState", CurveState_)
                & boost::serialization::make_nvp("Displacement", Displacement_)
                & boost::serialization::make_nvp("AlphaInitial", AlphaInitial_)
                & boost::serialization::make_nvp("AlphaMax", AlphaMax_)
                & boost::serialization::make_nvp("AlphaMin", AlphaMin_)
                & boost::serialization::make_nvp("MaximizeHomogeneity", MaximizeHomogeneity_)
                & boost::serialization::make_nvp("AlphaForm", AlphaForm_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCTSMMCapletMaxHomogeneityCalibration : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCTSMMCapletMaxHomogeneityCalibration() {}
        qlCTSMMCapletMaxHomogeneityCalibration(
            const std::string& ObjectId,
            const std::string& Evolution,
            const std::string& Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string& CurveState,
            double Displacement,
            double Caplet0Swaption1Priority,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Evolution_;
        std::string Correlations_;
        std::vector<std::string> SwapPiecewiseConstantVariances_;
        std::vector<double> CapletVols_;
        std::string CurveState_;
        double Displacement_;
        double Caplet0Swaption1Priority_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCTSMMCapletMaxHomogeneityCalibration, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Evolution", Evolution_)
                & boost::serialization::make_nvp("Correlations", Correlations_)
                & boost::serialization::make_nvp("SwapPiecewiseConstantVariances", SwapPiecewiseConstantVariances_)
                & boost::serialization::make_nvp("CapletVols", CapletVols_)
                & boost::serialization::make_nvp("CurveState", CurveState_)
                & boost::serialization::make_nvp("Displacement", Displacement_)
                & boost::serialization::make_nvp("Caplet0Swaption1Priority", Caplet0Swaption1Priority_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCTSMMCapletOriginalCalibration : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCTSMMCapletOriginalCalibration() {}
        qlCTSMMCapletOriginalCalibration(
            const std::string& ObjectId,
            const std::string& Evolution,
            const std::string& Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string& CurveState,
            double Displacement,
            const std::vector<double>& Alphas,
            bool LowestRoot,
            bool UseFullApprox,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string Evolution_;
        std::string Correlations_;
        std::vector<std::string> SwapPiecewiseConstantVariances_;
        std::vector<double> CapletVols_;
        std::string CurveState_;
        double Displacement_;
        std::vector<double> Alphas_;
        bool LowestRoot_;
        bool UseFullApprox_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCTSMMCapletOriginalCalibration, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Evolution", Evolution_)
                & boost::serialization::make_nvp("Correlations", Correlations_)
                & boost::serialization::make_nvp("SwapPiecewiseConstantVariances", SwapPiecewiseConstantVariances_)
                & boost::serialization::make_nvp("CapletVols", CapletVols_)
                & boost::serialization::make_nvp("CurveState", CurveState_)
                & boost::serialization::make_nvp("Displacement", Displacement_)
                & boost::serialization::make_nvp("Alphas", Alphas_)
                & boost::serialization::make_nvp("LowestRoot", LowestRoot_)
                & boost::serialization::make_nvp("UseFullApprox", UseFullApprox_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

