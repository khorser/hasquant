
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 
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
#include <qlo/abcd.hpp>
#include <qlo/optimization.hpp>
#include <ql/termstructures/volatility/abcd.hpp>
#include <ql/termstructures/volatility/abcdcalibration.hpp>
#include <qlo/valueobjects/vo_abcd.hpp>
#include <qlo/loop/loop_abcd.hpp>
#include <Addins/Cpp/loop.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAbcdCalibration(
            const std::string &ObjectId,
            const std::vector<double>& Times,
            const std::vector<double>& BlackVols,
            const ObjectHandler::property_t &A,
            const ObjectHandler::property_t &B,
            const ObjectHandler::property_t &C,
            const ObjectHandler::property_t &D,
            const ObjectHandler::property_t &AIsFixed,
            const ObjectHandler::property_t &BIsFixed,
            const ObjectHandler::property_t &CIsFixed,
            const ObjectHandler::property_t &DIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double ACpp = ObjectHandler::convert2<double>(
            A, "A", -0.06);

        double BCpp = ObjectHandler::convert2<double>(
            B, "B", 0.17);

        double CCpp = ObjectHandler::convert2<double>(
            C, "C", 0.54);

        double DCpp = ObjectHandler::convert2<double>(
            D, "D", 0.17);

        bool AIsFixedCpp = ObjectHandler::convert2<bool>(
            AIsFixed, "AIsFixed", false);

        bool BIsFixedCpp = ObjectHandler::convert2<bool>(
            BIsFixed, "BIsFixed", false);

        bool CIsFixedCpp = ObjectHandler::convert2<bool>(
            CIsFixed, "CIsFixed", false);

        bool DIsFixedCpp = ObjectHandler::convert2<bool>(
            DIsFixed, "DIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            VegaWeighted, "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            Method, "Method", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdCalibration(
                ObjectId,
                Times,
                BlackVols,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                AIsFixedCpp,
                BIsFixedCpp,
                CIsFixedCpp,
                DIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                MethodCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdCalibration(
                valueObject,
                Times,
                BlackVols,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                AIsFixedCpp,
                BIsFixedCpp,
                CIsFixedCpp,
                DIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAbcdCalibration : " << e.what());
        }
    }


    std::string qlAbcdFunction(
            const std::string &ObjectId,
            const ObjectHandler::property_t &A,
            const ObjectHandler::property_t &B,
            const ObjectHandler::property_t &C,
            const ObjectHandler::property_t &D,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double ACpp = ObjectHandler::convert2<double>(
            A, "A", -0.06);

        double BCpp = ObjectHandler::convert2<double>(
            B, "B", 0.17);

        double CCpp = ObjectHandler::convert2<double>(
            C, "C", 0.54);

        double DCpp = ObjectHandler::convert2<double>(
            D, "D", 0.17);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdFunction(
                ObjectId,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdFunction(
                valueObject,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAbcdFunction : " << e.what());
        }
    }

}

