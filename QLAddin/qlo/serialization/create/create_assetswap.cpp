
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

#include <qlo/serialization/create/create_assetswap.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/assetswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/bonds.hpp>
#include <ql/instruments/assetswap.hpp>
#include <ql/indexes/iborindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlAssetSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        bool PayBondCoupon =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayBondCoupon"));

        std::string Bond =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Bond"));

        double CleanPrice =
            ObjectHandler::convert2<double>(valueObject->getProperty("CleanPrice"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string FloatingLegSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FloatingLegSchedule"));

        std::string FloatingLegDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FloatingLegDayCounter"));

        bool ParAssetSwap =
            ObjectHandler::convert2<bool>(valueObject->getProperty("ParAssetSwap"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FloatingLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FloatingLegDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE_DEFAULT(FloatingLegScheduleLibObjPtr, FloatingLegSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Bond);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(FloatingLegSchedule);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AssetSwap(
                valueObject,
                PayBondCoupon,
                BondLibObjPtr,
                CleanPrice,
                IborIndexLibObjPtr,
                Spread,
                FloatingLegScheduleLibObjPtr,
                FloatingLegDayCounterEnum,
                ParAssetSwap,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlAssetSwap2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        bool ParAssetSwap =
            ObjectHandler::convert2<bool>(valueObject->getProperty("ParAssetSwap"));

        std::string Bond =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Bond"));

        double CleanPrice =
            ObjectHandler::convert2<double>(valueObject->getProperty("CleanPrice"));

        double NonParRepayment =
            ObjectHandler::convert2<double>(valueObject->getProperty("NonParRepayment"));

        double Gearing =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string FloatingLegDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FloatingLegDayCounter"));

        ObjectHandler::property_t DealMaturity =
            valueObject->getProperty("DealMaturity");

        bool PayBondCoupon =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayBondCoupon"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date DealMaturityLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("DealMaturity"), "DealMaturity", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FloatingLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FloatingLegDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Bond);
        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AssetSwap(
                valueObject,
                ParAssetSwap,
                BondLibObjPtr,
                CleanPrice,
                NonParRepayment,
                Gearing,
                IborIndexLibObjPtr,
                Spread,
                FloatingLegDayCounterEnum,
                DealMaturityLib,
                PayBondCoupon,
                Permanent));
        return object;
    }

}
