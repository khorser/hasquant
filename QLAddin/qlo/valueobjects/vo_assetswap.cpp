
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
#include <qlo/assetswap.hpp>
#include <qlo/valueobjects/vo_assetswap.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAssetSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "PayBondCoupon",
        "Bond",
        "CleanPrice",
        "IborIndex",
        "Spread",
        "FloatingLegSchedule",
        "FloatingLegDayCounter",
        "ParAssetSwap",
        "Permanent"
    };

    std::set<std::string> qlAssetSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAssetSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAssetSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAssetSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PAYBONDCOUPON")==0)
            return PayBondCoupon_;
        else if(strcmp(nameUpper.c_str(), "BOND")==0)
            return Bond_;
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            return CleanPrice_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGSCHEDULE")==0)
            return FloatingLegSchedule_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGDAYCOUNTER")==0)
            return FloatingLegDayCounter_;
        else if(strcmp(nameUpper.c_str(), "PARASSETSWAP")==0)
            return ParAssetSwap_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAssetSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYBONDCOUPON")==0)
            PayBondCoupon_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BOND")==0)
            Bond_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            CleanPrice_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGSCHEDULE")==0)
            FloatingLegSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGDAYCOUNTER")==0)
            FloatingLegDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PARASSETSWAP")==0)
            ParAssetSwap_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAssetSwap::qlAssetSwap(
            const std::string& ObjectId,
            bool PayBondCoupon,
            const std::string& Bond,
            double CleanPrice,
            const std::string& IborIndex,
            double Spread,
            const std::string& FloatingLegSchedule,
            const std::string& FloatingLegDayCounter,
            bool ParAssetSwap,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAssetSwap", Permanent),
        PayBondCoupon_(PayBondCoupon),
        Bond_(Bond),
        CleanPrice_(CleanPrice),
        IborIndex_(IborIndex),
        Spread_(Spread),
        FloatingLegSchedule_(FloatingLegSchedule),
        FloatingLegDayCounter_(FloatingLegDayCounter),
        ParAssetSwap_(ParAssetSwap),
        Permanent_(Permanent) {
                  
            processPrecedentID(Bond);
            processPrecedentID(IborIndex);
            processPrecedentID(FloatingLegSchedule);
            
    }

    const char* qlAssetSwap2::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ParAssetSwap",
        "Bond",
        "CleanPrice",
        "NonParRepayment",
        "Gearing",
        "IborIndex",
        "Spread",
        "FloatingLegDayCounter",
        "DealMaturity",
        "PayBondCoupon",
        "Permanent"
    };

    std::set<std::string> qlAssetSwap2::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAssetSwap2::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAssetSwap2::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAssetSwap2::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PARASSETSWAP")==0)
            return ParAssetSwap_;
        else if(strcmp(nameUpper.c_str(), "BOND")==0)
            return Bond_;
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            return CleanPrice_;
        else if(strcmp(nameUpper.c_str(), "NONPARREPAYMENT")==0)
            return NonParRepayment_;
        else if(strcmp(nameUpper.c_str(), "GEARING")==0)
            return Gearing_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGDAYCOUNTER")==0)
            return FloatingLegDayCounter_;
        else if(strcmp(nameUpper.c_str(), "DEALMATURITY")==0)
            return DealMaturity_;
        else if(strcmp(nameUpper.c_str(), "PAYBONDCOUPON")==0)
            return PayBondCoupon_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAssetSwap2::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PARASSETSWAP")==0)
            ParAssetSwap_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BOND")==0)
            Bond_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLEANPRICE")==0)
            CleanPrice_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NONPARREPAYMENT")==0)
            NonParRepayment_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GEARING")==0)
            Gearing_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FLOATINGLEGDAYCOUNTER")==0)
            FloatingLegDayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DEALMATURITY")==0)
            DealMaturity_ = value;
        else if(strcmp(nameUpper.c_str(), "PAYBONDCOUPON")==0)
            PayBondCoupon_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAssetSwap2::qlAssetSwap2(
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
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAssetSwap2", Permanent),
        ParAssetSwap_(ParAssetSwap),
        Bond_(Bond),
        CleanPrice_(CleanPrice),
        NonParRepayment_(NonParRepayment),
        Gearing_(Gearing),
        IborIndex_(IborIndex),
        Spread_(Spread),
        FloatingLegDayCounter_(FloatingLegDayCounter),
        DealMaturity_(DealMaturity),
        PayBondCoupon_(PayBondCoupon),
        Permanent_(Permanent) {
                  
            processPrecedentID(Bond);
            processPrecedentID(IborIndex);
            
    }

 } }
