
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

#include <qlo/serialization/create/create_piecewiseyieldcurve.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/piecewiseyieldcurve.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/conversions/coercetermstructure.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlPiecewiseYieldCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long NDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("NDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::vector<std::string> RateHelpers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("RateHelpers"), "RateHelpers");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<ObjectHandler::property_t> Jumps =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Jumps"), "Jumps");

        std::vector<ObjectHandler::property_t> JumpDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("JumpDates"), "JumpDates");

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        std::string TraitsID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("TraitsID"));

        std::string InterpolatorID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterpolatorID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> JumpDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(JumpDates, "JumpDates");

        QuantLib::Real AccuracyLib = Accuracy;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpers);

        std::vector<QuantLib::Handle<QuantLib::Quote> > JumpsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Jumps, "Jumps");

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = RateHelpers.begin();
                i != RateHelpers.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processVariant(Jumps);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseYieldCurve(
                valueObject,
                NDays,
                CalendarEnum,
                RateHelpersLibObjPtr,
                DayCounterEnum,
                JumpsLibObj,
                JumpDatesLib,
                AccuracyLib,
                TraitsID,
                InterpolatorID,
                Permanent));
        return object;
    }

}
