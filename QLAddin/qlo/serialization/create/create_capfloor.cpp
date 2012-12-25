
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

#include <qlo/serialization/create/create_capfloor.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/capfloor.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/couponvectors.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <ql/indexes/iborindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCapFloor(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OptionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionType"));

        std::string LegID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LegID"));

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CapFloor::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::CapFloor::Type>()(OptionType);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(LegIDLibObj, LegID,
            QuantLibAddin::Leg, QuantLib::Leg)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(LegID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CapFloor(
                valueObject,
                OptionTypeEnum,
                LegIDLibObj,
                Strikes,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeCapFloor(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OptionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionType"));

        std::string Length =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Length"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        std::string PricingEngineID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PricingEngineID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period LengthLib;
        QuantLibAddin::cppToLibrary(Length, LengthLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CapFloor::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::CapFloor::Type>()(OptionType);

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
            new QuantLibAddin::CapFloor(
                valueObject,
                OptionTypeEnum,
                LengthLib,
                IborIndexLibObjPtr,
                Strike,
                ForwardStartLib,
                PricingEngineIDLibObjPtr,
                Permanent));
        return object;
    }

}
