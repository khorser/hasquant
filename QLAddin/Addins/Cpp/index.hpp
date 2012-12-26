
/*  
 Copyright (C) 2006, 2007, 2008, 2009, 2010 Ferdinando Ametrano
 Copyright (C) 2006 Katiuscia Manzoni
 Copyright (C) 2005, 2007 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 
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

#ifndef qlcpp_index_hpp
#define qlcpp_index_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlBMAIndex(
            const std::string &ObjectId,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEonia(
            const std::string &ObjectId,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEuribor(
            const std::string &ObjectId,
            const std::string &Tenor,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEuribor365(
            const std::string &ObjectId,
            const std::string &Tenor,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEuriborSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &FixingType,
            const std::string &Tenor,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEuriborSwapIsdaFixA(
            const std::string &ObjectId,
            const std::string &Tenor,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlIborIndex(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &BDayConvention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    bool qlIndexAddFixings(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& FixingDates,
            const std::vector<double>& FixingValues,
            const ObjectHandler::property_t &ForceOverwrite,
            const ObjectHandler::property_t &Trigger);


    std::string qlLibor(
            const std::string &ObjectId,
            const std::string &Currency,
            const std::string &Tenor,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlLiborSwap(
            const std::string &ObjectId,
            const std::string &Currency,
            const ObjectHandler::property_t &FixingType,
            const std::string &Tenor,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlOvernightIndex(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &DayCounter,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlProxyIbor(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &BDayConvention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Gearing,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSonia(
            const std::string &ObjectId,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSwapIndex(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &FixedLegTenor,
            const std::string &FixedLegBDC,
            const std::string &FixedLegDayCounter,
            const std::string &IborIndex,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

