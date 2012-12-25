
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
#include <qlo/abcd.hpp>
#include <qlo/valueobjects/vo_abcd.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAbcdCalibration::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Times",
        "BlackVols",
        "A",
        "B",
        "C",
        "D",
        "AIsFixed",
        "BIsFixed",
        "CIsFixed",
        "DIsFixed",
        "VegaWeighted",
        "EndCriteria",
        "Method",
        "Permanent"
    };

    std::set<std::string> qlAbcdCalibration::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAbcdCalibration::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAbcdCalibration::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAbcdCalibration::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TIMES")==0)
            return Times_;
        else if(strcmp(nameUpper.c_str(), "BLACKVOLS")==0)
            return BlackVols_;
        else if(strcmp(nameUpper.c_str(), "A")==0)
            return A_;
        else if(strcmp(nameUpper.c_str(), "B")==0)
            return B_;
        else if(strcmp(nameUpper.c_str(), "C")==0)
            return C_;
        else if(strcmp(nameUpper.c_str(), "D")==0)
            return D_;
        else if(strcmp(nameUpper.c_str(), "AISFIXED")==0)
            return AIsFixed_;
        else if(strcmp(nameUpper.c_str(), "BISFIXED")==0)
            return BIsFixed_;
        else if(strcmp(nameUpper.c_str(), "CISFIXED")==0)
            return CIsFixed_;
        else if(strcmp(nameUpper.c_str(), "DISFIXED")==0)
            return DIsFixed_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            return VegaWeighted_;
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            return EndCriteria_;
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            return Method_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAbcdCalibration::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TIMES")==0)
            Times_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "BLACKVOLS")==0)
            BlackVols_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "A")==0)
            A_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "B")==0)
            B_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "C")==0)
            C_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "D")==0)
            D_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "AISFIXED")==0)
            AIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BISFIXED")==0)
            BIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "CISFIXED")==0)
            CIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "DISFIXED")==0)
            DIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            VegaWeighted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            EndCriteria_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "METHOD")==0)
            Method_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAbcdCalibration::qlAbcdCalibration(
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
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAbcdCalibration", Permanent),
        Times_(Times),
        BlackVols_(BlackVols),
        A_(A),
        B_(B),
        C_(C),
        D_(D),
        AIsFixed_(AIsFixed),
        BIsFixed_(BIsFixed),
        CIsFixed_(CIsFixed),
        DIsFixed_(DIsFixed),
        VegaWeighted_(VegaWeighted),
        EndCriteria_(EndCriteria),
        Method_(Method),
        Permanent_(Permanent) {
                  
            processPrecedentID(EndCriteria);
            processPrecedentID(Method);
            
    }

    const char* qlAbcdFunction::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "A",
        "B",
        "C",
        "D",
        "Permanent"
    };

    std::set<std::string> qlAbcdFunction::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAbcdFunction::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAbcdFunction::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAbcdFunction::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "A")==0)
            return A_;
        else if(strcmp(nameUpper.c_str(), "B")==0)
            return B_;
        else if(strcmp(nameUpper.c_str(), "C")==0)
            return C_;
        else if(strcmp(nameUpper.c_str(), "D")==0)
            return D_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAbcdFunction::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "A")==0)
            A_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "B")==0)
            B_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "C")==0)
            C_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "D")==0)
            D_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAbcdFunction::qlAbcdFunction(
            const std::string& ObjectId,
            double A,
            double B,
            double C,
            double D,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAbcdFunction", Permanent),
        A_(A),
        B_(B),
        C_(C),
        D_(D),
        Permanent_(Permanent) {
                  

            
    }

 } }
