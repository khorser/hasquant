
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

#include <qlo/serialization/create/create_couponvectors.hpp>
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

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCmsCouponPricer(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Volatility =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Volatility"));

        std::string CmsCouponPricerType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CmsCouponPricerType"));

        std::string YieldCurveModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurveModel"));

        ObjectHandler::property_t MeanReversion =
            valueObject->getProperty("MeanReversion");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Volatility);
        valueObject->processVariant(MeanReversion);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsCouponPricer(
                valueObject,
                VolatilityLibObj,
                CmsCouponPricerType,
                YieldCurveModelEnum,
                MeanReversionLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCmsLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<long> FixingDays =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("FixingDays"), "FixingDays");

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

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

        // convert input datatypes to QuantLib enumerated datatypes

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
            new QuantLibAddin::CmsLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrears,
                DayCounterEnum,
                Floors,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                Caps,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCmsZeroLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<long> FixingDays =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("FixingDays"), "FixingDays");

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

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

        // convert input datatypes to QuantLib enumerated datatypes

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
            new QuantLibAddin::CmsZeroLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrears,
                DayCounterEnum,
                Floors,
                Gearings,
                SwapIndexLibObjPtr,
                Spreads,
                Caps,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlConundrumPricerByNumericalIntegration(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwaptionVol =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwaptionVol"));

        std::string YieldCurveModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurveModel"));

        ObjectHandler::property_t MeanReversion =
            valueObject->getProperty("MeanReversion");

        ObjectHandler::property_t LowerLimit =
            valueObject->getProperty("LowerLimit");

        ObjectHandler::property_t UpperLimit =
            valueObject->getProperty("UpperLimit");

        ObjectHandler::property_t Precision =
            valueObject->getProperty("Precision");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real LowerLimitLib = LowerLimit;

        QuantLib::Real UpperLimitLib = UpperLimit;

        QuantLib::Real PrecisionLib = Precision;

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SwaptionVol);
        valueObject->processVariant(MeanReversion);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::NumericHaganPricer(
                valueObject,
                SwaptionVolLibObj,
                YieldCurveModelEnum,
                MeanReversionLibObj,
                LowerLimitLib,
                UpperLimitLib,
                PrecisionLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDigitalCmsLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<long> FixingDays =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("FixingDays"), "FixingDays");

        bool IsInArrears =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IsInArrears"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<double> Gearings =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Gearings"), "Gearings");

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        std::vector<double> Spreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Spreads"), "Spreads");

        std::vector<double> CallStrikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CallStrikes"), "CallStrikes");

        std::string CallSpecs =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CallSpecs"));

        std::vector<double> CallPayoff =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CallPayoff"), "CallPayoff");

        std::vector<double> PutStrikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PutStrikes"), "PutStrikes");

        std::string PutSpecs =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PutSpecs"));

        std::vector<double> PutPayoff =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PutPayoff"), "PutPayoff");

        std::string Replication =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Replication"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(ReplicationLibObjPtr, Replication,
            QuantLibAddin::DigitalReplication, QuantLib::DigitalReplication)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);
        valueObject->processPrecedentID(SwapIndex);
        valueObject->processPrecedentID(Replication);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalCmsLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrears,
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
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDigitalIborLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<long> FixingDays =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("FixingDays"), "FixingDays");

        bool IsInArrears =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IsInArrears"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<double> Gearings =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Gearings"), "Gearings");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::vector<double> Spreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Spreads"), "Spreads");

        std::vector<double> CallStrikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CallStrikes"), "CallStrikes");

        std::string CallSpecs =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CallSpecs"));

        std::vector<double> CallPayoff =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CallPayoff"), "CallPayoff");

        std::vector<double> PutStrikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PutStrikes"), "PutStrikes");

        std::string PutSpecs =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PutSpecs"));

        std::vector<double> PutPayoff =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PutPayoff"), "PutPayoff");

        std::string Replication =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Replication"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(ReplicationLibObjPtr, Replication,
            QuantLibAddin::DigitalReplication, QuantLib::DigitalReplication)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(Replication);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalIborLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrears,
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
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDigitalReplication(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Replication =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Replication"));

        ObjectHandler::property_t Gap =
            valueObject->getProperty("Gap");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GapLib = Gap;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Replication::Type ReplicationEnum =
            ObjectHandler::Create<QuantLib::Replication::Type>()(Replication);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DigitalReplication(
                valueObject,
                ReplicationEnum,
                GapLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFixedRateLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<double> Coupons =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Coupons"), "Coupons");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ScheduleID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                Coupons,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFixedRateLeg2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<std::string> Coupons =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("Coupons"), "Coupons");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

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
            new QuantLibAddin::FixedRateLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                CouponsLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIborCouponPricer(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Volatility =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Volatility"));

        std::string IborCouponPricerType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborCouponPricerType"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT(VolatilityCoerce, Volatility, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolatilityLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    VolatilityCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Volatility);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IborCouponPricer(
                valueObject,
                VolatilityLibObj,
                IborCouponPricerType,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIborLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<long> FixingDays =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("FixingDays"), "FixingDays");

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

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

        // convert input datatypes to QuantLib enumerated datatypes

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
            new QuantLibAddin::IborLeg(
                valueObject,
                PaymentBDCEnum,
                Nominals,
                ScheduleIDLibObjPtr,
                FixingDaysLib,
                IsInArrears,
                DayCounterEnum,
                Floors,
                Gearings,
                IborIndexLibObjPtr,
                Spreads,
                Caps,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRangeAccrualLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        std::vector<double> Nominals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominals"), "Nominals");

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<long> FixingDays =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("FixingDays"), "FixingDays");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::vector<double> LowerStrikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("LowerStrikes"), "LowerStrikes");

        std::vector<double> Gearings =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Gearings"), "Gearings");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::vector<double> Spreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Spreads"), "Spreads");

        std::vector<double> UpperStrikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("UpperStrikes"), "UpperStrikes");

        std::string ObservationsTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ObservationsTenor"));

        std::string ObservationsBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ObservationsBDC"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Natural> FixingDaysLib = 
            QuantLibAddin::convertVector<long, QuantLib::Natural>(FixingDays);

        QuantLib::Period ObservationsTenorLib;
        QuantLibAddin::cppToLibrary(ObservationsTenor, ObservationsTenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention ObservationsBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ObservationsBDC);

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
                Permanent));
        return object;
    }

}
