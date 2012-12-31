
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 
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
#include <qlo/optimization.hpp>
#include <ql/math/optimization/spherecylinder.hpp>
#include <ql/math/optimization/endcriteria.hpp>
#include <qlo/valueobjects/vo_optimization.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlArmijoLineSearch(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Epsilon,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double EpsilonCpp = ObjectHandler::convert2<double>(
            Epsilon, "Epsilon", 1e-8);

        double AlphaCpp = ObjectHandler::convert2<double>(
            Alpha, "Alpha", 0.05);

        double BetaCpp = ObjectHandler::convert2<double>(
            Beta, "Beta", 0.65);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlArmijoLineSearch(
                ObjectId,
                EpsilonCpp,
                AlphaCpp,
                BetaCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ArmijoLineSearch(
                valueObject,
                EpsilonCpp,
                AlphaCpp,
                BetaCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlArmijoLineSearch : " << e.what());
        }
    }


    std::string qlConjugateGradient(
            const std::string &ObjectId,
            const ObjectHandler::property_t &LineSearch,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string LineSearchCpp = ObjectHandler::convert2<std::string>(
            LineSearch, "LineSearch", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(LineSearchLibObjPtr, LineSearchCpp,
            QuantLibAddin::LineSearch, QuantLib::LineSearch)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlConjugateGradient(
                ObjectId,
                LineSearchCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ConjugateGradient(
                valueObject,
                LineSearchLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlConjugateGradient : " << e.what());
        }
    }


    std::string qlEndCriteria(
            const std::string &ObjectId,
            const long &MaxIterations,
            const long &MaxStationaryStateIterations,
            const double &RootEpsilon,
            const double &FunctionEpsilon,
            const double &GradientNormEpsilon,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEndCriteria(
                ObjectId,
                MaxIterations,
                MaxStationaryStateIterations,
                RootEpsilon,
                FunctionEpsilon,
                GradientNormEpsilon,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EndCriteria(
                valueObject,
                MaxIterations,
                MaxStationaryStateIterations,
                RootEpsilon,
                FunctionEpsilon,
                GradientNormEpsilon,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEndCriteria : " << e.what());
        }
    }


    std::string qlLevenbergMarquardt(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Epsfcn,
            const ObjectHandler::property_t &Xtol,
            const ObjectHandler::property_t &Gtol,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double EpsfcnCpp = ObjectHandler::convert2<double>(
            Epsfcn, "Epsfcn", 1.0e-8);

        double XtolCpp = ObjectHandler::convert2<double>(
            Xtol, "Xtol", 1.0e-8);

        double GtolCpp = ObjectHandler::convert2<double>(
            Gtol, "Gtol", 1.0e-8);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLevenbergMarquardt(
                ObjectId,
                EpsfcnCpp,
                XtolCpp,
                GtolCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LevenbergMarquardt(
                valueObject,
                EpsfcnCpp,
                XtolCpp,
                GtolCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLevenbergMarquardt : " << e.what());
        }
    }


    std::string qlSimplex(
            const std::string &ObjectId,
            const double &Lambda,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSimplex(
                ObjectId,
                Lambda,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Simplex(
                valueObject,
                Lambda,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSimplex : " << e.what());
        }
    }


    std::string qlSteepestDescent(
            const std::string &ObjectId,
            const ObjectHandler::property_t &LineSearch,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string LineSearchCpp = ObjectHandler::convert2<std::string>(
            LineSearch, "LineSearch", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(LineSearchLibObjPtr, LineSearchCpp,
            QuantLibAddin::LineSearch, QuantLib::LineSearch)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSteepestDescent(
                ObjectId,
                LineSearchCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SteepestDescent(
                valueObject,
                LineSearchLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSteepestDescent : " << e.what());
        }
    }

}

