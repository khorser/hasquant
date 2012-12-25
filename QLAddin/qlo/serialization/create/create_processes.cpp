
/*  
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov
 
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
//      QuantLibAddin/gensrc/stubs/stub.serialization.includes

#include <qlo/serialization/create/create_processes.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/processes.hpp>
#include <qlo/volatilities.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlGeneralizedBlackScholesProcess(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BlackVolID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BlackVolID"));

        double Underlying =
            ObjectHandler::convert2<double>(valueObject->getProperty("Underlying"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t SettlementDate =
            valueObject->getProperty("SettlementDate");

        double RiskFreeRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RiskFreeRate"));

        double DividendYield =
            ObjectHandler::convert2<double>(valueObject->getProperty("DividendYield"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("SettlementDate"), "SettlementDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BlackVolIDLibObjPtr, BlackVolID,
            QuantLibAddin::BlackVolTermStructure, QuantLib::BlackVolTermStructure)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(BlackVolID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GeneralizedBlackScholesProcess(
                valueObject,
                BlackVolIDLibObjPtr,
                Underlying,
                DayCounterEnum,
                SettlementDateLib,
                RiskFreeRate,
                DividendYield,
                Permanent));
        return object;
    }

}
