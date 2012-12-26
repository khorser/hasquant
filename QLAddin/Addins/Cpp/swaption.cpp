
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Cristina Duminuco
 Copyright (C) 2006 Eric Ehlers
 
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
#include <qlo/swaption.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/vanillaswap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/exercise.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/exercise.hpp>
#include <qlo/valueobjects/vo_swaption.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlMakeSwaption(
            const std::string &ObjectId,
            const std::string &SwapIndex,
            const std::string &OptionTenor,
            const ObjectHandler::property_t &Strike,
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

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMakeSwaption(
                ObjectId,
                SwapIndex,
                OptionTenor,
                StrikeCpp,
                PricingEngineID,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swaption(
                valueObject,
                SwapIndexLibObjPtr,
                OptionTenorLib,
                StrikeCpp,
                PricingEngineIDLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMakeSwaption : " << e.what());
        }
    }


    std::string qlSwaption(
            const std::string &ObjectId,
            const std::string &VanillaSwap,
            const std::string &Exercise,
            const std::string &SettlementType,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Settlement::Type SettlementTypeEnum =
            ObjectHandler::Create<QuantLib::Settlement::Type>()(SettlementType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(VanillaSwapLibObjPtr, VanillaSwap,
            QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::EuropeanExercise, QuantLib::EuropeanExercise)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaption(
                ObjectId,
                VanillaSwap,
                Exercise,
                SettlementType,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swaption(
                valueObject,
                VanillaSwapLibObjPtr,
                ExerciseLibObjPtr,
                SettlementTypeEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSwaption : " << e.what());
        }
    }

}

