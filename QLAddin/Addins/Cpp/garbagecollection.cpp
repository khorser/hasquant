
/*  
 Copyright (C) 2004, 2005 Ferdinando Ametrano
 Copyright (C) 2004, 2005, 2006 Eric Ehlers
 Copyright (C) 2005, 2006 Plamen Neykov
 Copyright (C) 2004 StatPro Italia srl
 
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

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    bool ohRepositoryDeleteAllObjects(
            const ObjectHandler::property_t &DeletePermanent,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        bool DeletePermanentCpp = ObjectHandler::convert2<bool>(
            DeletePermanent, "DeletePermanent", false);

        // invoke the utility function

        static bool returnValue = true;
        ObjectHandler::Repository::instance().deleteAllObjects(
                DeletePermanentCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohRepositoryDeleteAllObjects : " << e.what());
        }
    }


    bool ohRepositoryLogObject(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // invoke the utility function

        static bool returnValue = true;
        ObjectHandler::logObject(
                ObjectId);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohRepositoryLogObject : " << e.what());
        }
    }

}

