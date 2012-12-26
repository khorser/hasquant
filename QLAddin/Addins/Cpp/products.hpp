
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
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

#ifndef qlcpp_products_hpp
#define qlcpp_products_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlMarketModelMultiProductComposite(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMarketModelMultiStepRatchet(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const double &GearingOfFloor,
            const double &GearingOfFixing,
            const double &SpreadOfFloor,
            const double &SpreadOfFixing,
            const double &InitialFloor,
            const bool &Payer,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMarketModelOneStepForwards(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<double>& Strikes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMarketModelOneStepOptionlets(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<std::string>& Payoffs,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

