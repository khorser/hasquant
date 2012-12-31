
/*  
 Copyright (C) 2009, 2011 Ferdinando Ametrano
 
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
#include <qlo/overnightindexedswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/ratehelpers.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>
#include <qlo/valueobjects/vo_overnightindexedswap.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlMakeDatedOIS(
        char *ObjectId,
        OPER *StartDate,
        OPER *EndDate,
        char *OvernightIndex,
        OPER *FixedRate,
        OPER *FixDayCounter,
        OPER *Spread,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMakeDatedOIS"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        double FixedRateCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FixedRate), "FixedRate", QuantLib::Null<QuantLib::Rate>());

        std::string FixDayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FixDayCounter), "FixDayCounter", "Actual/360");

        double SpreadCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Spread), "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate", QuantLib::Date());

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string OvernightIndexStrip = ObjectHandler::CallingRange::getStub(OvernightIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeDatedOIS(
                ObjectIdStrip,
                StartDateCpp,
                EndDateCpp,
                OvernightIndexStrip,
                FixedRateCpp,
                FixDayCounterCpp,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                StartDateLib,
                EndDateLib,
                OvernightIndexLibObjPtr,
                FixedRateCpp,
                FixDayCounterEnum,
                SpreadCpp,
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
XLL_DEC char *qlMakeOIS(
        char *ObjectId,
        char *SwapTenor,
        char *OvernightIndex,
        OPER *FixedRate,
        char *ForwardStart,
        OPER *FixDayCounter,
        OPER *Spread,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMakeOIS"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double FixedRateCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FixedRate), "FixedRate", QuantLib::Null<QuantLib::Rate>());

        std::string FixDayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FixDayCounter), "FixDayCounter", "Actual/360");

        double SpreadCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Spread), "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string OvernightIndexStrip = ObjectHandler::CallingRange::getStub(OvernightIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeOIS(
                ObjectIdStrip,
                SwapTenor,
                OvernightIndexStrip,
                FixedRateCpp,
                ForwardStart,
                FixDayCounterCpp,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                SwapTenorLib,
                OvernightIndexLibObjPtr,
                FixedRateCpp,
                ForwardStartLib,
                FixDayCounterEnum,
                SpreadCpp,
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
XLL_DEC char *qlOvernightIndexedSwap(
        char *ObjectId,
        OPER *PayerReceiver,
        OPER *Nominal,
        char *Schedule,
        OPER *FixedRate,
        char *FixDayCounter,
        char *OvernightIndex,
        OPER *Spread,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwap"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PayerReceiverCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PayerReceiver), "PayerReceiver", "Payer");

        std::vector<double> NominalCpp =
            ObjectHandler::operToVector<double>(*Nominal, "Nominal");

        double FixedRateCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FixedRate), "FixedRate", 0.0);

        double SpreadCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Spread), "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> NominalLib =
            ObjectHandler::operToVector<QuantLib::Real>(*Nominal, "Nominal");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::OvernightIndexedSwap::Type PayerReceiverEnum =
            ObjectHandler::Create<QuantLib::OvernightIndexedSwap::Type>()(PayerReceiverCpp);

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleLibObjPtr, Schedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleStrip = ObjectHandler::CallingRange::getStub(Schedule);
        std::string OvernightIndexStrip = ObjectHandler::CallingRange::getStub(OvernightIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOvernightIndexedSwap(
                ObjectIdStrip,
                PayerReceiverCpp,
                NominalCpp,
                ScheduleStrip,
                FixedRateCpp,
                FixDayCounter,
                OvernightIndexStrip,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                PayerReceiverEnum,
                NominalLib,
                ScheduleLibObjPtr,
                FixedRateCpp,
                FixDayCounterEnum,
                OvernightIndexLibObjPtr,
                SpreadCpp,
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
XLL_DEC double *qlOvernightIndexedSwapFairRate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFairRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->fairRate();

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
XLL_DEC double *qlOvernightIndexedSwapFairSpread(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFairSpread"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->fairSpread();

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
XLL_DEC char *qlOvernightIndexedSwapFixedDayCount(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFixedDayCount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        QuantLib::DayCounter returnValue = ObjectIdLibObjPtr->fixedDayCount();

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
XLL_DEC OPER *qlOvernightIndexedSwapFixedLegAnalysis(
        char *ObjectId,
        OPER *AfterDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFixedLegAnalysis"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t AfterDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*AfterDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*AfterDate), "AfterDate", QuantLib::Date());

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::OvernightIndexedSwap)

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->fixedLegAnalysis(
                AfterDateLib);

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
XLL_DEC double *qlOvernightIndexedSwapFixedLegBPS(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFixedLegBPS"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->fixedLegBPS();

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
XLL_DEC double *qlOvernightIndexedSwapFixedLegNPV(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFixedLegNPV"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->fixedLegNPV();

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
XLL_DEC double *qlOvernightIndexedSwapFixedRate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFixedRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->fixedRate();

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
XLL_DEC char *qlOvernightIndexedSwapFromOISRateHelper(
        char *ObjectId,
        char *OISRateHelper,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapFromOISRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(OISRateHelperLibObjPtr, OISRateHelper,
            QuantLibAddin::OISRateHelper, QuantLib::OISRateHelper)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string OISRateHelperStrip = ObjectHandler::CallingRange::getStub(OISRateHelper);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOvernightIndexedSwapFromOISRateHelper(
                ObjectIdStrip,
                OISRateHelperStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                OISRateHelperLibObjPtr,
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
XLL_DEC double *qlOvernightIndexedSwapNominal(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapNominal"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->nominal();

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
XLL_DEC OPER *qlOvernightIndexedSwapOvernightLegAnalysis(
        char *ObjectId,
        OPER *AfterDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapOvernightLegAnalysis"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t AfterDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*AfterDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*AfterDate), "AfterDate", QuantLib::Date());

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::OvernightIndexedSwap)

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->overnightLegAnalysis(
                AfterDateLib);

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
XLL_DEC double *qlOvernightIndexedSwapOvernightLegBPS(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapOvernightLegBPS"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->overnightLegBPS();

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
XLL_DEC double *qlOvernightIndexedSwapOvernightLegNPV(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapOvernightLegNPV"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->overnightLegNPV();

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
XLL_DEC double *qlOvernightIndexedSwapSpread(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapSpread"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->spread();

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
XLL_DEC char *qlOvernightIndexedSwapType(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndexedSwapType"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)

        // invoke the member function

        QuantLib::OvernightIndexedSwap::Type returnValue = ObjectIdLibObjPtr->type();

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
