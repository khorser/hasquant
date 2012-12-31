
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2007 Marco Bianchetti
 Copyright (C) 2006 Eric Ehlers
 
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

#ifndef qlcpp_payoffs_hpp
#define qlcpp_payoffs_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlDoubleStickyRatchetPayoff(
            const std::string &ObjectId,
            const double &Type1,
            const double &Type2,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRatchetMaxPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRatchetMinPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRatchetPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Spread1,
            const double &Spread2,
            const double &InitialValue,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlStickyMaxPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlStickyMinPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlStickyPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Spread1,
            const double &Spread2,
            const double &InitialValue,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlStrikedTypePayoff(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const std::string &OptionType,
            const double &Strike,
            const ObjectHandler::property_t &ThirdParameter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

