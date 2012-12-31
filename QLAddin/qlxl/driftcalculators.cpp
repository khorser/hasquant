
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
#include <qlo/driftcalculators.hpp>
#include <qlo/curvestate.hpp>
#include <ql/models/marketmodels/curvestates/cmswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/coterminalswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/lmmcurvestate.hpp>
#include <qlo/valueobjects/vo_driftcalculators.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlCMSMMDriftCalculator(
        char *ObjectId,
        FP *Pseudo_square_root,
        OPER *Displacements,
        OPER *Taus,
        long *Numeraire,
        long *Alive,
        long *SpanningFwds,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCMSMMDriftCalculator"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_rootCpp =
            ObjectHandler::fpToMatrix<double>(*Pseudo_square_root);

        std::vector<double> DisplacementsCpp =
            ObjectHandler::operToVector<double>(*Displacements, "Displacements");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibXL::operToQlMatrix(*Pseudo_square_root);

        QuantLib::Size NumeraireLib;
        QuantLibAddin::cppToLibrary(*Numeraire, NumeraireLib);

        QuantLib::Size AliveLib;
        QuantLibAddin::cppToLibrary(*Alive, AliveLib);

        QuantLib::Size SpanningFwdsLib;
        QuantLibAddin::cppToLibrary(*SpanningFwds, SpanningFwdsLib);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCMSMMDriftCalculator(
                ObjectIdStrip,
                Pseudo_square_rootCpp,
                DisplacementsCpp,
                TausCpp,
                *Numeraire,
                *Alive,
                *SpanningFwds,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CMSMMDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                DisplacementsCpp,
                TausCpp,
                NumeraireLib,
                AliveLib,
                SpanningFwdsLib,
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
XLL_DEC OPER *qlCMSMMDriftCalculatorCompute(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCMSMMDriftCalculatorCompute"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::CMSMMDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CMSwapCurveState, QuantLib::CMSwapCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->compute(
                CurveStateLibObj);

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
XLL_DEC char *qlLMMDriftCalculator(
        char *ObjectId,
        FP *Pseudo_square_root,
        OPER *Displacements,
        OPER *Taus,
        long *Numeraire,
        long *Alive,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMDriftCalculator"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_rootCpp =
            ObjectHandler::fpToMatrix<double>(*Pseudo_square_root);

        std::vector<double> DisplacementsCpp =
            ObjectHandler::operToVector<double>(*Displacements, "Displacements");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibXL::operToQlMatrix(*Pseudo_square_root);

        QuantLib::Size NumeraireLib;
        QuantLibAddin::cppToLibrary(*Numeraire, NumeraireLib);

        QuantLib::Size AliveLib;
        QuantLibAddin::cppToLibrary(*Alive, AliveLib);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLMMDriftCalculator(
                ObjectIdStrip,
                Pseudo_square_rootCpp,
                DisplacementsCpp,
                TausCpp,
                *Numeraire,
                *Alive,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LMMDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                DisplacementsCpp,
                TausCpp,
                NumeraireLib,
                AliveLib,
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
XLL_DEC OPER *qlLMMDriftCalculatorCompute(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMDriftCalculatorCompute"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::LMMDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->compute(
                CurveStateLibObj);

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
XLL_DEC OPER *qlLMMDriftCalculatorComputePlain(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMDriftCalculatorComputePlain"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::LMMDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->computePlain(
                CurveStateLibObj);

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
XLL_DEC OPER *qlLMMDriftCalculatorComputeReduced(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMDriftCalculatorComputeReduced"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::LMMDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->computeReduced(
                CurveStateLibObj);

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
XLL_DEC char *qlLMMNormalDriftCalculator(
        char *ObjectId,
        FP *Pseudo_square_root,
        OPER *Taus,
        long *Numeraire,
        long *Alive,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMNormalDriftCalculator"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_rootCpp =
            ObjectHandler::fpToMatrix<double>(*Pseudo_square_root);

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibXL::operToQlMatrix(*Pseudo_square_root);

        QuantLib::Size NumeraireLib;
        QuantLibAddin::cppToLibrary(*Numeraire, NumeraireLib);

        QuantLib::Size AliveLib;
        QuantLibAddin::cppToLibrary(*Alive, AliveLib);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLMMNormalDriftCalculator(
                ObjectIdStrip,
                Pseudo_square_rootCpp,
                TausCpp,
                *Numeraire,
                *Alive,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LMMNormalDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                TausCpp,
                NumeraireLib,
                AliveLib,
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
XLL_DEC OPER *qlLMMNormalDriftCalculatorCompute(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMNormalDriftCalculatorCompute"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::LMMNormalDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->compute(
                CurveStateLibObj);

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
XLL_DEC OPER *qlLMMNormalDriftCalculatorComputePlain(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMNormalDriftCalculatorComputePlain"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::LMMNormalDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->computePlain(
                CurveStateLibObj);

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
XLL_DEC OPER *qlLMMNormalDriftCalculatorComputeReduced(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLMMNormalDriftCalculatorComputeReduced"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::LMMNormalDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->computeReduced(
                CurveStateLibObj);

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
XLL_DEC char *qlSMMDriftCalculator(
        char *ObjectId,
        FP *Pseudo_square_root,
        OPER *Displacements,
        OPER *Taus,
        long *Numeraire,
        long *Alive,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSMMDriftCalculator"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_rootCpp =
            ObjectHandler::fpToMatrix<double>(*Pseudo_square_root);

        std::vector<double> DisplacementsCpp =
            ObjectHandler::operToVector<double>(*Displacements, "Displacements");

        std::vector<double> TausCpp =
            ObjectHandler::operToVector<double>(*Taus, "Taus");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibXL::operToQlMatrix(*Pseudo_square_root);

        QuantLib::Size NumeraireLib;
        QuantLibAddin::cppToLibrary(*Numeraire, NumeraireLib);

        QuantLib::Size AliveLib;
        QuantLibAddin::cppToLibrary(*Alive, AliveLib);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSMMDriftCalculator(
                ObjectIdStrip,
                Pseudo_square_rootCpp,
                DisplacementsCpp,
                TausCpp,
                *Numeraire,
                *Alive,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SMMDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                DisplacementsCpp,
                TausCpp,
                NumeraireLib,
                AliveLib,
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
XLL_DEC OPER *qlSMMDriftCalculatorCompute(
        char *ObjectId,
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSMMDriftCalculatorCompute"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SMMDriftCalculator)

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CoterminalSwapCurveState, QuantLib::CoterminalSwapCurveState)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdObjPtr->compute(
                CurveStateLibObj);

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
