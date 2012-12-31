
/*  
 Copyright (C) 2006 Katiuscia Manzoni
 
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
#include <ql/prices.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC double *qlMidEquivalent(
        OPER *Bid,
        OPER *Ask,
        OPER *Last,
        OPER *Close,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMidEquivalent"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double BidCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Bid), "Bid", 0);

        double AskCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Ask), "Ask", 0);

        double LastCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Last), "Last", 0);

        double CloseCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Close), "Close", 0);

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::midEquivalent(
                BidCpp,
                AskCpp,
                LastCpp,
                CloseCpp);

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
XLL_DEC double *qlMidSafe(
        OPER *Bid,
        OPER *Ask,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMidSafe"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double BidCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Bid), "Bid", 0);

        double AskCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Ask), "Ask", 0);

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLib::midSafe(
                BidCpp,
                AskCpp);

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
