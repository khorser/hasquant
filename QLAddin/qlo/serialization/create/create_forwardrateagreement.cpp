
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

#include <qlo/serialization/create/create_forwardrateagreement.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/forwardrateagreement.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <ql/indexes/iborindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlFRA(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ValueDate =
            valueObject->getProperty("ValueDate");

        ObjectHandler::property_t MaturityDate =
            valueObject->getProperty("MaturityDate");

        std::string Position =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Position"));

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        double Notional =
            ObjectHandler::convert2<double>(valueObject->getProperty("Notional"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ValueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ValueDate"), "ValueDate");

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("MaturityDate"), "MaturityDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Position::Type PositionEnum =
            ObjectHandler::Create<QuantLib::Position::Type>()(Position);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardRateAgreement(
                valueObject,
                ValueDateLib,
                MaturityDateLib,
                PositionEnum,
                Strike,
                Notional,
                IborIndexLibObjPtr,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

}
