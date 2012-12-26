
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
#include <qlo/ctsmmcapletcalibration.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/correlation.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/volatility.hpp>
#include <qlo/alphaform.hpp>
#include <ql/models/marketmodels/models/capletcoterminalalphacalibration.hpp>
#include <qlo/valueobjects/vo_ctsmmcapletcalibration.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlCTSMMCapletAlphaFormCalibration(
        char *ObjectId,
        char *Evolution,
        char *Correlations,
        OPER *SwapPiecewiseConstantVariances,
        OPER *CapletVols,
        char *CurveState,
        OPER *Displacement,
        OPER *AlphaInitial,
        OPER *AlphaMax,
        OPER *AlphaMin,
        OPER *MaximizeHomogeneity,
        OPER *AlphaForm,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletAlphaFormCalibration"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> SwapPiecewiseConstantVariancesCpp =
            ObjectHandler::operToVector<std::string>(*SwapPiecewiseConstantVariances, "SwapPiecewiseConstantVariances");

        std::vector<double> CapletVolsCpp =
            ObjectHandler::operToVector<double>(*CapletVols, "CapletVols");

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        std::vector<double> AlphaInitialCpp =
            ObjectHandler::operToVector<double>(*AlphaInitial, "AlphaInitial");

        std::vector<double> AlphaMaxCpp =
            ObjectHandler::operToVector<double>(*AlphaMax, "AlphaMax");

        std::vector<double> AlphaMinCpp =
            ObjectHandler::operToVector<double>(*AlphaMin, "AlphaMin");

        bool MaximizeHomogeneityCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*MaximizeHomogeneity), "MaximizeHomogeneity", true);

        std::string AlphaFormCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*AlphaForm), "AlphaForm", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> AlphaInitialLib =
            ObjectHandler::operToVector<QuantLib::Real>(*AlphaInitial, "AlphaInitial");

        std::vector<QuantLib::Real> AlphaMaxLib =
            ObjectHandler::operToVector<QuantLib::Real>(*AlphaMax, "AlphaMax");

        std::vector<QuantLib::Real> AlphaMinLib =
            ObjectHandler::operToVector<QuantLib::Real>(*AlphaMin, "AlphaMin");

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariancesCpp);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        OH_GET_REFERENCE_DEFAULT(AlphaFormLibObjPtr, AlphaFormCpp,
            QuantLibAddin::AlphaForm, QuantLib::AlphaForm)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EvolutionStrip = ObjectHandler::CallingRange::getStub(Evolution);
        std::string CorrelationsStrip = ObjectHandler::CallingRange::getStub(Correlations);
        std::string CurveStateStrip = ObjectHandler::CallingRange::getStub(CurveState);
        std::string AlphaFormStrip = ObjectHandler::CallingRange::getStub(AlphaFormCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCTSMMCapletAlphaFormCalibration(
                ObjectIdStrip,
                EvolutionStrip,
                CorrelationsStrip,
                SwapPiecewiseConstantVariancesCpp,
                CapletVolsCpp,
                CurveStateStrip,
                DisplacementCpp,
                AlphaInitialCpp,
                AlphaMaxCpp,
                AlphaMinCpp,
                MaximizeHomogeneityCpp,
                AlphaFormCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletAlphaFormCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVolsCpp,
                CurveStateLibObjPtr,
                DisplacementCpp,
                AlphaInitialLib,
                AlphaMaxLib,
                AlphaMinLib,
                MaximizeHomogeneityCpp,
                AlphaFormLibObjPtr,
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
XLL_DEC OPER *qlCTSMMCapletAlphaFormCalibrationAlpha(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletAlphaFormCalibrationAlpha"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletAlphaFormCalibration, QuantLib::CTSMMCapletAlphaFormCalibration)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->alpha();

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
XLL_DEC short int *qlCTSMMCapletCalibrationCalibrate(
        char *ObjectId,
        long *NumberOfFactors,
        OPER *MaxIter,
        OPER *Tol,
        OPER *InnerMaxIter,
        OPER *InnerTol,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationCalibrate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        long MaxIterCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 2);

        double TolCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Tol), "Tol", 0.0001);

        long InnerMaxIterCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*InnerMaxIter), "InnerMaxIter", 100);

        double InnerTolCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*InnerTol), "InnerTol", 1e-8);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural NumberOfFactorsLib;
        QuantLibAddin::cppToLibrary(*NumberOfFactors, NumberOfFactorsLib);

        QuantLib::Natural MaxIterLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 2);

        QuantLib::Real TolLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Tol), "Tol", 0.0001);

        QuantLib::Natural InnerMaxIterLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*InnerMaxIter), "InnerMaxIter", 100);

        QuantLib::Real InnerTolLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*InnerTol), "InnerTol", 1e-8);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        static short int returnValue;
        returnValue = ObjectIdLibObjPtr->calibrate(
                NumberOfFactorsLib,
                MaxIterLib,
                TolLib,
                InnerMaxIterLib,
                InnerTolLib);

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
XLL_DEC OPER *qlCTSMMCapletCalibrationCapletMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationCapletMaxError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->capletMaxError();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationCapletRmsError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationCapletRmsError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->capletRmsError();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationDeformationSize(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationDeformationSize"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->deformationSize();

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
XLL_DEC long *qlCTSMMCapletCalibrationFailures(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationFailures"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Natural returnValue = ObjectIdLibObjPtr->failures();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationMarketCapletVols(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationMarketCapletVols"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->mktCapletVols();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationMarketSwaptionVols(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationMarketSwaptionVols"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->mktSwaptionVols();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationModelCapletVols(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationModelCapletVols"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->mdlCapletVols();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationModelSwaptionVols(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationModelSwaptionVols"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->mdlSwaptionVols();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationSwapPseudoRoot(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationSwapPseudoRoot"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->swapPseudoRoot(
                IndexLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCTSMMCapletCalibrationSwaptionMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationSwaptionMaxError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->swaptionMaxError();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationSwaptionRmsError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationSwaptionRmsError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->swaptionRmsError();

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
XLL_DEC OPER *qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->timeDependentCalibratedSwaptionVols(
                IndexLib);

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
XLL_DEC OPER *qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->timeDependentUnCalibratedSwaptionVols(
                IndexLib);

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
XLL_DEC char *qlCTSMMCapletMaxHomogeneityCalibration(
        char *ObjectId,
        char *Evolution,
        char *Correlations,
        OPER *SwapPiecewiseConstantVariances,
        OPER *CapletVols,
        char *CurveState,
        OPER *Displacement,
        OPER *Caplet0Swaption1Priority,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletMaxHomogeneityCalibration"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> SwapPiecewiseConstantVariancesCpp =
            ObjectHandler::operToVector<std::string>(*SwapPiecewiseConstantVariances, "SwapPiecewiseConstantVariances");

        std::vector<double> CapletVolsCpp =
            ObjectHandler::operToVector<double>(*CapletVols, "CapletVols");

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        double Caplet0Swaption1PriorityCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Caplet0Swaption1Priority), "Caplet0Swaption1Priority", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Caplet0Swaption1PriorityLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Caplet0Swaption1Priority), "Caplet0Swaption1Priority", 1.0);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariancesCpp);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EvolutionStrip = ObjectHandler::CallingRange::getStub(Evolution);
        std::string CorrelationsStrip = ObjectHandler::CallingRange::getStub(Correlations);
        std::string CurveStateStrip = ObjectHandler::CallingRange::getStub(CurveState);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCTSMMCapletMaxHomogeneityCalibration(
                ObjectIdStrip,
                EvolutionStrip,
                CorrelationsStrip,
                SwapPiecewiseConstantVariancesCpp,
                CapletVolsCpp,
                CurveStateStrip,
                DisplacementCpp,
                Caplet0Swaption1PriorityCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletMaxHomogeneityCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVolsCpp,
                CurveStateLibObjPtr,
                DisplacementCpp,
                Caplet0Swaption1PriorityLib,
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
XLL_DEC char *qlCTSMMCapletOriginalCalibration(
        char *ObjectId,
        char *Evolution,
        char *Correlations,
        OPER *SwapPiecewiseConstantVariances,
        OPER *CapletVols,
        char *CurveState,
        OPER *Displacement,
        OPER *Alphas,
        OPER *LowestRoot,
        bool *UseFullApprox,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCTSMMCapletOriginalCalibration"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> SwapPiecewiseConstantVariancesCpp =
            ObjectHandler::operToVector<std::string>(*SwapPiecewiseConstantVariances, "SwapPiecewiseConstantVariances");

        std::vector<double> CapletVolsCpp =
            ObjectHandler::operToVector<double>(*CapletVols, "CapletVols");

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        std::vector<double> AlphasCpp =
            ObjectHandler::operToVector<double>(*Alphas, "Alphas");

        bool LowestRootCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*LowestRoot), "LowestRoot", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> AlphasLib =
            ObjectHandler::operToVector<QuantLib::Real>(*Alphas, "Alphas");

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariancesCpp);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EvolutionStrip = ObjectHandler::CallingRange::getStub(Evolution);
        std::string CorrelationsStrip = ObjectHandler::CallingRange::getStub(Correlations);
        std::string CurveStateStrip = ObjectHandler::CallingRange::getStub(CurveState);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCTSMMCapletOriginalCalibration(
                ObjectIdStrip,
                EvolutionStrip,
                CorrelationsStrip,
                SwapPiecewiseConstantVariancesCpp,
                CapletVolsCpp,
                CurveStateStrip,
                DisplacementCpp,
                AlphasCpp,
                LowestRootCpp,
                *UseFullApprox,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletOriginalCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVolsCpp,
                CurveStateLibObjPtr,
                DisplacementCpp,
                AlphasLib,
                LowestRootCpp,
                *UseFullApprox,
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
