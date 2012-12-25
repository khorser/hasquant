
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

#ifndef qlo_vo_interpolation_hpp
#define qlo_vo_interpolation_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlAbcdInterpolation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAbcdInterpolation() {}
        qlAbcdInterpolation(
            const std::string& ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            double A,
            double B,
            double C,
            double D,
            bool AIsFixed,
            bool BIsFixed,
            bool CIsFixed,
            bool DIsFixed,
            bool VegaWeighted,
            const std::string& EndCriteria,
            const std::string& OptimizationMeth,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> XArray_;
        std::vector<ObjectHandler::property_t> YArray_;
        double A_;
        double B_;
        double C_;
        double D_;
        bool AIsFixed_;
        bool BIsFixed_;
        bool CIsFixed_;
        bool DIsFixed_;
        bool VegaWeighted_;
        std::string EndCriteria_;
        std::string OptimizationMeth_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAbcdInterpolation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("XArray", XArray_)
                & boost::serialization::make_nvp("YArray", YArray_)
                & boost::serialization::make_nvp("A", A_)
                & boost::serialization::make_nvp("B", B_)
                & boost::serialization::make_nvp("C", C_)
                & boost::serialization::make_nvp("D", D_)
                & boost::serialization::make_nvp("AIsFixed", AIsFixed_)
                & boost::serialization::make_nvp("BIsFixed", BIsFixed_)
                & boost::serialization::make_nvp("CIsFixed", CIsFixed_)
                & boost::serialization::make_nvp("DIsFixed", DIsFixed_)
                & boost::serialization::make_nvp("VegaWeighted", VegaWeighted_)
                & boost::serialization::make_nvp("EndCriteria", EndCriteria_)
                & boost::serialization::make_nvp("OptimizationMeth", OptimizationMeth_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCubicInterpolation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCubicInterpolation() {}
        qlCubicInterpolation(
            const std::string& ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const std::string& DerApprox,
            bool Monotonic,
            const std::string& LeftConditionType,
            double LeftConditionValue,
            const std::string& RightConditionType,
            double RightConditionValue,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> XArray_;
        std::vector<ObjectHandler::property_t> YArray_;
        std::string DerApprox_;
        bool Monotonic_;
        std::string LeftConditionType_;
        double LeftConditionValue_;
        std::string RightConditionType_;
        double RightConditionValue_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCubicInterpolation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("XArray", XArray_)
                & boost::serialization::make_nvp("YArray", YArray_)
                & boost::serialization::make_nvp("DerApprox", DerApprox_)
                & boost::serialization::make_nvp("Monotonic", Monotonic_)
                & boost::serialization::make_nvp("LeftConditionType", LeftConditionType_)
                & boost::serialization::make_nvp("LeftConditionValue", LeftConditionValue_)
                & boost::serialization::make_nvp("RightConditionType", RightConditionType_)
                & boost::serialization::make_nvp("RightConditionValue", RightConditionValue_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlInterpolation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlInterpolation() {}
        qlInterpolation(
            const std::string& ObjectId,
            const std::string& InterpolationType,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string InterpolationType_;
        std::vector<double> XArray_;
        std::vector<ObjectHandler::property_t> YArray_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlInterpolation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("InterpolationType", InterpolationType_)
                & boost::serialization::make_nvp("XArray", XArray_)
                & boost::serialization::make_nvp("YArray", YArray_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlInterpolation2D : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlInterpolation2D() {}
        qlInterpolation2D(
            const std::string& ObjectId,
            const std::string& InterpolationType,
            const std::vector<double>& XArray,
            const std::vector<double>& YArray,
            const std::vector<std::vector<double> >& ZMatrix,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string InterpolationType_;
        std::vector<double> XArray_;
        std::vector<double> YArray_;
        std::vector<std::vector <double> > ZMatrix_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlInterpolation2D, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("InterpolationType", InterpolationType_)
                & boost::serialization::make_nvp("XArray", XArray_)
                & boost::serialization::make_nvp("YArray", YArray_)
                & boost::serialization::make_nvp("ZMatrix", ZMatrix_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMixedLinearCubicInterpolation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMixedLinearCubicInterpolation() {}
        qlMixedLinearCubicInterpolation(
            const std::string& ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            long SwitchIndex,
            const std::string& DerApprox,
            bool Monotonic,
            const std::string& LeftConditionType,
            double LeftConditionValue,
            const std::string& RightConditionType,
            double RightConditionValue,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> XArray_;
        std::vector<ObjectHandler::property_t> YArray_;
        long SwitchIndex_;
        std::string DerApprox_;
        bool Monotonic_;
        std::string LeftConditionType_;
        double LeftConditionValue_;
        std::string RightConditionType_;
        double RightConditionValue_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMixedLinearCubicInterpolation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("XArray", XArray_)
                & boost::serialization::make_nvp("YArray", YArray_)
                & boost::serialization::make_nvp("SwitchIndex", SwitchIndex_)
                & boost::serialization::make_nvp("DerApprox", DerApprox_)
                & boost::serialization::make_nvp("Monotonic", Monotonic_)
                & boost::serialization::make_nvp("LeftConditionType", LeftConditionType_)
                & boost::serialization::make_nvp("LeftConditionValue", LeftConditionValue_)
                & boost::serialization::make_nvp("RightConditionType", RightConditionType_)
                & boost::serialization::make_nvp("RightConditionValue", RightConditionValue_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSABRInterpolation : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSABRInterpolation() {}
        qlSABRInterpolation(
            const std::string& ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            double Expiry,
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
            const std::string& OptimizationMeth,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> XArray_;
        std::vector<ObjectHandler::property_t> YArray_;
        double Expiry_;
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
        std::string OptimizationMeth_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSABRInterpolation, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("XArray", XArray_)
                & boost::serialization::make_nvp("YArray", YArray_)
                & boost::serialization::make_nvp("Expiry", Expiry_)
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
                & boost::serialization::make_nvp("OptimizationMeth", OptimizationMeth_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

