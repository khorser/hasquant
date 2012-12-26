
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
//      QuantLibAddin/gensrc/stubs/stub.excel.includes

#include <qlo/qladdindefines.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/valueobjects/vo_termstructures.hpp>
#include <qlo/loop/loop_termstructures.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlDiscountCurve(
        char *ObjectId,
        OPER *CurveDates,
        OPER *CurveDiscounts,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDiscountCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*CurveDates, "CurveDates");

        std::vector<double> CurveDiscountsCpp =
            ObjectHandler::operToVector<double>(*CurveDiscounts, "CurveDiscounts");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDiscountCurve(
                ObjectIdStrip,
                CurveDatesCpp,
                CurveDiscountsCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscountCurve(
                valueObject,
                CurveDatesLib,
                CurveDiscountsCpp,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlFlatForward(
        char *ObjectId,
        OPER *NDays,
        OPER *Calendar,
        OPER *Rate,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFlatForward"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        long NDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*NDays), "NDays", 0);

        std::string CalendarCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Calendar), "Calendar", "NullCalendar");

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Continuous");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*NDays), "NDays", 0);

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
                ObjectHandler::ConvertOper(*Rate), "Rate");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatForward(
                ObjectIdStrip,
                NDaysCpp,
                CalendarCpp,
                RateCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlForwardCurve(
        char *ObjectId,
        OPER *CurveDates,
        OPER *ForwardYields,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*CurveDates, "CurveDates");

        std::vector<double> ForwardYieldsCpp =
            ObjectHandler::operToVector<double>(*ForwardYields, "ForwardYields");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardCurve(
                ObjectIdStrip,
                CurveDatesCpp,
                ForwardYieldsCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardCurve(
                valueObject,
                CurveDatesLib,
                ForwardYieldsCpp,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlForwardSpreadedTermStructure(
        char *ObjectId,
        char *BaseYieldCurve,
        OPER *Spread,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardSpreadedTermStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Spread));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseYieldCurveCoerce, BaseYieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    BaseYieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Spread), "Spread");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BaseYieldCurveStrip = ObjectHandler::CallingRange::getStub(BaseYieldCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardSpreadedTermStructure(
                ObjectIdStrip,
                BaseYieldCurveStrip,
                SpreadCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlImpliedTermStructure(
        char *ObjectId,
        char *BaseYieldCurve,
        OPER *ReferenceDate,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlImpliedTermStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ReferenceDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ReferenceDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ReferenceDate), "ReferenceDate");

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseYieldCurveCoerce, BaseYieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    BaseYieldCurveCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BaseYieldCurveStrip = ObjectHandler::CallingRange::getStub(BaseYieldCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlImpliedTermStructure(
                ObjectIdStrip,
                BaseYieldCurveStrip,
                ReferenceDateCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlInterpolatedYieldCurve(
        char *ObjectId,
        OPER *Dates,
        OPER *Data,
        char *Calendar,
        OPER *DayCounter,
        OPER *Jumps,
        OPER *JumpDates,
        OPER *TraitsID,
        OPER *InterpolatorID,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedYieldCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> DatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*Dates, "Dates");

        std::vector<double> DataCpp =
            ObjectHandler::operToVector<double>(*Data, "Data");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        std::vector<ObjectHandler::property_t> JumpsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*Jumps, "Jumps");

        std::vector<ObjectHandler::property_t> JumpDatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*JumpDates, "JumpDates");

        std::string TraitsIDCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*TraitsID), "TraitsID", "Discount");

        std::string InterpolatorIDCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*InterpolatorID), "InterpolatorID", "MonotonicLogCubicNaturalSpline");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Dates, "Dates");

        std::vector<QuantLib::Real> DataLib =
            ObjectHandler::operToVector<QuantLib::Real>(*Data, "Data");

        std::vector<QuantLib::Date> JumpDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*JumpDates, "JumpDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > JumpsLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*Jumps, "Jumps");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolatedYieldCurve(
                ObjectIdStrip,
                DatesCpp,
                DataCpp,
                Calendar,
                DayCounterCpp,
                JumpsCpp,
                JumpDatesCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolatedYieldCurveData(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedYieldCurveData"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::InterpolatedYieldCurve)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdObjPtr->data();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolatedYieldCurveDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedYieldCurveDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::InterpolatedYieldCurve)

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdObjPtr->dates();

        // convert and return the return value

        std::vector<long> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolatedYieldCurveJumpDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedYieldCurveJumpDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::InterpolatedYieldCurve)

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdObjPtr->jumpDates();

        // convert and return the return value

        std::vector<long> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolatedYieldCurveJumpTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedYieldCurveJumpTimes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::InterpolatedYieldCurve)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->jumpTimes();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::vectorToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolatedYieldCurveTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedYieldCurveTimes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::InterpolatedYieldCurve)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->times();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::vectorToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlRelinkableHandleYieldTermStructure(
        char *ObjectId,
        OPER *CurrentLink,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRelinkableHandleYieldTermStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string CurrentLinkCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*CurrentLink), "CurrentLink", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRelinkableHandleYieldTermStructure(
                ObjectIdStrip,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlTermStructureCalendar(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTermStructureCalendar"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::TermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::TermStructure,
                QuantLib::TermStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Calendar returnValue = ObjectIdLibObjPtr->calendar();

        // convert and return the return value

        std::ostringstream os;
        os << returnValue;
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(os.str(), ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlTermStructureDayCounter(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTermStructureDayCounter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::TermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::TermStructure,
                QuantLib::TermStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::DayCounter returnValue = ObjectIdLibObjPtr->dayCounter();

        // convert and return the return value

        std::ostringstream os;
        os << returnValue;
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(os.str(), ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlTermStructureMaxDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTermStructureMaxDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

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

        static long returnValueXL;
        returnValueXL = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return &returnValueXL;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlTermStructureReferenceDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTermStructureReferenceDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

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

        static long returnValueXL;
        returnValueXL = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return &returnValueXL;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlTermStructureSettlementDays(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTermStructureSettlementDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

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

        static long returnValueXL;
        returnValueXL = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return &returnValueXL;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlTermStructureTimeFromReference(
        char *ObjectId,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTermStructureTimeFromReference"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::TermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::TermStructure,
                QuantLib::TermStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlTermStructureTimeFromReferenceBind bindObject = 
            boost::bind((QuantLibAddin::qlTermStructureTimeFromReferenceSignature)
                &QuantLib::TermStructure::timeFromReference,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlTermStructureTimeFromReferenceBind, QuantLib::Date, double>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlYieldTSDiscount(
        char *ObjectId,
        OPER *DfDates,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlYieldTSDiscount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DfDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*DfDates, "DfDates");

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlYieldTSDiscountBind bindObject = 
            boost::bind((QuantLibAddin::qlYieldTSDiscountSignature)
                &QuantLib::YieldTermStructure::discount,
                ObjectIdLibObjPtr,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlYieldTSDiscountBind, QuantLib::Date, double>
            (functionCall, bindObject, DfDates, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlYieldTSForwardRate(
        char *ObjectId,
        OPER *D1,
        OPER *D2,
        char *ResultDayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlYieldTSForwardRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t D1Cpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*D1));

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Simple");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date D1Lib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*D1), "D1");

        std::vector<QuantLib::Date> D2Lib =
            ObjectHandler::operToVector<QuantLib::Date>(*D2, "D2");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter ResultDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(ResultDayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlYieldTSForwardRateBind bindObject = 
            boost::bind((QuantLibAddin::qlYieldTSForwardRateSignature)
                &QuantLib::YieldTermStructure::forwardRate,
                ObjectIdLibObjPtr,
                D1Lib,
                _1,
                ResultDayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlYieldTSForwardRateBind, QuantLib::Date, QuantLib::InterestRate>
            (functionCall, bindObject, D2, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlYieldTSForwardRate2(
        char *ObjectId,
        OPER *Date,
        char *Period,
        char *ResultDayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlYieldTSForwardRate2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Simple");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        QuantLib::Period PeriodLib;
        QuantLibAddin::cppToLibrary(Period, PeriodLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter ResultDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(ResultDayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlYieldTSForwardRate2Bind bindObject = 
            boost::bind((QuantLibAddin::qlYieldTSForwardRate2Signature)
                &QuantLib::YieldTermStructure::forwardRate,
                ObjectIdLibObjPtr,
                _1,
                PeriodLib,
                ResultDayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlYieldTSForwardRate2Bind, QuantLib::Date, QuantLib::InterestRate>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlYieldTSZeroRate(
        char *ObjectId,
        OPER *Dates,
        char *ResultDayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlYieldTSZeroRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Continuous");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Dates, "Dates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter ResultDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(ResultDayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlYieldTSZeroRateBind bindObject = 
            boost::bind((QuantLibAddin::qlYieldTSZeroRateSignature)
                &QuantLib::YieldTermStructure::zeroRate,
                ObjectIdLibObjPtr,
                _1,
                ResultDayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlYieldTSZeroRateBind, QuantLib::Date, QuantLib::InterestRate>
            (functionCall, bindObject, Dates, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlZeroCurve(
        char *ObjectId,
        OPER *CurveDates,
        OPER *CurveYields,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlZeroCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*CurveDates, "CurveDates");

        std::vector<double> CurveYieldsCpp =
            ObjectHandler::operToVector<double>(*CurveYields, "CurveYields");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlZeroCurve(
                ObjectIdStrip,
                CurveDatesCpp,
                CurveYieldsCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ZeroCurve(
                valueObject,
                CurveDatesLib,
                CurveYieldsCpp,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
