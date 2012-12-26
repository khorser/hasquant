
/*  
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
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <ql/time/date.hpp>
#include <ql/time/calendar.hpp>
#include <qlo/loop/loop_calendar.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC bool *qlCalendarAddHoliday(
        char *calendar,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarAddHoliday"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t DateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Date));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Date), "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // invoke the member function

        static bool returnValue = true;
        calendarEnum.addHoliday(
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
XLL_DEC OPER *qlCalendarAdjust(
        char *calendar,
        OPER *Date,
        OPER *BusinessDayConvention,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarAdjust"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string BusinessDayConventionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*BusinessDayConvention), "BusinessDayConvention", "Following");

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConventionCpp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarAdjustBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarAdjustSignature)
                &QuantLib::Calendar::adjust,
                calendarEnum,
                _1,
                BusinessDayConventionEnum);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarAdjustBind, QuantLib::Date, QuantLib::Date>
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
XLL_DEC OPER *qlCalendarAdvance(
        char *calendar,
        OPER *StartDate,
        OPER *Period,
        OPER *BusinessDayConvention,
        OPER *EndOfMonth,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarAdvance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        std::string BusinessDayConventionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*BusinessDayConvention), "BusinessDayConvention", "Following");

        bool EndOfMonthCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*EndOfMonth), "EndOfMonth", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        std::vector<QuantLib::Period> PeriodLib =
            ObjectHandler::operToVector<QuantLib::Period>(*Period, "Period");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConventionCpp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarAdvanceBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarAdvanceSignature)
                &QuantLib::Calendar::advance,
                calendarEnum,
                StartDateLib,
                _1,
                BusinessDayConventionEnum,
                EndOfMonthCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarAdvanceBind, QuantLib::Period, QuantLib::Date>
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
XLL_DEC OPER *qlCalendarBusinessDaysBetween(
        char *calendar,
        OPER *FirstDate,
        OPER *LastDate,
        OPER *IncludeFirst,
        OPER *IncludeLast,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarBusinessDaysBetween"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t LastDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*LastDate));

        bool IncludeFirstCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeFirst), "IncludeFirst", false);

        bool IncludeLastCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeLast), "IncludeLast", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> FirstDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*FirstDate, "FirstDate");

        QuantLib::Date LastDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*LastDate), "LastDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarBusinessDaysBetweenBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarBusinessDaysBetweenSignature)
                &QuantLib::Calendar::businessDaysBetween,
                calendarEnum,
                _1,
                LastDateLib,
                IncludeFirstCpp,
                IncludeLastCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarBusinessDaysBetweenBind, QuantLib::Date, long>
            (functionCall, bindObject, FirstDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCalendarEndOfMonth(
        char *calendar,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarEndOfMonth"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarEndOfMonthBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarEndOfMonthSignature)
                &QuantLib::Calendar::endOfMonth,
                calendarEnum,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarEndOfMonthBind, QuantLib::Date, QuantLib::Date>
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
XLL_DEC OPER *qlCalendarHolidayList(
        char *Calendar,
        OPER *FromDate,
        OPER *ToDate,
        OPER *IncludeWeekEnds,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarHolidayList"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t FromDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*FromDate));

        ObjectHandler::property_t ToDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ToDate));

        bool IncludeWeekEndsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IncludeWeekEnds), "IncludeWeekEnds", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FromDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*FromDate), "FromDate");

        QuantLib::Date ToDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ToDate), "ToDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        // invoke the utility function

        std::vector<QuantLib::Date> returnValue = QuantLib::Calendar::holidayList(
                CalendarEnum,
                FromDateLib,
                ToDateLib,
                IncludeWeekEndsCpp);

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
XLL_DEC OPER *qlCalendarIsBusinessDay(
        char *calendar,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarIsBusinessDay"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarIsBusinessDayBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarIsBusinessDaySignature)
                &QuantLib::Calendar::isBusinessDay,
                calendarEnum,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarIsBusinessDayBind, QuantLib::Date, bool>
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
XLL_DEC OPER *qlCalendarIsEndOfMonth(
        char *calendar,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarIsEndOfMonth"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarIsEndOfMonthBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarIsEndOfMonthSignature)
                &QuantLib::Calendar::isEndOfMonth,
                calendarEnum,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarIsEndOfMonthBind, QuantLib::Date, bool>
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
XLL_DEC OPER *qlCalendarIsHoliday(
        char *calendar,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarIsHoliday"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*Date, "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlCalendarIsHolidayBind bindObject = 
            boost::bind((QuantLibAddin::qlCalendarIsHolidaySignature)
                &QuantLib::Calendar::isHoliday,
                calendarEnum,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlCalendarIsHolidayBind, QuantLib::Date, bool>
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
XLL_DEC char *qlCalendarName(
        char *calendar,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarName"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // invoke the member function

        std::string returnValue = calendarEnum.name();

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
XLL_DEC bool *qlCalendarRemoveHoliday(
        char *calendar,
        OPER *Date,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCalendarRemoveHoliday"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t DateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Date));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*Date), "Date");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar calendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(calendar);

        // invoke the member function

        static bool returnValue = true;
        calendarEnum.removeHoliday(
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
