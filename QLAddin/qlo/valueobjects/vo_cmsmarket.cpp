
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
//      gensrc/gensrc/stubs/stub.vo.includes.body

#include <oh/ohdefines.hpp>
#include <qlo/cmsmarket.hpp>
#include <qlo/valueobjects/vo_cmsmarket.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCmsMarket::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SwapLengths",
        "SwapIndexes",
        "IborIndex",
        "BidAskSpreads",
        "CmsCouponPricers",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlCmsMarket::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCmsMarket::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCmsMarket::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCmsMarket::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SWAPLENGTHS")==0)
            return SwapLengths_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXES")==0)
            return SwapIndexes_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "BIDASKSPREADS")==0)
            return BidAskSpreads_;
        else if(strcmp(nameUpper.c_str(), "CMSCOUPONPRICERS")==0)
            return CmsCouponPricers_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCmsMarket::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPLENGTHS")==0)
            SwapLengths_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXES")==0)
            SwapIndexes_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BIDASKSPREADS")==0)
            BidAskSpreads_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CMSCOUPONPRICERS")==0)
            CmsCouponPricers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCmsMarket::qlCmsMarket(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& SwapLengths,
            const std::vector<std::string>& SwapIndexes,
            const std::string& IborIndex,
            const std::vector<std::vector<ObjectHandler::property_t> >& BidAskSpreads,
            const std::vector<std::string>& CmsCouponPricers,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCmsMarket", Permanent),
        SwapLengths_(SwapLengths),
        SwapIndexes_(SwapIndexes),
        IborIndex_(IborIndex),
        BidAskSpreads_(BidAskSpreads),
        CmsCouponPricers_(CmsCouponPricers),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = SwapIndexes.begin();
                    i != SwapIndexes.end(); ++i)
                processPrecedentID(*i);
            processPrecedentID(IborIndex);
            processVariant(BidAskSpreads);
            for (std::vector<std::string>::const_iterator i = CmsCouponPricers.begin();
                    i != CmsCouponPricers.end(); ++i)
                processPrecedentID(*i);
            processPrecedentID(YieldCurve);
            
    }

 } }
