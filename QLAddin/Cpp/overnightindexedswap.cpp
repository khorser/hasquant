
/*  
 Copyright (C) 2009, 2011 Ferdinando Ametrano
 
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
#include <qlo/overnightindexedswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/ratehelpers.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>
#include <qlo/valueobjects/vo_overnightindexedswap.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlMakeDatedOIS(
            const std::string &ObjectId,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const std::string &OvernightIndex,
            const ObjectHandler::property_t &FixedRate,
            const ObjectHandler::property_t &FixDayCounter,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FixedRateCpp = ObjectHandler::convert2<double>(
            FixedRate, "FixedRate", QuantLib::Null<QuantLib::Rate>());

        std::string FixDayCounterCpp = ObjectHandler::convert2<std::string>(
            FixDayCounter, "FixDayCounter", "Actual/360");

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate", QuantLib::Date());

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EndDate, "EndDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeDatedOIS(
                ObjectId,
                StartDate,
                EndDate,
                OvernightIndex,
                FixedRateCpp,
                FixDayCounterCpp,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                StartDateLib,
                EndDateLib,
                OvernightIndexLibObjPtr,
                FixedRateCpp,
                FixDayCounterEnum,
                SpreadCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMakeDatedOIS : " << e.what());
        }
    }


    std::string qlMakeOIS(
            const std::string &ObjectId,
            const std::string &SwapTenor,
            const std::string &OvernightIndex,
            const ObjectHandler::property_t &FixedRate,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &FixDayCounter,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double FixedRateCpp = ObjectHandler::convert2<double>(
            FixedRate, "FixedRate", QuantLib::Null<QuantLib::Rate>());

        std::string FixDayCounterCpp = ObjectHandler::convert2<std::string>(
            FixDayCounter, "FixDayCounter", "Actual/360");

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

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeOIS(
                ObjectId,
                SwapTenor,
                OvernightIndex,
                FixedRateCpp,
                ForwardStart,
                FixDayCounterCpp,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                SwapTenorLib,
                OvernightIndexLibObjPtr,
                FixedRateCpp,
                ForwardStartLib,
                FixDayCounterEnum,
                SpreadCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMakeOIS : " << e.what());
        }
    }


    std::string qlOvernightIndexedSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PayerReceiver,
            const std::vector<double>& Nominal,
            const std::string &Schedule,
            const ObjectHandler::property_t &FixedRate,
            const std::string &FixDayCounter,
            const std::string &OvernightIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PayerReceiverCpp = ObjectHandler::convert2<std::string>(
            PayerReceiver, "PayerReceiver", "Payer");

        double FixedRateCpp = ObjectHandler::convert2<double>(
            FixedRate, "FixedRate", 0.0);

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> NominalLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Nominal);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::OvernightIndexedSwap::Type PayerReceiverEnum =
            ObjectHandler::Create<QuantLib::OvernightIndexedSwap::Type>()(PayerReceiverCpp);

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleLibObjPtr, Schedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOvernightIndexedSwap(
                ObjectId,
                PayerReceiverCpp,
                Nominal,
                Schedule,
                FixedRateCpp,
                FixDayCounter,
                OvernightIndex,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                PayerReceiverEnum,
                NominalLib,
                ScheduleLibObjPtr,
                FixedRateCpp,
                FixDayCounterEnum,
                OvernightIndexLibObjPtr,
                SpreadCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlOvernightIndexedSwap : " << e.what());
        }
    }


    std::string qlOvernightIndexedSwapFromOISRateHelper(
            const std::string &ObjectId,
            const std::string &OISRateHelper,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(OISRateHelperLibObjPtr, OISRateHelper,
            QuantLibAddin::OISRateHelper, QuantLib::OISRateHelper)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOvernightIndexedSwapFromOISRateHelper(
                ObjectId,
                OISRateHelper,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                OISRateHelperLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlOvernightIndexedSwapFromOISRateHelper : " << e.what());
        }
    }

}

