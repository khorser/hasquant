
/*  
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Francois du Vignaud
 Copyright (C) 2006 Giorgio Facchinetti
 
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

#ifndef qlcpp_quotes_hpp
#define qlcpp_quotes_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlCompositeQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Element1,
            const ObjectHandler::property_t &Element2,
            const std::string &Operator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEurodollarFuturesImpliedStdDevQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &AtmForwardValue,
            const ObjectHandler::property_t &CallPrice,
            const ObjectHandler::property_t &PutPrice,
            const double &Strike,
            const ObjectHandler::property_t &Guess,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlForwardSwapQuote(
            const std::string &ObjectId,
            const std::string &SwapIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlForwardValueQuote(
            const std::string &ObjectId,
            const std::string &IborIndex,
            const ObjectHandler::property_t &FixingDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlFuturesConvAdjustmentQuote(
            const std::string &ObjectId,
            const std::string &IborIndex,
            const std::string &ImmCode,
            const ObjectHandler::property_t &FuturesQuote,
            const ObjectHandler::property_t &Volatility,
            const ObjectHandler::property_t &MeanReversion,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlImpliedStdDevQuote(
            const std::string &ObjectId,
            const std::string &OptionType,
            const ObjectHandler::property_t &AtmForwardValue,
            const ObjectHandler::property_t &OptionPrice,
            const double &Strike,
            const ObjectHandler::property_t &Guess,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlLastFixingQuote(
            const std::string &ObjectId,
            const std::string &Index,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRelinkableHandleQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSimpleQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Value,
            const double &TickValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    double qlSimpleQuoteSetValue(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Value,
            const ObjectHandler::property_t &Trigger);

}

#endif

