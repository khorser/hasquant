
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

#include <qlo/serialization/create/create_swaption.hpp>
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

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeSwaption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        std::string OptionTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionTenor"));

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        std::string PricingEngineID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PricingEngineID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(PricingEngineIDLibObjPtr, PricingEngineID,
            QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SwapIndex);
        valueObject->processPrecedentID(PricingEngineID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swaption(
                valueObject,
                SwapIndexLibObjPtr,
                OptionTenorLib,
                Strike,
                PricingEngineIDLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwaption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string VanillaSwap =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("VanillaSwap"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        std::string SettlementType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SettlementType"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Settlement::Type SettlementTypeEnum =
            ObjectHandler::Create<QuantLib::Settlement::Type>()(SettlementType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(VanillaSwapLibObjPtr, VanillaSwap,
            QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::EuropeanExercise, QuantLib::EuropeanExercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(VanillaSwap);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swaption(
                valueObject,
                VanillaSwapLibObjPtr,
                ExerciseLibObjPtr,
                SettlementTypeEnum,
                Permanent));
        return object;
    }

}
