
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2007 Katiuscia Manzoni
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 
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
//      gensrc/gensrc/stubs/stub.cpp.header

#ifndef qlcpp_correlation_hpp
#define qlcpp_correlation_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlCotSwapFromFwdCorrelation(
            const std::string &ObjectId,
            const std::string &FwdCorr,
            const std::string &CurveState,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlExponentialForwardCorrelation(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const double &LongTermCorr,
            const double &Beta,
            const double &Gamma,
            const std::vector<double>& Times,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlHistoricalForwardRatesAnalysis(
            const std::string &ObjectId,
            const std::string &SequenceStats,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const std::string &Step,
            const std::string &IborIndex,
            const std::string &InitialGap,
            const std::string &Horizon,
            const std::vector<std::string>& IborIndexes,
            const std::vector<std::string>& SwapIndexes,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &TraitsID,
            const ObjectHandler::property_t &InterpolatorID,
            const ObjectHandler::property_t &BootstrapAccuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlHistoricalRatesAnalysis(
            const std::string &ObjectId,
            const std::string &SequenceStats,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const std::string &Step,
            const std::vector<std::string>& InterestRateIndexes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMarketModelLmLinearExponentialCorrelationModel(
            const std::string &ObjectId,
            const long &Size,
            const double &Rho,
            const double &Beta,
            const ObjectHandler::property_t &Factors,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

