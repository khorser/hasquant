
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

#include <qlo/serialization/create/create_credit.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/credit.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/schedule.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/defaulttermstructure.hpp>
#include <ql/time/daycounter.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCreditDefaultSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BuyerSeller =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BuyerSeller"));

        double Notional =
            ObjectHandler::convert2<double>(valueObject->getProperty("Notional"));

        double Upfront =
            ObjectHandler::convert2<double>(valueObject->getProperty("Upfront"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string PremiumSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PremiumSchedule"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool SettlesAccrual =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettlesAccrual"));

        bool PayAtDefault =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayAtDefault"));

        ObjectHandler::property_t ProtectionStart =
            valueObject->getProperty("ProtectionStart");

        ObjectHandler::property_t UpfrontDate =
            valueObject->getProperty("UpfrontDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real NotionalLib = Notional;

        QuantLib::Date ProtectionStartLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ProtectionStart"), "ProtectionStart", QuantLib::Date());

        QuantLib::Date UpfrontDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("UpfrontDate"), "UpfrontDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSeller);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(PremiumSchedule);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CreditDefaultSwap(
                valueObject,
                BuyerSellerEnum,
                NotionalLib,
                Upfront,
                Spread,
                PremiumScheduleLibObjPtr,
                PaymentConventionEnum,
                DayCounterEnum,
                SettlesAccrual,
                PayAtDefault,
                ProtectionStartLib,
                UpfrontDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlHazardRateCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("CurveDates"), "CurveDates");

        std::vector<double> CurveRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CurveRates"), "CurveRates");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HazardRateCurve(
                valueObject,
                CurveDatesLib,
                CurveRates,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMidPointCdsEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string DefaultCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DefaultCurve"));

        double RecoveryRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecoveryRate"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real RecoveryRateLib = RecoveryRate;

        // convert object IDs into library objects

        OH_GET_OBJECT(DefaultCurveCoerce, DefaultCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> DefaultCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::DefaultProbabilityTermStructure,
                QuantLib::DefaultProbabilityTermStructure>()(
                    DefaultCurveCoerce);

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(DefaultCurve);
        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCdsEngine(
                valueObject,
                DefaultCurveLibObj,
                RecoveryRateLib,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlPiecewiseFlatForwardCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ReferenceDate =
            valueObject->getProperty("ReferenceDate");

        std::vector<std::string> RateHelpers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("RateHelpers"), "RateHelpers");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ReferenceDate"), "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = Accuracy;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpers);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = RateHelpers.begin();
                i != RateHelpers.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseFlatForwardCurve(
                valueObject,
                ReferenceDateLib,
                RateHelpersLibObjPtr,
                DayCounterEnum,
                AccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlPiecewiseFlatHazardRateCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ReferenceDate =
            valueObject->getProperty("ReferenceDate");

        std::vector<std::string> Helpers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("Helpers"), "Helpers");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ReferenceDate"), "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = Accuracy;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> > HelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::DefaultProbabilityHelper, QuantLib::DefaultProbabilityHelper>(Helpers);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = Helpers.begin();
                i != Helpers.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseFlatHazardRateCurve(
                valueObject,
                ReferenceDateLib,
                HelpersLibObjPtr,
                DayCounterEnum,
                AccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSpreadCdsHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RunningSpread =
            valueObject->getProperty("RunningSpread");

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Frequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Frequency"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        std::string GenRule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("GenRule"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        double RecoveryRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecoveryRate"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        bool SettleAccrual =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettleAccrual"));

        bool PayAtDefault =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayAtDefault"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Real RecoveryRateLib = RecoveryRate;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(Frequency);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        QuantLib::DateGeneration::Rule GenRuleEnum =
            ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(GenRule);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RunningSpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                RunningSpread, "RunningSpread");

        OH_GET_OBJECT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processVariant(RunningSpread);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadCdsHelper(
                valueObject,
                RunningSpreadLibObj,
                TenorLib,
                SettlementDays,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                RecoveryRateLib,
                DiscountingCurveLibObj,
                SettleAccrual,
                PayAtDefault,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlUpfrontCdsHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t UpfrontSpread =
            valueObject->getProperty("UpfrontSpread");

        double RunningSpread =
            ObjectHandler::convert2<double>(valueObject->getProperty("RunningSpread"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Frequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Frequency"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        std::string GenRule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("GenRule"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        double RecoveryRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecoveryRate"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        long UpfrontSettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("UpfrontSettlementDays"));

        bool SettleAccrual =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettleAccrual"));

        bool PayAtDefault =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayAtDefault"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Real RecoveryRateLib = RecoveryRate;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(Frequency);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        QuantLib::DateGeneration::Rule GenRuleEnum =
            ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(GenRule);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> UpfrontSpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                UpfrontSpread, "UpfrontSpread");

        OH_GET_OBJECT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processVariant(UpfrontSpread);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::UpfrontCdsHelper(
                valueObject,
                UpfrontSpreadLibObj,
                RunningSpread,
                TenorLib,
                SettlementDays,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                RecoveryRateLib,
                DiscountingCurveLibObj,
                UpfrontSettlementDays,
                SettleAccrual,
                PayAtDefault,
                Permanent));
        return object;
    }

}
