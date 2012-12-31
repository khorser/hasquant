
/*  
 Copyright (C) 2006, 2007 Chiara Fornarola
 Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Walter Penschke
 Copyright (C) 2009 Piter Dias
 
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
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/couponvectors.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/pricingengines/bond/bondfunctions.hpp>
#include <ql/currency.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/valueobjects/vo_bonds.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlBond(
        char *ObjectId,
        OPER *Description,
        OPER *Currency,
        OPER *SettlementDays,
        OPER *Calendar,
        OPER *FaceAmount,
        OPER *MaturityDate,
        OPER *IssueDate,
        char *LegID,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBond"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Description), "Description", std::string());

        std::string CurrencyCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Currency), "Currency", "NullCurrency");

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*SettlementDays), "SettlementDays", 3);

        std::string CalendarCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Calendar), "Calendar", "NullCalendar");

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        ObjectHandler::property_t MaturityDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*MaturityDate));

        ObjectHandler::property_t IssueDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IssueDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*SettlementDays), "SettlementDays", 3);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*MaturityDate), "MaturityDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(CurrencyCpp);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(CalendarCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(LegIDLibObj, LegID,
            QuantLibAddin::Leg, QuantLib::Leg)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string LegIDStrip = ObjectHandler::CallingRange::getStub(LegID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBond(
                ObjectIdStrip,
                DescriptionCpp,
                CurrencyCpp,
                SettlementDaysCpp,
                CalendarCpp,
                FaceAmountCpp,
                MaturityDateCpp,
                IssueDateCpp,
                LegIDStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Bond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                CalendarEnum,
                FaceAmountLib,
                MaturityDateLib,
                IssueDateLib,
                LegIDLibObj,
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
XLL_DEC long *qlBondAccrualDays(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccrualDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static long returnValue;
        returnValue = QuantLib::BondFunctions::accrualDays(
                ObjectIdLibObj,
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
XLL_DEC long *qlBondAccrualEndDate(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccrualEndDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::accrualEndDate(
                ObjectIdLibObj,
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
XLL_DEC double *qlBondAccrualPeriod(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccrualPeriod"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::accrualPeriod(
                ObjectIdLibObj,
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
XLL_DEC long *qlBondAccrualStartDate(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccrualStartDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::accrualStartDate(
                ObjectIdLibObj,
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
XLL_DEC double *qlBondAccruedAmount(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccruedAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::accruedAmount(
                ObjectIdLibObj,
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
XLL_DEC long *qlBondAccruedDays(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccruedDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static long returnValue;
        returnValue = QuantLib::BondFunctions::accruedDays(
                ObjectIdLibObj,
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
XLL_DEC double *qlBondAccruedPeriod(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAccruedPeriod"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::accruedPeriod(
                ObjectIdLibObj,
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
XLL_DEC OPER *qlBondAlive(
        OPER *Bonds,
        OPER *RefDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAlive"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> BondsCpp =
            ObjectHandler::operToVector<std::string>(*Bonds, "Bonds");

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Bond> > BondsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Bond>(BondsCpp);

        // invoke the utility function

        std::vector<std::string> returnValue = QuantLibAddin::qlBondAlive(
                BondsObjPtr,
                RefDateLib);

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
XLL_DEC OPER *qlBondAtmRateFromYieldTermStructure(
        char *ObjectId,
        char *YieldCurve,
        OPER *SettlementDate,
        double *CleanPrice,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondAtmRateFromYieldTermStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_OBJECT(YieldCurveTemp, YieldCurve, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> YieldCurveTemp2 =
            QuantLibAddin::CoerceLibrarySame<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveTemp);
        const QuantLib::YieldTermStructure &YieldCurveLibObj =
            *(YieldCurveTemp2.get());

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::atmRate(
                ObjectIdLibObj,
                YieldCurveLibObj,
                SettlementDateLib,
                *CleanPrice);

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
XLL_DEC OPER *qlBondBpsFromYield(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondBpsFromYield"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::bps(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
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
XLL_DEC OPER *qlBondBpsFromYieldTermStructure(
        char *ObjectId,
        char *YieldCurve,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondBpsFromYieldTermStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_OBJECT(YieldCurveTemp, YieldCurve, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> YieldCurveTemp2 =
            QuantLibAddin::CoerceLibrarySame<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveTemp);
        const QuantLib::YieldTermStructure &YieldCurveLibObj =
            *(YieldCurveTemp2.get());

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::bps(
                ObjectIdLibObj,
                YieldCurveLibObj,
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
XLL_DEC char *qlBondCalendar(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondCalendar"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        QuantLib::Calendar returnValue = ObjectIdLibObjPtr->calendar();

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
XLL_DEC double *qlBondCleanPrice(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondCleanPrice"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->cleanPrice();

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
XLL_DEC OPER *qlBondCleanPriceFromYield(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondCleanPriceFromYield"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::cleanPrice(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
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
XLL_DEC OPER *qlBondCleanPriceFromYieldTermStructure(
        char *ObjectId,
        char *YieldCurve,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondCleanPriceFromYieldTermStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_OBJECT(YieldCurveTemp, YieldCurve, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::YieldTermStructure> YieldCurveTemp2 =
            QuantLibAddin::CoerceLibrarySame<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveTemp);
        const QuantLib::YieldTermStructure &YieldCurveLibObj =
            *(YieldCurveTemp2.get());

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::cleanPrice(
                ObjectIdLibObj,
                YieldCurveLibObj,
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
XLL_DEC OPER *qlBondCleanPriceFromZSpread(
        char *ObjectId,
        char *YieldCurve,
        double *ZSpread,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondCleanPriceFromZSpread"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_REFERENCE(YieldCurveLibObjPtr, YieldCurve,
            QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::cleanPrice(
                ObjectIdLibObj,
                YieldCurveLibObjPtr,
                *ZSpread,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
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
XLL_DEC OPER *qlBondConvexityFromYield(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondConvexityFromYield"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(CompoundingCpp);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::convexity(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
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
XLL_DEC char *qlBondCurrency(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondCurrency"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

        // invoke the member function

        std::string returnValue = ObjectIdObjPtr->currency();

        // convert and return the return value

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
XLL_DEC char *qlBondDescription(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondDescription"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

        // invoke the member function

        std::string returnValue = ObjectIdObjPtr->description();

        // convert and return the return value

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
XLL_DEC OPER *qlBondDurationFromYield(
        char *ObjectId,
        double *Yield,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *DurationType,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondDurationFromYield"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

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
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::duration(
                ObjectIdLibObj,
                *Yield,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                DurationTypeEnum,
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
XLL_DEC OPER *qlBondFlowAnalysis(
        char *ObjectId,
        OPER *AfterDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondFlowAnalysis"));

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

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

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
XLL_DEC short int *qlBondIsTradable(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondIsTradable"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        static short int returnValue;
        returnValue = ObjectIdLibObjPtr->isTradable(
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
XLL_DEC long *qlBondIssueDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondIssueDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->issueDate();

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
XLL_DEC long *qlBondMaturityDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondMaturityDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->maturityDate();

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
XLL_DEC char *qlBondMaturityLookup(
        OPER *Bonds,
        OPER *Maturity,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondMaturityLookup"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> BondsCpp =
            ObjectHandler::operToVector<std::string>(*Bonds, "Bonds");

        ObjectHandler::property_t MaturityCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Maturity));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Maturity), "Maturity");

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Bond> > BondsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Bond>(BondsCpp);

        // invoke the utility function

        std::string returnValue = QuantLibAddin::qlBondMaturityLookup(
                BondsObjPtr,
                MaturityLib);

        // convert and return the return value

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
XLL_DEC OPER *qlBondMaturitySort(
        OPER *Bonds,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondMaturitySort"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> BondsCpp =
            ObjectHandler::operToVector<std::string>(*Bonds, "Bonds");

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Bond> > BondsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Bond>(BondsCpp);

        // invoke the utility function

        std::vector<std::string> returnValue = QuantLibAddin::qlBondMaturitySort(
                BondsObjPtr);

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
XLL_DEC OPER *qlBondNextCashFlowAmount(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondNextCashFlowAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::nextCashFlowAmount(
                ObjectIdLibObj,
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
XLL_DEC long *qlBondNextCashFlowDate(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondNextCashFlowDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::nextCashFlowDate(
                ObjectIdLibObj,
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
XLL_DEC double *qlBondNextCouponRate(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondNextCouponRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::nextCouponRate(
                ObjectIdLibObj,
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
XLL_DEC OPER *qlBondNotional(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondNotional"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->notional(
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
XLL_DEC OPER *qlBondNotionals(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondNotionals"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->notionals();

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
XLL_DEC OPER *qlBondPreviousCashFlowAmount(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondPreviousCashFlowAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Real returnValue = QuantLib::BondFunctions::previousCashFlowAmount(
                ObjectIdLibObj,
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
XLL_DEC long *qlBondPreviousCashFlowDate(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondPreviousCashFlowDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::previousCashFlowDate(
                ObjectIdLibObj,
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
XLL_DEC double *qlBondPreviousCouponRate(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondPreviousCouponRate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::previousCouponRate(
                ObjectIdLibObj,
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
XLL_DEC OPER *qlBondRedemptionAmount(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondRedemptionAmount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->redemptionAmount();

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
XLL_DEC long *qlBondRedemptionDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondRedemptionDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdObjPtr->redemptionDate();

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
XLL_DEC long *qlBondReferencePeriodEnd(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondReferencePeriodEnd"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::referencePeriodEnd(
                ObjectIdLibObj,
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
XLL_DEC long *qlBondReferencePeriodStart(
        char *ObjectId,
        OPER *SettlementDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondReferencePeriodStart"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::referencePeriodStart(
                ObjectIdLibObj,
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
XLL_DEC bool *qlBondSetCouponPricer(
        char *ObjectId,
        char *FloatingRateCouponPricer,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondSetCouponPricer"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

        // convert object IDs into library objects

        OH_GET_REFERENCE(FloatingRateCouponPricerLibObjPtr, FloatingRateCouponPricer,
            QuantLibAddin::FloatingRateCouponPricer, QuantLib::FloatingRateCouponPricer)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->setCouponPricer(
                FloatingRateCouponPricerLibObjPtr);

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
XLL_DEC bool *qlBondSetCouponPricers(
        char *ObjectId,
        OPER *FloatingRateCouponPricer,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondSetCouponPricers"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::string> FloatingRateCouponPricerCpp =
            ObjectHandler::operToVector<std::string>(*FloatingRateCouponPricer, "FloatingRateCouponPricer");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Bond)

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::FloatingRateCouponPricer> > FloatingRateCouponPricerLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::FloatingRateCouponPricer, QuantLib::FloatingRateCouponPricer>(FloatingRateCouponPricerCpp);

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->setCouponPricers(
                FloatingRateCouponPricerLibObjPtr);

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
XLL_DEC long *qlBondSettlementDate(
        char *ObjectId,
        OPER *EvaluationDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondSettlementDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t EvaluationDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*EvaluationDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date EvaluationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*EvaluationDate), "EvaluationDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->settlementDate(
                EvaluationDateLib);

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
XLL_DEC long *qlBondSettlementDays(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondSettlementDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the member function

        QuantLib::Natural returnValue = ObjectIdLibObjPtr->settlementDays();

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
XLL_DEC long *qlBondStartDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondStartDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_UNDERLYING(ObjectIdLibObj, ObjectId,
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::BondFunctions::startDate(
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
XLL_DEC double *qlBondYieldFromCleanPrice(
        char *ObjectId,
        double *CleanPrice,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *SettlementDate,
        OPER *Accuracy,
        OPER *MaxIterations,
        OPER *Guess,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondYieldFromCleanPrice"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-10);

        long MaxIterationsCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIterations), "MaxIterations", 100);

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", 0.05);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

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
            QuantLibAddin::Bond, QuantLib::Bond)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::yield(
                ObjectIdLibObj,
                *CleanPrice,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                SettlementDateLib,
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
XLL_DEC double *qlBondZSpreadFromCleanPrice(
        char *ObjectId,
        double *CleanPrice,
        char *YieldCurve,
        OPER *DayCounter,
        OPER *Compounding,
        OPER *Frequency,
        OPER *SettlementDate,
        OPER *Accuracy,
        OPER *MaxIterations,
        OPER *Guess,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBondZSpreadFromCleanPrice"));

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

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-10);

        long MaxIterationsCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*MaxIterations), "MaxIterations", 100);

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", 0.0);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate", QuantLib::Date());

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
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_REFERENCE(YieldCurveLibObjPtr, YieldCurve,
            QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::BondFunctions::zSpread(
                ObjectIdLibObj,
                *CleanPrice,
                YieldCurveLibObjPtr,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                SettlementDateLib,
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
XLL_DEC char *qlCmsRateBond(
        char *ObjectId,
        OPER *Description,
        char *Currency,
        long *SettlementDays,
        OPER *PaymentBDC,
        OPER *FaceAmount,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Floors,
        OPER *Gearings,
        char *SwapIndex,
        OPER *Spreads,
        OPER *Caps,
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
            new ObjectHandler::FunctionCall("qlCmsRateBond"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Description), "Description", std::string());

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        long FixingDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*FixingDays), "FixingDays", QuantLib::Null<QuantLib::Natural>());

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> FloorsCpp =
            ObjectHandler::operToVector<double>(*Floors, "Floors");

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CapsCpp =
            ObjectHandler::operToVector<double>(*Caps, "Caps");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100);

        ObjectHandler::property_t IssueDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IssueDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(*SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*FixingDays), "FixingDays", QuantLib::Null<QuantLib::Natural>());

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsRateBond(
                ObjectIdStrip,
                DescriptionCpp,
                Currency,
                *SettlementDays,
                PaymentBDCCpp,
                FaceAmountCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                FloorsCpp,
                GearingsCpp,
                SwapIndexStrip,
                SpreadsCpp,
                CapsCpp,
                RedemptionCpp,
                IssueDateCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                PaymentBDCEnum,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                FloorsCpp,
                GearingsCpp,
                SwapIndexLibObjPtr,
                SpreadsCpp,
                CapsCpp,
                RedemptionLib,
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
XLL_DEC char *qlFixedRateBond(
        char *ObjectId,
        OPER *Description,
        char *Currency,
        long *SettlementDays,
        OPER *FaceAmount,
        char *ScheduleID,
        OPER *Coupons,
        char *DayCounter,
        OPER *PaymentBDC,
        OPER *Redemption,
        OPER *IssueDate,
        char *PaymentCalendar,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFixedRateBond"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Description), "Description", std::string());

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

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100.0);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateBond(
                ObjectIdStrip,
                DescriptionCpp,
                Currency,
                *SettlementDays,
                FaceAmountCpp,
                ScheduleIDStrip,
                CouponsCpp,
                DayCounter,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDateCpp,
                PaymentCalendar,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                CouponsCpp,
                DayCounterEnum,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PaymentCalendarEnum,
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
XLL_DEC char *qlFixedRateBond2(
        char *ObjectId,
        OPER *Description,
        char *Currency,
        long *SettlementDays,
        OPER *FaceAmount,
        char *ScheduleID,
        OPER *Coupons,
        OPER *PaymentBDC,
        OPER *Redemption,
        OPER *IssueDate,
        char *PaymentCalendar,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFixedRateBond2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Description), "Description", std::string());

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        std::vector<std::string> CouponsCpp =
            ObjectHandler::operToVector<std::string>(*Coupons, "Coupons");

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

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100.0);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        std::vector<boost::shared_ptr<QuantLib::InterestRate> > CouponsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRate, QuantLib::InterestRate>(CouponsCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateBond2(
                ObjectIdStrip,
                DescriptionCpp,
                Currency,
                *SettlementDays,
                FaceAmountCpp,
                ScheduleIDStrip,
                CouponsCpp,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDateCpp,
                PaymentCalendar,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                CouponsLibObjPtr,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PaymentCalendarEnum,
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
XLL_DEC char *qlFloatingRateBond(
        char *ObjectId,
        OPER *Description,
        char *Currency,
        long *SettlementDays,
        OPER *PaymentBDC,
        OPER *FaceAmount,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Floors,
        OPER *Gearings,
        char *IborIndex,
        OPER *Spreads,
        OPER *Caps,
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
            new ObjectHandler::FunctionCall("qlFloatingRateBond"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Description), "Description", std::string());

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        long FixingDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*FixingDays), "FixingDays", QuantLib::Null<QuantLib::Natural>());

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> FloorsCpp =
            ObjectHandler::operToVector<double>(*Floors, "Floors");

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CapsCpp =
            ObjectHandler::operToVector<double>(*Caps, "Caps");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100);

        ObjectHandler::property_t IssueDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IssueDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(*SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*FixingDays), "FixingDays", QuantLib::Null<QuantLib::Natural>());

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFloatingRateBond(
                ObjectIdStrip,
                DescriptionCpp,
                Currency,
                *SettlementDays,
                PaymentBDCCpp,
                FaceAmountCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                FloorsCpp,
                GearingsCpp,
                IborIndexStrip,
                SpreadsCpp,
                CapsCpp,
                RedemptionCpp,
                IssueDateCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FloatingRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                PaymentBDCEnum,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                FloorsCpp,
                GearingsCpp,
                IborIndexLibObjPtr,
                SpreadsCpp,
                CapsCpp,
                RedemptionLib,
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
XLL_DEC char *qlZeroCouponBond(
        char *ObjectId,
        OPER *Description,
        char *Currency,
        long *SettlementDays,
        char *Calendar,
        OPER *FaceAmount,
        OPER *Maturity,
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
            new ObjectHandler::FunctionCall("qlZeroCouponBond"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Description), "Description", std::string());

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        ObjectHandler::property_t MaturityCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Maturity));

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100);

        ObjectHandler::property_t IssueDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*IssueDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(*SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*FaceAmount), "FaceAmount", 100.0);

        QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Maturity), "Maturity");

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Redemption), "Redemption", 100);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*IssueDate), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlZeroCouponBond(
                ObjectIdStrip,
                DescriptionCpp,
                Currency,
                *SettlementDays,
                Calendar,
                FaceAmountCpp,
                MaturityCpp,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDateCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ZeroCouponBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                CalendarEnum,
                FaceAmountLib,
                MaturityLib,
                PaymentBDCEnum,
                RedemptionLib,
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
