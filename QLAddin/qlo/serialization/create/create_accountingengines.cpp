
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

#include <qlo/serialization/create/create_accountingengines.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/accountingengines.hpp>
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/products.hpp>
#include <qlo/sequencestatistics.hpp>
#include <ql/models/marketmodels/accountingengine.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlAccountingEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string MarketModelEvolver =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("MarketModelEvolver"));

        std::string Product =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Product"));

        double InitialNumeraireValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialNumeraireValue"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelEvolverLibObjPtr, MarketModelEvolver,
            QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)

        OH_GET_UNDERLYING(ProductLibObj, Product,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(MarketModelEvolver);
        valueObject->processPrecedentID(Product);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AccountingEngine(
                valueObject,
                MarketModelEvolverLibObjPtr,
                ProductLibObj,
                InitialNumeraireValue,
                Permanent));
        return object;
    }

}
