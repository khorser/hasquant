
/*  
 Copyright (C) 2006, 2009 Ferdinando Ametrano
 
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
#include <qlo/date.hpp>
#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/ecb.hpp>
#include <qlo/loop/loop_date.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC OPER *qlDateEndOfMonth(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateEndOfMonth"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlDateEndOfMonthBind bindObject = 
            boost::bind(
                &QuantLib::Date::endOfMonth,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlDateEndOfMonthBind, QuantLib::Date, QuantLib::Date>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlDateIsEndOfMonth(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateIsEndOfMonth"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlDateIsEndOfMonthBind bindObject = 
            boost::bind(
                &QuantLib::Date::isEndOfMonth,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlDateIsEndOfMonthBind, QuantLib::Date, bool>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlDateIsLeap(
        OPER *Year,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateIsLeap"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlDateIsLeapBind bindObject = 
            boost::bind(
                &QuantLib::Date::isLeap,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlDateIsLeapBind, long, bool>
            (functionCall, bindObject, Year, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlDateMaxDate(
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateMaxDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::Date::maxDate();

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
XLL_DEC long *qlDateMinDate(
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateMinDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::Date::minDate();

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
XLL_DEC OPER *qlDateNextWeekday(
        OPER *Date,
        char *Weekday,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateNextWeekday"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Weekday WeekdayEnum =
            ObjectHandler::Create<QuantLib::Weekday>()(Weekday);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlDateNextWeekdayBind bindObject = 
            boost::bind(
                &QuantLib::Date::nextWeekday,
                _1,
                WeekdayEnum);
        ObjectHandler::loop
            <QuantLibAddin::qlDateNextWeekdayBind, QuantLib::Date, QuantLib::Date>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlDateNthWeekday(
        long *Nth,
        char *Weekday,
        char *Month,
        long *Year,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDateNthWeekday"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Weekday WeekdayEnum =
            ObjectHandler::Create<QuantLib::Weekday>()(Weekday);

        QuantLib::Month MonthEnum =
            ObjectHandler::Create<QuantLib::Month>()(Month);

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::Date::nthWeekday(
                *Nth,
                WeekdayEnum,
                MonthEnum,
                *Year);

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
XLL_DEC bool *qlECBAddDate(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBAddDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t DateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Date));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Date), "Date");

        // invoke the utility function

        static bool returnValue = true;
        QuantLib::ECB::addDate(
                DateLib);

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
XLL_DEC OPER *qlECBIsECBcode(
        OPER *Code,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBIsECBcode"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlECBIsECBcodeBind bindObject = 
            boost::bind(
                &QuantLib::ECB::isECBcode,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlECBIsECBcodeBind, std::string, bool>
            (functionCall, bindObject, Code, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlECBIsECBdate(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBIsECBdate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlECBIsECBdateBind bindObject = 
            boost::bind(
                &QuantLib::ECB::isECBdate,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlECBIsECBdateBind, QuantLib::Date, bool>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlECBKnownDates(
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBKnownDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        std::vector<QuantLib::Date> returnValue = QuantLibAddin::qlECBKnownDates();

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
XLL_DEC char *qlECBNextCode(
        OPER *RefDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBNextCode"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // invoke the utility function

        std::string returnValue = QuantLib::ECB::nextCode(
                RefDateLib);

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
XLL_DEC char *qlECBNextCode2(
        char *Code,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBNextCode2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        std::string returnValue = QuantLib::ECB::nextCode(
                Code);

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
XLL_DEC long *qlECBNextDate(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBNextDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t DateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Date));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Date), "Date", QuantLib::Date());

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::ECB::nextDate(
                DateLib);

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
XLL_DEC long *qlECBNextDate2(
        char *Code,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBNextDate2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::ECB::nextDate(
                Code);

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
XLL_DEC OPER *qlECBNextDates(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBNextDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t DateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Date));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Date), "Date", QuantLib::Date());

        // invoke the utility function

        std::vector<QuantLib::Date> returnValue = QuantLib::ECB::nextDates(
                DateLib);

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
XLL_DEC bool *qlECBRemoveDate(
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBRemoveDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t DateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Date));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Date), "Date");

        // invoke the utility function

        static bool returnValue = true;
        QuantLib::ECB::removeDate(
                DateLib);

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
XLL_DEC char *qlECBcode(
        OPER *ECBdate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBcode"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ECBdateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ECBdate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ECBdateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ECBdate), "ECBdate");

        // invoke the utility function

        std::string returnValue = QuantLib::ECB::code(
                ECBdateLib);

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
XLL_DEC long *qlECBdate(
        char *ECBcode,
        OPER *RefDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBdate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::ECB::date(
                ECBcode,
                RefDateLib);

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
XLL_DEC long *qlECBdate2(
        char *Month,
        long *Year,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlECBdate2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Month MonthEnum =
            ObjectHandler::Create<QuantLib::Month>()(Month);

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::ECB::date(
                MonthEnum,
                *Year);

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
XLL_DEC OPER *qlFrequencyFromPeriod(
        OPER *Period,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFrequencyFromPeriod"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> PeriodLib =
            ObjectHandler::operToVector<QuantLib::Period>(*Period, "Period");

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlFrequencyFromPeriodBind bindObject = 
            boost::bind(
                &QuantLibAddin::frequencyFromPeriod,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlFrequencyFromPeriodBind, QuantLib::Period, QuantLib::Frequency>
            (functionCall, bindObject, Period, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlIMMIsIMMcode(
        OPER *Code,
        OPER *MainCycle,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMIsIMMcode"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool MainCycleCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*MainCycle), "MainCycle", true);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIMMIsIMMcodeBind bindObject = 
            boost::bind(
                &QuantLib::IMM::isIMMcode,
                _1,
                MainCycleCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlIMMIsIMMcodeBind, std::string, bool>
            (functionCall, bindObject, Code, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlIMMIsIMMdate(
        OPER *Date,
        OPER *MainCycle,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMIsIMMdate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool MainCycleCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*MainCycle), "MainCycle", true);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIMMIsIMMdateBind bindObject = 
            boost::bind(
                &QuantLib::IMM::isIMMdate,
                _1,
                MainCycleCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlIMMIsIMMdateBind, QuantLib::Date, bool>
            (functionCall, bindObject, Date, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlIMMNextCode(
        OPER *RefDate,
        OPER *MainCycle,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMNextCode"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        bool MainCycleCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*MainCycle), "MainCycle", true);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // invoke the utility function

        std::string returnValue = QuantLib::IMM::nextCode(
                RefDateLib,
                MainCycleCpp);

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
XLL_DEC OPER *qlIMMNextCodes(
        OPER *RefDate,
        OPER *MainCycle,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMNextCodes"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        std::vector<bool> MainCycleCpp =
            ObjectHandler::operToVector<bool>(*MainCycle, "MainCycle");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // invoke the utility function

        std::vector<std::string> returnValue = QuantLibAddin::qlIMMNextCodes(
                RefDateLib,
                MainCycleCpp);

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
XLL_DEC long *qlIMMNextDate(
        OPER *RefDate,
        OPER *MainCycle,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMNextDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        bool MainCycleCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*MainCycle), "MainCycle", true);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // invoke the utility function

        QuantLib::Date returnValue = QuantLib::IMM::nextDate(
                RefDateLib,
                MainCycleCpp);

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
XLL_DEC OPER *qlIMMNextDates(
        OPER *RefDate,
        OPER *MainCycle,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMNextDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        std::vector<bool> MainCycleCpp =
            ObjectHandler::operToVector<bool>(*MainCycle, "MainCycle");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // invoke the utility function

        std::vector<QuantLib::Date> returnValue = QuantLibAddin::qlIMMNextDates(
                RefDateLib,
                MainCycleCpp);

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
XLL_DEC OPER *qlIMMcode(
        OPER *IMMdate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMcode"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> IMMdateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*IMMdate, "IMMdate");

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIMMcodeBind bindObject = 
            boost::bind(
                &QuantLib::IMM::code,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlIMMcodeBind, QuantLib::Date, std::string>
            (functionCall, bindObject, IMMdate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlIMMdate(
        OPER *IMMcode,
        OPER *RefDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIMMdate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate", QuantLib::Date());

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIMMdateBind bindObject = 
            boost::bind(
                &QuantLib::IMM::date,
                _1,
                RefDateLib);
        ObjectHandler::loop
            <QuantLibAddin::qlIMMdateBind, std::string, QuantLib::Date>
            (functionCall, bindObject, IMMcode, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlPeriodEquivalent(
        char *Period,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPeriodEquivalent"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodLib;
        QuantLibAddin::cppToLibrary(Period, PeriodLib);

        // invoke the utility function

        QuantLib::Period returnValue = QuantLibAddin::periodEquivalent(
                PeriodLib);

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
XLL_DEC char *qlPeriodFromFrequency(
        char *Frequency,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPeriodFromFrequency"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(Frequency);

        // invoke the utility function

        QuantLib::Period returnValue = QuantLibAddin::periodFromFrequency(
                FrequencyEnum);

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
XLL_DEC short int *qlPeriodLessThan(
        char *Period1,
        char *Period2,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPeriodLessThan"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period Period1Lib;
        QuantLibAddin::cppToLibrary(Period1, Period1Lib);

        QuantLib::Period Period2Lib;
        QuantLibAddin::cppToLibrary(Period2, Period2Lib);

        // invoke the utility function

        static short int returnValue;
        returnValue = QuantLib::operator<(
                Period1Lib,
                Period2Lib);

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
