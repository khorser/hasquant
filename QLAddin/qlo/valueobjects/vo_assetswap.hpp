
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

#ifndef qlo_vo_assetswap_hpp
#define qlo_vo_assetswap_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlAssetSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAssetSwap() {}
        qlAssetSwap(
            const std::string& ObjectId,
            bool PayBondCoupon,
            const std::string& Bond,
            double CleanPrice,
            const std::string& IborIndex,
            double Spread,
            const std::string& FloatingLegSchedule,
            const std::string& FloatingLegDayCounter,
            bool ParAssetSwap,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        bool PayBondCoupon_;
        std::string Bond_;
        double CleanPrice_;
        std::string IborIndex_;
        double Spread_;
        std::string FloatingLegSchedule_;
        std::string FloatingLegDayCounter_;
        bool ParAssetSwap_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAssetSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PayBondCoupon", PayBondCoupon_)
                & boost::serialization::make_nvp("Bond", Bond_)
                & boost::serialization::make_nvp("CleanPrice", CleanPrice_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("FloatingLegSchedule", FloatingLegSchedule_)
                & boost::serialization::make_nvp("FloatingLegDayCounter", FloatingLegDayCounter_)
                & boost::serialization::make_nvp("ParAssetSwap", ParAssetSwap_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlAssetSwap2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAssetSwap2() {}
        qlAssetSwap2(
            const std::string& ObjectId,
            bool ParAssetSwap,
            const std::string& Bond,
            double CleanPrice,
            double NonParRepayment,
            double Gearing,
            const std::string& IborIndex,
            double Spread,
            const std::string& FloatingLegDayCounter,
            const ObjectHandler::property_t& DealMaturity,
            bool PayBondCoupon,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        bool ParAssetSwap_;
        std::string Bond_;
        double CleanPrice_;
        double NonParRepayment_;
        double Gearing_;
        std::string IborIndex_;
        double Spread_;
        std::string FloatingLegDayCounter_;
        ObjectHandler::property_t DealMaturity_;
        bool PayBondCoupon_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAssetSwap2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("ParAssetSwap", ParAssetSwap_)
                & boost::serialization::make_nvp("Bond", Bond_)
                & boost::serialization::make_nvp("CleanPrice", CleanPrice_)
                & boost::serialization::make_nvp("NonParRepayment", NonParRepayment_)
                & boost::serialization::make_nvp("Gearing", Gearing_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("FloatingLegDayCounter", FloatingLegDayCounter_)
                & boost::serialization::make_nvp("DealMaturity", DealMaturity_)
                & boost::serialization::make_nvp("PayBondCoupon", PayBondCoupon_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

