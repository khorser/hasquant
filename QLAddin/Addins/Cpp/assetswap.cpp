
/*  
 Copyright (C) 2009, 2011 Ferdinando Ametrano
 Copyright (C) 2006, 2007, Chiara Fornarola
 
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
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/assetswap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/bonds.hpp>
#include <ql/instruments/assetswap.hpp>
#include <ql/indexes/iborindex.hpp>
#include <qlo/valueobjects/vo_assetswap.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAssetSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &PayBondCoupon,
            const std::string &Bond,
            const double &CleanPrice,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &FloatingLegSchedule,
            const std::string &FloatingLegDayCounter,
            const ObjectHandler::property_t &ParAssetSwap,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PayBondCouponCpp = ObjectHandler::convert2<bool>(
            PayBondCoupon, "PayBondCoupon", false);

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        std::string FloatingLegScheduleCpp = ObjectHandler::convert2<std::string>(
            FloatingLegSchedule, "FloatingLegSchedule", "");

        bool ParAssetSwapCpp = ObjectHandler::convert2<bool>(
            ParAssetSwap, "ParAssetSwap", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FloatingLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FloatingLegDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE_DEFAULT(FloatingLegScheduleLibObjPtr, FloatingLegScheduleCpp,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAssetSwap(
                ObjectId,
                PayBondCouponCpp,
                Bond,
                CleanPrice,
                IborIndex,
                SpreadCpp,
                FloatingLegScheduleCpp,
                FloatingLegDayCounter,
                ParAssetSwapCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AssetSwap(
                valueObject,
                PayBondCouponCpp,
                BondLibObjPtr,
                CleanPrice,
                IborIndexLibObjPtr,
                SpreadCpp,
                FloatingLegScheduleLibObjPtr,
                FloatingLegDayCounterEnum,
                ParAssetSwapCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAssetSwap : " << e.what());
        }
    }


    std::string qlAssetSwap2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ParAssetSwap,
            const std::string &Bond,
            const double &CleanPrice,
            const double &NonParRepayment,
            const ObjectHandler::property_t &Gearing,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &FloatingLegDayCounter,
            const ObjectHandler::property_t &DealMaturity,
            const ObjectHandler::property_t &PayBondCoupon,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool ParAssetSwapCpp = ObjectHandler::convert2<bool>(
            ParAssetSwap, "ParAssetSwap", true);

        double GearingCpp = ObjectHandler::convert2<double>(
            Gearing, "Gearing", 1.0);

        double SpreadCpp = ObjectHandler::convert2<double>(
            Spread, "Spread", 0.0);

        std::string FloatingLegDayCounterCpp = ObjectHandler::convert2<std::string>(
            FloatingLegDayCounter, "FloatingLegDayCounter", "QuantLib::DayCounter()");

        bool PayBondCouponCpp = ObjectHandler::convert2<bool>(
            PayBondCoupon, "PayBondCoupon", false);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DealMaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            DealMaturity, "DealMaturity", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FloatingLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FloatingLegDayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAssetSwap2(
                ObjectId,
                ParAssetSwapCpp,
                Bond,
                CleanPrice,
                NonParRepayment,
                GearingCpp,
                IborIndex,
                SpreadCpp,
                FloatingLegDayCounterCpp,
                DealMaturity,
                PayBondCouponCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AssetSwap(
                valueObject,
                ParAssetSwapCpp,
                BondLibObjPtr,
                CleanPrice,
                NonParRepayment,
                GearingCpp,
                IborIndexLibObjPtr,
                SpreadCpp,
                FloatingLegDayCounterEnum,
                DealMaturityLib,
                PayBondCouponCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAssetSwap2 : " << e.what());
        }
    }

}

