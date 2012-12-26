
/*  
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2006, 2007, 2008, 2009 Ferdinando Ametrano
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet
 
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
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <qlo/valueobjects/vo_ratehelpers.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlBondHelper(
        char *ObjectId,
        OPER *CleanPrice,
        char *Bond,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t CleanPriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*CleanPrice));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> CleanPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*CleanPrice), "CleanPrice");

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BondStrip = ObjectHandler::CallingRange::getStub(Bond);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBondHelper(
                ObjectIdStrip,
                CleanPriceCpp,
                BondStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BondHelper(
                valueObject,
                CleanPriceLibObj,
                BondLibObjPtr,
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
XLL_DEC char *qlDatedOISRateHelper(
        char *ObjectId,
        OPER *StartDate,
        OPER *EndDate,
        OPER *FixedRate,
        char *ONIndex,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDatedOISRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        ObjectHandler::property_t FixedRateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*FixedRate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FixedRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*FixedRate), "FixedRate");

        OH_GET_REFERENCE(ONIndexLibObjPtr, ONIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ONIndexStrip = ObjectHandler::CallingRange::getStub(ONIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDatedOISRateHelper(
                ObjectIdStrip,
                StartDateCpp,
                EndDateCpp,
                FixedRateCpp,
                ONIndexStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DatedOISRateHelper(
                valueObject,
                StartDateLib,
                EndDateLib,
                FixedRateLibObj,
                ONIndexLibObjPtr,
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
XLL_DEC char *qlDepositRateHelper(
        char *ObjectId,
        OPER *Rate,
        char *IborIndex,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDepositRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Rate), "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDepositRateHelper(
                ObjectIdStrip,
                RateCpp,
                IborIndexStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DepositRateHelper(
                valueObject,
                RateLibObj,
                IborIndexLibObjPtr,
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
XLL_DEC char *qlDepositRateHelper2(
        char *ObjectId,
        OPER *Rate,
        char *Tenor,
        long *FixingDays,
        char *Calendar,
        char *Convention,
        bool *EndOfMonth,
        char *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDepositRateHelper2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(*FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Rate), "Rate");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDepositRateHelper2(
                ObjectIdStrip,
                RateCpp,
                Tenor,
                *FixingDays,
                Calendar,
                Convention,
                *EndOfMonth,
                DayCounter,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DepositRateHelper(
                valueObject,
                RateLibObj,
                TenorLib,
                FixingDaysLib,
                CalendarEnum,
                ConventionEnum,
                *EndOfMonth,
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
XLL_DEC char *qlFixedRateBondHelper(
        char *ObjectId,
        OPER *CleanPrice,
        long *SettlementDays,
        OPER *FaceAmount,
        char *ScheduleID,
        OPER *Coupons,
        char *DayCounter,
        OPER *PaymentBDC,
        OPER *Redemption,
        OPER *IssueDate,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFixedRateBondHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t CleanPriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*CleanPrice));

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        std::vector<double> CouponsCpp =
            ObjectHandler::operToVector<double>(*Coupons, "Coupons");

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100.0);

        ObjectHandler::property_t IssueDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IssueDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(*SettlementDays, SettlementDaysLib);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> CleanPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*CleanPrice), "CleanPrice");

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateBondHelper(
                ObjectIdStrip,
                CleanPriceCpp,
                *SettlementDays,
                FaceAmountCpp,
                ScheduleIDStrip,
                CouponsCpp,
                DayCounter,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDateCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBondHelper(
                valueObject,
                CleanPriceLibObj,
                SettlementDaysLib,
                FaceAmountCpp,
                ScheduleIDLibObjPtr,
                CouponsCpp,
                DayCounterEnum,
                PaymentBDCEnum,
                RedemptionCpp,
                IssueDateLib,
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
XLL_DEC char *qlFraRateHelper(
        char *ObjectId,
        OPER *Rate,
        char *PeriodToStart,
        char *IborIndex,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFraRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodToStartLib;
        QuantLibAddin::cppToLibrary(PeriodToStart, PeriodToStartLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Rate), "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFraRateHelper(
                ObjectIdStrip,
                RateCpp,
                PeriodToStart,
                IborIndexStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FraRateHelper(
                valueObject,
                RateLibObj,
                PeriodToStartLib,
                IborIndexLibObjPtr,
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
XLL_DEC char *qlFraRateHelper2(
        char *ObjectId,
        OPER *Rate,
        char *PeriodToStart,
        long *LengthInMonths,
        long *FixingDays,
        char *Calendar,
        char *Convention,
        bool *EndOfMonth,
        char *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFraRateHelper2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodToStartLib;
        QuantLibAddin::cppToLibrary(PeriodToStart, PeriodToStartLib);

        QuantLib::Natural LengthInMonthsLib;
        QuantLibAddin::cppToLibrary(*LengthInMonths, LengthInMonthsLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(*FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Rate), "Rate");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFraRateHelper2(
                ObjectIdStrip,
                RateCpp,
                PeriodToStart,
                *LengthInMonths,
                *FixingDays,
                Calendar,
                Convention,
                *EndOfMonth,
                DayCounter,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FraRateHelper(
                valueObject,
                RateLibObj,
                PeriodToStartLib,
                LengthInMonthsLib,
                FixingDaysLib,
                CalendarEnum,
                ConventionEnum,
                *EndOfMonth,
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
XLL_DEC char *qlFuturesRateHelper(
        char *ObjectId,
        OPER *Price,
        OPER *IMM,
        OPER *IborIndex,
        OPER *ConvexityAdjQuote,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t PriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Price));

        ObjectHandler::property_t IMMCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IMM));

        std::string IborIndexCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*IborIndex), "IborIndex", "Euribor3M");

        ObjectHandler::property_t ConvexityAdjQuoteCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ConvexityAdjQuote));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IMMLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IMM), "IMM");

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Price), "Price");

        OH_GET_REFERENCE_DEFAULT(IborIndexLibObjPtr, IborIndexCpp,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*ConvexityAdjQuote), "ConvexityAdjQuote");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndexCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFuturesRateHelper(
                ObjectIdStrip,
                PriceCpp,
                IMMCpp,
                IborIndexCpp,
                ConvexityAdjQuoteCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                IMMLib,
                IborIndexLibObjPtr,
                ConvexityAdjQuoteLibObj,
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
XLL_DEC char *qlFuturesRateHelper2(
        char *ObjectId,
        OPER *Price,
        OPER *IMM,
        OPER *LengthInMonths,
        char *Calendar,
        OPER *Convention,
        OPER *EndOfMonth,
        OPER *DayCounter,
        OPER *ConvexityAdjQuote,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesRateHelper2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t PriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Price));

        ObjectHandler::property_t IMMCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IMM));

        long LengthInMonthsCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*LengthInMonths), "LengthInMonths", 3);

        std::string ConventionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Convention), "Convention", "Modified Following");

        bool EndOfMonthCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*EndOfMonth), "EndOfMonth", true);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/360");

        ObjectHandler::property_t ConvexityAdjQuoteCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ConvexityAdjQuote));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IMMLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IMM), "IMM");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ConventionCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Price), "Price");

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*ConvexityAdjQuote), "ConvexityAdjQuote");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFuturesRateHelper2(
                ObjectIdStrip,
                PriceCpp,
                IMMCpp,
                LengthInMonthsCpp,
                Calendar,
                ConventionCpp,
                EndOfMonthCpp,
                DayCounterCpp,
                ConvexityAdjQuoteCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                IMMLib,
                LengthInMonthsCpp,
                CalendarEnum,
                ConventionEnum,
                EndOfMonthCpp,
                DayCounterEnum,
                ConvexityAdjQuoteLibObj,
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
XLL_DEC char *qlFuturesRateHelper3(
        char *ObjectId,
        OPER *Price,
        OPER *IMM,
        OPER *EndDate,
        OPER *DayCounter,
        OPER *ConvexityAdjQuote,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesRateHelper3"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t PriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Price));

        ObjectHandler::property_t IMMCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IMM));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/360");

        ObjectHandler::property_t ConvexityAdjQuoteCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ConvexityAdjQuote));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IMMLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IMM), "IMM");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Price), "Price");

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*ConvexityAdjQuote), "ConvexityAdjQuote");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFuturesRateHelper3(
                ObjectIdStrip,
                PriceCpp,
                IMMCpp,
                EndDateCpp,
                DayCounterCpp,
                ConvexityAdjQuoteCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                IMMLib,
                EndDateLib,
                DayCounterEnum,
                ConvexityAdjQuoteLibObj,
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
XLL_DEC double *qlFuturesRateHelperConvexityAdjustment(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesRateHelperConvexityAdjustment"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::FuturesRateHelper, QuantLib::FuturesRateHelper)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->convexityAdjustment();

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
XLL_DEC char *qlOISRateHelper(
        char *ObjectId,
        long *SettlDays,
        char *Tenor,
        OPER *FixedRate,
        char *ONIndex,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOISRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t FixedRateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*FixedRate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural SettlDaysLib;
        QuantLibAddin::cppToLibrary(*SettlDays, SettlDaysLib);

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FixedRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*FixedRate), "FixedRate");

        OH_GET_REFERENCE(ONIndexLibObjPtr, ONIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ONIndexStrip = ObjectHandler::CallingRange::getStub(ONIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOISRateHelper(
                ObjectIdStrip,
                *SettlDays,
                Tenor,
                FixedRateCpp,
                ONIndexStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OISRateHelper(
                valueObject,
                SettlDaysLib,
                TenorLib,
                FixedRateLibObj,
                ONIndexLibObjPtr,
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
XLL_DEC long *qlRateHelperEarliestDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperEarliestDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->earliestDate();

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
XLL_DEC double *qlRateHelperImpliedQuote(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperImpliedQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->impliedQuote();

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
XLL_DEC long *qlRateHelperLatestDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperLatestDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->latestDate();

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
XLL_DEC double *qlRateHelperQuoteError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperQuoteError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->quoteError();

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
XLL_DEC double *qlRateHelperQuoteIsValid(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperQuoteIsValid"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->quote()->isValid();

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
XLL_DEC double *qlRateHelperQuoteValue(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperQuoteValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::RateHelper, QuantLib::RateHelper)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->quote()->value();

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
XLL_DEC double *qlRateHelperRate(
        char *RateHelper,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(RateHelperObjPtr, RateHelper, QuantLibAddin::RateHelper)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLibAddin::qlRateHelperRate(
                RateHelperObjPtr);

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
XLL_DEC OPER *qlRateHelperSelection(
        OPER *RateHelpers,
        OPER *Priority,
        long *NImmFutures,
        long *NSerialFutures,
        OPER *FutureRollDays,
        OPER *DepoInclusion,
        OPER *MinDistance,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRateHelperSelection"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> RateHelpersCpp =
            ObjectHandler::operToVector<std::string>(*RateHelpers, "RateHelpers");

        std::vector<long> PriorityCpp =
            ObjectHandler::operToVector<long>(*Priority, "Priority");

        long FutureRollDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*FutureRollDays), "FutureRollDays", 2);

        std::string DepoInclusionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DepoInclusion), "DepoInclusion", "AllDepos");

        std::vector<long> MinDistanceCpp =
            ObjectHandler::operToVector<long>(*MinDistance, "MinDistance");

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> PriorityLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(PriorityCpp);

        QuantLib::Natural NImmFuturesLib;
        QuantLibAddin::cppToLibrary(*NImmFutures, NImmFuturesLib);

        QuantLib::Natural NSerialFuturesLib;
        QuantLibAddin::cppToLibrary(*NSerialFutures, NSerialFuturesLib);

        QuantLib::Natural FutureRollDaysLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*FutureRollDays), "FutureRollDays", 2);

        std::vector<QuantLib::Natural> MinDistanceLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(MinDistanceCpp);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLibAddin::RateHelper::DepoInclusionCriteria DepoInclusionEnum =
            ObjectHandler::Create<QuantLibAddin::RateHelper::DepoInclusionCriteria>()(DepoInclusionCpp);

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::RateHelper> > RateHelpersObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::RateHelper>(RateHelpersCpp);

        // invoke the utility function

        std::vector<std::string> returnValue = QuantLibAddin::qlRateHelperSelection(
                RateHelpersObjPtr,
                PriorityLib,
                NImmFuturesLib,
                NSerialFuturesLib,
                FutureRollDaysLib,
                DepoInclusionEnum,
                MinDistanceLib);

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
XLL_DEC char *qlSwapRateHelper(
        char *ObjectId,
        OPER *Rate,
        char *SwapIndex,
        OPER *Spread,
        char *ForwardStart,
        OPER *DiscountingCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapRateHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        ObjectHandler::property_t SpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Spread));

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DiscountingCurve), "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Rate), "Rate");

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Spread), "Spread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);
        std::string DiscountingCurveStrip = ObjectHandler::CallingRange::getStub(DiscountingCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwapRateHelper(
                ObjectIdStrip,
                RateCpp,
                SwapIndexStrip,
                SpreadCpp,
                ForwardStart,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapRateHelper(
                valueObject,
                RateLibObj,
                SwapIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
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
XLL_DEC char *qlSwapRateHelper2(
        char *ObjectId,
        OPER *Rate,
        char *Tenor,
        char *Calendar,
        char *FixedLegFrequency,
        char *FixedLegConvention,
        char *FixedLegDayCounter,
        char *IborIndex,
        OPER *Spread,
        char *ForwardStart,
        OPER *DiscountingCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapRateHelper2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Rate));

        ObjectHandler::property_t SpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Spread));

        std::string DiscountingCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DiscountingCurve), "DiscountingCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::Frequency FixedLegFrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FixedLegFrequency);

        QuantLib::BusinessDayConvention FixedLegConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(FixedLegConvention);

        QuantLib::DayCounter FixedLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixedLegDayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Rate), "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Spread), "Spread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);
        std::string DiscountingCurveStrip = ObjectHandler::CallingRange::getStub(DiscountingCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwapRateHelper2(
                ObjectIdStrip,
                RateCpp,
                Tenor,
                Calendar,
                FixedLegFrequency,
                FixedLegConvention,
                FixedLegDayCounter,
                IborIndexStrip,
                SpreadCpp,
                ForwardStart,
                DiscountingCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapRateHelper(
                valueObject,
                RateLibObj,
                TenorLib,
                CalendarEnum,
                FixedLegFrequencyEnum,
                FixedLegConventionEnum,
                FixedLegDayCounterEnum,
                IborIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
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
XLL_DEC char *qlSwapRateHelperForwardStart(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapRateHelperForwardStart"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)

        // invoke the member function

        QuantLib::Period returnValue = ObjectIdLibObjPtr->forwardStart();

        // convert and return the return value

        std::string str = QuantLibAddin::libraryToScalar(returnValue);
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(str, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlSwapRateHelperSpread(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapRateHelperSpread"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)

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
