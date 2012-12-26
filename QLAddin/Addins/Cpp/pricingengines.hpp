
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 
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

#ifndef qlcpp_pricingengines_hpp
#define qlcpp_pricingengines_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlAnalyticCapFloorEngine(
            const std::string &ObjectId,
            const std::string &HandleModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBinomialPricingEngine(
            const std::string &ObjectId,
            const std::string &EngineID,
            const std::string &ProcessID,
            const long &TimeSteps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackCalculator(
            const std::string &ObjectId,
            const std::string &OptionType,
            const double &Strike,
            const double &AtmForwardValue,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackCalculator2(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const double &AtmForwardValue,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackCapFloorEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const std::string &VolTS,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackCapFloorEngine2(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Vol,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackScholesCalculator(
            const std::string &ObjectId,
            const std::string &OptionType,
            const double &Strike,
            const double &Spot,
            const ObjectHandler::property_t &Growth,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackScholesCalculator2(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const double &Spot,
            const ObjectHandler::property_t &Growth,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackSwaptionEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const std::string &VolTS,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBlackSwaptionEngine2(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Vol,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBondEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlDiscountingSwapEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &IncludeSettlDate,
            const ObjectHandler::property_t &SettlementDate,
            const ObjectHandler::property_t &NpvDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlPricingEngine(
            const std::string &ObjectId,
            const std::string &EngineID,
            const std::string &ProcessID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

