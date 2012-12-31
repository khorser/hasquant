
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 
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
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/shortratemodels.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/marketmodels.hpp>
#include <qlo/processes.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolstructure.hpp>
#include <qlo/valueobjects/vo_pricingengines.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlAnalyticCapFloorEngine(
        char *ObjectId,
        char *HandleModel,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAnalyticCapFloorEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(HandleModelLibObjPtr, HandleModel,
            QuantLibAddin::AffineModel, QuantLib::AffineModel)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string HandleModelStrip = ObjectHandler::CallingRange::getStub(HandleModel);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine(
                ObjectIdStrip,
                HandleModelStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AnalyticCapFloorEngine(
                valueObject,
                HandleModelLibObjPtr,
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
XLL_DEC OPER *qlBachelierBlackFormula(
        char *OptionType,
        double *Strike,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBachelierBlackFormula"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::bachelierBlackFormula(
                OptionTypeEnum,
                *Strike,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib);

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
XLL_DEC OPER *qlBachelierBlackFormula2(
        char *Payoff,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBachelierBlackFormula2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::bachelierBlackFormula(
                PayoffLibObjPtr,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib);

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
XLL_DEC char *qlBinomialPricingEngine(
        char *ObjectId,
        char *EngineID,
        char *ProcessID,
        long *TimeSteps,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBinomialPricingEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ProcessIDLibObjPtr, ProcessID,
            QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ProcessIDStrip = ObjectHandler::CallingRange::getStub(ProcessID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBinomialPricingEngine(
                ObjectIdStrip,
                EngineID,
                ProcessIDStrip,
                *TimeSteps,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PricingEngine(
                valueObject,
                EngineID,
                ProcessIDLibObjPtr,
                *TimeSteps,
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
XLL_DEC char *qlBlackCalculator(
        char *ObjectId,
        char *OptionType,
        double *Strike,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculator"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCalculator(
                ObjectIdStrip,
                OptionType,
                *Strike,
                *AtmForwardValue,
                *StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCalculator(
                valueObject,
                OptionTypeEnum,
                *Strike,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib,
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
XLL_DEC char *qlBlackCalculator2(
        char *ObjectId,
        char *PayoffID,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculator2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string PayoffIDStrip = ObjectHandler::CallingRange::getStub(PayoffID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCalculator2(
                ObjectIdStrip,
                PayoffIDStrip,
                *AtmForwardValue,
                *StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCalculator(
                valueObject,
                PayoffIDLibObjPtr,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib,
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
XLL_DEC double *qlBlackCalculatorAlpha(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorAlpha"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->alpha();

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
XLL_DEC double *qlBlackCalculatorBeta(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorBeta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->beta();

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
XLL_DEC double *qlBlackCalculatorDelta(
        char *ObjectId,
        double *Spot,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorDelta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->delta(
                *Spot);

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
XLL_DEC double *qlBlackCalculatorDeltaForward(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorDeltaForward"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->deltaForward();

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
XLL_DEC double *qlBlackCalculatorDividendRho(
        char *ObjectId,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorDividendRho"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->dividendRho(
                *TimeToMaturity);

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
XLL_DEC double *qlBlackCalculatorElasticity(
        char *ObjectId,
        double *Spot,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorElasticity"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->elasticity(
                *Spot);

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
XLL_DEC double *qlBlackCalculatorElasticityForward(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorElasticityForward"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->elasticityForward();

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
XLL_DEC double *qlBlackCalculatorGamma(
        char *ObjectId,
        double *Spot,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorGamma"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->gamma(
                *Spot);

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
XLL_DEC double *qlBlackCalculatorGammaForward(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorGammaForward"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->gammaForward();

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
XLL_DEC double *qlBlackCalculatorItmAssetProbability(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorItmAssetProbability"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->itmAssetProbability();

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
XLL_DEC double *qlBlackCalculatorItmCashProbability(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorItmCashProbability"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->itmCashProbability();

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
XLL_DEC double *qlBlackCalculatorRho(
        char *ObjectId,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorRho"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->rho(
                *TimeToMaturity);

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
XLL_DEC double *qlBlackCalculatorStrikeSensitivity(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorStrikeSensitivity"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->strikeSensitivity();

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
XLL_DEC double *qlBlackCalculatorTheta(
        char *ObjectId,
        double *Spot,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorTheta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->theta(
                *Spot,
                *TimeToMaturity);

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
XLL_DEC double *qlBlackCalculatorThetaPerDay(
        char *ObjectId,
        double *Spot,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorThetaPerDay"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->thetaPerDay(
                *Spot,
                *TimeToMaturity);

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
XLL_DEC double *qlBlackCalculatorValue(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->value();

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
XLL_DEC double *qlBlackCalculatorVega(
        char *ObjectId,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCalculatorVega"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->vega(
                *TimeToMaturity);

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
XLL_DEC char *qlBlackCapFloorEngine(
        char *ObjectId,
        char *YieldCurve,
        char *VolTS,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCapFloorEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        OH_GET_OBJECT(VolTSCoerce, VolTS, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolTSLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    VolTSCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurve);
        std::string VolTSStrip = ObjectHandler::CallingRange::getStub(VolTS);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCapFloorEngine(
                ObjectIdStrip,
                YieldCurveStrip,
                VolTSStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCapFloorEngine(
                valueObject,
                YieldCurveLibObj,
                VolTSLibObj,
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
XLL_DEC char *qlBlackCapFloorEngine2(
        char *ObjectId,
        char *YieldCurve,
        OPER *Vol,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackCapFloorEngine2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t VolCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Vol));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> VolLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Vol), "Vol");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2(
                ObjectIdStrip,
                YieldCurveStrip,
                VolCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCapFloorEngine(
                valueObject,
                YieldCurveLibObj,
                VolLibObj,
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
XLL_DEC OPER *qlBlackFormula(
        char *OptionType,
        double *Strike,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormula"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormula(
                OptionTypeEnum,
                *Strike,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormula2(
        char *Payoff,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormula2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormula(
                PayoffLibObjPtr,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormulaCashItmProbability(
        char *OptionType,
        double *Strike,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaCashItmProbability"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaCashItmProbability(
                OptionTypeEnum,
                *Strike,
                *AtmForwardValue,
                *StdDev,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormulaCashItmProbability2(
        char *Payoff,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaCashItmProbability2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaCashItmProbability(
                PayoffLibObjPtr,
                *AtmForwardValue,
                *StdDev,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormulaImpliedStdDev(
        char *OptionType,
        double *Strike,
        double *AtmForwardValue,
        double *OptionPrice,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Guess,
        OPER *Accuracy,
        OPER *MaxIter,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaImpliedStdDev"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-6);

        long MaxIterCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 100);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        QuantLib::Real GuessLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-6);

        QuantLib::Natural MaxIterLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 100);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDev(
                OptionTypeEnum,
                *Strike,
                *AtmForwardValue,
                *OptionPrice,
                DeflatorLib,
                DisplacementLib,
                GuessLib,
                AccuracyLib,
                MaxIterLib);

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
XLL_DEC OPER *qlBlackFormulaImpliedStdDev2(
        char *PayoffID,
        double *AtmForwardValue,
        double *OptionPrice,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Guess,
        OPER *Accuracy,
        OPER *MaxIter,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaImpliedStdDev2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-6);

        long MaxIterCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 100);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        QuantLib::Real GuessLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-6);

        QuantLib::Natural MaxIterLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 100);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDev(
                PayoffIDLibObjPtr,
                *AtmForwardValue,
                *OptionPrice,
                DeflatorLib,
                DisplacementLib,
                GuessLib,
                AccuracyLib,
                MaxIterLib);

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
XLL_DEC OPER *qlBlackFormulaImpliedStdDevApproximation(
        char *OptionType,
        double *Strike,
        double *AtmForwardValue,
        double *OptionPrice,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaImpliedStdDevApproximation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDevApproximation(
                OptionTypeEnum,
                *Strike,
                *AtmForwardValue,
                *OptionPrice,
                DeflatorLib,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormulaImpliedStdDevApproximation2(
        char *Payoff,
        double *AtmForwardValue,
        double *OptionPrice,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaImpliedStdDevApproximation2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDevApproximation(
                PayoffLibObjPtr,
                *AtmForwardValue,
                *OptionPrice,
                DeflatorLib,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormulaStdDevDerivative(
        double *Strike,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaStdDevDerivative"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaStdDevDerivative(
                *Strike,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib,
                DisplacementLib);

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
XLL_DEC OPER *qlBlackFormulaStdDevDerivative2(
        char *PayoffID,
        double *AtmForwardValue,
        double *StdDev,
        OPER *Deflator,
        OPER *Displacement,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackFormulaStdDevDerivative2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        double DisplacementCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        QuantLib::Real DisplacementLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Displacement), "Displacement", 0.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::blackFormulaStdDevDerivative(
                PayoffIDLibObjPtr,
                *AtmForwardValue,
                *StdDev,
                DeflatorLib,
                DisplacementLib);

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
XLL_DEC char *qlBlackScholesCalculator(
        char *ObjectId,
        char *OptionType,
        double *Strike,
        double *Spot,
        OPER *Growth,
        double *StdDev,
        OPER *Deflator,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculator"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double GrowthCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Growth), "Growth", 1.0);

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackScholesCalculator(
                ObjectIdStrip,
                OptionType,
                *Strike,
                *Spot,
                GrowthCpp,
                *StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackScholesCalculator(
                valueObject,
                OptionTypeEnum,
                *Strike,
                *Spot,
                GrowthCpp,
                *StdDev,
                DeflatorLib,
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
XLL_DEC char *qlBlackScholesCalculator2(
        char *ObjectId,
        char *PayoffID,
        double *Spot,
        OPER *Growth,
        double *StdDev,
        OPER *Deflator,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculator2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double GrowthCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Growth), "Growth", 1.0);

        double DeflatorCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Deflator), "Deflator", 1.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string PayoffIDStrip = ObjectHandler::CallingRange::getStub(PayoffID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackScholesCalculator2(
                ObjectIdStrip,
                PayoffIDStrip,
                *Spot,
                GrowthCpp,
                *StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackScholesCalculator(
                valueObject,
                PayoffIDLibObjPtr,
                *Spot,
                GrowthCpp,
                *StdDev,
                DeflatorLib,
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
XLL_DEC double *qlBlackScholesCalculatorDelta(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculatorDelta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->delta();

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
XLL_DEC double *qlBlackScholesCalculatorElasticity(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculatorElasticity"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->elasticity();

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
XLL_DEC double *qlBlackScholesCalculatorGamma(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculatorGamma"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->gamma();

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
XLL_DEC double *qlBlackScholesCalculatorTheta(
        char *ObjectId,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculatorTheta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->theta(
                *TimeToMaturity);

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
XLL_DEC double *qlBlackScholesCalculatorThetaPerDay(
        char *ObjectId,
        double *TimeToMaturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackScholesCalculatorThetaPerDay"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->thetaPerDay(
                *TimeToMaturity);

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
XLL_DEC char *qlBlackSwaptionEngine(
        char *ObjectId,
        char *YieldCurve,
        char *VolTS,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackSwaptionEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        OH_GET_OBJECT(VolTSCoerce, VolTS, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> VolTSLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    VolTSCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurve);
        std::string VolTSStrip = ObjectHandler::CallingRange::getStub(VolTS);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackSwaptionEngine(
                ObjectIdStrip,
                YieldCurveStrip,
                VolTSStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackSwaptionEngine(
                valueObject,
                YieldCurveLibObj,
                VolTSLibObj,
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
XLL_DEC char *qlBlackSwaptionEngine2(
        char *ObjectId,
        char *YieldCurve,
        OPER *Vol,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBlackSwaptionEngine2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t VolCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Vol));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> VolLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Vol), "Vol");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2(
                ObjectIdStrip,
                YieldCurveStrip,
                VolCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackSwaptionEngine(
                valueObject,
                YieldCurveLibObj,
                VolLibObj,
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
XLL_DEC char *qlBondEngine(
        char *ObjectId,
        char *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

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
            new QuantLibAddin::ValueObjects::qlBondEngine(
                ObjectIdStrip,
                YieldCurveStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BondEngine(
                valueObject,
                YieldCurveLibObj,
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
XLL_DEC char *qlDiscountingSwapEngine(
        char *ObjectId,
        char *YieldCurve,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDiscountingSwapEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

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
            new QuantLibAddin::ValueObjects::qlDiscountingSwapEngine(
                ObjectIdStrip,
                YieldCurveStrip,
                IncludeSettlDateCpp,
                SettlementDateCpp,
                NpvDateCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscountingSwapEngine(
                valueObject,
                YieldCurveLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib,
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
XLL_DEC char *qlPricingEngine(
        char *ObjectId,
        char *EngineID,
        char *ProcessID,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPricingEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ProcessIDLibObjPtr, ProcessID,
            QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ProcessIDStrip = ObjectHandler::CallingRange::getStub(ProcessID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPricingEngine(
                ObjectIdStrip,
                EngineID,
                ProcessIDStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PricingEngine(
                valueObject,
                EngineID,
                ProcessIDLibObjPtr,
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
