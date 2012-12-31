
/*  
 Copyright (C) 2006, 2007, 2011 Ferdinando Ametrano
 Copyright (C) 2005 Aurelien Chanudet
 
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

#ifndef qlcpp_schedule_hpp
#define qlcpp_schedule_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlSchedule(
            const std::string &ObjectId,
            const ObjectHandler::property_t &EffectiveDate,
            const ObjectHandler::property_t &TerminationDate,
            const std::string &Tenor,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &Convention,
            const ObjectHandler::property_t &TermDateConv,
            const ObjectHandler::property_t &GenRule,
            const ObjectHandler::property_t &EndOfMonth,
            const ObjectHandler::property_t &FirstDate,
            const ObjectHandler::property_t &NextToLastDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlScheduleFromDateVector(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& EffectiveDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlScheduleTruncated(
            const std::string &ObjectId,
            const std::string &OriginalSchedule,
            const ObjectHandler::property_t &TruncationDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

