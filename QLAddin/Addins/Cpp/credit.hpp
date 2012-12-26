
/*  
 Copyright (C) 2010 Roland Lichters
 
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

#ifndef qlcpp_credit_hpp
#define qlcpp_credit_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlHazardRateCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveRates,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMidPointCdsEngine(
            const std::string &ObjectId,
            const std::string &DefaultCurve,
            const double &RecoveryRate,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlPiecewiseFlatForwardCurve(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ReferenceDate,
            const std::vector<std::string>& RateHelpers,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlPiecewiseFlatHazardRateCurve(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ReferenceDate,
            const std::vector<std::string>& Helpers,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSpreadCdsHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &RunningSpread,
            const std::string &Tenor,
            const ObjectHandler::property_t &SettlementDays,
            const std::string &Calendar,
            const std::string &Frequency,
            const std::string &PaymentConvention,
            const std::string &GenRule,
            const std::string &DayCounter,
            const double &RecoveryRate,
            const std::string &DiscountingCurve,
            const ObjectHandler::property_t &SettleAccrual,
            const ObjectHandler::property_t &PayAtDefault,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

