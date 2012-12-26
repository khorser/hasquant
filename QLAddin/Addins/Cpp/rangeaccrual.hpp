
/*  
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

#ifndef qlcpp_rangeaccrual_hpp
#define qlcpp_rangeaccrual_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlRangeAccrualFloatersCoupon(
            const std::string &ObjectId,
            const double &Nominal,
            const ObjectHandler::property_t &PaymentDate,
            const std::string &IborIndex,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const long &FixingDays,
            const std::string &DayCountID,
            const double &Gearings,
            const double &Spreads,
            const ObjectHandler::property_t &RefPeriodStart,
            const ObjectHandler::property_t &RefPeriodEnd,
            const std::string &ObserSchedID,
            const double &LowerTrigger,
            const double &UpperTrigger,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRangeAccrualFloatersCouponFromLeg(
            const std::string &ObjectId,
            const std::string &RangeAccrualLeg,
            const long &Position,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRangeAccrualPricerByBgm(
            const std::string &ObjectId,
            const double &Correlation,
            const std::string &SmileOnStartDateID,
            const std::string &SmileOnEndDateID,
            const bool &WithSmile,
            const bool &ByCallSpread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

