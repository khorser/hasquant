
/*  
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2006, 2007, 2009 Ferdinando Ametrano
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

#ifndef qlcpp_termstructures_hpp
#define qlcpp_termstructures_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlDiscountCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveDiscounts,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFlatForward(
            const std::string &ObjectId,
            const ObjectHandler::property_t &NDays,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &Rate,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Compounding,
            const ObjectHandler::property_t &Frequency,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlForwardCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& ForwardYields,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlForwardSpreadedTermStructure(
            const std::string &ObjectId,
            const std::string &BaseYieldCurve,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlImpliedTermStructure(
            const std::string &ObjectId,
            const std::string &BaseYieldCurve,
            const ObjectHandler::property_t &ReferenceDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlInterpolatedYieldCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& Dates,
            const std::vector<double>& Data,
            const std::string &Calendar,
            const ObjectHandler::property_t &DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
            const ObjectHandler::property_t &TraitsID,
            const ObjectHandler::property_t &InterpolatorID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRelinkableHandleYieldTermStructure(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    long qlTermStructureMaxDate(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    long qlTermStructureReferenceDate(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    long qlTermStructureSettlementDays(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    std::string qlZeroCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveYields,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

