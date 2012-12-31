
/*  
 Copyright (C) 2006, 2007, 2009, 2010, 2011 Ferdinando Ametrano
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
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
#include <qlo/couponvectors.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/capfloor.hpp>
#include <qlo/swap.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/instruments/swap.hpp>
#include <qlo/valueobjects/vo_leg.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlInterestRate(
        char *ObjectId,
        double *Rate,
        char *DayCounter,
        char *Compounding,
        OPER *Frequency,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(Compounding);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterestRate(
                ObjectIdStrip,
                *Rate,
                DayCounter,
                Compounding,
                FrequencyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterestRate(
                valueObject,
                *Rate,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
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
XLL_DEC OPER *qlInterestRateCompoundFactor(
        char *ObjectId,
        OPER *StartDate,
        OPER *EndDate,
        OPER *RefPeriodStart,
        OPER *RefPeriodEnd,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateCompoundFactor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        ObjectHandler::property_t RefPeriodStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodStart));

        ObjectHandler::property_t RefPeriodEndCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodEnd));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodStart), "RefPeriodStart", QuantLib::Date());

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodEnd), "RefPeriodEnd", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->compoundFactor(
                StartDateLib,
                EndDateLib,
                RefPeriodStartLib,
                RefPeriodEndLib);

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
XLL_DEC char *qlInterestRateCompounding(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateCompounding"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        QuantLib::Compounding returnValue = ObjectIdLibObjPtr->compounding();

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
XLL_DEC char *qlInterestRateDayCounter(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateDayCounter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        QuantLib::DayCounter returnValue = ObjectIdLibObjPtr->dayCounter();

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
XLL_DEC OPER *qlInterestRateDiscountFactor(
        char *ObjectId,
        OPER *StartDate,
        OPER *EndDate,
        OPER *RefPeriodStart,
        OPER *RefPeriodEnd,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateDiscountFactor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        ObjectHandler::property_t RefPeriodStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodStart));

        ObjectHandler::property_t RefPeriodEndCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodEnd));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodStart), "RefPeriodStart", QuantLib::Date());

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodEnd), "RefPeriodEnd", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->discountFactor(
                StartDateLib,
                EndDateLib,
                RefPeriodStartLib,
                RefPeriodEndLib);

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
XLL_DEC OPER *qlInterestRateEquivalentRate(
        char *ObjectId,
        char *DayCounter,
        char *Compounding,
        OPER *Frequency,
        OPER *StartDate,
        OPER *EndDate,
        OPER *RefPeriodStart,
        OPER *RefPeriodEnd,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateEquivalentRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        ObjectHandler::property_t RefPeriodStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodStart));

        ObjectHandler::property_t RefPeriodEndCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodEnd));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodStart), "RefPeriodStart", QuantLib::Date());

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodEnd), "RefPeriodEnd", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(Compounding);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->equivalentRate(
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                StartDateLib,
                EndDateLib,
                RefPeriodStartLib,
                RefPeriodEndLib);

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
XLL_DEC char *qlInterestRateFrequency(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateFrequency"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        QuantLib::Frequency returnValue = ObjectIdLibObjPtr->frequency();

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
XLL_DEC OPER *qlInterestRateImpliedRate(
        double *Compound,
        char *DayCounter,
        char *Compounding,
        OPER *Frequency,
        OPER *StartDate,
        OPER *EndDate,
        OPER *RefPeriodStart,
        OPER *RefPeriodEnd,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateImpliedRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t EndDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EndDate));

        ObjectHandler::property_t RefPeriodStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodStart));

        ObjectHandler::property_t RefPeriodEndCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodEnd));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EndDate), "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodStart), "RefPeriodStart", QuantLib::Date());

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodEnd), "RefPeriodEnd", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(Compounding);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::InterestRate::impliedRate(
                *Compound,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                StartDateLib,
                EndDateLib,
                RefPeriodStartLib,
                RefPeriodEndLib);

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
XLL_DEC double *qlInterestRateRate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRate, QuantLib::InterestRate)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->rate();

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
XLL_DEC char *qlLeg(
        char *ObjectId,
        OPER *Amounts,
        OPER *Dates,
        OPER *ToBeSorted,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> AmountsCpp =
            ObjectHandler::operToVector<double>(*Amounts, "Amounts");

        std::vector<ObjectHandler::property_t> DatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*Dates, "Dates");

        bool ToBeSortedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*ToBeSorted), "ToBeSorted", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Dates, "Dates");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLeg(
                ObjectIdStrip,
                AmountsCpp,
                DatesCpp,
                ToBeSortedCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                AmountsCpp,
                DatesLib,
                ToBeSortedCpp,
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
XLL_DEC long *qlLegAccrualDays(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccrualDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static long returnValue;
        returnValue = QuantLib::CashFlows::accrualDays(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegAccrualEndDate(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccrualEndDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::accrualEndDate(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC double *qlLegAccrualPeriod(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccrualPeriod"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::accrualPeriod(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegAccrualStartDate(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccrualStartDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::accrualStartDate(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC OPER *qlLegAccruedAmount(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccruedAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::accruedAmount(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegAccruedDays(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccruedDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static long returnValue;
        returnValue = QuantLib::CashFlows::accrualDays(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC double *qlLegAccruedPeriod(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAccruedPeriod"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::accrualPeriod(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC double *qlLegAtmRate(
        char *ObjectId,
        char *DiscountCurve,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *NPV,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegAtmRate"));

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

        double NPVCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*NPV), "NPV", QuantLib::Null<QuantLib::Real>());

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        QuantLib::Real NPVLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*NPV), "NPV", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        OH_GET_OBJECT(DiscountCurveTemp, DiscountCurve, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> DiscountCurveTemp2 =
            QuantLibAddin::CoerceLibrarySame<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountCurveTemp);
        const QuantLib::YieldTermStructure &DiscountCurveLibObj =
            *(DiscountCurveTemp2.get());

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::atmRate(
                ObjectIdLibObj,
                DiscountCurveLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib,
                NPVLib);

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
XLL_DEC double *qlLegBPS(
        char *ObjectId,
        char *DiscountCurve,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegBPS"));

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

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        OH_GET_OBJECT(DiscountCurveTemp, DiscountCurve, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> DiscountCurveTemp2 =
            QuantLibAddin::CoerceLibrarySame<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountCurveTemp);
        const QuantLib::YieldTermStructure &DiscountCurveLibObj =
            *(DiscountCurveTemp2.get());

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::bps(
                ObjectIdLibObj,
                DiscountCurveLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC double *qlLegBPSFromYield(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegBPSFromYield"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/Actual (ISDA)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::bps(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC OPER *qlLegBasisPointValue(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegBasisPointValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/Actual (ISDA)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::basisPointValue(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC OPER *qlLegConvexity(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegConvexity"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/Actual (ISDA)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::convexity(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC double *qlLegDuration(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *DurationType,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegDuration"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/Actual (ISDA)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        std::string DurationTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DurationType), "DurationType", "Modified");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        QuantLib::Duration::Type DurationTypeEnum =
            ObjectHandler::Create<QuantLib::Duration::Type>()(DurationTypeCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::duration(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                DurationTypeEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC OPER *qlLegFlowAnalysis(
        char *ObjectId,
        OPER *AfterDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegFlowAnalysis"));

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

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Leg)

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->flowAnalysis(
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
XLL_DEC char *qlLegFromCapFloor(
        char *ObjectId,
        char *CapFloor,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegFromCapFloor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CapFloorLibObjPtr, CapFloor,
            QuantLibAddin::CapFloor, QuantLib::CapFloor)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string CapFloorStrip = ObjectHandler::CallingRange::getStub(CapFloor);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLegFromCapFloor(
                ObjectIdStrip,
                CapFloorStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                CapFloorLibObjPtr,
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
XLL_DEC char *qlLegFromSwap(
        char *ObjectId,
        char *Swap,
        long *LegNumber,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegFromSwap"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapLibObjPtr, Swap,
            QuantLibAddin::Swap, QuantLib::Swap)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SwapStrip = ObjectHandler::CallingRange::getStub(Swap);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLegFromSwap(
                ObjectIdStrip,
                SwapStrip,
                *LegNumber,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                SwapLibObjPtr,
                *LegNumber,
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
XLL_DEC short int *qlLegIsExpired(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegIsExpired"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static short int returnValue;
        returnValue = QuantLib::CashFlows::isExpired(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegMaturityDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegMaturityDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::startDate(
                ObjectIdLibObj);

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
XLL_DEC double *qlLegNPV(
        char *ObjectId,
        char *DiscountCurve,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNPV"));

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

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        OH_GET_OBJECT(DiscountCurveTemp, DiscountCurve, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> DiscountCurveTemp2 =
            QuantLibAddin::CoerceLibrarySame<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountCurveTemp);
        const QuantLib::YieldTermStructure &DiscountCurveLibObj =
            *(DiscountCurveTemp2.get());

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::npv(
                ObjectIdLibObj,
                DiscountCurveLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC OPER *qlLegNPVFromYield(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNPVFromYield"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/Actual (ISDA)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::npv(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC OPER *qlLegNPVFromZSpread(
        char *ObjectId,
        char *DiscountCurve,
        double *ZSpread,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNPVFromZSpread"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        OH_GET_REFERENCE(DiscountCurveLibObjPtr, DiscountCurve,
            QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::npv(
                ObjectIdLibObj,
                DiscountCurveLibObjPtr,
                *ZSpread,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC OPER *qlLegNextCashFlowAmount(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNextCashFlowAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::nextCashFlowAmount(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegNextCashFlowDate(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNextCashFlowDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::nextCashFlowDate(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC double *qlLegNextCouponRate(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNextCouponRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::nextCouponRate(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC OPER *qlLegNominal(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegNominal"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::nominal(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC OPER *qlLegPreviousCashFlowAmount(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegPreviousCashFlowAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::previousCashFlowAmount(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegPreviousCashFlowDate(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegPreviousCashFlowDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::previousCashFlowDate(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC double *qlLegPreviousCouponRate(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegPreviousCouponRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::previousCouponRate(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegReferencePeriodEnd(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegReferencePeriodEnd"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::referencePeriodEnd(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC long *qlLegReferencePeriodStart(
        char *ObjectId,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegReferencePeriodStart"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::referencePeriodStart(
                ObjectIdLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib);

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
XLL_DEC bool *qlLegSetCouponPricers(
        char *ObjectId,
        OPER *FloatingRateCouponPricer,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegSetCouponPricers"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> FloatingRateCouponPricerCpp =
            ObjectHandler::operToVector<std::string>(*FloatingRateCouponPricer, "FloatingRateCouponPricer");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Leg)

        std::vector<boost::shared_ptr<QuantLibAddin::FloatingRateCouponPricer> > FloatingRateCouponPricerObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::FloatingRateCouponPricer>(FloatingRateCouponPricerCpp);

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->setCouponPricers(
                FloatingRateCouponPricerObjPtr);

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
XLL_DEC long *qlLegStartDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegStartDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::CashFlows::startDate(
                ObjectIdLibObj);

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
XLL_DEC double *qlLegYield(
        char *ObjectId,
        double *NPV,
        char *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Accuracy,
        OPER *MaxIterations,
        OPER *Guess,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegYield"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Continuous");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-10);

        long MaxIterationsCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIterations), "MaxIterations", 100);

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", 0.05);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-10);

        QuantLib::Size MaxIterationsLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*MaxIterations), "MaxIterations", 100);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::yield(
                ObjectIdLibObj,
                *NPV,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib,
                AccuracyLib,
                MaxIterationsLib,
                GuessCpp);

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
XLL_DEC OPER *qlLegYieldValueBasisPoint(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegYieldValueBasisPoint"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/Actual (ISDA)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Compounded");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::CashFlows::yieldValueBasisPoint(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib);

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
XLL_DEC double *qlLegZSpread(
        char *ObjectId,
        double *NPV,
        char *DiscountCurve,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *IncludeSettlDate,
        OPER *SettlementDate,
        OPER *NpvDate,
        OPER *Accuracy,
        OPER *MaxIterations,
        OPER *Guess,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLegZSpread"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        std::string CompoundingCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Compounding), "Compounding", "Continuous");

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Frequency), "Frequency", "Annual");

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeSettlDate), "IncludeSettlDate", true);

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        ObjectHandler::property_t NpvDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*NpvDate));

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-10);

        long MaxIterationsCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIterations), "MaxIterations", 100);

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*NpvDate), "NpvDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-10);

        QuantLib::Size MaxIterationsLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*MaxIterations), "MaxIterations", 100);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Leg, QuantLib::Leg)

        OH_GET_REFERENCE(DiscountCurveLibObjPtr, DiscountCurve,
            QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::CashFlows::zSpread(
                ObjectIdLibObj,
                *NPV,
                DiscountCurveLibObjPtr,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib,
                AccuracyLib,
                MaxIterationsLib,
                GuessCpp);

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
XLL_DEC char *qlMultiPhaseLeg(
        char *ObjectId,
        OPER *LegIDs,
        OPER *ToBeSorted,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMultiPhaseLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> LegIDsCpp =
            ObjectHandler::operToVector<std::string>(*LegIDs, "LegIDs");

        bool ToBeSortedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*ToBeSorted), "ToBeSorted", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Leg> > LegIDsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Leg>(LegIDsCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMultiPhaseLeg(
                ObjectIdStrip,
                LegIDsCpp,
                ToBeSortedCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiPhaseLeg(
                valueObject,
                LegIDsObjPtr,
                ToBeSortedCpp,
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
