
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

#include <qlo/serialization/create/create_randomsequencegenerator.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>

#include <qlo/randomsequencegenerator.hpp>
#include <qlo/valueobjects/vo_randomsequencegenerator.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlFaureRsg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long Dimension =
            ObjectHandler::convert2<long>(valueObject->getProperty("Dimension"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FaureRsg(
                valueObject,
                Dimension,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlHaltonRsg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long Dimension =
            ObjectHandler::convert2<long>(valueObject->getProperty("Dimension"));

        long Seed =
            ObjectHandler::convert2<long>(valueObject->getProperty("Seed"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HaltonRsg(
                valueObject,
                Dimension,
                Seed,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMersenneTwisterRsg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long Dimension =
            ObjectHandler::convert2<long>(valueObject->getProperty("Dimension"));

        long Seed =
            ObjectHandler::convert2<long>(valueObject->getProperty("Seed"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MersenneTwisterRsg(
                valueObject,
                Dimension,
                Seed,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSobolRsg(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long Dimension =
            ObjectHandler::convert2<long>(valueObject->getProperty("Dimension"));

        long Seed =
            ObjectHandler::convert2<long>(valueObject->getProperty("Seed"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SobolRsg(
                valueObject,
                Dimension,
                Seed,
                Permanent));
        return object;
    }

}
