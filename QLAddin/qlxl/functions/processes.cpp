
/*  
 Copyright (C) 2004, 2005 Eric Ehlers
 
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
#include <qlo/processes.hpp>
#include <qlo/volatilities.hpp>
#include <qlo/valueobjects/vo_processes.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlGeneralizedBlackScholesProcess(
        char *ObjectId,
        char *BlackVolID,
        double *Underlying,
        OPER *DayCounter,
        OPER *SettlementDate,
        double *RiskFreeRate,
        double *DividendYield,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlGeneralizedBlackScholesProcess"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        ObjectHandler::property_t SettlementDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SettlementDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SettlementDate), "SettlementDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BlackVolIDLibObjPtr, BlackVolID,
            QuantLibAddin::BlackVolTermStructure, QuantLib::BlackVolTermStructure)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BlackVolIDStrip = ObjectHandler::CallingRange::getStub(BlackVolID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlGeneralizedBlackScholesProcess(
                ObjectIdStrip,
                BlackVolIDStrip,
                *Underlying,
                DayCounterCpp,
                SettlementDateCpp,
                *RiskFreeRate,
                *DividendYield,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GeneralizedBlackScholesProcess(
                valueObject,
                BlackVolIDLibObjPtr,
                *Underlying,
                DayCounterEnum,
                SettlementDateLib,
                *RiskFreeRate,
                *DividendYield,
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
