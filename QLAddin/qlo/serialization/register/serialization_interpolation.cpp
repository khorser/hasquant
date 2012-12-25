
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
//      gensrc/gensrc/stubs/stub.serialization.body

#include <oh/ohdefines.hpp>
#include <qlo/serialization/register/serialization_interpolation.hpp>
#include <qlo/valueobjects/vo_interpolation.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>


namespace QuantLibAddin {

    void register_interpolation(boost::archive::xml_oarchive &ar) {
    
        // class ID 94 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlAbcdInterpolation>();
        // class ID 95 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlCubicInterpolation>();
        // class ID 96 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlInterpolation>();
        // class ID 97 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlInterpolation2D>();
        // class ID 98 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlMixedLinearCubicInterpolation>();
        // class ID 99 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlSABRInterpolation>();

    }
    
    void register_interpolation(boost::archive::xml_iarchive &ar) {
    
        // class ID 94 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlAbcdInterpolation>();
        // class ID 95 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlCubicInterpolation>();
        // class ID 96 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlInterpolation>();
        // class ID 97 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlInterpolation2D>();
        // class ID 98 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlMixedLinearCubicInterpolation>();
        // class ID 99 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlSABRInterpolation>();

    }
    
}

