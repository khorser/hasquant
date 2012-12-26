
/*  
 Copyright (C) 2009, 2011 Ferdinando Ametrano
 Copyright (C) 2006, 2007, Chiara Fornarola
 
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

#ifndef qlcpp_assetswap_hpp
#define qlcpp_assetswap_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlAssetSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PayBondCoupon,
            const std::string &Bond,
            const double &CleanPrice,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &FloatingLegSchedule,
            const std::string &FloatingLegDayCounter,
            const ObjectHandler::property_t &ParAssetSwap,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlAssetSwap2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ParAssetSwap,
            const std::string &Bond,
            const double &CleanPrice,
            const double &NonParRepayment,
            const ObjectHandler::property_t &Gearing,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &FloatingLegDayCounter,
            const ObjectHandler::property_t &DealMaturity,
            const ObjectHandler::property_t &PayBondCoupon,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

