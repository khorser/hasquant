
/*  
 Copyright (C) 2010, 2011 Ferdinando Ametrano
 
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

#ifndef qlcpp_btp_hpp
#define qlcpp_btp_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlBTP(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &MaturityDate,
            const double &Coupon,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlBTP2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &MaturityDate,
            const double &Coupon,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlCCTEU(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &MaturityDate,
            const double &Spread,
            const std::string &FwdCurve,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRendistatoBasket(
            const std::string &ObjectId,
            const std::vector<std::string>& BTPs,
            const std::vector<double>& Outstandings,
            const std::vector<ObjectHandler::property_t>& Prices,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRendistatoCalculator(
            const std::string &ObjectId,
            const std::string &RendistatoBasket,
            const std::string &Euribor,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRendistatoEquivalentSwapLengthQuote(
            const std::string &ObjectId,
            const std::string &RendistatoCalculator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlRendistatoEquivalentSwapSpreadQuote(
            const std::string &ObjectId,
            const std::string &RendistatoCalculator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

