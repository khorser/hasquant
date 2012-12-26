
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Cristina Duminuco
 Copyright (C) 2006 Eric Ehlers
 
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
#include <qlo/swaption.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/vanillaswap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/exercise.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/exercise.hpp>
#include <qlo/valueobjects/vo_swaption.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlMakeSwaption(
        char *ObjectId,
        char *SwapIndex,
        char *OptionTenor,
        OPER *Strike,
        char *PricingEngineID,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMakeSwaption"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double StrikeCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Strike), "Strike", QuantLib::Null<QuantLib::Rate>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);
        std::string PricingEngineIDStrip = ObjectHandler::CallingRange::getStub(PricingEngineID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeSwaption(
                ObjectIdStrip,
                SwapIndexStrip,
                OptionTenor,
                StrikeCpp,
                PricingEngineIDStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swaption(
                valueObject,
                SwapIndexLibObjPtr,
                OptionTenorLib,
                StrikeCpp,
                PricingEngineIDLibObjPtr,
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
XLL_DEC char *qlSwaption(
        char *ObjectId,
        char *VanillaSwap,
        char *Exercise,
        char *SettlementType,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaption"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Settlement::Type SettlementTypeEnum =
            ObjectHandler::Create<QuantLib::Settlement::Type>()(SettlementType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(VanillaSwapLibObjPtr, VanillaSwap,
            QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::EuropeanExercise, QuantLib::EuropeanExercise)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string VanillaSwapStrip = ObjectHandler::CallingRange::getStub(VanillaSwap);
        std::string ExerciseStrip = ObjectHandler::CallingRange::getStub(Exercise);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaption(
                ObjectIdStrip,
                VanillaSwapStrip,
                ExerciseStrip,
                SettlementType,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swaption(
                valueObject,
                VanillaSwapLibObjPtr,
                ExerciseLibObjPtr,
                SettlementTypeEnum,
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
XLL_DEC double *qlSwaptionImpliedVolatility(
        char *ObjectId,
        double *Price,
        char *YieldCurve,
        OPER *Guess,
        OPER *Accuracy,
        OPER *MaxIter,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionImpliedVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", 0.10);

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-6);

        long MaxIterCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 100);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-6);

        QuantLib::Natural MaxIterLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*MaxIter), "MaxIter", 100);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Swaption, QuantLib::Swaption)

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->impliedVolatility(
                *Price,
                YieldCurveLibObj,
                GuessCpp,
                AccuracyLib,
                MaxIterLib);

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
XLL_DEC char *qlSwaptionSettlementType(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionSettlementType"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Swaption, QuantLib::Swaption)

        // invoke the member function

        QuantLib::Settlement::Type returnValue = ObjectIdLibObjPtr->settlementType();

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
XLL_DEC char *qlSwaptionType(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionType"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Swaption, QuantLib::Swaption)

        // invoke the member function

        QuantLib::VanillaSwap::Type returnValue = ObjectIdLibObjPtr->type();

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
