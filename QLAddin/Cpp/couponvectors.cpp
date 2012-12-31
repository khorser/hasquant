
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
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

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCmsCouponPricer(
            const std::string &ObjectId,
            const std::string &Volatility,
            const std::string &CmsCouponPricerType,
            const std::string &YieldCurveModel,
            const ObjectHandler::property_t &MeanReversion,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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
                MeanReversion, "MeanReversion");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsCouponPricer(
                ObjectId,
                Volatility,
                CmsCouponPricerType,
                YieldCurveModel,
                MeanReversion,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCmsCouponPricer : " << e.what());
        }
    }


    std::string qlCmsLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                FixingDays,
                IsInArrearsCpp,
                DayCounter,
                Floors,
                Gearings,
                SwapIndex,
                Spreads,
                Caps,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Floors,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                Caps,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCmsLeg : " << e.what());
        }
    }


    std::string qlCmsZeroLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsZeroLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                FixingDays,
                IsInArrearsCpp,
                DayCounter,
                Floors,
                Gearings,
                SwapIndex,
                Spreads,
                Caps,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsZeroLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Floors,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                Caps,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCmsZeroLeg : " << e.what());
        }
    }


    std::string qlConundrumPricerByNumericalIntegration(
            const std::string &ObjectId,
            const std::string &SwaptionVol,
            const std::string &YieldCurveModel,
            const ObjectHandler::property_t &MeanReversion,
            const ObjectHandler::property_t &LowerLimit,
            const ObjectHandler::property_t &UpperLimit,
            const ObjectHandler::property_t &Precision,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double LowerLimitCpp = ObjectHandler::convert2<double>(
            LowerLimit, "LowerLimit", 0.0);

        double UpperLimitCpp = ObjectHandler::convert2<double>(
            UpperLimit, "UpperLimit", 1.0);

        double PrecisionCpp = ObjectHandler::convert2<double>(
            Precision, "Precision", 1.0e-6);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real LowerLimitLib = ObjectHandler::convert2<QuantLib::Real>(
            LowerLimit, "LowerLimit", 0.0);

        QuantLib::Real UpperLimitLib = ObjectHandler::convert2<QuantLib::Real>(
            UpperLimit, "UpperLimit", 1.0);

        QuantLib::Real PrecisionLib = ObjectHandler::convert2<QuantLib::Real>(
            Precision, "Precision", 1.0e-6);

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
                MeanReversion, "MeanReversion");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlConundrumPricerByNumericalIntegration(
                ObjectId,
                SwaptionVol,
                YieldCurveModel,
                MeanReversion,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlConundrumPricerByNumericalIntegration : " << e.what());
        }
    }


    std::string qlDigitalCmsLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Gearings,
            const std::string &SwapIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string &CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string &PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string &Replication,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDigitalCmsLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                FixingDays,
                IsInArrearsCpp,
                DayCounter,
                Gearings,
                SwapIndex,
                Spreads,
                CallStrikes,
                CallSpecs,
                CallPayoff,
                PutStrikes,
                PutSpecs,
                PutPayoff,
                Replication,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalCmsLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                CallStrikes,
                CallSpecs,
                CallPayoff,
                PutStrikes,
                PutSpecs,
                PutPayoff,
                ReplicationLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlDigitalCmsLeg : " << e.what());
        }
    }


    std::string qlDigitalIborLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& CallStrikes,
            const std::string &CallSpecs,
            const std::vector<double>& CallPayoff,
            const std::vector<double>& PutStrikes,
            const std::string &PutSpecs,
            const std::vector<double>& PutPayoff,
            const std::string &Replication,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDigitalIborLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                FixingDays,
                IsInArrearsCpp,
                DayCounter,
                Gearings,
                IborIndex,
                Spreads,
                CallStrikes,
                CallSpecs,
                CallPayoff,
                PutStrikes,
                PutSpecs,
                PutPayoff,
                Replication,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalIborLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Gearings,
                IborIndexLibObjPtr,
                Spreads,
                CallStrikes,
                CallSpecs,
                CallPayoff,
                PutStrikes,
                PutSpecs,
                PutPayoff,
                ReplicationLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlDigitalIborLeg : " << e.what());
        }
    }


    std::string qlFixedRateLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<double>& Coupons,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                Coupons,
                DayCounter,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                Coupons,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFixedRateLeg : " << e.what());
        }
    }


    std::string qlFixedRateLeg2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<std::string>& Coupons,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDCCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        std::vector<boost::shared_ptr<QuantLib::InterestRate> > CouponsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRate, QuantLib::InterestRate>(Coupons);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFixedRateLeg2(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                Coupons,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                CouponsLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFixedRateLeg2 : " << e.what());
        }
    }


    std::string qlIborCouponPricer(
            const std::string &ObjectId,
            const std::string &Volatility,
            const std::string &IborCouponPricerType,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolatilityCoerce, Volatility, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolatilityLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    VolatilityCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIborCouponPricer(
                ObjectId,
                Volatility,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlIborCouponPricer : " << e.what());
        }
    }


    std::string qlIborLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const ObjectHandler::property_t &IsInArrears,
            const std::string &DayCounter,
            const std::vector<double>& Floors,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& Caps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        bool IsInArrearsCpp = ObjectHandler::convert2<bool>(
            IsInArrears, "IsInArrears", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIborLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                FixingDays,
                IsInArrearsCpp,
                DayCounter,
                Floors,
                Gearings,
                IborIndex,
                Spreads,
                Caps,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IborLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrearsCpp,
                DayCounterEnum,
                Floors,
                Gearings,
                IborIndexLibObjPtr,
                Spreads,
                Caps,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlIborLeg : " << e.what());
        }
    }


    std::string qlRangeAccrualLeg(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PaymentBDC,
            const std::vector<double>& Nominals,
            const std::string &ScheduleID,
            const std::vector<long>& FixingDays,
            const std::string &DayCounter,
            const std::vector<double>& LowerStrikes,
            const std::vector<double>& Gearings,
            const std::string &IborIndex,
            const std::vector<double>& Spreads,
            const std::vector<double>& UpperStrikes,
            const std::string &ObservationsTenor,
            const ObjectHandler::property_t &ObservationsBDC,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDCCpp = ObjectHandler::convert2<std::string>(
            PaymentBDC, "PaymentBDC", "Following");

        std::string ObservationsBDCCpp = ObjectHandler::convert2<std::string>(
            ObservationsBDC, "ObservationsBDC", "Modified Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRangeAccrualLeg(
                ObjectId,
                PaymentBDCCpp,
                Nominals,
                ScheduleID,
                FixingDays,
                DayCounter,
                LowerStrikes,
                Gearings,
                IborIndex,
                Spreads,
                UpperStrikes,
                ObservationsTenor,
                ObservationsBDCCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RangeAccrualLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                DayCounterEnum,
                LowerStrikes,
                Gearings,
                IborIndexLibObjPtr,
                Spreads,
                UpperStrikes,
                ObservationsTenorLib,
                ObservationsBDCEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRangeAccrualLeg : " << e.what());
        }
    }

}

