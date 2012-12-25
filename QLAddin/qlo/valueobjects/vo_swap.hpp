
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

#ifndef qlo_vo_swap_hpp
#define qlo_vo_swap_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlMakeCms : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMakeCms() {}
        qlMakeCms(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& SwapIndex,
            const std::string& IborIndex,
            double IborSpread,
            const std::string& ForwardStart,
            const std::string& CmsCouponPricer,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapTenor_;
        std::string SwapIndex_;
        std::string IborIndex_;
        double IborSpread_;
        std::string ForwardStart_;
        std::string CmsCouponPricer_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMakeCms, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("SwapIndex", SwapIndex_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("IborSpread", IborSpread_)
                & boost::serialization::make_nvp("ForwardStart", ForwardStart_)
                & boost::serialization::make_nvp("CmsCouponPricer", CmsCouponPricer_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSwap() {}
        qlSwap(
            const std::string& ObjectId,
            const std::vector<std::string>& LegIDs,
            const std::vector<bool>& Payer,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::string> LegIDs_;
        std::vector<bool> Payer_;
        bool Permanent_;
        virtual std::string processorName() { return "InstrumentProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("LegIDs", LegIDs_)
                & boost::serialization::make_nvp("Payer", Payer_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

