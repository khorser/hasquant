
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
#include <qlo/marketmodels.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/correlation.hpp>
#include <qlo/ctsmmcapletcalibration.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <ql/models/marketmodels/models/fwdperiodadapter.hpp>
#include <ql/models/marketmodels/swapforwardmappings.hpp>
#include <ql/models/marketmodels/models/capletcoterminalalphacalibration.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <qlo/valueobjects/vo_marketmodels.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlAbcdVol(
        char *ObjectId,
        double *A,
        double *B,
        double *C,
        double *D,
        OPER *Ks,
        char *Correlations,
        char *EvolutionDescription,
        long *Factors,
        OPER *InitialRates,
        OPER *Displacements,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdVol"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> KsCpp =
            ObjectHandler::operToVector<double>(*Ks, "Ks");

        std::vector<double> InitialRatesCpp =
            ObjectHandler::operToVector<double>(*InitialRates, "InitialRates");

        std::vector<double> DisplacementsCpp =
            ObjectHandler::operToVector<double>(*Displacements, "Displacements");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(EvolutionDescriptionLibObj, EvolutionDescription,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string CorrelationsStrip = ObjectHandler::CallingRange::getStub(Correlations);
        std::string EvolutionDescriptionStrip = ObjectHandler::CallingRange::getStub(EvolutionDescription);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdVol(
                ObjectIdStrip,
                *A,
                *B,
                *C,
                *D,
                KsCpp,
                CorrelationsStrip,
                EvolutionDescriptionStrip,
                *Factors,
                InitialRatesCpp,
                DisplacementsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdVol(
                valueObject,
                *A,
                *B,
                *C,
                *D,
                KsCpp,
                CorrelationsLibObjPtr,
                EvolutionDescriptionLibObj,
                *Factors,
                InitialRatesCpp,
                DisplacementsCpp,
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
XLL_DEC OPER *qlAnnuity(
        char *CurveState,
        long *StartIndex,
        long *EndIndex,
        OPER *NumeraireIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAnnuity"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        long NumeraireIndexCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*NumeraireIndex), "NumeraireIndex", 0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size StartIndexLib;
        QuantLibAddin::cppToLibrary(*StartIndex, StartIndexLib);

        QuantLib::Size EndIndexLib;
        QuantLibAddin::cppToLibrary(*EndIndex, EndIndexLib);

        QuantLib::Size NumeraireIndexLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*NumeraireIndex), "NumeraireIndex", 0);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::SwapForwardMappings::annuity(
                CurveStateLibObj,
                StartIndexLib,
                EndIndexLib,
                NumeraireIndexLib);

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
XLL_DEC OPER *qlCmSwapForwardJacobian(
        char *CurveState,
        long *SpanningForwards,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCmSwapForwardJacobian"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(*SpanningForwards, SpanningForwardsLib);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::SwapForwardMappings::cmSwapForwardJacobian(
                CurveStateLibObj,
                SpanningForwardsLib);

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
XLL_DEC OPER *qlCmSwapZedMatrix(
        char *CurveState,
        long *SpanningForwards,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCmSwapZedMatrix"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(*SpanningForwards, SpanningForwardsLib);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::SwapForwardMappings::cmSwapZedMatrix(
                CurveStateLibObj,
                SpanningForwardsLib,
                DisplacementCpp);

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
XLL_DEC OPER *qlCoinitialSwapForwardJacobian(
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoinitialSwapForwardJacobian"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::SwapForwardMappings::coinitialSwapForwardJacobian(
                CurveStateLibObj);

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
XLL_DEC OPER *qlCoinitialSwapZedMatrix(
        char *CurveState,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoinitialSwapZedMatrix"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::SwapForwardMappings::coinitialSwapZedMatrix(
                CurveStateLibObj,
                DisplacementCpp);

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
XLL_DEC char *qlCotSwapToFwdAdapter(
        char *ObjectId,
        char *CoterminalModel,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCotSwapToFwdAdapter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CoterminalModelLibObjPtr, CoterminalModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string CoterminalModelStrip = ObjectHandler::CallingRange::getStub(CoterminalModel);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCotSwapToFwdAdapter(
                ObjectIdStrip,
                CoterminalModelStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CotSwapToFwdAdapter(
                valueObject,
                CoterminalModelLibObjPtr,
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
XLL_DEC OPER *qlCoterminalSwapForwardJacobian(
        char *CurveState,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoterminalSwapForwardJacobian"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::SwapForwardMappings::coterminalSwapForwardJacobian(
                CurveStateLibObj);

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
XLL_DEC OPER *qlCoterminalSwapZedMatrix(
        char *CurveState,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCoterminalSwapZedMatrix"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::SwapForwardMappings::coterminalSwapZedMatrix(
                CurveStateLibObj,
                DisplacementCpp);

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
XLL_DEC char *qlFlatVol(
        char *ObjectId,
        OPER *Volatilities,
        char *Correlations,
        char *EvolutionDescription,
        long *Factors,
        OPER *InitialRates,
        OPER *Displacements,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFlatVol"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> VolatilitiesCpp =
            ObjectHandler::operToVector<double>(*Volatilities, "Volatilities");

        std::vector<double> InitialRatesCpp =
            ObjectHandler::operToVector<double>(*InitialRates, "InitialRates");

        std::vector<double> DisplacementsCpp =
            ObjectHandler::operToVector<double>(*Displacements, "Displacements");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(EvolutionDescriptionLibObj, EvolutionDescription,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string CorrelationsStrip = ObjectHandler::CallingRange::getStub(Correlations);
        std::string EvolutionDescriptionStrip = ObjectHandler::CallingRange::getStub(EvolutionDescription);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatVol(
                ObjectIdStrip,
                VolatilitiesCpp,
                CorrelationsStrip,
                EvolutionDescriptionStrip,
                *Factors,
                InitialRatesCpp,
                DisplacementsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatVol(
                valueObject,
                VolatilitiesCpp,
                CorrelationsLibObjPtr,
                EvolutionDescriptionLibObj,
                *Factors,
                InitialRatesCpp,
                DisplacementsCpp,
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
XLL_DEC char *qlFlatVolFactory(
        char *ObjectId,
        double *LongTermCorr,
        double *Beta,
        OPER *Times,
        OPER *Volatilities,
        char *YieldCurve,
        OPER *Displacement,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFlatVolFactory"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> TimesCpp =
            ObjectHandler::operToVector<double>(*Times, "Times");

        std::vector<double> VolatilitiesCpp =
            ObjectHandler::operToVector<double>(*Volatilities, "Volatilities");

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatVolFactory(
                ObjectIdStrip,
                *LongTermCorr,
                *Beta,
                TimesCpp,
                VolatilitiesCpp,
                YieldCurveStrip,
                DisplacementCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatVolFactory(
                valueObject,
                *LongTermCorr,
                *Beta,
                TimesCpp,
                VolatilitiesCpp,
                YieldCurveLibObj,
                DisplacementCpp,
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
XLL_DEC char *qlFwdPeriodAdapter(
        char *ObjectId,
        char *LargeModel,
        long *Period,
        long *Offset,
        OPER *Displacements,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFwdPeriodAdapter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> DisplacementsCpp =
            ObjectHandler::operToVector<double>(*Displacements, "Displacements");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size PeriodLib;
        QuantLibAddin::cppToLibrary(*Period, PeriodLib);

        QuantLib::Size OffsetLib;
        QuantLibAddin::cppToLibrary(*Offset, OffsetLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(LargeModelLibObjPtr, LargeModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string LargeModelStrip = ObjectHandler::CallingRange::getStub(LargeModel);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFwdPeriodAdapter(
                ObjectIdStrip,
                LargeModelStrip,
                *Period,
                *Offset,
                DisplacementsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FwdPeriodAdapter(
                valueObject,
                LargeModelLibObjPtr,
                PeriodLib,
                OffsetLib,
                DisplacementsCpp,
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
XLL_DEC char *qlFwdToCotSwapAdapter(
        char *ObjectId,
        char *ForwardModel,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFwdToCotSwapAdapter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ForwardModelLibObjPtr, ForwardModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ForwardModelStrip = ObjectHandler::CallingRange::getStub(ForwardModel);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFwdToCotSwapAdapter(
                ObjectIdStrip,
                ForwardModelStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FwdToCotSwapAdapter(
                valueObject,
                ForwardModelLibObjPtr,
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
XLL_DEC OPER *qlMarketModelCovariance(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelCovariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->covariance(
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
XLL_DEC OPER *qlMarketModelDisplacements(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelDisplacements"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->displacements();

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
XLL_DEC OPER *qlMarketModelInitialRates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelInitialRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->initialRates();

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
XLL_DEC long *qlMarketModelNumberOfFactors(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelNumberOfFactors"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        static long returnValue;
        returnValue = ObjectIdLibObjPtr->numberOfFactors();

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
XLL_DEC long *qlMarketModelNumberOfRates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelNumberOfRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        static long returnValue;
        returnValue = ObjectIdLibObjPtr->numberOfRates();

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
XLL_DEC long *qlMarketModelNumberOfSteps(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelNumberOfSteps"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        static long returnValue;
        returnValue = ObjectIdLibObjPtr->numberOfSteps();

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
XLL_DEC OPER *qlMarketModelPseudoRoot(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelPseudoRoot"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->pseudoRoot(
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
XLL_DEC OPER *qlMarketModelTimeDependentVolatility(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelTimeDependentVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->timeDependentVolatility(
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
XLL_DEC OPER *qlMarketModelTotalCovariance(
        char *ObjectId,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelTotalCovariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->totalCovariance(
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
XLL_DEC char *qlPseudoRootFacade(
        char *ObjectId,
        char *Calibrator,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPseudoRootFacade"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CalibratorLibObjPtr, Calibrator,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string CalibratorStrip = ObjectHandler::CallingRange::getStub(Calibrator);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPseudoRootFacade(
                ObjectIdStrip,
                CalibratorStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PseudoRootFacade(
                valueObject,
                CalibratorLibObjPtr,
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
XLL_DEC OPER *qlRateInstVolDifferences(
        char *MarketModel1,
        char *MarketModel2,
        long *Index,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateInstVolDifferences"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size IndexLib;
        QuantLibAddin::cppToLibrary(*Index, IndexLib);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(MarketModel1LibObj, MarketModel1,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(MarketModel2LibObj, MarketModel2,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the utility function

        std::vector<QuantLib::Real> returnValue = QuantLibAddin::qlRateInstVolDifferences(
                MarketModel1LibObj,
                MarketModel2LibObj,
                IndexLib);

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
XLL_DEC OPER *qlRateVolDifferences(
        char *MarketModel1,
        char *MarketModel2,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateVolDifferences"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_UNDERLYING(MarketModel1LibObj, MarketModel1,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(MarketModel2LibObj, MarketModel2,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // invoke the utility function

        std::vector<QuantLib::Real> returnValue = QuantLibAddin::qlRateVolDifferences(
                MarketModel1LibObj,
                MarketModel2LibObj);

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
XLL_DEC OPER *qlSwapDerivative(
        char *CurveState,
        long *StartIndex,
        long *EndIndex,
        OPER *FwdRateIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapDerivative"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        long FwdRateIndexCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*FwdRateIndex), "FwdRateIndex", 0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size StartIndexLib;
        QuantLibAddin::cppToLibrary(*StartIndex, StartIndexLib);

        QuantLib::Size EndIndexLib;
        QuantLibAddin::cppToLibrary(*EndIndex, EndIndexLib);

        QuantLib::Size FwdRateIndexLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*FwdRateIndex), "FwdRateIndex", 0);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::SwapForwardMappings::swapDerivative(
                CurveStateLibObj,
                StartIndexLib,
                EndIndexLib,
                FwdRateIndexLib);

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
