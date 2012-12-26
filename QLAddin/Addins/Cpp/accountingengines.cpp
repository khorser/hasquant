
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
#include <qlo/accountingengines.hpp>
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/products.hpp>
#include <qlo/sequencestatistics.hpp>
#include <ql/models/marketmodels/accountingengine.hpp>
#include <qlo/valueobjects/vo_accountingengines.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAccountingEngine(
            const std::string &ObjectId,
            const std::string &MarketModelEvolver,
            const std::string &Product,
            const double &InitialNumeraireValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelEvolverLibObjPtr, MarketModelEvolver,
            QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)

        OH_GET_UNDERLYING(ProductLibObj, Product,
            QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAccountingEngine(
                ObjectId,
                MarketModelEvolver,
                Product,
                InitialNumeraireValue,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AccountingEngine(
                valueObject,
                MarketModelEvolverLibObjPtr,
                ProductLibObj,
                InitialNumeraireValue,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAccountingEngine : " << e.what());
        }
    }

}

