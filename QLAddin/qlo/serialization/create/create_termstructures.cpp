
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

#include <qlo/serialization/create/create_termstructures.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlDiscountCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("CurveDates"), "CurveDates");

        std::vector<double> CurveDiscounts =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CurveDiscounts"), "CurveDiscounts");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscountCurve(
                valueObject,
                CurveDatesLib,
                CurveDiscounts,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFlatForward(
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

        std::string Compounding =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Compounding"));

        std::string Frequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Frequency"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(Compounding);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(Frequency);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatForward(
                valueObject,
                NDays,
                CalendarEnum,
                RateLibObj,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("CurveDates"), "CurveDates");

        std::vector<double> ForwardYields =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("ForwardYields"), "ForwardYields");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardCurve(
                valueObject,
                CurveDatesLib,
                ForwardYields,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardSpreadedTermStructure(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BaseYieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BaseYieldCurve"));

        ObjectHandler::property_t Spread =
            valueObject->getProperty("Spread");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseYieldCurveCoerce, BaseYieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    BaseYieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(BaseYieldCurve);
        valueObject->processVariant(Spread);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardSpreadedTermStructure(
                valueObject,
                BaseYieldCurveLibObj,
                SpreadLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlImpliedTermStructure(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BaseYieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BaseYieldCurve"));

        ObjectHandler::property_t ReferenceDate =
            valueObject->getProperty("ReferenceDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ReferenceDate"), "ReferenceDate");

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseYieldCurveCoerce, BaseYieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    BaseYieldCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(BaseYieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ImpliedTermStructure(
                valueObject,
                BaseYieldCurveLibObj,
                ReferenceDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlInterpolatedYieldCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> Dates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Dates"), "Dates");

        std::vector<double> Data =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Data"), "Data");

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<ObjectHandler::property_t> Jumps =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Jumps"), "Jumps");

        std::vector<ObjectHandler::property_t> JumpDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("JumpDates"), "JumpDates");

        std::string TraitsID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("TraitsID"));

        std::string InterpolatorID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterpolatorID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(Dates, "Dates");

        std::vector<QuantLib::Real> DataLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Data);

        std::vector<QuantLib::Date> JumpDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(JumpDates, "JumpDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > JumpsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Jumps, "Jumps");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Jumps);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterpolatedYieldCurve(
                valueObject,
                DatesLib,
                DataLib,
                CalendarEnum,
                DayCounterEnum,
                JumpsLibObj,
                JumpDatesLib,
                TraitsID,
                InterpolatorID,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRelinkableHandleYieldTermStructure(
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
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure>(
                valueObject,
                CurrentLink,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlZeroCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("CurveDates"), "CurveDates");

        std::vector<double> CurveYields =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CurveYields"), "CurveYields");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ZeroCurve(
                valueObject,
                CurveDatesLib,
                CurveYields,
                DayCounterEnum,
                Permanent));
        return object;
    }

}
