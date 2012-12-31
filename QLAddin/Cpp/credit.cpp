
/*  
 Copyright (C) 2010 Roland Lichters
 
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
#include <qlo/credit.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>
#include <ql/pricingengines/credit/midpointcdsengine.hpp>
#include <qlo/valueobjects/vo_credit.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlHazardRateCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveRates,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHazardRateCurve(
                ObjectId,
                CurveDates,
                CurveRates,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HazardRateCurve(
                valueObject,
                CurveDatesLib,
                CurveRates,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlHazardRateCurve : " << e.what());
        }
    }


    std::string qlMidPointCdsEngine(
            const std::string &ObjectId,
            const std::string &DefaultCurve,
            const double &RecoveryRate,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMidPointCdsEngine(
                ObjectId,
                DefaultCurve,
                RecoveryRate,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCdsEngine(
                valueObject,
                DefaultCurveLibObj,
                RecoveryRate,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMidPointCdsEngine : " << e.what());
        }
    }


    std::string qlPiecewiseFlatForwardCurve(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ReferenceDate,
            const std::vector<std::string>& RateHelpers,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ReferenceDate, "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpers);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseFlatForwardCurve(
                ObjectId,
                ReferenceDate,
                RateHelpers,
                DayCounterCpp,
                AccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseFlatForwardCurve(
                valueObject,
                ReferenceDateLib,
                RateHelpersLibObjPtr,
                DayCounterEnum,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPiecewiseFlatForwardCurve : " << e.what());
        }
    }


    std::string qlPiecewiseFlatHazardRateCurve(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ReferenceDate,
            const std::vector<std::string>& Helpers,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ReferenceDate, "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> > HelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::DefaultProbabilityHelper, QuantLib::DefaultProbabilityHelper>(Helpers);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseFlatHazardRateCurve(
                ObjectId,
                ReferenceDate,
                Helpers,
                DayCounterCpp,
                AccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseFlatHazardRateCurve(
                valueObject,
                ReferenceDateLib,
                HelpersLibObjPtr,
                DayCounterEnum,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPiecewiseFlatHazardRateCurve : " << e.what());
        }
    }


    std::string qlSpreadCdsHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &RunningSpread,
            const std::string &Tenor,
            const ObjectHandler::property_t &SettlementDays,
            const std::string &Calendar,
            const std::string &Frequency,
            const std::string &PaymentConvention,
            const std::string &GenRule,
            const std::string &DayCounter,
            const double &RecoveryRate,
            const std::string &DiscountingCurve,
            const ObjectHandler::property_t &SettleAccrual,
            const ObjectHandler::property_t &PayAtDefault,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            SettlementDays, "SettlementDays", 0);

        bool SettleAccrualCpp = ObjectHandler::convert2<bool>(
            SettleAccrual, "SettleAccrual", true);

        bool PayAtDefaultCpp = ObjectHandler::convert2<bool>(
            PayAtDefault, "PayAtDefault", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural SettlementDaysLib = ObjectHandler::convert2<long>(
            SettlementDays, "SettlementDays", 0);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSpreadCdsHelper(
                ObjectId,
                RunningSpread,
                Tenor,
                SettlementDaysCpp,
                Calendar,
                Frequency,
                PaymentConvention,
                GenRule,
                DayCounter,
                RecoveryRate,
                DiscountingCurve,
                SettleAccrualCpp,
                PayAtDefaultCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadCdsHelper(
                valueObject,
                RunningSpreadLibObj,
                TenorLib,
                SettlementDaysLib,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                RecoveryRate,
                DiscountingCurveLibObj,
                SettleAccrualCpp,
                PayAtDefaultCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSpreadCdsHelper : " << e.what());
        }
    }

}

