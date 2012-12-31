
/*  
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 
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
#include <oh/enumerations/typefactory.hpp>
#include <qlo/rangeaccrual.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/smilesection.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/cashflows/rangeaccrual.hpp>
#include <ql/indexes/iborindex.hpp>
#include <qlo/valueobjects/vo_rangeaccrual.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlRangeAccrualFloatersCoupon(
            const std::string &ObjectId,
            const double &Nominal,
            const ObjectHandler::property_t &PaymentDate,
            const std::string &IborIndex,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const long &FixingDays,
            const std::string &DayCountID,
            const double &Gearings,
            const double &Spreads,
            const ObjectHandler::property_t &RefPeriodStart,
            const ObjectHandler::property_t &RefPeriodEnd,
            const std::string &ObserSchedID,
            const double &LowerTrigger,
            const double &UpperTrigger,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date PaymentDateLib = ObjectHandler::convert2<QuantLib::Date>(
            PaymentDate, "PaymentDate");

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EndDate, "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            RefPeriodStart, "RefPeriodStart");

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            RefPeriodEnd, "RefPeriodEnd");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCountIDEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCountID);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(ObserSchedIDLibObjPtr, ObserSchedID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRangeAccrualFloatersCoupon(
                ObjectId,
                Nominal,
                PaymentDate,
                IborIndex,
                StartDate,
                EndDate,
                FixingDays,
                DayCountID,
                Gearings,
                Spreads,
                RefPeriodStart,
                RefPeriodEnd,
                ObserSchedID,
                LowerTrigger,
                UpperTrigger,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualFloatersCoupon(
                valueObject,
                Nominal,
                PaymentDateLib,
                IborIndexLibObjPtr,
                StartDateLib,
                EndDateLib,
                FixingDays,
                DayCountIDEnum,
                Gearings,
                Spreads,
                RefPeriodStartLib,
                RefPeriodEndLib,
                ObserSchedIDLibObjPtr,
                LowerTrigger,
                UpperTrigger,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRangeAccrualFloatersCoupon : " << e.what());
        }
    }


    std::string qlRangeAccrualFloatersCouponFromLeg(
            const std::string &ObjectId,
            const std::string &RangeAccrualLeg,
            const long &Position,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size PositionLib;
        QuantLibAddin::cppToLibrary(Position, PositionLib);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(RangeAccrualLegLibObj, RangeAccrualLeg,
            QuantLibAddin::Leg, QuantLib::Leg)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRangeAccrualFloatersCouponFromLeg(
                ObjectId,
                RangeAccrualLeg,
                Position,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualFloatersCoupon(
                valueObject,
                RangeAccrualLegLibObj,
                PositionLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRangeAccrualFloatersCouponFromLeg : " << e.what());
        }
    }


    std::string qlRangeAccrualPricerByBgm(
            const std::string &ObjectId,
            const double &Correlation,
            const std::string &SmileOnStartDateID,
            const std::string &SmileOnEndDateID,
            const bool &WithSmile,
            const bool &ByCallSpread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SmileOnStartDateIDLibObjPtr, SmileOnStartDateID,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        OH_GET_REFERENCE(SmileOnEndDateIDLibObjPtr, SmileOnEndDateID,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRangeAccrualPricerByBgm(
                ObjectId,
                Correlation,
                SmileOnStartDateID,
                SmileOnEndDateID,
                WithSmile,
                ByCallSpread,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualPricerByBgm(
                valueObject,
                Correlation,
                SmileOnStartDateIDLibObjPtr,
                SmileOnEndDateIDLibObjPtr,
                WithSmile,
                ByCallSpread,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRangeAccrualPricerByBgm : " << e.what());
        }
    }

}

