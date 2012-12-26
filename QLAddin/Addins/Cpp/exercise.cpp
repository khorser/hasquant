
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Cristina Duminuco
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <ql/exercise.hpp>
#include <qlo/exercise.hpp>
#include <qlo/valueobjects/vo_exercise.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAmericanExercise(
            const std::string &ObjectId,
            const ObjectHandler::property_t &EarliestDate,
            const ObjectHandler::property_t &LatestDate,
            const ObjectHandler::property_t &PayoffAtExpiry,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PayoffAtExpiryCpp = ObjectHandler::convert2<bool>(
            PayoffAtExpiry, "PayoffAtExpiry", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date EarliestDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EarliestDate, "EarliestDate");

        QuantLib::Date LatestDateLib = ObjectHandler::convert2<QuantLib::Date>(
            LatestDate, "LatestDate");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAmericanExercise(
                ObjectId,
                EarliestDate,
                LatestDate,
                PayoffAtExpiryCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AmericanExercise(
                valueObject,
                EarliestDateLib,
                LatestDateLib,
                PayoffAtExpiryCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAmericanExercise : " << e.what());
        }
    }


    std::string qlBermudanExercise(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& Dates,
            const ObjectHandler::property_t &PayoffAtExpiry,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PayoffAtExpiryCpp = ObjectHandler::convert2<bool>(
            PayoffAtExpiry, "PayoffAtExpiry", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(Dates, "Dates");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBermudanExercise(
                ObjectId,
                Dates,
                PayoffAtExpiryCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BermudanExercise(
                valueObject,
                DatesLib,
                PayoffAtExpiryCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBermudanExercise : " << e.what());
        }
    }


    std::string qlEuropeanExercise(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ExpiryDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ExpiryDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ExpiryDate, "ExpiryDate");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuropeanExercise(
                ObjectId,
                ExpiryDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuropeanExercise(
                valueObject,
                ExpiryDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEuropeanExercise : " << e.what());
        }
    }

}

