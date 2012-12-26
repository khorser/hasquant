
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2007 Katiuscia Manzoni
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
#include <oh/enumerations/typefactory.hpp>
#include <qlo/sequencestatistics.hpp>
#include <qlo/correlation.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/models/marketmodels/correlations/expcorrelations.hpp>
#include <ql/models/marketmodels/historicalforwardratesanalysis.hpp>
#include <ql/models/marketmodels/historicalratesanalysis.hpp>
#include <qlo/valueobjects/vo_correlation.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlCotSwapFromFwdCorrelation(
        char *ObjectId,
        char *FwdCorr,
        char *CurveState,
        OPER *Displacement,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCotSwapFromFwdCorrelation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(FwdCorrLibObjPtr, FwdCorr,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string FwdCorrStrip = ObjectHandler::CallingRange::getStub(FwdCorr);
        std::string CurveStateStrip = ObjectHandler::CallingRange::getStub(CurveState);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCotSwapFromFwdCorrelation(
                ObjectIdStrip,
                FwdCorrStrip,
                CurveStateStrip,
                DisplacementCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CotSwapFromFwdCorrelation(
                valueObject,
                FwdCorrLibObjPtr,
                CurveStateLibObj,
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
XLL_DEC OPER *qlExponentialCorrelations(
        OPER *RateTimes,
        OPER *LongTermCorr,
        OPER *Beta,
        OPER *Gamma,
        double *Time,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlExponentialCorrelations"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        double LongTermCorrCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*LongTermCorr), "LongTermCorr", 0.0);

        double BetaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Beta), "Beta", 0.24);

        double GammaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Gamma), "Gamma", 0.333);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real LongTermCorrLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*LongTermCorr), "LongTermCorr", 0.0);

        QuantLib::Real BetaLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Beta), "Beta", 0.24);

        QuantLib::Real GammaLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Gamma), "Gamma", 0.333);

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::exponentialCorrelations(
                RateTimesCpp,
                LongTermCorrLib,
                BetaLib,
                GammaLib,
                *Time);

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
XLL_DEC char *qlExponentialForwardCorrelation(
        char *ObjectId,
        OPER *RateTimes,
        double *LongTermCorr,
        double *Beta,
        double *Gamma,
        OPER *Times,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlExponentialForwardCorrelation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        std::vector<double> TimesCpp =
            ObjectHandler::operToVector<double>(*Times, "Times");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlExponentialForwardCorrelation(
                ObjectIdStrip,
                RateTimesCpp,
                *LongTermCorr,
                *Beta,
                *Gamma,
                TimesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ExponentialForwardCorrelation(
                valueObject,
                RateTimesCpp,
                *LongTermCorr,
                *Beta,
                *Gamma,
                TimesCpp,
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
XLL_DEC char *qlHistoricalForwardRatesAnalysis(
        char *ObjectId,
        char *SequenceStats,
        OPER *StartDate,
        OPER *EndDate,
        char *Step,
        char *IborIndex,
        char *InitialGap,
        char *Horizon,
        OPER *IborIndexes,
        OPER *SwapIndexes,
        OPER *DayCounter,
        OPER *TraitsID,
        OPER *InterpolatorID,
        OPER *BootstrapAccuracy,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalForwardRatesAnalysis"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        std::vector<std::string> IborIndexesCpp =
            ObjectHandler::operToVector<std::string>(*IborIndexes, "IborIndexes");

        std::vector<std::string> SwapIndexesCpp =
            ObjectHandler::operToVector<std::string>(*SwapIndexes, "SwapIndexes");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        std::string TraitsIDCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*TraitsID), "TraitsID", "Discount");

        std::string InterpolatorIDCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*InterpolatorID), "InterpolatorID", "CubicSpline");

        double BootstrapAccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*BootstrapAccuracy), "BootstrapAccuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        QuantLib::Period StepLib;
        QuantLibAddin::cppToLibrary(Step, StepLib);

        QuantLib::Period InitialGapLib;
        QuantLibAddin::cppToLibrary(InitialGap, InitialGapLib);

        QuantLib::Period HorizonLib;
        QuantLibAddin::cppToLibrary(Horizon, HorizonLib);

        QuantLib::Real BootstrapAccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*BootstrapAccuracy), "BootstrapAccuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SequenceStatsLibObjPtr, SequenceStats,
            QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<boost::shared_ptr<QuantLib::IborIndex> > IborIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::IborIndex, QuantLib::IborIndex>(IborIndexesCpp);

        std::vector<boost::shared_ptr<QuantLib::SwapIndex> > SwapIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::SwapIndex, QuantLib::SwapIndex>(SwapIndexesCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SequenceStatsStrip = ObjectHandler::CallingRange::getStub(SequenceStats);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHistoricalForwardRatesAnalysis(
                ObjectIdStrip,
                SequenceStatsStrip,
                StartDateCpp,
                EndDateCpp,
                Step,
                IborIndexStrip,
                InitialGap,
                Horizon,
                IborIndexesCpp,
                SwapIndexesCpp,
                DayCounterCpp,
                TraitsIDCpp,
                InterpolatorIDCpp,
                BootstrapAccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HistoricalForwardRatesAnalysis(
                valueObject,
                SequenceStatsLibObjPtr,
                StartDateLib,
                EndDateLib,
                StepLib,
                IborIndexLibObjPtr,
                InitialGapLib,
                HorizonLib,
                IborIndexesLibObjPtr,
                SwapIndexesLibObjPtr,
                DayCounterEnum,
                TraitsIDCpp,
                InterpolatorIDCpp,
                BootstrapAccuracyLib,
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
XLL_DEC OPER *qlHistoricalForwardRatesAnalysisFailedDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalForwardRatesAnalysisFailedDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdLibObjPtr->failedDates();

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
XLL_DEC OPER *qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)

        // invoke the member function

        std::vector<std::string> returnValue = ObjectIdLibObjPtr->failedDatesErrorMessage();

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
XLL_DEC OPER *qlHistoricalForwardRatesAnalysisFixingPeriods(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalForwardRatesAnalysisFixingPeriods"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)

        // invoke the member function

        std::vector<QuantLib::Period> returnValue = ObjectIdLibObjPtr->fixingPeriods();

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
XLL_DEC OPER *qlHistoricalForwardRatesAnalysisSkippedDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalForwardRatesAnalysisSkippedDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdLibObjPtr->skippedDates();

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
XLL_DEC OPER *qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)

        // invoke the member function

        std::vector<std::string> returnValue = ObjectIdLibObjPtr->skippedDatesErrorMessage();

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
XLL_DEC char *qlHistoricalRatesAnalysis(
        char *ObjectId,
        char *SequenceStats,
        OPER *StartDate,
        OPER *EndDate,
        char *Step,
        OPER *InterestRateIndexes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalRatesAnalysis"));

        if (functionCall->calledByFunctionWizard())
            return 0;

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        std::vector<std::string> InterestRateIndexesCpp =
            ObjectHandler::operToVector<std::string>(*InterestRateIndexes, "InterestRateIndexes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        QuantLib::Period StepLib;
        QuantLibAddin::cppToLibrary(Step, StepLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SequenceStatsLibObjPtr, SequenceStats,
            QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)

        std::vector<boost::shared_ptr<QuantLib::InterestRateIndex> > InterestRateIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex>(InterestRateIndexesCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SequenceStatsStrip = ObjectHandler::CallingRange::getStub(SequenceStats);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHistoricalRatesAnalysis(
                ObjectIdStrip,
                SequenceStatsStrip,
                StartDateCpp,
                EndDateCpp,
                Step,
                InterestRateIndexesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HistoricalRatesAnalysis(
                valueObject,
                SequenceStatsLibObjPtr,
                StartDateLib,
                EndDateLib,
                StepLib,
                InterestRateIndexesLibObjPtr,
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
XLL_DEC OPER *qlHistoricalRatesAnalysisSkippedDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalRatesAnalysisSkippedDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalRatesAnalysis, QuantLib::HistoricalRatesAnalysis)

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdLibObjPtr->skippedDates();

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
XLL_DEC OPER *qlHistoricalRatesAnalysisSkippedDatesErrorMessage(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHistoricalRatesAnalysisSkippedDatesErrorMessage"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::HistoricalRatesAnalysis, QuantLib::HistoricalRatesAnalysis)

        // invoke the member function

        std::vector<std::string> returnValue = ObjectIdLibObjPtr->skippedDatesErrorMessage();

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
XLL_DEC char *qlMarketModelLmLinearExponentialCorrelationModel(
        char *ObjectId,
        long *Size,
        double *Rho,
        double *Beta,
        OPER *Factors,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelLmLinearExponentialCorrelationModel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        long FactorsCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*Factors), "Factors", QuantLib::Null<QuantLib::Size>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelLmLinearExponentialCorrelationModel(
                ObjectIdStrip,
                *Size,
                *Rho,
                *Beta,
                FactorsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LmLinearExponentialCorrelationModel(
                valueObject,
                *Size,
                *Rho,
                *Beta,
                FactorsCpp,
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
XLL_DEC OPER *qlPiecewiseConstantCorrelationCorrelation(
        char *ObjectId,
        long *TimeIndex,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantCorrelationCorrelation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size TimeIndexLib;
        QuantLibAddin::cppToLibrary(*TimeIndex, TimeIndexLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->correlation(
                TimeIndexLib);

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
XLL_DEC long *qlPiecewiseConstantCorrelationNumberOfRates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantCorrelationNumberOfRates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        // invoke the member function

        QuantLib::Size returnValue = ObjectIdLibObjPtr->numberOfRates();

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
XLL_DEC OPER *qlPiecewiseConstantCorrelationTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseConstantCorrelationTimes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->times();

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
XLL_DEC char *qlTimeHomogeneousForwardCorrelation(
        char *ObjectId,
        FP *FwdCorrMatrix,
        OPER *RateTimes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTimeHomogeneousForwardCorrelation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > FwdCorrMatrixCpp =
            ObjectHandler::fpToMatrix<double>(*FwdCorrMatrix);

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix FwdCorrMatrixLib =
            QuantLibXL::operToQlMatrix(*FwdCorrMatrix);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlTimeHomogeneousForwardCorrelation(
                ObjectIdStrip,
                FwdCorrMatrixCpp,
                RateTimesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TimeHomogeneousForwardCorrelation(
                valueObject,
                FwdCorrMatrixLib,
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
