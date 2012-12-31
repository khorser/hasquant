
/*  
 Copyright (C) 2006, 2007, 2011 Ferdinando Ametrano
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
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
#include <qlo/vanillaswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/schedule.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <qlo/valueobjects/vo_vanillaswap.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlMakeIMMSwap(
            const std::string &ObjectId,
            const std::string &SwapTenor,
            const std::string &IborIndex,
            const ObjectHandler::property_t &FixedRate,
            const ObjectHandler::property_t &FirstImmDate,
            const ObjectHandler::property_t &FixDayCounter,
            const ObjectHandler::property_t &Spread,
            const std::string &PricingEngineID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FixedRateCpp = ObjectHandler::convert2<double>(
            FixedRate, "FixedRate", QuantLib::Null<QuantLib::Rate>());

        std::string FixDayCounterCpp = ObjectHandler::convert2<std::string>(
            FixDayCounter, "FixDayCounter", "30/360 (Bond Basis)");

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Date FirstImmDateLib = ObjectHandler::convert2<QuantLib::Date>(
            FirstImmDate, "FirstImmDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeIMMSwap(
                ObjectId,
                SwapTenor,
                IborIndex,
                FixedRateCpp,
                FirstImmDate,
                FixDayCounterCpp,
                SpreadCpp,
                PricingEngineID,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapTenorLib,
                IborIndexLibObjPtr,
                FixedRateCpp,
                FirstImmDateLib,
                FixDayCounterEnum,
                SpreadCpp,
                PricingEngineIDLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMakeIMMSwap : " << e.what());
        }
    }


    std::string qlMakeVanillaSwap(
            const std::string &ObjectId,
            const std::string &SwapTenor,
            const std::string &IborIndex,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &FixDayCounter,
            const ObjectHandler::property_t &Spread,
            const std::string &PricingEngineID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FixedRateCpp = ObjectHandler::convert2<double>(
            FixedRate, "FixedRate", QuantLib::Null<QuantLib::Rate>());

        std::string FixDayCounterCpp = ObjectHandler::convert2<std::string>(
            FixDayCounter, "FixDayCounter", "DayCounter");

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeVanillaSwap(
                ObjectId,
                SwapTenor,
                IborIndex,
                FixedRateCpp,
                ForwardStart,
                FixDayCounterCpp,
                SpreadCpp,
                PricingEngineID,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapTenorLib,
                IborIndexLibObjPtr,
                FixedRateCpp,
                ForwardStartLib,
                FixDayCounterEnum,
                SpreadCpp,
                PricingEngineIDLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMakeVanillaSwap : " << e.what());
        }
    }


    std::string qlVanillaSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PayerReceiver,
            const ObjectHandler::property_t &Nominal,
            const std::string &FixSchedule,
            const ObjectHandler::property_t &FixedRate,
            const std::string &FixDayCounter,
            const std::string &FloatingLegSchedule,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &FloatingLegDayCounter,
            const ObjectHandler::property_t &PaymentConvention,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PayerReceiverCpp = ObjectHandler::convert2<std::string>(
            PayerReceiver, "PayerReceiver", "Payer");

        double NominalCpp = ObjectHandler::convert2<double>(
            Nominal, "Nominal", 100);

        double FixedRateCpp = ObjectHandler::convert2<double>(
            FixedRate, "FixedRate", 0.0);

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        std::string PaymentConventionCpp = ObjectHandler::convert2<std::string>(
            PaymentConvention, "PaymentConvention", "Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::VanillaSwap::Type PayerReceiverEnum =
            ObjectHandler::Create<QuantLib::VanillaSwap::Type>()(PayerReceiverCpp);

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        QuantLib::DayCounter FloatingLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FloatingLegDayCounter);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConventionCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(FixScheduleLibObjPtr, FixSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(FloatingLegScheduleLibObjPtr, FloatingLegSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlVanillaSwap(
                ObjectId,
                PayerReceiverCpp,
                NominalCpp,
                FixSchedule,
                FixedRateCpp,
                FixDayCounter,
                FloatingLegSchedule,
                IborIndex,
                SpreadCpp,
                FloatingLegDayCounter,
                PaymentConventionCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                PayerReceiverEnum,
                NominalCpp,
                FixScheduleLibObjPtr,
                FixedRateCpp,
                FixDayCounterEnum,
                FloatingLegScheduleLibObjPtr,
                IborIndexLibObjPtr,
                SpreadCpp,
                FloatingLegDayCounterEnum,
                PaymentConventionEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlVanillaSwap : " << e.what());
        }
    }


    std::string qlVanillaSwapFromSwapIndex(
            const std::string &ObjectId,
            const std::string &SwapIndex,
            const ObjectHandler::property_t &FixingDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            FixingDate, "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlVanillaSwapFromSwapIndex(
                ObjectId,
                SwapIndex,
                FixingDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapIndexLibObjPtr,
                FixingDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlVanillaSwapFromSwapIndex : " << e.what());
        }
    }


    std::string qlVanillaSwapFromSwapRateHelper(
            const std::string &ObjectId,
            const std::string &SwapRateHelper,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapRateHelperLibObjPtr, SwapRateHelper,
            QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlVanillaSwapFromSwapRateHelper(
                ObjectId,
                SwapRateHelper,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapRateHelperLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlVanillaSwapFromSwapRateHelper : " << e.what());
        }
    }

}

