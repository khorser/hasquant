
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

#include <qlo/serialization/create/create_driftcalculators.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>

#include <qlo/driftcalculators.hpp>
#include <qlo/valueobjects/vo_driftcalculators.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCMSMMDriftCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_root =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Pseudo_square_root"), "Pseudo_square_root");

        std::vector<double> Displacements =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Displacements"), "Displacements");

        std::vector<double> Taus =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Taus"), "Taus");

        long Numeraire =
            ObjectHandler::convert2<long>(valueObject->getProperty("Numeraire"));

        long Alive =
            ObjectHandler::convert2<long>(valueObject->getProperty("Alive"));

        long SpanningFwds =
            ObjectHandler::convert2<long>(valueObject->getProperty("SpanningFwds"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibAddin::vvToQlMatrix(Pseudo_square_root);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CMSMMDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                Displacements,
                Taus,
                Numeraire,
                Alive,
                SpanningFwds,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLMMDriftCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_root =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Pseudo_square_root"), "Pseudo_square_root");

        std::vector<double> Displacements =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Displacements"), "Displacements");

        std::vector<double> Taus =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Taus"), "Taus");

        long Numeraire =
            ObjectHandler::convert2<long>(valueObject->getProperty("Numeraire"));

        long Alive =
            ObjectHandler::convert2<long>(valueObject->getProperty("Alive"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibAddin::vvToQlMatrix(Pseudo_square_root);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LMMDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                Displacements,
                Taus,
                Numeraire,
                Alive,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLMMNormalDriftCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_root =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Pseudo_square_root"), "Pseudo_square_root");

        std::vector<double> Taus =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Taus"), "Taus");

        long Numeraire =
            ObjectHandler::convert2<long>(valueObject->getProperty("Numeraire"));

        long Alive =
            ObjectHandler::convert2<long>(valueObject->getProperty("Alive"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibAddin::vvToQlMatrix(Pseudo_square_root);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LMMNormalDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                Taus,
                Numeraire,
                Alive,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSMMDriftCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Pseudo_square_root =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Pseudo_square_root"), "Pseudo_square_root");

        std::vector<double> Displacements =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Displacements"), "Displacements");

        std::vector<double> Taus =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Taus"), "Taus");

        long Numeraire =
            ObjectHandler::convert2<long>(valueObject->getProperty("Numeraire"));

        long Alive =
            ObjectHandler::convert2<long>(valueObject->getProperty("Alive"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix Pseudo_square_rootLib =
            QuantLibAddin::vvToQlMatrix(Pseudo_square_root);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SMMDriftCalculator(
                valueObject,
                Pseudo_square_rootLib,
                Displacements,
                Taus,
                Numeraire,
                Alive,
                Permanent));
        return object;
    }

}
