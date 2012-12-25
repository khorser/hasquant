
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

#include <qlo/serialization/create/create_overnightindexedswap.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/overnightindexedswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/ratehelpers.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeDatedOIS(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t EndDate =
            valueObject->getProperty("EndDate");

        std::string OvernightIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OvernightIndex"));

        double FixedRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("FixedRate"));

        std::string FixDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixDayCounter"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate", QuantLib::Date());

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EndDate"), "EndDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(OvernightIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                StartDateLib,
                EndDateLib,
                OvernightIndexLibObjPtr,
                FixedRate,
                FixDayCounterEnum,
                Spread,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeOIS(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapTenor"));

        std::string OvernightIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OvernightIndex"));

        double FixedRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("FixedRate"));

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        std::string FixDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixDayCounter"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

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

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(OvernightIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                SwapTenorLib,
                OvernightIndexLibObjPtr,
                FixedRate,
                ForwardStartLib,
                FixDayCounterEnum,
                Spread,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlOvernightIndexedSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PayerReceiver =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PayerReceiver"));

        std::vector<double> Nominal =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Nominal"), "Nominal");

        std::string Schedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Schedule"));

        double FixedRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("FixedRate"));

        std::string FixDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixDayCounter"));

        std::string OvernightIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OvernightIndex"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> NominalLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Nominal);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::OvernightIndexedSwap::Type PayerReceiverEnum =
            ObjectHandler::Create<QuantLib::OvernightIndexedSwap::Type>()(PayerReceiver);

        QuantLib::DayCounter FixDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ScheduleLibObjPtr, Schedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_REFERENCE(OvernightIndexLibObjPtr, OvernightIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Schedule);
        valueObject->processPrecedentID(OvernightIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                PayerReceiverEnum,
                NominalLib,
                ScheduleLibObjPtr,
                FixedRate,
                FixDayCounterEnum,
                OvernightIndexLibObjPtr,
                Spread,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlOvernightIndexedSwapFromOISRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OISRateHelper =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OISRateHelper"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(OISRateHelperLibObjPtr, OISRateHelper,
            QuantLibAddin::OISRateHelper, QuantLib::OISRateHelper)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(OISRateHelper);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndexedSwap(
                valueObject,
                OISRateHelperLibObjPtr,
                Permanent));
        return object;
    }

}
