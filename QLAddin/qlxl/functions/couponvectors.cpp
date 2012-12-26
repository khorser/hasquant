
/*  
 Copyright (C) 2006, 2007, 2009 Ferdinando Ametrano
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 Copyright (C) 2005 Aurelien Chanudet
 
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
#include <qlo/couponvectors.hpp>
#include <qlo/schedule.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/valueobjects/vo_couponvectors.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlCmsCouponPricer(
        char *ObjectId,
        char *Volatility,
        char *CmsCouponPricerType,
        char *YieldCurveModel,
        OPER *MeanReversion,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCmsCouponPricer"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t MeanReversionCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*MeanReversion));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::GFunctionFactory::YieldCurveModel YieldCurveModelEnum =
            ObjectHandler::Create<QuantLib::GFunctionFactory::YieldCurveModel>()(YieldCurveModel);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolatilityCoerce, Volatility, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> VolatilityLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    VolatilityCoerce);

        QuantLib::Handle<QuantLib::Quote> MeanReversionLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*MeanReversion), "MeanReversion");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string VolatilityStrip = ObjectHandler::CallingRange::getStub(Volatility);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsCouponPricer(
                ObjectIdStrip,
                VolatilityStrip,
                CmsCouponPricerType,
                YieldCurveModel,
                MeanReversionCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsCouponPricer(
                valueObject,
                VolatilityLibObj,
                CmsCouponPricerType,
                YieldCurveModelEnum,
                MeanReversionLibObj,
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
XLL_DEC char *qlCmsLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Floors,
        OPER *Gearings,
        char *SwapIndex,
        OPER *Spreads,
        OPER *Caps,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCmsLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<long> FixingDaysCpp =
            ObjectHandler::operToVector<long>(*FixingDays, "FixingDays");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> FloorsCpp =
            ObjectHandler::operToVector<double>(*Floors, "Floors");

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CapsCpp =
            ObjectHandler::operToVector<double>(*Caps, "Caps");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDaysCpp);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                FloorsCpp,
                GearingsCpp,
                SwapIndexStrip,
                SpreadsCpp,
                CapsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                FloorsCpp,
                GearingsCpp,
                SwapIndexLibObjPtr,
                SpreadsCpp,
                CapsCpp,
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
XLL_DEC char *qlCmsZeroLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Floors,
        OPER *Gearings,
        char *SwapIndex,
        OPER *Spreads,
        OPER *Caps,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCmsZeroLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<long> FixingDaysCpp =
            ObjectHandler::operToVector<long>(*FixingDays, "FixingDays");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> FloorsCpp =
            ObjectHandler::operToVector<double>(*Floors, "Floors");

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CapsCpp =
            ObjectHandler::operToVector<double>(*Caps, "Caps");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDaysCpp);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsZeroLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                FloorsCpp,
                GearingsCpp,
                SwapIndexStrip,
                SpreadsCpp,
                CapsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsZeroLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                FloorsCpp,
                GearingsCpp,
                SwapIndexLibObjPtr,
                SpreadsCpp,
                CapsCpp,
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
XLL_DEC char *qlConundrumPricerByNumericalIntegration(
        char *ObjectId,
        char *SwaptionVol,
        char *YieldCurveModel,
        OPER *MeanReversion,
        OPER *LowerLimit,
        OPER *UpperLimit,
        OPER *Precision,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlConundrumPricerByNumericalIntegration"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t MeanReversionCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*MeanReversion));

        double LowerLimitCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*LowerLimit), "LowerLimit", 0.0);

        double UpperLimitCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*UpperLimit), "UpperLimit", 1.0);

        double PrecisionCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Precision), "Precision", 1.0e-6);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real LowerLimitLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*LowerLimit), "LowerLimit", 0.0);

        QuantLib::Real UpperLimitLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*UpperLimit), "UpperLimit", 1.0);

        QuantLib::Real PrecisionLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Precision), "Precision", 1.0e-6);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::GFunctionFactory::YieldCurveModel YieldCurveModelEnum =
            ObjectHandler::Create<QuantLib::GFunctionFactory::YieldCurveModel>()(YieldCurveModel);

        // convert object IDs into library objects

        OH_GET_OBJECT(SwaptionVolCoerce, SwaptionVol, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> SwaptionVolLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    SwaptionVolCoerce);

        QuantLib::Handle<QuantLib::Quote> MeanReversionLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*MeanReversion), "MeanReversion");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SwaptionVolStrip = ObjectHandler::CallingRange::getStub(SwaptionVol);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlConundrumPricerByNumericalIntegration(
                ObjectIdStrip,
                SwaptionVolStrip,
                YieldCurveModel,
                MeanReversionCpp,
                LowerLimitCpp,
                UpperLimitCpp,
                PrecisionCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::NumericHaganPricer(
                valueObject,
                SwaptionVolLibObj,
                YieldCurveModelEnum,
                MeanReversionLibObj,
                LowerLimitLib,
                UpperLimitLib,
                PrecisionLib,
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
XLL_DEC double *qlConundrumPricerByNumericalIntegrationUpperLimit(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlConundrumPricerByNumericalIntegrationUpperLimit"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::NumericHaganPricer, QuantLib::NumericHaganPricer)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->upperLimit();

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlDigitalCmsLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Gearings,
        char *SwapIndex,
        OPER *Spreads,
        OPER *CallStrikes,
        char *CallSpecs,
        OPER *CallPayoff,
        OPER *PutStrikes,
        char *PutSpecs,
        OPER *PutPayoff,
        char *Replication,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDigitalCmsLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<long> FixingDaysCpp =
            ObjectHandler::operToVector<long>(*FixingDays, "FixingDays");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CallStrikesCpp =
            ObjectHandler::operToVector<double>(*CallStrikes, "CallStrikes");

        std::vector<double> CallPayoffCpp =
            ObjectHandler::operToVector<double>(*CallPayoff, "CallPayoff");

        std::vector<double> PutStrikesCpp =
            ObjectHandler::operToVector<double>(*PutStrikes, "PutStrikes");

        std::vector<double> PutPayoffCpp =
            ObjectHandler::operToVector<double>(*PutPayoff, "PutPayoff");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDaysCpp);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(ReplicationLibObjPtr, Replication,
            QuantLibAddin::DigitalReplication, QuantLib::DigitalReplication)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);
        std::string ReplicationStrip = ObjectHandler::CallingRange::getStub(Replication);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDigitalCmsLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                GearingsCpp,
                SwapIndexStrip,
                SpreadsCpp,
                CallStrikesCpp,
                CallSpecs,
                CallPayoffCpp,
                PutStrikesCpp,
                PutSpecs,
                PutPayoffCpp,
                ReplicationStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalCmsLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                GearingsCpp,
                SwapIndexLibObjPtr,
                SpreadsCpp,
                CallStrikesCpp,
                CallSpecs,
                CallPayoffCpp,
                PutStrikesCpp,
                PutSpecs,
                PutPayoffCpp,
                ReplicationLibObjPtr,
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
XLL_DEC char *qlDigitalIborLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Gearings,
        char *IborIndex,
        OPER *Spreads,
        OPER *CallStrikes,
        char *CallSpecs,
        OPER *CallPayoff,
        OPER *PutStrikes,
        char *PutSpecs,
        OPER *PutPayoff,
        char *Replication,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDigitalIborLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<long> FixingDaysCpp =
            ObjectHandler::operToVector<long>(*FixingDays, "FixingDays");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CallStrikesCpp =
            ObjectHandler::operToVector<double>(*CallStrikes, "CallStrikes");

        std::vector<double> CallPayoffCpp =
            ObjectHandler::operToVector<double>(*CallPayoff, "CallPayoff");

        std::vector<double> PutStrikesCpp =
            ObjectHandler::operToVector<double>(*PutStrikes, "PutStrikes");

        std::vector<double> PutPayoffCpp =
            ObjectHandler::operToVector<double>(*PutPayoff, "PutPayoff");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDaysCpp);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(ReplicationLibObjPtr, Replication,
            QuantLibAddin::DigitalReplication, QuantLib::DigitalReplication)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);
        std::string ReplicationStrip = ObjectHandler::CallingRange::getStub(Replication);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDigitalIborLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                GearingsCpp,
                IborIndexStrip,
                SpreadsCpp,
                CallStrikesCpp,
                CallSpecs,
                CallPayoffCpp,
                PutStrikesCpp,
                PutSpecs,
                PutPayoffCpp,
                ReplicationStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalIborLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                GearingsCpp,
                IborIndexLibObjPtr,
                SpreadsCpp,
                CallStrikesCpp,
                CallSpecs,
                CallPayoffCpp,
                PutStrikesCpp,
                PutSpecs,
                PutPayoffCpp,
                ReplicationLibObjPtr,
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
XLL_DEC char *qlDigitalReplication(
        char *ObjectId,
        char *Replication,
        OPER *Gap,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDigitalReplication"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double GapCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Gap), "Gap", 0.0001);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GapLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Gap), "Gap", 0.0001);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Replication::Type ReplicationEnum =
            ObjectHandler::Create<QuantLib::Replication::Type>()(Replication);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDigitalReplication(
                ObjectIdStrip,
                Replication,
                GapCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalReplication(
                valueObject,
                ReplicationEnum,
                GapLib,
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
XLL_DEC char *qlFixedRateLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *Coupons,
        char *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFixedRateLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<double> CouponsCpp =
            ObjectHandler::operToVector<double>(*Coupons, "Coupons");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                CouponsCpp,
                DayCounter,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                CouponsCpp,
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
XLL_DEC char *qlFixedRateLeg2(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *Coupons,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFixedRateLeg2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<std::string> CouponsCpp =
            ObjectHandler::operToVector<std::string>(*Coupons, "Coupons");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        std::vector<boost::shared_ptr<QuantLib::InterestRate> > CouponsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRate, QuantLib::InterestRate>(CouponsCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateLeg2(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                CouponsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                CouponsLibObjPtr,
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
XLL_DEC char *qlIborCouponPricer(
        char *ObjectId,
        char *Volatility,
        char *IborCouponPricerType,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIborCouponPricer"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolatilityCoerce, Volatility, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolatilityLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    VolatilityCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string VolatilityStrip = ObjectHandler::CallingRange::getStub(Volatility);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIborCouponPricer(
                ObjectIdStrip,
                VolatilityStrip,
                IborCouponPricerType,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IborCouponPricer(
                valueObject,
                VolatilityLibObj,
                IborCouponPricerType,
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
XLL_DEC char *qlIborLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *FixingDays,
        OPER *IsInArrears,
        char *DayCounter,
        OPER *Floors,
        OPER *Gearings,
        char *IborIndex,
        OPER *Spreads,
        OPER *Caps,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIborLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<long> FixingDaysCpp =
            ObjectHandler::operToVector<long>(*FixingDays, "FixingDays");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*IsInArrears), "IsInArrears", false);

        std::vector<double> FloorsCpp =
            ObjectHandler::operToVector<double>(*Floors, "Floors");

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> CapsCpp =
            ObjectHandler::operToVector<double>(*Caps, "Caps");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDaysCpp);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIborLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                IsInArrearsCpp,
                DayCounter,
                FloorsCpp,
                GearingsCpp,
                IborIndexStrip,
                SpreadsCpp,
                CapsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IborLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                FloorsCpp,
                GearingsCpp,
                IborIndexLibObjPtr,
                SpreadsCpp,
                CapsCpp,
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
XLL_DEC char *qlRangeAccrualLeg(
        char *ObjectId,
        OPER *PaymentBDC,
        OPER *Nominals,
        char *ScheduleID,
        OPER *FixingDays,
        char *DayCounter,
        OPER *LowerStrikes,
        OPER *Gearings,
        char *IborIndex,
        OPER *Spreads,
        OPER *UpperStrikes,
        char *ObservationsTenor,
        OPER *ObservationsBDC,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRangeAccrualLeg"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*PaymentBDC), "PaymentBDC", "Following");

        std::vector<double> NominalsCpp =
            ObjectHandler::operToVector<double>(*Nominals, "Nominals");

        std::vector<long> FixingDaysCpp =
            ObjectHandler::operToVector<long>(*FixingDays, "FixingDays");

        std::vector<double> LowerStrikesCpp =
            ObjectHandler::operToVector<double>(*LowerStrikes, "LowerStrikes");

        std::vector<double> GearingsCpp =
            ObjectHandler::operToVector<double>(*Gearings, "Gearings");

        std::vector<double> SpreadsCpp =
            ObjectHandler::operToVector<double>(*Spreads, "Spreads");

        std::vector<double> UpperStrikesCpp =
            ObjectHandler::operToVector<double>(*UpperStrikes, "UpperStrikes");

        std::string ObservationsBDCCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*ObservationsBDC), "ObservationsBDC", "Modified Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDaysCpp);

        QuantLib::Period ObservationsTenorLib;
        QuantLibAddin::cppToLibrary(ObservationsTenor, ObservationsTenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention ObservationsBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ObservationsBDCCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string ScheduleIDStrip = ObjectHandler::CallingRange::getStub(ScheduleID);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRangeAccrualLeg(
                ObjectIdStrip,
                PaymentBDCCpp,
                NominalsCpp,
                ScheduleIDStrip,
                FixingDaysCpp,
                DayCounter,
                LowerStrikesCpp,
                GearingsCpp,
                IborIndexStrip,
                SpreadsCpp,
                UpperStrikesCpp,
                ObservationsTenor,
                ObservationsBDCCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualLeg(
                valueObject,
                PaymentBDCEnum,
                NominalsCpp,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                DayCounterEnum,
                LowerStrikesCpp,
                GearingsCpp,
                IborIndexLibObjPtr,
                SpreadsCpp,
                UpperStrikesCpp,
                ObservationsTenorLib,
                ObservationsBDCEnum,
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
