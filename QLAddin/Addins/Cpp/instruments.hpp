
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2005 Walter Penschke
 
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

#ifndef qlcpp_instruments_hpp
#define qlcpp_instruments_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    double qlInstrumentNPV(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);


    bool qlInstrumentSetPricingEngine(
            const std::string &ObjectId,
            const std::string &PricingEngine,
            const ObjectHandler::property_t &Trigger);


    long qlInstrumentValuationDate(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);

}

#endif

