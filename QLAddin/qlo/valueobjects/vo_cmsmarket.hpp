
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

#ifndef qlo_vo_cmsmarket_hpp
#define qlo_vo_cmsmarket_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCmsMarket : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCmsMarket() {}
        qlCmsMarket(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& SwapLengths,
            const std::vector<std::string>& SwapIndexes,
            const std::string& IborIndex,
            const std::vector<std::vector<ObjectHandler::property_t> >& BidAskSpreads,
            const std::vector<std::string>& CmsCouponPricers,
            const std::string& YieldCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<ObjectHandler::property_t> SwapLengths_;
        std::vector<std::string> SwapIndexes_;
        std::string IborIndex_;
        std::vector<std::vector<ObjectHandler::property_t> > BidAskSpreads_;
        std::vector<std::string> CmsCouponPricers_;
        std::string YieldCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCmsMarket, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapLengths", SwapLengths_)
                & boost::serialization::make_nvp("SwapIndexes", SwapIndexes_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("BidAskSpreads", BidAskSpreads_)
                & boost::serialization::make_nvp("CmsCouponPricers", CmsCouponPricers_)
                & boost::serialization::make_nvp("YieldCurve", YieldCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

