
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

#ifndef qlo_vo_abcd_hpp
#define qlo_vo_abcd_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlAbcdCalibration : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAbcdCalibration() {}
        qlAbcdCalibration(
            const std::string& ObjectId,
            const std::vector<double>& Times,
            const std::vector<double>& BlackVols,
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
            const std::string& Method,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<double> Times_;
        std::vector<double> BlackVols_;
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
        std::string Method_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAbcdCalibration, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Times", Times_)
                & boost::serialization::make_nvp("BlackVols", BlackVols_)
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
                & boost::serialization::make_nvp("Method", Method_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlAbcdFunction : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAbcdFunction() {}
        qlAbcdFunction(
            const std::string& ObjectId,
            double A,
            double B,
            double C,
            double D,
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
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAbcdFunction, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("A", A_)
                & boost::serialization::make_nvp("B", B_)
                & boost::serialization::make_nvp("C", C_)
                & boost::serialization::make_nvp("D", D_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

