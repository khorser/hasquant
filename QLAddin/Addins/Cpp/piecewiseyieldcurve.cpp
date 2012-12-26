
/*  
 Copyright (C) 2007, 2009 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 
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
#include <qlo/piecewiseyieldcurve.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/handleimpl.hpp>
#include <ql/interestrate.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/valueobjects/vo_piecewiseyieldcurve.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlPiecewiseYieldCurve(
            const std::string &ObjectId,
            const ObjectHandler::property_t &NDays,
            const std::string &Calendar,
            const std::vector<std::string>& RateHelpers,
            const ObjectHandler::property_t &DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &TraitsID,
            const ObjectHandler::property_t &InterpolatorID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long NDaysCpp = ObjectHandler::convert2<long>(
            NDays, "NDays", 0);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1.0e-12);

        std::string TraitsIDCpp = ObjectHandler::convert2<std::string>(
            TraitsID, "TraitsID", "Discount");

        std::string InterpolatorIDCpp = ObjectHandler::convert2<std::string>(
            InterpolatorID, "InterpolatorID", "LogLinear");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural NDaysLib = ObjectHandler::convert2<long>(
            NDays, "NDays", 0);

        std::vector<QuantLib::Date> JumpDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(JumpDates, "JumpDates");

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpers);

        std::vector<QuantLib::Handle<QuantLib::Quote> > JumpsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Jumps, "Jumps");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseYieldCurve(
                ObjectId,
                NDaysCpp,
                Calendar,
                RateHelpers,
                DayCounterCpp,
                Jumps,
                JumpDates,
                AccuracyCpp,
                TraitsIDCpp,
                InterpolatorIDCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseYieldCurve(
                valueObject,
                NDaysLib,
                CalendarEnum,
                RateHelpersLibObjPtr,
                DayCounterEnum,
                JumpsLibObj,
                JumpDatesLib,
                AccuracyLib,
                TraitsIDCpp,
                InterpolatorIDCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPiecewiseYieldCurve : " << e.what());
        }
    }

}

