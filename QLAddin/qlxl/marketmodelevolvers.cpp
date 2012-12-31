
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
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/browniangenerators.hpp>
#include <qlo/marketmodels.hpp>
#include <ql/models/marketmodels/evolver.hpp>
#include <qlo/valueobjects/vo_marketmodelevolvers.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlForwardRateIpc(
        char *ObjectId,
        char *MarketModel,
        char *BrownianGeneratorFactory,
        OPER *Numeraires,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardRateIpc"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<long> NumerairesCpp =
            ObjectHandler::operToVector<long>(*Numeraires, "Numeraires");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Size> NumerairesLib = 
            QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelLibObjPtr, MarketModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, BrownianGeneratorFactory,
            QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string MarketModelStrip = ObjectHandler::CallingRange::getStub(MarketModel);
        std::string BrownianGeneratorFactoryStrip = ObjectHandler::CallingRange::getStub(BrownianGeneratorFactory);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardRateIpc(
                ObjectIdStrip,
                MarketModelStrip,
                BrownianGeneratorFactoryStrip,
                NumerairesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LogNormalFwdRateIpc(
                valueObject,
                MarketModelLibObjPtr,
                BrownianGeneratorFactoryLibObj,
                NumerairesLib,
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
XLL_DEC char *qlForwardRateNormalPc(
        char *ObjectId,
        char *MarketModel,
        char *BrownianGeneratorFactory,
        OPER *Numeraires,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardRateNormalPc"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<long> NumerairesCpp =
            ObjectHandler::operToVector<long>(*Numeraires, "Numeraires");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Size> NumerairesLib = 
            QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelLibObjPtr, MarketModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, BrownianGeneratorFactory,
            QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string MarketModelStrip = ObjectHandler::CallingRange::getStub(MarketModel);
        std::string BrownianGeneratorFactoryStrip = ObjectHandler::CallingRange::getStub(BrownianGeneratorFactory);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardRateNormalPc(
                ObjectIdStrip,
                MarketModelStrip,
                BrownianGeneratorFactoryStrip,
                NumerairesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::NormalFwdRatePc(
                valueObject,
                MarketModelLibObjPtr,
                BrownianGeneratorFactoryLibObj,
                NumerairesLib,
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
XLL_DEC char *qlForwardRatePc(
        char *ObjectId,
        char *MarketModel,
        char *BrownianGeneratorFactory,
        OPER *Numeraires,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardRatePc"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<long> NumerairesCpp =
            ObjectHandler::operToVector<long>(*Numeraires, "Numeraires");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Size> NumerairesLib = 
            QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelLibObjPtr, MarketModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, BrownianGeneratorFactory,
            QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string MarketModelStrip = ObjectHandler::CallingRange::getStub(MarketModel);
        std::string BrownianGeneratorFactoryStrip = ObjectHandler::CallingRange::getStub(BrownianGeneratorFactory);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardRatePc(
                ObjectIdStrip,
                MarketModelStrip,
                BrownianGeneratorFactoryStrip,
                NumerairesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LogNormalFwdRatePc(
                valueObject,
                MarketModelLibObjPtr,
                BrownianGeneratorFactoryLibObj,
                NumerairesLib,
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
XLL_DEC double *qlMarketModelEvolverAdvanceStep(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelEvolverAdvanceStep"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->advanceStep();

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
XLL_DEC long *qlMarketModelEvolverCurrentStep(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelEvolverCurrentStep"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)

        // invoke the member function

        QuantLib::Size returnValue = ObjectIdLibObjPtr->currentStep();

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
XLL_DEC OPER *qlMarketModelEvolverNumeraires(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelEvolverNumeraires"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)

        // invoke the member function

        std::vector<QuantLib::Size> returnValue = ObjectIdLibObjPtr->numeraires();

        // convert and return the return value

        std::vector<long> returnValVec =
            QuantLibAddin::convertVector<QuantLib::Size, long>(returnValue);
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
XLL_DEC double *qlMarketModelEvolverStartNewPath(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelEvolverStartNewPath"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->startNewPath();

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
