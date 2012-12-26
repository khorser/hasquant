
/*  
 Copyright (C) 2006, 2007 Chiara Fornarola
 Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Walter Penschke
 Copyright (C) 2009 Piter Dias
 
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
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/couponvectors.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/pricingengines/bond/bondfunctions.hpp>
#include <ql/currency.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/valueobjects/vo_bonds.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &Currency,
            const ObjectHandler::property_t &SettlementDays,
            const ObjectHandler::property_t &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &MaturityDate,
            const ObjectHandler::property_t &IssueDate,
            const std::string &LegID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        std::string CurrencyCpp = ObjectHandler::convert2<std::string>(
            Currency, "Currency", "NullCurrency");

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            SettlementDays, "SettlementDays", 3);

        std::string CalendarCpp = ObjectHandler::convert2<std::string>(
            Calendar, "Calendar", "NullCalendar");

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            SettlementDays, "SettlementDays", 3);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            FaceAmount, "FaceAmount", 100.0);

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            MaturityDate, "MaturityDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(CurrencyCpp);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(CalendarCpp);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(LegIDLibObj, LegID,
            QuantLibAddin::Leg, QuantLib::Leg)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBond(
                ObjectId,
                DescriptionCpp,
                CurrencyCpp,
                SettlementDaysCpp,
                CalendarCpp,
                FaceAmountCpp,
                MaturityDate,
                IssueDate,
                LegID,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Bond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                CalendarEnum,
                FaceAmountLib,
                MaturityDateLib,
                IssueDateLib,
                LegIDLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBond : " << e.what());
        }
    }


    std::string qlCmsRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const ObjectHandler::property_t &FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        long FixingDaysCpp = ObjectHandler::convert2<long>(
            FixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            FaceAmount, "FaceAmount", 100.0);

        QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
            FixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            Redemption, "Redemption", 100);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsRateBond(
                ObjectId,
                DescriptionCpp,
                Currency,
                SettlementDays,
                PaymentBDCCpp,
                FaceAmountCpp,
                ScheduleID,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                Floors,
                Gearings,
                SwapIndex,
                Spreads,
                Caps,
                RedemptionCpp,
                IssueDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                PaymentBDCEnum,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Floors,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                Caps,
                RedemptionLib,
                IssueDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCmsRateBond : " << e.what());
        }
    }


    std::string qlFixedRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const std::string &PaymentCalendar,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            FaceAmount, "FaceAmount", 100.0);

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            Redemption, "Redemption", 100.0);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateBond(
                ObjectId,
                DescriptionCpp,
                Currency,
                SettlementDays,
                FaceAmountCpp,
                ScheduleID,
                Coupons,
                DayCounter,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDate,
                PaymentCalendar,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                Coupons,
                DayCounterEnum,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PaymentCalendarEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFixedRateBond : " << e.what());
        }
    }


    std::string qlFixedRateBond2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const std::vector<std::string>& Coupons,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const std::string &PaymentCalendar,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            FaceAmount, "FaceAmount", 100.0);

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            Redemption, "Redemption", 100.0);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        std::vector<boost::shared_ptr<QuantLib::InterestRate> > CouponsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRate, QuantLib::InterestRate>(Coupons);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateBond2(
                ObjectId,
                DescriptionCpp,
                Currency,
                SettlementDays,
                FaceAmountCpp,
                ScheduleID,
                Coupons,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDate,
                PaymentCalendar,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                CouponsLibObjPtr,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PaymentCalendarEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFixedRateBond2 : " << e.what());
        }
    }


    std::string qlFloatingRateBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &FaceAmount,
            const std::string &ScheduleID,
            const ObjectHandler::property_t &FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        long FixingDaysCpp = ObjectHandler::convert2<long>(
            FixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            FaceAmount, "FaceAmount", 100.0);

        QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
            FixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            Redemption, "Redemption", 100);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFloatingRateBond(
                ObjectId,
                DescriptionCpp,
                Currency,
                SettlementDays,
                PaymentBDCCpp,
                FaceAmountCpp,
                ScheduleID,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                Floors,
                Gearings,
                IborIndex,
                Spreads,
                Caps,
                RedemptionCpp,
                IssueDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FloatingRateBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                PaymentBDCEnum,
                FaceAmountLib,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Floors,
                Gearings,
                IborIndexLibObjPtr,
                Spreads,
                Caps,
                RedemptionLib,
                IssueDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFloatingRateBond : " << e.what());
        }
    }


    std::string qlZeroCouponBond(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const std::string &Currency,
            const long &SettlementDays,
            const std::string &Calendar,
            const ObjectHandler::property_t &FaceAmount,
            const ObjectHandler::property_t &Maturity,
            const ObjectHandler::property_t &PaymentBDC,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        double FaceAmountCpp = ObjectHandler::convert2<double>(
            FaceAmount, "FaceAmount", 100.0);

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        QuantLib::Real FaceAmountLib = ObjectHandler::convert2<QuantLib::Real>(
            FaceAmount, "FaceAmount", 100.0);

        QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            Maturity, "Maturity");

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            Redemption, "Redemption", 100);

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlZeroCouponBond(
                ObjectId,
                DescriptionCpp,
                Currency,
                SettlementDays,
                Calendar,
                FaceAmountCpp,
                Maturity,
                PaymentBDCCpp,
                RedemptionCpp,
                IssueDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ZeroCouponBond(
                valueObject,
                DescriptionCpp,
                CurrencyEnum,
                SettlementDaysLib,
                CalendarEnum,
                FaceAmountLib,
                MaturityLib,
                PaymentBDCEnum,
                RedemptionLib,
                IssueDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlZeroCouponBond : " << e.what());
        }
    }

}

