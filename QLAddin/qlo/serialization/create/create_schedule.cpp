
/*  
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov
 
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
//      QuantLibAddin/gensrc/stubs/stub.serialization.includes

#include <qlo/serialization/create/create_schedule.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>

#include <qlo/schedule.hpp>
#include <qlo/valueobjects/vo_schedule.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlSchedule(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t EffectiveDate =
            valueObject->getProperty("EffectiveDate");

        ObjectHandler::property_t TerminationDate =
            valueObject->getProperty("TerminationDate");

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

        std::string TermDateConv =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("TermDateConv"));

        std::string GenRule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("GenRule"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        ObjectHandler::property_t FirstDate =
            valueObject->getProperty("FirstDate");

        ObjectHandler::property_t NextToLastDate =
            valueObject->getProperty("NextToLastDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date EffectiveDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EffectiveDate"), "EffectiveDate", QuantLib::Date());

        QuantLib::Date TerminationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("TerminationDate"), "TerminationDate");

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Date FirstDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FirstDate"), "FirstDate", QuantLib::Date());

        QuantLib::Date NextToLastDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("NextToLastDate"), "NextToLastDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::BusinessDayConvention TermDateConvEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(TermDateConv);

        QuantLib::DateGeneration::Rule GenRuleEnum =
            ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(GenRule);

        // update value object precedent IDs (if any)



        // construct and return the object

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
                EndOfMonth,
                FirstDateLib,
                NextToLastDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlScheduleFromDateVector(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> EffectiveDate =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("EffectiveDate"), "EffectiveDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> EffectiveDateLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(EffectiveDate, "EffectiveDate");

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Schedule(
                valueObject,
                EffectiveDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlScheduleTruncated(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OriginalSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OriginalSchedule"));

        ObjectHandler::property_t TruncationDate =
            valueObject->getProperty("TruncationDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date TruncationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("TruncationDate"), "TruncationDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(OriginalScheduleLibObjPtr, OriginalSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(OriginalSchedule);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Schedule(
                valueObject,
                OriginalScheduleLibObjPtr,
                TruncationDateLib,
                Permanent));
        return object;
    }

}
