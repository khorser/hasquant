
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

#include <qlo/serialization/create/create_leg.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/couponvectors.hpp>
#include <qlo/capfloor.hpp>
#include <qlo/swap.hpp>
#include <ql/instruments/swap.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlInterestRate(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Rate =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rate"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string Compounding =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Compounding"));

        std::string Frequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Frequency"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(Compounding);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(Frequency);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterestRate(
                valueObject,
                Rate,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> Amounts =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Amounts"), "Amounts");

        std::vector<ObjectHandler::property_t> Dates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Dates"), "Dates");

        bool ToBeSorted =
            ObjectHandler::convert2<bool>(valueObject->getProperty("ToBeSorted"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(Dates, "Dates");

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                Amounts,
                DatesLib,
                ToBeSorted,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLegFromCapFloor(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string CapFloor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CapFloor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(CapFloorLibObjPtr, CapFloor,
            QuantLibAddin::CapFloor, QuantLib::CapFloor)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(CapFloor);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                CapFloorLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLegFromSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Swap =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Swap"));

        long LegNumber =
            ObjectHandler::convert2<long>(valueObject->getProperty("LegNumber"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapLibObjPtr, Swap,
            QuantLibAddin::Swap, QuantLib::Swap)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Swap);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                SwapLibObjPtr,
                LegNumber,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMultiPhaseLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::string> LegIDs =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("LegIDs"), "LegIDs");

        bool ToBeSorted =
            ObjectHandler::convert2<bool>(valueObject->getProperty("ToBeSorted"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Leg> > LegIDsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Leg>(LegIDs);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = LegIDs.begin();
                i != LegIDs.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiPhaseLeg(
                valueObject,
                LegIDsObjPtr,
                ToBeSorted,
                Permanent));
        return object;
    }

}
