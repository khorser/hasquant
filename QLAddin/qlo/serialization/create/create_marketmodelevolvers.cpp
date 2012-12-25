
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

#include <qlo/serialization/create/create_marketmodelevolvers.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/browniangenerators.hpp>
#include <qlo/marketmodels.hpp>
#include <ql/models/marketmodels/evolver.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardRateIpc(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string MarketModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("MarketModel"));

        std::string BrownianGeneratorFactory =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BrownianGeneratorFactory"));

        std::vector<long> Numeraires =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("Numeraires"), "Numeraires");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Size> NumerairesLib = 
            QuantLibAddin::convertVector<long, QuantLib::Size>(Numeraires);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelLibObjPtr, MarketModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, BrownianGeneratorFactory,
            QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(MarketModel);
        valueObject->processPrecedentID(BrownianGeneratorFactory);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LogNormalFwdRateIpc(
                valueObject,
                MarketModelLibObjPtr,
                BrownianGeneratorFactoryLibObj,
                NumerairesLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardRateNormalPc(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string MarketModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("MarketModel"));

        std::string BrownianGeneratorFactory =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BrownianGeneratorFactory"));

        std::vector<long> Numeraires =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("Numeraires"), "Numeraires");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Size> NumerairesLib = 
            QuantLibAddin::convertVector<long, QuantLib::Size>(Numeraires);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelLibObjPtr, MarketModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, BrownianGeneratorFactory,
            QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(MarketModel);
        valueObject->processPrecedentID(BrownianGeneratorFactory);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::NormalFwdRatePc(
                valueObject,
                MarketModelLibObjPtr,
                BrownianGeneratorFactoryLibObj,
                NumerairesLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardRatePc(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string MarketModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("MarketModel"));

        std::string BrownianGeneratorFactory =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BrownianGeneratorFactory"));

        std::vector<long> Numeraires =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("Numeraires"), "Numeraires");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Size> NumerairesLib = 
            QuantLibAddin::convertVector<long, QuantLib::Size>(Numeraires);

        // convert object IDs into library objects

        OH_GET_REFERENCE(MarketModelLibObjPtr, MarketModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, BrownianGeneratorFactory,
            QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(MarketModel);
        valueObject->processPrecedentID(BrownianGeneratorFactory);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LogNormalFwdRatePc(
                valueObject,
                MarketModelLibObjPtr,
                BrownianGeneratorFactoryLibObj,
                NumerairesLib,
                Permanent));
        return object;
    }

}
