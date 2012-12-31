
/*  
 Copyright (C) 2007, 2010 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 
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
#include <qlo/indexes/interestrateindex.hpp>
#include <qlo/volatilities.hpp>
#include <ql/math/interpolations/sabrinterpolation.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackvariancesurface.hpp>
#include <ql/experimental/volatility/abcdatmvolcurve.hpp>
#include <ql/experimental/volatility/sabrvolsurface.hpp>
#include <qlo/valueobjects/vo_volatilities.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlAbcdAtmVolCurve(
        char *ObjectId,
        long *SettlementDays,
        char *Calendar,
        OPER *OptionTenors,
        OPER *VolatilitiesQuotes,
        OPER *InclusionInInterpolation,
        char *Convention,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> OptionTenorsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*OptionTenors, "OptionTenors");

        std::vector<ObjectHandler::property_t> VolatilitiesQuotesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*VolatilitiesQuotes, "VolatilitiesQuotes");

        std::vector<bool> InclusionInInterpolationCpp =
            ObjectHandler::operToVector<bool>(*InclusionInInterpolation, "InclusionInInterpolation");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural SettlementDaysLib;
        QuantLibAddin::cppToLibrary(*SettlementDays, SettlementDaysLib);

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenors, "OptionTenors");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitiesQuotesLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*VolatilitiesQuotes, "VolatilitiesQuotes");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdAtmVolCurve(
                ObjectIdStrip,
                *SettlementDays,
                Calendar,
                OptionTenorsCpp,
                VolatilitiesQuotesCpp,
                InclusionInInterpolationCpp,
                Convention,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdAtmVolCurve(
                valueObject,
                SettlementDaysLib,
                CalendarEnum,
                OptionTenorsLib,
                VolatilitiesQuotesLibObj,
                InclusionInInterpolationCpp,
                ConventionEnum,
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
XLL_DEC OPER *qlAbcdAtmVolCurveA(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveA"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->a();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdAtmVolCurveB(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveB"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->b();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdAtmVolCurveC(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveC"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->c();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdAtmVolCurveD(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveD"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->d();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdAtmVolCurveK(
        char *ObjectId,
        double *Time,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveK"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->k(
                *Time);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdAtmVolCurveKatOptionTenors(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveKatOptionTenors"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->k();

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
XLL_DEC OPER *qlAbcdAtmVolCurveMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveMaxError"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->maxError();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdAtmVolCurveOptionDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveOptionDates"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdLibObjPtr->optionDates();

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
XLL_DEC OPER *qlAbcdAtmVolCurveOptionTenors(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveOptionTenors"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        std::vector<QuantLib::Period> returnValue = ObjectIdLibObjPtr->optionTenors();

        // convert and return the return value

        std::vector<std::string> returnValVec = QuantLibAddin::libraryToVector(returnValue);
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
XLL_DEC OPER *qlAbcdAtmVolCurveOptionTenorsInInterpolation(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveOptionTenorsInInterpolation"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        std::vector<QuantLib::Period> returnValue = ObjectIdLibObjPtr->optionTenorsInInterpolation();

        // convert and return the return value

        std::vector<std::string> returnValVec = QuantLibAddin::libraryToVector(returnValue);
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
XLL_DEC OPER *qlAbcdAtmVolCurveOptionTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveOptionTimes"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->optionTimes();

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
XLL_DEC OPER *qlAbcdAtmVolCurveRmsError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdAtmVolCurveRmsError"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdAtmVolCurve, QuantLib::AbcdAtmVolCurve)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->rmsError();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlAtmCurve(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAtmCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SabrVolSurface)

        // invoke the member function

        std::string returnValue = ObjectIdObjPtr->atmCurve();

        // convert and return the return value

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
XLL_DEC double *qlBlackAtmVolCurveAtmVariance(
        char *ObjectId,
        OPER *OptionDate,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackAtmVolCurveAtmVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackAtmVolCurve, QuantLib::BlackAtmVolCurve)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmVariance(
                OptionDateLib,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackAtmVolCurveAtmVariance2(
        char *ObjectId,
        char *OptionTenor,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackAtmVolCurveAtmVariance2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackAtmVolCurve, QuantLib::BlackAtmVolCurve)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmVariance(
                OptionTenorLib,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackAtmVolCurveAtmVariance3(
        char *ObjectId,
        double *OptionTime,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackAtmVolCurveAtmVariance3"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackAtmVolCurve, QuantLib::BlackAtmVolCurve)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmVariance(
                *OptionTime,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackAtmVolCurveAtmVol(
        char *ObjectId,
        OPER *OptionDate,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackAtmVolCurveAtmVol"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackAtmVolCurve, QuantLib::BlackAtmVolCurve)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmVol(
                OptionDateLib,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackAtmVolCurveAtmVol2(
        char *ObjectId,
        char *OptionTenor,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackAtmVolCurveAtmVol2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackAtmVolCurve, QuantLib::BlackAtmVolCurve)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmVol(
                OptionTenorLib,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackAtmVolCurveAtmVol3(
        char *ObjectId,
        double *OptionTime,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackAtmVolCurveAtmVol3"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackAtmVolCurve, QuantLib::BlackAtmVolCurve)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmVol(
                *OptionTime,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlBlackConstantVol(
        char *ObjectId,
        OPER *SettlementDate,
        char *Calendar,
        double *Volatility,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackConstantVol"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackConstantVol(
                ObjectIdStrip,
                SettlementDateCpp,
                Calendar,
                *Volatility,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackConstantVol(
                valueObject,
                SettlementDateLib,
                CalendarEnum,
                *Volatility,
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
XLL_DEC char *qlBlackVarianceSurface(
        char *ObjectId,
        OPER *SettlementDate,
        char *Calendar,
        OPER *Dates,
        OPER *Strikes,
        FP *Volatilities,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackVarianceSurface"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        std::vector<ObjectHandler::property_t> DatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*Dates, "Dates");

        std::vector<double> StrikesCpp =
            ObjectHandler::operToVector<double>(*Strikes, "Strikes");

        std::vector<std::vector<double> > VolatilitiesCpp =
            ObjectHandler::fpToMatrix<double>(*Volatilities);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate");

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Dates, "Dates");

        QuantLib::Matrix VolatilitiesLib =
            QuantLibXL::operToQlMatrix(*Volatilities);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackVarianceSurface(
                ObjectIdStrip,
                SettlementDateCpp,
                Calendar,
                DatesCpp,
                StrikesCpp,
                VolatilitiesCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackVarianceSurface(
                valueObject,
                SettlementDateLib,
                CalendarEnum,
                DatesLib,
                StrikesCpp,
                VolatilitiesLib,
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
XLL_DEC OPER *qlBlackVolTermStructureBlackForwardVariance(
        char *ObjectId,
        OPER *ForwardDate,
        OPER *OptionDate,
        double *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackVolTermStructureBlackForwardVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ForwardDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ForwardDate));

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ForwardDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ForwardDate), "ForwardDate");

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackVolTermStructure, QuantLib::BlackVolTermStructure)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->blackForwardVariance(
                ForwardDateLib,
                OptionDateLib,
                *Strike,
                AllowExtrapolationCpp);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackVolTermStructureBlackForwardVol(
        char *ObjectId,
        OPER *ForwardDate,
        OPER *OptionDate,
        double *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackVolTermStructureBlackForwardVol"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ForwardDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ForwardDate));

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ForwardDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ForwardDate), "ForwardDate");

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackVolTermStructure, QuantLib::BlackVolTermStructure)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->blackForwardVol(
                ForwardDateLib,
                OptionDateLib,
                *Strike,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlBlackVolTermStructureBlackVariance(
        char *ObjectId,
        OPER *OptionDate,
        double *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackVolTermStructureBlackVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackVolTermStructure, QuantLib::BlackVolTermStructure)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->blackVariance(
                OptionDateLib,
                *Strike,
                AllowExtrapolationCpp);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlBlackVolTermStructureBlackVol(
        char *ObjectId,
        OPER *OptionDate,
        double *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackVolTermStructureBlackVol"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackVolTermStructure, QuantLib::BlackVolTermStructure)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->blackVol(
                OptionDateLib,
                *Strike,
                AllowExtrapolationCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSabrVolSurface(
        char *ObjectId,
        char *InterestRateIndex,
        char *BlackAtmVolCurve,
        OPER *OptionTenors,
        OPER *AtmRateSpreads,
        OPER *VolatilitiesQuotes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrVolSurface"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> OptionTenorsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*OptionTenors, "OptionTenors");

        std::vector<double> AtmRateSpreadsCpp =
            ObjectHandler::operToVector<double>(*AtmRateSpreads, "AtmRateSpreads");

        std::vector<std::vector<ObjectHandler::property_t> > VolatilitiesQuotesCpp =
            ObjectHandler::operToMatrix<ObjectHandler::property_t>(*VolatilitiesQuotes, "VolatilitiesQuotes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenors, "OptionTenors");

        // convert object IDs into library objects

        OH_GET_REFERENCE(InterestRateIndexLibObjPtr, InterestRateIndex,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        OH_GET_OBJECT(BlackAtmVolCurveCoerce, BlackAtmVolCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::BlackAtmVolCurve> BlackAtmVolCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::BlackAtmVolCurve,
                QuantLib::BlackAtmVolCurve>()(
                    BlackAtmVolCurveCoerce);

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesQuotesLibObj =
            ObjectHandler::operToMatrix<QuantLib::Handle<QuantLib::Quote> >(*VolatilitiesQuotes, "VolatilitiesQuotes");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string InterestRateIndexStrip = ObjectHandler::CallingRange::getStub(InterestRateIndex);
        std::string BlackAtmVolCurveStrip = ObjectHandler::CallingRange::getStub(BlackAtmVolCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrVolSurface(
                ObjectIdStrip,
                InterestRateIndexStrip,
                BlackAtmVolCurveStrip,
                OptionTenorsCpp,
                AtmRateSpreadsCpp,
                VolatilitiesQuotesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrVolSurface(
                valueObject,
                InterestRateIndexLibObjPtr,
                BlackAtmVolCurveLibObj,
                OptionTenorsLib,
                AtmRateSpreadsCpp,
                VolatilitiesQuotesLibObj,
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
XLL_DEC double *qlSabrVolatility(
        double *Strike,
        double *Forward,
        double *ExpTime,
        double *Alpha,
        double *Beta,
        double *Nu,
        double *Rho,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::sabrVolatility(
                *Strike,
                *Forward,
                *ExpTime,
                *Alpha,
                *Beta,
                *Nu,
                *Rho);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlVolatilitySpreads(
        char *ObjectId,
        OPER *OptionDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolatilitySpreads"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrVolSurface, QuantLib::SabrVolSurface)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->volatilitySpreads(
                OptionDateLib);

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
XLL_DEC OPER *qlVolatilitySpreads2(
        char *ObjectId,
        char *OptionTenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolatilitySpreads2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrVolSurface, QuantLib::SabrVolSurface)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->volatilitySpreads(
                OptionTenorLib);

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
XLL_DEC char *qlVolatilityTermStructureBusinessDayConvention(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolatilityTermStructureBusinessDayConvention"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::VolatilityTermStructure, QuantLib::VolatilityTermStructure)

        // invoke the member function

        QuantLib::BusinessDayConvention returnValue = ObjectIdLibObjPtr->businessDayConvention();

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
XLL_DEC double *qlVolatilityTermStructureMaxStrike(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolatilityTermStructureMaxStrike"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::VolatilityTermStructure, QuantLib::VolatilityTermStructure)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->maxStrike();

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlVolatilityTermStructureMinStrike(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolatilityTermStructureMinStrike"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::VolatilityTermStructure, QuantLib::VolatilityTermStructure)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->minStrike();

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlVolatilityTermStructureOptionDateFromTenor(
        char *ObjectId,
        char *Tenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolatilityTermStructureOptionDateFromTenor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::VolatilityTermStructure, QuantLib::VolatilityTermStructure)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->optionDateFromTenor(
                TenorLib);

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
