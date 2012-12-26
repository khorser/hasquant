
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
#include <qlo/abcd.hpp>
#include <qlo/optimization.hpp>
#include <ql/termstructures/volatility/abcd.hpp>
#include <ql/termstructures/volatility/abcdcalibration.hpp>
#include <qlo/valueobjects/vo_abcd.hpp>
#include <qlo/loop/loop_abcd.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlAbcdCalibration(
        char *ObjectId,
        OPER *Times,
        OPER *BlackVols,
        OPER *A,
        OPER *B,
        OPER *C,
        OPER *D,
        OPER *AIsFixed,
        OPER *BIsFixed,
        OPER *CIsFixed,
        OPER *DIsFixed,
        OPER *VegaWeighted,
        OPER *EndCriteria,
        OPER *Method,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibration"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> TimesCpp =
            ObjectHandler::operToVector<double>(*Times, "Times");

        std::vector<double> BlackVolsCpp =
            ObjectHandler::operToVector<double>(*BlackVols, "BlackVols");

        double ACpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*A), "A", -0.06);

        double BCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*B), "B", 0.17);

        double CCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*C), "C", 0.54);

        double DCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*D), "D", 0.17);

        bool AIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AIsFixed), "AIsFixed", false);

        bool BIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*BIsFixed), "BIsFixed", false);

        bool CIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*CIsFixed), "CIsFixed", false);

        bool DIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*DIsFixed), "DIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeighted), "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Method), "Method", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string MethodStrip = ObjectHandler::CallingRange::getStub(MethodCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdCalibration(
                ObjectIdStrip,
                TimesCpp,
                BlackVolsCpp,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                AIsFixedCpp,
                BIsFixedCpp,
                CIsFixedCpp,
                DIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                MethodCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdCalibration(
                valueObject,
                TimesCpp,
                BlackVolsCpp,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                AIsFixedCpp,
                BIsFixedCpp,
                CIsFixedCpp,
                DIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
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
XLL_DEC double *qlAbcdCalibrationA(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationA"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->a();

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
XLL_DEC double *qlAbcdCalibrationB(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationB"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->b();

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
XLL_DEC double *qlAbcdCalibrationC(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationC"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->c();

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
XLL_DEC bool *qlAbcdCalibrationCompute(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationCompute"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->compute();

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
XLL_DEC double *qlAbcdCalibrationD(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationD"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->d();

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
XLL_DEC char *qlAbcdCalibrationEndCriteria(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationEndCriteria"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        QuantLib::EndCriteria::Type returnValue = ObjectIdLibObjPtr->endCriteria();

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
XLL_DEC double *qlAbcdCalibrationError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->error();

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
XLL_DEC OPER *qlAbcdCalibrationK(
        char *ObjectId,
        OPER *Times,
        OPER *BlackVols,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationK"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> TimesCpp =
            ObjectHandler::operToVector<double>(*Times, "Times");

        std::vector<double> BlackVolsCpp =
            ObjectHandler::operToVector<double>(*BlackVols, "BlackVols");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->k(
                TimesCpp,
                BlackVolsCpp);

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
XLL_DEC double *qlAbcdCalibrationMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdCalibrationMaxError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->maxError();

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
XLL_DEC double *qlAbcdDFunction(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdDFunction"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->d();

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
XLL_DEC char *qlAbcdFunction(
        char *ObjectId,
        OPER *A,
        OPER *B,
        OPER *C,
        OPER *D,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunction"));

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

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdFunction(
                ObjectIdStrip,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdFunction(
                valueObject,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
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
XLL_DEC double *qlAbcdFunctionA(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionA"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->a();

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
XLL_DEC double *qlAbcdFunctionB(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionB"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->b();

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
XLL_DEC double *qlAbcdFunctionC(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionC"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->c();

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
XLL_DEC OPER *qlAbcdFunctionCovariance(
        char *ObjectId,
        double *TMin,
        OPER *TMax,
        double *T,
        double *S,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionCovariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionCovarianceBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionCovarianceSignature)
                &QuantLib::AbcdFunction::covariance,
                ObjectIdLibObjPtr,
                *TMin,
                _1,
                *T,
                *S);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionCovarianceBind, double, double>
            (functionCall, bindObject, TMax, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlAbcdFunctionD(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionD"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->d();

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
XLL_DEC OPER *qlAbcdFunctionInstantaneousCovariance(
        char *ObjectId,
        OPER *U,
        double *T,
        double *S,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionInstantaneousCovariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionInstantaneousCovarianceBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousCovarianceSignature)
                &QuantLib::AbcdFunction::instantaneousCovariance,
                ObjectIdLibObjPtr,
                _1,
                *T,
                *S);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionInstantaneousCovarianceBind, double, double>
            (functionCall, bindObject, U, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdFunctionInstantaneousValue(
        char *ObjectId,
        OPER *U,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionInstantaneousValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionInstantaneousValueBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousValueSignature)
                &QuantLib::AbcdFunction::operator(),
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionInstantaneousValueBind, double, double>
            (functionCall, bindObject, U, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdFunctionInstantaneousVariance(
        char *ObjectId,
        OPER *U,
        double *T,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionInstantaneousVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionInstantaneousVarianceBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousVarianceSignature)
                &QuantLib::AbcdFunction::instantaneousVariance,
                ObjectIdLibObjPtr,
                _1,
                *T);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionInstantaneousVarianceBind, double, double>
            (functionCall, bindObject, U, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdFunctionInstantaneousVolatility(
        char *ObjectId,
        OPER *U,
        double *T,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionInstantaneousVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionInstantaneousVolatilityBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousVolatilitySignature)
                &QuantLib::AbcdFunction::instantaneousVolatility,
                ObjectIdLibObjPtr,
                _1,
                *T);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionInstantaneousVolatilityBind, double, double>
            (functionCall, bindObject, U, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlAbcdFunctionLongTermVolatility(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionLongTermVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->longTermVolatility();

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
XLL_DEC double *qlAbcdFunctionMaximumLocation(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionMaximumLocation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->maximumLocation();

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
XLL_DEC double *qlAbcdFunctionMaximumVolatility(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionMaximumVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->maximumVolatility();

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
XLL_DEC double *qlAbcdFunctionShortTermVolatility(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionShortTermVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->shortTermVolatility();

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
XLL_DEC OPER *qlAbcdFunctionVariance(
        char *ObjectId,
        double *TMin,
        OPER *TMax,
        double *T,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionVarianceBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionVarianceSignature)
                &QuantLib::AbcdFunction::variance,
                ObjectIdLibObjPtr,
                *TMin,
                _1,
                *T);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionVarianceBind, double, double>
            (functionCall, bindObject, TMax, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdFunctionVolatility(
        char *ObjectId,
        double *TMin,
        OPER *TMax,
        double *T,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdFunctionVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlAbcdFunctionVolatilityBind bindObject = 
            boost::bind((QuantLibAddin::qlAbcdFunctionVolatilitySignature)
                &QuantLib::AbcdFunction::volatility,
                ObjectIdLibObjPtr,
                *TMin,
                _1,
                *T);
        ObjectHandler::loop
            <QuantLibAddin::qlAbcdFunctionVolatilityBind, double, double>
            (functionCall, bindObject, TMax, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
