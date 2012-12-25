
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

#include <qlo/serialization/create/create_mathf.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/mathf.hpp>
#include <ql/math/primenumbers.hpp>
#include <ql/math/matrixutilities/pseudosqrt.hpp>
#include <ql/math/matrixutilities/choleskydecomposition.hpp>
#include <qlo/symmetricschurdecomposition.hpp>
#include <qlo/getcovariance.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCovarianceDecomposition(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > SymmetricMatrix =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("SymmetricMatrix"), "SymmetricMatrix");

        double Tolerance =
            ObjectHandler::convert2<double>(valueObject->getProperty("Tolerance"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix SymmetricMatrixLib =
            QuantLibAddin::vvToQlMatrix(SymmetricMatrix);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CovarianceDecomposition(
                valueObject,
                SymmetricMatrixLib,
                Tolerance,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSymmetricSchurDecomposition(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > SymmetricMatrix =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("SymmetricMatrix"), "SymmetricMatrix");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix SymmetricMatrixLib =
            QuantLibAddin::vvToQlMatrix(SymmetricMatrix);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SymmetricSchurDecomposition(
                valueObject,
                SymmetricMatrixLib,
                Permanent));
        return object;
    }

}
