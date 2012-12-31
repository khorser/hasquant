
/*  
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2006, 2007, 2008, 2009 Ferdinando Ametrano
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet
 
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

#ifndef qlcpp_ratehelpers_hpp
#define qlcpp_ratehelpers_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlBondHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CleanPrice,
            const std::string &Bond,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlDatedOISRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ONIndex,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlDepositRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlDepositRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Calendar,
            const std::string &Convention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFixedRateBondHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CleanPrice,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFraRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &PeriodToStart,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFraRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &PeriodToStart,
            const long &LengthInMonths,
            const long &FixingDays,
            const std::string &Calendar,
            const std::string &Convention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFuturesRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const ObjectHandler::property_t &IMM,
            const ObjectHandler::property_t &IborIndex,
            const ObjectHandler::property_t &ConvexityAdjQuote,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFuturesRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const ObjectHandler::property_t &IMM,
            const ObjectHandler::property_t &LengthInMonths,
            const std::string &Calendar,
            const ObjectHandler::property_t &Convention,
            const ObjectHandler::property_t &EndOfMonth,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &ConvexityAdjQuote,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFuturesRateHelper3(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Price,
            const ObjectHandler::property_t &IMM,
            const ObjectHandler::property_t &EndDate,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &ConvexityAdjQuote,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlOISRateHelper(
            const std::string &ObjectId,
            const long &SettlDays,
            const std::string &Tenor,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ONIndex,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    double qlRateHelperImpliedQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    double qlRateHelperQuoteError(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    double qlRateHelperQuoteIsValid(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    double qlRateHelperQuoteValue(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    std::string qlSwapRateHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &SwapIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSwapRateHelper2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Rate,
            const std::string &Tenor,
            const std::string &Calendar,
            const std::string &FixedLegFrequency,
            const std::string &FixedLegConvention,
            const std::string &FixedLegDayCounter,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &DiscountingCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

