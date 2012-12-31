
/*  
 Copyright (C) 2007 Cristina Duminuco
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Francois du Vignaud
 
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

#ifndef qlcpp_smilesection_hpp
#define qlcpp_smilesection_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlFlatSmileSection(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const double &Volatility,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &RefDate,
            const double &AtmValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlInterpolatedSmileSection(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t &AtmLevel,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSabrInterpolatedSmileSection(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const double &ForwardRate,
            const std::vector<double>& Strike,
            const bool &FloatingStrike,
            const double &AtmVolatility,
            const std::vector<double>& VolatilitySpreads,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSabrInterpolatedSmileSection1(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const ObjectHandler::property_t &ForwardRate,
            const std::vector<double>& Strike,
            const bool &FloatingStrike,
            const ObjectHandler::property_t &AtmVolatility,
            const std::vector<ObjectHandler::property_t>& VolatilitySpreads,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSabrSmileSection(
            const std::string &ObjectId,
            const double &OptionTime,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t &Forward,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

