
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 
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

#ifndef qlcpp_capletvolstructure_hpp
#define qlcpp_capletvolstructure_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlCapFloorTermVolCurve(
            const std::string &ObjectId,
            const long &SettlementDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& Volatilities,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlCapFloorTermVolSurface(
            const std::string &ObjectId,
            const long &SettlementDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<double>& Strikes,
            const std::vector<std::vector <ObjectHandler::property_t> >& Volatilities,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlConstantOptionletVolatility(
            const std::string &ObjectId,
            const ObjectHandler::property_t &NDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const ObjectHandler::property_t &Volatility,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRelinkableHandleOptionletVolatilityStructure(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSpreadedOptionletVolatility(
            const std::string &ObjectId,
            const std::string &BaseVolStructure,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlStrippedOptionlet(
            const std::string &ObjectId,
            const ObjectHandler::property_t &SettlementDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::string &IborIndex,
            const std::vector<ObjectHandler::property_t>& OptionletDates,
            const std::vector<double>& Strikes,
            const std::vector<std::vector <ObjectHandler::property_t> >& Volatilities,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlStrippedOptionletAdapter(
            const std::string &ObjectId,
            const std::string &StrippedOptionletBase,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    long qlStrippedOptionletBaseSettlementDays(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger);

}

#endif

