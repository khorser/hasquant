
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
//      QuantLibAddin/gensrc/stubs/stub.excel.includes

#include <qlo/qladdindefines.hpp>
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

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlCreditDefaultSwap(
        char *ObjectId,
        OPER *BuyerSeller,
        double *Notional,
        double *Upfront,
        double *Spread,
        char *PremiumSchedule,
        OPER *PaymentConvention,
        char *DayCounter,
        OPER *SettlesAccrual,
        OPER *PayAtDefault,
        OPER *ProtectionStart,
        OPER *UpfrontDate,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCreditDefaultSwap"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string BuyerSellerCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*BuyerSeller), "BuyerSeller", "Buyer");

        std::string PaymentConventionCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentConvention), "PaymentConvention", "Following");

        bool SettlesAccrualCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*SettlesAccrual), "SettlesAccrual", true);

        bool PayAtDefaultCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*PayAtDefault), "PayAtDefault", true);

        ObjectHandler::property_t ProtectionStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ProtectionStart));

        ObjectHandler::property_t UpfrontDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*UpfrontDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ProtectionStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ProtectionStart), "ProtectionStart", QuantLib::Date());

        QuantLib::Date UpfrontDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*UpfrontDate), "UpfrontDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSellerCpp);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConventionCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string PremiumScheduleStrip = ObjectHandler::CallingRange::getStub(PremiumSchedule);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCreditDefaultSwap(
                ObjectIdStrip,
                BuyerSellerCpp,
                *Notional,
                *Upfront,
                *Spread,
                PremiumScheduleStrip,
                PaymentConventionCpp,
                DayCounter,
                SettlesAccrualCpp,
                PayAtDefaultCpp,
                ProtectionStartCpp,
                UpfrontDateCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CreditDefaultSwap(
                valueObject,
                BuyerSellerEnum,
                *Notional,
                *Upfront,
                *Spread,
                PremiumScheduleLibObjPtr,
                PaymentConventionEnum,
                DayCounterEnum,
                SettlesAccrualCpp,
                PayAtDefaultCpp,
                ProtectionStartLib,
                UpfrontDateLib,
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
XLL_DEC char *qlHazardRateCurve(
        char *ObjectId,
        OPER *CurveDates,
        OPER *CurveRates,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlHazardRateCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*CurveDates, "CurveDates");

        std::vector<double> CurveRatesCpp =
            ObjectHandler::operToVector<double>(*CurveRates, "CurveRates");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHazardRateCurve(
                ObjectIdStrip,
                CurveDatesCpp,
                CurveRatesCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HazardRateCurve(
                valueObject,
                CurveDatesLib,
                CurveRatesCpp,
                DayCounterEnum,
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
XLL_DEC char *qlMidPointCdsEngine(
        char *ObjectId,
        char *DefaultCurve,
        double *RecoveryRate,
        char *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMidPointCdsEngine"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

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

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string DefaultCurveStrip = ObjectHandler::CallingRange::getStub(DefaultCurve);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMidPointCdsEngine(
                ObjectIdStrip,
                DefaultCurveStrip,
                *RecoveryRate,
                YieldCurveStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCdsEngine(
                valueObject,
                DefaultCurveLibObj,
                *RecoveryRate,
                YieldCurveLibObj,
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
XLL_DEC char *qlPiecewiseFlatForwardCurve(
        char *ObjectId,
        OPER *ReferenceDate,
        OPER *RateHelpers,
        OPER *DayCounter,
        OPER *Accuracy,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseFlatForwardCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ReferenceDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ReferenceDate));

        std::vector<std::string> RateHelpersCpp =
            ObjectHandler::operToVector<std::string>(*RateHelpers, "RateHelpers");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ReferenceDate), "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpersCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseFlatForwardCurve(
                ObjectIdStrip,
                ReferenceDateCpp,
                RateHelpersCpp,
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
XLL_DEC char *qlPiecewiseFlatHazardRateCurve(
        char *ObjectId,
        OPER *ReferenceDate,
        OPER *Helpers,
        OPER *DayCounter,
        OPER *Accuracy,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPiecewiseFlatHazardRateCurve"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ReferenceDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ReferenceDate));

        std::vector<std::string> HelpersCpp =
            ObjectHandler::operToVector<std::string>(*Helpers, "Helpers");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ReferenceDate), "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> > HelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::DefaultProbabilityHelper, QuantLib::DefaultProbabilityHelper>(HelpersCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseFlatHazardRateCurve(
                ObjectIdStrip,
                ReferenceDateCpp,
                HelpersCpp,
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
XLL_DEC char *qlSpreadCdsHelper(
        char *ObjectId,
        OPER *RunningSpread,
        char *Tenor,
        OPER *SettlementDays,
        char *Calendar,
        char *Frequency,
        char *PaymentConvention,
        char *GenRule,
        char *DayCounter,
        double *RecoveryRate,
        char *DiscountingCurve,
        OPER *SettleAccrual,
        OPER *PayAtDefault,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSpreadCdsHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RunningSpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RunningSpread));

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*SettlementDays), "SettlementDays", 0);

        bool SettleAccrualCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*SettleAccrual), "SettleAccrual", true);

        bool PayAtDefaultCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*PayAtDefault), "PayAtDefault", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural SettlementDaysLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*SettlementDays), "SettlementDays", 0);

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
                ObjectHandler::ConvertOper(*RunningSpread), "RunningSpread");

        OH_GET_OBJECT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string DiscountingCurveStrip = ObjectHandler::CallingRange::getStub(DiscountingCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSpreadCdsHelper(
                ObjectIdStrip,
                RunningSpreadCpp,
                Tenor,
                SettlementDaysCpp,
                Calendar,
                Frequency,
                PaymentConvention,
                GenRule,
                DayCounter,
                *RecoveryRate,
                DiscountingCurveStrip,
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
                *RecoveryRate,
                DiscountingCurveLibObj,
                SettleAccrualCpp,
                PayAtDefaultCpp,
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
XLL_DEC char *qlUpfrontCdsHelper(
        char *ObjectId,
        OPER *UpfrontSpread,
        double *RunningSpread,
        char *Tenor,
        OPER *SettlementDays,
        char *Calendar,
        char *Frequency,
        char *PaymentConvention,
        char *GenRule,
        char *DayCounter,
        double *RecoveryRate,
        char *DiscountingCurve,
        long *UpfrontSettlementDays,
        OPER *SettleAccrual,
        OPER *PayAtDefault,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlUpfrontCdsHelper"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t UpfrontSpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*UpfrontSpread));

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*SettlementDays), "SettlementDays", 0);

        bool SettleAccrualCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*SettleAccrual), "SettleAccrual", true);

        bool PayAtDefaultCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*PayAtDefault), "PayAtDefault", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural SettlementDaysLib = ObjectHandler::convert2<QuantLib::Natural>(
            ObjectHandler::ConvertOper(*SettlementDays), "SettlementDays", 0);

        QuantLib::Natural UpfrontSettlementDaysLib;
        QuantLibAddin::cppToLibrary(*UpfrontSettlementDays, UpfrontSettlementDaysLib);

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
                ObjectHandler::ConvertOper(*UpfrontSpread), "UpfrontSpread");

        OH_GET_OBJECT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string DiscountingCurveStrip = ObjectHandler::CallingRange::getStub(DiscountingCurve);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlUpfrontCdsHelper(
                ObjectIdStrip,
                UpfrontSpreadCpp,
                *RunningSpread,
                Tenor,
                SettlementDaysCpp,
                Calendar,
                Frequency,
                PaymentConvention,
                GenRule,
                DayCounter,
                *RecoveryRate,
                DiscountingCurveStrip,
                *UpfrontSettlementDays,
                SettleAccrualCpp,
                PayAtDefaultCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::UpfrontCdsHelper(
                valueObject,
                UpfrontSpreadLibObj,
                *RunningSpread,
                TenorLib,
                SettlementDaysLib,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                *RecoveryRate,
                DiscountingCurveLibObj,
                UpfrontSettlementDaysLib,
                SettleAccrualCpp,
                PayAtDefaultCpp,
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
