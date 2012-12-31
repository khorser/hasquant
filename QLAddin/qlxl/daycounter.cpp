
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 
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
#include <ql/time/date.hpp>
#include <ql/time/daycounter.hpp>
#include <qlo/loop/loop_daycounter.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC OPER *qlDayCounterDayCount(
        char *daycounter,
        OPER *StartDate,
        OPER *EndDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDayCounterDayCount"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        std::vector<QuantLib::Date> EndDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*EndDate, "EndDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter daycounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(daycounter);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlDayCounterDayCountBind bindObject = 
            boost::bind((QuantLibAddin::qlDayCounterDayCountSignature)
                &QuantLib::DayCounter::dayCount,
                daycounterEnum,
                StartDateLib,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlDayCounterDayCountBind, QuantLib::Date, long>
            (functionCall, bindObject, EndDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlDayCounterName(
        char *daycounter,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDayCounterName"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter daycounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(daycounter);

        // invoke the member function

        std::string returnValue = daycounterEnum.name();

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
XLL_DEC OPER *qlDayCounterYearFraction(
        char *daycounter,
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
            new ObjectHandler::FunctionCall("qlDayCounterYearFraction"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*StartDate));

        ObjectHandler::property_t RefPeriodStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodStart));

        ObjectHandler::property_t RefPeriodEndCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefPeriodEnd));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*StartDate), "StartDate");

        std::vector<QuantLib::Date> EndDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*EndDate, "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodStart), "RefPeriodStart", QuantLib::Date());

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefPeriodEnd), "RefPeriodEnd", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter daycounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(daycounter);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlDayCounterYearFractionBind bindObject = 
            boost::bind((QuantLibAddin::qlDayCounterYearFractionSignature)
                &QuantLib::DayCounter::yearFraction,
                daycounterEnum,
                StartDateLib,
                _1,
                RefPeriodStartLib,
                RefPeriodEndLib);
        ObjectHandler::loop
            <QuantLibAddin::qlDayCounterYearFractionBind, QuantLib::Date, double>
            (functionCall, bindObject, EndDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
