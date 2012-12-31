
/*  
 Copyright (C) 2006, 2007, 2008, 2011 Ferdinando Ametrano
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
#include <qlo/capfloor.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/couponvectors.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <qlo/valueobjects/vo_capfloor.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCapFloor(
            const std::string &ObjectId,
            const std::string &OptionType,
            const std::string &LegID,
            const std::vector<double>& Strikes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CapFloor::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::CapFloor::Type>()(OptionType);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(LegIDLibObj, LegID,
            QuantLibAddin::Leg, QuantLib::Leg)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCapFloor(
                ObjectId,
                OptionType,
                LegID,
                Strikes,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CapFloor(
                valueObject,
                OptionTypeEnum,
                LegIDLibObj,
                Strikes,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCapFloor : " << e.what());
        }
    }


    std::string qlMakeCapFloor(
            const std::string &ObjectId,
            const std::string &OptionType,
            const std::string &Length,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Strike,
            const std::string &ForwardStart,
            const std::string &PricingEngineID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double StrikeCpp = ObjectHandler::convert2<double>(
            Strike, "Strike", QuantLib::Null<QuantLib::Rate>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeCapFloor(
                ObjectId,
                OptionType,
                Length,
                IborIndex,
                StrikeCpp,
                ForwardStart,
                PricingEngineID,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CapFloor(
                valueObject,
                OptionTypeEnum,
                LengthLib,
                IborIndexLibObjPtr,
                StrikeCpp,
                ForwardStartLib,
                PricingEngineIDLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMakeCapFloor : " << e.what());
        }
    }

}

