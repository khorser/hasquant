
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
#include <qlo/correlation.hpp>
#include <qlo/valueobjects/vo_correlation.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCotSwapFromFwdCorrelation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FwdCorr",
        "CurveState",
        "Displacement",
        "Permanent"
    };

    std::set<std::string> qlCotSwapFromFwdCorrelation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCotSwapFromFwdCorrelation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCotSwapFromFwdCorrelation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCotSwapFromFwdCorrelation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FWDCORR")==0)
            return FwdCorr_;
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            return CurveState_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            return Displacement_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCotSwapFromFwdCorrelation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCORR")==0)
            FwdCorr_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURVESTATE")==0)
            CurveState_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENT")==0)
            Displacement_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCotSwapFromFwdCorrelation::qlCotSwapFromFwdCorrelation(
            const std::string& ObjectId,
            const std::string& FwdCorr,
            const std::string& CurveState,
            double Displacement,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCotSwapFromFwdCorrelation", Permanent),
        FwdCorr_(FwdCorr),
        CurveState_(CurveState),
        Displacement_(Displacement),
        Permanent_(Permanent) {
                  
            processPrecedentID(FwdCorr);
            processPrecedentID(CurveState);
            
    }

    const char* qlExponentialForwardCorrelation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RateTimes",
        "LongTermCorr",
        "Beta",
        "Gamma",
        "Times",
        "Permanent"
    };

    std::set<std::string> qlExponentialForwardCorrelation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlExponentialForwardCorrelation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlExponentialForwardCorrelation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlExponentialForwardCorrelation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            return RateTimes_;
        else if(strcmp(nameUpper.c_str(), "LONGTERMCORR")==0)
            return LongTermCorr_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "GAMMA")==0)
            return Gamma_;
        else if(strcmp(nameUpper.c_str(), "TIMES")==0)
            return Times_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlExponentialForwardCorrelation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            RateTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "LONGTERMCORR")==0)
            LongTermCorr_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GAMMA")==0)
            Gamma_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TIMES")==0)
            Times_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlExponentialForwardCorrelation::qlExponentialForwardCorrelation(
            const std::string& ObjectId,
            const std::vector<double>& RateTimes,
            double LongTermCorr,
            double Beta,
            double Gamma,
            const std::vector<double>& Times,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlExponentialForwardCorrelation", Permanent),
        RateTimes_(RateTimes),
        LongTermCorr_(LongTermCorr),
        Beta_(Beta),
        Gamma_(Gamma),
        Times_(Times),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlHistoricalForwardRatesAnalysis::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SequenceStats",
        "StartDate",
        "EndDate",
        "Step",
        "IborIndex",
        "InitialGap",
        "Horizon",
        "IborIndexes",
        "SwapIndexes",
        "DayCounter",
        "TraitsID",
        "InterpolatorID",
        "BootstrapAccuracy",
        "Permanent"
    };

    std::set<std::string> qlHistoricalForwardRatesAnalysis::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlHistoricalForwardRatesAnalysis::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlHistoricalForwardRatesAnalysis::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlHistoricalForwardRatesAnalysis::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SEQUENCESTATS")==0)
            return SequenceStats_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            return EndDate_;
        else if(strcmp(nameUpper.c_str(), "STEP")==0)
            return Step_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            return IborIndex_;
        else if(strcmp(nameUpper.c_str(), "INITIALGAP")==0)
            return InitialGap_;
        else if(strcmp(nameUpper.c_str(), "HORIZON")==0)
            return Horizon_;
        else if(strcmp(nameUpper.c_str(), "IBORINDEXES")==0)
            return IborIndexes_;
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXES")==0)
            return SwapIndexes_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "TRAITSID")==0)
            return TraitsID_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORID")==0)
            return InterpolatorID_;
        else if(strcmp(nameUpper.c_str(), "BOOTSTRAPACCURACY")==0)
            return BootstrapAccuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlHistoricalForwardRatesAnalysis::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SEQUENCESTATS")==0)
            SequenceStats_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            EndDate_ = value;
        else if(strcmp(nameUpper.c_str(), "STEP")==0)
            Step_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEX")==0)
            IborIndex_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INITIALGAP")==0)
            InitialGap_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "HORIZON")==0)
            Horizon_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "IBORINDEXES")==0)
            IborIndexes_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "SWAPINDEXES")==0)
            SwapIndexes_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TRAITSID")==0)
            TraitsID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORID")==0)
            InterpolatorID_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BOOTSTRAPACCURACY")==0)
            BootstrapAccuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlHistoricalForwardRatesAnalysis::qlHistoricalForwardRatesAnalysis(
            const std::string& ObjectId,
            const std::string& SequenceStats,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const std::string& Step,
            const std::string& IborIndex,
            const std::string& InitialGap,
            const std::string& Horizon,
            const std::vector<std::string>& IborIndexes,
            const std::vector<std::string>& SwapIndexes,
            const std::string& DayCounter,
            const std::string& TraitsID,
            const std::string& InterpolatorID,
            double BootstrapAccuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlHistoricalForwardRatesAnalysis", Permanent),
        SequenceStats_(SequenceStats),
        StartDate_(StartDate),
        EndDate_(EndDate),
        Step_(Step),
        IborIndex_(IborIndex),
        InitialGap_(InitialGap),
        Horizon_(Horizon),
        IborIndexes_(IborIndexes),
        SwapIndexes_(SwapIndexes),
        DayCounter_(DayCounter),
        TraitsID_(TraitsID),
        InterpolatorID_(InterpolatorID),
        BootstrapAccuracy_(BootstrapAccuracy),
        Permanent_(Permanent) {
                  
            processPrecedentID(SequenceStats);
            processPrecedentID(IborIndex);
            for (std::vector<std::string>::const_iterator i = IborIndexes.begin();
                    i != IborIndexes.end(); ++i)
                processPrecedentID(*i);
            for (std::vector<std::string>::const_iterator i = SwapIndexes.begin();
                    i != SwapIndexes.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlHistoricalRatesAnalysis::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "SequenceStats",
        "StartDate",
        "EndDate",
        "Step",
        "InterestRateIndexes",
        "Permanent"
    };

    std::set<std::string> qlHistoricalRatesAnalysis::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlHistoricalRatesAnalysis::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlHistoricalRatesAnalysis::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlHistoricalRatesAnalysis::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SEQUENCESTATS")==0)
            return SequenceStats_;
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            return StartDate_;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            return EndDate_;
        else if(strcmp(nameUpper.c_str(), "STEP")==0)
            return Step_;
        else if(strcmp(nameUpper.c_str(), "INTERESTRATEINDEXES")==0)
            return InterestRateIndexes_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlHistoricalRatesAnalysis::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SEQUENCESTATS")==0)
            SequenceStats_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "STARTDATE")==0)
            StartDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ENDDATE")==0)
            EndDate_ = value;
        else if(strcmp(nameUpper.c_str(), "STEP")==0)
            Step_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERESTRATEINDEXES")==0)
            InterestRateIndexes_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlHistoricalRatesAnalysis::qlHistoricalRatesAnalysis(
            const std::string& ObjectId,
            const std::string& SequenceStats,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const std::string& Step,
            const std::vector<std::string>& InterestRateIndexes,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlHistoricalRatesAnalysis", Permanent),
        SequenceStats_(SequenceStats),
        StartDate_(StartDate),
        EndDate_(EndDate),
        Step_(Step),
        InterestRateIndexes_(InterestRateIndexes),
        Permanent_(Permanent) {
                  
            processPrecedentID(SequenceStats);
            for (std::vector<std::string>::const_iterator i = InterestRateIndexes.begin();
                    i != InterestRateIndexes.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlMarketModelLmLinearExponentialCorrelationModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Size",
        "Rho",
        "Beta",
        "Factors",
        "Permanent"
    };

    std::set<std::string> qlMarketModelLmLinearExponentialCorrelationModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMarketModelLmLinearExponentialCorrelationModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMarketModelLmLinearExponentialCorrelationModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMarketModelLmLinearExponentialCorrelationModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "SIZE")==0)
            return Size_;
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            return Rho_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMarketModelLmLinearExponentialCorrelationModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SIZE")==0)
            Size_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "RHO")==0)
            Rho_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMarketModelLmLinearExponentialCorrelationModel::qlMarketModelLmLinearExponentialCorrelationModel(
            const std::string& ObjectId,
            long Size,
            double Rho,
            double Beta,
            long Factors,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMarketModelLmLinearExponentialCorrelationModel", Permanent),
        Size_(Size),
        Rho_(Rho),
        Beta_(Beta),
        Factors_(Factors),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlTimeHomogeneousForwardCorrelation::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "FwdCorrMatrix",
        "RateTimes",
        "Permanent"
    };

    std::set<std::string> qlTimeHomogeneousForwardCorrelation::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlTimeHomogeneousForwardCorrelation::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlTimeHomogeneousForwardCorrelation::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlTimeHomogeneousForwardCorrelation::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FWDCORRMATRIX")==0)
            return FwdCorrMatrix_;
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            return RateTimes_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlTimeHomogeneousForwardCorrelation::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FWDCORRMATRIX")==0)
            FwdCorrMatrix_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RATETIMES")==0)
            RateTimes_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlTimeHomogeneousForwardCorrelation::qlTimeHomogeneousForwardCorrelation(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& FwdCorrMatrix,
            const std::vector<double>& RateTimes,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlTimeHomogeneousForwardCorrelation", Permanent),
        FwdCorrMatrix_(FwdCorrMatrix),
        RateTimes_(RateTimes),
        Permanent_(Permanent) {
                  

            
    }

 } }
