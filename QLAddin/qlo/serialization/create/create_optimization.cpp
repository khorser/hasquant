
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

#include <qlo/serialization/create/create_optimization.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>

#include <qlo/optimization.hpp>
#include <qlo/valueobjects/vo_optimization.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlArmijoLineSearch(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Epsilon =
            ObjectHandler::convert2<double>(valueObject->getProperty("Epsilon"));

        double Alpha =
            ObjectHandler::convert2<double>(valueObject->getProperty("Alpha"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ArmijoLineSearch(
                valueObject,
                Epsilon,
                Alpha,
                Beta,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlConjugateGradient(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string LineSearch =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LineSearch"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(LineSearchLibObjPtr, LineSearch,
            QuantLibAddin::LineSearch, QuantLib::LineSearch)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(LineSearch);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ConjugateGradient(
                valueObject,
                LineSearchLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEndCriteria(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long MaxIterations =
            ObjectHandler::convert2<long>(valueObject->getProperty("MaxIterations"));

        long MaxStationaryStateIterations =
            ObjectHandler::convert2<long>(valueObject->getProperty("MaxStationaryStateIterations"));

        double RootEpsilon =
            ObjectHandler::convert2<double>(valueObject->getProperty("RootEpsilon"));

        double FunctionEpsilon =
            ObjectHandler::convert2<double>(valueObject->getProperty("FunctionEpsilon"));

        double GradientNormEpsilon =
            ObjectHandler::convert2<double>(valueObject->getProperty("GradientNormEpsilon"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EndCriteria(
                valueObject,
                MaxIterations,
                MaxStationaryStateIterations,
                RootEpsilon,
                FunctionEpsilon,
                GradientNormEpsilon,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLevenbergMarquardt(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Epsfcn =
            ObjectHandler::convert2<double>(valueObject->getProperty("Epsfcn"));

        double Xtol =
            ObjectHandler::convert2<double>(valueObject->getProperty("Xtol"));

        double Gtol =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gtol"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LevenbergMarquardt(
                valueObject,
                Epsfcn,
                Xtol,
                Gtol,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSimplex(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Lambda =
            ObjectHandler::convert2<double>(valueObject->getProperty("Lambda"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Simplex(
                valueObject,
                Lambda,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSteepestDescent(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string LineSearch =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LineSearch"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(LineSearchLibObjPtr, LineSearch,
            QuantLibAddin::LineSearch, QuantLib::LineSearch)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(LineSearch);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SteepestDescent(
                valueObject,
                LineSearchLibObjPtr,
                Permanent));
        return object;
    }

}
