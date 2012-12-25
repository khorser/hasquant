
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

#include <qlo/serialization/create/create_vanillaswap.hpp>
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

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeIMMSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapTenor"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double FixedRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("FixedRate"));

        ObjectHandler::property_t FirstImmDate =
            valueObject->getProperty("FirstImmDate");

        std::string FixDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixDayCounter"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string PricingEngineID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PricingEngineID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Date FirstImmDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FirstImmDate"), "FirstImmDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(PricingEngineID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapTenorLib,
                IborIndexLibObjPtr,
                FixedRate,
                FirstImmDateLib,
                FixDayCounterEnum,
                Spread,
                PricingEngineIDLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeVanillaSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapTenor"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double FixedRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("FixedRate"));

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        std::string FixDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixDayCounter"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string PricingEngineID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PricingEngineID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(PricingEngineID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapTenorLib,
                IborIndexLibObjPtr,
                FixedRate,
                ForwardStartLib,
                FixDayCounterEnum,
                Spread,
                PricingEngineIDLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlVanillaSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PayerReceiver =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PayerReceiver"));

        double Nominal =
            ObjectHandler::convert2<double>(valueObject->getProperty("Nominal"));

        std::string FixSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixSchedule"));

        double FixedRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("FixedRate"));

        std::string FixDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixDayCounter"));

        std::string FloatingLegSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FloatingLegSchedule"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string FloatingLegDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FloatingLegDayCounter"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::VanillaSwap::Type PayerReceiverEnum =
            ObjectHandler::Create<QuantLib::VanillaSwap::Type>()(PayerReceiver);

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        QuantLib::DayCounter FloatingLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FloatingLegDayCounter);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        // convert object IDs into library objects

        OH_GET_REFERENCE(FixScheduleLibObjPtr, FixSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(FloatingLegScheduleLibObjPtr, FloatingLegSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FixSchedule);
        valueObject->processPrecedentID(FloatingLegSchedule);
        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                PayerReceiverEnum,
                Nominal,
                FixScheduleLibObjPtr,
                FixedRate,
                FixDayCounterEnum,
                FloatingLegScheduleLibObjPtr,
                IborIndexLibObjPtr,
                Spread,
                FloatingLegDayCounterEnum,
                PaymentConventionEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlVanillaSwapFromSwapIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        ObjectHandler::property_t FixingDate =
            valueObject->getProperty("FixingDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FixingDate"), "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SwapIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapIndexLibObjPtr,
                FixingDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlVanillaSwapFromSwapRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapRateHelper =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapRateHelper"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapRateHelperLibObjPtr, SwapRateHelper,
            QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SwapRateHelper);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaSwap(
                valueObject,
                SwapRateHelperLibObjPtr,
                Permanent));
        return object;
    }

}
