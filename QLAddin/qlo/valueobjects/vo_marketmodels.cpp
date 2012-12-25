
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
#include <qlo/marketmodels.hpp>
#include <qlo/valueobjects/vo_marketmodels.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlAbcdVol::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "A",
        "B",
        "C",
        "D",
        "Ks",
        "Correlations",
        "EvolutionDescription",
        "Factors",
        "InitialRates",
        "Displacements",
        "Permanent"
    };

    std::set<std::string> qlAbcdVol::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlAbcdVol::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlAbcdVol::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlAbcdVol::getSystemProperty(const std::string& name) const {
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
        else if(strcmp(nameUpper.c_str(), "KS")==0)
            return Ks_;
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            return Correlations_;
        else if(strcmp(nameUpper.c_str(), "EVOLUTIONDESCRIPTION")==0)
            return EvolutionDescription_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "INITIALRATES")==0)
            return InitialRates_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            return Displacements_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlAbcdVol::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
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
        else if(strcmp(nameUpper.c_str(), "KS")==0)
            Ks_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            Correlations_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVOLUTIONDESCRIPTION")==0)
            EvolutionDescription_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALRATES")==0)
            InitialRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            Displacements_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlAbcdVol::qlAbcdVol(
            const std::string& ObjectId,
            double A,
            double B,
            double C,
            double D,
            const std::vector<double>& Ks,
            const std::string& Correlations,
            const std::string& EvolutionDescription,
            long Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlAbcdVol", Permanent),
        A_(A),
        B_(B),
        C_(C),
        D_(D),
        Ks_(Ks),
        Correlations_(Correlations),
        EvolutionDescription_(EvolutionDescription),
        Factors_(Factors),
        InitialRates_(InitialRates),
        Displacements_(Displacements),
        Permanent_(Permanent) {
                  
            processPrecedentID(Correlations);
            processPrecedentID(EvolutionDescription);
            
    }

    const char* qlCotSwapToFwdAdapter::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CoterminalModel",
        "Permanent"
    };

    std::set<std::string> qlCotSwapToFwdAdapter::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCotSwapToFwdAdapter::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCotSwapToFwdAdapter::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCotSwapToFwdAdapter::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "COTERMINALMODEL")==0)
            return CoterminalModel_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCotSwapToFwdAdapter::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "COTERMINALMODEL")==0)
            CoterminalModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCotSwapToFwdAdapter::qlCotSwapToFwdAdapter(
            const std::string& ObjectId,
            const std::string& CoterminalModel,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCotSwapToFwdAdapter", Permanent),
        CoterminalModel_(CoterminalModel),
        Permanent_(Permanent) {
                  
            processPrecedentID(CoterminalModel);
            
    }

    const char* qlFlatVol::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Volatilities",
        "Correlations",
        "EvolutionDescription",
        "Factors",
        "InitialRates",
        "Displacements",
        "Permanent"
    };

    std::set<std::string> qlFlatVol::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFlatVol::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFlatVol::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFlatVol::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            return Volatilities_;
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            return Correlations_;
        else if(strcmp(nameUpper.c_str(), "EVOLUTIONDESCRIPTION")==0)
            return EvolutionDescription_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "INITIALRATES")==0)
            return InitialRates_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            return Displacements_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFlatVol::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            Correlations_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVOLUTIONDESCRIPTION")==0)
            EvolutionDescription_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALRATES")==0)
            InitialRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            Displacements_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFlatVol::qlFlatVol(
            const std::string& ObjectId,
            const std::vector<double>& Volatilities,
            const std::string& Correlations,
            const std::string& EvolutionDescription,
            long Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFlatVol", Permanent),
        Volatilities_(Volatilities),
        Correlations_(Correlations),
        EvolutionDescription_(EvolutionDescription),
        Factors_(Factors),
        InitialRates_(InitialRates),
        Displacements_(Displacements),
        Permanent_(Permanent) {
                  
            processPrecedentID(Correlations);
            processPrecedentID(EvolutionDescription);
            
    }

    const char* qlFlatVolFactory::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "LongTermCorr",
        "Beta",
        "Times",
        "Volatilities",
        "YieldCurve",
        "Displacement",
        "Permanent"
    };

    std::set<std::string> qlFlatVolFactory::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFlatVolFactory::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFlatVolFactory::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFlatVolFactory::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "LONGTERMCORR")==0)
            return LongTermCorr_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "TIMES")==0)
            return Times_;
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            return Volatilities_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            return Displacement_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFlatVolFactory::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LONGTERMCORR")==0)
            LongTermCorr_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TIMES")==0)
            Times_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "VOLATILITIES")==0)
            Volatilities_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            Displacement_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFlatVolFactory::qlFlatVolFactory(
            const std::string& ObjectId,
            double LongTermCorr,
            double Beta,
            const std::vector<double>& Times,
            const std::vector<double>& Volatilities,
            const std::string& YieldCurve,
            double Displacement,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFlatVolFactory", Permanent),
        LongTermCorr_(LongTermCorr),
        Beta_(Beta),
        Times_(Times),
        Volatilities_(Volatilities),
        YieldCurve_(YieldCurve),
        Displacement_(Displacement),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlFwdPeriodAdapter::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "LargeModel",
        "Period",
        "Offset",
        "Displacements",
        "Permanent"
    };

    std::set<std::string> qlFwdPeriodAdapter::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFwdPeriodAdapter::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFwdPeriodAdapter::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFwdPeriodAdapter::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "LARGEMODEL")==0)
            return LargeModel_;
        else if(strcmp(nameUpper.c_str(), "PERIOD")==0)
            return Period_;
        else if(strcmp(nameUpper.c_str(), "OFFSET")==0)
            return Offset_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            return Displacements_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFwdPeriodAdapter::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LARGEMODEL")==0)
            LargeModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERIOD")==0)
            Period_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "OFFSET")==0)
            Offset_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            Displacements_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFwdPeriodAdapter::qlFwdPeriodAdapter(
            const std::string& ObjectId,
            const std::string& LargeModel,
            long Period,
            long Offset,
            const std::vector<double>& Displacements,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFwdPeriodAdapter", Permanent),
        LargeModel_(LargeModel),
        Period_(Period),
        Offset_(Offset),
        Displacements_(Displacements),
        Permanent_(Permanent) {
                  
            processPrecedentID(LargeModel);
            
    }

    const char* qlFwdToCotSwapAdapter::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ForwardModel",
        "Permanent"
    };

    std::set<std::string> qlFwdToCotSwapAdapter::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlFwdToCotSwapAdapter::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlFwdToCotSwapAdapter::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlFwdToCotSwapAdapter::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FORWARDMODEL")==0)
            return ForwardModel_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlFwdToCotSwapAdapter::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FORWARDMODEL")==0)
            ForwardModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlFwdToCotSwapAdapter::qlFwdToCotSwapAdapter(
            const std::string& ObjectId,
            const std::string& ForwardModel,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlFwdToCotSwapAdapter", Permanent),
        ForwardModel_(ForwardModel),
        Permanent_(Permanent) {
                  
            processPrecedentID(ForwardModel);
            
    }

    const char* qlPseudoRootFacade::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Calibrator",
        "Permanent"
    };

    std::set<std::string> qlPseudoRootFacade::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPseudoRootFacade::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPseudoRootFacade::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPseudoRootFacade::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CALIBRATOR")==0)
            return Calibrator_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPseudoRootFacade::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALIBRATOR")==0)
            Calibrator_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPseudoRootFacade::qlPseudoRootFacade(
            const std::string& ObjectId,
            const std::string& Calibrator,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPseudoRootFacade", Permanent),
        Calibrator_(Calibrator),
        Permanent_(Permanent) {
                  
            processPrecedentID(Calibrator);
            
    }

 } }
