
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2005 Walter Penschke
 
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
#include <qlo/baseinstruments.hpp>
#include <qlo/pricingengines.hpp>
#include <ql/instrument.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    double qlInstrumentNPV(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Instrument, QuantLib::Instrument)

        // invoke the member function

        double returnValue = ObjectIdLibObjPtr->NPV();

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInstrumentNPV : " << e.what());
        }
    }


    bool qlInstrumentSetPricingEngine(
            const std::string &ObjectId,
            const std::string &PricingEngine,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Instrument)

        OH_GET_OBJECT(PricingEngineObjPtr, PricingEngine, QuantLibAddin::PricingEngine)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->setPricingEngine(
                PricingEngineObjPtr);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInstrumentSetPricingEngine : " << e.what());
        }
    }


    long qlInstrumentValuationDate(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Instrument, QuantLib::Instrument)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->valuationDate();

        // convert and return the return value

        long returnValueLib = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return returnValueLib;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInstrumentValuationDate : " << e.what());
        }
    }

}

