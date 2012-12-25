
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

#include <qlo/serialization/create/create_cmsmarketcalibration.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/cmsmarketcalibration.hpp>
#include <qlo/cmsmarket.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/optimization.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube1.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCmsMarketCalibration(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string VolCube =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("VolCube"));

        std::string CmsMarket =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CmsMarket"));

        std::vector<std::vector<double> > Weights =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Weights"), "Weights");

        std::string CalibrationType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CalibrationType"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix WeightsLib =
            QuantLibAddin::vvToQlMatrix(Weights);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CmsMarketCalibration::CalibrationType CalibrationTypeEnum =
            ObjectHandler::Create<QuantLib::CmsMarketCalibration::CalibrationType>()(CalibrationType);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolCubeCoerce, VolCube, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> VolCubeLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    VolCubeCoerce);

        OH_GET_REFERENCE(CmsMarketLibObjPtr, CmsMarket,
            QuantLibAddin::CmsMarket, QuantLib::CmsMarket)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(VolCube);
        valueObject->processPrecedentID(CmsMarket);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsMarketCalibration(
                valueObject,
                VolCubeLibObj,
                CmsMarketLibObjPtr,
                WeightsLib,
                CalibrationTypeEnum,
                Permanent));
        return object;
    }

}
