
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
#include <qlo/ctsmmcapletcalibration.hpp>
#include <qlo/valueobjects/vo_ctsmmcapletcalibration.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCTSMMCapletAlphaFormCalibration::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Evolution",
        "Correlations",
        "SwapPiecewiseConstantVariances",
        "CapletVols",
        "CurveState",
        "Displacement",
        "AlphaInitial",
        "AlphaMax",
        "AlphaMin",
        "MaximizeHomogeneity",
        "AlphaForm",
        "Permanent"
    };

    std::set<std::string> qlCTSMMCapletAlphaFormCalibration::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCTSMMCapletAlphaFormCalibration::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCTSMMCapletAlphaFormCalibration::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCTSMMCapletAlphaFormCalibration::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EVOLUTION")==0)
            return Evolution_;
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            return Correlations_;
        else if(strcmp(nameUpper.c_str(), "SWAPPIECEWISECONSTANTVARIANCES")==0)
            return SwapPiecewiseConstantVariances_;
        else if(strcmp(nameUpper.c_str(), "CAPLETVOLS")==0)
            return CapletVols_;
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            return CurveState_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            return Displacement_;
        else if(strcmp(nameUpper.c_str(), "ALPHAINITIAL")==0)
            return AlphaInitial_;
        else if(strcmp(nameUpper.c_str(), "ALPHAMAX")==0)
            return AlphaMax_;
        else if(strcmp(nameUpper.c_str(), "ALPHAMIN")==0)
            return AlphaMin_;
        else if(strcmp(nameUpper.c_str(), "MAXIMIZEHOMOGENEITY")==0)
            return MaximizeHomogeneity_;
        else if(strcmp(nameUpper.c_str(), "ALPHAFORM")==0)
            return AlphaForm_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCTSMMCapletAlphaFormCalibration::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVOLUTION")==0)
            Evolution_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            Correlations_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPPIECEWISECONSTANTVARIANCES")==0)
            SwapPiecewiseConstantVariances_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CAPLETVOLS")==0)
            CapletVols_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            CurveState_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            Displacement_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAINITIAL")==0)
            AlphaInitial_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ALPHAMAX")==0)
            AlphaMax_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ALPHAMIN")==0)
            AlphaMin_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "MAXIMIZEHOMOGENEITY")==0)
            MaximizeHomogeneity_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAFORM")==0)
            AlphaForm_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCTSMMCapletAlphaFormCalibration::qlCTSMMCapletAlphaFormCalibration(
            const std::string& ObjectId,
            const std::string& Evolution,
            const std::string& Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string& CurveState,
            double Displacement,
            const std::vector<double>& AlphaInitial,
            const std::vector<double>& AlphaMax,
            const std::vector<double>& AlphaMin,
            bool MaximizeHomogeneity,
            const std::string& AlphaForm,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCTSMMCapletAlphaFormCalibration", Permanent),
        Evolution_(Evolution),
        Correlations_(Correlations),
        SwapPiecewiseConstantVariances_(SwapPiecewiseConstantVariances),
        CapletVols_(CapletVols),
        CurveState_(CurveState),
        Displacement_(Displacement),
        AlphaInitial_(AlphaInitial),
        AlphaMax_(AlphaMax),
        AlphaMin_(AlphaMin),
        MaximizeHomogeneity_(MaximizeHomogeneity),
        AlphaForm_(AlphaForm),
        Permanent_(Permanent) {
                  
            processPrecedentID(Evolution);
            processPrecedentID(Correlations);
            for (std::vector<std::string>::const_iterator i = SwapPiecewiseConstantVariances.begin();
                    i != SwapPiecewiseConstantVariances.end(); ++i)
                processPrecedentID(*i);
            processPrecedentID(CurveState);
            processPrecedentID(AlphaForm);
            
    }

    const char* qlCTSMMCapletMaxHomogeneityCalibration::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Evolution",
        "Correlations",
        "SwapPiecewiseConstantVariances",
        "CapletVols",
        "CurveState",
        "Displacement",
        "Caplet0Swaption1Priority",
        "Permanent"
    };

    std::set<std::string> qlCTSMMCapletMaxHomogeneityCalibration::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCTSMMCapletMaxHomogeneityCalibration::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCTSMMCapletMaxHomogeneityCalibration::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCTSMMCapletMaxHomogeneityCalibration::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EVOLUTION")==0)
            return Evolution_;
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            return Correlations_;
        else if(strcmp(nameUpper.c_str(), "SWAPPIECEWISECONSTANTVARIANCES")==0)
            return SwapPiecewiseConstantVariances_;
        else if(strcmp(nameUpper.c_str(), "CAPLETVOLS")==0)
            return CapletVols_;
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            return CurveState_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            return Displacement_;
        else if(strcmp(nameUpper.c_str(), "CAPLET0SWAPTION1PRIORITY")==0)
            return Caplet0Swaption1Priority_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCTSMMCapletMaxHomogeneityCalibration::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVOLUTION")==0)
            Evolution_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            Correlations_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPPIECEWISECONSTANTVARIANCES")==0)
            SwapPiecewiseConstantVariances_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CAPLETVOLS")==0)
            CapletVols_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            CurveState_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            Displacement_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "CAPLET0SWAPTION1PRIORITY")==0)
            Caplet0Swaption1Priority_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCTSMMCapletMaxHomogeneityCalibration::qlCTSMMCapletMaxHomogeneityCalibration(
            const std::string& ObjectId,
            const std::string& Evolution,
            const std::string& Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string& CurveState,
            double Displacement,
            double Caplet0Swaption1Priority,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCTSMMCapletMaxHomogeneityCalibration", Permanent),
        Evolution_(Evolution),
        Correlations_(Correlations),
        SwapPiecewiseConstantVariances_(SwapPiecewiseConstantVariances),
        CapletVols_(CapletVols),
        CurveState_(CurveState),
        Displacement_(Displacement),
        Caplet0Swaption1Priority_(Caplet0Swaption1Priority),
        Permanent_(Permanent) {
                  
            processPrecedentID(Evolution);
            processPrecedentID(Correlations);
            for (std::vector<std::string>::const_iterator i = SwapPiecewiseConstantVariances.begin();
                    i != SwapPiecewiseConstantVariances.end(); ++i)
                processPrecedentID(*i);
            processPrecedentID(CurveState);
            
    }

    const char* qlCTSMMCapletOriginalCalibration::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Evolution",
        "Correlations",
        "SwapPiecewiseConstantVariances",
        "CapletVols",
        "CurveState",
        "Displacement",
        "Alphas",
        "LowestRoot",
        "UseFullApprox",
        "Permanent"
    };

    std::set<std::string> qlCTSMMCapletOriginalCalibration::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCTSMMCapletOriginalCalibration::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCTSMMCapletOriginalCalibration::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCTSMMCapletOriginalCalibration::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EVOLUTION")==0)
            return Evolution_;
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            return Correlations_;
        else if(strcmp(nameUpper.c_str(), "SWAPPIECEWISECONSTANTVARIANCES")==0)
            return SwapPiecewiseConstantVariances_;
        else if(strcmp(nameUpper.c_str(), "CAPLETVOLS")==0)
            return CapletVols_;
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            return CurveState_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            return Displacement_;
        else if(strcmp(nameUpper.c_str(), "ALPHAS")==0)
            return Alphas_;
        else if(strcmp(nameUpper.c_str(), "LOWESTROOT")==0)
            return LowestRoot_;
        else if(strcmp(nameUpper.c_str(), "USEFULLAPPROX")==0)
            return UseFullApprox_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCTSMMCapletOriginalCalibration::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVOLUTION")==0)
            Evolution_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            Correlations_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SWAPPIECEWISECONSTANTVARIANCES")==0)
            SwapPiecewiseConstantVariances_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CAPLETVOLS")==0)
            CapletVols_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            CurveState_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            Displacement_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHAS")==0)
            Alphas_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "LOWESTROOT")==0)
            LowestRoot_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "USEFULLAPPROX")==0)
            UseFullApprox_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCTSMMCapletOriginalCalibration::qlCTSMMCapletOriginalCalibration(
            const std::string& ObjectId,
            const std::string& Evolution,
            const std::string& Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string& CurveState,
            double Displacement,
            const std::vector<double>& Alphas,
            bool LowestRoot,
            bool UseFullApprox,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCTSMMCapletOriginalCalibration", Permanent),
        Evolution_(Evolution),
        Correlations_(Correlations),
        SwapPiecewiseConstantVariances_(SwapPiecewiseConstantVariances),
        CapletVols_(CapletVols),
        CurveState_(CurveState),
        Displacement_(Displacement),
        Alphas_(Alphas),
        LowestRoot_(LowestRoot),
        UseFullApprox_(UseFullApprox),
        Permanent_(Permanent) {
                  
            processPrecedentID(Evolution);
            processPrecedentID(Correlations);
            for (std::vector<std::string>::const_iterator i = SwapPiecewiseConstantVariances.begin();
                    i != SwapPiecewiseConstantVariances.end(); ++i)
                processPrecedentID(*i);
            processPrecedentID(CurveState);
            
    }

 } }
