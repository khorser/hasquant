
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
#include <qlo/volatility.hpp>
#include <ql/models/marketmodels/models/piecewiseconstantabcdvariance.hpp>
#include <qlo/valueobjects/vo_volatility.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlMarketModelLmExtLinearExponentialVolModel(
        char *ObjectId,
        OPER *FixingTimes,
        double *A,
        double *B,
        double *C,
        double *D,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelLmExtLinearExponentialVolModel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> FixingTimesCpp =
            ObjectHandler::operToVector<double>(*FixingTimes, "FixingTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelLmExtLinearExponentialVolModel(
                ObjectIdStrip,
                FixingTimesCpp,
                *A,
                *B,
                *C,
                *D,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LmExtLinearExponentialVolModel(
                valueObject,
                FixingTimesCpp,
                *A,
                *B,
                *C,
                *D,
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
XLL_DEC char *qlPiecewiseConstantAbcdVariance(
        char *ObjectId,
        OPER *A,
        OPER *B,
        OPER *C,
        OPER *D,
        long *ResetIndex,
        OPER *RateTimes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantAbcdVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double ACpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*A), "A", -0.06);

        double BCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*B), "B", 0.17);

        double CCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*C), "C", 0.54);

        double DCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*D), "D", 0.17);

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseConstantAbcdVariance(
                ObjectIdStrip,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                *ResetIndex,
                RateTimesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseConstantAbcdVariance(
                valueObject,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                *ResetIndex,
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
XLL_DEC OPER *qlPiecewiseConstantVarianceRateTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceRateTimes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

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
XLL_DEC double *qlPiecewiseConstantVarianceTotalVariance(
        char *ObjectId,
        long *TimeIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceTotalVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size TimeIndexLib;
        QuantLibAddin::cppToLibrary(*TimeIndex, TimeIndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->totalVariance(
                TimeIndexLib);

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
XLL_DEC double *qlPiecewiseConstantVarianceTotalVolatility(
        char *ObjectId,
        long *TimeIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceTotalVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size TimeIndexLib;
        QuantLibAddin::cppToLibrary(*TimeIndex, TimeIndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->totalVolatility(
                TimeIndexLib);

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
XLL_DEC double *qlPiecewiseConstantVarianceVariance(
        char *ObjectId,
        long *TimeIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size TimeIndexLib;
        QuantLibAddin::cppToLibrary(*TimeIndex, TimeIndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->variance(
                TimeIndexLib);

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
XLL_DEC OPER *qlPiecewiseConstantVarianceVariances(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceVariances"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->variances();

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
XLL_DEC OPER *qlPiecewiseConstantVarianceVolatilities(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceVolatilities"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->volatilities();

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
XLL_DEC double *qlPiecewiseConstantVarianceVolatility(
        char *ObjectId,
        long *TimeIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantVarianceVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size TimeIndexLib;
        QuantLibAddin::cppToLibrary(*TimeIndex, TimeIndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->volatility(
                TimeIndexLib);

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
