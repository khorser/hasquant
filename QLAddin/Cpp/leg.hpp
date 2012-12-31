
/*  
 Copyright (C) 2006, 2007, 2009, 2010, 2011 Ferdinando Ametrano
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

#ifndef qlcpp_leg_hpp
#define qlcpp_leg_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlInterestRate(
            const std::string &ObjectId,
            const double &Rate,
            const std::string &DayCounter,
            const std::string &Compounding,
            const ObjectHandler::property_t &Frequency,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlLeg(
            const std::string &ObjectId,
            const std::vector<double>& Amounts,
            const std::vector<ObjectHandler::property_t>& Dates,
            const ObjectHandler::property_t &ToBeSorted,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlLegFromCapFloor(
            const std::string &ObjectId,
            const std::string &CapFloor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlLegFromSwap(
            const std::string &ObjectId,
            const std::string &Swap,
            const long &LegNumber,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    bool qlLegSetCouponPricers(
            const std::string &ObjectId,
            const std::vector<std::string>& FloatingRateCouponPricer,
            const ObjectHandler::property_t &Trigger);


    std::string qlMultiPhaseLeg(
            const std::string &ObjectId,
            const std::vector<std::string>& LegIDs,
            const ObjectHandler::property_t &ToBeSorted,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

