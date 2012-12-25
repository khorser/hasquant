
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
#include <qlo/interpolation.hpp>
#include <qlo/valueobjects/vo_interpolation.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAbcdInterpolation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "XArray",
        "YArray",
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
        "OptimizationMeth",
        "Permanent"
    };

    std::set<std::string> qlAbcdInterpolation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAbcdInterpolation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAbcdInterpolation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAbcdInterpolation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            return XArray_;
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            return YArray_;
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
        else if(strcmp(nameUpper.c_str(), "OPTIMIZATIONMETH")==0)
            return OptimizationMeth_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAbcdInterpolation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            XArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            YArray_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
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
        else if(strcmp(nameUpper.c_str(), "OPTIMIZATIONMETH")==0)
            OptimizationMeth_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAbcdInterpolation::qlAbcdInterpolation(
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
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAbcdInterpolation", Permanent),
        XArray_(XArray),
        YArray_(YArray),
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
        OptimizationMeth_(OptimizationMeth),
        Permanent_(Permanent) {
                  
            processVariant(YArray);
            processPrecedentID(EndCriteria);
            processPrecedentID(OptimizationMeth);
            
    }

    const char* qlCubicInterpolation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "XArray",
        "YArray",
        "DerApprox",
        "Monotonic",
        "LeftConditionType",
        "LeftConditionValue",
        "RightConditionType",
        "RightConditionValue",
        "Permanent"
    };

    std::set<std::string> qlCubicInterpolation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCubicInterpolation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCubicInterpolation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCubicInterpolation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            return XArray_;
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            return YArray_;
        else if(strcmp(nameUpper.c_str(), "DERAPPROX")==0)
            return DerApprox_;
        else if(strcmp(nameUpper.c_str(), "MONOTONIC")==0)
            return Monotonic_;
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONTYPE")==0)
            return LeftConditionType_;
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONVALUE")==0)
            return LeftConditionValue_;
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONTYPE")==0)
            return RightConditionType_;
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONVALUE")==0)
            return RightConditionValue_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCubicInterpolation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            XArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            YArray_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DERAPPROX")==0)
            DerApprox_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MONOTONIC")==0)
            Monotonic_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONTYPE")==0)
            LeftConditionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONVALUE")==0)
            LeftConditionValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONTYPE")==0)
            RightConditionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONVALUE")==0)
            RightConditionValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCubicInterpolation::qlCubicInterpolation(
            const std::string& ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const std::string& DerApprox,
            bool Monotonic,
            const std::string& LeftConditionType,
            double LeftConditionValue,
            const std::string& RightConditionType,
            double RightConditionValue,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCubicInterpolation", Permanent),
        XArray_(XArray),
        YArray_(YArray),
        DerApprox_(DerApprox),
        Monotonic_(Monotonic),
        LeftConditionType_(LeftConditionType),
        LeftConditionValue_(LeftConditionValue),
        RightConditionType_(RightConditionType),
        RightConditionValue_(RightConditionValue),
        Permanent_(Permanent) {
                  
            processVariant(YArray);
            
    }

    const char* qlInterpolation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "InterpolationType",
        "XArray",
        "YArray",
        "Permanent"
    };

    std::set<std::string> qlInterpolation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlInterpolation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlInterpolation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlInterpolation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATIONTYPE")==0)
            return InterpolationType_;
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            return XArray_;
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            return YArray_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlInterpolation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATIONTYPE")==0)
            InterpolationType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            XArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            YArray_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlInterpolation::qlInterpolation(
            const std::string& ObjectId,
            const std::string& InterpolationType,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlInterpolation", Permanent),
        InterpolationType_(InterpolationType),
        XArray_(XArray),
        YArray_(YArray),
        Permanent_(Permanent) {
                  
            processVariant(YArray);
            
    }

    const char* qlInterpolation2D::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "InterpolationType",
        "XArray",
        "YArray",
        "ZMatrix",
        "Permanent"
    };

    std::set<std::string> qlInterpolation2D::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlInterpolation2D::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlInterpolation2D::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlInterpolation2D::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATIONTYPE")==0)
            return InterpolationType_;
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            return XArray_;
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            return YArray_;
        else if(strcmp(nameUpper.c_str(), "ZMATRIX")==0)
            return ZMatrix_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlInterpolation2D::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATIONTYPE")==0)
            InterpolationType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            XArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            YArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ZMATRIX")==0)
            ZMatrix_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlInterpolation2D::qlInterpolation2D(
            const std::string& ObjectId,
            const std::string& InterpolationType,
            const std::vector<double>& XArray,
            const std::vector<double>& YArray,
            const std::vector<std::vector<double> >& ZMatrix,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlInterpolation2D", Permanent),
        InterpolationType_(InterpolationType),
        XArray_(XArray),
        YArray_(YArray),
        ZMatrix_(ZMatrix),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlMixedLinearCubicInterpolation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "XArray",
        "YArray",
        "SwitchIndex",
        "DerApprox",
        "Monotonic",
        "LeftConditionType",
        "LeftConditionValue",
        "RightConditionType",
        "RightConditionValue",
        "Permanent"
    };

    std::set<std::string> qlMixedLinearCubicInterpolation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMixedLinearCubicInterpolation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMixedLinearCubicInterpolation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMixedLinearCubicInterpolation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            return XArray_;
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            return YArray_;
        else if(strcmp(nameUpper.c_str(), "SWITCHINDEX")==0)
            return SwitchIndex_;
        else if(strcmp(nameUpper.c_str(), "DERAPPROX")==0)
            return DerApprox_;
        else if(strcmp(nameUpper.c_str(), "MONOTONIC")==0)
            return Monotonic_;
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONTYPE")==0)
            return LeftConditionType_;
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONVALUE")==0)
            return LeftConditionValue_;
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONTYPE")==0)
            return RightConditionType_;
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONVALUE")==0)
            return RightConditionValue_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMixedLinearCubicInterpolation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            XArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            YArray_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWITCHINDEX")==0)
            SwitchIndex_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "DERAPPROX")==0)
            DerApprox_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MONOTONIC")==0)
            Monotonic_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONTYPE")==0)
            LeftConditionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LEFTCONDITIONVALUE")==0)
            LeftConditionValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONTYPE")==0)
            RightConditionType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RIGHTCONDITIONVALUE")==0)
            RightConditionValue_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMixedLinearCubicInterpolation::qlMixedLinearCubicInterpolation(
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
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMixedLinearCubicInterpolation", Permanent),
        XArray_(XArray),
        YArray_(YArray),
        SwitchIndex_(SwitchIndex),
        DerApprox_(DerApprox),
        Monotonic_(Monotonic),
        LeftConditionType_(LeftConditionType),
        LeftConditionValue_(LeftConditionValue),
        RightConditionType_(RightConditionType),
        RightConditionValue_(RightConditionValue),
        Permanent_(Permanent) {
                  
            processVariant(YArray);
            
    }

    const char* qlSABRInterpolation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "XArray",
        "YArray",
        "Expiry",
        "Forward",
        "Alpha",
        "Beta",
        "Nu",
        "Rho",
        "AlphaIsFixed",
        "BetaIsFixed",
        "NuIsFixed",
        "RhoIsFixed",
        "VegaWeighted",
        "EndCriteria",
        "OptimizationMeth",
        "Permanent"
    };

    std::set<std::string> qlSABRInterpolation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSABRInterpolation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSABRInterpolation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSABRInterpolation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            return XArray_;
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            return YArray_;
        else if(strcmp(nameUpper.c_str(), "EXPIRY")==0)
            return Expiry_;
        else if(strcmp(nameUpper.c_str(), "FORWARD")==0)
            return Forward_;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            return Alpha_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            return Nu_;
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            return Rho_;
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            return AlphaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            return BetaIsFixed_;
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            return NuIsFixed_;
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            return RhoIsFixed_;
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            return VegaWeighted_;
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            return EndCriteria_;
        else if(strcmp(nameUpper.c_str(), "OPTIMIZATIONMETH")==0)
            return OptimizationMeth_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSABRInterpolation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "XARRAY")==0)
            XArray_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YARRAY")==0)
            YArray_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "EXPIRY")==0)
            Expiry_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FORWARD")==0)
            Forward_ = value;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            Alpha_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NU")==0)
            Nu_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            Rho_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAISFIXED")==0)
            AlphaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "BETAISFIXED")==0)
            BetaIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "NUISFIXED")==0)
            NuIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "RHOISFIXED")==0)
            RhoIsFixed_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "VEGAWEIGHTED")==0)
            VegaWeighted_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ENDCRITERIA")==0)
            EndCriteria_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "OPTIMIZATIONMETH")==0)
            OptimizationMeth_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSABRInterpolation::qlSABRInterpolation(
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
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSABRInterpolation", Permanent),
        XArray_(XArray),
        YArray_(YArray),
        Expiry_(Expiry),
        Forward_(Forward),
        Alpha_(Alpha),
        Beta_(Beta),
        Nu_(Nu),
        Rho_(Rho),
        AlphaIsFixed_(AlphaIsFixed),
        BetaIsFixed_(BetaIsFixed),
        NuIsFixed_(NuIsFixed),
        RhoIsFixed_(RhoIsFixed),
        VegaWeighted_(VegaWeighted),
        EndCriteria_(EndCriteria),
        OptimizationMeth_(OptimizationMeth),
        Permanent_(Permanent) {
                  
            processVariant(YArray);
            processVariant(Forward);
            processPrecedentID(EndCriteria);
            processPrecedentID(OptimizationMeth);
            
    }

 } }
