
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

#include <qlo/serialization/create/create_rangeaccrual.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/rangeaccrual.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/smilesection.hpp>
#include <ql/indexes/iborindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlRangeAccrualFloatersCoupon(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Nominal =
            ObjectHandler::convert2<double>(valueObject->getProperty("Nominal"));

        ObjectHandler::property_t PaymentDate =
            valueObject->getProperty("PaymentDate");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t EndDate =
            valueObject->getProperty("EndDate");

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string DayCountID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCountID"));

        double Gearings =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearings"));

        double Spreads =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spreads"));

        ObjectHandler::property_t RefPeriodStart =
            valueObject->getProperty("RefPeriodStart");

        ObjectHandler::property_t RefPeriodEnd =
            valueObject->getProperty("RefPeriodEnd");

        std::string ObserSchedID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ObserSchedID"));

        double LowerTrigger =
            ObjectHandler::convert2<double>(valueObject->getProperty("LowerTrigger"));

        double UpperTrigger =
            ObjectHandler::convert2<double>(valueObject->getProperty("UpperTrigger"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date PaymentDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("PaymentDate"), "PaymentDate");

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EndDate"), "EndDate");

        QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("RefPeriodStart"), "RefPeriodStart");

        QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("RefPeriodEnd"), "RefPeriodEnd");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCountIDEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCountID);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(ObserSchedIDLibObjPtr, ObserSchedID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(ObserSchedID);

        // construct and return the object

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
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRangeAccrualFloatersCouponFromLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string RangeAccrualLeg =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("RangeAccrualLeg"));

        long Position =
            ObjectHandler::convert2<long>(valueObject->getProperty("Position"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_UNDERLYING(RangeAccrualLegLibObj, RangeAccrualLeg,
            QuantLibAddin::Leg, QuantLib::Leg)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(RangeAccrualLeg);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualFloatersCoupon(
                valueObject,
                RangeAccrualLegLibObj,
                Position,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRangeAccrualPricerByBgm(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Correlation =
            ObjectHandler::convert2<double>(valueObject->getProperty("Correlation"));

        std::string SmileOnStartDateID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SmileOnStartDateID"));

        std::string SmileOnEndDateID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SmileOnEndDateID"));

        bool WithSmile =
            ObjectHandler::convert2<bool>(valueObject->getProperty("WithSmile"));

        bool ByCallSpread =
            ObjectHandler::convert2<bool>(valueObject->getProperty("ByCallSpread"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(SmileOnStartDateIDLibObjPtr, SmileOnStartDateID,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        OH_GET_REFERENCE(SmileOnEndDateIDLibObjPtr, SmileOnEndDateID,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SmileOnStartDateID);
        valueObject->processPrecedentID(SmileOnEndDateID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualPricerByBgm(
                valueObject,
                Correlation,
                SmileOnStartDateIDLibObjPtr,
                SmileOnEndDateIDLibObjPtr,
                WithSmile,
                ByCallSpread,
                Permanent));
        return object;
    }

}
