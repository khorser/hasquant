
/*  
 Copyright (C) 2004, 2005, 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2004, 2005, 2006, 2007, 2011 Eric Ehlers
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
#include <oh/utilities.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string ohVersion(
            const ObjectHandler::property_t &Trigger) {

        try {

        // invoke the utility function

        std::string returnValue = ObjectHandler::version();

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohVersion : " << e.what());
        }
    }

}

