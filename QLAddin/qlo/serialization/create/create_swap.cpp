
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

#include <qlo/serialization/create/create_swap.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/swap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/conundrumpricer.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlMakeCms(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapTenor"));

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double IborSpread =
            ObjectHandler::convert2<double>(valueObject->getProperty("IborSpread"));

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        std::string CmsCouponPricer =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CmsCouponPricer"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_REFERENCE(CmsCouponPricerLibObjPtr, CmsCouponPricer,
            QuantLibAddin::CmsCouponPricer, QuantLib::CmsCouponPricer)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SwapIndex);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(CmsCouponPricer);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swap(
                valueObject,
                SwapTenorLib,
                SwapIndexLibObjPtr,
                IborIndexLibObjPtr,
                IborSpread,
                ForwardStartLib,
                CmsCouponPricerLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::string> LegIDs =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("LegIDs"), "LegIDs");

        std::vector<bool> Payer =
            ObjectHandler::vector::convert2<bool>(valueObject->getProperty("Payer"), "Payer");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Leg> > LegIDsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Leg>(LegIDs);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = LegIDs.begin();
                i != LegIDs.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Swap(
                valueObject,
                LegIDsObjPtr,
                Payer,
                Permanent));
        return object;
    }

}
