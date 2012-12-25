
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
#include <qlo/cmsmarketcalibration.hpp>
#include <qlo/valueobjects/vo_cmsmarketcalibration.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCmsMarketCalibration::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "VolCube",
        "CmsMarket",
        "Weights",
        "CalibrationType",
        "Permanent"
    };

    std::set<std::string> qlCmsMarketCalibration::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCmsMarketCalibration::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCmsMarketCalibration::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCmsMarketCalibration::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VOLCUBE")==0)
            return VolCube_;
        else if(strcmp(nameUpper.c_str(), "CMSMARKET")==0)
            return CmsMarket_;
        else if(strcmp(nameUpper.c_str(), "WEIGHTS")==0)
            return Weights_;
        else if(strcmp(nameUpper.c_str(), "CALIBRATIONTYPE")==0)
            return CalibrationType_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCmsMarketCalibration::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLCUBE")==0)
            VolCube_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CMSMARKET")==0)
            CmsMarket_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "WEIGHTS")==0)
            Weights_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CALIBRATIONTYPE")==0)
            CalibrationType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCmsMarketCalibration::qlCmsMarketCalibration(
            const std::string& ObjectId,
            const std::string& VolCube,
            const std::string& CmsMarket,
            const std::vector<std::vector<double> >& Weights,
            const std::string& CalibrationType,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCmsMarketCalibration", Permanent),
        VolCube_(VolCube),
        CmsMarket_(CmsMarket),
        Weights_(Weights),
        CalibrationType_(CalibrationType),
        Permanent_(Permanent) {
                  
            processPrecedentID(VolCube);
            processPrecedentID(CmsMarket);
            
    }

 } }
