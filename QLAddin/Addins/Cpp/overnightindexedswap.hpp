
/*  
 Copyright (C) 2009, 2011 Ferdinando Ametrano
 
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

#ifndef qlcpp_overnightindexedswap_hpp
#define qlcpp_overnightindexedswap_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlMakeDatedOIS(
            const std::string &ObjectId,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const std::string &OvernightIndex,
            const ObjectHandler::property_t &FixedRate,
            const ObjectHandler::property_t &FixDayCounter,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMakeOIS(
            const std::string &ObjectId,
            const std::string &SwapTenor,
            const std::string &OvernightIndex,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &FixDayCounter,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlOvernightIndexedSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PayerReceiver,
            const std::vector<double>& Nominal,
            const std::string &Schedule,
            const ObjectHandler::property_t &FixedRate,
            const std::string &FixDayCounter,
            const std::string &OvernightIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlOvernightIndexedSwapFromOISRateHelper(
            const std::string &ObjectId,
            const std::string &OISRateHelper,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

