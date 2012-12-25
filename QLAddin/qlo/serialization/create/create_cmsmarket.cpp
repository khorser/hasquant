
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

#include <qlo/serialization/create/create_cmsmarket.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/quote.hpp>
#include <qlo/cmsmarket.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCmsMarket(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> SwapLengths =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("SwapLengths"), "SwapLengths");

        std::vector<std::string> SwapIndexes =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("SwapIndexes"), "SwapIndexes");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::vector<std::vector<ObjectHandler::property_t> > BidAskSpreads =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("BidAskSpreads"), "BidAskSpreads");

        std::vector<std::string> CmsCouponPricers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("CmsCouponPricers"), "CmsCouponPricers");

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> SwapLengthsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(SwapLengths, "SwapLengths");

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::SwapIndex> > SwapIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::SwapIndex, QuantLib::SwapIndex>(SwapIndexes);

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > BidAskSpreadsLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(BidAskSpreads, "BidAskSpreads");

        std::vector<boost::shared_ptr<QuantLib::CmsCouponPricer> > CmsCouponPricersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::CmsCouponPricer, QuantLib::CmsCouponPricer>(CmsCouponPricers);

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = SwapIndexes.begin();
                i != SwapIndexes.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processVariant(BidAskSpreads);
        for (std::vector<std::string>::const_iterator i = CmsCouponPricers.begin();
                i != CmsCouponPricers.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsMarket(
                valueObject,
                SwapLengthsLib,
                SwapIndexesLibObjPtr,
                IborIndexLibObjPtr,
                BidAskSpreadsLibObj,
                CmsCouponPricersLibObjPtr,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

}
