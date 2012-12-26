
/*  
 
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 
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
#include <ql/models/marketmodels/swapforwardmappings.hpp>
#include <ql/models/marketmodels/curvestates/cmswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/coterminalswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/lmmcurvestate.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/valueobjects/vo_curvestate.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlCMSwapCurveState(
        char *ObjectId,
        OPER *RateTimes,
        long *SpanningForwards,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCMSwapCurveState"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(*SpanningForwards, SpanningForwardsLib);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCMSwapCurveState(
                ObjectIdStrip,
                RateTimesCpp,
                *SpanningForwards,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CMSwapCurveState(
                valueObject,
                RateTimesCpp,
                SpanningForwardsLib,
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
XLL_DEC bool *qlCMSwapCurveStateSetOnCMSwapRates(
        char *ObjectId,
        OPER *CMSwapRates,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCMSwapCurveStateSetOnCMSwapRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> CMSwapRatesCpp =
            ObjectHandler::operToVector<double>(*CMSwapRates, "CMSwapRates");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CMSwapCurveState, QuantLib::CMSwapCurveState)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->setOnCMSwapRates(
                CMSwapRatesCpp);

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
XLL_DEC OPER *qlConstantMaturitySwapAnnuitiesFromDiscountRatios(
        long *SpanningForwards,
        long *FirstValidIndex,
        OPER *DiscountRatios,
        OPER *Taus,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlConstantMaturitySwapAnnuitiesFromDiscountRatios"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DiscountRatiosCpp =
            ObjectHandler::operToVector<double>(*DiscountRatios, "DiscountRatios");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(*SpanningForwards, SpanningForwardsLib);

        QuantLib::Size FirstValidIndexLib;
        QuantLibAddin::cppToLibrary(*FirstValidIndex, FirstValidIndexLib);

        // invoke the utility function

        std::vector<QuantLib::Real> returnValue = QuantLibAddin::qlConstantMaturitySwapAnnuitiesFromDiscountRatios(
                SpanningForwardsLib,
                FirstValidIndexLib,
                DiscountRatiosCpp,
                TausCpp);

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
XLL_DEC OPER *qlConstantMaturitySwapRatesFromDiscountRatios(
        long *SpanningForwards,
        long *FirstValidIndex,
        OPER *DiscountRatios,
        OPER *Taus,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlConstantMaturitySwapRatesFromDiscountRatios"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DiscountRatiosCpp =
            ObjectHandler::operToVector<double>(*DiscountRatios, "DiscountRatios");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(*SpanningForwards, SpanningForwardsLib);

        QuantLib::Size FirstValidIndexLib;
        QuantLibAddin::cppToLibrary(*FirstValidIndex, FirstValidIndexLib);

        // invoke the utility function

        std::vector<double> returnValue = QuantLibAddin::qlConstantMaturitySwapRatesFromDiscountRatios(
                SpanningForwardsLib,
                FirstValidIndexLib,
                DiscountRatiosCpp,
                TausCpp);

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
XLL_DEC OPER *qlCoterminalSwapAnnuitiesFromDiscountRatios(
        long *FirstValidIndex,
        OPER *DiscountRatios,
        OPER *Taus,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoterminalSwapAnnuitiesFromDiscountRatios"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DiscountRatiosCpp =
            ObjectHandler::operToVector<double>(*DiscountRatios, "DiscountRatios");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size FirstValidIndexLib;
        QuantLibAddin::cppToLibrary(*FirstValidIndex, FirstValidIndexLib);

        // invoke the utility function

        std::vector<QuantLib::Real> returnValue = QuantLibAddin::qlCoterminalSwapAnnuitiesFromDiscountRatios(
                FirstValidIndexLib,
                DiscountRatiosCpp,
                TausCpp);

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
XLL_DEC char *qlCoterminalSwapCurveState(
        char *ObjectId,
        OPER *RateTimes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoterminalSwapCurveState"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCoterminalSwapCurveState(
                ObjectIdStrip,
                RateTimesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CoterminalSwapCurveState(
                valueObject,
                RateTimesCpp,
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
XLL_DEC bool *qlCoterminalSwapCurveStateSetOnCoterminalSwapRates(
        char *ObjectId,
        OPER *CoterminalSwaps,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoterminalSwapCurveStateSetOnCoterminalSwapRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> CoterminalSwapsCpp =
            ObjectHandler::operToVector<double>(*CoterminalSwaps, "CoterminalSwaps");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CoterminalSwapCurveState, QuantLib::CoterminalSwapCurveState)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->setOnCoterminalSwapRates(
                CoterminalSwapsCpp);

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
XLL_DEC OPER *qlCoterminalSwapRatesFromDiscountRatios(
        long *FirstValidIndex,
        OPER *DiscountRatios,
        OPER *Taus,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoterminalSwapRatesFromDiscountRatios"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DiscountRatiosCpp =
            ObjectHandler::operToVector<double>(*DiscountRatios, "DiscountRatios");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size FirstValidIndexLib;
        QuantLibAddin::cppToLibrary(*FirstValidIndex, FirstValidIndexLib);

        // invoke the utility function

        std::vector<double> returnValue = QuantLibAddin::qlCoterminalSwapRatesFromDiscountRatios(
                FirstValidIndexLib,
                DiscountRatiosCpp,
                TausCpp);

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
XLL_DEC OPER *qlCurveStateCMSwapRates(
        char *ObjectId,
        long *SpanningForwards,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCurveStateCMSwapRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(*SpanningForwards, SpanningForwardsLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->cmSwapRates(
                SpanningForwardsLib);

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
XLL_DEC OPER *qlCurveStateCoterminalSwapRates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCurveStateCoterminalSwapRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->coterminalSwapRates();

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
XLL_DEC OPER *qlCurveStateForwardRates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCurveStateForwardRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->forwardRates();

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
XLL_DEC OPER *qlCurveStateRateTaus(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCurveStateRateTaus"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->rateTaus();

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
XLL_DEC OPER *qlCurveStateRateTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCurveStateRateTimes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->rateTimes();

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
XLL_DEC OPER *qlForwardsFromDiscountRatios(
        long *FirstValidIndex,
        OPER *DiscountRatios,
        OPER *Taus,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardsFromDiscountRatios"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DiscountRatiosCpp =
            ObjectHandler::operToVector<double>(*DiscountRatios, "DiscountRatios");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size FirstValidIndexLib;
        QuantLibAddin::cppToLibrary(*FirstValidIndex, FirstValidIndexLib);

        // invoke the utility function

        std::vector<double> returnValue = QuantLibAddin::qlForwardsFromDiscountRatios(
                FirstValidIndexLib,
                DiscountRatiosCpp,
                TausCpp);

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
XLL_DEC char *qlLMMCurveState(
        char *ObjectId,
        OPER *RateTimes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMCurveState"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLMMCurveState(
                ObjectIdStrip,
                RateTimesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LMMCurveState(
                valueObject,
                RateTimesCpp,
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
XLL_DEC bool *qlLMMCurveStateSetOnDiscountRatios(
        char *ObjectId,
        OPER *DiscountRatios,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMCurveStateSetOnDiscountRatios"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DiscountRatiosCpp =
            ObjectHandler::operToVector<double>(*DiscountRatios, "DiscountRatios");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->setOnDiscountRatios(
                DiscountRatiosCpp);

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
XLL_DEC bool *qlLMMCurveStateSetOnForwardRates(
        char *ObjectId,
        OPER *Rates,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMCurveStateSetOnForwardRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RatesCpp =
            ObjectHandler::operToVector<double>(*Rates, "Rates");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->setOnForwardRates(
                RatesCpp);

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
