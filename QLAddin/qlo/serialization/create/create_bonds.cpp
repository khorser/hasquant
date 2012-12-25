
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

#include <qlo/serialization/create/create_bonds.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/bonds.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/couponvectors.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/currency.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBond(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        ObjectHandler::property_t FaceAmount =
            valueObject->getProperty("FaceAmount");

        ObjectHandler::property_t MaturityDate =
            valueObject->getProperty("MaturityDate");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        std::string LegID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LegID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real FaceAmountLib = FaceAmount;

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("MaturityDate"), "MaturityDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(LegIDLibObj, LegID,
            QuantLibAddin::Leg, QuantLib::Leg)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(LegID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Bond(
                valueObject,
                Description,
                CurrencyEnum,
                SettlementDays,
                CalendarEnum,
                FaceAmountLib,
                MaturityDateLib,
                IssueDateLib,
                LegIDLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCmsRateBond(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        ObjectHandler::property_t FaceAmount =
            valueObject->getProperty("FaceAmount");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        bool IsInArrears =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IsInArrears"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<double> Floors =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Floors"), "Floors");

        std::vector<double> Gearings =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Gearings"), "Gearings");

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        std::vector<double> Spreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Spreads"), "Spreads");

        std::vector<double> Caps =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Caps"), "Caps");

        ObjectHandler::property_t Redemption =
            valueObject->getProperty("Redemption");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real FaceAmountLib = FaceAmount;

        QuantLib::Real RedemptionLib = Redemption;

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);
        valueObject->processPrecedentID(SwapIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsRateBond(
                valueObject,
                Description,
                CurrencyEnum,
                SettlementDays,
                PaymentBDCEnum,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                FixingDays,
                IsInArrears,
                DayCounterEnum,
                Floors,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                Caps,
                RedemptionLib,
                IssueDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFixedRateBond(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        ObjectHandler::property_t FaceAmount =
            valueObject->getProperty("FaceAmount");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<double> Coupons =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Coupons"), "Coupons");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        ObjectHandler::property_t Redemption =
            valueObject->getProperty("Redemption");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        std::string PaymentCalendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentCalendar"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real FaceAmountLib = FaceAmount;

        QuantLib::Real RedemptionLib = Redemption;

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBond(
                valueObject,
                Description,
                CurrencyEnum,
                SettlementDays,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                Coupons,
                DayCounterEnum,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PaymentCalendarEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFixedRateBond2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        ObjectHandler::property_t FaceAmount =
            valueObject->getProperty("FaceAmount");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<std::string> Coupons =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("Coupons"), "Coupons");

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        ObjectHandler::property_t Redemption =
            valueObject->getProperty("Redemption");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        std::string PaymentCalendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentCalendar"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real FaceAmountLib = FaceAmount;

        QuantLib::Real RedemptionLib = Redemption;

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        std::vector<boost::shared_ptr<QuantLib::InterestRate> > CouponsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRate, QuantLib::InterestRate>(Coupons);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);
        for (std::vector<std::string>::const_iterator i = Coupons.begin();
                i != Coupons.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBond(
                valueObject,
                Description,
                CurrencyEnum,
                SettlementDays,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                CouponsLibObjPtr,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PaymentCalendarEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFloatingRateBond(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        ObjectHandler::property_t FaceAmount =
            valueObject->getProperty("FaceAmount");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        bool IsInArrears =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IsInArrears"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<double> Floors =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Floors"), "Floors");

        std::vector<double> Gearings =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Gearings"), "Gearings");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::vector<double> Spreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Spreads"), "Spreads");

        std::vector<double> Caps =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Caps"), "Caps");

        ObjectHandler::property_t Redemption =
            valueObject->getProperty("Redemption");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real FaceAmountLib = FaceAmount;

        QuantLib::Real RedemptionLib = Redemption;

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);
        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FloatingRateBond(
                valueObject,
                Description,
                CurrencyEnum,
                SettlementDays,
                PaymentBDCEnum,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                FixingDays,
                IsInArrears,
                DayCounterEnum,
                Floors,
                Gearings,
                IborIndexLibObjPtr,
                Spreads,
                Caps,
                RedemptionLib,
                IssueDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlZeroCouponBond(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        ObjectHandler::property_t FaceAmount =
            valueObject->getProperty("FaceAmount");

        ObjectHandler::property_t Maturity =
            valueObject->getProperty("Maturity");

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        ObjectHandler::property_t Redemption =
            valueObject->getProperty("Redemption");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real FaceAmountLib = FaceAmount;

        QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("Maturity"), "Maturity");

        QuantLib::Real RedemptionLib = Redemption;

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ZeroCouponBond(
                valueObject,
                Description,
                CurrencyEnum,
                SettlementDays,
                CalendarEnum,
                FaceAmountLib,
                MaturityLib,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                Permanent));
        return object;
    }

}
