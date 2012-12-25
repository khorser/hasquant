
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
#include <qlo/serialization/register/serialization_pricingengines.hpp>
#include <qlo/valueobjects/vo_pricingengines.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>


namespace QuantLibAddin {

    void register_pricingengines(boost::archive::xml_oarchive &ar) {
    
        // class ID 145 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine>();
        // class ID 146 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBinomialPricingEngine>();
        // class ID 147 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator>();
        // class ID 148 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator2>();
        // class ID 149 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine>();
        // class ID 150 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2>();
        // class ID 151 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator>();
        // class ID 152 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator2>();
        // class ID 153 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine>();
        // class ID 154 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2>();
        // class ID 155 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBondEngine>();
        // class ID 156 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlDiscountingSwapEngine>();
        // class ID 157 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPricingEngine>();

    }
    
    void register_pricingengines(boost::archive::xml_iarchive &ar) {
    
        // class ID 145 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine>();
        // class ID 146 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBinomialPricingEngine>();
        // class ID 147 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator>();
        // class ID 148 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator2>();
        // class ID 149 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine>();
        // class ID 150 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2>();
        // class ID 151 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator>();
        // class ID 152 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator2>();
        // class ID 153 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine>();
        // class ID 154 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2>();
        // class ID 155 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBondEngine>();
        // class ID 156 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlDiscountingSwapEngine>();
        // class ID 157 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPricingEngine>();

    }
    
}

