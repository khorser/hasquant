
/*  
 Copyright (C) 2006, 2007, 2009 Ferdinando Ametrano
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
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

#ifndef qlcpp_couponvectors_hpp
#define qlcpp_couponvectors_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlCmsCouponPricer(
            const std::string &ObjectId,
            const std::string &Volatility,
            const std::string &CmsCouponPricerType,
            const std::string &YieldCurveModel,
            const ObjectHandler::property_t &MeanReversion,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlCmsLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlCmsZeroLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlConundrumPricerByNumericalIntegration(
            const std::string &ObjectId,
            const std::string &SwaptionVol,
            const std::string &YieldCurveModel,
            const ObjectHandler::property_t &MeanReversion,
            const ObjectHandler::property_t &LowerLimit,
            const ObjectHandler::property_t &UpperLimit,
            const ObjectHandler::property_t &Precision,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlDigitalCmsLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string &CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string &PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string &Replication,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlDigitalIborLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string &CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string &PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string &Replication,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFixedRateLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFixedRateLeg2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<std::string>& Coupons,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlIborCouponPricer(
            const std::string &ObjectId,
            const std::string &Volatility,
            const std::string &IborCouponPricerType,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlIborLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRangeAccrualLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const std::string &DayCounter,
            const std::vector<double>& LowerStrikes,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& UpperStrikes,
            const std::string &ObservationsTenor,
            const ObjectHandler::property_t &ObservationsBDC,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

