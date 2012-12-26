
/*  
 Copyright (C) 2006 Katiuscia Manzoni
 Copyright (C) 2006 Ferdinando Ametrano
 
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
#include <oh/enumerations/typefactory.hpp>
#include <qlo/forwardrateagreement.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <ql/indexes/iborindex.hpp>
#include <qlo/valueobjects/vo_forwardrateagreement.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlFRA(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ValueDate,
            const ObjectHandler::property_t &MaturityDate,
            const std::string &Position,
            const double &Strike,
            const double &Notional,
            const std::string &IborIndex,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ValueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ValueDate, "ValueDate");

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            MaturityDate, "MaturityDate");

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFRA(
                ObjectId,
                ValueDate,
                MaturityDate,
                Position,
                Strike,
                Notional,
                IborIndex,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
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
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFRA : " << e.what());
        }
    }

}

