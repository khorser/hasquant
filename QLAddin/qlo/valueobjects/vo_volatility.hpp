
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

#ifndef qlo_vo_volatility_hpp
#define qlo_vo_volatility_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlMarketModelLmExtLinearExponentialVolModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMarketModelLmExtLinearExponentialVolModel() {}
        qlMarketModelLmExtLinearExponentialVolModel(
            const std::string& ObjectId,
            const std::vector<double>& FixingTimes,
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

        std::vector<double> FixingTimes_;
        double A_;
        double B_;
        double C_;
        double D_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMarketModelLmExtLinearExponentialVolModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("FixingTimes", FixingTimes_)
                & boost::serialization::make_nvp("A", A_)
                & boost::serialization::make_nvp("B", B_)
                & boost::serialization::make_nvp("C", C_)
                & boost::serialization::make_nvp("D", D_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlPiecewiseConstantAbcdVariance : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlPiecewiseConstantAbcdVariance() {}
        qlPiecewiseConstantAbcdVariance(
            const std::string& ObjectId,
            double A,
            double B,
            double C,
            double D,
            long ResetIndex,
            const std::vector<double>& RateTimes,
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
        long ResetIndex_;
        std::vector<double> RateTimes_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlPiecewiseConstantAbcdVariance, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("A", A_)
                & boost::serialization::make_nvp("B", B_)
                & boost::serialization::make_nvp("C", C_)
                & boost::serialization::make_nvp("D", D_)
                & boost::serialization::make_nvp("ResetIndex", ResetIndex_)
                & boost::serialization::make_nvp("RateTimes", RateTimes_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

