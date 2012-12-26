
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <ql/time/schedule.hpp>
#include <qlo/schedule.hpp>
#include <qlo/valueobjects/vo_schedule.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

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
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string CalendarCpp = ObjectHandler::convert2<std::string>(
            Calendar, "Calendar", "NullCalendar");

        std::string ConventionCpp = ObjectHandler::convert2<std::string>(
            Convention, "Convention", "Unadjusted");

        std::string TermDateConvCpp = ObjectHandler::convert2<std::string>(
            TermDateConv, "TermDateConv", "Unadjusted");

        std::string GenRuleCpp = ObjectHandler::convert2<std::string>(
            GenRule, "GenRule", "Backward");

        bool EndOfMonthCpp = ObjectHandler::convert2<bool>(
            EndOfMonth, "EndOfMonth", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date EffectiveDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EffectiveDate, "EffectiveDate", QuantLib::Date());

        QuantLib::Date TerminationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            TerminationDate, "TerminationDate");

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Date FirstDateLib = ObjectHandler::convert2<QuantLib::Date>(
            FirstDate, "FirstDate", QuantLib::Date());

        QuantLib::Date NextToLastDateLib = ObjectHandler::convert2<QuantLib::Date>(
            NextToLastDate, "NextToLastDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(CalendarCpp);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ConventionCpp);

        QuantLib::BusinessDayConvention TermDateConvEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(TermDateConvCpp);

        QuantLib::DateGeneration::Rule GenRuleEnum =
            ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(GenRuleCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSchedule(
                ObjectId,
                EffectiveDate,
                TerminationDate,
                Tenor,
                CalendarCpp,
                ConventionCpp,
                TermDateConvCpp,
                GenRuleCpp,
                EndOfMonthCpp,
                FirstDate,
                NextToLastDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Schedule(
                valueObject,
                EffectiveDateLib,
                TerminationDateLib,
                TenorLib,
                CalendarEnum,
                ConventionEnum,
                TermDateConvEnum,
                GenRuleEnum,
                EndOfMonthCpp,
                FirstDateLib,
                NextToLastDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSchedule : " << e.what());
        }
    }


    std::string qlScheduleFromDateVector(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& EffectiveDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> EffectiveDateLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(EffectiveDate, "EffectiveDate");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlScheduleFromDateVector(
                ObjectId,
                EffectiveDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Schedule(
                valueObject,
                EffectiveDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlScheduleFromDateVector : " << e.what());
        }
    }


    std::string qlScheduleTruncated(
            const std::string &ObjectId,
            const std::string &OriginalSchedule,
            const ObjectHandler::property_t &TruncationDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date TruncationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            TruncationDate, "TruncationDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(OriginalScheduleLibObjPtr, OriginalSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlScheduleTruncated(
                ObjectId,
                OriginalSchedule,
                TruncationDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Schedule(
                valueObject,
                OriginalScheduleLibObjPtr,
                TruncationDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlScheduleTruncated : " << e.what());
        }
    }

}

