
/*  
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2006, 2007, 2009 Ferdinando Ametrano
 Copyright (C) 2005 Plamen Neykov
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
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/valueobjects/vo_termstructures.hpp>
#include <qlo/loop/loop_termstructures.hpp>
#include <Addins/Cpp/loop.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlDiscountCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveDiscounts,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDiscountCurve(
                ObjectId,
                CurveDates,
                CurveDiscounts,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscountCurve(
                valueObject,
                CurveDatesLib,
                CurveDiscounts,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlDiscountCurve : " << e.what());
        }
    }


    std::string qlFlatForward(
            const std::string &ObjectId,
            const ObjectHandler::property_t &NDays,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &Rate,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Compounding,
            const ObjectHandler::property_t &Frequency,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long NDaysCpp = ObjectHandler::convert2<long>(
            NDays, "NDays", 0);

        std::string CalendarCpp = ObjectHandler::convert2<std::string>(
            Calendar, "Calendar", "NullCalendar");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            Compounding, "Compounding", "Continuous");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            Frequency, "Frequency", "Annual");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            NDays, "NDays", 0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(CalendarCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatForward(
                ObjectId,
                NDaysCpp,
                CalendarCpp,
                Rate,
                DayCounterCpp,
                CompoundingCpp,
                FrequencyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatForward(
                valueObject,
                NDaysLib,
                CalendarEnum,
                RateLibObj,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFlatForward : " << e.what());
        }
    }


    std::string qlForwardCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& ForwardYields,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardCurve(
                ObjectId,
                CurveDates,
                ForwardYields,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardCurve(
                valueObject,
                CurveDatesLib,
                ForwardYields,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlForwardCurve : " << e.what());
        }
    }


    std::string qlForwardSpreadedTermStructure(
            const std::string &ObjectId,
            const std::string &BaseYieldCurve,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardSpreadedTermStructure(
                ObjectId,
                BaseYieldCurve,
                Spread,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardSpreadedTermStructure(
                valueObject,
                BaseYieldCurveLibObj,
                SpreadLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlForwardSpreadedTermStructure : " << e.what());
        }
    }


    std::string qlImpliedTermStructure(
            const std::string &ObjectId,
            const std::string &BaseYieldCurve,
            const ObjectHandler::property_t &ReferenceDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ReferenceDate, "ReferenceDate");

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseYieldCurveCoerce, BaseYieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    BaseYieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlImpliedTermStructure(
                ObjectId,
                BaseYieldCurve,
                ReferenceDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ImpliedTermStructure(
                valueObject,
                BaseYieldCurveLibObj,
                ReferenceDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlImpliedTermStructure : " << e.what());
        }
    }


    std::string qlInterpolatedYieldCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& Dates,
            const std::vector<double>& Data,
            const std::string &Calendar,
            const ObjectHandler::property_t &DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
            const ObjectHandler::property_t &TraitsID,
            const ObjectHandler::property_t &InterpolatorID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        std::string TraitsIDCpp = ObjectHandler::convert2<std::string>(
            TraitsID, "TraitsID", "Discount");

        std::string InterpolatorIDCpp = ObjectHandler::convert2<std::string>(
            InterpolatorID, "InterpolatorID", "MonotonicLogCubicNaturalSpline");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > JumpsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Jumps, "Jumps");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolatedYieldCurve(
                ObjectId,
                Dates,
                Data,
                Calendar,
                DayCounterCpp,
                Jumps,
                JumpDates,
                TraitsIDCpp,
                InterpolatorIDCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterpolatedYieldCurve(
                valueObject,
                DatesLib,
                DataLib,
                CalendarEnum,
                DayCounterEnum,
                JumpsLibObj,
                JumpDatesLib,
                TraitsIDCpp,
                InterpolatorIDCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInterpolatedYieldCurve : " << e.what());
        }
    }


    std::string qlRelinkableHandleYieldTermStructure(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string CurrentLinkCpp = ObjectHandler::convert2<std::string>(
            CurrentLink, "CurrentLink", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRelinkableHandleYieldTermStructure(
                ObjectId,
                CurrentLinkCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure>(
                valueObject,
                CurrentLinkCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRelinkableHandleYieldTermStructure : " << e.what());
        }
    }


    long qlTermStructureMaxDate(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::TermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::TermStructure,
                QuantLib::TermStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->maxDate();

        // convert and return the return value

        long returnValueLib = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return returnValueLib;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlTermStructureMaxDate : " << e.what());
        }
    }


    long qlTermStructureReferenceDate(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::TermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::TermStructure,
                QuantLib::TermStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->referenceDate();

        // convert and return the return value

        long returnValueLib = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return returnValueLib;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlTermStructureReferenceDate : " << e.what());
        }
    }


    long qlTermStructureSettlementDays(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::TermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::TermStructure,
                QuantLib::TermStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Natural returnValue = ObjectIdLibObjPtr->settlementDays();

        // convert and return the return value

        long returnValueLib = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return returnValueLib;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlTermStructureSettlementDays : " << e.what());
        }
    }


    std::string qlZeroCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveYields,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlZeroCurve(
                ObjectId,
                CurveDates,
                CurveYields,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ZeroCurve(
                valueObject,
                CurveDatesLib,
                CurveYields,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlZeroCurve : " << e.what());
        }
    }

}

