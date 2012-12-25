
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

#include <qlo/serialization/create/create_defaulttermstructures.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/conversions/coercetermstructure.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlFlatHazardRate(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long NDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("NDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatHazardRate(
                valueObject,
                NDays,
                CalendarEnum,
                RateLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRelinkableHandleDefaultProbabilityTermStructure(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string CurrentLink =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurrentLink"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(CurrentLink);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::DefaultProbabilityTermStructure, QuantLib::DefaultProbabilityTermStructure>(
                valueObject,
                CurrentLink,
                Permanent));
        return object;
    }

}
