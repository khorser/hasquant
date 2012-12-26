
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
#include <qlo/products.hpp>
#include <qlo/payoffs.hpp>
#include <ql/models/marketmodels/products/onestep/onestepforwards.hpp>
#include <ql/models/marketmodels/products/onestep/onestepoptionlets.hpp>
#include <ql/models/marketmodels/products/multistep/multistepratchet.hpp>
#include <ql/models/marketmodels/products/multiproductcomposite.hpp>
#include <qlo/valueobjects/vo_products.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlMarketModelMultiProductComposite(
        char *ObjectId,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductComposite"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelMultiProductComposite(
                ObjectIdStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiProductComposite(
                valueObject,
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
XLL_DEC bool *qlMarketModelMultiProductCompositeAdd(
        char *ObjectId,
        char *Product,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductCompositeAdd"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MultiProductComposite, QuantLib::MultiProductComposite)

        OH_GET_UNDERLYING(ProductLibObj, Product,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->MarketModelComposite::add(
                ProductLibObj);

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
XLL_DEC bool *qlMarketModelMultiProductCompositeFinalize(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductCompositeFinalize"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MultiProductComposite, QuantLib::MultiProductComposite)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->finalize();

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
XLL_DEC long *qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // invoke the member function

        static long returnValue;
        returnValue = ObjectIdLibObjPtr->maxNumberOfCashFlowsPerProductPerStep();

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
XLL_DEC long *qlMarketModelMultiProductNumberOfProducts(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductNumberOfProducts"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // invoke the member function

        static long returnValue;
        returnValue = ObjectIdLibObjPtr->numberOfProducts();

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
XLL_DEC OPER *qlMarketModelMultiProductPossibleCashFlowTimes(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductPossibleCashFlowTimes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // invoke the member function

        std::vector<double> returnValue = ObjectIdLibObjPtr->possibleCashFlowTimes();

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
XLL_DEC OPER *qlMarketModelMultiProductSuggestedNumeraires(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiProductSuggestedNumeraires"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // invoke the member function

        std::vector<QuantLib::Size> returnValue = ObjectIdLibObjPtr->suggestedNumeraires();

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
XLL_DEC char *qlMarketModelMultiStepRatchet(
        char *ObjectId,
        OPER *RateTimes,
        OPER *Accruals,
        OPER *PaymentTimes,
        double *GearingOfFloor,
        double *GearingOfFixing,
        double *SpreadOfFloor,
        double *SpreadOfFixing,
        double *InitialFloor,
        bool *Payer,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelMultiStepRatchet"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        std::vector<double> AccrualsCpp =
            ObjectHandler::operToVector<double>(*Accruals, "Accruals");

        std::vector<double> PaymentTimesCpp =
            ObjectHandler::operToVector<double>(*PaymentTimes, "PaymentTimes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelMultiStepRatchet(
                ObjectIdStrip,
                RateTimesCpp,
                AccrualsCpp,
                PaymentTimesCpp,
                *GearingOfFloor,
                *GearingOfFixing,
                *SpreadOfFloor,
                *SpreadOfFixing,
                *InitialFloor,
                *Payer,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiStepRatchet(
                valueObject,
                RateTimesCpp,
                AccrualsCpp,
                PaymentTimesCpp,
                *GearingOfFloor,
                *GearingOfFixing,
                *SpreadOfFloor,
                *SpreadOfFixing,
                *InitialFloor,
                *Payer,
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
XLL_DEC char *qlMarketModelOneStepForwards(
        char *ObjectId,
        OPER *RateTimes,
        OPER *Accruals,
        OPER *PaymentTimes,
        OPER *Strikes,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelOneStepForwards"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        std::vector<double> AccrualsCpp =
            ObjectHandler::operToVector<double>(*Accruals, "Accruals");

        std::vector<double> PaymentTimesCpp =
            ObjectHandler::operToVector<double>(*PaymentTimes, "PaymentTimes");

        std::vector<double> StrikesCpp =
            ObjectHandler::operToVector<double>(*Strikes, "Strikes");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelOneStepForwards(
                ObjectIdStrip,
                RateTimesCpp,
                AccrualsCpp,
                PaymentTimesCpp,
                StrikesCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OneStepForwards(
                valueObject,
                RateTimesCpp,
                AccrualsCpp,
                PaymentTimesCpp,
                StrikesCpp,
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
XLL_DEC char *qlMarketModelOneStepOptionlets(
        char *ObjectId,
        OPER *RateTimes,
        OPER *Accruals,
        OPER *PaymentTimes,
        OPER *Payoffs,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketModelOneStepOptionlets"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimesCpp =
            ObjectHandler::operToVector<double>(*RateTimes, "RateTimes");

        std::vector<double> AccrualsCpp =
            ObjectHandler::operToVector<double>(*Accruals, "Accruals");

        std::vector<double> PaymentTimesCpp =
            ObjectHandler::operToVector<double>(*PaymentTimes, "PaymentTimes");

        std::vector<std::string> PayoffsCpp =
            ObjectHandler::operToVector<std::string>(*Payoffs, "Payoffs");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::Payoff> > PayoffsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::Payoff, QuantLib::Payoff>(PayoffsCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelOneStepOptionlets(
                ObjectIdStrip,
                RateTimesCpp,
                AccrualsCpp,
                PaymentTimesCpp,
                PayoffsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OneStepOptionlets(
                valueObject,
                RateTimesCpp,
                AccrualsCpp,
                PaymentTimesCpp,
                PayoffsLibObjPtr,
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
